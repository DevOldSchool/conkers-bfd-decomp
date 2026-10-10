from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
from urllib.parse import parse_qs, urlparse

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_snapshot as snapshot


class ObjdiffSnapshotTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.git('init', '-q')
        (self.root / 'src').mkdir()
        (self.root / 'src/example.c').write_text('void f(void) {}\n')
        (self.root / '.gitignore').write_text('build/\n')
        self.git('add', '.')
        self.commit()
        self.output = self.root / snapshot.REPORT_DIRECTORY
        self.output.mkdir(parents=True)
        # Deliberately different from inventory credit; use the native metric.
        self.native = {'version': 2, 'measures': {
            'total_code': '1000', 'matched_code': '125', 'matched_code_percent': 12.5}}
        self.proof = {'snapshot_schema': 1, 'profile': 'us', 'source_dirty': False,
                      'git_revision': self.git('rev-parse', 'HEAD').strip(),
                      'source_fingerprint': snapshot.input_fingerprint(self.root),
                      'format_version': 2, 'per_unit_coverage_verified': True,
                      'compile_errors': [], 'reported_code_bytes': 1000,
                      'expected_code_bytes': 1000, 'measures': self.native['measures']}
        self.save()

    def git(self, *args):
        return subprocess.check_output(['git', *args], cwd=self.root, text=True,
                                       stderr=subprocess.PIPE)

    def commit(self):
        self.git('-c', 'user.name=Snapshot test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'test inputs')

    def save(self):
        raw = json.dumps(self.native).encode()
        (self.output / 'report.json').write_bytes(raw)
        self.proof['report_sha256'] = hashlib.sha256(raw).hexdigest()
        (self.output / 'validation.json').write_text(json.dumps(self.proof))

    def test_current_snapshot_preserves_native_metric_and_provenance(self):
        status = snapshot.read_status(self.root)
        self.assertEqual('current', status['status'])
        self.assertEqual(12.5, status['matched_code_percent'])
        self.assertEqual(self.proof['git_revision'], status['git_revision'])
        text = '\n'.join(snapshot.render_status(status))
        self.assertIn('US Code: 12.5000%', text)
        self.assertIn('Profile: **us**', text)
        self.assertIn(self.proof['report_sha256'], text)

    def test_working_tree_edit_marks_snapshot_stale_without_fallback(self):
        (self.root / 'src/example.c').write_text('void g(void) {}\n')
        status = snapshot.read_status(self.root)
        self.assertEqual('stale', status['status'])
        text = '\n'.join(snapshot.render_status(status))
        self.assertIn('US Code: unavailable (stale)', text)
        self.assertIn('Last snapshot (not current)', text)

    def test_ignored_editable_font_changes_invalidate_snapshot(self):
        glyph = self.root / 'build/fonts/us/glyph.pgm'
        glyph.parent.mkdir(parents=True)
        glyph.write_bytes(b'original pixels')
        self.proof['asset_verification'] = {'font': {'source_inputs': {
            glyph.relative_to(self.root).as_posix(): hashlib.sha256(glyph.read_bytes()).hexdigest()}}}
        self.save()
        self.assertEqual('current', snapshot.read_status(self.root)['status'])
        glyph.write_bytes(b'edited pixels')
        self.assertEqual(self.proof['source_fingerprint'], snapshot.input_fingerprint(self.root))
        self.assertEqual('stale', snapshot.read_status(self.root)['status'])
        glyph.unlink()
        self.assertEqual('stale', snapshot.read_status(self.root)['status'])

    def test_added_and_deleted_input_invalidate_fingerprint(self):
        before = snapshot.input_fingerprint(self.root)
        source = self.root / 'src/new.c'
        source.write_text('void new(void) {}\n')
        self.assertNotEqual(before, snapshot.input_fingerprint(self.root))
        source.unlink()
        self.assertEqual(before, snapshot.input_fingerprint(self.root))
        (self.root / 'src/example.c').unlink()
        self.assertNotEqual(before, snapshot.input_fingerprint(self.root))

    def test_commit_with_identical_inputs_stays_current_and_reports_both_revisions(self):
        (self.root / 'README.md').write_text('documentation only\n')
        self.git('add', 'README.md')
        self.commit()
        status = snapshot.read_status(self.root)
        self.assertEqual('current', status['status'])
        self.assertIn('another commit with identical inputs', status['reason'])
        self.assertNotEqual(status['git_revision'], status['current_revision'])

    def test_unavailable_snapshot_explains_how_to_generate_or_skip(self):
        (self.output / 'report.json').unlink()
        text = '\n'.join(snapshot.render_status(snapshot.read_status(self.root)))
        self.assertIn('unavailable (missing)', text)
        self.assertIn('./conker objdiff report', text)
        self.assertIn('--inventory-only', text)

    def test_generated_outputs_do_not_invalidate_input_fingerprint(self):
        before = snapshot.input_fingerprint(self.root)
        (self.output / 'another-output').write_text('ignored output')
        self.assertEqual(before, snapshot.input_fingerprint(self.root))

    def test_dirty_snapshot_can_be_current_but_is_labeled(self):
        (self.root / 'src/example.c').write_text('void g(void) {}\n')
        self.proof.update(source_dirty=True, source_fingerprint=snapshot.input_fingerprint(self.root))
        self.save()
        status = snapshot.read_status(self.root)
        self.assertEqual('current', status['status'])
        self.assertIn('Modified report inputs at generation: **yes**', '\n'.join(snapshot.render_status(status)))

    def test_missing_sidecar_or_native_report_needs_no_git_or_build(self):
        for name in ('report.json', 'validation.json'):
            with self.subTest(name=name):
                self.save()
                (self.output / name).unlink()
                with patch.object(snapshot, 'git', side_effect=AssertionError('unexpected Git/build')):
                    self.assertEqual('missing', snapshot.read_status(self.root)['status'])

    def test_old_or_other_profile_provenance_is_not_trusted(self):
        for key, value in [('snapshot_schema', None), ('profile', 'eu'), ('git_revision', ''),
                           ('source_dirty', None), ('source_fingerprint', 'legacy')]:
            with self.subTest(key=key):
                original = self.proof[key]
                self.proof[key] = value
                self.save()
                self.assertEqual('unverified', snapshot.read_status(self.root)['status'])
                self.proof[key] = original

    def test_hash_mismatch_or_failed_generation_is_unavailable(self):
        (self.output / 'report.json').write_text('{}')
        self.assertEqual('invalid', snapshot.read_status(self.root)['status'])
        self.proof['compile_errors'] = ['game/unit/build.log']
        self.save()
        self.assertEqual('invalid', snapshot.read_status(self.root)['status'])

    def test_invalid_native_measures_and_zero_denominator_are_unavailable(self):
        for measures in ({'total_code': '0'}, {'total_code': '1000', 'matched_code_percent': float('nan')},
                         {'total_code': '1000', 'matched_code': '125', 'matched_code_percent': 99},
                         {'total_code': '1000', 'matched_code': '-1'}):
            with self.subTest(measures=measures):
                self.native['measures'] = measures
                self.proof['measures'] = measures
                self.save()
                self.assertEqual('invalid', snapshot.read_status(self.root)['status'])

    def test_malformed_sidecar_is_reported_without_crash(self):
        for raw in ('[]', 'null', '{'):
            (self.output / 'validation.json').write_text(raw)
            self.assertEqual('invalid', snapshot.read_status(self.root)['status'])

    def test_sdk_worktree_content_is_part_of_fingerprint(self):
        sdk = self.root / 'lib/sdk'
        sdk.mkdir(parents=True)
        subprocess.run(['git', 'init', '-q', str(sdk)], check=True)
        (sdk / 'source.c').write_text('int sdk;\n')
        subprocess.run(['git', '-C', str(sdk), 'add', '.'], check=True)
        subprocess.run(['git', '-C', str(sdk), '-c', 'user.name=Test',
                        '-c', 'user.email=test@example.invalid', 'commit', '-qm', 'sdk'], check=True)
        self.git('add', 'lib/sdk')
        before = snapshot.input_fingerprint(self.root)
        (sdk / 'source.c').write_text('int sdk_changed;\n')
        self.assertNotEqual(before, snapshot.input_fingerprint(self.root))

    def test_uninitialized_sdk_prevents_current_claim(self):
        self.git('update-index', '--add', '--cacheinfo',
                 f"160000,{self.proof['git_revision']},lib/sdk")
        (self.root / 'lib/sdk').mkdir(parents=True)
        self.assertEqual('invalid', snapshot.read_status(self.root)['status'])


class PublicBadgeTests(unittest.TestCase):
    def test_readme_uses_explicit_native_us_all_category_badge(self):
        text = (ROOT / 'README.md').read_text()
        url = re.search(r'\[!\[US Code\]\(([^)]+)\)', text).group(1)
        parsed = urlparse(url)
        self.assertEqual('https', parsed.scheme)
        self.assertEqual('decomp.dev', parsed.netloc)
        self.assertEqual('/DevOldSchool/conkers-bfd-decomp/us.svg', parsed.path)
        self.assertEqual({'mode': ['shield'], 'category': ['all'],
                          'measure': ['matched_code_percent'], 'label': ['US Code']},
                         parse_qs(parsed.query))
        self.assertNotIn('[![EU', text)
