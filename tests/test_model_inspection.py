from __future__ import annotations

import base64
import copy
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from scripts import model_inspection as inspection


PNG = base64.b64decode('iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mP8/x8AAwMCAO+jRZkAAAAASUVORK5CYII=')


class ModelInspectionTests(unittest.TestCase):
    def fixture(self, root):
        source = root / 'model.gltf'
        data = struct.pack('<3f3H', 1.25, -2.5, 3.75, 0, 1, 2)
        (root / 'model.bin').write_bytes(data)
        (root / 'eye.png').write_bytes(PNG)
        doc = {'asset': {'version': '2.0'}, 'buffers': [{'uri': 'model.bin', 'byteLength': len(data)}],
               'bufferViews': [{'buffer': 0, 'byteLength': 12}, {'buffer': 0, 'byteOffset': 12, 'byteLength': 6}],
               'images': [{'uri': 'eye.png', 'name': 'eye'}], 'textures': [{'source': 0}],
               'materials': [{'pbrMetallicRoughness': {'baseColorTexture': {'index': 0}},
                              'extensions': {'KHR_materials_unlit': {}}}],
               'extensionsUsed': ['KHR_materials_unlit'], 'nodes': [{'name': 'joint', 'translation': [1, 2, 3]}],
               'skins': [{'joints': [0]}], 'animations': [{'name': 'retained-action'}]}
        source.write_text(json.dumps(doc))
        return source, doc, data

    def test_pack_embeds_exact_buffer_and_images_without_changing_rig_or_materials(self):
        with tempfile.TemporaryDirectory() as tmp:
            source, doc, original = self.fixture(Path(tmp))
            source_bytes = source.read_bytes()
            glb, evidence = inspection.pack_glb(source)
            packed, binary = inspection.read_glb(glb)
            self.assertEqual(original, binary[:len(original)])
            self.assertNotIn('uri', packed['buffers'][0])
            self.assertNotIn('uri', packed['images'][0])
            view = packed['bufferViews'][packed['images'][0]['bufferView']]
            self.assertEqual(0, view['byteOffset'] % 4)
            self.assertEqual(PNG, binary[view['byteOffset']:view['byteOffset'] + view['byteLength']])
            for key in ('nodes', 'skins', 'animations', 'materials', 'textures'):
                self.assertEqual(doc[key], packed[key])
            self.assertEqual(source_bytes, source.read_bytes())
            self.assertEqual(1, evidence['animation_count'])
            self.assertEqual(glb, inspection.pack_glb(source)[0])

    def test_pack_rejects_missing_data_bad_lengths_and_remote_resources(self):
        with tempfile.TemporaryDirectory() as tmp:
            source, original, _ = self.fixture(Path(tmp))
            for change in ('length', 'missing', 'remote'):
                doc = copy.deepcopy(original)
                if change == 'length':
                    doc['buffers'][0]['byteLength'] += 1
                else:
                    doc['images'][0]['uri'] = 'missing.png' if change == 'missing' else 'https://example.com/image.png'
                source.write_text(json.dumps(doc))
                with self.assertRaises((ValueError, FileNotFoundError)):
                    inspection.pack_glb(source)

    def test_publisher_rejects_stale_source_before_overwriting_inspection_files(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source, _, _ = self.fixture(root)
            fingerprint = inspection.preview_fingerprint(source)
            (root / 'preview.png').write_bytes(PNG)
            report = {'status': 'incomplete', 'summary': {'completed': True},
                      'files': [{'path': str(source), 'input_fingerprint': fingerprint,
                                 'checks': {'gltf': {'status': 'passed'}, 'blender': {'status': 'passed'}}}],
                      'renders': [{'id': 'test', 'source': str(source), 'image': str(root / 'preview.png'),
                                   'check': {'current_sha256': inspection.digest(PNG)}}]}
            (root / 'report.json').write_text(json.dumps(report))
            config = {'validation_report': 'report.json', 'previews': 'previews',
                      'models': [{'name': 'conker-test', 'label': 'Conker', 'note': 'Fixture',
                                  'category': 'characters', 'render_case': 'test'}]}
            (root / 'config.json').write_text(json.dumps(config))
            with mock.patch.object(inspection, 'ROOT', root):
                manifest = inspection.publish_inspection(root / 'config.json', root / 'inspect')
                output = root / 'inspect/conker-test.glb'
                before = output.read_bytes()
                self.assertEqual('ready-for-inspection', manifest['models'][0]['status'])
                # Renaming and regrouping cannot alter the model or preview bytes.
                config['models'][0].update(label='Conker renamed', category='scene-items', aliases=['Conker'])
                (root / 'config.json').write_text(json.dumps(config))
                renamed = inspection.publish_inspection(root / 'config.json', root / 'inspect')
                self.assertEqual('scene-items', renamed['models'][0]['category'])
                self.assertEqual(before, output.read_bytes())
                self.assertEqual(PNG, (root / 'previews/conker-test.png').read_bytes())
                (root / 'model.bin').write_bytes(b'bad input')
                with self.assertRaisesRegex(ValueError, 'stale or unvalidated'):
                    inspection.publish_inspection(root / 'config.json', root / 'inspect')
                self.assertEqual(before, output.read_bytes())

    def test_gallery_metadata_rejects_uncategorized_models_and_unsafe_references(self):
        model = {'name': 'test', 'category': 'characters', 'aliases': ['old name']}
        inspection.validate_gallery_metadata([model])
        for bad in ({'category': 'character-bank'}, {'category': None}, {'aliases': 'name'},
                    {'identification': {'basis': 'visual-reference', 'reference_label': 'Wiki',
                                        'reference_url': 'javascript:alert(1)'}}):
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                inspection.validate_gallery_metadata([{**model, **bad}])

    def test_gallery_escapes_names_aliases_and_reference_labels(self):
        record = {'label': 'Test <model>', 'file': 'test.glb', 'category': 'characters',
                  'preview': 'preview.png', 'note': '<b>Note</b>', 'aliases': ['" onclick="bad()'],
                  'preview_sha256': inspection.digest(PNG), 'glb_sha256': inspection.digest(b'glb'),
                  'identification': {'basis': 'visual-reference', 'reference_label': '<Wiki>',
                                     'reference_url': 'https://example.com/?a=1&b=2'}}
        page = inspection.gallery_page([record], inspection.ROOT / 'inspect')
        self.assertIn('Test &lt;model&gt;', page)
        self.assertIn('&quot; onclick=&quot;bad()', page)
        self.assertIn('&lt;Wiki&gt;', page)
        self.assertNotIn('<b>Note</b>', page)
        self.assertNotIn('{{CARDS}}', page)

    def test_rom_source_gate_checks_selected_model_in_mixed_corpus(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            geometry = root / 'geometry'
            geometry.mkdir()
            source, document, _ = self.fixture(geometry)
            row = {'bank_entry': 173, 'segment': 0, 'gltf_file': 'geometry/model.gltf',
                   'material_runs': [{'runtime_material': None}]}
            manifest = {'profile': 'us', 'bank_index': 9,
                        'family': 'indexed-bank-09-model-preview', 'models': [row,
                        {'gltf_file': 'geometry/other.gltf', 'material_runs': [{'runtime_material': {'observed': True}}]}]}
            path = root / 'manifest.json'
            path.write_text(json.dumps(manifest))
            self.assertEqual([], inspection.rom_source_evidence(source)['capture_inputs'])
            row['material_runs'][0]['runtime_material'] = {'observed': True}
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(ValueError, 'captured runtime materials'):
                inspection.rom_source_evidence(source)
            row['material_runs'][0]['runtime_material'] = None
            path.write_text(json.dumps(manifest))
            document['materials'][0]['extras'] = {'runtimeMaterial': {}}
            source.write_text(json.dumps(document))
            with self.assertRaisesRegex(ValueError, 'captured runtime material evidence'):
                inspection.rom_source_evidence(source)

    def test_rom_source_gate_rejects_captured_compositions_and_nondefault_characters(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            geometry = root / 'geometry'
            geometry.mkdir()
            source, _, _ = self.fixture(geometry)
            for bank, family, message in [(1, 'indexed-bank-01-model-preview', 'ROM-default corpus'),
                                          (1, 'submitted-character-poses', 'captured composition')]:
                (root / 'manifest.json').write_text(json.dumps({'profile': 'us', 'bank_index': bank,
                                                                'family': family, 'models': []}))
                with self.assertRaisesRegex(ValueError, message):
                    inspection.rom_source_evidence(source)
