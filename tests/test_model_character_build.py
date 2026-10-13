from __future__ import annotations

import copy
import unittest

from scripts import model_build, model_character_build as character
from test_model_assets import character_model_payload


class CharacterBuildTests(unittest.TestCase):
    def test_typed_regions_roundtrip_and_mutations_change_bytes(self):
        payload = character_model_payload()
        records = character.character_records(payload)
        self.assertEqual(character.encode_character_records(records), payload)
        self.assertEqual(model_build.encode_records(model_build.model_records(payload, bank=1), bank=1), payload)
        for field, component, value in [('vertices', 0, -123), ('joints', 4, -2.5),
                                         ('normal_xy_s8', 0, -100), ('procedural_joint_indices', 0, 255)]:
            changed = copy.deepcopy(records)
            changed[field][0][component] = value
            with self.subTest(field=field):
                rebuilt = character.encode_character_records(changed)
                self.assertNotEqual(rebuilt, payload)
                self.assertEqual(character.character_records(rebuilt), changed)

    def test_native_counts_pointers_and_opaque_storage_fail(self):
        records = character.character_records(character_model_payload())
        for field in ('vertices', 'joints', 'texture_descriptors', 'normal_xy_s8', 'primary_pointers'):
            changed = copy.deepcopy(records)
            changed[field].pop()
            with self.subTest(field=field), self.assertRaises(ValueError):
                character.encode_character_records(changed)
        for key, value in [('opaque', '00'), ('zero_regions', [[0, 16]]), ('header_words', [0])]:
            with self.subTest(field=key), self.assertRaises(ValueError):
                character.encode_character_records(dict(records, **{key: value}))
        changed = copy.deepcopy(records)
        changed['primary_pointers'][0][0] += 8
        with self.assertRaises(ValueError):
            character.encode_character_records(changed)
        with self.assertRaises(ValueError):
            character.character_records(character_model_payload() + b'\x01')

    def test_small_zero_suffixes_are_explicit_and_nonzero_suffixes_fail(self):
        for count in (1, 6, 15):
            payload = character_model_payload() + bytes(count)
            records = character.character_records(payload)
            self.assertEqual(records['zero_regions'], [[len(payload) - count, count]])
            self.assertEqual(character.encode_character_records(records), payload)
        with self.assertRaises(ValueError):
            character.character_records(character_model_payload() + bytes(16))

    def test_full_consumer_spans_are_required(self):
        with self.assertRaisesRegex(ValueError, 'character consumer changed'):
            character.verify_consumers(b'', 0x15000000)
