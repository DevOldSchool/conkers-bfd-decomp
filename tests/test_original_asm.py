from __future__ import annotations

import copy
import hashlib
import json
import sys
import tempfile
import unittest
from contextlib import ExitStack, redirect_stdout
from io import StringIO
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import original_asm
import project_state
import diff
import rom_span


class OriginalAssemblyTests(unittest.TestCase):
    def setUp(self):
        self.evidence = {"rom_sha1": "a" * 40, "span_sha256": "b" * 64,
                         "assembly_sha256": "c" * 64, "verified_revision": "working-tree"}
        self.entry = {"symbol": "func_test", "overlay": "game", "source": "src/game/test.c",
                      "original_asm": {"reason": "custom register ABI", "reference": "evidence.md",
                                       "recorded_revision": "working-tree"},
                      "regions": {"us": {"state": "original_asm", "symbol": "func_test",
                                         "vram": "0x15000000", "size_bytes": 4,
                                         "evidence": self.evidence}}}

    def test_classification_requires_proof_and_cannot_claim_a_c_match(self):
        project_state.validate_functions({"schema_version": 1, "functions": [self.entry]})
        self.assertFalse(project_state.is_complete(self.entry))
        self.assertEqual("raw_asm", project_state.source_unit_work_state([self.entry]))
        for mutate in (lambda x: x.pop("original_asm"),
                       lambda x: x.update(deferred={}),
                       lambda x: x["regions"]["us"]["evidence"].update(current_differences=0),
                       lambda x: x["regions"]["us"]["evidence"].pop("span_sha256"),
                       lambda x: x["regions"]["us"].update(state="raw_asm")):
            entry = copy.deepcopy(self.entry)
            mutate(entry)
            with self.assertRaises((ValueError, project_state.ProjectStateError)):
                project_state.validate_functions({"schema_version": 1, "functions": [entry]})

    def test_source_and_generated_assembly_must_remain_preserved(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / self.entry["source"]
            source.parent.mkdir(parents=True)
            source.write_text(project_state.global_asm_pragma(self.entry["source"], "func_test"))
            (root / "evidence.md").write_text("Reviewed custom ABI")
            original_asm.validate_source(root, self.entry)
            assembly = root / project_state.nonmatching_asm_path(self.entry["source"], "func_test")
            assembly.parent.mkdir(parents=True)
            assembly.write_text("original bytes")
            self.evidence["assembly_sha256"] = hashlib.sha256(assembly.read_bytes()).hexdigest()
            original_asm.validate_source(root, self.entry)
            assembly.write_text("changed bytes")
            with self.assertRaisesRegex(ValueError, "changed"):
                original_asm.validate_source(root, self.entry)
            assembly.unlink()
            source.write_text("void func_test(void) {}")
            with self.assertRaisesRegex(ValueError, "GLOBAL_ASM"):
                original_asm.validate_source(root, self.entry)

    def test_batch_accepts_classification_without_promoting_it_to_matched(self):
        with patch.object(project_state, "validate_project", return_value=({}, [self.entry])), redirect_stdout(StringIO()) as output:
            project_state.batch_plan(["func_test"])
        self.assertEqual("game\n", output.getvalue())
        self.assertFalse(project_state.is_complete(self.entry))

    def test_failed_proof_and_failed_render_do_not_change_inventory(self):
        for failure in ("proof", "render"):
            with self.subTest(failure=failure), tempfile.TemporaryDirectory() as temporary, ExitStack() as stack:
                root = Path(temporary)
                (root / "evidence.md").write_text("Reviewed custom ABI")
                entry = copy.deepcopy(self.entry)
                entry.pop("original_asm")
                entry["regions"]["us"].update(state="raw_asm")
                entry["regions"]["us"].pop("evidence")
                inventory = root / "functions.json"
                before = json.dumps({"schema_version": 1, "functions": [entry]})
                inventory.write_text(before)
                for name, value in {"ROOT": root, "FUNCTIONS_FILE": inventory,
                                    "SUMMARY_FILE": root / "summary.json", "DOCUMENT_FILE": root / "progress.md",
                                    "BADGE_FILES": {"us": root / "badge.json"}}.items():
                    stack.enter_context(patch.object(project_state, name, value))
                stack.enter_context(patch.object(project_state, "validate_project", return_value=({}, [entry])))
                stack.enter_context(patch.object(original_asm, "validate_source"))
                stack.enter_context(patch.object(original_asm, "read_proof", return_value=self.evidence,
                                                side_effect=ValueError("bad proof") if failure == "proof" else None))
                stack.enter_context(patch.object(project_state, "render_progress", side_effect=RuntimeError("render failed")))
                with self.assertRaises((project_state.ProjectStateError, RuntimeError)):
                    project_state.verify_original_asm(SimpleNamespace(symbol="func_test", check=False, proof_output=None, proof="proof.json",
                                                                       reason="custom ABI", evidence_reference="evidence.md"))
                self.assertEqual(before, inventory.read_text())

    def test_matched_byte_progress_excludes_original_assembly(self):
        ranges = {overlay: {region: (0, 16) for region in project_state.KNOWN_REGIONS}
                  for overlay in project_state.OVERLAYS}
        entry = copy.deepcopy(self.entry)
        entry["regions"]["us"]["vram"] = "0x00000000"
        result = project_state.code_progress([entry], [], ranges)
        self.assertEqual(0, result["matched_bytes"])

    def test_main_classification_is_separate_from_c_and_unknown_overlays_fail(self):
        entry = copy.deepcopy(self.entry)
        entry["overlay"] = "main"
        entry["regions"]["us"]["vram"] = "0x80008120"
        original_asm.validate_metadata(entry)
        self.assertFalse(project_state.is_complete(entry))
        with patch.object(project_state, "validate_project", return_value=({}, [entry])), redirect_stdout(StringIO()) as output:
            project_state.batch_plan(["func_test"])
        self.assertEqual("main\n", output.getvalue())
        entry["overlay"] = "rsp"
        with self.assertRaisesRegex(ValueError, "main or game"):
            original_asm.validate_metadata(entry)
        with self.assertRaisesRegex(ValueError, "main and game"):
            original_asm.reference_image(Path("."), entry)

    def test_main_verifier_assembles_independent_full_span_and_rejects_changed_bytes(self):
        with tempfile.TemporaryDirectory() as temporary, ExitStack() as stack:
            root = Path(temporary)
            entry = copy.deepcopy(self.entry)
            entry.update(overlay="main", source="src/main/test.c")
            entry["regions"]["us"]["vram"] = "0x80008120"
            assembly = root / project_state.nonmatching_asm_path(entry["source"], "func_test")
            assembly.parent.mkdir(parents=True)
            assembly.write_text("/* 8120 80008120 03E00008 */ jr $ra\n")
            payload = bytes.fromhex("03e00008")
            stack.enter_context(patch.object(original_asm, "validate_source"))
            stack.enter_context(patch.object(rom_span, "main_code", return_value=(payload, 0x80008120, "a" * 40)))
            game = stack.enter_context(patch.object(rom_span, "game_code", side_effect=AssertionError("wrong overlay")))
            stack.enter_context(patch.object(diff, "expected_function_size", return_value=4))
            raw = stack.enter_context(patch.object(diff, "ensure_reference_function", return_value=assembly))
            obj = root / "object.o"
            obj.write_bytes(b"mock object")
            ref = stack.enter_context(patch.object(diff, "reference_object", return_value=obj))
            parsed = SimpleNamespace(symbols={0: [(".L80008120", 0, 0, 0)]})
            stack.enter_context(patch.object(original_asm, "Object32", return_value=parsed))
            link = stack.enter_context(patch.object(original_asm.linked_aliases, "linked_span", return_value=payload))
            evidence = original_asm.verify(root, entry)
            self.assertEqual(hashlib.sha256(payload).hexdigest(), evidence["span_sha256"])
            raw.assert_called_once_with("us", "func_test", game_reference=False)
            self.assertFalse(ref.call_args.kwargs["game_reference"])
            game.assert_not_called()
            self.assertEqual({".L80008120": 0x80008120}, link.call_args.args[5])
            for invalid in (".L80008124", ".L80008120_suffix", "other_symbol"):
                parsed.symbols = {0: [(invalid, 0, 0, 0)]}
                with self.assertRaisesRegex(ValueError, "outside main CPU|unsupported"):
                    original_asm.verify(root, entry)
            parsed.symbols = {0: [(".L80008120", 1, 0, 0)]}
            with self.assertRaisesRegex(ValueError, "unsupported"):
                original_asm.verify(root, entry)
            parsed.symbols = {}
            proof = root / "proof.json"
            proof.write_text(json.dumps({"symbol": "func_test", "evidence": evidence}))
            self.assertEqual(evidence, original_asm.read_proof(root, entry, proof))
            link.return_value = b"\0" * 4
            with self.assertRaisesRegex(ValueError, "differs from the US ROM"):
                original_asm.verify(root, entry)
            assembly.write_text("/* 8120 80008120 00000000 */ nop\n")
            with self.assertRaisesRegex(ValueError, "differ from the US ROM"):
                original_asm.read_proof(root, entry, proof)

    def test_main_image_checks_rom_and_excludes_boot_and_rsp(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for directory in ("config/reference", "config/rsp", "roms"):
                (root / directory).mkdir(parents=True)
            rom = bytes.fromhex("80371240") + bytes(range(4, 64))
            digest = hashlib.sha1(rom).hexdigest()
            metadata = {"profiles": {"us": {"sha1": digest, "size_bytes": len(rom)}}}
            (root / "config/roms.json").write_text(json.dumps(metadata))
            (root / "roms/baserom.us.z64").write_bytes(rom)
            (root / "config/reference/us.yaml").write_text(
                "segments:\n- name: entry\n  start: 16\n  vram: 0x80001000\n")
            rsp = {"rom_sha1": digest, "payloads": [{"kind": "code", "start": 32}]}
            layout = root / "config/rsp/us.json"
            layout.write_text(json.dumps(rsp))
            image, base, actual = rom_span.main_code(root)
            self.assertEqual((rom[16:32], 0x80001000, digest), (image, base, actual))
            with self.assertRaisesRegex(ValueError, "differ from the US ROM"):
                rom_span.raw_span("/* 20 80001010 20212223 */ nop", base + 16, 4, image, base)
            rsp["rom_sha1"] = "0" * 40
            layout.write_text(json.dumps(rsp))
            with self.assertRaisesRegex(ValueError, "same checksum"):
                rom_span.main_code(root)
            rsp["rom_sha1"] = digest
            rsp["payloads"][0]["start"] = 65
            layout.write_text(json.dumps(rsp))
            with self.assertRaisesRegex(ValueError, "invalid main CPU interval"):
                rom_span.main_code(root)
            metadata["profiles"]["us"]["size_bytes"] = 65
            (root / "config/roms.json").write_text(json.dumps(metadata))
            with self.assertRaisesRegex(ValueError, "checksum-validated"):
                rom_span.main_code(root)
            metadata["profiles"]["us"].update(size_bytes=64, sha1="0" * 40)
            (root / "config/roms.json").write_text(json.dumps(metadata))
            with self.assertRaisesRegex(ValueError, "checksum-validated"):
                rom_span.main_code(root)

    def test_host_rejects_stale_proof_or_wrong_work_item(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            entry = copy.deepcopy(self.entry)
            assembly = root / project_state.nonmatching_asm_path(entry["source"], "func_test")
            assembly.parent.mkdir(parents=True)
            assembly.write_text("/* 0 15000000 03E00008 */ jr $ra\n")
            payload = bytes.fromhex("03e00008")
            output = root / "build/us/original-asm/func_test"
            output.mkdir(parents=True)
            (output / "span.bin").write_bytes(payload)
            evidence = {"rom_sha1": "a" * 40, "span_sha256": hashlib.sha256(payload).hexdigest(),
                        "assembly_sha256": hashlib.sha256(assembly.read_bytes()).hexdigest(),
                        "verified_revision": "working-tree"}
            proof = output / "proof.json"
            with patch.object(diff, "expected_function_size", return_value=4), patch.object(
                    rom_span, "game_code", return_value=(payload, 0x15000000, "a" * 40)):
                for symbol in ("wrong", "func_test"):
                    proof.write_text(json.dumps({"symbol": symbol, "evidence": evidence}))
                    if symbol == "wrong":
                        with self.assertRaisesRegex(ValueError, "different work item"):
                            original_asm.read_proof(root, entry, proof)
                    else:
                        self.assertEqual(evidence, original_asm.read_proof(root, entry, proof))
                assembly.write_text(assembly.read_text() + "/* changed after assembly */\n")
                with self.assertRaisesRegex(ValueError, "current inputs"):
                    original_asm.read_proof(root, entry, proof)
