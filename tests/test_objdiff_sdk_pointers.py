"""Independent ROM-free regression checks for main-runtime comparison pointers."""
import copy
import hashlib
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_candidate as c
import objdiff_data_targets as targets
import objdiff_sdk_pointers as sdk
from prepare_main_library_object import rebase_code_pointers


class ReferenceNamesTests(unittest.TestCase):
    def test_generated_suffix_only_and_matching_link_definition(self):
        text = '/* 0 80000000 10001234 */ .word .L10001234_main_data'
        self.assertEqual(targets.reference_definitions(text, bytes.fromhex('10001234')), {'.L10001234': 0x10001234})
        self.assertEqual(targets.reference_label_names('.L10001234_game .L10001234_main_data_extra x.L10001234_main_data'),
                         '.L10001234_game .L10001234_main_data_extra x.L10001234_main_data')
        self.assertIn('.word .L10001234', targets.reference_assembly('.section .data\n' + text, '.data'))

    def test_only_main_analysis_context_uses_execution_alias(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp);directory = root / 'targets';directory.mkdir()
            binary = root / 'input.bin';binary.write_bytes(bytes(64))
            image = {'vram_start': 0x80000020, 'ranges': [{'start': 0x80000020}]}
            with patch.object(targets, 'ROOT', root):
                main = targets.target_config(image, directory, binary, 0, 32, code_vram=0x80001000)
                game = targets.target_config(image, directory, binary, 0, 32, overlay='game', code_vram=0x15000000)
            self.assertEqual(main['segments'][0]['vram'], 0x10001000)
            self.assertEqual(main['segments'][1]['vram'], 0x80000020)
            self.assertEqual(main['options']['reloc_addrs_path'], ['config/relocs/main-data-us.txt'])
            self.assertEqual(game['segments'][0]['vram'], 0x15000000)
            self.assertEqual(game['options']['reloc_addrs_path'], ['config/relocs/game-data-us.txt'])


@unittest.skipUnless(shutil.which('mips-linux-gnu-as') and shutil.which('mips-linux-gnu-ld'),
                     'requires pinned MIPS binutils')
class RuntimePointerTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.directory = Path(self.tmp.name);self.raw_path = self.directory / 'raw.o'
        subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32', '-no-pad-sections',
                        '-o', str(self.raw_path), str(ROOT / 'tests/fixtures/objdiff_candidate/adjacent_switches.s')], check=True)
        self.original = self.raw_path.read_bytes()
        self.raw = rebase_code_pointers(self.original, sdk.ALIAS_DELTA, 5)
        self.raw_path.write_bytes(self.raw);self.obj = c.Elf(self.raw)
        self.bases = {'.text': 0x80001000, '.rodata': 0x80002000}
        script = self.directory / 'runtime.ld';self.runtime_path = self.directory / 'runtime.elf'
        script.write_text('SECTIONS { .text 0x80001000 : { *(.text) } '
                          '.rodata 0x80002000 : { *(.rodata) } .bss 0x80003000 : { *(.bss) } '
                          '/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.gnu.attributes) } }\n')
        subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script),
                        '-o', str(self.runtime_path), str(self.raw_path)], check=True)

    def test_adjacent_bounds_and_exact_runtime_destinations(self):
        result, proof = sdk.canonicalize(self.raw, self.bases, 5)
        self.assertEqual([(s['offset'], s['size']) for s in proof['symbols']], [(0, 8), (8, 12)])
        after = c.Elf(result);text = self.obj.names.index('.text');rodata = self.obj.names.index('.rodata')
        self.assertEqual(after.payload(text), self.obj.payload(text))
        self.assertEqual(after.payload(rodata), bytes(20))
        for (section, offset), (kind, index) in self.obj.relocations.items():
            if section != rodata:continue
            original = (self.bases['.text'] + self.obj.symbols[index][1] + self.obj.word(section, offset)) & 0xffffffff
            new_kind, new_index = after.relocations[(section, offset)]
            self.assertEqual(new_kind, kind)
            self.assertEqual(after.symbols[new_index][1], original)
            self.assertEqual(after.symbols[new_index][5], 0xfff1)
        path = self.directory / 'canonical.o';path.write_bytes(result)
        linked = sdk.verify_linked(self.raw_path, path, self.runtime_path.read_bytes(), self.bases, self.directory / 'proof')
        self.assertTrue(linked['raw_and_canonical_match_runtime'])
        self.assertEqual(linked['nobits_placements'], {'.bss': 0x80003000})
        self.assertEqual(self.raw_path.read_bytes(), self.raw)

    def test_bad_guards_registers_delay_slots_and_destinations_are_rejected(self):
        text = self.obj.names.index('.text');rodata = self.obj.names.index('.rodata')
        for section, offset, value in [(text, 0, 0x2c810001), (text, 4, 0x10200000),
                                       (text, 8, 0x24040002), (text, 12, 0), (text, 20, 0),
                                       (text, 28, 0), (text, 32, 0x24020001),
                                       (rodata, 0, 0x9000ffff)]:
            changed = bytearray(self.raw);struct.pack_into('>I', changed, self.obj.headers[section][4] + offset, value)
            with self.subTest(section=section, offset=offset), self.assertRaises((ValueError, c.AnnotationError)):
                sdk.canonicalize(bytes(changed), self.bases, 5)
        with self.assertRaises(ValueError):sdk.canonicalize(self.raw, self.bases, 4)
        with self.assertRaises(c.AnnotationError):sdk.canonicalize(self.original, self.bases, 5)
        with self.assertRaises(c.AnnotationError):sdk.canonicalize(self.raw, {**self.bases, '.text': 0x15000000}, 5)

    def test_verifier_rejects_code_pointer_symbol_and_relocation_tampering(self):
        result, _ = sdk.canonicalize(self.raw, self.bases, 5);obj = c.Elf(result)
        text, rodata = obj.names.index('.text'), obj.names.index('.rodata')
        rel = obj.names.index('.rel.rodata')
        label = next(i for i,s in enumerate(obj.symbols) if s[5] == 0xfff1)
        edits = [(obj.headers[text][4], obj.word(text, 0) ^ 1), (obj.headers[rodata][4], 4),
                 (obj.headers[rel][4]+4, 2), (obj.headers[obj.symtab][4]+label*16+4, 0x10001000)]
        for at, value in edits:
            changed = bytearray(result);struct.pack_into('>I', changed, at, value)
            with self.subTest(at=at), self.assertRaises(c.AnnotationError):
                sdk.verify(self.raw, bytes(changed), self.bases, 5)

    def test_whole_link_rejects_wrong_code_placement_and_corrupted_runtime(self):
        result, _ = sdk.canonicalize(self.raw, self.bases, 5);path=self.directory/'canonical.o';path.write_bytes(result)
        with self.assertRaises(c.AnnotationError):
            sdk.verify_linked(self.raw_path,path,self.runtime_path.read_bytes(),{**self.bases,'.text':0x80001100},self.directory/'bad-base')
        runtime=bytearray(self.runtime_path.read_bytes());obj=c.Elf(bytes(runtime),2)
        runtime[obj.headers[obj.names.index('.rodata')][4]]^=1
        with self.assertRaises(c.AnnotationError):
            sdk.verify_linked(self.raw_path,path,bytes(runtime),self.bases,self.directory/'bad-runtime')

    def test_report_hook_requires_actual_archive_and_complete_reviewed_ownership(self):
        root = self.directory / 'checkout';output = root / 'report';output.mkdir(parents=True)
        (output / 'raw.o').write_bytes(self.raw)
        archive = root / 'build/us/lib/libultrare.a';archive.parent.mkdir(parents=True)
        archive.write_bytes(b'fixture archive')
        (root / 'build/us/conker.us.elf').write_bytes(self.runtime_path.read_bytes())
        runtime=c.Elf(self.runtime_path.read_bytes(),2)
        code=runtime.payload(runtime.names.index('.text'))
        digest=hashlib.sha256(runtime.payload(runtime.names.index('.rodata'))).hexdigest()
        unit = {'kind':'sdk','overlay':'main','archive':'libultrare','member':'fixture.o',
                'start':0x1000,'end':0x1000+len(code),'key':'main/fixture','base_path':'raw.o','complete':False,
                'data_ranges':[{'kind':'sdk_placement','owner':{'archive':'libultrare','member':'fixture.o'},
                                'evidence_reference':'config/profiles/us.yaml','section':'.rodata',
                                'start':0x80002000,'size':20,'sha256':digest}]}
        config = {'base_path':'raw.o','metadata':{'complete':False}}
        with patch.object(sdk,'OWNERS',{'fixture.o':5}), \
             patch.object(sdk.rom_span,'main_code',return_value=(code,0x80001000,'fixture')), \
             patch.object(sdk.subprocess,'check_output',return_value=self.raw):
            for key,value in [('size',16),('evidence_reference','unreviewed'),('sha256','0'*64),
                              ('owner',{'archive':'other','member':'fixture.o'})]:
                bad=copy.deepcopy(unit);bad['data_ranges'][0][key]=value
                with self.subTest(key=key), self.assertRaises(c.AnnotationError):
                    sdk.prepare_candidates([bad],[copy.deepcopy(config)],root,output)
            (output/'raw.o').write_bytes(b'stale')
            with self.assertRaisesRegex(c.AnnotationError,'actual archive'):
                sdk.prepare_candidates([unit],[config],root,output)
            (output/'raw.o').write_bytes(self.raw)
            sdk.prepare_candidates([unit],[config],root,output)
        self.assertEqual((output/'raw.o').read_bytes(),self.raw)
        self.assertFalse(unit['complete']);self.assertFalse(config['metadata']['complete'])
        self.assertTrue(unit['comparison_copy']['linked_verification']['raw_and_canonical_match_runtime'])


if __name__ == '__main__':
    unittest.main()
