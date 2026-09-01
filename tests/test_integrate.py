from __future__ import annotations

import importlib.util
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock


ROOT = Path(__file__).resolve().parent.parent
SCRIPTS = ROOT / "scripts"
sys.path.insert(0, str(SCRIPTS))
import project_state  # noqa: E402

SPEC = importlib.util.spec_from_file_location("integrate", SCRIPTS / "integrate.py")
assert SPEC is not None and SPEC.loader is not None
integrate = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(integrate)


class IntegrationTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary_directory = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary_directory.name)
        self.original_integrate_root = integrate.ROOT
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
            )
        }
        integrate.ROOT = self.root
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
        self.write_project()

    def tearDown(self) -> None:
        integrate.ROOT = self.original_integrate_root
        for name, value in self.original_paths.items():
            setattr(project_state, name, value)
        self.temporary_directory.cleanup()

    def write_project(self) -> None:
        source = self.root / "src" / "game" / "func_test.c"
        source.parent.mkdir(parents=True)
        source.write_text("void func_test(void) {}\n", encoding="utf-8")
        game_map = self.root / "config" / "game" / "us.yaml"
        game_map.parent.mkdir(parents=True)
        game_map.write_text(
            "    subsegments:\n"
            "      - [0x0, asm]\n"
            "      - [0x10, asm]\n"
            "      - [0x30, asm]\n",
            encoding="utf-8",
        )
        project_state.FUNCTIONS_FILE.parent.mkdir(parents=True)
        project_state.FUNCTIONS_FILE.write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "functions": [
                        {
                            "overlay": "game",
                            "symbol": "func_test",
                            "source": "src/game/func_test.c",
                            "regions": {
                                "us": {
                                    "state": "matched",
                                    "symbol": "func_test",
                                    "vram": "0x15000010",
                                    "evidence": {
                                        "current_differences": 0,
                                        "rom_sha1": "a" * 40,
                                        "verified_revision": "working-tree",
                                    },
                                }
                            },
                        }
                    ],
                }
            )
            + "\n",
            encoding="utf-8",
        )
        project_state.SOURCE_UNITS_FILE.write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "source_units": [
                        {
                            "source": "src/game/func_test.c",
                            "functions": ["func_test"],
                            "integration": "raw_asm",
                            "boundary_evidence": {
                                "us": {
                                    "kind": "structural_analysis",
                                    "reference": "review/test-boundary",
                                    "reviewed": True,
                                }
                            },
                            "regions": {
                                "us": {"state": "candidate", "start": "0x10", "end": "0x20"}
                            },
                        }
                    ],
                }
            )
            + "\n",
            encoding="utf-8",
        )
        project_state.OVERLAYS_FILE.write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "overlays": {
                        overlay: {
                            "code_ranges": {
                                "us": {"start": "0x0", "end": "0x100"},
                                "eu": {"start": "0x0", "end": "0x100"},
                            }
                        }
                        for overlay in project_state.OVERLAYS
                    },
                }
            )
            + "\n",
            encoding="utf-8",
        )

    @mock.patch.object(integrate.subprocess, "run")
    def test_integrates_matched_game_source_after_byte_identical_build(self, run: mock.Mock) -> None:
        def assert_build_sees_finalized_project(*args: object, **kwargs: object) -> None:
            functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
            units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
            self.assertEqual("src/game/done/func_test.c", functions["functions"][0]["source"])
            self.assertEqual("src/game/done/func_test.c", units["source_units"][0]["source"])
            self.assertEqual("c", units["source_units"][0]["integration"])
            self.assertTrue((self.root / "src/game/done/func_test.c").is_file())

        run.side_effect = assert_build_sees_finalized_project
        integrate.integrate("func_test", "us")

        run.assert_called_once_with(
            ["make", "--silent", "--jobs", "4", "game-integrated-refresh"],
            cwd=self.root,
            check=True,
        )
        self.assertFalse((self.root / "src/game/func_test.c").exists())
        self.assertTrue((self.root / "src/game/done/func_test.c").is_file())
        game_map = (self.root / "config/game/us.yaml").read_text(encoding="utf-8")
        self.assertIn("- [0x10, c, game/done/func_test]", game_map)
        self.assertIn("- [0x20, asm]", game_map)
        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        self.assertEqual("src/game/done/func_test.c", functions["functions"][0]["source"])
        self.assertEqual("c", units["source_units"][0]["integration"])
        self.assertEqual("complete", units["source_units"][0]["regions"]["us"]["state"])

    @mock.patch.object(integrate.subprocess, "run")
    def test_failed_build_restores_source_map_and_inventories(self, run: mock.Mock) -> None:
        run.side_effect = subprocess.CalledProcessError(1, ["make", "game-integrated-refresh"])
        original_map = (self.root / "config/game/us.yaml").read_bytes()
        original_functions = project_state.FUNCTIONS_FILE.read_bytes()
        original_units = project_state.SOURCE_UNITS_FILE.read_bytes()

        with self.assertRaises(subprocess.CalledProcessError):
            integrate.integrate("func_test", "us")

        self.assertTrue((self.root / "src/game/func_test.c").is_file())
        self.assertFalse((self.root / "src/game/done/func_test.c").exists())
        self.assertEqual(original_map, (self.root / "config/game/us.yaml").read_bytes())
        self.assertEqual(original_functions, project_state.FUNCTIONS_FILE.read_bytes())
        self.assertEqual(original_units, project_state.SOURCE_UNITS_FILE.read_bytes())

    def test_integration_rejects_source_unit_without_reviewed_boundary_evidence(self) -> None:
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        del units["source_units"][0]["boundary_evidence"]
        project_state.SOURCE_UNITS_FILE.write_text(json.dumps(units) + "\n", encoding="utf-8")

        with self.assertRaisesRegex(
            project_state.ProjectStateError, "lacks reviewed boundary evidence"
        ):
            integrate.integrate("func_test", "us")

    @mock.patch.object(integrate.subprocess, "run")
    def test_integration_maps_incomplete_unit_as_mixed_c_and_asm(self, run: mock.Mock) -> None:
        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        functions["functions"].append(
            {
                "overlay": "game",
                "symbol": "func_unmatched",
                "source": "src/game/func_test.c",
                "regions": {
                    "us": {
                        "state": "raw_asm",
                        "symbol": "func_unmatched",
                        "vram": "0x15000018",
                    }
                },
            }
        )
        project_state.FUNCTIONS_FILE.write_text(json.dumps(functions) + "\n", encoding="utf-8")
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        units["source_units"][0]["functions"].append("func_unmatched")
        project_state.SOURCE_UNITS_FILE.write_text(json.dumps(units) + "\n", encoding="utf-8")
        source = self.root / "src/game/func_test.c"
        source.write_text(
            source.read_text(encoding="utf-8")
            + '#pragma GLOBAL_ASM("asm/nonmatchings/func_test/func_unmatched.s")\n',
            encoding="utf-8",
        )

        integrate.integrate("func_test", "us")

        self.assertTrue(source.is_file())
        self.assertFalse((self.root / "src/game/done/func_test.c").exists())
        game_map = (self.root / "config/game/us.yaml").read_text(encoding="utf-8")
        self.assertIn("- [0x10, c, game/func_test]", game_map)
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        self.assertEqual("mixed", units["source_units"][0]["integration"])
        self.assertEqual("in_progress", units["source_units"][0]["regions"]["us"]["state"])

        with self.assertRaisesRegex(
            project_state.ProjectStateError,
            "mixed source unit is not ready to finalize; unmatched active functions: func_unmatched",
        ):
            integrate.integrate("func_test", "us")


if __name__ == "__main__":
    unittest.main()
