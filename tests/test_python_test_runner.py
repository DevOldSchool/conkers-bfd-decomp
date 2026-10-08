from pathlib import Path
import os
import subprocess
import tempfile
import unittest


SCRIPT = (Path(__file__).resolve().parents[1] / "scripts/conker.sh").read_text()
RUNNER = ("select_test_runner() {" + SCRIPT.split("select_test_runner() {", 1)[1]
          .split("run_in_container_interactive() {", 1)[0])
TEST_COMMAND = ("case test in\n    test)\n"
                + SCRIPT.split("\n    test)\n", 1)[1].split("        ;;\n", 1)[0] + "        ;;\nesac\n")


class PythonTestRunnerTests(unittest.TestCase):
    def run_command(self, *args, docker="up", host="ok", runner=None, extra_env=None):
        with tempfile.TemporaryDirectory() as root:
            harness = r'''
set -euo pipefail
repo_root="$1"; docker_state="$2"; host_state="$3"; shift 3
image_name=pinned-image
container_run_args=(--platform linux/amd64 --read-only --tmpfs /tmp:rw,nosuid,nodev,size=1g)
die() { printf 'error: %s\n' "$*" >&2; exit 1; }
require_docker_access() { [[ "$docker_state" == up ]]; }
ensure_image() { image_name=rsp-image; }
docker() { printf 'docker %s\n' "$*" >&2; }
python3() {
    if [[ "$1" == "$repo_root/scripts/host_environment.py" ]]; then
        printf 'host-check\n' >&2; [[ "$host_state" == ok ]]; return
    fi
    if [[ "$1" == "--version" ]]; then printf 'Python 3.12.0\n'; return; fi
    if [[ "$1" == "-c" ]]; then printf '%s\n' "$repo_root"; return; fi
    printf 'host-python %s\n' "$*" >&2
}
'''
            env = dict(os.environ)
            env.pop("CONKER_TEST_RUNNER", None)
            env.pop("CONKER_ROM_TESTS", None)
            env.update(extra_env or {})
            if runner is not None:
                env["CONKER_TEST_RUNNER"] = runner
            return subprocess.run(
                ["bash", "-c", harness + RUNNER + TEST_COMMAND, "test", root, docker, host, *args],
                capture_output=True, text=True, env=env)

    def test_docker_is_default_with_writable_build_and_executable_tmp_outside_checkout(self):
        result = self.run_command("-q")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertNotIn("host-check", result.stderr)
        self.assertNotIn("host-python", result.stderr)
        self.assertIn("tests: docker runner (rsp-image)", result.stdout)
        command = next(line for line in result.stderr.splitlines() if line.startswith("docker run "))
        self.assertIn("--rm --platform linux/amd64 --read-only --tmpfs /tmp:rw,exec,nosuid,nodev,size=1g ", command)
        self.assertEqual(1, command.count("--tmpfs"))
        self.assertNotIn("TMPDIR", command)
        self.assertRegex(command, r"source=\S+,target=/workspace,readonly ")
        self.assertRegex(command, r"source=\S+/build,target=/workspace/build ")
        for setting in ("CONKER_IN_CONTAINER=1", "HOME=/tmp", "PYTHONDONTWRITEBYTECODE=1"):
            self.assertIn("--env " + setting, command)
        self.assertTrue(command.endswith("rsp-image python3 -m unittest discover -s tests -q"))
        self.assertNotIn("CONKER_ROM_TESTS", command)

    def test_docker_runner_forwards_rom_integration_opt_in(self):
        result = self.run_command("-q", extra_env={"CONKER_ROM_TESTS": "1"})
        self.assertEqual(0, result.returncode, result.stderr)
        command = next(line for line in result.stderr.splitlines() if line.startswith("docker run "))
        self.assertIn("--env CONKER_ROM_TESTS=1 ", command)

    def test_unavailable_docker_never_falls_back_to_host(self):
        result = self.run_command(docker="down")
        self.assertEqual(2, result.returncode)
        self.assertIn("use --host", result.stderr)
        self.assertNotIn("host-python", result.stderr)
        self.assertNotIn("docker run", result.stderr)

    def test_host_flag_and_environment_select_checked_host_runner(self):
        for result in (self.run_command("--host", "-v"), self.run_command("-v", runner="host")):
            self.assertEqual(0, result.returncode, result.stderr)
            self.assertEqual("host-check", result.stderr.splitlines()[0])
            self.assertIn("host-python -m unittest discover -s tests -v", result.stderr)
            self.assertIn("tests: host runner (Python 3.12.0)", result.stdout)
            self.assertNotIn("docker run", result.stderr)

    def test_host_runner_stops_when_pins_are_missing(self):
        result = self.run_command("--host", host="missing")
        self.assertEqual(2, result.returncode)
        self.assertNotIn("host-python", result.stderr)

    def test_unknown_runner_is_rejected(self):
        result = self.run_command(runner="podman")
        self.assertEqual(1, result.returncode)
        self.assertIn("CONKER_TEST_RUNNER must be 'docker' or 'host'", result.stderr)


if __name__ == "__main__":
    unittest.main()
