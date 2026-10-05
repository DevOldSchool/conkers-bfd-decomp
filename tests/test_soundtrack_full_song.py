from __future__ import annotations

import hashlib
import json
from pathlib import Path
import tempfile
import unittest
import wave
from unittest.mock import patch

import numpy as np
import soundfile as sf

from scripts.soundtrack_full_song import build_full_song, remove_silent_intervals, overlay_incidental, load_incidental
from scripts.soundtrack_preview import write_preview_page
import test_soundtrack_stream_experiment as stream_fixtures


class FullSongTests(unittest.TestCase):
    def fixture(self, root: Path) -> tuple[Path, Path]:
        preview, main_profile = stream_fixtures.StreamExperimentTests().fixture(root)
        manifest = json.loads((preview / "manifest.json").read_text())
        manifest["sequences"][0]["midi_file"] = "main.mid"
        (preview / "main.mid").write_bytes(b"midi")
        sha = lambda name: hashlib.sha1((preview / name).read_bytes()).hexdigest()
        for index in (271, 272):
            sf.write(preview / f"{index}.wav", np.full((800, 1), 0.2), 8000, subtype="PCM_16")
            (preview / f"{index}.source").write_bytes(str(index).encode())
            manifest["music_streams"].append({"index": index, "file": f"{index}.wav", "preview_sha1": sha(f"{index}.wav"),
                                              "source_file": f"{index}.source", "source_sha1": sha(f"{index}.source")})
        sf.write(preview / "closing.wav", np.full((400, 2), -0.2), 8000, subtype="PCM_16")
        (preview / "closing.cseq").write_bytes(b"closing")
        (preview / "closing.mid").write_bytes(b"midi")
        manifest["sequences"].append({"index": 74, "file": "closing.wav", "wav_sha1": sha("closing.wav"),
                                      "source_file": "closing.cseq", "source_sha1": sha("closing.cseq"), "midi_file": "closing.mid"})
        manifest["sequences"][0]["album_title"] = "Sloprano (Instrumental)"
        (preview / "manifest.json").write_text(json.dumps(manifest))
        write_preview_page(preview, manifest, {"base_path": "", "samples": []})
        profile = {"title": "Sloprano", "normalized_rom_sha1": "owned-rom", "sequence_index": 66,
                   "main_profile": main_profile.name, "main_profile_sha1": hashlib.sha1(main_profile.read_bytes()).hexdigest(),
                   "notice": "Continuous edit; ending join inferred", "ending_streams": [],
                   "closing_sequence": {"index": 74, "source_sha1": sha("closing.cseq"), "wav_sha1": sha("closing.wav"),
                                        "placement": "after-last-vocal", "gain": 1}}
        for stream, seconds in zip(manifest["music_streams"][1:], (0, 0.1)):
            profile["ending_streams"].append({**stream, "seconds_after_main": seconds,
                                              "playback_rate": 8000, "gain": 0.4, "delay_seconds": 0.01})
        spec = root / "full.json"
        spec.write_text(json.dumps(profile))
        return preview, spec

    def test_full_song_ending_order_sting_timing_and_slim_asset_reuse(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp); preview, profile = self.fixture(root); output = preview.parent / "full"
            report = build_full_song(preview, profile, output)
            self.assertEqual([r["index"] for r in report["main_stream_triggers"]], [239])
            self.assertEqual([r["index"] for r in report["ending_stream_triggers"]], [271, 272])
            self.assertAlmostEqual(report["closing_onset_seconds"], 1.21)
            self.assertAlmostEqual(report["duration_seconds"], 1.26)
            self.assertEqual(report["clipped_samples"], 0)
            self.assertEqual(len(list(output.rglob("*.wav"))), 1)
            with wave.open(str(output / report["file"])) as wav:
                pcm = np.frombuffer(wav.readframes(wav.getnframes()), dtype="<i2").reshape(-1, 2)
            self.assertTrue(np.all(pcm[9700:10000] < 0))  # closing sting after the last vocal
            embedded = (output / "index.html").read_text()
            self.assertIn('id="full-songs"', embedded)
            self.assertIn("Sloprano (Instrumental)", embedded)
            self.assertIn("ending join inferred", embedded)
            original = hashlib.sha1((output / report["file"]).read_bytes()).hexdigest()
            with self.assertRaisesRegex(ValueError, "already exists"):
                build_full_song(preview, profile, output)
            self.assertEqual(hashlib.sha1((output / report["file"]).read_bytes()).hexdigest(), original)

    def test_changed_sources_and_invalid_arrangement_never_publish_a_preview(self) -> None:
        for change in ["rom", "main-profile", "271.source", "272.wav", "closing.cseq", "closing.wav", "duplicate", "order", "outside"]:
            with self.subTest(change=change), tempfile.TemporaryDirectory() as temp:
                root = Path(temp); preview, profile = self.fixture(root); output = preview.parent / "full"
                data = json.loads(profile.read_text())
                if change == "rom": data["normalized_rom_sha1"] = "changed"
                elif change == "main-profile": (root / data["main_profile"]).write_text("changed")
                elif change == "duplicate": data["ending_streams"][1]["index"] = 271
                elif change == "order": data["ending_streams"][0]["seconds_after_main"] = 0.3
                elif change == "outside": data["main_profile"] = "../outside.json"
                else: (preview / change).write_bytes(b"changed")
                profile.write_text(json.dumps(data))
                with self.assertRaises(ValueError):
                    build_full_song(preview, profile, output)
                self.assertFalse(output.exists())


class SilentEditTests(unittest.TestCase):
    def test_only_exact_silence_is_removed_and_audio_frames_survive(self) -> None:
        audible = np.array([[120, -120], [50, -50]], dtype="<i2").tobytes()
        pcm = audible + bytes(40) + audible
        self.assertEqual(remove_silent_intervals(pcm, [{"start_frame": 2, "end_frame": 12}]), audible * 2)
        for cuts in [[{"start_frame": 0, "end_frame": 3}],
                     [{"start_frame": 5, "end_frame": 3}],
                     [{"start_frame": 2, "end_frame": 8}, {"start_frame": 7, "end_frame": 12}]]:
            with self.subTest(cuts=cuts), self.assertRaises(ValueError):
                remove_silent_intervals(pcm, cuts)


class IncidentalTests(unittest.TestCase):
    def test_overlays_overlap_without_replacing_existing_audio(self) -> None:
        pcm = np.full((8000, 2), 1000, dtype="<i2")
        settings = {"index": 237, "onset_seconds": 0.2, "playback_rate": 8000, "gain": 0.5}
        clip = np.full((800, 1), 0.1)
        payload, report = overlay_incidental(pcm.tobytes(), 8000, [(settings, (clip, 8000)), (settings, (clip, 8000))])
        result = np.frombuffer(payload, dtype="<i2").reshape(-1, 2)
        np.testing.assert_array_equal(result[:1600], pcm[:1600])
        np.testing.assert_array_equal(result[2400:], pcm[2400:])
        self.assertTrue(np.all(result[1600:2400] == 4276))
        self.assertEqual(report[0]["onset_frame"], 1600)
        self.assertEqual(overlay_incidental(pcm.tobytes(), 8000, [])[0], pcm.tobytes())

    def test_bad_onsets_clocks_audio_and_clipping_are_rejected(self) -> None:
        setting = {"index": 237, "onset_seconds": 0.2, "playback_rate": 8000, "gain": 0.5}
        clip = np.full((800, 1), 0.1)
        for field, value in [("onset_seconds", -1), ("onset_seconds", 1), ("onset_seconds", float("nan")),
                             ("playback_rate", 0), ("gain", float("nan")), ("gain", 2)]:
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                overlay_incidental(bytes(32000), 8000, [({**setting, field: value}, (clip, 8000))])
        with self.assertRaisesRegex(ValueError, "clip"):
            overlay_incidental(np.full((8000, 2), 32000, dtype="<i2").tobytes(), 8000, [(setting, (clip, 8000))])
        with self.assertRaises(ValueError):
            overlay_incidental(bytes(32000), 8000, [(setting, (np.full((800, 1), np.nan), 8000))])

    def test_bank_rom_native_bytes_and_playable_hash_are_guarded(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            bank = Path(temp)
            sf.write(bank / "237.wav", np.full((800, 1), 0.1), 8000, subtype="PCM_16")
            digest = hashlib.sha1((bank / "237.wav").read_bytes()).hexdigest()
            record = {"entry_index": 237, "file": "237.wav", "decoded_sha1": digest}
            manifest = {"normalized_sha1": "owned-rom", "stream_bank": {"streams": [record]}}
            (bank / "manifest.json").write_text(json.dumps(manifest))
            setting = {"index": 237, "source_sha1": digest, "preview_sha1": digest, "note": "Measured reaction"}
            with patch("scripts.soundtrack_full_song.standard_mp3_frames", side_effect=lambda b: b):
                self.assertEqual(len(load_incidental(bank, [setting], "owned-rom")), 1)
                for change in [{"source_sha1": "changed"}, {"preview_sha1": "changed"}, {"note": ""}, {"index": 999}]:
                    with self.subTest(change=change), self.assertRaises(ValueError):
                        load_incidental(bank, [{**setting, **change}], "owned-rom")
                with self.assertRaises(ValueError):
                    load_incidental(bank, [setting], "other-rom")
                (bank / "237.wav").write_bytes(b"changed")
                with self.assertRaises(ValueError):
                    load_incidental(bank, [setting], "owned-rom")
            with self.assertRaises(ValueError):
                load_incidental(None, [setting], "owned-rom")
