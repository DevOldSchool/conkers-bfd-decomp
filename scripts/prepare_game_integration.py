#!/usr/bin/env python3
"""Materialize the active US game-overlay map for a byte-identical C build."""

from __future__ import annotations

from pathlib import Path
import re


ROOT = Path(__file__).resolve().parent.parent
TEMPLATE = ROOT / "config" / "game" / "us.yaml"
OUTPUT = ROOT / "build" / "config" / "game-integrated.us.yaml"
SUBSEGMENT_PATTERN = re.compile(
    r"^\s*-\s*\[(?:0x[0-9A-Fa-f]+),\s*(?P<kind>asm|hasm|c|lib|data)(?:,\s*[^\]]+)?\]\s*$"
)
DICT_SUBSEGMENT_PATTERN = re.compile(
    r"^\s*-\s*\{[^}]*\btype:\s*(?P<kind>asm|hasm|c|lib|data)\b[^}]*\}\s*$"
)


def match_subsegment(line: str) -> re.Match[str] | None:
    return SUBSEGMENT_PATTERN.match(line) or DICT_SUBSEGMENT_PATTERN.match(line)


def collapse_raw_assembly_boundaries(content: str) -> str:
    """Keep C/archive/data boundaries while coalescing navigation-only ASM ranges."""

    lines = content.splitlines()
    entry_indexes = [index for index, line in enumerate(lines) if match_subsegment(line)]
    if not entry_indexes:
        raise RuntimeError("game integration template has no code subsegments")
    keep: set[int] = set()
    previous_kind: str | None = None
    for position, index in enumerate(entry_indexes):
        match = match_subsegment(lines[index])
        assert match is not None
        kind = match.group("kind")
        if kind in {"c", "lib", "data"} or position == 0 or previous_kind in {"c", "lib", "data"}:
            keep.add(index)
        previous_kind = kind
    return "\n".join(line for index, line in enumerate(lines) if index not in entry_indexes or index in keep) + "\n"


def main() -> int:
    content = TEMPLATE.read_text(encoding="utf-8")
    replacements = {
        "name: Conker US game-code reference": "name: Conker US integrated game code",
        "basename: conker.game.us.reference": "basename: conker.game.us.integrated",
        'target_path: "__GAME_CODE_PATH__"': 'target_path: "build/game-integrated/us/game.code.bin"',
        "elf_path: build/game-reference/us/conker.game.us.elf": "elf_path: build/game-integrated/us/conker.game.us.integrated.elf",
        "asm_path: reference/game/us/asm": "asm_path: asm/game_integrated/us",
        "build_path: build/game-reference/us": "build_path: build/game-integrated/us",
        "ld_script_path: build/game-reference/us/conker.game.us.ld": "ld_script_path: build/game-integrated/us/conker.game.us.integrated.ld",
    }
    for original, replacement in replacements.items():
        if original not in content:
            raise RuntimeError(f"game integration template is missing: {original}")
        content = content.replace(original, replacement, 1)
    content = collapse_raw_assembly_boundaries(content)
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text(content, encoding="utf-8")
    print(f"Prepared {OUTPUT.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
