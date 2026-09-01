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
        entry = next(
            entry for entry in functions if entry["symbol"] == "func_15000AC0"
        )
        us_record = entry["regions"]["us"]

        self.assertEqual(entry["overlay"], "game")
        self.assertEqual(us_record["symbol"], "func_15000AC0")
        self.assertEqual(us_record["vram"], "0x15000AC0")
        self.assertEqual(us_record["state"], "matched")
        self.assertEqual(us_record["evidence"]["current_differences"], 0)

    def test_current_summary_is_consistent_with_the_inventory(self) -> None:
        _, functions = project_state.validate_project()
        result = project_state.summary(functions)

        self.assertEqual(result["active_regions"], ["us"])
        self.assertEqual(result["future_regions"], ["eu"])
        self.assertEqual(result["known_functions"], len(functions))
        self.assertEqual(
            result["target_matched"],
            sum(project_state.is_complete(entry) for entry in functions),
        )
        self.assertEqual(
            result["target_matched"] + result["target_remaining"],
            result["known_functions"],
        )
        self.assertEqual(
            sum(values["known_functions"] for values in result["overlays"].values()),
            result["known_functions"],
        )
        for counts in result["regions"].values():
            self.assertEqual(sum(counts.values()), result["known_functions"])

    def test_render_badge_formats_the_selected_region_percentage(self) -> None:
        result = {
            "code_bytes": {
                "regions": {
                    "us": {"percentage": 0.010548},
                    "eu": {"percentage": 12.5},
                }
            }
        }

        us_badge = project_state.render_badge(result, "us")
        eu_badge = project_state.render_badge(result, "eu")
        self.assertEqual(us_badge["label"], "US")
        self.assertEqual(us_badge["message"], "0.0105%")
        self.assertEqual(eu_badge["label"], "EU/PAL")
        self.assertEqual(eu_badge["message"], "12.5%")

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

    def test_deferred_function_requires_a_reason_and_revision(self) -> None:
        entry = {
            "symbol": "func_12345678",
            "deferred": {"reason": "", "recorded_revision": "working-tree"},
            "regions": {
                "us": {
                    "state": "raw_asm",
                    "symbol": "func_12345678",
                    "vram": "0x80000000",
                }
            },
        }
        with self.assertRaisesRegex(project_state.ProjectStateError, "needs a reason"):
            project_state.validate_functions(
                {"schema_version": 1, "functions": [entry]}
            )

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

    def test_next_one_details_prints_bounded_local_context(self) -> None:
        function = {
            "symbol": "func_small",
            "source": "src/game/effects/test.c",
            "overlay": "game",
            "regions": {
                "us": {
                    "state": "raw_asm",
                    "symbol": "func_small",
                    "vram": "0x15000000",
                    "size_bytes": 20,
                }
            },
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "game" / "effects" / "test.c"
            assembly = (
                root
                / "asm"
                / "nonmatchings"
                / "effects"
                / "test"
                / "func_small.s"
            )
            caller = root / "reference" / "game" / "us" / "asm" / "caller.s"
            source.parent.mkdir(parents=True)
            assembly.parent.mkdir(parents=True)
            caller.parent.mkdir(parents=True)
            source.write_text(
                '#include "types.h"\n\n'
                'extern s32 D_test;\n\n'
                '#pragma GLOBAL_ASM("asm/nonmatchings/effects/test/func_small.s")\n',
                encoding="utf-8",
            )
            assembly.write_text("glabel func_small\n    jr $ra\n", encoding="utf-8")
            caller.write_text(
                "    or         $a0, $s0, $zero\n"
                "    addiu      $a1, $zero, 1\n"
                "    or         $a2, $zero, $zero\n"
                "    jal        func_small\n"
                "     nop\n",
                encoding="utf-8",
            )
            output = io.StringIO()
            with (
                patch.object(project_state, "ROOT", root),
                patch.object(
                    project_state,
                    "validate_project",
                    return_value=({}, [function]),
                ),
                patch.object(project_state, "load_json", return_value={}),
                patch.object(project_state, "validate_source_units", return_value=[]),
                redirect_stdout(output),
            ):
                project_state.next_function(SimpleNamespace(one=True, details=True))

        details = output.getvalue()
        self.assertIn("work-item: func_small", details)
        self.assertIn("allowed-edit: src/game/effects/test.c", details)
        self.assertIn("target-file-dirty: unknown", details)
        self.assertIn("source-unit-state: not-reviewed", details)
        self.assertIn("post-match-action: stop", details)
        self.assertIn("issue: none recorded; do not query GitHub", details)
        self.assertIn("finish: ./conker finish func_small", details)
        self.assertIn("raw-us-call-sites:\n  reference/game/us/asm/caller.s:4", details)
        self.assertIn("    jal        func_small", details)
        self.assertIn("assembly-body:\n  glabel func_small", details)
        self.assertIn("source-line: 5", details)
        self.assertIn('extern s32 D_test;', details)

    def test_next_source_unit_guidance_reports_required_integration(self) -> None:
        target = {
            "symbol": "func_target",
            "source": "src/game/test.c",
            "overlay": "game",
            "regions": {"us": {"state": "raw_asm"}},
        }
        other = {
            "symbol": "func_other",
            "source": "src/game/test.c",
            "overlay": "game",
            "regions": {"us": {"state": "raw_asm"}},
        }
        unit = {
            "source": "src/game/test.c",
            "functions": ["func_target", "func_other"],
            "integration": "raw_asm",
        }

        self.assertEqual(
            project_state.next_source_unit_guidance(target, [target, other], [unit]),
            ("raw_asm", "integrate"),
        )

        unit["integration"] = "mixed"
        self.assertEqual(
            project_state.next_source_unit_guidance(target, [target, other], [unit]),
            ("mixed", "stop"),
        )
        other["regions"]["us"]["state"] = "matched"
        self.assertEqual(
            project_state.next_source_unit_guidance(target, [target, other], [unit]),
            ("mixed", "integrate"),
        )

    def test_git_path_dirty_reports_porcelain_state(self) -> None:
        with patch.object(
            project_state.subprocess,
            "run",
            return_value=SimpleNamespace(returncode=0, stdout=" M src/game/test.c\n"),
        ):
            self.assertEqual(project_state.git_path_dirty("src/game/test.c"), "yes")

        with patch.object(
            project_state.subprocess,
            "run",
            return_value=SimpleNamespace(returncode=0, stdout=""),
        ):
            self.assertEqual(project_state.git_path_dirty("src/game/test.c"), "no")

    def test_batch_plan_resolves_matched_overlays(self) -> None:
        functions = [
            {
                "symbol": "func_main",
                "regions": {"us": {"state": "matched"}},
            },
            {
                "symbol": "func_game",
                "overlay": "game",
                "regions": {"us": {"state": "matched"}},
            },
        ]
        output = io.StringIO()
        with (
            patch.object(project_state, "validate_project", return_value=({}, functions)),
            redirect_stdout(output),
        ):
            project_state.batch_plan(["func_game", "func_main"])

        self.assertEqual("main game\n", output.getvalue())

    def test_batch_plan_rejects_unmatched_work_item(self) -> None:
        function = {
            "symbol": "func_test",
            "overlay": "game",
            "regions": {"us": {"state": "raw_asm"}},
        }
        with (
            patch.object(project_state, "validate_project", return_value=({}, [function])),
            self.assertRaisesRegex(
                project_state.ProjectStateError,
                "verify-batch requires matched active work items",
            ),
        ):
            project_state.batch_plan(["func_test"])

    def test_batch_fingerprint_changes_with_source_content(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text("void func_test(void) {}\n", encoding="utf-8")
            with patch.object(project_state, "ROOT", root):
                before = project_state.batch_fingerprint()
                source.write_text("void func_test(void) { return; }\n", encoding="utf-8")
                after = project_state.batch_fingerprint()

        self.assertNotEqual(before, after)

    def test_next_one_id_only_prints_only_the_work_item_identifier(self) -> None:
        function = {
            "symbol": "func_small",
            "source": "src/game/test.c",
            "overlay": "game",
            "regions": {
                "us": {
                    "state": "raw_asm",
                    "symbol": "func_small",
                    "vram": "0x15000000",
                    "size_bytes": 4,
                }
            },
        }
        output = io.StringIO()
        with (
            patch.object(
                project_state,
                "validate_project",
                return_value=({}, [function]),
            ),
            patch.object(project_state, "load_json", return_value={}),
            patch.object(project_state, "validate_source_units", return_value=[]),
            redirect_stdout(output),
        ):
            project_state.next_function(
                SimpleNamespace(one=True, details=False, id_only=True)
            )

        self.assertEqual("func_small\n", output.getvalue())

    def test_next_skips_deferred_work_items(self) -> None:
        functions = []
        for symbol, size in (("func_deferred", 4), ("func_ready", 8)):
            functions.append(
                {
                    "symbol": symbol,
                    "source": "src/game/test.c",
                    "overlay": "game",
                    "regions": {
                        "us": {
                            "state": "raw_asm",
                            "symbol": symbol,
                            "vram": "0x15000000",
                            "size_bytes": size,
                        }
                    },
                }
            )
        functions[0]["deferred"] = {
            "reason": "register allocation",
            "recorded_revision": "working-tree",
            "candidate_preserved": True,
        }
        output = io.StringIO()
        with (
            patch.object(project_state, "validate_project", return_value=({}, functions)),
            patch.object(project_state, "load_json", return_value={}),
            patch.object(project_state, "validate_source_units", return_value=[]),
            redirect_stdout(output),
        ):
            project_state.next_function(
                SimpleNamespace(one=True, details=False, id_only=True)
            )

        self.assertEqual("func_ready\n", output.getvalue())

    def test_defer_preserves_and_resume_restores_the_best_c_candidate(self) -> None:
        entry = {
            "symbol": "func_test",
            "source": "src/game/test.c",
            "regions": {
                "us": {
                    "state": "raw_asm",
                    "symbol": "func_test",
                    "vram": "0x15000000",
                }
            },
        }
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            inventory = root / "progress" / "functions.json"
            inventory.parent.mkdir(parents=True)
            inventory.write_text(
                json.dumps({"schema_version": 1, "functions": [entry]}),
                encoding="utf-8",
            )
            source = root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            original_source = (
                "void func_test(void) {\n"
                "    const char *brace = \"}\";\n"
                "    if (brace[0]) { /* ignored } */\n"
                "        return;\n"
                "    }\n"
                "}\n"
            )
            source.write_text(original_source, encoding="utf-8")
            with (
                patch.object(project_state, "ROOT", root),
                patch.object(project_state, "FUNCTIONS_FILE", inventory),
            ):
                project_state.defer_function(
                    SimpleNamespace(symbol="func_test", reason="register allocation")
                )
                deferred = json.loads(inventory.read_text(encoding="utf-8"))
                deferred_source = source.read_text(encoding="utf-8")
                self.assertEqual(
                    "register allocation",
                    deferred["functions"][0]["deferred"]["reason"],
                )
                self.assertTrue(
                    deferred["functions"][0]["deferred"]["candidate_preserved"]
                )
                self.assertIn(
                    "#if 0 /* CONKER_DEFERRED_CANDIDATE func_test */",
                    deferred_source,
                )
                self.assertIn(original_source.rstrip(), deferred_source)
                self.assertIn(
                    '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")',
                    deferred_source,
                )
                project_state.resume_function(SimpleNamespace(symbol="func_test"))
                resumed = json.loads(inventory.read_text(encoding="utf-8"))
                self.assertEqual(original_source, source.read_text(encoding="utf-8"))

        self.assertNotIn("deferred", resumed["functions"][0])

    def test_defer_rejects_a_function_that_still_uses_global_asm(self) -> None:
        entry = {
            "symbol": "func_test",
            "source": "src/game/test.c",
            "regions": {
                "us": {
                    "state": "raw_asm",
                    "symbol": "func_test",
                    "vram": "0x15000000",
                }
            },
        }
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            inventory = root / "progress" / "functions.json"
            inventory.parent.mkdir(parents=True)
            inventory.write_text(
                json.dumps({"schema_version": 1, "functions": [entry]}),
                encoding="utf-8",
            )
            source = root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n',
                encoding="utf-8",
            )
            with (
                patch.object(project_state, "ROOT", root),
                patch.object(project_state, "FUNCTIONS_FILE", inventory),
                self.assertRaisesRegex(
                    project_state.ProjectStateError, "add the best C candidate"
                ),
            ):
                project_state.defer_function(
                    SimpleNamespace(symbol="func_test", reason="register allocation")
                )

    def test_validation_rejects_deferred_inventory_without_source_candidate(self) -> None:
        function = {
            "symbol": "func_test",
            "source": "src/game/test.c",
            "deferred": {
                "reason": "register allocation",
                "recorded_revision": "working-tree",
                "candidate_preserved": True,
            },
        }
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n',
                encoding="utf-8",
            )
            with (
                patch.object(project_state, "ROOT", root),
                self.assertRaisesRegex(
                    project_state.ProjectStateError,
                    "lacks a preserved deferred candidate",
                ),
            ):
                project_state.validate_deferred_candidate_sources([function])

    def test_next_details_requires_one(self) -> None:
        with self.assertRaisesRegex(project_state.ProjectStateError, "requires --one"):
            project_state.next_function(SimpleNamespace(one=False, details=True))

    def test_next_id_only_requires_one(self) -> None:
        with self.assertRaisesRegex(project_state.ProjectStateError, "requires --one"):
            project_state.next_function(
                SimpleNamespace(one=False, details=False, id_only=True)
            )


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

    def test_mark_matched_removes_the_exact_source_todo(self) -> None:
        project_state.register_game(
            SimpleNamespace(
                identifier="func_game_test",
                source="src/game/reviewed_unit.c",
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
        source_path = self.root / "src/game/reviewed_unit.c"
        source_path.write_text(
            source_path.read_text(encoding="utf-8").replace(
                '#pragma GLOBAL_ASM("asm/nonmatchings/reviewed_unit/func_game_test.s")',
                "void func_game_test(void) {}",
            ),
            encoding="utf-8",
        )

        project_state.mark_matched(
            SimpleNamespace(profile="us", symbol="func_game_test")
        )

        source = source_path.read_text(encoding="utf-8")
        self.assertNotIn(" * - func_game_test\n", source)
        self.assertIn("Unmatched members use generated GLOBAL_ASM", source)

    def test_mark_matched_rejects_unknown_work_item(self) -> None:
        with self.assertRaises(project_state.ProjectStateError):
            project_state.mark_matched(SimpleNamespace(profile="us", symbol="missing"))
