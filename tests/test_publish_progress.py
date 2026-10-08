from __future__ import annotations

from contextlib import redirect_stdout
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import publish_progress as publisher


class PublicOutputTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.output = Path(self.temporary.name) / "progress"
        self.output.mkdir()
        self.expected = {name: "public\n" for name in publisher.REPORT_FILES}
        for name, content in self.expected.items():
            (self.output / name).write_text(content)

    def files(self, **kwargs):
        return publisher.public_files(self.output, self.expected, "a" * 40,
                                      kwargs.get("run_id", "123"), "2")

    def test_deterministic_public_files_include_exact_source_and_run(self):
        files = self.files()
        self.assertEqual(files, self.files())
        self.assertEqual(publisher.PUBLIC_FILES, set(files))
        checkpoint = json.loads(files["checkpoint.json"])
        self.assertEqual("a" * 40, checkpoint["source_sha"])
        self.assertEqual("2", checkpoint["workflow_run_attempt"])
        self.assertTrue(checkpoint["workflow_run_url"].endswith("/runs/123/attempts/2"))
        self.assertEqual(publisher.REPORT_FILES, set(checkpoint["files_sha256"]))
        self.assertIn(checkpoint["workflow_run_url"], files["progress.md"])

    def test_extra_private_file_or_directory_is_rejected(self):
        for directory in (False, True):
            with self.subTest(directory=directory):
                extra = self.output / "private-build.log"
                extra.mkdir() if directory else extra.write_text("private")
                with self.assertRaisesRegex(ValueError, "unexpected or missing"):
                    self.files()
                extra.rmdir() if directory else extra.unlink()

    def test_missing_file_and_changed_public_filename_contents_are_rejected(self):
        path = self.output / "summary.json"
        path.unlink()
        with self.assertRaisesRegex(ValueError, "unexpected or missing"):
            self.files()
        path.write_text("private data disguised as summary")
        with self.assertRaisesRegex(ValueError, "differs from validated"):
            self.files()

    def test_file_and_output_directory_symlinks_are_rejected(self):
        path = self.output / "summary.json"
        path.unlink()
        path.symlink_to(self.output / "badge-us.json")
        with self.assertRaisesRegex(ValueError, "regular bounded"):
            self.files()
        alias = self.output.parent / "alias"
        alias.symlink_to(self.output, target_is_directory=True)
        with self.assertRaisesRegex(ValueError, "directory or allowlist"):
            publisher.public_files(alias, self.expected, "a" * 40, "123", "1")

    def test_invalid_provenance_and_allowlist_fail(self):
        with self.assertRaisesRegex(ValueError, "positive workflow"):
            self.files(run_id="../123")
        self.expected["extra"] = "data"
        with self.assertRaisesRegex(ValueError, "allowlist"):
            self.files()

    def test_cli_refuses_pr_or_fork_context_before_git_or_credentials(self):
        env = {"GITHUB_ACTIONS": "true", "GITHUB_REPOSITORY": publisher.REPOSITORY,
               "GITHUB_REF": "refs/heads/main", "GITHUB_EVENT_NAME": "push"}
        for change in ({"GITHUB_REF": "refs/pull/1/merge"},
                       {"GITHUB_EVENT_NAME": "pull_request_target"},
                       {"GITHUB_REPOSITORY": "contributor/fork"}):
            with self.subTest(change=change), patch.dict(os.environ, {**env, **change}, clear=True):
                with self.assertRaisesRegex(ValueError, "approved main workflow"):
                    publisher.main()


class PublicationGitTests(unittest.TestCase):
    """Real local Git transport exercises ordering, CAS and first publication."""

    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name) / "source"
        self.remote = Path(self.temporary.name) / "remote.git"
        self.root.mkdir()
        publisher.git(self.root, "init", "-q", "-b", "main")
        publisher.git(self.root, "config", "user.name", "Test")
        publisher.git(self.root, "config", "user.email", "test@example.invalid")
        publisher.git(self.root, "init", "--bare", "-q", str(self.remote))
        publisher.git(self.root, "remote", "add", "origin", str(self.remote))
        self.source_a = self.advance("A")
        self.source_b = self.advance("B")

    def advance(self, content):
        (self.root / "source.txt").write_text(content)
        publisher.git(self.root, "add", "source.txt")
        publisher.git(self.root, "commit", "-qm", content)
        publisher.git(self.root, "push", "-q", "origin", "HEAD:refs/heads/main")
        return publisher.git(self.root, "rev-parse", "HEAD")

    def files(self, source):
        output = Path(self.temporary.name) / "reports"
        output.mkdir(exist_ok=True)
        expected = {name: f"public {source}\n" for name in publisher.REPORT_FILES}
        for name, content in expected.items():
            (output / name).write_text(content)
        return publisher.public_files(output, expected, source, "123", "1")

    def publish(self, source):
        publisher.git(self.root, "checkout", "-q", "--detach", source)
        with redirect_stdout(io.StringIO()):
            return publisher.publish(self.root, self.files(source), source)

    def test_bootstrap_and_forward_update_preserve_source_and_only_publish_allowlist(self):
        first = self.publish(self.source_a)
        self.assertEqual(first, publisher.remote_head(self.root, publisher.REPORT_REF))
        self.assertEqual([first], publisher.git(self.root, "rev-list", "--parents", "-1", first).split())
        second = self.publish(self.source_b)
        self.assertEqual(first, publisher.git(self.root, "rev-parse", second + "^"))
        identity = publisher.git(self.root, "show", "-s", "--format=%an <%ae>%n%cn <%ce>", second)
        self.assertEqual(["DevOldSchool-AI-Agent <267263626+DevOldSchool-AI-Agent@users.noreply.github.com>"] * 2, identity.splitlines())
        self.assertEqual(publisher.PUBLIC_FILES, set(publisher.git(self.root, "ls-tree", "--name-only", second).splitlines()))
        self.assertEqual(self.source_b, publisher.remote_head(self.root, "refs/heads/main"))
        self.assertEqual(self.source_b, publisher.git(self.root, "rev-parse", "HEAD"))
        self.assertEqual("", publisher.git(self.root, "status", "--porcelain"))

    def test_same_source_and_out_of_order_runs_leave_newer_checkpoint_untouched(self):
        current = self.publish(self.source_b)
        self.assertIsNone(self.publish(self.source_b))
        self.assertIsNone(self.publish(self.source_a))
        self.assertEqual(current, publisher.remote_head(self.root, publisher.REPORT_REF))

    def test_non_main_source_dirty_checkout_and_wrong_head_are_rejected(self):
        with self.assertRaisesRegex(ValueError, "clean checkout"):
            publisher.publish(self.root, self.files(self.source_a), self.source_a)
        (self.root / "source.txt").write_text("dirty")
        with self.assertRaisesRegex(ValueError, "clean checkout"):
            publisher.publish(self.root, self.files(self.source_b), self.source_b)
        publisher.git(self.root, "commit", "-qam", "unpublished source")
        source = publisher.git(self.root, "rev-parse", "HEAD")
        with self.assertRaisesRegex(ValueError, "not in current main"):
            publisher.publish(self.root, self.files(source), source)
        self.assertIsNone(publisher.remote_head(self.root, publisher.REPORT_REF))

    def test_divergent_published_source_is_rejected(self):
        publisher.git(self.root, "checkout", "-q", "--detach", self.source_a)
        (self.root / "source.txt").write_text("divergent")
        publisher.git(self.root, "commit", "-qam", "divergent")
        other = publisher.git(self.root, "rev-parse", "HEAD")
        with self.assertRaisesRegex(ValueError, "histories diverge"):
            publisher.should_publish(self.root, self.source_b, other)

    def test_unexpected_existing_report_files_fail_closed(self):
        publisher.git(self.remote, "update-ref", publisher.REPORT_REF, self.source_a)
        with self.assertRaisesRegex(ValueError, "unexpected files"):
            self.publish(self.source_b)
        self.assertEqual(self.source_a, publisher.remote_head(self.root, publisher.REPORT_REF))

    def test_commit_builder_rejects_extra_output(self):
        with self.assertRaisesRegex(ValueError, "only the five"):
            publisher.create_commit(self.root, {**self.files(self.source_b), "private.log": "x"}, None, self.source_b)

    def test_expected_head_protects_against_rewind_even_when_push_would_fast_forward(self):
        first = self.publish(self.source_a)
        second = self.publish(self.source_b)
        candidate = publisher.create_commit(self.root, self.files(self.source_b), second, self.source_b)
        # Simulate an external report-branch rewind in this disposable bare repo.
        publisher.git(self.remote, "update-ref", publisher.REPORT_REF, first, second)
        with self.assertRaises(subprocess.CalledProcessError):
            publisher.push_checkpoint(self.root, candidate, second)
        self.assertEqual(first, publisher.remote_head(self.root, publisher.REPORT_REF))

    def test_expected_head_protects_against_deletion_and_first_publication_races(self):
        first = self.publish(self.source_a)
        candidate = publisher.create_commit(self.root, self.files(self.source_b), first, self.source_b)
        with self.assertRaises(subprocess.CalledProcessError):
            publisher.push_checkpoint(self.root, candidate, None)
        publisher.git(self.remote, "update-ref", "-d", publisher.REPORT_REF, first)
        with self.assertRaises(subprocess.CalledProcessError):
            publisher.push_checkpoint(self.root, candidate, first)
        self.assertIsNone(publisher.remote_head(self.root, publisher.REPORT_REF))


if __name__ == "__main__":
    unittest.main()
