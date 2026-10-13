from __future__ import annotations

from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import ci_checks

class PublicChecksTests(unittest.TestCase):
    def test_forbidden_paths_and_allowed_project_files(self):
        for path in ['roms/test.bin', 'asm/test.s', 'build/a.json', 'x.Z64', 'x.o', 'x.n64', 'private-work/private-build.log', 'private-assets/input.bin',
                     'progress/summary.json', 'progress/badge-us.json', 'progress/badge-eu.json', 'build/progress/progress.md']:
            self.assertTrue(ci_checks.forbidden_path(path), path)
        for path in ['roms/.gitkeep', 'docs/ci.md', 'tests/fixtures/ido_smoke.c', 'src/main/a.c',
                     'docs/progress.md', 'progress/functions.json', 'progress/source_units.json']:
            self.assertFalse(ci_checks.forbidden_path(path), path)

    def test_committed_whitespace_is_checked_even_with_clean_worktree(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            def git(*args):
                return subprocess.check_output(['git', '-C', tmp, *args], stderr=subprocess.DEVNULL)
            git('init', '-q'); git('config', 'user.name', 'Test'); git('config', 'user.email', 'test@example.invalid')
            (root / 'file.c').write_text('int a;\n')
            git('add', 'file.c'); git('commit', '-qm', 'base')
            base = git('rev-parse', 'HEAD').decode().strip()
            (root / 'file.c').write_text('int a; \n')
            git('add', 'file.c'); git('commit', '-qm', 'bad whitespace')
            self.assertFalse(git('diff'))
            with self.assertRaises(subprocess.CalledProcessError):
                ci_checks.hygiene(root, base, 'HEAD')

    def test_renamed_rom_detected_by_magic(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'innocent.txt').write_bytes(bytes.fromhex('80371240') + b'payload')
            with patch.object(ci_checks, 'tracked_paths', return_value=['innocent.txt']), \
                 patch.object(ci_checks.subprocess, 'check_output', return_value='a'*40+'\n'), \
                 patch.object(ci_checks.subprocess, 'run'):
                with self.assertRaisesRegex(ValueError, 'innocent'):
                    ci_checks.hygiene(root, 'base', 'head')

    def test_compile_omits_asm_without_enabling_deferred_code(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp); (root / 'src').mkdir()
            source = '#pragma GLOBAL_ASM("missing.s")\n#if 0\nunknown deferred;\n#endif\nint f(void) { return 0; }\n'
            (root / 'src/a.c').write_text(source)
            with patch.object(ci_checks, 'tracked_paths', return_value=['src/a.c']), patch.object(ci_checks.subprocess, 'run') as run:
                ci_checks.compile_active(root)
                self.assertEqual(run.call_count, 1)
            result = (root / 'build/ci-compile/src/a.c').read_text()
            self.assertNotIn('GLOBAL_ASM', result)
            self.assertIn('#if 0\nunknown deferred;', result)
            self.assertEqual((root / 'src/a.c').read_text(), source)


    def test_compile_omits_only_reviewed_local_asset_include(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            name = 'src/done/debugger/debugger_0000.c'
            source = root / name
            source.parent.mkdir(parents=True)
            original = ('#include "types.h"\nextern const u8 glyphs[];\n'
                        'int f(void) { return glyphs[0]; }\n'
                        '#include "debugger-assets/ui.inc.c"\n'
                        '#include "another-required.inc.c"\n')
            source.write_text(original)
            # No ROM or generated asset exists in this checkout.
            with patch.object(ci_checks, 'tracked_paths', return_value=[name]), \
                 patch.object(ci_checks.subprocess, 'run') as run:
                ci_checks.compile_active(root)
                run.assert_called_once()
                self.assertTrue(run.call_args.kwargs['check'])
            temporary = (root / 'build/ci-compile' / name).read_text()
            self.assertNotIn('#include "debugger-assets/ui.inc.c"', temporary)
            self.assertIn('#include "types.h"', temporary)
            self.assertIn('#include "another-required.inc.c"', temporary)
            self.assertIn('extern const u8 glyphs[];', temporary)
            self.assertIn('return glyphs[0];', temporary)
            self.assertEqual(source.read_text(), original)
            self.assertFalse((root / 'build/us/debugger-assets').exists())

    def test_local_asset_omission_is_scoped_to_reviewed_source(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'src').mkdir()
            original = '#include "debugger-assets/ui.inc.c"\n'
            (root / 'src/other.c').write_text(original)
            with patch.object(ci_checks, 'tracked_paths', return_value=['src/other.c']), \
                 patch.object(ci_checks.subprocess, 'run'):
                ci_checks.compile_active(root)
            self.assertEqual((root / 'build/ci-compile/src/other.c').read_text(), original)

    def test_source_list_rejects_escape_without_running_compiler(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp); (root / 'src').mkdir()
            source_list = root / 'sources.list'
            source_list.write_text('src/../../outside.c\0')
            with patch.object(ci_checks.subprocess, 'run') as run:
                with self.assertRaises(ValueError):
                    ci_checks.compile_active(root, source_list)
                run.assert_not_called()

    def test_nonempty_rom_placeholder_is_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp); (root / 'roms').mkdir()
            (root / 'roms/.gitkeep').write_bytes(b'disguised payload')
            with patch.object(ci_checks, 'tracked_paths', return_value=['roms/.gitkeep']), \
                 patch.object(ci_checks.subprocess, 'check_output', return_value='a'*40+'\n'), \
                 patch.object(ci_checks.subprocess, 'run'):
                with self.assertRaisesRegex(ValueError, 'gitkeep'):
                    ci_checks.hygiene(root, 'base', 'head')


if __name__ == '__main__':
    unittest.main()
