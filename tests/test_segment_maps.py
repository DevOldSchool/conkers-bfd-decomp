from __future__ import annotations

import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SUBSEGMENT_PATTERN = re.compile(r"\s+- \[(0x[0-9A-Fa-f]+),\s*(asm|hasm|c)(?:,\s*([^\]]+))?\]")


def segment_subsegments(path: Path, name: str) -> list[tuple[int, str, str | None]]:
    lines = path.read_text(encoding="utf-8").splitlines()
    segment_start = next(
        index
        for index, line in enumerate(lines)
        if re.match(rf"  - name:\s*{re.escape(name)}\s*$", line)
    )
    subsegments = next(
        index
        for index in range(segment_start + 1, len(lines))
        if lines[index].strip() == "subsegments:"
    )
    result = []
    for line in lines[subsegments + 1 :]:
        if line.startswith("  - ") and not line.startswith("      - "):
            break
        match = SUBSEGMENT_PATTERN.fullmatch(line)
        if match:
            result.append((int(match.group(1), 16), match.group(2), match.group(3)))
    return result


class SegmentMapTests(unittest.TestCase):
    def test_production_source_tree_has_no_fixture_directory(self) -> None:
        self.assertFalse((ROOT / "src" / "fixtures").exists())

    def test_working_maps_preserve_reference_main_boundaries(self) -> None:
        expected_counts = {"us": (165, 165), "eu": (119, 119)}
        for region, (working_count, reference_count) in expected_counts.items():
            working = segment_subsegments(ROOT / "config" / "profiles" / f"{region}.yaml", "main")
            reference = segment_subsegments(ROOT / "config" / "reference" / f"{region}.yaml", "main")
            self.assertEqual(reference_count, len(reference))
            self.assertEqual(working_count, len(working))
            self.assertEqual(0x1050, working[0][0])
            self.assertEqual(sorted({offset for offset, _, _ in working}), [entry[0] for entry in working])
            self.assertEqual(reference, working)

    def test_game_maps_cover_all_reviewed_raw_boundaries(self) -> None:
        expected = {
            "us": (539, 0x0, 0x1F9BF0),
            "eu": (537, 0x0, 0x1FA3E0),
        }
        for region, (count, first, last) in expected.items():
            entries = segment_subsegments(ROOT / "config" / "game" / f"{region}.yaml", "game")
            offsets = [offset for offset, _, _ in entries]
            self.assertEqual(count, len(entries))
            self.assertEqual(first, offsets[0])
            self.assertEqual(last, offsets[-1])
            self.assertEqual(sorted(set(offsets)), offsets)

    def test_existing_named_us_reference_splits_are_preserved(self) -> None:
        entries = segment_subsegments(ROOT / "config" / "game" / "us.yaml", "game")
        names = {offset: name for offset, _, name in entries if name is not None}
        self.assertEqual("game_3BFD0", names[0xEB20])
        self.assertEqual("game_1765E0", names[0x149130])
        self.assertEqual("game/game_1A6300", names[0x178E50])
        self.assertEqual("game/game_1BFC70", names[0x1927C0])


if __name__ == "__main__":
    unittest.main()
