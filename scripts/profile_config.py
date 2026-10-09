"""Load canonical profiles with file-backed binary asset subsegment lists.

Only group subsegments may use ``{include: relative/path.yaml}``. Fragments
contain plain binary rows, never code mappings or further includes, so source
integration can keep editing the executable mappings in the root profile.
"""
from __future__ import annotations

import argparse
from pathlib import Path

import yaml


def _read(path: Path) -> tuple[dict, list[Path]]:
    path = path.resolve()
    profile = yaml.safe_load(path.read_text(encoding="utf-8"))
    if not isinstance(profile, dict) or not isinstance(profile.get("segments"), list):
        raise ValueError(f"{path}: expected a profile with a segments list")
    dependencies = [path]
    for segment in profile["segments"]:
        if not isinstance(segment, dict):
            continue
        reference = segment.get("subsegments")
        if not isinstance(reference, dict):
            continue
        if segment.get("type") != "group" or set(reference) != {"include"}:
            raise ValueError(f"{path}: only asset groups may include a subsegment list")
        name = reference["include"]
        if (not isinstance(name, str) or not name or Path(name).is_absolute()
                or ".." in Path(name).parts):
            raise ValueError(f"{path}: include must be a relative path below the profile directory")
        fragment = (path.parent / name).resolve()
        if not fragment.is_relative_to(path.parent):
            raise ValueError(f"{path}: include escapes the profile directory: {name}")
        if fragment in dependencies:
            raise ValueError(f"{path}: repeated or self-referencing include: {name}")
        rows = yaml.safe_load(fragment.read_text(encoding="utf-8"))
        if not isinstance(rows, list) or not rows:
            raise ValueError(f"{fragment}: expected a nonempty binary subsegment list")
        for row in rows:
            if (not isinstance(row, list) or len(row) != 3
                    or type(row[0]) is not int or row[0] < 0 or row[1] != "bin"
                    or not isinstance(row[2], str) or not row[2]):
                raise ValueError(f"{fragment}: expected [ROM offset, bin, name] rows")
        segment["subsegments"] = rows
        dependencies.append(fragment)
    return profile, dependencies


def load_profile(path: Path) -> dict:
    """Return the same Splat structure as an inline profile, in original order."""
    return _read(path)[0]


def profile_dependencies(path: Path) -> list[Path]:
    """Return the root and all included files, validating the same input graph."""
    return _read(path)[1]


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("dependencies",))
    parser.add_argument("profile", type=Path)
    args = parser.parse_args()
    paths = profile_dependencies(args.profile)
    # Make consumes whitespace-separated prerequisites; fail rather than split
    # a path into unrelated inputs. Repository profile paths use plain names.
    names = [str(path.relative_to(Path.cwd().resolve())) for path in paths]
    if any(any(c.isspace() or c in "#$:%\\" for c in name) for name in names):
        parser.error("profile dependency paths must be safe Make prerequisites")
    print(" ".join(names))


if __name__ == "__main__":
    main()
