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
        return probe_report.classify(*probe_report.aligned(self.reference, candidate))

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

    def test_retargeted_branch_of_equal_rank_is_reported(self):
        # The only branch still renders as `.L1`, but it now lands one instruction earlier.
        candidate = self.candidate('beqz\ta0,1c <func_15000000+0x1c>', 'beqz\ta0,18 <func_15000000+0x18>')
        counts = self.counts(candidate)
        self.assertEqual(counts['branch-target'], 1)
        self.assertEqual(sum(counts.values()), 1)
        diff = probe_report.diff_lines(self.reference, candidate, context=0)
        self.assertIn('-    c:       beqz\ta0,.L1 -> +0x1c', diff)
        self.assertIn('+    c:       beqz\ta0,.L1 -> +0x18', diff)

    def test_branch_that_follows_its_moved_target_is_not_reported(self):
        moved = listing(
            '   0:\taddiu\tsp,sp,-24\n'
            '   4:\tlui\tv0,0x0\n\t\t\t4: R_MIPS_HI16\tD_800BE9E4\n'
            '   8:\tlw\tv0,0(v0)\n\t\t\t8: R_MIPS_LO16\tD_800BE9E4\n'
            '   c:\tbeqz\ta0,20 <func_15000000+0x20>\n'
            '  10:\tnop\n'
            '  14:\tmove\tv1,zero\n'
            '  18:\tjal\t0 <func_15000000>\n\t\t\t18: R_MIPS_26\tfunc_15001000\n'
            '  1c:\tmove\ta0,v0\n'
            '  20:\tjr\tra\n'
            '  24:\taddiu\tsp,sp,24\n')
        counts = self.counts(probe_report.function_listings(moved)['func_15000000'])
        self.assertEqual(counts['branch-target'], 0)
        self.assertEqual(counts['inserted'], 1)
        self.assertEqual(sum(counts.values()), 1)

    def test_trailing_insertion_without_context(self):
        candidate = probe_report.function_listings(REFERENCE + '  24:\tnop\n')['func_15000000']
        diff = probe_report.diff_lines(self.reference, candidate, context=0)
        self.assertEqual(diff, ['@@ reference +0x24, candidate +0x24 @@', '+   24:       nop'])

    def test_empty_listings_do_not_raise(self):
        self.assertEqual(probe_report.diff_lines([], [], context=0), [])
        diff = probe_report.diff_lines([], self.reference, context=0)
        self.assertEqual(diff[0], '@@ reference +0x0, candidate +0x0 @@')
        self.assertEqual(len(diff), 10)
        self.assertEqual(probe_report.diff_lines(self.reference, [], context=2)[0],
                         '@@ reference +0x0, candidate +0x0 @@')

    def test_symbol_spelling_with_a_different_addend_is_relocation_only(self):
        # A named reference symbol against the candidate's own section plus offset.
        reference = ['lwc1\t$f6,0(at) %lo(D_800A04E4)', 'lui\tat,0x0 %hi(D_800A04E4)',
                     'addiu\ta2,a2,0 %lo(D_800C3600)']
        candidate = ['lwc1\t$f6,4(at) %lo(.rodata)', 'lui\tat,0x0 %hi(.rodata)',
                     'addiu\ta2,a2,16 %lo(D_800C35F0)']
        counts = probe_report.classify(reference, candidate)
        self.assertEqual(counts['relocation-only'], 3)
        self.assertEqual(sum(counts.values()), 3)

    def test_zero_is_not_an_allocated_register(self):
        counts = probe_report.classify(['move\tv0,zero'], ['move\tv0,a0'])
        self.assertEqual(counts['other'], 1)
        self.assertEqual(probe_report.register_map(['move\tv0,zero'], ['move\tv0,a0']), [])

    def test_summary_names_each_kind(self):
        text = probe_report.summary({'register-only': 2, 'relocation-only': 0, 'branch-target': 0,
                                     'other': 1, 'inserted': 0, 'deleted': 3})
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

    def test_break_is_not_a_branch(self):
        instructions = self.listing('   0:\tbreak\t0x7\n   4:\tnop\n   8:\tnop\n')
        self.assertEqual([item.offset for item in probe_report.trim_padding(instructions)], [0])

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

    def test_trailing_alignment_of_the_last_function_is_ignored(self):
        last = listing('  40:\tjr\tra\n  44:\tnop\n  48:\tnop\n  4c:\tnop\n', 'func_15000100', 0x40)
        shorter = listing('  40:\tjr\tra\n  44:\tnop\n', 'func_15000100', 0x40)
        base = probe_report.function_listings(REFERENCE + last)
        candidate = probe_report.function_listings(REFERENCE + shorter)
        self.assertEqual(probe_report.compare_functions(base, candidate, {'func_15000000'}), (1, []))

    def test_literal_that_only_moved_inside_rodata_is_identical(self):
        def user(offset):
            return listing(f'  40:\tlui\tat,0x0\n\t\t\t40: R_MIPS_HI16\t.rodata\n'
                           f'  44:\tlwc1\t$f4,{offset}(at)\n\t\t\t44: R_MIPS_LO16\t.rodata\n'
                           '  48:\tjr\tra\n  4c:\tnop\n', 'func_15000100', 0x40)
        base = probe_report.function_listings(REFERENCE + user(0))
        candidate = probe_report.function_listings(REFERENCE + user(4))
        before = sections(rodata=bytes.fromhex('3f800000'))
        after = sections(rodata=bytes.fromhex('c61c40003f800000'))
        self.assertEqual(probe_report.compare_functions(base, candidate, {'func_15000000'}, before, after),
                         (1, []))
        # Without the section contents the changed offset is all there is to compare.
        self.assertEqual(probe_report.compare_functions(base, candidate, {'func_15000000'})[0], 0)
        # A different word at the new offset is a real change.
        other = sections(rodata=bytes.fromhex('c61c400040000000'))
        self.assertEqual(probe_report.compare_functions(base, candidate, {'func_15000000'}, before, other)[0], 0)

    def test_render_names_section_loads_by_content(self):
        text = listing('   0:\tlwc1\t$f4,4(at)\n\t\t\t0: R_MIPS_LO16\t.rodata\n'
                       '   4:\tlw\tt0,8(at)\n\t\t\t4: R_MIPS_LO16\t.rodata\n'
                       '   8:\taddiu\ta0,a0,0\n\t\t\t8: R_MIPS_LO16\t.bss\n'
                       '   c:\tlwc1\t$f6,64(at)\n\t\t\tc: R_MIPS_LO16\t.rodata\n')
        contents = sections(rodata=probe_report.Section(bytes.fromhex('c61c40003f80000000000000'),
                                                        frozenset({8})), bss=bytes(8))
        lines = probe_report.render(probe_report.function_listings(text)['func_15000000'], contents)
        self.assertEqual(lines, ['lwc1\t$f4,0(at) %lo(.rodata:3f800000)', 'lw\tt0,0(at) %lo(.rodata:relocated)',
                                 'addiu\ta0,a0,0 %lo(.bss)', 'lwc1\t$f6,64(at) %lo(.rodata)'])

    def test_target_is_skipped(self):
        base = probe_report.function_listings(REFERENCE)
        identical, problems = probe_report.compare_functions(base, {}, {'func_15000000'})
        self.assertEqual((identical, problems), (0, []))


def sections(**contents):
    """{'.rodata': Section(...)} from keyword arguments named without the dot."""

    return {'.' + name: content if isinstance(content, probe_report.Section) else probe_report.Section(content)
            for name, content in contents.items()}


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
                         sections(rodata=bytes.fromhex('3f800000'), data=bytes.fromhex('000003e7'),
                                  bss=bytes(0x10)))

    def test_relocated_words_are_recorded_per_section(self):
        entries = struct.pack('>II', 4, 0x102) + struct.pack('>II', 8, 0x102)
        data = elf({'.text': (1, bytes(8)), '.rodata': (1, bytes(12)), '.rel.rodata': (9, entries),
                    '.rel.text': (9, struct.pack('>II', 0, 0x105))})
        self.assertEqual(probe_report.data_sections(data),
                         {'.rodata': probe_report.Section(bytes(12), frozenset({4, 8}))})

    def test_absent_sections_are_omitted(self):
        self.assertEqual(probe_report.data_sections(elf({'.text': (1, bytes(4))})), {})

    def test_other_files_are_rejected(self):
        with self.assertRaises(ValueError):
            probe_report.data_sections(b'not an object')


class SectionComparisonTests(unittest.TestCase):
    def test_equal_sections_are_silent(self):
        contents = sections(rodata=bytes.fromhex('3f800000'), data=b'', bss=b'')
        self.assertEqual(probe_report.compare_sections(contents, dict(contents)), [])

    def test_appended_literal_words_are_listed(self):
        base = sections(rodata=bytes.fromhex('4479c0004479c000c61c40004479c000'))
        candidate = sections(rodata=bytes.fromhex('4479c0004479c000c61c40004479c000c61c4000') + bytes(12))
        lines = probe_report.compare_sections(base, candidate)
        self.assertEqual(lines, ['.rodata: size 0x10 -> 0x20; appended words: c61c4000'])

    def test_new_pool_after_alignment_padding(self):
        base = sections(rodata=bytes.fromhex('3d4ccccd') + bytes(12))
        candidate = sections(rodata=bytes.fromhex('3d4ccccd3ba3d70a') + bytes(8))
        lines = probe_report.compare_sections(base, candidate)
        self.assertEqual(lines, ['.rodata: size 0x10 -> 0x10; appended words: 3ba3d70a'])

    def test_change_inside_the_pool_is_shown_from_the_first_difference(self):
        base = sections(rodata=bytes.fromhex('3f99999a3f4ccccd'))
        candidate = sections(rodata=bytes.fromhex('3f99999a38d1b7173f4ccccd') + bytes(4))
        lines = probe_report.compare_sections(base, candidate)
        self.assertEqual(lines, ['.rodata: size 0x8 -> 0x10; differs from +0x4, '
                                 'variant words there: 38d1b717 3f4ccccd 00000000'])

    def test_shrunk_pool_is_reported(self):
        base = sections(rodata=bytes.fromhex('3f99999a3f4ccccd'))
        candidate = sections(rodata=bytes.fromhex('3f99999a'))
        lines = probe_report.compare_sections(base, candidate)
        self.assertEqual(lines, ['.rodata: size 0x8 -> 0x4; differs from +0x4, variant words there: (none)'])

    def test_jump_table_entries_are_not_compared(self):
        # Table words hold text offsets, which move when the function before the target changes size.
        base = sections(rodata=probe_report.Section(bytes.fromhex('0000001000000020'), frozenset({0, 4})))
        candidate = sections(rodata=probe_report.Section(bytes.fromhex('0000001400000024'), frozenset({0, 4})))
        self.assertEqual(probe_report.compare_sections(base, candidate), [])
        literal = sections(rodata=probe_report.Section(bytes.fromhex('00000014000000243f800000'),
                                                       frozenset({0, 4})))
        self.assertEqual(probe_report.compare_sections(base, literal),
                         ['.rodata: size 0x8 -> 0xc; appended words: 3f800000'])

    def test_bss_reports_size_only(self):
        lines = probe_report.compare_sections(sections(bss=bytes(4)), sections(bss=bytes(16)))
        self.assertEqual(lines, ['.bss: size 0x4 -> 0x10'])

    def test_long_pools_are_truncated(self):
        self.assertTrue(probe_report.words(bytes(100)).endswith(' ...'))


if __name__ == '__main__':
    unittest.main()
