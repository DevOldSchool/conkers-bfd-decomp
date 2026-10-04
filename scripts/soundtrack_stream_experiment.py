#!/usr/bin/env python3
"""Build a separate, hash-guarded MP3 timing experiment from an existing preview."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import wave

from scripts.soundtrack_preview import checked_file, mix_stream_cues


def build_stream_experiment(preview: Path, profile: Path, output: Path) -> dict:
    import soundfile as sf

    preview, output = preview.resolve(), output.resolve()
    if output.exists():
        raise ValueError("output already exists; preserve previous experiments")
    manifest = json.loads(checked_file(preview, "manifest.json").read_text())
    measured = json.loads(profile.read_text())
    if (manifest.get("family") != "conker-local-soundtrack-preview" or
            manifest.get("profile") != "us" or
            measured.get("normalized_rom_sha1") != manifest.get("normalized_rom_sha1") or
            not measured.get("notice")):
        raise ValueError("measured profile requires the same US ROM and a qualification")
    sequence = next((r for r in manifest["sequences"] if r["index"] == measured["sequence_index"]), None)
    if sequence is None:
        raise ValueError("measured sequence is missing from preview")
    if (sequence["source_sha1"] != measured["sequence_sha1"] or
            sequence["wav_sha1"] != measured["instrumental_wav_sha1"] or
            sequence["stream_triggers"] != measured["stream_triggers"]):
        raise ValueError("measured profile sequence, instrumental source or cue timing changed")

    def asset(filename: str, digest: str) -> Path:
        relative = (preview / filename).resolve().relative_to(preview.parent)
        return checked_file(preview.parent, str(relative), digest)

    asset(sequence["source_file"], sequence["source_sha1"])
    with wave.open(str(asset(sequence["file"], sequence["wav_sha1"])), "rb") as wav:
        if wav.getnchannels() != 2 or wav.getsampwidth() != 2 or wav.getcomptype() != "NONE":
            raise ValueError("instrumental must be stereo PCM16")
        rate = wav.getframerate()
        pcm = wav.readframes(wav.getnframes())
        if len(pcm) != wav.getnframes() * 4:
            raise ValueError("instrumental WAV is truncated")
    settings = {r["index"]: r for r in measured["streams"]}
    if (len(settings) != len(measured["streams"]) or
            set(settings) != {r["index"] for r in sequence["stream_triggers"]}):
        raise ValueError("measured settings must exactly cover the sequence's cue IDs")
    streams = {}
    for index, setting in settings.items():
        stream = next((r for r in manifest["music_streams"] if r["index"] == index), None)
        if stream is None:
            raise ValueError("measured stream is missing from preview")
        if (setting["preview_sha1"] != stream["preview_sha1"] or
                setting["source_sha1"] != stream["source_sha1"]):
            raise ValueError("measured stream source changed")
        asset(stream["source_file"], stream["source_sha1"])
        streams[index] = sf.read(asset(stream["file"], stream["preview_sha1"]),
                                 dtype="float32", always_2d=True)
    payload, report = mix_stream_cues(pcm, rate, sequence["stream_triggers"], streams, settings=settings)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("xb") as file:
        with wave.open(file, "wb") as wav:
            wav.setnchannels(2)
            wav.setsampwidth(2)
            wav.setframerate(rate)
            wav.writeframes(payload)
    return {**report, "sample_rate": rate, "wav_sha1": hashlib.sha1(output.read_bytes()).hexdigest(),
            "notice": measured["notice"]}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--preview", type=Path, required=True)
    parser.add_argument("--profile", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(build_stream_experiment(args.preview, args.profile, args.output), indent=2))


if __name__ == "__main__":
    main()
