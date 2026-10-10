"""Selector provenance and command boundaries fail closed."""
import copy
import hashlib
import struct
import unittest
from contextlib import ExitStack
from pathlib import Path
from types import SimpleNamespace as NS
from unittest.mock import patch

from scripts import texture_character_selectors as selectors


def sha(raw):
    return hashlib.sha1(raw).hexdigest()


class CharacterSelectorTests(unittest.TestCase):
    def script(self, commands=None):
        # Distinct counts prove that commands do not start at 1 + 3 * tracks.
        commands = commands or [bytes.fromhex(s) for s in (
            '0000001400000000', '0902000601000000', '0503006f00090000')]
        metadata = bytes.fromhex('0900000400000000') * 4
        blocks = [struct.pack('>4H', 2, 1, 2, 0), bytes(8), bytes(8),
                  bytes.fromhex('0002070000000000'), bytes.fromhex('0002090000000000'),
                  bytes(8), metadata + b''.join(commands), bytes(32)]
        offset = len(blocks) * 8
        table = []
        for index, raw in enumerate(blocks):
            table.append(struct.pack('>II', offset, len(raw) | (0x80000000 if index == len(blocks)-1 else 0)))
            offset += len(raw)
        return b''.join(table + blocks)

    def test_native_command_group_metadata_and_time_are_preserved(self):
        raw = self.script()
        commands = selectors.command_selectors(raw, 0)
        self.assertEqual([(r['segment'], r['descriptor_index']) for r in commands], [(7, 6), (10, 9)])
        self.assertEqual([r['declared_time'] for r in commands], [20, 22])
        self.assertEqual([r['command_index'] for r in commands], [5, 6])
        self.assertTrue(all(r['command_child'] == 6 for r in commands))
        self.assertEqual(commands[0]['preceding_commands'][:4], ['0900000400000000'] * 4)
        self.assertEqual(selectors.command_selectors(raw, 1), [])

    def test_signed_operands_and_unsupported_commands_cannot_select(self):
        invalid = [bytes.fromhex(s) for s in (
            '0900ffff00000000', '090000f600000000', '09000003ff000000',
            '0900000302000000', '0500006f00800000', '0500006e00090000',
            '0800000300000000')]
        self.assertEqual(selectors.command_selectors(self.script(invalid), 0), [])

    def test_missing_short_partial_and_out_of_range_command_blocks_reject(self):
        raw = self.script()
        for size in (24, 33, 0xFFFFFF):
            altered = bytearray(raw)
            struct.pack_into('>I', altered, 6 * 8 + 4, size)
            with self.subTest(size=size), self.assertRaises(ValueError):
                selectors.command_selectors(altered, 0)
        with self.assertRaisesRegex(ValueError, 'track is out of range'):
            selectors.command_selectors(raw, 2)
        altered = bytearray(raw)
        # Header group count would place the selected command beyond the directory.
        struct.pack_into('>H', altered, 8 * 8 + 2, 100)
        with self.assertRaisesRegex(ValueError, 'command group is missing'):
            selectors.command_selectors(altered, 0)

    def update_fixture(self):
        code = b'full native update and blink functions'
        data = struct.pack('>3I', 18, 11, 19)
        manifest = {'entries': {entry: {'descriptor_indices': {'6': 4, '7': 5, '10': 1, '11': 2}}
                                for entry in (66, 91)}}
        return code, data, manifest

    def test_native_update_outcomes_preserve_initializers_and_binding_proof(self):
        code, data, manifest = self.update_fixture()
        before = copy.deepcopy(manifest)
        with patch.object(selectors, 'UPDATE_SPANS', ((0x1000, len(code), sha(code)),)), \
                patch.object(selectors, 'UPDATE_TABLE', (0x2000, len(data), sha(data))):
            result = selectors.update_choices(manifest, code, 0x1000, data, 0x2000)
        self.assertEqual([d['descriptor_indices']['10'] for _, d, _ in result[66]], [13, 12, 21])
        self.assertEqual([d['descriptor_indices']['10'] for _, d, _ in result[91]], [18, 11, 19])
        self.assertTrue(all(d['descriptor_indices']['6'] == 4 for rows in result.values() for _, d, _ in rows))
        self.assertEqual(result[66][1][2]['representative_state'],
                         {'animation': 1, 'prior_selector': 13, 'random_low_bits': 1})
        self.assertEqual(manifest, before)

    def test_whole_native_span_and_every_table_byte_are_guarded(self):
        code, data, manifest = self.update_fixture()
        with patch.object(selectors, 'UPDATE_SPANS', ((0x1000, len(code), sha(code)),)), \
                patch.object(selectors, 'UPDATE_TABLE', (0x2000, len(data), sha(data))):
            for offset in (0, len(code)-1):
                changed = bytearray(code); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'evidence changed'):
                    selectors.update_choices(manifest, changed, 0x1000, data, 0x2000)
            for offset in range(len(data)):
                changed = bytearray(data); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'evidence changed'):
                    selectors.update_choices(manifest, code, 0x1000, changed, 0x2000)

    def test_reference_rom_changes_fail_before_any_source_lookup(self):
        with self.assertRaisesRegex(ValueError, 'reference ROM changed'):
            selectors.load(None, b'changed ROM', {})

    def test_stored_commands_keep_the_initial_track_and_spawn_binding(self):
        raw = self.script()
        manifest = {'entries': {7: {'sha1': 'initializer', 'descriptor_indices': {'6': 1, '7': 2, '10': 3}}}}
        track = dict(selectors.alpha.script_tracks(raw)[0], model=[1, 7, 0], combined_record_index=1)
        script = {'asset_path': [6, 0, 0], 'rom_span': ['0x0', hex(len(raw))],
                  'sha256': hashlib.sha256(raw).hexdigest(), 'matches': [track], 'tracks': [track]}
        spawn = {'model': [1, 7, 0], 'combined_record_index': 1, 'record_hex': 'stored spawn'}
        callers = {'consumer_spans': ['native spawn'], 'jump_table_spans': ['native table'],
                   'spawn_contexts': [{'entry': 0, 'records': [spawn], 'prefix_sha256': 'prefix'}],
                   'scene_script_routes': [{'scene': 0, 'scripts': [script]}]}
        bank, parent = NS(index=6), NS(index=0, start=0, end=len(raw))
        child = NS(index=0, start=0, end=len(raw), compressed=False)
        layout = dict(game_start=0, game_end=0, game_vram=0, game_data_vram=0, asset_table=0)
        with ExitStack() as stack:
            for owner, name, value in ((selectors, 'US_SHA1', sha(raw)),):
                stack.enter_context(patch.object(owner, name, value))
            stack.enter_context(patch.object(selectors.h, 'resolve_rom', return_value=(None, layout)))
            stack.enter_context(patch.object(selectors.h, 'parse_game_archive', return_value=NS(code=b'', data=b'')))
            stack.enter_context(patch.object(selectors, 'update_choices', return_value={}))
            stack.enter_context(patch.object(selectors.alpha, 'checked_spans', return_value=['guard']))
            stack.enter_context(patch.object(selectors.alpha, 'caller_evidence', return_value=callers))
            stack.enter_context(patch.object(selectors.models, 'parse_asset_banks', return_value=[bank]))
            stack.enter_context(patch.object(selectors.models, 'parse_asset_entries',
                side_effect=lambda rom, selected: [parent] if selected.index == 6 else [child]))
            result = selectors.load(Path('/synthetic'), raw, manifest)
            self.assertEqual(list(result), [7])
            self.assertEqual(len(result[7]), 2)
            for _, default, proof in result[7]:
                self.assertEqual(default['descriptor_indices']['6'], 1)
                self.assertEqual(proof['spawn_record'], spawn)
                self.assertEqual(proof['track'], track)
                self.assertEqual(proof['script']['asset_path'], [6, 0, 0])
            script['sha256'] = 'changed'
            with self.assertRaisesRegex(ValueError, 'source changed'):
                selectors.load(Path('/synthetic'), raw, manifest)
