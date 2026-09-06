#!/usr/bin/env python3
"""Survey, verify, extract, and preview Conker's non-MP3 US audio assets."""

from __future__ import annotations

import argparse
import copy
import hashlib
import json
import struct
import sys
from array import array
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import (
        decode_rzip_chunk,
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
    )
    from scripts.rzip_extract import (
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )
except ModuleNotFoundError:
    from rzip_archive import (  # type: ignore[no-redef]
        decode_rzip_chunk,
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


AUDIO_BANK_INDEX = 0x17
SOUND_BANK_CONTROL_ENTRY = 0
SOUND_BANK_DATA_ENTRY = 1
WAVETABLE_ENTRY = 2
SEQUENCE_BANK_ENTRY = 3
REQUIRED_ENTRY_INDICES = (
    SOUND_BANK_CONTROL_ENTRY,
    SOUND_BANK_DATA_ENTRY,
    WAVETABLE_ENTRY,
    SEQUENCE_BANK_ENTRY,
)

AL_BANK_VERSION = 0x4231
AL_SEQBANK_VERSION = 0x5331
COMPACT_SEQUENCE_HEADER_SIZE = 17 * 4

EXPECTED_ENTRY_CONTRACTS = {
    SOUND_BANK_CONTROL_ENTRY: ("sound-bank-control", 7_768, 0x10, True),
    SOUND_BANK_DATA_ENTRY: ("sound-bank-data", 430_608, 0x00, False),
    WAVETABLE_ENTRY: ("wavetable", 21_705_520, 0x01, False),
    SEQUENCE_BANK_ENTRY: ("compact-sequence-bank", 685_656, 0x00, False),
}


@dataclass(frozen=True)
class AudioAsset:
    entry_index: int
    role: str
    data: bytes
    rom_start: int
    rom_end: int
    type_flags: int
    compressed: bool


@dataclass(frozen=True)
class SoundBankSummary:
    revision: int
    bank_offsets: tuple[int, ...]
    instrument_count: int
    sample_rate: int


@dataclass(frozen=True)
class SoundBankGraph:
    manifest: dict[str, Any]
    sample_ranges: tuple[tuple[int, int], ...]


@dataclass(frozen=True)
class CompactSequence:
    index: int
    offset: int
    data: bytes
    padding_after: bytes
    track_offsets: tuple[int, ...]
    division: int


@dataclass(frozen=True)
class CompactSequencePreview:
    midi: bytes
    active_tracks: int
    source_events: int
    notes: int
    loop_markers: int
    end_tick: int


@dataclass(frozen=True)
class AdpcmLoopValidation:
    checked_samples: int
    exact_frames: int
    maximum_error: int


@dataclass(frozen=True)
class NonMp3AudioFamily:
    bank_start: int
    bank_end: int
    assets: tuple[AudioAsset, ...]
    sound_bank: SoundBankSummary
    sequences: tuple[CompactSequence, ...]
    sound_graph: SoundBankGraph | None = None


class CompactTrackReader:
    """Read one CSeq track with the SDK's 0xFE back-reference expansion."""

    def __init__(self, data: bytes, start: int, end: int, track: int) -> None:
        self.data = data
        self.start = start
        self.end = end
        self.track = track
        self.cursor = start
        self.backup_cursor = 0
        self.backup_remaining = 0

    def _error(self, message: str) -> ValueError:
        return ValueError(f"compact sequence track {self.track}: {message}")

    def _read_physical_byte(self) -> int:
        if self.cursor >= self.end:
            raise self._error("event stream ended before end-of-track")
        value = self.data[self.cursor]
        self.cursor += 1
        return value

    def read_physical(self, length: int) -> bytes:
        if self.cursor + length > self.end:
            raise self._error("event payload exceeds its track")
        value = self.data[self.cursor : self.cursor + length]
        self.cursor += length
        return value

    def read_byte(self) -> int:
        if self.backup_remaining:
            if self.backup_cursor >= len(self.data):
                raise self._error("back-reference exceeds the sequence")
            value = self.data[self.backup_cursor]
            self.backup_cursor += 1
            self.backup_remaining -= 1
            return value

        value = self._read_physical_byte()
        if value != 0xFE:
            return value

        high = self._read_physical_byte()
        if high == 0xFE:
            return 0xFE

        low = self._read_physical_byte()
        length = self._read_physical_byte()
        distance = (high << 8) | low
        backup_start = self.cursor - (distance + 4)
        if length == 0:
            raise self._error("back-reference has zero length")
        if backup_start < 0 or backup_start + length > len(self.data):
            raise self._error("back-reference points outside the sequence")
        self.backup_cursor = backup_start + 1
        self.backup_remaining = length - 1
        return self.data[backup_start]

    def read_varlen(self) -> int:
        value = 0
        for _ in range(5):
            byte = self.read_byte()
            value = (value << 7) | (byte & 0x7F)
            if not byte & 0x80:
                if value > 0x0FFFFFFF:
                    raise self._error("variable-length value exceeds Standard MIDI")
                return value
        raise self._error("variable-length value is too long")


def _encode_varlen(value: int) -> bytes:
    if not 0 <= value <= 0x0FFFFFFF:
        raise ValueError(f"MIDI variable-length value is out of range: {value}")
    encoded = bytearray((value & 0x7F,))
    value >>= 7
    while value:
        encoded.append(0x80 | (value & 0x7F))
        value >>= 7
    encoded.reverse()
    return bytes(encoded)


def _meta_event(kind: int, payload: bytes) -> bytes:
    return bytes((0xFF, kind)) + _encode_varlen(len(payload)) + payload


def _midi_track(
    name: str, events: list[tuple[int, int, int, bytes]], end_tick: int
) -> bytes:
    ordered = sorted(events, key=lambda event: (event[0], event[1], event[2]))
    body = bytearray()
    previous_tick = 0
    body.extend(b"\x00" + _meta_event(0x03, name.encode("ascii")))
    for tick, _priority, _order, message in ordered:
        if tick < previous_tick:
            raise ValueError("MIDI events are not in chronological order")
        body.extend(_encode_varlen(tick - previous_tick))
        body.extend(message)
        previous_tick = tick
    final_tick = max(previous_tick, end_tick)
    body.extend(_encode_varlen(final_tick - previous_tick))
    body.extend(b"\xFF\x2F\x00")
    return b"MTrk" + struct.pack(">I", len(body)) + body


def compact_sequence_to_midi(data: bytes) -> CompactSequencePreview:
    """Convert a CSeq to a deterministic, single-pass Standard MIDI preview."""

    if len(data) < COMPACT_SEQUENCE_HEADER_SIZE:
        raise ValueError("compact sequence is shorter than its 68-byte header")
    header = struct.unpack_from(">17I", data)
    track_offsets = tuple(header[:16])
    division = header[16]
    if not 0 < division <= 0x7FFF:
        raise ValueError("compact sequence has an invalid MIDI division")
    active_offsets = sorted(offset for offset in track_offsets if offset)
    if not active_offsets:
        raise ValueError("compact sequence has no active tracks")
    if len(active_offsets) != len(set(active_offsets)):
        raise ValueError("compact sequence has duplicate track offsets")
    if (
        active_offsets[0] < COMPACT_SEQUENCE_HEADER_SIZE
        or active_offsets[-1] >= len(data)
    ):
        raise ValueError("compact sequence has a track offset outside the file")

    conductor_events: list[tuple[int, int, int, bytes]] = []
    midi_tracks: list[tuple[str, list[tuple[int, int, int, bytes]], int]] = []
    source_event_count = 0
    note_count = 0
    loop_marker_count = 0
    sequence_end_tick = 0

    for track, start in enumerate(track_offsets):
        if start == 0:
            continue
        end = next((offset for offset in active_offsets if offset > start), len(data))
        reader = CompactTrackReader(data, start, end, track)
        tick = 0
        order = 0
        running_status = 0
        track_events: list[tuple[int, int, int, bytes]] = []
        delta = reader.read_varlen()

        while True:
            tick += delta
            status = reader.read_byte()
            source_event_count += 1

            if status == 0xFF:
                meta_type = reader.read_byte()
                if meta_type == 0x51:
                    tempo = bytes(reader.read_byte() for _ in range(3))
                    conductor_events.append(
                        (tick, track, order, _meta_event(0x51, tempo))
                    )
                    running_status = 0
                elif meta_type == 0x2F:
                    sequence_end_tick = max(sequence_end_tick, tick)
                    break
                elif meta_type == 0x2E:
                    payload = bytes((reader.read_byte(), reader.read_byte()))
                    marker = (
                        f"Conker loop start track={track} value={int.from_bytes(payload, 'big')}"
                    ).encode("ascii")
                    exact = b"CONKER_CSEQ\x00" + bytes((meta_type,)) + payload
                    conductor_events.extend(
                        (
                            (tick, track, order, _meta_event(0x06, marker)),
                            (tick, track, order + 1, _meta_event(0x7F, exact)),
                        )
                    )
                    loop_marker_count += 1
                    running_status = 0
                elif meta_type == 0x2D:
                    payload = reader.read_physical(6)
                    distance = int.from_bytes(payload[2:], "big")
                    marker = (
                        f"Conker loop end track={track} count={payload[0]} "
                        f"current={payload[1]} back={distance}"
                    ).encode("ascii")
                    exact = b"CONKER_CSEQ\x00" + bytes((meta_type,)) + payload
                    conductor_events.extend(
                        (
                            (tick, track, order, _meta_event(0x06, marker)),
                            (tick, track, order + 1, _meta_event(0x7F, exact)),
                        )
                    )
                    loop_marker_count += 1
                    running_status = 0
                else:
                    raise ValueError(
                        f"compact sequence track {track}: unsupported meta event "
                        f"0x{meta_type:02X}"
                    )
            else:
                if status & 0x80:
                    message_type = status & 0xF0
                    if not 0x80 <= message_type <= 0xE0:
                        raise ValueError(
                            f"compact sequence track {track}: unsupported MIDI status "
                            f"0x{status:02X}"
                        )
                    running_status = message_type | track
                    first = reader.read_byte()
                else:
                    if running_status == 0:
                        raise ValueError(
                            f"compact sequence track {track}: running status is unset"
                        )
                    message_type = running_status & 0xF0
                    first = status
                if first & 0x80:
                    raise ValueError(
                        f"compact sequence track {track}: MIDI data byte has its high bit set"
                    )

                message = bytearray((running_status, first))
                duration = None
                if message_type not in (0xC0, 0xD0):
                    second = reader.read_byte()
                    if second & 0x80:
                        raise ValueError(
                            f"compact sequence track {track}: MIDI data byte has its high bit set"
                        )
                    message.append(second)
                    if message_type == 0x90:
                        duration = reader.read_varlen()
                        note_count += 1
                priority = 0 if message_type == 0x80 else 1
                track_events.append((tick, priority, order, bytes(message)))
                if duration is not None:
                    note_off_priority = 2 if duration == 0 else 0
                    track_events.append(
                        (
                            tick + duration,
                            note_off_priority,
                            order,
                            bytes((0x80 | track, first, 0)),
                        )
                    )
            order += 2
            if source_event_count > 1_000_000:
                raise ValueError("compact sequence exceeds the event safety limit")
            delta = reader.read_varlen()

        track_end_tick = max((event[0] for event in track_events), default=tick)
        sequence_end_tick = max(sequence_end_tick, track_end_tick)
        midi_tracks.append((f"CSeq track {track}", track_events, track_end_tick))

    conductor = _midi_track("Conker CSeq conductor", conductor_events, sequence_end_tick)
    tracks = b"".join(
        _midi_track(name, events, end_tick) for name, events, end_tick in midi_tracks
    )
    midi_header = b"MThd" + struct.pack(">IHHH", 6, 1, len(midi_tracks) + 1, division)
    return CompactSequencePreview(
        midi=midi_header + conductor + tracks,
        active_tracks=len(midi_tracks),
        source_events=source_event_count,
        notes=note_count,
        loop_markers=loop_marker_count,
        end_tick=sequence_end_tick,
    )


def parse_sound_bank_control(data: bytes) -> SoundBankSummary:
    if len(data) < 8:
        raise ValueError("sound-bank control is shorter than its header")
    revision, bank_count = struct.unpack_from(">HH", data)
    if revision != AL_BANK_VERSION:
        raise ValueError(
            f"sound-bank revision is 0x{revision:04X}; expected 0x{AL_BANK_VERSION:04X}"
        )
    if bank_count <= 0 or 4 + bank_count * 4 > len(data):
        raise ValueError("sound-bank control has an invalid bank count")

    bank_offsets = struct.unpack_from(f">{bank_count}I", data, 4)
    if len(set(bank_offsets)) != len(bank_offsets):
        raise ValueError("sound-bank control contains duplicate bank offsets")
    for bank_offset in bank_offsets:
        if bank_offset % 4 or bank_offset + 12 > len(data):
            raise ValueError("sound-bank control contains an invalid bank offset")

    first_bank = bank_offsets[0]
    instrument_count, flags, _padding, sample_rate = struct.unpack_from(
        ">HBBI", data, first_bank
    )
    if flags != 0:
        raise ValueError("sound-bank control is already runtime-patched")
    if first_bank + 12 + instrument_count * 4 > len(data):
        raise ValueError("sound-bank instrument pointer array exceeds the control file")
    if sample_rate <= 0:
        raise ValueError("sound-bank sample rate is not positive")
    return SoundBankSummary(
        revision=revision,
        bank_offsets=tuple(bank_offsets),
        instrument_count=instrument_count,
        sample_rate=sample_rate,
    )


def _require_range(data: bytes, offset: int, length: int, label: str) -> None:
    if offset < 0 or length < 0 or offset + length > len(data):
        raise ValueError(f"{label} exceeds its source payload")


def decode_external_bank_offset(encoded_address: int) -> int:
    """Decode the external-bank object offset used by Conker's fetch callbacks."""

    return (encoded_address >> 5) & ~7


def decode_n64_vadpcm(
    data: bytes,
    coefficients: list[int] | tuple[int, ...],
    order: int,
    predictor_count: int,
    initial_state: tuple[int, ...] | None = None,
) -> tuple[int, ...]:
    """Decode whole Nintendo 64 VADPCM frames to signed 16-bit PCM."""

    if len(data) % 9:
        raise ValueError("N64 ADPCM payload length is not a multiple of nine")
    if order <= 0 or predictor_count <= 0:
        raise ValueError("N64 ADPCM book has invalid dimensions")
    if len(coefficients) != order * predictor_count * 8:
        raise ValueError("N64 ADPCM book has an invalid coefficient count")
    if initial_state is None:
        history = [0] * order
    elif len(initial_state) != order:
        raise ValueError("N64 ADPCM initial state does not match the book order")
    else:
        history = list(initial_state)

    decoded: list[int] = []
    for frame_offset in range(0, len(data), 9):
        frame = data[frame_offset : frame_offset + 9]
        scale = 1 << (frame[0] >> 4)
        predictor = frame[0] & 0x0F
        if predictor >= predictor_count:
            raise ValueError(
                f"N64 ADPCM frame at 0x{frame_offset:X} selects predictor "
                f"{predictor}, but its book has {predictor_count}"
            )
        book_offset = predictor * order * 8
        residuals = [
            (nibble - 16 if nibble & 8 else nibble) * scale
            for byte in frame[1:]
            for nibble in (byte >> 4, byte & 0x0F)
        ]

        for vector_index in range(2):
            vector = residuals[vector_index * 8 : vector_index * 8 + 8]
            output_vector: list[int] = []
            for sample_index, residual in enumerate(vector):
                accumulator = sum(
                    coefficients[book_offset + coefficient_order * 8 + sample_index]
                    * history[coefficient_order]
                    for coefficient_order in range(order)
                )
                for prior_index in range(sample_index - 1, -1, -1):
                    for coefficient_order in range(1, order):
                        accumulator += (
                            vector[(sample_index - 1) - prior_index]
                            * coefficients[
                                book_offset + coefficient_order * 8 + prior_index
                            ]
                        )
                sample = (residual * 2048 + accumulator) >> 11
                output_vector.append(max(-32768, min(32767, sample)))
            decoded.extend(output_vector)
            history = output_vector[-order:]
    return tuple(decoded)


def pcm16_mono_wav(samples: tuple[int, ...], sample_rate: int) -> bytes:
    """Build a deterministic mono PCM16 RIFF/WAVE file."""

    if sample_rate <= 0:
        raise ValueError("WAV sample rate must be positive")
    pcm = array("h", samples)
    if sys.byteorder != "little":
        pcm.byteswap()
    payload = pcm.tobytes()
    format_chunk = struct.pack(
        "<HHIIHH", 1, 1, sample_rate, sample_rate * 2, 2, 16
    )
    return (
        b"RIFF"
        + struct.pack("<I", 4 + 8 + len(format_chunk) + 8 + len(payload))
        + b"WAVEfmt "
        + struct.pack("<I", len(format_chunk))
        + format_chunk
        + b"data"
        + struct.pack("<I", len(payload))
        + payload
    )


def parse_sound_bank_graph(
    control: bytes, external: bytes, wavetable_data: bytes
) -> SoundBankGraph:
    """Parse the complete US B1 graph without assigning semantic names."""

    summary = parse_sound_bank_control(control)
    if len(summary.bank_offsets) != 1:
        raise ValueError("sound-bank graph parser expects one bank")
    bank_offset = summary.bank_offsets[0]
    _require_range(control, bank_offset, 12 + summary.instrument_count * 4, "bank")
    instrument_addresses = struct.unpack_from(
        f">{summary.instrument_count}I", control, bank_offset + 12
    )
    if not instrument_addresses or instrument_addresses[0] == 0:
        raise ValueError("sound bank has no embedded first instrument")
    percussion_offset = struct.unpack_from(">I", control, bank_offset + 8)[0]
    if percussion_offset:
        raise ValueError("US sound-bank percussion pointer was expected to be null")

    instrument_records: list[dict[str, Any]] = []
    sound_specs: list[tuple[int, int, int, int, str, int, int]] = []

    def add_instrument(
        index: int,
        source: bytes,
        source_name: str,
        offset: int,
        encoded_address: int | None,
    ) -> None:
        _require_range(source, offset, 16, f"instrument {index}")
        fields = struct.unpack_from(">12Bhh", source, offset)
        sound_count = fields[13]
        if sound_count < 0:
            raise ValueError(f"instrument {index} has a negative sound count")
        _require_range(
            source,
            offset + 16,
            sound_count * 4,
            f"instrument {index} sound array",
        )
        if fields[3] != 0:
            raise ValueError(f"instrument {index} is already runtime-patched")
        sound_addresses = struct.unpack_from(
            f">{sound_count}I", source, offset + 16
        )
        sound_indices: list[int] = []
        for instrument_sound_index, address in enumerate(sound_addresses):
            if address == 0:
                raise ValueError(
                    f"instrument {index} sound {instrument_sound_index} is null"
                )
            if source_name == "control":
                sound_offset = decode_external_bank_offset(address)
                relative_base = sound_offset
                pointer_kind = "encoded-external"
            else:
                sound_offset = offset + address
                relative_base = offset
                pointer_kind = "instrument-relative"
            sound_index = len(sound_specs)
            sound_indices.append(sound_index)
            sound_specs.append(
                (
                    sound_index,
                    index,
                    instrument_sound_index,
                    sound_offset,
                    pointer_kind,
                    relative_base,
                    address,
                )
            )
        instrument_records.append(
            {
                "index": index,
                "storage": source_name,
                "offset": f"0x{offset:X}",
                "bank_pointer": f"0x{encoded_address if encoded_address is not None else offset:X}",
                "bank_pointer_kind": (
                    "encoded-external"
                    if encoded_address is not None
                    else "control-relative"
                ),
                "encoded_address": (
                    f"0x{encoded_address:X}" if encoded_address is not None else None
                ),
                "volume": fields[0],
                "pan": fields[1],
                "priority": fields[2],
                "flags": fields[3],
                "tremolo": {
                    "type": fields[4],
                    "rate": fields[5],
                    "depth": fields[6],
                    "delay": fields[7],
                },
                "vibrato": {
                    "type": fields[8],
                    "rate": fields[9],
                    "depth": fields[10],
                    "delay": fields[11],
                },
                "bend_range": fields[12],
                "sound_count": sound_count,
                "sound_indices": sound_indices,
            }
        )

    add_instrument(
        0,
        control,
        "control",
        instrument_addresses[0],
        None,
    )
    for index, encoded_address in enumerate(instrument_addresses[1:], 1):
        if encoded_address == 0:
            raise ValueError(f"instrument slot {index} is null")
        add_instrument(
            index,
            external,
            "external",
            decode_external_bank_offset(encoded_address),
            encoded_address,
        )

    envelope_records: list[dict[str, Any]] = []
    key_map_records: list[dict[str, Any]] = []
    book_records: list[dict[str, Any]] = []
    loop_records: list[dict[str, Any]] = []
    wavetable_records: list[dict[str, Any]] = []
    sound_records: list[dict[str, Any]] = []
    envelope_indices: dict[int, int] = {}
    key_map_indices: dict[int, int] = {}
    book_indices: dict[int, int] = {}
    loop_indices: dict[tuple[str, int], int] = {}
    wavetable_indices: dict[int, int] = {}

    def parse_envelope(offset: int) -> int:
        if offset in envelope_indices:
            return envelope_indices[offset]
        _require_range(external, offset, 16, "envelope")
        attack, decay, release, attack_volume, decay_volume, padding = (
            struct.unpack_from(">iiiBBH", external, offset)
        )
        index = len(envelope_records)
        envelope_indices[offset] = index
        envelope_records.append(
            {
                "index": index,
                "offset": f"0x{offset:X}",
                "attack_time_us": attack,
                "decay_time_us": decay,
                "release_time_us": release,
                "attack_volume": attack_volume,
                "decay_volume": decay_volume,
                "padding": f"0x{padding:04X}",
            }
        )
        return index

    def parse_key_map(offset: int) -> int:
        if offset in key_map_indices:
            return key_map_indices[offset]
        _require_range(external, offset, 6, "key map")
        velocity_min, velocity_max, key_min, key_max, key_base, detune = (
            struct.unpack_from(">BBBBBb", external, offset)
        )
        index = len(key_map_records)
        key_map_indices[offset] = index
        key_map_records.append(
            {
                "index": index,
                "offset": f"0x{offset:X}",
                "velocity_min": velocity_min,
                "velocity_max": velocity_max,
                "key_min": key_min,
                "key_max": key_max,
                "key_base": key_base,
                "detune": detune,
            }
        )
        return index

    def parse_book(offset: int) -> int:
        if offset in book_indices:
            return book_indices[offset]
        _require_range(external, offset, 8, "ADPCM book")
        order, predictor_count = struct.unpack_from(">ii", external, offset)
        if order <= 0 or predictor_count <= 0:
            raise ValueError(f"ADPCM book at 0x{offset:X} has invalid dimensions")
        coefficient_count = 8 * order * predictor_count
        _require_range(
            external,
            offset + 8,
            coefficient_count * 2,
            "ADPCM book coefficients",
        )
        coefficients = struct.unpack_from(
            f">{coefficient_count}h", external, offset + 8
        )
        index = len(book_records)
        book_indices[offset] = index
        book_records.append(
            {
                "index": index,
                "offset": f"0x{offset:X}",
                "order": order,
                "predictor_count": predictor_count,
                "coefficients": list(coefficients),
            }
        )
        return index

    def parse_loop(kind: str, offset: int) -> int:
        key = (kind, offset)
        if key in loop_indices:
            return loop_indices[key]
        size = 44 if kind == "adpcm" else 12
        _require_range(external, offset, size, f"{kind} loop")
        start, end, count = struct.unpack_from(">III", external, offset)
        if start > end:
            raise ValueError(f"{kind} loop at 0x{offset:X} has an invalid range")
        record: dict[str, Any] = {
            "index": len(loop_records),
            "offset": f"0x{offset:X}",
            "kind": kind,
            "start_sample": start,
            "end_sample": end,
            "count": count,
        }
        if kind == "adpcm":
            record["state"] = list(struct.unpack_from(">16h", external, offset + 12))
        index = len(loop_records)
        loop_indices[key] = index
        loop_records.append(record)
        return index

    sample_keys: set[tuple[int, int, str]] = set()

    def parse_wavetable(offset: int, relative_base: int) -> int:
        if offset in wavetable_indices:
            return wavetable_indices[offset]
        _require_range(external, offset, 20, "wavetable")
        base, length, wave_type, flags, padding, loop_pointer, book_pointer = (
            struct.unpack_from(">IiBBHII", external, offset)
        )
        if length <= 0 or base + length > len(wavetable_data):
            raise ValueError(f"wavetable at 0x{offset:X} has an invalid sample range")
        if flags != 0:
            raise ValueError(f"wavetable at 0x{offset:X} is already runtime-patched")
        if wave_type == 0:
            kind = "adpcm"
            _require_range(external, offset, 24, "Conker ADPCM wavetable")
            extra = struct.unpack_from(">I", external, offset + 20)[0]
            if book_pointer == 0:
                raise ValueError(f"ADPCM wavetable at 0x{offset:X} has no book")
            book_index = parse_book(relative_base + book_pointer)
            loop_index = (
                parse_loop(kind, relative_base + loop_pointer)
                if loop_pointer
                else None
            )
        elif wave_type == 1:
            kind = "raw16"
            extra = None
            book_index = None
            loop_index = (
                parse_loop(kind, relative_base + loop_pointer)
                if loop_pointer
                else None
            )
        else:
            raise ValueError(f"wavetable at 0x{offset:X} has unknown type {wave_type}")
        sample_keys.add((base, length, kind))
        index = len(wavetable_records)
        wavetable_indices[offset] = index
        wavetable_records.append(
            {
                "index": index,
                "offset": f"0x{offset:X}",
                "base": f"0x{base:X}",
                "stored_length": length,
                "kind": kind,
                "flags": flags,
                "padding": f"0x{padding:04X}",
                "loop_index": loop_index,
                "book_index": book_index,
                "loop_pointer": f"0x{loop_pointer:X}",
                "book_pointer": f"0x{book_pointer:X}",
                "conker_field_0x14": extra,
                "sample_key": (base, length, kind),
            }
        )
        return index

    seen_sound_offsets: set[int] = set()
    for (
        sound_index,
        instrument_index,
        instrument_sound_index,
        sound_offset,
        pointer_kind,
        relative_base,
        pointer_value,
    ) in sound_specs:
        if sound_offset in seen_sound_offsets:
            raise ValueError(f"sound at 0x{sound_offset:X} is referenced more than once")
        seen_sound_offsets.add(sound_offset)
        _require_range(external, sound_offset, 16, f"sound {sound_index}")
        envelope_pointer, key_map_pointer, wavetable_pointer, pan, volume, flags, padding = (
            struct.unpack_from(">IIIBBBB", external, sound_offset)
        )
        if flags != 0:
            raise ValueError(f"sound {sound_index} is already runtime-patched")
        envelope_index = parse_envelope(relative_base + envelope_pointer)
        key_map_index = parse_key_map(relative_base + key_map_pointer)
        wavetable_index = parse_wavetable(
            relative_base + wavetable_pointer, relative_base
        )
        sound_records.append(
            {
                "index": sound_index,
                "instrument_index": instrument_index,
                "instrument_sound_index": instrument_sound_index,
                "offset": f"0x{sound_offset:X}",
                "pointer_kind": pointer_kind,
                "pointer_value": f"0x{pointer_value:X}",
                "relative_base": f"0x{relative_base:X}",
                "envelope_pointer": f"0x{envelope_pointer:X}",
                "key_map_pointer": f"0x{key_map_pointer:X}",
                "wavetable_pointer": f"0x{wavetable_pointer:X}",
                "pan": pan,
                "volume": volume,
                "flags": flags,
                "padding": padding,
                "envelope_index": envelope_index,
                "key_map_index": key_map_index,
                "wavetable_index": wavetable_index,
            }
        )

    sorted_sample_keys = sorted(sample_keys)
    sample_indices = {key: index for index, key in enumerate(sorted_sample_keys)}
    sample_records: list[dict[str, Any]] = []
    sample_ranges: list[tuple[int, int]] = []
    for index, (base, length, kind) in enumerate(sorted_sample_keys):
        end = base + length
        if sample_ranges and base < sample_ranges[-1][1]:
            raise ValueError("distinct sound-bank sample ranges overlap")
        sample_ranges.append((base, end))
        runtime_length = length - (length % 9) if kind == "adpcm" else length
        sample_records.append(
            {
                "index": index,
                "base": f"0x{base:X}",
                "stored_length": length,
                "runtime_payload_length": runtime_length,
                "trailing_bytes": length - runtime_length,
                "kind": kind,
                "wavetable_indices": [],
            }
        )
    for record in wavetable_records:
        key = tuple(record.pop("sample_key"))
        sample_index = sample_indices[key]
        record["sample_index"] = sample_index
        sample_records[sample_index]["wavetable_indices"].append(record["index"])

    referenced_bytes = sum(end - start for start, end in sample_ranges)
    manifest = {
        "schema_version": 1,
        "family": "conker-b1-sound-bank-graph",
        "pointer_encoding": {
            "external_object_offset": "(encoded_address >> 5) & ~7",
            "instrument_zero_sounds": "encoded-external",
            "other_instrument_sounds": "instrument-relative",
        },
        "bank": {
            "revision": f"0x{summary.revision:04X}",
            "sample_rate": summary.sample_rate,
            "instrument_count": len(instrument_records),
            "percussion_instrument": None,
        },
        "summary": {
            "instrument_count": len(instrument_records),
            "sound_count": len(sound_records),
            "envelope_count": len(envelope_records),
            "key_map_count": len(key_map_records),
            "wavetable_count": len(wavetable_records),
            "adpcm_book_count": len(book_records),
            "loop_count": len(loop_records),
            "unique_sample_count": len(sample_records),
            "referenced_wavetable_bytes": referenced_bytes,
            "unreferenced_wavetable_bytes": len(wavetable_data) - referenced_bytes,
        },
        "instruments": instrument_records,
        "sounds": sound_records,
        "envelopes": envelope_records,
        "key_maps": key_map_records,
        "wavetables": wavetable_records,
        "adpcm_books": book_records,
        "loops": loop_records,
        "samples": sample_records,
    }
    return SoundBankGraph(manifest=manifest, sample_ranges=tuple(sample_ranges))


def parse_compact_sequence_bank(data: bytes) -> tuple[CompactSequence, ...]:
    if len(data) < 12:
        raise ValueError("compact-sequence bank is shorter than its header")
    revision, sequence_count = struct.unpack_from(">HH", data)
    if revision != AL_SEQBANK_VERSION:
        raise ValueError(
            f"sequence-bank revision is 0x{revision:04X}; "
            f"expected 0x{AL_SEQBANK_VERSION:04X}"
        )
    table_end = 4 + sequence_count * 8
    if sequence_count <= 0 or table_end > len(data):
        raise ValueError("compact-sequence bank has an invalid sequence count")

    descriptors = [
        struct.unpack_from(">II", data, 4 + index * 8)
        for index in range(sequence_count)
    ]
    if descriptors[0][0] != table_end:
        raise ValueError("compact-sequence data does not begin after its descriptor table")

    sequences: list[CompactSequence] = []
    for index, (offset, length) in enumerate(descriptors):
        end = offset + length
        next_offset = (
            descriptors[index + 1][0] if index + 1 < sequence_count else len(data)
        )
        if (
            offset % 4
            or length < COMPACT_SEQUENCE_HEADER_SIZE
            or end > next_offset
            or next_offset > len(data)
            or next_offset - end > 3
        ):
            raise ValueError(f"compact sequence {index} has an invalid range")
        padding = data[end:next_offset]

        sequence_data = data[offset:end]
        header = struct.unpack_from(">17I", sequence_data)
        track_offsets = tuple(header[:16])
        division = header[16]
        if division <= 0:
            raise ValueError(f"compact sequence {index} has an invalid division")
        if any(
            track_offset != 0
            and not (COMPACT_SEQUENCE_HEADER_SIZE <= track_offset < length)
            for track_offset in track_offsets
        ):
            raise ValueError(f"compact sequence {index} has an invalid track offset")
        if not any(track_offsets):
            raise ValueError(f"compact sequence {index} has no active tracks")
        sequences.append(
            CompactSequence(
                index=index,
                offset=offset,
                data=sequence_data,
                padding_after=padding,
                track_offsets=track_offsets,
                division=division,
            )
        )
    return tuple(sequences)


def rebuild_compact_sequence_bank(sequences: tuple[CompactSequence, ...]) -> bytes:
    table_end = 4 + len(sequences) * 8
    descriptors = bytearray(struct.pack(">HH", AL_SEQBANK_VERSION, len(sequences)))
    payload = bytearray()
    offset = table_end
    for expected_index, sequence in enumerate(sequences):
        if sequence.index != expected_index:
            raise ValueError("compact-sequence indices are not contiguous")
        descriptors.extend(struct.pack(">II", offset, len(sequence.data)))
        payload.extend(sequence.data)
        payload.extend(sequence.padding_after)
        offset += len(sequence.data) + len(sequence.padding_after)
    rebuilt = bytes(descriptors + payload)
    parse_compact_sequence_bank(rebuilt)
    return rebuilt


def resolve_rom(profile: str, rom_argument: Path | None) -> tuple[Path, dict[str, Any]]:
    if profile != "us":
        raise ValueError("the non-MP3 audio family is currently proven only for US")
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


def load_profile_audio_assets(
    profile: str, rom_argument: Path | None
) -> tuple[Path, bytes, str, NonMp3AudioFamily]:
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(
            f"{profile} normalized ROM SHA-1 mismatch: got {digest}; expected one of "
            + ", ".join(layout["normalized_sha1"])
        )

    banks = parse_asset_banks(normalized, layout["asset_table"])
    if len(banks) <= AUDIO_BANK_INDEX:
        raise ValueError("US asset table does not contain audio bank 0x17")
    bank = banks[AUDIO_BANK_INDEX]
    by_index = {
        entry.index: entry for entry in parse_asset_entries(normalized, bank)
    }
    if not all(index in by_index for index in REQUIRED_ENTRY_INDICES):
        raise ValueError("US audio bank is missing one or more entries 0 through 3")

    assets: list[AudioAsset] = []
    for entry_index in REQUIRED_ENTRY_INDICES:
        entry = by_index[entry_index]
        stored = normalized[entry.start : entry.end]
        data = decode_rzip_chunk(stored).data if entry.compressed else stored
        role, expected_size, expected_flags, expected_compressed = (
            EXPECTED_ENTRY_CONTRACTS[entry_index]
        )
        if (
            len(data) != expected_size
            or entry.type_flags != expected_flags
            or entry.compressed != expected_compressed
        ):
            raise ValueError(f"US audio bank entry {entry_index} violates its contract")
        assets.append(
            AudioAsset(
                entry_index=entry_index,
                role=role,
                data=data,
                rom_start=entry.start,
                rom_end=entry.end,
                type_flags=entry.type_flags,
                compressed=entry.compressed,
            )
        )

    sound_bank = parse_sound_bank_control(assets[0].data)
    family = NonMp3AudioFamily(
        bank_start=bank.start,
        bank_end=bank.end,
        assets=tuple(assets),
        sound_bank=sound_bank,
        sequences=parse_compact_sequence_bank(assets[3].data),
        sound_graph=parse_sound_bank_graph(
            assets[0].data, assets[1].data, assets[2].data
        ),
    )
    validate_family(family)
    return rom_path, normalized, source_order, family


def validate_family(family: NonMp3AudioFamily) -> None:
    if tuple(asset.entry_index for asset in family.assets) != REQUIRED_ENTRY_INDICES:
        raise ValueError("non-MP3 audio entries are not ordered 0 through 3")
    if family.sound_bank.bank_offsets != (8,):
        raise ValueError("US sound-bank control does not contain its one expected bank")
    if family.sound_bank.instrument_count != 170:
        raise ValueError("US sound bank does not contain 170 instruments")
    if family.sound_bank.sample_rate != 22_050:
        raise ValueError("US sound-bank sample rate is not 22050 Hz")
    if family.sound_graph is None:
        raise ValueError("US sound-bank graph was not parsed")
    graph_summary = family.sound_graph.manifest["summary"]
    expected_graph_counts = {
        "instrument_count": 170,
        "sound_count": 2_786,
        "envelope_count": 2_786,
        "key_map_count": 2_786,
        "wavetable_count": 2_786,
        "adpcm_book_count": 2_786,
        "loop_count": 491,
        "unique_sample_count": 2_258,
        "referenced_wavetable_bytes": 21_698_538,
        "unreferenced_wavetable_bytes": 6_982,
    }
    if any(
        graph_summary[key] != expected
        for key, expected in expected_graph_counts.items()
    ):
        raise ValueError("US sound-bank graph violates its reviewed node counts")
    if len(family.sequences) != 149:
        raise ValueError("US compact-sequence bank does not contain 149 sequences")


def extract_audio_assets(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    rom_path, normalized, source_order, family = load_profile_audio_assets(
        profile, rom_argument
    )
    prepare_output(output, force)
    sequences_dir = output / "sequences"
    sequences_dir.mkdir()

    fixed_files = {
        SOUND_BANK_CONTROL_ENTRY: "sound-bank-control.b1",
        SOUND_BANK_DATA_ENTRY: "sound-bank-data.bin",
        WAVETABLE_ENTRY: "wavetable.bin",
    }
    entry_records: list[dict[str, Any]] = []
    for asset in family.assets:
        record: dict[str, Any] = {
            "entry_index": asset.entry_index,
            "role": asset.role,
            "rom_start": f"0x{asset.rom_start:X}",
            "rom_end": f"0x{asset.rom_end:X}",
            "decoded_size": len(asset.data),
            "type_flags": asset.type_flags,
            "compressed": asset.compressed,
            "decoded_sha1": hashlib.sha1(asset.data).hexdigest(),
        }
        if asset.entry_index in fixed_files:
            filename = fixed_files[asset.entry_index]
            (output / filename).write_bytes(asset.data)
            record["file"] = filename
        entry_records.append(record)

    sequence_records: list[dict[str, Any]] = []
    for sequence in family.sequences:
        filename = f"sequences/{sequence.index:04d}.cseq"
        (output / filename).write_bytes(sequence.data)
        sequence_records.append(
            {
                "index": sequence.index,
                "offset": f"0x{sequence.offset:X}",
                "length": len(sequence.data),
                "alignment_bytes": sequence.padding_after.hex(),
                "active_tracks": sum(offset != 0 for offset in sequence.track_offsets),
                "division": sequence.division,
                "decoded_sha1": hashlib.sha1(sequence.data).hexdigest(),
                "file": filename,
            }
        )

    sound_bank_record: dict[str, Any] = {
        "revision": f"0x{family.sound_bank.revision:04X}",
        "bank_count": len(family.sound_bank.bank_offsets),
        "instrument_count": family.sound_bank.instrument_count,
        "sample_rate": family.sound_bank.sample_rate,
    }
    if family.sound_graph is not None:
        samples_dir = output / "samples"
        samples_dir.mkdir()
        graph_manifest = copy.deepcopy(family.sound_graph.manifest)
        wavetable_data = family.assets[WAVETABLE_ENTRY].data
        for record, (start, end) in zip(
            graph_manifest["samples"], family.sound_graph.sample_ranges, strict=True
        ):
            sample_data = wavetable_data[start:end]
            filename = f"samples/{record['index']:04d}.adpcm"
            (output / filename).write_bytes(sample_data)
            record["file"] = filename
            record["stored_sha1"] = hashlib.sha1(sample_data).hexdigest()
        graph_filename = "sound-bank-graph.json"
        (output / graph_filename).write_text(
            json.dumps(graph_manifest, indent=2) + "\n", encoding="utf-8"
        )
        sound_bank_record.update(
            {
                "graph_file": graph_filename,
                **graph_manifest["summary"],
            }
        )

    manifest = {
        "schema_version": 1,
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(),
        "family": "non-mp3-audio",
        "bank_index": AUDIO_BANK_INDEX,
        "bank_start": f"0x{family.bank_start:X}",
        "bank_end": f"0x{family.bank_end:X}",
        "entries": entry_records,
        "sound_bank": sound_bank_record,
        "sequence_bank": {
            "entry_index": SEQUENCE_BANK_ENTRY,
            "revision": f"0x{AL_SEQBANK_VERSION:04X}",
            "sequence_count": len(sequence_records),
            "sequences": sequence_records,
        },
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def verify_audio_assets(
    profile: str, rom_argument: Path | None
) -> tuple[NonMp3AudioFamily, int, AdpcmLoopValidation]:
    _, _, _, family = load_profile_audio_assets(profile, rom_argument)
    rebuilt = rebuild_compact_sequence_bank(family.sequences)
    if rebuilt != family.assets[SEQUENCE_BANK_ENTRY].data:
        raise ValueError("US compact-sequence bank did not rebuild byte-identically")
    loop_validation = validate_adpcm_loop_states(family)
    return family, sum(len(asset.data) for asset in family.assets), loop_validation


def _graph_decode_context(
    graph: dict[str, Any], sample: dict[str, Any]
) -> tuple[dict[str, Any], dict[str, Any] | None]:
    wavetables = graph["wavetables"]
    books = graph["adpcm_books"]
    loops = graph["loops"]
    referenced_wavetables = [
        wavetables[index] for index in sample["wavetable_indices"]
    ]
    if not referenced_wavetables:
        raise ValueError(f"sample {sample['index']} has no wavetable reference")
    book_records = [books[record["book_index"]] for record in referenced_wavetables]
    book_signatures = {
        (
            record["order"],
            record["predictor_count"],
            tuple(record["coefficients"]),
        )
        for record in book_records
    }
    if len(book_signatures) != 1:
        raise ValueError(f"sample {sample['index']} has conflicting ADPCM books")

    loop_records = [
        loops[record["loop_index"]] if record["loop_index"] is not None else None
        for record in referenced_wavetables
    ]
    loop_signatures = {
        None
        if record is None
        else (
            record["start_sample"],
            record["end_sample"],
            record["count"],
            tuple(record.get("state", ())),
        )
        for record in loop_records
    }
    if len(loop_signatures) != 1:
        raise ValueError(f"sample {sample['index']} has conflicting loop metadata")
    return book_records[0], loop_records[0]


def validate_adpcm_loop_states(family: NonMp3AudioFamily) -> AdpcmLoopValidation:
    """Compare decoded loop frames with the states retained in the B1 graph."""

    if family.sound_graph is None:
        raise ValueError("sound-bank graph is required for ADPCM verification")
    graph = family.sound_graph.manifest
    wavetable_data = family.assets[WAVETABLE_ENTRY].data
    checked = 0
    exact = 0
    maximum_error = 0
    for sample, (start, _end) in zip(
        graph["samples"], family.sound_graph.sample_ranges, strict=True
    ):
        if sample["kind"] != "adpcm":
            continue
        book, loop = _graph_decode_context(graph, sample)
        if loop is None:
            continue
        runtime_length = sample["runtime_payload_length"]
        decoded = decode_n64_vadpcm(
            wavetable_data[start : start + runtime_length],
            book["coefficients"],
            book["order"],
            book["predictor_count"],
        )
        frame_start = (loop["start_sample"] // 16) * 16
        actual = decoded[frame_start : frame_start + 16]
        expected = tuple(loop["state"])
        if len(actual) != 16:
            raise ValueError(f"sample {sample['index']} loop state exceeds decoded PCM")
        error = max(abs(left - right) for left, right in zip(actual, expected))
        checked += 1
        maximum_error = max(maximum_error, error)
        exact += error == 0
    if checked == 0:
        raise ValueError("sound-bank graph contains no ADPCM loop states")
    if maximum_error > 2:
        raise ValueError(
            f"decoded ADPCM loop states diverge by {maximum_error} PCM levels"
        )
    return AdpcmLoopValidation(checked, exact, maximum_error)


def preview_compact_sequence_files(
    input_path: Path, output: Path | None, force: bool
) -> tuple[Path, int, int, int]:
    if not input_path.is_absolute():
        input_path = ROOT / input_path
    if not input_path.exists():
        raise ValueError(f"preview input does not exist: {display_path(input_path)}")

    if input_path.is_file():
        if input_path.suffix.lower() != ".cseq":
            raise ValueError("preview input file must use the .cseq extension")
        output_path = output or input_path.with_suffix(".mid")
        if not output_path.is_absolute():
            output_path = ROOT / output_path
        if output_path.suffix.lower() != ".mid":
            raise ValueError("preview output file must use the .mid extension")
        if output_path.resolve() == input_path.resolve():
            raise ValueError("preview output cannot overwrite its CSeq input")
        if output_path.exists() and not force:
            raise ValueError(
                f"preview output already exists: {display_path(output_path)}"
            )
        output_path.parent.mkdir(parents=True, exist_ok=True)
        preview = compact_sequence_to_midi(input_path.read_bytes())
        output_path.write_bytes(preview.midi)
        return output_path, 1, preview.notes, preview.loop_markers

    inputs = sorted(input_path.glob("*.cseq"))
    if not inputs:
        raise ValueError(
            f"preview directory contains no .cseq files: {display_path(input_path)}"
        )
    output_path = output or (input_path.parent / "midi-preview")
    if not output_path.is_absolute():
        output_path = ROOT / output_path
    resolved_input = input_path.resolve()
    resolved_output = output_path.resolve()
    if resolved_output == resolved_input or resolved_output in resolved_input.parents:
        raise ValueError("preview output cannot contain its CSeq input directory")
    prepare_output(output_path, force)

    records: list[dict[str, Any]] = []
    total_notes = 0
    total_loops = 0
    for source in inputs:
        source_data = source.read_bytes()
        preview = compact_sequence_to_midi(source_data)
        target = output_path / f"{source.stem}.mid"
        target.write_bytes(preview.midi)
        total_notes += preview.notes
        total_loops += preview.loop_markers
        records.append(
            {
                "source": source.name,
                "source_sha1": hashlib.sha1(source_data).hexdigest(),
                "file": target.name,
                "midi_sha1": hashlib.sha1(preview.midi).hexdigest(),
                "active_tracks": preview.active_tracks,
                "source_events": preview.source_events,
                "notes": preview.notes,
                "loop_markers": preview.loop_markers,
                "end_tick": preview.end_tick,
            }
        )
    manifest = {
        "schema_version": 1,
        "family": "conker-cseq-midi-preview",
        "playback": "single-pass",
        "instrumentation": "generic-midi",
        "sequence_count": len(records),
        "sequences": records,
    }
    (output_path / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return output_path, len(records), total_notes, total_loops


def preview_adpcm_sample_files(
    input_path: Path, output: Path | None, force: bool
) -> tuple[Path, int, int, float]:
    """Decode an extracted B1 sample directory into playable PCM WAV files."""

    if not input_path.is_absolute():
        input_path = ROOT / input_path
    graph_path = input_path / "sound-bank-graph.json"
    if not graph_path.is_file():
        raise ValueError(
            f"sample preview input has no sound-bank graph: {display_path(graph_path)}"
        )
    graph = json.loads(graph_path.read_text(encoding="utf-8"))
    if graph.get("family") != "conker-b1-sound-bank-graph":
        raise ValueError("sample preview input has an unsupported graph family")

    output_path = output or (input_path / "wav-preview")
    if not output_path.is_absolute():
        output_path = ROOT / output_path
    resolved_input = input_path.resolve()
    resolved_output = output_path.resolve()
    if resolved_output == resolved_input or resolved_output in resolved_input.parents:
        raise ValueError("sample preview output cannot contain its extracted input")
    prepare_output(output_path, force)

    sample_rate = graph["bank"]["sample_rate"]
    records: list[dict[str, Any]] = []
    total_pcm_samples = 0
    looped_samples = 0
    for sample in graph["samples"]:
        if sample["kind"] != "adpcm":
            raise ValueError(
                f"sample {sample['index']} uses unsupported kind {sample['kind']}"
            )
        source = (input_path / sample["file"]).resolve()
        if resolved_input not in source.parents or not source.is_file():
            raise ValueError(f"sample {sample['index']} has an unsafe or missing file")
        encoded = source.read_bytes()
        if (
            sample.get("stored_sha1")
            and hashlib.sha1(encoded).hexdigest() != sample["stored_sha1"]
        ):
            raise ValueError(f"sample {sample['index']} no longer matches its source hash")
        runtime_length = sample["runtime_payload_length"]
        if runtime_length > len(encoded):
            raise ValueError(f"sample {sample['index']} runtime payload is truncated")
        book, loop = _graph_decode_context(graph, sample)
        decoded = decode_n64_vadpcm(
            encoded[:runtime_length],
            book["coefficients"],
            book["order"],
            book["predictor_count"],
        )
        filename = f"{sample['index']:04d}.wav"
        wav = pcm16_mono_wav(decoded, sample_rate)
        (output_path / filename).write_bytes(wav)
        pcm_payload = wav[44:]
        record: dict[str, Any] = {
            "index": sample["index"],
            "source": sample["file"],
            "source_sha1": hashlib.sha1(encoded).hexdigest(),
            "file": filename,
            "wav_sha1": hashlib.sha1(wav).hexdigest(),
            "pcm_sha1": hashlib.sha1(pcm_payload).hexdigest(),
            "sample_rate": sample_rate,
            "sample_count": len(decoded),
            "duration_seconds": len(decoded) / sample_rate,
            "book_index": book["index"],
            "wavetable_indices": sample["wavetable_indices"],
            "loop": None,
        }
        if loop is not None:
            record["loop"] = {
                "start_sample": loop["start_sample"],
                "end_sample": loop["end_sample"],
                "count": loop["count"],
            }
            looped_samples += 1
        records.append(record)
        total_pcm_samples += len(decoded)

    manifest = {
        "schema_version": 1,
        "family": "conker-b1-pcm-preview",
        "source_root": "..",
        "source_graph": "../sound-bank-graph.json",
        "encoding": "mono signed 16-bit little-endian PCM",
        "sample_rate": sample_rate,
        "sample_count": len(records),
        "looped_sample_count": looped_samples,
        "total_pcm_samples": total_pcm_samples,
        "total_duration_seconds": total_pcm_samples / sample_rate,
        "editable_import_supported": False,
        "samples": records,
    }
    (output_path / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return output_path, len(records), looped_samples, total_pcm_samples / sample_rate


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)

    for command in ("survey", "verify"):
        command_parser = subparsers.add_parser(command)
        command_parser.add_argument("--profile", choices=("us",), default="us")
        command_parser.add_argument("--rom", type=Path)

    extract_parser = subparsers.add_parser("extract")
    extract_parser.add_argument("--profile", choices=("us",), default="us")
    extract_parser.add_argument("--rom", type=Path)
    extract_parser.add_argument("--output", type=Path)
    extract_parser.add_argument("--force", action="store_true")

    preview_parser = subparsers.add_parser("preview")
    preview_parser.add_argument("--input", type=Path, required=True)
    preview_parser.add_argument("--output", type=Path)
    preview_parser.add_argument("--force", action="store_true")

    sample_preview_parser = subparsers.add_parser("sample-preview")
    sample_preview_parser.add_argument(
        "--input", type=Path, default=Path("build/assets/audio/us")
    )
    sample_preview_parser.add_argument("--output", type=Path)
    sample_preview_parser.add_argument("--force", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        if args.command == "extract":
            output = args.output or (ROOT / "build" / "assets" / "audio" / args.profile)
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_audio_assets(args.profile, args.rom, output, args.force)
            print(
                f"Extracted US non-MP3 audio: {manifest['sound_bank']['instrument_count']} "
                f"instruments, {manifest['sound_bank'].get('sound_count', 0)} sounds, "
                f"{manifest['sound_bank'].get('unique_sample_count', 0)} unique sample "
                f"ranges, and {manifest['sequence_bank']['sequence_count']} compact "
                f"sequences to {display_path(output)}"
            )
        elif args.command == "preview":
            output, count, notes, loops = preview_compact_sequence_files(
                args.input, args.output, args.force
            )
            print(
                f"Prepared {count} single-pass MIDI preview(s) with {notes} notes "
                f"and {loops} retained Conker loop markers at {display_path(output)}"
            )
        elif args.command == "sample-preview":
            output, count, looped, duration = preview_adpcm_sample_files(
                args.input, args.output, args.force
            )
            print(
                f"Prepared {count} mono PCM WAV preview(s), including {looped} "
                f"looped samples and {duration:.1f} seconds of source audio, at "
                f"{display_path(output)}"
            )
        else:
            family, size, loop_validation = verify_audio_assets(args.profile, args.rom)
            verb = "Surveyed" if args.command == "survey" else "Verified"
            suffix = "" if args.command == "survey" else ", byte-identical sequence bank"
            graph_summary = family.sound_graph.manifest["summary"]
            print(
                f"{verb} US non-MP3 audio: 4 bank entries, "
                f"{family.sound_bank.instrument_count} instruments, "
                f"{graph_summary['sound_count']} sounds, "
                f"{graph_summary['unique_sample_count']} unique samples, "
                f"{len(family.sequences)} compact sequences, {size} decoded bytes{suffix}"
                f", {loop_validation.exact_frames}/{loop_validation.checked_samples} "
                f"exact ADPCM loop-state frames (maximum error "
                f"{loop_validation.maximum_error} PCM levels)"
            )
    except (OSError, TypeError, ValueError) as error:
        print(f"error: {error}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
