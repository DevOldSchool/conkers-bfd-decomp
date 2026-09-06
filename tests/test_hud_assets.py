from __future__ import annotations

import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import hud_assets


def sample_family() -> hud_assets.HudAssetFamily:
    glyph_map = (
        b"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        + bytes(range(0x80, 0x80 + hud_assets.GLYPH_MAP_SIZE - 36))
    )
    records = [
        struct.pack(">BBBBI", 1, 1, 0x80, 0, 0x894)
        for _ in range(hud_assets.SPRITE_RECORD_COUNT)
    ]
    records[hud_assets.ANIMATED_SELECTOR - 1] = struct.pack(
        ">BBBBI", 2, 1, 0x80, 1, 0x7E7
    )
    table = b"".join(records)
    return hud_assets.HudAssetFamily(
        glyph_map=glyph_map,
        sprite_table=table,
        sprites=hud_assets.parse_sprite_table(table),
    )


class HudAssetsTests(unittest.TestCase):
    def test_glyph_lookup_matches_ascii_folding_and_space_case(self) -> None:
        glyph_map = sample_family().glyph_map
        self.assertEqual(10, hud_assets.glyph_index_for_byte(ord("A"), glyph_map))
        self.assertEqual(10, hud_assets.glyph_index_for_byte(ord("a"), glyph_map))
        self.assertEqual(
            hud_assets.SPACE_GLYPH_INDEX,
            hud_assets.glyph_index_for_byte(ord(" "), glyph_map),
        )
        self.assertIsNone(hud_assets.glyph_index_for_byte(0, glyph_map))

    def test_sprite_records_preserve_selector_fields_and_animation(self) -> None:
        family = sample_family()
        animated = hud_assets.sprite_records(family.sprites)[
            hud_assets.ANIMATED_SELECTOR - 1
        ]
        self.assertEqual(2, animated["tile_columns"])
        self.assertEqual(1.0, animated["scale"])
        self.assertEqual(0x7E7, animated["flat_asset_index"])
        self.assertEqual(
            list(range(0x7E7, 0x7ED)),
            animated["runtime_animation"]["flat_asset_indices"],
        )

    def test_sprite_parser_rejects_unknown_flag_bits(self) -> None:
        table = bytearray(sample_family().sprite_table)
        table[3] = 4
        with self.assertRaisesRegex(ValueError, "unknown flag bits"):
            hud_assets.parse_sprite_table(bytes(table))

    def test_reachable_indices_include_tiles_and_animation_frames(self) -> None:
        sprites = (
            hud_assets.SpriteMetadata(1, 3, 1, 0x80, 0, 100),
            hud_assets.SpriteMetadata(
                hud_assets.ANIMATED_SELECTOR, 1, 1, 0x80, 0, 200
            ),
        )
        self.assertEqual(
            (100, 101, 102, 200, 201, 202, 203, 204, 205),
            hud_assets.reachable_flat_indices(sprites),
        )

    def test_compose_rgba_tiles_uses_column_major_selector_order(self) -> None:
        red = bytes((255, 0, 0, 255)) * (32 * 32)
        blue = bytes((0, 0, 255, 255)) * (32 * 32)
        width, height, pixels = hud_assets.compose_rgba_tiles(
            [red, blue], columns=2, rows=1
        )
        self.assertEqual((64, 32), (width, height))
        self.assertEqual(bytes((255, 0, 0, 255)), pixels[:4])
        self.assertEqual(bytes((0, 0, 255, 255)), pixels[32 * 4 : 32 * 4 + 4])

    def test_preview_decodes_row_complete_short_resources_without_padding(self) -> None:
        sprite = hud_assets.SpriteMetadata(1, 2, 1, 0x80, 0, 100)
        table = struct.pack(">BBBBI", 2, 1, 0x80, 0, 100)
        family = hud_assets.HudAssetFamily(
            glyph_map=sample_family().glyph_map,
            sprite_table=table,
            sprites=(sprite,),
        )
        assets = {
            100: hud_assets.FlatHudAsset(100, 0x1000, 0x1100, bytes(4096)),
            101: hud_assets.FlatHudAsset(101, 0x1100, 0x1200, bytes(2048)),
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            output = Path(temporary_directory) / "preview"
            manifest = hud_assets.build_preview(family, assets, output, False)
            verified = hud_assets.verify_preview(family, assets, output)

            self.assertEqual(2, manifest["resource_count"])
            self.assertEqual(2, manifest["previewable_resource_count"])
            self.assertEqual(1, manifest["previewable_selector_count"])
            self.assertEqual((2, 1), verified)
            self.assertTrue((output / "resources" / "0101.bin").is_file())
            self.assertTrue((output / "selectors" / "0001.png").is_file())
            short = manifest["resources"][1]
            self.assertEqual(16, short["preview_height"])
            self.assertEqual(0, short["trailing_raw_bytes"])

    def test_rgba32_preview_keeps_source_rows_top_to_bottom(self) -> None:
        top = bytes((255, 0, 0, 255)) * 4
        bottom = bytes((0, 0, 255, 255)) * 4
        linear = top + bottom
        stored = bytearray(linear)
        stored[16:32] = stored[24:32] + stored[16:24]

        height, pixels, used = hud_assets.rgba32_preview_pixels(
            bytes(stored), width=4, height=2
        )

        self.assertEqual(2, height)
        self.assertEqual(32, used)
        self.assertEqual(linear, pixels)

    def test_flag_bit_one_selects_the_16x16_render_window(self) -> None:
        sprite = hud_assets.SpriteMetadata(1, 1, 1, 0x80, 2, 100)
        self.assertEqual((16, 16), hud_assets.selector_tile_dimensions(sprite))
        height, pixels, used = hud_assets.rgba32_preview_pixels(
            bytes(1440), width=16, height=16
        )
        self.assertEqual(16, height)
        self.assertEqual(1024, used)
        self.assertEqual(1024, len(pixels))

    def test_rgba16_candidate_undoes_odd_row_word_swap(self) -> None:
        red = struct.pack(">H", 0xF801) * 4
        blue = struct.pack(">H", 0x003F) * 4
        stored = red + blue[4:8] + blue[:4]

        height, pixels, used = hud_assets.rgba16_preview_pixels(
            stored, width=4, height=2
        )

        self.assertEqual(2, height)
        self.assertEqual(16, used)
        self.assertEqual(bytes((255, 0, 0, 255)) * 4, pixels[:16])
        self.assertEqual(bytes((0, 0, 255, 255)) * 4, pixels[16:])

    def test_reviewed_resource_preview_contracts_are_explicit(self) -> None:
        linear = hud_assets.resource_preview_image(
            2202, bytes((1, 2, 3, 4)) * (32 * 8), 32, 32
        )
        i8_linear = bytes(range(64)) * 64
        i8_stored = hud_assets.texture_native.convert_row_layout(
            i8_linear,
            hud_assets.texture_base.ROW_LAYOUT_TMEM,
            "i8",
            64,
            64,
        )
        i8 = hud_assets.resource_preview_image(2139, i8_stored, 64, 64)
        label_linear = bytes(range(64)) * 32
        label_stored = hud_assets.texture_native.convert_row_layout(
            label_linear,
            hud_assets.texture_base.ROW_LAYOUT_TMEM,
            "i8",
            64,
            32,
        )
        label = hud_assets.resource_preview_image(2198, label_stored, 64, 32)
        question_linear = bytes(range(32)) * 32
        question_stored = hud_assets.texture_native.convert_row_layout(
            question_linear,
            hud_assets.texture_base.ROW_LAYOUT_TMEM,
            "i8",
            32,
            32,
        )
        question = hud_assets.resource_preview_image(
            2199, question_stored, 32, 32
        )
        zero = hud_assets.resource_preview_image(2224, bytes(4096), 32, 32)

        self.assertIsNotNone(linear)
        self.assertEqual(hud_assets.texture_base.ROW_LAYOUT_LINEAR, linear.row_layout)
        self.assertEqual("reviewed-linear-rgba32-short-preview", linear.status)
        self.assertIsNotNone(i8)
        self.assertEqual("i8", i8.texture_format)
        self.assertEqual(hud_assets.texture_base.ROW_LAYOUT_TMEM, i8.row_layout)
        self.assertEqual("reviewed-i8-tmem-preview", i8.status)
        self.assertEqual(
            hud_assets.texture_native.payload_to_rgba(i8_linear, "i8"), i8.pixels
        )
        self.assertEqual("i8", label.texture_format)
        self.assertEqual(
            hud_assets.texture_native.payload_to_rgba(label_linear, "i8"),
            label.pixels,
        )
        self.assertEqual("i8", question.texture_format)
        self.assertEqual(
            hud_assets.texture_native.payload_to_rgba(question_linear, "i8"),
            question.pixels,
        )
        self.assertEqual("rgba32", zero.texture_format)
        self.assertEqual("reviewed-rgba32-32x32-source-preview", zero.status)
        self.assertIsNone(
            hud_assets.resource_preview_image(2041, bytes(3072), 32, 32)
        )

    def test_reference_sheet_identities_use_reviewed_source_dimensions(self) -> None:
        sprites = (
            hud_assets.SpriteMetadata(3, 1, 1, 0x80, 0, 2198),
            hud_assets.SpriteMetadata(4, 1, 1, 0x80, 0, 2199),
            hud_assets.SpriteMetadata(5, 1, 1, 0x80, 0, 2171),
            hud_assets.SpriteMetadata(8, 1, 1, 0x80, 0, 2215),
            hud_assets.SpriteMetadata(52, 1, 1, 0x80, 0, 2172),
            hud_assets.SpriteMetadata(59, 1, 1, 0x80, 2, 2224),
        )

        self.assertEqual(
            {
                2198: (64, 32),
                2199: (32, 32),
                2171: (64, 32),
                2215: (64, 32),
                2172: (64, 32),
                2224: (32, 32),
            },
            hud_assets.resource_preview_dimensions(sprites),
        )
        self.assertEqual(
            {
                2198: (32, 32),
                2199: (32, 32),
                2171: (32, 32),
                2215: (32, 32),
                2172: (32, 32),
                2224: (16, 16),
            },
            hud_assets.resource_render_dimensions(sprites),
        )
        self.assertEqual(
            "poops-label", hud_assets.SELECTOR_REVIEWED_IDENTITIES[3]["name"]
        )
        self.assertEqual(
            "question-mark-icon", hud_assets.SELECTOR_REVIEWED_IDENTITIES[4]["name"]
        )
        self.assertEqual(
            "dang-label", hud_assets.SELECTOR_REVIEWED_IDENTITIES[5]["name"]
        )
        self.assertEqual(
            "total-label", hud_assets.SELECTOR_REVIEWED_IDENTITIES[8]["name"]
        )
        self.assertEqual(
            "dino-label", hud_assets.SELECTOR_REVIEWED_IDENTITIES[52]["name"]
        )
        self.assertEqual(
            "green-zero-digit",
            hud_assets.SELECTOR_REVIEWED_IDENTITIES[59]["name"],
        )

    def test_shared_source_selectors_render_at_their_recorded_scales(self) -> None:
        selectors = []
        for selector, scale in ((76, 1.0), (89, 85 / 128)):
            selectors.append(
                {
                    "selector": selector,
                    "flat_asset_index": 2147,
                    "tile_columns": 2,
                    "tile_rows": 1,
                    "scale": scale,
                    "flags_raw": 0,
                    "preview_files": [f"selectors/{selector:04d}.png"],
                    "preview_modes": ["previewable-render-window"],
                    "preview_note": None,
                    "reviewed_identity": None,
                    "reviewed_variants": None,
                }
            )
        rendered = hud_assets.preview_html(
            {
                "selectors": selectors,
                "previewable_selector_count": 2,
                "selector_count": 2,
            },
            b"",
        )

        self.assertIn('style="height:64px" src="selectors/0076.png"', rendered)
        self.assertIn('style="height:42px" src="selectors/0089.png"', rendered)

    def test_selector_61_has_reviewed_c_button_identity_and_order(self) -> None:
        identity = hud_assets.SELECTOR_REVIEWED_IDENTITIES[61]
        variants = hud_assets.SELECTOR_REVIEWED_VARIANTS[61]

        self.assertEqual("n64-c-buttons-direction-row", identity["name"])
        self.assertEqual(
            ["C-left", "C-up", "C-right", "C-down"], identity["elements"]
        )
        self.assertEqual("user-supplied visual reference", identity["evidence"])
        self.assertEqual(
            ["left", "up", "right", "down"],
            [variant["name"] for variant in variants],
        )
        self.assertEqual(
            [2222, 2222, 2223, 2222], [v["flat_index"] for v in variants]
        )
        self.assertEqual(
            [0, 1, 0, 3], [v["clockwise_quarter_turns"] for v in variants]
        )

    def test_selector_61_uses_16x16_tmem_sources_and_reviewed_rotations(self) -> None:
        sprite = hud_assets.SpriteMetadata(61, 1, 1, 0x80, 0, 2222)
        left = bytearray(16 * 16 * 4)
        left[0:4] = bytes((255, 0, 0, 255))
        left[-4:] = bytes((0, 255, 0, 255))
        right = bytes((0, 0, 255, 255)) * (16 * 16)
        previews = {2222: (16, 16, bytes(left)), 2223: (16, 16, right)}

        outputs = hud_assets.selector_preview_outputs(sprite, previews)

        self.assertEqual(
            ["-left", "-up", "-right", "-down"], [x[0] for x in outputs]
        )
        self.assertEqual((255, 0, 0, 255), tuple(outputs[1][4][15 * 4 : 16 * 4]))
        self.assertEqual((255, 0, 0, 255), tuple(outputs[3][4][-16 * 4 : -15 * 4]))
        self.assertEqual(right, outputs[2][4])
        self.assertEqual(
            {2222: (16, 16), 2223: (16, 16)},
            hud_assets.resource_preview_dimensions((sprite,)),
        )
        self.assertEqual(
            {2222: (32, 32)}, hud_assets.resource_render_dimensions((sprite,))
        )

    def test_selector_87_has_reviewed_nintendo_identity_and_two_tile_order(self) -> None:
        identity = hud_assets.SELECTOR_REVIEWED_IDENTITIES[87]
        composition = hud_assets.SELECTOR_REVIEWED_COMPOSITIONS[87]
        sprite = hud_assets.SpriteMetadata(87, 2, 1, 0x80, 0, 2139)

        self.assertEqual("nintendo-wordmark", identity["name"])
        self.assertEqual("Nintendo wordmark", identity["display_name"])
        self.assertEqual(["Nintendo"], identity["elements"])
        self.assertEqual([[2139, 2140]], hud_assets.selector_frame_indices(sprite))
        self.assertEqual(
            [2139, 2140, 2141], composition["flat_indices"]
        )
        self.assertEqual(3, composition["tile_columns"])
        self.assertEqual(
            {2139: (64, 64), 2140: (64, 64), 2141: (64, 64)},
            hud_assets.resource_preview_dimensions((sprite,)),
        )
        preview = hud_assets.resource_preview_image(
            2139, bytes(64 * 64), 64, 64
        )
        self.assertEqual(
            hud_assets.texture_base.ROW_LAYOUT_TMEM,
            preview.row_layout,
        )
        self.assertEqual("i8", preview.texture_format)

        outputs = hud_assets.selector_preview_outputs(
            sprite,
            {
                flat_index: (64, 64, bytes((flat_index - 2138,)) * 64 * 64 * 4)
                for flat_index in composition["flat_indices"]
            },
        )
        self.assertEqual(1, len(outputs))
        self.assertEqual((2139, 2140, 2141), outputs[0][1])
        self.assertEqual((192, 64), outputs[0][2:4])

    def test_extract_and_verify_round_trip(self) -> None:
        family = sample_family()
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            rom = root / "owned.z64"
            rom.write_bytes(bytes.fromhex("80371240"))
            output = root / "interface"
            loaded = (rom, "z64", "digest", family)
            with patch.object(hud_assets, "load_profile_hud_assets", return_value=loaded):
                manifest = hud_assets.extract("us", None, output, False)
                counts = hud_assets.verify_extraction("us", None, output)

            self.assertEqual((hud_assets.GLYPH_MAP_SIZE, 92), counts)
            self.assertEqual(
                family.glyph_map, (output / "glyph-map.bin").read_bytes()
            )
            self.assertEqual(
                family.sprite_table, (output / "sprite-metadata.bin").read_bytes()
            )
            parsed = json.loads((output / "manifest.json").read_text())
            self.assertEqual(manifest, parsed)
            self.assertEqual(0x5C, parsed["runtime_layout_record"]["size"])


if __name__ == "__main__":
    unittest.main()
