from __future__ import annotations

from contextlib import ExitStack
import hashlib
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import diff
import layout_check
import linked_aliases
import project_state
import rom_span
from candidate_tables import Object32


@unittest.skipUnless(shutil.which("mips-linux-gnu-as") and shutil.which("mips-linux-gnu-ld"),
                     "requires pinned MIPS binutils")
class GameComparisonTests(unittest.TestCase):
    source = "src/game/unit.c"
    symbol = "func_15001010"
    start = 0x15001010
    words = [0x3C02800F, 0x24428000, 0x03E00008, 0]

    def metadata(self, root):
        members = [{"symbol": f"func_{address:08X}", "source": self.source, "overlay": "game",
                    "regions": {"us": {"symbol": f"func_{address:08X}", "vram": hex(address),
                                        "size_bytes": 16}}}
                   for address in (0x15001000, self.start, 0x15001020)]
        unit = {"source": self.source, "functions": [member["symbol"] for member in members],
                "boundary_evidence": {"us": {"reviewed": True}},
                "regions": {"us": {"start": "0x1000", "end": "0x1030"}}}
        (root / "progress").mkdir(exist_ok=True)
        (root / "progress/functions.json").write_text(json.dumps({"functions": members}))
        (root / "progress/source_units.json").write_text(json.dumps({"source_units": [unit]}))

    def assemble(self, root, name, body):
        source = root / (name + ".s")
        source.write_text(".text\n.set noreorder\n" + body)
        output = source.with_suffix(".o")
        subprocess.run(["mips-linux-gnu-as", "-EB", "-mabi=32", "-march=vr4300",
                        "-o", str(output), str(source)], check=True, capture_output=True)
        return output

    def function(self, symbol, body, size=None):
        return (f".globl {symbol}\n{symbol}:\n{body}\n"
                f".size {symbol},{size if size is not None else '.-'+symbol}\n")

    def body(self, expression="D_800E7FFC+4"):
        return f"lui $v0,%hi({expression})\naddiu $v0,$v0,%lo({expression})\njr $ra\nnop"

    def objects(self, root, *, body=None, prefix="jr $ra\nnop\nnop\nnop", size=16,
                neighbor="jal func_15001000\nnop\njr $ra\nnop", tail=""):
        candidate = self.assemble(root, "mixed", self.function("func_15001000", prefix)
                                  + self.function(self.symbol, body or self.body(), size)
                                  + self.function("func_15001020", neighbor) + tail)
        reference = self.assemble(root, "raw", self.function(self.symbol, self.body("D_800E8000")))
        return candidate, reference

    def prove(self, root, candidate, reference, *, raw=None, words=None, unit_words=None, start=None):
        words = words or self.words
        unit_words = unit_words or [0x03E00008, 0, 0, 0, *words, 0x0D400400, 0, 0x03E00008, 0]
        code = bytes(0x1000) + struct.pack(">" + "I" * len(unit_words), *unit_words)
        assembly = root / "target.s"
        assembly.write_text(raw or "".join(
            f"/* {i*4:X} {self.start+i*4:08X} {word:08X} */ instruction\n"
            for i, word in enumerate(words)))
        with patch.object(rom_span, "game_code", return_value=(code, 0x15000000, "validated")):
            return linked_aliases.prepare_game(root, self.source, candidate, reference, assembly,
                                               self.symbol, start or self.start, 16)

    def test_exact_endpoint_carry_and_complete_unit_with_real_defined_call(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            self.metadata(root)
            candidate, reference = self.objects(root)
            original = candidate.read_bytes()
            self.assertTrue(linked_aliases.game_eligible(candidate, reference, self.symbol, 16))
            self.assertIsNone(linked_aliases.definitions(Object32(original)))
            pair = self.prove(root, candidate, reference)
            self.assertIsNotNone(pair)
            self.assertEqual(pair[0].read_bytes(), pair[1].read_bytes())
            self.assertEqual(original, candidate.read_bytes())
            output = root / "build/us/linked-aliases" / self.symbol
            self.assertEqual(48, len((output / "candidate.bin").read_bytes()))
            self.assertNotIn("func_15001000 =", (output / "candidate.ld").read_text())

    def test_instruction_and_endpoint_errors_cannot_become_a_match(self):
        changes = [self.body("D_800E7FFC+8"), self.body("D_800E7FF8+4"),
                   self.body().replace("$v0", "$v1"), self.body().replace("addiu", "ori"),
                   self.body().replace("nop", "addiu $v1,$zero,1"),
                   self.body().replace("jr $ra", "beq $zero,$zero,func_15001000")]
        for body in changes:
            with self.subTest(body=body), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                candidate, reference = self.objects(root, body=body)
                self.assertIsNone(self.prove(root, candidate, reference))

    def test_wrong_neighbor_rejected_even_when_entire_target_matches(self):
        for neighbor in ("jal func_15001000+4\nnop\njr $ra\nnop",
                         "jal func_15001000\nnop\njr $ra\naddiu $v0,$zero,1"):
            with self.subTest(neighbor=neighbor), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                candidate, reference = self.objects(root, neighbor=neighbor)
                self.assertIsNone(self.prove(root, candidate, reference))

    def test_full_object_unsupported_dependencies_are_not_hidden_by_target(self):
        cases = [("jal unknown_function\nnop\njr $ra\nnop", ""),
                 ("lui $v0,%hi(jtbl_80091A50_game)\naddiu $v0,$v0,%lo(jtbl_80091A50_game)\njr $ra\nnop", ""),
                 ("lui $v0,%hi(D_800E8000)\naddiu $v0,$v0,%lo(D_800E8000)\njr $ra\nnop",
                  ".data\n.globl D_800E8000\nD_800E8000: .word 0\n"),
                 ("lw $v0,%gp_rel(D_800E8000)($gp)\nnop\njr $ra\nnop", ""),
                 ("j func_15001000\nnop\njr $ra\nnop", "")]
        for neighbor, tail in cases:
            with self.subTest(neighbor=neighbor), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                candidate, reference = self.objects(root, neighbor=neighbor, tail=tail)
                self.assertIsNone(self.prove(root, candidate, reference))

    def test_duplicate_foreign_and_incorrectly_defined_callees_are_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            self.metadata(root)
            candidate, _ = self.objects(root)
            obj = Object32(candidate.read_bytes())
            _, section = linked_aliases.function(obj, self.symbol, 16)
            addresses = {"func_15001000": 0x15001000}
            self.assertIsNotNone(linked_aliases.game_definitions(obj, addresses, section, 0x15001000))
            self.assertIsNone(linked_aliases.game_definitions(obj, {}, section, 0x15001000))
            self.assertIsNone(linked_aliases.game_definitions(obj, addresses, section, 0x15001004))
            table = next(iter(obj.symbols.values()))
            table.append(next(symbol for symbol in table if symbol[0] == "func_15001000"))
            self.assertIsNone(linked_aliases.game_definitions(obj, addresses, section, 0x15001000))

    def test_short_long_shifted_or_extended_objects_never_supply_proof(self):
        cases = [{"size": 12}, {"size": 20}, {"prefix": "jr $ra\nnop\nnop"},
                 {"prefix": "jr $ra\nnop\nnop\nnop\nnop"}, {"tail": "nop\n"}]
        for options in cases:
            with self.subTest(options=options), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                candidate, reference = self.objects(root, **options)
                with self.assertRaises(ValueError):
                    self.prove(root, candidate, reference)

    def test_registration_ownership_gaps_overlaps_and_wrong_base_are_rejected(self):
        changes = [lambda f, u: u[0]["boundary_evidence"]["us"].update(reviewed=False),
                   lambda f, u: u.append(dict(u[0])),
                   lambda f, u: f.append(dict(f[1])),
                   lambda f, u: f[0].update(source="src/game/foreign.c"),
                   lambda f, u: f[0]["regions"]["us"].update(size_bytes=12),
                   lambda f, u: f[1]["regions"]["us"].update(size_bytes=20),
                   lambda f, u: u[0]["regions"]["us"].update(end="0x102C"),
                   lambda f, u: u[0]["regions"]["us"].update(start="0x1010", end="0x1040"),
                   lambda f, u: f[2]["regions"]["us"].update(symbol="func_15001024")]
        for change in changes:
            with self.subTest(change=change), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                fp, up = root / "progress/functions.json", root / "progress/source_units.json"
                functions, units = json.loads(fp.read_text()), json.loads(up.read_text())
                change(functions["functions"], units["source_units"])
                fp.write_text(json.dumps(functions))
                up.write_text(json.dumps(units))
                candidate, reference = self.objects(root)
                with self.assertRaises(ValueError):
                    self.prove(root, candidate, reference)

    def foreign_unit(self, root, start, end, *, size=None, overlay="game", profile="us"):
        functions_path = root / "progress/functions.json"
        units_path = root / "progress/source_units.json"
        functions, units = json.loads(functions_path.read_text()), json.loads(units_path.read_text())
        address = (0x15000000 if overlay == "game" else 0x80000000) + start
        symbol, source = f"func_{address:08X}", f"src/{overlay}/foreign.c"
        region = {"symbol": symbol, "vram": hex(address)}
        if size is not None:
            region["size_bytes"] = size
        functions["functions"].append({"symbol": symbol, "source": source, "overlay": overlay,
                                       "regions": {profile: region}})
        units["source_units"].append({"source": source, "functions": [symbol],
                                     "boundary_evidence": {profile: {"reviewed": True}},
                                     "regions": {profile: {"start": hex(start), "end": hex(end)}}})
        functions_path.write_text(json.dumps(functions))
        units_path.write_text(json.dumps(units))

    def test_foreign_unit_intervals_reject_enclosure_and_partial_overlaps_without_sizes(self):
        # A preceding function's explicit short extent (or omitted extent) does
        # not erase its source unit's independently registered ownership interval.
        for start, end in ((0xFF0, 0x1040), (0xFF0, 0x1030), (0xFF0, 0x1010),
                           (0x1028, 0x1040), (0x1008, 0x1028)):
            for size in (None, 4):
                with self.subTest(bounds=(start, end), foreign_size=size), tempfile.TemporaryDirectory() as temporary:
                    root = Path(temporary)
                    self.metadata(root)
                    self.foreign_unit(root, start, end, size=size)
                    candidate, reference = self.objects(root)
                    with self.assertRaisesRegex(ValueError, "overlaps another registered GAME source unit"):
                        self.prove(root, candidate, reference)

    def test_disjoint_touching_and_other_overlay_unit_intervals_do_not_block_proof(self):
        cases = [(0xFE0, 0xFF0, "game", "us"), (0xFF0, 0x1000, "game", "us"),
                 (0x1030, 0x1040, "game", "us"), (0x1040, 0x1050, "game", "us"),
                 (0xFF0, 0x1040, "main", "us"), (0xFF0, 0x1040, "game", "eu")]
        for start, end, overlay, profile in cases:
            with self.subTest(bounds=(start, end), overlay=overlay, profile=profile), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                self.foreign_unit(root, start, end, overlay=overlay, profile=profile)
                candidate, reference = self.objects(root)
                self.assertIsNotNone(self.prove(root, candidate, reference))

    def test_noncontiguous_truncated_and_wrong_raw_rom_evidence_fails_closed(self):
        valid = "".join(f"/* {i*4:X} {self.start+i*4:08X} {word:08X} */ instruction\n"
                        for i, word in enumerate(self.words))
        for raw in (valid.replace("15001014", "15001018"), valid.rsplit("/*", 1)[0],
                    valid + "/* 10 15001020 00000000 */ nop\n",
                    valid.replace("03E00008", "03E00009")):
            with self.subTest(raw=raw), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                candidate, reference = self.objects(root)
                with self.assertRaises(ValueError):
                    self.prove(root, candidate, reference, raw=raw)
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            self.metadata(root)
            candidate, reference = self.objects(root)
            with self.assertRaisesRegex(ValueError, "raw-reference span differs"):
                self.prove(root, candidate, reference, words=[*self.words[:-1], 1])


class GameComparisonWorkflowTests(unittest.TestCase):
    def test_real_fingerprints_cover_phase_executables_modules_and_proof_inputs(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            files = ["src/game/unit.c", "include/types.h", "src/game/local.h", "raw.s",
                     "asm/raw.s", "progress/functions.json", "progress/source_units.json",
                     "toolchain/tools.lock.json", "Dockerfile", "Makefile", "config/roms.json",
                     "config/overlays.json", "config/reference/us.yaml", "config/profiles/us.yaml",
                     "config/game/us.yaml", "config/symbols/game-us.txt", "config/relocs/us.txt",
                     "scripts/compile_c.py", "rom.z64", "installed/ido/cc", "installed/ido/uopt",
                     "installed/asm/build.py", "installed/asm/prelude.inc", "installed/asm/helper.py",
                     "installed/bin/as"]
            for name in files:
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("input\n")
            (root / "src/game/unit.c").write_text('#pragma GLOBAL_ASM("asm/raw.s")\n')
            (root / "config/rzip_layouts.json").write_text(json.dumps({"profiles": {"us": {"default_rom": "rom.z64"}}}))
            with patch.object(diff, "ROOT", root), \
                    patch.object(diff.compile_c, "IDO_CC", root / "installed/ido/cc"), \
                    patch.object(diff.compile_c, "ASM_PROCESSOR", root / "installed/asm/build.py"), \
                    patch.object(diff.compile_c, "ASM_PROCESSOR_PRELUDE", root / "installed/asm/prelude.inc"), \
                    patch.object(diff.shutil, "which", return_value=str(root / "installed/bin/as")):
                fingerprint = lambda: diff.game_comparison_inputs("src/game/unit.c", root / "raw.s")
                for name in files:
                    with self.subTest(input=name):
                        before = fingerprint()
                        path = root / name
                        original = path.read_bytes()
                        path.write_bytes(original + b"changed\n")
                        self.assertNotEqual(before, fingerprint())
                        path.write_bytes(original)
                before = fingerprint()
                with patch.object(diff.compile_c, "compiler_flags", return_value=["different"]):
                    self.assertNotEqual(before, fingerprint())
                with patch.object(diff.shutil, "which", return_value=None):
                    with self.assertRaisesRegex(ValueError, "requires"):
                        fingerprint()

    def wrapper(self, root, *, before=None, after=None, deferred=False, proof=None, compile_hook=None):
        source = root / "src/game/unit.c"
        source.parent.mkdir(parents=True)
        body = "void func_15001010(void) {}\n"
        if deferred:
            body = (f"#if 0 /* {project_state.DEFERRED_CANDIDATE_TAG} func_15001010 CURRENT (10) */\n" + body
                    + f"#endif /* {project_state.DEFERRED_CANDIDATE_TAG} func_15001010 */\n"
                    + project_state.global_asm_pragma("src/game/unit.c", "func_15001010") + "\n")
        source.write_text(body)
        with ExitStack() as stack:
            stack.enter_context(patch.object(diff, "ROOT", root))
            stack.enter_context(patch.object(linked_aliases, "game_eligible", return_value=True))
            stack.enter_context(patch.object(linked_aliases, "game_context"))
            materialize = stack.enter_context(patch.object(diff.prepare_nonmatching_asm, "materialize"))
            stack.enter_context(patch.object(diff, "game_comparison_inputs", side_effect=[before or {}, after or {}]))
            command = stack.enter_context(patch.object(diff.compile_c, "compile_command", return_value=["compiler"]))
            run = stack.enter_context(patch.object(diff.subprocess, "run", side_effect=compile_hook))
            reference = stack.enter_context(patch.object(diff, "reference_object", return_value=Path("fresh.o")))
            prepare = stack.enter_context(patch.object(linked_aliases, "prepare_game", return_value=proof))
            result = diff.prepare_game_comparison(source, Path("focused.o"), Path("stale.o"),
                                                 Path("raw.s"), "func_15001010", 0x15001010, 16,
                                                 deferred_symbol="func_15001010" if deferred else None)
            materialize.assert_called_once_with("us", "src/game/unit.c")
            reference.assert_called_once_with("us", "func_15001010", game_reference=True,
                                               assembly=Path("raw.s"), force=True)
            self.assertEqual(Path("fresh.o"), prepare.call_args.args[3])
            self.assertIn("linked-aliases/func_15001010/source.c", str(command.call_args.args[1]))
            run.assert_called_once_with(["compiler"], cwd=root, check=True)
            return result

    def test_active_and_deferred_paths_compile_complete_fresh_context(self):
        for deferred in (False, True):
            with self.subTest(deferred=deferred), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.assertEqual((Path("proved.o"), Path("raw.o")), self.wrapper(
                    root, deferred=deferred, proof=(Path("proved.o"), Path("raw.o"))))
                self.assertNotIn("GLOBAL_ASM", (root / "build/us/linked-aliases/func_15001010/source.c").read_text())

    def test_every_stale_input_class_is_rejected_after_compilation(self):
        for key in ("source", "header", "raw_neighbor", "inventory", "mapping", "settings", "compiler", "ROM"):
            with self.subTest(input=key), tempfile.TemporaryDirectory() as temporary:
                with self.assertRaisesRegex(ValueError, "inputs changed"):
                    self.wrapper(Path(temporary), before={key: "old"}, after={key: "new"},
                                 proof=(Path("proved.o"), Path("raw.o")))

    def test_stale_compilation_cache_is_removed_before_fresh_compile(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            old = root / "build/us/linked-aliases/func_15001010/mixed.o"
            old.parent.mkdir(parents=True)
            old.write_bytes(b"stale")
            self.wrapper(root, compile_hook=lambda *args, **kwargs: self.assertFalse(old.exists()))

    def test_watch_and_strict_rejection_never_fall_through_to_legacy(self):
        for watch in (False, True):
            with self.subTest(watch=watch), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                source, reference = root / "unit.c", root / "raw.o"
                source.write_text("void func_15001010(void) {}\n")
                reference.write_bytes(b"raw")
                (root / "progress").mkdir()
                (root / "progress/functions.json").write_text(json.dumps({"functions": [
                    {"regions": {"us": {"symbol": "func_15001010", "vram": "0x15001010"}}}]}))
                with ExitStack() as stack:
                    stack.enter_context(patch.object(diff, "ROOT", root))
                    stack.enter_context(patch.object(sys, "argv", ["diff.py", "us", "func_15001010", "--game"]
                                                       + (["--watch"] if watch else ["--require-match"])))
                    for name, value in (("find_work_item", (source, "func_15001010")),
                                        ("ensure_reference_function", Path("raw.s")),
                                        ("expected_function_size", 16), ("require_c_implementation", None),
                                        ("compile_candidate", Path("original.o")), ("reference_object", reference),
                                        ("write_settings", root), ("asm_diff_command", ["differ"]),
                                        ("run_asm_diff", 0)):
                        stack.enter_context(patch.object(diff, name, return_value=value))
                    stack.enter_context(patch.object(linked_aliases, "game_unit_registered", return_value=True))
                    strict = stack.enter_context(patch.object(diff, "prepare_game_comparison", return_value=None))
                    legacy = stack.enter_context(patch.object(linked_aliases, "prepare"))
                    table = stack.enter_context(patch.object(diff.candidate_tables, "verify_candidate"))
                    def required(candidate, raw, *args, **kwargs):
                        self.assertEqual(Path("original.o"), candidate)
                        kwargs["table_check"]()
                        return 1
                    stack.enter_context(patch.object(diff, "run_required_asm_diff", side_effect=required))
                    self.assertEqual(0 if watch else 1, diff.main())
                    legacy.assert_not_called()
                    if watch:
                        strict.assert_not_called()
                    else:
                        strict.assert_called_once()
                        table.assert_called_once_with(Path("original.o"), "func_15001010", Path("raw.s"), 16)


@unittest.skipUnless(os.environ.get("CONKER_ROM_TESTS") == "1" and diff.compile_c.IDO_CC.is_file(),
                     "opt-in integration tests require the pinned toolchain and reviewed US ROM")
class RegisteredGameComparisonTests(unittest.TestCase):
    def test_real_preceding_unit_cannot_claim_the_initializer_interval(self):
        root, source, symbol = diff.ROOT, "src/game/game_1A0100.c", "func_15172C50"
        functions = json.loads((root / "progress/functions.json").read_text())
        units = json.loads((root / "progress/source_units.json").read_text())
        previous = next(unit for unit in units["source_units"] if unit["source"] == "src/game/game_19F150.c")
        self.assertEqual("0x172C50", previous["regions"]["us"]["end"])
        final_member = next(entry for entry in functions["functions"] if entry["symbol"] == previous["functions"][-1])
        final_member["regions"]["us"].pop("size_bytes", None)
        with tempfile.TemporaryDirectory() as temporary:
            fixture = Path(temporary)
            (fixture / "progress").mkdir()
            (fixture / "progress/functions.json").write_text(json.dumps(functions))
            path = fixture / "progress/source_units.json"
            path.write_text(json.dumps(units))
            linked_aliases.game_context(fixture, source, symbol, 0x15172C50, 88)
            for end in ("0x172C60", "0x172F70", "0x172F80"):
                with self.subTest(foreign_end=end):
                    previous["regions"]["us"]["end"] = end
                    path.write_text(json.dumps(units))
                    with self.assertRaisesRegex(ValueError, "overlaps another registered GAME source unit"):
                        linked_aliases.game_context(fixture, source, symbol, 0x15172C50, 88)

    def test_active_real_initializer_with_materialized_raw_neighbor(self):
        root, symbol = diff.ROOT, "func_15172C50"
        source, _ = diff.find_work_item(symbol, "us", overlay="game")
        relative = source.relative_to(root)
        original = source.read_bytes()
        content = source.read_text()
        if diff.work_item_is_deferred(symbol):
            content = diff.activate_deferred_candidate(content, source, symbol)
        neighbor = "func_15172CA8"
        start, end = project_state.c_function_span(content, neighbor)
        content = content[:start] + project_state.global_asm_pragma(relative.as_posix(), neighbor) + "\n" + content[end:]
        with tempfile.TemporaryDirectory(dir=root / "build") as temporary:
            fixture = Path(temporary)
            for directory in ("scripts", "progress", "src"):
                shutil.copytree(root / directory, fixture / directory)
            for directory in ("config", "include", "reference", "roms", "toolchain", "tools", "docs"):
                (fixture / directory).symlink_to(root / directory, target_is_directory=True)
            for name in ("Dockerfile", "Makefile"):
                shutil.copy2(root / name, fixture / name)
            (fixture / relative).write_text(content)
            inventory_path = fixture / "progress/functions.json"
            inventory = json.loads(inventory_path.read_text())
            for entry in inventory["functions"]:
                if entry["symbol"] in (symbol, neighbor):
                    entry.pop("deferred", None)
                    entry["regions"]["us"]["state"] = "raw_asm"
            inventory_path.write_text(json.dumps(inventory))
            result = subprocess.run([sys.executable, "scripts/diff.py", "us", symbol, "--game", "--require-match"],
                                    cwd=fixture, capture_output=True, text=True)
            self.assertEqual(0, result.returncode, result.stdout + result.stderr)
            self.assertIn("CURRENT (0)", result.stdout)
            output = fixture / "build/us/linked-aliases" / symbol
            self.assertIn("GLOBAL_ASM", (output / "source.c").read_text())
            self.assertEqual("542153dd45050da6c8db54294eb8474bec9201ccf47014fe0f383c143b359d96",
                             hashlib.sha256((output / "candidate.bin").read_bytes()).hexdigest())
            symbols, extent, alignment = layout_check.archived_object_layout((output / "mixed.o").read_bytes())
            self.assertEqual((88, 800, 16), (symbols[neighbor], extent, alignment))
        self.assertEqual(original, source.read_bytes())

    def test_real_88_byte_initializer_and_held_jump_table_candidate(self):
        for symbol in ("func_15172C50", "func_15002878"):
            with self.subTest(symbol=symbol):
                source, _ = diff.find_work_item(symbol, "us", overlay="game")
                original = source.read_bytes()
                inventory = (diff.ROOT / "progress/functions.json").read_bytes()
                assembly = diff.ensure_reference_function("us", symbol, game_reference=True)
                reference = diff.reference_object("us", symbol, game_reference=True, assembly=assembly)
                deferred = symbol if diff.work_item_is_deferred(symbol) else None
                candidate = diff.compile_candidate("us", source, deferred_symbol=deferred)
                size = diff.expected_function_size("us", symbol)
                pair = diff.prepare_game_comparison(source, candidate, reference, assembly, symbol,
                                                    int(symbol[-8:], 16), size, deferred_symbol=deferred)
                if symbol == "func_15002878":
                    self.assertIsNone(pair)
                    mixed = Object32((diff.ROOT / "build/us/linked-aliases" / symbol / "mixed.o").read_bytes())
                    self.assertTrue(any("jtbl_" in item[1][0] for item in mixed.relocations.values()))
                else:
                    self.assertIsNotNone(pair)
                    obj = Object32(pair[0].read_bytes())
                    _, section = linked_aliases.function(obj, symbol, 88)
                    self.assertEqual("276590b6fd1af72abb45e1b76d352b988397165f8e9a5e69598a41a213e8465a",
                                     hashlib.sha256(obj.section(section)).hexdigest())
                    unit = diff.ROOT / "build/us/linked-aliases" / symbol / "candidate.bin"
                    self.assertEqual(800, unit.stat().st_size)
                    self.assertEqual("542153dd45050da6c8db54294eb8474bec9201ccf47014fe0f383c143b359d96",
                                     hashlib.sha256(unit.read_bytes()).hexdigest())
                self.assertEqual(original, source.read_bytes())
                self.assertEqual(inventory, (diff.ROOT / "progress/functions.json").read_bytes())
