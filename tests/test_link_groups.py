"""Check that per-asset linker statements collapse into ordered partial links."""
from __future__ import annotations

import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
import link_groups

# Concatenates its response-file members; stands in for `ld -r` on binary objects.
FAKE_LINKER = '''import sys
from pathlib import Path
arguments = sys.argv[1:]
output = Path(arguments[arguments.index('-o') + 1])
members = Path(arguments[-1][1:]).read_text().split()
output.write_bytes(b''.join(Path(member).read_bytes() for member in members))
'''


def section(name: str, objects: list[str], subalign: int = 1) -> str:
    body = ''.join(f'        {path}(.data);\n' for path in objects)
    return (f'    .{name} prev_VRAM_END : AT({name}_ROM_START) SUBALIGN({subalign})\n'
            f'    {{\n        {name}_DATA_START = .;\n{body}        {name}_DATA_END = .;\n    }}\n')


def assets(prefix: str, count: int) -> list[str]:
    return [f'build/us/assets/{prefix}/{index:04d}.o' for index in range(count)]


class GroupScriptTests(unittest.TestCase):
    def test_long_runs_group_in_order_and_short_or_aligned_runs_stay(self):
        textures = assets('flat/textures', 10)
        script = (section('assets_flat_rzip', ['build/us/assets/flat/raw/001A37E0.o'] + textures)
                  + section('font_rle', assets('font/glyphs', 3))
                  + section('code', assets('aligned', 9), subalign=16)
                  + section('asset_bank_17', ['build/us/src/x.o'] + assets('audio/a', 8) + ['build/us/src/y.o']
                            + assets('audio/b', 8)))
        grouped, groups = link_groups.group_script(script, 'build/us/link-groups')
        self.assertEqual(list(groups), ['build/us/link-groups/assets_flat_rzip-0.o',
                                        'build/us/link-groups/asset_bank_17-0.o',
                                        'build/us/link-groups/asset_bank_17-1.o'])
        # The raw object starts the same run: grouping is by statement, not family.
        self.assertEqual(groups['build/us/link-groups/assets_flat_rzip-0.o'],
                         ['build/us/assets/flat/raw/001A37E0.o'] + textures)
        self.assertEqual(groups['build/us/link-groups/asset_bank_17-1.o'], assets('audio/b', 8))
        for kept in assets('font/glyphs', 3) + assets('aligned', 9) + ['build/us/src/x.o', 'build/us/src/y.o']:
            self.assertIn(f'        {kept}(.data);\n', grouped)
        for name in groups:
            self.assertEqual(grouped.count(f'{name}(.data);'), 1)
        self.assertNotIn('flat/textures/0000.o', grouped)
        self.assertLess(grouped.index('src/x.o'), grouped.index('asset_bank_17-0.o'))
        self.assertLess(grouped.index('asset_bank_17-0.o'), grouped.index('src/y.o'))
        self.assertLess(grouped.index('src/y.o'), grouped.index('asset_bank_17-1.o'))


class LinkGroupsCommandTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary.name)
        self.addCleanup(self.temporary.cleanup)
        self.linker = self.root / 'fake_ld.py'
        self.linker.write_text(FAKE_LINKER)
        self.textures = assets('flat/textures', 9)
        self.fonts = assets('font/glyphs', 9)
        for index, path in enumerate(self.textures + self.fonts + ['build/us/src/main.o']):
            target = self.root / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(bytes([index]))
        (self.root / 'build/us/conker.us.ld').write_text(
            section('assets_flat_rzip', self.textures) + section('font_rle', self.fonts))
        (self.root / 'build/us/link-inputs.txt').write_text(
            ' '.join(['build/us/src/main.o'] + self.textures + self.fonts))

    def run_groups(self) -> subprocess.CompletedProcess:
        return subprocess.run(
            [sys.executable, str(ROOT / 'scripts/link_groups.py'), 'build/us/conker.us.ld',
             '--output', 'build/us/conker.us.grouped.ld', '--group-dir', 'build/us/link-groups',
             '--inputs', 'build/us/link-inputs.txt', '--responses', 'build/us/link-inputs.rsp',
             '--linker', f'{sys.executable} {self.linker}'],
            cwd=self.root, text=True, capture_output=True)

    def test_groups_relink_only_when_members_change(self):
        result = self.run_groups()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('18 asset inputs in 2 groups (2 relinked)', result.stderr)
        texture_group = self.root / 'build/us/link-groups/assets_flat_rzip-0.o'
        font_group = self.root / 'build/us/link-groups/font_rle-0.o'
        self.assertEqual(texture_group.read_bytes(), bytes(range(9)))
        self.assertEqual(font_group.read_bytes(), bytes(range(9, 18)))
        self.assertEqual((self.root / 'build/us/link-inputs.rsp').read_text().split(),
                         ['build/us/src/main.o', 'build/us/link-groups/assets_flat_rzip-0.o',
                          'build/us/link-groups/font_rle-0.o'])

        before = font_group.stat().st_mtime_ns
        self.assertIn('(0 relinked)', self.run_groups().stderr)
        changed = self.root / self.textures[3]
        changed.write_bytes(b'\xff')
        later = texture_group.stat().st_mtime_ns + 1_000_000_000
        os.utime(changed, ns=(later, later))
        result = self.run_groups()
        self.assertIn('(1 relinked)', result.stderr)
        self.assertEqual(texture_group.read_bytes()[3:4], b'\xff')
        self.assertEqual(font_group.stat().st_mtime_ns, before)

    def test_script_objects_missing_from_the_link_are_rejected(self):
        (self.root / 'build/us/link-inputs.txt').write_text(' '.join(self.textures))
        result = self.run_groups()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('outside the link', result.stderr)
        self.assertFalse((self.root / 'build/us/conker.us.grouped.ld').exists())


if __name__ == '__main__':
    unittest.main()
