import copy
import hashlib
import struct
import unittest
from unittest import mock

try:
    from scripts import model_expression_constructors as expressions
except ImportError:
    import model_expression_constructors as expressions


class ExpressionConstructors(unittest.TestCase):
    def fixture(self):
        base = 0x80086CC4
        data = bytearray(0x8009D915 - base)
        def put(address, raw):
            data[address-base:address-base+len(raw)] = raw
        put(0x8009D910, bytes((5, 6, 7, 10, 11)))
        put(0x8009B8A0, struct.pack('>I', 0x3A83126F))
        put(0x80096F48, struct.pack('>I', 0x15031C00))
        for action, address, entries in (
            (5, 0x8009CE50, ((132, 6, 2, 1),)),
            (6, 0x8009CE60, ((15, 0, 1, 0),)),
            (7, 0x8009CE70, ((16, 0, 1, 0),)),
            (10, 0x8009CEB0, ((18, 0, 1, 0),)),
            (11, 0x8009CED0, ((132, 6, 2, 1), (18, 0, 1, 0))),
        ):
            put(0x80086CC4+(action-1)*8, struct.pack('>IB3x', address, len(entries)))
            for i, (model, updater, kind, animation) in enumerate(entries):
                put(address+i*16, bytes((model, 12, updater, kind, 0, 0, animation, 0))+bytes(8))
        code = b'fixture-expression-consumer'
        spans = ((0x1000, len(code), hashlib.sha1(code).hexdigest()),)
        return code, base, data, spans

    def parse(self, code, base, data, spans):
        with mock.patch.object(expressions, 'CONSUMERS', spans):
            return expressions.parse_expression_constructor_programs(code, 0x1000, data, base)

    def test_program_order_and_record_identity(self):
        code, base, data, spans = self.fixture()
        report = self.parse(code, base, data, spans)
        self.assertEqual([5, 6, 7, 10, 11], [p['native_action'] for p in report['programs']])
        self.assertEqual([[132], [15], [16], [18], [132, 18]],
                         [[r['entry'] for r in p['operations']] for p in report['programs']])
        self.assertEqual([15, 16, 18, 132], report['attachment_entries'])
        self.assertEqual(6, report['operation_count'])
        for p in report['programs']:
            self.assertEqual(p['record_count']*16, p['decoded_size'])
            for index, row in enumerate(p['operations']):
                self.assertEqual(int(p['program_address'], 16)+index*16,
                                 int(row['record_address'], 16))
                self.assertEqual(p['native_action'], row['descriptor_initial_fields']['u8_0x06'])
                self.assertEqual('attachment-constructor', row['operation'])

    def test_constructor_reads_and_signed_loader_selector(self):
        code, base, data, spans = self.fixture()
        report = self.parse(code, base, data, spans)
        for p in report['programs']:
            for row in p['operations']:
                fields = row['descriptor_initial_fields']
                self.assertEqual(row['entry'], fields['u8_0x01'])
                self.assertEqual(12, fields['u8_0x02'])
                self.assertEqual(0xFFFF, fields['u16_0x1C'])
                self.assertEqual(0, fields['u16_0x18'])
                self.assertEqual(0, fields['u16_0x1A'])
                animated = row['entry'] == 132
                self.assertEqual(1 if animated else -1, row['attachment_animation_selector'])
                self.assertEqual(6 if animated else 0, row['updater_selector'])
                self.assertEqual('func_1503F62C' if animated else 'func_1502FE10', row['loader'])
                self.assertFalse(row['creation_conditions']['duplicate_bypass_flag'])
                self.assertEqual('ignored-by-attachment-constructor-branch',
                                 row['expression_action_parameter_usage'])

    def test_big_endian_record_fields_are_unsigned_storage(self):
        raw = bytes((15, 12, 0, 1, 7, 8, 99, 0, 0xAB, 0xCD, 0x12, 0x34, 0xFE, 0xDC, 0xAA, 0xBB))
        row = expressions._decode_record(raw, 6, 0, 0x1000)
        f = row['descriptor_initial_fields']
        self.assertEqual((0xABCD, 0x1234, 0xFEDC, 0xAA, 0xBB),
                         (f['u16_0x0A'], f['u16_0x0C'], f['u16_0x0E'], f['u16_0x1E'], f['u16_0x20']))
        self.assertEqual(-1, f['s8_0x17'])
        self.assertEqual([6], row['record_offsets_ignored_by_dispatch'])

    def test_action_parameter_is_not_lifetime_or_clip(self):
        code, base, data, spans = self.fixture()
        p = self.parse(code, base, data, spans)['action_parameter']
        self.assertEqual(6, p['expression_offset'])
        self.assertAlmostEqual(0.001, p['scale_f32'])
        self.assertEqual('ignored', p['attachment_constructor_usage'])

    def test_every_pinned_source_byte_is_guarded(self):
        code, base, data, spans = self.fixture()
        for address, size, _ in expressions.SOURCE_SPANS:
            for i in range(size):
                changed = data.copy()
                changed[address-base+i] ^= 1
                with self.subTest(address=hex(address+i)):
                    with self.assertRaisesRegex(ValueError, 'source changed'):
                        self.parse(code, base, changed, spans)

    def test_consumer_and_bounds_fail_closed(self):
        code, base, data, spans = self.fixture()
        for i in range(len(code)):
            changed = bytearray(code)
            changed[i] ^= 1
            with self.assertRaisesRegex(ValueError, 'consumer changed'):
                self.parse(changed, base, data, spans)
        for new_code, new_base, new_data in ((code[:-1], base, data),
                                            (code, base+1, data),
                                            (code, base, data[:-1])):
            with self.assertRaises(ValueError):
                self.parse(new_code, new_base, new_data, spans)

    def test_parent_modification_unknown_kind_and_truncation_are_rejected(self):
        for kind in (0, 3, 255):
            with self.assertRaisesRegex(ValueError, 'not a reviewed attachment'):
                expressions._decode_record(bytes((15, 0, 0, kind))+bytes(12), 6, 0, 0)
        for size in (0, 15, 17):
            with self.assertRaises(ValueError):
                expressions._decode_record(bytes(size), 6, 0, 0)
        with self.assertRaisesRegex(ValueError, 'outside the reviewed range'):
            expressions._decode_record(bytes((132, 12, 6, 2, 0, 0, 255, 0))+bytes(8), 5, 0, 0)

    def test_exported_manifest_exposes_actions_and_constructor_proof(self):
        from scripts import model_assets as models
        code, base, data, spans = self.fixture()
        constructors = self.parse(code, base, data, spans)
        preset = {'index': 0, 'animation_selector': 5, 'animation_duration_raw': 1000,
                  'native_action': 11}
        source = {'entries': {0: {'sha1': 'source', 'header_sha1': 'header',
                  'expression_offset': 16, 'expression_size': 10,
                  'expression_presets': [preset]}}, 'expression_consumers': {},
                  'expression_animation_programs': [{'native_action': 11}],
                  'expression_constructors': constructors}
        before = copy.deepcopy(source)
        with mock.patch.object(models, 'load_character_defaults', return_value=source) as load:
            report = models.load_character_expression_manifest('us', None, 'digest')
        load.assert_called_once_with('us', None, 'digest', include_expressions=True)
        self.assertEqual(before, source)
        self.assertEqual(constructors, report['attachment_constructors'])
        self.assertEqual(report['action_programs'], report['animation_programs'])
        actual = report['models'][0]['presets'][0]
        self.assertEqual(5, actual['action_selector'])
        self.assertEqual(1000, actual['action_parameter_raw'])
        self.assertEqual('action_parameter_raw', report['legacy_field_names']['animation_duration_raw'])
        self.assertIn('ignored', report['scope'])

    def test_metadata_decode_is_read_only_and_reproducible(self):
        code, base, data, spans = self.fixture()
        before = bytes(data)
        first = self.parse(code, base, data, spans)
        original = copy.deepcopy(first)
        first['programs'][0]['operations'][0]['descriptor_initial_fields']['u8_0x01'] = 0
        self.assertEqual(original, self.parse(code, base, data, spans))
        self.assertEqual(before, data)


if __name__ == '__main__':
    unittest.main()
