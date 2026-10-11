"""Incremental build receipts never replace fresh native report verification."""
import json
import os
import struct
import unittest
from unittest.mock import patch
from scripts import adpcm_build as build
import test_adpcm_build as fixture


class AdpcmIncrementalTests(unittest.TestCase):
    setUp = fixture.AdpcmBuildTests.setUp

    def two_samples(self):
        second = dict(self.expected, sample=1)
        directory = self.root / build.input_directory(1)
        build.texture_build.publish_inputs(directory, build.input_files(second, self.plan, self.wav))
        return self.rom, [self.selection[1][0], (second, self.plan, self.wav)]

    def test_unchanged_build_encodes_nothing_and_one_wav_edit_encodes_one_sample(self):
        selection = self.two_samples()
        with patch.object(build, 'reviewed_samples', return_value=selection):
            first = build.build_parts(self.root)
            with patch.object(build, 'packed_sample', wraps=build.packed_sample) as encode:
                self.assertEqual(build.build_parts(self.root), first)
                encode.assert_not_called()
                # A metadata-only WAV edit retains PCM but must invalidate by
                # content even if the filesystem timestamp has been restored.
                path = self.root / build.input_directory(1) / 'sample.wav'
                stamp = path.stat()
                wav = path.read_bytes()
                path.write_bytes(wav[:4] + struct.pack('<I', len(wav)) + wav[8:] + b'JUNK' + bytes(4))
                os.utime(path, ns=(stamp.st_atime_ns, stamp.st_mtime_ns))
                build.build_parts(self.root)
                encode.assert_called_once()
                self.assertEqual(encode.call_args.args[1]['sample'], 1)

    def test_missing_or_corrupt_part_and_changed_encoder_force_fresh_encoding(self):
        with patch.object(build, 'reviewed_samples', return_value=self.selection):
            build.build_parts(self.root)
            path = self.root / 'build/us/adpcm/parts' / (build.adpcm_layout.part_name(0, 0) + '.bin')
            for corrupt in (False, True):
                if corrupt: path.write_bytes(bytes(len(self.packed)))
                else: path.unlink()
                with patch.object(build, 'packed_sample', wraps=build.packed_sample) as encode:
                    build.build_parts(self.root)
                    encode.assert_called_once()
                self.assertEqual(path.read_bytes(), self.packed)
            with patch.object(build, 'encoder_fingerprint', return_value='new implementation'), \
                    patch.object(build, 'packed_sample', wraps=build.packed_sample) as encode:
                build.build_parts(self.root)
                encode.assert_called_once()

    def test_bad_receipt_cannot_bypass_encoding_or_missing_source_checks(self):
        with patch.object(build, 'reviewed_samples', return_value=self.selection):
            build.build_parts(self.root)
            receipt = self.root / 'build/us/adpcm/batch.json'
            for text in ('{', 'null', '[]', json.dumps({'encoder_fingerprint': build.encoder_fingerprint(), 'parts': [None]})):
                receipt.write_text(text)
                with patch.object(build, 'packed_sample', wraps=build.packed_sample) as encode:
                    build.build_parts(self.root)
                    encode.assert_called_once()
            (self.inputs / 'sample.wav').unlink()
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.build_parts(self.root)

    def test_changed_pcm_rejected_even_with_matching_cached_output(self):
        with patch.object(build, 'reviewed_samples', return_value=self.selection):
            build.build_parts(self.root)
            pcm = self.pcm.copy(); pcm[0] += 1
            edited = build.adpcm_codec.source_wav(pcm, 22050)
            (self.inputs / 'sample.wav').write_bytes(edited)
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.build_parts(self.root)
            self.assertEqual((self.inputs / 'sample.wav').read_bytes(), edited)

    def test_report_always_runs_fresh_source_encoder(self):
        from test_objdiff_data_targets import targets
        with patch.object(build, 'reviewed_samples', return_value=self.selection):
            build.build_parts(self.root)
        with patch.object(targets, 'ROOT', self.root), \
                patch.object(targets.adpcm_build, 'packed_sample', side_effect=ValueError('fresh encoder ran')) as encode:
            with self.assertRaisesRegex(ValueError, 'fresh encoder ran'):
                targets.prepare_adpcm_sample(self.rom, self.expected, output=self.root / 'report')
            encode.assert_called_once_with(self.inputs, self.expected)

    def test_migration_hint_exposes_single_and_all_sample_recovery(self):
        error = str(build.input_error(self.inputs, self.expected, 'old manifest'))
        self.assertIn('recover-adpcm --sample 0', error)
        self.assertIn('recover-adpcm --all', error)

    def test_sample_decode_workers_are_equivalent_under_spawn(self):
        import multiprocessing
        from concurrent.futures import ProcessPoolExecutor
        extent = {'rom_start': 6, 'rom_end': 38, 'pcm_format': 'pcm16',
                  'zero_padding_bytes': 5, 'stored_sha256': build.sha256(self.packed)}
        wave = {'index': 0, 'book_index': 0}
        book = {'coefficients': self.plan['coefficients'], 'order': 2, 'predictor_count': 1}
        jobs = [({'index': i}, extent, wave, book, self.raw, 22050) for i in range(2)]
        serial = [build.review_sample(job) for job in jobs]
        with ProcessPoolExecutor(max_workers=2, mp_context=multiprocessing.get_context('spawn')) as workers:
            self.assertEqual(list(workers.map(build.review_sample, jobs)), serial)
        self.assertEqual(serial[0][1:], (self.plan, self.wav))
