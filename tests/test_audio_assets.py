from __future__ import annotations

import io
import json
import struct
import tempfile
import unittest
import wave
from pathlib import Path
from unittest.mock import patch

from scripts import audio_assets


def compact_sequence(track_offset: int = 68, division: int = 480) -> bytes:
    return struct.pack(">17I", track_offset, *([0] * 15), division) + b"\x00\xFF"


def compact_sequence_bank() -> bytes:
    first = compact_sequence()
    second = compact_sequence(68, 384) + b"\x01"
    table_end = 20
    second_offset = table_end + len(first) + 2
    return (
        struct.pack(
            ">HHIIII",
            audio_assets.AL_SEQBANK_VERSION,
            2,
            table_end,
            len(first),
            second_offset,
            len(second),
        )
        + first
        + b"\xAA\xBB"
        + second
        + b"\xCC"
    )


def sound_bank_control() -> bytes:
    data = bytearray(64)
    struct.pack_into(">HHI", data, 0, audio_assets.AL_BANK_VERSION, 1, 8)
    struct.pack_into(">HBBIII", data, 8, 2, 0, 0, 22_050, 0, 32)
    return bytes(data)


def preview_sequence(track: bytes, division: int = 480) -> bytes:
    return struct.pack(">17I", 68, *([0] * 15), division) + track


def sound_bank_graph_fixture() -> tuple[bytes, bytes, bytes]:
    control = bytearray(64)
    struct.pack_into(">HH", control, 0, audio_assets.AL_BANK_VERSION, 1)
    struct.pack_into(">I", control, 4, 8)
    struct.pack_into(">HBBIII", control, 8, 1, 0, 0, 22_050, 0, 0x20)
    struct.pack_into(
        ">12BhhI",
        control,
        0x20,
        127,
        64,
        5,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        200,
        1,
        0xCF,
    )

    external = bytearray(0x94)
    struct.pack_into(">IIIBBBB", external, 0, 0x10, 0x20, 0x28, 64, 127, 0, 0)
    struct.pack_into(">iiiBBH", external, 0x10, 1, 2, 3, 127, 100, 0)
    struct.pack_into(">BBBBBb", external, 0x20, 0, 127, 0, 127, 60, -2)
    struct.pack_into(">IiBBHIII", external, 0x28, 0, 9, 0, 0, 0, 0x68, 0x40, 112)
    struct.pack_into(">ii16h", external, 0x40, 2, 1, *range(16))
    struct.pack_into(">III16h", external, 0x68, 0, 16, 0xFFFFFFFF, *range(16))
    return bytes(control), bytes(external), bytes(range(9))


class AudioAssetsTests(unittest.TestCase):
    def test_decodes_n64_adpcm_frame_and_writes_pcm_wav(self) -> None:
        decoded = audio_assets.decode_n64_vadpcm(
            bytes.fromhex("00 12 34 56 78 9A BC DE F0"),
            [0] * 16,
            order=2,
            predictor_count=1,
        )

        self.assertEqual(
            (1, 2, 3, 4, 5, 6, 7, -8, -7, -6, -5, -4, -3, -2, -1, 0),
            decoded,
        )
        wav = audio_assets.pcm16_mono_wav(decoded, 22_050)
        with wave.open(io.BytesIO(wav), "rb") as reader:
            self.assertEqual(1, reader.getnchannels())
            self.assertEqual(2, reader.getsampwidth())
            self.assertEqual(22_050, reader.getframerate())
            self.assertEqual(16, reader.getnframes())
            self.assertEqual(struct.pack("<16h", *decoded), reader.readframes(16))

    def test_adpcm_decoder_rejects_partial_frames_and_unknown_predictors(self) -> None:
        with self.assertRaisesRegex(ValueError, "multiple of nine"):
            audio_assets.decode_n64_vadpcm(b"\0", [0] * 16, 2, 1)
        with self.assertRaisesRegex(ValueError, "selects predictor 1"):
            audio_assets.decode_n64_vadpcm(b"\x01" + bytes(8), [0] * 16, 2, 1)

    def test_parses_sound_bank_control(self) -> None:
        summary = audio_assets.parse_sound_bank_control(sound_bank_control())
        self.assertEqual((8,), summary.bank_offsets)
        self.assertEqual(2, summary.instrument_count)
        self.assertEqual(22_050, summary.sample_rate)

    def test_compact_sequence_bank_round_trip(self) -> None:
        data = compact_sequence_bank()
        sequences = audio_assets.parse_compact_sequence_bank(data)

        self.assertEqual(2, len(sequences))
        self.assertEqual((480, 384), tuple(sequence.division for sequence in sequences))
        self.assertEqual(data, audio_assets.rebuild_compact_sequence_bank(sequences))

    def test_rejects_compact_sequence_track_outside_record(self) -> None:
        data = bytearray(compact_sequence_bank())
        struct.pack_into(">I", data, 20, 0x1000)

        with self.assertRaisesRegex(ValueError, "invalid track offset"):
            audio_assets.parse_compact_sequence_bank(bytes(data))

    def test_parses_complete_sound_bank_graph_and_sample_range(self) -> None:
        control, external, wavetable = sound_bank_graph_fixture()

        graph = audio_assets.parse_sound_bank_graph(control, external, wavetable)

        self.assertEqual(1, graph.manifest["summary"]["instrument_count"])
        self.assertEqual(1, graph.manifest["summary"]["sound_count"])
        self.assertEqual(1, graph.manifest["summary"]["adpcm_book_count"])
        self.assertEqual(1, graph.manifest["summary"]["loop_count"])
        self.assertEqual(1, graph.manifest["summary"]["unique_sample_count"])
        self.assertEqual(((0, 9),), graph.sample_ranges)
        self.assertEqual(112, graph.manifest["wavetables"][0]["conker_field_0x14"])
        self.assertEqual(list(range(16)), graph.manifest["adpcm_books"][0]["coefficients"])
        self.assertEqual(0xFFFFFFFF, graph.manifest["loops"][0]["count"])

    def test_extract_writes_sequences_and_sanitized_manifest(self) -> None:
        control = sound_bank_control()
        sequence_bank = compact_sequence_bank()
        assets = (
            audio_assets.AudioAsset(0, "sound-bank-control", control, 0x100, 0x140, 0x10, True),
            audio_assets.AudioAsset(1, "sound-bank-data", bytes(16), 0x140, 0x150, 0, False),
            audio_assets.AudioAsset(2, "wavetable", bytes(32), 0x150, 0x170, 1, False),
            audio_assets.AudioAsset(
                3,
                "compact-sequence-bank",
                sequence_bank,
                0x170,
                0x200,
                0,
                False,
            ),
        )
        family = audio_assets.NonMp3AudioFamily(
            bank_start=0x100,
            bank_end=0x200,
            assets=assets,
            sound_bank=audio_assets.parse_sound_bank_control(control),
            sequences=audio_assets.parse_compact_sequence_bank(sequence_bank),
        )

        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "owned.z64"
            source.write_bytes(bytes.fromhex("80371240"))
            output = root / "audio"
            with patch.object(
                audio_assets,
                "load_profile_audio_assets",
                return_value=(source, source.read_bytes(), "z64", family),
            ):
                manifest = audio_assets.extract_audio_assets("us", None, output, False)

            self.assertEqual(2, manifest["sequence_bank"]["sequence_count"])
            self.assertNotIn(temporary_directory, manifest["source_rom"])
            self.assertEqual(control, (output / "sound-bank-control.b1").read_bytes())
            self.assertEqual(
                family.sequences[1].data,
                (output / "sequences" / "0001.cseq").read_bytes(),
            )

    def test_extract_writes_graph_and_exact_sample_slices(self) -> None:
        control, external, wavetable = sound_bank_graph_fixture()
        sequence_bank = compact_sequence_bank()
        graph = audio_assets.parse_sound_bank_graph(control, external, wavetable)
        assets = (
            audio_assets.AudioAsset(0, "sound-bank-control", control, 0, 1, 0x10, True),
            audio_assets.AudioAsset(1, "sound-bank-data", external, 1, 2, 0, False),
            audio_assets.AudioAsset(2, "wavetable", wavetable, 2, 3, 1, False),
            audio_assets.AudioAsset(
                3, "compact-sequence-bank", sequence_bank, 3, 4, 0, False
            ),
        )
        family = audio_assets.NonMp3AudioFamily(
            bank_start=0,
            bank_end=4,
            assets=assets,
            sound_bank=audio_assets.parse_sound_bank_control(control),
            sequences=audio_assets.parse_compact_sequence_bank(sequence_bank),
            sound_graph=graph,
        )

        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "owned.z64"
            source.write_bytes(bytes.fromhex("80371240"))
            output = root / "audio"
            with patch.object(
                audio_assets,
                "load_profile_audio_assets",
                return_value=(source, source.read_bytes(), "z64", family),
            ):
                manifest = audio_assets.extract_audio_assets("us", None, output, False)

            graph_manifest = json.loads((output / "sound-bank-graph.json").read_text())
            self.assertEqual(1, manifest["sound_bank"]["unique_sample_count"])
            self.assertEqual(wavetable, (output / "samples" / "0000.adpcm").read_bytes())
            self.assertEqual("samples/0000.adpcm", graph_manifest["samples"][0]["file"])

            preview, count, looped, duration = (
                audio_assets.preview_adpcm_sample_files(output, None, False)
            )
            self.assertEqual((1, 1), (count, looped))
            self.assertEqual(16 / 22_050, duration)
            with wave.open(str(preview / "0000.wav"), "rb") as reader:
                self.assertEqual(16, reader.getnframes())
            preview_manifest = json.loads((preview / "manifest.json").read_text())
            self.assertFalse(preview_manifest["editable_import_supported"])
            self.assertEqual("samples/0000.adpcm", preview_manifest["samples"][0]["source"])

    def test_cseq_preview_emits_midi_notes_tempo_and_exact_loop_markers(self) -> None:
        track = bytes.fromhex(
            "00 C0 05 "
            "00 90 3C 64 60 "
            "30 FF 51 07 A1 20 "
            "00 FF 2E 00 03 "
            "00 FF 2D 02 02 00 00 00 08 "
            "00 FF 2F"
        )

        preview = audio_assets.compact_sequence_to_midi(preview_sequence(track))

        self.assertEqual(b"MThd", preview.midi[:4])
        self.assertEqual((6, 1, 2, 480), struct.unpack(">IHHH", preview.midi[4:14]))
        self.assertIn(bytes.fromhex("90 3C 64"), preview.midi)
        self.assertIn(bytes.fromhex("80 3C 00"), preview.midi)
        self.assertIn(bytes.fromhex("FF 51 03 07 A1 20"), preview.midi)
        self.assertIn(b"Conker loop start track=0 value=3", preview.midi)
        self.assertIn(b"CONKER_CSEQ\x00\x2E\x00\x03", preview.midi)
        self.assertIn(b"CONKER_CSEQ\x00\x2D\x02\x02\x00\x00\x00\x08", preview.midi)
        self.assertEqual(1, preview.notes)
        self.assertEqual(2, preview.loop_markers)
        self.assertEqual(96, preview.end_tick)

    def test_cseq_preview_expands_sdk_back_references(self) -> None:
        track = bytes.fromhex(
            "00 90 3C 40 10 "
            "00 FE 00 05 04 "
            "00 FF 2F"
        )

        preview = audio_assets.compact_sequence_to_midi(preview_sequence(track))

        self.assertEqual(2, preview.notes)
        self.assertEqual(16, preview.end_tick)
        self.assertEqual(2, preview.midi.count(bytes.fromhex("90 3C 40")))

    def test_preview_file_refuses_to_overwrite_without_force(self) -> None:
        track = bytes.fromhex("00 90 3C 40 10 00 FF 2F")
        with tempfile.TemporaryDirectory() as temporary_directory:
            source = Path(temporary_directory) / "0000.cseq"
            source.write_bytes(preview_sequence(track))

            output, count, notes, loops = audio_assets.preview_compact_sequence_files(
                source, None, False
            )

            self.assertEqual(source.with_suffix(".mid"), output)
            self.assertEqual((1, 1, 0), (count, notes, loops))
            self.assertEqual(b"MThd", output.read_bytes()[:4])
            with self.assertRaisesRegex(ValueError, "already exists"):
                audio_assets.preview_compact_sequence_files(source, None, False)


if __name__ == "__main__":
    unittest.main()
