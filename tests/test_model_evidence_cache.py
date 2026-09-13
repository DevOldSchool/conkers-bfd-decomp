import hashlib
import json
from pathlib import Path
import tempfile
import unittest

from scripts.model_evidence_cache import ContentSnapshot, source_identity
from scripts.model_preview_evidence import preview_fingerprint


class EvidenceCacheTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.geometry = self.root / 'geometry'
        self.geometry.mkdir()
        (self.root / 'textures').mkdir()
        self.texture = self.root / 'textures/shared.png'
        self.texture.write_bytes(b'pixels')
        self.paths = [self.geometry / (name + '.gltf') for name in ('a', 'b')]
        for path in self.paths:
            path.write_text(json.dumps({'images': [{'uri': '../textures/shared.png'}]}))

    def test_shared_input_read_once_and_matches_independent_worker(self):
        snapshot = ContentSnapshot()
        for _ in range(3):
            for path in self.paths:
                self.assertEqual(preview_fingerprint(path), snapshot.fingerprint(path))
        self.assertEqual(3, snapshot.read_count)
        after = ContentSnapshot()
        self.assertEqual([], snapshot.verify(after))
        self.assertEqual(3, after.read_count)

    def test_changed_and_deleted_shared_inputs_fail_final_verification(self):
        snapshot = ContentSnapshot()
        snapshot.fingerprint(self.paths[0])
        self.texture.write_bytes(b'changed')
        self.assertEqual([str(self.texture)], snapshot.verify(ContentSnapshot()))
        self.texture.unlink()
        self.assertEqual([str(self.texture)], snapshot.verify(ContentSnapshot()))

    def test_change_between_digest_and_document_read_is_not_masked(self):
        snapshot = ContentSnapshot()
        snapshot.digest(self.paths[0])
        self.paths[0].write_text('{}')
        with self.assertRaisesRegex(ValueError, 'changed within'):
            snapshot.fingerprint(self.paths[0])

    def test_path_rules_match_worker_including_symlink_escape(self):
        with tempfile.TemporaryDirectory() as outside:
            target = Path(outside) / 'pixels'; target.write_bytes(b'x')
            (self.root / 'textures/escape').symlink_to(target)
            for uri in ('https://example.com/x', '/absolute', '../../../outside',
                        '../textures/shared.png?q=1', '../textures/escape'):
                self.paths[0].write_text(json.dumps({'images': [{'uri': uri}]}))
                for fingerprint in (ContentSnapshot().fingerprint, preview_fingerprint):
                    with self.assertRaises(ValueError):
                        fingerprint(self.paths[0])

    def test_dependency_closure_includes_lazy_imports_but_not_unrelated_tools(self):
        scripts = self.root / 'scripts'; scripts.mkdir()
        (scripts / 'entry.py').write_text('def f():\n from scripts import helper\n')
        (scripts / 'helper.py').write_text('from scripts.leaf import run\n')
        (scripts / 'leaf.py').write_text('run = 1\n')
        (scripts / 'unrelated.py').write_text('x = 1\n')
        digest = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
        before = source_identity(self.root, ['scripts/entry.py'], digest)
        (scripts / 'unrelated.py').write_text('x = 2\n')
        self.assertEqual(before, source_identity(self.root, ['scripts/entry.py'], digest))
        (scripts / 'leaf.py').write_text('run = 2\n')
        self.assertNotEqual(before, source_identity(self.root, ['scripts/entry.py'], digest))
        (scripts / 'entry.py').write_text('__import__(name)\n')
        self.assertIn('scripts/unrelated.py', source_identity(self.root, ['scripts/entry.py'], digest))
