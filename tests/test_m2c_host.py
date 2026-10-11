from __future__ import annotations

import os
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


class HostM2CTests(unittest.TestCase):
    def run_wrapper(self, override: str | None, cwd: Path):
        script = (ROOT / "scripts/conker.sh").read_text()
        function = "run_host_mips_to_c() {" + script.split("run_host_mips_to_c() {", 1)[1].split("\n}", 1)[0] + "\n}\n"
        harness = r'''set -euo pipefail
host_mips_to_c=/pinned
ensure_host_mips_to_c() { printf 'cache\n'; }
die() { printf '%s\n' "$*" >&2; exit 1; }
python3() { printf '%s\n' "$CONKER_MIPS_TO_C" "$PYTHONPATH" "$CONKER_HOST_M2C" "$@"; }
'''
        env = {k: v for k, v in os.environ.items() if k not in {"CONKER_MIPS_TO_C", "PYTHONPATH"}}
        env["PYTHONPATH"] = "/existing"
        if override is not None:
            env["CONKER_MIPS_TO_C"] = override
        return subprocess.run(["bash", "-c", harness + function + 'run_host_mips_to_c us func_test'], cwd=cwd, env=env, capture_output=True, text=True)

    def test_default_still_uses_pinned_cache(self):
        result = self.run_wrapper(None, ROOT)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.splitlines()[:4], ["cache", "/pinned/m2c.py", "/pinned:/existing", "1"])

    def test_override_handles_relative_path_spaces_and_python_imports(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder).resolve()
            tool = root / "fork with spaces"
            tool.mkdir()
            (tool / "m2c").mkdir()
            (tool / "m2c.py").touch()
            result = self.run_wrapper("fork with spaces/m2c.py", root)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(result.stdout.splitlines(), [str(tool / "m2c.py"), f"{tool}:/existing", "1", "scripts/m2c.py", "us", "func_test"])

    def test_invalid_override_does_not_fall_back(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / "m2c.py").touch()
            for override in (str(root / "missing.py"), str(root / "m2c.py")):
                with self.subTest(override=override):
                    result = self.run_wrapper(override, root)
                    self.assertNotEqual(result.returncode, 0)
                    self.assertEqual(result.stdout, "")
                    self.assertIn("CONKER_MIPS_TO_C", result.stderr)


class HostM2CCacheRevisionTests(unittest.TestCase):
    """The host cache must be keyed by the revision actually copied from the image."""

    def run_cache(self, pinned: str, folder: Path):
        image = folder / "image"
        (image / "m2c").mkdir(parents=True)
        (image / "m2c.py").touch()
        git = ["git", "-C", str(image), "-c", "user.name=t", "-c", "user.email=t@t"]
        subprocess.run(["git", "init", "-q", str(image)], check=True)
        subprocess.run([*git, "add", "-A"], check=True)
        subprocess.run([*git, "commit", "-qm", "image"], check=True)
        copied = subprocess.check_output([*git, "rev-parse", "HEAD"], text=True).strip()
        script = (ROOT / "scripts/conker.sh").read_text()
        function = "ensure_host_mips_to_c() {" + script.split("ensure_host_mips_to_c() {", 1)[1].split("\n}", 1)[0] + "\n}\n"
        harness = f'''set -euo pipefail
repo_root={folder}
mips_to_c_revision={pinned or copied}
host_mips_to_c="$repo_root/build/host-tools/mips_to_c-$mips_to_c_revision"
warm_container_name=test
ensure_warm_container() {{ :; }}
docker() {{ cp -R {image}/. "$3"; }}
die() {{ printf '%s\\n' "$*" >&2; exit 1; }}
'''
        result = subprocess.run(["bash", "-c", harness + function + 'ensure_host_mips_to_c; printf "%s\\n" "$host_mips_to_c"'],
                                capture_output=True, text=True)
        return result, copied

    def test_matching_image_revision_uses_pinned_cache(self):
        with tempfile.TemporaryDirectory() as folder:
            result, copied = self.run_cache("", Path(folder))
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(result.stdout.strip(), f"{folder}/build/host-tools/mips_to_c-{copied}")
            self.assertEqual(result.stderr, "")

    def test_stale_image_revision_is_not_cached_under_the_pin(self):
        with tempfile.TemporaryDirectory() as folder:
            pinned = "a" * 40
            result, copied = self.run_cache(pinned, Path(folder))
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(result.stdout.strip(), f"{folder}/build/host-tools/mips_to_c-{copied}")
            self.assertIn(f"provides mips_to_c {copied}, not pinned {pinned}", result.stderr)
            self.assertFalse((Path(folder) / f"build/host-tools/mips_to_c-{pinned}").exists())
            self.assertTrue((Path(folder) / f"build/host-tools/mips_to_c-{copied}/m2c.py").is_file())
