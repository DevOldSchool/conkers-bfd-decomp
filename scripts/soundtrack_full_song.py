#!/usr/bin/env python3
"""Assemble a qualified full listening edit and a slim, directly openable preview.

All audio comes from matching local ROM extracts/renders. Reference recordings
are comparison evidence only, never part of the output mix.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import math
from pathlib import Path
import tempfile
import wave

from scripts.soundtrack_native_review import build_native_review
from scripts.soundtrack_preview import checked_file, mix_stream_cues
from scripts.soundtrack_stream_experiment import build_stream_experiment



def remove_silent_intervals(pcm: bytes, intervals: list[dict]) -> bytes:
    """Remove only explicit all-channel PCM16 silence; never cut audible material."""
    frames = len(pcm) // 4
    cursor = 0
    pieces = []
    for interval in intervals:
        start, end = interval["start_frame"], interval["end_frame"]
        if (not isinstance(start, int) or not isinstance(end, int) or
                not cursor <= start < end <= frames):
            raise ValueError("silent cuts must be ordered, non-overlapping frame ranges")
        if any(pcm[start * 4:end * 4]):
            raise ValueError("silent cut contains audible PCM")
        pieces.append(pcm[cursor * 4:start * 4])
        cursor = end
    pieces.append(pcm[cursor * 4:])
    return b"".join(pieces)


def build_full_song(preview: Path, profile: Path, output: Path) -> dict:
    import numpy as np
    import soundfile as sf
    from scipy.signal import resample_poly

    preview, profile, output = preview.resolve(), profile.resolve(), output.resolve()
    if output.exists():
        raise ValueError("output already exists; preserve previous previews")
    measured = json.loads(profile.read_text())
    manifest = json.loads(checked_file(preview, "manifest.json").read_text())
    if measured["normalized_rom_sha1"] != manifest["normalized_rom_sha1"] or not measured.get("notice"):
        raise ValueError("full song requires the same ROM and a listening qualification")
    main_profile = checked_file(profile.parent, measured["main_profile"], measured["main_profile_sha1"])
    main_settings = json.loads(main_profile.read_text())
    if main_settings["sequence_index"] != measured["sequence_index"]:
        raise ValueError("full song and main sequence IDs disagree")

    def asset(filename: str, digest: str) -> Path:
        path = (preview / filename).resolve().relative_to(preview.parent)
        return checked_file(preview.parent, str(path), digest)

    ending = measured["ending_streams"]
    if not ending or len({r["index"] for r in ending}) != len(ending):
        raise ValueError("ending must contain unique, ordered stream IDs")
    main_ids = {r["index"] for r in main_settings["streams"]}
    if main_ids & {r["index"] for r in ending}:
        raise ValueError("ending streams must be distinct from the main cues")
    settings, streams = {}, {}
    for setting in ending:
        stream = next((r for r in manifest["music_streams"] if r["index"] == setting["index"]), None)
        if (stream is None or setting["source_sha1"] != stream["source_sha1"] or
                setting["preview_sha1"] != stream["preview_sha1"]):
            raise ValueError("ending stream source changed")
        asset(stream["source_file"], stream["source_sha1"])
        streams[stream["index"]] = sf.read(asset(stream["file"], stream["preview_sha1"]), dtype="float32", always_2d=True)
        settings[stream["index"]] = setting
    closing = measured["closing_sequence"]
    sequence = next((r for r in manifest["sequences"] if r["index"] == closing["index"]), None)
    if (sequence is None or closing["source_sha1"] != sequence["source_sha1"] or
            closing["wav_sha1"] != sequence["wav_sha1"] or
            closing["placement"] != "after-last-vocal" or
            not math.isfinite(closing["gain"]) or not 0 <= closing["gain"] <= 1):
        raise ValueError("closing sequence source or placement changed")
    asset(sequence["source_file"], sequence["source_sha1"])
    sting, sting_rate = sf.read(asset(sequence["file"], sequence["wav_sha1"]), dtype="float32", always_2d=True)
    if sting.shape[1] != 2 or not np.all(np.isfinite(sting)):
        raise ValueError("closing sequence must be finite stereo audio")
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".full-song-", dir=output.parent) as temp:
        staging = Path(temp)
        main_report = build_stream_experiment(preview, main_profile, staging / "main.wav")
        with wave.open(str(staging / "main.wav")) as wav:
            rate = wav.getframerate()
            main = wav.readframes(wav.getnframes())
        cuts = measured.get("remove_silent_intervals", [])
        if cuts and main_report["wav_sha1"] != measured.get("main_mix_sha1"):
            raise ValueError("silent-cut profile requires the exact reviewed main mix")
        main = remove_silent_intervals(main, cuts)
        removed_frames = sum(r["end_frame"] - r["start_frame"] for r in cuts)
        listening_cues = []
        for cue in main_report["stream_triggers"]:
            source_frame = round(cue["seconds"] * rate)
            removed = sum(max(0, min(source_frame, r["end_frame"]) - r["start_frame"]) for r in cuts)
            listening_cues.append({**cue, "seconds": (source_frame - removed) / rate})
        main_frames = len(main) // 4
        cues = [{"index": r["index"], "seconds": main_frames / rate + r["seconds_after_main"]} for r in ending]
        if any(not math.isfinite(r["seconds_after_main"]) or r["seconds_after_main"] < 0 for r in ending):
            raise ValueError("invalid ending time")
        last = ending[-1]
        clock = last["playback_rate"]
        if not isinstance(clock, int) or not 4000 <= clock <= 192000:
            raise ValueError("invalid ending playback clock")
        divisor = math.gcd(rate, clock)
        last_clip = resample_poly(streams[last["index"]][0], rate // divisor, clock // divisor, axis=0)
        sting_start = round((cues[-1]["seconds"] + last["delay_seconds"]) * rate) + len(last_clip)
        if sting_rate != rate:
            raise ValueError("closing and main renders require the same sample rate")
        if sting_start + len(sting) > 300 * rate or sting_start < main_frames:
            raise ValueError("full listening edit exceeds the five-minute safety limit")
        padded = bytearray((sting_start + len(sting)) * 4)
        padded[:len(main)] = main
        sting_pcm = (np.clip(sting * closing["gain"], -1, 1) * 32767).astype("<i2").tobytes()
        padded[sting_start * 4:] = sting_pcm
        payload, report = mix_stream_cues(bytes(padded), rate, cues, streams, settings=settings)
        song = staging / "full.wav"
        with wave.open(str(song), "wb") as wav:
            wav.setnchannels(2)
            wav.setsampwidth(2)
            wav.setframerate(rate)
            wav.writeframes(payload)
        pcm = np.frombuffer(payload, dtype="<i2").reshape(-1, 2)
        diagnostics = {"main_duration_seconds": main_frames / rate,
                       "main_stream_triggers": listening_cues,
                       "source_main_stream_triggers": main_report["stream_triggers"],
                       "removed_silent_frames": removed_frames,
                       "removed_silent_seconds": removed_frames / rate,
                       "ending_stream_triggers": cues, "ending_onset_frames": report["onset_frames"],
                       "closing_sequence_index": closing["index"], "closing_onset_seconds": sting_start / rate,
                       "peak_pcm": int(np.max(np.abs(pcm.astype(np.int32)))),
                       "clipped_samples": int(np.count_nonzero(np.abs(pcm.astype(np.int32)) >= 32767)),
                       "attenuation": report["attenuation"]}
        record = {"sequence_index": measured["sequence_index"], "kind": "full-song-reconstruction",
                  "title": measured["title"], "note": measured["notice"], "file": song.name,
                  "wav_sha1": hashlib.sha1(song.read_bytes()).hexdigest(), **diagnostics}
        spec = staging / "song.json"
        spec.write_text(json.dumps({"normalized_rom_sha1": measured["normalized_rom_sha1"],
                                    "notice": manifest.get("native_review_notice", ""), "captures": [record]}))
        result = build_native_review(preview, spec, output)
    return result["reconstructions"][-1]


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--preview", type=Path, required=True)
    parser.add_argument("--profile", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    print(json.dumps(build_full_song(args.preview, args.profile, args.output), indent=2))


if __name__ == "__main__":
    main()
