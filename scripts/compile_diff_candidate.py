#!/usr/bin/env python3
"""Rebuild one focused diff candidate for asm-differ watch mode."""

from __future__ import annotations

import argparse
from pathlib import Path

import diff


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profile", choices=("us", "eu"), required=True)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("target", type=Path)
    arguments = parser.parse_args()

    source = arguments.source
    if not source.is_absolute():
        source = diff.ROOT / source
    target = arguments.target
    if not target.is_absolute():
        target = diff.ROOT / target
    expected = diff.candidate_object(arguments.profile, source)
    if target != expected:
        parser.error(
            f"unexpected candidate target {target}; expected {expected}"
        )
    diff.compile_candidate(arguments.profile, source)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
