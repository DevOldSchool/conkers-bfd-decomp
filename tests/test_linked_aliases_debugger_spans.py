from __future__ import annotations

import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import linked_aliases
from candidate_tables import Object32
from test_linked_aliases_si import object_bytes

SYMBOL, START, SIZE, ORIGIN = "func_160019A8", 0x160019A8, 0xC4, 0x30
TAIL = ("func_16001A64", ORIGIN + 0xBC, 8, 1)
WORDS = [0x3C19A480, 0xAF220000] + [0] * 43 + [0x03E00008, 0, 0x03E00008, 0]
ROM = struct.pack(">49I", *WORDS)


def composed(*, primary=0xBC, tail=TAIL, extras=(), words=None, origin=ORIGIN):
    symbols = ([] if tail is None else [tail]) + list(extras)
    payload = bytearray(object_bytes([0] * (origin // 4) + (WORDS if words is None else words),
                                    origin=origin, size=primary, symbols=symbols, target=SYMBOL))
    obj = Object32(bytes(payload))
    for index in range(1, len(symbols) + 2):
        payload[obj.sections[3][4] + index * 16 + 12] = 0x12
    return bytes(payload)


def reference():
    words = WORDS.copy()
    words[0] &= 0xFFFF0000
    return object_bytes(words, size=SIZE, symbols=[("D_A4800000", 0, 0, 0)],
                        relocations=[(0, 5, "D_A4800000"), (4, 6, "D_A4800000")], target=SYMBOL)


class DebuggerSpanTests(unittest.TestCase):
    def test_ido_sized_text_section_metadata_is_not_an_overlapping_function(self):
        for length in (0, ORIGIN + SIZE):
            payload = bytearray(composed(extras=[(".text", 0, length, 1)]))
            obj = Object32(bytes(payload))
            offset = obj.sections[3][4] + 3 * 16
            payload[offset + 12] = 3
            self.assertTrue(linked_aliases.reviewed_empty_companion(
                Object32(bytes(payload)), SYMBOL, SIZE))
            for field, value, fmt in ((4, 4, ">I"), (8, SIZE, ">I"),
                                      (12, 0x13, ">B"), (13, 2, ">B")):
                changed = bytearray(payload)
                struct.pack_into(fmt, changed, offset + field, value)
                with self.subTest(length=length, field=field, value=value):
                    self.assertFalse(linked_aliases.reviewed_empty_companion(
                        Object32(bytes(changed)), SYMBOL, SIZE))

    def test_exact_companion_is_explicit_and_retains_complete_span(self):
        obj = Object32(composed())
        with self.assertRaisesRegex(ValueError, "extent"):
            linked_aliases.function(obj, SYMBOL, SIZE)
        self.assertEqual((ORIGIN, 1), linked_aliases.function(obj, SYMBOL, SIZE, empty_companion=True))
        self.assertEqual(ROM, obj.section(1)[ORIGIN:ORIGIN + SIZE])
        current, raw = obj, Object32(reference())
        self.assertTrue(linked_aliases.si_literal_equivalent(current, raw, SYMBOL, SIZE, empty_companion=True))
        self.assertEqual({}, linked_aliases.si_definitions(current, SYMBOL, START, SIZE, empty_companion=True))
        for symbol, size in (("func_160019A4", SIZE), (SYMBOL, SIZE - 4), (SYMBOL, SIZE + 4)):
            self.assertFalse(linked_aliases.reviewed_empty_companion(obj, symbol, size))

    def test_missing_misnamed_gap_overlap_extent_and_ambiguous_members_reject(self):
        malformed = [composed(tail=None), composed(tail=("func_16001A68", ORIGIN + 0xBC, 8, 1)),
                     composed(tail=(TAIL[0], ORIGIN + 0xB8, 8, 1)),
                     composed(tail=(TAIL[0], ORIGIN + 0xC0, 8, 1)),
                     composed(tail=(TAIL[0], ORIGIN + 0xBC, 4, 1)),
                     composed(tail=(TAIL[0], ORIGIN + 0xBC, 8, 2)),
                     composed(primary=0xB8), composed(primary=0xC0),
                     composed(extras=[TAIL]), composed(extras=[(SYMBOL, ORIGIN, 0xBC, 1)]),
                     composed(extras=[("func_16001A60", ORIGIN + 0xB8, 8, 1)]),
                     composed(extras=[("func_160019AC", ORIGIN + 4, 0, 1)]),
                     composed(extras=[("func_160019A4", ORIGIN - 4, 8, 1)]),
                     composed(words=WORDS[:-1])]
        for index, payload in enumerate(malformed):
            with self.subTest(case=index):
                with self.assertRaises(ValueError):
                    linked_aliases.function(Object32(payload), SYMBOL, SIZE, empty_companion=True)

    def test_malformed_symbol_kind_visibility_section_and_tail_relocations_reject(self):
        for symbol_index, field, value in ((1, 12, 0x11), (2, 12, 0x10), (2, 12, 0x02), (2, 13, 2)):
            payload = bytearray(composed())
            obj = Object32(bytes(payload))
            payload[obj.sections[3][4] + symbol_index * 16 + field] = value
            self.assertFalse(linked_aliases.reviewed_empty_companion(Object32(bytes(payload)), SYMBOL, SIZE))
        obj = Object32(composed())
        obj.sections[1] = (*obj.sections[1][:2], 3, *obj.sections[1][3:])
        self.assertFalse(linked_aliases.reviewed_empty_companion(obj, SYMBOL, SIZE))
        obj = Object32(composed())
        obj.relocations[(1, ORIGIN + 0xC0)] = (4, ("func_16001A64", ORIGIN + 0xBC, 8, 1))
        self.assertFalse(linked_aliases.reviewed_empty_companion(obj, SYMBOL, SIZE))
        for index in (-4, -3, -2, -1):
            words = WORDS.copy()
            words[index] ^= 1
            self.assertFalse(linked_aliases.reviewed_empty_companion(Object32(composed(words=words)), SYMBOL, SIZE))

    def prepare(self, *, overlay="debugger", start=START, candidate=None,
                current_bytes=ROM, raw_bytes=ROM):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            current, raw, asm = root / "candidate.o", root / "reference.o", root / "raw.s"
            current.write_bytes(composed() if candidate is None else candidate)
            raw.write_bytes(reference())
            asm.write_text("".join(f"/* {i*4:X} {START+i*4:08X} {word:08X} */ instruction\n"
                                   for i, word in enumerate(WORDS)))
            with patch.object(linked_aliases.rom_span, "code_image", return_value=(ROM, START, "checked")) as rom, \
                    patch.object(linked_aliases, "linked_span", side_effect=[raw_bytes, current_bytes]) as link:
                result = linked_aliases.prepare(root, current, raw, asm, SYMBOL, start, SIZE, overlay=overlay)
                return (tuple(p.read_bytes() for p in result) if result else None), link.call_args_list, rom.call_count

    def test_full_span_link_and_rom_checks_remain_mandatory(self):
        result, calls, count = self.prepare()
        self.assertIsNotNone(result)
        self.assertEqual(result[0], result[1])
        self.assertEqual((2, 1), (len(calls), count))
        self.assertTrue(calls[1].kwargs["empty_companion"])
        self.assertEqual([SIZE, SIZE], [call.args[4] for call in calls])
        obj = Object32(result[0])
        self.assertEqual(ROM, obj.section(1))
        for offset in (0, 0xBB, 0xBC, 0xC3):
            changed = bytearray(ROM)
            changed[offset] ^= 1
            self.assertIsNone(self.prepare(current_bytes=bytes(changed))[0])
        self.assertIsNone(self.prepare(current_bytes=ROM[:-4])[0])
        with self.assertRaisesRegex(ValueError, "raw-reference span differs"):
            self.prepare(raw_bytes=ROM[:-1] + b"\1")

    def test_linked_span_revalidates_companion_and_extracts_every_byte(self):
        obj = Object32(composed())
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "candidate"
            def command(arguments, **unused):
                if arguments[0] == "mips-linux-gnu-objcopy":
                    Path(arguments[-1]).write_bytes(obj.section(1))
            with patch.object(linked_aliases.subprocess, "run", side_effect=command) as run:
                result = linked_aliases.linked_span(Path("candidate.o"), obj, SYMBOL, START, SIZE,
                                                    {}, output, reference=False, empty_companion=True)
                self.assertEqual(ROM, result)
                self.assertEqual(2, run.call_count)
                self.assertIn(f".text 0x{START - ORIGIN:X}", output.with_suffix(".ld").read_text())
                with self.assertRaisesRegex(ValueError, "extent"):
                    linked_aliases.linked_span(Path("candidate.o"), Object32(composed(tail=None)),
                                               SYMBOL, START, SIZE, {}, output,
                                               reference=False, empty_companion=True)
                self.assertEqual(2, run.call_count)

    def test_game_wrong_canonical_start_and_missing_tail_never_link(self):
        for options in ({"overlay": "game"}, {"start": START + 4}, {"candidate": composed(tail=None)}):
            self.assertEqual((None, [], 0), self.prepare(**options))


class DebuggerAliasTests(unittest.TestCase):
    symbol, start, size, origin = "func_160018BC", 0x160018BC, 0xC8, 0x10
    words = [0x3C038004, 0x24632A50] + [0] * 46 + [0x03E00008, 0]
    rom = struct.pack(">50I", *words)

    def fixtures(self, *, inside=False, value=4, addend=0x40, register=3, kind=4):
        words = self.words.copy()
        words[0] = 0x3C000000 | register << 16
        words[1] = 0x24000000 | register << 21 | register << 16 | addend
        current = [0x0C000000, 0, 0, 0] + words
        call_offset = self.origin + 8 if inside else 0
        current[call_offset // 4] = 0x0C000000
        candidate = object_bytes(current, target=self.symbol, origin=self.origin, size=self.size,
                                 symbols=[("D_80042A10", 0, 0, 0), ("func_160012B0", value, 4, 1)],
                                 relocations=[(self.origin, 5, "D_80042A10"),
                                              (self.origin + 4, 6, "D_80042A10"),
                                              (call_offset, kind, "func_160012B0")])
        raw_words = self.words.copy()
        raw_words[0] &= 0xFFFF0000
        raw_words[1] &= 0xFFFF0000
        raw = object_bytes(raw_words, target=self.symbol, size=self.size,
                           symbols=[("D_80042A50", 0, 0, 0)],
                           relocations=[(0, 5, "D_80042A50"), (4, 6, "D_80042A50")])
        return candidate, raw

    def prepare(self, *, overlay="debugger", candidate=None, current_bytes=None):
        normal_candidate, normal_raw = self.fixtures()
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            current, raw, asm = root / "candidate.o", root / "reference.o", root / "raw.s"
            current.write_bytes(normal_candidate if candidate is None else candidate)
            raw.write_bytes(normal_raw)
            asm.write_text("".join(f"/* {i*4:X} {self.start+i*4:08X} {word:08X} */ instruction\n"
                                   for i, word in enumerate(self.words)))
            with patch.object(linked_aliases.rom_span, "code_image", return_value=(self.rom, self.start, "checked")) as rom, \
                    patch.object(linked_aliases, "linked_span", side_effect=[self.rom, self.rom if current_bytes is None else current_bytes]) as link:
                result = linked_aliases.prepare(root, current, raw, asm, self.symbol, self.start, self.size, overlay=overlay)
                return result is not None, link.call_args_list, rom.call_count

    def test_debugger_two_sided_end_alias_keeps_compacted_calls_natural(self):
        accepted, calls, count = self.prepare()
        self.assertTrue(accepted)
        self.assertEqual({"D_80042A10": 0x80042A10}, calls[1].args[5])
        self.assertEqual((2, 1), (len(calls), count))
        self.assertEqual((False, [], 0), self.prepare(overlay="game"))

    def test_debugger_alias_wrong_inspan_target_or_defined_relocation_kind_declines(self):
        for arguments in ({"inside": True}, {"kind": 5}, {"value": 0xFFFF}):
            candidate, _ = self.fixtures(**arguments)
            self.assertEqual((False, [], 0), self.prepare(candidate=candidate))
        candidate, _ = self.fixtures()
        payload = bytearray(candidate)
        obj = Object32(candidate)
        struct.pack_into(">I", payload, obj.sections[3][4] + 16 + 8, self.size - 4)
        self.assertEqual((False, [], 0), self.prepare(candidate=bytes(payload)))

    def test_alias_register_addend_and_final_byte_errors_cannot_match(self):
        # Eligibility is not acceptance: independently linked byte differences
        # (including a wrong alias addend) must still reject the whole span.
        for arguments, byte_offset in (({"addend": 0x44}, 7), ({"register": 4}, 3), ({}, self.size - 1)):
            candidate, _ = self.fixtures(**arguments)
            changed = bytearray(self.rom)
            changed[byte_offset] ^= 1
            self.assertFalse(self.prepare(candidate=candidate, current_bytes=bytes(changed))[0])


if __name__ == "__main__":
    unittest.main()
