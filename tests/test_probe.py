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
    def run_main(self, outcomes):
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
                redirect_stdout(stdout), redirect_stderr(stderr):
            status = probe.main()
        return status, stdout.getvalue(), stderr.getvalue()

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


def mdebug_object(symbols: list[tuple[str, int, int, int]]) -> bytes:
    """Build a minimal big-endian ELF32 with an IDO-style .mdebug symbol table."""

    strings = b''
    entries = b''
    for name, value, st, sc in symbols:
        iss = len(strings)
        strings += name.encode() + b'\0'
        entries += struct.pack('>iiI', iss, value, (st << 26) | (sc << 21))
    shstrtab = b'\0.shstrtab\0.mdebug\0'
    elf_header_size = 52
    mdebug_offset = elf_header_size
    symbols_offset = mdebug_offset + 0x60
    strings_offset = symbols_offset + len(entries)
    fields = [0] * 23
    fields[7], fields[8] = len(symbols), symbols_offset
    fields[14] = strings_offset
    mdebug = struct.pack('>hh' + 'i' * 23, 0x7009, 0, *fields) + entries + strings
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
