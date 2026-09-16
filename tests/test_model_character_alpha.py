import unittest
import hashlib
import struct
from types import SimpleNamespace

from scripts import model_character_alpha as alpha


class CharacterAlphaTests(unittest.TestCase):
    @staticmethod
    def script_payload(blocks):
        offset = len(blocks) * 8
        directory = bytearray()
        for index, block in enumerate(blocks):
            flags = 0x80000000 if index == len(blocks) - 1 else 0
            directory.extend(struct.pack('>II', offset, flags | len(block)))
            offset += len(block)
        return directory + b''.join(blocks)

    def test_script_tracks_follow_header_count_and_contiguous_descriptors(self):
        blocks = [struct.pack('>4H', 2, 2, 2, 0), bytes(16), b'',
                  bytes.fromhex('0002120000000000'), bytes.fromhex('00020e0000000000')]
        data = self.script_payload(blocks)
        rows = alpha.script_tracks(data)
        self.assertEqual([2, 0], [row['initial_counter'] for row in rows])
        self.assertEqual([18, 14], [row['script_selector'] for row in rows])
        self.assertEqual(48, rows[0]['track_offset'])
        self.assertEqual(64, rows[0]['descriptor_offset'])
        self.assertEqual(hashlib.sha256(bytes(16)).hexdigest(), rows[0]['track_sha256'])
        self.assertEqual([], alpha.script_tracks(self.script_payload([bytes(8)])))

    def test_script_rejects_bad_ranges_flags_and_layout(self):
        blocks = [struct.pack('>4H', 1, 1, 1, 0), bytes(8), bytes.fromhex('0002120000000000')]
        data = self.script_payload(blocks)
        for offset, value in ((0, 7), (0, len(data) + 8), (8, 16),
                              (12, 0x10000008), (20, 8), (20, 0x80000009)):
            changed = bytearray(data)
            struct.pack_into('>I', changed, offset, value)
            with self.assertRaises(ValueError):
                alpha.script_tracks(changed)
        for bad in (b'', data[:7], data[:-1], self.script_payload([bytes(6)]),
                    self.script_payload([struct.pack('>4H', 256, 0, 0, 0)]),
                    self.script_payload([blocks[0], bytes(8 * 65536), blocks[2]]),
                    self.script_payload([blocks[0], bytes(7), blocks[2]]),
                    self.script_payload([blocks[0], blocks[1]]),
                    self.script_payload([blocks[0], blocks[1], bytes(9)])):
            with self.assertRaises(ValueError):
                alpha.script_tracks(bad)
        two = self.script_payload([struct.pack('>4H', 2, 2, 2, 0), bytes(8), bytes(8),
                                   bytes(8), bytes(8), bytes(8)])
        struct.pack_into('>I', two, 4 * 8, struct.unpack_from('>I', two, 4 * 8)[0] + 1)
        with self.assertRaises(ValueError):
            alpha.script_tracks(two)

    def test_script_selectors_use_first_match_including_prefix_and_skip_empty_tracks(self):
        records = bytearray(4 * 48)
        for i, (model, selector) in enumerate(((5, 18), (154, 18), (162, 14), (155, 0))):
            records[i * 48 + 4] = model
            records[i * 48 + 0x28] = selector
        tracks = [{'track_index': i, 'descriptor_type': typ, 'script_selector': selector,
                   'initial_counter': count} for i, (typ, selector, count) in enumerate(
                       ((2, 18, 1), (2, 14, 1), (2, 0, 1), (2, 14, 0), (1, 14, 1), (2, 99, 1)))]
        rows = alpha.script_spawn_matches(tracks, records, {154, 155, 162})
        self.assertEqual(1, len(rows))
        self.assertEqual([1, 162, 0], rows[0]['model'])
        self.assertEqual(2, rows[0]['combined_record_index'])

    def test_wrapper_full_opacity_and_mode_four_attenuation(self):
        self.assertEqual(255, alpha.wrapper_opacity(255, 255))
        self.assertEqual(253, alpha.wrapper_opacity(254, 255))
        self.assertEqual(0, alpha.wrapper_opacity(0, 255))
        self.assertEqual(255, alpha.wrapper_opacity(128, 255, force_full=True))
        self.assertEqual(254, alpha.wrapper_opacity(255, 255, mode_4_alpha=255))
        self.assertEqual(127, alpha.wrapper_opacity(128, 255, force_full=True, mode_4_alpha=128))
        self.assertEqual('0x80082FC0', alpha.render_table_for_call(
            4, alpha.wrapper_opacity(255, 255, mode_4_alpha=255))['segment_8_base'])
        for value in (-1, 256):
            with self.assertRaises(ValueError):
                alpha.wrapper_opacity(value, 255)
            with self.assertRaises(ValueError):
                alpha.wrapper_opacity(255, 255, mode_4_alpha=value)

    def test_spawn_identity_signed_position_and_record_alignment(self):
        data = bytearray(3 * 48)
        data[4] = 155
        data[48 + 3:48 + 5] = bytes([2, 162])
        data[48 + 2] = 1
        data[48 + 0x28] = 14
        struct.pack_into('>hhh', data, 48 + 6, -32768, 32767, -339)
        data[96 + 5] = 162  # Wrong field must not supply a model identity.
        rows = alpha.spawn_records(bytes(data), {162})
        self.assertEqual(1, len(rows))
        self.assertEqual([1, 162, 0], rows[0]['model'])
        self.assertEqual(1, rows[0]['record_index'])
        self.assertEqual(48, rows[0]['decoded_offset'])
        self.assertEqual(2, rows[0]['actor_type_byte'])
        self.assertTrue(rows[0]['ordinary_spawn_skipped'])
        self.assertEqual(14, rows[0]['script_selector'])
        self.assertEqual([-32768, 32767, -339], rows[0]['initial_position_xyz'])
        self.assertEqual(bytes(data[48:96]), bytes.fromhex(rows[0]['record_hex']))
        for size in (1, 47, 49):
            with self.assertRaisesRegex(ValueError, 'whole number'):
                alpha.spawn_records(bytes(size), {162})

    def test_caller_proof_rejects_changed_truncated_and_misplaced_spans(self):
        data = b'\x01\x02\x03\x04'
        spans = ((0x1000, 4, hashlib.sha1(data).hexdigest()),)
        self.assertEqual(4, alpha.checked_spans(data, 0x1000, spans)[0]['bytes'])
        for value, base in ((data[:-1], 0x1000), (bytes(4), 0x1000), (data, 0x1004)):
            with self.assertRaisesRegex(ValueError, 'caller evidence changed'):
                alpha.checked_spans(value, base, spans)

    def test_opacity_boundary_and_special_modes(self):
        for mode in (0, 1, 2, 4):
            self.assertEqual('0x80082FC0', alpha.render_table_for_call(mode, 254)['segment_8_base'])
            self.assertEqual('0x80083140', alpha.render_table_for_call(mode, 255)['segment_8_base'])
        for mode in (3, 5):
            for opacity in (0, 254, 255):
                self.assertEqual('0x800832C0', alpha.render_table_for_call(mode, opacity)['segment_8_base'])
        self.assertEqual('secondary', alpha.render_table_for_call(3, 255)['display_list_table'])
        self.assertEqual('primary', alpha.render_table_for_call(5, 255)['display_list_table'])

    def test_outside_reviewed_input_domain_is_rejected(self):
        for mode, opacity in ((-1, 255), (6, 255), (0, -1), (0, 256)):
            with self.assertRaises(ValueError):
                alpha.render_table_for_call(mode, opacity)

    def test_coverage_replacement_does_not_imply_invisibility(self):
        opaque = alpha.alpha_state((0xEF19AC3F, 0x04D12078))
        self.assertTrue(opaque['zero_combiner_alpha_replaced_by_coverage'])
        self.assertTrue(opaque['depth_write'])
        self.assertFalse(opaque['force_blend'])
        self.assertFalse(alpha.alpha_state((0xEF19AC3F, 0x04D13078))[
            'zero_combiner_alpha_replaced_by_coverage'])
        translucent = alpha.alpha_state((0xEF19AC3F, 0x04D049D8))
        self.assertFalse(translucent['zero_combiner_alpha_replaced_by_coverage'])
        self.assertTrue(translucent['force_blend'])

    def test_palette_modes_preserve_actual_alpha_and_offsets(self):
        for mode, size in ((1, 512), (2, 32)):
            binding = SimpleNamespace(flat_index=9, mode=mode)
            run = SimpleNamespace(palette=binding)
            payload = b'\xff' * 64 + b'\x12\x34' * (size // 2)
            evidence = alpha.palette_evidence(run, {9: payload})
            self.assertEqual(64, evidence['palette_offset'])
            self.assertEqual(size // 2, evidence['zero_alpha_entries'])
            changed = payload[:-1] + b'\x35'
            other = alpha.palette_evidence(run, {9: changed})
            self.assertEqual(size // 2 - 1, other['zero_alpha_entries'])
            self.assertNotEqual(evidence['palette_sha256'], other['palette_sha256'])

    def test_short_or_missing_palette_is_not_padded(self):
        run = SimpleNamespace(palette=SimpleNamespace(flat_index=9, mode=2))
        with self.assertRaisesRegex(ValueError, 'shorter'):
            alpha.palette_evidence(run, {9: bytes(31)})
        with self.assertRaises(KeyError):
            alpha.palette_evidence(run, {})
        self.assertIsNone(alpha.palette_evidence(SimpleNamespace(palette=None), {}))

    def test_changed_renderer_cannot_supply_conditional_evidence(self):
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            alpha.parts.verify_consumers(bytes(0x40000), 0x15000000)


if __name__ == '__main__':
    unittest.main()
