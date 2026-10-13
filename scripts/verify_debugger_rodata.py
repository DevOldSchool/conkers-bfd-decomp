#!/usr/bin/env python3
"""Verify the allocated debugger image against the checksum-validated US ROM."""
from __future__ import annotations
import argparse
from pathlib import Path

from elf_sections import sections
import rom_span
import debugger_layout

ROOT = Path(__file__).resolve().parent.parent


def allocated_image(elf: bytes) -> bytes:
    """Require runtime bytes, not a non-allocated verification-only copy."""
    layout = debugger_layout.load(ROOT)
    extent = layout['rom_end'] - layout['rom_start']
    parsed = sections(elf, 2)
    if any(name.startswith('.debugger_rodata') for name in parsed):
        raise ValueError('obsolete external debugger rodata section')
    if '.debugger' not in parsed:
        raise ValueError('missing allocated debugger image')
    header, image = parsed['.debugger']
    if header[1] != 1 or header[2] != 7 or (header[3], header[5]) != (layout['vram'], extent):
        raise ValueError('incorrect allocated debugger image extent/type/flags')
    return image


def verify(elf: Path) -> None:
    image = allocated_image(elf.read_bytes())
    code, data, code_base, data_base, _ = rom_span.debugger_image(ROOT)
    if code_base != debugger_layout.load(ROOT)['vram'] or data_base != code_base + len(code):
        raise ValueError('debugger loader boundaries changed')
    expected = code + data
    if image != expected:
        raise ValueError('allocated debugger code/data differs from US ROM')
    print(f'debugger: {len(code)} code and {len(data)} allocated data bytes match US ROM')


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('elf', type=Path)
    args = parser.parse_args()
    try:
        verify(args.elf)
    except (ValueError, OSError) as error:
        parser.exit(1, f'error: {error}\n')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
