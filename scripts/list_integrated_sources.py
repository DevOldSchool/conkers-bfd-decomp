#!/usr/bin/env python3
"""List source units currently mapped into a selected build overlay."""

from __future__ import annotations

import argparse

import project_state


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--overlay", choices=project_state.OVERLAYS, required=True)
    parser.add_argument("--profile", choices=project_state.KNOWN_REGIONS, required=True)
    arguments = parser.parse_args()
    sources = [
        f"src/{name}.c"
        for _, kind, name in project_state.mapped_subsegments(arguments.profile, arguments.overlay)
        if kind == "c" and name is not None
    ]
    print(" ".join(sources))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
