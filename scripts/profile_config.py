"""Load canonical profiles with file-backed binary asset subsegment lists.

Only group subsegments may use ``{include: relative/path.yaml}``. Fragments
contain plain binary rows, never code mappings or further includes, so source
integration can keep editing the executable mappings in the root profile.
"""
from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import textwrap

import yaml


def _yaml(path: Path, source: str, *, compose: bool = False):
    """Keep YAML diagnostics local to the input, without parser tracebacks."""
    try:
        return yaml.compose(source) if compose else yaml.safe_load(source)
    except yaml.YAMLError as error:
        mark = getattr(error, "problem_mark", None)
        location = f":{mark.line + 1}:{mark.column + 1}" if mark else ""
        problem = getattr(error, "problem", None) or str(error)
        raise ValueError(f"{path}{location}: {' '.join(problem.split())}") from error


def _read(path: Path) -> tuple[dict, list[Path]]:
    path = path.resolve()
    profile = _yaml(path, path.read_text(encoding="utf-8"))
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
                or ".." in Path(name).parts or Path(name).suffix != ".yaml"):
            raise ValueError(f"{path}: include must be a relative .yaml path below the profile directory")
        fragment = (path.parent / name).resolve()
        if not fragment.is_relative_to(path.parent):
            raise ValueError(f"{path}: include escapes the profile directory: {name}")
        if fragment in dependencies:
            raise ValueError(f"{path}: repeated or self-referencing include: {name}")
        rows = _yaml(fragment, fragment.read_text(encoding="utf-8"))
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


def _field(node: yaml.MappingNode, name: str):
    if isinstance(node, yaml.MappingNode):
        for key, value in node.value:
            if key.value == name:
                return key, value
    raise ValueError(f"missing required mapping field: {name}")


def render_profile(path: Path, target_path: str, *, reference: bool = False) -> str:
    """Expand asset lists and replace one scalar without reformatting the map.

    Node marks locate values; YAML, rather than a textual placeholder replace,
    determines the ROM path's boundaries. A final structural comparison checks
    the splice against the shared loader before anything is written.
    """
    source = path.read_text(encoding="utf-8")
    expected = _yaml(path, source) if reference else load_profile(path)
    root = _yaml(path, source, compose=True)
    try:
        _, options = _field(root, "options")
        _, target = _field(options, "target_path")
    except ValueError as error:
        raise ValueError(f"{path}: missing or invalid options.target_path; expected __ROM_PATH__") from error
    if not isinstance(target, yaml.ScalarNode) or target.value != "__ROM_PATH__":
        raise ValueError(f"{path}: target_path must be __ROM_PATH__")
    expected["options"]["target_path"] = target_path
    edits = [(target.start_mark.index, target.end_mark.index, json.dumps(target_path))]
    if not reference:
        _, segments = _field(root, "segments")
        for segment in segments.value:
            if not isinstance(segment, yaml.MappingNode):
                continue
            fields = {key.value: (key, value) for key, value in segment.value}
            if "subsegments" not in fields:
                continue
            key, value = fields["subsegments"]
            if not isinstance(value, yaml.MappingNode):
                continue
            _, include = _field(value, "include")
            fragment = textwrap.dedent((path.parent / include.value).read_text(encoding="utf-8"))
            indent = " " * (key.start_mark.column + 2)
            # Retain comments attached to the include directive as well as all
            # original root/fragment comments, hexadecimal values and row styles.
            comments = [line.strip() for line in source[key.start_mark.index:include.start_mark.index].splitlines()
                        if line.lstrip().startswith("#")]
            suffix = source[include.end_mark.index:].partition("\n")[0]
            if not value.flow_style and include.end_mark.column and suffix.lstrip().startswith("#"):
                comments.append(suffix.strip())
            body = "\n".join(comments + fragment.rstrip("\n").splitlines())
            replacement = "subsegments:\n" + textwrap.indent(body, indent) + "\n"
            end = value.end_mark.index
            if not value.flow_style:
                # Mapping end marks include comments/indentation before the next
                # segment. Replace only through the include scalar's own line.
                end = include.end_mark.index
                if include.end_mark.column:
                    newline = source.find("\n", end)
                    end = len(source) if newline == -1 else newline + 1
            edits.append((key.start_mark.index, end, replacement))
    for start, end, replacement in sorted(edits, reverse=True):
        source = source[:start] + replacement + source[end:]
    if yaml.safe_load(source) != expected:
        raise ValueError(f"{path}: rendered profile differs from expanded structure")
    return source


def profile_sources(configuration: dict, segment_name: str) -> list[str]:
    """Read executable sources without importing the progress tooling."""
    sources = []
    for segment in configuration["segments"]:
        if not isinstance(segment, dict) or segment.get("name") != segment_name:
            continue
        for entry in segment.get("subsegments", []):
            if isinstance(entry, dict):
                kind, name = entry.get("type"), entry.get("name")
            else:
                kind = entry[1]
                name = entry[2] if len(entry) > 2 else None
            if kind == "c" and name:
                sources.append(f"src/{name}.c")
    return sources


def make_assets(path: Path, *, relative_to: Path | None = None) -> list[str]:
    """Plan inputs in one parse; dependencies are absolute unless a base is given."""
    try:
        from scripts import audio_boundaries, font_splits, mp3_bank
    except ModuleNotFoundError:
        import audio_boundaries
        import font_splits
        import mp3_bank

    profile, dependencies = _read(path)
    tokens = ["dep=" + (str(p) if relative_to is None else os.path.relpath(p, relative_to))
              for p in dependencies]
    fonts, _ = font_splits.layout_bins(path, configuration=profile)
    _, _, audio = audio_boundaries.bank_layout(path, configuration=profile)
    mp3 = mp3_bank.layout_bins(path, configuration=profile)
    for label, rows in (("font", fonts), ("audio", audio), ("mp3", mp3)):
        tokens.extend(f"{label}=assets/{name}.bin" for _, name in rows)
    for segment in ("main", "debugger"):
        tokens.extend("source=" + name for name in
                      profile_sources(profile, segment))
    return tokens


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("dependencies", "make-assets"))
    parser.add_argument("profile", type=Path)
    args = parser.parse_args()
    try:
        if args.action == "make-assets":
            names = make_assets(args.profile, relative_to=Path.cwd())
        else:
            paths = profile_dependencies(args.profile)
            names = [os.path.relpath(path, Path.cwd()) for path in paths]
    except (OSError, ValueError) as error:
        parser.error(str(error))
    # Make consumes whitespace-separated prerequisites; fail rather than split
    # a path into unrelated inputs. Repository profile paths use plain names.
    if any(any(c.isspace() or c in "#$:%\\" for c in name) for name in names):
        parser.error("profile dependency paths must be safe Make prerequisites")
    print(" ".join(names))


if __name__ == "__main__":
    main()
