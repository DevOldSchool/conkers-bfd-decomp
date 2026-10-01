"""Captured appearance contract, full-run history and scope mutation tests; no ROM."""
import copy
from dataclasses import replace
import hashlib
import json
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import patch
from scripts import model_assets as models, model_scene60_appearance as scene
from scripts import model_library_bat155_appearance as library


def tuples(value):
    return tuple(tuples(item) for item in value) if isinstance(value, list) else value


def material(value):
    fields = {key: tuples(item) for key, item in value.items()}
    def binding(item):
        return models.ModelTextureBinding(**{key: tuples(value) for key, value in item.items()}) if item is not None else None
    fields['pixel'], fields['palette'] = binding(value['pixel']), binding(value['palette'])
    fields['texture_loads'] = tuple((binding(image), tuples(tile)) for image, tile in value['texture_loads'])
    return models.ModelMaterialRun(**fields)


def fixture(index):
    evidence = library.contract()
    run = material(evidence['material_contracts'][str(index)])
    rows = evidence['models']['155']['runs']
    count = max(row[0] for row in rows) + 1
    runs = [run] * count
    offsets = [0] * evidence['models']['155']['selected_primary_faces']
    for row in rows:
        i, first, faces, _, _, start, end = row
        runs[i] = material(evidence['material_contracts'][str(i)])
        offsets[first], offsets[first + faces - 1] = start, end
    return evidence, run, SimpleNamespace(material_runs=tuple(runs), face_command_offsets=tuple(offsets))


class Library155AppearanceTests(unittest.TestCase):
    def test_canonical_contract_preserves_exact_scope(self):
        evidence = library.contract()
        library.guard(evidence)
        self.assertEqual('library-bat155-captured-primary-opacity255', library.PRESET)
        self.assertEqual('model-library-bat155-captured-appearance.json', library.CONTRACT_PATH.name)
        self.assertEqual(library.CONTRACT_SHA256, hashlib.sha256(library.CONTRACT_PATH.read_bytes()).hexdigest())
        self.assertEqual({'155'}, set(evidence['models']))
        self.assertEqual(186, sum(row[2] for row in evidence['models']['155']['runs']))
        self.assertEqual([12,25], [task['events'][-1] for task in evidence['task']['submissions']])
        self.assertEqual([314,314], [task['triangles'] for task in evidence['task']['submissions']])

    def test_full_run_contracts_reproduce_hashes_and_checked_coverage(self):
        for index in (0,1,3,5,6,8,11,13,14,18,20):
            evidence, run, geometry = fixture(index)
            self.assertEqual(evidence['local_source_guards']['material_run_sha256']['155'][str(index)], scene.run_digest(run))
            flat, _ = scene.checked_run(run,index,geometry,155,evidence)
            self.assertEqual(run.pixel.flat_index,flat)
        self.assertEqual(202,sum(len(item['texture_loads']) for item in evidence['material_contracts'].values()))
        self.assertEqual(66,sum(len(item['render_tiles']) for item in evidence['material_contracts'].values()))

    def test_flat926_uses_library_offset64_and_recorded_B_state(self):
        evidence, run, geometry = fixture(13)
        self.assertEqual(64,run.runtime_render_state_offset)
        self.assertEqual(926,scene.checked_run(run,13,geometry,155,evidence)[0])
        self.assertEqual('B',evidence['source_contracts']['926']['captured_state'])
        self.assertEqual('04D12078',evidence['captured_states']['B']['other_mode'][1])
        changed=replace(run,runtime_render_state_offset=112)
        geometry.material_runs=geometry.material_runs[:13]+(changed,)+geometry.material_runs[14:]
        with self.assertRaisesRegex(ValueError,'canonical source material state'):
            scene.checked_run(changed,13,geometry,155,evidence)

    def test_source_history_mutations_rejected_even_when_geometry_agrees(self):
        fields = {'texture_loads':((None,None),),'render_tiles':((0,1,2),),
                  'texture_dimensions':(1,1),'detail_tile_bounds':((0,1,2),),
                  'preview_coordinate_state':((1,2),(3,4),(5,6))}
        for field, value in fields.items():
            evidence, run, geometry = fixture(13)
            changed=replace(run,**{field:value})
            geometry.material_runs=geometry.material_runs[:13]+(changed,)+geometry.material_runs[14:]
            with self.subTest(field=field),self.assertRaisesRegex(ValueError,'canonical source material state'):
                scene.checked_run(changed,13,geometry,155,evidence)

    def test_flat903_closes_all_four_requested_mips(self):
        evidence, run, _ = fixture(0)
        scene.guard_flat903_mips(run)
        self.assertEqual([0,512,640,704],[level['source_byte_offset'] for level in evidence['textures']['903']['levels']])
        self.assertEqual(7,sum(len(info['levels']) for info in evidence['textures'].values()))
        self.assertEqual(5456,sum(level['width']*level['height'] for info in evidence['textures'].values() for level in info['levels']))
        for changed in (replace(run,render_tiles=tuple(tile for tile in run.render_tiles if tile[0]!=3)),
                        replace(run,texture_scale=(0xD7000002,0xFFFFFFFF)),
                        replace(run,pixel=replace(run.pixel,load_command=(0xF3000000,0)))):
            with self.assertRaises(ValueError):scene.guard_flat903_mips(changed)

    def test_context_submission_fog_and_pixel_mutations_rejected(self):
        mutations = {
            'opacity':lambda e:e['models']['155']['caller_arguments'].__setitem__(0,254),
            'mode':lambda e:e['models']['155']['selected_part'].update(draw_mode=2),
            'secondary':lambda e:e['models']['155']['selected_part'].update(secondary_model=155),
            'model':lambda e:e['models']['155']['selected_part'].update(display_model=154),
            'missing_submission':lambda e:e['task']['submissions'].pop(),
            'execution_count':lambda e:e['task']['submissions'][0].update(execution_count=0),
            'triangle_count':lambda e:e['task']['submissions'][0].update(triangles=313),
            'fog_rgba':lambda e:e['task']['submissions'][1]['effective_fog'].update(rgba=[1,0,0,255]),
            'fog_origin':lambda e:e['task']['submissions'][1]['effective_fog'].update(origin=0),
            'fog_offset':lambda e:e['task']['submissions'][1]['effective_fog'].update(flattened_byte_offset=0),
            'mip_pixel':lambda e:e['textures']['903']['levels'][3].update(png_sha1='0'*40),
            'palette':lambda e:e['textures']['926'].update(palette_sha256='0'*64),
            'alpha_state':lambda e:e['captured_state_common'].update(cvg_times_alpha=True),
        }
        for name, mutate in mutations.items():
            evidence=library.contract();mutate(evidence)
            with self.subTest(mutation=name),self.assertRaisesRegex(ValueError,'evidence changed'):
                library.guard(evidence)

    def test_additive_fog_does_not_rewrite_recorded_material_state_hashes(self):
        evidence=library.contract();common=evidence['captured_state_common']
        self.assertEqual('6d27162ffa5036aa3ddee7609a127fc9753db90589b02670231bddb5710d6f91',evidence['captured_states']['B']['state_subset_sha256'])
        self.assertNotIn('fog',common['colours'])
        for state in evidence['captured_states'].values():
            numeric={'other_mode':[int(word,16) for word in state['other_mode']],
                     'combine_mode':[int(word,16) for word in state['combine_mode']],
                     'convert_mode':[int(word,16) for word in common['convert_mode']],
                     'colours':common['colours']}
            self.assertEqual(state['state_subset_sha256'],hashlib.sha256(json.dumps(numeric,sort_keys=True).encode()).hexdigest())

    def test_matrix_evidence_qualifies_float_to_fixed_conversion(self):
        evidence=library.contract()
        for task in evidence['task']['submissions']:
            matrix=task['matrix_evidence']
            self.assertEqual([],task['recorded_matrix_report'])
            self.assertEqual(35,matrix['matrix_count'])
            self.assertEqual(35,matrix['matrix_byte_blocks_changed'])
            self.assertEqual(420,matrix['affine_components_compared'])
            self.assertLessEqual(matrix['matrix_maximum_absolute_error'],1/65536)
            self.assertEqual('float-to-split-fixed-affine-components-agree-within-precision',matrix['matrix_status'])
            self.assertFalse(matrix['flattened_fog_offset_independently_recomputed'])
        evidence['task']['submissions'][0]['matrix_evidence']['matrix_byte_blocks_changed']=0
        with self.assertRaisesRegex(ValueError,'evidence changed'):
            library.guard(evidence)

    def test_zero_own_clips_is_not_runtime_animation_absence(self):
        self.assertFalse(library.contract()['models']['155']['runtime_animation_absence_proven'])
        record={'animation_clip_count':0,'animation_frame_count':0,'incompatible_animation_clip_count':0}
        for bind in (False,True):scene.guard_animation_inventory(155,record,{},bind=bind)
        with self.assertRaises(ValueError):scene.guard_animation_inventory(155,record,{'animations':[{}]})
        record['animation_frame_count']=1
        with self.assertRaises(ValueError):scene.guard_animation_inventory(155,record,{})

    def test_contract_byte_and_source_document_mutations_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            path=Path(temporary)/'changed.json';path.write_bytes(b'{}')
            with patch.object(library,'CONTRACT_PATH',path),self.assertRaisesRegex(ValueError,'contract changed'):
                library.contract()
        before={field:[{'source':True}] for field in scene.PRESERVED_DOCUMENT_FIELDS}
        for field in scene.PRESERVED_DOCUMENT_FIELDS:
            after=copy.deepcopy(before);after[field]=[]
            with self.subTest(field=field),self.assertRaises(ValueError):scene.guard_document_preservation(before,after,b'x',b'x')
        with self.assertRaises(ValueError):scene.guard_document_preservation(before,before,b'x',b'y')


if __name__=='__main__':unittest.main()
