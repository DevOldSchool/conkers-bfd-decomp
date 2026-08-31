from __future__ import annotations

import importlib.util
import io
import json
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location("project_state", ROOT / "scripts" / "project_state.py")
assert SPEC is not None and SPEC.loader is not None
project_state = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(project_state)


class ProjectStateTests(unittest.TestCase):
    def test_current_inventory_includes_the_first_game_work_item(self) -> None:
        _, functions = project_state.validate_project()
        result = project_state.summary(functions)
        self.assertEqual(result["known_functions"], 250)
        self.assertEqual(result["active_regions"], ["us"])
        self.assertEqual(result["future_regions"], ["eu"])
        self.assertEqual(result["target_matched"], 4)
        self.assertEqual(result["complete_source_units"], 0)
        self.assertEqual(result["unassigned_functions"], 0)
        self.assertEqual(result["overlays"]["main"]["target_matched"], 1)
        self.assertEqual(result["overlays"]["game"]["known_functions"], 248)
        self.assertEqual(result["overlays"]["game"]["target_matched"], 3)
        self.assertEqual(result["code_bytes"]["matched_bytes"], 0xD8)
        self.assertEqual(
            result["code_bytes"]["fully_matched_source_unit_bytes"], 0xA8
        )
        self.assertEqual(result["code_bytes"]["total_bytes"], 2_237_392)
        self.assertEqual(result["code_bytes"]["regions"]["us"]["matched_bytes"], 0xD8)
        self.assertEqual(result["code_bytes"]["regions"]["eu"]["matched_bytes"], 0xA8)
        self.assertEqual(result["code_bytes"]["regions"]["eu"]["total_bytes"], 2_240_240)

        us_badge = project_state.render_badge(result, "us")
        eu_badge = project_state.render_badge(result, "eu")
        self.assertEqual(us_badge["label"], "US")
        self.assertEqual(us_badge["message"], "0.0097%")
        self.assertEqual(eu_badge["label"], "EU/PAL")
        self.assertEqual(eu_badge["message"], "0.0075%")

    def test_merged_size_does_not_double_count_overlapping_ranges(self) -> None:
        self.assertEqual(project_state.merged_size([(0x10, 0x20), (0x18, 0x28)]), 0x18)

    def test_code_progress_counts_the_active_us_target(self) -> None:
        functions = [
            {
                "overlay": "game",
                "symbol": "func_test",
                "source": "src/game/func_test.c",
                "regions": {
                    "us": {"state": "matched", "vram": "0x15000010"},
                    "eu": {"state": "candidate", "vram": "0x15000014"},
                },
            }
        ]
        units = [
            {
                "source": "src/game/func_test.c",
                "functions": ["func_test"],
                "regions": {
                    "us": {"start": "0x10", "end": "0x20"},
                    "eu": {"start": "0x14", "end": "0x28"},
                },
            }
        ]
        ranges = {
            "main": {"us": (0, 0x100), "eu": (0, 0x100)},
            "game": {"us": (0, 0x100), "eu": (0, 0x100)},
        }

        result = project_state.code_progress(functions, units, ranges)

        self.assertEqual(result["matched_bytes"], 0x10)
        self.assertEqual(result["fully_matched_source_unit_bytes"], 0x10)
        self.assertEqual(result["regions"]["us"]["matched_bytes"], 0x10)
        self.assertEqual(result["regions"]["eu"]["matched_bytes"], 0)

    def test_code_progress_counts_a_matched_function_in_a_mixed_unit(self) -> None:
        functions = [
            {
                "overlay": "game",
                "symbol": "func_matched",
                "regions": {
                    "us": {"state": "matched", "vram": "0x15000010"},
                },
            },
            {
                "overlay": "game",
                "symbol": "func_asm",
                "regions": {
                    "us": {"state": "raw_asm", "vram": "0x15000020"},
                },
            },
        ]
        units = [
            {
                "source": "src/game/mixed.c",
                "functions": ["func_matched", "func_asm"],
                "regions": {"us": {"start": "0x10", "end": "0x30"}},
            }
        ]
        ranges = {
            "main": {"us": (0, 0x100), "eu": (0, 0x100)},
            "game": {"us": (0, 0x100), "eu": (0, 0x100)},
        }

        result = project_state.code_progress(functions, units, ranges)

        self.assertEqual(result["matched_bytes"], 0x10)
        self.assertEqual(result["fully_matched_source_unit_bytes"], 0)
        self.assertEqual(result["overlays"]["game"]["matched_bytes"], 0x10)

    def test_rejects_unknown_overlay(self) -> None:
        entry = {
            "overlay": "unknown",
            "symbol": "func_12345678",
            "regions": {
                "us": {"state": "raw_asm", "symbol": "func_12345678", "vram": "0x80000000"},
                "eu": {"state": "raw_asm", "symbol": "func_12345678", "vram": "0x80000000"},
            },
        }
        with self.assertRaises(project_state.ProjectStateError):
            project_state.validate_functions({"schema_version": 1, "functions": [entry]})

    def test_match_requires_zero_difference_evidence(self) -> None:
        entry = {
            "symbol": "func_12345678",
            "regions": {
                "us": {"state": "matched", "symbol": "func_12345678", "vram": "0x80000000", "evidence": {"current_differences": 1}},
                "eu": {"state": "raw_asm", "symbol": "func_12345678", "vram": "0x80000000"},
            },
        }
        with self.assertRaises(project_state.ProjectStateError):
            project_state.validate_functions({"schema_version": 1, "functions": [entry]})

    def test_active_match_only_needs_us(self) -> None:
        entry = {
            "symbol": "func_12345678",
            "regions": {
                "us": {"state": "matched", "symbol": "func_12345678", "vram": "0x80000000", "evidence": {"current_differences": 0, "rom_sha1": "a", "verified_revision": "b"}},
                "eu": {"state": "candidate", "symbol": "func_12345678", "vram": "0x80000000"},
            },
        }
        self.assertTrue(project_state.is_complete(entry))

    def test_completed_source_requires_an_exact_c_map_entry(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src" / "game" / "done" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text("void func_test(void) {}\n", encoding="utf-8")
            profile = root / "config" / "profiles" / "us.yaml"
            profile.parent.mkdir(parents=True)
            profile.write_text(
                "      - [0x10, c, game/done/test]\n      - [0x20, asm]\n",
                encoding="utf-8",
            )
            overlays = root / "config" / "overlays.json"
            overlays.write_text(
                json.dumps(
                    {
                        "schema_version": 1,
                        "overlays": {
                            overlay: {
                                "code_ranges": {
                                    region: {"start": "0x0", "end": "0x100"}
                                    for region in project_state.KNOWN_REGIONS
                                }
                            }
                            for overlay in project_state.OVERLAYS
                        },
                    }
                ),
                encoding="utf-8",
            )
            function = {
                "symbol": "func_test",
                "source": "src/game/done/test.c",
                "regions": {"us": {"state": "matched"}},
            }
            unit = {
                "source": "src/game/done/test.c",
                "functions": ["func_test"],
                "integration": "c",
                "boundary_evidence": {
                    "us": {
                        "kind": "object_symbols",
                        "reference": "review/test-object-symbols",
                        "reviewed": True,
                    }
                },
                "regions": {"us": {"state": "complete", "start": "0x10", "end": "0x20"}},
            }
            original_root = project_state.ROOT
            original_overlays = project_state.OVERLAYS_FILE
            try:
                project_state.ROOT = root
                project_state.OVERLAYS_FILE = overlays
                project_state.validate_source_units(
                    {"schema_version": 1, "source_units": [unit]},
                    [function],
                )
                profile.write_text("      - [0x10, asm]\n      - [0x20, asm]\n", encoding="utf-8")
                with self.assertRaises(project_state.ProjectStateError):
                    project_state.validate_source_units(
                        {"schema_version": 1, "source_units": [unit]},
                        [function],
                    )
                unit["regions"]["us"]["end"] = "0x18"
                profile.write_text(
                    "      - [0x10, c, game/done/test]\n      - [0x18, asm]\n",
                    encoding="utf-8",
                )
                with self.assertRaises(project_state.ProjectStateError):
                    project_state.validate_source_units(
                        {"schema_version": 1, "source_units": [unit]},
                        [function],
                    )
            finally:
                project_state.ROOT = original_root
                project_state.OVERLAYS_FILE = original_overlays

    def test_completed_source_requires_reviewed_boundary_evidence(self) -> None:
        function = {
            "symbol": "func_test",
            "source": "src/game/done/test.c",
            "regions": {
                "us": {
                    "state": "matched",
                    "symbol": "func_test",
                    "vram": "0x15000010",
                    "evidence": {
                        "current_differences": 0,
                        "rom_sha1": "a",
                        "verified_revision": "review",
                    },
                }
            },
        }
        unit = {
            "source": "src/game/done/test.c",
            "functions": ["func_test"],
            "integration": "c",
            "regions": {"us": {"state": "complete", "start": "0x10", "end": "0x20"}},
        }

        with self.assertRaisesRegex(project_state.ProjectStateError, "lacks reviewed boundary evidence"):
            project_state.validate_source_units(
                {"schema_version": 1, "source_units": [unit]}, [function]
            )

    def test_next_reports_unmatched_members_of_the_reviewed_game_unit(self) -> None:
        output = io.StringIO()
        with redirect_stdout(output):
            project_state.next_function()
        self.assertIn(
            "func_15000AD0 (src/game/game_2DF70.c; us=func_15000AD0; size=2448 bytes)\n",
            output.getvalue(),
        )

    def test_next_orders_functions_by_size_then_symbol(self) -> None:
        functions = [
            {
                "symbol": "func_large",
                "source": "src/game/test.c",
                "overlay": "game",
                "regions": {
                    "us": {
                        "state": "raw_asm",
                        "symbol": "func_large",
                        "vram": "0x15000000",
                    }
                },
            },
            {
                "symbol": "func_small_b",
                "source": "src/game/test.c",
                "overlay": "game",
                "regions": {
                    "us": {
                        "state": "raw_asm",
                        "symbol": "func_small_b",
                        "vram": "0x15000008",
                    }
                },
            },
            {
                "symbol": "func_small_a",
                "source": "src/game/unassigned.c",
                "overlay": "game",
                "regions": {
                    "us": {
                        "state": "raw_asm",
                        "symbol": "func_small_a",
                        "vram": "0x15000100",
                        "size_bytes": 4,
                    }
                },
            },
        ]
        units = [
            {
                "source": "src/game/test.c",
                "functions": ["func_large", "func_small_b"],
                "regions": {"us": {"start": "0x0", "end": "0xC"}},
            }
        ]
        output = io.StringIO()
        with (
            patch.object(project_state, "validate_project", return_value=({}, functions)),
            patch.object(project_state, "load_json", return_value={}),
            patch.object(project_state, "validate_source_units", return_value=units),
            redirect_stdout(output),
        ):
            project_state.next_function()

        lines = [
            line
            for line in output.getvalue().splitlines()
            if not line.startswith("#")
        ]
        self.assertEqual(
            ["func_small_a", "func_small_b", "func_large"],
            [line.split()[0] for line in lines],
        )
        self.assertIn("./conker m2c <work-item-id>", output.getvalue())
        self.assertIn("size=4 bytes", lines[0])
        self.assertIn("size=4 bytes", lines[1])
        self.assertIn("size=8 bytes", lines[2])


class GameInventoryTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary_directory = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary_directory.name)
        self.original_paths = {
            name: getattr(project_state, name)
            for name in (
                "ROOT",
                "FUNCTIONS_FILE",
                "SOURCE_UNITS_FILE",
                "SUMMARY_FILE",
                "BADGE_FILES",
                "DOCUMENT_FILE",
                "OVERLAYS_FILE",
                "ROMS_FILE",
            )
        }
        project_state.ROOT = self.root
        project_state.FUNCTIONS_FILE = self.root / "progress" / "functions.json"
        project_state.SOURCE_UNITS_FILE = self.root / "progress" / "source_units.json"
        project_state.SUMMARY_FILE = self.root / "progress" / "summary.json"
        project_state.BADGE_FILES = {
            "us": self.root / "progress" / "badge-us.json",
            "eu": self.root / "progress" / "badge-eu.json",
        }
        project_state.DOCUMENT_FILE = self.root / "docs" / "progress.md"
        project_state.OVERLAYS_FILE = self.root / "config" / "overlays.json"
        project_state.ROMS_FILE = self.root / "config" / "roms.json"
        self.write_inventory()
        self.write_assembly("us", "func_15000000", "func_15000004")
        self.write_assembly("eu", "func_15001000", "func_15001004")

    def tearDown(self) -> None:
        for name, value in self.original_paths.items():
            setattr(project_state, name, value)
        self.temporary_directory.cleanup()

    def write_inventory(self) -> None:
        project_state.FUNCTIONS_FILE.parent.mkdir(parents=True, exist_ok=True)
        project_state.FUNCTIONS_FILE.write_text('{"schema_version": 1, "functions": []}\n', encoding="utf-8")
        project_state.SOURCE_UNITS_FILE.write_text('{"schema_version": 1, "source_units": []}\n', encoding="utf-8")
        project_state.OVERLAYS_FILE.parent.mkdir(parents=True, exist_ok=True)
        project_state.OVERLAYS_FILE.write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "overlays": {
                        overlay: {
                            "code_ranges": {
                                region: {"start": "0x0", "end": "0x100"}
                                for region in project_state.KNOWN_REGIONS
                            }
                        }
                        for overlay in project_state.OVERLAYS
                    },
                }
            )
            + "\n",
            encoding="utf-8",
        )
        project_state.ROMS_FILE.write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "profiles": {
                        "us": {
                            "sha1": "a" * 40,
                            "size_bytes": 1,
                            "status": "active",
                        },
                        "eu": {
                            "sha1": "b" * 40,
                            "size_bytes": 1,
                            "status": "future",
                        },
                    },
                }
            )
            + "\n",
            encoding="utf-8",
        )
        game_map = self.root / "config" / "game" / "us.yaml"
        game_map.parent.mkdir(parents=True, exist_ok=True)
        game_map.write_text(
            "    subsegments:\n"
            "      - [0x0, asm]\n"
            "      - [0x10, asm]\n",
            encoding="utf-8",
        )

    def write_assembly(self, region: str, first_symbol: str, second_symbol: str) -> None:
        assembly = self.root / "reference" / "game" / region / "asm" / "sample.s"
        assembly.parent.mkdir(parents=True, exist_ok=True)
        vram = "15000000" if region == "us" else "15001000"
        assembly.write_text(
            "\n".join(
                (
                    f"glabel {first_symbol}",
                    f"    /* 0 {vram} 00000000 */  nop",
                    f"glabel {second_symbol}",
                    f"    /* 4 {int(vram, 16) + 4:08X} 03E00008 */  jr         $ra",
                    f"    /* 8 {int(vram, 16) + 8:08X} 00000000 */   nop",
                    "",
                )
            ),
            encoding="utf-8",
        )

    def test_parses_sorted_game_functions_with_ranges(self) -> None:
        functions = project_state.parse_game_functions("us")
        self.assertEqual(["func_15000000", "func_15000004"], [function.symbol for function in functions])
        self.assertEqual((0, 4), (functions[0].offset, functions[0].end))
        self.assertEqual((4, 12), (functions[1].offset, functions[1].end))

    def test_register_game_registers_function_without_source_unit(self) -> None:
        arguments = SimpleNamespace(
            identifier="func_game_test",
            source="src/game/func_game_test.c",
            us="func_15000000",
        )
        project_state.register_game(arguments)

        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        self.assertEqual("raw_asm", functions["functions"][0]["regions"]["us"]["state"])
        self.assertEqual(4, functions["functions"][0]["regions"]["us"]["size_bytes"])
        self.assertEqual({"us"}, set(functions["functions"][0]["regions"]))
        self.assertEqual([], units["source_units"])
        self.assertTrue(project_state.SUMMARY_FILE.is_file())
        self.assertTrue(project_state.BADGE_FILES["us"].is_file())
        self.assertTrue(project_state.BADGE_FILES["eu"].is_file())
        self.assertIn("Known functions: **1**", project_state.DOCUMENT_FILE.read_text(encoding="utf-8"))

    def test_register_game_rejects_an_existing_region_symbol(self) -> None:
        arguments = SimpleNamespace(
            identifier="func_game_test",
            source="src/game/func_game_test.c",
            us="func_15000000",
        )
        project_state.register_game(arguments)
        duplicate = SimpleNamespace(
            identifier="func_game_duplicate",
            source="src/game/func_game_duplicate.c",
            us="func_15000000",
        )

        with self.assertRaises(project_state.ProjectStateError):
            project_state.register_game(duplicate)

        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        self.assertEqual(1, len(functions["functions"]))

    def test_register_source_unit_requires_every_function_in_reviewed_range(self) -> None:
        project_state.register_game(
            SimpleNamespace(
                identifier="func_game_first",
                source="src/game/reviewed_unit.c",
                us="func_15000000",
            )
        )

        with self.assertRaisesRegex(
            project_state.ProjectStateError, "unregistered functions: func_15000004"
        ):
            project_state.register_source_unit(
                SimpleNamespace(
                    source="src/game/reviewed_unit.c",
                    functions=["func_game_first"],
                    us_start="0x0",
                    us_end="0x10",
                    evidence_kind="object_symbols",
                    evidence_reference="review/object-map.txt",
                )
            )
        self.assertFalse((self.root / "src/game/reviewed_unit.c").exists())

    def test_register_source_unit_records_reviewed_boundary_and_all_members(self) -> None:
        for identifier, symbol in (
            ("func_game_first", "func_15000000"),
            ("func_game_second", "func_15000004"),
        ):
            project_state.register_game(
                SimpleNamespace(
                    identifier=identifier,
                    source="src/game/reviewed_unit.c",
                    us=symbol,
                )
            )

        project_state.register_source_unit(
            SimpleNamespace(
                source="src/game/reviewed_unit.c",
                functions=["func_game_first", "func_game_second"],
                us_start="0x0",
                us_end="0x10",
                evidence_kind="object_symbols",
                evidence_reference="review/object-map.txt",
            )
        )

        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        unit = units["source_units"][0]
        self.assertEqual(["func_game_first", "func_game_second"], unit["functions"])
        self.assertEqual("raw_asm", unit["integration"])
        self.assertEqual("raw_asm", unit["regions"]["us"]["state"])
        self.assertEqual(
            {
                "kind": "object_symbols",
                "reference": "review/object-map.txt",
                "reviewed": True,
            },
            unit["boundary_evidence"]["us"],
        )
        skeleton = self.root / "src/game/reviewed_unit.c"
        self.assertTrue(skeleton.is_file())
        skeleton_content = skeleton.read_text(encoding="utf-8")
        self.assertIn('#include "types.h"', skeleton_content)
        self.assertIn("Boundary evidence: review/object-map.txt", skeleton_content)
        self.assertIn("TODO: Implement these source-unit functions", skeleton_content)
        self.assertIn(" * - func_game_first", skeleton_content)
        self.assertIn(" * - func_game_second", skeleton_content)
        self.assertIn("generated GLOBAL_ASM placeholders", skeleton_content)
        self.assertIn(
            '#pragma GLOBAL_ASM("asm/nonmatchings/reviewed_unit/func_game_first.s")',
            skeleton_content,
        )
        self.assertIn(
            '#pragma GLOBAL_ASM("asm/nonmatchings/reviewed_unit/func_game_second.s")',
            skeleton_content,
        )

    def test_register_source_unit_preserves_existing_source(self) -> None:
        for identifier, symbol in (
            ("func_game_first", "func_15000000"),
            ("func_game_second", "func_15000004"),
        ):
            project_state.register_game(
                SimpleNamespace(
                    identifier=identifier,
                    source="src/game/reviewed_unit.c",
                    us=symbol,
                )
            )
        source = self.root / "src/game/reviewed_unit.c"
        source.parent.mkdir(parents=True)
        source.write_text("void existing_work(void) {}\n", encoding="utf-8")

        project_state.register_source_unit(
            SimpleNamespace(
                source="src/game/reviewed_unit.c",
                functions=["func_game_first", "func_game_second"],
                us_start="0x0",
                us_end="0x10",
                evidence_kind="object_symbols",
                evidence_reference="review/object-map.txt",
            )
        )

        self.assertEqual("void existing_work(void) {}\n", source.read_text(encoding="utf-8"))

    def test_register_source_unit_can_register_all_recovered_members(self) -> None:
        project_state.register_game(
            SimpleNamespace(
                identifier="existing_first",
                source="src/game/old_guess.c",
                us="func_15000000",
            )
        )

        project_state.register_source_unit(
            SimpleNamespace(
                source="src/game/reviewed_unit.c",
                functions=None,
                register_members=True,
                us_start="0x0",
                us_end="0x10",
                evidence_kind="structural_analysis",
                evidence_reference="docs/evidence/reviewed.md",
            )
        )

        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        by_symbol = {entry["symbol"]: entry for entry in functions["functions"]}
        self.assertEqual("src/game/reviewed_unit.c", by_symbol["existing_first"]["source"])
        self.assertEqual("src/game/reviewed_unit.c", by_symbol["func_15000004"]["source"])
        self.assertEqual("raw_asm", by_symbol["func_15000004"]["regions"]["us"]["state"])
        self.assertEqual(8, by_symbol["func_15000004"]["regions"]["us"]["size_bytes"])

        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        self.assertEqual(
            ["existing_first", "func_15000004"],
            units["source_units"][0]["functions"],
        )

    def test_mark_matched_does_not_require_a_source_unit(self) -> None:
        project_state.register_game(
            SimpleNamespace(
                identifier="func_game_test",
                source="src/game/func_game_test.c",
                us="func_15000000",
            )
        )

        project_state.mark_matched(SimpleNamespace(profile="us", symbol="func_game_test"))

        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        region = functions["functions"][0]["regions"]["us"]
        self.assertEqual("matched", region["state"])
        self.assertEqual(0, region["evidence"]["current_differences"])
        self.assertEqual("a" * 40, region["evidence"]["rom_sha1"])
        self.assertEqual("working-tree", region["evidence"]["verified_revision"])
        self.assertEqual([], units["source_units"])
        self.assertIn(
            "Matched for active target: **1**",
            project_state.DOCUMENT_FILE.read_text(encoding="utf-8"),
        )

    def test_mark_matched_rejects_unknown_work_item(self) -> None:
        with self.assertRaises(project_state.ProjectStateError):
            project_state.mark_matched(SimpleNamespace(profile="us", symbol="missing"))
