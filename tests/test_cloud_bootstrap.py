"""ROM-free checks for the optional external-runtime cloud adapter source."""
from __future__ import annotations

import hashlib
import importlib.machinery
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
SOURCE = ROOT / 'toolchain/cloud-bootstrap'


def load_source(name, path):
    loader = importlib.machinery.SourceFileLoader(name, str(path))
    spec = importlib.util.spec_from_loader(name, loader)
    module = importlib.util.module_from_spec(spec)
    loader.exec_module(module)
    return module


bootstrap = load_source('cloud_bootstrap', SOURCE / 'bootstrap.py')
adapter = load_source('cloud_docker', SOURCE / 'bin/docker')
pull = load_source('cloud_pull_oci', SOURCE / 'pull_oci.py')


class CloudBootstrapTests(unittest.TestCase):
    def test_source_pins_match_repository(self):
        lock = json.loads((ROOT / 'toolchain/tools.lock.json').read_text())
        image = lock['container_image']
        expected = image['repository'] + '@' + image['digest']
        self.assertEqual(bootstrap.IMAGE, expected)
        self.assertEqual(adapter.BASE, expected)
        self.assertEqual('ghcr.io/' + pull.REPO + '@' + pull.DIGEST, expected)
        self.assertEqual(bootstrap.REV, lock['tools']['armips']['revision'])
        self.assertEqual(adapter.REV, bootstrap.REV)
        recipe = hashlib.sha256((ROOT / 'toolchain/rsp.Dockerfile').read_bytes()).hexdigest()
        receipt = json.loads((SOURCE / 'provenance/armips.json').read_text())
        self.assertEqual(bootstrap.DOCKERFILE_HASH, recipe)
        self.assertEqual(receipt['dockerfile_sha256'], recipe)
        self.assertEqual(receipt['revision'], bootstrap.REV)

    def test_runtime_must_be_disjoint_from_checkouts(self):
        with patch.object(bootstrap, 'HOME', Path('/work/runtime')):
            bootstrap.validate_runtime_location([Path('/work/repo')])
            for root in ('/work/runtime', '/work', '/work/runtime/repo'):
                with self.subTest(root=root), self.assertRaisesRegex(RuntimeError, 'outside'):
                    bootstrap.validate_runtime_location([Path(root)])

    def test_adapter_rejects_unknown_security_options(self):
        for option in ('--privileged', '--not-a-security-boundary', '--net', '--volume'):
            with self.subTest(option=option), self.assertRaisesRegex(RuntimeError, 'Unsupported'):
                adapter.parse_options([option, 'anything'])

    def test_launch_rejects_weaker_security_values_before_execution(self):
        cases = {'network': 'host', 'capdrop': 'NONE', 'security': 'none',
                 'pids': '9999', 'platform': 'linux/arm64', 'user': '0:0'}
        with patch.object(adapter, 'image', return_value={'Config': {}, 'armips': False}), \
             patch.object(adapter.os, 'execv') as execute:
            for key, value in cases.items():
                with self.subTest(key=key), self.assertRaisesRegex(RuntimeError, 'Unsupported'):
                    adapter.launch({key: value}, adapter.BASE, ['true'])
            execute.assert_not_called()

    def test_bind_sources_resolve_within_explicit_checkout(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            repo = root / 'repo'
            repo.mkdir()
            outside = root / 'private'
            outside.mkdir()
            (repo / 'escape').symlink_to(outside, target_is_directory=True)
            with patch.object(adapter, 'load', return_value=[str(repo)]):
                self.assertEqual(adapter.validate_source(repo), repo)
                for path in (outside, repo / 'escape'):
                    with self.subTest(path=path), self.assertRaisesRegex(RuntimeError, 'outside'):
                        adapter.validate_source(path)

    def test_no_runtime_payloads_are_part_of_source(self):
        for name in ('state', 'oci', 'rootfs', 'armips', 'cmake-package'):
            self.assertFalse((SOURCE / name).exists(), name)


if __name__ == '__main__':
    unittest.main()
