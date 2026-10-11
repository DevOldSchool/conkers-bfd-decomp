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


class RelocationAddendTests(unittest.TestCase):
    def object(self, relocations, words):
        from types import SimpleNamespace
        return SimpleNamespace(sections=[[0] * 5 + [32], [0] * 5 + [16]],
                               relocations=relocations, word=lambda section, offset: words[offset])

    def test_absolute_addend_cannot_escape_private_section(self):
        for addend, expected in [(0, True), (12, True), (16, False), (0xFFFFFFFC, False)]:
            with self.subTest(addend=addend):
                obj = self.object({(0, 0): (2, ('.data', 0, 0, 1))}, {0: addend})
                self.assertEqual(linked.relocation_addends_fit(obj, {1}), expected)

    def test_negative_offset_can_stay_within_its_private_section(self):
        obj = self.object({(0, 0): (2, ('data', 8, 4, 1))}, {0: 0xFFFFFFFC})
        self.assertTrue(linked.relocation_addends_fit(obj, {1}))

    def test_instruction_hi_lo_addends_are_checked(self):
        target = ('.data', 0, 0, 1)
        relocations = {(0, 0): (5, target), (0, 4): (6, target)}
        for low, expected in [(0, True), (12, True), (16, False), (0xFFFC, False)]:
            with self.subTest(low=low):
                obj = self.object(relocations, {0: 0x3C080000, 4: 0x25080000 | low})
                self.assertEqual(linked.relocation_addends_fit(obj, {1}), expected)

    def test_external_and_call_addends_do_not_change_named_destination(self):
        for kind, original, changed in [(2, 0, 4), (4, 0x0C000000, 0x0C000001)]:
            for word, expected in [(original, True), (changed, False)]:
                obj = self.object({(0, 0): (kind, ('func_16000000', 0, 0, 0))}, {0: word})
                self.assertEqual(linked.relocation_addends_fit(obj, set()), expected)


class CandidateMismatchTests(unittest.TestCase):
    def test_candidate_failure_falls_back_but_metadata_error_is_not_hidden(self):
        import linked_aliases
        for error in [linked.CandidateMismatch('wrong candidate layout'), ValueError('bad metadata')]:
            with self.subTest(error=type(error).__name__), \
                 patch.object(Path, 'read_bytes', return_value=b'elf'), \
                 patch.object(linked_aliases, 'Object32'), \
                 patch.object(linked_aliases, 'address_alias_present', return_value=True), \
                 patch.object(linked_aliases, 'si_definitions', return_value={}), \
                 patch.object(linked, 'context', side_effect=error), \
                 patch.object(linked_aliases.rom_span, 'code_image') as image:
                args = (ROOT, Path('candidate'), Path('reference'), Path('asm'), 'func_16000000', 0x16000000, 8)
                if isinstance(error, linked.CandidateMismatch):
                    self.assertIsNone(linked_aliases.prepare(*args, overlay='debugger'))
                else:
                    with self.assertRaisesRegex(ValueError, 'bad metadata'):
                        linked_aliases.prepare(*args, overlay='debugger')
                image.assert_not_called()

    def test_missing_or_wrong_candidate_section_is_a_mismatch(self):
        import json, tempfile
        from types import SimpleNamespace
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'config/profiles').mkdir(parents=True)
            (root / 'config/profiles/us.yaml').write_text('{}')
            (root / 'progress').mkdir()
            entry = {'symbol': 'f', 'overlay': 'debugger', 'source': 'src/f.c',
                     'regions': {'us': {'symbol': 'f', 'vram': '0x10'}}}
            unit = {'source': 'src/f.c', 'functions': ['f'], 'boundary_evidence': {'us': {'reviewed': True}},
                    'regions': {'us': {'start': '0x10', 'end': '0x18'}}}
            (root / 'progress/functions.json').write_text(json.dumps({'functions': [entry]}))
            (root / 'progress/source_units.json').write_text(json.dumps({'source_units': [unit]}))
            text = [0, 1, 6, 0, 0, 8, 0, 0, 4, 0]
            data = [0, 1, 2, 0, 8, 4, 0, 0, 4, 0]
            obj = SimpleNamespace(data=b'elf', sections=[text, data], relocations={})
            mappings = [{'source': 'src/f.c', 'input': '.data', 'start': 32, 'end': 40}]
            with patch.object(linked.data_boundaries, 'debugger_source_mappings', return_value=mappings), \
                 patch.object(linked.debugger_layout, 'load', return_value={'origin': 0}), \
                 patch.object(linked.layout_check, 'archived_object_layout', return_value=({}, 8, 4)), \
                 patch.object(linked.layout_check, 'validate_layout'):
                for parsed in [{'.text': (text, b'0' * 8)}, {'.text': (text, b'0' * 8), '.data': (data, b'0' * 4)}]:
                    with self.subTest(parsed=list(parsed)), patch.object(linked, 'sections', return_value=parsed):
                        with self.assertRaises(linked.CandidateMismatch):
                            linked.context(root, obj, 'f', 16)
