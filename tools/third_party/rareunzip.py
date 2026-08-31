#!/usr/bin/env python3
"""Decompress one Rare RZIP raw-deflate chunk."""

# Vendored from n64decomp/banjo-kazooie at 9db90a003fff15d13d29505d571aff2543b50383.
# The upstream project is CC0-1.0; see tools/third_party/README.md.

from __future__ import annotations

import argparse
import zlib
from pathlib import Path


def runzip_with_leftovers(data: bytes) -> tuple[bytes, bytes]:
    """Decompress a chunk and retain any bytes after its deflate stream."""

    if len(data) < 4:
        raise ValueError("RZIP chunk is shorter than its four-byte length header")
    decompressor = zlib.decompressobj(wbits=-15)
    result = decompressor.decompress(data[4:])
    return result, decompressor.unused_data


def runzip(data: bytes) -> bytes:
    """Decompress one chunk, ignoring any following bytes."""

    result, _ = runzip_with_leftovers(data)
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path, help="RZIP chunk, relative to the repository root")
    parser.add_argument("output", type=Path, help="decompressed output, relative to the repository root")
    args = parser.parse_args()

    data = args.input.read_bytes()
    # Some Rare game payloads prepend this two-byte wrapper before the RZIP header.
    if data[:2] == b"\x11\x72":
        data = data[2:]
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(runzip(data))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
