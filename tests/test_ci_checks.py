from __future__ import annotations

import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch, MagicMock

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import ci_checks

spec = importlib.util.spec_from_file_location('private_verify', ROOT / 'ci/private-verifier/verify.py')
verify = importlib.util.module_from_spec(spec)
spec.loader.exec_module(verify)
spec = importlib.util.spec_from_file_location('private_sandbox', ROOT / 'ci/private-verifier/sandbox.py')
sandbox = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sandbox)
with patch.dict(sys.modules, {'verify': verify}):
    spec = importlib.util.spec_from_file_location('private_publish', ROOT / 'ci/private-verifier/publish.py')
    publish = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(publish)
spec = importlib.util.spec_from_file_location('pr_protection', ROOT / 'scripts/configure_pr_protection.py')
protection = importlib.util.module_from_spec(spec)
spec.loader.exec_module(protection)


class PublicChecksTests(unittest.TestCase):
    def test_forbidden_paths_and_allowed_project_files(self):
        for path in ['roms/test.bin', 'asm/test.s', 'build/a.json', 'x.Z64', 'x.o', 'x.n64', 'private-work/private-build.log', 'private-assets/input.bin']:
            self.assertTrue(ci_checks.forbidden_path(path), path)
        for path in ['roms/.gitkeep', 'docs/ci.md', 'tests/fixtures/ido_smoke.c', 'src/main/a.c']:
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


class PrivateVerifierTests(unittest.TestCase):
    def test_host_output_read_is_bounded_and_captures_container_diagnostics(self):
        with patch.object(verify.subprocess, 'run', return_value=MagicMock(returncode=0, stdout=b'1234')) as run:
            self.assertEqual(verify.read_container_file('sandbox', '/workspace/output', 4), b'1234')
            self.assertEqual(run.call_args.args[0],
                             ['docker', 'exec', 'sandbox', '/usr/bin/head', '-c', '5', '--', '/workspace/output'])
            self.assertTrue(run.call_args.kwargs['capture_output'])
            self.assertEqual(run.call_args.kwargs['timeout'], 30)
            run.return_value.stdout = b'12345'
            with self.assertRaises(ValueError):
                verify.read_container_file('sandbox', '/workspace/output', 4)
            run.return_value.returncode = 1
            run.return_value.stdout = b''
            with self.assertRaises(ValueError):
                verify.read_container_file('sandbox', '/workspace/output', 4)

    def test_inventory_cannot_shorten_or_move_the_approved_reference_span(self):
        import copy
        trusted = {'functions': [{'symbol': 'f', 'source': 'src/a.c', 'overlay': 'game',
                    'regions': {'us': {'vram': '0x15000000', 'symbol': 'f', 'size_bytes': 56, 'state': 'raw_asm'}}}]}
        candidate = copy.deepcopy(trusted)
        candidate['functions'][0]['regions']['us'].update(state='matched', evidence={'current_differences': 0})
        verify.enforce_registrations(trusted, candidate)
        for key, value in [('size_bytes', 4), ('vram', '0x15000004'), ('symbol', 'other')]:
            changed = copy.deepcopy(candidate)
            changed['functions'][0]['regions']['us'][key] = value
            with self.assertRaisesRegex(ValueError, 'reference registrations'):
                verify.enforce_registrations(trusted, changed)
        changed = copy.deepcopy(candidate)
        changed['functions'][0]['source'] = 'src/other.c'
        with self.assertRaises(ValueError):
            verify.enforce_registrations(trusted, changed)

    def test_source_unit_layout_requires_promotion_but_progress_state_does_not(self):
        import copy
        trusted = {'source_units': [{'source': 'src/a.c', 'functions': ['f'], 'integration': 'mixed',
                    'regions': {'us': {'start': '0x0', 'end': '0x40', 'state': 'in_progress'}}}]}
        candidate = copy.deepcopy(trusted)
        candidate['source_units'][0]['regions']['us']['state'] = 'matched'
        verify.enforce_registrations(trusted, candidate, units=True)
        candidate['source_units'][0]['regions']['us']['end'] = '0x4'
        with self.assertRaises(ValueError):
            verify.enforce_registrations(trusted, candidate, units=True)

    def test_source_context_keeps_real_padding_and_compiles_unit_once(self):
        import compile_c
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source = root / 'src/mixed.c'
            source.parent.mkdir()
            source.write_text('#pragma GLOBAL_ASM("neighbor.s")\nvoid tail(void) {}\n')
            differ, layout, aliases, tables = (MagicMock() for _ in range(4))
            differ.find_work_item_by_id.return_value = (source, 'tail', True)
            differ.expected_function_size.return_value = 56
            differ.run_required_asm_diff.return_value = 0
            focused_source = root / 'focused.c'
            focused_source.write_text('void tail(void) {}\n')
            differ.focused_candidate_source.return_value = focused_source
            layout.load_work_item.return_value = ({'regions': {'us': {'vram': '0x151B4C98'}}}, None)
            aliases.prepare.return_value = None
            tables.Object32.return_value.symbols = {1: [('tail', 0, 44, 1)]}
            modules = {'diff': differ, 'layout_check': layout, 'linked_aliases': aliases, 'candidate_tables': tables}
            with patch.dict(sys.modules, modules), patch.object(sandbox, 'run') as run, patch.object(Path, 'read_bytes', return_value=b'object'):
                objects = {}
                sandbox.verify_match(root, 'tail', objects)
                sandbox.verify_match(root, 'tail', objects)
                self.assertEqual(run.call_count, 2)
                self.assertIn(str(compile_c.ASM_PROCESSOR), run.call_args_list[0].args)
                self.assertEqual(run.call_args_list[0].args[-1], str(source))
                self.assertEqual(differ.run_required_asm_diff.call_args.args[4], 56)
                self.assertIn('private-check', str(differ.run_required_asm_diff.call_args.args[0]))
                differ.require_c_implementation.assert_called_with(source, 'tail')
                tables.Object32.return_value.symbols = {1: [('tail', 0, 56, 1)]}
                sandbox.verify_match(root, 'tail', objects)
                self.assertIn('private-focused', str(differ.run_required_asm_diff.call_args.args[0]))
                self.assertEqual(run.call_count, 2)
                differ.run_required_asm_diff.return_value = 1
                with self.assertRaisesRegex(ValueError, 'Full registered-span comparison failed'):
                    sandbox.verify_match(root, 'tail', objects)

    def test_stale_success_becomes_fixed_failure_and_token_is_revoked(self):
        args = ['publish.py', '--pr', '12', '--head', 'a'*40, '--base', 'b'*40,
                '--merge', 'c'*40, '--state', 'success']
        with (patch.object(sys, 'argv', args), patch.object(publish, 'resolve', side_effect=ValueError('untrusted detail')),
             patch.object(publish, 'installation_token', return_value='not-a-real-token'),
             patch.object(publish, 'request') as request, patch.object(publish.urllib.request, 'urlopen', return_value=MagicMock()) as revoke):
            publish.main()
            path, _, payload = request.call_args.args
            self.assertTrue(path.endswith('/statuses/' + 'c'*40))
            self.assertEqual(payload['state'], 'failure')
            self.assertNotIn('untrusted detail', payload['description'])
            self.assertEqual(revoke.call_args.args[0].method, 'DELETE')

    def test_rules_migration_preserves_other_checks_and_binds_verifier_app(self):
        old = {'name': 'Protect main', 'target': 'branch', 'enforcement': 'active', 'conditions': {},
               'rules': [{'type': 'deletion'}, {'type': 'required_status_checks', 'parameters':
                         {'required_status_checks': [{'context': 'metadata-and-tooling'}, {'context': 'another-check'}]}}]}
        new = protection.updated_ruleset(old, 123, require_reviews=True)
        checks = new['rules'][-1]['parameters']['required_status_checks']
        self.assertIn({'context': 'another-check'}, checks)
        self.assertIn({'context': protection.ROM_CHECK, 'integration_id': 123}, checks)
        self.assertNotIn({'context': 'metadata-and-tooling'}, checks)
        review = next(r['parameters'] for r in new['rules'] if r['type'] == 'pull_request')
        self.assertTrue(review['dismiss_stale_reviews_on_push'])
        self.assertTrue(review['require_code_owner_review'])

    def test_initial_rules_migration_preserves_single_maintainer_review_policy(self):
        review = {'required_approving_review_count': 0, 'require_code_owner_review': False,
                  'require_last_push_approval': False, 'required_review_thread_resolution': True}
        old = {'name': 'Protect main', 'target': 'branch', 'enforcement': 'active', 'conditions': {},
               'rules': [{'type': 'pull_request', 'parameters': review}]}
        updated = protection.updated_ruleset(old, 5045941)
        self.assertEqual(next(r['parameters'] for r in updated['rules'] if r['type'] == 'pull_request'), review)

    def test_tooling_and_reference_changes_fail_closed(self):
        for path in ['scripts/diff.py', 'Makefile', 'Dockerfile', '.github/workflows/ci.yml',
                     'config/roms.json', 'config/reference/us.yaml', 'config/game/us.yaml',
                     'lib/ultralib', 'include/macro.inc']:
            with self.assertRaisesRegex(ValueError, 'Trusted-tooling review'):
                verify.enforce_policy({path: ('100644', 'blob', 'a')}, {path: ('100644', 'blob', 'b')})
        verify.enforce_policy({'src/game/a.c': ('100644', 'blob', 'a')}, {'src/game/a.c': ('100644', 'blob', 'b')})

    def test_paths_symlinks_and_make_metacharacters_rejected(self):
        for entry in [b'120000 blob abc\tsrc/link\0', b'100644 blob abc\t../escape\0',
                      b'100644 blob abc\tsrc/$(touch x).c\0', b'100644 blob abc\t.git/hooks/foo\0']:
            with patch.object(verify, 'git', return_value=entry):
                with self.assertRaises(ValueError):
                    verify.tree(Path('unused'), 'a'*40)

    def test_header_changes_reverify_all_matched_functions(self):
        rows = [{'symbol': 'f', 'source': 'src/a.c', 'regions': {'us': {'state': 'matched'}}},
                {'symbol': 'g', 'source': 'src/b.c', 'regions': {'us': {'state': 'raw_asm'}}}]
        inventory = {'functions': rows}
        self.assertEqual(verify.selected_functions(inventory, inventory, {'include/a.h'}), [{'symbol': 'f', 'state': 'matched'}])
        self.assertEqual(verify.selected_functions(inventory, inventory, {'src/local.h'}), [{'symbol': 'f', 'state': 'matched'}])
        self.assertEqual(verify.selected_functions(inventory, inventory, {'docs/a.md'}), [])
        self.assertEqual(verify.selected_functions(inventory, inventory, {'src/a.c'})[0]['symbol'], 'f')

    def test_sandbox_has_no_network_credentials_or_writable_host_mount(self):
        command = verify.docker_command('test', {'image': 'pinned'}, Path('/source'), Path('/rom'), Path('/verifier'), Path('/plan'))
        self.assertEqual(command[command.index('--network') + 1], 'none')
        for required in ['--read-only', '--cap-drop', '--security-opt', '--pids-limit', '--memory']:
            self.assertIn(required, command)
        mounts = [command[i+1] for i, token in enumerate(command) if token == '--mount']
        self.assertTrue(all(m.endswith(',readonly') for m in mounts))
        self.assertEqual(mounts, [
            'type=bind,source=/source,target=/candidate,readonly',
            'type=bind,source=/rom,target=/input/baserom.us.z64,readonly',
            'type=bind,source=/verifier/sandbox.py,target=/verifier/sandbox.py,readonly',
            'type=bind,source=/plan,target=/plan.json,readonly',
        ])
        self.assertNotIn('--privileged', command)
        self.assertNotIn('/var/run/docker.sock', ' '.join(command))
        self.assertNotIn('--env', command)

    def test_rsp_image_build_context_contains_only_reviewed_dockerfile(self):
        with tempfile.TemporaryDirectory() as tmp:
            work = Path(tmp)
            toolchain = work / 'candidate/toolchain'; toolchain.mkdir(parents=True)
            (toolchain / 'tools.lock.json').write_text(json.dumps({'tools': {'armips': {'revision': 'a'*40}}}))
            (toolchain / 'rsp.Dockerfile').write_text('ARG BASE_IMAGE\nFROM ${BASE_IMAGE}\n')
            (work / 'private-input').write_text('must not enter build context')
            seen = []
            def run(command, **kwargs):
                seen.append(command)
                if command[:2] == ['docker', 'build']:
                    context = Path(command[-1])
                    self.assertEqual([p.name for p in context.iterdir()], ['Dockerfile'])
                    self.assertEqual((context / 'Dockerfile').read_bytes(), (toolchain / 'rsp.Dockerfile').read_bytes())
            with (patch.object(verify.subprocess, 'run', return_value=MagicMock(returncode=0)),
                  patch.object(verify.subprocess, 'check_output', side_effect=['sha256:'+'b'*64, 'sha256:'+'c'*64]),
                  patch.object(verify, 'run', side_effect=run)):
                image = verify.build_image({'image': 'repo@sha256:'+'b'*64}, work)
            self.assertEqual(image, 'sha256:'+'c'*64)
            self.assertEqual(seen[-1][:2], ['docker', 'build'])

    def test_host_hashes_outputs_before_removing_live_tmpfs_container(self):
        events = []
        settings = {'image': 'pinned', 'rom_sha1': 'rom-hash', 'game_sha1': 'game-hash'}
        rom = MagicMock()
        rom.stat.return_value.st_size = 67108864
        digests = [MagicMock() for _ in range(3)]
        for digest, value in zip(digests, ['rom-hash', 'rom-hash', 'game-hash']):
            digest.hexdigest.return_value = value
        def command(args, **kwargs):
            events.append(args[:2])
            return MagicMock(returncode=0)
        def output(*args):
            events.append(['read', args[1]])
            return b'output'
        with tempfile.TemporaryDirectory() as tmp, \
             patch.object(verify.hashlib, 'sha1', side_effect=digests), \
             patch.object(verify, 'build_image', return_value='pinned'), \
             patch.object(verify, 'run', side_effect=command), \
             patch.object(verify.subprocess, 'run', side_effect=command), \
             patch.object(verify, 'read_container_file', side_effect=output):
            verify.verify(settings, {}, Path(tmp), rom, Path(tmp))
        self.assertEqual([event[0] for event in events], ['docker', 'docker', 'read', 'read', 'docker'])
        self.assertEqual(events[1], ['docker', 'exec'])
        self.assertEqual(events[-1], ['docker', 'rm'])

    def test_approval_binds_both_parents(self):
        head, base, merge = 'a'*40, 'b'*40, 'c'*40
        pr = {'state': 'open', 'base': {'repo': {'full_name': verify.REPOSITORY}, 'ref': 'main', 'sha': base}, 'head': {'sha': head}}
        with patch.object(verify, 'api', side_effect=[pr, {'object': {'sha': merge}}, {'parents': [{'sha': base}, {'sha': head}]}]):
            self.assertEqual(verify.resolve(12, head, base)['merge'], merge)
        pr['head']['sha'] = 'd'*40
        with patch.object(verify, 'api', return_value=pr):
            with self.assertRaises(ValueError):
                verify.resolve(12, head, base)

    def test_private_workflow_never_uploads_or_runs_on_public_events(self):
        import yaml
        data = yaml.safe_load((ROOT / 'ci/private-verifier/verify-pr.yml').read_text())
        trigger = data.get('on', data.get(True))
        self.assertEqual(set(trigger), {'workflow_dispatch'})
        self.assertFalse(trigger['workflow_dispatch']['inputs']['reviewed']['default'])
        for job in data['jobs'].values():
            gate = job['if']
            self.assertIn("github.actor_id == '168640902'", gate)
            self.assertIn("github.triggering_actor == 'DevOldSchool'", gate)
            self.assertIn('inputs.reviewed', gate)
        text = (ROOT / 'ci/private-verifier/verify-pr.yml').read_text()
        self.assertNotIn('upload-artifact@', text)
        self.assertNotIn('actions/cache@', text)
        self.assertIn('github.event.repository.private', text)
        verify_job = data['jobs']['verify']
        self.assertEqual(verify_job['environment'], 'rom-verification')
        self.assertNotIn('VERIFIER_APP_PRIVATE_KEY', json.dumps(verify_job))


if __name__ == '__main__':
    unittest.main()
