from __future__ import annotations

import struct
import sys
import tempfile
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_targets as targets


def elf_fixture(extra_name=b'.data', extra_size=0):
    data = bytearray(52)
    data[:7] = b'\x7fELF\x01\x02\x01'
    struct.pack_into('>HH', data, 16, 1, 8)
    data.extend(bytes(8 + extra_size))
    names_offset = len(data)
    names = b'\0.text\0' + extra_name + b'\0.shstrtab\0'
    data.extend(names)
    data.extend(bytes(-len(data) % 4))
    section_offset = len(data)
    sections = [(0,)*10, (1,1,6,0,52,8,0,0,4,0),
                (7,1,2,0,60,extra_size,0,0,4,0),
                (8+len(extra_name),3,0,0,names_offset,len(names),0,0,1,0)]
    for section in sections:
        data.extend(struct.pack('>10I',*section))
    struct.pack_into('>I',data,32,section_offset)
    struct.pack_into('>HHH',data,46,40,len(sections),3)
    return bytes(data)


class TargetValidationTests(unittest.TestCase):
    def test_full_linked_bytes_include_padding(self):
        expected = bytes.fromhex('03e000080000000000000000')
        result = targets.verify_linked_bytes(expected, expected, 'game')
        self.assertEqual(result['bytes'],12)
        for actual in (expected[:-4], expected+b'\0'*4, expected[:-1]+b'\1'):
            with self.subTest(actual=actual), self.assertRaisesRegex(ValueError,'differs'):
                targets.verify_linked_bytes(actual, expected, 'game')

    def test_equal_length_instruction_or_relocation_corruption_is_rejected(self):
        with self.assertRaisesRegex(ValueError,r'\+0x3'):
            targets.verify_linked_bytes(bytes.fromhex('0c0089bd'),bytes.fromhex('0c0089bc'),'main')

    def test_text_extent_includes_all_section_bytes(self):
        self.assertEqual(targets.text_extent(elf_fixture()),8)

    def test_unknown_data_cannot_be_silently_discarded(self):
        for name in (b'.data', b'.rodata', b'.late_rodata', b'.other'):
            with self.subTest(name=name), self.assertRaisesRegex(ValueError,'unmapped allocated'):
                targets.text_extent(elf_fixture(name,4))

    def test_mips_metadata_is_not_game_data(self):
        self.assertEqual(targets.text_extent(elf_fixture(b'.reginfo',24)),8)

    def test_truncated_or_wrong_architecture_objects_fail(self):
        bad = bytearray(elf_fixture())
        struct.pack_into('>H',bad,18,3)
        for data in (bytes(bad),elf_fixture()[:-1],b'not ELF'):
            with self.subTest(data=data[:20]), self.assertRaises(ValueError):
                targets.text_extent(data)

    def test_link_uses_actual_definitions_and_asserts_each_range(self):
        units=[{'start':0,'end':8,'overlay':'game','key':'game/0'},
               {'start':8,'end':16,'overlay':'game','key':'game/8'}]
        script=targets.linker_script(units,[Path('a.o'),Path('b.o')],'func_15000008 = 0x15000008;')
        self.assertIn('PROVIDE(func_15000008 = 0x15000008)',script)
        self.assertIn('.unit1 0x15000008',script)
        self.assertEqual(script.count('ASSERT(SIZEOF('),2)
        with self.assertRaises(ValueError):
            targets.linker_script(units,[Path('a.o')],'')

    def test_padding_is_audited_without_extending_function_sizes(self):
        symbols = {'f': {'address':0, 'size':8, 'hidden':False},
                   'g': {'address':12, 'size':4, 'hidden':False}}
        result = targets.symbol_coverage(bytes.fromhex('03e0000800000000') + bytes(12), symbols)
        self.assertEqual(result['report_code_bytes'],12)
        self.assertEqual(result['excluded_zero_bytes'],8)
        self.assertEqual(result['excluded_zero_ranges'],[{'start':8,'end':12},{'start':16,'end':20}])
        with self.assertRaisesRegex(ValueError,'nonzero original bytes'):
            targets.symbol_coverage(bytes.fromhex('03e0000800000000') + b'\1' + bytes(11), symbols)
        symbols['g']['address'] = 4
        with self.assertRaisesRegex(ValueError,'overlapping'):
            targets.symbol_coverage(bytes(20), symbols)

    def test_isolated_splat_config_preserves_source_and_missing_units(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(targets,'ROOT',Path(tmp)):
            root=Path(tmp)
            binary=root/'game.bin'
            binary.write_bytes(bytes(32))
            dest=root/'build/us/report/targets/game'
            units=[{'start':0,'end':16,'kind':'source','overlay':'game'},
                   {'start':16,'end':32,'kind':'unassigned','overlay':'game'}]
            config=targets.config_document(units,dest,binary,'test-sha1')
            options=config['options']
            self.assertTrue(options['make_full_disasm_for_code'])
            self.assertTrue(options['asm_emit_size_directive'])
            self.assertFalse(options['create_c_files'])
            self.assertEqual((dest.parent/options['base_path']).resolve(),root.resolve())
            for key in ('asm_path','src_path','asset_path','build_path','ld_script_path','cache_path',
                        'undefined_funcs_auto_path','undefined_syms_auto_path'):
                self.assertTrue((root/options[key]).is_relative_to(dest))
            self.assertEqual(config['segments'][0]['subsegments'],
                             [[0,'c','000000'],[16,'asm','000010']])
            self.assertEqual(config['sha1'],'test-sha1')


if __name__ == '__main__':
    unittest.main()
