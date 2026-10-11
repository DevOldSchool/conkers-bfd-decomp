import copy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import sound_bank_build as build
from test_audio_assets import sound_bank_graph_fixture

class SoundBankBuildTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        control,external,wave=sound_bank_graph_fixture()
        self.records=build.sound_bank_codec.typed_regions(control[:56],external,wave)['control'][0]
        self.decoded=build.sound_bank_codec.encode_region(self.records);self.packed=build.rzip_pack.encode_rzip_chunk(self.decoded)
        self.rom=b'prefix'+self.packed+b'tail'
        self.expected={'schema_version':1,'profile':'us','part':'control','rom_sha1':'test','rom_start':6,'rom_end':6+len(self.packed),'decoded_size':len(self.decoded),'original_decoded_sha256':build.sha256(self.decoded),'original_stored_sha256':build.sha256(self.packed),'encoder':'rzip-zlib9'}
        self.inputs=self.root/build.input_directory('control')
        build.texture_build.publish_inputs(self.inputs,build.input_files(self.expected,self.records))

    def test_fresh_control_compression_and_raw_records(self):
        with patch.object(build.rzip_pack,'encode_rzip_chunk',wraps=build.rzip_pack.encode_rzip_chunk) as encode:
            packed,hashes=build.packed_part(self.inputs,self.expected)
        self.assertEqual(packed,self.packed);encode.assert_called_once_with(self.decoded)
        expected=dict(self.expected,part='00000000',encoder='native-records',rom_end=6+len(self.decoded),original_stored_sha256=build.sha256(self.decoded))
        directory=self.root/build.input_directory('00000000');build.texture_build.publish_inputs(directory,build.input_files(expected,self.records))
        with patch.object(build.rzip_pack,'encode_rzip_chunk') as encode:
            self.assertEqual(build.packed_part(directory,expected)[0],self.decoded)
        encode.assert_not_called()

    def test_changed_records_never_replace_existing_linker_parts(self):
        with patch.object(build,'reviewed_parts',return_value=(self.rom,[(self.expected,self.records)])):
            result=build.build_parts(self.root)
            part=self.root/'build/us/sound-bank/parts/audio/bank17/sound_bank_control_rzip.bin'
            before=part.read_bytes(),part.stat().st_mtime_ns
            changed=copy.deepcopy(self.records);changed['records'][1]['sample_rate']+=1
            (self.inputs/'records.json').write_text(json.dumps(changed))
            with self.assertRaisesRegex(ValueError,'Inputs were preserved'):build.build_parts(self.root)
            self.assertEqual((part.read_bytes(),part.stat().st_mtime_ns),before)
            restored=build.recover_inputs('control',self.root)
            self.assertEqual(json.loads((Path(restored['backup_directory'])/'records.json').read_text()),changed)
            self.assertEqual(build.build_parts(self.root),result)
            self.assertEqual((part.read_bytes(),part.stat().st_mtime_ns),before)

    def test_encoder_drift_missing_records_and_invalid_selectors_fail(self):
        with patch.object(build.rzip_pack,'encode_rzip_chunk',return_value=bytes(len(self.packed))):
            with self.assertRaisesRegex(ValueError,'stored bytes'):build.packed_part(self.inputs,self.expected)
        (self.inputs/'records.json').unlink()
        with self.assertRaisesRegex(ValueError,'Inputs were preserved'):build.packed_part(self.inputs,self.expected)
        for name in ('../escape','1','abcdefgh','0000000g','control/extra'):
            with self.subTest(name=name),self.assertRaises(ValueError):build.input_directory(name)

    def test_partition_retains_unknown_ranges_and_rejects_overlap(self):
        from types import SimpleNamespace
        parts={'external':[{'start':0,'end':4},{'start':8,'end':12}],'external_unknown_ranges':[(4,8)]}
        asset=SimpleNamespace(rom_start=100,rom_end=112)
        rows=build.external_partition(asset,parts)
        self.assertEqual([(a,b) for a,b,_ in rows],[(100,104),(104,108),(108,112)])
        self.assertIn('/unreconstructed/',rows[1][2])
        parts['external_unknown_ranges']=[(3,8)]
        with self.assertRaises(ValueError):build.external_partition(asset,parts)

    def test_native_report_uses_actual_candidate_and_independent_original_target(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / ('build/us/assets/' + build.part_name('control') + '.o')
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.packed)]))
        def link(args, *, cwd, check):
            self.assertEqual(args[-1], build.part_name('control') + '.bin')
            original = (cwd / args[-1]).read_bytes()
            self.assertEqual(original, self.packed)
            (cwd / 'target.o').write_bytes(object_file([('.data', 1, 3, original)]))
        with patch.object(targets, 'ROOT', self.root), patch.object(targets.subprocess, 'run', side_effect=link):
            unit, item = targets.prepare_sound_part(self.rom, self.expected, output=self.root / 'report')
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['report_data_bytes'], len(self.packed))
            self.assertEqual(item['metadata']['progress_categories'], ['data'])
            self.assertEqual(len(unit['source_inputs']), 2)
            self.assertEqual(set(unit['linked_inputs']), {str(linked.relative_to(self.root))})
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.packed)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_sound_part(self.rom, self.expected, output=self.root / 'report')
