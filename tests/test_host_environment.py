from pathlib import Path
import importlib.metadata
import os
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import host_environment as host


class HostEnvironmentTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(); self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name); (self.root / "toolchain").mkdir()
        self.path = self.root / "toolchain/python-requirements.txt"
        self.path.write_text("".join(name + "==1.2.3\n" for name in host.MODULES))

    def test_exact_complete_unique_pins_required(self):
        self.assertEqual(set(host.MODULES), set(host.requirements(self.root)))
        original = self.path.read_text()
        for text in ["numpy>=1\n", original + "numpy==1.2.3\n", "numpy==1.2.3\n"]:
            self.path.write_text(text)
            with self.assertRaises(ValueError): host.requirements(self.root)

    def test_all_missing_stale_and_broken_imports_reported_with_remedy(self):
        with patch.object(host.importlib.metadata, "version", side_effect=importlib.metadata.PackageNotFoundError("fixture")), patch.object(host.importlib, "import_module") as imports:
            errors = host.check(self.root)
            self.assertEqual(len(host.MODULES)+1, len(errors)); imports.assert_not_called()
        with patch.object(host.importlib.metadata, "version", return_value="old"):
            self.assertIn("expected 1.2.3, found old", host.check(self.root)[0])
        with patch.object(host.importlib.metadata, "version", return_value="1.2.3"), patch.object(host.importlib, "import_module", side_effect=OSError("shared library unavailable")):
            errors = host.check(self.root)
            self.assertIn("shared library unavailable", errors[0]); self.assertIn("./conker host-setup", errors[-1])

    def test_setup_installs_and_verifies_only_isolated_environment(self):
        with patch.object(host.venv, "EnvBuilder") as builder, patch.object(host.subprocess, "run") as run:
            host.setup(self.root)
            builder.assert_called_once_with(with_pip=True)
            builder.return_value.create.assert_called_once_with(self.root/"build/host-python")
            calls = [call.args[0] for call in run.call_args_list]
            python = str(self.root/"build/host-python/bin/python3")
            self.assertEqual(calls[0], [python,"-m","pip","install","--requirement",str(self.path)])
            self.assertEqual(calls[1], [python,str(self.root/"scripts/host_environment.py"),"check"])
            self.assertTrue(all(call.kwargs["check"] for call in run.call_args_list))

    def test_launcher_automatically_selects_managed_python(self):
        (self.root/"scripts").mkdir(); (self.root/"scripts/conker.sh").write_text('#!/usr/bin/env bash\ncommand -v python3\n')
        (self.root/"scripts/conker.sh").chmod(0o755)
        launcher=self.root/"conker"; launcher.write_bytes((ROOT/"conker").read_bytes()); launcher.chmod(0o755)
        python=self.root/"build/host-python/bin/python3"; python.parent.mkdir(parents=True)
        python.write_text('#!/bin/sh\nexit 0\n'); python.chmod(0o755)
        environment={k:v for k,v in os.environ.items() if k!="CONKER_IN_CONTAINER"}
        result=subprocess.run([str(launcher),"host-check"],capture_output=True,text=True,check=True,env=environment)
        self.assertEqual(str(python),result.stdout.strip())
        # Inside the toolchain container the host venv is never selected.
        result=subprocess.run([str(launcher),"host-check"],capture_output=True,text=True,check=True,
                              env=dict(environment,CONKER_IN_CONTAINER="1"))
        self.assertNotEqual(str(python),result.stdout.strip())


if __name__ == "__main__": unittest.main()
