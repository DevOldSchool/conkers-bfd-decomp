from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import data_boundaries as data


def placement(name='game_rodata_pool', address=0x1020, size=0x20, payload=None,
              selector='*pool.o(.rodata)', mode='INFO'):
    text = (f'.{name} 0x{address:X} ({mode}) : SUBALIGN(4) {{ {selector} }}\n'
            f'ASSERT(SIZEOF(.{name}) == 0 || SIZEOF(.{name}) == {size}, "extent")\n')
    if payload is not None:
        text += f'__{name}_payload_size = {payload};\n'
    return text


class DataBoundaryTests(unittest.TestCase):
    def test_zero_gaps_remain_unassigned(self):
        spans = data.partition(0x1000, bytes(0x50), data.external_mappings(
            placement(payload=0x14), 'evidence.ld'))
        self.assertEqual([(s['start'], s['end'], s['kind']) for s in spans], [
            (0x1000, 0x1020, 'unassigned'), (0x1020, 0x1034, 'external_payload'),
            (0x1034, 0x1050, 'unassigned')])
        self.assertEqual(sum(s['size'] for s in spans), 0x50)
        self.assertEqual(spans[1]['compiler_padding_bytes'], 12)

    def test_invalid_ranges_fail(self):
        for spans in ([{'start': 0, 'end': 5}, {'start': 4, 'end': 8}],
                      [{'start': -1, 'end': 3}], [{'start': 0, 'end': 17}],
                      [{'start': 4, 'end': 4}]):
            with self.subTest(spans=spans), self.assertRaises(ValueError):
                data.partition(0, bytes(16), spans)

    def test_no_ownership_inferred_from_nonzero_or_zero_bytes(self):
        raw = bytes(range(16))
        spans = data.partition(100, raw, [])
        self.assertEqual(len(spans), 1)
        self.assertEqual(spans[0]['kind'], 'unassigned')
        self.assertEqual(spans[0]['sha256'], hashlib.sha256(raw).hexdigest())

    def test_missing_conflicting_duplicate_and_invalid_extents_fail(self):
        cases = [placement().split('ASSERT')[0], placement() + placement(),
                 placement() + 'ASSERT(SIZEOF(.game_rodata_pool) == 48, "changed")',
                 placement(payload=0), placement(payload=0x21), placement(payload=3),
                 placement(payload=0x10), placement(selector='*pool.o(.rodata) *other.o(.data)'),
                 placement().replace('(INFO)', '(COPY)'),
                 placement().replace('0x1020', '4128')]
        for text in cases:
            with self.subTest(text=text), self.assertRaises(ValueError):
                data.external_mappings(text, 'evidence.ld')

    def test_noload_does_not_imply_bss(self):
        result = data.external_mappings(placement(name='sdk_seed_data', mode='NOLOAD',
            selector='build/game-libs/us/libultra_2_0G.a:random.o(.data)'), 'sdk.ld')
        self.assertEqual(result[0]['input'], '.data')
        self.assertEqual(result[0]['end'] - result[0]['start'], 32)

    def test_real_constructor_payload_excludes_neighbor(self):
        mappings = data.external_mappings((ROOT / 'config/game/us-rodata.ld').read_text(), 'game.ld')
        pool = next(s for s in mappings if s['output'] == '.game_rodata_981e0')
        self.assertEqual((pool['start'], pool['end']), (0x80099DAC, 0x80099E98))
        self.assertEqual(pool['emitted_size'], 240)
        self.assertEqual(pool['compiler_padding_bytes'], 4)

    def test_shared_backing_counted_once_and_bss_excluded(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for overlay in ('main', 'game', 'debugger'):
                (root / 'config' / overlay).mkdir(parents=True)
                (root / f'config/{overlay}/us-rodata.ld').write_text('')
            (root / 'config/game/us-sdk.ld').write_text(
                placement(name='sdk_shared', address=0x1000, size=16,
                          selector='build/game-libs/us/lib.a:controller.o(.data)', mode='NOLOAD') +
                placement(name='sdk_workspace', address=0x9000, size=16,
                          selector='build/game-libs/us/lib.a:pfs.o(.bss)', mode='NOLOAD'))
            digest = hashlib.sha1(bytes(32)).hexdigest()
            (root / 'config/rzip_layouts.json').write_text(json.dumps({'profiles': {'us': {
                'normalized_sha1': [digest], 'game_format': 'rzip', 'game_start': '0x0',
                'game_end': '0x20', 'game_data_vram': '0x2000'}}}))
            with patch.object(data, 'checked_manifest', side_effect=lambda root, images, digest: images), \
                    patch.object(data.main_private_data, 'validated_rom', return_value=bytes(32)), \
                    patch.object(data, 'main_image', return_value=(bytes(32), 0x1000,
                        [{'start': 0x1000, 'end': 0x1010, 'kind': 'sdk_placement'}])), \
                    patch.object(data.rzip_archive, 'parse_game_archive', return_value=SimpleNamespace(data=bytes(32))), \
                    patch.object(data.rom_span, 'debugger_image', return_value=(b'', bytes(32), 0, 0x3000, digest)):
                result = data.audit(root)
            main = result['images']['main']
            self.assertEqual(main['mapped_bytes'], 16)
            self.assertEqual(main['ranges'][0]['shared_placements'][0]['consumer_overlay'], 'game')
            self.assertEqual(result['images']['game']['mapped_bytes'], 0)
            self.assertEqual(len(result['excluded_bindings']), 1)

    def test_failed_generation_removes_previous_audit(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            output = root / 'build/us/data-boundaries/audit.json'
            output.parent.mkdir(parents=True)
            output.write_text('{}')
            with patch.object(data, 'audit', side_effect=ValueError('bad ROM')), self.assertRaises(ValueError):
                data.generate(root)
            self.assertFalse(output.exists())

    def test_command_does_not_install_objdiff_or_build(self):
        spec = importlib.util.spec_from_file_location('objdiff_command', ROOT / 'scripts/objdiff.py')
        command = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(command)
        with patch.object(sys, 'argv', ['objdiff.py', 'data-audit']), \
                patch.object(command, 'install', side_effect=AssertionError('download')), \
                patch.object(data, 'generate', return_value=0) as generate:
            self.assertEqual(command.main(), 0)
        generate.assert_called_once_with(ROOT)


class CheckedManifestTests(unittest.TestCase):
    def fixture(self, root):
        (root / 'config/data').mkdir(parents=True)
        (root / 'src/main').mkdir(parents=True)
        (root / 'src/main/pool.c').touch()
        images = {'main': {'vram_start': 0x1000, 'vram_end': 0x1030, 'ranges': [
            {'start': 0x1000, 'end': 0x1020, 'kind': 'external_payload',
             'input': '.rodata', 'input_selector': '*pool.o(.rodata)'},
            {'start': 0x1020, 'end': 0x1030, 'kind': 'unassigned'}]}}
        document = {'schema_version': 2, 'rom_sha1': 'rom', 'owners': {'main': [
            {'address': '0x00001000', 'section': '.rodata',
             'owner': {'sources': ['src/main/pool.c', 'src/done/main/pool.c']}}]}}
        return images, document

    def test_extent_follows_build_without_copying_boundary_into_manifest(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            images, document = self.fixture(root)
            (root / 'config/data/us.json').write_text(json.dumps(document))
            images['main']['ranges'][0]['end'] = 0x1024
            images['main']['ranges'][1]['start'] = 0x1024
            result = data.checked_manifest(root, images, 'rom')['main']['ranges']
            self.assertEqual(result[0]['end'], 0x1024)
            self.assertEqual(result[0]['owner'], document['owners']['main'][0]['owner'])
            self.assertIsNone(result[1]['owner'])

    def test_missing_extra_duplicate_wrong_section_and_invented_owners_fail(self):
        from copy import deepcopy
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            images, document = self.fixture(root)
            for change in ('missing', 'extra', 'duplicate', 'section', 'source', 'sdk',
                           'decimal', 'rom', 'extent'):
                bad = deepcopy(document)
                owners = bad['owners']['main']
                if change == 'missing':
                    owners.clear()
                elif change == 'extra':
                    owners.append({**owners[0], 'address': '0x00001020'})
                elif change == 'duplicate':
                    owners.append(dict(owners[0]))
                elif change == 'section':
                    owners[0]['section'] = '.data'
                elif change == 'source':
                    owners[0]['owner'] = {'sources': ['src/main/fake.c']}
                elif change == 'sdk':
                    owners[0]['owner'] = {'archive': 'fake', 'member': 'pool.o'}
                elif change == 'decimal':
                    owners[0]['address'] = 4096
                elif change == 'rom':
                    bad['rom_sha1'] = 'different'
                else:
                    owners[0]['end'] = '0x00001020'
                (root / 'config/data/us.json').write_text(json.dumps(bad))
                with self.subTest(change=change), self.assertRaises(ValueError):
                    data.checked_manifest(root, deepcopy(images), 'rom')

    def test_active_source_rejects_missing_and_ambiguous_alternatives(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            sources = ['raw.c', 'done.c']
            with self.assertRaisesRegex(ValueError, 'exactly one'):
                data.active_source(root, sources)
            (root / 'done.c').touch()
            self.assertEqual(data.active_source(root, sources), 'done.c')
            (root / 'raw.c').touch()
            with self.assertRaisesRegex(ValueError, 'exactly one'):
                data.active_source(root, sources)


if __name__ == '__main__':
    unittest.main()
