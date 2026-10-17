#!/usr/bin/env python3
"""Classify a batch's changes and select the matching-relevant Python tests.

``verify-batch`` runs the full Python suite for tooling, asset or build-input
changes and public CI always runs it in Docker. A batch whose only changes are
C sources, headers, inventories, the game source map, documentation or
nonmatching assembly cannot break the asset, model, audio, texture or
soundtrack reconstruction tests, so it runs only the curated matching subset.

Subcommands:

``classify [--base REF]``
    Print ``c-only`` or ``full`` on the first line and the reason on the second.
    Changes are the working tree (``git status --porcelain``) plus every commit
    since the merge base with the base branch (``CONKER_BASE_BRANCH``, else
    ``origin/main``, else ``main``).
``modules [--explain]``
    Print the selected test module names, one per line (``--explain`` adds the
    scripts that selected each module).
``run [unittest options] <module>...``
    Run the named test modules the way ``python3 -m unittest discover -s tests``
    would import them.
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# A batch is "C-only" when every changed path lives here.
C_ONLY_DIRECTORIES = ("src/", "include/", "progress/", "docs/", "asm/nonmatchings/")
C_ONLY_FILES = ("config/game/us.yaml",)

# Script stems whose test modules exercise the matching, integration,
# inventory, data-ownership or progress paths a C/inventory change can break.
# ``conker`` stands for the shell entry points (conker, scripts/conker.sh).
MATCHING_SCRIPTS = frozenset({
    "conker",
    "attempt_history",
    "call_signatures",
    "candidate_rewrites",
    "candidate_syntax",
    "candidate_tables",
    "compile_c",
    "compile_diff_candidate",
    "data_boundaries",
    "declaration_conflicts",
    "declaration_facts",
    "diff",
    "frame_plan",
    "integrate",
    "layout_check",
    "linked_aliases",
    "list_integrated_sources",
    "m2c",
    "m2c_context",
    "main_private_data",
    "matching_blockers",
    "matching_callers",
    "matching_context",
    "matching_history",
    "matching_prerequisites",
    "normalize_asm",
    "objdiff_ownership",
    "original_asm",
    "permute",
    "prepare_game_integration",
    "prepare_game_reference",
    "prepare_nonmatching_asm",
    "probe",
    "project_state",
    "rom_span",
    "siblings",
    "split_game_rodata",
    "struct_layouts",
    "test_selection",
    "verify_debugger_rodata",
    "verify_game_rodata",
    "verify_main_rodata",
    "verify_main_vi_bss",
})

# Test modules that always belong to the subset, whatever the scan finds.
ALWAYS_SELECTED_MODULES = frozenset({
    "test_declaration_conflicts",
    "test_defer_shell",
    "test_matching_shell",
    "test_overlay_headers",
    "test_project_state",
    "test_python_test_runner",
    "test_test_selection",
})

# A module that exercises an asset, model, audio, texture or soundtrack script
# belongs to the full suite even when it also imports a matching helper.
ASSET_SCRIPT_PREFIXES = (
    "adpcm_", "animation_", "asset_", "audio_", "event_", "font_", "hud_",
    "model_", "mp3_", "route_", "rzip_", "scene_", "script_", "sequence_",
    "sound_", "soundtrack_", "sprite_", "texture_", "visibility_",
)

_FROM_SCRIPTS = re.compile(r"^\s*from\s+scripts\s+import\s+(.*)$")
_FROM_SCRIPTS_MODULE = re.compile(r"^\s*from\s+scripts\.([A-Za-z_][A-Za-z0-9_]*)\s+import\b")
_IMPORT_SCRIPTS_MODULE = re.compile(r"^\s*import\s+scripts\.([A-Za-z_][A-Za-z0-9_]*)\b")
_IMPORT = re.compile(r"^\s*import\s+(.*)$")
_FROM_MODULE = re.compile(r"^\s*from\s+([A-Za-z_][A-Za-z0-9_]*)\s+import\b")
_SCRIPT_FILE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\.(?:py|sh)\b")


@dataclass
class Classification:
    kind: str  # "c-only" or "full"
    reason: str
    paths: list[str] = field(default_factory=list)


def is_c_only_path(path: str) -> bool:
    return path in C_ONLY_FILES or path.startswith(C_ONLY_DIRECTORIES)


def _summarize(paths: list[str], limit: int = 6) -> str:
    shown = ", ".join(paths[:limit])
    if len(paths) > limit:
        shown += f", ... ({len(paths) - limit} more)"
    return shown


def classify_paths(paths: list[str], *, base: str | None) -> Classification:
    """Classify changed paths; ``base`` names the compared branch for the reason."""

    unique = sorted(set(paths))
    compared = f" relative to {base}" if base else ""
    if not unique:
        return Classification("c-only", f"no changed paths{compared}", unique)
    outside = [path for path in unique if not is_c_only_path(path)]
    if outside:
        return Classification(
            "full",
            f"{len(outside)} of {len(unique)} changed paths are outside the "
            f"C/inventory set{compared}: {_summarize(outside)}",
            unique,
        )
    return Classification(
        "c-only",
        f"all {len(unique)} changed paths are C, header, inventory, game source map, "
        f"docs or nonmatching assembly{compared}: {_summarize(unique)}",
        unique,
    )


def _git(root: Path, *arguments: str) -> str:
    return subprocess.run(
        ["git", "-C", str(root), *arguments],
        check=True, capture_output=True, text=True,
    ).stdout


def _ref_exists(root: Path, ref: str) -> bool:
    result = subprocess.run(
        ["git", "-C", str(root), "rev-parse", "--verify", "--quiet", ref + "^{commit}"],
        capture_output=True, text=True,
    )
    return result.returncode == 0


def resolve_base(root: Path, base: str | None = None) -> str | None:
    """Pick the base branch: explicit, CONKER_BASE_BRANCH, origin/main, main."""

    candidates = [base] if base else []
    environment = os.environ.get("CONKER_BASE_BRANCH")
    if environment:
        candidates.append(environment)
    candidates.extend(["origin/main", "main"])
    for candidate in candidates:
        if candidate and _ref_exists(root, candidate):
            return candidate
    return None


def worktree_paths(root: Path) -> list[str]:
    """Paths with staged, unstaged or untracked changes (renames give both sides)."""

    paths: list[str] = []
    for line in _git(root, "status", "--porcelain", "--untracked-files=all").splitlines():
        if len(line) < 4:
            continue
        entry = line[3:]
        if " -> " in entry:
            paths.extend(entry.split(" -> ", 1))
        else:
            paths.append(entry)
    return [path.strip('"') for path in paths if path]


def committed_paths(root: Path, base: str) -> list[str]:
    merge_base = _git(root, "merge-base", "HEAD", base).strip()
    return [line for line in _git(root, "diff", "--name-only", merge_base, "HEAD").splitlines() if line]


def classify_repository(root: Path = ROOT, base: str | None = None) -> Classification:
    """Classify the checkout's working tree plus its commits since the base branch."""

    resolved = resolve_base(root, base)
    if resolved is None:
        return Classification(
            "full",
            "no base branch to compare against (set CONKER_BASE_BRANCH or fetch origin/main)",
        )
    paths = worktree_paths(root) + committed_paths(root, resolved)
    return classify_paths(paths, base=resolved)


def _names(fragment: str) -> list[str]:
    fragment = fragment.split("#", 1)[0]
    names = []
    for piece in fragment.replace("(", " ").replace(")", " ").split(","):
        token = piece.strip().split()
        if token:
            names.append(token[0])
    return names


def referenced_scripts(text: str, known: frozenset[str]) -> set[str]:
    """Script stems a test module imports, loads by file or runs as a subprocess."""

    found: set[str] = set()
    pending: list[str] = []
    for line in text.splitlines():
        if pending:
            pending.append(line)
            if ")" in line:
                found.update(name for name in _names(" ".join(pending)) if name in known)
                pending = []
            continue
        match = _FROM_SCRIPTS.match(line)
        if match:
            fragment = match.group(1)
            if "(" in fragment and ")" not in fragment:
                pending = [fragment]
            else:
                found.update(name for name in _names(fragment) if name in known)
            continue
        match = _FROM_SCRIPTS_MODULE.match(line) or _IMPORT_SCRIPTS_MODULE.match(line)
        if match:
            if match.group(1) in known:
                found.add(match.group(1))
            continue
        match = _IMPORT.match(line)
        if match:
            found.update(name for name in _names(match.group(1)) if name in known)
        match = _FROM_MODULE.match(line)
        if match and match.group(1) in known:
            found.add(match.group(1))
        for match in _SCRIPT_FILE.finditer(line):
            if match.group(1) in known:
                found.add(match.group(1))
    return found


def known_scripts(root: Path) -> frozenset[str]:
    names = {path.stem for path in (root / "scripts").glob("*.py")}
    names.add("conker")
    return frozenset(names)


def select_modules(root: Path = ROOT) -> dict[str, str]:
    """Map each selected test module to the reason it belongs to the subset."""

    known = known_scripts(root)
    selected: dict[str, str] = {}
    for path in sorted((root / "tests").glob("test_*.py")):
        stem = path.stem
        references = referenced_scripts(path.read_text(encoding="utf-8"), known)
        matching = sorted(references & MATCHING_SCRIPTS)
        asset = sorted(name for name in references if name.startswith(ASSET_SCRIPT_PREFIXES))
        if stem in ALWAYS_SELECTED_MODULES:
            selected[stem] = "allowlisted"
        elif matching and not asset:
            selected[stem] = "references " + ", ".join(matching)
    return selected


def run_modules(arguments: list[str]) -> None:
    """Run test modules as ``unittest discover -s tests`` would import them."""

    import unittest

    tests = str(ROOT / "tests")
    sys.path[:] = [tests, str(ROOT)] + [entry for entry in sys.path[1:] if entry not in (tests, str(ROOT))]
    os.chdir(ROOT)
    unittest.main(module=None, argv=["python3 -m unittest", *arguments])


def parse_args(argv: list[str] | None = None) -> tuple[argparse.Namespace, list[str]]:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    subparsers = parser.add_subparsers(dest="command", required=True)
    classify = subparsers.add_parser("classify", help="print c-only/full and the reason")
    classify.add_argument("--base", help="base branch (default: CONKER_BASE_BRANCH, origin/main, main)")
    classify.add_argument("--root", type=Path, default=ROOT, help=argparse.SUPPRESS)
    modules = subparsers.add_parser("modules", help="print the selected test modules")
    modules.add_argument("--explain", action="store_true", help="show why each module is selected")
    modules.add_argument("--root", type=Path, default=ROOT, help=argparse.SUPPRESS)
    subparsers.add_parser("run", help="run the named test modules (unittest options first)")
    if argv is None:
        argv = sys.argv[1:]
    if argv and argv[0] == "run":
        return parser.parse_args(argv[:1]), argv[1:]
    return parser.parse_args(argv), []


def main() -> int:
    args, rest = parse_args()
    if args.command == "classify":
        try:
            classification = classify_repository(args.root, args.base)
        except subprocess.CalledProcessError as error:
            print(f"error: git failed: {error.stderr.strip() or error}", file=sys.stderr)
            return 2
        print(classification.kind)
        print(classification.reason)
        return 0
    if args.command == "modules":
        for name, reason in select_modules(args.root).items():
            print(f"{name}\t{reason}" if args.explain else name)
        return 0
    run_modules(rest)
    return 0


if __name__ == "__main__":
    sys.exit(main())
