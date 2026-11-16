#!/usr/bin/env python3
"""Compose the GAME initialized-data image from the integrated link.

The integrated game ELF already places every reviewed unit and SDK data
section at its original address (INFO output sections in
config/game/us-rodata.ld and config/game/us-sdk.ld). Those section contents
are actual linker output: emitted by the compiled or archived input object,
with relocations resolved against the integrated game code.

This step writes the full GAME data image the way the integrated build writes
game.code.bin: every reviewed placement contributes its linked payload, and
only bytes no source or SDK object owns yet are preserved from the
checksum-validated ROM. The image must equal the original decoded GAME data
byte for byte. The manifest records, per range, whether the bytes were
linked or preserved and which actual link input supplied them, so reports can
credit linked data without trusting placement alone.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import sys

import data_boundaries
from elf_sections import sections
import rom_span

ROOT = Path(__file__).resolve().parent.parent
PLACEMENT_SCRIPTS = ("config/game/us-rodata.ld", "config/game/us-sdk.ld")
BUILD_DIR = "build/game-integrated/us"
SCHEMA = 1


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def placements(root: Path, base: int, size: int) -> list[dict]:
    """Return reviewed initialized placements backed by the GAME data image."""
    result = []
    for path in PLACEMENT_SCRIPTS:
        for mapping in data_boundaries.external_mappings((root / path).read_text(), path):
            if mapping["input"] in (".bss", ".sbss"):
                continue
            inside = base <= mapping["start"] < mapping["end"] <= base + size
            if not inside:
                if base <= mapping["start"] < base + size:
                    raise ValueError(f"{mapping['output']}: placement crosses the GAME data image end")
                continue  # e.g. SDK objects bound to main's initialized storage
            if mapping["linker_mode"] != "INFO":
                raise ValueError(f"{mapping['output']}: GAME data placements must be INFO "
                                 "so the integrated ELF retains linked bytes")
            result.append(mapping)
    result.sort(key=lambda item: item["start"])
    for left, right in zip(result, result[1:]):
        if right["start"] < left["end"]:
            raise ValueError(f"{left['output']} and {right['output']} overlap")
    return result


def linked_objects(root: Path, sources: list[str]) -> dict[str, Path]:
    """Map each actual integrated C object by stem, as the linker selectors do."""
    result: dict[str, Path] = {}
    for source in sources:
        stem = Path(source).stem
        if stem in result:
            raise ValueError(f"ambiguous integrated object stem: {stem}")
        result[stem] = root / BUILD_DIR / (source.removesuffix(".c") + ".o")
    return result


def link_input(root: Path, mapping: dict, objects: dict[str, Path]) -> dict:
    """Name the one actual link input a reviewed selector consumes."""
    selector = mapping["input_selector"]
    match = re.fullmatch(r"\*(\w+)\.o\((\.[\w.]+)\)", selector)
    if match:
        path = objects.get(match[1])
        if path is None or not path.is_file():
            raise ValueError(f"{mapping['output']}: selector {selector} has no integrated C object")
        relative = path.relative_to(root).as_posix()
        return {"kind": "source", "object": relative,
                "source": relative.removeprefix(BUILD_DIR + "/").removesuffix(".o") + ".c",
                "object_sha256": sha256(path.read_bytes())}
    match = re.fullmatch(r"(build/game-libs/us/\w+\.a):(\w+\.o)\((\.[\w.]+)\)", selector)
    if match:
        archive = root / match[1]
        if not archive.is_file():
            raise ValueError(f"{mapping['output']}: missing SDK archive {match[1]}")
        return {"kind": "sdk", "archive": match[1], "member": match[2],
                "archive_sha256": sha256(archive.read_bytes())}
    raise ValueError(f"{mapping['output']}: unsupported selector {selector}")


def compose(elf: bytes, original: bytes, base: int, mappings: list[dict],
            inputs: list[dict]) -> tuple[bytes, list[dict]]:
    """Overlay linked payloads on preserved bytes and verify the whole image."""
    linked = sections(elf, 2)
    image = bytearray(original)
    ranges = []
    cursor = base
    for mapping, origin in zip(mappings, inputs, strict=True):
        name = mapping["output"]
        if name not in linked:
            raise ValueError(f"{name}: placement is missing from the integrated ELF")
        header, payload = linked[name]
        # Section type 1 (PROGBITS): INFO keeps contents without allocation.
        if header[1] != 1 or header[3] != mapping["start"] or header[5] != mapping["emitted_size"]:
            raise ValueError(f"{name}: linked section differs from its reviewed address, type or extent")
        size = mapping["end"] - mapping["start"]
        if any(payload[size:]):
            raise ValueError(f"{name}: compiler padding beyond the payload is not zero")
        offset = mapping["start"] - base
        expected = original[offset:offset + size]
        if payload[:size] != expected:
            raise ValueError(f"{name}: linked payload differs from US ROM GAME data at 0x{mapping['start']:X}")
        if cursor < mapping["start"]:
            ranges.append(preserved(original, base, cursor, mapping["start"]))
        image[offset:offset + size] = payload[:size]
        ranges.append({"start": mapping["start"], "end": mapping["end"], "size": size,
                       "provenance": "linked", "output": name, "input": mapping["input"],
                       "input_selector": mapping["input_selector"], **origin,
                       "sha256": sha256(payload[:size])})
        cursor = mapping["end"]
    if cursor < base + len(original):
        ranges.append(preserved(original, base, cursor, base + len(original)))
    if bytes(image) != original:
        raise ValueError("composed GAME data image differs from the US ROM")
    return bytes(image), ranges


def preserved(original: bytes, base: int, start: int, end: int) -> dict:
    payload = original[start - base:end - base]
    return {"start": start, "end": end, "size": end - start, "provenance": "preserved",
            "sha256": sha256(payload)}


def build(elf_path: Path, output: Path, manifest_path: Path, *, root: Path = ROOT,
          sources: list[str] | None = None) -> dict:
    original, base, digest = rom_span.game_data(root)
    if sources is None:
        import list_integrated_sources
        sources = list_integrated_sources.mapped_sources("us", overlay="game")
    mappings = placements(root, base, len(original))
    objects = linked_objects(root, sources)
    inputs = [link_input(root, mapping, objects) for mapping in mappings]
    elf = elf_path.read_bytes()
    image, ranges = compose(elf, original, base, mappings, inputs)
    linked = sum(r["size"] for r in ranges if r["provenance"] == "linked")
    manifest = {
        "schema": SCHEMA,
        "rom_sha1": digest,
        "elf": elf_path.resolve().relative_to(root).as_posix(),
        "elf_sha256": sha256(elf),
        "image": {"vram_start": base, "vram_end": base + len(image), "size": len(image),
                  "sha256": sha256(image), "matches_rom": True},
        "linked_bytes": linked,
        "preserved_bytes": len(image) - linked,
        "ranges": ranges,
    }
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = output.with_suffix(output.suffix + ".tmp")
    temporary.write_bytes(image)
    temporary.replace(output)
    manifest["image"]["path"] = output.resolve().relative_to(root).as_posix()
    text = json.dumps(manifest, indent=2) + "\n"
    temporary = manifest_path.with_suffix(manifest_path.suffix + ".tmp")
    temporary.write_text(text)
    temporary.replace(manifest_path)
    return manifest


def load_manifest(root: Path = ROOT) -> dict:
    """Read the manifest only while its ELF and image still match the files on disk."""
    path = root / BUILD_DIR / "game.data.json"
    manifest = json.loads(path.read_text())
    if manifest.get("schema") != SCHEMA or manifest["image"].get("matches_rom") is not True:
        raise ValueError("GAME data image manifest has an unsupported schema or failed proof")
    if sha256((root / manifest["elf"]).read_bytes()) != manifest["elf_sha256"]:
        raise ValueError("GAME data image manifest is stale: the integrated ELF changed")
    if sha256((root / manifest["image"]["path"]).read_bytes()) != manifest["image"]["sha256"]:
        raise ValueError("GAME data image changed after its proof")
    return manifest


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("elf", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    arguments = parser.parse_args()
    try:
        manifest = build(arguments.elf, arguments.output, arguments.manifest)
    except (ValueError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(f"{arguments.output}: GAME data image matches US ROM; "
          f"{manifest['linked_bytes']} linked bytes, {manifest['preserved_bytes']} preserved")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
