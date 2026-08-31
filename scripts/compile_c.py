#!/usr/bin/env python3
"""Compile one project C source, embedding GLOBAL_ASM members when present."""

from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
IDO_CC = Path("/opt/ido/cc")
ASM_PROCESSOR = Path("/opt/tools/asm-processor/build.py")
ASM_PROCESSOR_PRELUDE = Path("/opt/tools/asm-processor/prelude.inc")
ASSEMBLER = "mips-linux-gnu-as"
GLOBAL_ASM_PRAGMA = re.compile(r"^[ \t]*#pragma[ \t]+GLOBAL_ASM\(", re.MULTILINE)


def compiler_flags(profile: str) -> list[str]:
    return [
        "-c",
        "-32",
        "-G",
        "0",
        "-Xfullwarn",
        "-Xcpluscomm",
        "-signed",
        "-nostdinc",
        "-non_shared",
        "-Wab,-r4300_mul",
        "-D_LANGUAGE_C",
        "-D_FINALROM",
        "-D_MIPS_SZLONG=32",
        f"-DPROFILE_{profile.upper()}=1",
        "-I",
        "include",
        "-O2",
        "-g3",
        "-mips2",
    ]


def compile_command(profile: str, source: Path, output: Path) -> list[str]:
    flags = compiler_flags(profile)
    if not GLOBAL_ASM_PRAGMA.search(source.read_text(encoding="utf-8")):
        return [str(IDO_CC), *flags, "-o", str(output), str(source)]
    return [
        "python3",
        str(ASM_PROCESSOR),
        "--input-enc",
        "utf-8",
        "--asm-prelude",
        str(ASM_PROCESSOR_PRELUDE),
        str(IDO_CC),
        "--",
        ASSEMBLER,
        "-W",
        "-EB",
        "-march=vr4300",
        "-mabi=32",
        "-I",
        "include",
        "--",
        *flags,
        "-o",
        str(output),
        str(source),
    ]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profile", choices=("us", "eu"), required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("source", type=Path)
    arguments = parser.parse_args()

    arguments.output.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        compile_command(arguments.profile, arguments.source, arguments.output),
        cwd=ROOT,
        check=True,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
