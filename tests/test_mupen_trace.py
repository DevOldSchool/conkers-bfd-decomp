from __future__ import annotations

import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import mupen_trace


ROOT = Path(__file__).resolve().parent.parent


class MupenTraceTests(unittest.TestCase):
    def test_public_command_uses_pinned_container_recorder(self) -> None:
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")
        trace_case = script.split("    mupen-trace)", 1)[1].split("        ;;", 1)[0]

        self.assertIn("ensure_mupen_image", trace_case)
        self.assertIn("ensure_warm_container", trace_case)
        self.assertIn("scripts/mupen_trace.py record", trace_case)
        self.assertIn("mupen-trace --spec <path> --output <build-path>", script)

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
        self.assertIs(True, breakpoint["decoder"]["capture_lights"])
        self.assertIs(True, breakpoint["decoder"]["capture_normals"])

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
        self.assertEqual(26, matrix["matrix_slot"])
        self.assertEqual(
            0x80125680,
            decoded["rdp"]["draw_runs"][0]["state"]["matrix"]["resolved_address"],
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
        self.assertEqual(runtime_clusters[0]["signature"], correlations[0]["signature"])

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
