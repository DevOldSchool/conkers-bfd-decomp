from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import list_integrated_sources


class MappedSourceTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.root_patch = patch.object(list_integrated_sources.project_state, "ROOT", self.root)
        self.root_patch.start()
        self.addCleanup(self.root_patch.stop)
        profiles = self.root / "config/profiles"
        profiles.mkdir(parents=True)
        (profiles / "us.yaml").write_text(
            "segments:\n"
            "  - name: main\n"
            "    subsegments:\n"
            "      - [0x1000, c, main/entry]\n"
            "      - [0x1020, asm, main/raw]\n"
            "      - [0x1040, data, main/data]\n"
            "  - name: debugger\n"
            "    subsegments:\n"
            "      - [0x2000, c, debugger/first]\n"
            "      - {start: 0x2020, type: c, name: debugger/second}\n"
            "      - [0x2040, asm, debugger/tlb]\n"
            "  - [0x3000]\n",
            encoding="utf-8",
        )
        (profiles / "eu.yaml").write_text(
            "segments:\n  - name: main\n    subsegments:\n      - [0x1000, asm]\n",
            encoding="utf-8",
        )

    def test_main_listing_excludes_other_executable_segments(self) -> None:
        self.assertEqual(
            ["src/main/entry.c"],
            list_integrated_sources.mapped_sources("us", overlay="main"),
        )

    def test_explicit_segment_lists_ordered_c_sources_only(self) -> None:
        self.assertEqual(
            ["src/debugger/first.c", "src/debugger/second.c"],
            list_integrated_sources.mapped_sources("us", profile_segment="debugger"),
        )

    def test_future_profile_without_debugger_adds_no_sources(self) -> None:
        self.assertEqual(
            [], list_integrated_sources.mapped_sources("eu", profile_segment="debugger")
        )

    def test_game_keeps_its_separate_map(self) -> None:
        with patch.object(
            list_integrated_sources.project_state, "mapped_subsegments",
            return_value=[(0, "c", "game/done/example"), (16, "asm", None)],
        ) as mapping:
            self.assertEqual(
                ["src/game/done/example.c"],
                list_integrated_sources.mapped_sources("us", overlay="game"),
            )
        mapping.assert_called_once_with("us", "game")


if __name__ == "__main__":
    unittest.main()
