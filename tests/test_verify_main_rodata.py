from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import verify_main_rodata as verifier


def image(*, name=verifier.SECTION_NAME, flags=0, address=verifier.SECTION_VRAM,
          size=verifier.SECTION_SIZE, duplicate=False, include=True):
    names = b"\0.shstrtab\0" + name.encode() + b"\0"
    data_offset = 52 + len(names)
    payload = bytes(range(32))
    section_offset = data_offset + len(payload)
    sections = [(0,) * 10, (1, 3, 0, 0, 52, len(names), 0, 0, 1, 0)]
    if include:
        sections.append((11, 1, flags, address, data_offset, size, 0, 0, 4, 0))
    if duplicate:
        sections.append(sections[-1])
    header = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                         2, 8, 1, 0, 0, section_offset, 0, 52, 0, 0, 40, len(sections), 1)
    return header + names + payload + b"".join(struct.pack(">10I", *s) for s in sections)


class MainRodataTests(unittest.TestCase):
    def test_reviewed_info_payload(self):
        self.assertEqual(verifier.external_payload(image()), bytes(range(32)))

    def test_missing_and_duplicate_tables(self):
        for blob in [image(include=False), image(duplicate=True)]:
            with self.subTest(blob_size=len(blob)), self.assertRaises(ValueError):
                verifier.external_payload(blob)

    def test_unreviewed_table(self):
        with self.assertRaisesRegex(ValueError, "unreviewed"):
            verifier.external_payload(image(name=".main_rodata_other"))

    def test_allocated_or_writable_sections_rejected(self):
        for flags in [1, 2, 3, 4]:
            with self.subTest(flags=flags), self.assertRaisesRegex(ValueError, "non-allocated read-only"):
                verifier.external_payload(image(flags=flags))

    def test_wrong_address_or_extent_rejected(self):
        for blob in [image(address=verifier.SECTION_VRAM + 4), image(size=28), image(size=36)]:
            with self.subTest(blob_size=len(blob)), self.assertRaisesRegex(ValueError, "mapping"):
                verifier.external_payload(blob)

    def test_truncated_headers_and_sections(self):
        blob = image()
        for length in [0, 51, 52, len(blob) - 1]:
            with self.subTest(length=length), self.assertRaises(ValueError):
                verifier.external_payload(blob[:length])

    def test_unsupported_elf_identity(self):
        for at, value in [(0, 0), (4, 2), (5, 1), (17, 1), (19, 3)]:
            blob = bytearray(image()); blob[at] = value
            with self.subTest(at=at), self.assertRaises(ValueError):
                verifier.external_payload(bytes(blob))

    def test_full_payload_and_padding_compared(self):
        linked = bytes(range(32))
        rom = bytes(verifier.ROM_START) + linked
        verifier.verify_bytes(linked, rom)
        for at in [0, 27, 28, 31]:
            changed = bytearray(linked); changed[at] ^= 1
            with self.subTest(at=at), self.assertRaisesRegex(ValueError, "differs"):
                verifier.verify_bytes(bytes(changed), rom)

    def test_truncated_rom_and_wrong_payload_size(self):
        for linked, rom in [(bytes(32), bytes(verifier.ROM_START + 31)), (bytes(28), bytes(verifier.ROM_START + 32))]:
            with self.subTest(length=len(linked)), self.assertRaises(ValueError):
                verifier.verify_bytes(linked, rom)


SELECTOR = ".main_rodata_init_11fa0"


def image_sections(entries):
    names = bytearray(b"\0.shstrtab\0")
    starts = []
    for name, flags, address, payload in entries:
        starts.append(len(names))
        names.extend(name.encode() + b"\0")
    data = bytearray(52) + names
    sections = [(0,) * 10, (1, 3, 0, 0, 52, len(names), 0, 0, 1, 0)]
    for start, (_, flags, address, payload) in zip(starts, entries):
        sections.append((start, 1, flags, address, len(data), len(payload), 0, 0, 4, 0))
        data.extend(payload)
    table_offset = len(data)
    for section in sections:
        data.extend(struct.pack(">10I", *section))
    struct.pack_into(">16sHHIIIIIHHHHHH", data, 0,
                     b"\x7fELF\x01\x02\x01" + bytes(9), 2, 8, 1, 0, 0,
                     table_offset, 0, 52, 0, 0, 40, len(sections), 1)
    return bytes(data)


class MainSelectorRodataTests(unittest.TestCase):
    def setUp(self):
        self.queue = (verifier.SECTION_NAME, 0, verifier.SECTION_VRAM, bytes(range(32)))
        self.selector = (SELECTOR, 0, 0x8002C410, bytes(range(64)))
        self.required = (verifier.SECTION_NAME, SELECTOR)

    def test_both_reviewed_sections_and_selector_only(self):
        self.assertEqual(verifier.external_payloads(image_sections([self.queue, self.selector]), self.required),
                         {self.queue[0]: self.queue[3], self.selector[0]: self.selector[3]})
        self.assertEqual(verifier.external_payloads(image_sections([self.selector]), (SELECTOR,)),
                         {SELECTOR: self.selector[3]})

    def test_missing_duplicate_and_unrequested_selector_rejected(self):
        for entries, required in [([self.queue], self.required),
                                  ([self.queue, self.selector, self.selector], self.required),
                                  ([self.queue, self.selector], (verifier.SECTION_NAME,))]:
            with self.subTest(entries=len(entries), required=required), self.assertRaises(ValueError):
                verifier.external_payloads(image_sections(entries), required)

    def test_selector_address_extent_and_flags_fail_closed(self):
        for flags, address, payload in [(1, 0x8002C410, bytes(64)),
                                        (2, 0x8002C410, bytes(64)),
                                        (0, 0x8002C414, bytes(64)),
                                        (0, 0x8002C410, bytes(60))]:
            with self.subTest(flags=flags, address=address, size=len(payload)), self.assertRaises(ValueError):
                verifier.external_payloads(image_sections([(SELECTOR, flags, address, payload)]), (SELECTOR,))

    def test_every_selector_table_literal_and_padding_byte_is_checked(self):
        payload = self.selector[3]
        rom = bytes(0x2C410) + payload
        verifier.verify_bytes(payload, rom, SELECTOR)
        for at in range(64):
            changed = bytearray(payload)
            changed[at] ^= 1
            with self.subTest(at=at), self.assertRaisesRegex(ValueError, "differs"):
                verifier.verify_bytes(bytes(changed), rom, SELECTOR)

    def test_invalid_required_section_lists_rejected(self):
        for required in [(), (SELECTOR, SELECTOR), (".main_rodata_unknown",)]:
            with self.subTest(required=required), self.assertRaises(ValueError):
                verifier.external_payloads(image_sections([self.selector]), required)


class MainSchedulerRodataTests(unittest.TestCase):
    def setUp(self):
        self.name = ".main_rodata_init_49e0"
        self.payload = bytes(range(32))
        self.scheduler = (self.name, 0, 0x8002C0A0, self.payload)
        self.other = [(verifier.SECTION_NAME, 0, verifier.SECTION_VRAM, bytes(32)),
                      (SELECTOR, 0, 0x8002C410, bytes(64))]

    def test_scheduler_only_and_all_reviewed_pools(self):
        self.assertEqual(verifier.external_payloads(image_sections([self.scheduler]), (self.name,)),
                         {self.name: self.payload})
        entries = self.other + [self.scheduler]
        required = tuple(entry[0] for entry in entries)
        self.assertEqual(verifier.external_payloads(image_sections(entries), required),
                         {entry[0]: entry[3] for entry in entries})

    def test_missing_duplicate_unrequested_and_invalid_scheduler_mapping(self):
        invalid = [(self.name, flags, address, bytes(size))
                   for flags, address, size in [(1, 0x8002C0A0, 32), (2, 0x8002C0A0, 32),
                                                (0, 0x8002C0A4, 32), (0, 0x8002C0A0, 28),
                                                (0, 0x8002C0A0, 36)]]
        for entry in invalid:
            with self.subTest(entry=entry[:3]), self.assertRaises(ValueError):
                verifier.external_payloads(image_sections([entry]), (self.name,))
        for entries, required in [([], (self.name,)),
                                  ([self.scheduler, self.scheduler], (self.name,)),
                                  ([self.other[0], self.scheduler], (verifier.SECTION_NAME,))]:
            with self.subTest(entries=len(entries), required=required), self.assertRaises(ValueError):
                verifier.external_payloads(image_sections(entries), required)

    def test_every_scheduler_pointer_and_padding_byte_is_checked(self):
        rom = bytes(0x2C0A0) + self.payload
        verifier.verify_bytes(self.payload, rom, self.name)
        for at in range(32):
            changed = bytearray(self.payload)
            changed[at] ^= 1
            with self.subTest(at=at), self.assertRaisesRegex(ValueError, "differs"):
                verifier.verify_bytes(bytes(changed), rom, self.name)


if __name__ == "__main__":
    unittest.main()
