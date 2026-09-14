import struct
import unittest
from scripts.model_constructor_flow import analyze
from scripts.model_constructor_analysis import trace_calls

BASE = 0x15000000
DATA = 0x800A0000
JAL = 0x0C000000 | (0x1513264C >> 2 & 0x3FFFFFF)


def run(words, data=b'', **options):
    return analyze(struct.pack(f'>{len(words)}I', *words), BASE, data, DATA, **options)


class ConstructorFlowTests(unittest.TestCase):
    def test_delay_slot_updates_arguments_and_observes_link_register(self):
        result = run([0x27BDFFE0, JAL, 0x03E02025, 0x03E00008, 0])
        self.assertEqual(BASE + 12, result['calls']['0x15000004']['arguments']['a0']['value'])

    def test_stack_template_fields_resolve_at_submission(self):
        result = run([0x27BDFF00, 0x240839E9, 0xAFA80070, 0x2409000D,
                      0xA7A90076, JAL, 0x27A40020, 0x03E00008, 0])
        self.assertEqual({'flags': 0x39E9, 'selector': 13}, result['calls']['0x15000014']['template_fields'])

    def test_disagreeing_branch_paths_do_not_claim_constant(self):
        result = run([0x27BDFFE0, 0x10A00004, 0, 0x24040001,
                      0x10000002, 0, 0x24040002, JAL, 0, 0x03E00008, 0])
        self.assertNotIn('a0', result['calls']['0x1500001C']['arguments'])

    def test_likely_untaken_path_annuls_delay_slot(self):
        result = run([0x24040007, 0x54000002, 0x24040008, JAL, 0, 0x03E00008, 0])
        self.assertEqual(7, result['calls']['0x1500000C']['arguments']['a0']['value'])

    def test_constant_table_read_and_array_are_initial_rom_evidence(self):
        data = struct.pack('>3I', 10, 20, 30)
        result = run([0x3C08800A, 0x8D040004, 0x3C05800A, 0x24070003,
                      JAL, 0, 0x03E00008, 0], data)
        call = result['calls']['0x15000010']
        self.assertEqual(20, call['arguments']['a0']['value'])
        self.assertEqual([10, 20, 30], call['initial_array_words'])
        self.assertEqual(4, result['initial_rom_loads'][0]['width'])

    def test_calls_kill_volatile_values_and_stack_memory(self):
        result = run([0x27BDFF00, 0x2408000D, 0xA7A80056, 0x24040007,
                      JAL, 0, JAL, 0x27A40000, 0x03E00008, 0])
        self.assertEqual({}, result['calls']['0x15000018']['template_fields'])

    def test_unsupported_control_flow_and_budget_discard_claims(self):
        for words, options in (([JAL, 0, 0x01000008, 0], {}),
                               ([JAL, 0, 0x08000000 | (BASE >> 2 & 0x3FFFFFF), 0], {'max_steps': 1})):
            result = run(words, **options)
            self.assertEqual('incomplete', result['status'])
            self.assertEqual({}, result['calls'])

    def test_observed_table_writes_do_not_reuse_initial_values(self):
        result = run([0x3C08800A, 0xAD000000, 0x8D040000, JAL, 0], struct.pack('>I', 13))
        self.assertEqual({}, result['calls'])
        self.assertIn('ROM data write needs mutation analysis', result['barriers'])

    def test_traced_selector_is_a_review_candidate_never_admitted(self):
        words = [0x27BDFF00, 0x2409000D, 0xA7A90056, JAL, 0x27A40000, 0x03E00008, 0]
        lookup = [0] * 233; lookup[13] = 213
        rows, _ = trace_calls(struct.pack('>7I', *words), BASE, b'', DATA, lookup)
        self.assertEqual([213], rows[0]['review_candidate_entries'])
        self.assertEqual('requires-consumer-review', rows[0]['status'])
        self.assertNotIn('model', rows[0])
