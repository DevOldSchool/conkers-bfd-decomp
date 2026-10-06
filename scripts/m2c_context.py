#!/usr/bin/env python3
"""Recover parser context with the same preprocessor and flags as the US build."""

from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path

import compile_c

ROOT = Path(__file__).resolve().parent.parent
LINE_MARKER = re.compile(r'^\s*#\s*\d+\s+"[^"\n]+"(?:\s+\d+)*\s*$')
ASM_PRAGMA = re.compile(r'^\s*#pragma\s+GLOBAL_ASM\("[^"\n]+"\)\s*$')
INTRINSICS = r'(?:sqrtf|fabsf)(?:\s*,\s*(?:sqrtf|fabsf))*'
INTRINSIC_PRAGMA = re.compile(
    rf'^\s*(?:#pragma\s+intrinsic\s*\(\s*{INTRINSICS}\s*\)'
    rf'|__pragma\s*\(\s*1\s*,\s*{INTRINSICS}\s*\)\s*;)\s*$'
)


def clean_context(text: str) -> str:
    """Remove only understood metadata; unknown layout pragmas fail closed."""
    lines = []
    for line in text.splitlines():
        if LINE_MARKER.fullmatch(line) or ASM_PRAGMA.fullmatch(line) or INTRINSIC_PRAGMA.fullmatch(line):
            continue
        if line.lstrip().startswith(('#', '__pragma')):
            raise ValueError(f'unsupported preprocessed directive: {line.strip()}')
        lines.append(line)
    return '\n'.join(lines) + '\n'


def preprocess_source(profile: str, source: Path) -> str:
    source = source.resolve()
    relative = source.relative_to(ROOT.resolve())
    if not relative.parts or relative.parts[0] != 'src' or source.suffix != '.c':
        raise ValueError('m2c context requires a project src/*.c file')
    command = [str(compile_c.IDO_CC),
               *(flag for flag in compile_c.compiler_flags(profile) if flag != '-c'),
               '-E', str(relative)]
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, check=False)
    if result.returncode:
        raise ValueError(f'IDO preprocessing failed: {result.stderr.strip()}')
    return clean_context(result.stdout)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('profile', choices=('us', 'eu'))
    parser.add_argument('source', type=Path)
    args = parser.parse_args()
    try:
        print(preprocess_source(args.profile, args.source), end='')
    except (OSError, ValueError) as error:
        parser.exit(1, f'{error}\n')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
