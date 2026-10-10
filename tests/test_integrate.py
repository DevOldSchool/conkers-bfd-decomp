from __future__ import annotations

import os

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
    def test_raw_debugger_integration_preserves_existing_data_endpoint(self) -> None:
        path = self.root / "config/profiles/us.yaml"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("    subsegments:\n      - [0x58, asm, debugger/test]\n"
                        "      - [0x68, data, debugger/data]\n")
        integrate.replace_map_range(path, 0x58, 0x68, "debugger/test")
        self.assertEqual("    subsegments:\n      - [0x58, c, debugger/test]\n"
                         "      - [0x68, data, debugger/data]\n", path.read_text())

    def setUp(self) -> None:
        jobs = mock.patch.dict(os.environ, CONKER_JOBS="4")
        jobs.start()
        self.addCleanup(jobs.stop)
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
                "DOCUMENT_FILE",
                "OVERLAYS_FILE",
            )
        }
        integrate.ROOT = self.root
        project_state.ROOT = self.root
        project_state.FUNCTIONS_FILE = self.root / "progress" / "functions.json"
        project_state.SOURCE_UNITS_FILE = self.root / "progress" / "source_units.json"
        project_state.SUMMARY_FILE = self.root / "build" / "progress" / "summary.json"
        project_state.DOCUMENT_FILE = self.root / "build" / "progress" / "progress.md"
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

    def add_profile_unit(self, overlay: str, symbol: str, start: int, *,
                         mixed: bool = False, incomplete: bool = False) -> str:
        """Add a reviewed synthetic unit without claiming any retail boundary."""
        source = f"src/{overlay}/system/{symbol}.c"
        path = self.root / source
        path.parent.mkdir(parents=True, exist_ok=True)
        functions = project_state.load_json(project_state.FUNCTIONS_FILE)
        units = project_state.load_json(project_state.SOURCE_UNITS_FILE)
        function = json.loads(json.dumps(functions["functions"][0]))
        function.update(source=source, overlay=overlay, symbol=symbol)
        base = 0x16000000 if overlay == "debugger" else 0x80000000
        function["regions"]["us"].update(symbol=symbol, vram=f"0x{base + start:X}")
        functions["functions"].append(function)
        unit = json.loads(json.dumps(units["source_units"][0]))
        unit.update(source=source, functions=[symbol], integration="mixed" if mixed else "raw_asm")
        unit["regions"]["us"].update(start=f"0x{start:X}", end=f"0x{start + 16:X}")
        content = f"void {symbol}(void) {{}}\n"
        if incomplete:
            other = json.loads(json.dumps(function))
            other_symbol = symbol + "_raw"
            other["symbol"] = other_symbol
            other["regions"]["us"] = {
                "symbol": other_symbol, "state": "raw_asm", "vram": f"0x{base + start + 8:X}"
            }
            functions["functions"].append(other)
            unit["functions"].append(other_symbol)
            unit["regions"]["us"]["state"] = "in_progress"
            content += project_state.global_asm_pragma(source, other_symbol) + "\n"
        units["source_units"].append(unit)
        path.write_text(content)
        profile = self.root / "config/profiles/us.yaml"
        profile.parent.mkdir(parents=True, exist_ok=True)
        existing = profile.read_text() if profile.exists() else "segments:\n"
        entry = f"c, {source.removeprefix('src/').removesuffix('.c')}" if mixed else "asm"
        profile.write_text(existing + f"  - name: {overlay}\n    type: code\n    subsegments:\n"
                           f"      - [0x{start:X}, {entry}]\n      - [0x{start + 16:X}, asm]\n")
        project_state.write_json(project_state.FUNCTIONS_FILE, functions)
        project_state.write_json(project_state.SOURCE_UNITS_FILE, units)
        return source

    @mock.patch.object(integrate.subprocess, "run")
    def test_build_overlays_respects_jobs(self, run):
        with mock.patch.dict(os.environ, CONKER_JOBS="1"):
            integrate.build_overlays({"main", "game"}, "us")
        self.assertEqual([call.args[0][3] for call in run.call_args_list], ["1", "1"])
        run.reset_mock()
        with mock.patch.dict(os.environ, CONKER_JOBS="0"), self.assertRaises(ValueError):
            integrate.build_overlays({"main", "game"}, "us")
        run.assert_not_called()

    @mock.patch.object(integrate.subprocess, "run")
    def test_debugger_finalization_uses_eight_byte_boundaries_and_full_rom(self, run: mock.Mock) -> None:
        source = self.add_profile_unit("debugger", "func_debugger", 0x58, mixed=True)
        integrate.integrate("func_debugger", "us")
        destination = "src/done/debugger/system/func_debugger.c"
        self.assertFalse((self.root / source).exists())
        self.assertTrue((self.root / destination).is_file())
        self.assertIn("done/debugger/system/func_debugger", (self.root / "config/profiles/us.yaml").read_text())
        run.assert_called_once_with(
            ["make", "--silent", "--jobs", "4", "build", "PROFILE=us"],
            cwd=self.root, check=True,
        )

    @mock.patch.object(integrate.subprocess, "run")
    def test_debugger_raw_unit_can_enter_mixed_integration(self, run: mock.Mock) -> None:
        source = self.add_profile_unit("debugger", "func_debugger", 0x58, incomplete=True)
        integrate.integrate("func_debugger", "us")
        self.assertTrue((self.root / source).is_file())
        units = project_state.load_json(project_state.SOURCE_UNITS_FILE)["source_units"]
        self.assertEqual("mixed", next(unit for unit in units if unit["source"] == source)["integration"])
        self.assertIn("- [0x58, c, debugger/system/func_debugger]", (self.root / "config/profiles/us.yaml").read_text())
        run.assert_called_once_with(
            ["make", "--silent", "--jobs", "4", "build", "PROFILE=us"],
            cwd=self.root, check=True,
        )

    @mock.patch.object(integrate.subprocess, "run")
    def test_debugger_complete_raw_unit_finalizes_directly(self, run: mock.Mock) -> None:
        self.add_profile_unit("debugger", "func_debugger", 0x58)
        integrate.integrate("func_debugger", "us")
        self.assertTrue((self.root / "src/done/debugger/system/func_debugger.c").is_file())
        self.assertEqual("build", run.call_args.args[0][4])

    @mock.patch.object(integrate.subprocess, "run")
    def test_all_reviewed_builds_shared_full_rom_once_and_game_once(self, run: mock.Mock) -> None:
        self.add_profile_unit("main", "func_main", 0x40)
        self.add_profile_unit("debugger", "func_debugger", 0x58, mixed=True)
        integrate.integrate_all_reviewed("us")
        self.assertEqual([
            mock.call(["make", "--silent", "--jobs", "4", "build", "PROFILE=us"], cwd=self.root, check=True),
            mock.call(["make", "--silent", "--jobs", "4", "game-integrated-refresh"], cwd=self.root, check=True),
        ], run.call_args_list)
        for path in ("game/func_test.c", "main/system/func_main.c", "debugger/system/func_debugger.c"):
            self.assertTrue((self.root / "src/done" / path).is_file())
        units = project_state.load_json(project_state.SOURCE_UNITS_FILE)["source_units"]
        self.assertTrue(all(unit["integration"] == "c" for unit in units))

    @mock.patch.object(integrate.subprocess, "run")
    def test_all_reviewed_rolls_back_both_maps_after_second_build_fails(self, run: mock.Mock) -> None:
        self.add_profile_unit("main", "func_main", 0x40)
        self.add_profile_unit("debugger", "func_debugger", 0x58, mixed=True)
        project_state.render_progress(project_state.load_json(project_state.FUNCTIONS_FILE)["functions"])
        before = {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()}
        run.side_effect = [None, subprocess.CalledProcessError(1, ["make", "game-integrated-refresh"])]
        with self.assertRaises(subprocess.CalledProcessError):
            integrate.integrate_all_reviewed("us")
        self.assertEqual(before, {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()})
        self.assertFalse((self.root / "src/done").exists())
        self.assertEqual(2, run.call_count)

    @mock.patch.object(integrate.subprocess, "run")
    def test_all_reviewed_restores_progress_outputs_after_rendering_fails(self, run: mock.Mock) -> None:
        self.add_profile_unit("main", "func_main", 0x40)
        self.add_profile_unit("debugger", "func_debugger", 0x58, mixed=True)
        project_state.render_progress(project_state.load_json(project_state.FUNCTIONS_FILE)["functions"])
        before = {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()}
        render = project_state.render_progress
        def fail_after_render(functions: list[dict]) -> None:
            render(functions)
            raise RuntimeError("render failed after writes")
        with mock.patch.object(project_state, "render_progress", side_effect=fail_after_render):
            with self.assertRaisesRegex(RuntimeError, "render failed after writes"):
                integrate.integrate_all_reviewed("us")
        self.assertEqual(before, {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()})
        self.assertFalse((self.root / "src/done").exists())

    @mock.patch.object(integrate.subprocess, "run")
    def test_failed_transaction_removes_reports_that_did_not_exist_before(self, run: mock.Mock) -> None:
        self.add_profile_unit("main", "func_main", 0x40)
        before = {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()}
        self.assertFalse(project_state.SUMMARY_FILE.exists())
        render = project_state.render_progress
        def fail_after_render(functions: list[dict]) -> None:
            render(functions)
            raise RuntimeError("render failed after writes")
        with mock.patch.object(project_state, "render_progress", side_effect=fail_after_render):
            with self.assertRaisesRegex(RuntimeError, "render failed after writes"):
                integrate.integrate_all_reviewed("us")
        self.assertEqual(before, {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()})

    @mock.patch.object(integrate.subprocess, "run")
    def test_all_reviewed_skips_incomplete_main_but_integrates_raw_debugger(self, run: mock.Mock) -> None:
        main_source = self.add_profile_unit("main", "func_main", 0x40, incomplete=True)
        debugger_source = self.add_profile_unit("debugger", "func_debugger", 0x58, incomplete=True)
        integrate.integrate_all_reviewed("us")
        units = {unit["source"]: unit for unit in project_state.load_json(project_state.SOURCE_UNITS_FILE)["source_units"]}
        self.assertEqual("raw_asm", units[main_source]["integration"])
        self.assertEqual("mixed", units[debugger_source]["integration"])
        self.assertTrue((self.root / main_source).is_file())
        self.assertTrue((self.root / debugger_source).is_file())
        self.assertEqual(2, run.call_count)

    def test_map_range_ending_at_library_preserves_library_boundary(self) -> None:
        game_map = self.root / "config/game/us.yaml"
        game_map.write_text(
            "    subsegments:\n"
            "      - [0x10, asm]\n"
            "      - [0x20, lib, libultrare, cosf, .text]\n",
            encoding="utf-8",
        )

        integrate.replace_map_range(game_map, 0x10, 0x20, "game/func_test")

        self.assertEqual(
            "    subsegments:\n"
            "      - [0x10, c, game/func_test]\n"
            "      - [0x20, lib, libultrare, cosf, .text]\n",
            game_map.read_text(encoding="utf-8"),
        )

    @mock.patch.object(integrate.subprocess, "run")
    def test_main_finalization_preserves_arbitrary_source_directory(self, run: mock.Mock) -> None:
        source = "src/platform/system/init_test.c"
        destination = self.root / source
        destination.parent.mkdir(parents=True)
        (self.root / "src/game/func_test.c").rename(destination)
        functions = project_state.load_json(project_state.FUNCTIONS_FILE)
        functions["functions"][0].update(source=source, overlay="main")
        functions["functions"][0]["regions"]["us"]["vram"] = "0x80000010"
        units = project_state.load_json(project_state.SOURCE_UNITS_FILE)
        units["source_units"][0]["source"] = source
        project_state.write_json(project_state.FUNCTIONS_FILE, functions)
        project_state.write_json(project_state.SOURCE_UNITS_FILE, units)
        profile = self.root / "config/profiles/us.yaml"
        profile.parent.mkdir(parents=True)
        profile.write_bytes((self.root / "config/game/us.yaml").read_bytes())

        integrate.integrate("func_test", "us")

        run.assert_called_once_with(
            ["make", "--silent", "--jobs", "4", "build", "PROFILE=us"],
            cwd=self.root, check=True,
        )
        self.assertTrue((self.root / "src/done/platform/system/init_test.c").is_file())
        self.assertIn("done/platform/system/init_test", profile.read_text())

    def test_completed_path_mirrors_debugger_directory_and_nested_paths(self) -> None:
        for source in ("src/debugger/debugger_0000.c", "src/debugger/transport/serial.c"):
            with self.subTest(source=source):
                expected = source.replace("src/", "src/done/", 1)
                self.assertEqual(expected, project_state.completed_source_path(source, "debugger"))
                self.assertEqual(expected, project_state.completed_source_path(expected, "debugger"))

    def prepare_legacy_completed_units(self) -> None:
        functions = project_state.load_json(project_state.FUNCTIONS_FILE)
        units = project_state.load_json(project_state.SOURCE_UNITS_FILE)
        for overlay, symbol, filename in (("game", "func_test", "func_test"),
                                           ("main", "func_main", "init_test")):
            source = f"src/game/done/{filename}.c"
            path = self.root / source
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(f"void {symbol}(void) {{}}\n")
            function = json.loads(json.dumps(functions["functions"][0]))
            function.update(source=source, overlay=overlay, symbol=symbol)
            function["regions"]["us"].update(symbol=symbol, vram="0x80000010" if overlay == "main" else "0x15000010")
            unit = json.loads(json.dumps(units["source_units"][0]))
            unit.update(source=source, integration="c", functions=[symbol])
            unit["regions"]["us"]["state"] = "complete"
            if overlay == "game":
                functions["functions"][0] = function
                units["source_units"][0] = unit
            else:
                functions["functions"].append(function)
                units["source_units"].append(unit)
            directory = "profiles" if overlay == "main" else "game"
            mapping = self.root / f"config/{directory}/us.yaml"
            mapping.parent.mkdir(parents=True, exist_ok=True)
            mapping.write_text(f"      - [0x10, c, game/done/{filename}]\n      - [0x20, asm]\n")
        (self.root / "src/game/func_test.c").unlink()
        project_state.write_json(project_state.FUNCTIONS_FILE, functions)
        project_state.write_json(project_state.SOURCE_UNITS_FILE, units)

    def test_normalization_moves_both_overlays_and_is_idempotent(self) -> None:
        self.prepare_legacy_completed_units()
        project_state.normalize_done_sources()
        functions = project_state.validate_functions(project_state.load_json(project_state.FUNCTIONS_FILE))
        units = project_state.validate_source_units(project_state.load_json(project_state.SOURCE_UNITS_FILE), functions)
        self.assertEqual(["src/done/game/func_test.c", "src/done/main/init_test.c"],
                         [unit["source"] for unit in units])
        for function in functions:
            self.assertEqual(f"void {function['symbol']}(void) {{}}\n",
                             (self.root / function["source"]).read_text())
        before = {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()}
        project_state.normalize_done_sources()
        self.assertEqual(before, {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()})

    def test_normalization_restores_all_files_when_rendering_fails(self) -> None:
        self.prepare_legacy_completed_units()
        before = {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()}
        with mock.patch.object(project_state, "render_progress", side_effect=RuntimeError("render failed")):
            with self.assertRaisesRegex(RuntimeError, "render failed"):
                project_state.normalize_done_sources()
        self.assertEqual(before, {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()})
        self.assertFalse((self.root / "src/done").exists())

    def test_normalization_rejects_destination_collision_before_moving(self) -> None:
        self.prepare_legacy_completed_units()
        collision = self.root / "src/done/main/init_test.c"
        collision.parent.mkdir(parents=True)
        collision.write_text("existing work\n")
        before = {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()}
        with self.assertRaisesRegex(project_state.ProjectStateError, "destination already exists"):
            project_state.normalize_done_sources()
        self.assertEqual(before, {path: path.read_bytes() for path in self.root.rglob("*") if path.is_file()})

    def test_map_range_cannot_cross_library_boundary(self) -> None:
        game_map = self.root / "config/game/us.yaml"
        game_map.write_text(
            "    subsegments:\n"
            "      - [0x10, asm]\n"
            "      - [0x20, lib, libultrare, cosf, .text]\n"
            "      - [0x30, asm]\n",
            encoding="utf-8",
        )
        original_map = game_map.read_bytes()

        with self.assertRaisesRegex(
            project_state.ProjectStateError, "crosses an existing map boundary"
        ):
            integrate.replace_map_range(game_map, 0x10, 0x30, "game/func_test")

        self.assertEqual(original_map, game_map.read_bytes())

    @mock.patch.object(integrate.subprocess, "run")
    def test_integrates_matched_game_source_after_byte_identical_build(self, run: mock.Mock) -> None:
        def assert_build_sees_finalized_project(*args: object, **kwargs: object) -> None:
            functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
            units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
            self.assertEqual("src/done/game/func_test.c", functions["functions"][0]["source"])
            self.assertEqual("src/done/game/func_test.c", units["source_units"][0]["source"])
            self.assertEqual("c", units["source_units"][0]["integration"])
            self.assertTrue((self.root / "src/done/game/func_test.c").is_file())

        run.side_effect = assert_build_sees_finalized_project
        integrate.integrate("func_test", "us")

        run.assert_called_once_with(
            ["make", "--silent", "--jobs", "4", "game-integrated-refresh"],
            cwd=self.root,
            check=True,
        )
        self.assertFalse((self.root / "src/game/func_test.c").exists())
        self.assertTrue((self.root / "src/done/game/func_test.c").is_file())
        game_map = (self.root / "config/game/us.yaml").read_text(encoding="utf-8")
        self.assertIn("- [0x10, c, done/game/func_test]", game_map)
        self.assertIn("- [0x20, asm]", game_map)
        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        self.assertEqual("src/done/game/func_test.c", functions["functions"][0]["source"])
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
        self.assertFalse((self.root / "src/done/game/func_test.c").exists())
        self.assertEqual(original_map, (self.root / "config/game/us.yaml").read_bytes())
        self.assertEqual(original_functions, project_state.FUNCTIONS_FILE.read_bytes())
        self.assertEqual(original_units, project_state.SOURCE_UNITS_FILE.read_bytes())

    @mock.patch.object(integrate.subprocess, "run")
    def test_all_reviewed_finalizes_complete_raw_unit(self, run: mock.Mock) -> None:
        integrate.integrate_all_reviewed("us")

        run.assert_called_once_with(
            ["make", "--silent", "--jobs", "4", "game-integrated-refresh"],
            cwd=self.root,
            check=True,
        )
        self.assertFalse((self.root / "src/game/func_test.c").exists())
        self.assertTrue((self.root / "src/done/game/func_test.c").is_file())
        game_map = (self.root / "config/game/us.yaml").read_text(encoding="utf-8")
        self.assertIn("- [0x10, c, done/game/func_test]", game_map)
        functions = json.loads(project_state.FUNCTIONS_FILE.read_text(encoding="utf-8"))
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        self.assertEqual("src/done/game/func_test.c", functions["functions"][0]["source"])
        self.assertEqual("c", units["source_units"][0]["integration"])
        self.assertEqual("complete", units["source_units"][0]["regions"]["us"]["state"])

    @mock.patch.object(integrate.subprocess, "run")
    def test_all_reviewed_finalizes_complete_mixed_unit(self, run: mock.Mock) -> None:
        game_map = self.root / "config/game/us.yaml"
        game_map.write_text(
            "    subsegments:\n"
            "      - [0x0, asm]\n"
            "      - [0x10, c, game/func_test]\n"
            "      - [0x20, asm]\n"
            "      - [0x30, asm]\n",
            encoding="utf-8",
        )
        units = json.loads(project_state.SOURCE_UNITS_FILE.read_text(encoding="utf-8"))
        units["source_units"][0]["integration"] = "mixed"
        project_state.SOURCE_UNITS_FILE.write_text(json.dumps(units) + "\n", encoding="utf-8")

        integrate.integrate_all_reviewed("us")

        self.assertTrue((self.root / "src/done/game/func_test.c").is_file())
        self.assertIn(
            "- [0x10, c, done/game/func_test]",
            game_map.read_text(encoding="utf-8"),
        )

    @mock.patch.object(integrate.subprocess, "run")
    def test_failed_all_reviewed_finalization_restores_project(self, run: mock.Mock) -> None:
        run.side_effect = subprocess.CalledProcessError(
            1, ["make", "game-integrated-refresh"]
        )
        original_map = (self.root / "config/game/us.yaml").read_bytes()
        original_functions = project_state.FUNCTIONS_FILE.read_bytes()
        original_units = project_state.SOURCE_UNITS_FILE.read_bytes()

        with self.assertRaises(subprocess.CalledProcessError):
            integrate.integrate_all_reviewed("us")

        self.assertTrue((self.root / "src/game/func_test.c").is_file())
        self.assertFalse((self.root / "src/done/game/func_test.c").exists())
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
        self.assertFalse((self.root / "src/done/game/func_test.c").exists())
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
