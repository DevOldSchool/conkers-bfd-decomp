#!/usr/bin/env python3
"""Relocate evidence and its tracked references without changing project state."""

from __future__ import annotations

import argparse
import json
from pathlib import Path, PurePosixPath
import posixpath
import re
import subprocess


ROOT = Path(__file__).resolve().parent.parent
# Inline Markdown destinations (including images) and reference-style links.
LINK = re.compile(r"(?<=\]\()([^\s)]+)|(?m:^\[[^\]\n]+\]:\s*)([^\s]+)")


def tracked_files(root: Path) -> list[str]:
    return subprocess.check_output(
        ["git", "-c", "core.fsmonitor=false", "ls-files", "-z"], cwd=root
    ).decode().rstrip("\0").split("\0")


def ignored_paths(root: Path, paths: list[str]) -> list[str]:
    result = subprocess.run(
        ["git", "check-ignore", "--no-index", "-z", "--stdin"], cwd=root,
        input="\0".join(paths) + "\0", capture_output=True, text=True,
    )
    if result.returncode not in (0, 1):
        raise ValueError(result.stderr.strip())
    return result.stdout.rstrip("\0").split("\0") if result.stdout else []


def validate_mapping(root: Path, mapping: dict[str, str], tracked: list[str]) -> None:
    if not isinstance(mapping, dict) or not mapping:
        raise ValueError("map must be a nonempty JSON object of old paths to new paths")
    if not all(isinstance(k, str) and isinstance(v, str) for k, v in mapping.items()):
        raise ValueError("map paths must be strings")
    if len(set(mapping.values())) != len(mapping):
        raise ValueError("duplicate destination")
    for old, new in mapping.items():
        for name in (old, new):
            path = PurePosixPath(name)
            if (not name.startswith("docs/evidence/") or str(path) != name
                    or ".." in path.parts or path.suffix not in {".md", ".json", ".patch"}
                    or any((root / parent).is_symlink() for parent in (path, *path.parents))):
                raise ValueError(f"unsafe evidence path: {name}")
        if old not in tracked or not (root / old).is_file():
            raise ValueError(f"source is not a tracked file: {old}")
        if (root / new).exists() or new in mapping:
            raise ValueError(f"destination already exists or overlaps a source: {new}")
    ignored = ignored_paths(root, list(mapping.values()))
    if ignored:
        raise ValueError(f"destinations would be ignored by Git: {', '.join(ignored)}")


def rewrite(content: str, old: str, new: str, mapping: dict[str, str]) -> str:
    if old.endswith(".md"):
        def link(match: re.Match) -> str:
            token = match[1] or match[2]
            target, marker, anchor = token.partition("#")
            if not target or target.startswith(("/", "<")) or re.match(r"[\w+.-]+:", target):
                return match[0]
            resolved = posixpath.normpath(posixpath.join(posixpath.dirname(old), target))
            destination = mapping.get(resolved, resolved)
            if old == new and destination == resolved:
                return match[0]
            replacement = posixpath.relpath(destination, posixpath.dirname(new)) + marker + anchor
            return match[0].replace(token, replacement, 1)
        content = LINK.sub(link, content)
    # Bound the token so a filename prefix cannot rewrite another filename.
    pattern = r"(?<![\w/.-])(?:" + "|".join(re.escape(p) for p in mapping) + r")(?![\w/-]|\.[\w])"
    return re.sub(pattern, lambda match: mapping[match[0]], content)


def relocate(root: Path, mapping: dict[str, str], *, apply: bool = False) -> tuple[int, int]:
    tracked = tracked_files(root)
    validate_mapping(root, mapping, tracked)
    originals: dict[str, bytes] = {}
    updates: dict[str, bytes] = {}
    for name in tracked:
        path = root / name
        if not path.is_file() or path.is_symlink():
            continue
        raw = path.read_bytes()
        if not name.endswith(".md") and b"docs/evidence/" not in raw and name not in mapping:
            continue
        if b"\0" in raw:
            continue
        try:
            content = raw.decode("utf-8")
        except UnicodeDecodeError:
            continue
        destination = mapping.get(name, name)
        updated = rewrite(content, name, destination, mapping).encode("utf-8")
        if name != destination or updated != raw:
            originals[name] = raw
            updates[destination] = updated
    if not set(mapping).issubset(originals):
        raise ValueError("all moved evidence must be UTF-8 text")
    if not apply:
        return len(mapping), len(updates)
    created_dirs: set[Path] = set()
    try:
        for name, raw in updates.items():
            parent = (root / name).parent
            while not parent.exists():
                created_dirs.add(parent)
                parent = parent.parent
            (root / name).parent.mkdir(parents=True, exist_ok=True)
            (root / name).write_bytes(raw)
        for name in mapping:
            (root / name).unlink()
    except BaseException:
        for name, raw in originals.items():
            (root / name).write_bytes(raw)
        for name in mapping.values():
            (root / name).unlink(missing_ok=True)
        for directory in sorted(created_dirs, key=lambda p: len(p.parts), reverse=True):
            directory.rmdir()
        raise
    return len(mapping), len(updates)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--map", type=Path, required=True,
                        help="JSON object mapping repository-relative old paths to new paths")
    parser.add_argument("--apply", action="store_true", help="apply after a dry-run review")
    args = parser.parse_args()
    try:
        moves, updates = relocate(ROOT, json.loads(args.map.read_text()), apply=args.apply)
    except (OSError, ValueError) as error:
        parser.exit(1, f"error: {error}\n")
    print(f"{'Applied' if args.apply else 'Dry run:'} {moves} evidence moves; {updates} files affected.")


if __name__ == "__main__":
    main()
