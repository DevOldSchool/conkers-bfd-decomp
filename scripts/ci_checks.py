#!/usr/bin/env python3
"""ROM-free PR hygiene and active-C compilation checks (not match evidence)."""
from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path, PurePosixPath

import compile_c

ROOT = Path(__file__).resolve().parent.parent
GLOBAL_ASM = re.compile(r"^[ \t]*#pragma[ \t]+GLOBAL_ASM\([^\r\n]*\)[ \t]*\r?$", re.M)
GENERATED_ROOTS = {"roms", "asm", "assets", "build", "expected", "reference", ".conker", ".private-rom-assets", "private-work", "private-assets"}
ROM_MAGIC = {bytes.fromhex(x) for x in ("80371240", "37804012", "40123780")}


def forbidden_path(name: str) -> bool:
    if name == "roms/.gitkeep":
        return False
    path = PurePosixPath(name)
    return (path.parts[0] in GENERATED_ROOTS or path.name.lower().startswith("baserom.")
            or path.suffix.lower() in {".z64", ".n64", ".v64", ".o", ".obj", ".elf", ".a"})


def tracked_paths(root: Path) -> list[str]:
    return [p for p in subprocess.check_output(["git", "ls-files", "-z"], cwd=root).decode().split("\0") if p]


def hygiene(root: Path, base: str, head: str) -> None:
    def resolve(ref: str) -> str:
        return subprocess.check_output(
            ["git", "rev-parse", "--verify", "--end-of-options", ref + "^{commit}"], cwd=root, text=True
        ).strip()
    before, after = resolve(base), resolve(head)
    subprocess.run(["git", "-c", "core.whitespace=cr-at-eol", "diff", "--check", before, after, "--"], cwd=root, check=True)
    rejected = []
    for name in tracked_paths(root):
        path = root / name
        if forbidden_path(name) or (name == "roms/.gitkeep" and path.read_bytes() not in {b"", b"\n"}):
            rejected.append(name)
        elif path.is_file() and not path.is_symlink():
            with path.open("rb") as stream:
                if stream.read(4) in ROM_MAGIC:
                    rejected.append(name)
    if rejected:
        raise ValueError("Forbidden generated/binary inputs: " + ", ".join(repr(p) for p in rejected))
    print("PR whitespace and tracked-file hygiene passed.")


def compile_active(root: Path, source_list: Path | None = None) -> None:
    paths = tracked_paths(root) if source_list is None else source_list.read_text().split("\0")
    sources = [p for p in paths if p.startswith("src/") and p.endswith(".c")]
    output = root / "build" / "ci-compile"
    for name in sources:
        source = root / name
        if ".." in PurePosixPath(name).parts or not source.resolve().is_relative_to((root / "src").resolve()) or source.is_symlink():
            raise ValueError(f"Source symlink is unsupported: {name}")
        temporary = output / name
        temporary.parent.mkdir(parents=True, exist_ok=True)
        temporary.write_text(GLOBAL_ASM.sub("", source.read_text()), encoding="utf-8")
        command = [str(compile_c.IDO_CC), *compile_c.compiler_flags("us"),
                   "-I", str(source.parent), "-o", str(temporary.with_suffix(".o")), str(temporary)]
        print(f"Compiling active US C: {name}", flush=True)
        subprocess.run(command, cwd=root, check=True)
    if not sources:
        raise ValueError("No tracked C source units found")
    print(f"Compiled {len(sources)} source units; GLOBAL_ASM bodies and disabled candidates were not compiled.")
    print("Compile-only success is not full-span matching or link verification.")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    check = commands.add_parser("hygiene")
    check.add_argument("--base", required=True)
    check.add_argument("--head", default="HEAD")
    compile_parser = commands.add_parser("compile")
    compile_parser.add_argument("--source-list", type=Path, help="NUL-separated git source list prepared outside the container")
    args = parser.parse_args()
    if args.command == "hygiene":
        hygiene(ROOT, args.base, args.head)
    else:
        compile_active(ROOT, args.source_list)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
