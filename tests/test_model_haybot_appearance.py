import copy
import json
from dataclasses import replace
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest.mock import patch
from scripts import model_haybot_appearance as h, model_assets as m, model_scene60_appearance as common


def fixture():
    e=h.contract();d=e['run16'];shared=d['load_history_shared'];loads=[]
    for i,(flat,mode,segment,offset,second) in enumerate(d['load_history']):
        pixel=i%2==0
        loads.append((m.ModelTextureBinding(shared['image_command'],flat,mode,segment,offset,False,
            (shared['pixel_load_first' if pixel else 'palette_load_first'],second)),tuple(shared['pixel_tile' if pixel else 'palette_tile'])))
    kwargs={key:value for key,value in d.items() if not key.startswith('load_history')}
    for key in ('pixel','palette'):
        kwargs[key]=m.ModelTextureBinding(**{**kwargs[key],'load_command':tuple(kwargs[key]['load_command'])})
    for key in ('render_tile','tile_bounds','texture_scale','combine_mode'):kwargs[key]=tuple(kwargs[key])
    kwargs['render_tiles']=tuple(tuple(row) for row in kwargs['render_tiles']);kwargs['detail_tile_bounds']=();kwargs['texture_loads']=tuple(loads)
    run=m.ModelMaterialRun(**kwargs)
    offsets=[0]*368+[offset for offset in e['source_triangle_offsets'] for _ in range(4)]
    return e,run,SimpleNamespace(material_runs=(None,)*16+(run,),face_command_offsets=tuple(offsets))


class HaybotAppearanceTests(unittest.TestCase):
    def test_complete_packet_run_contract(self):
        e,r,g=fixture();self.assertEqual(r,h.checked_run(g,e));h.guard_evidence(e)
        self.assertEqual(15,e['selector_evidence']['captured_selector'])
        self.assertEqual(5,e['selector_evidence']['captured_phase'])
        with patch.object(Path,'read_bytes',return_value=b'{}'),self.assertRaises(ValueError):h.contract()

    def test_context_bindings_and_submissions_are_fixed(self):
        mutations=[lambda e:e['context'].update(scene=24),lambda e:e['context'].update(args=[254,2147686152,1,0]),
            lambda e:e['context'].update(selected_parts=[0]),lambda e:e.update(tasks=[]),
            lambda e:e['tasks'][0]['submission'].update(triangle_count=1226),
            lambda e:e['selector_evidence'].update(captured_selector=0),lambda e:e['flat3823'].update(bytes=1888),
            lambda e:e['reconstruction'].update(schema='unverified')]
        for mutate in mutations:
            e=h.contract();mutate(e)
            with self.assertRaises(ValueError):h.guard_evidence(e)

    def test_mutated_run_and_geometry_rejected_together(self):
        e,r,g=fixture()
        for field,value in [('render_tiles',()),('texture_loads',()),('runtime_render_state_offset',112),('matrix_index',3),('texture_dimensions',(32,32)),('preview_coordinate_state',((1,2),))]:
            g.material_runs=(None,)*16+(replace(r,**{field:value}),)
            with self.assertRaises(ValueError):h.checked_run(g,e)

    def test_triangle_provenance_guard(self):
        e,r,g=fixture();g.face_command_offsets=(0,)*392
        with self.assertRaises(ValueError):h.checked_run(g,e)

    def test_flat3839_is_not_accepted(self):
        e,r,g=fixture()
        for data in (bytes(1888),bytes(2080),bytes(2081)):
            with self.assertRaises(ValueError):h.decode_image(g,data,e)

    def test_material_edit_preserves_all_source_fields(self):
        e,r,g=fixture();doc={'materials':[{'extras':{'materialRun':16},'pbrMetallicRoughness':{}}],
            **{field:[{'source':True}] for field in common.PRESERVED_DOCUMENT_FIELDS}}
        before=copy.deepcopy(doc);after=h.apply_document(doc,g,e)
        self.assertEqual(doc,before);common.guard_document_preservation(before,after,b'x',b'x')
        self.assertEqual(h.PRESET,after['extras']['capturedTexturePreset']['preset'])
        self.assertEqual(3823,after['materials'][0]['extras']['capturedTexturePreset']['flat'])
        self.assertNotIn('KHR_materials_unlit',after['materials'][0].get('extensions',{}))

    def test_pinned_clip_inventory_normal_and_bind(self):
        r=dict(animation_clip_count=15,animation_frame_count=291,incompatible_animation_clip_count=0)
        doc={'animations':[{'extras':dict(sourceBank=2,sourceEntry=75,sourcePair=i,sourceFrameCount=n)} for i,n in enumerate(h.FRAMES)]}
        h.guard_animations(r,doc);h.guard_animations(r,{},True)
        with self.assertRaises(ValueError):h.guard_animations(r,doc,True)
        doc['animations'][0]['extras']['sourceFrameCount']=14
        with self.assertRaises(ValueError):h.guard_animations(r,doc)
        r['animation_clip_count']=14
        with self.assertRaises(ValueError):h.guard_animations(r,{})

    def test_preserve_degenerate_requires_explicit_character_selection(self):
        for bank,selection in [(1,None),(9,frozenset({75}))]:
            with self.assertRaises(ValueError):m.extract_model_preview('us',None,Path('unused'),Path('unused'),False,bank,
                entry_filter=selection,preserve_zero_area_faces=True)

    def test_canonical_preset_and_pinned_contract(self):
        import hashlib
        self.assertEqual('haybot-captured-selector15', h.PRESET)
        self.assertEqual(common.ROOT/'config/model-haybot-captured-appearance.json', h.CONTRACT_PATH)
        self.assertEqual(h.CONTRACT_SHA256, hashlib.sha256(h.CONTRACT_PATH.read_bytes()).hexdigest())
        self.assertEqual(h.PRESET, h.contract()['preset'])
        h.guard_evidence(h.contract())

    def test_contract_remains_capture_scoped(self):
        evidence = h.contract()
        self.assertEqual('haybot-captured-appearance-v1', evidence['reconstruction']['schema'])
        self.assertEqual((15, 5), (evidence['selector_evidence']['captured_selector'], evidence['selector_evidence']['captured_phase']))
        self.assertIn('no phase cycle or playback timeline', evidence['selector_evidence']['scope'])

    def test_capture_provenance_qualifies_capture_and_matrix_evidence(self):
        e, _, geometry = fixture()
        document = {'materials':[{'extras':{'materialRun':16}, 'pbrMetallicRoughness':{}}],
                    **{field:[{'source':True}] for field in common.PRESERVED_DOCUMENT_FIELDS}}
        result = h.apply_document(document, geometry, e)
        preset = result['extras']['capturedTexturePreset']
        provenance = preset['capture_provenance']
        self.assertEqual('captured renderer evidence and authenticated US ROM', provenance['source'])
        self.assertEqual(h.CONTRACT_SHA256, provenance['contract_sha256'])
        self.assertEqual('254846215d32ece3913f2adcb8bef94909f1492fbc95b0d70e11d16f0c16615d', provenance['packet_sha256'])
        self.assertEqual('99e3b3f1b3eab6b7834718e7007ceff69a987147d2531e9513db7f6aac8ce382', provenance['capture_audit_sha256'])
        self.assertIs(False, provenance['capture_replayed_locally'])
        self.assertIs(False, preset['capture_replayed_locally'])
        self.assertIn('float32', provenance['matrix_evidence'])
        self.assertIn('signed 16.16', provenance['matrix_evidence'])
        self.assertIn('35 segment3', provenance['matrix_evidence'])
        self.assertIn('7.62939453125e-06', provenance['matrix_evidence'])
        self.assertIn('(0,0,0,1)', provenance['matrix_evidence'])
        self.assertNotIn('pending', provenance['matrix_evidence'])
        self.assertIn('Raw matrix byte immutability is not asserted', provenance['matrix_evidence'])
        self.assertIn('1226', preset['scope'])
        self.assertIn('45 joints', preset['scope'])
        self.assertIn('15 animation clips/291 frames', preset['scope'])
        self.assertIn('selector15/phase5 static', preset['scope'])
        self.assertNotIn('romConsumerTextureVariant', result['extras'])
        self.assertEqual('../textures/haybot-captured-selector15-flat3823.png', result['images'][0]['uri'])

    def test_pinned_contract_rejects_reserialization_and_changed_evidence(self):
        raw = h.CONTRACT_PATH.read_bytes()
        changed = json.loads(raw)
        changed['selector_evidence']['captured_selector'] = 16
        for data in (raw + b'\n', json.dumps(changed).encode()):
            with self.subTest(data=data[:40]):
                with patch.object(Path, 'read_bytes', return_value=data):
                    with self.assertRaisesRegex(ValueError, 'Haybot captured contract changed'):
                        h.contract()
