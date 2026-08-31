#!/usr/bin/env python3
"""Report the first byte and MIPS-word differences in a rebuilt ROM."""

from __future__ import annotations

import argparse
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent


def format_words(data: bytes) -> str:
    padded = data + b"\0" * ((4 - len(data) % 4) % 4)
    return " ".join(f"{int.from_bytes(padded[index:index + 4], 'big'):08X}" for index in range(0, len(padded), 4))


def first_difference(expected: bytes, actual: bytes) -> int | None:
    for offset, (target, current) in enumerate(zip(expected, actual)):
        if target != current:
            return offset
    if len(expected) != len(actual):
        return min(len(expected), len(actual))
    return None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=("us", "eu"))
    args = parser.parse_args()
    target = ROOT / "roms" / f"baserom.{args.profile}.z64"
    current = ROOT / "build" / args.profile / f"conker.{args.profile}.z64"
    if not target.is_file() or not current.is_file():
        parser.error(f"missing ROM input or build output; run ./conker build --profile {args.profile} first")
    expected_data = target.read_bytes()
    current_data = current.read_bytes()
    offset = first_difference(expected_data, current_data)
    if offset is None:
        print(f"{current.relative_to(ROOT)}: identical")
        return 0
    start = offset - offset % 4
    end = min(max(len(expected_data), len(current_data)), start + 16)
    print(f"First difference: ROM offset 0x{offset:08X}")
    print(f"TARGET : {format_words(expected_data[start:end])}")
    print(f"CURRENT: {format_words(current_data[start:end])}")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
