#!/usr/bin/env python3
"""Translate spimdisasm's IDO O32 FPR aliases for GNU as.

The reference assembly stays exactly as generated.  This helper writes a
throwaway copy for the GNU-binutils bootstrap build, whose assembler only
recognises numeric FPR names (for example ``$f20`` rather than ``$fs0``).
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path


IDO_O32_FPRS = {
    "fv0": 0,
    "fv0f": 1,
    "fv1": 2,
    "fv1f": 3,
    "ft0": 4,
    "ft0f": 5,
    "ft1": 6,
    "ft1f": 7,
    "ft2": 8,
    "ft2f": 9,
    "ft3": 10,
    "ft3f": 11,
    "fa0": 12,
    "fa0f": 13,
    "fa1": 14,
    "fa1f": 15,
    "ft4": 16,
    "ft4f": 17,
    "ft5": 18,
    "ft5f": 19,
    "fs0": 20,
    "fs0f": 21,
    "fs1": 22,
    "fs1f": 23,
    "fs2": 24,
    "fs2f": 25,
    "fs3": 26,
    "fs3f": 27,
    "fs4": 28,
    "fs4f": 29,
    "fs5": 30,
    "fs5f": 31,
}

ALIAS_PATTERN = re.compile(
    r"\$(" + "|".join(sorted(IDO_O32_FPRS, key=len, reverse=True)) + r")\b"
)


def normalize(source: str) -> str:
    """Return *source* with IDO-only floating-point aliases replaced."""

    return ALIAS_PATTERN.sub(lambda match: f"$f{IDO_O32_FPRS[match.group(1)]}", source)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    arguments = parser.parse_args()

    arguments.output.parent.mkdir(parents=True, exist_ok=True)
    arguments.output.write_text(normalize(arguments.input.read_text(encoding="utf-8")), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
