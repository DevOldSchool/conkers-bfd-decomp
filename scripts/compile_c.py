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
DEBUGGER_UI_INCLUDE = '#include "debugger-assets/ui.inc.c"'
GLOBAL_ASM_PRAGMA = re.compile(r"^[ \t]*#pragma[ \t]+GLOBAL_ASM\(", re.MULTILINE)
# A reviewed source unit whose original object provably used different flags
# names the pinned flags it drops, once, e.g. `/* CONKER_COMPILE_WITHOUT: -g3 */`.
# The directive travels with every focused, probe, layout and CI copy of the
# text, so each build of that unit agrees. Only the flags below may be dropped.
COMPILE_WITHOUT_DIRECTIVE = re.compile(
    r"^[ \t]*/\*[ \t]*CONKER_COMPILE_WITHOUT:[ \t]*([^*\n]*?)[ \t]*\*/[ \t]*$", re.MULTILINE
)
REMOVABLE_FLAGS = frozenset({"-g3"})


def dropped_flags(source_text: str) -> tuple[str, ...]:
    """Flags a source's CONKER_COMPILE_WITHOUT directive removes from the pinned set."""
    directives = COMPILE_WITHOUT_DIRECTIVE.findall(source_text)
    if not directives:
        return ()
    if len(directives) > 1:
        raise ValueError("a source may carry at most one CONKER_COMPILE_WITHOUT directive")
    flags = tuple(directives[0].split())
    unsupported = [flag for flag in flags if flag not in REMOVABLE_FLAGS]
    if not flags or unsupported:
        allowed = ", ".join(sorted(REMOVABLE_FLAGS))
        raise ValueError(
            f"CONKER_COMPILE_WITHOUT supports only {allowed}; got {directives[0]!r}"
        )
    return flags


def compiler_flags(profile: str, source_text: str | None = None) -> list[str]:
    flags = [
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
        "-I",
        "lib/ultralib/include",
        "-O2",
        "-g3",
        "-mips2",
    ]
    if source_text is not None:
        for flag in dropped_flags(source_text):
            flags.remove(flag)
    return flags


def compile_command(profile: str, source: Path, output: Path, *,
                    generated_dir: Path | None = None, source_text: str | None = None) -> list[str]:
    if source_text is None:
        source_text = source.read_text(encoding="utf-8")
    flags = compiler_flags(profile, source_text)
    if DEBUGGER_UI_INCLUDE in source_text:
        flags += ['-I', str(generated_dir or ROOT / 'build' / profile)]
    if not GLOBAL_ASM_PRAGMA.search(source_text):
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


def run_compile(profile: str, source: Path, output: Path, *,
                inputs_prepared: bool = False, generated_dir: Path | None = None, **kwargs):
    """Prepare local generated inputs explicitly, then execute the compiler."""
    source_text = source.read_text(encoding="utf-8")
    if not inputs_prepared and DEBUGGER_UI_INCLUDE in source_text:
        if profile != 'us':
            raise ValueError('debugger assets currently support US only')
        import debugger_assets
        debugger_assets.prepare(ROOT, output=(generated_dir or ROOT / 'build' / profile)
                                / 'debugger-assets/ui.inc.c')
    options = {'generated_dir': generated_dir} if generated_dir is not None else {}
    return subprocess.run(compile_command(profile, source, output, source_text=source_text, **options), **kwargs)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profile", choices=("us", "eu"), required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("source", type=Path)
    parser.add_argument("--inputs-prepared", action="store_true",
                        help="Caller already prepared all generated inputs (Make prerequisite).")
    parser.add_argument("--generated-dir", type=Path)
    arguments = parser.parse_args()

    arguments.output.parent.mkdir(parents=True, exist_ok=True)
    run_compile(arguments.profile, arguments.source, arguments.output,
        inputs_prepared=arguments.inputs_prepared, generated_dir=arguments.generated_dir,
        cwd=ROOT,
        check=True,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
