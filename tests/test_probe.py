from __future__ import annotations

from contextlib import redirect_stderr, redirect_stdout
import io
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import probe


SOURCE = '''#include "types.h"

extern s32 D_1;

void func_10000000(void *arg0) {
    if (arg0 != 0) {
        D_1 = 1; /* } in comment */
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/unit/func_10000010.s")
s32 func_10000020(s32 arg0) {
    return arg0;
}
'''

# Mirrors src/main/init_1420.c: the work-item ID names the pragma, while the
# definition uses a profile macro alias of the regional symbol.
ALIASED = '''#include "types.h"

#if PROFILE_US
#define clear_bootstrap_region func_80001420
#else
#define clear_bootstrap_region func_800014B0
#endif

#if 0 /* CONKER_DEFERRED_CANDIDATE func_bootstrap_clear_region CURRENT (30) */
void clear_bootstrap_region(void) {
    return;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_bootstrap_clear_region */
#pragma GLOBAL_ASM("asm/nonmatchings/unit/func_bootstrap_clear_region.s")
'''


def splice(content, identifier, regional, variant):
    return probe.splice_variant(content, identifier, regional, 'src/unit.c', variant)


class SpliceVariantTests(unittest.TestCase):
    def test_replaces_existing_definition_in_place(self):
        variant = 'void func_10000000(void *arg0) {\n    D_1 = 2;\n}\n'
        result = splice(SOURCE, 'func_10000000', 'func_10000000', variant)
        self.assertIn('D_1 = 2;', result)
        self.assertNotIn('D_1 = 1;', result)
        self.assertLess(result.index('D_1 = 2;'), result.index('#pragma'))

    def test_replaces_global_asm_pragma_and_keeps_helper_declarations(self):
        variant = 'extern s32 D_2;\n\ns32 func_10000010(void) {\n    return D_2;\n}\n'
        result = splice(SOURCE, 'func_10000010', 'func_10000010', variant)
        self.assertNotIn('func_10000010.s', result)
        self.assertIn('extern s32 D_2;', result)
        self.assertLess(result.index('return D_2;'), result.index('s32 func_10000020'))

    def test_profile_alias_definition_replaces_identifier_pragma(self):
        variant = 'void clear_bootstrap_region(void) {\n    D_1 = 3;\n}\n'
        result = splice(ALIASED, 'func_bootstrap_clear_region', 'func_80001420', variant)
        self.assertNotIn('func_bootstrap_clear_region.s', result)
        self.assertIn('D_1 = 3;', result)
        self.assertIn('#if 0 /* CONKER_DEFERRED_CANDIDATE func_bootstrap_clear_region', result)

    def test_regional_symbol_definition_is_accepted_for_aliased_item(self):
        variant = 'void func_80001420(void) {\n}\n'
        result = splice(ALIASED, 'func_bootstrap_clear_region', 'func_80001420', variant)
        self.assertIn('void func_80001420(void) {', result)
        self.assertNotIn('func_bootstrap_clear_region.s', result)

    def test_differing_work_item_id_is_rejected_because_it_emits_no_regional_symbol(self):
        variant = 'void func_bootstrap_clear_region(void) {\n}\n'
        with self.assertRaisesRegex(probe.VariantError, 'func_80001420, clear_bootstrap_region'):
            splice(ALIASED, 'func_bootstrap_clear_region', 'func_80001420', variant)

    def test_matching_work_item_id_is_its_own_regional_symbol(self):
        self.assertEqual(['func_10000000'], probe.definition_names(SOURCE, 'func_10000000'))

    def test_complete_source_variant_is_used_verbatim(self):
        variant = '#include "types.h"\nvoid func_10000000(void) {\n}\n'
        self.assertEqual(variant, splice(SOURCE, 'func_10000000', 'func_10000000', variant))

    def test_variant_must_define_the_work_item(self):
        with self.assertRaises(probe.VariantError):
            splice(SOURCE, 'func_10000000', 'func_10000000', 'void other(void) {\n}\n')

    def test_missing_definition_and_pragma_is_rejected(self):
        with self.assertRaises(probe.VariantError):
            splice('s32 x;\n', 'func_10000000', 'func_10000000', 'void func_10000000(void) {\n}\n')


class MainErrorHandlingTests(unittest.TestCase):
    def run_main(self, outcomes, padding=None):
        """Run main() over variants whose build/score steps follow ``outcomes``."""

        target = probe.Target('func_A', 'us', Path('src/unit.c'), 'func_A', Path('ref.s'),
                              Path('ref.o'), 8, Path('build/probe'))
        builds = iter(outcomes)

        def build_variant(_target, _variant, _index):
            outcome = next(builds)
            if outcome == 'reject':
                raise probe.VariantError('cfe: Error: syntax')
            return outcome

        def score(_target, candidate):
            if candidate == 'scorer-fails':
                raise probe.ToolingError('asm-differ crashed')
            return 7

        stdout, stderr = io.StringIO(), io.StringIO()
        argv = ['probe.py', 'us', 'func_A', *[f'v{i}.c' for i in range(len(outcomes))]]
        with mock.patch.object(sys, 'argv', argv), \
                mock.patch.object(probe, 'resolve', return_value=target), \
                mock.patch.object(probe, 'build_variant', side_effect=build_variant), \
                mock.patch.object(probe, 'score', side_effect=score), \
                mock.patch.object(probe, 'object_frame_size', return_value=0x20), \
                mock.patch.object(probe, 'reference_frame_size', return_value=0x20), \
                mock.patch.object(probe, 'terminal_padding_extent', return_value=padding), \
                redirect_stdout(stdout), redirect_stderr(stderr):
            status = probe.main()
        return status, stdout.getvalue(), stderr.getvalue()

    def test_unscored_terminal_padding_is_reported(self):
        status, stdout, _stderr = self.run_main(['ok'], padding=4)
        self.assertEqual(0, status)
        self.assertIn('trailing alignment words were not scored for v0.c', stdout)
        status, stdout, _stderr = self.run_main(['ok'])
        self.assertNotIn('trailing alignment words', stdout)

    def test_scorer_failure_after_a_scored_variant_blocks_without_partial_ranking(self):
        status, stdout, stderr = self.run_main(['ok', 'scorer-fails'])
        self.assertEqual(probe.diff.EXIT_BLOCKED_TOOLING, status)
        self.assertNotIn('CURRENT', stdout)
        self.assertIn('asm-differ crashed', stderr)

    def test_scorer_failure_on_every_variant_is_tooling_not_compile(self):
        status, _stdout, stderr = self.run_main(['scorer-fails'])
        self.assertEqual(probe.diff.EXIT_BLOCKED_TOOLING, status)
        self.assertIn('asm-differ crashed', stderr)

    def test_rejected_variants_are_skipped_and_others_ranked(self):
        status, stdout, stderr = self.run_main(['reject', 'ok'])
        self.assertEqual(0, status)
        self.assertIn('CURRENT (7)', stdout)
        self.assertIn('skip v0.c', stderr)

    def test_all_variants_rejected_is_a_compile_failure(self):
        status, _stdout, _stderr = self.run_main(['reject'])
        self.assertEqual(probe.diff.EXIT_FIX_COMPILE, status)


LISTING = (
    '\nDisassembly of section .text:\n\n00000000 <func_A>:\n'
    '   0:\tlui\tv0,0x0\n\t\t\t0: R_MIPS_HI16\tD_1\n'
    '   4:\tjr\tra\n   8:\tlw\tv0,0(v0)\n\t\t\t8: R_MIPS_LO16\tD_1\n'
    '   c:\tnop\n'
    '\n00000010 <func_B>:\n  10:\tjr\tra\n  14:\tnop\n'
)


class ReportTests(unittest.TestCase):
    target = probe.Target('func_A', 'us', Path('src/unit.c'), 'func_A', Path('ref.s'),
                          Path('ref.o'), 8, Path('build/probe'))

    def run_main(self, flags, scores, *, diff_report=None, unit_report=None, base=None):
        stdout, stderr = io.StringIO(), io.StringIO()
        argv = ['probe.py', 'us', 'func_A', *scores, *flags]
        calls = {'diff': [], 'unit': [], 'base': 0}

        def default_diff(_target, candidate, context):
            calls['diff'].append((candidate, context))
            return ['instruction diff: identical']

        def default_unit(_target, _base, candidate):
            calls['unit'].append(candidate)
            return ['2 other functions identical']

        def build_base(_target):
            calls['base'] += 1
            if base is not None:
                raise base
            return Path('base.o')

        with mock.patch.object(sys, 'argv', argv), \
                mock.patch.object(probe, 'resolve', return_value=self.target), \
                mock.patch.object(probe, 'build_variant', side_effect=lambda _t, variant, _i: variant), \
                mock.patch.object(probe, 'score', side_effect=lambda _t, candidate: scores[str(candidate)]), \
                mock.patch.object(probe, 'object_frame_size', return_value=0x20), \
                mock.patch.object(probe, 'reference_frame_size', return_value=0x20), \
                mock.patch.object(probe, 'terminal_padding_extent', return_value=None), \
                mock.patch.object(probe, 'build_base', side_effect=build_base), \
                mock.patch.object(probe, 'diff_report', side_effect=diff_report or default_diff), \
                mock.patch.object(probe, 'unit_report', side_effect=unit_report or default_unit), \
                redirect_stdout(stdout), redirect_stderr(stderr):
            try:
                status = probe.main()
            except SystemExit as error:
                status = error.code
        return status, stdout.getvalue(), stderr.getvalue(), calls

    def test_plain_probe_builds_no_reports(self):
        status, stdout, _stderr, calls = self.run_main([], {'a.c': 5})
        self.assertEqual(0, status)
        self.assertEqual(calls, {'diff': [], 'unit': [], 'base': 0})
        self.assertNotIn('--- diff', stdout)

    def test_diff_reports_only_the_best_variant(self):
        status, stdout, _stderr, calls = self.run_main(['--diff', '--context', '1'], {'a.c': 30, 'b.c': 5})
        self.assertEqual(0, status)
        self.assertEqual(calls['diff'], [(Path('b.c'), 1)])
        self.assertIn('--- diff of b.c (CURRENT 5): - reference, + candidate', stdout)
        self.assertLess(stdout.index('CURRENT (30)'), stdout.index('--- diff of b.c'))

    def test_unit_reports_every_variant_against_one_base(self):
        def unit_report(_target, _base, candidate):
            if str(candidate) == 'a.c':
                return ['1 other functions identical, 1 not', 'func_B: CHANGED (1 lines differ (1 other))',
                        '.rodata: size 0x0 -> 0x10; appended words: 3f800000']
            return ['2 other functions identical']

        status, stdout, _stderr, calls = self.run_main(['--unit'], {'a.c': 30, 'b.c': 5},
                                                       unit_report=unit_report)
        self.assertEqual(0, status)
        self.assertEqual(calls['base'], 1)
        self.assertIn('unit b.c: 2 other functions identical\n', stdout)
        self.assertIn('unit a.c: 1 other functions identical, 1 not\n'
                      '  func_B: CHANGED (1 lines differ (1 other))\n'
                      '  .rodata: size 0x0 -> 0x10; appended words: 3f800000\n', stdout)

    def test_report_failure_blocks_after_the_ranking(self):
        status, stdout, stderr, _calls = self.run_main(['--unit'], {'a.c': 5},
                                                       base=probe.ToolingError('the current source does not compile'))
        self.assertEqual(probe.diff.EXIT_BLOCKED_TOOLING, status)
        self.assertIn('CURRENT (5)', stdout)
        self.assertIn('report failed: the current source does not compile', stderr)

    def test_layout_excludes_the_reports(self):
        status, _stdout, stderr, _calls = self.run_main(['--layout', '--diff'], {'a.c': 5})
        self.assertEqual(2, status)
        self.assertIn('--layout cannot be combined', stderr)

    def test_asm_prints_the_best_variant_listing(self):
        with mock.patch.object(probe, 'compiler_assembly', return_value=['\t.ent\tfunc_A 2', '\t.end\tfunc_A']) as asm:
            status, stdout, _stderr, _calls = self.run_main(['--asm'], {'a.c': 30, 'b.c': 5})
        self.assertEqual(0, status)
        asm.assert_called_once_with(self.target, Path('b.c'))
        self.assertIn('--- compiler assembly of b.c (CURRENT 5), before assembler scheduling\n'
                      '\t.ent\tfunc_A 2\n\t.end\tfunc_A\n', stdout)

    def test_function_assembly_keeps_source_comments_and_drops_debug_directives(self):
        listing = ('\t.ent\tfunc_B 2\nfunc_B:\n\tjr\t$31\n\t.end\tfunc_B\n'
                   '\t.ent\tfunc_A 2\nfunc_A:\n\t.option\tO2\n\t.loc\t2 10\n\t.bgnb\t3\n'
                   ' #  10\t    D_1 = 1;\n\tli\t$14, 1\n\t.noalias\t$2,$sp\n\tsw\t$14, D_1\n'
                   '\t.endb\t9\n\t.end\tfunc_A\n\t.ent\tfunc_C 2\n')
        self.assertEqual(probe.function_assembly(listing, 'func_A'),
                         ['\t.ent\tfunc_A 2', 'func_A:', ' #  10\t    D_1 = 1;', '\tli\t$14, 1',
                          '\tsw\t$14, D_1', '\t.end\tfunc_A'])
        self.assertEqual(probe.function_assembly(listing, 'func_D'), [])

    def test_compiler_assembly_runs_cc_with_dash_s_and_absolute_includes(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'variant001.c'
            source.write_text('void func_A(void) {}\n', encoding='utf-8')

            def run(command, **kwargs):
                self.assertEqual(Path(kwargs['cwd']), Path(directory))
                self.assertIn('-S', command)
                self.assertNotIn('-c', command)
                self.assertIn(str(probe.ROOT / 'include'), command)
                self.assertEqual(command[-1], 'variant001.c')
                (Path(directory) / 'variant001.s').write_text(
                    '\t.ent\tfunc_A 2\nfunc_A:\n\tjr\t$31\n\t.end\tfunc_A\n', encoding='utf-8')
                return mock.Mock(returncode=0)

            with mock.patch.object(probe.subprocess, 'run', side_effect=run):
                lines = probe.compiler_assembly(self.target, Path(directory) / 'variant001.o')
            self.assertEqual(lines, ['\t.ent\tfunc_A 2', 'func_A:', '\tjr\t$31', '\t.end\tfunc_A'])
            self.assertFalse((Path(directory) / 'variant001.s').exists())

    def test_compiler_assembly_adds_the_generated_include_for_debugger_units(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'variant001.c'
            source.write_text(probe.compile_c.DEBUGGER_UI_INCLUDE + '\nvoid func_A(void) {}\n', encoding='utf-8')

            def run(command, **_kwargs):
                self.assertIn(str(probe.ROOT / 'build' / 'us'), command)
                (Path(directory) / 'variant001.s').write_text('\t.ent\tfunc_A 2\n\t.end\tfunc_A\n',
                                                               encoding='utf-8')
                return mock.Mock(returncode=0)

            with mock.patch.object(probe.subprocess, 'run', side_effect=run):
                self.assertEqual(len(probe.compiler_assembly(self.target, Path(directory) / 'variant001.o')), 2)

    def test_compiler_assembly_reports_the_compiler_error_and_cleans_up(self):
        with tempfile.TemporaryDirectory() as directory:
            (Path(directory) / 'variant001.c').write_text('void func_A(void) {}\n', encoding='utf-8')

            def run(_command, **_kwargs):
                (Path(directory) / 'variant001.s').write_text('partial', encoding='utf-8')
                return mock.Mock(returncode=1, stdout='', stderr='cfe: Error: variant001.c, line 3: bad\n')

            with mock.patch.object(probe.subprocess, 'run', side_effect=run):
                with self.assertRaisesRegex(probe.ToolingError, 'cfe: Error: variant001.c, line 3: bad'):
                    probe.compiler_assembly(self.target, Path(directory) / 'variant001.o')
            self.assertFalse((Path(directory) / 'variant001.s').exists())

    def test_object_listing_keeps_zero_runs(self):
        completed = mock.Mock(stdout='listing')
        with mock.patch.object(probe.subprocess, 'run', return_value=completed) as run:
            self.assertEqual(probe.object_listing(Path('x.o')), 'listing')
        command = run.call_args.args[0]
        self.assertIn('-z', command)
        self.assertIn('-r', command)

    def test_object_listing_failure_is_a_tooling_error(self):
        with mock.patch.object(probe.subprocess, 'run', side_effect=OSError('no objdump')):
            with self.assertRaises(probe.ToolingError):
                probe.object_listing(Path('x.o'))

    def test_build_base_compiles_the_current_source_without_raw_members(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'unit.c'
            source.write_text('s32 a;\n#pragma GLOBAL_ASM("asm/nonmatchings/unit/func_A.s")\ns32 b;\n',
                              encoding='utf-8')
            target = probe.Target('func_A', 'us', source, 'func_A', Path('ref.s'), Path('ref.o'), 8,
                                  Path(directory))
            with mock.patch.object(probe.compile_c, 'run_compile', return_value=mock.Mock(returncode=0)) as run:
                self.assertEqual(probe.build_base(target), Path(directory) / 'base.o')
            self.assertNotIn('GLOBAL_ASM', (Path(directory) / 'base.c').read_text(encoding='utf-8'))
            self.assertEqual(run.call_args.args[:3], ('us', Path(directory) / 'base.c', Path(directory) / 'base.o'))
            with mock.patch.object(probe.compile_c, 'run_compile', return_value=mock.Mock(returncode=1)):
                with self.assertRaisesRegex(probe.ToolingError, 'does not compile'):
                    probe.build_base(target)

    def test_exact_match_note_is_printed_only_with_remaining_rows(self):
        rows = ['instruction diff: 1 lines differ (1 relocation-only)', '@@ x @@']
        status, stdout, _stderr, _calls = self.run_main(['--diff'], {'a.c': 0},
                                                        diff_report=lambda *_args: rows)
        self.assertEqual(0, status)
        self.assertIn('note: the scorer resolves the symbol spellings below', stdout)
        status, stdout, _stderr, _calls = self.run_main(['--diff'], {'a.c': 0})
        self.assertNotIn('symbol spellings', stdout)

    def test_compiler_assembly_failure_is_a_tooling_error(self):
        with tempfile.TemporaryDirectory() as directory:
            (Path(directory) / 'variant001.c').write_text('void func_A(void) {}\n', encoding='utf-8')
            with mock.patch.object(probe.subprocess, 'run', return_value=mock.Mock(returncode=1)):
                with self.assertRaises(probe.ToolingError):
                    probe.compiler_assembly(self.target, Path(directory) / 'variant001.o')

    def test_negative_context_is_rejected(self):
        status, _stdout, stderr, _calls = self.run_main(['--diff', '--context', '-1'], {'a.c': 5})
        self.assertEqual(2, status)
        self.assertIn('--context must not be negative', stderr)

    def test_diff_report_summarises_and_lists_hunks(self):
        candidate = LISTING.replace('lw\tv0,0(v0)', 'lw\tv1,0(v0)')
        listings = {'ref.o': LISTING, 'new.o': candidate}
        with mock.patch.object(probe, 'object_listing', side_effect=lambda path: listings[str(path)]), \
                mock.patch.object(probe, 'object_data_sections', return_value={}):
            lines = probe.diff_report(self.target, Path('new.o'), 0)
        self.assertEqual(lines[0], 'instruction diff: 1 lines differ (1 register-only)')
        self.assertEqual(lines[1], 'register map (reference->candidate): v0->v1 x1')
        self.assertIn('-    8:       lw\tv0,0(v0) %lo(D_1)', lines)
        self.assertIn('+    8:       lw\tv1,0(v0) %lo(D_1)', lines)

    def test_diff_report_requires_the_target_in_both_objects(self):
        listings = {'ref.o': LISTING, 'new.o': LISTING.replace('<func_A>', '<func_C>')}
        with mock.patch.object(probe, 'object_listing', side_effect=lambda path: listings[str(path)]), \
                mock.patch.object(probe, 'object_data_sections', return_value={}):
            with self.assertRaisesRegex(probe.ToolingError, 'func_A not found in new.o'):
                probe.diff_report(self.target, Path('new.o'), 2)

    def test_unit_report_compares_functions_and_sections(self):
        changed = LISTING.replace('  14:\tnop', '  14:\tmove\tv0,zero')
        listings = {'base.o': LISTING, 'same.o': LISTING, 'changed.o': changed}
        section = probe.probe_report.Section
        sections = {b'base': {'.rodata': section()}, b'same': {'.rodata': section()},
                    b'changed': {'.rodata': section(bytes.fromhex('3f800000') + bytes(12))}}
        with tempfile.TemporaryDirectory() as directory:
            paths = {}
            for name in ('base', 'same', 'changed'):
                paths[name] = Path(directory) / f'{name}.o'
                paths[name].write_bytes(name.encode())
            with mock.patch.object(probe, 'object_listing',
                                   side_effect=lambda path: listings[Path(path).name]), \
                    mock.patch.object(probe.probe_report, 'data_sections',
                                      side_effect=lambda data: sections[data]):
                self.assertEqual(probe.unit_report(self.target, paths['base'], paths['same']),
                                 ['1 other functions identical'])
                self.assertEqual(probe.unit_report(self.target, paths['base'], paths['changed']),
                                 ['0 other functions identical, 1 not',
                                  'func_B: CHANGED (1 lines differ (1 other))',
                                  '.rodata: size 0x0 -> 0x10; appended words: 3f800000'])


class TerminalPaddingTests(unittest.TestCase):
    """Probe leaves out only the alignment words a terminal unit member gains in finish."""

    def extent(self, start, size, extent, unit_end, tail=bytes(8)):
        reference = mock.Mock()
        reference.read_bytes.return_value = b''
        target = probe.Target('func_A', 'us', probe.ROOT / 'src/game/unit.c', 'func_A',
                              Path('ref.s'), reference, size, Path('build/probe'))
        inventory = {'functions': [{'regions': {'us': {'symbol': 'func_A', 'vram': hex(start)}}}]}
        raw = mock.Mock(relocations=[])
        raw.section.return_value = bytes(size - len(tail)) + tail
        candidate = mock.Mock()
        candidate.read_bytes.return_value = b''
        with mock.patch.object(probe.project_state, 'load_json', return_value=inventory), \
                mock.patch.object(probe.linked_aliases, 'game_context',
                                  return_value=(None, None, None, None, unit_end - 0x100, 0x100, None)), \
                mock.patch.object(probe.linked_aliases, 'Object32', return_value=raw), \
                mock.patch.object(probe.linked_aliases, 'game_padding_extent', return_value=extent), \
                mock.patch.object(probe.linked_aliases, 'function', return_value=(0, 1)):
            return probe.terminal_padding_extent(target, candidate)

    def test_terminal_alignment_words_are_left_out(self):
        self.assertEqual(0x70, self.extent(0x15000008, 0x78, 0x70, 0x15000080))

    def test_interior_members_keep_their_full_span(self):
        self.assertIsNone(self.extent(0x15000008, 0x78, 0x70, 0x15000090))

    def test_a_unit_end_off_16_byte_alignment_keeps_the_full_span(self):
        self.assertIsNone(self.extent(0x15000004, 0x78, 0x70, 0x1500007C))

    def test_nonzero_reference_words_are_still_scored(self):
        self.assertIsNone(self.extent(0x15000008, 0x78, 0x70, 0x15000080, tail=b'\0\0\0\0\x03\xe0\0\x08'))


def mdebug_object(symbols: list[tuple], aux: list[int] = ()) -> bytes:
    """Build a minimal big-endian ELF32 with an IDO-style .mdebug symbol table.

    Each symbol is ``(name, value, st, sc[, aux index])``; ``aux`` holds the
    auxiliary type words. There is no file descriptor table, so the reader
    treats the table as one file.
    """

    strings = b''
    entries = b''
    for name, value, st, sc, *index in symbols:
        iss = len(strings)
        strings += name.encode() + b'\0'
        entries += struct.pack('>iiI', iss, value, (st << 26) | (sc << 21) | (index[0] if index else 0))
    shstrtab = b'\0.shstrtab\0.mdebug\0'
    elf_header_size = 52
    mdebug_offset = elf_header_size
    symbols_offset = mdebug_offset + 0x60
    strings_offset = symbols_offset + len(entries)
    aux_offset = strings_offset + len(strings)
    fields = [0] * 23
    fields[7], fields[8] = len(symbols), symbols_offset
    fields[11], fields[12] = len(aux), aux_offset
    fields[14] = strings_offset
    mdebug = (struct.pack('>hh' + 'i' * 23, 0x7009, 0, *fields) + entries + strings
              + b''.join(struct.pack('>I', word) for word in aux))
    shstrtab_offset = mdebug_offset + len(mdebug)
    section_offset = shstrtab_offset + len(shstrtab)
    header = bytearray(elf_header_size)
    header[:6] = b'\x7fELF\x01\x02'
    struct.pack_into('>I', header, 0x20, section_offset)
    struct.pack_into('>HHH', header, 0x2E, 40, 3, 1)
    sections = struct.pack('>10I', *([0] * 10))
    sections += struct.pack('>10I', 1, 3, 0, 0, shstrtab_offset, len(shstrtab), 0, 0, 1, 0)
    sections += struct.pack('>10I', 11, 0x70000005, 0, 0, mdebug_offset, len(mdebug), 0, 0, 4, 0)
    return bytes(header) + mdebug + shstrtab + sections


class MdebugLocalsTests(unittest.TestCase):
    def test_reads_only_the_requested_procedure(self):
        data = mdebug_object([
            ('func_A', 0, probe.ST_PROC, 1),
            ('arg0', 0, probe.ST_PARAM, probe.SC_ABS),
            ('', 16, probe.ST_BLOCK, 1),
            ('link', -4, probe.ST_LOCAL, probe.SC_ABS),
            ('kinds', -176, probe.ST_LOCAL, probe.SC_ABS),
            ('', 760, probe.ST_END, 1),
            ('func_B', 0, probe.ST_PROC, 1),
            ('other', -8, probe.ST_LOCAL, probe.SC_ABS),
        ])
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'unit.o'
            path.write_bytes(data)
            found = probe.mdebug_locals(path, 'func_A')
        self.assertEqual(
            [('param', 'arg0', 0), ('local', 'link', -4), ('local', 'kinds', -176)],
            [(entry.kind, entry.name, entry.frame_offset) for entry in found],
        )

    def read(self, symbols, aux=()):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'unit.o'
            path.write_bytes(mdebug_object(symbols, list(aux)))
            return probe.mdebug_locals(path, 'func_A')

    def test_block_scoped_locals_sit_below_the_body_block(self):
        found = self.read([
            ('func_A', 0, probe.ST_PROC, 1),
            ('arg0', 0, probe.ST_PARAM, probe.SC_ABS),
            ('', 0, probe.ST_BLOCK, 1),
            ('original', -4, probe.ST_LOCAL, probe.SC_ABS),
            ('', 0, probe.ST_BLOCK, 1),
            ('packet0', -8, probe.ST_LOCAL, probe.SC_ABS),
            ('', 0, probe.ST_END, 1),
            ('', 0, probe.ST_BLOCK, 1),
            ('packet1', -12, probe.ST_LOCAL, probe.SC_ABS),
            ('', 0, probe.ST_END, 1),
            ('', 0, probe.ST_END, 1),
            ('', 0, probe.ST_END, 1),
            ('stray', -16, probe.ST_LOCAL, probe.SC_ABS),
        ])
        self.assertEqual([('arg0', False), ('original', False), ('packet0', True), ('packet1', True)],
                         [(entry.name, entry.block) for entry in found])

    def test_sizes_come_from_type_records(self):
        def tir(basic, *qualifiers):
            shifts = (12, 8, 4, 0)
            return (basic << 24) | sum(qualifier << shift for qualifier, shift in zip(qualifiers, shifts))

        escape = probe.RFD_ESCAPE << 20
        aux = [
            tir(4),                                                  # 0: short (s16's type)
            tir(probe.BT_TYPEDEF, probe.TQ_ARRAY), escape | 0, 0,    # 1: s16 rows[33]
            escape | 0, 0, 0, 32, 16,
            tir(6, probe.TQ_PTR),                                    # 9: int *
            tir(6, probe.TQ_PTR, probe.TQ_ARRAY), escape | 0, 0, 0, 2, 32,  # 10: int *table[3]
            tir(probe.BT_STRUCT), escape | 1, 0,                     # 16: Pair
            tir(11),                                                 # 19: double
            tir(probe.BT_TYPEDEF), escape | 0, 7,                    # 20: a type from another file
        ]
        found = self.read([
            ('s16', 0, 10, 11, 0),
            ('Pair', 8, 26, 11, 0),
            ('func_A', 0, probe.ST_PROC, 1),
            ('', 0, probe.ST_BLOCK, 1),
            ('rows', -0x44, probe.ST_LOCAL, probe.SC_ABS, 1),
            ('pointer', -0x48, probe.ST_LOCAL, probe.SC_ABS, 9),
            ('table', -0x54, probe.ST_LOCAL, probe.SC_ABS, 10),
            ('pair', -0x5C, probe.ST_LOCAL, probe.SC_ABS, 16),
            ('value', -0x68, probe.ST_LOCAL, probe.SC_ABS, 19),
            ('foreign', -0x6C, probe.ST_LOCAL, probe.SC_ABS, 20),
            ('', 0, probe.ST_END, 1),
        ], aux)
        self.assertEqual(
            [('rows', 66, True), ('pointer', 4, False), ('table', 12, True), ('pair', 8, True),
             ('value', 8, False), ('foreign', None, False)],
            [(entry.name, entry.size, entry.aggregate) for entry in found],
        )

    def test_missing_mdebug_section_is_reported(self):
        header = bytearray(52)
        header[:6] = b'\x7fELF\x01\x02'
        struct.pack_into('>I', header, 0x20, 52)
        struct.pack_into('>HHH', header, 0x2E, 40, 2, 1)
        shstrtab = b'\0.shstrtab\0'
        sections = struct.pack('>10I', *([0] * 10))
        sections += struct.pack('>10I', 1, 3, 0, 0, 52 + 80, len(shstrtab), 0, 0, 1, 0)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'unit.o'
            path.write_bytes(bytes(header) + sections + shstrtab)
            with self.assertRaises(probe.ProbeError):
                probe.mdebug_locals(path, 'func_A')


LAYOUT_SOURCE = '''#include "types.h"

s32 func_A(s32 arg0) {
    s32 count;
    if (arg0) {
        return func_B(func_C(arg0));
    }
    return 0;
}
'''


class LayoutAccountTests(unittest.TestCase):
    def target(self, directory: Path) -> probe.Target:
        return probe.Target('func_A', 'us', Path('src/unit.c'), 'func_A', Path('ref.s'), Path('ref.o'), 8, directory)

    def test_function_body_spans_the_definition_braces(self):
        start, end = probe.function_body(LAYOUT_SOURCE, self.target(Path('.')))
        self.assertEqual('{', LAYOUT_SOURCE[start])
        self.assertEqual('}\n', LAYOUT_SOURCE[end:])

    def test_pad_probe_adds_one_block_local_and_reads_the_frame_change(self):
        with tempfile.TemporaryDirectory() as directory:
            candidate = Path(directory) / 'variant000.o'
            target = self.target(Path(directory))
            body = probe.function_body(LAYOUT_SOURCE, target)
            completed = mock.Mock(returncode=0)
            for frames, expected in (([0x40, 0x40], 1), ([0x40, 0x48], 0), ([0x40, 0x50], None)):
                with self.subTest(frames=frames), \
                        mock.patch.object(probe.compile_c, 'run_compile', return_value=completed), \
                        mock.patch.object(probe.frame_plan, 'object_frame_size', side_effect=frames):
                    self.assertEqual(expected, probe.pad_alignment(target, candidate, LAYOUT_SOURCE, body))
            padded = (Path(directory) / 'variant000-pad.c').read_text(encoding='utf-8')
        self.assertIn('    return 0;\n    { int conker_layout_pad; }\n}\n', padded)

    def test_failed_pad_compile_leaves_the_alignment_unknown(self):
        with tempfile.TemporaryDirectory() as directory:
            target = self.target(Path(directory))
            body = probe.function_body(LAYOUT_SOURCE, target)
            with mock.patch.object(probe.compile_c, 'run_compile', return_value=mock.Mock(returncode=1)):
                self.assertIsNone(probe.pad_alignment(target, Path(directory) / 'current.o', LAYOUT_SOURCE, body))

    def test_account_counts_call_arguments_in_the_candidate_source(self):
        sys.path.insert(0, str(ROOT / 'tests'))
        from test_frame_plan import crossing, framed

        candidate_plan = framed(0x28, ['sw $ra, 0x14($sp)'], crossing(0x24))
        reference = framed(0x20, ['sw $ra, 0x14($sp)'], crossing(0x1C))
        locals_ = [probe.Local('param', 'arg0', 0, 4), probe.Local('local', 'count', -4, 4),
                   probe.Local('local', 'extra', -8, 4)]
        with tempfile.TemporaryDirectory() as directory:
            candidate = Path(directory) / 'variant000.o'
            candidate.with_suffix('.c').write_text(LAYOUT_SOURCE, encoding='utf-8')
            with mock.patch.object(probe.frame_plan, 'object_plan', return_value=candidate_plan), \
                    mock.patch.object(probe, 'header_macros', return_value=frozenset()), \
                    mock.patch.object(probe, 'pad_alignment', return_value=1) as pad:
                lines = probe.account_lines(self.target(Path(directory)), candidate, locals_, reference)
        pad.assert_called_once()
        text = '\n'.join(lines)
        self.assertIn('call-arg temps 1 word (largest statement: return func_B(func_C(arg0)))', text)
        # A call-arg temp and an unused named home explain the surplus equally; the
        # call-arg temp ranks first and the named home is the alternative.
        self.assertIn('  candidate +2 words: 1 call-arg temp, 1 alignment', lines)
        self.assertIn('  or: 1 named, 1 alignment (extra)', lines)
        self.assertIn('  or: 1 named, 1 call-arg temp (extra)', lines)


class FrameParsingTests(unittest.TestCase):
    def test_reference_frame_uses_symbol_prologue(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'unit.s'
            path.write_text(
                'glabel func_A\n  /* 0 */ jr $ra\n  nop\n'
                'glabel func_B\n  /* 0 1 2 */ addiu      $sp, $sp, -0x100\n',
                encoding='utf-8',
            )
            self.assertEqual(0x100, probe.reference_frame_size(path, 'func_B'))
            self.assertIsNone(probe.reference_frame_size(path, 'func_A'))


if __name__ == '__main__':
    unittest.main()
