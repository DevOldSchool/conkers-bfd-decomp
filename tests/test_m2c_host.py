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
