from pathlib import Path
import os
import subprocess
import tempfile
import unittest


SCRIPT = (Path(__file__).resolve().parents[1] / "scripts/conker.sh").read_text()


class DebuggerCommandTests(unittest.TestCase):
    def run_script(self, body, *args, failure="", runner=None, jobs=None):
        with tempfile.TemporaryDirectory() as root:
            harness = r'''
set -euo pipefail
repo_root="$1"; shift
state_tool=state-tool
selected_profile=us
selected_value=func_debugger
failure="$1"; shift
die() { printf 'error: %s\n' "$*" >&2; exit 1; }
python3() {
    if [[ "$1" == */build_jobs.py ]]; then
        command python3 "$job_helper" "${@:2}"; return
    fi
    if [[ "$1" == "$repo_root/scripts/host_environment.py" ]]; then
        [[ "$failure" == host-core ]] && return 2
        [[ "$failure" == host && "$3" != --core ]] && return 2
        return 0
    fi
    case "${2:-}" in
        batch-plan|integration-plan) printf 'debugger\n' ;;
        batch-fingerprint) printf 'fingerprint\n' ;;
    esac
}
git() { return 0; }
ensure_warm_container() { return 0; }
select_test_runner() { test_runner="${CONKER_TEST_RUNNER:-docker}"; }
run_python_tests() { return 0; }
run_in_container_libultra() {
    printf 'libraries: %s\n' "$*" >&2
    [[ "$failure" != libraries ]]
}
run_in_container() { printf 'build: %s\n' "$*" >&2; }
run_in_warm_container() {
    printf 'warm: %s\n' "$*" >&2
    [[ "$failure" != asm || "$2" != scripts/prepare_nonmatching_asm.py ]]
}
run_in_container_integrating() { printf 'integrate: %s\n' "$*" >&2; }
parse_profile_and_value() { shift; selected_value="$1"; }
'''
            helper = SCRIPT.split('configure_build_jobs() {', 1)[1].split('\n}\n', 1)[0]
            harness += 'configure_build_jobs() {' + helper + '\n}\n'
            harness += f'job_helper={str(Path(__file__).resolve().parents[1] / "scripts/build_jobs.py")!r}\n'
            env = dict(os.environ)
            env.pop("CONKER_JOBS", None)
            if jobs is not None:
                env["CONKER_JOBS"] = jobs
            env.pop("CONKER_TEST_RUNNER", None)
            if runner:
                env["CONKER_TEST_RUNNER"] = runner
            return subprocess.run(["bash", "-c", harness + body, "test", root, failure, *args],
                                  capture_output=True, text=True, env=env)

    def test_batch_stages_profile_archives_before_full_rom_build(self):
        body = ("case verify-batch in\n    verify-batch)\n"
                + SCRIPT.split("    verify-batch)\n", 1)[1].split("    stop)\n", 1)[0] + "esac\n")
        result = self.run_script(body, "func_debugger")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertEqual([
            "libraries: make --silent --jobs 4 profile-libs PROFILE=us",
            "build: make --silent --jobs 4 build PROFILE=us",
        ], result.stderr.splitlines())
        self.assertIn("AGENT_ACTION: BATCH_COMPLETE", result.stdout)
        failed = self.run_script(body, "func_debugger", failure="libraries")
        self.assertNotEqual(0, failed.returncode)
        self.assertNotIn("build:", failed.stderr)

    def test_batch_job_override_and_invalid_setting(self):
        body = ("case verify-batch in\n    verify-batch)\n"
                + SCRIPT.split("    verify-batch)\n", 1)[1].split("    stop)\n", 1)[0] + "esac\n")
        result = self.run_script(body, "func_debugger", jobs="1")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn("libraries: make --silent --jobs 1 profile-libs", result.stderr)
        self.assertIn("build: make --silent --jobs 1 build", result.stderr)
        for jobs in ("0", "-1", "invalid", "1 2"):
            result = self.run_script(body, "func_debugger", jobs=jobs)
            self.assertNotEqual(0, result.returncode)
            self.assertIn("positive integer", result.stderr)
            self.assertNotIn("libraries:", result.stderr)
            self.assertNotIn("build:", result.stderr)

    def test_batch_missing_host_dependencies_stops_before_build(self):
        body = ("case verify-batch in\n    verify-batch)\n"
                + SCRIPT.split("    verify-batch)\n", 1)[1].split("    stop)\n", 1)[0] + "esac\n")
        for result in (self.run_script(body, "func_debugger", failure="host", runner="host"),
                       self.run_script(body, "--host-tests", "func_debugger", failure="host")):
            self.assertEqual(2, result.returncode)
            self.assertIn("AGENT_ACTION: BLOCKED_TOOLING", result.stdout)
            self.assertNotIn("libraries:", result.stderr)
            self.assertNotIn("build:", result.stderr)

    def test_batch_docker_tests_do_not_need_host_dependencies(self):
        body = ("case verify-batch in\n    verify-batch)\n"
                + SCRIPT.split("    verify-batch)\n", 1)[1].split("    stop)\n", 1)[0] + "esac\n")
        result = self.run_script(body, "func_debugger", failure="host")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn("AGENT_ACTION: BATCH_COMPLETE", result.stdout)

    def test_batch_missing_core_host_dependencies_stop_docker_mode_before_build(self):
        body = ("case verify-batch in\n    verify-batch)\n"
                + SCRIPT.split("    verify-batch)\n", 1)[1].split("    stop)\n", 1)[0] + "esac\n")
        result = self.run_script(body, "func_debugger", failure="host-core")
        self.assertEqual(2, result.returncode)
        self.assertIn("AGENT_ACTION: BLOCKED_TOOLING", result.stdout)
        self.assertNotIn("libraries:", result.stderr)
        self.assertNotIn("build:", result.stderr)

    def test_finish_materializes_asm_before_layout_and_fails_closed(self):
        body = SCRIPT.split("verify_and_record_match() {", 1)[1].split("prepare_next_work() {", 1)[0]
        body = "verify_and_record_match() {" + body + "verify_and_record_match\n"
        result = self.run_script(body)
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertEqual([
            "warm: python3 scripts/diff.py us func_debugger --auto-overlay --require-match",
            "warm: python3 scripts/prepare_nonmatching_asm.py --profile us --identifier func_debugger",
            "warm: python3 scripts/layout_check.py us func_debugger",
        ], result.stderr.splitlines())
        failed = self.run_script(body, failure="asm")
        self.assertEqual(3, failed.returncode)
        self.assertNotIn("layout_check.py", failed.stderr)

    def test_integration_stages_only_full_rom_libraries(self):
        body = "case progress in\n    progress)\n" + SCRIPT.split("    progress)\n", 1)[1].split("    normalize-source-headers)\n", 1)[0] + "esac\n"
        result = self.run_script(body, "integrate", "func_debugger")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertEqual([
            "libraries: make --silent --jobs 4 profile-libs PROFILE=us",
            "integrate: python3 scripts/integrate.py --profile us func_debugger",
        ], result.stderr.splitlines())

    def test_registration_refreshes_an_older_reference_without_debugger(self):
        body = ("mkdir -p \"$repo_root/reference/us/asm\"\n"
                + "case register-debugger in\n    register-debugger)\n"
                + SCRIPT.split("    register-debugger)\n", 1)[1].split("    record-region-size)\n", 1)[0]
                + "esac\n")
        result = self.run_script(body, "--id", "func_debugger", "--us", "func_16000000",
                                 "--source", "src/debugger/test.c")
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn("build: make prepare-reference PROFILE=us", result.stderr)


if __name__ == "__main__":
    unittest.main()
