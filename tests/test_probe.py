from __future__ import annotations

from pathlib import Path
import struct
import sys
import tempfile
import unittest

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_10000010 CURRENT (4) */
s32 func_10000010(void) {
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_10000010 */
#pragma GLOBAL_ASM("asm/nonmatchings/unit/func_10000010.s")
s32 func_10000020(s32 arg0) {
    return arg0;
}
'''


class DefinitionSpanTests(unittest.TestCase):
    def test_finds_complete_definition_with_nested_braces_and_comment_brace(self):
        start, end = probe.definition_span(SOURCE, 'func_10000000')
        body = SOURCE[start:end]
        self.assertTrue(body.startswith('void func_10000000(void *arg0) {'))
        self.assertTrue(body.endswith('}\n'))
        self.assertIn('D_1 = 1;', body)

    def test_ignores_preserved_deferred_candidate(self):
        self.assertIsNone(probe.definition_span(SOURCE, 'func_10000010'))

    def test_prototype_is_not_a_definition(self):
        self.assertIsNone(probe.definition_span('s32 func_10000030(s32);\n', 'func_10000030'))


class SpliceVariantTests(unittest.TestCase):
    def test_replaces_existing_definition_in_place(self):
        variant = 'void func_10000000(void *arg0) {\n    D_1 = 2;\n}\n'
        result = probe.splice_variant(SOURCE, 'func_10000000', variant)
        self.assertIn('D_1 = 2;', result)
        self.assertNotIn('D_1 = 1;', result)
        self.assertLess(result.index('D_1 = 2;'), result.index('#if 0'))

    def test_replaces_global_asm_pragma_and_keeps_helper_declarations(self):
        variant = 'extern s32 D_2;\n\ns32 func_10000010(void) {\n    return D_2;\n}\n'
        result = probe.splice_variant(SOURCE, 'func_10000010', variant)
        self.assertNotIn('func_10000010.s', result)
        self.assertIn('extern s32 D_2;', result)
        self.assertIn('#if 0 /* CONKER_DEFERRED_CANDIDATE func_10000010', result)
        self.assertLess(result.index('return D_2;'), result.index('s32 func_10000020'))

    def test_complete_source_variant_is_used_verbatim(self):
        variant = '#include "types.h"\nvoid func_10000000(void) {\n}\n'
        self.assertEqual(variant, probe.splice_variant(SOURCE, 'func_10000000', variant))

    def test_variant_must_define_the_symbol(self):
        with self.assertRaises(probe.ProbeError):
            probe.splice_variant(SOURCE, 'func_10000000', 'void other(void) {\n}\n')

    def test_missing_definition_and_pragma_is_rejected(self):
        with self.assertRaises(probe.ProbeError):
            probe.splice_variant('s32 x;\n', 'func_10000000', 'void func_10000000(void) {\n}\n')


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
