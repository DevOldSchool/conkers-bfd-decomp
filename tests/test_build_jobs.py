from __future__ import annotations

import os
from pathlib import Path
import shlex
import subprocess
import sys
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from build_jobs import job_count

SCRIPT = (ROOT / 'scripts/conker.sh').read_text()


def shell_function(name):
    return name + '() {' + SCRIPT.split(name + '() {', 1)[1].split('\n}\n', 1)[0] + '\n}\n'


class BuildJobsTests(unittest.TestCase):
    def test_default_override_and_validation(self):
        with patch.dict(os.environ, clear=True):
            self.assertEqual(job_count(), 4)
        for value, expected in (('', 4), ('1', 1), ('12', 12)):
            with self.subTest(value=value), patch.dict(os.environ, CONKER_JOBS=value):
                self.assertEqual(job_count(), expected)
        for value in ('0', '-1', '01', '1.5', ' 1', '1\n', 'all', '١'):
            with self.subTest(value=value), patch.dict(os.environ, CONKER_JOBS=value):
                with self.assertRaisesRegex(ValueError, 'positive integer'):
                    job_count()
                self.assertEqual(job_count('2'), 2)

    def test_container_forwarding_and_validation_even_in_conditional_calls(self):
        harness = 'set -euo pipefail\n' + f'repo_root={shlex.quote(str(ROOT))}\n'
        harness += '''
warm_container_name=warm
image_name=image
container_run_args=(--network none)
workspace_mounts=(--mount fixture)
ensure_image() { :; }
ensure_warm_container() { :; }
watch_image_is_compatible() { return 0; }
workspace_mount_args() { :; }
docker() { printf '%s\\n' "$@"; }
'''
        harness += shell_function('configure_build_jobs')
        harness += shell_function('run_in_warm_container')
        for function in ('run_in_container', 'run_in_warm_container', 'run_in_ephemeral_container',
                         'run_in_container_integrating', 'run_in_container_libultra'):
            definitions = '' if function == 'run_in_warm_container' else shell_function(function)
            for jobs in ('1', '7', 'invalid'):
                with self.subTest(function=function, jobs=jobs):
                    # A conditional caller suppresses Bash errexit inside functions.
                    body = harness + definitions + f'if {function} make; then exit 0; else exit 9; fi\n'
                    result = subprocess.run(['bash', '-c', body], capture_output=True, text=True,
                                            env=dict(os.environ, CONKER_JOBS=jobs))
                    if jobs == 'invalid':
                        self.assertEqual(result.returncode, 9, result.stderr)
                        self.assertEqual(result.stdout, '')
                    else:
                        self.assertEqual(result.returncode, 0, result.stderr)
                        self.assertIn(f'--env\nCONKER_JOBS={jobs}\n', result.stdout)
                        self.assertTrue(result.stdout.endswith('make\n'))

    def test_build_cli_override_is_exported_to_children(self):
        dispatch = '    prepare|build)' + SCRIPT.split('    prepare|build)', 1)[1].split('        ;;', 1)[0] + '        ;;\n'
        harness = 'set -euo pipefail\n' + f'repo_root={shlex.quote(str(ROOT))}\n'
        harness += shell_function('configure_build_jobs')
        harness += '''
state_tool=state
command=build
die() { echo "$*" >&2; exit 2; }
python3() { if [[ "$1" == */build_jobs.py ]]; then command python3 "$@"; fi; }
parse_profile_only() { selected_profile=us; }
run_in_container_libultra() { printf 'SDK:%s ENV:%s\\n' "$*" "$CONKER_JOBS"; }
run_in_container() { printf 'ROM:%s ENV:%s\\n' "$*" "$CONKER_JOBS"; }
'''
        for arguments, env_jobs, expected in (([], '1', '1'), (['--jobs', '2'], '1', '2'),
                                               (['--jobs', '3'], 'invalid', '3')):
            result = subprocess.run(['bash', '-c', harness + 'case build in\n' + dispatch + 'esac\n',
                                     'test', *arguments], capture_output=True, text=True,
                                    env=dict(os.environ, CONKER_JOBS=env_jobs))
            self.assertEqual(result.returncode, 0, result.stderr)
            lines = [line for line in result.stdout.splitlines() if line.startswith(('SDK:', 'ROM:'))]
            self.assertEqual(len(lines), 2)
            for line in lines:
                self.assertIn(f'--jobs {expected} ', line)
                self.assertTrue(line.endswith(f'ENV:{expected}'))


if __name__ == '__main__':
    unittest.main()
