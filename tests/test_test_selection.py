from __future__ import annotations

import os
from pathlib import Path
import shlex
import subprocess
import sys
import tempfile
import textwrap
import unittest

from scripts import test_selection


ROOT = Path(__file__).resolve().parents[1]
SCRIPT = (ROOT / "scripts/conker.sh").read_text(encoding="utf-8")
GIT_ENV = dict(os.environ, GIT_AUTHOR_NAME="fixture", GIT_AUTHOR_EMAIL="fixture@example.invalid",
               GIT_COMMITTER_NAME="fixture", GIT_COMMITTER_EMAIL="fixture@example.invalid",
               GIT_CONFIG_GLOBAL=os.devnull, GIT_CONFIG_NOSYSTEM="1")


def git(root: Path, *arguments: str) -> str:
    return subprocess.run(["git", "-C", str(root), *arguments], check=True, capture_output=True,
                          text=True, env=GIT_ENV).stdout


def write(root: Path, relative: str, text: str = "x\n") -> None:
    path = root / relative
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


class FixtureRepository:
    """A git repository with a `main` base commit and a `work` branch on top."""

    def __init__(self, root: Path) -> None:
        self.root = root
        git(root, "init", "-q", "-b", "main")
        for relative in ("src/game/game_1.c", "include/types.h", "progress/functions.json",
                         "config/game/us.yaml", "config/data/us.json", "docs/guide.md",
                         "asm/nonmatchings/game/func.s", "scripts/conker.sh", "tests/test_x.py",
                         "Makefile", "Dockerfile", "toolchain/python-requirements.txt",
                         "lib/README.md", "AGENTS.md"):
            write(root, relative)
        git(root, "add", "-A")
        git(root, "commit", "-q", "-m", "base")
        git(root, "checkout", "-q", "-b", "work")

    def commit(self, *relatives: str) -> None:
        for relative in relatives:
            write(self.root, relative, "changed\n")
        git(self.root, "add", "-A")
        git(self.root, "commit", "-q", "-m", "change " + " ".join(relatives))

    def classify(self, base: str | None = None) -> test_selection.Classification:
        return test_selection.classify_repository(self.root, base)


class ClassifyPathsTests(unittest.TestCase):
    def test_c_only_set_covers_sources_headers_inventories_source_map_docs_and_nonmatchings(self):
        result = test_selection.classify_paths(
            ["src/game/game_1.c", "include/types.h", "progress/functions.json",
             "progress/source_units.json", "config/game/us.yaml", "docs/guide.md",
             "asm/nonmatchings/game/func.s", "src/done/main/boot.c"], base="main")
        self.assertEqual("c-only", result.kind)
        self.assertIn("all 8 changed paths", result.reason)
        self.assertIn("relative to main", result.reason)

    def test_each_tooling_asset_or_build_input_path_forces_the_full_suite(self):
        for path in ("scripts/conker.sh", "scripts/test_selection.py", "tests/test_diff.py",
                     "tests/fixtures/frame_plan/a.s", "Makefile", "Dockerfile",
                     "toolchain/tools.lock.json", "config/data/us.json", "config/game/eu.yaml",
                     "config/game/us-rodata.ld", "lib/ultralib", "assets/textures/a.png",
                     ".github/workflows/ci.yml", "AGENTS.md", "conker", "asm/us/main.s"):
            with self.subTest(path=path):
                result = test_selection.classify_paths(["src/game/game_1.c", path], base="main")
                self.assertEqual("full", result.kind, path)
                self.assertIn("1 of 2 changed paths are outside the C/inventory set", result.reason)
                self.assertIn(path, result.reason)
                self.assertNotIn("src/game/game_1.c", result.reason)

    def test_no_changes_is_c_only_and_long_lists_are_summarised(self):
        self.assertEqual("c-only", test_selection.classify_paths([], base="main").kind)
        self.assertIn("no changed paths relative to main", test_selection.classify_paths([], base="main").reason)
        many = [f"src/game/game_{index}.c" for index in range(10)]
        result = test_selection.classify_paths(many + many, base=None)
        self.assertEqual("c-only", result.kind)
        self.assertEqual(sorted(set(many)), result.paths)
        self.assertIn("... (4 more)", result.reason)
        self.assertNotIn("relative to", result.reason)


class ClassifyRepositoryTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="test selection ")
        self.addCleanup(self.temporary.cleanup)
        self.repo = FixtureRepository(Path(self.temporary.name))
        self.environment = dict(os.environ)
        os.environ.pop("CONKER_BASE_BRANCH", None)
        self.addCleanup(lambda: (os.environ.clear(), os.environ.update(self.environment)))

    def test_clean_branch_without_commits_is_c_only(self):
        result = self.repo.classify()
        self.assertEqual("c-only", result.kind)
        self.assertEqual("no changed paths relative to main", result.reason)

    def test_committed_c_and_inventory_changes_since_the_merge_base_are_c_only(self):
        self.repo.commit("src/game/game_1.c", "progress/functions.json")
        self.repo.commit("src/game/game_2.c", "config/game/us.yaml")
        write(self.repo.root, "include/types.h", "unstaged\n")
        write(self.repo.root, "docs/new.md")
        result = self.repo.classify()
        self.assertEqual("c-only", result.kind)
        self.assertEqual(["config/game/us.yaml", "docs/new.md", "include/types.h",
                          "progress/functions.json", "src/game/game_1.c", "src/game/game_2.c"],
                         result.paths)

    def test_main_moving_ahead_does_not_count_its_tooling_changes(self):
        self.repo.commit("src/game/game_1.c")
        git(self.repo.root, "checkout", "-q", "main")
        self.repo.commit("scripts/conker.sh")
        git(self.repo.root, "checkout", "-q", "work")
        result = self.repo.classify()
        self.assertEqual("c-only", result.kind)
        self.assertEqual(["src/game/game_1.c"], result.paths)

    def test_committed_tooling_change_forces_the_full_suite(self):
        self.repo.commit("src/game/game_1.c", "scripts/diff.py")
        result = self.repo.classify()
        self.assertEqual("full", result.kind)
        self.assertIn("scripts/diff.py", result.reason)

    def test_untracked_staged_and_renamed_paths_count(self):
        write(self.repo.root, "tests/fixtures/new/case.s")
        self.assertEqual("full", self.repo.classify().kind)
        os.remove(self.repo.root / "tests/fixtures/new/case.s")
        self.assertEqual("c-only", self.repo.classify().kind)
        write(self.repo.root, "Makefile", "staged\n")
        git(self.repo.root, "add", "Makefile")
        self.assertIn("Makefile", self.repo.classify().reason)
        git(self.repo.root, "checkout", "-q", "--", "Makefile")
        git(self.repo.root, "mv", "src/game/game_1.c", "scripts/game_1.c")
        result = self.repo.classify()
        self.assertEqual("full", result.kind)
        self.assertIn("scripts/game_1.c", result.reason)

    def test_base_branch_resolution_prefers_explicit_then_environment_then_origin_main(self):
        self.repo.commit("src/game/game_1.c")
        git(self.repo.root, "branch", "release", "main")
        git(self.repo.root, "checkout", "-q", "release")
        self.repo.commit("scripts/conker.sh")
        git(self.repo.root, "checkout", "-q", "work")
        self.assertEqual("main", test_selection.resolve_base(self.repo.root))
        self.assertEqual("release", test_selection.resolve_base(self.repo.root, "release"))
        os.environ["CONKER_BASE_BRANCH"] = "release"
        self.assertEqual("release", test_selection.resolve_base(self.repo.root))
        self.assertIn("relative to release", self.repo.classify().reason)
        self.assertEqual("c-only", self.repo.classify().kind)
        os.environ["CONKER_BASE_BRANCH"] = "missing"
        self.assertEqual("main", test_selection.resolve_base(self.repo.root))
        git(self.repo.root, "update-ref", "refs/remotes/origin/main", "release")
        self.assertEqual("origin/main", test_selection.resolve_base(self.repo.root))

    def test_missing_base_branch_falls_back_to_the_full_suite(self):
        git(self.repo.root, "branch", "-D", "main")
        result = self.repo.classify()
        self.assertEqual("full", result.kind)
        self.assertIn("no base branch", result.reason)

    def test_command_line_prints_kind_then_reason(self):
        self.repo.commit("src/game/game_1.c")
        result = subprocess.run([sys.executable, str(ROOT / "scripts/test_selection.py"), "classify",
                                 "--root", str(self.repo.root)], capture_output=True, text=True, env=GIT_ENV)
        self.assertEqual(0, result.returncode, result.stderr)
        kind, reason = result.stdout.splitlines()
        self.assertEqual("c-only", kind)
        self.assertIn("src/game/game_1.c", reason)
        result = subprocess.run([sys.executable, str(ROOT / "scripts/test_selection.py"), "classify",
                                 "--root", self.temporary.name + "/missing"], capture_output=True, text=True)
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertEqual("full", result.stdout.splitlines()[0])
        self.assertIn("no base branch", result.stdout)


class ReferencedScriptsTests(unittest.TestCase):
    KNOWN = frozenset({"diff", "texture_build", "compile_c", "conker", "layout_check", "model_assets", "probe"})

    def scan(self, text: str) -> set[str]:
        return test_selection.referenced_scripts(textwrap.dedent(text), self.KNOWN)

    def test_every_import_and_file_reference_style_is_found(self):
        self.assertEqual({"diff"}, self.scan("from scripts import diff\n"))
        self.assertEqual({"diff", "compile_c"}, self.scan("from scripts import diff, compile_c as cc\n"))
        self.assertEqual({"diff", "texture_build"}, self.scan("""
            from scripts import (
                diff,
                texture_build as build,  # comment
            )
        """))
        self.assertEqual({"layout_check"}, self.scan("from scripts.layout_check import check\n"))
        self.assertEqual({"layout_check"}, self.scan("import scripts.layout_check\n"))
        self.assertEqual({"diff", "probe"}, self.scan("import diff, probe\n"))
        self.assertEqual({"diff"}, self.scan("    import diff  # inside a function\n"))
        self.assertEqual({"model_assets"}, self.scan("from model_assets import load\n"))
        self.assertEqual({"conker"}, self.scan('script = (ROOT / "scripts/conker.sh").read_text()\n'))
        self.assertEqual({"compile_c"}, self.scan("spec_from_file_location('x', SCRIPTS / 'compile_c.py')\n"))
        self.assertEqual({"diff"}, self.scan('subprocess.run(["python3", "scripts/diff.py"])\n'))

    def test_unknown_names_and_stdlib_imports_are_ignored(self):
        self.assertEqual(set(), self.scan("import json\nfrom pathlib import Path\nfrom scripts import unknown\n"))
        self.assertEqual(set(), self.scan("# from scripts import diff\n"))
        self.assertEqual(set(), self.scan("from tests.test_diff import helper\n"))


class SelectModulesTests(unittest.TestCase):
    def make_tree(self, modules: dict[str, str], scripts: tuple[str, ...]) -> Path:
        temporary = tempfile.TemporaryDirectory(prefix="test selection tree ")
        self.addCleanup(temporary.cleanup)
        root = Path(temporary.name)
        for name in scripts:
            write(root, f"scripts/{name}.py", "")
        for name, text in modules.items():
            write(root, f"tests/{name}.py", textwrap.dedent(text))
        return root

    def test_matching_modules_are_selected_and_asset_modules_are_not(self):
        root = self.make_tree({
            "test_diff": "from scripts import diff\n",
            "test_new_matching_tool": "import sys\nsys.path.insert(0, 'scripts')\nimport layout_check\n",
            "test_texture_build": "from scripts import texture_build\n",
            "test_asset_build": "from scripts import compile_c, texture_build\n",
            "test_model_batch": "from scripts import (\n    diff,\n    model_assets,\n)\n",
            "test_shell_gate": "SCRIPT = (ROOT / 'scripts/conker.sh').read_text()\n",
            "test_defer_shell": "import unittest\n",
            "test_unrelated": "import unittest\n",
            "helper": "from scripts import diff\n",
        }, ("diff", "layout_check", "texture_build", "compile_c", "model_assets"))
        selected = test_selection.select_modules(root)
        self.assertEqual({
            "test_defer_shell": "allowlisted",
            "test_diff": "references diff",
            "test_new_matching_tool": "references layout_check",
            "test_shell_gate": "references conker",
        }, selected)
        self.assertEqual(sorted(selected), list(selected))

    def test_asset_prefixes_cover_every_reconstruction_domain(self):
        for name in ("adpcm_build", "animation_bank_build", "asset_inputs", "audio_assets", "event_build",
                     "font_assets", "hud_assets", "model_build", "mp3_bank", "route_build", "rzip_pack",
                     "scene_field_build", "script_build", "sequence_build", "sound_bank_build",
                     "soundtrack_preview", "sprite_build", "texture_assets", "visibility_build"):
            self.assertTrue(name.startswith(test_selection.ASSET_SCRIPT_PREFIXES), name)
        for name in sorted(test_selection.MATCHING_SCRIPTS):
            self.assertFalse(name.startswith(test_selection.ASSET_SCRIPT_PREFIXES), name)

    def test_real_repository_selection_keeps_matching_and_drops_reconstruction_modules(self):
        selected = test_selection.select_modules(ROOT)
        for name in ("test_diff", "test_compile_c", "test_layout_check", "test_integrate", "test_project_state",
                     "test_matching_history", "test_matching_context", "test_candidate_tables",
                     "test_linked_aliases", "test_prepare_nonmatching_asm", "test_list_integrated_sources",
                     "test_main_private_data", "test_data_boundaries", "test_objdiff_ownership",
                     "test_verify_main_rodata", "test_verify_game_rodata", "test_verify_debugger_rodata",
                     "test_declaration_conflicts", "test_call_signatures", "test_siblings", "test_frame_plan",
                     "test_struct_layouts", "test_defer_shell", "test_matching_shell", "test_overlay_headers",
                     "test_repository_safety", "test_python_test_runner", "test_test_selection"):
            self.assertIn(name, selected)
        for name in ("test_asset_build", "test_texture_build", "test_model_build", "test_model_assets",
                     "test_adpcm_build", "test_audio_assets", "test_soundtrack_preview", "test_mp3_bank",
                     "test_font_assets", "test_main_queue_object_build", "test_automate"):
            self.assertNotIn(name, selected)
        self.assertLess(len(selected), 90)
        for name in test_selection.MATCHING_SCRIPTS:
            self.assertTrue(name == "conker" or (ROOT / "scripts" / f"{name}.py").is_file(), name)
        for name in test_selection.ALWAYS_SELECTED_MODULES:
            self.assertTrue((ROOT / "tests" / f"{name}.py").is_file(), name)

    def test_modules_command_lists_names_and_explains_them(self):
        root = self.make_tree({"test_diff": "from scripts import diff\n", "test_other": ""}, ("diff",))
        plain = subprocess.run([sys.executable, str(ROOT / "scripts/test_selection.py"), "modules", "--root", str(root)],
                               capture_output=True, text=True, check=True).stdout
        self.assertEqual("test_diff\n", plain)
        explained = subprocess.run([sys.executable, str(ROOT / "scripts/test_selection.py"), "modules", "--explain",
                                    "--root", str(root)], capture_output=True, text=True, check=True).stdout
        self.assertEqual("test_diff\treferences diff\n", explained)


class RunModulesTests(unittest.TestCase):
    def test_run_imports_modules_like_discover_and_forwards_unittest_options(self):
        result = subprocess.run([sys.executable, str(ROOT / "scripts/test_selection.py"), "run", "-q",
                                 "test_test_selection.ReferencedScriptsTests"],
                                capture_output=True, text=True, cwd=self.temporary_cwd())
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertRegex(result.stderr, r"Ran 2 tests")
        self.assertIn("OK", result.stderr)
        result = subprocess.run([sys.executable, str(ROOT / "scripts/test_selection.py"), "run", "-q",
                                 "test_module_that_does_not_exist"], capture_output=True, text=True)
        self.assertNotEqual(0, result.returncode)

    def temporary_cwd(self) -> str:
        temporary = tempfile.TemporaryDirectory(prefix="run cwd ")
        self.addCleanup(temporary.cleanup)
        return temporary.name


def shell_function(name: str) -> str:
    return name + "() {" + SCRIPT.split(name + "() {", 1)[1].split("\n}\n", 1)[0] + "\n}\n"


class ShellIntegrationTests(unittest.TestCase):
    """Run the real Bash pieces with the Python selector and Docker replaced."""

    RUNNER = ("select_test_runner() {" + SCRIPT.split("select_test_runner() {", 1)[1]
              .split("run_in_container_interactive() {", 1)[0])

    def run_shell(self, body: str, *, classify: str, modules: str, runner: str = "host") -> subprocess.CompletedProcess:
        with tempfile.TemporaryDirectory(prefix="shell selection ") as root:
            for directory in ("src", "tests"):
                (Path(root) / directory).mkdir()
            harness = "set -euo pipefail\nrepo_root=" + shlex.quote(root) + "\n"
            harness += "fake_classify=" + shlex.quote(classify) + "\nfake_modules=" + shlex.quote(modules) + "\n"
            harness += r'''
image_name=pinned-image
container_run_args=(--platform linux/amd64 --read-only --tmpfs /tmp:rw,nosuid,nodev,size=1g)
die() { printf 'error: %s\n' "$*" >&2; exit 1; }
require_docker_access() { :; }
ensure_image() { :; }
docker() { printf 'docker %s\n' "$*" >&2; }
python3() {
    case "${1##*/} ${2:-}" in
        'host_environment.py check') return 0 ;;
        'test_selection.py classify') [[ -n "$fake_classify" ]] || return 1; printf '%s\n' "$fake_classify"; return 0 ;;
        'test_selection.py modules') printf '%s\n' "$fake_modules"; return 0 ;;
    esac
    if [[ "$1" == "--version" ]]; then printf 'Python 3.12.0\n'; return; fi
    if [[ "$1" == "-c" ]]; then printf '%s\n' "$repo_root"; return; fi
    printf 'host-python %s\n' "$*" >&2
}
'''
            env = dict(os.environ, CONKER_TEST_RUNNER=runner)
            return subprocess.run(["bash", "-c", harness + self.RUNNER + body], capture_output=True, text=True,
                                  env=env, cwd=root)

    def test_c_only_batch_runs_the_subset_through_the_selector_on_host_and_in_docker(self):
        body = "select_test_runner\nclassify_batch_tests\nrun_python_tests -q -b\n"
        result = self.run_shell(body, classify="c-only\nall 2 changed paths are C: src/a.c, progress/functions.json",
                                modules="test_diff\ntest_project_state\n")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn("tests: C-only batch -> matching subset (2 modules) (all 2 changed paths are C: src/a.c, progress/functions.json)",
                      result.stdout)
        self.assertRegex(result.stderr, r"host-python .*/scripts/test_selection\.py run -q -b test_diff test_project_state\n")
        self.assertNotIn("unittest discover", result.stderr)
        result = self.run_shell(body, classify="c-only\nreason", modules="test_diff\n", runner="docker")
        self.assertEqual(0, result.returncode, result.stderr)
        command = next(line for line in result.stderr.splitlines() if line.startswith("docker run "))
        self.assertTrue(command.endswith("pinned-image python3 scripts/test_selection.py run -q -b test_diff"), command)

    def test_full_batches_keep_the_discover_command(self):
        body = "select_test_runner\nclassify_batch_tests\nrun_python_tests -q -b\n"
        result = self.run_shell(body, classify="full\n1 of 2 changed paths are outside the C/inventory set: scripts/diff.py",
                                modules="test_diff\n")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn("tests: full suite (1 of 2 changed paths are outside the C/inventory set: scripts/diff.py)", result.stdout)
        self.assertIn("host-python -m unittest discover -s tests -q -b", result.stderr)
        self.assertNotIn("test_selection.py run", result.stderr)
        result = self.run_shell(body, classify="full\nreason", modules="", runner="docker")
        command = next(line for line in result.stderr.splitlines() if line.startswith("docker run "))
        self.assertTrue(command.endswith("pinned-image python3 -m unittest discover -s tests -q -b"), command)

    def test_selector_failure_or_empty_selection_fails_the_classification(self):
        body = "select_test_runner\nclassify_batch_tests || { printf 'classification failed\\n'; exit 3; }\n"
        result = self.run_shell(body, classify="", modules="test_diff\n")
        self.assertEqual(3, result.returncode, result.stderr)
        result = self.run_shell(body, classify="c-only\nreason", modules="")
        self.assertEqual(3, result.returncode, result.stderr)
        self.assertNotIn("host-python", result.stderr)

    def test_verify_batch_case_classifies_before_the_build_and_honours_full_tests(self):
        batch_case = SCRIPT.split("    verify-batch)", 1)[1].split("        ;;", 1)[0]
        self.assertIn("--full-tests) batch_full_tests=1", batch_case)
        self.assertIn("classify_batch_tests", batch_case)
        self.assertIn("tests: full suite (--full-tests)", batch_case)
        self.assertLess(batch_case.index("classify_batch_tests"), batch_case.index("batch-fingerprint"))
        self.assertLess(batch_case.index("run_python_tests -q -b"), batch_case.index("passed in %ds"))
        test_case = SCRIPT.split("\n    test)\n", 1)[1].split("\n    test-selection)\n", 1)[0]
        self.assertIn("--matching)", test_case)
        self.assertIn("select_matching_test_modules", test_case)
        self.assertIn("verify-batch [--incremental] [--host-tests] [--full-tests]", SCRIPT)
        self.assertIn("test [--host] [--matching] [unittest options]", SCRIPT)
        ci = (ROOT / ".github/workflows/ci.yml").read_text(encoding="utf-8")
        self.assertIn("./conker test --host -v", ci)
        self.assertIn("./conker test -v", ci)
        self.assertNotIn("--matching", ci)


if __name__ == "__main__":
    unittest.main()
