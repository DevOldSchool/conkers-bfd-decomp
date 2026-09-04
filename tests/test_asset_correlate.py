from __future__ import annotations

import unittest

from scripts import asset_correlate


def manifest(profile: str, flat: list[tuple[int, str]], indexed: list[tuple[int, int, str]]):
    return {
        "profile": profile,
        "assets": {
            "flat": {
                "files": [
                    {
                        "index": index,
                        "decoded_size": 4,
                        "decoded_sha1": digest,
                    }
                    for index, digest in flat
                ]
            },
            "banks": [
                {
                    "index": bank,
                    "entries": [
                        {
                            "index": index,
                            "decoded_size": 8,
                            "decoded_sha1": digest,
                        }
                        for entry_bank, index, digest in indexed
                        if entry_bank == bank
                    ],
                }
                for bank in sorted({entry_bank for entry_bank, _, _ in indexed})
            ],
        },
    }


class AssetCorrelateTests(unittest.TestCase):
    def test_tracks_relocated_and_duplicate_assets_explicitly(self) -> None:
        base = manifest(
            "us",
            [(0, "a"), (1, "duplicate"), (2, "duplicate")],
            [(0, 0, "indexed")],
        )
        comparison = manifest(
            "debug",
            [(0, "a"), (5, "duplicate"), (6, "indexed")],
            [(1, 0, "duplicate")],
        )

        result = asset_correlate.correlate_manifests(base, comparison)

        self.assertEqual(3, result["shared_unique_hash_count"])
        self.assertEqual(1, result["exact_locator_match_count"])
        self.assertEqual(2, result["relocated_hash_count"])
        self.assertEqual(1, result["duplicate_shared_hash_count"])
        self.assertEqual(["flat:0000"], result["exact_locators"])

        duplicate = next(
            record
            for record in result["shared_assets"]
            if record["decoded_sha1"] == "duplicate"
        )
        self.assertEqual(2, len(duplicate["us"]))
        self.assertEqual(2, len(duplicate["debug"]))
        self.assertEqual([], duplicate["same_locators"])

    def test_rejects_repeated_profiles(self) -> None:
        with self.assertRaisesRegex(ValueError, "profiles must be unique"):
            asset_correlate.build_report("us", ["us"])


if __name__ == "__main__":
    unittest.main()
