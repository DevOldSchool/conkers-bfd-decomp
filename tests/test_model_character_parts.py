import copy
import json
import struct
import tempfile
import unittest
from dataclasses import replace
from pathlib import Path

from scripts import model_assets as models, model_character_parts as parts, model_validation


def fixture():
    vertices = b''.join(struct.pack('>hhhHhh4B', *p, 0, 0, 0, 255, 255, 255, 255)
                        for p in ((0, 0, 0), (8, 0, 0), (0, 8, 0)))
    commands = b''.join(struct.pack('>II', *c) for c in (
        (0xFCFFFFFF, 0xFFFCF279), (0xD7000000, 0), (0x01003006, 0x01000000), (0x05000204, 0), (0xDF000000, 0)))
    secondary = commands[:4] + struct.pack('>I', 1) + commands[8:]
    data = struct.pack('>10I', 88, len(commands) * 2, 0, 0, 0, 0, 0, 0, 0, 0x80000000) + vertices + commands + secondary
    geometry = models.parse_model_geometry(data, independent_display_lists=True)
    layout = {'display_list_pointer_tables': [
        {'name': 'primary', 'pointers': ['0x58']}, {'name': 'secondary', 'pointers': ['0x80']}]}
    return data, geometry, layout


class CharacterPartsTests(unittest.TestCase):
    def test_native_table_selection_preserves_source_and_material_indices(self):
        data, geometry, layout = fixture()
        selected, evidence = parts.primary_preview(data, geometry, layout)
        self.assertEqual(((0, 1, 2),), selected.faces)
        self.assertEqual((0,), selected.face_source_indices)
        self.assertEqual([1, 0], [r.face_count for r in selected.material_runs])
        self.assertEqual([0, 1], [r.first_face for r in selected.material_runs])
        self.assertEqual((geometry.face_command_offsets[0],), selected.face_command_offsets)
        self.assertEqual(1, evidence['excluded_secondary_face_count'])
        self.assertEqual(geometry.vertices, selected.vertices)
        self.assertEqual(2, len(geometry.faces))

    def test_no_secondary_table_leaves_geometry_unchanged(self):
        data, geometry, layout = fixture()
        layout['display_list_pointer_tables'][1]['pointers'] = []
        self.assertEqual((geometry, None), parts.primary_preview(data, geometry, layout))

    def test_invalid_list_provenance_is_rejected(self):
        data, geometry, layout = fixture()
        for pointer in ('0x58', '0x60', '0x81', '0xFFFF'):
            changed = copy.deepcopy(layout)
            changed['display_list_pointer_tables'][1]['pointers'] = [pointer]
            with self.assertRaises(ValueError):
                parts.primary_preview(data, geometry, changed)
        with self.assertRaisesRegex(ValueError, 'outside'):
            parts.primary_preview(data, replace(geometry, face_command_offsets=(0, 1)), layout)
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            parts.verify_consumers(b'', 0x15000000)

    def test_export_selection_and_corner_validation_agree(self):
        data, geometry, layout = fixture()
        selected, evidence = parts.primary_preview(data, geometry, layout)
        encoded, binary = models.encode_gltf(58, 0, selected, bank_index=1, character_draw_pass=evidence)
        runs = [{'face_count': r.face_count, 'runtime_material': None} for r in selected.material_runs]
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / '0058-00.gltf'
            path.write_bytes(encoded)
            path.with_suffix('.bin').write_bytes(binary)
            self.assertEqual(1, model_validation.compare_geometry(path, selected, None, runs, draw_pass=evidence)['faces'])
            document = json.loads(encoded)
            document['extras']['romCharacterDrawPass']['primary_pointers'] = [0x80]
            path.write_text(json.dumps(document))
            with self.assertRaisesRegex(ValueError, 'draw-pass selection'):
                model_validation.compare_geometry(path, selected, None, runs, draw_pass=evidence)
