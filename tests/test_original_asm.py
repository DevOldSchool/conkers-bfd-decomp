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
