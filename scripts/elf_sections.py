"""Strict section reader shared by reviewed ROM-backed data verifiers."""
from __future__ import annotations
import struct


def sections(data: bytes, elf_type: int) -> dict[str, tuple[tuple[int, ...], bytes]]:
    def read(offset: int, length: int) -> bytes:
        if offset < 0 or length < 0 or offset + length > len(data):
            raise ValueError("truncated storage ELF")
        return data[offset:offset + length]

    h = struct.unpack(">16sHHIIIIIHHHHHH", read(0, 52))
    if (h[0][:7] != b"\x7fELF\x01\x02\x01" or h[1:4] != (elf_type, 8, 1)
            or h[8] != 52 or h[6] < 52 or h[11] != 40 or not 0 < h[13] < h[12]):
        raise ValueError("unsupported storage ELF")
    table = read(h[6], h[12] * 40)
    entries = [struct.unpack_from(">10I", table, i * 40) for i in range(h[12])]
    strings = entries[h[13]]
    if strings[1] != 3:
        raise ValueError("invalid ELF section-name table")
    names = read(strings[4], strings[5])
    result = {}
    for s in entries[1:]:
        end = names.find(b"\0", s[0])
        if not 0 <= s[0] < len(names) or end < s[0]:
            raise ValueError("invalid ELF section name")
        name = names[s[0]:end].decode("ascii")
        if name in result:
            raise ValueError("duplicate ELF section")
        payload = b"" if s[1] == 8 else read(s[4], s[5])
        result[name] = (s, payload)
    return result
