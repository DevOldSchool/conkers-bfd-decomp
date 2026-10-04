"""Render local B1/CSeq listening previews; never infer names from track order."""

from __future__ import annotations

import hashlib
import json
import math
import shutil
import struct
import tempfile
import wave
from collections import Counter, deque
from pathlib import Path
from typing import Any

from scripts import audio_assets, mp3_assets

ROOT = audio_assets.ROOT
LIMITATIONS = [
    "Approximate game-sample render, not native N64 playback or the album recording.",
    "One linear sequence pass; CSeq finite and infinite loops are not expanded.",
    "All tracks sound together; game-driven channel mutes, fades and sequence volume are absent.",
    "Envelopes and resampling are approximated; native filters, reverb, vibrato and tremolo are absent.",
    "Channel volume, pan and pitch bend are sampled at note-on; later changes and sustain are not reproduced.",
    "ADPCM sample loops repeat while a note sounds; finite sample-loop counts are approximated as continuous.",
    "Only nominated MP3 comparison candidates are included; other MP3 streams may contain voices, effects or music.",
]


def checked_file(root: Path, filename: str, digest: str | None = None) -> Path:
    path = (root / filename).resolve()
    if root.resolve() not in path.parents or not path.is_file():
        raise ValueError("manifest contains an unsafe or missing file")
    if digest and hashlib.sha1(path.read_bytes()).hexdigest() != digest:
        raise ValueError(f"source hash mismatch: {filename}")
    return path


def midi_events(data: bytes) -> tuple[int, list[tuple[int, int, bytes]]]:
    """Read the deterministic SMF emitted by compact_sequence_to_midi."""
    if len(data) < 14 or data[:8] != b"MThd\x00\x00\x00\x06":
        raise ValueError("invalid preview MIDI header")
    fmt, count, division = struct.unpack_from(">HHH", data, 8)
    if fmt != 1 or not 0 < division < 0x8000:
        raise ValueError("unsupported preview MIDI format")
    events = []
    offset = 14
    order = 0
    for _ in range(count):
        if data[offset:offset + 4] != b"MTrk":
            raise ValueError("missing MIDI track")
        length = int.from_bytes(data[offset + 4:offset + 8], "big")
        pos, end = offset + 8, offset + 8 + length
        if end > len(data):
            raise ValueError("truncated MIDI track")
        tick, running = 0, 0

        def varlen() -> int:
            nonlocal pos
            value = 0
            for _ in range(4):
                if pos >= end:
                    raise ValueError("truncated MIDI variable integer")
                byte = data[pos]
                pos += 1
                value = (value << 7) | (byte & 127)
                if byte < 128:
                    return value
            raise ValueError("oversized MIDI variable integer")

        while pos < end:
            tick += varlen()
            if pos >= end:
                raise ValueError("missing MIDI event")
            status = data[pos]
            if status >= 128:
                pos += 1
            elif running:
                status = running
            else:
                raise ValueError("unset MIDI running status")
            if status == 255:
                if pos >= end:
                    raise ValueError("truncated MIDI meta event")
                kind = data[pos]
                pos += 1
                size = varlen()
                message = bytes((255, kind)) + data[pos:pos + size]
                pos += size
                running = 0
            elif 0x80 <= status <= 0xEF:
                size = 1 if status & 0xF0 in (0xC0, 0xD0) else 2
                message = bytes((status,)) + data[pos:pos + size]
                pos += size
                running = status
            else:
                raise ValueError("unsupported MIDI event")
            if pos > end:
                raise ValueError("truncated MIDI event")
            events.append((tick, order, message))
            order += 1
        offset = end
    if offset != len(data):
        raise ValueError("unexpected MIDI trailing bytes")
    return division, sorted(events)


def schedule_notes(data: bytes, instrument_count: int) -> tuple[list[dict], dict]:
    division, events = midi_events(data)
    # The reconstructed __n_initFromBank starts with the first instrument after 0.
    channels = [dict(major=0, instrument=1, volume=127, pan=64, bend=0) for _ in range(16)]
    pending: dict[tuple[int, int], deque] = {}
    notes: list[dict] = []
    tick, seconds, tempo = 0, 0.0, 500_000
    controllers: Counter = Counter()
    bends = 0
    for event_tick, _, message in events:
        seconds += (event_tick - tick) * tempo / (division * 1_000_000)
        tick = event_tick
        status, kind, channel = message[0], message[0] & 0xF0, message[0] & 15
        if status == 255:
            if message[1] == 0x51:
                if len(message) != 5 or int.from_bytes(message[2:], "big") == 0:
                    raise ValueError("invalid MIDI tempo")
                tempo = int.from_bytes(message[2:], "big")
            continue
        state = channels[channel]
        key = message[1]
        if kind == 0xB0:
            value = message[2]
            controllers[key] += 1
            field = {7: "volume", 10: "pan", 32: "major"}.get(key)
            if field:
                state[field] = value
        elif kind == 0xC0:
            instrument = (state["major"] << 7) + key
            if instrument < instrument_count:
                state["instrument"] = instrument
        elif kind == 0xE0:
            state["bend"] = ((message[2] << 7) + key - 8192) * 200 / 8192
            bends += 1
        elif kind == 0x90 and message[2] > 0:
            note = dict(state, key=key, velocity=message[2], start=seconds, channel=channel)
            pending.setdefault((channel, key), deque()).append(note)
        elif kind == 0x80 or (kind == 0x90 and message[2] == 0):
            queue = pending.get((channel, key))
            if queue:
                note = queue.popleft()
                notes.append(dict(note, end=seconds))
    if any(pending.values()):
        raise ValueError("preview MIDI has unclosed notes")
    return notes, {"controllers": dict(sorted(controllers.items())), "pitch_bend_events": bends}


def lookup_sound(graph: dict, instrument: int, key: int, velocity: int) -> dict | None:
    """Mirror __n_lookupSoundQuick's binary search over sorted key/velocity maps."""
    indices = graph["instruments"][instrument]["sound_indices"]
    left, right = 1, len(indices)
    while left <= right:
        i = (left + right) // 2
        sound = graph["sounds"][indices[i - 1]]
        mapping = graph["key_maps"][sound["key_map_index"]]
        if mapping["key_min"] <= key <= mapping["key_max"] and mapping["velocity_min"] <= velocity <= mapping["velocity_max"]:
            return sound
        if key < mapping["key_min"] or (velocity < mapping["velocity_min"] and key <= mapping["key_max"]):
            right = i - 1
        else:
            left = i + 1
    return None


def render_sequence(midi: bytes, graph: dict, samples: dict, rate: int) -> tuple[bytes, dict]:
    import numpy as np

    notes, diagnostics = schedule_notes(midi, len(graph["instruments"]))
    voices = []
    missed = 0
    end = 0.0
    for note in notes:
        sound = lookup_sound(graph, note["instrument"], note["key"], note["velocity"])
        if sound is None:
            missed += 1
            continue
        mapping = graph["key_maps"][sound["key_map_index"]]
        env = graph["envelopes"][sound["envelope_index"]]
        table = graph["wavetables"][sound["wavetable_index"]]
        release = max(0.016, env["release_time_us"] / 1_000_000)
        end = max(end, note["end"] + release)
        voices.append((note, sound, mapping, env, table, release))
    if end > 900:
        raise ValueError("render exceeds the 15-minute sequence safety limit")
    # No-note entries produce a short silent file rather than minutes of empty loop timing.
    frames = max(rate // 4, math.ceil(end * rate))
    mix = np.zeros((frames, 2), dtype=np.float32)
    used = set()
    for note, sound, mapping, env, table, release in voices:
        start = round(note["start"] * rate)
        count = min(frames - start, math.ceil((note["end"] - note["start"] + release) * rate))
        age = np.arange(count, dtype=np.float64) / rate
        ratio = 2 ** (((note["key"] - mapping["key_base"]) * 100 + mapping["detune"] + note["bend"]) / 1200)
        source = samples[table["sample_index"]]
        used.add(table["sample_index"])
        position = age * graph["bank"]["sample_rate"] * ratio
        loop = graph["loops"][table["loop_index"]] if table["loop_index"] is not None else None
        if loop and loop["count"] and 0 <= loop["start_sample"] < loop["end_sample"] <= len(source):
            loop_start, loop_end = loop["start_sample"], loop["end_sample"]
            position = np.where(position >= loop_end, loop_start + (position - loop_start) % (loop_end - loop_start), position)
        pcm = np.interp(position, np.arange(len(source)), source, left=0, right=0)
        attack = max(0, env["attack_time_us"] / 1_000_000)
        decay = max(0, env["decay_time_us"] / 1_000_000)
        attack_gain, decay_gain = env["attack_volume"] / 127, env["decay_volume"] / 127
        envelope = np.full(count, decay_gain)
        if decay:
            envelope = np.where(age < attack + decay, attack_gain + (decay_gain - attack_gain) * np.clip((age - attack) / decay, 0, 1), envelope)
        if attack:
            envelope = np.where(age < attack, attack_gain * age / attack, envelope)
        envelope *= np.clip((note["end"] - note["start"] + release - age) / release, 0, 1)
        gain = note["velocity"] * sound["volume"] * note["volume"] / 127 ** 3
        pan = min(127, max(0, note["pan"] - 64 + sound["pan"])) / 127
        pcm *= envelope * gain
        mix[start:start + count, 0] += pcm * math.cos(pan * math.pi / 2)
        mix[start:start + count, 1] += pcm * math.sin(pan * math.pi / 2)
    peak = float(np.max(np.abs(mix)))
    # Only attenuate to prevent clipping; never amplify silence or very quiet sequences.
    scale = min(1.0, 0.9 / peak) if peak else 1.0
    payload = (np.clip(mix * scale, -1, 1) * 32767).astype("<i2").tobytes()
    diagnostics.update({"note_count": len(notes), "mapped_notes": len(voices), "unmapped_notes": missed,
                        "sample_ids": sorted(used), "duration_seconds": frames / rate,
                        "peak_before_attenuation": peak, "attenuation": scale,
                        "audible": bool(np.any(mix)), "sample_rate": rate})
    return payload, diagnostics


def standard_mp3_frames(data: bytes) -> bytes:
    """Retain exact MPEG frames, omitting runtime L: callbacks and trailing data."""
    parsed = mp3_assets.parse_mp3_cue_stream(data)
    pieces = []
    cursor = 0
    for cue in parsed.cues:
        pieces.append(data[cursor:cue["record_offset"]])
        cursor = cue["record_offset"] + cue["record_size"]
    pieces.append(data[cursor:parsed.trailing_offset])
    return b"".join(pieces)


def validate_reference_sequences(reference: dict, records: list[dict], rom_sha1: str) -> None:
    """Do not transfer recorded correspondence evidence to changed source bytes."""
    method = reference.get("comparison_method", {})
    if method.get("normalized_rom_sha1", rom_sha1) != rom_sha1:
        raise ValueError("album comparison evidence belongs to a different ROM")
    sources = {item["index"]: item["decoded_sha1"] for item in records}
    for album in [*reference["albums"], *reference.get("additional_albums", [])]:
        for track in album["tracks"]:
            for match in track.get("review", {}).get("matches", []):
                if match["kind"] == "sequence" and sources.get(match["index"]) != match["source_sha1"]:
                    raise ValueError("album comparison sequence source hash mismatch")


def album_names(label: dict, reference: dict) -> dict:
    """Keep title vocabulary separate from asset-match and contributor confidence."""
    matches = [item for item in reference.get("sequence_album_names", []) if item["index"] == label["index"]]
    if len(matches) > 1:
        raise ValueError("multiple preferred album names for one sequence")
    related = [{"album": item["album"], "title": item["title"], "status": item["status"]}
               for item in [*reference.get("comparisons", []), *reference.get("additional_comparisons", [])] if label["index"] in item["sequence_ids"]]
    if not matches:
        return {**label, "album_matches": related}
    match = matches[0]
    album = next(item for item in [*reference["albums"], *reference.get("additional_albums", [])] if item["key"] == match["album"])
    if match["title"] not in {item["title"] for item in album["tracks"]}:
        raise ValueError("preferred title is not in the supplied album listing")
    aliases = [label["name"], *label.get("aliases", []),
               *(item["title"] for item in related if item["title"] != match["title"])]
    return {**label, "aliases": list(dict.fromkeys(alias for alias in aliases if alias)), "album_matches": related,
            "album_title": match["title"], "album_variant": match["variant"],
            "album_match_confidence": match["match_confidence"], "album_match_note": match["note"],
            "album_reference_url": album["url"],
            "album_title_authority": match.get("title_authority", "older-reference-only"),
            "album_title_canonical": match.get("canonical", False)}


def write_preview_page(target: Path, manifest: dict, samples: dict) -> None:
    """Embed metadata so the generated folder can open directly without fetch/CORS."""
    sample_data = {"samples": [{key: sample[key] for key in
                               ("index", "file", "duration_seconds", "sample_rate", "loop")}
                              for sample in samples["samples"]]}
    payload = json.dumps({"manifest": manifest, "samples": sample_data}, ensure_ascii=True).replace("<", "\\u003c")
    template = (ROOT / "scripts/soundtrack-preview/index.html").read_text()
    (target / "index.html").write_text(template.replace("{{PREVIEW_DATA}}", payload))
    for name in ("preview.js", "preview.css"):
        shutil.copyfile(ROOT / "scripts/soundtrack-preview" / name, target / name)
    shutil.copyfile(ROOT / "scripts/preview-common.css", target / "preview-common.css")


def nominated_mp3_streams(input_path: Path | None, reference: dict, rom_sha1: str) -> list[dict]:
    if input_path is None:
        return []
    manifest = json.loads((input_path / "manifest.json").read_text())
    if manifest.get("profile") != "us" or manifest.get("normalized_sha1") != rom_sha1:
        raise ValueError("MP3 and sequence extractions must come from the same reviewed US ROM")
    streams = {item["entry_index"]: item for item in manifest["stream_bank"]["streams"]}
    records = []
    for candidate in reference.get("music_stream_candidates", []):
        index = candidate["index"]
        if index not in streams:
            raise ValueError(f"nominated MP3 stream {index:04d} is missing")
        source = streams[index]
        if candidate.get("source_sha1", source["decoded_sha1"]) != source["decoded_sha1"]:
            raise ValueError("album comparison MP3 source hash mismatch")
        checked_file(input_path, source["file"], source["decoded_sha1"])
        records.append({**candidate, "file": f"music-streams/{index:04d}.mp3",
                        "source_file": f"music-streams/sources/{index:04d}.mp3",
                        "source_sha1": source["decoded_sha1"]})
    return records


def build_soundtrack_preview(input_path: Path, output: Path, labels_path: Path, mp3_input: Path | None = None) -> dict[str, Any]:
    try:
        import numpy as np
    except ImportError as error:
        raise ValueError("soundtrack rendering requires NumPy; use a Python environment with numpy installed") from error
    input_path, output = input_path.resolve(), output.resolve()
    if output.exists():
        raise ValueError("soundtrack output already exists; choose a new output directory to preserve previews")
    if output == input_path or output in input_path.parents or input_path in output.parents:
        raise ValueError("soundtrack output must be separate from the extracted input")
    manifest = json.loads((input_path / "manifest.json").read_text())
    graph_path = checked_file(input_path, "sound-bank-graph.json")
    graph = json.loads(graph_path.read_text())
    labels = json.loads(labels_path.read_text())
    if manifest.get("family") != "non-mp3-audio" or graph.get("family") != "conker-b1-sound-bank-graph" or labels.get("family") != "conker-us-music-sequence-labels":
        raise ValueError("unsupported extraction or label family")
    if manifest.get("profile") != "us" or labels.get("profile") != "us":
        raise ValueError("soundtrack preview supports the reviewed US profile only")
    label_map = {item["index"]: item for item in labels["sequences"]}
    records = manifest["sequence_bank"]["sequences"]
    ids = [item["index"] for item in records]
    if len(label_map) != len(labels["sequences"]) or len(set(ids)) != len(ids) or set(ids) != set(label_map):
        raise ValueError("sequence and label IDs must be unique and cover the same set")
    for item in records:
        checked_file(input_path, item["file"], item["decoded_sha1"])
    for item in graph["samples"]:
        checked_file(input_path, item["file"], item["stored_sha1"])
    reference = json.loads((ROOT / "config/soundtrack-reference.json").read_text())
    validate_reference_sequences(reference, records, manifest["normalized_sha1"])
    music_streams = nominated_mp3_streams(mp3_input, reference, manifest["normalized_sha1"])
    output.parent.mkdir(parents=True, exist_ok=True)
    # Publish only a complete directory. Failure never replaces an existing preview.
    with tempfile.TemporaryDirectory(prefix=".soundtracks-", dir=output.parent) as temp:
        target = Path(temp) / "preview"
        target.mkdir()
        audio_assets.preview_adpcm_sample_files(input_path, target / "samples", False)
        shutil.copyfile(graph_path, target / "sound-bank-graph.json")
        # Retain the source-root and source-graph links in the sample manifest.
        for item in graph["samples"]:
            shutil.copyfile(checked_file(input_path, item["file"], item["stored_sha1"]), target / item["file"])
        sample_manifest = json.loads((target / "samples/manifest.json").read_text())
        samples = {}
        for item in sample_manifest["samples"]:
            with wave.open(str(target / "samples" / item["file"]), "rb") as wav:
                samples[item["index"]] = np.frombuffer(wav.readframes(wav.getnframes()), dtype="<i2").astype(np.float32) / 32768
        for name in ("music", "midi", "sequences"):
            (target / name).mkdir()
        if music_streams:
            (target / "music-streams/sources").mkdir(parents=True)
            for item in music_streams:
                source = checked_file(mp3_input, f"streams/{item['index']:04d}.mp3", item["source_sha1"])
                shutil.copyfile(source, target / item["source_file"])
                frames = standard_mp3_frames(source.read_bytes())
                (target / item["file"]).write_bytes(frames)
                item["preview_sha1"] = hashlib.sha1(frames).hexdigest()
                item["preview_encoding"] = "Exact MPEG frames; runtime L: cue records and trailer omitted"
        results = []
        for item in sorted(records, key=lambda item: item["index"]):
            index = item["index"]
            data = checked_file(input_path, item["file"], item["decoded_sha1"]).read_bytes()
            preview = audio_assets.compact_sequence_to_midi(data)
            pcm, render = render_sequence(preview.midi, graph, samples, graph["bank"]["sample_rate"])
            filename = f"music/{index:04d}.wav"
            with wave.open(str(target / filename), "wb") as wav:
                wav.setnchannels(2)
                wav.setsampwidth(2)
                wav.setframerate(render["sample_rate"])
                wav.writeframes(pcm)
            (target / f"midi/{index:04d}.mid").write_bytes(preview.midi)
            (target / f"sequences/{index:04d}.cseq").write_bytes(data)
            results.append({**album_names(label_map[index], reference), "file": filename, "source_sha1": item["decoded_sha1"],
                            "wav_sha1": hashlib.sha1((target / filename).read_bytes()).hexdigest(),
                            "loop_markers": preview.loop_markers, **render})
            print(f"Rendered sequence {index:04d}: {render['mapped_notes']}/{render['note_count']} mapped notes", flush=True)
        summary = {"schema_version": 1, "family": "conker-local-soundtrack-preview", "profile": "us",
                   "normalized_rom_sha1": manifest["normalized_sha1"], "playback": "approximate-game-samples-single-pass",
                   "limitations": LIMITATIONS, "label_notice": labels["notice"], "sequences": results,
                   "coverage": {"sequences": len(results), "audible": sum(item["audible"] for item in results),
                                "samples": len(samples), "confidence": dict(Counter(item["confidence"] for item in results)),
                                "unmapped_notes": sum(item["unmapped_notes"] for item in results)},
                   "music_streams": music_streams, "album_reference": reference}
        (target / "manifest.json").write_text(json.dumps(summary, indent=2) + "\n")
        write_preview_page(target, summary, sample_manifest)
        target.rename(output)
    return summary
