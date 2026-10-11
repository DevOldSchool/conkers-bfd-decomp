#!/usr/bin/env python3
"""Collapse runs of per-asset linker inputs into a few partially linked groups.

Splat names every asset object in the ROM linker script. GNU ld resolves each
named input with a linear search over all inputs, so ~12k asset statements make
the final link quadratic (minutes of CPU). Consecutive `<asset>.o(.data);`
statements inside one output section are replaced by a single group object
that `ld -r` builds from the same objects in the same order. Binary asset
sections have alignment 1, so inside a SUBALIGN(1) output section the linked
bytes are unchanged. Other sections keep their statements.
"""
from __future__ import annotations

import argparse
from pathlib import Path
import re
import shlex
import subprocess
import sys

from build_files import write_if_changed

ASSET_STATEMENT = re.compile(r'^(\s*)(build/[^\s()]+/assets/[^\s()]+\.o)\(\.data\);$')
SECTION_START = re.compile(r'^\s*(\.[A-Za-z0-9_.]+)\s.*:\s*AT\(.*?(SUBALIGN\((\d+)\))?\s*$')
# A run shorter than this gains nothing from an extra partial link.
MINIMUM_GROUP = 8


def group_script(script: str, group_dir: str) -> tuple[str, dict[str, list[str]]]:
    lines = script.splitlines(keepends=True)
    output: list[str] = []
    groups: dict[str, list[str]] = {}
    section = 'none'
    groupable = False
    run: list[str] = []
    indent = ''
    counts: dict[str, int] = {}

    def flush() -> None:
        nonlocal run
        if groupable and len(run) >= MINIMUM_GROUP:
            stem = section.lstrip('.')
            name = f'{group_dir}/{stem}-{counts.get(stem, 0)}.o'
            counts[stem] = counts.get(stem, 0) + 1
            groups[name] = run
            output.append(f'{indent}{name}(.data);\n')
        else:
            output.extend(f'{indent}{path}(.data);\n' for path in run)
        run = []

    for line in lines:
        match = ASSET_STATEMENT.match(line.rstrip('\n'))
        if match:
            if not run:
                indent = match.group(1)
            run.append(match.group(2))
            continue
        if run:
            flush()
        start = SECTION_START.match(line)
        if start:
            section = start.group(1)
            groupable = start.group(3) == '1'
        output.append(line)
    if run:
        flush()
    return ''.join(output), groups


def build_group(linker: str, name: Path, members: list[str]) -> bool:
    """Partially link one group when its membership or any member changed."""
    membership = name.with_suffix('.members')
    listed = '\n'.join(members) + '\n'
    try:
        current = (membership.read_text() == listed
                   and name.stat().st_mtime_ns >= max(Path(m).stat().st_mtime_ns for m in members))
    except FileNotFoundError:
        current = False
    if current:
        return False
    name.parent.mkdir(parents=True, exist_ok=True)
    temporary = name.with_name(name.name + '.tmp')
    responses = name.with_name(name.name + '.rsp')
    responses.write_text(listed)
    subprocess.run([*shlex.split(linker), '-r', '-m', 'elf32btsmip', '-o', str(temporary), f'@{responses}'], check=True)
    temporary.replace(name)
    write_if_changed(membership, listed.encode())
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('script', type=Path, help='splat linker script')
    parser.add_argument('--output', type=Path, required=True, help='grouped linker script')
    parser.add_argument('--group-dir', type=Path, required=True, help='directory for group objects')
    parser.add_argument('--inputs', type=Path, required=True,
                        help='whitespace-separated object inputs of the full link')
    parser.add_argument('--responses', type=Path, required=True,
                        help='ld response file receiving the grouped link inputs')
    parser.add_argument('--linker', default='mips-linux-gnu-ld', help='linker command (shell words)')
    args = parser.parse_args()
    grouped, groups = group_script(args.script.read_text(), args.group_dir.as_posix().rstrip('/'))
    inputs = args.inputs.read_text().split()
    available = set(inputs)
    grouped_members = {member for members in groups.values() for member in members}
    missing = sorted(grouped_members - available)
    if missing:
        raise SystemExit(f'link_groups: linker script names objects outside the link: {missing[:5]}')
    rebuilt = sum(build_group(args.linker, Path(name), members) for name, members in groups.items())
    write_if_changed(args.output, grouped.encode())
    write_if_changed(args.responses, ('\n'.join(
        [path for path in inputs if path not in grouped_members] + list(groups)) + '\n').encode())
    print(f'link_groups: {len(grouped_members)} asset inputs in {len(groups)} groups '
          f'({rebuilt} relinked)', file=sys.stderr)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
