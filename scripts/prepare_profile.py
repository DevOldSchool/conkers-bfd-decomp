#!/usr/bin/env python3
"""Materialize a splat profile with an ignored, contributor-local ROM path."""

from __future__ import annotations

import argparse
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
OUTPUT_DIR = ROOT / "build" / "config"
ROM_PATHS = {
    "us": ROOT / "roms" / "baserom.us.z64",
    "eu": ROOT / "roms" / "baserom.eu.z64",
}


def yaml_string(value: str) -> str:
    return value.replace("\\", "\\\\").replace('"', '\\"')


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument(
        "--reference",
        action="store_true",
        help="materialize the immutable raw-assembly reference split",
    )
    args = parser.parse_args()

    kind = "reference" if args.reference else "profiles"
    template_path = ROOT / "config" / kind / f"{args.profile}.yaml"
    rom_path = ROM_PATHS[args.profile]
    if not rom_path.is_file():
        parser.error(f"configured {args.profile} ROM does not exist: {rom_path}; run ./conker setup")

    template = template_path.read_text(encoding="utf-8")
    output = template.replace("__ROM_PATH__", yaml_string(str(rom_path.relative_to(ROOT))))
    if output == template:
        parser.error(f"{template_path.relative_to(ROOT)} is missing the __ROM_PATH__ token")

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    output_path = (
        OUTPUT_DIR / "reference" / f"{args.profile}.yaml"
        if args.reference
        else OUTPUT_DIR / f"{args.profile}.yaml"
    )
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(output, encoding="utf-8")
    print(f"Prepared {output_path.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
