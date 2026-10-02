from __future__ import annotations

import json
import hashlib
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import layout_check
import project_state


def object_fixture(next_offset=0x10, extent=0x30):
    names = b"\0.text\0.symtab\0.strtab\0.shstrtab\0"
    strings = b"\0func_test\0func_next\0"
    symbols = bytes(16) + struct.pack(">IIIBBH", 1, 0, 16, 0x12, 0, 1)
    symbols += struct.pack(">IIIBBH", 11, next_offset, 16, 0x12, 0, 1)
    sections = [(0, 0, 0, b"", 0, 0, 0, 0), (1, 1, 6, bytes(extent), 0, 0, 16, 0),
                (7, 2, 0, symbols, 3, 1, 4, 16), (15, 3, 0, strings, 0, 0, 1, 0),
                (23, 3, 0, names, 0, 0, 1, 0)]
    body = bytearray(52)
    headers = []
    for name, kind, flags, data, link, info, align, entsize in sections:
        body.extend(bytes(-len(body) % 4))
        headers.append(struct.pack(">10I", name, kind, flags, 0, len(body), len(data), link, info, align, entsize))
        body.extend(data)
    body.extend(bytes(-len(body) % 4))
    offset = len(body)
    body.extend(b"".join(headers))
    body[:52] = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                            1, 8, 1, 0, 0, offset, 0, 52, 0, 0, 40, len(sections), 4)
    return bytes(body)


class LayoutDeferralTests(unittest.TestCase):
    def fixture(self, root):
        source = root / "src/main/test.c"
        source.parent.mkdir(parents=True)
        source.write_text('void func_test(void) { work(); }\n'
                          '#pragma GLOBAL_ASM("asm/nonmatchings/main/test/func_next.s")\n')
        asm = root / "asm/nonmatchings/main/test/func_next.s"
        asm.parent.mkdir(parents=True)
        asm.write_text("glabel func_next\n")
        functions = [{
            "symbol": name, "source": "src/main/test.c", "overlay": "main",
            "regions": {"us": {"state": "raw_asm", "symbol": name, "vram": hex(address)}},
        } for name, address in (("func_test", 0x80001000), ("func_next", 0x80001020))]
        unit = {
            "source": "src/main/test.c", "functions": ["func_test", "func_next"],
            "integration": "raw_asm",
            "boundary_evidence": {"us": {"reviewed": True}},
            "regions": {"us": {"start": "0x1000", "end": "0x1040", "state": "raw_asm"}},
        }
        inventory = root / "progress/functions.json"
        inventory.parent.mkdir()
        inventory.write_text(json.dumps({"schema_version": 1, "functions": functions}))
        (root / "progress/source_units.json").write_text(json.dumps({"source_units": [unit]}))
        lock = root / "toolchain/tools.lock.json"
        lock.parent.mkdir()
        lock.write_text("{}")
        obj = root / "build/us/layout-check/src/main/test.o"
        obj.parent.mkdir(parents=True)
        obj.write_bytes(object_fixture())
        archive = root / "build/us/deferred-layout/attempt"
        return source, inventory, functions[0], unit, obj, archive

    def make_proof(self, root, fixture):
        source, inventory, function, unit, obj, archive = fixture
        symbols = {"func_test": 0, "func_next": 0x10}
        try:
            layout_check.validate_layout(function, unit, symbols, 0x30, 0x10, "us", root=root)
        except layout_check.LayoutMismatch as error:
            layout_check.archive_layout_failure(
                root, archive, "us", "func_test", function, unit, obj, symbols,
                0x30, 0x10, error, layout_check.failure_inputs(root, function["source"]),
                "func_test: CURRENT (0)\n",
            )
        else:
            self.fail("fixture must have a genuine layout mismatch")
        return archive / "proof.json"

    def defer(self, root, fixture, proof, score=0):
        with patch.object(project_state, "ROOT", root), patch.object(project_state, "FUNCTIONS_FILE", fixture[1]):
            project_state.defer_function(SimpleNamespace(
                symbol="func_test", reason="exact body, shifted successor", score=score,
                layout_failure_proof=str(proof) if proof is not None else None,
            ))

    def test_exact_failed_layout_is_archived_deferred_and_resumable(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            original = fixture[0].read_bytes()
            proof = self.make_proof(root, fixture)
            self.defer(root, fixture, proof)
            entry = json.loads(fixture[1].read_text())["functions"][0]
            self.assertEqual("raw_asm", entry["regions"]["us"]["state"])
            self.assertNotIn("current_score", entry["deferred"])
            self.assertEqual(0, entry["deferred"]["layout_failure"]["focused_current_differences"])
            self.assertEqual(original, (proof.parent / "candidate.c").read_bytes())
            self.assertEqual(fixture[4].read_bytes(), (proof.parent / "candidate.o").read_bytes())
            self.assertIn("#if 0 /* CONKER_DEFERRED_CANDIDATE func_test */", fixture[0].read_text())
            self.assertIn('GLOBAL_ASM("asm/nonmatchings/main/test/func_test.s")', fixture[0].read_text())
            with patch.object(project_state, "ROOT", root), patch.object(project_state, "FUNCTIONS_FILE", fixture[1]):
                project_state.resume_function(SimpleNamespace(symbol="func_test"))
            self.assertEqual(original, fixture[0].read_bytes())

    def test_rejects_missing_stale_or_changed_proof_without_mutation(self):
        for mutation in ("missing", "source", "object", "archived source", "archived object",
                         "focused log", "target", "profile", "metadata", "preserved layout", "unreviewed"):
            with self.subTest(mutation), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                fixture = self.fixture(root)
                proof = self.make_proof(root, fixture)
                receipt = json.loads(proof.read_text())
                if mutation == "missing":
                    proof.unlink()
                elif mutation == "source":
                    fixture[0].write_text(fixture[0].read_text() + "/* changed */\n")
                elif mutation == "object":
                    fixture[4].write_bytes(b"changed")
                elif mutation in ("archived source", "archived object"):
                    (proof.parent / ("candidate.c" if mutation == "archived source" else "candidate.o")).write_bytes(b"changed")
                elif mutation == "focused log":
                    (proof.parent / "focused.log").write_text("func_test: CURRENT (1)\n")
                elif mutation in ("target", "profile"):
                    receipt["identifier" if mutation == "target" else "profile"] = "other"
                    proof.write_text(json.dumps(receipt))
                elif mutation == "preserved layout":
                    receipt.update(symbols={"func_test": 0, "func_next": 0x20}, text_size=0x40)
                    proof.write_text(json.dumps(receipt))
                else:
                    path = root / "progress/source_units.json"
                    if mutation == "metadata":
                        path.write_text(path.read_text() + "\n")
                    else:
                        data = json.loads(path.read_text())
                        data["source_units"][0]["boundary_evidence"]["us"]["reviewed"] = False
                        path.write_text(json.dumps(data))
                        receipt["inputs"] = layout_check.failure_inputs(root, fixture[2]["source"])
                        proof.write_text(json.dumps(receipt))
                before = fixture[0].read_bytes(), fixture[1].read_bytes()
                with self.assertRaises(project_state.ProjectStateError):
                    self.defer(root, fixture, proof)
                self.assertEqual(before, (fixture[0].read_bytes(), fixture[1].read_bytes()))

    def test_zero_without_proof_and_matched_function_are_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            with self.assertRaises(project_state.ProjectStateError):
                self.defer(root, fixture, None)
            proof = self.make_proof(root, fixture)
            data = json.loads(fixture[1].read_text())
            data["functions"][0]["regions"]["us"].update(
                state="matched", evidence={"current_differences": 0,
                                           "rom_sha1": "0" * 40,
                                           "verified_revision": "working-tree"})
            fixture[1].write_text(json.dumps(data))
            with self.assertRaisesRegex(project_state.ProjectStateError, "matched function"):
                self.defer(root, fixture, proof)

    def test_inventory_write_failure_restores_active_c(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            proof = self.make_proof(root, fixture)
            before = fixture[0].read_bytes(), fixture[1].read_bytes()
            def partial_write(path, data):
                path.write_text("partial inventory")
                raise OSError("write failed")
            with patch.object(project_state, "write_json", side_effect=partial_write):
                with self.assertRaises(OSError):
                    self.defer(root, fixture, proof)
            self.assertEqual(before, (fixture[0].read_bytes(), fixture[1].read_bytes()))
            self.assertEqual(before[0], (proof.parent / "candidate.c").read_bytes())

    def test_source_write_failure_rolls_back_source_and_inventory(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            proof = self.make_proof(root, fixture)
            before = fixture[0].read_bytes(), fixture[1].read_bytes()
            original_write = Path.write_text
            failed = False
            def partial_write(path, text, *args, **kwargs):
                nonlocal failed
                if path == fixture[0] and not failed:
                    failed = True
                    original_write(path, "partial source")
                    raise OSError("source write failed")
                return original_write(path, text, *args, **kwargs)
            with patch.object(Path, "write_text", partial_write), self.assertRaises(OSError):
                self.defer(root, fixture, proof)
            self.assertEqual(before, (fixture[0].read_bytes(), fixture[1].read_bytes()))

    def test_changed_inputs_during_compilation_cannot_be_archived(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            inputs = layout_check.failure_inputs(root, fixture[2]["source"])
            fixture[0].write_text(fixture[0].read_text() + "/* changed */\n")
            with self.assertRaisesRegex(layout_check.LayoutError, "changed during compilation"):
                layout_check.archive_layout_failure(
                    root, fixture[5], "us", "func_test", fixture[2], fixture[3], fixture[4],
                    {"func_test": 0, "func_next": 0x10}, 0x30, 0x10,
                    layout_check.LayoutMismatch("shifted"), inputs, "func_test: CURRENT (0)\n",
                )
            self.assertFalse((fixture[5] / "proof.json").exists())

    def test_positive_score_cannot_use_exact_layout_proof(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            proof = self.make_proof(root, fixture)
            with self.assertRaisesRegex(project_state.ProjectStateError, "only to an exact"):
                self.defer(root, fixture, proof, score=1)

    def test_tampered_measurements_cannot_claim_a_preserved_object_failed(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            proof = self.make_proof(root, fixture)
            valid_object = object_fixture(next_offset=0x20, extent=0x40)
            fixture[4].write_bytes(valid_object)
            (proof.parent / "candidate.o").write_bytes(valid_object)
            receipt = json.loads(proof.read_text())
            receipt["object_sha256"] = hashlib.sha256(valid_object).hexdigest()
            # All object hashes agree, but receipt measurements still assert a shift.
            proof.write_text(json.dumps(receipt))
            with self.assertRaisesRegex(project_state.ProjectStateError, "measurements do not match"):
                self.defer(root, fixture, proof)

    def test_rehashed_nonexact_or_wrong_target_focused_log_is_rejected(self):
        for output in ("func_test: CURRENT (1)\n", "other: CURRENT (0)\n",
                       "func_test: CURRENT (0)\nfunc_test: CURRENT (1)\n"):
            with self.subTest(output=output), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                fixture = self.fixture(root)
                proof = self.make_proof(root, fixture)
                (proof.parent / "focused.log").write_text(output)
                receipt = json.loads(proof.read_text())
                receipt["focused_log_sha256"] = hashlib.sha256(output.encode()).hexdigest()
                proof.write_text(json.dumps(receipt))
                with self.assertRaisesRegex(project_state.ProjectStateError, "exact-target"):
                    self.defer(root, fixture, proof)

    def test_archival_failure_never_creates_authorizing_receipt(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            before = fixture[0].read_bytes(), fixture[1].read_bytes()
            original_open = Path.open
            def fail_object(path, *args, **kwargs):
                if path.name == "candidate.o":
                    raise OSError("archive write failed")
                return original_open(path, *args, **kwargs)
            with patch.object(Path, "open", fail_object), self.assertRaises(OSError):
                self.make_proof(root, fixture)
            self.assertFalse((fixture[5] / "proof.json").exists())
            with self.assertRaises(project_state.ProjectStateError):
                self.defer(root, fixture, fixture[5] / "proof.json")
            self.assertEqual(before, (fixture[0].read_bytes(), fixture[1].read_bytes()))

    def test_compile_tool_and_metadata_errors_do_not_archive_layout_failure(self):
        for failure in (subprocess.CalledProcessError(1, ["compiler"]), OSError("missing tool"), KeyError("metadata")):
            with self.subTest(type(failure).__name__), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                fixture = self.fixture(root)
                argv = ["layout_check.py", "us", "func_test", "--failure-archive", str(fixture[5])]
                with (patch.object(layout_check, "ROOT", root), patch.object(sys, "argv", argv),
                      patch.object(layout_check.subprocess, "run", return_value=SimpleNamespace(stdout="func_test: CURRENT (0)\n")),
                      patch.object(layout_check, "compile_mixed_object", side_effect=failure)):
                    self.assertEqual(1, layout_check.main())
                self.assertFalse((fixture[5] / "proof.json").exists())

    def test_successful_layout_never_creates_deferral_receipt(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            argv = ["layout_check.py", "us", "func_test", "--failure-archive", str(fixture[5])]
            with (patch.object(layout_check, "ROOT", root), patch.object(sys, "argv", argv),
                  patch.object(layout_check.subprocess, "run", return_value=SimpleNamespace(stdout="func_test: CURRENT (0)\n")),
                  patch.object(layout_check, "compile_mixed_object", return_value=fixture[4]),
                  patch.object(layout_check, "object_symbols", return_value={"func_test": 0, "func_next": 0x20}),
                  patch.object(layout_check, "text_extent", return_value=(0x40, 0x10))):
                self.assertEqual(0, layout_check.main())
            self.assertFalse((fixture[5] / "proof.json").exists())

    def test_main_archives_only_after_fresh_exact_and_failed_layout(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            fixture = self.fixture(root)
            argv = ["layout_check.py", "us", "func_test", "--failure-archive", str(fixture[5])]
            with (patch.object(layout_check, "ROOT", root), patch.object(sys, "argv", argv),
                  patch.object(layout_check.subprocess, "run", return_value=SimpleNamespace(stdout="func_test: CURRENT (0)\n")) as focused,
                  patch.object(layout_check, "compile_mixed_object", return_value=fixture[4]),
                  patch.object(layout_check, "object_symbols", return_value={"func_test": 0, "func_next": 0x10}),
                  patch.object(layout_check, "text_extent", return_value=(0x30, 0x10))):
                self.assertEqual(1, layout_check.main())
            self.assertIn("--require-match", focused.call_args.args[0])
            self.assertTrue(focused.call_args.kwargs["check"])
            layout_check.validate_failure_proof(root, fixture[5] / "proof.json", fixture[2], "us")

    def test_nonexact_or_failed_focused_comparison_never_archives(self):
        for failure in (False, True):
            with self.subTest(failure=failure), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                fixture = self.fixture(root)
                argv = ["layout_check.py", "us", "func_test", "--failure-archive", str(fixture[5])]
                with (patch.object(layout_check, "ROOT", root), patch.object(sys, "argv", argv),
                      patch.object(layout_check.subprocess, "run",
                                   side_effect=subprocess.CalledProcessError(1, ["diff"]) if failure else None,
                                   return_value=SimpleNamespace(stdout="func_test: CURRENT (1)\n")),
                      patch.object(layout_check, "compile_mixed_object", return_value=fixture[4]),
                      patch.object(layout_check, "object_symbols", return_value={"func_test": 0, "func_next": 0x10}),
                      patch.object(layout_check, "text_extent", return_value=(0x30, 0x10))):
                    self.assertEqual(1, layout_check.main())
                self.assertFalse((fixture[5] / "proof.json").exists())


if __name__ == "__main__":
    unittest.main()
