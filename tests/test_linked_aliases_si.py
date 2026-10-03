from __future__ import annotations

import struct
import sys
import tempfile
import unittest
from contextlib import nullcontext
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import linked_aliases
from candidate_tables import Object32


SYMBOL = "func_16001984"
START = 0x16001984
SIZE = 0x24
ORIGIN = 0x10
WORDS = [0x3C0EA480, 0x8DC20018, 0x304F0003, 0x11E00003, 0x00001025,
         0x03E00008, 0x24020001, 0x03E00008, 0]
ROM = struct.pack(">9I", *WORDS)


def object_bytes(words, *, origin=0, size=SIZE, symbols=(), relocations=(), target=SYMBOL):
    names = bytearray(b"\0")
    entries = [(target, origin, size, 1), *symbols]
    symdata = bytearray(16)
    indices = {}
    for index, (name, value, extent, section) in enumerate(entries, 1):
        name_offset = len(names)
        names.extend(name.encode() + b"\0")
        symdata.extend(struct.pack(">IIIBBH", name_offset, value, extent, 0x10, 0, section))
        indices[name] = index
    relocs = b"".join(struct.pack(">II", offset, indices[name] << 8 | kind)
                      for offset, kind, name in relocations)
    section_names = b"\0.text\0.data\0.symtab\0.strtab\0.rel.text\0.shstrtab\0"
    contents = [("", 0, 0, b"", 0, 0, 0),
                (".text", 1, 6, struct.pack(">" + "I" * len(words), *words), 0, 0, 0),
                (".data", 1, 3, bytes(4), 0, 0, 0),
                (".symtab", 2, 0, bytes(symdata), 4, 1, 16),
                (".strtab", 3, 0, bytes(names), 0, 0, 0),
                (".rel.text", 9, 0, relocs, 3, 1, 8),
                (".shstrtab", 3, 0, section_names, 0, 0, 0)]
    body = bytearray(52)
    sections = []
    for name, kind, flags, payload, link, info, entry_size in contents:
        body.extend(bytes(-len(body) % 4))
        name_offset = section_names.find(name.encode() + b"\0") if name else 0
        sections.append(struct.pack(">10I", name_offset, kind, flags, 0, len(body),
                                    len(payload), link, info, 4, entry_size))
        body.extend(payload)
    body.extend(bytes(-len(body) % 4))
    section_offset = len(body)
    body.extend(b"".join(sections))
    body[:52] = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                           1, 8, 1, 0, 0, section_offset, 0, 52, 0, 0, 40, len(sections), 6)
    return bytes(body)


def pair(*, address=0xA4800018, store=False, outside_call=False):
    words = WORDS.copy()
    words[1] = (0xADC20000 if store else 0x8DC20000) | (address & 0xFFFF)
    current = [0] * 4 + words + [0] * 11
    symbols, relocations = [], []
    if outside_call:
        current[0] = 0x0C000000
        symbols.append(("func_160012B0", 4, 4, 1))
        relocations.append((0, 4, "func_160012B0"))
    candidate = object_bytes(current, origin=ORIGIN, symbols=symbols, relocations=relocations)
    words[0] &= 0xFFFF0000
    words[1] &= 0xFFFF0000
    name = f"D_{address:08X}"
    reference = object_bytes(words, symbols=[(name, 0, 0, 0)],
                             relocations=[(0, 5, name), (4, 6, name)])
    return candidate, reference


class SiLiteralTests(unittest.TestCase):
    def test_exact_four_si_addresses_loads_and_stores_are_eligible(self):
        for address in (0xA4800000, 0xA4800004, 0xA4800010, 0xA4800018):
            for store in (False, True):
                current, raw = map(Object32, pair(address=address, store=store))
                self.assertTrue(linked_aliases.si_literal_equivalent(current, raw, SYMBOL, SIZE))

    def test_unknown_address_operand_changes_and_candidate_relocation_decline(self):
        current, raw = map(Object32, pair(address=0xA4800020))
        self.assertFalse(linked_aliases.si_literal_equivalent(current, raw, SYMBOL, SIZE))
        for relative, xor in ((0, 1), (0, 0x10000), (4, 4), (4, 0x200000), (4, 0x40000000)):
            candidate, reference = pair()
            current, raw = Object32(candidate), Object32(reference)
            start = current.sections[1][4] + ORIGIN + relative
            changed = bytearray(candidate)
            struct.pack_into(">I", changed, start, struct.unpack_from(">I", changed, start)[0] ^ xor)
            self.assertFalse(linked_aliases.si_literal_equivalent(Object32(bytes(changed)), raw, SYMBOL, SIZE))
        current, raw = map(Object32, pair())
        current.relocations[(1, ORIGIN)] = raw.relocations[(1, 0)]
        self.assertFalse(linked_aliases.si_literal_equivalent(current, raw, SYMBOL, SIZE))

    def test_orphan_reversed_ambiguous_or_nonzero_addend_reference_declines(self):
        for change in ("orphan", "reversed", "duplicate", "addend"):
            current, raw = map(Object32, pair())
            if change == "orphan":
                del raw.relocations[(1, 4)]
            elif change == "reversed":
                raw.relocations[(1, 0)], raw.relocations[(1, 4)] = raw.relocations[(1, 4)], raw.relocations[(1, 0)]
            elif change == "duplicate":
                raw.relocations[(1, 8)] = raw.relocations[(1, 4)]
            else:
                payload = bytearray(raw.data)
                offset = raw.sections[1][4] + 4
                struct.pack_into(">I", payload, offset, raw.word(1, 4) | 4)
                raw = Object32(bytes(payload))
            with self.subTest(change=change):
                self.assertFalse(linked_aliases.si_literal_equivalent(current, raw, SYMBOL, SIZE))

    def test_outside_compacted_call_stays_defined_and_unassigned(self):
        current, _ = map(Object32, pair(outside_call=True))
        self.assertIsNone(linked_aliases.definitions(current))
        self.assertEqual({}, linked_aliases.si_definitions(current, SYMBOL, START, SIZE))

    def test_defined_in_span_call_requires_natural_address_and_zero_addend(self):
        callee = "func_160019B4"
        for value, addend, accepted in ((0x40, 0, True), (0x44, 0, False), (0x40, 1, False)):
            words = [0] * 24
            words[ORIGIN // 4 + 2] = 0x0C000000 | addend
            obj = Object32(object_bytes(words, origin=ORIGIN, symbols=[(callee, value, 4, 1)],
                                       relocations=[(ORIGIN + 8, 4, callee)]))
            result = linked_aliases.si_definitions(obj, SYMBOL, START, SIZE)
            self.assertEqual({} if accepted else None, result)

    def test_unknown_local_data_noncalls_and_name_collisions_still_decline(self):
        for symbols, kind, opcode in (([("unknown", 0, 0, 0)], 4, 0x0C000000),
                                      ([("D_160038A0", 0, 4, 2)], 5, 0x3C0E0000),
                                      ([("func_160012B0", 4, 4, 1)], 4, 0x08000000),
                                      ([("func_160012B0", 4, 4, 1),
                                        ("func_160012B0", 0, 0, 0)], 4, 0x0C000000)):
            words = [opcode] + [0] * 23
            obj = Object32(object_bytes(words, origin=ORIGIN, symbols=symbols,
                                       relocations=[(0, kind, symbols[-1][0])]))
            self.assertIsNone(linked_aliases.si_definitions(obj, SYMBOL, START, SIZE))

    def prepare_fixture(self, *, overlay="debugger", current_bytes=ROM, raw_bytes=ROM,
                        candidate=None, raw=None, force_old=None):
        normal_candidate, normal_raw = pair(outside_call=True)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            candidate_path, reference_path, asm = root / "candidate.o", root / "reference.o", root / "raw.s"
            candidate_path.write_bytes(normal_candidate if candidate is None else candidate)
            reference_path.write_bytes(normal_raw if raw is None else raw)
            asm.write_text("".join(f"/* {i * 4:X} {START + i * 4:08X} {word:08X} */ instruction\n"
                                   for i, word in enumerate(WORDS)))
            with patch.object(linked_aliases.rom_span, "code_image", return_value=(ROM, START, "checked")) as rom, \
                    patch.object(linked_aliases, "linked_span", side_effect=[raw_bytes, current_bytes]) as link, \
                    (nullcontext() if force_old is None else patch.object(linked_aliases, "address_alias_present", return_value=force_old)), \
                    patch.object(linked_aliases, "si_literal_equivalent", wraps=linked_aliases.si_literal_equivalent) as si:
                result = linked_aliases.prepare(root, candidate_path, reference_path, asm,
                                                SYMBOL, START, SIZE, overlay=overlay)
                payloads = tuple(path.read_bytes() for path in result) if result else None
                return payloads, link.call_args_list, rom.call_count, si.call_count

    def test_success_requires_linked_reference_and_complete_candidate_equality(self):
        result, calls, rom_count, si_count = self.prepare_fixture()
        self.assertIsNotNone(result)
        self.assertEqual(result[0], result[1])
        obj = Object32(result[0])
        origin, section = linked_aliases.function(obj, SYMBOL, SIZE)
        self.assertEqual(ROM, obj.section(section)[origin:origin + SIZE])
        self.assertEqual(2, len(calls))
        self.assertEqual({}, calls[1].args[5])
        self.assertEqual((1, 1), (rom_count, si_count))
        for position in (0, len(ROM) - 1):
            changed = bytearray(ROM)
            changed[position] ^= 1
            result, _, _, _ = self.prepare_fixture(current_bytes=bytes(changed))
            self.assertIsNone(result)
        with self.assertRaisesRegex(ValueError, "raw-reference span differs"):
            self.prepare_fixture(raw_bytes=ROM[:-1] + b"\1")

    def test_extent_mismatch_and_non_debugger_never_reach_linking(self):
        candidate, raw = pair()
        obj = Object32(candidate)
        changed = bytearray(candidate)
        # Target is symbol entry1; st_size is at entry offset8.
        struct.pack_into(">I", changed, obj.sections[3][4] + 16 + 8, SIZE - 4)
        result, calls, rom_count, _ = self.prepare_fixture(candidate=bytes(changed), raw=raw)
        self.assertIsNone(result)
        self.assertEqual(([], 0), (calls, rom_count))
        result, calls, rom_count, si_count = self.prepare_fixture(overlay="game")
        self.assertEqual((None, [], 0, 0), (result, calls, rom_count, si_count))

    def test_existing_two_sided_alias_proof_remains_unchanged(self):
        words = WORDS.copy()
        words[0] &= 0xFFFF0000
        candidate = object_bytes(words, symbols=[("D_A4800000", 0, 0, 0)],
                                 relocations=[(0, 5, "D_A4800000"), (4, 6, "D_A4800000")])
        result, calls, rom_count, si_count = self.prepare_fixture(candidate=candidate)
        self.assertIsNotNone(result)
        self.assertEqual({"D_A4800000": 0xA4800000}, calls[1].args[5])
        self.assertEqual((1, 0), (rom_count, si_count))

    def test_existing_alias_path_retains_its_defined_symbol_rejection(self):
        result, calls, rom_count, si_count = self.prepare_fixture(force_old=True, overlay="game")
        self.assertEqual((None, [], 0, 0), (result, calls, rom_count, si_count))


if __name__ == "__main__":
    unittest.main()
