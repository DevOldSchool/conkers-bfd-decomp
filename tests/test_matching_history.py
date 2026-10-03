from __future__ import annotations

from contextlib import redirect_stdout
import io
import json
import os
from pathlib import Path
import stat
import subprocess
import select
import signal
import sys
import tempfile
import unittest
from unittest.mock import patch
import zipfile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import matching_history as history


class MatchingHistoryTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.entry = {"symbol": "func_test", "source": "src/test.c", "overlay": "game",
                      "regions": {"us": {"symbol": "func_test", "vram": "0x15000000",
                                         "size_bytes": 8, "state": "raw_asm"}}}
        self.write("progress/functions.json", json.dumps({"functions": [self.entry]}))
        self.write("src/test.c", "void func_test(void) { return; }\nvoid neighbor(void) {}\n")
        self.write("reference/game/us/asm/game.s", "glabel func_test\n/* independent raw */\n")
        self.child("print('func_test: CURRENT (42)')\nprint('AGENT_ACTION: CONTINUE_MISMATCH')\nraise SystemExit(1)\n")

    def write(self, name, text):
        path = self.root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
        return path

    def child(self, code):
        path = self.write("conker", f"#!{sys.executable}\n" + code)
        path.chmod(0o755)

    def record(self):
        with redirect_stdout(io.StringIO()):
            status = history.record(self.root, "func_test")
        return status, history.records(self.root, "func_test")[-1]

    def show(self, **kwargs):
        output = io.StringIO()
        with redirect_stdout(output):
            history.summarize(self.root, "func_test", **kwargs)
        return output.getvalue()

    def test_attempt_preserves_exact_target_and_exit_without_inventory_changes(self):
        original = (self.root / "progress/functions.json").read_bytes()
        status, row = self.record()
        self.assertEqual(1, status)
        self.assertEqual(42, row["score"])
        self.assertEqual("CONTINUE_MISMATCH", row["status"])
        self.assertEqual("not_recorded_by_history", row["acceptance"])
        self.assertEqual("void func_test(void) { return; }\n", (row["directory"] / "function.c").read_text())
        self.assertEqual(original, (self.root / "progress/functions.json").read_bytes())
        self.assertIn("lowest-observed: CURRENT (42) [unreviewed]", self.show())

    def test_compile_failure_never_reuses_stale_score_or_diff(self):
        self.record()
        self.write("build/us/diff/func_test/mismatch.json", '{"current_score": 42}')
        self.child("print('AGENT_ACTION: FIX_COMPILE')\nraise SystemExit(2)\n")
        status, row = self.record()
        self.assertEqual(2, status)
        self.assertIsNone(row["score"])
        self.assertFalse((row["directory"] / "mismatch.json").exists())
        latest = next(line for line in self.show().splitlines() if line.startswith("latest-recorded-finish:"))
        self.assertIn("FIX_COMPILE", latest)
        self.assertNotIn("CURRENT", latest)

    def test_only_fresh_emitted_diagnostics_are_archived(self):
        self.child("from pathlib import Path\np=Path('build/us/diff/func_test/mismatch.json')\n"
                   "p.parent.mkdir(parents=True,exist_ok=True)\np.write_text('{\"current_score\":42}')\n"
                   "print('func_test: CURRENT (42)')\nprint('diff-evidence: build/us/diff/func_test/mismatch.json')\n"
                   "print('AGENT_ACTION: CONTINUE_MISMATCH')\nraise SystemExit(1)\n")
        _, row = self.record()
        self.assertTrue((row["directory"] / "mismatch.json").is_file())

    def test_focused_zero_with_layout_failure_is_not_match_acceptance(self):
        self.child("print('other_function: CURRENT (7)')\nprint('func_test: CURRENT (0)')\n"
                   "print('AGENT_ACTION: CONTINUE_MISMATCH')\nraise SystemExit(1)\n")
        status, row = self.record()
        self.assertEqual((1, 0, "CONTINUE_MISMATCH"), (status, row["score"], row["status"]))
        self.assertEqual("not_recorded_by_history", row["acceptance"])
        self.assertIn("latest-recorded-finish: CONTINUE_MISMATCH CURRENT (0)", self.show())
        self.assertNotIn("latest-recorded-finish: STOP_MATCHED", self.show())

    def test_successful_todo_cleanup_still_shows_recorded_gate_without_relaxing_comparison(self):
        source = self.root / "src/test.c"
        source.write_text("/*\n * TODO:\n * - func_test\n */\n" + source.read_text())
        self.child("from pathlib import Path\np=Path('src/test.c')\n"
                   "p.write_text(p.read_text().replace(' * - func_test\\n', ''))\n"
                   "print('func_test: CURRENT (0)')\nprint('AGENT_ACTION: STOP_MATCHED')\n")
        status, row = self.record()
        self.assertEqual(0, status)
        self.assertFalse(row["target_changed"])
        self.assertNotEqual(row["source_sha256"], row["source_after_sha256"])
        self.assertNotEqual(row["context_fingerprint"], row["context_after_fingerprint"])
        output = self.show()
        self.assertIn("latest-recorded-finish: STOP_MATCHED CURRENT (0); target=current; "
                      "context=changed-during-finish", output)
        self.assertIn("historical evidence, not current verification or BATCH_COMPLETE", output)
        self.assertNotIn("lowest-observed", output)

    def test_old_zero_stays_historical_after_input_change_and_does_not_hide_latest_failure(self):
        self.child("print('func_test: CURRENT (0)')\nprint('AGENT_ACTION: STOP_MATCHED')\n")
        self.record()
        self.write("config/settings.json", '{}\n')
        output = self.show()
        self.assertIn("latest-recorded-finish: STOP_MATCHED CURRENT (0); target=current; context=historical", output)
        self.assertNotIn("lowest-observed", output)
        self.child("print('AGENT_ACTION: FIX_COMPILE')\nraise SystemExit(2)\n")
        self.record()
        latest = next(line for line in self.show().splitlines() if line.startswith("latest-recorded-finish:"))
        self.assertIn("FIX_COMPILE", latest)
        self.assertNotIn("STOP_MATCHED", latest)
        self.assertNotIn("CURRENT", latest)

    def test_failed_extraction_and_macro_alias_keep_full_source(self):
        self.write("src/test.c", "void func_test(void) {\n")
        _, row = self.record()
        self.assertIsNone(row["function_sha256"])
        self.assertTrue((row["directory"] / "source.c").is_file())
        self.assertNotIn("lowest-observed", self.show())
        self.write("src/test.c", "#define local_name func_test\nvoid local_name(void) {}\n")
        _, row = self.record()
        self.assertIn("local_name", (row["directory"] / "function.c").read_text())

    def test_context_reference_and_mapping_changes_prevent_score_comparison(self):
        _, row = self.record()
        self.assertIn("reference/game/us/asm/game.s", row["reference_files"])
        self.write("config/game/us-symbols.ld", "changed = 1;\n")
        self.assertNotIn("lowest-observed", self.show(current_score=100))
        self.assertIn("context=historical", self.show())
        (self.root / "config/game/us-symbols.ld").unlink()
        self.write("reference/game/us/asm/game.s", "glabel func_test\n/* changed raw */\n")
        self.assertNotIn("lowest-observed", self.show())

    def test_invalid_best_is_excluded_and_history_remains_after_continuation(self):
        _, row = self.record()
        history.annotate(self.root, "func_test", row["attempt_id"], assessment="invalid",
                         hypothesis="wrong pointer stride", expected="four-byte advance", exhausted=True)
        self.assertNotIn("lowest-observed", self.show())
        self.assertIn("does not reset prior work", self.show())
        _, another = self.record()
        self.assertNotEqual(row["attempt_id"], another["attempt_id"])
        self.assertIn("2 finish calls, 1 distinct inputs", self.show())

    def test_source_drift_is_explicit_and_never_best(self):
        self.child("from pathlib import Path\nPath('src/test.c').write_text('void func_test(void) { int a; }\\n')\n"
                   "print('func_test: CURRENT (0)')\nprint('AGENT_ACTION: STOP_MATCHED')\n")
        _, row = self.record()
        self.assertTrue(row["target_changed"])
        self.assertNotIn("lowest-observed", self.show())
        self.assertIn("target=changed-during-finish", self.show())

    def test_start_without_result_is_visible_as_interrupted(self):
        _, row = self.record()
        (row["directory"] / "result.json").unlink()
        self.assertIn("status=interrupted", self.show())

    def test_signaled_child_keeps_raw_status_and_shell_exit_convention(self):
        self.child("import os,signal\nos.kill(os.getpid(),signal.SIGTERM)\n")
        status, row = self.record()
        self.assertEqual(143, status)
        self.assertEqual(-15, row["return_code"])

    def test_ready_baseline_and_later_attempts_report_changed_prototypes(self):
        self.write("src/test.c", "extern int callee(int);\nvoid func_test(void) {}\n")
        history.prepare(self.root, "func_test")
        self.write("src/test.c", "extern int callee(float);\nvoid func_test(void) {}\n")
        _, row = self.record()
        self.assertEqual(["callee"], row["changed_declarations"])
        self.write("src/test.c", "extern int callee(float);\nvoid func_test(void) { int a; }\n")
        _, row = self.record()
        self.assertEqual([], row["changed_declarations"])

    def test_pure_additions_are_recorded_without_global_caller_lookup_or_reminder(self):
        self.write("src/test.c", 'void neighbor(void) {}\n#pragma GLOBAL_ASM("raw.s")\n')
        history.prepare(self.root, "func_test")
        self.write("src/test.c", 'void neighbor(void) {}\nvoid callee(u8);\n'
                   'void func_test(void) { callee(1); }\n')
        output = io.StringIO()
        with redirect_stdout(output), patch.object(history.matching_callers, "affected_callers",
                                                   side_effect=AssertionError("no global caller scan")):
            history.record(self.root, "func_test")
        row = history.records(self.root, "func_test")[-1]
        self.assertEqual(['callee', 'func_test'], row['declaration_review']['added'])
        self.assertEqual([], row['changed_declarations'])
        self.assertEqual([], row['caller_review_symbols'])
        self.assertIn('declaration-additions: callee, func_test', output.getvalue())
        self.assertNotIn('caller-review:', output.getvalue())

    def test_caller_reminder_contains_only_changes_and_additions_used_by_existing_code(self):
        self.write("src/test.c", 'void changed(s32); void removed(void);\n'
                   'void neighbor(void) { added(1); changed(2); }\n'
                   '#pragma GLOBAL_ASM("raw.s")\n')
        history.prepare(self.root, "func_test")
        self.write("src/test.c", 'void changed(u8); void added(u8); void fresh(u8);\n'
                   'void neighbor(void) { added(1); changed(2); }\n'
                   'void func_test(void) { fresh(1); }\n')
        output = io.StringIO()
        with redirect_stdout(output), patch.object(history.matching_callers, "affected_callers",
                                                   side_effect=AssertionError("no global caller scan")):
            history.record(self.root, "func_test")
        row = history.records(self.root, "func_test")[-1]
        self.assertEqual(['changed', 'removed'], row['changed_declarations'])
        self.assertEqual(['added', 'changed', 'removed'], row['caller_review_symbols'])
        self.assertEqual(['added'], row['declaration_review']['added_with_existing_calls'])
        reminder = next(line for line in output.getvalue().splitlines() if line.startswith('caller-review:'))
        self.assertTrue(reminder.endswith('./conker matching-callers added changed removed'))

    def test_ambiguous_existing_definitions_keep_a_conservative_caller_reminder(self):
        before = ('#ifdef FLAG\nvoid neighbor(void) { callee(1); }\n'
                  '#else\nvoid neighbor(void) { callee(2); }\n#endif\n'
                  'void func_test(void) {}\n')
        self.write('src/test.c', before)
        history.prepare(self.root, 'func_test')
        self.write('src/test.c', 'void callee(u8);\n' + before)
        output = io.StringIO()
        with redirect_stdout(output):
            history.record(self.root, 'func_test')
        row = history.records(self.root, 'func_test')[-1]
        self.assertEqual(['callee'], row['declaration_review']['added_with_uncertain_callers'])
        self.assertEqual(['callee'], row['caller_review_symbols'])
        self.assertIn('uncertain-local-call-review: callee', output.getvalue())
        self.assertIn('./conker matching-callers callee', output.getvalue())

    def test_sigterm_preserves_attempt_and_stops_child(self):
        self.child("import os,time\nprint('ready '+str(os.getpid()),flush=True)\ntime.sleep(30)\n")
        runner = self.root / "runner.py"
        runner.write_text("import sys\nfrom pathlib import Path\n"
                          f"sys.path.insert(0, {str(Path(history.__file__).parent)!r})\n"
                          "import matching_history as h\n"
                          f"h.ROOT=Path({str(self.root)!r})\n"
                          "sys.argv=['history','record','func_test']\nraise SystemExit(h.main())\n")
        child = subprocess.Popen([sys.executable, str(runner)], stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE, text=True)
        try:
            self.assertTrue(select.select([child.stdout], [], [], 5)[0])
            line = child.stdout.readline()
            self.assertTrue(line.startswith("ready "), line)
            pid = int(line.split()[1])
            child.send_signal(signal.SIGTERM)
            output, errors = child.communicate(timeout=5)
            self.assertEqual(130, child.returncode, errors)
            self.assertIn("attempt-record", output)
            with self.assertRaises(ProcessLookupError):
                os.kill(pid, 0)
            self.assertEqual("interrupted", history.records(self.root, "func_test")[-1]["status"])
        finally:
            if child.poll() is None:
                child.kill()
            child.communicate(timeout=5)

    def bundle(self):
        _, row = self.record()
        history.annotate(self.root, "func_test", row["attempt_id"], assessment="structural",
                         hypothesis="frame recovery", expected="frame shrinks to 0x50", exhausted=True)
        output = self.root / "attempts.zip"
        with redirect_stdout(io.StringIO()):
            history.export_bundle(self.root, "func_test", output)
        return output, row

    def test_portable_roundtrip_is_idempotent_and_never_imports_inventory(self):
        archive, row = self.bundle()
        target = self.root / "other"
        with redirect_stdout(io.StringIO()):
            history.import_bundle(target, archive)
            history.import_bundle(target, archive)
        loaded = history.records(target, "func_test")[0]
        self.assertEqual(row["source_sha256"], loaded["source_sha256"])
        self.assertEqual("structural", loaded["note"]["assessment"])
        self.assertFalse((target / "progress").exists())
        self.assertFalse((target / "src").exists())

    def modified_bundle(self, change):
        archive, _ = self.bundle()
        with zipfile.ZipFile(archive) as source:
            contents = {name: source.read(name) for name in source.namelist()}
        manifest = json.loads(contents.pop("manifest.json"))
        change(contents, manifest)
        result = self.root / "malicious.zip"
        with zipfile.ZipFile(result, "w") as output:
            output.writestr("manifest.json", json.dumps(manifest))
            for name, data in contents.items():
                output.writestr(name, data)
        return result

    def test_traversal_checksum_and_identity_override_rejected_before_writes(self):
        def traversal(contents, manifest):
            contents["../escape"] = b"bad"
            manifest["files"]["../escape"] = history.sha(b"bad")
        def checksum(contents, manifest):
            name = next(name for name in contents if name.endswith("source.c"))
            contents[name] = b"changed"
        def identity(contents, manifest):
            name = next(name for name in contents if name.endswith("result.json"))
            contents[name] = json.dumps({"attempt_id": "0" * 32}).encode()
            manifest["files"][name] = history.sha(contents[name])
        for change in (traversal, checksum, identity):
            with self.subTest(change=change.__name__):
                archive = self.modified_bundle(change)
                target = self.root / "import"
                with self.assertRaises(ValueError):
                    history.import_bundle(target, archive)
                self.assertFalse(target.exists())
                (self.root / "attempts.zip").unlink()

    def test_export_symlink_and_import_symlink_destination_rejected(self):
        archive, row = self.bundle()
        path = row["directory"] / "function.c"
        path.unlink()
        path.symlink_to(self.root / "src/test.c")
        with self.assertRaises(ValueError):
            history.export_bundle(self.root, "func_test", self.root / "bad.zip")
        target = self.root / "other"
        target.mkdir()
        (target / "build").symlink_to(self.root / "outside", target_is_directory=True)
        with self.assertRaises(ValueError):
            history.import_bundle(target, archive)

    def test_zip_symlink_rejected(self):
        path = self.root / "bad.zip"
        with zipfile.ZipFile(path, "w") as archive:
            link = zipfile.ZipInfo("manifest.json")
            link.external_attr = (stat.S_IFLNK | 0o777) << 16
            archive.writestr(link, "outside")
        with self.assertRaises(ValueError):
            history.import_bundle(self.root / "other", path)

    def test_atomic_writes_do_not_follow_predictable_temp_symlinks(self):
        directory = history.history_dir(self.root, "func_test")
        directory.mkdir(parents=True)
        sentinel = self.write("sentinel", "preserve me")
        for name in ("ready-source.tmp", "ready.json.tmp", "result.json.tmp"):
            (directory / name).symlink_to(sentinel)
        history.prepare(self.root, "func_test")
        history.write_json(directory / "result.json", {"status": "interrupted"})
        self.assertEqual("preserve me", sentinel.read_text())
        self.assertEqual((self.root / "src/test.c").read_bytes(),
                         (directory / "ready-source.c").read_bytes())
        self.assertEqual("interrupted", json.loads((directory / "result.json").read_text())["status"])

    def test_failed_atomic_replace_preserves_destination_and_cleans_temp(self):
        destination = self.write("result.json", "original")
        before = set(destination.parent.iterdir())
        with patch.object(Path, "replace", side_effect=OSError("replace failed")):
            with self.assertRaises(OSError):
                history.write_json(destination, {"status": "interrupted"})
        self.assertEqual("original", destination.read_text())
        self.assertEqual(before, set(destination.parent.iterdir()))

    def test_import_empty_result_is_visible_as_interrupted(self):
        def empty_result(contents, manifest):
            name = next(name for name in contents if name.endswith("result.json"))
            contents[name] = b"{}"
            manifest["files"][name] = history.sha(contents[name])
        archive = self.modified_bundle(empty_result)
        target = self.root / "other"
        with redirect_stdout(io.StringIO()):
            history.import_bundle(target, archive)
            history.summarize(target, "func_test")
        row = history.records(target, "func_test")[0]
        self.assertEqual("interrupted", row["status"])
        self.assertIsNone(row["score"])

    def test_import_write_failure_leaves_no_visible_attempt(self):
        archive, _ = self.bundle()
        target = self.root / "other"
        with patch.object(Path, "write_bytes", side_effect=OSError("disk full")):
            with self.assertRaises(OSError):
                history.import_bundle(target, archive)
        self.assertEqual([], history.records(target, "func_test"))


if __name__ == "__main__":
    unittest.main()
