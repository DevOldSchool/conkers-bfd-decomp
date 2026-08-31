from __future__ import annotations

import importlib.util
import struct
import unittest
import zlib
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location("extract_game_code", ROOT / "scripts" / "extract_game_code.py")
assert SPEC is not None and SPEC.loader is not None
extract_game_code = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(extract_game_code)


class ExtractGameCodeTests(unittest.TestCase):
    def test_extracts_concatenated_code_chunks(self) -> None:
        key = extract_game_code.OFFSET_XOR
        first = 0x20
        second = 0x30
        end = 0x40
        compressed_one = struct.pack(">I", 2) + zlib.compress(b"AB", wbits=-15)
        compressed_two = struct.pack(">I", 2) + zlib.compress(b"CD", wbits=-15)
        payload = bytearray(end)
        struct.pack_into(">I", payload, 4, key ^ first)
        struct.pack_into(">I", payload, 8, key ^ second)
        struct.pack_into(">I", payload, 12, key ^ end)
        payload[first : first + len(compressed_one)] = compressed_one
        payload[second : second + len(compressed_two)] = compressed_two
        original_layout = extract_game_code.RZIP_LAYOUTS["us"]
        try:
            extract_game_code.RZIP_LAYOUTS["us"] = {
                "start": 0,
                "end": len(payload),
                "code_end": end,
            }
            self.assertEqual(extract_game_code.extract_code(bytes(payload), "us"), b"ABCD")
        finally:
            extract_game_code.RZIP_LAYOUTS["us"] = original_layout
