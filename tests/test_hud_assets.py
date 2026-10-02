from __future__ import annotations

import hashlib
import json
import struct
import tempfile
import unittest
import zlib
from types import SimpleNamespace
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
    def test_loader_preserves_empty_ids_and_exact_rom_extents(self) -> None:
        def chunk(payload: bytes) -> bytes:
            compressor = zlib.compressobj(wbits=-15)
            return struct.pack(">I", len(payload)) + compressor.compress(payload) + compressor.flush()

        chunks = [chunk(value) for value in (b"first", b"correct target", b"wrong ordinal")]
        rom_bytes = bytes.fromhex("80371240") + b"".join(chunks)
        sizes = (len(chunks[0]), 0, 0, len(chunks[1]), len(chunks[2]))
        game = SimpleNamespace(code=b"", data=struct.pack(">5H", *sizes))
        layout = {"normalized_sha1": [hashlib.sha1(rom_bytes).hexdigest()],
            "flat_assets_start": 4, "flat_assets_end": len(rom_bytes),
            "game_start": 0, "game_end": 4, "game_vram": 0,
            "game_data_vram": hud_assets.RUNTIME_FLAT_SIZE_TABLE}
        with tempfile.TemporaryDirectory() as directory:
            rom = Path(directory) / "owned.z64"
            rom.write_bytes(rom_bytes)
            with patch.object(hud_assets, "resolve_rom", return_value=(rom, layout)), \
                 patch.object(hud_assets, "parse_game_archive", return_value=game), \
                 patch.object(hud_assets, "validate_code"), \
                 patch.object(hud_assets, "RUNTIME_FLAT_ASSET_COUNT", 5), \
                 patch.dict(hud_assets.RUNTIME_FLAT_IDENTITY, {"empty_runtime_slots": [1, 2]}):
                assets = hud_assets.load_reachable_flat_assets("us", rom,
                    (hud_assets.SpriteMetadata(1, 1, 1, 128, 0, 3),))
                self.assertEqual(set(assets), {3})
                self.assertEqual(assets[3].data, b"correct target")
                self.assertEqual(assets[3].rom_start, 4 + len(chunks[0]))
                self.assertEqual(assets[3].rom_end, 4 + len(chunks[0]) + len(chunks[1]))
                with self.assertRaisesRegex(ValueError, "missing flat indices"):
                    hud_assets.load_reachable_flat_assets("us", rom,
                        (hud_assets.SpriteMetadata(1, 1, 1, 128, 0, 1),))

    def test_changed_loader_table_instruction_is_rejected(self) -> None:
        base = 0x15000000
        code = bytearray(max(hud_assets.GAME_CODE_SIGNATURES) - base + 4)
        for address, word in hud_assets.GAME_CODE_SIGNATURES.items():
            struct.pack_into(">I", code, address - base, word)
        hud_assets.validate_code(bytes(code), base)
        struct.pack_into(">I", code, 0x1510D164 - base, 0)
        with self.assertRaises(ValueError):
            hud_assets.validate_code(bytes(code), base)

    def test_resource_provenance_and_identity_space_are_verified(self) -> None:
        sprite = hud_assets.SpriteMetadata(59, 1, 1, 128, 2, 2224)
        family = hud_assets.HudAssetFamily(b"A", b"", (sprite,))
        asset = hud_assets.FlatHudAsset(2224, 123, 234, bytes([255]) * 1024)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "preview"
            manifest = hud_assets.build_preview(family, {2224: asset}, output, False)
            self.assertEqual(hud_assets.verify_preview(family, {2224: asset}, output), (1, 1))
            self.assertEqual(manifest["resources"][0]["preview_width"], 16)
            self.assertEqual(manifest["resources"][0]["preview_height"], 16)
            path = output / "preview-manifest.json"
            manifest["resources"][0]["rom_start"] = "0xBAD"
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(ValueError, "provenance"):
                hud_assets.verify_preview(family, {2224: asset}, output)
            manifest["resources"][0]["rom_start"] = "0x7B"
            manifest["resource_identity"] = {"index_space": "physical-stream-ordinal"}
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(ValueError, "identity space"):
                hud_assets.verify_preview(family, {2224: asset}, output)

    def test_named_exports_keep_selector_identity_and_animation_suffixes(self) -> None:
        records = [
            {"selector": selector, "reviewed_identity": hud_assets.SELECTOR_REVIEWED_IDENTITIES[selector],
             "preview_files": [f"selectors/{selector:04d}.png"]}
            for selector in (34, 50)
        ]
        paths = [hud_assets.named_exports(record)[0]["file"] for record in records]
        self.assertEqual(paths, ["named/0034-restart-label-bright.png", "named/0050-restart-label-bright.png"])
        animated = {"selector": 26, "reviewed_identity": hud_assets.SELECTOR_REVIEWED_IDENTITIES[26],
                    "preview_files": ["selectors/0026-frame-5.png"]}
        self.assertEqual(hud_assets.named_exports(animated)[0]["file"], "named/0026-analog-stick-animation-frame-5.png")

    def test_named_png_and_identity_corruption_are_rejected(self) -> None:
        sprite = hud_assets.SpriteMetadata(1, 1, 1, 128, 0, 2196)
        family = hud_assets.HudAssetFamily(b"A", b"", (sprite,))
        asset = hud_assets.FlatHudAsset(2196, 0, 4096, bytes([255]) * 4096)
        with tempfile.TemporaryDirectory() as temporary_directory:
            output = Path(temporary_directory) / "preview"
            manifest = hud_assets.build_preview(family, {2196: asset}, output, False)
            self.assertEqual(hud_assets.verify_preview(family, {2196: asset}, output), (1, 1))
            named = output / manifest["selectors"][0]["named_exports"][0]["file"]
            named.write_bytes(b"corrupted")
            with self.assertRaisesRegex(ValueError, "named PNG"):
                hud_assets.verify_preview(family, {2196: asset}, output)

    def test_consistently_corrupted_gallery_metadata_is_rejected(self) -> None:
        sprite = hud_assets.SpriteMetadata(1, 1, 1, 128, 0, 2196)
        family = hud_assets.HudAssetFamily(b"A", b"", (sprite,))
        asset = hud_assets.FlatHudAsset(2196, 123, 234, bytes([255]) * 4096)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "preview"
            original = hud_assets.build_preview(family, {2196: asset}, output, False)
            for field, value in {"flat_asset_index": 9999, "tile_columns": 99,
                    "tile_rows": 99, "scale": 0.1, "flags_raw": 99}.items():
                with self.subTest(field=field):
                    manifest = json.loads(json.dumps(original))
                    manifest["selectors"][0][field] = value
                    (output / "preview-manifest.json").write_text(json.dumps(manifest))
                    (output / "index.html").write_text(hud_assets.preview_html(manifest, family.glyph_map))
                    with self.assertRaisesRegex(ValueError, "preview metadata"):
                        hud_assets.verify_preview(family, {2196: asset}, output)

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
