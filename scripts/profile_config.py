"""Load canonical profiles with file-backed binary asset subsegment lists.

Only group subsegments may use ``{include: relative/path.yaml}``. Fragments
contain plain binary rows, never code mappings or further includes, so source
integration can keep editing the executable mappings in the root profile.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import textwrap

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
                or ".." in Path(name).parts or Path(name).suffix != ".yaml"):
            raise ValueError(f"{path}: include must be a relative .yaml path below the profile directory")
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


def _field(node: yaml.MappingNode, name: str):
    return next((key, value) for key, value in node.value if key.value == name)


def render_profile(path: Path, target_path: str, *, reference: bool = False) -> str:
    """Expand asset lists and replace one scalar without reformatting the map.

    Node marks locate values; YAML, rather than a textual placeholder replace,
    determines the ROM path's boundaries. A final structural comparison checks
    the splice against the shared loader before anything is written.
    """
    source = path.read_text(encoding="utf-8")
    expected = yaml.safe_load(source) if reference else load_profile(path)
    root = yaml.compose(source)
    _, options = _field(root, "options")
    _, target = _field(options, "target_path")
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
            comments = [line.strip() for line in source[key.start_mark.index:value.end_mark.index].splitlines()
                        if line.lstrip().startswith("#")]
            suffix = source[include.end_mark.index:].partition("\n")[0]
            if suffix.lstrip().startswith("#"):
                comments.append(suffix.strip())
            body = "\n".join(comments + fragment.rstrip("\n").splitlines())
            replacement = "subsegments:\n" + textwrap.indent(body, indent) + "\n"
            if not value.flow_style:
                replacement += " " * value.end_mark.column
            edits.append((key.start_mark.index, value.end_mark.index, replacement))
    for start, end, replacement in sorted(edits, reverse=True):
        source = source[:start] + replacement + source[end:]
    if yaml.safe_load(source) != expected:
        raise ValueError(f"{path}: rendered profile differs from expanded structure")
    return source


def make_assets(path: Path) -> list[str]:
    """Plan dependencies, asset inputs and executable sources in one parse."""
    import audio_boundaries
    import font_splits
    import list_integrated_sources
    import mp3_bank

    profile, dependencies = _read(path)
    tokens = ["dep=" + str(p.relative_to(Path.cwd().resolve())) for p in dependencies]
    fonts, _ = font_splits.layout_bins(path, configuration=profile)
    _, _, audio = audio_boundaries.bank_layout(path, configuration=profile)
    mp3 = mp3_bank.layout_bins(path, configuration=profile)
    for label, rows in (("font", fonts), ("audio", audio), ("mp3", mp3)):
        tokens.extend(f"{label}=assets/{name}.bin" for _, name in rows)
    for segment in ("main", "debugger"):
        tokens.extend("source=" + name for name in
                      list_integrated_sources.profile_sources(profile, segment))
    return tokens


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("dependencies", "make-assets"))
    parser.add_argument("profile", type=Path)
    args = parser.parse_args()
    if args.action == "make-assets":
        names = make_assets(args.profile)
    else:
        paths = profile_dependencies(args.profile)
        names = [str(path.relative_to(Path.cwd().resolve())) for path in paths]
    # Make consumes whitespace-separated prerequisites; fail rather than split
    # a path into unrelated inputs. Repository profile paths use plain names.
    if any(any(c.isspace() or c in "#$:%\\" for c in name) for name in names):
        parser.error("profile dependency paths must be safe Make prerequisites")
    print(" ".join(names))


if __name__ == "__main__":
    main()
