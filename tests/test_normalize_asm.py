from __future__ import annotations

import importlib.util
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location("normalize_asm", ROOT / "scripts" / "normalize_asm.py")
assert SPEC is not None and SPEC.loader is not None
normalize_asm = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(normalize_asm)


class NormalizeAsmTests(unittest.TestCase):
    def test_replaces_ido_fpr_aliases_without_touching_similar_names(self) -> None:
        self.assertEqual(
            normalize_asm.normalize("sdc1 $fs0, 0($sp)\nmtc1 $zero, $ft0f\n$fs0_suffix\n"),
            "sdc1 $f20, 0($sp)\nmtc1 $zero, $f5\n$fs0_suffix\n",
        )

