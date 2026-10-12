import copy
import unittest
from test_audio_assets import sound_bank_graph_fixture
from scripts import sound_bank_codec as codec

class SoundBankCodecTests(unittest.TestCase):
    def setUp(self):
        control,self.external,self.wave=sound_bank_graph_fixture()
        self.control=control[:56]
        self.parts=codec.typed_regions(self.control,self.external,self.wave)

    def test_complete_typed_control_and_external_graph_rebuild_exactly(self):
        self.assertEqual(codec.encode_region(self.parts['control'][0]),self.control)
        self.assertEqual(codec.encode_region(self.parts['external'][0]),self.external)
        self.assertEqual(self.parts['external_unknown_ranges'],[])
        kinds={row['kind'] for part in self.parts['control']+self.parts['external'] for row in part['records']}
        self.assertEqual(kinds,{'bank_file','bank','instrument','sound','envelope','key_map','adpcm_wave','book','adpcm_loop','zero_gap'})

    def test_nonzero_unknown_gap_is_excluded_from_both_candidates(self):
        raw=bytearray(self.external);raw[0x26:0x28]=b'XY'
        parts=codec.typed_regions(self.control,bytes(raw),self.wave)
        self.assertEqual(parts['external_unknown_ranges'],[(0x26,0x28)])
        self.assertEqual([(p['start'],p['end']) for p in parts['external']],[(0,0x26),(0x28,len(raw))])
        for p in parts['external']:
            self.assertEqual(codec.encode_region(p),raw[p['start']:p['end']])

    def test_native_field_edits_change_bytes(self):
        fields={'bank':'sample_rate','instrument':'volume','sound':'volume','envelope':'attack_time_us',
                'key_map':'detune','adpcm_wave':'conker_field_0x14','adpcm_loop':'end_sample'}
        for part in self.parts['control']+self.parts['external']:
            for index,row in enumerate(part['records']):
                kind=row['kind']
                if kind not in fields and kind!='book':continue
                changed=copy.deepcopy(part)
                if kind=='book':changed['records'][index]['coefficients'][0]-=1
                else:changed['records'][index][fields[kind]]+=1
                with self.subTest(kind=kind):
                    self.assertNotEqual(codec.encode_region(changed),codec.encode_region(part))

    def test_arrays_zero_gaps_and_schema_cannot_hide_opaque_bytes(self):
        for part in self.parts['control']+self.parts['external']:
            for row in part['records']:
                changed=dict(row,opaque_bytes='00')
                with self.assertRaises(ValueError):codec.encode_record(changed)
                if row['kind'] in codec.ARRAYS:
                    changed=copy.deepcopy(row);changed[codec.ARRAYS[row['kind']][0]].pop()
                    with self.assertRaises(ValueError):codec.encode_record(changed)
                if 'reserved_zero' in row:
                    with self.assertRaises(ValueError):codec.encode_record(dict(row,reserved_zero=1))
                for field,value in row.items():
                    if type(value) is int and field not in ('offset','revision'):
                        with self.subTest(kind=row['kind'],field=field),self.assertRaises(ValueError):
                            codec.encode_record(dict(row,**{field:True}))
        for size in (0,1,3,16):
            with self.assertRaises(ValueError):codec.encode_record({'kind':'zero_gap','offset':0,'size':size})
        with self.assertRaises(ValueError):codec.encode_record({'kind':[],'offset':0})

    def test_region_overlap_and_missing_records_fail(self):
        region=self.parts['external'][0]
        for change in ('overlap','missing','extent'):
            changed=copy.deepcopy(region)
            if change=='overlap':changed['records'][1]['offset']-=1
            elif change=='missing':changed['records'].pop(1)
            else:changed['end']+=1
            with self.subTest(change=change),self.assertRaises(ValueError):codec.encode_region(changed)

    def test_unexplained_control_tail_and_changed_native_reserved_bytes_fail(self):
        with self.assertRaisesRegex(ValueError,'suffix'):
            codec.typed_regions(self.control+bytes(8),self.external,self.wave)
        raw=bytearray(self.external);raw[0x1f]=1
        with self.assertRaisesRegex(ValueError,'reserved'):
            codec.typed_regions(self.control,bytes(raw),self.wave)

    def test_consumer_proof_requires_complete_matched_spans(self):
        with self.assertRaisesRegex(ValueError,'consumer changed'):
            codec.verify_consumers(b'')
