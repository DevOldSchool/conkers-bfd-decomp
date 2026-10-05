from __future__ import annotations

import hashlib
import json
from pathlib import Path
import tempfile
import unittest
import wave

from scripts.soundtrack_native_review import build_native_review
from scripts.soundtrack_preview import write_preview_page


class NativeReviewTests(unittest.TestCase):
    def fixture(self, root: Path) -> tuple[Path, Path]:
        base = root / "collection/base"
        base.mkdir(parents=True)
        for name in ["track.wav", "track.mid", "track.cseq", "sample.wav"]:
            (base / name).write_bytes(name.encode())
        sha = lambda name: hashlib.sha1((base / name).read_bytes()).hexdigest()
        manifest = {"family": "conker-local-soundtrack-preview", "profile": "us", "normalized_rom_sha1": "owned-rom",
                    "sequences": [{"index": 66, "file": "track.wav", "wav_sha1": sha("track.wav"),
                                   "source_file": "track.cseq", "source_sha1": sha("track.cseq"), "midi_file": "track.mid"}]}
        samples = {"base_path": "", "samples": [{"index": 0, "file": "sample.wav", "duration_seconds": 1, "sample_rate": 22018, "loop": None}]}
        (base / "manifest.json").write_text(json.dumps(manifest))
        write_preview_page(base, manifest, samples)
        capture = root / "capture.wav"
        with wave.open(str(capture), "wb") as wav:
            wav.setnchannels(2); wav.setsampwidth(2); wav.setframerate(22018); wav.writeframes(bytes(22018 * 4))
        spec = root / "captures.json"
        spec.write_text(json.dumps({"normalized_rom_sha1": "owned-rom", "notice": "Qualified game mix",
                    "captures": [{"file": "capture.wav", "wav_sha1": hashlib.sha1(capture.read_bytes()).hexdigest(),
                    "sequence_index": 66, "kind": "native-game-mix", "title": "Opening", "note": "Game mix, not a music stem."}]}))
        return base, spec

    def test_reuses_assets_and_preserves_qualified_capture(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp); base, spec = self.fixture(root); out = base.parent / "review"
            report = build_native_review(base, spec, out)
            self.assertEqual((out / report["sequences"][0]["file"]).read_bytes(), b"track.wav")
            self.assertFalse((out / "track.wav").exists())
            self.assertEqual(report["native_captures"][0]["duration_seconds"], 1)
            self.assertIn("Game mix", (out / "index.html").read_text())
            with self.assertRaisesRegex(ValueError, "already exists"):
                build_native_review(base, spec, out)

    def test_rom_source_and_capture_hashes_guard_evidence(self) -> None:
        for change in ["rom", "source", "capture"]:
            with self.subTest(change=change), tempfile.TemporaryDirectory() as temp:
                root = Path(temp); base, spec = self.fixture(root); out = base.parent / "review"
                if change == "rom":
                    data = json.loads(spec.read_text()); data["normalized_rom_sha1"] = "different"; spec.write_text(json.dumps(data))
                else:
                    (base / "track.cseq" if change == "source" else root / "capture.wav").write_bytes(b"changed")
                with self.assertRaises(ValueError):
                    build_native_review(base, spec, out)
                self.assertFalse(out.exists())

    def test_capture_path_cannot_escape_specification_directory(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp); base, spec = self.fixture(root)
            data = json.loads(spec.read_text()); data["captures"][0]["file"] = "../outside.wav"; spec.write_text(json.dumps(data))
            with self.assertRaises(ValueError):
                build_native_review(base, spec, base.parent / "review")
