from __future__ import annotations

import hashlib
import json
import re
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import toolchain_inputs  # noqa: E402

SCRIPT = ROOT / "scripts" / "toolchain_inputs.py"
DIGEST = "sha256:" + "ab" * 32
LOCK = {
    "container_image": {"digest": DIGEST, "repository": "ghcr.io/example/toolchain"},
    "schema_version": 1,
    "tools": {"mips_to_c": {"repository": "https://example.invalid/m2c.git", "revision": "f" * 40}},
}
FILES = {
    "Dockerfile": b"FROM scratch\n",
    ".dockerignore": b"**\n!Dockerfile\n",
    "toolchain/mupen64plus-debug.sh": b"#!/bin/sh\n",
    "toolchain/python-constraints.txt": b"pyyaml==6.0.2\n",
    "toolchain/python-requirements.txt": b"pyyaml\n",
}


def make_checkout(root: Path, lock: dict = LOCK, files: dict[str, bytes] = FILES) -> None:
    for name, data in files.items():
        (root / name).parent.mkdir(parents=True, exist_ok=True)
        (root / name).write_bytes(data)
    (root / "toolchain").mkdir(exist_ok=True)
    (root / "toolchain/tools.lock.json").write_text(json.dumps(lock, indent=2) + "\n")


def run(root: Path, *args: str) -> subprocess.CompletedProcess:
    return subprocess.run([sys.executable, str(SCRIPT), "--root", str(root), *args],
                          capture_output=True, text=True)


class InputsHashTests(unittest.TestCase):
    def test_hash_is_sorted_path_nul_bytes_with_the_lock_minus_its_image_record(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            make_checkout(root)
            expected = hashlib.sha256()
            pins = {key: value for key, value in LOCK.items() if key != "container_image"}
            canonical = (json.dumps(pins, sort_keys=True, separators=(",", ":")) + "\n").encode()
            contents = dict(FILES, **{"toolchain/tools.lock.json": canonical})
            for name in sorted(contents):
                expected.update(name.encode() + b"\0" + contents[name])
            self.assertEqual(toolchain_inputs.inputs_hash(root), expected.hexdigest())

    def test_recording_a_new_image_does_not_change_the_hash_but_inputs_do(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            make_checkout(root)
            before = toolchain_inputs.inputs_hash(root)
            relocked = json.loads(json.dumps(LOCK))
            relocked["container_image"] = {"digest": "sha256:" + "cd" * 32, "repository": "ghcr.io/other/toolchain",
                                           "inputs_sha256": "0" * 64}
            (root / "toolchain/tools.lock.json").write_text(json.dumps(relocked, indent=2) + "\n")
            self.assertEqual(toolchain_inputs.inputs_hash(root), before)
            for name, data in (("Dockerfile", b"FROM scratch\nRUN true\n"), ("toolchain/python-requirements.txt", b"pyyaml\nrich\n")):
                make_checkout(root, files=dict(FILES, **{name: data}))
                self.assertNotEqual(toolchain_inputs.inputs_hash(root), before, name)
            pinned = json.loads(json.dumps(LOCK))
            pinned["tools"]["mips_to_c"]["revision"] = "e" * 40
            make_checkout(root, lock=pinned)
            self.assertNotEqual(toolchain_inputs.inputs_hash(root), before)

    def test_inputs_list_matches_the_publish_workflow_triggers(self):
        workflow = yaml.safe_load((ROOT / ".github/workflows/publish-toolchain.yml").read_text(encoding="utf-8"))
        paths = set(workflow[True]["push"]["paths"]) - {".github/workflows/publish-toolchain.yml"}
        self.assertEqual({path.as_posix() for path in toolchain_inputs.INPUTS}, paths)
        ignore = (ROOT / ".dockerignore").read_text(encoding="utf-8")
        for path in toolchain_inputs.INPUTS:
            if path.as_posix() != ".dockerignore" and path != toolchain_inputs.LOCK:
                self.assertIn(f"!{path.as_posix()}", ignore)


class CheckAndRecordTests(unittest.TestCase):
    def test_check_exit_status_covers_match_change_missing_field_and_missing_input(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            make_checkout(root)
            result = run(root, "check")
            self.assertEqual(result.returncode, 1, result.stdout)
            self.assertIn("records no inputs_sha256", result.stdout)

            result = run(root, "record", "--digest", DIGEST)
            self.assertEqual(result.returncode, 0, result.stderr)
            result = run(root, "check")
            self.assertEqual(result.returncode, 0, result.stdout)
            self.assertIn("match the published image", result.stdout)
            self.assertIn(f"ghcr.io/example/toolchain@{DIGEST}", result.stdout)
            self.assertEqual(run(root, "check", "--quiet").stdout, "")

            (root / "Dockerfile").write_bytes(b"FROM scratch\nRUN changed\n")
            result = run(root, "check")
            self.assertEqual(result.returncode, 1, result.stdout)
            self.assertIn("lock ", result.stdout)
            self.assertIn(" != checkout ", result.stdout)

            (root / "Dockerfile").unlink()
            result = run(root, "check")
            self.assertEqual(result.returncode, 1, result.stdout)
            self.assertIn("missing input", result.stdout)

    def test_record_writes_the_image_record_and_refuses_a_foreign_inputs_hash(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            make_checkout(root)
            current = toolchain_inputs.inputs_hash(root)
            new_digest = "sha256:" + "12" * 32
            result = run(root, "record", "--digest", new_digest, "--repository", "ghcr.io/example/other",
                         "--inputs-sha256", current)
            self.assertEqual(result.returncode, 0, result.stderr)
            lock = json.loads((root / "toolchain/tools.lock.json").read_text())
            self.assertEqual(lock["container_image"], {
                "digest": new_digest, "repository": "ghcr.io/example/other", "inputs_sha256": current})
            self.assertEqual(lock["tools"], LOCK["tools"])
            self.assertEqual(run(root, "image").stdout.strip(), f"ghcr.io/example/other@{new_digest}")
            self.assertEqual(run(root, "hash").stdout.strip(), current)

            result = run(root, "record", "--digest", DIGEST, "--inputs-sha256", "0" * 64)
            self.assertEqual(result.returncode, 1)
            self.assertIn("differs from this checkout", result.stderr)
            self.assertEqual(json.loads((root / "toolchain/tools.lock.json").read_text()), lock)

            result = run(root, "record", "--digest", "latest")
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("sha256:", result.stderr)


class RepositoryLockTests(unittest.TestCase):
    def test_repository_lock_records_a_well_formed_inputs_hash(self):
        image = toolchain_inputs.load_lock()["container_image"]
        self.assertRegex(image["digest"], re.compile(r"^sha256:[0-9a-f]{64}$"))
        self.assertRegex(image["inputs_sha256"], re.compile(r"^[0-9a-f]{64}$"))

    def test_wrapper_exposes_the_check_and_ci_pulls_only_on_a_match(self):
        script = (ROOT / "scripts/conker.sh").read_text(encoding="utf-8")
        self.assertIn("toolchain-inputs-check)", script)
        self.assertIn('scripts/toolchain_inputs.py" check "$@"', script)
        workflow = yaml.safe_load((ROOT / ".github/workflows/rom-verify-main.yml").read_text(encoding="utf-8"))
        self.assertEqual(workflow["concurrency"], {"group": "protected-rom-verification", "cancel-in-progress": True})
        steps = workflow["jobs"]["verify-main"]["steps"]
        toolchain = next(step for step in steps if "docker build " in step.get("run", ""))
        self.assertIn("./conker toolchain-inputs-check", toolchain["run"])
        self.assertIn('docker pull --platform linux/amd64 "$published"', toolchain["run"])
        self.assertIn('docker build --platform linux/amd64 --tag "$CONKER_IMAGE" .', toolchain["run"])
        self.assertLess(toolchain["run"].index("docker pull"), toolchain["run"].index("docker build"))
        publish = yaml.safe_load((ROOT / ".github/workflows/publish-toolchain.yml").read_text(encoding="utf-8"))
        record = publish["jobs"]["publish"]["steps"][-1]["run"]
        self.assertIn("scripts/toolchain_inputs.py hash", record)
        self.assertIn("--inputs-sha256", record)


if __name__ == "__main__":
    unittest.main()
