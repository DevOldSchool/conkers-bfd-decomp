"""ROM-free authenticity, privacy, and mutation checks for optional audit tools."""
import argparse
import base64
import contextlib
import copy
import hashlib
import io
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts.model_evidence import audit_expression_constructors as expression
from scripts.model_evidence import audit_haybot_preserved_capture_portable as capture
from scripts.model_evidence import common
from scripts.model_evidence import derive_haybot_contract as haybot
from scripts.model_evidence import derive_library155_contract as library
from scripts.model_evidence import derive_scene60_contract as scene
from scripts.model_evidence import library155_raw_closure as closure

ROOT = Path(__file__).resolve().parents[1]


class EvidenceToolTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)

    def source(self, name, raw=b"local input"):
        path = self.root / name
        path.write_bytes(raw)
        return path

    def test_source_reader_authenticates_size_and_digest_without_paths(self):
        raw = b"source bytes"
        path = self.source("private-input-name", raw)
        expected = {"packet": {"bytes": len(raw), "sha256": common.sha(raw)}}
        read, provenance = common.source_reader({"packet": path}, expected)
        self.assertEqual(raw, read("packet"))
        self.assertEqual(expected, provenance)
        self.assertNotIn(str(path), json.dumps(provenance))
        for changed in (b"source byteS", b"source bytes!"):
            path.write_bytes(changed)
            with self.assertRaisesRegex(ValueError, "evidence identity changed: packet"):
                read("packet")

    def test_capture_pins_match_canonical_contract_sources(self):
        for module, name in ((scene, "scene60"), (library, "library-bat155")):
            with self.subTest(module=name):
                contract = json.loads((ROOT / f"config/model-{name}-captured-appearance.json").read_bytes())
                self.assertEqual(module.INPUTS, contract["provenance"]["sources"])
                self.assertEqual(module.PACKET_SHA256, contract["provenance"]["packet_sha256"])
                self.assertEqual(module.PRESET, contract["preset"])
                self.assertTrue(all("/" not in role and "\\" not in role for role in module.INPUTS))
        contract = json.loads((ROOT / "config/model-library-bat155-captured-appearance.json").read_bytes())
        self.assertEqual(library.SCOPE, contract["scope"])

    def test_existing_output_rejected_before_all_audit_work(self):
        cases = [(expression, ("rom",), "audit"),
                 (scene, ("rom", *scene.INPUTS), "derive"),
                 (library, ("rom", *library.INPUTS), "derive"),
                 (capture, ("manifest", *capture.INPUT_ROLES), "audit")]
        output = self.source("output.json", b"keep report")
        for module, roles, operation in cases:
            with self.subTest(module=module.__name__):
                args = []
                for role in roles:
                    args.extend(["--" + role.replace("_", "-"), str(self.source(role))])
                args.extend(["--output", str(output)])
                if module is capture:
                    args.extend(["--manifest-sha256", "0" * 64])
                with patch.object(module, operation) as work:
                    with self.assertRaisesRegex(ValueError, "must be a new file"):
                        module.main(args)
                work.assert_not_called()
                self.assertEqual(b"keep report", output.read_bytes())

    def test_scene_and_library_reject_changed_packet_before_rom_resolution(self):
        for module in (scene, library):
            with self.subTest(module=module.__name__):
                packet = self.source("changed-packet.json", b'{"passed":true}')
                with self.assertRaisesRegex(ValueError, "evidence identity changed: packet"):
                    module.derive(self.root / "absent.rom", {"packet": packet})

    def test_expression_output_contains_no_local_paths(self):
        rom = self.source("private-rom-name")
        output = self.root / "new-report.json"
        result = {"constructors": {"operation_count": 0, "attachment_entries": []},
                  "stored_expression_references": [], "rom_mutations_rejected": 0,
                  "geometry_uv_rig_invariants": []}
        stdout = io.StringIO()
        with patch.object(expression, "audit", return_value=result), contextlib.redirect_stdout(stdout):
            expression.main(["--rom", str(rom), "--output", str(output)])
        self.assertEqual(common.encoded(result), output.read_bytes())
        self.assertNotIn(str(self.root), stdout.getvalue())

    def test_portable_capture_rejects_changed_manifest_before_reading_inputs(self):
        manifest = self.source("manifest.json", b'{"files":[]}')
        with self.assertRaisesRegex(ValueError, "reviewed input manifest changed"):
            capture.audit({}, manifest, "0" * 64)
        for digest in ("x" * 64, "a" * 63, "A" * 64):
            with self.subTest(digest=digest), self.assertRaisesRegex(ValueError, "lowercase SHA256"):
                capture.audit({}, manifest, digest)

    def test_portable_capture_requires_packet_in_reviewed_manifest(self):
        packet = self.source("packet", b"not the reviewed packet")
        manifest = self.source("manifest.json", b'{"files":[]}')
        with self.assertRaisesRegex(ValueError, "Input absent from reviewed manifest: packet"):
            capture.audit({"packet": packet}, manifest, common.sha(manifest.read_bytes()))

    def test_portable_capture_manifest_cannot_repin_packet(self):
        raw = b"not the pinned packet"
        packet = self.source("packet", raw)
        manifest = self.source("manifest.json", common.encoded({"files": [
            {"path": "/unread/private/location", "bytes": len(raw), "sha256": common.sha(raw)}]}))
        with self.assertRaisesRegex(ValueError, "Pinned capture input changed: packet"):
            capture.audit({"packet": packet}, manifest, common.sha(manifest.read_bytes()))

    def test_trace_state_hash_recomputed(self):
        state = {"model": {"index": 75}, "other": [1, 2]}
        digest = common.sha(json.dumps(state, sort_keys=True, separators=(",", ":")).encode())
        event = {"state": state, "render_state_hash": digest}
        common.validate_event_hashes([event])
        state["model"]["index"] = 76
        with self.assertRaisesRegex(ValueError, "trace state hash changed"):
            common.validate_event_hashes([event])

    def test_success_looking_capture_report_cannot_replace_authentication(self):
        path = self.source("new-capture-audit.json", common.encoded({"passed": True,
            "checks": {"all": True}, "inputs": [{"sha256": haybot.TRACE_SHA256},
                                                     {"sha256": haybot.PACKET_SHA256}]}))
        with self.assertRaisesRegex(ValueError, "independently reviewed capture audit changed"):
            haybot.checked_capture_audit(path)

    def test_haybot_contract_format_preserves_technical_fields_and_omits_timestamp(self):
        contract = json.loads((ROOT / "config/model-haybot-captured-appearance.json").read_bytes())
        packet = copy.deepcopy(contract)
        for key in ("source_run_sha256", "selector_evidence", "reconstruction", "preset"):
            packet.pop(key)
        packet["context"]["timestamp"] = "private-capture-time"
        packet["context"]["core"] = "wrapper core detail"
        original = copy.deepcopy(packet)
        report = {"source_run_sha256": contract["source_run_sha256"]}
        expected = copy.deepcopy(contract)
        expected["reconstruction"]["rom_audit_sha256"] = common.sha(common.encoded(report))
        self.assertEqual(expected, haybot.build_contract(packet, report))
        self.assertEqual(original, packet)


class LibraryRawClosureTests(unittest.TestCase):
    """Synthetic bytes exercise raw task/fog/matrix checks without a game asset."""

    @staticmethod
    def probe(name, address, raw):
        return {"name": name, "resolved_address": hex(address), "length": len(raw),
                "sha256": common.sha(raw), "data_base64": base64.b64encode(raw).decode()}

    def fixture(self):
        start = 0x80001000
        commands = struct.pack(">4I", 0xF8000000, 255, 0xDF000000, 0)
        header = [0] * 16
        header[0], header[12], header[13] = 1, start, len(commands)
        before = [self.probe("character-command-buffer", start, commands)]
        after = [self.probe("command-buffer", start, commands),
                 self.probe("task", 0x80002000, struct.pack(">16I", *header))]
        addresses = [0x80003000 + index * 64 for index in range(35)]
        floats = [1.0 if i in (0, 5, 10, 15) else 0.0 for i in range(16)]
        fixed = struct.pack(">16h16H", *(int(f) for f in floats), *([0] * 16))
        for index, address in enumerate(addresses):
            before.append(self.probe(f"runtime-matrix-{index}", address, struct.pack(">16f", *floats)))
            after.append(self.probe(f"runtime-matrix-{index}", address, fixed))
        events = [{}, {"evidence": {"memory": before}},
                  {"evidence": {"memory": after}, "hook_address": "0x10023DF0",
                   "state": {"rdp": {"draw_runs": [{"command_offset": 8}]}}}]
        packet = {"tasks": [{"entry": 0, "return": 1, "task": 2,
            "submission": {"command_buffer_start": start, "command_buffer_end": start + len(commands),
                           "command_sha256": common.sha(commands)},
            "effective_fog": {"origin": [start], "offset": 0, "words": [0xF8000000, 255]}}]}
        quick = {"draws": [{"entry_event": 0, "return_event": 1, "task_event": 2,
                            "rows": [{"draw_index": 0}]}]}
        paired = {"draw_calls": [{"event_index": 0,
                                  "runtime_matrices": [{"address": address} for address in addresses]}]}
        return events, packet, quick, paired

    def test_synthetic_raw_closure_passes_and_reports_only_metadata(self):
        result = closure.verify_raw_closure(*self.fixture())
        self.assertEqual(35, result[0]["matrix_count"])
        self.assertEqual(420, result[0]["affine_components_compared"])
        self.assertEqual(0, result[0]["matrix_maximum_absolute_error"])
        self.assertFalse(result[0]["flattened_fog_offset_independently_recomputed"])
        self.assertNotIn("data_base64", json.dumps(result))

    def test_changed_memory_hash_rejected(self):
        events, packet, quick, paired = self.fixture()
        events[1]["evidence"]["memory"][0]["sha256"] = "0" * 64
        with self.assertRaisesRegex(ValueError, "capture probe hash changed"):
            closure.verify_raw_closure(events, packet, quick, paired)

    def test_changed_task_root_size_rejected(self):
        events, packet, quick, paired = self.fixture()
        task = events[2]["evidence"]["memory"][1]
        raw = bytearray(base64.b64decode(task["data_base64"]))
        struct.pack_into(">I", raw, 13 * 4, 32)
        events[2]["evidence"]["memory"][1] = self.probe("task", 0x80002000, raw)
        with self.assertRaisesRegex(ValueError, "task header/root mismatch"):
            closure.verify_raw_closure(events, packet, quick, paired)

    def test_matrix_change_beyond_quantization_rejected(self):
        events, packet, quick, paired = self.fixture()
        matrix = events[2]["evidence"]["memory"][2]
        raw = bytearray(base64.b64decode(matrix["data_base64"]))
        struct.pack_into(">h", raw, 0, 2)
        events[2]["evidence"]["memory"][2] = self.probe(matrix["name"], int(matrix["resolved_address"], 0), raw)
        with self.assertRaisesRegex(ValueError, "matrix changed beyond fixed-point precision"):
            closure.verify_raw_closure(events, packet, quick, paired)

    def test_duplicate_matrix_inventory_rejected(self):
        events, packet, quick, paired = self.fixture()
        paired["draw_calls"][0]["runtime_matrices"][1] = paired["draw_calls"][0]["runtime_matrices"][0]
        with self.assertRaisesRegex(ValueError, "target matrix inventory changed"):
            closure.verify_raw_closure(events, packet, quick, paired)

    def test_recorded_fog_offset_before_targets_required(self):
        events, packet, quick, paired = self.fixture()
        packet["tasks"][0]["effective_fog"]["offset"] = 12
        with self.assertRaisesRegex(ValueError, "target command precedes"):
            closure.verify_raw_closure(events, packet, quick, paired)


if __name__ == "__main__":
    unittest.main()
