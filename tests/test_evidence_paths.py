from pathlib import Path
import json
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import evidence_paths


class EvidencePathsTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.old = "docs/evidence/claim.md"
        self.new = "docs/evidence/matching/claim.md"
        self.mapping = {self.old: self.new}
        self.contents = {
            self.old: "# Claim\n[Guide](../README.md#rules)\n[Source](../../src/a.c)\n",
            "docs/README.md": "[Claim](evidence/claim.md#proof)\n[ref]: evidence/claim.md\n",
            "src/a.c": f"/* Evidence: {self.old}. */\nvoid a(void) {{}}\n",
            "progress/functions.json": json.dumps({"state": "matched", "score": 0,
                                                    "evidence": self.old}),
        }
        for name, content in self.contents.items():
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content)
        mock = patch.object(evidence_paths, "tracked_files", return_value=list(self.contents))
        mock.start()
        self.addCleanup(mock.stop)
        ignored = patch.object(evidence_paths, "ignored_paths", return_value=[])
        ignored.start()
        self.addCleanup(ignored.stop)

    def assert_unchanged(self):
        for name, content in self.contents.items():
            self.assertEqual((self.root / name).read_text(), content)

    def test_dry_run_does_not_write(self):
        self.assertEqual(evidence_paths.relocate(self.root, self.mapping), (1, 4))
        self.assert_unchanged()
        self.assertFalse((self.root / self.new).exists())

    def test_moves_rebase_links_and_preserve_state(self):
        evidence_paths.relocate(self.root, self.mapping, apply=True)
        self.assertFalse((self.root / self.old).exists())
        self.assertEqual((self.root / self.new).read_text(),
                         "# Claim\n[Guide](../../README.md#rules)\n[Source](../../../src/a.c)\n")
        self.assertEqual((self.root / "docs/README.md").read_text(),
                         "[Claim](evidence/matching/claim.md#proof)\n[ref]: evidence/matching/claim.md\n")
        self.assertEqual((self.root / "src/a.c").read_text(),
                         self.contents["src/a.c"].replace(self.old, self.new))
        state = json.loads((self.root / "progress/functions.json").read_text())
        self.assertEqual(state, {"state": "matched", "score": 0, "evidence": self.new})

    def test_collision_and_traversal_fail_before_writes(self):
        for destination in (self.old, "docs/evidence/../../outside.md", "/tmp/out.md"):
            with self.subTest(destination=destination), self.assertRaises(ValueError):
                evidence_paths.relocate(self.root, {self.old: destination}, apply=True)
            self.assert_unchanged()

    def test_ignored_destination_fails_before_writes(self):
        with patch.object(evidence_paths, "ignored_paths", return_value=[self.new]):
            with self.assertRaisesRegex(ValueError, "ignored by Git"):
                evidence_paths.relocate(self.root, self.mapping, apply=True)
        self.assert_unchanged()
        self.assertFalse((self.root / self.new).exists())

    def test_failed_unlink_rolls_back_all_files(self):
        unlink = Path.unlink
        def fail_once(path, *args, **kwargs):
            if path == self.root / self.old:
                raise OSError("injected failure")
            return unlink(path, *args, **kwargs)
        with patch.object(Path, "unlink", fail_once), self.assertRaisesRegex(OSError, "injected"):
            evidence_paths.relocate(self.root, self.mapping, apply=True)
        self.assert_unchanged()
        self.assertFalse((self.root / self.new).exists())

    def test_prefixes_external_links_and_fragments_are_preserved(self):
        content = (f"`{self.old}.backup` `{self.old}`\n"
                   "[web](https://example.com/docs/evidence/claim.md) [local](#proof)\n")
        result = evidence_paths.rewrite(content, self.old, self.new, self.mapping)
        self.assertEqual(result, content.replace(f"`{self.old}`", f"`{self.new}`"))


if __name__ == "__main__":
    unittest.main()
