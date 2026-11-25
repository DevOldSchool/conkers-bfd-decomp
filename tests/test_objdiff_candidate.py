"""ROM-free checks for candidate-only IDO comparison copies."""
import builtins
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
from elf_sections import sections

FIXTURE = ROOT / 'tests/fixtures/objdiff_candidate/switch.s'
BASES = {'.text': 0x80000000, '.rodata': 0x80001000}


@unittest.skipUnless(shutil.which('mips-linux-gnu-as'), 'requires pinned MIPS binutils')
class ScheduledFloatTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        path = Path(self.tmp.name) / 'base.o'
        subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32',
                        '-no-pad-sections', '-o', str(path),
                        str(FIXTURE.with_name('scheduled_float.s'))], check=True)
        self.raw = path.read_bytes()
        self.obj = c.Elf(self.raw)
        self.text = self.obj.names.index('.text')

    def test_scheduled_loads_derive_widths_without_changing_storage(self):
        result, proof = c.annotate(self.raw, BASES)
        self.assertEqual([(s['offset'], s['size']) for s in proof['symbols']], [(0, 4), (8, 8)])
        self.assertTrue(proof['invariance_verified'])
        self.assertEqual(c.annotate(result, BASES)[0], result)

    def test_base_writes_control_transfers_and_unknown_operations_fail_closed(self):
        # Intervening LW, ADDIU, MFC1, ADDU and LUI all overwrite $at.
        # Calls, branches, indirect jumps and unsupported COP0 cannot prove it live.
        for word in (0x8FA10000, 0x24210001, 0x44012000, 0x01090821, 0x3C010000,
                     0x0C000000, 0x10000001, 0x45000001, 0x03E00008, 0x40016000):
            data = bytearray(self.raw)
            struct.pack_into('>I', data, self.obj.headers[self.text][4] + 4, word)
            with self.subTest(word=hex(word)), self.assertRaises(c.AnnotationError):
                c.annotate(bytes(data), BASES)


@unittest.skipUnless(shutil.which('mips-linux-gnu-as'), 'requires pinned MIPS binutils')
class InitializerCopyTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.path = Path(self.tmp.name) / 'base.o'
        subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32', '-no-pad-sections',
                        '-o', str(self.path), str(FIXTURE.with_name('initializer.s'))], check=True)
        self.raw = self.path.read_bytes()
        self.obj = c.Elf(self.raw)
        self.text = self.obj.names.index('.text')

    def changed_word(self, offset, word):
        data = bytearray(self.raw)
        struct.pack_into('>I', data, self.obj.headers[self.text][4] + offset, word)
        return bytes(data)

    def test_initializer_and_float_extents_come_from_instructions(self):
        with patch.object(builtins, 'open', side_effect=AssertionError('file access')), \
                patch.object(subprocess, 'run', side_effect=AssertionError('subprocess access')):
            result, proof = c.annotate(self.raw, BASES)
        self.assertEqual([(s['kind'], s['offset'], s['size']) for s in proof['symbols']],
                         [('initializer', 4, 28), ('float', 32, 4)])
        self.assertTrue(proof['invariance_verified'])
        self.assertEqual(c.annotate(result, BASES)[0], result)
        self.assertEqual(c.canonicalize(result, BASES)[0], result)
        after = c.Elf(result)
        self.assertEqual(after.relocations, self.obj.relocations)
        for section in ('.text', '.rodata'):
            self.assertEqual(after.payload(after.names.index(section)),
                             self.obj.payload(self.obj.names.index(section)))

    def test_every_copy_instruction_is_required(self):
        for offset in range(4, 52, 4):
            with self.subTest(offset=offset), self.assertRaises(c.AnnotationError):
                c.annotate(self.changed_word(offset, self.obj.word(self.text, offset) ^ (1 << 26)), BASES)

    def test_bounds_register_alias_branch_and_tail_are_checked(self):
        for label, offset, word in (
                ('zero bound', 8, self.obj.word(self.text, 8) & ~0xffff),
                ('unaligned bound', 8, self.obj.word(self.text, 8) + 1),
                ('negative bound', 8, self.obj.word(self.text, 8) | 0x8000),
                ('past section', 8, self.obj.word(self.text, 8) + 12),
                ('stack alignment', 12, self.obj.word(self.text, 12) + 1),
                ('end aliases source', 8, self.obj.word(self.text, 8) ^ (1 << 16)),
                ('branch destination', 44, self.obj.word(self.text, 44) ^ 1),
                ('tail destination', 56, self.obj.word(self.text, 56) ^ 4),
                ('float base', 64, self.obj.word(self.text, 64) ^ (1 << 21))):
            with self.subTest(label=label), self.assertRaises(c.AnnotationError):
                c.annotate(self.changed_word(offset, word), BASES)

    def test_missing_tail_does_not_borrow_reference_extent(self):
        raw = self.changed_word(52, 0)
        symbols = c.discover(raw, BASES)
        self.assertEqual(symbols[0].size, 24)

    def test_relocation_inside_copy_is_rejected(self):
        data = bytearray(self.raw)
        rel = self.obj.headers[self.obj.names.index('.rel.text')]
        # Move the float HI16 into the loop. The candidate cannot prove its bounds.
        struct.pack_into('>I', data, rel[4] + 16, 20)
        with self.assertRaises(c.AnnotationError):
            c.annotate(bytes(data), BASES)

    def test_decoder_report_hook_requires_actual_archive_and_whole_rom_proof(self):
        import objdiff_report as report
        root = Path(self.tmp.name)
        output = root / 'report'
        output.mkdir()
        (output / 'base.o').write_bytes(self.raw)
        archive = root / 'build/game-libs/us/libultrare.a'
        archive.parent.mkdir(parents=True)
        archive.write_bytes(b'test archive')
        payload = self.obj.payload(self.obj.names.index('.rodata'))
        span = {'section': '.rodata', 'kind': 'external_payload', 'linker_mode': 'NOLOAD',
                'owner': {'archive': 'libultrare', 'member': 'decoder.o'},
                'evidence_reference': 'config/game/us-sdk.ld', 'candidate_data_relocations': 0,
                'literal_payload_matches_rom': True, 'size': len(payload),
                'sha256': hashlib.sha256(payload).hexdigest(), 'start': BASES['.rodata']}
        unit = {'key': 'game/decoder', 'kind': 'sdk', 'overlay': 'game', 'archive': 'libultrare',
                'member': 'decoder.o', 'base_path': 'base.o', 'data_ranges': [span], 'complete': False}
        config = {'base_path': 'base.o', 'metadata': {'complete': False}}
        with patch.object(report, 'ROOT', root), patch.object(report, 'OUTPUT', output), \
                patch.object(report.subprocess, 'check_output', return_value=self.raw):
            for field, value in (('linker_mode', 'LOAD'), ('literal_payload_matches_rom', False),
                                 ('candidate_data_relocations', 1), ('size', len(payload) - 1),
                                 ('sha256', '0' * 64)):
                wrong = copy.deepcopy(unit)
                wrong['data_ranges'][0][field] = value
                with self.subTest(field=field), self.assertRaises(ValueError):
                    report.annotate_sdk_literal_candidates([wrong], [config.copy()])
            (output / 'base.o').write_bytes(b'stale')
            with self.assertRaisesRegex(ValueError, 'actual archive'):
                report.annotate_sdk_literal_candidates([unit], [config])
            (output / 'base.o').write_bytes(self.raw)
            report.annotate_sdk_literal_candidates([unit], [config])
        self.assertFalse(unit['complete'])
        self.assertFalse(config['metadata']['complete'])
        self.assertEqual(config['base_path'], unit['base_path'])
        self.assertTrue(unit['comparison_copy']['invariance_verified'])
        self.assertEqual((output / 'base.o').read_bytes(), self.raw)
        self.assertEqual(unit['linked_inputs']['build/game-libs/us/libultrare.a'],
                         hashlib.sha256(archive.read_bytes()).hexdigest())


@unittest.skipUnless(shutil.which('mips-linux-gnu-as') and shutil.which('mips-linux-gnu-ld'),
                     'requires pinned MIPS binutils')
class ComparisonCopyTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.directory = Path(self.tmp.name)
        self.raw_path = self.directory / 'raw.o'
        subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32', '-no-pad-sections',
                        '-o', str(self.raw_path), str(FIXTURE)], check=True)
        self.raw = self.raw_path.read_bytes()
        script = self.directory / 'runtime.ld'
        script.write_text('SECTIONS { .text 0x80000000 : { *(.text) } '
                          '.rodata 0x80001000 : { *(.rodata) } '
                          '/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.gnu.attributes) } }\n')
        runtime = self.directory / 'runtime.elf'
        subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script),
                        '-o', str(runtime), str(self.raw_path)], check=True)
        self.runtime = runtime.read_bytes()

    def tearDown(self):
        self.tmp.cleanup()

    def canonical(self):
        return c.canonicalize(self.raw, c.linked_section_bases(self.raw, self.runtime))

    def test_runtime_anchors_supply_section_bases(self):
        self.assertEqual(c.linked_section_bases(self.raw, self.runtime), BASES)

    def test_copy_names_anonymous_data_and_moves_table_addends_into_labels(self):
        with patch.object(builtins, 'open', side_effect=AssertionError('file access')), \
             patch.object(subprocess, 'run', side_effect=AssertionError('subprocess access')):
            canonical, proof = c.canonicalize(self.raw, BASES)
        self.assertEqual([(s['name'], s['offset'], s['size']) for s in proof['symbols']],
                         [('jtbl_80001004', 4, 16), ('D_80001018', 0x18, 8)])
        self.assertEqual(proof['destination_labels'],
                         ['.L80000020', '.L80000028', '.L80000030', '.L80000038'])
        self.assertEqual(proof['semantic_verification']['canonical_table_words'], 4)
        before, after = sections(self.raw, 1), sections(canonical, 1)
        self.assertEqual(before['.rodata'][1][4:20], bytes.fromhex('00000020000000280000003000000038'))
        self.assertEqual(after['.rodata'][1][4:20], bytes(16))
        for name in ('.text', '.rodata'):
            self.assertEqual(before[name][1][:4] if name == '.rodata' else before[name][1],
                             after[name][1][:4] if name == '.rodata' else after[name][1])
        self.assertEqual(before['.rodata'][1][20:], after['.rodata'][1][20:])
        self.assertEqual(c.canonicalize(canonical, BASES)[0], canonical)

    def test_raw_and_canonical_copies_link_to_runtime_bytes(self):
        canonical, _ = self.canonical()
        path = self.directory / 'canonical.o'
        path.write_bytes(canonical)
        proof = c.verify_linked_copies(self.raw_path, path, self.runtime, BASES, self.directory / 'proof')
        self.assertEqual(set(proof), {'.text', '.rodata'})
        self.assertTrue(all(p['raw_and_canonical_match_runtime'] for p in proof.values()))

    def test_object_without_anonymous_references_is_unchanged(self):
        obj = c.Elf(self.raw)
        rel = obj.names.index('.rel.text')
        header = obj.headers[rel]
        rodata = obj.names.index('.rodata')
        entries = [self.raw[at:at + 8] for at in range(header[4], header[4] + header[5], 8)
                   if obj.symbols[struct.unpack_from('>I', self.raw, at + 4)[0] >> 8][5] != rodata]
        self.assertEqual(len(entries) * 8, header[5] - 32)
        stripped = bytearray(self.raw)
        stripped[header[4]:header[4] + len(entries) * 8] = b''.join(entries)
        struct.pack_into('>I', stripped, obj.header[6] + 40 * rel + 20, len(entries) * 8)
        self.assertEqual(c.canonicalize(bytes(stripped), BASES)[0], bytes(stripped))

    def test_verifier_rejects_any_unapproved_change(self):
        canonical, _ = self.canonical()
        obj = c.Elf(canonical)
        text, rodata = obj.names.index('.text'), obj.names.index('.rodata')
        rel = obj.names.index('.rel.rodata')
        for label, offset, value in (
                ('code', obj.headers[text][4], obj.word(text, 0) ^ 1),
                ('literal', obj.headers[rodata][4] + 0x18, obj.word(rodata, 0x18) ^ 1),
                ('table addend', obj.headers[rodata][4] + 4, 4),
                ('relocation target', obj.headers[rel][4] + 4,
                 struct.unpack_from('>I', canonical, obj.headers[rel][4] + 12)[0]),
                ('section size', obj.header[6] + 40 * rodata + 20, obj.headers[rodata][5] - 8)):
            with self.subTest(label):
                modified = bytearray(canonical)
                struct.pack_into('>I', modified, offset, value)
                with self.assertRaises(c.AnnotationError):
                    c.verify_canonicalization(self.raw, bytes(modified), BASES)

    def test_inconsistent_dispatch_or_destination_is_rejected(self):
        obj = c.Elf(self.raw)
        text, rodata = obj.names.index('.text'), obj.names.index('.rodata')
        for label, offset, value in (
                ('bound', obj.headers[text][4], obj.word(text, 0) - 1),
                ('destination', obj.headers[rodata][4] + 4, 0xFFFFFFFC)):
            with self.subTest(label):
                modified = bytearray(self.raw)
                struct.pack_into('>I', modified, offset, value)
                with self.assertRaises(c.AnnotationError):
                    c.canonicalize(bytes(modified), BASES)


@unittest.skipUnless(shutil.which('mips-linux-gnu-as'), 'requires pinned MIPS binutils')
class PrintfStringTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(); self.addCleanup(self.tmp.cleanup)
        output = Path(self.tmp.name) / 'strings.o'
        subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32', '-no-pad-sections',
                        '-o', str(output), str(FIXTURE.parent / 'printf_strings.s')], check=True)
        self.raw = output.read_bytes(); self.obj = c.Elf(self.raw)
        self.text = self.obj.names.index('.text'); self.rodata = self.obj.names.index('.rodata')

    def changed_word(self, offset, word):
        raw = bytearray(self.raw)
        struct.pack_into('>I', raw, self.obj.headers[self.text][4] + offset, word)
        return bytes(raw)

    def test_direct_printf_calls_prove_exact_nul_extents_and_preserve_all_bytes(self):
        result, proof = c.annotate(self.raw, BASES)
        self.assertEqual([(s['offset'], s['size'], s['kind']) for s in proof['symbols']],
                         [(0, 10, 'string'), (12, 7, 'string')])
        self.assertTrue(proof['invariance_verified'])
        self.assertEqual(c.Elf(result).payload(self.rodata), self.obj.payload(self.rodata))
        self.assertEqual(c.annotate(result, BASES)[0], result)

    def test_clobbers_stores_control_transfers_and_nonzero_call_addends_fail_closed(self):
        for offset, word in [(0, 0x3c050000), (4, 0x24850000), (8, 0x92040000),
                             (8, 0xac800000), (8, 0x10000001), (8, 0x40084800),
                             (12, 0x01202025), (16, 0x0c000001), (20, 0x01202025),
                             (20, 0x03e00008)]:
            with self.subTest(offset=offset, word=word), self.assertRaises(c.AnnotationError):
                c.annotate(self.changed_word(offset, word), BASES)

    def test_named_call_contract_and_terminator_are_required(self):
        # Same-width symbol edit preserves ELF layout but removes the known ABI.
        with self.assertRaises(c.AnnotationError):
            c.annotate(self.raw.replace(b'osSyncPrintf', b'xxSyncPrintf'), BASES)
        raw = bytearray(self.raw); start = self.obj.headers[self.rodata][4]
        raw[start:start + self.obj.headers[self.rodata][5]] = b'A' * self.obj.headers[self.rodata][5]
        with self.assertRaisesRegex(c.AnnotationError, 'bounded ASCII'):
            c.annotate(bytes(raw), BASES)
        raw = bytearray(self.raw); raw[start + 1] = 0xff
        with self.assertRaisesRegex(c.AnnotationError, 'bounded ASCII'):
            c.annotate(bytes(raw), BASES)


if __name__ == '__main__':
    unittest.main()
