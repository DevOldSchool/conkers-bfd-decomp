#!/usr/bin/env python3
"""Experimental objdiff comparison alongside the authoritative registered-span gate."""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import platform
import shutil
import struct
import subprocess
import sys
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def write_json(path: Path, value: object) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")


def install() -> Path:
    """Fetch an official release into the ignored cache, checking even cached bytes."""
    lock = json.loads((ROOT / "toolchain/tools.lock.json").read_text())["objdiff_cli"]
    system = {"Darwin": "macos", "Linux": "linux"}.get(platform.system())
    machine = {"arm64": "arm64", "aarch64": "arm64", "x86_64": "x86_64", "AMD64": "x86_64"}.get(platform.machine())
    if system == "linux" and machine == "arm64":
        machine = "aarch64"
    asset = f"objdiff-cli-{system}-{machine}"
    digest = lock["assets"].get(asset)
    if not digest:
        raise ValueError(f"unsupported objdiff host: {platform.system()} {platform.machine()}")
    destination = ROOT / "build/host-tools" / f"objdiff-{lock['version']}" / asset
    if destination.is_file() and hashlib.sha256(destination.read_bytes()).hexdigest() == digest:
        return destination
    destination.parent.mkdir(parents=True, exist_ok=True)
    url = f"{lock['repository']}/releases/download/{lock['version']}/{asset}"
    with tempfile.NamedTemporaryFile(dir=destination.parent, delete=False) as temporary:
        download = Path(temporary.name)
    try:
        subprocess.run(["curl", "--fail", "--location", "--silent", "--show-error",
                        "--connect-timeout", "15", "--max-time", "180", url,
                        "--output", str(download)], check=True)
        if hashlib.sha256(download.read_bytes()).hexdigest() != digest:
            raise ValueError(f"objdiff checksum mismatch for {asset}")
        download.chmod(0o755)
        os.replace(download, destination)
    finally:
        download.unlink(missing_ok=True)
    return destination


def bound_reference(data: bytes, symbol: str, size: int) -> bytes:
    """Set ELF symbol metadata in a COPY; leave section bytes and relocations intact.

    Raw assembler symbols may lack sizes. objdiff then infers a span through a
    neighboring return stub. Use exactly the same reviewed span as diff.py.
    Never resize a candidate symbol to hide missing or extra C instructions.
    """
    if size <= 0 or size % 4:
        raise ValueError("reference span must be a positive multiple of four")
    if len(data) < 52 or data[:6] != b"\x7fELF\x01\x02":
        raise ValueError("expected an ELF32 big-endian reference object")
    if struct.unpack_from(">HH", data, 16) != (1, 8):
        raise ValueError("expected a relocatable MIPS reference object")
    section_offset = struct.unpack_from(">I", data, 32)[0]
    entry_size, section_count = struct.unpack_from(">HH", data, 46)
    if entry_size != 40 or section_offset + section_count * entry_size > len(data):
        raise ValueError("invalid ELF section table")
    sections = [struct.unpack_from(">10I", data, section_offset + i * 40)
                for i in range(section_count)]
    matches = []
    for section in sections:
        if section[1] != 2:  # SHT_SYMTAB
            continue
        if section[9] != 16 or section[5] % 16 or section[6] >= len(sections):
            raise ValueError("invalid ELF symbol table")
        strings = sections[section[6]]
        if strings[4] + strings[5] > len(data) or section[4] + section[5] > len(data):
            raise ValueError("truncated ELF symbol/string table")
        names = data[strings[4]:strings[4] + strings[5]]
        for offset in range(section[4], section[4] + section[5], 16):
            name, address, _, info, _, index = struct.unpack_from(">IIIBBH", data, offset)
            if name >= len(names):
                raise ValueError("invalid ELF symbol name")
            if names[name:].split(b"\0", 1)[0].decode("utf-8") != symbol:
                continue
            if not 0 < index < len(sections) or info & 15 not in (0, 2):
                raise ValueError("reference symbol is not a defined function")
            code = sections[index]
            if code[1] != 1 or not code[2] & 4 or address + size > code[5] or code[4] + code[5] > len(data):
                raise ValueError("reference object does not cover the registered instruction span")
            matches.append((offset, info))
    if len(matches) != 1:
        raise ValueError(f"expected one reference symbol {symbol}, found {len(matches)}")
    offset, info = matches[0]
    output = bytearray(data)
    struct.pack_into(">I", output, offset + 8, size)
    output[offset + 12] = (info & 0xF0) | 2  # STT_FUNC
    return bytes(output)


def prepare(identifiers: list[str]) -> None:
    """Run in the pinned Docker toolchain; no source or progress writes."""
    import diff
    for identifier in identifiers:
        source, symbol, game = diff.find_work_item_by_id(identifier, "us")
        deferred = diff.work_item_is_deferred(identifier)
        if not deferred:
            diff.require_c_implementation(source, identifier)
        assembly = diff.ensure_reference_function("us", symbol, game_reference=game)
        size = diff.expected_function_size("us", symbol)
        candidate = diff.compile_candidate("us", source, deferred_symbol=identifier if deferred else None)
        reference = diff.reference_object("us", symbol, game_reference=game, assembly=assembly)
        directory = ROOT / "build/us/objdiff" / identifier
        directory.mkdir(parents=True, exist_ok=True)
        # Own copies also prevent the next deferred member in the same source
        # unit from overwriting the candidate used by this experiment.
        target = directory / "reference.o"
        base = directory / "candidate.o"
        target.write_bytes(bound_reference(reference.read_bytes(), symbol, size))
        shutil.copyfile(candidate, base)
        settings = diff.write_settings("us", source, directory=directory)
        start = time.perf_counter()
        result = subprocess.run(diff.asm_diff_command(base, reference, symbol, size, require_match=True),
                                cwd=settings, check=True, capture_output=True, text=True)
        elapsed = time.perf_counter() - start
        evidence = json.loads(result.stdout)
        score = diff.current_difference_count(result.stdout)
        write_json(directory / "asm-differ.json", evidence)
        write_json(directory / "inputs.json", {
            "id": identifier, "symbol": symbol, "source": str(source.relative_to(ROOT)),
            "deferred": deferred, "registered_size": size, "current_score": score,
            "asm_differ_seconds": elapsed,
            "reference_assembly": str(assembly.relative_to(ROOT)),
            "reference_sha256": hashlib.sha256(target.read_bytes()).hexdigest(),
            "candidate_sha256": hashlib.sha256(base.read_bytes()).hexdigest(),
        })
        print(f"Prepared {identifier}: CURRENT ({score}), registered span {size} bytes", flush=True)


def summarize(evidence: dict, symbol: str, expected_size: int) -> dict:
    symbols = []
    for side in ("left", "right"):
        found = [item for item in evidence.get(side, {}).get("symbols", []) if item.get("name") == symbol]
        if len(found) != 1:
            raise ValueError(f"objdiff did not return one {side} symbol for {symbol}")
        symbols.append(found[0])
    target, base = symbols
    if "match_percent" not in target or "target_symbol" not in target:
        raise ValueError(f"objdiff did not compare {symbol}")
    rows = target.get("instructions", [])
    instructions = [row["instruction"] for row in rows if "instruction" in row]
    start = int(target.get("address", 0))
    coverage = (int(target.get("size", 0)) == expected_size
                and [int(i.get("address", 0)) for i in instructions] == list(range(start, start + expected_size, 4))
                and all(i.get("size") == 4 for i in instructions))
    return {
        "match_percent": target["match_percent"],
        "reference_size": int(target.get("size", 0)), "candidate_size": int(base.get("size", 0)),
        "reference_span_covered": coverage,
        "different_rows": sum(row.get("diff_kind", "DIFF_NONE") != "DIFF_NONE" for row in rows),
    }


def compare(binary: Path, identifiers: list[str]) -> None:
    output = ROOT / "build/us/objdiff"
    summaries = []
    units = []
    for identifier in identifiers:
        directory = output / identifier
        inputs = json.loads((directory / "inputs.json").read_text())
        start = time.perf_counter()
        subprocess.run([str(binary), "diff", "-1", str(directory / "reference.o"),
                        "-2", str(directory / "candidate.o"), "-o", str(directory / "objdiff.json"),
                        inputs["symbol"]], check=True, cwd=ROOT)
        elapsed = time.perf_counter() - start
        result = summarize(json.loads((directory / "objdiff.json").read_text()),
                           inputs["symbol"], inputs["registered_size"])
        summaries.append({**inputs, "objdiff": result, "objdiff_seconds": elapsed})
        units.append({"name": identifier, "target_path": f"{identifier}/reference.o",
                      "base_path": f"{identifier}/candidate.o", "metadata": {"complete": False}})
        coverage = "full reference span" if result["reference_span_covered"] else "WARNING: incomplete reference span"
        print(f"{identifier}: CURRENT ({inputs['current_score']}); objdiff {result['match_percent']:.4f}%; "
              f"sizes {result['reference_size']}/{result['candidate_size']}; {coverage}")
    write_json(output / "comparison.json", {"scope": "diagnostic selected functions; not project progress",
                                            "objdiff_version": json.loads((ROOT / "toolchain/tools.lock.json").read_text())["objdiff_cli"]["version"],
                                            "comparisons": summaries})
    write_json(output / "objdiff.json", {"build_target": False, "build_base": False, "units": units})
    print("Saved build/us/objdiff/comparison.json and GUI project build/us/objdiff/objdiff.json")
    print("Diagnostic only: objdiff percentages do not record matches or source-unit integration.")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("report", help="generate an exhaustive US CPU-code progress report")
    commands.add_parser("install", help="download and verify the pinned host CLI")
    for command in ("compare", "view", "prepare"):
        sub = commands.add_parser(command, help={"compare": "compare selected US C/deferred candidates using both tools",
                                                "view": "open an interactive terminal diff",
                                                "prepare": "internal Docker object preparation"}[command])
        sub.add_argument("ids", nargs="+" if command != "view" else 1)
    args = parser.parse_args()
    try:
        if args.command == "prepare":
            prepare(args.ids)
            return 0
        binary = install()
        if args.command == "report":
            import objdiff_report
            return objdiff_report.generate(binary)
        if args.command == "install":
            subprocess.run([str(binary), "--version"], check=True)
            print(binary)
            return 0
        if args.command == "view" and not (sys.stdin.isatty() and sys.stdout.isatty()):
            raise ValueError("view requires interactive stdin/stdout; use compare for saved JSON")
        identifiers = list(dict.fromkeys(args.ids))
        # Resolve IDs before using them as cache directory names.
        import diff
        for identifier in identifiers:
            diff.find_work_item_by_id(identifier, "us")
        for name in ("comparison.json", "objdiff.json"):
            (ROOT / "build/us/objdiff" / name).unlink(missing_ok=True)
        subprocess.run([str(ROOT / "conker"), "objdiff-prepare", *identifiers], cwd=ROOT, check=True)
        compare(binary, identifiers)
        if args.command == "view":
            directory = ROOT / "build/us/objdiff" / identifiers[0]
            inputs = json.loads((directory / "inputs.json").read_text())
            return subprocess.run([str(binary), "diff", "-1", str(directory / "reference.o"),
                                   "-2", str(directory / "candidate.o"), inputs["symbol"]], cwd=ROOT).returncode
        return 0
    except (ValueError, OSError, subprocess.CalledProcessError, struct.error) as error:
        print(f"error: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
