#!/usr/bin/env python3
"""Recover parser context with the same preprocessor and flags as the US build."""

from __future__ import annotations

import argparse
import json
import re
import subprocess
from pathlib import Path

import call_signatures
import compile_c

ROOT = Path(__file__).resolve().parent.parent
LINE_MARKER = re.compile(r'^\s*#\s*\d+\s+"(?P<filename>[^"\n]+)"(?:\s+\d+)*\s*$')
HEADER_MARKER = 'CONKER_M2C_HEADER_DECLARATIONS'
HEADER_DECLARATIONS = re.compile(r'/\* ' + HEADER_MARKER + r': (.*) \*/')
ASM_PRAGMA = re.compile(r'^\s*#pragma\s+GLOBAL_ASM\("[^"\n]+"\)\s*$')
INTRINSICS = r'(?:sqrtf|fabsf)(?:\s*,\s*(?:sqrtf|fabsf))*'
INTRINSIC_PRAGMA = re.compile(
    rf'^\s*(?:#pragma\s+intrinsic\s*\(\s*{INTRINSICS}\s*\)'
    rf'|__pragma\s*\(\s*1\s*,\s*{INTRINSICS}\s*\)\s*;)\s*$'
)


def header_declarations(context: str) -> tuple[str, ...]:
    """Read generated header provenance, retaining nothing on malformed input."""
    markers = [line.strip() for line in context.splitlines() if HEADER_MARKER in line]
    if len(markers) != 1:
        return ()
    match = HEADER_DECLARATIONS.fullmatch(markers[0])
    if match is None:
        return ()
    try:
        declarations = json.loads(match[1])
    except (TypeError, ValueError):
        return ()
    if not isinstance(declarations, list):
        return ()
    seen = set()
    for declaration in declarations:
        if (not isinstance(declaration, str)
                or any(part in declaration for part in ('\n', '\r', '/*', '*/'))):
            return ()
        signatures = call_signatures.source_signatures(declaration)
        if len(signatures) != 1:
            return ()
        symbol, choices = next(iter(signatures.items()))
        if symbol in seen or len(choices) != 1 or None in choices:
            return ()
        signature = next(iter(choices))
        if signature.declaration(symbol) != declaration:
            return ()
        seen.add(symbol)
    return tuple(declarations)


def clean_context(text: str) -> str:
    """Strip known metadata and retain proven initial-header declarations.

    The compiler already selected active branches. Filename markers distinguish
    initial (including nested) headers from source C; after source code starts,
    later includes cannot establish visibility at an earlier candidate position.
    Already-cleaned contexts retain their generated marker without regeneration.
    """
    lines = []
    header_lines = []
    in_header = False
    initial_headers = True
    for line in text.splitlines():
        marker = LINE_MARKER.fullmatch(line)
        if marker is not None:
            in_header = Path(marker['filename']).suffix == '.h'
            continue
        if ASM_PRAGMA.fullmatch(line):
            if not in_header:
                initial_headers = False
            continue
        if INTRINSIC_PRAGMA.fullmatch(line):
            continue
        if line.lstrip().startswith(('#', '__pragma')):
            raise ValueError(f'unsupported preprocessed directive: {line.strip()}')
        lines.append(line)
        if initial_headers and line.strip():
            if in_header:
                header_lines.append(line)
            else:
                initial_headers = False
    signatures = call_signatures.source_signatures('\n'.join(header_lines))
    declarations = [next(iter(choices)).declaration(symbol)
                    for symbol, choices in sorted(signatures.items())
                    if len(choices) == 1 and None not in choices]
    if declarations:
        lines.append(f'/* {HEADER_MARKER}: {json.dumps(declarations)} */')
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
