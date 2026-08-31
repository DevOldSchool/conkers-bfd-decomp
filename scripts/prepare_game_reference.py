#!/usr/bin/env python3
"""Materialize a profile's game-code reference map with a local payload."""

from __future__ import annotations

import argparse
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parent.parent
CODE_SUBSEGMENT = re.compile(
    r"^(?P<indent>\s*)-\s*\[(?P<offset>0x[0-9A-Fa-f]+),\s*c(?:,\s*[^\]]+)?\]\s*$",
    re.MULTILINE,
)


def raw_reference_map(content: str) -> str:
    """Make every integrated C range a raw-assembly reference range."""

    return CODE_SUBSEGMENT.sub(
        lambda match: f"{match.group('indent')}- [{match.group('offset')}, asm]",
        content,
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("profile", choices=("us", "eu"))
    args = parser.parse_args()
    template_path = ROOT / "config" / "game" / f"{args.profile}.yaml"
    output = ROOT / "build" / "config" / f"game-reference.{args.profile}.yaml"
    template = template_path.read_text(encoding="utf-8")
    content = template.replace("__GAME_CODE_PATH__", f"build/game-reference/{args.profile}/game.code.bin")
    if content == template:
        raise RuntimeError("game reference template is missing __GAME_CODE_PATH__")
    content = raw_reference_map(content)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(content, encoding="utf-8")
    print(f"Prepared {output.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
