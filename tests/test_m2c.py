from __future__ import annotations

import importlib.util
import json
import os
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location("m2c_helper", ROOT / "scripts" / "m2c.py")
assert SPEC is not None and SPEC.loader is not None
m2c_helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(m2c_helper)


class M2CHelperTests(unittest.TestCase):
    @staticmethod
    def write_game_inventory(root: Path) -> None:
        inventory = root / "progress" / "functions.json"
        inventory.parent.mkdir(parents=True)
        inventory.write_text(
            '{"functions":[{"symbol":"func_test","overlay":"game",'
            '"source":"src/game/effects/test.c",'
            '"regions":{"us":{"symbol":"func_15000000"}}}]}',
            encoding="utf-8",
        )

    def test_locates_exact_generated_label(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "asm" / "us" / "main.s"
            source.parent.mkdir(parents=True)
            source.write_text("glabel func_80001050\n", encoding="utf-8")
            with patch.object(m2c_helper, "ROOT", temporary_root):
                self.assertEqual(m2c_helper.locate_function("us", "func_80001050"), source)

    def test_rejects_missing_symbol(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            with patch.object(m2c_helper, "ROOT", Path(temporary_directory)):
                with self.assertRaises(ValueError):
                    m2c_helper.locate_function("eu", "func_80001050")

    def test_locates_game_reference_label(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "reference" / "game" / "us" / "asm" / "game_1A6300.s"
            source.parent.mkdir(parents=True)
            source.write_text("glabel func_15178E50\n", encoding="utf-8")
            with patch.object(m2c_helper, "ROOT", temporary_root):
                self.assertEqual(
                    m2c_helper.locate_function("us", "func_15178E50", game_reference=True),
                    source,
                )

    def test_reuses_validated_reference_symbol_index(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "reference" / "game" / "us" / "asm" / "game.s"
            source.parent.mkdir(parents=True)
            source.write_text("glabel func_15178E50\n", encoding="utf-8")
            with patch.object(m2c_helper, "ROOT", temporary_root):
                first = m2c_helper.locate_function(
                    "us", "func_15178E50", game_reference=True
                )
                with patch.object(
                    m2c_helper,
                    "scan_reference_functions",
                    side_effect=AssertionError("reference index was not reused"),
                ):
                    second = m2c_helper.locate_function(
                        "us", "func_15178E50", game_reference=True
                    )

            self.assertEqual(source, first)
            self.assertEqual(source, second)

    def test_rebuilds_reference_index_when_cached_label_is_invalid(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "reference" / "game" / "us" / "asm" / "game.s"
            source.parent.mkdir(parents=True)
            source.write_text("glabel func_old\n", encoding="utf-8")
            cache = temporary_root / "build" / "reference-index" / "game-us.json"
            cache.parent.mkdir(parents=True)
            cache.write_text(
                json.dumps(
                    {
                        "schema_version": 1,
                        "assembly_root_mtime_ns": source.parent.stat().st_mtime_ns,
                        "symbols": {"func_new": ["game.s"]},
                    }
                ),
                encoding="utf-8",
            )
            with patch.object(m2c_helper, "ROOT", temporary_root):
                with self.assertRaises(ValueError):
                    m2c_helper.locate_function(
                        "us", "func_new", game_reference=True
                    )

    def test_extracts_only_requested_function(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "asm" / "us" / "main.s"
            source.parent.mkdir(parents=True)
            source.write_text(
                ".section .text\n\nglabel func_80001050\n    nop\n\nglabel func_80001058\n    break\n",
                encoding="utf-8",
            )
            with patch.object(m2c_helper, "ROOT", temporary_root):
                extracted = m2c_helper.extract_function(source, "func_80001050")
                self.assertEqual(
                    extracted.read_text(encoding="utf-8"),
                    ".section .text\n\nglabel func_80001050\n    nop\n\n",
                )

    def test_repairs_proven_preserved_a0_call_argument(self) -> None:
        assembly = """\
glabel func_wrapper
    jal        func_target
     addiu     $a1, $a0, 0x18
"""
        starter = """\
M2C_UNK func_target(s32); /* extern */

void func_wrapper(s32 arg0) {
    func_target(arg0 + 0x18);
}
"""

        repaired = m2c_helper.repair_preserved_call_arguments(
            starter, assembly, "func_wrapper"
        )

        self.assertIn("M2C_UNK func_target(s32, s32);", repaired)
        self.assertIn("func_target(arg0, arg0 + 0x18);", repaired)

    def test_does_not_guess_a0_when_delay_slot_does_not_prove_it(self) -> None:
        assembly = """\
glabel func_wrapper
    jal        func_target
     addiu     $a1, $zero, 0x18
"""
        starter = """\
M2C_UNK func_target(s32); /* extern */
void func_wrapper(s32 arg0) {
    func_target(0x18);
}
"""

        self.assertEqual(
            starter,
            m2c_helper.repair_preserved_call_arguments(
                starter, assembly, "func_wrapper"
            ),
        )

    def test_ready_output_labels_required_declarations(self) -> None:
        starter = """\
extern s32 D_800DBE38;
M2C_UNK func_target(s32, s32); /* extern */

void func_wrapper(s32 arg0) {
    func_target(arg0, D_800DBE38);
}
"""

        output = m2c_helper.ready_output(starter, "func_wrapper")

        self.assertIn("required-declarations:\n  extern s32 D_800DBE38;", output)
        self.assertIn("  M2C_UNK func_target(s32, s32); /* extern */", output)
        self.assertIn("c-starter:\n" + starter, output)

    def test_registered_game_item_prefers_existing_rom_reference(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            self.write_game_inventory(temporary_root)
            reference = (
                temporary_root
                / "reference"
                / "game"
                / "us"
                / "asm"
                / "game.s"
            )
            reference.parent.mkdir(parents=True)
            reference.write_text("glabel func_15000000\n    nop\n", encoding="utf-8")
            nonmatching = (
                temporary_root
                / "asm"
                / "nonmatchings"
                / "effects"
                / "test"
                / "func_test.s"
            )
            nonmatching.parent.mkdir(parents=True)
            nonmatching.write_text("glabel func_15000000\n    break\n", encoding="utf-8")

            with (
                patch.object(m2c_helper, "ROOT", temporary_root),
                patch.object(m2c_helper, "prepare_reference") as prepare_reference,
            ):
                source, symbol = m2c_helper.locate_registered_function("us", "func_test")

            self.assertEqual(reference, source)
            self.assertEqual("func_15000000", symbol)
            prepare_reference.assert_not_called()

    def test_registered_game_item_uses_valid_nonmatching_without_reference(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            self.write_game_inventory(temporary_root)
            nonmatching = (
                temporary_root
                / "asm"
                / "nonmatchings"
                / "effects"
                / "test"
                / "func_test.s"
            )
            nonmatching.parent.mkdir(parents=True)
            nonmatching.write_text("glabel func_15000000\n    nop\n", encoding="utf-8")

            with (
                patch.object(m2c_helper, "ROOT", temporary_root),
                patch.object(m2c_helper, "prepare_reference") as prepare_reference,
            ):
                source, symbol = m2c_helper.locate_registered_function("us", "func_test")

            self.assertEqual(nonmatching, source)
            self.assertEqual("func_15000000", symbol)
            prepare_reference.assert_not_called()

    def test_registered_game_item_rebuilds_when_no_safe_input_exists(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            self.write_game_inventory(temporary_root)
            generated = temporary_root / "reference" / "game" / "us" / "asm" / "game.s"

            def generate_reference(profile: str, *, game_reference: bool) -> None:
                self.assertEqual("us", profile)
                self.assertTrue(game_reference)
                generated.parent.mkdir(parents=True)
                generated.write_text("glabel func_15000000\n    nop\n", encoding="utf-8")

            with (
                patch.object(m2c_helper, "ROOT", temporary_root),
                patch.object(m2c_helper, "prepare_reference", side_effect=generate_reference) as prepare,
            ):
                source, symbol = m2c_helper.locate_registered_function("us", "func_test")

            self.assertEqual(generated, source)
            self.assertEqual("func_15000000", symbol)
            prepare.assert_called_once_with("us", game_reference=True)

    def test_host_run_delegates_missing_game_reference_to_conker(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            with (
                patch.object(m2c_helper, "ROOT", temporary_root),
                patch.dict(os.environ, {"CONKER_HOST_M2C": "1"}),
                patch.object(m2c_helper.subprocess, "run") as run,
            ):
                m2c_helper.prepare_reference("us", game_reference=True)

            run.assert_called_once_with(
                [str(temporary_root / "conker"), "game-asm", "--profile", "us"],
                cwd=temporary_root,
                check=True,
                stdout=m2c_helper.sys.stderr,
            )
