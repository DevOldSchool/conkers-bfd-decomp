from pathlib import Path
import sys
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import linked_debugger_data as linked


class DebuggerDataAliasTests(unittest.TestCase):
    def test_full_code_and_each_data_section_must_match(self):
        code, data = bytes(range(32)), bytes(range(32, 64))
        context = {'text_start': 0x16000008, 'text_end': 0x16000020, 'mappings': [
            {'start': 0x16000020, 'end': 0x16000030, 'input': '.data'},
            {'start': 0x16000030, 'end': 0x16000040, 'input': '.rodata'}]}
        expected = {'.text': ([], code[8:]), '.data': ([], data[:16]), '.rodata': ([], data[16:])}
        with patch.object(Path, 'read_bytes', return_value=b'elf'), \
             patch.object(linked.rom_span, 'debugger_image', return_value=(code, data, 0x16000000, 0x16000020, 'hash')):
            with patch.object(linked, 'sections', return_value=expected):
                self.assertTrue(linked.verify(ROOT, Path('candidate.elf'), context))
            for section in expected:
                changed = dict(expected)
                payload = expected[section][1]
                changed[section] = ([], payload[:-1] + bytes([payload[-1] ^ 1]))
                with self.subTest(section=section), patch.object(linked, 'sections', return_value=changed):
                    self.assertFalse(linked.verify(ROOT, Path('candidate.elf'), context))
            # A candidate matching only the requested function cannot substitute
            # for the required full unit in an address-alias proof.
            changed = {**expected, '.text': ([], code[8:16])}
            with patch.object(linked, 'sections', return_value=changed):
                self.assertFalse(linked.verify(ROOT, Path('candidate.elf'), context))
