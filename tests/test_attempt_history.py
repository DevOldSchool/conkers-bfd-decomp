from __future__ import annotations

import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import attempt_history
import matching_blockers


class AttemptHistoryTests(unittest.TestCase):
    def report(self, entries=(), *, pending=(), verified=(), mode="execute"):
        return {"schema_version": 3, "profile": "us", "mode": mode,
                "generated_at": "2026-09-19", "functions": list(entries),
                "pending_batch": list(pending), "verified_batch": list(verified),
                "batch_verified": bool(verified)}

    def test_bounded_reports_share_failures_without_erasing_other_candidates(self):
        first = {"symbol": "a", "outcome": "skipped", "fingerprint": "one"}
        second = {"symbol": "b", "outcome": "preserved", "fingerprint": "two"}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            attempt_history.save(root, self.report([first]))
            attempt_history.save(root, self.report([second, {"symbol": "a", "outcome": "not_attempted"}]))
            entries = {x["symbol"]: x for x in attempt_history.load(root)["functions"]}
            self.assertEqual(first, entries["a"])
            self.assertEqual(second, entries["b"])

    def test_pending_gate_survives_until_explicit_verification(self):
        history = attempt_history.merge({}, self.report(pending=["a"]))
        history = attempt_history.merge(history, self.report())
        self.assertEqual(["a"], history["pending_batch"])
        history = attempt_history.merge(history, self.report(verified=["a"]))
        self.assertEqual([], history["pending_batch"])

    def test_analysis_does_not_poison_execution_cache(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            attempt_history.save(root, self.report([{"symbol": "a", "outcome": "ready"}], mode="analyze"))
            self.assertFalse(attempt_history.path(root).exists())

    def test_import_existing_reports_in_date_order(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            folder = attempt_history.path(root).parent
            folder.mkdir(parents=True)
            first = self.report([{"symbol": "a", "outcome": "skipped", "fingerprint": "old"}])
            latest = self.report([{"symbol": "a", "outcome": "preserved", "fingerprint": "new"}])
            latest["generated_at"] = "2026-09-20"
            (folder / "all-report.json").write_text(json.dumps(first))
            (folder / "report.json").write_text(json.dumps(latest))
            self.assertEqual("new", attempt_history.load(root)["functions"][0]["fingerprint"])

    def test_blocker_ranking_deduplicates_and_excludes_matched_dependents(self):
        inventory = [{"symbol": name, "regions": {"us": {"state": state}}}
                     for name, state in [("a", "raw_asm"), ("b", "matched"), ("callee", "matched")]]
        results = [{"symbol": name, "blocker_code": "declaration_evidence",
                    "detail": "no unique project declaration evidence for: callee, callee"}
                   for name in ("a", "b")]
        report = matching_blockers.summarize({"functions": results}, inventory, 10)
        self.assertEqual(1, report["declarations"][0]["dependent_count"])
        self.assertTrue(report["declarations"][0]["currently_matched"])
        self.assertEqual(["a"], report["declarations"][0]["examples"])
