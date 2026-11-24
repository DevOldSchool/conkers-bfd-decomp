from __future__ import annotations

from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import probe_report


def listing(body: str, name: str = 'func_15000000', address: int = 0) -> str:
    return f'\nDisassembly of section .text:\n\n{address:08x} <{name}>:\n{body}'


REFERENCE = listing(
    '   0:\taddiu\tsp,sp,-24\n'
    '   4:\tlui\tv0,0x0\n'
    '\t\t\t4: R_MIPS_HI16\tD_800BE9E4\n'
    '   8:\tlw\tv0,0(v0)\n'
    '\t\t\t8: R_MIPS_LO16\tD_800BE9E4\n'
    '   c:\tbeqz\ta0,1c <func_15000000+0x1c>\n'
    '  10:\tnop\n'
    '  14:\tjal\t0 <func_15000000>\n'
    '\t\t\t14: R_MIPS_26\tfunc_15001000\n'
    '  18:\tmove\ta0,v0\n'
    '  1c:\tjr\tra\n'
    '  20:\taddiu\tsp,sp,24\n'
)


class ListingTests(unittest.TestCase):
    def test_parses_instructions_and_attaches_relocations(self):
        instructions = probe_report.function_listings(REFERENCE)['func_15000000']
        self.assertEqual([item.offset for item in instructions], [0, 4, 8, 0xC, 0x10, 0x14, 0x18, 0x1C, 0x20])
        self.assertEqual(instructions[1].relocations, [('R_MIPS_HI16', 'D_800BE9E4')])
        self.assertEqual(instructions[5].relocations, [('R_MIPS_26', 'func_15001000')])

    def test_offsets_are_relative_to_the_function(self):
        moved = listing('  40:\tjr\tra\n  44:\tnop\n', address=0x40)
        instructions = probe_report.function_listings(moved)['func_15000000']
        self.assertEqual([item.offset for item in instructions], [0, 4])

    def test_render_uses_labels_and_symbols(self):
        lines = probe_report.render(probe_report.function_listings(REFERENCE)['func_15000000'])
        self.assertEqual(lines[1], 'lui\tv0,0x0 %hi(D_800BE9E4)')
        self.assertEqual(lines[3], 'beqz\ta0,.L1')
        self.assertEqual(lines[5], 'jal\t%call(func_15001000)')

    def test_render_is_position_independent(self):
        moved = REFERENCE.replace('00000000 <func_15000000>', '00000100 <func_15000000>')
        moved = moved.replace('   c:\tbeqz\ta0,1c <func_15000000+0x1c>', ' 10c:\tbeqz\ta0,11c <func_15000000+0x1c>')
        first = probe_report.render(probe_report.function_listings(REFERENCE)['func_15000000'])
        second = probe_report.render(probe_report.function_listings(moved)['func_15000000'])
        self.assertEqual(first, second)

    def test_stops_at_the_next_section(self):
        text = REFERENCE + '\nDisassembly of section .other:\n\n   0:\tnop\n'
        self.assertEqual(len(probe_report.function_listings(text)['func_15000000']), 9)


class DiffTests(unittest.TestCase):
    def setUp(self):
        self.reference = probe_report.function_listings(REFERENCE)['func_15000000']

    def candidate(self, old: str, new: str):
        self.assertIn(old, REFERENCE)
        return probe_report.function_listings(REFERENCE.replace(old, new))['func_15000000']

    def counts(self, candidate):
        return probe_report.classify(probe_report.render(self.reference), probe_report.render(candidate))

    def test_identical_listings_have_no_diff(self):
        self.assertEqual(probe_report.diff_lines(self.reference, self.reference), [])
        self.assertEqual(probe_report.summary(self.counts(self.reference)), 'instruction diff: identical')

    def test_register_swap_is_classified(self):
        candidate = self.candidate('move\ta0,v0', 'move\ta0,v1')
        counts = self.counts(candidate)
        self.assertEqual(counts['register-only'], 1)
        self.assertEqual(sum(counts.values()), 1)
        diff = probe_report.diff_lines(self.reference, candidate, context=1)
        self.assertIn('-   18:       move\ta0,v0', diff)
        self.assertIn('+   18:       move\ta0,v1', diff)
        self.assertTrue(diff[0].startswith('@@ reference +0x14'))

    def test_relocation_symbol_change_is_classified(self):
        candidate = self.candidate('8: R_MIPS_LO16\tD_800BE9E4', '8: R_MIPS_LO16\tD_800BE9E0')
        counts = self.counts(candidate)
        self.assertEqual(counts['relocation-only'], 1)
        self.assertEqual(sum(counts.values()), 1)

    def test_inserted_instruction_does_not_cascade(self):
        candidate = self.candidate(
            '  18:\tmove\ta0,v0\n  1c:\tjr\tra\n  20:\taddiu\tsp,sp,24\n',
            '  18:\tmove\ta0,v0\n  1c:\tnop\n  20:\tjr\tra\n  24:\taddiu\tsp,sp,24\n')
        counts = self.counts(candidate)
        # The branch target moved with the inserted nop, so only the insertion is reported.
        self.assertEqual(counts['inserted'], 1)
        self.assertEqual(counts['other'] + counts['register-only'] + counts['deleted'], 0)

    def test_labels_are_shown_at_branch_targets(self):
        candidate = self.candidate('move\ta0,v0', 'move\ta0,v1')
        diff = probe_report.diff_lines(self.reference, candidate, context=2)
        self.assertTrue(any('.L1:' in line and 'jr\tra' in line for line in diff))

    def test_summary_names_each_kind(self):
        text = probe_report.summary({'register-only': 2, 'relocation-only': 0, 'other': 1,
                                     'inserted': 0, 'deleted': 3})
        self.assertEqual(text, 'instruction diff: 6 lines differ (2 register-only, 1 other, 3 deleted)')


class RegisterMapTests(unittest.TestCase):
    def test_rotation_is_counted_per_pair(self):
        reference = ['sub.s\t$f8,$f4,$f18', 'add.s\t$f4,$f18,$f6', 'move\tv0,a0']
        candidate = ['sub.s\t$f8,$f4,$f0', 'add.s\t$f4,$f0,$f6', 'move\tv1,a0']
        mapping = probe_report.register_map(reference, candidate)
        self.assertEqual(mapping, [('f18', 'f0', 2), ('v0', 'v1', 1)])
        self.assertEqual(probe_report.register_summary(mapping),
                         'register map (reference->candidate): f18->f0 x2, v0->v1 x1')

    def test_other_differences_are_ignored(self):
        self.assertEqual(probe_report.register_map(['lw\tv0,4(a0)'], ['lh\tv1,4(a0)']), [])
        self.assertEqual(probe_report.register_summary([]), '')

    def test_long_maps_are_truncated(self):
        mapping = [(f't{index}', f's{index}', 1) for index in range(10)]
        self.assertTrue(probe_report.register_summary(mapping).endswith(', +2 more'))


class TrimPaddingTests(unittest.TestCase):
    def listing(self, body):
        return probe_report.function_listings(listing(body))['func_15000000']

    def test_alignment_nops_are_dropped_but_the_delay_slot_stays(self):
        instructions = self.listing('   0:\tjr\tra\n   4:\tnop\n   8:\tnop\n   c:\tnop\n')
        self.assertEqual([item.offset for item in probe_report.trim_padding(instructions)], [0, 4])

    def test_filled_delay_slot_keeps_no_padding(self):
        instructions = self.listing('   0:\tjr\tra\n   4:\taddiu\tsp,sp,24\n   8:\tnop\n')
        self.assertEqual([item.offset for item in probe_report.trim_padding(instructions)], [0, 4])

    def test_listing_without_padding_is_unchanged(self):
        instructions = self.listing('   0:\tjr\tra\n   4:\tnop\n')
        self.assertEqual(len(probe_report.trim_padding(instructions)), 2)


class UnitComparisonTests(unittest.TestCase):
    def test_moved_function_counts_as_identical(self):
        other = listing('  40:\tjr\tra\n  44:\tnop\n', 'func_15000100', 0x40)
        moved = listing('  48:\tjr\tra\n  4c:\tnop\n', 'func_15000100', 0x48)
        base = probe_report.function_listings(REFERENCE + other)
        candidate = probe_report.function_listings(REFERENCE + moved)
        identical, problems = probe_report.compare_functions(base, candidate, {'func_15000000'})
        self.assertEqual((identical, problems), (1, []))

    def test_changed_missing_and_extra_functions_are_reported(self):
        other = listing('  40:\tjr\tra\n  44:\tnop\n', 'func_15000100', 0x40)
        changed = listing('  40:\tjr\tra\n  44:\tmove\tv0,zero\n', 'func_15000100', 0x40)
        extra = listing('  48:\tjr\tra\n  4c:\tnop\n', 'func_15000200', 0x48)
        gone = listing('  48:\tjr\tra\n  4c:\tnop\n', 'func_15000300', 0x48)
        base = probe_report.function_listings(REFERENCE + other + gone)
        candidate = probe_report.function_listings(REFERENCE + changed + extra)
        identical, problems = probe_report.compare_functions(base, candidate, {'func_15000000'})
        self.assertEqual(identical, 0)
        self.assertEqual(len(problems), 3)
        self.assertTrue(problems[0].startswith('func_15000100: CHANGED (1 lines differ'))
        self.assertIn('func_15000300: missing from the variant object', problems)
        self.assertIn('func_15000200: only in the variant object', problems)

    def test_target_is_skipped(self):
        base = probe_report.function_listings(REFERENCE)
        identical, problems = probe_report.compare_functions(base, {}, {'func_15000000'})
        self.assertEqual((identical, problems), (0, []))


def elf(sections):
    """A minimal ELF32 big-endian object holding ``sections``: {name: (type, bytes | size)}."""

    names = b'\0'
    offsets = {}
    for name in [*sections, '.shstrtab']:
        offsets[name] = len(names)
        names += name.encode() + b'\0'
    body = b''
    headers = [struct.pack('>10I', *([0] * 10))]
    position = 52
    for name, (kind, content) in sections.items():
        size = content if isinstance(content, int) else len(content)
        headers.append(struct.pack('>10I', offsets[name], kind, 0, 0, position, size, 0, 0, 4, 0))
        if not isinstance(content, int):
            body += content
            position += len(content)
    headers.append(struct.pack('>10I', offsets['.shstrtab'], 3, 0, 0, position, len(names), 0, 0, 1, 0))
    body += names
    position += len(names)
    header = bytearray(52)
    header[:7] = b'\x7fELF\x01\x02\x01'
    struct.pack_into('>I', header, 0x20, position)
    struct.pack_into('>HHH', header, 0x2E, 40, len(headers), len(headers) - 1)
    return bytes(header) + body + b''.join(headers)


class DataSectionTests(unittest.TestCase):
    def test_reads_rodata_data_and_bss(self):
        data = elf({'.text': (1, bytes(8)), '.rodata': (1, bytes.fromhex('3f800000')),
                    '.data': (1, bytes.fromhex('000003e7')), '.bss': (8, 0x10)})
        self.assertEqual(probe_report.data_sections(data),
                         {'.rodata': bytes.fromhex('3f800000'), '.data': bytes.fromhex('000003e7'),
                          '.bss': bytes(0x10)})

    def test_absent_sections_are_omitted(self):
        self.assertEqual(probe_report.data_sections(elf({'.text': (1, bytes(4))})), {})

    def test_other_files_are_rejected(self):
        with self.assertRaises(ValueError):
            probe_report.data_sections(b'not an object')


class SectionComparisonTests(unittest.TestCase):
    def test_equal_sections_are_silent(self):
        sections = {'.rodata': bytes.fromhex('3f800000'), '.data': b'', '.bss': b''}
        self.assertEqual(probe_report.compare_sections(sections, dict(sections)), [])

    def test_appended_literal_words_are_listed(self):
        base = {'.rodata': bytes.fromhex('4479c0004479c000c61c40004479c000')}
        candidate = {'.rodata': bytes.fromhex('4479c0004479c000c61c40004479c000c61c4000') + bytes(12)}
        lines = probe_report.compare_sections(base, candidate)
        self.assertEqual(lines, ['.rodata: size 0x10 -> 0x20; appended words: c61c4000'])

    def test_new_pool_after_alignment_padding(self):
        base = {'.rodata': bytes.fromhex('3d4ccccd') + bytes(12)}
        candidate = {'.rodata': bytes.fromhex('3d4ccccd3ba3d70a') + bytes(8)}
        lines = probe_report.compare_sections(base, candidate)
        self.assertEqual(lines, ['.rodata: size 0x10 -> 0x10; appended words: 3ba3d70a'])

    def test_reordered_pool_prints_the_variant_words(self):
        base = {'.rodata': bytes.fromhex('3f99999a3f4ccccd')}
        candidate = {'.rodata': bytes.fromhex('38d1b7173f99999a3f4ccccd') + bytes(4)}
        lines = probe_report.compare_sections(base, candidate)
        self.assertEqual(lines, ['.rodata: size 0x8 -> 0x10; variant words: 38d1b717 3f99999a 3f4ccccd 00000000'])

    def test_bss_reports_size_only(self):
        lines = probe_report.compare_sections({'.bss': bytes(4)}, {'.bss': bytes(16)})
        self.assertEqual(lines, ['.bss: size 0x4 -> 0x10'])

    def test_long_pools_are_truncated(self):
        self.assertTrue(probe_report.words(bytes(100)).endswith(' ...'))


if __name__ == '__main__':
    unittest.main()
