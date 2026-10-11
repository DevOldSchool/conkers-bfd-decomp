#!/usr/bin/env python3
"""Write MIPS ELF objects byte-identical to `ld -r -b binary -m elf32btsmip`.

Spawning GNU ld once per asset dominates rebuilds under amd64 emulation; this
in-process writer reproduces the same five-section relocatable object exactly.
"""
from __future__ import annotations

import argparse
import os
from pathlib import Path
import re
import struct
import sys
import tempfile

_SHSTRTAB = b'\0.symtab\0.strtab\0.shstrtab\0.data\0'
_SYMBOL_UNSAFE = re.compile(rb'[^0-9A-Za-z]')
_BFD_HASH_SIZE = 4051


def _align(value: int, alignment: int) -> int:
    return (value + alignment - 1) & -alignment


def symbol_stem(relative_name: str) -> bytes:
    """Mangle a command-line input path the way BFD names binary symbols."""
    return b'_binary_' + _SYMBOL_UNSAFE.sub(b'_', os.fsencode(relative_name))


def _bfd_hash_bucket(name: bytes) -> int:
    """Bucket of `name` in BFD's default 4051-entry link hash table (64-bit host)."""
    value = 0
    mask = (1 << 64) - 1
    for character in name:
        value = (value + character + (character << 17)) & mask
        value ^= value >> 2
    value = (value + len(name) + (len(name) << 17)) & mask
    value ^= value >> 2
    return value % _BFD_HASH_SIZE


def binary_object(data: bytes, relative_name: str) -> bytes:
    """Return the object ld creates for `relative_name` containing `data`."""
    stem = symbol_stem(relative_name)
    # ld emits globals by hash-table traversal: ascending bucket, and within a
    # bucket the most recently entered (start, end, size) symbol first.
    entered = (stem + b'_start', stem + b'_end', stem + b'_size')
    names = tuple(sorted(entered, key=lambda name: (_bfd_hash_bucket(name), -entered.index(name))))
    strtab = b'\0' + b''.join(name + b'\0' for name in names)
    name_offsets = []
    offset = 1
    for name in names:
        name_offsets.append(offset)
        offset += len(name) + 1
    size = len(data)
    values = {entered[0]: (0, 1), entered[1]: (size, 1), entered[2]: (size, 0xFFF1)}
    symtab = b''.join([bytes(16), struct.pack('>IIIBBH', 0, 0, 0, 0x03, 0, 1)] + [
        struct.pack('>IIIBBH', offset, values[name][0], 0, 0x10, 0, values[name][1])
        for name, offset in zip(names, name_offsets)])
    data_offset = 0x34
    symtab_offset = _align(data_offset + size, 4)
    strtab_offset = symtab_offset + len(symtab)
    shstrtab_offset = strtab_offset + len(strtab)
    sections_offset = _align(shstrtab_offset + len(_SHSTRTAB), 4)
    header = b'\x7fELF\x01\x02\x01' + bytes(9) + struct.pack(
        '>HHIIIIIHHHHHH', 1, 8, 1, 0, 0, sections_offset, 0, 0x34, 0, 0, 40, 5, 4)
    sections = b''.join((
        bytes(40),
        struct.pack('>10I', 0x1B, 1, 3, 0, data_offset, size, 0, 0, 1, 0),
        struct.pack('>10I', 0x01, 2, 0, 0, symtab_offset, len(symtab), 3, 2, 4, 16),
        struct.pack('>10I', 0x09, 3, 0, 0, strtab_offset, len(strtab), 0, 0, 1, 0),
        struct.pack('>10I', 0x11, 3, 0, 0, shstrtab_offset, len(_SHSTRTAB), 0, 0, 1, 0),
    ))
    return b''.join((
        header, data, bytes(symtab_offset - data_offset - size), symtab, strtab,
        _SHSTRTAB, bytes(sections_offset - shstrtab_offset - len(_SHSTRTAB)), sections,
    ))


def write_if_changed(path: Path, content: bytes) -> bool:
    """Atomically replace `path` only when its bytes differ; return whether it changed."""
    try:
        if path.stat().st_size == len(content) and path.read_bytes() == content:
            return False
    except FileNotFoundError:
        pass
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary = tempfile.mkstemp(prefix=path.name + '.', suffix='.tmp', dir=path.parent)
    try:
        with os.fdopen(descriptor, 'wb') as stream:
            stream.write(content)
        os.replace(temporary, path)
    except BaseException:
        Path(temporary).unlink(missing_ok=True)
        raise
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, required=True,
                        help='directory that input names are relative to (ld\'s working directory)')
    parser.add_argument('--output-root', type=Path, required=True)
    parser.add_argument('--strip-prefix', default='',
                        help='input-name prefix omitted from output paths (symbols keep it)')
    parser.add_argument('names', nargs='*', help='input names relative to --root, ending in .bin')
    parser.add_argument('--names-from', type=Path, help='read further newline-separated names from a file')
    args = parser.parse_args()
    names = list(args.names)
    if args.names_from:
        names.extend(args.names_from.read_text().split())
    for name in names:
        if not name.endswith('.bin'):
            parser.error(f'{name}: expected a .bin input')
        source = args.root / name
        if not name.startswith(args.strip_prefix):
            parser.error(f'{name}: expected prefix {args.strip_prefix}')
        output = args.output_root / (name[len(args.strip_prefix):-len('.bin')] + '.o')
        try:
            if output.stat().st_mtime_ns >= source.stat().st_mtime_ns:
                continue
        except FileNotFoundError:
            pass
        try:
            if write_if_changed(output, binary_object(source.read_bytes(), name)):
                print(f'binary_object {source} -> {output}', file=sys.stderr)
            else:
                # Keep Make's view current without changing the object's bytes.
                os.utime(output)
        except OSError as error:
            print(f'binary_object: cannot write {output} from {source}: {error}', file=sys.stderr)
            return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
