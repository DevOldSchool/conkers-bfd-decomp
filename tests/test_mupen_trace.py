from __future__ import annotations

import json
import base64
import hashlib
import struct
import tempfile
import time
import unittest
from pathlib import Path

from scripts import mupen_trace


ROOT = Path(__file__).resolve().parent.parent


class MupenTraceTests(unittest.TestCase):
    def test_model_clusters_read_verified_shared_effect_geometry(self):
        draw = struct.pack('>6I', 0x01003006, 0x01000000, 0x05000204, 0, 0xDF000000, 0)
        payload = bytes(32) + draw
        geometry = {'display_list_offset': '0x20', 'display_list_size': len(draw),
                    'effect_layout': {'family': 'bank-09-four-pair-effect-model',
                                      'geometry_source_entry': 173,
                                      'geometry_source_sha1': hashlib.sha1(payload).hexdigest()}}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / 'bundles/0173/segment-00.bin'
            source.parent.mkdir(parents=True)
            source.write_bytes(payload)
            actual = mupen_trace.model_cluster_display_bytes(root, 9, 0, bytes(32), geometry)
            self.assertEqual(draw, actual)
            self.assertEqual(1, mupen_trace.geometry_clusters(actual)[0]['triangle_count'])
            source.write_bytes(payload + b'changed')
            with self.assertRaisesRegex(mupen_trace.TraceError, 'hash changed'):
                mupen_trace.model_cluster_display_bytes(root, 9, 0, bytes(32), geometry)
            source.unlink()
            with self.assertRaisesRegex(mupen_trace.TraceError, 'requires shared'):
                mupen_trace.model_cluster_display_bytes(root, 9, 0, bytes(32), geometry)

    def test_model_clusters_reject_invalid_direct_bounds(self):
        for offset, size in ((1, 8), (0, 9), (8, 16), (-8, 8), (0, 0)):
            with self.subTest(offset=offset, size=size), self.assertRaises(mupen_trace.TraceError):
                mupen_trace.model_cluster_display_bytes(Path('.'), 3, 0, bytes(16),
                    {'display_list_offset': offset, 'display_list_size': size})

    def test_tracks_render_targets_across_character_passes(self) -> None:
        data = b"".join(struct.pack(">II", command, argument) for command, argument in (
            (0xFF48003F, 0x800DE080),
            (0x05000204, 0),
            (0xDF000000, 0),
            (0x05000204, 0),
            (0xFF100123, 0x803D6300),
            (0x05000204, 0),
        ))
        decoded = mupen_trace.decode_f3dex2_cbfd(data)
        targets = [run["state"]["color_image"] for run in decoded["rdp"]["draw_runs"]]
        self.assertEqual([0x800DE080, 0x800DE080, 0x803D6300], [t["resolved_address"] for t in targets])
        self.assertEqual((2, 1, 64), tuple(targets[0][k] for k in ("format", "size", "width")))
        self.assertEqual((0, 2, 292), tuple(targets[2][k] for k in ("format", "size", "width")))

    def test_public_command_uses_pinned_container_recorder(self) -> None:
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")
        trace_case = script.split("    mupen-trace)", 1)[1].split("        ;;", 1)[0]

        self.assertIn("ensure_mupen_image", trace_case)
        self.assertIn("run_in_ephemeral_container", trace_case)
        self.assertNotIn("run_in_warm_container", trace_case)
        self.assertIn("scripts/mupen_trace.py record", trace_case)
        self.assertIn("mupen-trace --spec <path> --output <build-path>", script)

    def test_replays_per_tile_bounds_without_rewriting_recorded_state(self) -> None:
        commands = (
            (0xF2002002, 0x0407E07E), (0x05000204, 0),
            (0xDF000000, 0), (0xF2004004, 0x00080080),
            (0x05000204, 0), (0xF2006006, 0x04082082), (0x05000204, 0),
        )
        data = b"".join(struct.pack(">II", *pair) for pair in commands)
        state = mupen_trace.decode_f3dex2_cbfd(data)
        state["rdp"]["model_correlations"] = []
        draws = state["rdp"]["draw_runs"]
        self.assertEqual([0xF2002002, 0xF2002002, 0xF2006006],
                         [d["state"]["tile_bounds"]["4"][0] for d in draws])
        # Older captures did not record SetTileSize; replay adds evidence next
        # to the old state and preserves its hash and captured pixel references.
        for draw in draws:
            draw["state"].pop("tile_bounds")
        original_states = json.dumps([d["state"] for d in draws], sort_keys=True)
        original_hashes = [d["material_state_hash"] for d in draws]
        probe = {"name": "command-buffer", "length": len(data),
                 "sha256": hashlib.sha256(data).hexdigest(),
                 "data_base64": base64.b64encode(data).decode("ascii")}
        event = {"state": state, "evidence": {"memory": [probe]}}
        self.assertTrue(mupen_trace.refresh_trace_model_correlations(event, []))
        self.assertEqual(original_states, json.dumps([d["state"] for d in draws], sort_keys=True))
        self.assertEqual(original_hashes, [d["material_state_hash"] for d in draws])
        self.assertEqual([0xF2002002, 0xF2002002, 0xF2006006],
                         [d["replayed_tile_bounds"]["4"][0] for d in draws])

    def test_checked_in_texture_parser_spec_is_valid(self) -> None:
        spec = json.loads(
            (ROOT / "config" / "model-trace-texture-parser.json").read_text(encoding="utf-8")
        )

        self.assertIs(spec, mupen_trace.validate_spec(spec))
        self.assertEqual("0x1510D010", spec["breakpoints"][0]["address"])

    def test_checked_in_graphics_task_spec_is_valid(self) -> None:
        spec = json.loads(
            (ROOT / "config" / "model-trace-gfx-task.json").read_text(encoding="utf-8")
        )

        self.assertIs(spec, mupen_trace.validate_spec(spec))
        breakpoint = spec["breakpoints"][0]
        self.assertEqual("0x10023DF0", breakpoint["address"])
        self.assertEqual("command-buffer", breakpoint["memory"][1]["name"])
        self.assertIs(True, breakpoint["decoder"]["capture_matrices"])
        self.assertEqual("n64-mtx", breakpoint["decoder"]["matrix_format"])
        self.assertIs(True, breakpoint["decoder"]["capture_lights"])
        self.assertIs(True, breakpoint["decoder"]["capture_normals"])
        self.assertIs(True, breakpoint["decoder"]["capture_textures"])
        self.assertEqual(512, breakpoint["decoder"]["max_matrices"])
        self.assertEqual(512, breakpoint["decoder"]["max_lights"])
        self.assertEqual(512, breakpoint["decoder"]["max_normal_streams"])
        self.assertEqual(1024, breakpoint["decoder"]["max_texture_images"])
        self.assertEqual(16384, breakpoint["decoder"]["max_texture_bytes"])

    def test_all_graphics_submission_hooks_require_a_graphics_task_header(self):
        for filename in ("model-trace-gfx-task.json", "model-trace-character-draws.json",
                         "model-trace-character-activity.json", "model-trace-character-part-tables.json"):
            spec = json.loads((ROOT / "config" / filename).read_text())
            for breakpoint in spec["breakpoints"]:
                if breakpoint["address"] != "0x10023DF0":
                    continue
                self.assertIn({"source": "memory", "name": "task", "offset": 0,
                               "size": 4, "endian": "big", "equals": 1}, breakpoint["when"])
                self.assertIn({"name": "task", "address": "$a2", "length": 64}, breakpoint["memory"])

    def test_checked_in_character_activity_spec_is_valid(self) -> None:
        spec = json.loads(
            (ROOT / "config" / "model-trace-character-activity.json").read_text(
                encoding="utf-8"
            )
        )

        self.assertIs(spec, mupen_trace.validate_spec(spec))
        self.assertEqual("character-model-activity", spec["name"])
        self.assertIs(True, spec["model_inventory_digest"])
        self.assertEqual(1, spec["target"]["bank"])
        breakpoint = spec["breakpoints"][0]
        self.assertEqual("0x10023DF0", breakpoint["address"])
        self.assertEqual("cbfd-character-pool", breakpoint["decoder"]["format"])
        self.assertEqual(0x4F4C, breakpoint["memory"][0]["length"])

    def test_checked_in_character_draw_spec_is_valid(self) -> None:
        spec = json.loads(
            (ROOT / "config" / "model-trace-character-draws.json").read_text(
                encoding="utf-8"
            )
        )

        self.assertIs(spec, mupen_trace.validate_spec(spec))
        self.assertEqual("character-model-draw-ranges", spec["name"])
        breakpoints = {item["name"]: item for item in spec["breakpoints"]}
        self.assertEqual(
            "0x1502CCFC", breakpoints["character-model-draw-enter"]["address"]
        )
        self.assertEqual(
            "0x1502D494", breakpoints["character-normal-part-selected"]["address"]
        )
        self.assertEqual(
            "0x1502D404", breakpoints["character-extra-part-selected"]["address"]
        )
        self.assertEqual(
            "0x1502D544", breakpoints["character-model-draw-return"]["address"]
        )
        self.assertEqual(
            "cbfd-character-draw-range",
            breakpoints["character-model-draw-return"]["decoder"]["format"],
        )
        self.assertIs(
            True, breakpoints["character-model-draw-return"]["decoder"]["walk_nested"]
        )
        self.assertEqual(
            "cbfd-character-f32",
            breakpoints["character-model-draw-return"]["decoder"]["matrix_format"],
        )
        self.assertEqual(
            "n64-mtx",
            breakpoints["character-draws-at-graphics-submit"]["decoder"][
                "matrix_format"
            ],
        )
        self.assertEqual(
            16,
            breakpoints["character-draws-at-graphics-submit"][
                "stop_after_capture_count"
            ],
        )
        self.assertIn(
            {"source": "memory", "name": "task", "offset": 0,
             "size": 4, "endian": "big", "equals": 1},
            breakpoints["character-draws-at-graphics-submit"]["when"],
        )

    def test_checked_in_character_part_table_spec_is_valid(self) -> None:
        spec = json.loads(
            (ROOT / "config" / "model-trace-character-part-tables.json").read_text(
                encoding="utf-8"
            )
        )

        self.assertIs(spec, mupen_trace.validate_spec(spec))
        breakpoint = spec["breakpoints"][0]
        self.assertEqual("0x10023DF0", breakpoint["address"])
        self.assertIs(True, breakpoint["stop_after_capture"])
        self.assertIs(True, breakpoint["decoder"]["capture_character_part_tables"])

    def test_stop_after_capture_requires_boolean(self) -> None:
        spec = {
            "schema_version": 1,
            "name": "bad-stop",
            "breakpoints": [
                {
                    "name": "stop",
                    "address": "0x1000",
                    "stop_after_capture": 1,
                }
            ],
        }

        with self.assertRaisesRegex(mupen_trace.TraceError, "must be boolean"):
            mupen_trace.validate_spec(spec)

    def test_stop_after_capture_count_is_bounded(self) -> None:
        spec = {
            "schema_version": 1,
            "name": "bad-stop-count",
            "breakpoints": [
                {
                    "name": "stop",
                    "address": "0x1000",
                    "stop_after_capture_count": 0,
                }
            ],
        }

        with self.assertRaisesRegex(mupen_trace.TraceError, "between 1 and 100000"):
            mupen_trace.validate_spec(spec)

    def test_matrix_format_is_explicitly_bounded(self) -> None:
        spec = {
            "schema_version": 1,
            "name": "bad-matrix-format",
            "breakpoints": [
                {
                    "name": "capture",
                    "address": "0x1000",
                    "memory": [
                        {"name": "commands", "address": "$a0", "length": 8}
                    ],
                    "decoder": {
                        "format": "f3dex2-cbfd",
                        "memory": "commands",
                        "capture_matrices": True,
                        "matrix_format": "guess",
                    },
                }
            ],
        }

        with self.assertRaisesRegex(mupen_trace.TraceError, "matrix_format"):
            mupen_trace.validate_spec(spec)

    def test_default_trace_state_has_model_namespace(self) -> None:
        self.assertEqual({}, mupen_trace.default_state()["model"])

    def test_character_pool_decoder_preserves_active_model_records(self) -> None:
        data = bytearray(mupen_trace.CHARACTER_POOL_SIZE)
        offset = 3 * mupen_trace.CHARACTER_POOL_RECORD_SIZE
        struct.pack_into(">I", data, offset, 0x80123400)
        data[offset + 4] = 127
        data[offset + 0xAC] = 5
        struct.pack_into(">I", data, offset + 0x144, 0x80246800)

        decoded = mupen_trace.decode_cbfd_character_pool(bytes(data))

        self.assertEqual(1, decoded["active_record_count"])
        self.assertEqual([127], decoded["active_entries"])
        self.assertEqual(
            {
                "slot": 3,
                "record_offset": offset,
                "record_address": mupen_trace.CHARACTER_POOL_ADDRESS + offset,
                "owner_address": 0x80123400,
                "entry": 127,
                "flags": 5,
                "animation_state_address": 0x80246800,
            },
            decoded["active_records"][0],
        )

    def test_character_part_table_headers_preserve_counts_and_addresses(self) -> None:
        pointers = bytearray(mupen_trace.CHARACTER_PART_POINTER_TABLE_SIZE)
        counts = bytearray(mupen_trace.CHARACTER_PART_COUNT_TABLE_SIZE)
        extra_pointers = bytearray(mupen_trace.CHARACTER_PART_POINTER_TABLE_SIZE)
        struct.pack_into(">I", pointers, 4 * 7, 0x80123400)
        struct.pack_into(">H", counts, 2 * 7, 3)
        struct.pack_into(">I", extra_pointers, 4 * 7, 0x80246800)

        decoded = mupen_trace.decode_cbfd_character_part_table_headers(
            bytes(pointers), bytes(counts), bytes(extra_pointers)
        )

        self.assertEqual(
            [
                {
                    "model_index": 7,
                    "part_count": 3,
                    "part_pointer_table_address": 0x80123400,
                    "extra_part_pointer_table_address": 0x80246800,
                }
            ],
            decoded,
        )

    def test_session_timeout_caps_each_debugger_wait(self) -> None:
        debugger = object.__new__(mupen_trace.MupenDebugger)
        debugger.session_deadline = time.monotonic() + 2.0

        deadline = debugger.wait_deadline(300)

        self.assertLessEqual(deadline, debugger.session_deadline)
        self.assertGreater(deadline, time.monotonic())

    def test_session_timeout_is_exposed_by_record_parser(self) -> None:
        args = mupen_trace.build_parser().parse_args(
            [
                "record",
                "--spec",
                "config/model-trace-gfx-task.json",
                "--output",
                "build/trace.jsonl",
                "--session-timeout",
                "45",
            ]
        )

        self.assertEqual(45, args.session_timeout)

    def test_software_backend_executes_lle_graphics_without_changing_default(self):
        parser = mupen_trace.build_parser()
        common = ["record", "--spec", "spec.json", "--output", "build/trace.jsonl"]
        ordinary = parser.parse_args(common)
        command = mupen_trace.runtime_command(ordinary)
        self.assertEqual("dummy", command[command.index("--gfx") + 1])
        self.assertEqual("mupen64plus-rsp-hle", command[command.index("--rsp") + 1])
        software = parser.parse_args([*common, "--software-renderer", "--savestate", "build/frame.st"])
        command = mupen_trace.runtime_command(software)
        self.assertEqual("xvfb-run", command[0])
        self.assertIn("LIBGL_ALWAYS_SOFTWARE=1", command)
        self.assertEqual("mupen64plus-video-angrylion-plus", command[command.index("--gfx") + 1])
        self.assertEqual("mupen64plus-rsp-cxd4-sse2", command[command.index("--rsp") + 1])
        self.assertEqual("build/frame.st", command[command.index("--savestate") + 1])
        software.mupen_args = ["--gfx=dummy"]
        with self.assertRaises(mupen_trace.TraceError):
            mupen_trace.runtime_command(software)

    def test_register_parser_accepts_debugger_format_and_ansi(self) -> None:
        names = [
            "r0", "at", "v0", "v1", "a0", "a1", "a2", "a3",
            "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
            "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
            "t8", "t9", "k0", "k1", "gp", "sp", "sB", "ra",
        ]
        # k0/k1 are printed by Mupen but are not legal probe registers. They
        # still count toward the complete 32-register snapshot.
        output = "\n".join(
            f"\x1b[1m ${name if name in {'r0', 'at', 'gp', 'sp', 'ra'} else name} {index:016X} \x1b[0m"
            for index, name in enumerate(names)
        )
        parsed = mupen_trace.parse_registers(output)

        self.assertEqual(32, len(parsed))
        self.assertEqual(4, parsed["a0"])
        self.assertEqual(31, parsed["ra"])

    def test_address_expressions_resolve_to_guest_32_bit_addresses(self) -> None:
        registers = {"t0": 0xFFFFFFFF80123400, "sp": 0xFFFFFFFF80001000}

        self.assertEqual(0x80123408, mupen_trace.resolve_address("$t0+0x8", registers))
        self.assertEqual(0x80000FF0, mupen_trace.resolve_address("$sp-16", registers))
        self.assertEqual(0x1510D010, mupen_trace.resolve_address("0x1510D010", registers))

    def test_indirect_probe_address_and_length_resolve_from_prior_memory(self) -> None:
        task = bytearray(64)
        task[48:52] = (0x00123400).to_bytes(4, "big")
        task[52:56] = (0x280).to_bytes(4, "big")
        memory = {"task": bytes(task)}
        address = {
            "source": "memory",
            "name": "task",
            "offset": 48,
            "size": 4,
            "map": "kseg0",
        }
        length = {
            "source": "memory",
            "name": "task",
            "offset": 52,
            "size": 4,
            "max": 0x1000,
        }

        self.assertEqual(
            0x80123400,
            mupen_trace.resolve_probe_address(address, {}, memory),
        )
        self.assertEqual(0x280, mupen_trace.resolve_probe_length(length, {}, memory))

    def test_indirect_probe_must_reference_an_earlier_probe(self) -> None:
        spec = {
            "schema_version": 1,
            "name": "forward-reference",
            "breakpoints": [
                {
                    "name": "bad",
                    "address": "0x1234",
                    "memory": [
                        {
                            "name": "payload",
                            "address": {
                                "source": "memory",
                                "name": "task",
                                "offset": 48,
                                "map": "kseg0",
                            },
                            "length": 8,
                        },
                        {"name": "task", "address": "$a0", "length": 64},
                    ],
                }
            ],
        }

        with self.assertRaises(mupen_trace.TraceError):
            mupen_trace.validate_spec(spec)

    def test_dynamic_probe_length_is_bounded_at_runtime(self) -> None:
        task = bytearray(64)
        task[52:56] = (0x1001).to_bytes(4, "big")

        with self.assertRaises(mupen_trace.TraceError):
            mupen_trace.resolve_probe_length(
                {
                    "source": "memory",
                    "name": "task",
                    "offset": 52,
                    "size": 4,
                    "max": 0x1000,
                },
                {},
                {"task": bytes(task)},
            )

    def test_fields_decode_big_endian_memory_and_register_bits(self) -> None:
        registers = {"s0": (5 << 22) | 0x12345}
        memory = {"command": bytes.fromhex("FD0000008ABCDEFF")}

        flat_id = mupen_trace.extract_value(
            {"source": "register", "name": "s0", "mask": "0x003FFFFF"},
            registers,
            memory,
        )
        mode = mupen_trace.extract_value(
            {"source": "register", "name": "s0", "shift": 22, "mask": "0x3F"},
            registers,
            memory,
        )
        address = mupen_trace.extract_value(
            {
                "source": "memory",
                "name": "command",
                "offset": 4,
                "size": 4,
                "endian": "big",
                "mask": "0xF0FFFFFF",
            },
            registers,
            memory,
        )

        self.assertEqual(0x12345, flat_id)
        self.assertEqual(5, mode)
        self.assertEqual(0x80BCDEFF, address)

    def test_memory_parser_ignores_echoed_address(self) -> None:
        output = "mem /8b 0x80122F98\r\nd7 00 00 02 ff ff ff ff \r\n"

        self.assertEqual(
            bytes.fromhex("D7000002FFFFFFFF"),
            mupen_trace.parse_memory_bytes(output, 8),
        )

    def test_render_state_hash_is_canonical(self) -> None:
        first = {"texture": {"mode": 1, "flat_id": 7}, "segments": {}}
        second = {"segments": {}, "texture": {"flat_id": 7, "mode": 1}}

        self.assertEqual(mupen_trace.state_hash(first), mupen_trace.state_hash(second))

    def test_cbfd_command_decoder_tracks_material_state_at_triangles(self) -> None:
        commands = [
            (0xDB060008, 0x80100000),
            (0xDB020000, 0x00000210),
            (0xDB100000, 0x00000000),
            (0xDB100010, 0x80004000),
            (0xDB100020, 0x00000050),
            (0xDC280C0A, 0x801FFF80),
            (0xDC38000E, 0x801FFE00),
            (0xD9FFFFFF, 0x00020400),
            (0xD7000002, 0xFFFFFFFF),
            (0xFD100000, 0x80123140),
            (0xF5101000, 0x00018050),
            (0xF3000000, 0x077FF000),
            (0xEC15FDF0, 0x3B78E42A),
            (0xFC121824, 0xFF33FFFF),
            (0xEF082C3F, 0x00552078),
            (0xFA00F200, 0x11223344),
            (0xFB000000, 0x55667788),
            (0xDA380003, 0x80124000),
            (0x12000000, 0x00000000),
            (0xDE000000, 0x80123400),
            (0xDF000000, 0x00000000),
        ]
        data = b"".join(
            command.to_bytes(4, "big") + argument.to_bytes(4, "big")
            for command, argument in commands
        )

        decoded = mupen_trace.decode_f3dex2_cbfd(data)

        self.assertEqual({"2": 0x80100000}, decoded["segments"])
        self.assertEqual(0x80123140, decoded["texture"]["resolved_pixel_address"])
        self.assertEqual([0x11, 0x22, 0x33, 0x44], decoded["colours"]["primitive"]["rgba"])
        self.assertEqual(0x44, decoded["colours"]["alpha"])
        self.assertEqual(1, decoded["rdp"]["end_count"])
        self.assertEqual(0x80123400, decoded["rdp"]["nested_display_lists"][0]["address"])
        self.assertEqual(0x80124000, decoded["rdp"]["matrix_commands"][0]["address"])
        self.assertEqual(
            0x80124000,
            decoded["rdp"]["matrix_commands"][0]["resolved_address"],
        )
        run = decoded["rdp"]["draw_runs"][0]
        self.assertEqual(4, run["triangle_count"])
        self.assertEqual([0xFC121824, 0xFF33FFFF], run["state"]["combine_mode"])
        self.assertEqual([0xEC15FDF0, 0x3B78E42A], run["state"]["convert_mode"])
        self.assertEqual(0x80123140, run["state"]["texture"]["pixel_image"]["address"])
        self.assertEqual(0x80124000, run["state"]["matrix"]["address"])
        self.assertEqual(0x00020400, run["state"]["geometry_mode"])
        self.assertTrue(run["state"]["lighting_enabled"])
        self.assertEqual(11, run["state"]["lights"]["num_lights"])
        self.assertEqual(0, run["state"]["lights"]["slots"][0]["light_slot"])
        self.assertEqual(0x801FFE00, run["state"]["normal_base"]["address"])
        self.assertEqual(0.5, run["state"]["lights"]["coordinate_modifiers"][12])
        self.assertEqual(80.0, run["state"]["lights"]["coordinate_modifiers"][9])

    def test_cbfd_light_decoder_matches_extended_runtime_layout(self) -> None:
        data = bytearray(48)
        data[0:3] = bytes((0x40, 0x80, 0xC0))
        data[4:7] = bytes((0x20, 0x60, 0xA0))
        struct.pack_into(">3b", data, 8, -64, 0, 64)
        data[12] = 24
        struct.pack_into(">4h", data, 32, -100, 200, -300, 1)

        decoded = mupen_trace.decode_cbfd_light(bytes(data))

        self.assertEqual([0x40, 0x80, 0xC0], decoded["colour"])
        self.assertEqual([-64, 0, 64], decoded["direction_s8"])
        self.assertAlmostEqual(-2 ** -0.5, decoded["direction_normalized"][0])
        self.assertEqual(1.5, decoded["attenuation"])
        self.assertEqual([-100, 200, -300, 1], decoded["position_s16"])

    def test_runtime_light_capture_is_attached_to_draw_run(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xDB020000, 0x30),
                (0xDC280C0A, 0x801FFF80),
                (0x05000204, 0),
                (0xDF000000, 0),
            )
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(commands)
        light = {
            "address": 0x801FFF80,
            "sha256": "light-digest",
            "colour": [1, 2, 3],
            "colour_copy": [4, 5, 6],
            "direction_s8": [0, 0, 127],
            "direction_normalized": [0.0, 0.0, 1.0],
            "attenuation": 0.0,
            "position_s16": [0, 0, 0, 0],
        }

        mupen_trace.attach_runtime_lights(decoded, [light])

        slot = decoded["rdp"]["draw_runs"][0]["state"]["lights"]["slots"][0]
        self.assertEqual(0, slot["captured_light_index"])
        self.assertEqual("light-digest", slot["sha256"])
        self.assertEqual([1, 2, 3], slot["decoded"]["colour"])

    def test_runtime_normal_stream_is_attached_to_draw_run(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xDC38000E, 0x801FFE00),
                (0x05000204, 0),
                (0xDF000000, 0),
            )
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(commands)
        stream = {
            "address": 0x801FFE00,
            "sha256": "normal-digest",
            "layout": "f3dex2-cbfd-normal-xy-s8-32",
            "normal_xy_s8": [[index, -index] for index in range(32)],
        }

        mupen_trace.attach_runtime_normal_streams(decoded, [stream])

        normal = decoded["rdp"]["draw_runs"][0]["state"]["normal_base"]
        self.assertEqual(0, normal["captured_normal_stream_index"])
        self.assertEqual("normal-digest", normal["sha256"])
        self.assertEqual([31, -31], normal["normal_xy_s8"][31])

    def test_runtime_texture_load_resolves_and_captures_segmented_image(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xDB06002C, 0x00140000),
                (0xFD100000, 0x0B000000),
                (0xF5101000, 0x00018050),
                (0xF3000000, 0x007FF000),
                (0x05000204, 0),
                (0xDF000000, 0),
            )
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(commands)
        image = decoded["rdp"]["tmem"][0]["image"]

        self.assertEqual(0x80140000, image["resolved_address"])
        self.assertEqual(2048, image["texel_count"])
        self.assertEqual(4096, image["byte_length"])

        payload = bytes(index & 0xFF for index in range(4096))

        class MemoryDebugger:
            def command(self, command: str, timeout: int) -> str:
                del timeout
                _, length_token, address_token = command.split()
                length = int(length_token[1:-1])
                address = int(address_token, 16)
                offset = address - 0x80140000
                return payload[offset : offset + length].hex(" ")

        images, evidence, unresolved = mupen_trace.capture_runtime_texture_images(
            MemoryDebugger(), decoded["rdp"]["tmem"], 4, 0x4000, 1
        )
        mupen_trace.attach_runtime_texture_images(decoded, images)

        self.assertEqual([], unresolved)
        self.assertEqual(1, len(images))
        self.assertEqual(4096, evidence[0]["length"])
        run_image = decoded["rdp"]["draw_runs"][0]["state"]["texture"][
            "pixel_image"
        ]
        self.assertEqual(0, run_image["captured_texture_image_index"])
        self.assertEqual(images[0]["sha256"], run_image["sha256"])

    def test_runtime_tlut_load_length_uses_rgba16_entries(self) -> None:
        image = mupen_trace.runtime_texture_image_record(
            {"command": 0xFD100000, "address": 0x80100000},
            0xF0000000,
            0x073FC000,
            "tlut",
        )

        self.assertIsNotNone(image)
        self.assertEqual(256, image["texel_count"])
        self.assertEqual(512, image["byte_length"])

    def test_rsp_matrix_decoder_combines_split_fixed_point_values(self) -> None:
        data = bytearray(64)
        values = (
            (1.0, 0.25, -0.5, 0.0),
            (0.0, 1.0, 0.0, 0.0),
            (0.5, 0.0, 1.0, 0.0),
            (10.5, 11.25, -12.75, 1.0),
        )
        for index, value in enumerate(item for row in values for item in row):
            fixed = round(value * 65536) & 0xFFFFFFFF
            struct.pack_into(">H", data, index * 2, fixed >> 16)
            struct.pack_into(">H", data, 0x20 + index * 2, fixed & 0xFFFF)

        decoded = mupen_trace.decode_rsp_matrix(bytes(data))

        self.assertEqual([list(row) for row in values], decoded["rows"])
        self.assertEqual([10.5, 11.25, -12.75], decoded["translation"])

    def test_character_matrix_decoder_reads_float_affine_components(self) -> None:
        data = struct.pack(
            ">16f",
            0.5,
            0.0,
            0.0,
            123.0,
            0.0,
            0.5,
            0.0,
            float("nan"),
            0.0,
            0.0,
            0.5,
            -999.0,
            10.0,
            20.0,
            30.0,
            0.0,
        )

        decoded = mupen_trace.decode_cbfd_character_matrix(data)

        self.assertEqual("decoded-affine-components", decoded["status"])
        self.assertEqual(
            [
                [0.5, 0.0, 0.0, 0.0],
                [0.0, 0.5, 0.0, 0.0],
                [0.0, 0.0, 0.5, 0.0],
                [10.0, 20.0, 30.0, 1.0],
            ],
            decoded["rows"],
        )
        self.assertEqual([10.0, 20.0, 30.0], decoded["translation"])

    def test_character_matrix_decoder_rejects_invalid_affine_components(self) -> None:
        values = [0.0] * 16
        values[0] = float("nan")

        decoded = mupen_trace.decode_cbfd_character_matrix(
            struct.pack(">16f", *values)
        )

        self.assertEqual("invalid-or-uninitialized-at-capture", decoded["status"])
        self.assertIsNone(decoded["rows"])
        self.assertIsNone(decoded["translation"])

    def test_runtime_matrix_capture_is_attached_to_draw_run(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xDA380003, 0x80124000),
                (0x01003006, 0x80130000),
                (0x05000204, 0),
                (0xDF000000, 0),
            )
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(commands)
        matrix = {
            "address": 0x80124000,
            "sha256": "matrix-digest",
            "references": [],
            "rows": [],
            "translation": [1.0, 2.0, 3.0],
        }

        mupen_trace.attach_runtime_matrices(decoded, [matrix])

        run = decoded["rdp"]["draw_runs"][0]
        self.assertEqual(0, run["captured_matrix_index"])
        self.assertEqual("matrix-digest", run["matrix_sha256"])
        self.assertEqual([1.0, 2.0, 3.0], run["matrix_translation"])
        self.assertIn("pose_state_hash", run)

    def test_vertex_lighting_keeps_load_state_across_later_draw_changes(self) -> None:
        commands = (
            (0xDA380007, 0x80100000),  # Projection LOAD.
            (0xDA380003, 0x80100100),  # Model-view LOAD.
            (0xD9FFFFFF, 0x20000),
            (0xDB020000, 96),
            (0xDC280C0A, 0x80101000),
            (0xDC38000E, 0x80102000),
            (0x01003006, 0x80103000),  # Load slots 0..2.
            (0xDA380003, 0x80100200),
            (0xDC280C0A, 0x80101100),
            (0xDC38000E, 0x80102100),
            (0xDD000000, 0),
            (0x01001006, 0x80103030),  # Replace only slot 2.
            (0xDA380003, 0x80100300),
            (0x05000204, 0),
            (0x02000002, 0),  # Modify slot 1; source load no longer sufficient.
            (0x06000204, 0x00000402),
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(b"".join(
            struct.pack(">II", *pair) for pair in commands
        ))
        loads = decoded["rdp"]["vertex_loads"]
        draws = decoded["rdp"]["draw_runs"]
        self.assertEqual([[0, 0, 1]], draws[0]["vertex_load_indices"])
        self.assertEqual([[0, None, 1], [0, 1, None]], draws[1]["vertex_load_indices"])
        self.assertEqual(0x80100100, loads[0]["state"]["matrix"]["address"])
        self.assertEqual(0x80100200, loads[1]["state"]["matrix"]["address"])
        self.assertEqual(0x80100300, draws[0]["state"]["matrix"]["address"])
        self.assertFalse(loads[0]["state"]["lights"]["advanced_lighting"])
        self.assertTrue(loads[1]["state"]["lights"]["advanced_lighting"])
        lights = [{"address": addr, "sha256": str(addr), **mupen_trace.decode_cbfd_light(bytes(48))}
                  for addr in (0x80101000, 0x80101100)]
        normals = [{"address": addr, "sha256": str(addr), "layout": "test",
                    "normal_xy_s8": [[value, 0]] * 32}
                   for addr, value in ((0x80102000, 1), (0x80102100, 2))]
        mupen_trace.attach_runtime_lights(decoded, lights)
        mupen_trace.attach_runtime_normal_streams(decoded, normals)
        self.assertEqual(str(0x80101000), loads[0]["state"]["lights"]["slots"][0]["sha256"])
        self.assertEqual(str(0x80101100), loads[1]["state"]["lights"]["slots"][0]["sha256"])
        self.assertEqual([1, 0], loads[0]["state"]["normal_base"]["normal_xy_s8"][0])
        self.assertEqual([2, 0], loads[1]["state"]["normal_base"]["normal_xy_s8"][0])

    def test_projection_multiply_and_model_view_stack_use_row_vector_order(self) -> None:
        commands = (
            (0xDA380007, 0x80100000),  # Projection LOAD translation.
            (0xDA380005, 0x80100100),  # Projection MUL scale.
            (0xDA380003, 0x80100200),  # Model-view LOAD translation.
            (0xDA380000, 0x80100300),  # Model-view PUSH and MUL scale.
            (0x01003006, 0x80110000),
            (0xD8380002, 64),
            (0x01003006, 0x80110000),
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(b"".join(
            struct.pack(">II", *pair) for pair in commands
        ))
        identity = [[float(i == j) for j in range(4)] for i in range(4)]
        matrices = []
        for address, scale, translation in (
            (0x80100000, 1, 10), (0x80100100, 2, 0),
            (0x80100200, 1, 3), (0x80100300, 4, 0),
        ):
            rows = [row[:] for row in identity]
            rows[0][0] = scale
            rows[3][0] = translation
            matrices.append({"address": address, "rows": rows, "sha256": str(address),
                             "translation": rows[3][:3]})
        mupen_trace.attach_runtime_matrices(decoded, matrices)
        first, second = [load["processing_matrices"] for load in decoded["rdp"]["vertex_loads"]]
        # x=1 -> model-view 4*x+3=7 -> projection 2*x+10=24.
        self.assertEqual(24, first["combined_rows"][0][0] + first["combined_rows"][3][0])
        self.assertEqual(18, second["combined_rows"][0][0] + second["combined_rows"][3][0])
        self.assertEqual([str(0x80100000), str(0x80100100)], first["projection_sha256"])
        self.assertEqual(4, len(decoded["rdp"]["matrix_commands"]))
        mupen_trace.attach_runtime_matrices(decoded, matrices[1:])
        self.assertIsNone(decoded["rdp"]["vertex_loads"][0]["processing_matrices"]["combined_rows"])

    def test_vertex_processing_does_not_invent_initial_projection_or_stack(self) -> None:
        commands = (
            (0xDA380003, 0x80100000),
            (0x01003006, 0x80110000),
            (0xDA380005, 0x80100000),  # MUL cannot establish unknown projection.
            (0xD8380002, 64),  # Pop underflow cannot establish a model-view.
            (0x01003006, 0x80110000),
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(b"".join(
            struct.pack(">II", *pair) for pair in commands
        ))
        mupen_trace.attach_runtime_matrices(decoded, [{
            "address": 0x80100000, "sha256": "identity", "translation": [0, 0, 0],
            "rows": [[float(i == j) for j in range(4)] for i in range(4)],
        }])
        first, second = decoded["rdp"]["vertex_loads"]
        self.assertIsNotNone(first["processing_matrices"]["model_view_rows"])
        self.assertIsNone(first["processing_matrices"]["combined_rows"])
        self.assertIsNone(second["processing_matrices"]["model_view_rows"])
        self.assertIsNone(second["processing_matrices"]["projection_rows"])

    def test_cbfd_tri4_cache_indices_preserve_all_corners(self) -> None:
        faces = [[0, 1, 18], [3, 4, 5], [6, 7, 8], [9, 10, 11]]
        command = 0x10000000 | (1 << 18) | (4 << 15) | (3 << 10) | (4 << 5) | 5
        argument = (2 << 30) | (6 << 25) | (7 << 20) | (8 << 15) | (9 << 10) | (10 << 5) | 11
        self.assertEqual(faces, mupen_trace.triangle_cache_indices(command, argument))

    def test_vertex_processing_refresh_uses_verified_matrix_bytes(self) -> None:
        data = b"".join(struct.pack(">II", *pair) for pair in (
            (0xDA380007, 0x80100000), (0xDA380003, 0x80100000),
            (0x01003006, 0x80110000), (0x05000204, 0),
        ))
        state = mupen_trace.decode_f3dex2_cbfd(data)
        state["rdp"]["model_correlations"] = []
        integers = [int(i == j) for i in range(4) for j in range(4)]
        matrix_data = struct.pack(">16h16H", *integers, *([0] * 16))
        matrix_digest = hashlib.sha256(matrix_data).hexdigest()
        state["joint_matrices"] = [{
            "address": 0x80100000, "sha256": matrix_digest,
            "layout": "n64-mtx-row-major-4x4-s16.16-split",
            "rows": [[999] * 4] * 4,  # Derived values cannot override captured bytes.
        }]
        probes = [{"name": name, "length": len(payload),
                   "resolved_address": address,
                   "sha256": hashlib.sha256(payload).hexdigest(),
                   "data_base64": base64.b64encode(payload).decode("ascii")}
                  for name, address, payload in (
                      ("command-buffer", "0x80120000", data),
                      ("runtime-matrix-0000", "0x80100000", matrix_data),
                  )]
        event = {"state": state, "evidence": {"memory": probes}}
        original = json.dumps(state["rdp"]["draw_runs"][0]["state"], sort_keys=True)
        mupen_trace.refresh_trace_model_correlations(event, [])
        processing = state["rdp"]["replayed_vertex_loads"][0]["processing_matrices"]
        self.assertEqual([[float(i == j) for j in range(4)] for i in range(4)],
                         processing["combined_rows"])
        self.assertEqual(original, json.dumps(state["rdp"]["draw_runs"][0]["state"], sort_keys=True))
        probes[1]["data_base64"] = base64.b64encode(bytes(64)).decode("ascii")
        with self.assertRaisesRegex(mupen_trace.TraceError, "identity changed"):
            mupen_trace.refresh_trace_model_correlations(event, [])

    def test_runtime_vertex_capture_deduplicates_spans_and_enforces_bounds(self) -> None:
        commands = []

        class MemoryDebugger:
            def command(self, command: str, timeout: int) -> str:
                commands.append(command)
                return bytes(48).hex(" ")

        loads = [{"resolved_address": 0x80100000, "vertex_count": count} for count in (2, 3)]
        probes = mupen_trace.capture_runtime_vertices(MemoryDebugger(), loads, 1, 1)
        self.assertEqual(["mem /48b 0x80100000"], commands)
        self.assertEqual(48, probes[0]["length"])
        self.assertEqual(hashlib.sha256(bytes(48)).hexdigest(), probes[0]["sha256"])
        with self.assertRaisesRegex(mupen_trace.TraceError, "outside RDRAM"):
            mupen_trace.capture_runtime_vertices(MemoryDebugger(), [{"resolved_address": 0x807FFFF0, "vertex_count": 2}], 1, 1)
        with self.assertRaisesRegex(mupen_trace.TraceError, "limit is 1"):
            mupen_trace.capture_runtime_vertices(MemoryDebugger(), [*loads, {"resolved_address": 0x80200000, "vertex_count": 2}], 1, 1)

    def test_projection_capture_keeps_n64_layout_with_float_character_palette(self) -> None:
        data = b"".join(struct.pack(">II", *pair) for pair in (
            (0xDA380007, 0x80100000), (0xDA380003, 0x80100100),
        ))
        decoded = mupen_trace.decode_f3dex2_cbfd(data)
        integers = [int(i == j) for i in range(4) for j in range(4)]
        split_matrix = struct.pack(">16h16H", *integers, *([0] * 16))
        float_matrix = struct.pack(">16f", *integers)

        class MemoryDebugger:
            def command(self, command: str, timeout: int) -> str:
                return (split_matrix if command.endswith("0x80100000") else float_matrix).hex(" ")

        matrices, _, unresolved = mupen_trace.capture_runtime_matrices(
            MemoryDebugger(), decoded["rdp"]["matrix_commands"], 2, "cbfd-character-f32", 1
        )
        self.assertEqual([], unresolved)
        self.assertEqual("n64-mtx-row-major-4x4-s16.16-split", matrices[0]["layout"])
        self.assertEqual("cbfd-character-row-major-f32", matrices[1]["layout"])
        self.assertEqual(matrices[0]["rows"], matrices[1]["rows"])

    def test_runtime_matrix_address_maps_physical_but_not_segmented_values(self) -> None:
        self.assertEqual(
            0x80089470,
            mupen_trace.resolve_runtime_matrix_address(0x00089470),
        )
        self.assertEqual(
            0x80124000,
            mupen_trace.resolve_runtime_matrix_address(0x80124000),
        )
        self.assertIsNone(mupen_trace.resolve_runtime_matrix_address(0x03000000))
        self.assertEqual(
            0x80125680,
            mupen_trace.resolve_runtime_matrix_address(
                0x03000680,
                {"3": 0x80125000},
            ),
        )

    def test_cbfd_decoder_resolves_segmented_joint_matrix_at_command_time(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xDB06000C, 0x80125000),
                (0xDA380003, 0x03000680),
                (0x01003006, 0x80130000),
                (0x05000204, 0),
                (0xDF000000, 0),
            )
        )

        decoded = mupen_trace.decode_f3dex2_cbfd(commands)

        matrix = decoded["rdp"]["matrix_commands"][0]
        self.assertEqual(0x80125680, matrix["resolved_address"])
        self.assertEqual(3, matrix["segment"])
        self.assertEqual(0x680, matrix["segment_offset"])
        self.assertEqual(0x80125000, matrix["segment_base_address"])
        self.assertEqual(26, matrix["segment_relative_matrix_slot"])
        self.assertEqual(26, matrix["matrix_slot"])
        self.assertEqual(
            0x80125680,
            decoded["rdp"]["draw_runs"][0]["state"]["matrix"]["resolved_address"],
        )

    def test_cbfd_matrix_identity_preserves_interior_segment_rebases(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xDB06000C, 0x80125000),
                (0xDA380003, 0x03000300),
                (0xDB06000C, 0x80125300),
                (0xDA380003, 0x03000000),
                (0xDF000000, 0),
            )
        )

        decoded = mupen_trace.decode_f3dex2_cbfd(commands)
        first, second = decoded["rdp"]["matrix_commands"]

        self.assertEqual(0x80125300, first["resolved_address"])
        self.assertEqual(0x80125300, second["resolved_address"])
        self.assertEqual(0x80125000, first["segment_base_address"])
        self.assertEqual(0x80125300, second["segment_base_address"])
        self.assertEqual(12, first["segment_relative_matrix_slot"])
        self.assertEqual(0, second["segment_relative_matrix_slot"])
        self.assertEqual(12, first["matrix_slot"])
        self.assertEqual(0, second["matrix_slot"])

        class MemoryDebugger:
            def command(self, command: str, timeout: int) -> str:
                del command, timeout
                return bytes(64).hex(" ")

        matrices, _, unresolved = mupen_trace.capture_runtime_matrices(
            MemoryDebugger(),
            decoded["rdp"]["matrix_commands"],
            4,
            "n64-mtx",
            1,
        )
        self.assertEqual([], unresolved)
        self.assertEqual(1, len(matrices))
        self.assertEqual(
            [0x80125000, 0x80125300],
            [
                reference["segment_base_address"]
                for reference in matrices[0]["references"]
            ],
        )
        self.assertEqual(
            [12, 0],
            [
                reference["segment_relative_matrix_slot"]
                for reference in matrices[0]["references"]
            ],
        )

    def test_geometry_clusters_normalize_vertex_addresses_and_correlate_prefixes(self) -> None:
        runtime = b"".join(
            command.to_bytes(4, "big") + argument.to_bytes(4, "big")
            for command, argument in (
                (0x01019032, 0x80122E08),
                (0x12140483, 0xC0110462),
                (0x14249907, 0xC86298E5),
                (0xDF000000, 0),
            )
        )
        static = b"".join(
            command.to_bytes(4, "big") + argument.to_bytes(4, "big")
            for command, argument in (
                (0x01019032, 0x01000000),
                (0x12140483, 0xC0110462),
                (0x14249907, 0xC86298E5),
                (0x1614AD87, 0xD2A3A967),
                (0xDF000000, 0),
            )
        )
        runtime_clusters = mupen_trace.geometry_clusters(runtime)
        static_cluster = mupen_trace.geometry_clusters(static)[0]
        index = [
            {
                "bank": 4,
                "entry": entry,
                "segment": 0,
                "model_sha1": "same-model",
                "static_cluster_index": 0,
                "static_first_face": 0,
                "commands": static_cluster["commands"],
                "triangle_count": static_cluster["triangle_count"],
                "material_run": {
                    "index": 3,
                    "first_face": 0,
                    "face_count": 12,
                    "pixel": {"source": "flat-archive", "flat_index": 42, "mode": 0},
                    "palette": None,
                    "matrix_index": 2,
                },
            }
            for entry in (5, 8)
        ]

        correlations = mupen_trace.correlate_model_clusters(runtime_clusters, index)

        self.assertEqual("equivalent-aliases", correlations[0]["status"])
        self.assertEqual(2, correlations[0]["candidate_count"])
        self.assertEqual(1, correlations[0]["unique_model_count"])
        self.assertEqual([5, 8], [item["entry"] for item in correlations[0]["candidates"]])
        self.assertEqual([8, 8], [item["triangle_count"] for item in correlations[0]["candidates"]])
        self.assertEqual(runtime_clusters[0]["signature"], correlations[0]["signature"])

    def test_geometry_clusters_keep_cached_vertices_across_render_state(self) -> None:
        commands = (
            (0x01003006, 0x01000000),
            (0xDC38000E, 0x01000100),
            (0x05000204, 0),
            (0xDA380003, 0x03000040),
            (0xFCFFFFFF, 0xFFFFFFFF),
            (0x05040200, 0),
            (0xDF000000, 0),
            (0x05000204, 0),
        )
        clusters = mupen_trace.geometry_clusters(b"".join(
            struct.pack(">II", *pair) for pair in commands
        ))
        self.assertEqual([0, 1, 2], [c["first_face"] for c in clusters])
        self.assertEqual([16, 40, 56], [c["triangle_command_offset"] for c in clusters])
        self.assertEqual([24, 48, 64], [c["triangle_end_offset"] for c in clusters])
        self.assertEqual(3, sum(c["triangle_count"] for c in clusters))
        self.assertEqual([[0x01003006, 0]] * 3, [c["commands"][0] for c in clusters])

    def test_refresh_correlations_replays_checked_command_evidence(self) -> None:
        data = b"".join(struct.pack(">II", *pair) for pair in (
            (0x01003006, 0x01000000), (0x05000204, 0),
            (0xFCFFFFFF, 0xFFFFFFFF), (0x05040200, 0), (0xDF000000, 0),
        ))
        state = mupen_trace.decode_f3dex2_cbfd(data)
        state["rdp"]["model_correlations"] = []
        state["rdp"]["geometry_clusters"] = []
        probe = {"name": "command-buffer", "resolved_address": "0x80100000",
                 "length": len(data), "sha256": hashlib.sha256(data).hexdigest(),
                 "data_base64": base64.b64encode(data).decode("ascii")}
        event = {"state": state, "evidence": {"memory": [probe]}}
        self.assertTrue(mupen_trace.refresh_trace_model_correlations(event, []))
        self.assertEqual(2, len(state["rdp"]["geometry_clusters"]))
        self.assertEqual([[0], [1]], [
            c["draw_run_indices"] for c in state["rdp"]["material_run_correlations"]
        ])
        self.assertEqual([{"mode": None, "known_bits": 0}] * 2,
                         [draw["replayed_face_culling"] for draw in state["rdp"]["draw_runs"]])
        probe["sha256"] = "changed"
        with self.assertRaisesRegex(mupen_trace.TraceError, "identity changed"):
            mupen_trace.refresh_trace_model_correlations(event, [])

    def test_culling_replay_requires_resolved_call_ancestry(self) -> None:
        root = b"".join(struct.pack(">II", *pair) for pair in (
            (0xD9FFF9FF, 0x400), (0xDE000000, 0x80002000),
            (0x05000204, 0), (0xDE000000, 0x80003000),
            (0x05000204, 0), (0xD9FFFFFF, 0x400),
            (0x05000204, 0), (0xD9FFFDFF, 0), (0x05000204, 0), (0xDF000000, 0),
        ))
        nested = b"".join(struct.pack(">II", *pair) for pair in (
            (0xEF082C3F, 0x00552230), (0xDF000000, 0),
        ))
        origins = []
        flattened, unresolved = mupen_trace.flatten_display_lists(
            root, {0x80002000: nested}, root_address=0x80001000, origins=origins,
        )
        self.assertEqual([0x80003000], unresolved)
        states = list(mupen_trace.replay_face_culling(flattened, origins).values())
        self.assertEqual([0x400, None, None, 0x400], [state["mode"] for state in states])
        self.assertEqual([0x600, 0, 0x400, 0x600], [state["known_bits"] for state in states])
        self.assertIsNone(next(iter(mupen_trace.replay_face_culling(flattened).values()))["mode"])
        with self.assertRaisesRegex(mupen_trace.TraceError, "origin span"):
            mupen_trace.replay_face_culling(flattened, origins[:-1])

    def test_culling_replay_declines_unexecuted_conditional_flow(self) -> None:
        for conditional in (0x03000000, 0x04000000):
            root = b"".join(struct.pack(">II", *pair) for pair in (
                (0xD9FFF9FF, 0x400), (0xDE000000, 0x80002000),
                (0x05000204, 0), (0xDF000000, 0),
            ))
            nested = b"".join(struct.pack(">II", *pair) for pair in (
                (conditional, 0), (0xD9FFF9FF, 0), (0xDF000000, 0),
            ))
            origins = []
            flattened, _ = mupen_trace.flatten_display_lists(
                root, {0x80002000: nested}, root_address=0x80001000, origins=origins,
            )
            self.assertEqual([{"mode": None, "known_bits": 0}],
                             list(mupen_trace.replay_face_culling(flattened, origins).values()))

    def test_material_correlation_joins_runtime_address_to_static_flat_id(self) -> None:
        draw_runs = [
            {
                "command_offset": 8,
                "state": {
                    "texture": {
                        "pixel_image": {"address": 0x80220000},
                        "palette_image": {"address": 0x80221000},
                    }
                },
            }
        ]
        material = {
            "index": 7,
            "first_face": 10,
            "face_count": 4,
            "pixel": {"source": "flat-archive", "flat_index": 3097, "mode": 0},
            "palette": {"source": "flat-archive", "flat_index": 3097, "mode": 2},
            "matrix_index": 22,
        }
        correlations = [
            {
                "runtime_cluster_index": 0,
                "command_offset": 0,
                "command_count": 2,
                "candidates": [
                    {"bank": 1, "entry": 1, "segment": 0, "material_run": material}
                ],
            }
        ]

        joined = mupen_trace.correlate_material_runs(draw_runs, correlations)

        self.assertEqual("unique", joined[0]["status"])
        self.assertEqual(3097, joined[0]["texture_join"]["pixel"]["static"]["flat_index"])
        self.assertEqual(0x80220000, joined[0]["texture_join"]["pixel"]["runtime_address"])
        self.assertEqual(22, joined[0]["matrix_slot"]["static"])
        self.assertEqual(0, draw_runs[0]["material_correlation_index"])

    def test_equivalent_material_aliases_do_not_guess_model_identity(self) -> None:
        draw_runs = [
            {
                "command_offset": 8,
                "state": {
                    "texture": {"pixel_image": None, "palette_image": None},
                    "matrix": None,
                },
            }
        ]
        material = {
            "index": 0,
            "first_face": 0,
            "face_count": 4,
            "pixel": None,
            "palette": None,
            "matrix_index": None,
        }
        correlations = [
            {
                "runtime_cluster_index": 0,
                "command_offset": 0,
                "command_count": 2,
                "candidates": [
                    {"bank": 4, "entry": 5, "segment": 0, "material_run": material},
                    {"bank": 4, "entry": 8, "segment": 0, "material_run": material},
                ],
            }
        ]

        joined = mupen_trace.correlate_material_runs(draw_runs, correlations)

        self.assertEqual("equivalent-material-aliases", joined[0]["status"])
        self.assertIsNone(joined[0]["resolved"])
        self.assertEqual(material, joined[0]["common_material"])
        self.assertIn("texture_join", joined[0])

    def test_cbfd_command_decoder_rejects_partial_command(self) -> None:
        with self.assertRaises(mupen_trace.TraceError):
            mupen_trace.decode_f3dex2_cbfd(b"\xDF")

    def test_nested_target_resolution_tracks_segment_bases(self) -> None:
        data = b"".join(
            command.to_bytes(4, "big") + argument.to_bytes(4, "big")
            for command, argument in (
                (0xDB060020, 0x00120000),
                (0xDE000000, 0x08000340),
                (0xDE000000, 0x80123400),
                (0xDF000000, 0),
            )
        )
        segments = {}

        targets = mupen_trace.update_segments_and_targets(data, segments)
        decoded = mupen_trace.decode_f3dex2_cbfd(data)

        self.assertEqual({8: 0x00120000}, segments)
        self.assertEqual([0x80120340, 0x80123400], targets)
        self.assertEqual(
            [0x80120340, 0x80123400],
            [
                record["resolved_address"]
                for record in decoded["rdp"]["nested_display_lists"]
            ],
        )

    def test_nested_capture_replays_segment_changes_in_execution_order(self) -> None:
        def commands(*values: tuple[int, int]) -> bytes:
            return b"".join(struct.pack(">II", *value) for value in values)

        root = commands(
            (0xDE000000, 0x80100000),
            (0xDF000000, 0),
        )
        parent = commands(
            (0xDB060020, 0x00120000),
            (0xDE000000, 0x08000040),
            (0xDB060020, 0x00130000),
            (0xDE000000, 0x08000000),
            (0xDF000000, 0),
        )
        first_state = commands((0xEF000000, 1), (0xDF000000, 0))
        second_state = commands((0xEF000000, 2), (0xDF000000, 0))
        memory = {
            0x80100000: parent,
            0x80120040: first_state,
            0x80130000: second_state,
        }

        class MemoryDebugger:
            def command(self, command: str, timeout: int) -> str:
                del timeout
                _, length_token, address_token = command.split()
                length = int(length_token[1:-1])
                address = int(address_token, 16)
                data = memory[address]
                return (data + bytes(length - len(data))).hex(" ")

        captured, evidence = mupen_trace.capture_nested_display_lists(
            MemoryDebugger(), root, 8, 0x400, 1
        )

        self.assertEqual(
            [0x80100000, 0x80120040, 0x80130000],
            [record["address"] for record in captured],
        )
        self.assertEqual(3, len(evidence))
        flattened, unresolved = mupen_trace.flatten_display_lists(
            root,
            {record["address"]: record["data"] for record in captured},
        )
        self.assertEqual([], unresolved)
        self.assertIn(struct.pack(">II", 0xEF000000, 1), flattened)
        self.assertIn(struct.pack(">II", 0xEF000000, 2), flattened)

    def test_nested_display_list_state_is_inlined_before_parent_draw(self) -> None:
        root = b"".join(
            command.to_bytes(4, "big") + argument.to_bytes(4, "big")
            for command, argument in (
                (0xDE000000, 0x80123400),
                (0x01004008, 0x80130000),
                (0x05000204, 0),
                (0xDF000000, 0),
            )
        )
        nested = b"".join(
            command.to_bytes(4, "big") + argument.to_bytes(4, "big")
            for command, argument in (
                (0xFA00F200, 0x11223344),
                (0xFB000000, 0x55667788),
                (0xDF000000, 0),
            )
        )

        flattened, unresolved = mupen_trace.flatten_display_lists(
            root,
            {0x80123400: nested},
        )
        decoded = mupen_trace.decode_f3dex2_cbfd(flattened)

        self.assertEqual([], unresolved)
        self.assertEqual(7, len(flattened) // 8)
        draw_state = decoded["rdp"]["draw_runs"][0]["state"]
        self.assertEqual([0x11, 0x22, 0x33, 0x44], draw_state["colours"]["primitive"]["rgba"])
        self.assertEqual([0x55, 0x66, 0x77, 0x88], draw_state["colours"]["environment"]["rgba"])

    def test_command_origins_distinguish_repeated_instance_calls(self):
        nested = struct.pack(">4I", 0x05000204, 0, 0xDF000000, 0)
        root = struct.pack(">6I", 0xDE000000, 0x80110000,
                           0xDE000000, 0x80110000, 0xDF000000, 0)
        origins = []
        flat, missing = mupen_trace.flatten_display_lists(
            root, {0x80110000: nested}, root_address=0x80100000, origins=origins)
        self.assertEqual([], missing)
        self.assertEqual(len(flat) // 8, len(origins))
        self.assertEqual([0x80100000, 0x80110000], origins[1])
        self.assertEqual([0x80100008, 0x80110000], origins[4])

    def test_audio_task_is_not_replayed_as_graphics(self):
        raw = struct.pack(">I", 2) + bytes(60)
        event = {"evidence": {"memory": [{"name": "task", "length": 64,
                 "data_base64": base64.b64encode(raw).decode(),
                 "sha256": hashlib.sha256(raw).hexdigest()}]}}
        self.assertEqual(2, mupen_trace.captured_task_type(event))
        self.assertFalse(mupen_trace.refresh_trace_model_correlations(event, []))
        event["evidence"]["memory"][0]["sha256"] = "0" * 64
        with self.assertRaises(mupen_trace.TraceError):
            mupen_trace.captured_task_type(event)

    def test_output_is_confined_to_build(self) -> None:
        with self.assertRaises(mupen_trace.TraceError):
            mupen_trace.output_path("docs/trace.jsonl")

        self.assertEqual(
            (ROOT / "build" / "trace.jsonl").resolve(),
            mupen_trace.output_path("build/trace.jsonl"),
        )

    def test_rejects_shell_syntax_in_probe_address(self) -> None:
        spec = {
            "schema_version": 1,
            "name": "unsafe",
            "breakpoints": [
                {
                    "name": "bad",
                    "address": "0x1234",
                    "memory": [{"name": "probe", "address": "$t0;quit", "length": 4}],
                }
            ],
        }

        with self.assertRaises(mupen_trace.TraceError):
            mupen_trace.validate_spec(spec)


if __name__ == "__main__":
    unittest.main()
