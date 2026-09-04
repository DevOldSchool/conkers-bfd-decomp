from __future__ import annotations

import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import texture_assets


def sample_payload(
    seed: int = 0,
    width: int = texture_assets.WIDTH,
    height: int = texture_assets.HEIGHT,
) -> bytes:
    pixel_size = width * height // 2
    pixels = bytes((index + seed) & 0xFF for index in range(pixel_size))
    palette = bytearray()
    for index in range(texture_assets.PALETTE_COLORS):
        red = (index + seed) & 0x1F
        green = (index * 2 + seed) & 0x1F
        blue = (index * 3 + seed) & 0x1F
        value = (red << 11) | (green << 6) | (blue << 1) | (index & 1)
        palette.extend(value.to_bytes(2, "big"))
    return pixels + bytes(palette)


def sample_ci8_payload(
    seed: int = 0,
    width: int = texture_assets.TILED_STORAGE_WIDTH,
    height: int = texture_assets.TILED_STORAGE_HEIGHT,
) -> bytes:
    pixels = bytes(
        (index + seed) & 0xFF
        for index in range(width * height)
    )
    palette = bytearray()
    for index in range(256):
        red = (index + seed) & 0x1F
        green = (index * 2 + seed) & 0x1F
        blue = (index * 3 + seed) & 0x1F
        value = (red << 11) | (green << 6) | (blue << 1) | (index & 1)
        palette.extend(value.to_bytes(2, "big"))
    return pixels + bytes(palette)


class TextureAssetsTests(unittest.TestCase):
    def test_display_list_contract_proves_rectangular_ci4_dimensions(self) -> None:
        commands = b"".join(
            struct.pack(
                ">II", command, argument
            )
            for command, argument in (
                (0xFD500000, 35),
                (0xF3000000, 0x071FF000),
                (0xF5400800, 0x00094260),
                (0xFD100000, 0x00800023),
                (0xF0000000, 0x0603C000),
                (0xDF000000, 0),
            )
        )

        references = texture_assets.scan_direct_texture_references(
            commands, "bank-04/0002", frozenset((35,))
        )

        self.assertEqual(1, len(references))
        self.assertEqual((64, 32), (references[0].width, references[0].height))
        self.assertTrue(references[0].palette_at_payload_end)
        self.assertEqual(512, references[0].load_block_texels)

    def test_consecutive_texture_can_reuse_previous_ci4_tile_dimensions(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xFD500000, 35),
                (0xF3000000, 0x071FF000),
                (0xF5400400, 0x00094260),
                (0xFD100000, 0x00800023),
                (0xF0000000, 0x0603C000),
                (0xFD500000, 61),
                (0xF3000000, 0x071FF000),
                (0xFD100000, 0x0080003D),
                (0xF0000000, 0x0603C000),
                (0xDF000000, 0),
            )
        )

        references = texture_assets.scan_direct_texture_references(
            commands, "bank-04/0024", frozenset((35, 61))
        )

        self.assertEqual(2, len(references))
        self.assertEqual((32, 64), (references[1].width, references[1].height))
        self.assertTrue(references[1].palette_at_payload_end)

    def test_non_ci4_tile_is_not_promoted_by_size_alone(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xFD500000, 35),
                (0xF3000000, 0x073FF000),
                (0xF5480800, 0x00094250),
                (0xFD100000, 0x00400023),
                (0xF0000000, 0x063FC000),
                (0xDF000000, 0),
            )
        )

        reference = texture_assets.scan_direct_texture_references(
            commands, "bank-01/0069", frozenset((35,))
        )[0]

        self.assertIsNone(reference.width)
        self.assertIsNone(reference.height)
        self.assertFalse(reference.palette_at_payload_end)
        self.assertEqual(texture_assets.CI_FORMAT, reference.tile_format)
        self.assertEqual(1, reference.tile_size)
        self.assertEqual(1, reference.palette_reference_mode)
        self.assertEqual(256, reference.palette_entries)

    def test_explicit_ci8_tile_is_not_hidden_by_preceding_ci4_state(self) -> None:
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xF5400800, 0x00094260),
                (0xFD500000, 35),
                (0xF3000000, 0x073FF000),
                (0xF5481000, 0x00094260),
                (0xFD100000, 0x00400023),
                (0xF0000000, 0x063FC000),
                (0xDF000000, 0),
            )
        )

        reference = texture_assets.scan_direct_texture_references(
            commands, "bank-04/0019", frozenset((35,))
        )[0]

        self.assertIsNone(reference.width)
        self.assertEqual(0xF5481000, reference.tile_command)
        self.assertEqual(1, reference.tile_size)

    def test_indirect_preload_groups_require_code_contract_and_split_candidates(
        self,
    ) -> None:
        layout = {"game_vram": 0x15000000, "game_data_vram": 0x80082B20}
        code = bytearray(0xC40)
        for address, word in texture_assets.PRELOAD_CODE_SIGNATURES.items():
            struct.pack_into(">I", code, address - layout["game_vram"], word)
        data = bytearray(0xE000)
        pointers = [0x80089130 + index * 4 for index in range(7)]
        for index, pointer in enumerate(pointers):
            struct.pack_into(
                ">I",
                data,
                texture_assets.PRELOAD_POINTER_TABLE_VRAM
                - layout["game_data_vram"]
                + index * 4,
                pointer,
            )
            struct.pack_into(
                ">I", data, pointer - layout["game_data_vram"], 1000 + index * 400
            )
        struct.pack_into(
            ">I",
            data,
            texture_assets.PRELOAD_POINTER_TABLE_VRAM
            - layout["game_data_vram"]
            + 7 * 4,
            0x15000100,
        )

        groups, candidates = texture_assets.scan_indirect_preload_groups(
            bytes(code),
            bytes(data),
            layout,
            frozenset((1000, 1001, 1359, 1400, 3400)),
            4000,
        )

        self.assertEqual(7, len(groups))
        self.assertEqual(3, groups[0]["candidate_count"])
        self.assertEqual(frozenset((1000, 1001, 1359, 1400, 3400)), candidates)

    def test_indirect_preload_groups_reject_changed_loader_signature(self) -> None:
        layout = {"game_vram": 0x15000000, "game_data_vram": 0x80082B20}
        code = bytes(0xC40)
        data = bytes(0xE000)

        with self.assertRaisesRegex(ValueError, "preload signature"):
            texture_assets.scan_indirect_preload_groups(
                code, data, layout, frozenset(), 4000
            )

    def test_tiled_render_groups_require_renderer_and_ci4_config_contracts(self) -> None:
        layout = {"game_vram": 0x15000000, "game_data_vram": 0x80082B20}
        code = bytearray(0x123000)
        for address, word in texture_assets.TILED_RENDER_CODE_SIGNATURES.items():
            struct.pack_into(">I", code, address - layout["game_vram"], word)
        data = bytearray(0xE000)
        pointers = [0x80089130 + index * 0x14 for index in range(7)]
        for group_index, pointer in enumerate(pointers):
            struct.pack_into(
                ">I",
                data,
                texture_assets.PRELOAD_POINTER_TABLE_VRAM
                - layout["game_data_vram"]
                + group_index * 4,
                pointer,
            )
            for view_index in range(texture_assets.TILED_VIEW_BASE_COUNT):
                struct.pack_into(
                    ">I",
                    data,
                    pointer - layout["game_data_vram"] + view_index * 4,
                    1000 + group_index * 500 + view_index * 100,
                )
        for address, word in texture_assets.TILED_RENDER_DATA_WORDS.items():
            struct.pack_into(">I", data, address - layout["game_data_vram"], word)

        groups, candidates = texture_assets.scan_tiled_render_groups(
            bytes(code),
            bytes(data),
            layout,
            frozenset((1000, 1071, 1100, 1172, 4000, 5747, 5750, 5752)),
            6000,
        )

        self.assertEqual(7, len(groups))
        self.assertEqual(2, groups[0]["views"][0]["ci4_candidate_count"])
        self.assertEqual(1, groups[0]["views"][1]["ci4_candidate_count"])
        self.assertEqual(
            frozenset((1000, 1071, 1100, 4000, 5747, 5750, 5752)),
            candidates,
        )

        struct.pack_into(
            ">I", data, 0x800891F4 - layout["game_data_vram"], 0x08000800
        )
        with self.assertRaisesRegex(ValueError, "tiled-render data"):
            texture_assets.scan_tiled_render_groups(
                bytes(code), bytes(data), layout, frozenset(), 5000
            )

    def test_indexed_png_round_trip_preserves_indices_and_rgba5551_palette(self) -> None:
        payload = sample_payload()

        self.assertEqual(
            payload,
            texture_assets.decode_indexed_png(
                texture_assets.encode_indexed_png(payload)
            ),
        )

    def test_rectangular_indexed_png_round_trips_both_proven_dimensions(self) -> None:
        for width, height in ((32, 64), (64, 32)):
            with self.subTest(width=width, height=height):
                payload = sample_payload(width=width, height=height)
                encoded = texture_assets.encode_indexed_png(
                    payload, width=width, height=height
                )
                self.assertEqual(
                    payload,
                    texture_assets.decode_indexed_png(
                        encoded, width=width, height=height
                    ),
                )

    def test_tiled_ci8_indexed_png_round_trips(self) -> None:
        for width in (
            texture_assets.TILED_STORAGE_WIDTH,
            texture_assets.TILED_EDGE_STORAGE_WIDTH,
        ):
            with self.subTest(width=width):
                payload = sample_ci8_payload(width=width)
                encoded = texture_assets.encode_ci8_png(
                    payload, width=width, height=texture_assets.TILED_STORAGE_HEIGHT
                )
                self.assertEqual(
                    payload,
                    texture_assets.decode_ci8_png(
                        encoded,
                        width=width,
                        height=texture_assets.TILED_STORAGE_HEIGHT,
                    ),
                )

    def test_tiled_preview_applies_continuous_two_entry_phase(self) -> None:
        base = 1000
        textures = {
            index: texture_assets.TextureAsset(
                index,
                0,
                0,
                sample_ci8_payload(seed=index - base + 2),
            )
            for index in range(
                base - texture_assets.TILED_STREAM_PHASE,
                base
                + texture_assets.TILED_ENTRIES_PER_VIEW
                - texture_assets.TILED_STREAM_PHASE,
            )
        }

        rgba, edge_indices = texture_assets.compose_tiled_view(base, textures)

        self.assertEqual([], edge_indices)
        self.assertEqual(
            texture_assets.TILED_VIEW_WIDTH
            * texture_assets.TILED_VIEW_HEIGHT
            * 4,
            len(rgba),
        )
        for destination_row, source_index in ((0, base - 2), (1, base - 1), (2, base)):
            with self.subTest(destination_row=destination_row):
                source_rgba = texture_assets.indexed_payload_rgba(
                    textures[source_index].payload,
                    8,
                )
                destination = (
                    destination_row
                    * texture_assets.TILED_VISIBLE_HEIGHT
                    * texture_assets.TILED_VIEW_WIDTH
                    * 4
                )
                self.assertEqual(
                    source_rgba[: texture_assets.TILED_VISIBLE_WIDTH * 4],
                    rgba[
                        destination : destination
                        + texture_assets.TILED_VISIBLE_WIDTH * 4
                    ],
                )

    def test_tiled_family_pack_round_trips_ci4_ci8_and_edge_tiles(self) -> None:
        ci4 = sample_payload(
            width=texture_assets.TILED_STORAGE_WIDTH,
            height=texture_assets.TILED_STORAGE_HEIGHT,
        )
        ci8 = sample_ci8_payload()
        edge = sample_ci8_payload(width=texture_assets.TILED_EDGE_STORAGE_WIDTH)
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            tile_dir = root / "tiles"
            tile_dir.mkdir()
            (tile_dir / "0001.ci4.png").write_bytes(
                texture_assets.encode_indexed_png(
                    ci4,
                    width=texture_assets.TILED_STORAGE_WIDTH,
                    height=texture_assets.TILED_STORAGE_HEIGHT,
                )
            )
            (tile_dir / "0002.ci8.png").write_bytes(
                texture_assets.encode_ci8_png(ci8)
            )
            (tile_dir / "0003.ci8-edge.png").write_bytes(
                texture_assets.encode_ci8_png(
                    edge,
                    width=texture_assets.TILED_EDGE_STORAGE_WIDTH,
                    height=texture_assets.TILED_STORAGE_HEIGHT,
                )
            )
            records = [
                {
                    "flat_index": 1,
                    "decoded_size": len(ci4),
                    "format": "ci4",
                    "row_layout": texture_assets.ROW_LAYOUT_TMEM,
                    "storage_width": texture_assets.TILED_STORAGE_WIDTH,
                    "storage_height": texture_assets.TILED_STORAGE_HEIGHT,
                    "file": "tiles/0001.ci4.png",
                },
                {
                    "flat_index": 2,
                    "decoded_size": len(ci8),
                    "format": "ci8",
                    "row_layout": texture_assets.ROW_LAYOUT_TMEM,
                    "storage_width": texture_assets.TILED_STORAGE_WIDTH,
                    "storage_height": texture_assets.TILED_STORAGE_HEIGHT,
                    "file": "tiles/0002.ci8.png",
                },
                {
                    "flat_index": 3,
                    "decoded_size": len(edge),
                    "format": "ci8-edge",
                    "row_layout": texture_assets.ROW_LAYOUT_TMEM,
                    "storage_width": texture_assets.TILED_EDGE_STORAGE_WIDTH,
                    "storage_height": texture_assets.TILED_STORAGE_HEIGHT,
                    "file": "tiles/0003.ci8-edge.png",
                },
            ]
            (root / "manifest.json").write_text(
                json.dumps(
                    {
                        "schema_version": 5,
                        "profile": "us",
                        "family": texture_assets.TILED_VIEWS_FAMILY,
                        "source_origin": texture_assets.SOURCE_ORIGIN,
                        "png_origin": texture_assets.PNG_ORIGIN,
                        "tile_count": len(records),
                        "tiles": records,
                    }
                ),
                encoding="utf-8",
            )

            packed = texture_assets.pack_textures(root, root / "packed", False)

            self.assertEqual({1: ci4, 2: ci8, 3: edge}, packed)

    def test_tmem_row_layout_swaps_32_bit_halves_on_odd_rows(self) -> None:
        pixels = bytes(range(256)) * 8

        converted = texture_assets.convert_row_layout(
            pixels, texture_assets.ROW_LAYOUT_TMEM
        )

        self.assertEqual(pixels[:32], converted[:32])
        self.assertEqual(pixels[36:40], converted[32:36])
        self.assertEqual(pixels[32:36], converted[36:40])
        self.assertEqual(
            pixels,
            texture_assets.convert_row_layout(
                converted, texture_assets.ROW_LAYOUT_TMEM
            ),
        )

    def test_vertical_flip_reverses_rows_and_is_its_own_inverse(self) -> None:
        row_size = texture_assets.WIDTH // 2
        pixels = b"".join(
            bytes((row,)) * row_size for row in range(texture_assets.HEIGHT)
        )

        flipped = texture_assets.flip_vertical(pixels)

        self.assertEqual(bytes((63,)) * row_size, flipped[:row_size])
        self.assertEqual(bytes((0,)) * row_size, flipped[-row_size:])
        self.assertEqual(pixels, texture_assets.flip_vertical(flipped))

    def test_known_linear_texture_indices_do_not_swap_rows(self) -> None:
        self.assertEqual(
            texture_assets.ROW_LAYOUT_LINEAR,
            texture_assets.row_layout_for_flat_index(1296),
        )
        self.assertEqual(
            texture_assets.ROW_LAYOUT_LINEAR,
            texture_assets.row_layout_for_flat_index(1297),
        )
        self.assertEqual(
            texture_assets.ROW_LAYOUT_TMEM,
            texture_assets.row_layout_for_flat_index(35),
        )

    def test_extract_and_pack_preserves_sparse_flat_indices(self) -> None:
        textures = [
            texture_assets.TextureAsset(35, 0x2000, 0x2100, sample_payload()),
            texture_assets.TextureAsset(61, 0x2200, 0x2300, sample_payload(1)),
        ]
        normalized = bytes.fromhex("80371240") + bytes(28)
        layout = {"flat_assets_start": 0x1000, "flat_assets_end": 0x3000}

        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "owned.z64"
            source.write_bytes(normalized)
            output = root / "textures"
            with (
                patch.object(texture_assets, "ROOT", root),
                patch.object(
                    texture_assets,
                    "load_profile_textures",
                    return_value=(source, normalized, "z64", layout, textures),
                ),
            ):
                manifest = texture_assets.extract_textures(
                    "us", None, output, False
                )

            self.assertEqual(2, manifest["texture_count"])
            self.assertEqual(3, manifest["schema_version"])
            self.assertEqual("bottom-left", manifest["source_origin"])
            self.assertEqual("top-left", manifest["png_origin"])
            self.assertEqual(
                texture_assets.ROW_LAYOUT_TMEM,
                manifest["textures"][0]["row_layout"],
            )
            self.assertNotIn(temporary_directory, manifest["source_rom"])
            self.assertTrue((output / "textures" / "0035.ci4.png").is_file())
            self.assertFalse((output / "textures" / "0036.ci4.png").exists())

            packed_output = root / "packed"
            packed = texture_assets.pack_textures(output, packed_output, False)
            self.assertEqual(textures[0].payload, packed[35])
            self.assertEqual(textures[1].payload, packed[61])
            self.assertEqual(
                textures[1].payload,
                (packed_output / "flat" / "0061.bin").read_bytes(),
            )

    def test_extract_and_pack_proven_rectangular_textures(self) -> None:
        textures = [
            texture_assets.TextureAsset(
                1282, 0x2000, 0x2100, sample_payload(width=64, height=32)
            ),
            texture_assets.TextureAsset(
                1401, 0x2200, 0x2300, sample_payload(1, width=32, height=64)
            ),
        ]
        contracts = {
            1282: {
                "flat_index": 1282,
                "width": 64,
                "height": 32,
                "references": [{"source": "bank-01/0001", "offset": "0x10"}],
            },
            1401: {
                "flat_index": 1401,
                "width": 32,
                "height": 64,
                "references": [{"source": "bank-01/0002", "offset": "0x20"}],
            },
        }
        normalized = bytes.fromhex("80371240") + bytes(28)
        layout = {"flat_assets_start": 0x1000, "flat_assets_end": 0x3000}
        survey = {
            "candidate_count": 1840,
            "directly_incompatible_texture_count": 12,
            "direct_incompatible_runtime_tiled_overlap_count": 8,
            "indirect_preload_candidate_count": 1573,
            "runtime_tiled_ci4_candidate_count": 1816,
            "runtime_tiled_only_candidate_count": 1806,
            "preload_only_candidate_count": 0,
            "unreferenced_candidate_count": 9,
            "runtime_referenced_candidate_count": 1831,
            "not_standalone_extracted_texture_count": 1827,
            "unresolved_texture_count": 9,
        }

        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "owned.z64"
            source.write_bytes(normalized)
            output = root / "textures"
            with patch.object(
                texture_assets,
                "load_rectangular_textures",
                return_value=(
                    source,
                    normalized,
                    "z64",
                    layout,
                    textures,
                    contracts,
                    survey,
                ),
            ):
                manifest = texture_assets.extract_rectangular_textures(
                    "us", None, output, False
                )

            self.assertEqual(4, manifest["schema_version"])
            self.assertEqual(12, manifest["directly_incompatible_texture_count"])
            self.assertEqual(
                8, manifest["direct_incompatible_runtime_tiled_overlap_count"]
            )
            self.assertEqual(1816, manifest["runtime_tiled_ci4_candidate_count"])
            self.assertEqual(0, manifest["preload_only_candidate_count"])
            self.assertEqual(9, manifest["unreferenced_candidate_count"])
            self.assertEqual(
                texture_assets.RECTANGULAR_FAMILY, manifest["family"]
            )
            self.assertEqual(
                (64, 32),
                tuple(
                    manifest["textures"][0][key] for key in ("width", "height")
                ),
            )
            self.assertEqual(
                (32, 64),
                tuple(
                    manifest["textures"][1][key] for key in ("width", "height")
                ),
            )

            packed_output = root / "packed"
            packed = texture_assets.pack_textures(output, packed_output, False)
            self.assertEqual(textures[0].payload, packed[1282])
            self.assertEqual(textures[1].payload, packed[1401])
            packed_manifest = json.loads(
                (packed_output / "manifest.json").read_text(encoding="utf-8")
            )
            self.assertEqual(4, packed_manifest["schema_version"])
            self.assertEqual(32, packed_manifest["textures"][1]["width"])

    def test_rectangular_pack_rejects_unproven_dimensions(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            texture_dir = root / "textures"
            texture_dir.mkdir()
            (texture_dir / "0001.ci4.png").write_bytes(
                texture_assets.encode_indexed_png(
                    sample_payload(width=64, height=32), width=64, height=32
                )
            )
            (root / "manifest.json").write_text(
                json.dumps(
                    {
                        "schema_version": 4,
                        "profile": "us",
                        "family": texture_assets.RECTANGULAR_FAMILY,
                        "source_origin": texture_assets.SOURCE_ORIGIN,
                        "png_origin": texture_assets.PNG_ORIGIN,
                        "texture_count": 1,
                        "textures": [
                            {
                                "flat_index": 1,
                                "width": 16,
                                "height": 128,
                                "row_layout": texture_assets.ROW_LAYOUT_TMEM,
                                "file": "textures/0001.ci4.png",
                            }
                        ],
                    }
                ),
                encoding="utf-8",
            )

            with self.assertRaisesRegex(ValueError, "unsupported dimensions"):
                texture_assets.pack_textures(root, root / "packed", False)

    def test_pack_rejects_unsafe_manifest_file(self) -> None:
        textures = [texture_assets.TextureAsset(35, 0, 1, sample_payload())]
        normalized = bytes.fromhex("80371240")
        layout = {"flat_assets_start": 0, "flat_assets_end": 1}
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "owned.z64"
            source.write_bytes(normalized)
            output = root / "textures"
            with patch.object(
                texture_assets,
                "load_profile_textures",
                return_value=(source, normalized, "z64", layout, textures),
            ):
                texture_assets.extract_textures("us", None, output, False)
            manifest_path = output / "manifest.json"
            manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
            manifest["textures"][0]["file"] = "../0035.png"
            manifest_path.write_text(json.dumps(manifest), encoding="utf-8")

            with self.assertRaisesRegex(ValueError, "unsafe texture manifest path"):
                texture_assets.pack_textures(output, root / "packed", False)

    def test_png_crc_is_checked(self) -> None:
        encoded = bytearray(texture_assets.encode_indexed_png(sample_payload()))
        encoded[-8] ^= 1

        with self.assertRaisesRegex(ValueError, "CRC"):
            texture_assets.decode_indexed_png(bytes(encoded))


if __name__ == "__main__":
    unittest.main()
