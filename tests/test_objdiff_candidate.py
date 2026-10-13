"""ROM-free checks for the candidate-only debugger comparison copy."""
import builtins
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


if __name__ == '__main__':
    unittest.main()
