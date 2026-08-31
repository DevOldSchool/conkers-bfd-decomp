from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "compile_diff_candidate", ROOT / "scripts" / "compile_diff_candidate.py"
)
assert SPEC is not None and SPEC.loader is not None
compile_diff_candidate = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(compile_diff_candidate)


class CompileDiffCandidateTests(unittest.TestCase):
    def test_compiles_only_the_expected_candidate_target(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "src" / "game" / "test.c"
            target = temporary_root / "build" / "us" / "src" / "game" / "test.o"
            with (
                patch.object(compile_diff_candidate.diff, "ROOT", temporary_root),
                patch.object(
                    compile_diff_candidate.diff,
                    "candidate_object",
                    return_value=target,
                ),
                patch.object(compile_diff_candidate.diff, "compile_candidate") as compile_candidate,
                patch.object(
                    sys,
                    "argv",
                    [
                        "compile_diff_candidate.py",
                        "--profile",
                        "us",
                        "--source",
                        "src/game/test.c",
                        "build/us/src/game/test.o",
                    ],
                ),
            ):
                self.assertEqual(0, compile_diff_candidate.main())

            compile_candidate.assert_called_once_with("us", source)


if __name__ == "__main__":
    unittest.main()
