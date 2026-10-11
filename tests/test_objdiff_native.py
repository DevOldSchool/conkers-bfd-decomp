import hashlib
import json
from pathlib import Path
import platform
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_native as native


class NativeDataTests(unittest.TestCase):
    def test_pinned_patch_hash_and_upstream_revision(self):
        lock = json.loads((ROOT / 'toolchain/tools.lock.json').read_text())['objdiff_cli']['source_build']
        self.assertRegex(lock['revision'], '^[0-9a-f]{40}$')
        self.assertRegex(lock['archive_sha256'], '^[0-9a-f]{64}$')
        self.assertEqual(native.sha256(ROOT / lock['patch']), lock['patch_sha256'])

    def test_invalid_patch_is_rejected_before_build(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'patch').write_bytes(b'changed')
            with self.assertRaisesRegex(ValueError, 'patch checksum'):
                native.install_patched(root, {'source_build': {'patch': 'patch', 'patch_sha256': '0' * 64}})

    def test_native_anonymous_storage_and_relocation_regressions(self):
        lock = json.loads((ROOT / 'toolchain/tools.lock.json').read_text())['objdiff_cli']
        key = hashlib.sha256(json.dumps(lock['source_build'], sort_keys=True).encode()).hexdigest()[:16]
        binary = ROOT / 'build/host-tools' / ('objdiff-' + lock['version'] + '-' + key) / (
            'objdiff-cli-' + platform.system().lower() + '-' + platform.machine())
        if not binary.is_file():
            self.skipTest('patched native CLI unavailable on this host; installer runs this gate')
        native.verify_native(binary)
