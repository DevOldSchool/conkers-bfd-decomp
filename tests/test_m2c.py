from __future__ import annotations

import importlib.util
import json
import os
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location("m2c_helper", ROOT / "scripts" / "m2c.py")
assert SPEC is not None and SPEC.loader is not None
m2c_helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(m2c_helper)


class M2CHelperTests(unittest.TestCase):
    def test_recovers_bounded_rom_jump_table_and_missing_case_labels(self) -> None:
        base = 0x15000000
        words = [0x2DE10002, 0x10200009, 0x000F7880, 0x3C018009,
                 0x002F0821, 0x8C2F1A30, 0x01E00008, 0,
                 0x24020001, 0x03E00008, 0, 0x03E00008, 0]
        code = b"".join(word.to_bytes(4, "big") for word in words)
        assembly = ".section .text\nglabel func_test\n" + "".join(
            f"    /* {index * 4:X} {base + index * 4:08X} {word:08X} */ "
            + ("lw $t7, %lo(jtbl_80091A30_game)($at)" if index == 5 else "nop")
            + "\n" for index, word in enumerate(words)
        )
        data = (base + 32).to_bytes(4, "big") + (base + 44).to_bytes(4, "big")
        recover = lambda text, raw, table: m2c_helper.add_game_jump_tables(
            text, raw, table, base, 0x80091A30
        )
        result = recover(assembly, code, data)
        self.assertIn(".L15000020:\n", result)
        self.assertIn(".L1500002C:\n", result)
        self.assertIn("glabel jtbl_80091A30_game\n    .word .L15000020\n    .word .L1500002C\n", result)
        self.assertEqual(result, recover(result, code, data))
        # Neither truncated tables nor targets outside the extracted function qualify.
        self.assertEqual(assembly, recover(assembly, code, data[:4]))
        self.assertEqual(assembly, recover(assembly, code, b"\x15\x00\x10\x00" + data[4:]))
        self.assertEqual(assembly, recover(assembly, bytes(len(code)), data))
        # The name alone is insufficient: the decoded unsigned bounds check is required.
        unchecked = assembly.replace("2DE10002", "00000000")
        self.assertEqual(unchecked, recover(unchecked, bytes(4) + code[4:], data))

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

    def test_extracts_internal_global_entry_until_next_registered_function(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "asm" / "us" / "game.s"
            source.parent.mkdir(parents=True)
            source.write_text(
                ".section .text\n\n"
                "glabel func_start\n"
                "    b func_return\n"
                "     nop\n\n"
                "  glabel func_return\n"
                "    jr $ra\n"
                "     nop\n\n"
                "glabel func_next\n"
                "    break\n",
                encoding="utf-8",
            )
            with patch.object(m2c_helper, "ROOT", temporary_root):
                extracted = m2c_helper.extract_function(
                    source,
                    "func_start",
                    boundary_symbols={"func_start", "func_next"},
                )

            self.assertEqual(
                extracted.read_text(encoding="utf-8"),
                ".section .text\n\n"
                "glabel func_start\n"
                "    b .Lfunc_return\n"
                "     nop\n\n"
                "  .Lfunc_return:\n"
                "    jr $ra\n"
                "     nop\n\n",
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

    def test_prepares_source_local_context_under_ignored_build_output(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            types = temporary_root / "include" / "types.h"
            types.parent.mkdir(parents=True)
            types.write_text(
                "#ifndef TYPES_H\n#define TYPES_H\ntypedef signed int s32;\n#endif\n",
                encoding="utf-8",
            )
            source = temporary_root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                '#include "types.h"\n\n'
                "typedef struct Test { s32 value; } Test;\n\n"
                "#if 0 /* preserved candidate */\n"
                "void func_test(Test *arg0) { arg0->value = 1; }\n"
                "#endif\n"
                '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n',
                encoding="utf-8",
            )

            with patch.object(m2c_helper, "ROOT", temporary_root):
                context = m2c_helper.prepare_m2c_context(source)

            self.assertEqual(
                temporary_root / "build" / "m2c" / "context" / "game" / "test.c",
                context,
            )
            assert context is not None
            generated = context.read_text(encoding="utf-8")
            self.assertIn("typedef signed int s32;", generated)
            self.assertIn("typedef struct Test", generated)
            self.assertIn("void func_test(Test *arg0)", generated)
            self.assertNotIn("#include", generated)
            self.assertNotIn("#if", generated)
            self.assertNotIn("#pragma", generated)

    def test_mips_to_c_command_uses_source_context_when_available(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            extracted = temporary_root / "build" / "m2c" / "game" / "func_test.s"
            extracted.parent.mkdir(parents=True)
            extracted.write_text("glabel func_test\n", encoding="utf-8")
            source = temporary_root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                "typedef struct Test { s32 value; } Test;\n", encoding="utf-8"
            )

            with patch.object(m2c_helper, "ROOT", temporary_root):
                command = m2c_helper.mips_to_c_command(
                    extracted, "func_test", source
                )

            self.assertIn("--context", command)
            self.assertIn("build/m2c/context/game/test.c", command)
            self.assertEqual("build/m2c/game/func_test.s", command[-1])

    def test_mips_to_c_command_skips_unsupported_source_directives(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            extracted = temporary_root / "build" / "m2c" / "game" / "func_test.s"
            extracted.parent.mkdir(parents=True)
            extracted.write_text("glabel func_test\n", encoding="utf-8")
            source = temporary_root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                "#if PROFILE_US\nvoid func_test(void);\n#endif\n",
                encoding="utf-8",
            )

            with patch.object(m2c_helper, "ROOT", temporary_root):
                command = m2c_helper.mips_to_c_command(
                    extracted, "func_test", source
                )

            self.assertNotIn("--context", command)
            self.assertEqual("build/m2c/game/func_test.s", command[-1])

    def test_intrinsic_pragmas_keep_source_context_without_changing_source(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            original = (
                '#include "types.h"\n'
                'typedef struct State { s32 value; } State;\n'
                'f32 sqrtf(f32);\n#pragma intrinsic(sqrtf)\n'
                'f32 fabsf(f32);\n#pragma intrinsic ( fabsf )\n'
                'extern State *D_state;\n'
            )
            source.write_text(original)
            with patch.object(m2c_helper, "ROOT", root):
                command = m2c_helper.mips_to_c_command(root / "input.s", "func_test", source)
            self.assertIn("--context", command)
            context = (root / command[command.index("--context") + 1]).read_text()
            self.assertIn('typedef struct State', context)
            self.assertIn('f32 sqrtf(f32);', context)
            self.assertIn('extern State *D_state;', context)
            self.assertNotIn('#pragma', context)
            self.assertEqual(original, source.read_text())

    def test_other_pragmas_still_reject_context(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            source = Path(temporary_directory) / "test.c"
            for directive in ('#pragma intrinsic(other)', '#pragma pack(1)',
                              '#pragma intrinsic(sqrtf) unexpected'):
                with self.subTest(directive=directive):
                    source.write_text(directive + '\nvoid func_test(void);\n')
                    self.assertIsNone(m2c_helper.flattened_source_context(source))

    def test_context_fallback_retains_recovered_calls_and_original_artifact(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            (root / 'context.c').write_text('void incompatible(s32, s32);\n')
            recovery = m2c_helper.call_signatures.Recovery(('s32 proven(s32);',), ('project evidence',))
            typed = SimpleNamespace(returncode=0, stdout='M2C_ERROR(/* unset register */)')
            plain = SimpleNamespace(returncode=0, stdout='s32 f(s32 x) { return proven(x); }')
            command = ['m2c', '--context', 'context.c', 'input.s']
            with patch.object(m2c_helper, 'ROOT', root), patch.object(
                    m2c_helper.subprocess, 'run', side_effect=[typed, plain]) as run:
                result, fallback = m2c_helper.run_m2c_command(
                    command, recovery, 'func_test', allow_context_fallback=True)
            self.assertIs(plain, result)
            self.assertTrue(fallback)
            fallback_command = run.call_args.args[0]
            context = (root / fallback_command[fallback_command.index('--context') + 1]).read_text()
            self.assertIn('s32 proven(s32);', context)
            self.assertNotIn('incompatible', context)
            self.assertEqual(typed.stdout, (root / 'build/m2c/calls/func_test-typed-starter.c').read_text())
            self.assertEqual(['m2c', '--context', 'context.c', 'input.s'], command)

    def test_context_fallback_is_bounded_and_must_remove_register_errors(self) -> None:
        recovery = m2c_helper.call_signatures.Recovery((), ())
        error = SimpleNamespace(returncode=0, stdout='M2C_ERROR(/* unset */)')
        good = SimpleNamespace(returncode=0, stdout='void f(void) {}')
        failed = SimpleNamespace(returncode=1, stdout='failed')
        for allow, context, results in (
            (False, True, [error]), (True, False, [error]),
            (True, True, [good]), (True, True, [failed]),
            (True, True, [error, failed]), (True, True, [error, error]),
        ):
            with self.subTest(allow=allow, context=context, results=results):
                command = ['m2c', '--context', 'context.c', 'input.s'] if context else ['m2c', 'input.s']
                with patch.object(m2c_helper.subprocess, 'run', side_effect=results) as run:
                    result, fallback = m2c_helper.run_m2c_command(
                        command, recovery, 'func_test', allow_context_fallback=allow)
                self.assertIs(results[0], result)
                self.assertFalse(fallback)
                self.assertEqual(len(results), run.call_count)

    def test_only_intrinsic_context_enables_fallback_and_records_it(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / 'test.c'
            recovery = m2c_helper.call_signatures.Recovery((), ())
            error = SimpleNamespace(returncode=0, stdout='M2C_ERROR(/* unset */)')
            good = SimpleNamespace(returncode=0, stdout='void f(void) {}')
            for intrinsic in (False, True):
                with self.subTest(intrinsic=intrinsic):
                    source.write_text('#pragma intrinsic(sqrtf)\n' if intrinsic else 'void f(void);\n')
                    with (patch.object(m2c_helper, 'ROOT', root),
                          patch.object(m2c_helper.call_signatures, 'recover', return_value=recovery),
                          patch.object(m2c_helper.call_signatures, 'wrapper_call', return_value=None),
                          patch.object(m2c_helper.call_signatures, 'dependency_digest', return_value='test'),
                          patch.object(m2c_helper.subprocess, 'run', side_effect=[error, good] if intrinsic else [error])):
                        output, status = m2c_helper.generate_with_call_context(
                            ['m2c', '--context', 'context.c', 'input.s'], '', 'func_test', source, 'us')
                    self.assertEqual(0, status)
                    evidence = json.loads((root / 'build/m2c/calls/func_test.json').read_text())
                    self.assertEqual(intrinsic, evidence['source_context_fallback'])
                    self.assertEqual(intrinsic, 'using the starter without source context' in output)

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
