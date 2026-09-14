from __future__ import annotations

import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import normalize_asm


class NormalizeAsmTests(unittest.TestCase):
    def test_normalizes_global_asm_label_and_ido_register_alias(self) -> None:
        source = ".section .text\n\nglabel func_test\n    mfc1 $a0, $ft0\n"

        self.assertEqual(
            ".section .text\n\n.globl func_test\nfunc_test:\n    mfc1 $a0, $f4\n",
            normalize_asm.normalize(source),
        )
