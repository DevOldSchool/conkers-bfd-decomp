from __future__ import annotations

import importlib.util
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "automation_common", ROOT / "scripts" / "automation_common.py"
)
assert SPEC is not None and SPEC.loader is not None
common = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = common
SPEC.loader.exec_module(common)


class AutomationCommonTests(unittest.TestCase):
    def test_scheduler_interleaves_raw_and_deferred_pools(self) -> None:
        raw = [
            common.RawCandidate("raw_one", "raw_one", "one.c", 4),
            common.RawCandidate("raw_two", "raw_two", "two.c", 8),
        ]
        deferred = [
            common.DeferredCandidate("deferred_one", "three.c", 10),
            common.DeferredCandidate("deferred_two", "four.c", 20),
            common.DeferredCandidate("deferred_three", "five.c", 30),
        ]

        self.assertEqual(
            ["raw_one", "deferred_one", "raw_two", "deferred_two", "deferred_three"],
            [item.identifier for item in common.scheduled_candidates(raw, deferred)],
        )

    def test_replaces_only_canonical_pragma_and_preserves_crlf(self) -> None:
        original = (
            b'#include "types.h"\r\n\r\n'
            b'#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\r\n'
        )

        updated = common.replace_target_pragma(
            original,
            "src/game/test.c",
            "func_test",
            "void func_test(void) {\n    return;\n}\n",
        )

        self.assertEqual(
            b'#include "types.h"\r\n\r\nvoid func_test(void) {\r\n    return;\r\n}\r\n',
            updated,
        )

    def test_refuses_missing_or_duplicate_pragmas(self) -> None:
        pragma = b'#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n'
        with self.assertRaisesRegex(common.AutomationError, "found 0"):
            common.replace_target_pragma(
                b"", "src/game/test.c", "func_test", "void func_test(void) {}\n"
            )
        with self.assertRaisesRegex(common.AutomationError, "found 2"):
            common.replace_target_pragma(
                pragma + pragma,
                "src/game/test.c",
                "func_test",
                "void func_test(void) {}\n",
            )


if __name__ == "__main__":
    unittest.main()
