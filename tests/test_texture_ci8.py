from __future__ import annotations

import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import rzip_pack, texture_assets as t, texture_ci8 as ci8


def commands(index=42, width=32, height=64):
    return [
        (0xFD500000, index),
        (0xF5500000, 0x07000000),
        (0xF3000000, 0x07000000 | (width * height // 2 - 1) << 12),
        (0xF5480000 | (width // 8) << 9, 0),
        (0xF2000000, ((width - 1) * 4) << 12 | (height - 1) * 4),
        (0xFD100000, 0x00400000 | index),
        (0xF5600100, 0x06000000),
        (0xE6000000, 0),
        (0xF0000000, 0x063FC000),
        (0xDF000000, 0),
    ]


def scan(words, size=2560, index=42):
    return ci8.scan_contracts(b"".join(struct.pack(">II", *w) for w in words),
                              "fixture", {index: size})


class CI8Tests(unittest.TestCase):
    def test_human_reviewed_eye_geometry_is_explicit(self):
        self.assertEqual(
            (32, 64, t.ROW_LAYOUT_TMEM,
             "manual-review-transposed-preview-geometry",
             "manual-review-preview-geometry"),
            ci8.preview_contract(3091, 64, 32),
        )
        self.assertEqual(
            (64, 32, t.ROW_LAYOUT_TMEM,
             "manual-review-transposed-preview-geometry",
             "manual-review-preview-geometry"),
            ci8.preview_contract(1786, 32, 64),
        )
        for index in (3074, 4574):
            with self.subTest(index=index):
                self.assertEqual(
                    (32, 64, t.ROW_LAYOUT_TMEM,
                     "manual-review-transposed-preview-geometry",
                     "manual-review-preview-geometry"),
                    ci8.preview_contract(index, 64, 32),
                )
        self.assertEqual(
            (16, 128, t.ROW_LAYOUT_TMEM,
             "manual-review-explicit-preview-geometry",
             "manual-review-preview-geometry"),
            ci8.preview_contract(2376, 32, 64),
        )
        self.assertEqual(
            (64, 32, t.ROW_LAYOUT_TMEM, "display-list-render-geometry",
             "runtime-appearance-not-verified"),
            ci8.preview_contract(3090, 64, 32),
        )

    def test_unresolved_previews_are_not_geometry_overrides(self):
        for index in ci8.UNRESOLVED_PREVIEW_INDICES:
            self.assertNotIn(index, ci8.TRANSPOSED_PREVIEW_INDICES)
            self.assertNotIn(index, ci8.CUSTOM_PREVIEW_GEOMETRY)
        self.assertEqual(
            (32, 32, t.ROW_LAYOUT_TMEM,
             "manual-review-no-supported-reversible-transform",
             "manual-review-unresolved"),
            ci8.preview_contract(2795, 32, 32),
        )
        self.assertEqual(
            (32, 64, t.ROW_LAYOUT_TMEM,
             "manual-review-no-supported-reversible-transform",
             "manual-review-unresolved"),
            ci8.preview_contract(3560, 32, 64),
        )

    def test_runtime_incompatible_palette_contract_is_not_extracted(self):
        refs = scan(commands(index=3358, width=32, height=32), size=1536, index=3358)
        self.assertEqual(refs, ci8.consistent_contracts(refs))
        self.assertEqual([], ci8.extractable_contracts(3358, refs))
        self.assertEqual(
            "excluded-runtime-base-palette-overlaps-pixels",
            ci8.RUNTIME_CONSUMER_EVIDENCE[3358]["status"],
        )
        self.assertEqual(0, ci8.RUNTIME_CONSUMER_EVIDENCE[3358]["palette_offset"])

        ordinary = scan(
            commands(index=3357, width=32, height=32), size=1536, index=3357
        )
        self.assertEqual(ordinary, ci8.extractable_contracts(3357, ordinary))

    def test_exact_contract_and_non_power_of_two_bounds(self):
        for width, height in ((32, 64), (64, 32), (16, 16), (40, 40), (48, 42)):
            with self.subTest(width=width, height=height):
                record, = scan(commands(width=width, height=height), width * height + 512)
                self.assertEqual("proven", record["status"])
                self.assertEqual((width, height), (record["width"], record["height"]))

    def test_size_alone_does_not_prove_contract(self):
        self.assertEqual([], scan([(0xFD500000, 42), (0xDF000000, 0)]))
        record, = scan(commands(), 1536)
        self.assertEqual("payload-size-disagrees-with-consumer", record["status"])

    def test_reject_partial_load(self):
        words = commands()
        words[2] = (0xF3000000, 0x071FF000)
        self.assertEqual("partial-or-mismatched-load", scan(words)[0]["status"])

    def test_nonzero_dxt_does_not_use_preswizzled_contract(self):
        words = commands()
        words[2] = (0xF3000000, 0x073FF200)
        self.assertEqual("unsupported-load-row-conversion", scan(words)[0]["status"])

    def test_conflicting_consumers_are_not_promoted(self):
        refs = scan(commands())
        self.assertEqual(refs, ci8.consistent_contracts(refs))
        conflicting = scan(commands(width=64, height=32))
        self.assertEqual([], ci8.consistent_contracts(refs + conflicting))
        mismatch = scan(commands(), 1536)
        self.assertEqual([], ci8.consistent_contracts(refs + mismatch))

    def test_reject_inconsistent_stride(self):
        words = commands()
        words[3] = (0xF5481000, 0)
        self.assertEqual("noncanonical-tile-bounds-or-stride", scan(words)[0]["status"])

    def test_require_own_palette_and_full_tlut(self):
        for position, replacement in ((5, (0xFD100000, 0x0040002B)),
                                      (5, (0xFD100000, 0x0080002A)),
                                      (8, (0xF0000000, 0x0603C000))):
            with self.subTest(position=position, replacement=replacement):
                words = commands()
                words[position] = replacement
                self.assertEqual("incomplete-local-contract", scan(words)[0]["status"])

    def test_do_not_borrow_state_across_display_list_or_image(self):
        for barrier in ((0xDF000000, 0), (0xDE000000, 0), (0xFD500000, 43)):
            words = commands()
            words.insert(4, barrier)
            self.assertEqual("incomplete-local-contract", scan(words)[0]["status"])

    def test_ci4_render_state_is_not_ci8(self):
        words = commands()
        words[3] = (0xF5400800, 0)
        self.assertEqual([], scan(words))

    def test_ci8_pack_and_rzip_override_round_trip(self):
        for width, height in ((32, 64), (40, 40), (48, 42)):
            with self.subTest(width=width, height=height), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                source, output = root / "source", root / "packed"
                source.mkdir()
                payload = bytes(i % 256 for i in range(width * height)) + b"".join(
                    (i * 257).to_bytes(2, "big") for i in range(256))
                (source / "0042.ci8.png").write_bytes(t.encode_ci8_png(
                    payload, t.ROW_LAYOUT_TMEM, width, height))
                manifest = {"schema_version": 6, "family": ci8.FAMILY, "profile": "us",
                            "source_origin": t.SOURCE_ORIGIN, "png_origin": t.PNG_ORIGIN,
                            "texture_count": 1, "textures": [{"flat_index": 42,
                            "width": width, "height": height, "row_layout": t.ROW_LAYOUT_TMEM,
                            "file": "0042.ci8.png"}]}
                (source / "manifest.json").write_text(json.dumps(manifest))
                self.assertEqual({42: payload}, t.pack_textures(source, output, False))
                self.assertEqual({42: payload}, rzip_pack.load_texture_overrides(output))
                with self.assertRaisesRegex(ValueError, "tiled-views"):
                    t.pack_textures(source, root / "bad", False, views=True)

    def test_ci8_pack_accepts_reversible_preview_geometry(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source, output = root / "source", root / "packed"
            source.mkdir()
            payload = bytes(i % 256 for i in range(64 * 32)) + b"".join(
                (i * 257).to_bytes(2, "big") for i in range(256)
            )
            (source / "3091.ci8.png").write_bytes(t.encode_ci8_png(
                payload, t.ROW_LAYOUT_TMEM, 32, 64))
            manifest = {
                "schema_version": 6,
                "family": ci8.FAMILY,
                "profile": "us",
                "source_origin": t.SOURCE_ORIGIN,
                "png_origin": t.PNG_ORIGIN,
                "texture_count": 1,
                "textures": [{
                    "flat_index": 3091,
                    "width": 64,
                    "height": 32,
                    "preview_width": 32,
                    "preview_height": 64,
                    "row_layout": t.ROW_LAYOUT_TMEM,
                    "file": "3091.ci8.png",
                }],
            }
            (source / "manifest.json").write_text(json.dumps(manifest))
            self.assertEqual({3091: payload}, t.pack_textures(source, output, False))


if __name__ == "__main__":
    unittest.main()
