#!/usr/bin/env python3
"""Find complete libultra section templates still present in raw US main ranges."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parent.parent
DEFAULT_VERSIONS = ("I", "J", "K", "L")
DEFAULT_TARGETS = ("libultra", "libultra_d", "libultra_rom")
LOADABLE_SECTION_NAMES = {".text", ".data", ".rodata", ".sdata", ".lit4", ".lit8"}


class AuditError(RuntimeError):
    pass


@dataclass(frozen=True)
class TextTemplate:
    text: bytes
    relocations: tuple[tuple[int, int], ...]
    section: str = ".text"
    alignment: int = 16

    @property
    def compare_mask(self) -> bytes:
        masks = bytearray(b"\xff" * len(self.text))
        for offset, relocation_type in self.relocations:
            if relocation_type == 4:  # R_MIPS_26: preserve the six-bit opcode.
                relocation_mask = b"\xfc\x00\x00\x00"
            elif relocation_type in {1, 5, 6, 7, 8, 9, 10, 11}:
                # R_MIPS_16/HI16/LO16/GPREL16/LITERAL/GOT16/PC16/CALL16.
                relocation_mask = b"\xff\xff\x00\x00"
            else:
                # R_MIPS_32/REL32/GPREL32 and unknown whole-word relocations.
                relocation_mask = b"\x00\x00\x00\x00"
            for index, mask in enumerate(relocation_mask):
                if offset + index < len(masks):
                    masks[offset + index] &= mask
        return bytes(masks)

    @property
    def relocation_words(self) -> tuple[int, ...]:
        return tuple(sorted({offset for offset, _ in self.relocations}))

    @property
    def masked_text(self) -> bytes:
        return bytes(value & mask for value, mask in zip(self.text, self.compare_mask))

    @property
    def signature(self) -> str:
        digest = hashlib.sha256()
        digest.update(self.masked_text)
        digest.update(b"|")
        digest.update(self.compare_mask)
        return digest.hexdigest()

    @property
    def spans(self) -> tuple[tuple[int, int], ...]:
        result = []
        start = None
        for offset in range(len(self.text) + 1):
            is_unmasked = offset < len(self.text) and self.compare_mask[offset] == 0xFF
            if is_unmasked and start is None:
                start = offset
            elif not is_unmasked and start is not None:
                result.append((start, offset))
                start = None
        return tuple(result)


def read_c_string(data: bytes, offset: int) -> str:
    end = data.find(b"\0", offset)
    if end < 0:
        raise AuditError("unterminated ELF section name")
    return data[offset:end].decode("ascii", errors="replace")


def read_object_templates(path: Path) -> list[TextTemplate]:
    data = path.read_bytes()
    if len(data) < 52 or data[:4] != b"\x7fELF" or data[4:6] != b"\x01\x02":
        return []

    section_offset = struct.unpack_from(">I", data, 32)[0]
    section_size = struct.unpack_from(">H", data, 46)[0]
    section_count = struct.unpack_from(">H", data, 48)[0]
    names_index = struct.unpack_from(">H", data, 50)[0]
    if section_size < 40 or names_index >= section_count:
        raise AuditError(f"invalid ELF section table: {path}")

    sections = []
    for index in range(section_count):
        offset = section_offset + index * section_size
        if offset + 40 > len(data):
            raise AuditError(f"truncated ELF section table: {path}")
        sections.append(struct.unpack_from(">10I", data, offset))

    names = sections[names_index]
    names_data = data[names[4] : names[4] + names[5]]
    section_names = [read_c_string(names_data, section[0]) for section in sections]
    relocations_by_section: dict[int, set[tuple[int, int]]] = defaultdict(set)
    for section in sections:
        section_type = section[1]
        section_file_offset = section[4]
        section_byte_size = section[5]
        section_info = section[7]
        entry_size = section[9] or 8
        if section_type != 9 or section_info >= len(sections):
            continue
        for offset in range(section_file_offset, section_file_offset + section_byte_size, entry_size):
            if offset + 8 > len(data):
                raise AuditError(f"truncated ELF relocation table: {path}")
            relocation_offset, relocation_info = struct.unpack_from(">II", data, offset)
            target_size = sections[section_info][5]
            if relocation_offset < target_size:
                relocations_by_section[section_info].add(
                    (relocation_offset & ~3, relocation_info & 0xFF)
                )

    templates = []
    for index, section in enumerate(sections):
        name = section_names[index]
        section_type = section[1]
        section_flags = section[2]
        section_file_offset = section[4]
        section_byte_size = section[5]
        section_alignment = section[8]
        if (
            name not in LOADABLE_SECTION_NAMES
            or section_type != 1
            or not section_flags & 0x2
            or not section_byte_size
        ):
            continue
        contents = data[section_file_offset : section_file_offset + section_byte_size]
        templates.append(
            TextTemplate(
                text=contents,
                relocations=tuple(sorted(relocations_by_section[index])),
                section=name,
                alignment=max(1, section_alignment),
            )
        )
    return templates


def main_subsegments(path: Path) -> list:
    config = yaml.safe_load(path.read_text(encoding="utf-8"))
    return next(segment["subsegments"] for segment in config["segments"] if segment.get("name") == "main")


def list_boundaries(subsegments: list) -> list[int]:
    result = []
    for entry in subsegments:
        if isinstance(entry, list) and entry and isinstance(entry[0], int):
            result.append(entry[0])
        elif isinstance(entry, dict) and isinstance(entry.get("start"), int):
            result.append(entry["start"])
    return sorted(set(result))


def mapped_section_ranges(
    subsegments: list, scan_end: int
) -> dict[str, list[tuple[int, int]]]:
    boundaries = list_boundaries(subsegments)
    next_boundary = {
        start: boundaries[index + 1] if index + 1 < len(boundaries) else scan_end
        for index, start in enumerate(boundaries)
    }
    result: dict[str, list[tuple[int, int]]] = defaultdict(list)
    for entry in subsegments:
        if (
            isinstance(entry, list)
            and len(entry) >= 5
            and entry[1] == "lib"
            and entry[0] < scan_end
        ):
            result[entry[4]].append(
                (entry[0], min(next_boundary[entry[0]], scan_end))
            )
    return dict(result)


def overlaps(ranges: list[tuple[int, int]], start: int, end: int) -> bool:
    return any(start < range_end and range_start < end for range_start, range_end in ranges)


def find_occurrences(template: TextTemplate, rom: bytes, start: int, end: int) -> list[int]:
    spans = template.spans
    partial = [
        (offset, mask)
        for offset, mask in enumerate(template.compare_mask)
        if mask not in {0, 0xFF}
    ]
    if (not spans and not partial) or start + len(template.text) > end:
        return []

    longest_span = max(spans, key=lambda span: span[1] - span[0], default=None)
    if longest_span is None:
        candidates = range(start, end - len(template.text) + 1, template.alignment)
    else:
        left, right = longest_span
        needle = template.text[left:right]
        found = []
        position = rom.find(needle, start + left, end - len(template.text) + right)
        while position >= 0:
            offset = position - left
            if offset >= start and offset % template.alignment == 0:
                found.append(offset)
            position = rom.find(needle, position + 1, end - len(template.text) + right)
        candidates = found

    result = []
    for offset in candidates:
        if all(
            rom[offset + left : offset + right] == template.text[left:right]
            for left, right in spans
        ) and all(
            ((rom[offset + relative] ^ template.text[relative]) & mask) == 0
            for relative, mask in partial
        ):
            result.append(offset)
    return result


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=ROOT / "roms/baserom.us.z64")
    parser.add_argument("--profile", type=Path, default=ROOT / "config/profiles/us.yaml")
    parser.add_argument("--build-root", type=Path, default=ROOT / "lib/ultralib/build")
    parser.add_argument("--versions", nargs="+", default=DEFAULT_VERSIONS)
    parser.add_argument("--targets", nargs="+", default=DEFAULT_TARGETS)
    parser.add_argument("--start", type=lambda value: int(value, 0), default=0x1050)
    parser.add_argument("--text-end", type=lambda value: int(value, 0), default=0x292F0)
    parser.add_argument("--end", type=lambda value: int(value, 0), default=0x2D4B0)
    parser.add_argument("--minimum-size", type=lambda value: int(value, 0), default=1)
    parser.add_argument("--json", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    rom = args.rom.read_bytes()
    if len(rom) < args.end:
        raise AuditError(f"ROM ends before requested scan range: {args.rom}")

    subsegments = main_subsegments(args.profile)
    boundaries = list_boundaries(subsegments)
    boundary_ends = {
        start: boundaries[index + 1] if index + 1 < len(boundaries) else args.end
        for index, start in enumerate(boundaries)
    }
    linked_ranges = mapped_section_ranges(subsegments, args.end)
    all_linked_ranges = [
        mapped_range
        for section_ranges in linked_ranges.values()
        for mapped_range in section_ranges
    ]

    template_paths: dict[tuple[str, bytes, bytes], list[str]] = defaultdict(list)
    templates: dict[tuple[str, bytes, bytes], TextTemplate] = {}
    object_count = 0
    section_count = 0
    for version in args.versions:
        for target in args.targets:
            directory = args.build_root / version / target
            if not directory.is_dir():
                raise AuditError(f"missing archive build directory: {directory}")
            for path in sorted(directory.rglob("*.o")):
                object_count += 1
                for template in read_object_templates(path):
                    section_count += 1
                    key = (template.section, template.masked_text, template.compare_mask)
                    templates.setdefault(key, template)
                    template_paths[key].append(
                        f"{path.relative_to(args.build_root).as_posix()}:{template.section}"
                    )

    raw_matches = []
    distinctive = []
    exact_boundaries = []
    for key, paths in template_paths.items():
        template = templates[key]
        if len(template.text) < args.minimum_size:
            continue
        scan_start, scan_end = (
            (args.start, args.text_end)
            if template.section == ".text"
            else (args.text_end, args.end)
        )
        occurrences = find_occurrences(template, rom, scan_start, scan_end)
        raw_occurrences = [
            offset
            for offset in occurrences
            if not overlaps(all_linked_ranges, offset, offset + len(template.text))
        ]
        if not raw_occurrences:
            continue

        record = {
            "signature": template.signature,
            "section": template.section,
            "size": len(template.text),
            "relocation_words": list(template.relocation_words),
            "relocations": [list(relocation) for relocation in template.relocations],
            "objects": paths,
            "occurrences": occurrences,
            "raw_occurrences": raw_occurrences,
        }
        raw_matches.append(record)
        if len(occurrences) == 1:
            distinctive.append(record)
        exact_occurrences = [
            offset
            for offset in raw_occurrences
            if boundary_ends.get(offset) == offset + len(template.text)
        ]
        if exact_occurrences:
            exact_boundaries.append(
                {**record, "exact_raw_boundary_occurrences": exact_occurrences}
            )

    result = {
        "object_instances": object_count,
        "section_instances": section_count,
        "unique_section_templates": len(template_paths),
        "scan_range": [args.start, args.end],
        "text_end": args.text_end,
        "minimum_size": args.minimum_size,
        "mapped_library_section_ranges": sum(
            len(ranges) for ranges in linked_ranges.values()
        ),
        "raw_matching_templates": len(raw_matches),
        "raw_templates": raw_matches,
        "distinctive_raw_templates": distinctive,
        "ambiguous_exact_boundary_templates": exact_boundaries,
    }

    if args.json:
        print(json.dumps(result, indent=2, sort_keys=True))
    else:
        print(f"object instances: {object_count}")
        print(f"loadable section instances: {section_count}")
        print(f"unique complete section templates: {len(template_paths)}")
        print(
            "mapped library section ranges: "
            f"{sum(len(ranges) for ranges in linked_ranges.values())}"
        )
        print(f"raw matching templates: {len(raw_matches)}")
        print(f"distinctive raw templates: {len(distinctive)}")
        print(f"ambiguous exact raw-boundary templates: {len(exact_boundaries)}")
        for label, records in (
            ("distinctive", distinctive),
            ("ambiguous-exact-boundary", exact_boundaries),
        ):
            for record in records:
                occurrence_key = (
                    "exact_raw_boundary_occurrences"
                    if "exact_raw_boundary_occurrences" in record
                    else "raw_occurrences"
                )
                offsets = ", ".join(f"0x{offset:X}" for offset in record[occurrence_key])
                objects = ", ".join(record["objects"][:6])
                if len(record["objects"]) > 6:
                    objects += f", ... (+{len(record['objects']) - 6})"
                print(
                    f"{label}: {offsets} section={record['section']} "
                    f"size=0x{record['size']:X} objects={objects}"
                )

    return 1 if distinctive else 0


if __name__ == "__main__":
    raise SystemExit(main())
