from __future__ import annotations

import importlib.util
import io
import json
import os
import sys
import tempfile
import unittest
from contextlib import redirect_stderr
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import m2c_context
import compile_c
spec = importlib.util.spec_from_file_location("context_helper", ROOT / "scripts/m2c.py")
helper = importlib.util.module_from_spec(spec)
spec.loader.exec_module(helper)


class M2CContextTests(unittest.TestCase):
    def test_cleaning_retains_declarations_and_removes_only_known_metadata(self):
        text = '\n'.join([
            '# 1 "include/types.h"', 'typedef int s32;',
            '#pragma GLOBAL_ASM("asm/f.s")', '#pragma intrinsic(sqrtf, fabsf)',
            '__pragma(1, sqrtf, fabsf);', 'struct State { s32 field; };',
            'extern struct State *state;',
        ])
        self.assertEqual(m2c_context.clean_context(text),
                         'typedef int s32;\nstruct State { s32 field; };\nextern struct State *state;\n')

    def test_unknown_layout_pragmas_and_unexpanded_directives_fail_closed(self):
        for line in ('#pragma pack(1)', '#define VALUE 1', '__pragma(2, state);',
                     '#pragma intrinsic(other)', '#pragma intrinsic(sqrtf) junk'):
            with self.subTest(line=line), self.assertRaisesRegex(ValueError, 'unsupported'):
                m2c_context.clean_context(line)

    def test_preprocessing_uses_actual_build_flags_and_canonical_source(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder).resolve()
            source = root / 'src/test.c'
            source.parent.mkdir()
            source.write_text('#if PROFILE_US\nint active;\n#else\nint other;\n#endif\n')
            original = source.read_bytes()
            result = SimpleNamespace(returncode=0, stdout='# 1 "src/test.c"\nint active;\n', stderr='')
            with patch.object(m2c_context, 'ROOT', root), patch.object(m2c_context.subprocess, 'run', return_value=result) as run:
                self.assertEqual(m2c_context.preprocess_source('us', source), 'int active;\n')
            command = run.call_args.args[0]
            self.assertEqual(command, [str(compile_c.IDO_CC),
                             *[f for f in compile_c.compiler_flags('us') if f != '-c'], '-E', 'src/test.c'])
            self.assertEqual(run.call_args.kwargs['cwd'], root)
            self.assertEqual(source.read_bytes(), original)

    def test_preprocessor_errors_do_not_become_context(self):
        result = SimpleNamespace(returncode=1, stdout='partial context', stderr='missing header')
        with patch.object(m2c_context.subprocess, 'run', return_value=result):
            with self.assertRaisesRegex(ValueError, 'missing header'):
                m2c_context.preprocess_source('us', ROOT / 'src/f.c')

    def test_outside_source_is_rejected_before_preprocessing(self):
        with patch.object(m2c_context.subprocess, 'run') as run:
            for path in (ROOT, ROOT / 'include/f.c', Path('/tmp/not-project.c')):
                with self.subTest(path=path), self.assertRaises(ValueError):
                    m2c_context.preprocess_source('us', path)
            run.assert_not_called()

    def test_fallback_refreshes_headers_and_records_profile_and_reason(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            source = root / 'src/game/f.c'
            source.parent.mkdir(parents=True)
            source.write_text('#include "state.h"\n')
            responses = [SimpleNamespace(returncode=0, stdout='struct State { int x; };\n', stderr=''),
                         SimpleNamespace(returncode=0, stdout='struct State { int x, y; };\n', stderr=''),
                         SimpleNamespace(returncode=1, stdout='partial', stderr='missing state.h')]
            with patch.object(helper, 'ROOT', root), patch.dict(os.environ, {'CONKER_HOST_M2C': '1'}), patch.object(helper.subprocess, 'run', side_effect=responses) as run:
                first = helper.prepare_m2c_context(source, 'us')
                digest = json.loads(first.with_suffix('.json').read_text())['sha256']
                second = helper.prepare_m2c_context(source, 'us')
                self.assertNotEqual(digest, json.loads(second.with_suffix('.json').read_text())['sha256'])
                self.assertIn('x, y', second.read_text())
                errors = io.StringIO()
                with redirect_stderr(errors):
                    self.assertIsNone(helper.prepare_m2c_context(source, 'us'))
                metadata = json.loads(second.with_suffix('.json').read_text())
                self.assertEqual(metadata['method'], 'unavailable')
                self.assertIsNone(metadata['sha256'])
                self.assertIn('missing state.h', errors.getvalue())
                self.assertEqual(run.call_args.args[0], [str(root / 'conker'), 'm2c-context', '--profile', 'us', 'src/game/f.c'])

    def test_flattened_context_does_not_invoke_preprocessor_and_profiles_are_separate(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            source = root / 'src/f.c'
            source.parent.mkdir()
            source.write_text('extern int value;\n')
            with patch.object(helper, 'ROOT', root), patch.object(helper.subprocess, 'run') as run:
                us = helper.prepare_m2c_context(source, 'us')
                eu = helper.prepare_m2c_context(source, 'eu')
                run.assert_not_called()
            self.assertNotEqual(us, eu)
            self.assertEqual(json.loads(us.with_suffix('.json').read_text())['method'], 'flattened')

    def test_generator_fingerprint_tracks_local_python_changes(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / 'm2c').mkdir()
            (root / 'm2c_pycparser').mkdir()
            tool = root / 'm2c.py'
            tool.write_text('import m2c\n')
            module = root / 'm2c/translate.py'
            module.write_text('value = 1\n')
            command = ['python3', str(tool), '-f', 'func_test', 'input.s']
            before = helper.generator_evidence(command)
            module.write_text('value = 2\n')
            after = helper.generator_evidence(command)
            self.assertNotEqual(before['python_sources_sha256'], after['python_sources_sha256'])
            self.assertEqual(after['path'], str(tool.resolve()))
            self.assertEqual(after['requested_command'], command)
