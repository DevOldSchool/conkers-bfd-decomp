"""Full-span scoring regressions; pinned-library cases also run in Docker."""
from __future__ import annotations

import importlib.util
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
SPEC = importlib.util.spec_from_file_location('registered_diff_helper', ROOT / 'scripts/diff.py')
helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(helper)


def line(address, mnemonic='nop'):
    return SimpleNamespace(line_num=address, mnemonic=mnemonic, original=mnemonic,
                           diff_row=mnemonic)


class RegisteredSpanTests(unittest.TestCase):
    def test_only_final_display_marker_is_removed(self):
        instructions = [line(0), line(4)]
        self.assertEqual(instructions, helper.registered_span_lines(
            instructions + [line(None, '...')], 2, reference=True))

    def test_missing_reference_word_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'does not cover'):
            helper.registered_span_lines([line(0)], 2, reference=True)

    def test_short_candidate_remains_available_for_mismatch_scoring(self):
        instructions = [line(0)]
        self.assertEqual(instructions, helper.registered_span_lines(instructions, 2, reference=False))

    def test_discontinuous_words_are_rejected(self):
        with self.assertRaisesRegex(ValueError, 'discontinuous'):
            helper.registered_span_lines([line(0), line(8)], 2, reference=True)

    def test_interior_marker_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'non-instruction'):
            helper.registered_span_lines([line(None, '...'), line(4)], 2, reference=True)

    def test_data_reference_annotations_are_excluded_from_instruction_span(self):
        instructions = [line(0), line(4)]
        annotation = line(None, '<data-ref>')
        annotation.original = '.rodata+0x0,0x4,0x8,0xc,0x10'
        for reference in (True, False):
            with self.subTest(reference=reference):
                self.assertEqual(instructions, helper.registered_span_lines(
                    [instructions[0], annotation, instructions[1], line(None, '...')],
                    2, reference=reference))

    def test_data_reference_cannot_replace_missing_reference_instruction(self):
        with self.assertRaisesRegex(ValueError, 'does not cover'):
            helper.registered_span_lines(
                [line(0), line(None, '<data-ref>')], 2, reference=True)

    def test_data_reference_with_instruction_address_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'data-reference annotation has an instruction address'):
            helper.registered_span_lines([line(0, '<data-ref>')], 1, reference=True)


@unittest.skipUnless(helper.ASM_DIFFER.is_file(), 'requires pinned Docker asm-differ')
class PinnedScoringTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        spec = importlib.util.spec_from_file_location('test_pinned_asm_differ', helper.ASM_DIFFER)
        cls.differ = importlib.util.module_from_spec(spec)
        sys.modules[spec.name] = cls.differ
        spec.loader.exec_module(cls.differ)
        helper.configure_registered_span_differ(cls.differ)

    def score(self, base, current, count, *, base_refs='', current_refs=''):
        d = self.differ
        config = d.Config(
            arch=d.get_arch('mips'), diff_obj=True, file=None, ref_file=None,
            make=False, source_old_binutils=False, diff_section='.text', inlines=False,
            max_function_size_lines=count, max_function_size_bytes=count*4,
            formatter=d.PlainFormatter(column_width=80), diff_mode=d.DiffMode.NORMAL,
            base_shift=0, skip_lines=0, compress=None, show_rodata_refs=True,
            show_branches=False, show_line_numbers=True, show_source=False,
            stop_at_ret=None, ignore_large_imms=False, ignore_addr_diffs=False,
            algorithm='difflib', reg_categories={}, diff_function_symbols=False)
        def parse(instructions, refs):
            dump = '\n'.join(f' {i*4:x}:\t00000000\t{text}' for i, text in enumerate(instructions))
            return d.process(refs + dump, config)
        return d.do_diff(parse(base, base_refs), parse(current, current_refs), config).score

    def test_one_sided_jump_table_annotations_do_not_change_score(self):
        instructions = ['addiu\tv0,v0,1', 'jr\tra', 'nop']
        refs = ''.join(f'DATAREF 4 {offset} .rodata\n' for offset in range(0, 20, 4))
        for side in ('base_refs', 'current_refs'):
            with self.subTest(side=side):
                self.assertEqual(0, self.score(instructions, instructions, 3, **{side: refs}))

    def test_jump_table_annotation_does_not_hide_instruction_difference(self):
        self.assertGreater(self.score(
            ['addiu\tv0,v0,1', 'jr\tra', 'nop'],
            ['addiu\tv0,v0,2', 'jr\tra', 'nop'], 3,
            current_refs='DATAREF 4 0 .rodata\n'), 0)

    def test_short_exact_wrapper_ignores_neighbor_display_marker(self):
        wrapper = ['addiu\tsp,sp,-24', 'sw\tra,20(sp)', 'jal\t0', 'nop',
                   'lw\tra,20(sp)', 'addiu\tsp,sp,24', 'jr\tra', 'nop']
        self.assertEqual(0, self.score(wrapper, wrapper + ['addiu\tv0,zero,1'], 8))

    def test_tail_difference_after_long_matching_prefix_is_scored(self):
        prefix = ['addiu\tv0,v0,1'] * 60
        base = prefix + ['addu\tv0,v0,a0', 'jr\tra', 'nop']
        current = prefix + ['subu\tv0,v0,a0', 'jr\tra', 'nop', 'nop']
        self.assertGreater(self.score(base, current, len(base)), 0)

    def test_registered_trailing_nop_is_not_trimmed(self):
        self.assertGreater(self.score(['jr\tra', 'nop', 'nop'], ['jr\tra', 'nop'], 3), 0)

    def test_second_return_is_scored(self):
        self.assertGreater(self.score(['jr\tra', 'nop', 'jr\tra', 'nop'],
                                      ['jr\tra', 'nop', 'break\t0', 'nop'], 4), 0)
