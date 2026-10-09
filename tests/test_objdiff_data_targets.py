from __future__ import annotations

from pathlib import Path
import os
import struct
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_data_targets as targets


def object_file(entries):
    names = bytearray(b'\0.shstrtab\0')
    headers = [(0,) * 10]
    body = bytearray(52)
    for name, kind, flags, payload in entries:
        at = len(names)
        names.extend(name.encode() + b'\0')
        headers.append((at, kind, flags, 0, len(body), len(payload), 0, 0, 16, 0))
        if kind != 8:
            body.extend(payload)
    strings_at = len(body)
    body.extend(names)
    headers.append((1, 3, 0, 0, strings_at, len(names), 0, 0, 1, 0))
    header_at = len(body)
    for header in headers:
        body.extend(struct.pack('>10I', *header))
    body[:52] = struct.pack('>16sHHIIIIIHHHHHH', b'\x7fELF\x01\x02\x01' + bytes(9),
                           1, 8, 1, 0, 0, header_at, 0, 52, 0, 0, 40, len(headers), len(headers)-1)
    return bytes(body)


class DataTargetTests(unittest.TestCase):
    @unittest.skipUnless(os.environ.get('CONKER_ROM_TESTS') == '1' and shutil.which('splat')
                         and shutil.which('mips-linux-gnu-as'), 'requires owned ROM and toolchain')
    def test_canonical_sdk_payload_extents_survive_splat_and_full_image_link(self):
        audit = targets.data_boundaries.audit(ROOT)
        declared = targets.declared_data_symbols(ROOT / 'config/symbols/us.txt')
        self.assertTrue(declared)
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='sdk-symbol-test-') as tmp:
            output = Path(tmp)
            units, proof = targets.prepare_targets(audit['images']['main'],
                (ROOT / 'roms/baserom.us.z64').read_bytes(), output=output)
            self.assertTrue(proof['matches_original'])
            found = {}
            for unit in units:
                obj = targets.Object32((output / unit['target_path']).read_bytes())
                for name, offset, size, section in obj.non_section_symbols:
                    if name in declared and section:
                        self.assertNotIn(name, found)
                        found[name] = (unit['start'] + offset, size)
            self.assertEqual(found, declared)

    def test_declared_padding_is_anonymous_but_keeps_every_byte(self):
        text = (
            '.section .data, "wa"\n'
            'glabel counter\n'
            '/* 0010 80000010 00000000 */ .word 0x00000000\n'
            '.size counter, . - counter\n'
            '/* Automatically generated and unreferenced pad */\n'
            'glabel D_80000014\n'
            '/* 0014 80000014 00000000 */ .word 0x00000000\n'
            '/* 0018 80000018 00000000 */ .word 0x00000000\n'
            '/* 001C 8000001C 00000000 */ .word 0x00000000\n'
            '.size D_80000014, . - D_80000014\n')
        declared = {'counter': (0x80000010, 4)}
        actual = targets.reference_assembly(text, '.data', declared_symbols=declared)
        self.assertNotIn('D_80000014', actual)
        self.assertIn('.size counter, . - counter', actual)
        self.assertEqual(actual.count('.word 0x00000000'), 4)
        for modified, sizes in (
                (text, {}),
                (text, {'counter': (0x80000010, 8)}),
                (text, {'counter': (0x80000000, 4)}),
                (text.replace(' and unreferenced', ''), declared),
                (text.replace('001C 8000001C 00000000', '001C 8000001C 00000001'), declared),
                (text.replace('001C 8000001C', '0020 80000020'), declared),
                (text.replace('.word 0x00000000\n.size D_', '.word 0x00000001\n.size D_'), declared),
                (text.replace('.size D_', '/* 0020 80000020 00000000 */ .word 0x00000000\n.size D_'), declared)):
            with self.subTest(text=modified, sizes=sizes):
                actual = targets.reference_assembly(modified, '.data', declared_symbols=sizes)
                self.assertIn('.globl D_80000014', actual)

    def test_rodata_zero_padding_accepts_float_and_byte_rows(self):
        for directive, width, encoded in (('float 0', 4, '00000000 '), ('byte 0x00', 1, '')):
            with self.subTest(directive=directive):
                payload = ('glabel scalar\n'
                           '/* 0010 80000010 00000001 */ .word 0x00000001\n'
                           '.size scalar, . - scalar\n')
                padding = ''.join(f'/* {offset:04X} {0x80000000 + offset:08X} {encoded}*/ .{directive}\n'
                                  for offset in range(0x14, 0x20, width))
                text = ('.section .rodata, "a"\n' + payload
                        + '/* Automatically generated and unreferenced pad */\n'
                        + 'glabel pad\n' + padding + '.size pad, . - pad\n')
                actual = targets.reference_assembly(text, '.rodata', declared_symbols={'scalar': (0x80000010, 4)})
                self.assertNotIn('.globl pad', actual)
                self.assertIn(padding, actual)

    def test_pointer_definitions_use_verified_original_rows(self):
        rom = bytes.fromhex('10002ff4')
        text = '/* 0000 80000000 10002FF4 */ .word .L10002FF4_main-data'
        # The actual generated labels use underscores; unsupported names fail at link time.
        text = text.replace('main-data', 'main_data')
        self.assertEqual(targets.reference_definitions(text, rom), {'.L10002FF4_main_data': 0x10002FF4})
        with self.assertRaises(ValueError):
            targets.reference_definitions(text, bytes(4))
        with self.assertRaises(ValueError):
            targets.reference_definitions(text.replace('80000000', '80000004'), rom)
        self.assertEqual(targets.reference_definitions(text + ' + 4', rom), {})

    def test_debugger_pointer_rows_use_loaded_origin_and_checked_bytes(self):
        image = bytes(16) + bytes.fromhex('16001AD0')
        text = '/* 0010 16000010 16001AD0 */ .word func_16001AD0'
        self.assertEqual(targets.reference_definitions(text, image, origin=0x16000000),
                         {'func_16001AD0': 0x16001AD0})
        with self.assertRaisesRegex(ValueError, 'original ROM'):
            targets.reference_definitions(text, image)
        with self.assertRaisesRegex(ValueError, 'original ROM'):
            targets.reference_definitions(text.replace('16000010', '16000014'), image,
                                        origin=0x16000000)

    def test_target_configs_preserve_code_data_coordinates_and_all_gaps(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            directory = root / 'build/us/report/debugger-targets'
            directory.mkdir(parents=True)
            binary = directory / 'input.bin'
            binary.write_bytes(bytes(80))
            image = {'vram_start': 0x16000020, 'vram_end': 0x16000050,
                     'ranges': [{'start': 0x16000020}, {'start': 0x16000030, 'input': '.rodata'},
                                {'start': 0x16000040}]}
            with patch.object(targets, 'ROOT', root):
                config = targets.target_config(image, directory, binary, 0, 32,
                                             overlay='debugger', origin=0x16000000)
                self.assertEqual(len(config['segments']), 3)
                self.assertEqual(config['segments'][0]['subsegments'], [[0, 'asm', 'context']])
                self.assertEqual(config['segments'][1]['vram'], 0x16000020)
                self.assertEqual(config['segments'][1]['subsegments'],
                                 [[32, 'data', '16000020'], [48, 'rodata', '16000030'],
                                  [64, 'data', '16000040']])
                self.assertEqual(config['segments'][2], [80])
                self.assertEqual((directory.parent / config['options']['base_path']).resolve(), root.resolve())
                with self.assertRaisesRegex(ValueError, 'overlaps'):
                    targets.target_config(image, directory, binary, 0, 36,
                                        overlay='debugger', origin=0x16000000)

    def test_debugger_reference_rejects_changed_data_or_loader_boundary_before_splat(self):
        import hashlib
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            rom, code, data = bytes(64), bytes(16), bytes(32)
            image = {'vram_start': 0x16000010, 'vram_end': 0x16000030, 'loaded_bytes': 32,
                     'sha256': hashlib.sha256(data).hexdigest(), 'ranges': []}
            for wrong_base, wrong_data in ((0x16000014, data), (0x16000010, bytes([1])*32)):
                with self.subTest(base=wrong_base, data=wrong_data), \
                        patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                        patch.object(targets.rom_span, 'debugger_image', return_value=(
                            code, wrong_data, 0x16000000, wrong_base, hashlib.sha1(rom).hexdigest())), \
                        patch.object(targets.subprocess, 'run') as run:
                    with self.assertRaises(ValueError):
                        targets.prepare_targets(image, rom, overlay='debugger')
                    run.assert_not_called()

    def test_debugger_candidate_uses_debugger_source_and_category(self):
        import hashlib
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / 'src/debugger/debugger_1AD0.c'
            source.parent.mkdir(parents=True)
            source.write_text('void formatter(void) {}\n')
            # A main file with the same name must never supply debugger data.
            other = root / 'src/main/debugger_1AD0.c'
            other.parent.mkdir(parents=True)
            other.write_text('')
            unit = {'key': '1600487C', 'kind': 'external_payload', 'overlay': 'debugger',
                    'owner': {'sources': ['src/debugger/debugger_1AD0.c',
                                          'src/done/debugger/debugger_1AD0.c']},
                    'input_selector': '*debugger_1AD0.o(.rodata)', 'section': '.rodata',
                    'size': 16, 'target_path': 'target.o', 'sha256': hashlib.sha256(bytes(16)).hexdigest()}
            blob = object_file([('.rodata', 1, 2, bytes(16))])
            def compile_(command, **kwargs):
                (root / '1600487C/base.o').write_bytes(blob)
                return SimpleNamespace(returncode=0)
            with patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                    patch.object(targets.subprocess, 'run', side_effect=compile_):
                config = targets.prepare_candidates([unit])
            self.assertEqual(unit['source'], 'src/debugger/debugger_1AD0.c')
            self.assertEqual(config[0]['name'], 'debugger/data/1600487C')
            self.assertEqual(config[0]['metadata']['progress_categories'], ['debugger-data'])
            self.assertFalse(config[0]['metadata']['complete'])
            self.assertEqual((root / unit['base_path']).read_bytes(), blob)

    @unittest.skipUnless(shutil.which('mips-linux-gnu-as'), 'requires pinned MIPS binutils')
    def test_unaligned_range_preserves_original_double_offset_and_exact_extent(self):
        # Runtime addresses are 0x1600494C, 0x16004950 and 0x16004958.
        # The double is aligned in memory but starts at local object offset 4.
        assembly = '.section .data, "wa"\n.word 0\n.double 100000000\n.double 0\n'
        expected = bytes.fromhex('000000004197D784000000000000000000000000')
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source, target = root / 'data.s', root / 'data.o'
            source.write_text(targets.reference_assembly(assembly, '.data'))
            subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32',
                            '-no-pad-sections', '-o', str(target), str(source)], check=True)
            targets.target_extent(target, '.data', 20)
            self.assertEqual(targets.sections(target.read_bytes(), 1)['.data'][1], expected)

    def test_reference_alignment_does_not_rewrite_symbols_or_sizes(self):
        assembly = '.section .rodata, "a"\n.globl table\ntable:\n.word target\n.size table, . - table\n'
        normalized = targets.reference_assembly(assembly, '.rodata')
        self.assertEqual(normalized.replace('.align 0\n', ''), assembly)
        with self.assertRaisesRegex(ValueError, 'one data reference'):
            targets.reference_assembly(assembly, '.data')

    def test_game_context_and_data_have_distinct_loaded_origins(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            directory = root / 'build/us/report/game-targets'
            directory.mkdir(parents=True)
            binary = directory / 'input.bin'
            binary.write_bytes(bytes(64))
            image = {'vram_start': 0x80082B20, 'vram_end': 0x80082B40,
                     'ranges': [{'start': 0x80082B20},
                                {'start': 0x80082B30, 'input': '.rodata.16ee20_0'}]}
            with patch.object(targets, 'ROOT', root):
                config = targets.target_config(image, directory, binary, 0, 32, overlay='game',
                                             origin=0x80082B00, code_vram=0x15000000)
            context, data, end = config['segments']
            self.assertEqual(context['vram'], 0x15000000)
            self.assertEqual(data['vram'], 0x80082B20)
            self.assertEqual(data['subsegments'], [[32, 'data', '80082B20'], [48, 'rodata', '80082B30']])
            self.assertEqual(end, [64])
            self.assertEqual(config['options']['symbol_addrs_path'], ['config/symbols/game-us.txt'])
            pointer_image = bytes(32) + bytes.fromhex('15000004')
            row = '/* 0020 80082B20 15000004 */ .word func_15000004'
            self.assertEqual(targets.reference_definitions(row, pointer_image, origin=0x80082B00),
                             {'func_15000004': 0x15000004})
            with self.assertRaises(ValueError):
                targets.reference_definitions(row, pointer_image, origin=0x15000000)

    def test_game_sdk_uses_reviewed_archive_and_section(self):
        unit = {'kind': 'external_payload', 'overlay': 'game', 'section': '.data', 'key': '80091970',
                'input_selector': 'build/game-libs/us/libultra_2_0G.a:random.o(.data)'}
        self.assertEqual(targets.candidate_archive(unit),
                         (targets.ROOT / 'build/game-libs/us/libultra_2_0G.a', 'random.o'))
        self.assertIsNone(targets.candidate_source(unit))
        for change in ({'overlay': 'main'}, {'section': '.rodata'},
                       {'input_selector': '../lib.a:random.o(.data)'}):
            with self.subTest(change=change):
                invalid = {**unit, **change}
                self.assertIsNone(targets.candidate_archive(invalid))
                with self.assertRaises(ValueError):
                    targets.candidate_source(invalid)

    def test_compiler_padding_keeps_full_base_without_claiming_next_rom_word(self):
        import hashlib
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            payload = bytes(range(12))
            original = object_file([('.rodata', 1, 2, payload + bytes(4))])
            unit = {'key': 'pool', 'kind': 'sdk_placement', 'archive': 'sdk', 'member': 'member.o',
                    'section': '.rodata', 'size': 12, 'emitted_size': 16, 'compiler_padding_bytes': 4,
                    'target_path': 'target.o', 'sha256': hashlib.sha256(payload).hexdigest()}
            with patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                    patch.object(targets.subprocess, 'run', return_value=SimpleNamespace(stdout=original)):
                config = targets.prepare_candidates([unit])
            self.assertEqual((root / config[0]['base_path']).read_bytes(), original)
            self.assertEqual(unit['size'], 12)
            self.assertEqual(unit['candidate_section_size'], 16)
            self.assertEqual(unit['candidate_compiler_padding_bytes'], 4)
            self.assertTrue(unit['literal_payload_matches_rom'])

    def test_bad_padding_extent_bytes_relocations_and_symbols_are_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            base = root / 'base.o'
            good = object_file([('.rodata', 1, 2, bytes(16))])
            base.write_bytes(good)
            unit = {'section': '.rodata', 'size': 12, 'emitted_size': 16, 'compiler_padding_bytes': 4}
            for change in ({'compiler_padding_bytes': 0}, {'size': 0, 'compiler_padding_bytes': 16},
                           {'emitted_size': 12}):
                with self.subTest(change=change), self.assertRaises(ValueError):
                    targets.candidate_section({**unit, **change}, base)
            base.write_bytes(object_file([('.rodata', 1, 2, bytes(15) + b'x')]))
            with self.assertRaisesRegex(ValueError, 'padding'):
                targets.candidate_section(unit, base)
            base.write_bytes(good)
            for kind in ('relocation', 'symbol', 'tail_label'):
                obj = targets.Object32(good)
                section = next(i for i, h in enumerate(obj.sections) if h[1] == 1 and h[5] == 16)
                if kind == 'relocation':
                    obj.relocations[(section, 12)] = (2, ('target', 0, 0, 0))
                elif kind == 'symbol':
                    obj.non_section_symbols.append(('crossing', 8, 8, section))
                else:
                    obj.non_section_symbols.append(('tail_label', 12, 0, section))
                with self.subTest(kind=kind), patch.object(targets, 'Object32', return_value=obj), \
                        self.assertRaisesRegex(ValueError, 'padding'):
                    targets.candidate_section(unit, base)

    def test_split_target_uses_canonical_section_without_rewriting_symbols(self):
        text = '.section .rodata, "a"\n.globl table\ntable:\n.word target\n.size table, . - table\n'
        result = targets.reference_assembly(text, '.rodata', output_section='.rodata.16ee20_0')
        self.assertEqual(result.replace('.rodata.16ee20_0', '.rodata').replace('.align 0\n', ''), text)

    def test_unproved_split_table_retains_target_with_no_stale_candidate_credit(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / 'src/game/game_16EE20.c'
            source.parent.mkdir(parents=True)
            source.write_text('#pragma GLOBAL_ASM("raw.s")\nvoid matched(void) {}\n')
            (root / 'table').mkdir()
            (root / 'table/base.o').write_bytes(b'stale mixed object')
            unit = {'key': 'table', 'kind': 'external_payload', 'overlay': 'game',
                    'input_selector': '*game_16EE20.o(.rodata.16ee20_0)',
                    'section': '.rodata.16ee20_0', 'size': 180, 'target_path': 'target.o'}
            with patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                    patch.object(targets.subprocess, 'run') as run:
                config = targets.prepare_candidates([unit])
            run.assert_not_called()
            self.assertIn('candidate_unavailable', unit)
            self.assertNotIn('base_path', config[0])
            self.assertEqual(config[0]['target_path'], 'target.o')
            self.assertFalse((root / 'table/base.o').exists())


    def test_font_target_is_independent_of_edited_candidate(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            inputs = root / 'build/fonts/us'
            inputs.mkdir(parents=True)
            (inputs / 'manifest.json').write_text('{"glyphs": [{"file": "0030.pgm"}]}')
            (inputs / '0030.pgm').write_bytes(b'edited pixels')
            (root / 'build/us/assets').mkdir(parents=True)
            original, edited = bytes(16), bytes([1]) * 16
            (root / 'build/us/assets/font_test.o').write_bytes(object_file([('.data', 1, 3, edited)]))
            def run(command, **kwargs):
                if command[0] == 'mips-linux-gnu-ld':
                    directory = kwargs['cwd']
                    payload = (directory / command[-1]).read_bytes()
                    (directory / command[-2]).write_bytes(object_file([('.data', 1, 3, payload)]))
            with patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                    patch.object(targets.subprocess, 'run', side_effect=run), \
                    patch.object(targets.font_splits, 'verify_splits', return_value=[(16, 32, 'font_test')]), \
                    patch.object(targets.font_assets, 'load_layout', return_value={
                        'font_start': 16, 'font_storage_end': 32}), \
                    patch.object(targets.font_assets, 'packed_font_bytes', return_value=edited):
                unit, config = targets.prepare_font(bytes(16) + original)
                self.assertFalse(unit['literal_payload_matches_rom'])
                self.assertEqual(targets.sections((root / unit['target_path']).read_bytes(), 1)['.data'][1], original)
                self.assertEqual(config['metadata']['progress_categories'], ['data'])
                self.assertFalse(config['metadata']['complete'])


    def test_texture_batch_builds_all_objects_in_one_make_call(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            selected = [({'flat_index': index}, None) for index in (1063, 1296)]
            with patch.object(targets, 'ROOT', root), \
                    patch.object(targets.texture_build, 'reviewed_textures', return_value=(b'ROM', selected)), \
                    patch.object(targets, 'prepare_texture', side_effect=[({'key': 'a'}, {'name': 'a'}),
                                                                        ({'key': 'b'}, {'name': 'b'})]) as prepare, \
                    patch.object(targets.subprocess, 'run') as run:
                units, configs = targets.prepare_textures(b'ROM', output=root)
                self.assertEqual(len(units), 2)
                self.assertEqual(len(configs), 2)
                self.assertEqual(prepare.call_count, 2)
                run.assert_called_once()
                self.assertEqual(run.call_args.args[0], ['make', '--silent', '--jobs', '4',
                    'build/us/assets/flat/textures/1063.o', 'build/us/assets/flat/textures/1296.o', 'PROFILE=us'])
                run.reset_mock()
                with self.assertRaisesRegex(ValueError, 'reference ROM differs'):
                    targets.prepare_textures(b'wrong ROM', output=root)
                run.assert_not_called()

    def test_texture_uses_actual_link_input_and_rejects_stale_object(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            original = bytes(range(16))
            rom = bytes(16) + original
            expected = {'flat_index': 1063, 'rom_start': 16, 'rom_end': 32}
            linked = root / ('build/us/assets/' + targets.texture_build.part_name(1063) + '.o')
            linked.parent.mkdir(parents=True)
            linked.write_bytes(object_file([('.data', 1, 3, original)]))
            change_during_wrap = False
            def run(command, **kwargs):
                if command[0] == 'mips-linux-gnu-ld':
                    directory = kwargs['cwd']
                    payload = (directory / command[-1]).read_bytes()
                    (directory / command[-2]).write_bytes(object_file([('.data', 1, 3, payload)]))
                    if change_during_wrap:
                        linked.write_bytes(object_file([('.data', 1, 3, bytes([1]) * 16)]))
            with patch.object(targets, 'ROOT', root), \
                    patch.object(targets.subprocess, 'run', side_effect=run), \
                    patch.object(targets.texture_build, 'packed_texture', return_value=(original, {'1063.ci4.png': 'hash'})), \
                    patch.object(targets.texture_build, 'input_hashes', return_value={'1063.ci4.png': 'hash'}):
                unit, config = targets.prepare_texture(rom, expected, output=root)
                self.assertEqual(unit['report_data_bytes'], 16)
                self.assertEqual(unit['report_code_bytes'], 0)
                self.assertTrue(config['metadata']['complete'])
                self.assertEqual(config['metadata']['progress_categories'], ['data'])
                self.assertEqual((root / unit['base_path']).read_bytes(), linked.read_bytes())
                self.assertEqual(targets.sections((root / unit['target_path']).read_bytes(), 1)['.data'][1], original)
                self.assertIn(linked.relative_to(root).as_posix(), unit['linked_inputs'])
                change_during_wrap = True
                with self.assertRaisesRegex(ValueError, 'current editable inputs'):
                    targets.prepare_texture(rom, expected, output=root)
                change_during_wrap = False
                with self.assertRaisesRegex(ValueError, 'current editable inputs'):
                    targets.prepare_texture(rom, expected, output=root)

    def test_target_extent_checks_every_allocated_section(self):
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'target.o'
            cases = [([('.data', 1, 3, bytes(16))], True),
                     ([('.data', 1, 3, bytes(16)), ('.text', 1, 6, bytes(4))], False),
                     ([('.data', 1, 3, bytes(16)), ('.bss', 8, 3, bytes(4))], False),
                     ([('.data', 1, 3, bytes(32))], False),
                     ([('.data', 8, 3, bytes(16))], False),
                     ([('.data', 1, 0, bytes(16))], False),
                     ([('.rodata', 1, 2, bytes(16))], False)]
            for entries, valid in cases:
                path.write_bytes(object_file(entries))
                with self.subTest(entries=entries):
                    if valid:
                        targets.target_extent(path, '.data', 16)
                    else:
                        with self.assertRaises(ValueError):
                            targets.target_extent(path, '.data', 16)

    def test_candidate_retains_relocations_and_other_sections(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / 'src/main/test.c'
            source.parent.mkdir(parents=True)
            source.write_text('#pragma GLOBAL_ASM("raw.s")\n#if 0\nvoid deferred(void) {}\n#endif\n')
            unit = {'key': '8002AB40', 'kind': 'private_section', 'sources': ['src/main/test.c'],
                    'section': '.data', 'size': 16, 'target_path': 'target.o'}
            blob = object_file([('.text', 1, 6, bytes(32)), ('.data', 1, 3, bytes(16)),
                                ('.rel.data', 9, 0, bytes(8))])
            def compile_(command, **kwargs):
                (root / '8002AB40/base.o').write_bytes(blob)
                return SimpleNamespace(returncode=0)
            with patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                    patch.object(targets.subprocess, 'run', side_effect=compile_), \
                    patch.object(targets, 'Object32', return_value=SimpleNamespace(
                        sections=[h for h, _ in targets.sections(blob, 1).values()],
                        relocations={(1, 0): 'preserved'})):
                config = targets.prepare_candidates([unit])
            self.assertEqual((root / '8002AB40/base.o').read_bytes(), blob)
            focused = (root / '8002AB40/base.c').read_text()
            self.assertNotIn('GLOBAL_ASM', focused)
            self.assertIn('#if 0', focused)
            self.assertIn('base_path', config[0])
            self.assertFalse(config[0]['metadata']['complete'])

    def test_wrong_size_candidate_keeps_target_without_base(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            unit = {'key': 'test', 'kind': 'sdk_placement', 'archive': 'sdk', 'member': 'member.o',
                    'section': '.data', 'size': 16, 'target_path': 'target.o'}
            blob = object_file([('.data', 1, 3, bytes(32))])
            with patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                    patch.object(targets.subprocess, 'run', return_value=SimpleNamespace(stdout=blob)):
                config = targets.prepare_candidates([unit])
            self.assertEqual(config[0]['target_path'], 'target.o')
            self.assertNotIn('base_path', config[0])
            self.assertIn('candidate_error', unit)

    def test_literal_equality_is_separate_from_native_credit(self):
        import hashlib
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for payload in (bytes(16), bytes([1]) * 16):
                unit = {'key': 'test', 'kind': 'sdk_placement', 'archive': 'sdk', 'member': 'member.o',
                        'section': '.data', 'size': 16, 'target_path': 'target.o',
                        'sha256': hashlib.sha256(bytes(16)).hexdigest()}
                blob = object_file([('.data', 1, 3, payload)])
                with patch.object(targets, 'ROOT', root), patch.object(targets, 'OUTPUT', root), \
                        patch.object(targets.subprocess, 'run', return_value=SimpleNamespace(stdout=blob)):
                    config = targets.prepare_candidates([unit])
                self.assertEqual(unit['literal_payload_matches_rom'], not any(payload))
                self.assertNotIn('matched_data', unit)
                self.assertIn('base_path', config[0])
                self.assertFalse(config[0]['metadata']['complete'])

    def test_unknown_data_has_no_base_even_with_stale_object(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / 'raw').mkdir()
            (root / 'raw/base.o').write_bytes(b'stale candidate')
            unit = {'key': 'raw', 'kind': 'unassigned', 'section': '.data', 'size': 16,
                    'target_path': 'target.o'}
            with patch.object(targets, 'OUTPUT', root), patch.object(targets.subprocess, 'run') as run:
                config = targets.prepare_candidates([unit])
            run.assert_not_called()
            self.assertNotIn('base_path', config[0])
            self.assertFalse((root / 'raw/base.o').exists())

    def test_ambiguous_source_aliases_fail(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for name in ('a.c', 'b.c'):
                (root / name).write_text('')
            with patch.object(targets, 'ROOT', root), self.assertRaisesRegex(ValueError, 'one active'):
                targets.candidate_source({'kind': 'private_section', 'key': 'test', 'sources': ['a.c', 'b.c']})


if __name__ == '__main__':
    unittest.main()
