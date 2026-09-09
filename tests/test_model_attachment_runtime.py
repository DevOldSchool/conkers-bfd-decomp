from __future__ import annotations

import base64
import copy
import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from scripts import model_attachment_runtime as attachment
from scripts import model_assets as models
from scripts import mupen_trace
from scripts import model_coverage
from test_model_attachment_format import payload


DIGEST = "fixture-rom"


def probe(name, address, data):
    return {"name": name, "resolved_address": hex(address), "length": len(data),
            "data_base64": base64.b64encode(data).decode(), "sha256": hashlib.sha256(data).hexdigest()}


def matrix_bytes(x=0):
    values = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, 0, 0, 1]
    return struct.pack(">16h16H", *values, *([0] * 16))


def fixture(parts=1):
    data = payload(parts=parts)
    _, layout = models.parse_attachment_model(data, models.parse_model_geometry)
    native, vertices, matrices, parent_root = 0x80004000, 0x80006000, 0x80007000, 0x80008000
    root = 0x80001000
    record = bytearray(0x5C)
    record[0:3] = bytes((1, 17, 12))
    record[0x14] = parts
    struct.pack_into(">III", record, 0x24, native + layout["pointer_table_offset"], vertices, vertices + 0x100)
    parent = bytearray(attachment.CHARACTER_POOL_RECORD_SIZE)
    struct.pack_into(">I", parent, 0, 1)
    parent[4] = 7
    struct.pack_into(">I", parent, 0x1D4, parent_root)
    common = [probe("attachment-record", 0x80003000, bytes(record)),
              probe("parent-character", attachment.CHARACTER_POOL_ADDRESS, bytes(parent)),
              probe("attachment-stack", 0x80009000, struct.pack(">I", root))]
    commands = [(0xDB060004, vertices), (0xDB06000C, matrices)]
    events = []
    nested = []
    for part, start in enumerate(layout["display_list_pointers"]):
        end = layout["display_list_pointers"][part+1] if part+1 < parts else layout["normal_offset"]
        raw = bytearray(data[start:end])
        for offset in range(0, len(raw), 8):
            if struct.unpack_from(">I", raw, offset)[0] == 0xDC38000E:
                struct.pack_into(">I", raw, offset + 4, native + layout["normal_offset"])
        target = native + start
        nested.append(probe(f"nested-display-list-{part:04d}", target, bytes(raw)))
        events.append({"breakpoint": "attachment-part-selected", "hook_address": "0x15031870",
            "state": {"model": {"attachment_address": 0x80003000, "parent_character_address": attachment.CHARACTER_POOL_ADDRESS},
                      "rdp": {"selected_display_list": target, "call_command_address": root + len(commands) * 8}},
            "evidence": {"memory": copy.deepcopy(common)}})
        commands.append((0xDE000000, target))
    events.append({"breakpoint": "attachment-draw-return", "hook_address": "0x15031914",
        "state": {"rdp": {"command_buffer_end": root + len(commands) * 8}},
        "evidence": {"memory": copy.deepcopy(common)}})
    commands.append((0xDF000000, 0))
    raw = b"".join(struct.pack(">II", *command) for command in commands)
    task = bytearray(64)
    struct.pack_into(">I", task, 0, 1)
    struct.pack_into(">II", task, 48, root, len(raw))
    events.append({"breakpoint": "character-draws-at-graphics-submit", "state": {"rdp": {}},
        "evidence": {"memory": [probe("task", 0x80000100, bytes(task)), probe("command-buffer", root, raw),
            probe("runtime-vertex-block-0000", vertices, data[24:layout["pointer_table_offset"]]),
            probe("runtime-matrix-0000", matrices, matrix_bytes(20)),
            probe("runtime-matrix-0001", parent_root, matrix_bytes(10)),
            probe("runtime-normal-stream-0000", native + layout["normal_offset"], data[layout["normal_offset"]:]), *nested]}})
    for event in events:
        event.update(record_type="draw_state", schema="conker.model-draw-state-trace/v1")
    return data, events


def write_trace(path, events, spec):
    header = {"schema": "conker.model-draw-state-trace/v1", "record_type": "session",
              "normalized_sha1": DIGEST, "spec_name": spec}
    path.write_text("\n".join(json.dumps(r) for r in (header, *events)) + "\n")
    return hashlib.sha256(path.read_bytes()).hexdigest()


class AttachmentRuntimeTests(unittest.TestCase):
    def test_capture_spec_retains_proven_hooks_and_graphics_filter(self):
        path = Path(__file__).resolve().parents[1] / "config/model-trace-attachment-draws.json"
        spec = mupen_trace.validate_spec(json.loads(path.read_text()))
        self.assertEqual(spec["target"]["bank"], 9)
        self.assertEqual([address["address"] for address in spec["breakpoints"]],
                         ["0x15031870", "0x15031914", "0x10023DF0"])
        self.assertIn({"source": "memory", "name": "task", "offset": 0, "size": 4,
                       "endian": "big", "equals": 1}, spec["breakpoints"][-1]["when"])

    def test_multiple_parts_use_native_pointers_and_submitted_palettes(self):
        data, events = fixture(parts=2)
        draws, incomplete = attachment.attachment_draws(events)
        self.assertEqual(len(draws), 1)
        self.assertEqual(incomplete, [])
        parts = attachment.resolve_draw(draws[0], attachment.graphics_snapshot(events[-1]), data)
        self.assertEqual([p["part"] for p in parts], [0, 1])
        self.assertEqual([p["geometry"].face_source_indices for p in parts], [(0,), (1,)])
        self.assertEqual([p["source_face_count"] for p in parts], [1, 1])
        self.assertEqual(parts[0]["matrices"][0][3][:3], [20.0, 0.0, 0.0])

    def test_missing_return_and_graphics_submission_remain_incomplete(self):
        _, events = fixture()
        self.assertEqual(attachment.attachment_draws(events[:1])[1][0]["reason"], "selected-parts-without-return")
        self.assertEqual(attachment.attachment_draws(events[:-1])[1][0]["reason"], "no-following-graphics-task")

    def test_record_changes_and_corrupted_memory_are_rejected(self):
        _, events = fixture()
        events[0]["state"]["model"]["attachment_address"] += 4
        with self.assertRaisesRegex(ValueError, "record address"):
            attachment.attachment_draws(events)
        _, events = fixture()
        events[-1]["evidence"]["memory"][1]["sha256"] = "0" * 64
        with self.assertRaisesRegex(ValueError, "memory identity"):
            attachment.graphics_snapshot(events[-1])

    def test_captured_geometry_changes_do_not_become_model_matches(self):
        data, events = fixture()
        draws, _ = attachment.attachment_draws(events)
        for name, offset in (("runtime-vertex-block-0000", 1), ("nested-display-list-0000", 0)):
            with self.subTest(name=name):
                changed = copy.deepcopy(events[-1])
                item = next(p for p in changed["evidence"]["memory"] if p["name"] == name)
                raw = bytearray(base64.b64decode(item["data_base64"]))
                raw[offset] ^= 1
                item.update(probe(name, int(item["resolved_address"], 0), bytes(raw)))
                with self.assertRaisesRegex(ValueError, "positions disagree|opcode differs"):
                    attachment.resolve_draw(draws[0], attachment.graphics_snapshot(changed), data)

    def test_selected_parts_must_cover_the_entire_draw_range(self):
        data, events = fixture(parts=2)
        draws, _ = attachment.attachment_draws(events)
        draws[0]["parts"].pop()
        with self.assertRaisesRegex(ValueError, "every submitted triangle"):
            attachment.resolve_draw(draws[0], attachment.graphics_snapshot(events[-1]), data)

    def test_runtime_uv_and_normal_attributes_follow_captured_vertex_loads(self):
        data, events = fixture()
        draw = attachment.attachment_draws(events)[0][0]
        for item in events[-1]["evidence"]["memory"]:
            if item["name"] not in ("runtime-vertex-block-0000", "runtime-normal-stream-0000"):
                continue
            raw = bytearray(base64.b64decode(item["data_base64"]))
            if item["name"] == "runtime-vertex-block-0000":
                struct.pack_into(">Hh", raw, 6, 246, 64)
            else:
                raw[:2] = bytes((10, 20))
            item.update(probe(item["name"], int(item["resolved_address"], 0), bytes(raw)))
        part = attachment.resolve_draw(draw, attachment.graphics_snapshot(events[-1]), data)[0]
        self.assertEqual(part["geometry"].vertices[0].s, 64)
        self.assertEqual(part["geometry"].face_normal_bytes[0][0], (10, 20, -10))
        self.assertEqual(part["runtime_vertex_attribute_changes"], [0])

    def test_non_graphics_task_is_rejected(self):
        _, events = fixture()
        task = events[-1]["evidence"]["memory"][0]
        raw = bytearray(base64.b64decode(task["data_base64"]))
        struct.pack_into(">I", raw, 0, 2)
        task.update(probe("task", int(task["resolved_address"], 0), bytes(raw)))
        with self.assertRaisesRegex(ValueError, "graphics task header"):
            attachment.graphics_snapshot(events[-1])

    def test_attachment_coverage_checks_native_parts_without_inventing_scenes(self):
        data, events = fixture(parts=2)
        draw = attachment.attachment_draws(events)[0][0]
        parts = attachment.resolve_draw(draw, attachment.graphics_snapshot(events[-1]), data)
        record = {"parent_entry": 7, "attachment": {"model_sha1": hashlib.sha1(data).hexdigest(),
                  "parent_bone": 12, "parts": [parts[1]]}}
        self.assertEqual(model_coverage.attachment_source_faces(data, [record]), ({1}, {7}, {12}))
        record["attachment"]["parts"][0]["source_first_command"] += 8
        with self.assertRaisesRegex(ValueError, "source span"):
            model_coverage.attachment_source_faces(data, [record])

    def test_composition_binds_to_parent_task_and_deduplicates_captures(self):
        for scenario in ("matched", "wrong-parent", "changed-attachment-matrix"):
            with self.subTest(scenario=scenario), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                data, events = fixture()
                trace = root / "attachments.jsonl"
                write_trace(trace, events, "character-attachment-draw-ranges")
                body_trace = root / "body.jsonl"
                body_events = copy.deepcopy(events[-1:])
                if scenario == "changed-attachment-matrix":
                    item = next(p for p in body_events[0]["evidence"]["memory"] if p["name"] == "runtime-matrix-0000")
                    item.update(probe(item["name"], int(item["resolved_address"], 0), matrix_bytes(21)))
                body_hash = write_trace(body_trace, body_events, "character-model-draw-ranges")
                geo = models.parse_geometry_for_bank(data, 9)
                gltf, binary = models.encode_gltf(7, 0, geo, output_stem="body")
                (root / "posed").mkdir()
                (root / "posed/body.gltf").write_bytes(gltf)
                (root / "posed/body.bin").write_bytes(binary)
                instance = {"state": "fixture", "task_submission_index": 1, "slot": 0,
                    "entry": 8 if scenario == "wrong-parent" else 7, "root_matrix_address": "0x80008000",
                    "resolved_clusters": [{"runtime_appearances": [{"draw_trace": str(body_trace),
                        "draw_trace_sha256": body_hash, "submitted_graphics": {"event_index": 0}}]}],
                    "runtime_matrices": [{"status": "decoded-affine-components", "address": 0x80008000,
                                          "rows": models.decode_rsp_matrix(matrix_bytes(10))["rows"]}]}
                record = {k: instance[k] for k in ("state", "task_submission_index", "slot", "entry", "root_matrix_address")}
                record.update(origin_matrix_slot=0, source_face_count=1, face_count=1, omitted_zero_area_face_count=0,
                    source_zero_area_face_count=0, runtime_pose_zero_area_face_count=0, linked_texture_run_count=0,
                    linked_texture_face_count=0, task_local_runtime_material_run_count=0, source_models=[],
                    gltf_file="posed/body.gltf", gltf_binary_file="posed/body.bin")
                source = models.ModelBundle(index=17, type_flags=0, compressed=False, data=data, segments=())
                with mock.patch.object(attachment.models, "load_model_bundles", return_value=(None, None, DIGEST, [source], ())):
                    report = attachment.attach_composition_previews("us", None, DIGEST, (trace, trace),
                        {"character_composition_instances": [instance]}, [record], root, None, {})
                self.assertEqual(len(report["source_attachment_traces"]), 1)
                if scenario != "matched":
                    self.assertEqual(record["face_count"], 1)
                    self.assertEqual(report["attachment_instance_count"], 0)
                    self.assertEqual((root / "posed/body.gltf").read_bytes(), gltf)
                    continue
                self.assertEqual(report["attachment_instance_count"], 1)
                self.assertEqual(record["face_count"], 2)
                merged = json.loads((root / "posed/body.gltf").read_text())
                raw = (root / "posed/body.bin").read_bytes()
                self.assertEqual(len(merged["meshes"]), 2)
                accessor = merged["accessors"][merged["meshes"][1]["primitives"][0]["attributes"]["POSITION"]]
                view = merged["bufferViews"][accessor["bufferView"]]
                position = struct.unpack_from("<3f", raw, view["byteOffset"] + accessor.get("byteOffset", 0))
                self.assertEqual(position, (10.0, 0.0, 0.0))
                self.assertEqual(raw[:len(binary)], binary)
                self.assertEqual(merged["materials"][0], json.loads(gltf)["materials"][0])


if __name__ == "__main__":
    unittest.main()
