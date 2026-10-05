"""Render local B1/CSeq listening previews; never infer names from track order."""

from __future__ import annotations

import hashlib
import json
import math
import os
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
    "Envelope interruption and native pitch limits are modelled; resampling, native filters and reverb remain approximate/absent.",
    "Held-note volume, pan, bend, pressure and sustain are modelled; RSP frame rounding and release-tail updates are approximate.",
    "ADPCM sample loops repeat while a note sounds; finite sample-loop counts are approximated as continuous.",
    "Timed MP3 assemblies are separate experiments; decoder delay, callbacks, crossfades and native gain are not reproduced.",
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


def schedule_notes(data: bytes, instrument_count: int, graph: dict | None = None) -> tuple[list[dict], dict]:
    """Schedule MIDI voices and controls using the reconstructed CSeq player rules."""
    division, events = midi_events(data)
    channels = [dict(major=0, instrument=1, volume=127, pan=64, bend=0, bend_range=200,
                     sustain=0) for _ in range(16)]
    pending: dict[tuple[int, int], deque] = {}
    active: list[list[dict]] = [[] for _ in range(16)]
    notes: list[dict] = []
    tick, seconds, tempo = 0, 0.0, 500_000
    controllers: Counter = Counter()
    bends = applied = sustain_releases = 0
    mp3_major = 0
    stream_triggers = []

    def release(note: dict, *, sustained: bool = False) -> None:
        nonlocal sustain_releases
        note["end"] = seconds
        note["sustain_release"] = sustained
        sustain_releases += int(sustained)
        active[note["channel"]].remove(note)
        notes.append(note)

    def change(channel: int, values: dict, key: int | None = None) -> None:
        nonlocal applied
        for note in active[channel]:
            if key is None or (note["key"] == key and not note.get("key_released", False)):
                note["controls"].append({"time": seconds, **values})
                applied += 1
                if key is not None:
                    break  # __n_lookupVoice selects the first non-released key voice.

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
            field = {7: "volume", 10: "pan", 32: "major", 64: "sustain"}.get(key)
            if field:
                state[field] = value
            if key in (7, 10):
                change(channel, {field: value})
            elif key == 64 and value < 64:
                for note in list(active[channel]):
                    if note.get("key_released", False):
                        release(note, sustained=True)
            elif key == 27:
                mp3_major = value
            elif key == 26:
                stream_triggers.append({"index": mp3_major * 100 + value, "seconds": seconds,
                                        "tick": event_tick, "channel": channel})
        elif kind == 0xC0:
            instrument = (state["major"] << 7) + key
            if instrument < instrument_count:
                state["instrument"] = instrument
                if graph is not None:
                    inst = graph["instruments"][instrument]
                    # Program selection loads channel defaults; it does not reprogram held voices.
                    state.update(volume=inst.get("volume", 127), pan=inst.get("pan", 64),
                                 bend_range=inst.get("bend_range", 200))
        elif kind == 0xE0:
            raw = (message[2] << 7) + key - 8192
            state["bend"] = math.trunc(raw * state["bend_range"] / 8192)
            change(channel, {"bend": state["bend"]})
            bends += 1
        elif kind in (0xA0, 0xD0):
            change(channel, {"velocity": message[2] if kind == 0xA0 else key},
                   key if kind == 0xA0 else None)
        elif kind == 0x90 and message[2] > 0:
            note = dict(state, key=key, velocity=message[2], start=seconds, channel=channel,
                        controls=[])
            pending.setdefault((channel, key), deque()).append(note)
            active[channel].append(note)
        elif kind == 0x80 or (kind == 0x90 and message[2] == 0):
            queue = pending.get((channel, key))
            if queue:
                note = queue.popleft()
                if state["sustain"] >= 64:
                    note["key_released"] = True
                else:
                    release(note)
    if any(pending.values()):
        raise ValueError("preview MIDI has unclosed notes")
    # A bounded/offline pass can end with the pedal still down. Record this cutoff.
    sustained_at_end = sum(len(channel) for channel in active)
    for channel in active:
        for note in list(channel):
            release(note, sustained=True)
    return notes, {"controllers": dict(sorted(controllers.items())), "pitch_bend_events": bends,
                   "held_voice_updates": applied, "sustain_releases": sustain_releases,
                   "sustained_voices_cut_at_end": sustained_at_end, "stream_triggers": stream_triggers}


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


def voice_gain_curve(note: dict, sound: dict, envelope: dict, age: Any, release: float) -> Any:
    """Linear envelope targets with native-style interruption from the current gain.

    __n_vsDelta keeps a controller ramp's original envelope endpoint, or uses
    AL_GAIN_CHANGE_TIME (1ms) once that endpoint is past. RSP frame/integer rounding,
    wet buses and controls arriving during a release tail remain approximations.
    """
    import numpy as np

    attack = max(0.0, envelope["attack_time_us"] / 1_000_000)
    decay = max(0.0, envelope["decay_time_us"] / 1_000_000)
    duration = note["end"] - note["start"]
    volume, pan, velocity = note["volume"], note["pan"], note["velocity"]
    env_gain = envelope["attack_volume"] / 127

    def target() -> Any:
        balance = min(127, max(0, pan - 64 + sound["pan"]))
        gain = env_gain * velocity * sound["volume"] * volume / 127 ** 3
        return gain * np.array([math.cos(balance * math.pi / 254),
                               math.sin(balance * math.pi / 254)])

    initial = target()
    origin = np.zeros(2) if attack else initial
    destination = initial
    segment_start, segment_end = 0.0, attack
    events = [(attack, -1, "decay", {})] if attack < duration else []
    events.extend((control["time"] - note["start"], order, "control", control)
                  for order, control in enumerate(note.get("controls", []))
                  if control["time"] < note["end"] and any(k in control for k in ("volume", "pan", "velocity")))
    events.append((duration, len(events) + 1, "release", {}))
    values = np.zeros((len(age), 2), dtype=np.float32)
    cursor = 0

    def interpolate(times: Any) -> Any:
        if segment_end <= segment_start:
            return np.broadcast_to(destination, (len(times), 2))
        fraction = np.clip((times - segment_start) / (segment_end - segment_start), 0, 1)
        return origin + fraction[:, None] * (destination - origin)

    for when, _, kind, control in sorted(events):
        stop = min(len(age), int(np.searchsorted(age, when)))
        values[cursor:stop] = interpolate(age[cursor:stop])
        current = interpolate(np.array([when]))[0]
        if kind == "release":
            destination = np.zeros(2)
            finish = when + release
        else:
            if kind == "decay":
                env_gain = envelope["decay_volume"] / 127
                finish = attack + decay
            else:
                volume = control.get("volume", volume)
                pan = control.get("pan", pan)
                velocity = control.get("velocity", velocity)
                endpoint = attack if when < attack else attack + decay
                finish = endpoint if endpoint >= when else when + 0.001
            destination = target()
        origin, segment_start, segment_end = current, when, finish
        cursor = stop
    values[cursor:] = interpolate(age[cursor:])
    return values


def render_sequence(midi: bytes, graph: dict, samples: dict, rate: int) -> tuple[bytes, dict]:
    import numpy as np

    notes, diagnostics = schedule_notes(midi, len(graph["instruments"]), graph)
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
        release = max(0.016 if note.get("sustain_release") else 0.0, env["release_time_us"] / 1_000_000)
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
        base_cents = (note["key"] - mapping["key_base"]) * 100 + mapping["detune"]
        ratios = np.full(count, 2 ** ((base_cents + note["bend"]) / 1200), dtype=np.float64)
        for control in note.get("controls", []):
            if "bend" in control:
                offset = min(count, max(0, math.ceil((control["time"] - note["start"]) * rate)))
                ratios[offset:] = 2 ** ((base_cents + control["bend"]) / 1200)
        # n_alResamplePull clips and quantizes the RSP pitch increment.
        ratios = np.floor(np.minimum(ratios, 1.99996) * 32768) / 32768
        source = samples[table["sample_index"]]
        used.add(table["sample_index"])
        increments = ratios * graph["bank"]["sample_rate"] / rate
        position = np.concatenate((np.zeros(1), np.cumsum(increments[:-1]))) if count else np.zeros(0)
        loop = graph["loops"][table["loop_index"]] if table["loop_index"] is not None else None
        if loop and loop["count"] and 0 <= loop["start_sample"] < loop["end_sample"] <= len(source):
            loop_start, loop_end = loop["start_sample"], loop["end_sample"]
            position = np.where(position >= loop_end, loop_start + (position - loop_start) % (loop_end - loop_start), position)
        pcm = np.interp(position, np.arange(len(source)), source, left=0, right=0)
        gains = voice_gain_curve(note, sound, env, age, release)
        mix[start:start + count] += pcm[:, None] * gains

    peak = float(np.max(np.abs(mix)))
    # Only attenuate to prevent clipping; never amplify silence or very quiet sequences.
    scale = min(1.0, 0.9 / peak) if peak else 1.0
    payload = (np.clip(mix * scale, -1, 1) * 32767).astype("<i2").tobytes()
    diagnostics.update({"note_count": len(notes), "mapped_notes": len(voices), "unmapped_notes": missed,
                        "sample_ids": sorted(used), "duration_seconds": frames / rate,
                        "peak_before_attenuation": peak, "attenuation": scale,
                        "audible": bool(np.any(mix)), "sample_rate": rate})
    return payload, diagnostics



def mix_stream_cues(pcm: bytes, rate: int, cues: list[dict], streams: dict,
                    *, settings: dict[int, dict] | None = None) -> tuple[bytes, dict]:
    """Experimental one-player assembly from exact CC27/26 resource commands.

    Defaults replace streams at command time with equal sample rates. Explicit
    measured settings affect only MP3 clock, gain and onset; the instrumental
    timeline stays unchanged. These remain qualified listening experiments.
    """
    import numpy as np

    music = np.frombuffer(pcm, dtype="<i2").reshape(-1, 2).astype(np.float32) / 32768
    clips = []
    frames = len(music)
    starts = []
    for cue in cues:
        if settings is not None and (cue["index"] not in settings or
                not {"playback_rate", "gain", "delay_seconds"} <= settings[cue["index"]].keys()):
            raise ValueError("missing measured stream setting")
        setting = settings[cue["index"]] if settings is not None else {}
        delay = setting.get("delay_seconds", 0)
        gain = setting.get("gain", 1)
        clock = setting.get("playback_rate", rate)
        if (not math.isfinite(delay) or not 0 <= delay <= 0.5 or
                not math.isfinite(gain) or not 0 <= gain <= 1 or
                (settings is not None and (not isinstance(clock, int) or not 4000 <= clock <= 192000))):
            raise ValueError("invalid measured stream setting")
        if not math.isfinite(cue["seconds"]) or cue["seconds"] < 0:
            raise ValueError("invalid cue time")
        if starts and cue["seconds"] < cues[len(starts) - 1]["seconds"]:
            raise ValueError("cue commands are not chronological")
        start = round((cue["seconds"] + delay) * rate)
        if starts and start < starts[-1]:
            raise ValueError("delayed cue onsets are not chronological")
        starts.append(start)
    for order, cue in enumerate(cues):
        if cue["index"] not in streams:
            raise ValueError(f"missing cue stream {cue['index']:04d}")
        clip, sample_rate = streams[cue["index"]]
        if sample_rate != rate or clip.ndim != 2 or clip.shape[1] not in (1, 2):
            raise ValueError("cue streams require matching sample rates and mono/stereo PCM")
        if not np.all(np.isfinite(clip)):
            raise ValueError("non-finite stream PCM")
        if settings is not None:
            from scipy.signal import resample_poly
            setting = settings[cue["index"]]
            clock = setting["playback_rate"]
            divisor = math.gcd(rate, clock)
            clip = resample_poly(clip, rate // divisor, clock // divisor, axis=0) * setting["gain"]
        start = starts[order]
        if order + 1 < len(cues):
            clip = clip[:starts[order + 1] - start]
        if start + len(clip) > rate * 900:
            raise ValueError("cue assembly exceeds the 15-minute safety limit")
        if clip.shape[1] == 1:
            clip = np.repeat(clip, 2, axis=1)
        clips.append((start, clip))
        frames = max(frames, start + len(clip))
    mix = np.zeros((frames, 2), dtype=np.float32)
    mix[:len(music)] = music
    for start, clip in clips:
        mix[start:start + len(clip)] += clip
    peak = float(np.max(np.abs(mix))) if mix.size else 0.0
    scale = min(1.0, 0.9 / peak) if peak else 1.0
    payload = (np.clip(mix * scale, -1, 1) * 32767).astype("<i2").tobytes()
    return payload, {"stream_triggers": cues, "duration_seconds": frames / rate,
                     "peak_before_attenuation": peak, "attenuation": scale,
                     "stream_settings": settings, "onset_frames": starts}

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
    sample_data["base_path"] = samples.get("base_path", "samples/")
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



def render_loop_variants(records: list[dict], labels: dict, reference: dict, graph: dict,
                         samples: dict, input_path: Path, target: Path, indices: list[int]) -> list[dict]:
    """Keep bounded loop experiments separate from the default naming renders."""
    by_id = {item["index"]: item for item in records}
    if len(indices) != len(set(indices)) or not set(indices) <= set(by_id):
        raise ValueError("loop variant IDs must be unique extracted sequence IDs")
    variants = []
    for index in indices:
        source = by_id[index]
        data = checked_file(input_path, source["file"], source["decoded_sha1"]).read_bytes()
        midi = audio_assets.compact_sequence_to_midi(data, loop_repeats=1)
        pcm, diagnostics = render_sequence(midi.midi, graph, samples, graph["bank"]["sample_rate"])
        filename = f"music/{index:04d}-bounded-loop.wav"
        path = target / filename
        if path.exists():
            raise ValueError("loop variant output already exists")
        with wave.open(str(path), "wb") as wav:
            wav.setnchannels(2); wav.setsampwidth(2); wav.setframerate(diagnostics["sample_rate"])
            wav.writeframes(pcm)
        variants.append({"kind": "bounded-loop", "sequence_index": index, "file": filename,
                         "title": f"{album_names(labels[index], reference).get('album_title') or 'Sequence'} · bounded loop experiment",
                         "note": "One backwards jump per native loop end, then stop there. Game marker selection, runtime channel mutes and arrangement remain unverified.",
                         "source_sha1": source["decoded_sha1"], "wav_sha1": hashlib.sha1(path.read_bytes()).hexdigest(),
                         "loop_repeat_cap": 1, "loop_jumps": midi.loop_jumps, "loop_cutoffs": midi.loop_cutoffs,
                         **diagnostics})
    return variants

def build_soundtrack_preview(input_path: Path, output: Path, labels_path: Path, mp3_input: Path | None = None,
                             *, reuse_preview: Path | None = None, loop_repeats: int = 0,
                             stream_cues: bool = False, loop_variants: list[int] | None = None) -> dict[str, Any]:
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
    reused = None
    prefix = ""
    if reuse_preview is not None:
        reuse_preview = reuse_preview.resolve()
        reused = json.loads((reuse_preview / "manifest.json").read_text())
        if (reused.get("family") != "conker-local-soundtrack-preview" or
                reused.get("normalized_rom_sha1") != manifest["normalized_sha1"]):
            raise ValueError("reused preview must belong to the same ROM")
        validate_reference_sequences(reference, [{"index": item["index"], "decoded_sha1": item["source_sha1"]} for item in reused["sequences"]], manifest["normalized_sha1"])
        if checked_file(reuse_preview, "sound-bank-graph.json").read_bytes() != graph_path.read_bytes():
            raise ValueError("reused sample bank graph changed")
        prefix = Path(os.path.relpath(reuse_preview, output)).as_posix() + "/"
    if stream_cues:
        try:
            import soundfile as sf
        except ImportError as error:
            raise ValueError("timed stream experiments require the optional soundfile dependency") from error
    output.parent.mkdir(parents=True, exist_ok=True)
    # Publish only a complete directory. Failure never replaces an existing preview.
    with tempfile.TemporaryDirectory(prefix=".soundtracks-", dir=output.parent) as temp:
        target = Path(temp) / "preview"
        target.mkdir()
        if reused is None:
            audio_assets.preview_adpcm_sample_files(input_path, target / "samples", False)
            shutil.copyfile(graph_path, target / "sound-bank-graph.json")
            for item in graph["samples"]:
                shutil.copyfile(checked_file(input_path, item["file"], item["stored_sha1"]), target / item["file"])
            sample_manifest = json.loads((target / "samples/manifest.json").read_text())
            sample_root = target / "samples"
        else:
            sample_manifest = json.loads(checked_file(reuse_preview, "samples/manifest.json").read_text())
            sample_root = reuse_preview / "samples"
            sample_manifest["base_path"] = prefix + "samples/"
        samples = {}
        for item in sample_manifest["samples"]:
            path = checked_file(sample_root, item["file"], item["wav_sha1"])
            with wave.open(str(path), "rb") as wav:
                samples[item["index"]] = np.frombuffer(wav.readframes(wav.getnframes()), dtype="<i2").astype(np.float32) / 32768
        for name in ("music", "midi", "sequences"):
            (target / name).mkdir()
        if music_streams:
            if reused is None:
                (target / "music-streams/sources").mkdir(parents=True)
            prior_streams = {item["index"]: item for item in reused.get("music_streams", [])} if reused else {}
            for item in music_streams:
                source = checked_file(mp3_input, f"streams/{item['index']:04d}.mp3", item["source_sha1"])
                frames = standard_mp3_frames(source.read_bytes())
                item["preview_sha1"] = hashlib.sha1(frames).hexdigest()
                item["preview_encoding"] = "Exact MPEG frames; runtime L: cue records and trailer omitted"
                if reused is None:
                    shutil.copyfile(source, target / item["source_file"])
                    (target / item["file"]).write_bytes(frames)
                else:
                    prior = prior_streams.get(item["index"], {})
                    checked_file(reuse_preview, prior.get("source_file", "missing"), item["source_sha1"])
                    checked_file(reuse_preview, prior.get("file", "missing"), item["preview_sha1"])
                    item["source_file"] = prefix + prior["source_file"]
                    item["file"] = prefix + prior["file"]
        results = []
        experiments = []
        prior_sequences = {item["index"]: item for item in reused["sequences"]} if reused else {}
        for item in sorted(records, key=lambda item: item["index"]):
            index = item["index"]
            data = checked_file(input_path, item["file"], item["decoded_sha1"]).read_bytes()
            preview = audio_assets.compact_sequence_to_midi(data, loop_repeats)
            pcm, render = render_sequence(preview.midi, graph, samples, graph["bank"]["sample_rate"])
            filename = f"music/{index:04d}.wav"
            with wave.open(str(target / filename), "wb") as wav:
                wav.setnchannels(2)
                wav.setsampwidth(2)
                wav.setframerate(render["sample_rate"])
                wav.writeframes(pcm)
            midi_file, source_file = f"midi/{index:04d}.mid", f"sequences/{index:04d}.cseq"
            if reused is None or loop_repeats:
                (target / midi_file).write_bytes(preview.midi)
            else:
                if checked_file(reuse_preview, midi_file).read_bytes() != preview.midi:
                    raise ValueError(f"reused MIDI changed for {index:04d}")
                midi_file = prefix + midi_file
            if reused is None:
                (target / source_file).write_bytes(data)
            else:
                if prior_sequences.get(index, {}).get("source_sha1") != item["decoded_sha1"]:
                    raise ValueError(f"reused sequence source changed for {index:04d}")
                checked_file(reuse_preview, source_file, item["decoded_sha1"])
                source_file = prefix + source_file
            if stream_cues and render["stream_triggers"]:
                decoded = {}
                for cue in render["stream_triggers"]:
                    stream = next((s for s in music_streams if s["index"] == cue["index"]), None)
                    if stream is None:
                        raise ValueError(f"cue stream {cue['index']:04d} has no reviewed source")
                    path = (output / stream["file"]).resolve() if reused else target / stream["file"]
                    decoded[cue["index"]] = sf.read(path, dtype="float32", always_2d=True)
                assembled, timing = mix_stream_cues(pcm, render["sample_rate"], render["stream_triggers"], decoded)
                assembled_file = f"music/{index:04d}-stream-cues.wav"
                with wave.open(str(target / assembled_file), "wb") as wav:
                    wav.setnchannels(2); wav.setsampwidth(2); wav.setframerate(render["sample_rate"])
                    wav.writeframes(assembled)
                experiments.append({"kind": "timed-stream", "sequence_index": index, "file": assembled_file,
                                    "title": f"{album_names(label_map[index], reference).get('album_title') or 'Sequence'} · timed MP3 experiment",
                                    "note": "Exact CSeq resource commands; one-player replacement at the next cue. Native gain, decoder delay, crossfades and callback timing remain unverified.",
                                    "wav_sha1": hashlib.sha1((target / assembled_file).read_bytes()).hexdigest(),
                                    **timing})
            results.append({**album_names(label_map[index], reference), "file": filename, "source_sha1": item["decoded_sha1"], "midi_file": midi_file, "source_file": source_file,
                            "wav_sha1": hashlib.sha1((target / filename).read_bytes()).hexdigest(),
                            "loop_markers": preview.loop_markers, "loop_repeats": preview.loop_repeats,
                            "loop_jumps": preview.loop_jumps, "loop_cutoffs": preview.loop_cutoffs, **render})
            print(f"Rendered sequence {index:04d}: {render['mapped_notes']}/{render['note_count']} mapped notes", flush=True)
        experiments.extend(render_loop_variants(records, label_map, reference, graph, samples,
                                                input_path, target, loop_variants or []))
        summary = {"schema_version": 1, "family": "conker-local-soundtrack-preview", "profile": "us",
                   "normalized_rom_sha1": manifest["normalized_sha1"], "playback": "approximate-game-samples",
                   "renderer_version": "controllers-envelope-v2", "loop_repeat_cap": loop_repeats,
                   "reused_preview": prefix or None, "experiments": experiments,
                   "limitations": [text for text in LIMITATIONS if not (loop_repeats and text.startswith("One linear"))] +
                                  ([f"Loops stop after {loop_repeats} backwards jumps per loop end; marker selection and runtime arrangement remain unverified."] if loop_repeats else []), "label_notice": labels["notice"], "sequences": results,
                   "coverage": {"sequences": len(results), "audible": sum(item["audible"] for item in results),
                                "samples": len(samples), "confidence": dict(Counter(item["confidence"] for item in results)),
                                "unmapped_notes": sum(item["unmapped_notes"] for item in results)},
                   "music_streams": music_streams, "album_reference": reference}
        (target / "manifest.json").write_text(json.dumps(summary, indent=2) + "\n")
        write_preview_page(target, summary, sample_manifest)
        target.rename(output)
    return summary
