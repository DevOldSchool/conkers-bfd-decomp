from __future__ import annotations

from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
SCRIPT = (ROOT / 'scripts/conker.sh').read_text()


def shell_function(name):
    return name + '() {' + SCRIPT.split(name + '() {', 1)[1].split('\n}\n', 1)[0] + '\n}\n'


class WarmFileMountTests(unittest.TestCase):
    def run_lifecycle(self, change='', *, exists=True, running=True, legacy=False):
        with tempfile.TemporaryDirectory(prefix='warm mounts ') as temporary:
            root = Path(temporary)
            (root / 'Makefile').write_text('all:\n\ttrue\n')
            (root / 'Dockerfile').write_text('FROM fixture\n')
            harness = 'set -euo pipefail\nrepo_root=' + shlex.quote(str(root)) + '\n'
            harness += r'''
warm_container_name=fixture-warm
warm_container_schema=1
image_name=fixture-image
container_run_args=(--network none)
workspace_mounts=(--mount fixture)
ensure_image() { :; }
workspace_mount_args() { :; }
docker() {
    case "$1 $2" in
        'image inspect') printf '%s\n' image-id ;;
        'container inspect')
            [[ "$exists" == true ]] || return 1
            if [[ "$3" == --format ]]; then
                case "$4" in
                    *'.Image'*) printf '%s\n' image-id ;;
                    *warm-schema*) printf '%s\n' 1 ;;
                    *file-mounts*) printf '%s\n' "$fake_file_mounts" ;;
                    *Running*) printf '%s\n' "$fake_running" ;;
                    *) return 2 ;;
                esac
            fi
            ;;
        'rm --force')
            [[ "$3" == "$warm_container_name" ]] || return 2
            printf 'remove\n' >> "$repo_root/events"
            exists=false
            ;;
        'run --detach')
            printf 'create\n' >> "$repo_root/events"
            while (( $# )); do
                if [[ "$1" == org.devoldschool.conker.file-mounts=* ]]; then
                    fake_file_mounts="${1#*=}"
                    printf '%s\n' "$fake_file_mounts" > "$repo_root/created-fingerprint"
                fi
                shift
            done
            exists=true
            fake_running=true
            ;;
        'start fixture-warm')
            printf 'start\n' >> "$repo_root/events"
            fake_running=true
            ;;
        *) return 2 ;;
    esac
}
'''
            harness += shell_function('warm_file_mount_fingerprint')
            harness += shell_function('remove_warm_container')
            harness += shell_function('ensure_warm_container')
            harness += f'exists={str(exists).lower()}\nfake_running={str(running).lower()}\n'
            harness += 'fake_file_mounts="$(warm_file_mount_fingerprint)"\n'
            if legacy:
                harness += 'fake_file_mounts=""\n'
            harness += change + '\nensure_warm_container\nensure_warm_container\n'
            harness += 'warm_file_mount_fingerprint > "$repo_root/expected-fingerprint"\n'
            result = subprocess.run(['bash', '-c', harness], text=True, capture_output=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            events = (root / 'events').read_text().splitlines() if (root / 'events').exists() else []
            if 'create' in events:
                self.assertEqual((root / 'created-fingerprint').read_text(),
                                 (root / 'expected-fingerprint').read_text())
            return events

    def test_unchanged_files_reuse_running_container(self):
        self.assertEqual(self.run_lifecycle(), [])

    def test_unchanged_files_restart_stopped_container(self):
        self.assertEqual(self.run_lifecycle(running=False), ['start'])

    def test_content_changes_refresh_once(self):
        for name in ('Makefile', 'Dockerfile'):
            with self.subTest(name=name):
                self.assertEqual(self.run_lifecycle(f'printf "changed\\n" >> "$repo_root/{name}"'),
                                 ['remove', 'create'])

    def test_atomic_same_content_replacement_refreshes_once(self):
        for name in ('Makefile', 'Dockerfile'):
            with self.subTest(name=name):
                change = (f'cp "$repo_root/{name}" "$repo_root/replacement"\n'
                          f'mv "$repo_root/replacement" "$repo_root/{name}"')
                self.assertEqual(self.run_lifecycle(change), ['remove', 'create'])

    def test_container_without_fingerprint_is_migrated(self):
        self.assertEqual(self.run_lifecycle(legacy=True), ['remove', 'create'])

    def test_new_container_is_labeled_and_reused(self):
        self.assertEqual(self.run_lifecycle(exists=False), ['create'])


if __name__ == '__main__':
    unittest.main()
