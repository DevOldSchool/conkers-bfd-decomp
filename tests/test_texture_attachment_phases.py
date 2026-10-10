import copy
import unittest
from unittest import mock

from scripts import texture_attachment_phases as phases


class AttachmentPhaseTests(unittest.TestCase):
    def test_frame_witnesses_and_reviewed_branch_bounds(self):
        for frame, expected in phases.WITNESSES:
            self.assertEqual(phases.phase_index(frame), expected)
        for frame, expected in ((36, 6), (51, 0), (54, 0), (65, 8)):
            self.assertEqual(phases.phase_index(frame), expected)
        for frame in (35, 55, 60, 66, float('nan'), float('inf')):
            with self.assertRaisesRegex(ValueError, 'unreviewed'):
                phases.phase_index(frame)

    def fixture(self):
        base = phases.DATA[0][0]
        data = bytearray(phases.DATA[-2][0] + 4 - base)
        for address, expected in phases.DATA:
            raw = bytes.fromhex(expected)
            data[address - base:address - base + len(raw)] = raw
        shared = {'consumers': [{'function': 'guarded-shared-consumer'}], 'models': []}
        for entry, excluded in ((19, 13), (49, 174)):
            shared['models'].append({'entry': entry, 'texture_binding': {
                'selector': {'excluded_parent_0x84': excluded, 'parent_0x84': 0},
                'bindings': {'6': {'pixel_segment': 6, 'palette_segment': 6,
                                    'flats': [1352 if entry == 19 else 3256], 'selected_index': 0}}}})
        return base, data, shared

    def test_choices_preserve_old_context_and_use_only_proven_frames(self):
        base, data, shared = self.fixture()
        before = copy.deepcopy(shared)
        with mock.patch.object(phases.attachments, 'material_context', return_value=shared) as guard:
            choices = phases.verified_choices(b'code', 123, data, base)
        guard.assert_called_once_with(b'code', 123, data, base)
        self.assertEqual(shared, before)
        self.assertEqual([s['bindings']['6']['flats'][0] for s, _ in choices[49]],
                         [3250, 3251, 3252, 3253, 3254, 3255, 3257, 3258])
        state, proof = choices[19][0]
        self.assertEqual(state['bindings']['6']['flats'], [1351])
        self.assertEqual(state['selector']['parent_animation_frame'], 23)
        self.assertFalse(proof['uv_update']['geometry_changed'])
        for entry, variants in choices.items():
            for state, proof in variants:
                self.assertNotIn('excluded_parent_0x84', state['selector'])
                self.assertEqual(state['selector']['parent_0x84'], 13 if entry == 19 else 174)
                self.assertEqual(proof['native_consumers'], shared['consumers'])

    def test_changed_constants_tables_models_and_shared_code_fail_closed(self):
        base, data, shared = self.fixture()
        with mock.patch.object(phases.attachments, 'material_context', return_value=shared):
            for address, raw in phases.DATA:
                for i in range(len(bytes.fromhex(raw))):
                    changed = bytearray(data); changed[address - base + i] ^= 1
                    with self.assertRaisesRegex(ValueError, 'table or constant changed'):
                        phases.verified_choices(b'', 0, changed, base)
        with mock.patch.object(phases.attachments, 'material_context', side_effect=ValueError('consumer changed')):
            with self.assertRaisesRegex(ValueError, 'consumer changed'):
                phases.verified_choices(b'', 0, data, base)
        for entry in phases.MODELS:
            with self.assertRaisesRegex(ValueError, 'model changed'):
                phases.check_model(entry, bytes(1816))


if __name__ == '__main__':
    unittest.main()
