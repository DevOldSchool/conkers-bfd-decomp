"""Verify that the ROM-free objdiff reproducer describes equivalent link inputs."""
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
from candidate_tables import Object32
from elf_sections import sections


@unittest.skipUnless(shutil.which('mips-linux-gnu-as') and shutil.which('mips-linux-gnu-ld'),
                     'requires pinned MIPS binutils')
class RelAddendReproducerTests(unittest.TestCase):
    def test_different_rel_words_have_identical_destinations_and_linked_bytes(self):
        with tempfile.TemporaryDirectory() as tmp:
            directory = Path(tmp)
            script = directory / 'link.ld'
            script.write_text('SECTIONS { .text 0x80000000 : { *(.text) } '
                              '.rodata 0x80001000 : { *(.rodata) } }\n')
            objects, linked, destinations = {}, {}, {}
            for name in ('named', 'section'):
                obj = directory / (name + '.o')
                subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32',
                    '-no-pad-sections', '-o', str(obj),
                    str(ROOT / 'tests/fixtures/objdiff_rel_addends' / (name + '.s'))], check=True)
                objects[name] = sections(obj.read_bytes(), 1)
                parsed = Object32(obj.read_bytes())
                rodata = parsed.sections.index(objects[name]['.rodata'][0])
                kind, (_, value, _, target) = parsed.relocations[(rodata, 0)]
                self.assertEqual(kind, 2)
                self.assertEqual(parsed.sections[target], objects[name]['.text'][0])
                destinations[name] = value + parsed.word(rodata, 0)
                elf = directory / (name + '.elf')
                subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script),
                                '-o', str(elf), str(obj)], check=True)
                linked[name] = sections(elf.read_bytes(), 2)
            self.assertEqual(destinations, {'named': 4, 'section': 4})
            self.assertEqual(objects['named']['.rodata'][1], bytes.fromhex('00000000'))
            self.assertEqual(objects['section']['.rodata'][1], bytes.fromhex('00000004'))
            for section in ('.text', '.rodata'):
                self.assertEqual(linked['named'][section][1], linked['section'][section][1])
            self.assertEqual(linked['named']['.rodata'][1], bytes.fromhex('80000004'))


if __name__ == '__main__':
    unittest.main()
