#!/usr/bin/env python3
"""Add hash-guarded local game captures to a fresh soundtrack review folder.

Reuse the original sequence, sample and MP3 files without re-rendering or copying
an entire collection. Capture specifications contain relative local WAV paths,
ROM/source hashes, titles and listening qualifications. No emulator or network
access is performed by this tool.
"""
from __future__ import annotations

import argparse
import copy
from html.parser import HTMLParser
import json
import os
from pathlib import Path
import shutil
import tempfile
import wave

from scripts.soundtrack_preview import checked_file, write_preview_page


class EmbeddedData(HTMLParser):
    def __init__(self) -> None:
        super().__init__()
        self.active = False
        self.parts: list[str] = []

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        self.active = tag == "script" and dict(attrs).get("id") == "preview-data"

    def handle_endtag(self, tag: str) -> None:
        if tag == "script":
            self.active = False

    def handle_data(self, data: str) -> None:
        if self.active:
            self.parts.append(data)


def build_native_review(preview: Path, specification: Path, output: Path) -> dict:
    preview, specification, output = preview.resolve(), specification.resolve(), output.resolve()
    if output.exists():
        raise ValueError("output already exists; preserve previous previews")
    manifest = json.loads(checked_file(preview, "manifest.json").read_text())
    parser = EmbeddedData()
    parser.feed(checked_file(preview, "index.html").read_text())
    embedded = json.loads("".join(parser.parts))
    if embedded["manifest"] != manifest:
        raise ValueError("embedded preview and manifest disagree")
    spec = json.loads(specification.read_text())
    if (manifest.get("family") != "conker-local-soundtrack-preview" or
            manifest.get("profile") != "us" or
            spec.get("normalized_rom_sha1") != manifest.get("normalized_rom_sha1")):
        raise ValueError("capture review and preview must belong to the same US ROM")
    samples = copy.deepcopy(embedded["samples"])
    manifest = copy.deepcopy(manifest)
    # Reused files can live in sibling previews; never accept paths outside the
    # local soundtrack collection or transfer evidence to changed bytes.
    def rebase(filename: str, digest: str | None = None) -> str:
        path = (preview / filename).resolve()
        checked_file(preview.parent, str(path.relative_to(preview.parent)), digest)
        return Path(os.path.relpath(path, output)).as_posix()

    for record in manifest["sequences"]:
        for key, digest in (("file", "wav_sha1"), ("source_file", "source_sha1"), ("midi_file", None)):
            record[key] = rebase(record[key], record.get(digest) if digest else None)
    for record in manifest.get("music_streams", []):
        record["file"] = rebase(record["file"], record["preview_sha1"])
        record["source_file"] = rebase(record["source_file"], record["source_sha1"])
    for record in [*manifest.get("experiments", []), *manifest.get("native_captures", []),
                   *manifest.get("reconstructions", [])]:
        record["file"] = rebase(record["file"], record["wav_sha1"])
    sample_root = samples.get("base_path", "samples/")
    for record in samples["samples"]:
        rebase(sample_root + record["file"])
    samples["base_path"] = Path(os.path.relpath((preview / sample_root).resolve(), output)).as_posix() + "/"
    ids = {record["index"] for record in manifest["sequences"]}
    captures = spec.get("captures", [])
    if not captures:
        raise ValueError("at least one qualified capture is required")
    reviewed = []
    for record in captures:
        if (record.get("sequence_index") not in ids or
                record.get("kind") not in {"native-game-mix", "measured-stream-cue", "calibrated-stream-experiment", "full-song-reconstruction"} or
                not record.get("title") or not record.get("note")):
            raise ValueError("captures require an extracted sequence ID, kind, title and qualification")
        path = checked_file(specification.parent, record["file"], record["wav_sha1"])
        with wave.open(str(path), "rb") as wav:
            duration = wav.getnframes() / wav.getframerate()
            if (wav.getnchannels() != 2 or wav.getsampwidth() != 2 or
                    wav.getcomptype() != "NONE" or not 0 < duration <= 300):
                raise ValueError("captures must be bounded stereo PCM16 WAVs")
            # Reading all data catches truncated containers instead of publishing
            # an apparently valid header with incomplete audio.
            data = wav.readframes(wav.getnframes())
            if len(data) != wav.getnframes() * 4:
                raise ValueError("capture WAV is truncated")
            reviewed.append((path, {**record, "duration_seconds": duration,
                                     "sample_rate": wav.getframerate()}))
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".native-review-", dir=output.parent) as temp:
        target = Path(temp) / "preview"
        (target / "game-captures").mkdir(parents=True)
        for number, (path, record) in enumerate(reviewed):
            reconstruction = record["kind"] == "full-song-reconstruction"
            name = f"songs/{number:02d}-{record['sequence_index']:04d}-full.wav" if reconstruction else f"game-captures/{number:02d}.wav"
            (target / name).parent.mkdir(exist_ok=True)
            shutil.copyfile(path, target / name)
            record["file"] = name
            manifest.setdefault("reconstructions" if reconstruction else "native_captures", []).append(record)
        manifest["native_review_notice"] = spec["notice"]
        manifest["reused_preview"] = Path(os.path.relpath(preview, output)).as_posix() + "/"
        (target / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
        write_preview_page(target, manifest, samples)
        target.rename(output)
    return manifest


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--preview", type=Path, required=True)
    parser.add_argument("--captures", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    manifest = build_native_review(args.preview, args.captures, args.output)
    print(json.dumps({"sequences": len(manifest["sequences"]),
                      "native_captures": len(manifest["native_captures"])}))


if __name__ == "__main__":
    main()
