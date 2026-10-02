#!/usr/bin/env python3
"""List C files mapped into an overlay or a named full-ROM profile segment."""

from __future__ import annotations

import argparse

import yaml

import project_state


def mapped_sources(profile: str, *, overlay: str | None = None,
                   profile_segment: str | None = None) -> list[str]:
    if overlay == "game":
        entries = project_state.mapped_subsegments(profile, overlay)
        return [f"src/{name}.c" for _, kind, name in entries if kind == "c" and name]

    # Full-ROM profiles contain multiple executable images. Select the named
    # segment explicitly; debugger source units are separate from main units.
    segment_name = profile_segment if profile_segment is not None else overlay
    path = project_state.ROOT / "config/profiles" / f"{profile}.yaml"
    configuration = yaml.safe_load(path.read_text(encoding="utf-8"))
    sources = []
    for segment in configuration["segments"]:
        if not isinstance(segment, dict) or segment.get("name") != segment_name:
            continue
        for entry in segment.get("subsegments", []):
            if isinstance(entry, dict):
                kind, name = entry.get("type"), entry.get("name")
            else:
                kind = entry[1]
                name = entry[2] if len(entry) > 2 else None
            if kind == "c" and name:
                sources.append(f"src/{name}.c")
    return sources


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    selection = parser.add_mutually_exclusive_group(required=True)
    selection.add_argument("--overlay", choices=project_state.OVERLAYS)
    selection.add_argument(
        "--profile-segment",
        help="named full-ROM segment; does not register a matching overlay",
    )
    parser.add_argument("--profile", choices=project_state.KNOWN_REGIONS, required=True)
    arguments = parser.parse_args()
    print(" ".join(mapped_sources(arguments.profile, overlay=arguments.overlay,
                                 profile_segment=arguments.profile_segment)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
