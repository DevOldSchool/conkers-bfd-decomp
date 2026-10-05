from __future__ import annotations

import hashlib
import json
from pathlib import Path
import tempfile
import unittest
import wave

import numpy as np
import soundfile as sf

from scripts.soundtrack_preview import mix_stream_cues
from scripts.soundtrack_stream_experiment import build_stream_experiment


class StreamExperimentTests(unittest.TestCase):
    def test_clock_gain_delay_and_replacement_keep_instrumental_frames(self) -> None:
        rate = 8000
        instrumental = np.zeros((8000, 2), dtype="<i2")
        instrumental[50] = 1000
        cues = [{"index": 1, "seconds": 0.1}, {"index": 2, "seconds": 0.3}]
        streams = {1: (np.full((2400, 1), 0.2), rate), 2: (np.full((800, 1), -0.2), rate)}
        settings = {i: {"playback_rate": 4000, "gain": 0.5, "delay_seconds": 0.1} for i in (1, 2)}
        payload, report = mix_stream_cues(instrumental.tobytes(), rate, cues, streams, settings=settings)
        result = np.frombuffer(payload, dtype="<i2").reshape(-1, 2)
        self.assertEqual(len(result), 8000)
        self.assertEqual(result[50, 0], 999)
        self.assertEqual(report["onset_frames"], [1600, 3200])
        self.assertEqual(result[1599, 0], 0)
        self.assertTrue(3250 < result[2000, 0] < 3300)
        self.assertTrue(-3300 < result[3500, 0] < -3250)
        self.assertEqual(result[4800, 0], 0)
        self.assertEqual(report["attenuation"], 1)

    def test_invalid_measurements_fail_without_silent_defaults(self) -> None:
        streams = {1: (np.ones((10, 1)), 8000)}
        for settings in [{}, {1: {"playback_rate": 22018}},
                         {1: {"playback_rate": 0, "gain": 0.5, "delay_seconds": 0.1}},
                         {1: {"playback_rate": 8000, "gain": float("nan"), "delay_seconds": 0.1}}]:
            with self.subTest(settings=settings), self.assertRaises(ValueError):
                mix_stream_cues(bytes(400), 8000, [{"index": 1, "seconds": 0}], streams, settings=settings)

    def fixture(self, root: Path) -> tuple[Path, Path]:
        preview = root / "collection/base"
        preview.mkdir(parents=True)
        sf.write(preview / "instrumental.wav", np.zeros((8000, 2)), 8000, subtype="PCM_16")
        sf.write(preview / "stream.wav", np.full((800, 1), 0.2), 8000, subtype="PCM_16")
        (preview / "sequence.cseq").write_bytes(b"sequence")
        (preview / "stream.source").write_bytes(b"native stream")
        sha = lambda name: hashlib.sha1((preview / name).read_bytes()).hexdigest()
        seq = {"index": 66, "source_file": "sequence.cseq", "source_sha1": sha("sequence.cseq"),
               "file": "instrumental.wav", "wav_sha1": sha("instrumental.wav"),
               "stream_triggers": [{"index": 239, "seconds": 0.1}]}
        stream = {"index": 239, "source_file": "stream.source", "source_sha1": sha("stream.source"),
                  "file": "stream.wav", "preview_sha1": sha("stream.wav")}
        manifest = {"family": "conker-local-soundtrack-preview", "profile": "us", "normalized_rom_sha1": "owned-rom",
                    "sequences": [seq], "music_streams": [stream]}
        profile = {"normalized_rom_sha1": "owned-rom", "sequence_index": 66, "sequence_sha1": seq["source_sha1"],
                   "instrumental_wav_sha1": seq["wav_sha1"], "stream_triggers": seq["stream_triggers"], "notice": "Experiment only",
                   "streams": [{**stream, "playback_rate": 4000, "gain": 0.5, "delay_seconds": 0.1}]}
        (preview / "manifest.json").write_text(json.dumps(manifest))
        spec = root / "profile.json"
        spec.write_text(json.dumps(profile))
        return preview, spec

    def test_build_is_qualified_and_preserves_existing_output(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp); preview, profile = self.fixture(root); out = root / "experiment.wav"
            report = build_stream_experiment(preview, profile, out)
            self.assertEqual(report["notice"], "Experiment only")
            with wave.open(str(out)) as wav:
                self.assertEqual((wav.getframerate(), wav.getnframes()), (8000, 8000))
            digest = hashlib.sha1(out.read_bytes()).hexdigest()
            with self.assertRaisesRegex(ValueError, "already exists"):
                build_stream_experiment(preview, profile, out)
            self.assertEqual(hashlib.sha1(out.read_bytes()).hexdigest(), digest)

    def test_rom_and_every_source_guard_against_misapplied_evidence(self) -> None:
        for change in ["rom", "sequence.cseq", "instrumental.wav", "stream.source", "stream.wav", "cue-ids", "cue-time"]:
            with self.subTest(change=change), tempfile.TemporaryDirectory() as temp:
                root = Path(temp); preview, profile = self.fixture(root); out = root / "experiment.wav"
                if change in {"rom", "cue-ids", "cue-time"}:
                    spec = json.loads(profile.read_text())
                    if change == "rom": spec["normalized_rom_sha1"] = "other"
                    elif change == "cue-ids": spec["streams"][0]["index"] = 240
                    else: spec["stream_triggers"][0]["seconds"] = 0.5
                    profile.write_text(json.dumps(spec))
                else:
                    (preview / change).write_bytes(b"changed")
                with self.assertRaises(ValueError):
                    build_stream_experiment(preview, profile, out)
                self.assertFalse(out.exists())
