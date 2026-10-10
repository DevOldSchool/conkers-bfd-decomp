from __future__ import annotations

import hashlib
import json
import struct
import subprocess
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


    def test_debugger_uses_full_rom_symbols_and_eight_byte_alignment(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(targets, 'ROOT', Path(tmp)):
            root = Path(tmp)
            binary = root / 'roms/baserom.us.z64'
            binary.parent.mkdir()
            binary.write_bytes(bytes(0x1A33E8))
            units = [{'start': 0x19EA88, 'end': 0x1A2178, 'kind': 'unassigned',
                      'overlay': 'debugger', 'key': 'debugger/19EA88'}]
            config = targets.config_document(units, root / 'report/targets/debugger', binary, 'us-sha1')
            self.assertEqual(config['options']['target_path'], 'roms/baserom.us.z64')
            self.assertEqual(config['options']['symbol_addrs_path'], ['config/symbols/us.txt'])
            self.assertEqual(config['options']['reloc_addrs_path'], ['config/relocs/us.txt'])
            self.assertEqual(config['segments'][0], [0, 'bin', 'prefix'])
            self.assertEqual(config['segments'][1]['vram'], 0x16000000)
            self.assertEqual(config['segments'][1]['align'], 8)
            self.assertEqual(config['segments'][1]['subsegments'], [[0x19EA88, 'asm', '19EA88']])
            self.assertEqual(config['segments'][2], [0x1A2178, 'bin', 'suffix'])
            script = targets.linker_script(units, [Path('debugger.o')], '')
            self.assertIn('.unit0 0x16000000', script)
            self.assertIn('ASSERT(SIZEOF(.unit0) == 14064', script)

    def test_debugger_plan_must_cover_checked_text_including_raw_tail(self):
        code = bytes.fromhex('03e0000800000000')
        start = targets.DEBUGGER_ROM_START
        rom = bytes(start) + code
        units = [{'overlay': 'debugger', 'start': start, 'end': start + len(code)}]
        with patch.object(targets.rom_span, 'debugger_code', return_value=(code, 0x16000000, 'sha1')):
            self.assertEqual(targets.debugger_target_bytes(units, rom, 'sha1'), code)
            invalid = [[], [{**units[0], 'start': start + 4}], [{**units[0], 'end': start + 4}],
                       [{'overlay': 'debugger', 'start': start, 'end': start + 4},
                        {'overlay': 'debugger', 'start': start + 8, 'end': start + 8}]]
            for plan in invalid:
                with self.subTest(plan=plan), self.assertRaisesRegex(ValueError, 'complete checked text'):
                    targets.debugger_target_bytes(plan, rom, 'sha1')
            with self.assertRaisesRegex(ValueError, 'checked ROM image'):
                targets.debugger_target_bytes(units, rom[:-1] + b'\1', 'sha1')
        for image in ((code, 0x80000000, 'sha1'), (code, 0x16000000, 'different-sha1')):
            with patch.object(targets.rom_span, 'debugger_code', return_value=image), \
                    self.assertRaisesRegex(ValueError, 'checked ROM image'):
                targets.debugger_target_bytes(units, rom, 'sha1')

    def test_prepare_rejects_omitted_debugger_before_running_tools(self):
        with patch.object(targets.subprocess, 'run') as run:
            with self.assertRaisesRegex(ValueError, 'every US CPU overlay'):
                targets.prepare([{'overlay': 'main'}, {'overlay': 'game'}], Path('unused'))
        run.assert_not_called()

    def test_prepare_proves_debugger_linked_bytes_and_rejects_corruption(self):
        for corrupt in (False, True):
            with self.subTest(corrupt=corrupt), tempfile.TemporaryDirectory() as tmp, \
                    patch.object(targets, 'ROOT', Path(tmp)):
                root, start = Path(tmp), targets.DEBUGGER_ROM_START
                code = bytes.fromhex('03e0000800000000')
                game = bytes.fromhex('0800000400000000')
                rom = code + bytes(start - len(code)) + code
                digest = hashlib.sha1(rom).hexdigest()
                (root / 'roms').mkdir()
                (root / 'roms/baserom.us.z64').write_bytes(rom)
                (root / 'config').mkdir()
                (root / 'config/roms.json').write_text(json.dumps({'profiles': {'us': {
                    'size_bytes': len(rom), 'sha1': digest}}}))
                (root / 'config/overlays.json').write_text(json.dumps({'overlays': {'game': {
                    'profiles': {'us': {'sha1': hashlib.sha1(game).hexdigest()}}}}}))
                specs = [{'overlay': overlay, 'start': offset, 'end': offset + 8,
                          'kind': 'unassigned', 'key': f'{overlay}/{offset:06X}'}
                         for overlay, offset in [('main', 0), ('game', 0), ('debugger', start)]]
                commands = []
                def run(command, **kwargs):
                    commands.append(command)
                    if command[0] == 'splat':
                        config = json.loads(Path(command[2]).read_text())
                        directory = root / config['options']['asm_path']
                        directory.mkdir(parents=True)
                        segment = next(s for s in config['segments'] if isinstance(s, dict))
                        for offset, _, name in segment['subsegments']:
                            (directory / (name + '.s')).write_text('glabel f\n')
                        for name in ('undefined_funcs.txt', 'undefined_syms.txt'):
                            (directory.parent / name).write_text('')
                    elif command[0] == 'mips-linux-gnu-as':
                        Path(command[command.index('-o') + 1]).write_bytes(bytes(8))
                    elif command[0] == 'mips-linux-gnu-objcopy':
                        path = Path(command[-1])
                        data = game if path.parent.name == 'game' else code
                        if corrupt and path.parent.name == 'debugger':
                            data = data[:-1] + b'\1'
                        path.write_bytes(data)
                    return subprocess.CompletedProcess(command, 0)
                with patch.object(targets.extract_game_code, 'extract_code', return_value=game), \
                        patch.object(targets.rom_span, 'debugger_code', return_value=(code, 0x16000000, digest)), \
                        patch.object(targets, 'text_extent', return_value=8), \
                        patch.object(targets.subprocess, 'run', side_effect=run):
                    if corrupt:
                        with self.assertRaisesRegex(ValueError, 'debugger linked target differs'):
                            targets.prepare(specs, root / 'report')
                    else:
                        prepared, verified = targets.prepare(specs, root / 'report')
                        self.assertEqual(set(verified), {'main', 'game', 'debugger'})
                        self.assertEqual(verified['debugger']['bytes'], 8)
                        self.assertEqual(verified['debugger']['input_sha1'], digest)
                        self.assertTrue(verified['debugger']['matches_original'])
                        self.assertEqual(set(prepared), {s['key'] for s in specs})
                self.assertEqual(sum(c[0] == 'mips-linux-gnu-ld' for c in commands), 3)


if __name__ == '__main__':
    unittest.main()
