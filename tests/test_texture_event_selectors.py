"""Event selectors require the complete constructor and unchanged actor handle."""
import hashlib
import unittest
from unittest.mock import patch

from scripts import texture_event_selectors as selectors


def fixture():
    rows = [dict(offset=0x656, end=0x65C, opcode=14,
                 operands=[dict(mode=0, value=-8), dict(mode=5, value=0)]),
            dict(offset=0x65C, end=0x662, opcode=14,
                 operands=[dict(mode=1, value=36), dict(mode=0, value=-8)])]
    create = dict(offset=0x652, dispatch='native', target=3, packet_complete=True,
                  syntactic_argument_count=1, literal_arguments=[0x2018],
                  packet_span=[0x64E, 0x656])
    calls = [create]
    for at, operation, axis, descriptor in ((0x672, 61, 1, 2), *selectors.CASES):
        calls.append(dict(offset=at, dispatch='native', target=6, packet_complete=True,
            syntactic_argument_count=4, packet_span=[at-16, at+4],
            arguments=[dict(mode=m, value=v) for m, v in
                       ((1, 36), (4, operation), (4, axis), (4, descriptor))]))
    return dict(instruction_count=370, entrypoints=[0x20], instructions=rows), calls


def run_fixture(program, calls):
    data = bytes(1944)
    with patch.object(selectors, 'PROGRAM_SHA256', hashlib.sha256(data).hexdigest()), \
            patch.object(selectors, 'BLOCK_SHA256', hashlib.sha256(data[0x64E:0x6B2]).hexdigest()), \
            patch.object(selectors.events, 'decode_program', return_value=program), \
            patch.object(selectors.events, 'call_packets', return_value=calls):
        return selectors.program_requests(data)


class EventSelectorTests(unittest.TestCase):
    def test_three_requests_preserve_constructor_and_actor_handle(self):
        program, calls = fixture()
        result = run_fixture(program, calls)
        self.assertEqual([(r['segment'], r['descriptor_index']) for r in result],
                         [(6, 8), (7, 10), (10, 2)])
        self.assertTrue(all(r['constructor'] == calls[0] for r in result))
        self.assertTrue(all(r['actor_handle'] == {'return_to_frame': -8, 'frame_to_state': 36}
                            for r in result))

    def test_source_and_extent_changes_fail_closed(self):
        data = bytes(1944)
        with patch.object(selectors, 'PROGRAM_SHA256', hashlib.sha256(data).hexdigest()):
            for offset in (0, 0x656, len(data)-1):
                changed = bytearray(data); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'program source changed'):
                    selectors.program_requests(changed)
            for changed in (data[:-2], data + bytes(2)):
                with self.assertRaisesRegex(ValueError, 'program source changed'):
                    selectors.program_requests(changed)

    def test_constructor_selector_target_completeness_and_arity_are_required(self):
        for key, value in (('dispatch', 'internal'), ('target', 6), ('packet_complete', False),
                           ('syntactic_argument_count', 2), ('literal_arguments', [0x2019]),
                           ('packet_span', [0x650, 0x656])):
            program, calls = fixture(); calls[0][key] = value
            with self.subTest(key=key), self.assertRaisesRegex(ValueError, 'actor constructor changed'):
                run_fixture(program, calls)

    def test_actor_handle_reassignment_or_wrong_storage_rejects(self):
        for row, operand, field, value in ((0, 0, 'value', -4), (0, 1, 'mode', 4),
                                          (1, 0, 'value', 40), (1, 1, 'value', -4)):
            program, calls = fixture()
            program['instructions'][row]['operands'][operand][field] = value
            with self.assertRaisesRegex(ValueError, 'handle assignment changed'):
                run_fixture(program, calls)

    def test_incoming_branch_or_entry_cannot_bypass_constructor(self):
        for entry in (True, False):
            program, calls = fixture()
            if entry:
                program['entrypoints'].append(0x662)
            else:
                program['instructions'].append(dict(offset=0x100, target=0x662))
            with self.assertRaisesRegex(ValueError, 'control flow changed'):
                run_fixture(program, calls)

    def test_every_selector_packet_and_preceding_flag_operation_are_checked(self):
        for index in range(1, 5):
            for argument in range(4):
                program, calls = fixture()
                calls[index]['arguments'][argument]['value'] += 1
                with self.subTest(packet=index, argument=argument), \
                        self.assertRaisesRegex(ValueError, 'native packet changed'):
                    run_fixture(program, calls)
            program, calls = fixture(); calls[index]['packet_complete'] = False
            with self.assertRaisesRegex(ValueError, 'native packet changed'):
                run_fixture(program, calls)

    def test_changed_reference_rom_rejects_before_source_lookup(self):
        with self.assertRaisesRegex(ValueError, 'reference ROM changed'):
            selectors.load(None, b'changed ROM', {})
