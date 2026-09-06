#!/usr/bin/env python3
"""Extract and byte-identically rebuild Conker US MP3 streams and decoder tables."""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import normalize_rom, parse_asset_banks, parse_asset_entries
    from scripts.rzip_extract import (
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )
except ModuleNotFoundError:
    from rzip_archive import (  # type: ignore[no-redef]
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
    )
    from rzip_extract import (  # type: ignore[no-redef]
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )


MP3_STREAM_BANK_INDEX = 0x16
MP3_DECODER_BANK_INDEX = 0x17
OFFSET_ENTRY_INDEX = 4
LOOKUP_ENTRY_INDEX = 5
HUFFMAN_ENTRY_INDEX = 6
OFFSET_COUNT = 36
OFFSET_TABLE_SIZE = OFFSET_COUNT * 4
LOOKUP_TABLE_SIZE = 0x4400
HUFFMAN_TABLE_SIZE = 0xA410
MPEG_LAYER_3 = 1
MPEG_VERSION_SAMPLE_RATES = {
    0: (11025, 12000, 8000),
    2: (22050, 24000, 16000),
    3: (44100, 48000, 32000),
}
MPEG1_LAYER3_BITRATES = (
    0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0
)
MPEG2_LAYER3_BITRATES = (
    0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0
)


@dataclass(frozen=True)
class Mp3Asset:
    entry_index: int
    role: str
    data: bytes
    rom_start: int
    rom_end: int
    type_flags: int
    compressed: bool


@dataclass(frozen=True)
class Mp3AssetFamily:
    stream_bank_start: int
    stream_bank_end: int
    streams: tuple[Mp3Asset, ...]
    decoder_bank_start: int
    decoder_bank_end: int
    offsets: Mp3Asset
    lookup: Mp3Asset
    huffman: Mp3Asset


@dataclass(frozen=True)
class MpegLayer3Header:
    version: int
    bitrate_kbps: int
    sample_rate: int
    frame_size: int
    samples_per_frame: int
    copyright: bool


@dataclass(frozen=True)
class Mp3CueStream:
    frame_count: int
    sample_rate: int
    sample_count: int
    bitrate_counts: dict[int, int]
    cues: tuple[dict[str, Any], ...]
    trailing_offset: int
    trailing_size: int
    trailing_sha1: str
    id3v1: dict[str, Any] | None


def parse_mpeg_layer3_header(data: bytes, offset: int) -> MpegLayer3Header | None:
    """Parse the exact four-byte MPEG Layer III header used by a stream frame."""

    if offset < 0 or offset + 4 > len(data):
        return None
    first, second, third, fourth = data[offset : offset + 4]
    if first != 0xFF or second & 0xE0 != 0xE0:
        return None
    version = (second >> 3) & 3
    layer = (second >> 1) & 3
    bitrate_index = third >> 4
    sample_rate_index = (third >> 2) & 3
    if (
        version not in MPEG_VERSION_SAMPLE_RATES
        or layer != MPEG_LAYER_3
        or bitrate_index in (0, 15)
        or sample_rate_index == 3
    ):
        return None

    sample_rate = MPEG_VERSION_SAMPLE_RATES[version][sample_rate_index]
    bitrate_table = MPEG1_LAYER3_BITRATES if version == 3 else MPEG2_LAYER3_BITRATES
    bitrate_kbps = bitrate_table[bitrate_index]
    padding = (third >> 1) & 1
    coefficient = 144000 if version == 3 else 72000
    frame_size = coefficient * bitrate_kbps // sample_rate + padding
    return MpegLayer3Header(
        version=version,
        bitrate_kbps=bitrate_kbps,
        sample_rate=sample_rate,
        frame_size=frame_size,
        samples_per_frame=1152 if version == 3 else 576,
        copyright=bool(fourth & 0x08),
    )


def decode_id3v1(data: bytes, offset: int) -> dict[str, Any] | None:
    """Decode a source tag only when it begins at the runtime audio boundary."""

    if offset < 0 or offset + 128 > len(data) or data[offset : offset + 3] != b"TAG":
        return None
    tag = data[offset : offset + 128]

    def field(start: int, end: int) -> str:
        return tag[start:end].rstrip(b"\0 ").decode("latin-1")

    return {
        "offset": offset,
        "title": field(3, 33),
        "artist": field(33, 63),
        "album": field(63, 93),
        "year": field(93, 97),
        "comment": field(97, 127),
        "genre": tag[127],
        "raw_sha1": hashlib.sha1(tag).hexdigest(),
    }


def parse_mp3_cue_stream(data: bytes) -> Mp3CueStream:
    """Walk runtime MPEG frames and retain Conker's post-frame `L:` records."""

    offset = 0
    frame_index = 0
    sample_count = 0
    sample_rate: int | None = None
    bitrate_counts: Counter[int] = Counter()
    cues: list[dict[str, Any]] = []

    while True:
        header = parse_mpeg_layer3_header(data, offset)
        if header is None:
            break
        if sample_rate is None:
            sample_rate = header.sample_rate
        elif header.sample_rate != sample_rate:
            raise ValueError("MP3 stream changes sample rate between frames")

        frame_start = offset
        frame_end = frame_start + header.frame_size
        if frame_end > len(data):
            raise ValueError(f"MP3 frame {frame_index} extends beyond the stream")
        offset = frame_end
        sample_count += header.samples_per_frame
        bitrate_counts[header.bitrate_kbps] += 1

        if header.copyright:
            terminator = data.find(b"\0", offset, min(len(data), offset + 256))
            if terminator < 0:
                raise ValueError(f"MP3 frame {frame_index} cue has no terminator")
            payload = data[offset:terminator]
            if len(payload) != 8 or payload[:2] != b"L:":
                raise ValueError(
                    f"MP3 frame {frame_index} has unsupported embedded cue "
                    f"{payload.hex()}"
                )
            cues.append(
                {
                    "cue_index": len(cues),
                    "frame_index": frame_index,
                    "frame_offset": frame_start,
                    "record_offset": offset,
                    "record_size": len(payload) + 1,
                    "sample_offset": sample_count,
                    "time_seconds": round(sample_count / header.sample_rate, 6),
                    "marker": "L:",
                    "payload_hex": payload.hex(),
                    "payload_bytes": list(payload[2:]),
                }
            )
            offset = terminator + 1
        frame_index += 1

    if frame_index == 0 or sample_rate is None:
        raise ValueError("MP3 stream contains no supported MPEG Layer III frames")
    trailing = data[offset:]
    return Mp3CueStream(
        frame_count=frame_index,
        sample_rate=sample_rate,
        sample_count=sample_count,
        bitrate_counts=dict(sorted(bitrate_counts.items())),
        cues=tuple(cues),
        trailing_offset=offset,
        trailing_size=len(trailing),
        trailing_sha1=hashlib.sha1(trailing).hexdigest(),
        id3v1=decode_id3v1(data, offset),
    )


def decode_huffman_offsets(data: bytes, huffman_size: int) -> list[int]:
    if len(data) != OFFSET_TABLE_SIZE:
        raise ValueError(
            f"MP3 Huffman offset table is {len(data)} bytes; expected {OFFSET_TABLE_SIZE}"
        )
    offsets = list(struct.unpack(f">{OFFSET_COUNT}I", data))
    if offsets[0] != 0 or offsets[34:] != [0, 0]:
        raise ValueError("MP3 Huffman offset table has invalid unused slots")

    active = offsets[1:34]
    if active != sorted(active):
        raise ValueError("MP3 Huffman offsets are not monotonic")
    if any(offset % 4 for offset in active):
        raise ValueError("MP3 Huffman offsets are not four-byte aligned")
    if any(offset >= huffman_size for offset in active):
        raise ValueError("MP3 Huffman offset is outside the Huffman table")
    return offsets


def encode_huffman_offsets(offsets: list[int], huffman_size: int) -> bytes:
    if len(offsets) != OFFSET_COUNT:
        raise ValueError(f"MP3 Huffman offset list must contain {OFFSET_COUNT} values")
    if any(
        not isinstance(offset, int) or offset < 0 or offset > 0xFFFFFFFF
        for offset in offsets
    ):
        raise ValueError("MP3 Huffman offsets must be unsigned 32-bit integers")
    encoded = struct.pack(f">{OFFSET_COUNT}I", *offsets)
    decode_huffman_offsets(encoded, huffman_size)
    return encoded


def validate_family(family: Mp3AssetFamily) -> list[int]:
    if not family.streams:
        raise ValueError("MP3 stream bank is empty")
    stream_indices = [stream.entry_index for stream in family.streams]
    if stream_indices != sorted(set(stream_indices)):
        raise ValueError("MP3 stream bank indices are not unique and ordered")
    for stream in family.streams:
        if stream.compressed:
            raise ValueError(f"MP3 stream entry {stream.entry_index} is RZIP-compressed")
        if (
            len(stream.data) < 2
            or stream.data[0] != 0xFF
            or stream.data[1] & 0xE0 != 0xE0
        ):
            raise ValueError(f"MP3 stream entry {stream.entry_index} has no MPEG frame sync")

    expected = (
        (family.offsets, OFFSET_ENTRY_INDEX, OFFSET_TABLE_SIZE, 0),
        (family.lookup, LOOKUP_ENTRY_INDEX, LOOKUP_TABLE_SIZE, 0),
        (family.huffman, HUFFMAN_ENTRY_INDEX, HUFFMAN_TABLE_SIZE, 0x80),
    )
    for asset, entry_index, expected_size, expected_flags in expected:
        if asset.entry_index != entry_index:
            raise ValueError(f"MP3 asset role {asset.role} has the wrong bank entry")
        if asset.compressed or asset.type_flags != expected_flags:
            raise ValueError(
                f"MP3 asset entry {entry_index} has unexpected storage flags"
            )
        if len(asset.data) != expected_size:
            raise ValueError(
                f"MP3 asset entry {entry_index} is {len(asset.data)} bytes; "
                f"expected {expected_size}"
            )
    return decode_huffman_offsets(family.offsets.data, len(family.huffman.data))


def resolve_rom(profile: str, rom_argument: Path | None) -> tuple[Path, dict[str, Any]]:
    if profile != "us":
        raise ValueError("the MP3 asset family is currently proven only for the US profile")
    layout = load_layout(profile)
    if rom_argument is None:
        default_rom = layout.get("default_rom")
        if not default_rom:
            raise ValueError(f"--rom is required for the {profile} profile")
        rom_path = ROOT / default_rom
    else:
        rom_path = rom_argument if rom_argument.is_absolute() else ROOT / rom_argument
    if not rom_path.is_file():
        raise ValueError(f"ROM does not exist: {display_path(rom_path)}")
    return rom_path, layout


def load_profile_mp3_assets(
    profile: str, rom_argument: Path | None
) -> tuple[Path, bytes, str, Mp3AssetFamily]:
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(
            f"{profile} normalized ROM SHA-1 mismatch: got {digest}; expected one of "
            + ", ".join(layout["normalized_sha1"])
        )

    banks = parse_asset_banks(normalized, layout["asset_table"])
    if len(banks) <= MP3_DECODER_BANK_INDEX:
        raise ValueError("US asset table does not contain MP3 banks 0x16 and 0x17")
    stream_bank = banks[MP3_STREAM_BANK_INDEX]
    decoder_bank = banks[MP3_DECODER_BANK_INDEX]
    stream_entries = parse_asset_entries(normalized, stream_bank)
    decoder_entries = {
        entry.index: entry for entry in parse_asset_entries(normalized, decoder_bank)
    }

    def load_asset(entry_index: int, role: str) -> Mp3Asset:
        try:
            entry = decoder_entries[entry_index]
        except KeyError as error:
            raise ValueError(f"MP3 asset bank is missing entry {entry_index}") from error
        return Mp3Asset(
            entry_index=entry.index,
            role=role,
            data=normalized[entry.start : entry.end],
            rom_start=entry.start,
            rom_end=entry.end,
            type_flags=entry.type_flags,
            compressed=entry.compressed,
        )

    family = Mp3AssetFamily(
        stream_bank_start=stream_bank.start,
        stream_bank_end=stream_bank.end,
        streams=tuple(
            Mp3Asset(
                entry_index=entry.index,
                role="stream",
                data=normalized[entry.start : entry.end],
                rom_start=entry.start,
                rom_end=entry.end,
                type_flags=entry.type_flags,
                compressed=entry.compressed,
            )
            for entry in stream_entries
        ),
        decoder_bank_start=decoder_bank.start,
        decoder_bank_end=decoder_bank.end,
        offsets=load_asset(OFFSET_ENTRY_INDEX, "huffman-offsets"),
        lookup=load_asset(LOOKUP_ENTRY_INDEX, "lookup"),
        huffman=load_asset(HUFFMAN_ENTRY_INDEX, "huffman"),
    )
    validate_family(family)
    return rom_path, normalized, source_order, family


def safe_manifest_file(input_dir: Path, filename: str) -> Path:
    relative = Path(filename)
    if relative.is_absolute() or ".." in relative.parts:
        raise ValueError(f"unsafe MP3 asset manifest path: {filename}")
    return input_dir / relative


def extract_mp3_assets(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    rom_path, normalized, source_order, family = load_profile_mp3_assets(
        profile, rom_argument
    )
    offsets = validate_family(family)
    prepare_output(output, force)
    streams_dir = output / "streams"
    streams_dir.mkdir()

    stream_records = []
    for stream in family.streams:
        filename = f"streams/{stream.entry_index:04d}.mp3"
        (output / filename).write_bytes(stream.data)
        stream_records.append(
            {
                "entry_index": stream.entry_index,
                "rom_start": f"0x{stream.rom_start:X}",
                "rom_end": f"0x{stream.rom_end:X}",
                "decoded_size": len(stream.data),
                "type_flags": stream.type_flags,
                "compressed": stream.compressed,
                "decoded_sha1": hashlib.sha1(stream.data).hexdigest(),
                "file": filename,
            }
        )

    offsets_file = "huffman-offsets.json"
    lookup_file = "lookup.bin"
    huffman_file = "huffman.bin"
    (output / offsets_file).write_text(
        json.dumps(
            {
                "schema_version": 1,
                "entry_index": OFFSET_ENTRY_INDEX,
                "offsets": [f"0x{offset:X}" for offset in offsets],
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    (output / lookup_file).write_bytes(family.lookup.data)
    (output / huffman_file).write_bytes(family.huffman.data)

    files = {
        OFFSET_ENTRY_INDEX: offsets_file,
        LOOKUP_ENTRY_INDEX: lookup_file,
        HUFFMAN_ENTRY_INDEX: huffman_file,
    }
    decoder_records = []
    for asset in (family.offsets, family.lookup, family.huffman):
        decoder_records.append(
            {
                "entry_index": asset.entry_index,
                "role": asset.role,
                "rom_start": f"0x{asset.rom_start:X}",
                "rom_end": f"0x{asset.rom_end:X}",
                "decoded_size": len(asset.data),
                "type_flags": asset.type_flags,
                "compressed": asset.compressed,
                "decoded_sha1": hashlib.sha1(asset.data).hexdigest(),
                "file": files[asset.entry_index],
            }
        )

    manifest = {
        "schema_version": 2,
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(),
        "asset_count": len(stream_records) + len(decoder_records),
        "stream_bank": {
            "bank_index": MP3_STREAM_BANK_INDEX,
            "bank_start": f"0x{family.stream_bank_start:X}",
            "bank_end": f"0x{family.stream_bank_end:X}",
            "stream_count": len(stream_records),
            "streams": stream_records,
        },
        "decoder_bank": {
            "bank_index": MP3_DECODER_BANK_INDEX,
            "bank_start": f"0x{family.decoder_bank_start:X}",
            "bank_end": f"0x{family.decoder_bank_end:X}",
            "asset_count": len(decoder_records),
            "assets": decoder_records,
        },
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def read_offset_file(path: Path) -> list[int]:
    document = json.loads(path.read_text(encoding="utf-8"))
    if (
        document.get("schema_version") != 1
        or document.get("entry_index") != OFFSET_ENTRY_INDEX
    ):
        raise ValueError("MP3 Huffman offset file has an unsupported schema")
    raw_offsets = document.get("offsets")
    if not isinstance(raw_offsets, list):
        raise ValueError("MP3 Huffman offset file does not contain an offset list")
    try:
        return [
            int(value, 0) if isinstance(value, str) else int(value)
            for value in raw_offsets
        ]
    except (TypeError, ValueError) as error:
        raise ValueError("MP3 Huffman offset file contains an invalid value") from error


def pack_mp3_assets(
    input_dir: Path, output: Path, force: bool
) -> dict[int, dict[int, bytes]]:
    manifest = json.loads((input_dir / "manifest.json").read_text(encoding="utf-8"))
    if manifest.get("schema_version") != 2 or manifest.get("profile") != "us":
        raise ValueError("MP3 asset manifest has an unsupported schema or profile")
    stream_bank = manifest.get("stream_bank")
    decoder_bank = manifest.get("decoder_bank")
    if not isinstance(stream_bank, dict) or not isinstance(decoder_bank, dict):
        raise ValueError("MP3 asset manifest does not describe both US banks")
    stream_records = stream_bank.get("streams")
    records = decoder_bank.get("assets")
    if (
        stream_bank.get("bank_index") != MP3_STREAM_BANK_INDEX
        or decoder_bank.get("bank_index") != MP3_DECODER_BANK_INDEX
        or not isinstance(stream_records, list)
        or not isinstance(records, list)
    ):
        raise ValueError("MP3 asset manifest has invalid bank records")
    if int(stream_bank.get("stream_count", -1)) != len(stream_records):
        raise ValueError("MP3 stream manifest count does not match its stream list")
    if int(decoder_bank.get("asset_count", -1)) != len(records):
        raise ValueError("MP3 decoder manifest count does not match its asset list")
    if int(manifest.get("asset_count", -1)) != len(stream_records) + len(records):
        raise ValueError("MP3 asset manifest count does not match its asset lists")

    streams: dict[int, bytes] = {}
    for record in stream_records:
        entry_index = int(record["entry_index"])
        if entry_index in streams:
            raise ValueError("MP3 asset manifest contains a duplicate stream entry")
        data = safe_manifest_file(input_dir, record["file"]).read_bytes()
        if len(data) != int(record["decoded_size"]):
            raise ValueError(f"MP3 stream entry {entry_index} has the wrong size")
        if hashlib.sha1(data).hexdigest() != record["decoded_sha1"]:
            raise ValueError(f"MP3 stream entry {entry_index} has the wrong SHA-1")
        if len(data) < 2 or data[0] != 0xFF or data[1] & 0xE0 != 0xE0:
            raise ValueError(f"MP3 stream entry {entry_index} has no MPEG frame sync")
        streams[entry_index] = data

    by_index: dict[int, dict[str, Any]] = {}
    for record in records:
        entry_index = int(record["entry_index"])
        if entry_index in by_index:
            raise ValueError("MP3 asset manifest contains a duplicate bank entry")
        by_index[entry_index] = record
    if set(by_index) != {OFFSET_ENTRY_INDEX, LOOKUP_ENTRY_INDEX, HUFFMAN_ENTRY_INDEX}:
        raise ValueError("MP3 asset manifest must contain entries 4, 5, and 6 exactly once")

    huffman_record = by_index[HUFFMAN_ENTRY_INDEX]
    huffman = safe_manifest_file(input_dir, huffman_record["file"]).read_bytes()
    if len(huffman) != HUFFMAN_TABLE_SIZE:
        raise ValueError(
            f"MP3 Huffman table is {len(huffman)} bytes; expected {HUFFMAN_TABLE_SIZE}"
        )
    lookup_record = by_index[LOOKUP_ENTRY_INDEX]
    lookup = safe_manifest_file(input_dir, lookup_record["file"]).read_bytes()
    if len(lookup) != LOOKUP_TABLE_SIZE:
        raise ValueError(
            f"MP3 lookup table is {len(lookup)} bytes; expected {LOOKUP_TABLE_SIZE}"
        )
    offsets_record = by_index[OFFSET_ENTRY_INDEX]
    offsets = encode_huffman_offsets(
        read_offset_file(safe_manifest_file(input_dir, offsets_record["file"])),
        len(huffman),
    )

    decoder_assets = {
        OFFSET_ENTRY_INDEX: offsets,
        LOOKUP_ENTRY_INDEX: lookup,
        HUFFMAN_ENTRY_INDEX: huffman,
    }
    prepare_output(output, force)
    stream_output = output / "bank-16"
    decoder_output = output / "bank-17"
    stream_output.mkdir()
    decoder_output.mkdir()
    for entry_index, data in streams.items():
        (stream_output / f"{entry_index:04d}.mp3").write_bytes(data)
    for entry_index, data in decoder_assets.items():
        (decoder_output / f"{entry_index:04d}.bin").write_bytes(data)
    (output / "manifest.json").write_text(
        json.dumps(
            {
                "schema_version": 2,
                "profile": "us",
                "banks": [
                    {
                        "bank_index": MP3_STREAM_BANK_INDEX,
                        "entries": [
                            {
                                "entry_index": entry_index,
                                "size": len(data),
                                "sha1": hashlib.sha1(data).hexdigest(),
                                "file": f"bank-16/{entry_index:04d}.mp3",
                            }
                            for entry_index, data in streams.items()
                        ],
                    },
                    {
                        "bank_index": MP3_DECODER_BANK_INDEX,
                        "entries": [
                            {
                                "entry_index": entry_index,
                                "size": len(data),
                                "sha1": hashlib.sha1(data).hexdigest(),
                                "file": f"bank-17/{entry_index:04d}.bin",
                            }
                            for entry_index, data in decoder_assets.items()
                        ],
                    },
                ],
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    return {
        MP3_STREAM_BANK_INDEX: streams,
        MP3_DECODER_BANK_INDEX: decoder_assets,
    }


def verify_mp3_assets(profile: str, rom_argument: Path | None) -> tuple[int, int]:
    _, _, _, family = load_profile_mp3_assets(profile, rom_argument)
    offsets = encode_huffman_offsets(validate_family(family), len(family.huffman.data))
    if offsets != family.offsets.data:
        raise ValueError("US MP3 Huffman offsets did not rebuild byte-identically")
    size = sum(len(stream.data) for stream in family.streams)
    size += len(offsets) + len(family.lookup.data) + len(family.huffman.data)
    return len(family.streams) + 3, size


def extract_mp3_cues(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    rom_path, normalized, source_order, family = load_profile_mp3_assets(
        profile, rom_argument
    )
    prepare_output(output, force)
    cues_dir = output / "cues"
    cues_dir.mkdir()

    streams: list[dict[str, Any]] = []
    total_frames = 0
    total_samples = 0
    summed_duration = 0.0
    total_cues = 0
    cue_streams = 0
    tagged_streams = 0
    payload_variant_counts: Counter[int] = Counter()
    bitrate_counts: Counter[int] = Counter()

    for stream in family.streams:
        parsed = parse_mp3_cue_stream(stream.data)
        total_frames += parsed.frame_count
        total_samples += parsed.sample_count
        summed_duration += parsed.sample_count / parsed.sample_rate
        total_cues += len(parsed.cues)
        cue_streams += bool(parsed.cues)
        tagged_streams += parsed.id3v1 is not None
        bitrate_counts.update(parsed.bitrate_counts)
        payload_variant_counts.update(cue["payload_bytes"][0] for cue in parsed.cues)

        cue_file: str | None = None
        if parsed.cues:
            cue_file = f"cues/{stream.entry_index:04d}.json"
            (output / cue_file).write_text(
                json.dumps(
                    {
                        "schema_version": 1,
                        "profile": profile,
                        "stream_entry_index": stream.entry_index,
                        "source_file": f"../../../mp3/us/streams/{stream.entry_index:04d}.mp3",
                        "timing_basis": {
                            "sample_rate": parsed.sample_rate,
                            "samples_per_frame": 576,
                            "event_point": "after decoded frame",
                        },
                        "cue_count": len(parsed.cues),
                        "cues": parsed.cues,
                    },
                    indent=2,
                )
                + "\n",
                encoding="utf-8",
            )

        streams.append(
            {
                "entry_index": stream.entry_index,
                "rom_start": f"0x{stream.rom_start:X}",
                "rom_end": f"0x{stream.rom_end:X}",
                "frame_count": parsed.frame_count,
                "sample_rate": parsed.sample_rate,
                "sample_count": parsed.sample_count,
                "duration_seconds": round(parsed.sample_count / parsed.sample_rate, 6),
                "bitrate_frame_counts": {
                    str(key): value for key, value in parsed.bitrate_counts.items()
                },
                "cue_count": len(parsed.cues),
                "first_cue_seconds": (
                    parsed.cues[0]["time_seconds"] if parsed.cues else None
                ),
                "last_cue_seconds": (
                    parsed.cues[-1]["time_seconds"] if parsed.cues else None
                ),
                "cue_file": cue_file,
                "trailing_offset": parsed.trailing_offset,
                "trailing_size": parsed.trailing_size,
                "trailing_sha1": parsed.trailing_sha1,
                "id3v1": parsed.id3v1,
            }
        )

    manifest = {
        "schema_version": 1,
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(),
        "semantic_status": {
            "record_marker": "L:",
            "runtime_transport": "MPEG Layer III copyright-bit post-frame callback",
            "payload": "six opaque bytes; lip purpose is not yet runtime-confirmed",
            "speaker_ids": "not present in the extracted records",
        },
        "stream_count": len(streams),
        "cue_stream_count": cue_streams,
        "cue_count": total_cues,
        "frame_count": total_frames,
        "sample_count": total_samples,
        "summed_duration_seconds": round(summed_duration, 6),
        "id3v1_stream_count": tagged_streams,
        "bitrate_frame_counts": {
            str(key): value for key, value in sorted(bitrate_counts.items())
        },
        "payload_variant_counts": {
            f"0x{key:02X}": value for key, value in sorted(payload_variant_counts.items())
        },
        "streams": streams,
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def verify_mp3_cues(
    profile: str, rom_argument: Path | None
) -> tuple[int, int, int, int]:
    _, _, _, family = load_profile_mp3_assets(profile, rom_argument)
    parsed = [parse_mp3_cue_stream(stream.data) for stream in family.streams]
    return (
        len(parsed),
        sum(bool(stream.cues) for stream in parsed),
        sum(len(stream.cues) for stream in parsed),
        sum(stream.frame_count for stream in parsed),
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)

    extract_parser = subparsers.add_parser("extract")
    extract_parser.add_argument("--profile", choices=("us",), default="us")
    extract_parser.add_argument("--rom", type=Path)
    extract_parser.add_argument("--output", type=Path)
    extract_parser.add_argument("--force", action="store_true")

    pack_parser = subparsers.add_parser("pack")
    pack_parser.add_argument("--input", type=Path, required=True)
    pack_parser.add_argument("--output", type=Path, required=True)
    pack_parser.add_argument("--force", action="store_true")

    verify_parser = subparsers.add_parser("verify")
    verify_parser.add_argument("--profile", choices=("us",), default="us")
    verify_parser.add_argument("--rom", type=Path)

    cue_extract_parser = subparsers.add_parser("cue-extract")
    cue_extract_parser.add_argument("--profile", choices=("us",), default="us")
    cue_extract_parser.add_argument("--rom", type=Path)
    cue_extract_parser.add_argument("--output", type=Path)
    cue_extract_parser.add_argument("--force", action="store_true")

    cue_verify_parser = subparsers.add_parser("cue-verify")
    cue_verify_parser.add_argument("--profile", choices=("us",), default="us")
    cue_verify_parser.add_argument("--rom", type=Path)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        if args.command == "extract":
            output = args.output or (ROOT / "build" / "assets" / "mp3" / args.profile)
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_mp3_assets(args.profile, args.rom, output, args.force)
            print(
                f"Extracted {manifest['stream_bank']['stream_count']} US MP3 streams "
                f"and 3 decoder assets from banks 0x16/0x17 to "
                f"{display_path(output)}"
            )
        elif args.command == "pack":
            input_dir = args.input if args.input.is_absolute() else ROOT / args.input
            output = args.output if args.output.is_absolute() else ROOT / args.output
            packed = pack_mp3_assets(input_dir, output, args.force)
            count = sum(len(bank) for bank in packed.values())
            size = sum(len(data) for bank in packed.values() for data in bank.values())
            print(f"Packed {count} US MP3 bank entries ({size} bytes) to {display_path(output)}")
        elif args.command == "verify":
            count, size = verify_mp3_assets(args.profile, args.rom)
            print(f"Verified US MP3 assets: {count} entries, {size} bytes, byte-identical")
        elif args.command == "cue-extract":
            output = args.output or (ROOT / "build" / "assets" / "dialogue" / args.profile)
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_mp3_cues(args.profile, args.rom, output, args.force)
            print(
                f"Extracted {manifest['cue_count']} embedded L: cues from "
                f"{manifest['cue_stream_count']}/{manifest['stream_count']} US MP3 streams "
                f"to {display_path(output)}"
            )
        else:
            streams, cue_streams, cues, frames = verify_mp3_cues(
                args.profile, args.rom
            )
            print(
                f"Verified US MP3 cues: {cues} L: records across "
                f"{cue_streams}/{streams} streams and {frames} MPEG frames"
            )
    except (KeyError, OSError, TypeError, ValueError, json.JSONDecodeError) as error:
        print(f"error: {error}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
