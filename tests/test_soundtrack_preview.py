from __future__ import annotations

import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import audio_assets, soundtrack_preview as preview


def midi(events: list[tuple[int, bytes]], division: int = 480) -> bytes:
    track = audio_assets._midi_track("test", [(tick, 1, i, message) for i, (tick, message) in enumerate(events)], max((tick for tick, _ in events), default=0))
    return b"MThd" + struct.pack(">IHHH", 6, 1, 1, division) + track


class SoundtrackPreviewTests(unittest.TestCase):
    def test_program_major_and_tempo_changes_preserve_note_timing(self) -> None:
        data = midi([(0, b"\xb0\x20\x01"), (0, b"\xc0\x01"), (0, b"\x90\x3c\x64"),
                     (480, b"\xff\x51\x03\x0f\x42\x40"), (960, b"\x80\x3c\x00")])
        notes, _ = preview.schedule_notes(data, 170)
        self.assertEqual(notes[0]["instrument"], 129)
        self.assertEqual(notes[0]["start"], 0)
        self.assertEqual(notes[0]["end"], 1.5)

    def test_invalid_program_retains_previous_instrument(self) -> None:
        notes, _ = preview.schedule_notes(midi([(0, b"\xc0\x02"), (0, b"\xc0\x7f"),
                                               (0, b"\x90\x3c\x64"), (480, b"\x80\x3c\x00")]), 3)
        self.assertEqual(notes[0]["instrument"], 2)

    def test_duplicate_keys_have_independent_durations(self) -> None:
        notes, _ = preview.schedule_notes(midi([(0, b"\x90\x3c\x64"), (100, b"\x90\x3c\x64"),
                                               (200, b"\x80\x3c\x00"), (400, b"\x80\x3c\x00")]), 3)
        self.assertEqual(len(notes), 2)
        self.assertLess(notes[0]["end"], notes[1]["end"])
        self.assertLess(notes[0]["start"], notes[1]["start"])

    def test_rejects_truncated_midi_and_unclosed_notes(self) -> None:
        data = midi([(0, b"\x90\x3c\x64")])
        with self.assertRaisesRegex(ValueError, "unclosed"):
            preview.schedule_notes(data, 170)
        with self.assertRaisesRegex(ValueError, "truncated"):
            preview.midi_events(data[:-1])

    def test_key_velocity_lookup_and_instrument_zero_silence(self) -> None:
        graph = {"instruments": [{"sound_indices": [0]}, {"sound_indices": [1, 2]}],
                 "sounds": [{"key_map_index": i} for i in range(3)],
                 "key_maps": [{"key_min": 1, "key_max": 0, "velocity_min": 0, "velocity_max": 0},
                              {"key_min": 0, "key_max": 60, "velocity_min": 1, "velocity_max": 127},
                              {"key_min": 61, "key_max": 127, "velocity_min": 1, "velocity_max": 127}]}
        self.assertIsNone(preview.lookup_sound(graph, 0, 60, 100))
        self.assertEqual(preview.lookup_sound(graph, 1, 61, 100), graph["sounds"][2])
        self.assertIsNone(preview.lookup_sound(graph, 1, 60, 0))

    def test_hash_and_path_validation(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / "sample").write_bytes(b"owned-input")
            digest = hashlib.sha1(b"owned-input").hexdigest()
            self.assertEqual(preview.checked_file(root, "sample", digest), (root / "sample").resolve())
            with self.assertRaisesRegex(ValueError, "hash mismatch"):
                preview.checked_file(root, "sample", "0" * 40)
            with self.assertRaisesRegex(ValueError, "unsafe"):
                preview.checked_file(root, "../sample")

    def test_existing_output_is_never_overwritten(self) -> None:
        try:
            import numpy  # noqa: F401
        except ImportError:
            self.skipTest("NumPy is an optional renderer dependency")
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            marker = root / "keep.txt"
            marker.write_text("previous preview")
            with self.assertRaisesRegex(ValueError, "already exists"):
                preview.build_soundtrack_preview(root / "input", root, root / "labels.json")
            self.assertEqual(marker.read_text(), "previous preview")

    def test_mp3_candidates_require_matching_rom_and_unchanged_stream(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / "streams").mkdir()
            (root / "streams/0138.mp3").write_bytes(b"local-stream")
            manifest = {"profile": "us", "normalized_sha1": "rom-hash", "stream_bank": {"streams": [
                {"entry_index": 138, "file": "streams/0138.mp3", "decoded_sha1": hashlib.sha1(b"local-stream").hexdigest()}]}}
            (root / "manifest.json").write_text(json.dumps(manifest))
            reference = {"music_stream_candidates": [{"index": 138, "confidence": "tentative"}]}
            records = preview.nominated_mp3_streams(root, reference, "rom-hash")
            reference["music_stream_candidates"][0]["source_sha1"] = "different-reviewed-source"
            with self.assertRaisesRegex(ValueError, "MP3 source hash mismatch"):
                preview.nominated_mp3_streams(root, reference, "rom-hash")
            del reference["music_stream_candidates"][0]["source_sha1"]
            self.assertEqual(records[0]["file"], "music-streams/0138.mp3")
            with self.assertRaisesRegex(ValueError, "same reviewed US ROM"):
                preview.nominated_mp3_streams(root, reference, "different-rom")
            (root / "streams/0138.mp3").write_bytes(b"changed")
            with self.assertRaisesRegex(ValueError, "hash mismatch"):
                preview.nominated_mp3_streams(root, reference, "rom-hash")

    def test_reference_candidates_preserve_known_numeric_ids_and_provenance(self) -> None:
        reference = json.loads((preview.ROOT / "config/soundtrack-reference.json").read_text())
        ids = {item["index"] for item in json.loads((preview.ROOT / "config/audio-sequences.json").read_text())["sequences"]}
        for comparison in reference["comparisons"]:
            self.assertTrue(set(comparison["sequence_ids"]) <= ids)
            self.assertTrue(comparison["reference_url"].startswith("https://downloads.khinsider.com/"))
            self.assertTrue(comparison["basis"])
            self.assertNotEqual(comparison["status"], "confirmed")

    def test_portable_page_embeds_metadata_without_script_injection(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            manifest = {"name": "</script><script>bad()</script>"}
            preview.write_preview_page(root, manifest, {"samples": []})
            page = (root / "index.html").read_text()
            self.assertNotIn("{{PREVIEW_DATA}}", page)
            self.assertNotIn(manifest["name"], page)
            payload = page.split('<script id="preview-data" type="application/json">')[1].split('</script>')[0]
            self.assertEqual(json.loads(payload)["manifest"], manifest)
            self.assertTrue((root / "preview-common.css").is_file())

    def test_album_titles_preserve_aliases_and_separate_match_confidence(self) -> None:
        reference = json.loads((preview.ROOT / "config/soundtrack-reference.json").read_text())
        label = {"index": 66, "name": "GreatMightyPoo", "confidence": "identified"}
        named = preview.album_names(label, reference)
        self.assertEqual(named["album_title"], "Sloprano (Instrumental)")
        self.assertIn("GreatMightyPoo", named["aliases"])
        self.assertIn("Sloprano", named["aliases"])
        self.assertEqual(named["confidence"], "identified")
        self.assertEqual(named["album_match_confidence"], "tentative")
        self.assertEqual(named["name"], label["name"])

    def test_all_album_entries_have_qualified_reviews_and_consistent_totals(self) -> None:
        reference = json.loads((preview.ROOT / "config/soundtrack-reference.json").read_text())
        self.assertEqual([len(album["tracks"]) for album in reference["albums"]], [18, 27])
        self.assertEqual(len(reference["comparisons"]), 45)
        for album in [*reference["albums"], *reference.get("additional_albums", [])]:
            reviews = [track["review"] for track in album["tracks"]]
            for status in ("matched", "tentative", "unresolved"):
                self.assertEqual(album["coverage"][status], sum(review["status"] == status for review in reviews))
            for track in album["tracks"]:
                review = track["review"]
                self.assertTrue(review["reason"])
                self.assertRegex(review["reference_sha1"], r"^[0-9a-f]{40}$")
                self.assertFalse(review["confirmed_by_ear"])
                self.assertFalse(review["runtime_use_verified"])
                self.assertEqual(review["status"] == "tentative", bool(review["matches"]))
                for match in review["matches"]:
                    self.assertIn(match["kind"], ("sequence", "stream"))
                    self.assertEqual(match["confidence"], "tentative")
                    self.assertRegex(match["source_sha1"], r"^[0-9a-f]{40}$")
                    self.assertTrue(match["audio_evidence"])
                    for evidence in match["audio_evidence"]:
                        self.assertLessEqual(abs(evidence["score"]), 1.000001)
                        self.assertGreater(evidence["seconds"], 0)
        unresolved = [track["title"] for album in reference["albums"] for track in album["tracks"]
                      if track["review"]["status"] == "unresolved"]
        self.assertEqual(unresolved, ["electric wires", "zombie attack"])

    def test_additional_references_preserve_variants_aliases_and_source_guards(self) -> None:
        reference = json.loads((preview.ROOT / "config/soundtrack-reference.json").read_text())
        self.assertEqual(len(reference["additional_albums"][0]["tracks"]), 71)
        self.assertEqual(len(reference["additional_comparisons"]), 71)
        labels = {item["index"]: item for item in json.loads((preview.ROOT / "config/audio-sequences.json").read_text())["sequences"]}
        for index, title, old in [(18, "The Cognitive Cogs", "bats tower"),
                                  (113, "Credits", "Conker The King (Reprise)"),
                                  (119, "Broken Franky", "sad mrs. bee"),
                                  (140, "The Panther and the Weasel", "Don Weazo")]:
            named = preview.album_names(labels[index], reference)
            self.assertEqual(named["album_title"], title)
            self.assertIn(old, named["aliases"])
            self.assertEqual(named["confidence"], labels[index]["confidence"])
        candidate = next(match for track in reference["additional_albums"][0]["tracks"] for match in track["review"]["matches"] if match["kind"] == "sequence" and match["index"] == 45)
        isolated = {"albums": [], "additional_albums": [{"tracks": [{"review": {"matches": [candidate]}}]}]}
        preview.validate_reference_sequences(isolated, [{"index": 45, "decoded_sha1": candidate["source_sha1"]}], "rom")
        with self.assertRaisesRegex(ValueError, "source hash mismatch"):
            preview.validate_reference_sequences(isolated, [{"index": 45, "decoded_sha1": "changed"}], "rom")

    def test_gamerip_titles_are_exact_canonical_and_older_leads_stay_qualified(self) -> None:
        reference = json.loads((preview.ROOT / "config/soundtrack-reference.json").read_text())
        titles = {track["title"] for track in reference["additional_albums"][0]["tracks"]}
        labels = {item["index"]: item for item in json.loads((preview.ROOT / "config/audio-sequences.json").read_text())["sequences"]}
        for preferred in reference["sequence_album_names"]:
            named = preview.album_names(labels[preferred["index"]], reference)
            if preferred["canonical"]:
                self.assertEqual(preferred["album"], "gamerip")
                self.assertIn(named["album_title"], titles)
                self.assertTrue(named["album_title_canonical"])
            else:
                self.assertIn("Source-specific older-album lead", named["album_match_note"])
                self.assertFalse(named["album_title_canonical"])
        for index, title, alias in [(2, "Sad Mrs. Bee", "sad mrs. bee"),
                                     (13, "Bullfish Territory", "you brute!"),
                                     (49, "Chemical Warfare", "let's leg it"),
                                     (66, "Sloprano (Instrumental)", "Sloprano"),
                                     (145, "Conker the King Reprise", "Conker The King (Reprise)")]:
            named = preview.album_names(labels[index], reference)
            self.assertEqual(named["album_title"], title)
            self.assertIn(alias, named["aliases"])
            self.assertEqual(named["confidence"], labels[index]["confidence"])
        self.assertEqual(preview.album_names(labels[53], reference)["album_title"], "Poo (Instrumental)")

    def test_reference_evidence_rejects_changed_rom_or_sequence_source(self) -> None:
        reference = {"comparison_method": {"normalized_rom_sha1": "rom"}, "albums": [
            {"tracks": [{"review": {"matches": [{"kind": "sequence", "index": 3, "source_sha1": "reviewed"}]}}]}]}
        records = [{"index": 3, "decoded_sha1": "reviewed"}]
        preview.validate_reference_sequences(reference, records, "rom")
        with self.assertRaisesRegex(ValueError, "different ROM"):
            preview.validate_reference_sequences(reference, records, "other")
        records[0]["decoded_sha1"] = "changed"
        with self.assertRaisesRegex(ValueError, "source hash mismatch"):
            preview.validate_reference_sequences(reference, records, "rom")

    def test_unknown_contributor_name_is_retained_without_null_alias(self) -> None:
        reference = json.loads((preview.ROOT / "config/soundtrack-reference.json").read_text())
        named = preview.album_names({"index": 3, "name": None, "confidence": "unidentified"}, reference)
        self.assertIsNone(named["name"])
        self.assertEqual(named["confidence"], "unidentified")
        self.assertNotIn(None, named["aliases"])
        self.assertEqual(named["album_title"], "Stealthy Conker")

    def test_shared_theme_names_remain_searchable_without_merging_ids(self) -> None:
        reference = json.loads((preview.ROOT / "config/soundtrack-reference.json").read_text())
        label = {"index": 1, "name": "MainTheme", "confidence": "identified"}
        named = preview.album_names(label, reference)
        self.assertEqual(named["album_title"], "Windy & Co.")
        self.assertIn("inside the wasp's fortress", named["aliases"])
        self.assertIn("near bats tower", named["aliases"])
        self.assertEqual(named["index"], 1)
        self.assertEqual(named["confidence"], "identified")

    def test_mp3_browser_preview_retains_frames_and_omits_runtime_cues(self) -> None:
        frame = bytes.fromhex("FFF330C8") + bytes(74)
        plain = bytes.fromhex("FFF330C0") + bytes(74)
        native = frame + b"L:\x01\x05\x80\x80\x90\xf4\0" + plain + b"trailer"
        self.assertEqual(preview.standard_mp3_frames(native), frame + plain)

    def test_sample_loop_envelope_stereo_and_silent_render(self) -> None:
        try:
            import numpy as np
        except ImportError:
            self.skipTest("NumPy is an optional renderer dependency")
        graph = {"bank": {"sample_rate": 8000}, "instruments": [{"sound_indices": []}, {"sound_indices": [0]}],
                 "sounds": [{"key_map_index": 0, "envelope_index": 0, "wavetable_index": 0, "volume": 127, "pan": 64}],
                 "key_maps": [{"key_min": 0, "key_max": 127, "velocity_min": 1, "velocity_max": 127, "key_base": 60, "detune": 0}],
                 "envelopes": [{"attack_time_us": 1000, "decay_time_us": 10000, "release_time_us": 16000, "attack_volume": 127, "decay_volume": 100}],
                 "wavetables": [{"sample_index": 0, "loop_index": 0}],
                 "loops": [{"start_sample": 0, "end_sample": 16, "count": 0xffffffff}]}
        source = np.sin(np.arange(16) * 2 * np.pi / 16).astype(np.float32)
        data = midi([(0, b"\x90\x3c\x64"), (480, b"\x80\x3c\x00")])
        pcm, info = preview.render_sequence(data, graph, {0: source}, 8000)
        samples = np.frombuffer(pcm, dtype="<i2").reshape(-1, 2)
        self.assertTrue(info["audible"])
        self.assertEqual(info["mapped_notes"], 1)
        self.assertGreater(np.max(np.abs(samples[3000:3100])), 0)  # beyond source length
        self.assertLessEqual(np.max(np.abs(samples.astype(np.int32))), 32767)
        self.assertNotEqual(samples[4, 0], samples[4, 1])  # center is 64 / 127
        silence, info = preview.render_sequence(midi([]), graph, {0: source}, 8000)
        self.assertFalse(info["audible"])
        self.assertEqual(set(silence), {0})


if __name__ == "__main__":
    unittest.main()
