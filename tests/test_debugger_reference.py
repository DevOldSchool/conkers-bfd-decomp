from __future__ import annotations

import copy
import hashlib
import io
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from contextlib import ExitStack, redirect_stdout, redirect_stderr
from unittest.mock import patch

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import candidate_tables
import diff
import linked_aliases
import m2c
import original_asm
import project_state
import rom_span


BASE = 0x16000000
DATA_BASE = 0x160036F0
ROM_START = 0x19EA88
ROM_SPLIT = 0x1A2178
ROM_END = 0x1A33E8


def raw_text(words, base=BASE, *, table=None):
    return 'glabel func_test\n' + ''.join(
        f'/* {ROM_START + index * 4:X} {base + index * 4:08X} {word:08X} */ '
        + (f'lw $t7, %lo({table})($at)' if table and index == 5 else 'nop')
        + '\n' for index, word in enumerate(words))


def table_fixture(*, wrong_case=False, missing_relocation=False):
    words = [0x2DE10002, 0x10200009, 0x000F7880, 0x3C011600,
             0x002F0821, 0x8C2F36F0, 0x01E00008, 0,
             0x24020001, 0x03E00008, 0, 0x03E00008, 0]
    code = struct.pack('>13I', *words)
    data = struct.pack('>2I', BASE + 32, BASE + 44)
    raw = raw_text(words, table='jtbl_160036F0')
    current = words.copy()
    current[3], current[5] = 0x3C010000, 0x8C2F0000
    text = struct.pack('>13I', *current)
    rodata = struct.pack('>2I', 32, 32 if wrong_case else 44)
    symbol = lambda name, value, size, info, section: struct.pack('>IIIBBH', name, value, size, info, 0, section)
    symbols = (bytes(16) + symbol(1, 0, len(code), 0x12, 1)
               + symbol(0, 0, 0, 3, 1) + symbol(0, 0, 0, 3, 2))
    reltext = struct.pack('>4I', 12, 3 << 8 | 5, 20, 3 << 8 | 6)
    reltable = struct.pack('>2I', 0, 2 << 8 | 2)
    if not missing_relocation:
        reltable += struct.pack('>2I', 4, 2 << 8 | 2)
    sections = [(0, b'', 0, 0, 0), (1, text, 0, 0, 0), (1, rodata, 0, 0, 0),
                (2, symbols, 4, 0, 16), (3, b'\0func_test\0', 0, 0, 0),
                (9, reltext, 3, 1, 8), (9, reltable, 3, 2, 8)]
    body = bytearray(52)
    headers = []
    for kind, payload, link, info, entsize in sections:
        headers.append(struct.pack('>10I', 0, kind, 0, 0, len(body), len(payload), link, info, 4, entsize))
        body.extend(payload)
    offset = len(body)
    body.extend(b''.join(headers))
    body[:52] = struct.pack('>16sHHIIIIIHHHHHH', b'\x7fELF\x01\x02\x01' + bytes(9),
                           1, 8, 1, 0, 0, offset, 0, 52, 0, 0, 40, len(sections), 0)
    return raw, code, data, bytes(body)


class DebuggerReferenceTests(unittest.TestCase):
    def image_fixture(self, root):
        (root / 'config/reference').mkdir(parents=True)
        (root / 'roms').mkdir()
        payload = bytearray(ROM_END + 8)
        payload[:4] = bytes.fromhex('80371240')
        payload[ROM_START:ROM_SPLIT] = b'\x11' * (ROM_SPLIT - ROM_START)
        payload[ROM_SPLIT:ROM_END] = b'\x22' * (ROM_END - ROM_SPLIT)
        payload[ROM_END:] = b'\x33' * 8
        (root / 'roms/baserom.us.z64').write_bytes(payload)
        (root / 'config/roms.json').write_text(json.dumps({'profiles': {'us': {
            'sha1': hashlib.sha1(payload).hexdigest(), 'size_bytes': len(payload)}}}))
        profile = {'segments': [{'name': 'debugger', 'type': 'code',
                    'start': ROM_START, 'vram': BASE, 'align': 8,
                    'subsegments': [[ROM_START, 'asm', 'debugger/debugger'],
                                    [ROM_SPLIT, 'data', 'debugger/data']]},
                   {'start': ROM_END, 'type': 'bin'}]}
        (root / 'config/reference/us.yaml').write_text(yaml.safe_dump(profile))
        return profile

    def test_image_checks_checksum_size_bounds_and_keeps_data_separate(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            profile = self.image_fixture(root)
            code, data, base, data_base, digest = rom_span.debugger_image(root)
            self.assertEqual((BASE, DATA_BASE), (base, data_base))
            self.assertEqual(b'\x11' * (ROM_SPLIT - ROM_START), code)
            self.assertEqual(b'\x22' * (ROM_END - ROM_SPLIT), data)
            self.assertEqual((code, base, digest), rom_span.code_image(root, 'debugger'))
            with self.assertRaisesRegex(ValueError, 'US ROM'):
                rom_span.raw_span(raw_text([0x22222222], DATA_BASE), DATA_BASE, 4, code, base)
            for mutate in (lambda p: p['segments'][0].update(align=16),
                           lambda p: p['segments'][0].update(vram=0x86000000),
                           lambda p: p['segments'][0]['subsegments'][1].__setitem__(0, ROM_SPLIT + 4),
                           lambda p: p['segments'][1].update(start=ROM_END + 8),
                           lambda p: p['segments'].append(copy.deepcopy(p['segments'][0]))):
                changed = copy.deepcopy(profile)
                mutate(changed)
                (root / 'config/reference/us.yaml').write_text(yaml.safe_dump(changed))
                with self.assertRaisesRegex(ValueError, 'debugger reference'):
                    rom_span.debugger_image(root)
            (root / 'config/reference/us.yaml').write_text(yaml.safe_dump(profile))
            metadata = json.loads((root / 'config/roms.json').read_text())
            for field, value in [('sha1', 'a' * 40), ('size_bytes', ROM_END)]:
                changed = copy.deepcopy(metadata)
                changed['profiles']['us'][field] = value
                (root / 'config/roms.json').write_text(json.dumps(changed))
                with self.assertRaisesRegex(ValueError, 'checksum-validated'):
                    rom_span.debugger_image(root)

    def test_m2c_prefers_independent_normal_reference_then_canonical_fallback(self):
        for source in ('src/debugger/nested/test.c', 'src/done/debugger/nested/test.c'):
            with self.subTest(source=source), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                (root / 'progress').mkdir()
                (root / 'progress/functions.json').write_text(json.dumps({'functions': [{
                    'symbol': 'func_test', 'overlay': 'debugger', 'source': source,
                    'regions': {'us': {'symbol': 'func_test'}}}]}))
                canonical = root / project_state.nonmatching_asm_path(source, 'func_test')
                canonical.parent.mkdir(parents=True)
                canonical.write_text(raw_text([0x03E00008, 0]))
                independent = root / 'reference/us/asm/text/debugger/debugger.s'
                independent.parent.mkdir(parents=True)
                independent.write_text(raw_text([0x03E00008, 0]))
                with patch.object(m2c, 'ROOT', root), patch.object(m2c, 'prepare_reference') as prepare:
                    self.assertEqual((independent, 'func_test'), m2c.locate_registered_function('us', 'func_test'))
                    independent.unlink()
                    self.assertEqual((canonical, 'func_test'), m2c.locate_registered_function('us', 'func_test'))
                    prepare.assert_not_called()
                    canonical.write_text(canonical.read_text() + 'glabel other\n')
                    self.assertIsNone(m2c.nonmatching_function_source(root / source, 'func_test', 'func_test'))

    def test_debugger_tables_recover_from_debugger_rom_and_fail_closed(self):
        raw, code, data, _ = table_fixture()
        with patch.object(rom_span, 'debugger_image', return_value=(code, data, BASE, DATA_BASE, 'rom')):
            recovered = m2c.prepare_game_jump_tables(raw, 'us')
            self.assertIn('glabel jtbl_160036F0\n', recovered)
            self.assertIn('.word .L16000020\n', recovered)
            self.assertIn('.word .L1600002C\n', recovered)
            with self.assertRaisesRegex(ValueError, 'only the US'):
                m2c.prepare_game_jump_tables(raw, 'eu')
        for bad_code, bad_data in [(code[:-4], data), (code, data[:4]),
                                   (code, struct.pack('>2I', BASE + 0x100, BASE + 44))]:
            with patch.object(rom_span, 'debugger_image', return_value=(bad_code, bad_data, BASE, DATA_BASE, 'rom')):
                with self.assertRaises(ValueError):
                    m2c.prepare_game_jump_tables(raw, 'us')

    def test_candidate_table_gate_checks_real_relocations_and_case_targets(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            raw, code, data, payload = table_fixture()
            assembly, candidate = root / 'raw.s', root / 'candidate.o'
            assembly.write_text(raw)
            candidate.write_bytes(payload)
            with patch.object(rom_span, 'debugger_image', return_value=(code, data, BASE, DATA_BASE, 'rom')):
                candidate_tables.verify_candidate(candidate, 'func_test', assembly, len(code), overlay='debugger')
                for options in ({'wrong_case': True}, {'missing_relocation': True}):
                    candidate.write_bytes(table_fixture(**options)[3])
                    with self.assertRaises(candidate_tables.TableEvidenceError):
                        candidate_tables.verify_candidate(candidate, 'func_test', assembly, len(code), overlay='debugger')

    def test_no_table_still_requires_full_rom_span_including_tail(self):
        with tempfile.TemporaryDirectory() as temporary:
            assembly = Path(temporary) / 'raw.s'
            assembly.write_text(raw_text([0x03E00008, 0, 0]))
            code = bytes.fromhex('03E000080000000000000000')
            with patch.object(rom_span, 'debugger_image', return_value=(code, b'', BASE, DATA_BASE, 'rom')):
                candidate_tables.verify_candidate(Path('unused.o'), 'func_test', assembly, 12, overlay='debugger')
                with self.assertRaisesRegex(ValueError, 'not contiguous'):
                    candidate_tables.verify_candidate(Path('unused.o'), 'func_test', assembly, 12,
                                                      overlay='debugger', expected_start=BASE + 4)
                for size in (8, 16):
                    with self.assertRaisesRegex(ValueError, 'full registered span'):
                        candidate_tables.verify_candidate(Path('unused.o'), 'func_test', assembly, size, overlay='debugger')
                assembly.write_text(raw_text([0x03E00008, 0, 1]))
                with self.assertRaisesRegex(ValueError, 'US ROM'):
                    candidate_tables.verify_candidate(Path('unused.o'), 'func_test', assembly, 12, overlay='debugger')

    def test_diff_routes_debugger_and_runs_rom_gate_before_accepting_zero(self):
        with tempfile.TemporaryDirectory() as temporary, ExitStack() as stack:
            root = Path(temporary)
            source = root / 'src/debugger/test.c'
            source.parent.mkdir(parents=True)
            source.write_text('void func_test(void) {}\n')
            (root / 'progress').mkdir()
            (root / 'progress/functions.json').write_text(json.dumps({'functions': [{
                'symbol': 'func_test', 'overlay': 'debugger', 'source': 'src/debugger/test.c',
                'regions': {'us': {'symbol': 'func_test', 'vram': hex(BASE), 'size_bytes': 8}}}]}))
            reference = root / 'reference.o'
            reference.write_bytes(b'reference')
            stack.enter_context(patch.object(diff, 'ROOT', root))
            stack.enter_context(patch.object(sys, 'argv', ['diff.py', 'us', 'func_test', '--auto-overlay', '--require-match']))
            ensure = stack.enter_context(patch.object(diff, 'ensure_reference_function', return_value=Path('raw.s')))
            stack.enter_context(patch.object(diff, 'compile_candidate', return_value=Path('candidate.o')))
            stack.enter_context(patch.object(diff, 'reference_object', return_value=reference))
            stack.enter_context(patch.object(diff, 'write_settings', return_value=root))
            alias = stack.enter_context(patch.object(linked_aliases, 'prepare', return_value=None))
            table = stack.enter_context(patch.object(candidate_tables, 'verify_candidate'))
            def authoritative(*args, **kwargs):
                self.assertEqual(8, args[4])
                kwargs['table_check']()
                return 0
            stack.enter_context(patch.object(diff, 'run_required_asm_diff', side_effect=authoritative))
            self.assertEqual(0, diff.main())
            ensure.assert_called_once_with('us', 'func_test', game_reference=False)
            table.assert_called_once_with(Path('candidate.o'), 'func_test', Path('raw.s'), 8,
                                          overlay='debugger', expected_start=BASE)
            self.assertEqual('debugger', alias.call_args.kwargs['overlay'])

    def test_original_assembly_supports_debugger_without_c_match_credit(self):
        evidence = {'rom_sha1': 'a' * 40, 'span_sha256': 'b' * 64,
                    'assembly_sha256': 'c' * 64, 'verified_revision': 'working-tree'}
        entry = {'overlay': 'debugger', 'original_asm': {'reason': 'privileged ABI',
                 'reference': 'evidence.md', 'recorded_revision': 'working-tree'},
                 'regions': {'us': {'state': 'original_asm', 'evidence': evidence}}}
        original_asm.validate_metadata(entry)
        with patch.object(rom_span, 'debugger_code', return_value=(b'code', BASE, 'rom')) as reader:
            self.assertEqual((b'code', BASE, 'rom'), original_asm.reference_image(Path('.'), entry))
            reader.assert_called_once_with(Path('.'))
        entry['regions']['us']['evidence']['current_differences'] = 0
        with self.assertRaisesRegex(ValueError, 'must not claim C CURRENT'):
            original_asm.validate_metadata(entry)

    def test_registered_debugger_extracts_exact_span_before_unregistered_labels(self):
        with tempfile.TemporaryDirectory() as temporary, ExitStack() as stack:
            root = Path(temporary)
            source = root / 'src/debugger/test.c'
            source.parent.mkdir(parents=True)
            source.write_text('#include "types.h"\n')
            (root / 'progress').mkdir()
            inventory = {'functions': [{'symbol': 'func_test', 'overlay': 'debugger',
                'source': 'src/debugger/test.c', 'regions': {'us': {
                    'symbol': 'func_test', 'vram': hex(BASE), 'size_bytes': 12}}}]}
            (root / 'progress/functions.json').write_text(json.dumps(inventory))
            reference = root / 'reference/us/asm/debugger/debugger.s'
            reference.parent.mkdir(parents=True)
            target = raw_text([0x03E00008, 0, 0])
            following = raw_text([0x24020001, 0x03E00008, 0], BASE + 12).replace(
                'glabel func_test', 'glabel func_unregistered')
            reference.write_text('.set noreorder\n' + target + following)
            stack.enter_context(patch.object(m2c, 'ROOT', root))
            stack.enter_context(patch.object(diff, 'ROOT', root))
            prepare = stack.enter_context(patch.object(diff, 'prepare_reference'))
            extracted = diff.ensure_reference_function('us', 'func_test')
            self.assertEqual('.set noreorder\n' + target, extracted.read_text())
            prepare.assert_not_called()
            # The public m2c auto-overlay path must use the same endpoint and
            # retain padding after jr/its delay slot rather than ending early.
            stack.enter_context(patch.object(sys, 'argv', ['m2c.py', 'us', 'func_test', '--auto-overlay']))
            stack.enter_context(patch.object(m2c, 'mips_to_c_command', return_value=['m2c']))
            generate = stack.enter_context(patch.object(m2c, 'generate_with_call_context',
                                                       return_value=('void func_test(void) {}\n', 0)))
            with redirect_stdout(io.StringIO()):
                self.assertEqual(0, m2c.main())
            self.assertEqual('.set noreorder\n' + target, generate.call_args.args[1])
            self.assertNotIn('func_unregistered', generate.call_args.args[1])
            for body in (raw_text([0x03E00008, 0]),
                         target.replace('16000004', '16000008')):
                reference.write_text(body)
                with self.assertRaisesRegex(ValueError, 'truncated|contiguous'):
                    diff.ensure_reference_function('us', 'func_test')
                with redirect_stderr(io.StringIO()):
                    self.assertEqual(1, m2c.main())
            for size in (0, 10, True, 0x36F4):
                inventory['functions'][0]['regions']['us']['size_bytes'] = size
                (root / 'progress/functions.json').write_text(json.dumps(inventory))
                with self.assertRaisesRegex(ValueError, 'invalid registered debugger byte span'):
                    diff.ensure_reference_function('us', 'func_test')

    def test_explicit_span_retains_interior_secondary_entry_and_rejects_address_gaps(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / 'raw.s'
            source.write_text('glabel func_test\n/* 0 16000000 03E00008 */ jr $ra\n'
                              'glabel secondary_entry\n/* 4 16000004 00000000 */ nop\n'
                              'glabel following_function\n/* 8 16000008 00000000 */ nop\n')
            with patch.object(m2c, 'ROOT', root):
                extracted = m2c.extract_function(source, 'func_test',
                    boundary_symbols={'func_test'}, byte_span=(BASE, 8)).read_text()
                self.assertIn('glabel secondary_entry', extracted)
                self.assertNotIn('following_function', extracted)
                for span in ((BASE, 16), (BASE + 4, 8), (BASE, 6)):
                    with self.assertRaisesRegex(ValueError, 'truncated|contiguous|invalid'):
                        m2c.extract_function(source, 'func_test', byte_span=span)


if __name__ == '__main__':
    unittest.main()
