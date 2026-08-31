from __future__ import annotations

import importlib.util
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location("first_diff", ROOT / "scripts" / "first_diff.py")
assert SPEC is not None and SPEC.loader is not None
first_diff = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(first_diff)


class FirstDiffTests(unittest.TestCase):
    def test_reports_first_changed_byte(self) -> None:
        self.assertEqual(first_diff.first_difference(b"\x00\x01\x02", b"\x00\x03\x02"), 1)

    def test_reports_length_difference(self) -> None:
        self.assertEqual(first_diff.first_difference(b"\x00", b"\x00\x01"), 1)

    def test_formats_full_words(self) -> None:
        self.assertEqual(first_diff.format_words(b"\x12\x34\x56\x78"), "12345678")
