import hashlib
import unittest
from unittest.mock import patch
from scripts import model_event_activation as e


def semantic_fixture():
    def row(at,op,args=(),end=None,**extra):
        return dict(offset=at,end=at+4 if end is None else end,opcode=op,
            operands=[dict(mode=m,value=v) for m,v in args],**extra)
    rows=[row(0x138,27),row(0x144,25,[(3,0x430)]),row(0x430,27),row(0x434,15,target=0xC50)]
    calls=[]
    for i,(phase,region,query,create,selector) in enumerate(e.SCENE30_CASES):
        eq=0xC50+i*14;frame=-40-i*4
        rows.extend([row(eq,22,[(0,frame),(1,0x2C),(4,phase)],end=eq+8),
            row(eq+8,17,[(0,frame),(3,query-12)],target=query-12),
            row(query,25,[(6,5)]),row(query+4,14,[(0,frame),(5,0)],end=query+10),
            row(query+10,16,[(0,frame),(3,create+48)],end=create-4,target=create+48),
            row(create,25,[(6,3)])])
        for at,target,args,span in ((query,5,[0x2000,172,0x4000+region],[query-12,query+4]),(create,3,[0x2000+selector],[create-4,create+4])):
            calls.append(dict(offset=at,dispatch='native',target=target,packet_complete=True,
                syntactic_argument_count=len(args),literal_arguments=args,packet_span=span,packet_sha256='fixture'))
    return dict(instruction_count=709,instructions=rows),calls


def run_fixture(program,calls):
    data=bytes(3390)
    with patch.object(e,'SCENE30_PROGRAM_SHA256',hashlib.sha256(data).hexdigest()),patch.object(e,'decode_program',return_value=program),patch.object(e,'call_packets',return_value=calls):
        return e.scene30_program_requests(data)


class Scene30EventActivationTests(unittest.TestCase):
    def test_six_conditional_requests_keep_phase_region_selector(self):
        program,calls=semantic_fixture();_,_,requests=run_fixture(program,calls)
        self.assertEqual([2,3,5,10,11,12],[r['phase'] for r in requests])
        self.assertEqual(list(range(20,26)),[r['region'] for r in requests])
        self.assertEqual(list(range(6,12)),[r['selector'] for r in requests])
        self.assertTrue(all(r['model']==[1,66,0] for r in requests))
        self.assertTrue(all('nonzero' in r['condition'] for r in requests))
        self.assertTrue(all('appearance' not in r for r in requests))

    def test_source_program_and_extent_guard(self):
        for data in (bytes(3390),bytes(3388),bytes(3392)):
            with self.assertRaisesRegex(ValueError,'source changed'):e.scene30_program_requests(data)

    def test_packet_count_arity_literal_selector_and_query_rejected(self):
        for mutation in ('count','arity','literal','incomplete','query','target'):
            p,c=semantic_fixture()
            if mutation=='count':c.pop()
            elif mutation=='arity':c[1]['syntactic_argument_count']=2
            elif mutation=='literal':c[1]['literal_arguments']=[0x200C]
            elif mutation=='incomplete':c[1]['packet_complete']=False
            elif mutation=='query':c[0]['literal_arguments'][2]=0x401F
            else:c[1]['target']=6
            with self.assertRaises(ValueError):run_fixture(p,c)

    def test_phase_and_query_control_flow_guards(self):
        for mutation in ('phase','state','gate','return','target','controller'):
            p,c=semantic_fixture();rows={r['offset']:r for r in p['instructions']}
            if mutation=='phase':rows[0xC50]['operands'][2]['value']=4
            elif mutation=='state':rows[0xC50]['operands'][1]['value']=0x30
            elif mutation=='gate':rows[0x5D2]['opcode']=17
            elif mutation=='return':rows[0x5CC]['operands'][1]['mode']=0
            elif mutation=='target':rows[0x5D2]['target']=0x5DC
            else:rows[0x144]['operands'][0]['value']=0x438
            with self.assertRaises(ValueError):run_fixture(p,c)

    def test_spawn_source_hashes_fail_closed(self):
        for prefix,scene in ((bytes(240),bytes(1344)),(bytes(239),bytes(1344)),(bytes(240),bytes(1343))):
            with self.assertRaises(ValueError):e.scene30_spawn_records(prefix,scene)


    def test_existing_actor_and_membership_callees_are_pinned(self):
        required=((0x15083E90,288,'9056d859958dee82b4b70863bd102612d9a0b49c'),
                  (0x1505EEF4,220,'1103976ffa718b02f3bddfa0bf52f9bc6d953a34'),
                  (0x150A1DA0,1604,'9b34b9a88009fa729779740826f139eb017876a7'))
        for address,size,sha1 in required:
            self.assertIn((address,size,sha1),e.SCENE30_CODE_SPANS)
            source=bytes([0x55])*size
            spans=((address,size,hashlib.sha1(source).hexdigest()),)
            e.checked_spans(source,address,spans)
            for replacement in (bytes.fromhex('03E0000800000000')+source[8:],bytes([0x54])+source[1:]):
                with self.assertRaises(ValueError):e.checked_spans(replacement,address,spans)


import copy
import struct
from pathlib import Path
from dataclasses import replace


def instruction(op, *operands, wide=False):
    word = op | (0x40 if wide else 0)
    for i, (mode, value) in enumerate(operands):
        word |= mode << (13 - i * 3)
    data = struct.pack('>H', word)
    for mode, value in operands:
        long = wide and mode in (3, 4, 6)
        data += struct.pack('>i' if long else '>h', value)
        if long:
            wide = False
    return data


def source(*rows):
    body = b''.join(rows)
    header = [0x1000, 0, len(body) + 32, 16, 0, 0, 0, 32, 32, 32, 32, 0, 0, 0, 0, 0]
    return struct.pack('>16H', *header) + body


class EventDecoderTests(unittest.TestCase):
    def test_signed_halfwords_and_first_immediate_wide_operand(self):
        data = source(instruction(22, (0, -4), (1, 44), (4, 65537), wide=True),
                      instruction(26, (4, 0)))
        program = e.decode_program(data)
        args = program['instructions'][0]['operands']
        self.assertEqual([(0, -4, 2), (1, 44, 2), (4, 65537, 4)],
                         [(a['mode'], a['value'], a['encoded_bytes']) for a in args])
        self.assertEqual(42, program['instructions'][0]['end'])

    def test_reverse_push_order_and_native_packet_hash(self):
        data = source(instruction(24, (4, 1)), instruction(24, (4, 0x1008)),
                      instruction(25, (6, 6)), instruction(26, (4, 0)))
        call = e.call_packets(e.decode_program(data), data, 60)[0]
        self.assertEqual([0x1008, 1], call['literal_arguments'])
        self.assertTrue(call['packet_complete'])
        self.assertEqual([32, 44], call['packet_span'])
        self.assertEqual(hashlib.sha256(data[32:44]).hexdigest(), call['packet_sha256'])

    def test_header_opcode_mode_extent_and_branch_mutations_rejected(self):
        valid = source(instruction(26, (4, 0)))
        bad = []
        for offset, value in ((4, 34), (8, 2), (14, 33), (22, 1), (32, 0),
                              (32, 0xE018), (32, 0x001F), (32, 0x8018)):
            data = bytearray(valid)
            struct.pack_into('>H', data, offset, value)
            # A PUSH replacing return is syntactically valid but flows off end.
            bad.append(bytes(data))
        bad += [valid[:-1], source(instruction(15, (3, 33))),
                source(instruction(15, (0, -4))), source(instruction(25, (6, 14))),
                source(instruction(26, (0, 0), wide=True))]
        for data in bad:
            with self.subTest(data=data.hex()), self.assertRaises(ValueError):
                program = e.decode_program(data)
                e.call_packets(program, data, 60)

    def test_computed_argument_is_not_literal(self):
        data = source(instruction(24, (1, 8)), instruction(25, (6, 6)),
                      instruction(26, (4, 0)))
        call = e.call_packets(e.decode_program(data), data, 60)[0]
        self.assertIsNone(call['literal_arguments'])
        self.assertTrue(call['packet_complete'])

    def test_branch_entering_packet_and_nonadjacent_pushes_not_complete(self):
        data = source(instruction(16, (0, -4), (3, 42)),  # targets second push
                      instruction(24, (4, 1)), instruction(24, (4, 0x1008)),
                      instruction(25, (6, 6)), instruction(26, (4, 0)))
        call = e.call_packets(e.decode_program(data), data, 60)[0]
        self.assertEqual([1, 2], call['pending_argument_counts'])
        self.assertFalse(call['packet_complete'])
        data = source(instruction(24, (4, 1)), instruction(14, (0, -4), (4, 0)),
                      instruction(24, (4, 0x1008)), instruction(25, (6, 6)),
                      instruction(26, (4, 0)))
        call = e.call_packets(e.decode_program(data), data, 60)[0]
        self.assertEqual([2], call['pending_argument_counts'])
        self.assertEqual(1, call['syntactic_argument_count'])
        self.assertFalse(call['packet_complete'])

    def test_internal_call_reset_and_branch_target_validation(self):
        data = source(instruction(25, (3, 40)), instruction(26, (4, 0)),
                      instruction(27, (4, 0)), instruction(26, (4, 0)))
        program = e.decode_program(data)
        self.assertEqual('internal', program['instructions'][0]['dispatch'])
        self.assertTrue(e.call_packets(program, data, 30)[0]['packet_complete'])
        bad = bytearray(data)
        struct.pack_into('>h', bad, 34, 42)
        with self.assertRaisesRegex(ValueError, 'boundary'):
            e.decode_program(bad)

    def test_loop_with_unbounded_pushes_does_not_certify_packet(self):
        data = source(instruction(24, (4, 1)), instruction(16, (0, -4), (3, 32)),
                      instruction(25, (6, 6)), instruction(26, (4, 0)))
        call = e.call_packets(e.decode_program(data), data, 60)[0]
        self.assertFalse(call['packet_complete'])
        self.assertIn(-1, call['pending_argument_counts'])

    def test_scene_list_count_layout_and_padding_guards(self):
        data = bytearray(104)
        struct.pack_into('>4I', data, 0, 16, 76, 96, 0x80000002)
        data[34] = 1
        struct.pack_into('>H', data, 96, 144)
        self.assertEqual([144], e.scene_event_list(data)['event_ids'])
        for offset, value in ((34, 2), (94, 1), (98, 1), (12, 0), (11, 98)):
            bad = bytearray(data)
            bad[offset] = value
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                e.scene_event_list(bad)
        with self.assertRaises(ValueError):
            e.scene_event_list(data[:-1])

    def test_scene60_classifier_exact_packets_and_bounded_request_set(self):
        programs = []
        for event in (169, 170, 171, 172, 173):
            calls = [dict(offset=offset, dispatch='native', target=6,
                          literal_arguments=[0x1000 + script, 1], packet_complete=True,
                          syntactic_argument_count=2, packet_span=[offset - 8, offset + 4],
                          packet_sha256='fixture')
                     for eid, offset, script in e.SCENE60_REQUESTS if eid == event]
            programs.append(dict(asset_path=[20, event], calls=calls))
        self.assertEqual(8, len(e.scene60_script_requests(programs)))
        for field, value in (('target', 5), ('packet_complete', False),
                             ('literal_arguments', [0x1001, 1, 30]),
                             ('syntactic_argument_count', 3)):
            bad = copy.deepcopy(programs)
            bad[0]['calls'][0][field] = value
            with self.assertRaises(ValueError):
                e.scene60_script_requests(bad)
        with self.assertRaises(ValueError):
            e.scene60_script_requests(programs[1:])


class EventRomIntegrationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        path = e.models.ROOT / 'roms/baserom.us.z64'
        if not path.is_file():
            raise unittest.SkipTest('authorized reviewed US ROM is not available')
        cls.rom, _ = e.models.normalize_rom(path.read_bytes())
        if hashlib.sha1(cls.rom).hexdigest() != e.US_SHA1:
            raise unittest.SkipTest('local ROM is not the reviewed US input')
        cls.layout = e.models.load_layout('us')
        cls.game = e.models.parse_game_archive(cls.rom[cls.layout['game_start']:cls.layout['game_end']])

    def test_both_real_reports_and_scene30_identity(self):
        result = e.report(self.rom, self.layout, self.game, 30)
        requests = result['conditional_spawn_requests']
        self.assertEqual(709, result['programs'][0]['instruction_count'])
        self.assertEqual([6, 7, 8, 9, 10, 11], [r['spawn_record']['script_selector'] for r in requests])
        self.assertEqual([5, 6, 7, 8, 9, 10], [r['spawn_record']['record_index'] for r in requests])
        self.assertTrue(all(r['model'] == [1, 66, 0] for r in requests))
        self.assertFalse(result['conditional_script_requests'])
        result = e.report(self.rom, self.layout, self.game, 60)
        self.assertEqual([93, 455, 986, 251, 344], [p['instruction_count'] for p in result['programs']])
        requests = result['conditional_script_requests']
        matches = [(r['event_asset_path'][1], r['script_asset_path'][2],
                    [m['model'] for m in r['initial_model_matches']]) for r in requests]
        self.assertEqual([(170, n, [[1, 162, 0]]) for n in (8, 10, 11, 12)],
                         [r for r in matches if r[2]])
        self.assertFalse(result['conditional_spawn_requests'])

    def test_real_scene30_semantic_mutations_fail_after_repinning_test_input(self):
        banks = {b.index: b for b in e.models.parse_asset_banks(self.rom, self.layout['asset_table'])}
        _, source_data = e._asset(self.rom, banks[20], 144)
        # Override only the input hash in this test so the actual decoder and
        # semantic checks, rather than the outer identity guard, reject changes.
        for offset, value in ((0xC72, 4), (0x146, 0x438), (0x5D2, 0x0C11),
                              (0x5DE, 6), (0x5DA, 0x200C)):
            data = bytearray(source_data)
            struct.pack_into('>H', data, offset, value)
            with self.subTest(offset=hex(offset)), patch.object(
                    e, 'SCENE30_PROGRAM_SHA256', hashlib.sha256(data).hexdigest()):
                with self.assertRaises(ValueError):
                    e.scene30_program_requests(bytes(data))

    def test_code_tables_and_rom_mutations_fail_closed(self):
        for field, spans, base in (('code', e.CODE_SPANS + e.SCENE30_CODE_SPANS, self.layout['game_vram']),
                                    ('data', e.DATA_SPANS + e.SCENE30_DATA_SPANS, self.layout['game_data_vram'])):
            for address, length, digest in spans:
                payload = bytearray(getattr(self.game, field))
                payload[address - base] ^= 1
                with self.subTest(field=field, address=hex(address)), self.assertRaises(ValueError):
                    e.report(self.rom, self.layout, replace(self.game, **{field: bytes(payload)}), 30)
        bad = bytearray(self.rom)
        bad[0x13176A8] ^= 1
        with self.assertRaisesRegex(ValueError, 'reviewed normalized US ROM'):
            e.report(bytes(bad), self.layout, self.game, 30)
        with self.assertRaisesRegex(ValueError, 'bounded'):
            e.report(self.rom, self.layout, self.game, 31)
