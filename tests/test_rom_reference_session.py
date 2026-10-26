"""Report reference reuse must be bounded to stable files and one invocation."""
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import rzip_archive as archive


class ReferenceSessionTests(unittest.TestCase):
    def test_reuses_reads_hashes_and_archive_only_inside_session(self):
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'rom.z64'
            path.write_bytes(archive.Z64_MAGIC + bytes(16))
            with patch.object(archive, 'normalize_rom', wraps=archive.normalize_rom) as normalize, \
                    patch.object(archive, 'parse_game_archive', return_value='game') as parse, \
                    patch.object(archive.hashlib, 'sha1', wraps=archive.hashlib.sha1) as digest:
                for _ in range(2):
                    with archive.reference_session():
                        rom, _ = archive.read_rom(path)
                        self.assertIs(archive.read_rom(path)[0], rom)
                        archive.rom_sha1(rom); archive.rom_sha1(rom)
                        self.assertEqual(archive.game_archive(rom, 4, 20), 'game')
                        self.assertEqual(archive.game_archive(rom, 4, 20), 'game')
                self.assertEqual(normalize.call_count, 2)
                self.assertEqual(parse.call_count, 2)
                self.assertEqual(digest.call_count, 2)
            with self.assertRaisesRegex(ValueError, 'changed during report'):
                with archive.reference_session():
                    archive.read_rom(path)
                    path.write_bytes(archive.Z64_MAGIC + bytes(17))
                    archive.read_rom(path)
            # Each rewrite changes the size: Linux file timestamps are
            # tick-coarse, so a same-size rewrite can keep the file signature.
            with self.assertRaisesRegex(ValueError, 'changed during report'):
                with archive.reference_session():
                    archive.read_rom(path)
                    path.write_bytes(archive.Z64_MAGIC + bytes(18))
            self.assertEqual(len(archive.read_rom(path)[0]), 22)

    def test_report_and_builders_use_same_reference_session(self):
        import sys
        sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
        import objdiff_report as report
        self.assertIs(report.rzip_archive, report.main_private_data.rzip_archive)
        self.assertIs(report.rzip_archive, report.objdiff_data_targets.model_build.rzip_archive)
