from __future__ import annotations

import struct
import unittest
from dataclasses import replace

from scripts import beta_index
from scripts.rzip_extract import load_layout


def function(index: int, fingerprint: str) -> beta_index.FunctionRecord:
    offset = index * 0x10
    return beta_index.FunctionRecord(
        offset=offset,
        address=0x15000000 + offset,
        symbol=f"func_{index}",
        length=0x10,
        fingerprint=fingerprint,
    )


class BetaIndexTests(unittest.TestCase):
    def test_marks_unique_ordered_sequence_as_strong(self) -> None:
        active = [function(0, "A"), function(1, "B"), function(2, "C")]
        evidence = [function(10, "X"), function(11, "B"), function(12, "C")]

        mappings, summary = beta_index.align_functions(active, evidence)

        self.assertEqual(2, summary["strong"])
        self.assertEqual(["func_1", "func_2"], [mapping["us_symbol"] for mapping in mappings])
        self.assertTrue(all(mapping["confidence"] == "strong" for mapping in mappings))

    def test_keeps_repeated_fingerprint_candidate_only(self) -> None:
        active = [function(0, "A"), function(1, "A")]
        evidence = [function(10, "A"), function(11, "A")]

        mappings, summary = beta_index.align_functions(active, evidence)

        self.assertEqual(0, summary["strong"])
        self.assertEqual([], mappings)
        self.assertEqual(0, summary["candidate"])
        self.assertEqual(1, summary["ambiguous_fingerprints"])

    def test_keeps_isolated_unique_fingerprint_candidate_only(self) -> None:
        active = [function(0, "A")]
        evidence = [function(10, "A")]

        mappings, summary = beta_index.align_functions(active, evidence)

        self.assertEqual(0, summary["strong"])
        self.assertEqual("candidate", mappings[0]["confidence"])

    def test_candidate_mappings_remain_one_to_one(self) -> None:
        active = [function(0, "A"), function(1, "B"), function(2, "C")]
        evidence = [
            function(10, "A"),
            function(11, "B"),
            function(12, "B"),
            function(13, "C"),
        ]

        mappings, summary = beta_index.align_functions(active, evidence)

        self.assertEqual(3, summary["ordered_exact"])
        self.assertEqual(len(mappings), len({mapping["us_symbol"] for mapping in mappings}))
        self.assertEqual(
            len(mappings), len({mapping["evidence_symbol"] for mapping in mappings})
        )

    def test_function_index_identity_includes_vram_and_pinned_toolchain(self) -> None:
        image = beta_index.GameImage(
            profile="test",
            rom_path=beta_index.ROOT / "roms" / "test.z64",
            normalized_rom=b"rom",
            normalized_sha1="rom-sha1",
            code=b"code",
            data=b"data",
            code_vram=0x15000000,
            data_vram=0x80000000,
        )

        identity = beta_index.function_index_identity(image, "code-sha1")
        moved_identity = beta_index.function_index_identity(
            replace(image, code_vram=image.code_vram + 0x10), "code-sha1"
        )

        self.assertNotEqual(identity, moved_identity)
        self.assertEqual("0x15000000", identity["code_vram"])
        self.assertEqual("1.33.0", identity["spimdisasm"]["version"])
        self.assertIn("--compiler", identity["options"])

    def test_ects_data_vram_matches_reviewed_runtime_addresses(self) -> None:
        self.assertEqual(0x80068F80, load_layout("ects")["game_data_vram"])

    def test_finds_lui_addiu_address_reference(self) -> None:
        address = 0x80012345
        code = struct.pack(">II", 0x3C088001, 0x25042345)

        self.assertEqual([0], beta_index.code_references(code, address))

    def test_source_lead_requires_strong_mapping(self) -> None:
        paths = [
            {
                "path": "../Effects/Test/test.c",
                "function_anchors": [{"symbol": "func_beta"}],
            }
        ]
        mappings = [
            {
                "evidence_symbol": "func_beta",
                "us_symbol": "func_us",
                "confidence": "strong",
            }
        ]

        leads = beta_index.source_leads(paths, mappings)

        self.assertEqual("func_us", leads[0]["us_function_candidates"][0]["us_symbol"])
        self.assertEqual("unreviewed", leads[0]["boundary_status"])

    def test_source_lead_deduplicates_repeated_filename_references(self) -> None:
        paths = [
            {
                "path": "../Effects/Test/test.c",
                "function_anchors": [{"symbol": "func_beta"}, {"symbol": "func_beta"}],
            }
        ]
        mappings = [
            {
                "evidence_symbol": "func_beta",
                "us_symbol": "func_us",
                "confidence": "strong",
            }
        ]

        leads = beta_index.source_leads(paths, mappings)

        self.assertEqual(1, len(leads[0]["us_function_candidates"]))


if __name__ == "__main__":
    unittest.main()
