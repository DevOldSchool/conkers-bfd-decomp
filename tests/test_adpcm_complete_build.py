import struct
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import adpcm_build as build, adpcm_layout, adpcm_headroom as headroom

class CompleteBuildTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        self.raw=bytes.fromhex('f0 7788887777888877 f0 8877778888777788')
        self.plan=build.adpcm_codec.frame_plan(self.raw,[0]*16,2,1)
        self.pcm=headroom.decode_headroom(self.raw,[0]*16,2,1)
        self.wav=headroom.source_float_wav(self.pcm,22050);self.packed=self.raw+bytes(6);self.rom=b'prefix'+self.packed+b'tail'
        self.expected={'schema_version':2,'profile':'us','sample':0,'rom_sha1':'test','rom_start':6,
                       'runtime_bytes':18,'pcm_frames':32,'sample_rate':22050,'context_wavetable':0,'context_book':0,
                       'pcm_format':'float32-headroom','original_pcm_sha256':build.sha256(struct.pack('<32i',*self.pcm)),
                       'native_plan_sha256':build.plan_digest(self.plan),
                       'parts':[{'first_frame':0,'end_frame':2,'rom_start':6,'rom_end':30,'zero_padding_bytes':6,
                                 'original_stored_sha256':build.sha256(self.packed)}]}
        self.inputs=self.root/build.input_directory(0);build.texture_build.publish_inputs(self.inputs,build.input_files(self.expected,self.plan,self.wav))
        self.selection=(self.rom,[(self.expected,self.plan,self.wav)])

    def test_float_signal_reconstructs_full_payload_and_derived_zero_alignment(self):
        with patch.object(headroom,'encode_headroom',wraps=headroom.encode_headroom) as encode:
            parts,hashes=build.packed_sample(self.inputs,self.expected)
        encode.assert_called_once_with(self.pcm,self.plan);self.assertEqual(parts[0][1],self.packed)
        self.assertEqual(len(hashes),3)
        with patch.object(build,'reviewed_samples',return_value=self.selection):
            proof=build.build_parts(self.root)
        self.assertEqual((proof['part_count'],proof['stored_bytes']),(1,24))

    def test_batch_recovery_retains_entire_previous_source_tree(self):
        changed=b'user edited WAV';(self.inputs/'sample.wav').write_bytes(changed);(self.inputs/'notes.txt').write_text('retain note')
        extra=self.inputs.parent/'extra-file';extra.write_text('retain extra')
        with patch.object(build,'reviewed_samples',return_value=self.selection):
            result=build.recover_all_inputs(self.root)
        backup=Path(result['backup_directory'])
        self.assertEqual((backup/'0000/sample.wav').read_bytes(),changed)
        self.assertEqual((backup/'0000/notes.txt').read_text(),'retain note')
        self.assertEqual((backup/'extra-file').read_text(),'retain extra')
        self.assertEqual((self.inputs/'sample.wav').read_bytes(),self.wav)
        self.assertEqual(build.packed_sample(self.inputs,self.expected)[0][0][1],self.packed)
        self.assertFalse(list(self.inputs.parent.parent.glob('.restore-*')))

    def test_staging_failure_preserves_sources_and_publish_failure_restores_backup(self):
        before=(self.inputs/'sample.wav').read_bytes()
        with patch.object(build,'reviewed_samples',return_value=self.selection),patch.object(build.texture_build,'publish_inputs',side_effect=ValueError('staging failure')):
            with self.assertRaisesRegex(ValueError,'staging failure'):build.recover_all_inputs(self.root)
        self.assertEqual((self.inputs/'sample.wav').read_bytes(),before)
        original=Path.rename
        def fail(path,target):
            if path.parent.name.startswith('.restore-'):raise OSError('publish failure')
            return original(path,target)
        with patch.object(build,'reviewed_samples',return_value=self.selection),patch.object(Path,'rename',fail):
            with self.assertRaisesRegex(OSError,'publish failure'):build.recover_all_inputs(self.root)
        self.assertEqual((self.inputs/'sample.wav').read_bytes(),before)
        self.assertFalse(list(self.inputs.parent.parent.glob('.restore-*')))

    def test_changed_float_source_preserved_and_no_published_parts_replaced(self):
        with patch.object(build,'reviewed_samples',return_value=self.selection):
            build.build_parts(self.root)
            path=self.root/'build/us/adpcm/parts'/ (adpcm_layout.part_name(0,0)+'.bin');before=path.read_bytes(),path.stat().st_mtime_ns
            pcm=self.pcm.copy();pcm[0]+=32768;(self.inputs/'sample.wav').write_bytes(headroom.source_float_wav(pcm,22050))
            with self.assertRaisesRegex(ValueError,'Inputs were preserved'):build.build_parts(self.root)
        self.assertEqual((path.read_bytes(),path.stat().st_mtime_ns),before)
        self.assertEqual(headroom.read_float_wav((self.inputs/'sample.wav').read_bytes(),22050,32),pcm)

    def test_native_report_uses_actual_complete_linker_object_with_float_source_hashes(self):
        from test_objdiff_data_targets import object_file,targets
        name=adpcm_layout.part_name(0,0);linked=self.root/('build/us/assets/'+name+'.o');linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data',1,3,self.packed)]))
        def link(args,*,cwd,check):
            original=(cwd/args[-1]).read_bytes();self.assertEqual(original,self.packed)
            (cwd/'target.o').write_bytes(object_file([('.data',1,3,original)]))
        with patch.object(targets,'ROOT',self.root),patch.object(targets,'adpcm_build',build),patch.object(targets.subprocess,'run',side_effect=link):
            pairs=targets.prepare_adpcm_sample(self.rom,self.expected,output=self.root/'report')
            self.assertEqual(len(pairs),1);unit,item=pairs[0];self.assertTrue(unit['complete'])
            self.assertEqual(unit['report_data_bytes'],24);self.assertEqual(len(unit['source_inputs']),3)
            linked.write_bytes(object_file([('.data',1,3,self.raw+bytes([1])*6)]))
            with self.assertRaisesRegex(ValueError,'candidate differs'):targets.prepare_adpcm_sample(self.rom,self.expected,output=self.root/'report')

if __name__=='__main__':unittest.main()
