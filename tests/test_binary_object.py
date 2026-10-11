"""Check the in-process writer against `ld -r -b binary` and its batch command."""
from __future__ import annotations

import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
import binary_object

LD = shutil.which('mips-linux-gnu-ld')
# Names whose three symbols land in different BFD hash-bucket orders.
NAMES = ('flat/textures/0007.bin', 'flat/textures/t-00a.bin', 'font/glyphs/0000.bin',
         'audio/bank17/samples/0003/000000.bin', 'models/bank09/0123.bin',
         'audio/mp3/streams/0000.bin', 'assets/asset_bank_0a.bin')


class BinaryObjectTests(unittest.TestCase):
    def test_payload_and_symbols(self):
        data = b'\x01\x02\x03\x04\x05'
        result = binary_object.binary_object(data, 'flat/textures/t-00a.bin')
        self.assertEqual(result[:4], b'\x7fELF')
        self.assertEqual(result[0x34:0x39], data)
        for suffix in (b'_start', b'_end', b'_size'):
            self.assertIn(b'\0_binary_flat_textures_t_00a_bin' + suffix + b'\0', result)

    @unittest.skipUnless(LD, 'requires mips-linux-gnu-ld')
    def test_objects_match_gnu_ld_byte_for_byte(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for index, name in enumerate(NAMES):
                for size in (0, 1, 3, 4, 37):
                    with self.subTest(name=name, size=size):
                        data = bytes((index * 31 + offset) & 0xFF for offset in range(size))
                        source = root / name
                        source.parent.mkdir(parents=True, exist_ok=True)
                        source.write_bytes(data)
                        subprocess.run([LD, '-r', '-b', 'binary', '-m', 'elf32btsmip', '-o', 'out.o', name],
                                       cwd=root, check=True)
                        self.assertEqual(binary_object.binary_object(data, name), (root / 'out.o').read_bytes())

    def test_command_writes_missing_and_changed_objects_only(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for name in ('a/0000.bin', 'a/0001.bin'):
                (root / 'parts' / name).parent.mkdir(parents=True, exist_ok=True)
                (root / 'parts' / name).write_bytes(name.encode())
            (root / 'names').write_text('a/0000.bin\na/0001.bin\n')

            def run(*extra):
                return subprocess.run([sys.executable, str(ROOT / 'scripts/binary_object.py'),
                                       '--root', 'parts', '--output-root', 'out', '--names-from', 'names', *extra],
                                      cwd=root, text=True, capture_output=True)

            first = run()
            self.assertEqual(first.returncode, 0, first.stderr)
            objects = [root / 'out/a/0000.o', root / 'out/a/0001.o']
            self.assertEqual(first.stderr.count('binary_object '), 2)
            before = [path.stat().st_mtime_ns for path in objects]
            self.assertEqual(run().stderr, '')
            self.assertEqual([path.stat().st_mtime_ns for path in objects], before)

            # An object older than an unchanged part only has its timestamp refreshed.
            os.utime(objects[0], ns=(1_000_000_000, 1_000_000_000))
            self.assertEqual(run().stderr, '')
            self.assertGreaterEqual(objects[0].stat().st_mtime_ns,
                                    (root / 'parts/a/0000.bin').stat().st_mtime_ns)
            (root / 'parts/a/0001.bin').write_bytes(b'changed')
            os.utime(objects[1], ns=(1_000_000_000, 1_000_000_000))
            result = run()
            self.assertIn('-> out/a/0001.o', result.stderr)
            self.assertEqual(objects[1].read_bytes(), binary_object.binary_object(b'changed', 'a/0001.bin'))

    def test_strip_prefix_keeps_symbol_names(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / 'assets').mkdir()
            (root / 'assets/boot.bin').write_bytes(b'boot')
            result = subprocess.run([sys.executable, str(ROOT / 'scripts/binary_object.py'), '--root', '.',
                                     '--strip-prefix', 'assets/', '--output-root', 'out', 'assets/boot.bin'],
                                    cwd=root, text=True, capture_output=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual((root / 'out/boot.o').read_bytes(),
                             binary_object.binary_object(b'boot', 'assets/boot.bin'))


if __name__ == '__main__':
    unittest.main()
