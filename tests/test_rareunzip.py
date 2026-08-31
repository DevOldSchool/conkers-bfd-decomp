from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
import zlib
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location("rareunzip", ROOT / "tools" / "third_party" / "rareunzip.py")
assert SPEC is not None and SPEC.loader is not None
rareunzip = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(rareunzip)


def rzip_chunk(data: bytes) -> bytes:
    return len(data).to_bytes(4, "big") + zlib.compress(data, wbits=-15)


class RareUnzipTests(unittest.TestCase):
    def test_decompresses_a_raw_deflate_rzip_chunk(self) -> None:
        self.assertEqual(b"Conker", rareunzip.runzip(rzip_chunk(b"Conker")))

    def test_reports_bytes_after_the_deflate_stream(self) -> None:
        result, leftovers = rareunzip.runzip_with_leftovers(rzip_chunk(b"game") + b"next-chunk")
        self.assertEqual(b"game", result)
        self.assertEqual(b"next-chunk", leftovers)

    def test_cli_accepts_the_rare_two_byte_wrapper(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "input.rzip"
            destination = root / "output.bin"
            source.write_bytes(b"\x11\x72" + rzip_chunk(b"payload"))
            original_argv = sys.argv
            try:
                sys.argv = ["rareunzip.py", str(source), str(destination)]
                self.assertEqual(0, rareunzip.main())
            finally:
                sys.argv = original_argv
            self.assertEqual(b"payload", destination.read_bytes())
