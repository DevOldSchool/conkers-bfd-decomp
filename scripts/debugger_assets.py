"""Reconstruct the debugger glyph atlas and UI strings from editable local inputs.

Only extraction reads the checked ROM. Repacking consumes a PGM atlas and JSON
strings; neither extracted content nor the generated C include is tracked.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path

from build_files import write_if_changed
import main_private_data
import debugger_layout

ROOT = Path(__file__).resolve().parent.parent
from debugger_asset_inputs import DIRECTORY, LEGACY_DIRECTORY, INPUTS, migrate

GENERATED = Path('build/us/debugger-assets/ui.inc.c')


def encode_atlas(pixels: bytes) -> bytes:
    if len(pixels) != 128 * 48 or any(p not in (0, 255) for p in pixels):
        raise ValueError('debugger atlas must be 128x48 monochrome pixels')
    rows = bytearray()
    for glyph in range(96):
        x, y = glyph % 16 * 8, glyph // 16 * 8
        for row in range(8):
            rows.append(sum((pixels[(y + row) * 128 + x + bit] != 0) << (7 - bit) for bit in range(8)))
    return bytes(rows)


def decode_atlas(data: bytes) -> bytes:
    if len(data) != 768:
        raise ValueError('debugger glyph extent must be 768 bytes')
    pixels = bytearray(128 * 48)
    for glyph in range(96):
        x, y = glyph % 16 * 8, glyph // 16 * 8
        for row in range(8):
            for bit in range(8):
                pixels[(y + row) * 128 + x + bit] = 255 if data[glyph * 8 + row] & (128 >> bit) else 0
    return bytes(pixels)


def extract(root: Path = ROOT) -> None:
    directory = root / DIRECTORY
    directory.mkdir(parents=True, exist_ok=True)
    if any((directory / name).exists() for name in INPUTS):
        raise ValueError('refusing to extract over existing or partial editable debugger inputs')
    rom = main_private_data.validated_rom(root)
    layout = debugger_layout.ui(root)
    origin = layout['origin']
    items = []
    for item in layout['strings']:
        address, end = int(item['start'], 0), int(item['payload_end'], 0)
        if layout['strings_start'] <= address < layout['end']:
            raw = rom[address - origin:end - origin]
            if not raw.endswith(b'\0') or b'\0' in raw[:-1]:
                raise ValueError('invalid debugger string extent')
            items.append({'address': address, 'text': raw[:-1].decode('ascii')})
    atlas = directory / 'glyphs.pgm'
    strings = directory / 'strings.json'
    # Never silently overwrite user edits or a partially existing input set.
    if not atlas.exists():
        atlas.write_bytes(b'P5\n128 48\n255\n' + decode_atlas(rom[layout['start'] - origin:layout['strings_start'] - origin]))
    if not strings.exists():
        strings.write_text(json.dumps(items, indent=2) + '\n')


def pack(root: Path = ROOT) -> tuple[bytes, list[tuple[int, bytes]]]:
    directory = root / DIRECTORY
    layout = debugger_layout.ui(root)
    pgm = (directory / 'glyphs.pgm').read_bytes()
    header = b'P5\n128 48\n255\n'
    if not pgm.startswith(header):
        raise ValueError('invalid debugger atlas PGM header')
    glyphs = encode_atlas(pgm[len(header):])
    items = json.loads((directory / 'strings.json').read_text())
    payload = bytearray(glyphs)
    strings = []
    cursor = layout['strings_start']
    for item in items:
        address = item['address']
        text = item['text'].encode('ascii')
        if address != cursor or b'\0' in text:
            raise ValueError('debugger strings must retain their reviewed addresses and NUL boundaries')
        text += b'\0'
        strings.append((address, text))
        payload.extend(text)
        padding = -len(text) % 4
        payload.extend(bytes(padding))
        cursor += len(text) + padding
    payload.extend(bytes(-len(payload) % 16))
    if len(payload) != layout['end'] - layout['start']:
        raise ValueError('debugger UI storage differs from its reviewed extent')
    return bytes(payload), strings


def ensure_inputs(root: Path) -> None:
    if not migrate(root):
        extract(root)


def prepare(root: Path = ROOT, *, output: Path | None = None) -> Path:
    ensure_inputs(root)
    layout = debugger_layout.ui(root)
    payload, strings = pack(root)
    lines = ['/* Generated from local editable debugger assets. Do not commit. */',
             f'const u8 D_{layout["start"]:08X}[768] = {{']
    for i in range(0, 768, 16):
        lines.append('    ' + ', '.join(f'0x{x:02X}' for x in payload[i:i + 16]) + ',')
    lines.append('};')
    for address, text in strings:
        # Numeric character initializers preserve arbitrary ASCII/control bytes.
        lines.append(f'const u8 D_{address:08X}[{len(text)}] = {{' + ', '.join(str(c) for c in text) + '};')
    path = output if output is not None else root / GENERATED
    path.parent.mkdir(parents=True, exist_ok=True)
    write_if_changed(path, ('\n'.join(lines) + '\n').encode())
    return path


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    print(prepare(output=args.output))
