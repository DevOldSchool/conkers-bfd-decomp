import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import adpcm_build as build, adpcm_codec as codec, adpcm_layout as layout

class AdpcmBuildTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        self.pcm=list(range(-8,8))*3
        self.plan={'format':'conker-adpcm-pcm16-plan-v1','order':2,'predictor_count':1,'coefficients':[0]*16,'frames':[[0,0]]*3}
        self.wav=codec.source_wav(self.pcm,22050);self.raw=codec.encode_pcm(self.pcm,self.plan);self.packed=self.raw+bytes(5);self.rom=b'prefix'+self.packed+b'tail'
        self.expected={'schema_version':2,'pcm_format':'pcm16','profile':'us','sample':0,'rom_sha1':'test','rom_start':6,
                       'runtime_bytes':27,'pcm_frames':48,'sample_rate':22050,'context_wavetable':0,'context_book':0,
                       'original_pcm_sha256':build.sha256(struct.pack('<48h',*self.pcm)),
                       'native_plan_sha256':build.plan_digest(self.plan),
                       'parts':[{'first_frame':0,'end_frame':3,'rom_start':6,'rom_end':38,'zero_padding_bytes':5,'original_stored_sha256':build.sha256(self.packed)}]}
        self.inputs=self.root/build.input_directory(0)
        build.texture_build.publish_inputs(self.inputs,build.input_files(self.expected,self.plan,self.wav))
        self.selection=(self.rom,[(self.expected,self.plan,self.wav)])

    def test_encoder_receives_pcm_plan_and_complete_sample_storage_publishes(self):
        with patch.object(codec,'encode_pcm',wraps=codec.encode_pcm) as encode:
            parts,hashes=build.packed_sample(self.inputs,self.expected)
        encode.assert_called_once_with(self.pcm,self.plan)
        self.assertEqual([raw for _,raw in parts],[self.packed])
        self.assertEqual(set(hashes),set(build.SOURCE_NAMES))
        with patch.object(build,'reviewed_samples',return_value=self.selection):
            proof=build.build_parts(self.root)
        self.assertEqual((proof['sample_count'],proof['part_count'],proof['stored_bytes']),(1,1,32))
        self.assertEqual(len(list((self.root/'build/us/adpcm/parts').rglob('*.bin'))),1)

    def test_pcm_edits_preserved_and_recovery_backs_up_entire_folder(self):
        with patch.object(build,'reviewed_samples',return_value=self.selection):
            first=build.build_parts(self.root)
            path=self.root/'build/us/adpcm/parts'/ (layout.part_name(0,0)+'.bin')
            before=path.read_bytes(),path.stat().st_mtime_ns
            changed=self.pcm.copy();changed[16]+=1
            edited=codec.source_wav(changed,22050);(self.inputs/'sample.wav').write_bytes(edited)
            (self.inputs/'notes.txt').write_text('keep this note')
            with self.assertRaisesRegex(ValueError,'Inputs were preserved'):build.build_parts(self.root)
            self.assertEqual((path.read_bytes(),path.stat().st_mtime_ns),before)
            recovery=build.recover_inputs(0,self.root);backup=Path(recovery['backup_directory'])
            self.assertEqual((backup/'sample.wav').read_bytes(),edited)
            self.assertEqual((backup/'notes.txt').read_text(),'keep this note')
            self.assertEqual(build.build_parts(self.root),first)
            self.assertEqual((path.read_bytes(),path.stat().st_mtime_ns),before)

    def test_native_book_or_frame_plan_edits_fail_even_if_output_would_be_unchanged(self):
        for field in ('coefficients','frames'):
            plan=copy.deepcopy(self.plan)
            if field=='coefficients':plan[field][0]=1
            else:plan[field][1][0]=1
            (self.inputs/'encoding.json').write_text(json.dumps(plan))
            with patch.object(codec,'encode_pcm',return_value=self.raw) as encode:
                with self.assertRaisesRegex(ValueError,'native book context changed'):build.packed_sample(self.inputs,self.expected)
            encode.assert_not_called()

    def test_missing_partial_inputs_and_encoder_drift_fail_without_replacement(self):
        with patch.object(codec,'encode_pcm',return_value=bytes(27)):
            with self.assertRaisesRegex(ValueError,'complete-frame region'):build.packed_sample(self.inputs,self.expected)
        (self.inputs/'encoding.json').unlink()
        with patch.object(build,'reviewed_samples',return_value=self.selection):
            with self.assertRaisesRegex(ValueError,'Inputs were preserved'):build.build_parts(self.root)
        self.assertFalse((self.inputs/'encoding.json').exists())

    def test_batch_failure_does_not_publish_an_earlier_sample(self):
        second=dict(self.expected,sample=1);directory=self.root/build.input_directory(1)
        build.texture_build.publish_inputs(directory,build.input_files(second,self.plan,b'bad wav'))
        selection=(self.rom,[(self.expected,self.plan,self.wav),(second,self.plan,self.wav)])
        with patch.object(build,'reviewed_samples',return_value=selection):
            with self.assertRaisesRegex(ValueError,'Inputs were preserved'):build.build_parts(self.root)
        self.assertFalse((self.root/'build/us/adpcm/parts').exists())

    def test_source_changes_during_encoding_fail(self):
        original=codec.encode_pcm
        def changed(pcm,plan):
            (self.inputs/'encoding.json').write_text(json.dumps(plan,indent=1))
            return original(pcm,plan)
        with patch.object(codec,'encode_pcm',side_effect=changed):
            with self.assertRaisesRegex(ValueError,'inputs changed during encoding'):build.packed_sample(self.inputs,self.expected)

    def test_native_report_compares_actual_linker_regions_and_retains_all_source_hashes(self):
        from test_objdiff_data_targets import object_file, targets
        linked=[]
        for part in self.expected['parts']:
            name=layout.part_name(0,part['first_frame'])
            path=self.root/('build/us/assets/'+name+'.o');path.parent.mkdir(parents=True,exist_ok=True)
            raw=self.rom[part['rom_start']:part['rom_end']]
            path.write_bytes(object_file([('.data',1,3,raw)]));linked.append(path)
        def link(args,*,cwd,check):
            raw=(cwd/args[-1]).read_bytes()
            (cwd/'target.o').write_bytes(object_file([('.data',1,3,raw)]))
        with patch.object(targets,'ROOT',self.root),patch.object(targets.subprocess,'run',side_effect=link):
            pairs=targets.prepare_adpcm_sample(self.rom,self.expected,output=self.root/'report')
            self.assertEqual(len(pairs),1)
            self.assertEqual(sum(unit['report_data_bytes'] for unit,_ in pairs),32)
            self.assertTrue(all(unit['complete'] for unit,_ in pairs))
            self.assertTrue(all(len(unit['source_inputs'])==3 for unit,_ in pairs))
            self.assertEqual([item['name'] for _,item in pairs],['assets/'+layout.part_name(0,f) for f in (0,)])
            linked[0].write_bytes(object_file([('.data',1,3,bytes(len(self.packed)))]))
            with self.assertRaisesRegex(ValueError,'candidate differs'):
                targets.prepare_adpcm_sample(self.rom,self.expected,output=self.root/'report')
