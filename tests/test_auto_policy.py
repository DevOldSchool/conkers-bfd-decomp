from __future__ import annotations

import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import auto_policy


def entry(symbol: str, state: str, differences: int | None = None, deferred_score: int | None = None) -> dict:
    us = {"state": state, "symbol": symbol, "vram": "0x15000000"}
    if differences is not None:
        us["evidence"] = {"current_differences": differences}
    data = {"overlay": "game", "regions": {"us": us}, "source": "src/game/game_1.c", "symbol": symbol}
    if deferred_score is not None:
        data["deferred"] = {"candidate_preserved": True, "current_score": deferred_score}
    return data


BASE_FUNCTIONS = [entry("func_A", "raw_asm", deferred_score=40), entry("func_B", "raw_asm"), entry("func_C", "matched", 0)]


def inventory_text(functions: list[dict]) -> str:
    return json.dumps({"functions": functions, "schema_version": 3}, indent=1)
BASE_SOURCE = '#include "game_functions.h"\n\n#pragma GLOBAL_ASM("asm/func_A.s")\n\n#pragma GLOBAL_ASM("asm/func_B.s")\n'
MATCHED_A = '#include "game_functions.h"\n\nvoid func_A(void) {\n    D_1 = 0;\n}\n\n#pragma GLOBAL_ASM("asm/func_B.s")\n'


def owner(address: str, *sources: str, section: str = '.rodata') -> dict:
    return {"address": address, "section": section, "owner": {"sources": list(sources)}}


BASE_OWNERS = [owner('0x80001000', 'src/game/game_2.c', 'src/done/game/game_2.c')]


def owners_text(game: list[dict]) -> str:
    return json.dumps({"schema_version": 1, "rom_sha1": "abc", "owners": {"game": game}}, indent=2)


class Repo:
    def __init__(self, root: Path):
        self.root = root
        self.git('init', '-q', '-b', 'main')
        self.git('config', 'user.name', 'Test')
        self.git('config', 'user.email', 'test@example.invalid')
        self.write('progress/functions.json', inventory_text(BASE_FUNCTIONS))
        self.write('src/game/game_1.c', BASE_SOURCE)
        self.write('include/game_functions.h', 'void func_A(void);\n')
        self.write('config/game/us-rodata.ld', 'KEEP(a)\nKEEP(b)\n')
        self.write('config/data/us.json', owners_text(BASE_OWNERS))
        self.write('config/game/us.yaml', 'segments:\n  - [0x100, c, game/game_1]\n  - [0x200, c, done/game/game_2]\n')
        self.commit('base')
        self.git('checkout', '-q', '-b', 'topic')

    def git(self, *args: str) -> str:
        return subprocess.check_output(['git', '-C', str(self.root), *args], text=True, stderr=subprocess.DEVNULL)

    def write(self, rel: str, text: str) -> None:
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)

    def commit(self, message: str) -> None:
        self.git('add', '-A')
        self.git('commit', '-qm', message)

    def inventory(self, **changes: dict) -> None:
        functions = [changes.get(f["symbol"], f) for f in BASE_FUNCTIONS]
        self.write('progress/functions.json', inventory_text(functions))

    def evaluate(self, *ids: str) -> auto_policy.Result:
        return auto_policy.evaluate(str(self.root), 'main', 'topic', list(ids))


class AutoPolicyTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.repo = Repo(Path(self.tmp.name))

    def tearDown(self):
        self.tmp.cleanup()

    def match_a(self, source: str = MATCHED_A) -> None:
        self.repo.write('src/game/game_1.c', source)
        self.repo.inventory(func_A=entry('func_A', 'matched', 0))

    def test_clean_match_passes(self):
        self.match_a()
        self.repo.write('config/game/us-rodata.ld', 'KEEP(a)\nKEEP(b)\nKEEP(c)\n')
        self.repo.commit('match func_A')
        result = self.repo.evaluate('func_A')
        self.assertEqual(result.findings, [])
        self.assertTrue(result.passed)

    def test_rename_into_done_is_allowed(self):
        self.match_a()
        (self.repo.root / 'src/done/game').mkdir(parents=True)
        (self.repo.root / 'src/game/game_1.c').rename(self.repo.root / 'src/done/game/game_1.c')
        moved = [dict(f, source='src/done/game/game_1.c') for f in BASE_FUNCTIONS]
        moved[0] = dict(entry('func_A', 'matched', 0), source='src/done/game/game_1.c')
        self.repo.write('progress/functions.json', inventory_text(moved))
        self.repo.write('config/game/us.yaml', 'segments:\n  - [0x100, c, done/game/game_1]\n  - [0x200, c, done/game/game_2]\n')
        self.repo.commit('integrate')
        result = self.repo.evaluate('func_A')
        self.assertEqual(result.findings, [])
        self.assertIn('src/game/game_1.c -> src/done/game/game_1.c', result.notes)
        self.assertIn('func_B moved with its completed unit', result.notes)

    def test_completed_unit_below_rename_similarity_is_a_move(self):
        # Matching most of a unit and moving it under done/ in one commit drops
        # Git's similarity below 50%, so it reports D + A rather than R.
        body = '\n'.join(f'void func_{i}(void) {{\n    D_{i} = {i} * 7 + D_{i + 1};\n}}\n' for i in range(40))
        (self.repo.root / 'src/done/game').mkdir(parents=True)
        (self.repo.root / 'src/game/game_1.c').unlink()
        self.repo.write('src/done/game/game_1.c', '#include "game_functions.h"\n\nvoid func_A(void) {\n    D_1 = 0;\n}\n\n' + body)
        moved = [dict(f, source='src/done/game/game_1.c') for f in BASE_FUNCTIONS]
        moved[0] = dict(entry('func_A', 'matched', 0), source='src/done/game/game_1.c')
        self.repo.write('progress/functions.json', inventory_text(moved))
        self.repo.write('config/game/us.yaml', 'segments:\n  - [0x100, c, done/game/game_1]\n  - [0x200, c, done/game/game_2]\n')
        self.repo.commit('integrate heavy')
        status = self.repo.git('diff', '--name-status', 'main...topic')
        self.assertIn('D\tsrc/game/game_1.c', status)
        result = self.repo.evaluate('func_A')
        self.assertEqual(result.findings, [])
        self.assertIn('src/game/game_1.c -> src/done/game/game_1.c', result.notes)

    def test_source_map_layout_change_fails(self):
        self.match_a()
        self.repo.write('config/game/us.yaml', 'segments:\n  - [0x100, c, game/game_1]\n  - [0x180, c, game/game_1b]\n  - [0x200, c, done/game/game_2]\n')
        self.repo.commit('split')
        self.assertIn('config/game/us.yaml: changes other than moving completed units under done/', self.repo.evaluate('func_A').findings)

    def test_header_change_fails(self):
        self.match_a()
        self.repo.write('include/game_functions.h', 'void func_A(void);\nvoid func_B(s32);\n')
        self.repo.commit('header')
        findings = self.repo.evaluate('func_A').findings
        self.assertTrue(any(f.startswith('include/game_functions.h') for f in findings), findings)

    def test_tooling_change_fails(self):
        self.match_a()
        self.repo.write('scripts/x.py', 'print(1)\n')
        self.repo.commit('tooling')
        self.assertTrue(any('scripts/x.py' in f for f in self.repo.evaluate('func_A').findings))

    def test_fake_constructs_fail(self):
        for body, reason in [('    if (1) {}\n', 'fake match'), ('    x = y ^ 0;\n', 'fake match'),
                             ('    volatile s32 t;\n', 'volatile'), ('#include "extra.h"\n', 'include'),
                             ('#if 0\n', 'preprocessor')]:
            with self.subTest(body=body):
                self.match_a(MATCHED_A.replace('    D_1 = 0;\n', '    D_1 = 0;\n' + body))
                self.repo.commit('variant')
                findings = self.repo.evaluate('func_A').findings
                self.assertTrue(any(reason in f for f in findings), (body, findings))
                self.repo.git('reset', '-q', '--hard', 'main')

    def test_unclaimed_inventory_change_fails(self):
        self.match_a()
        self.repo.inventory(func_A=entry('func_A', 'matched', 0), func_B=entry('func_B', 'raw_asm', deferred_score=12))
        self.repo.commit('defer too')
        self.assertIn('progress/functions.json: func_B changed but is not a claimed match', self.repo.evaluate('func_A').findings)

    def test_claim_without_match_fails(self):
        self.match_a()
        self.repo.commit('match')
        findings = self.repo.evaluate('func_A', 'func_B').findings
        self.assertIn('progress/functions.json: claimed func_B has no inventory change', findings)

    def test_claim_not_matched_state_fails(self):
        self.repo.write('src/game/game_1.c', MATCHED_A)
        self.repo.inventory(func_A=entry('func_A', 'raw_asm', deferred_score=4))
        self.repo.commit('deferred')
        findings = self.repo.evaluate('func_A').findings
        self.assertTrue(any("claimed func_A is 'raw_asm'" in f for f in findings), findings)

    def test_rodata_removal_fails(self):
        self.match_a()
        self.repo.write('config/game/us-rodata.ld', 'KEEP(a)\n')
        self.repo.commit('rodata')
        self.assertTrue(any('us-rodata.ld: removes 1 line' in f for f in self.repo.evaluate('func_A').findings))

    def test_literal_owner_record_for_matched_unit_passes(self):
        self.match_a()
        self.repo.write('config/game/us-rodata.ld', 'KEEP(a)\nKEEP(b)\nKEEP(c)\n')
        self.repo.write('config/data/us.json', owners_text(BASE_OWNERS + [
            owner('0x80002000', 'src/game/game_1.c', 'src/done/game/game_1.c')]))
        self.repo.commit('literal pool')
        self.assertEqual(self.repo.evaluate('func_A').findings, [])

    def test_owner_record_problems_fail(self):
        cases = [
            ('unit this PR does not change', BASE_OWNERS + [owner('0x80002000', 'src/game/game_3.c')]),
            ('is not a .rodata source-owner record', BASE_OWNERS + [owner('0x80002000', 'src/game/game_1.c', section='.data')]),
            ('duplicates an existing address', BASE_OWNERS + [owner('0x80001000', 'src/game/game_1.c')]),
            ('changed or removed', [owner('0x80001000', 'src/game/game_1.c')]),
        ]
        for reason, records in cases:
            with self.subTest(reason=reason):
                self.match_a()
                self.repo.write('config/data/us.json', owners_text(records))
                self.repo.commit('owners')
                findings = self.repo.evaluate('func_A').findings
                self.assertTrue(any(reason in f for f in findings), (reason, findings))
                self.repo.git('reset', '-q', '--hard', 'main')

    def test_cli_exit_codes(self):
        self.match_a()
        self.repo.commit('match')
        self.assertEqual(auto_policy.main(['--repo', str(self.repo.root), '--base', 'main', '--head', 'topic', '--ids', 'func_A']), 0)
        self.assertEqual(auto_policy.main(['--repo', str(self.repo.root), '--base', 'main', '--head', 'topic', '--ids', 'func_B', '--json']), 1)


if __name__ == '__main__':
    unittest.main()
