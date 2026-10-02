"""UI-only recovery validation: real synthetic geometry, resolvers and PNGs."""
import copy
import hashlib
import json
import struct
import tempfile
import unittest
from contextlib import ExitStack
from dataclasses import replace
from pathlib import Path
from unittest.mock import patch

from scripts import model_assets as models, model_validation as validation
from scripts import model_ui_materials as ui
from scripts.model_evidence_cache import ContentSnapshot

PROOF_FIELDS = ('rom_texture_state_consensus', 'rom_object_texture_animation',
                'rom_object_texture_binding', 'rom_scene_texture_state',
                'rom_ui_material_state')


def native_triangle(commands, *, attachment=True, target_size=None):
    """Build public synthetic model bytes; no private ROM fixture is embedded."""
    vertices = b''.join(struct.pack('>hhhHhh4B', x, y, 0, 127, x * 32, y * 32,
                                    255, 255, 255, 255)
                        for x, y in ((0, 0), (10, 0), (0, 10)))
    commands = ([(0xDA380003, 0x03000000)] if attachment else []) + [(0x01003006, 0x01000000), *commands]
    if attachment:
        table = 24 + len(vertices)
        start = (table + 4 + 7) & ~7
        prefix = bytearray(start)
        struct.pack_into('>6I', prefix, 0, table, 4, 0, 0, 0, 0x80000000)
        prefix[24:table] = vertices
        struct.pack_into('>I', prefix, table, start)
    else:
        prefix = bytearray(40 + len(vertices))
        prefix[40:] = vertices
    if target_size:
        while len(prefix) + (len(commands) + 1) * 8 < target_size:
            commands.append((0xE7000000, 0))
    commands.append((0xDF000000, 0))
    display = b''.join(struct.pack('>II', *pair) for pair in commands)
    if not attachment:
        struct.pack_into('>10I', prefix, 0, len(prefix), len(display),
                         0, 0, 0, 0, 0, 0, 0, 0x80000000)
    raw = bytes(prefix) + display
    if target_size:
        assert len(raw) == target_size
    return raw


def ui_fixture():
    raw = native_triangle([
        (0xD7000002, 0xFFFFFFFF), (0xEF19AC3F, 0x0C192078),
        (0xFD100000, 0x07000000), (0xF5100000, 0x07000000),
        (0xF3000000, 0x073FF000), (0xFD100000, 0x07000800),
        (0xF5000100, 0x06000000), (0xF0000000, 0x063FC000),
        (0xF5080800, 0x00014060), (0xF2002002, 0x0007E0FE),
        (0x05000204, 0)])
    payloads = {flat: bytes(range(256)) * 8 + struct.pack('>H', colour) * 256
                for flat, colour in ((1287, 0xF801), (1288, 0x07C1))}
    return raw, payloads


class UiMaterialValidationTests(unittest.TestCase):
    def setUp(self):
        self.stack = ExitStack()
        self.addCleanup(self.stack.close)
        self.root = Path(self.stack.enter_context(tempfile.TemporaryDirectory()))
        self.path = self.root / 'manifest.json'


    def pin(self, module, name, value):
        self.stack.enter_context(patch.object(module, name, value))


    def setup_family(self):
        self.entry = 164
        self.raw, self.payloads = ui_fixture()
        self.pin(ui, 'MODELS', {164: (len(self.raw), hashlib.sha1(self.raw).hexdigest(), 1, 1)})
        self.pin(ui, 'PAYLOADS', {k: (len(v), hashlib.sha1(v).hexdigest())
                                for k, v in self.payloads.items()})
        self.context = ui.model_context(164)
        self.field = 'rom_ui_material_state'
        segment = models.ModelSegment(0, 0, len(self.raw), True, self.raw)
        self.bundle = models.ModelBundle(self.entry, 0, False, self.raw, (segment,))
        self.source = models.parse_segment_geometry(segment, 9)
        self.context_report = {'models': [self.context], 'normalized_sha1': 'synthetic-rom'}
        self.stack.enter_context(patch.object(models, 'load_model_bundles',
            return_value=(None, None, 'synthetic-rom', [self.bundle], [])))
        self.stack.enter_context(patch.object(models, 'load_object_material_context',
                                              return_value=self.context_report))
        self.build_manifest()

    def build_manifest(self, runtime=None):
        runtime = runtime or {}
        per_model = {i: runtime[(9, self.entry, 0, i)] for i in range(len(self.source.material_runs))
                     if (9, self.entry, 0, i) in runtime}
        self.mapped, self.proof = ui.apply_preview_geometry(self.source, self.raw,
            self.context, self.payloads, per_model)
        self.textures = {}
        rows = []
        for index, run in enumerate(self.mapped.material_runs):
            texture, status = models.choose_preview_texture(run, {}, self.payloads)
            row = {'material_run': index, 'source_face_count': run.face_count,
                   'face_count': run.face_count, 'runtime_material': None,
                   'status': status, 'texture': None}
            if self.proof is not None:
                row[self.field] = self.proof
            if texture is not None:
                self.textures[index] = texture
                row['texture'] = self.save_texture(texture, 'textures/' + models.preview_texture_filename(texture))
            rows.append(row)
        record = {'bank_entry': self.entry, 'segment': 0,
                  'source_face_count': len(self.source.faces), 'material_runs': rows}
        if self.proof is not None:
            record[self.field] = self.proof
        self.manifest = {'bank_index': 9, 'normalized_sha1': 'synthetic-rom',
                         'rom_object_material_context': self.context_report, 'models': [record]}
        self.save()

    def save_texture(self, texture, name):
        destination = self.root / name
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(texture.png_data)
        return {'file': name, 'png_sha1': texture.sha1, 'flat_index': texture.flat_index,
                'source_family': texture.family, 'format': texture.format, 'size': texture.size,
                'width': texture.width, 'height': texture.height,
                'pixel_byte_offset': texture.pixel_byte_offset,
                'palette_byte_offset': texture.palette_byte_offset}


    def save(self):
        validation.write(self.path, self.manifest)
        self.manifest = validation.read(self.path)


    def compare(self, runtime=None):
        return validation.compare_rom_object_materials(self.path, self.payloads, {}, runtime or {})


    def assert_invalid(self, runtime=None):
        result = validation.checked(lambda: self.compare(runtime))
        self.assertEqual('failed', result['status'], result)


    def test_ui_proof_mutations_at_model_and_run_are_rejected(self):
        self.setup_family()
        original = copy.deepcopy(self.manifest)
        for level in ('model', 'run'):
            for field, value in (('renderer', 'func_unreviewed'), ('source_faces', 99),
                                 ('source_runs', True)):
                self.manifest = copy.deepcopy(original)
                # JSON serialization separates equal proof objects, as in a saved manifest.
                self.manifest = json.loads(json.dumps(self.manifest))
                record = self.manifest['models'][0]
                target = record if level == 'model' else record['material_runs'][0]
                target[self.field][field] = value
                self.save()
                with self.subTest(level=level, field=field):
                    self.assert_invalid()


    def test_missing_model_run_and_all_ui_proofs_are_rejected(self):
        self.setup_family()
        original = json.loads(json.dumps(self.manifest))
        for absent in ('model', 'run', 'all'):
            self.manifest = copy.deepcopy(original)
            record = self.manifest['models'][0]
            if absent in ('model', 'all'):
                record.pop(self.field)
            for row in record['material_runs'] if absent == 'all' else [record['material_runs'][0]]:
                if absent in ('run', 'all'):
                    row.pop(self.field)
            self.save()
            with self.subTest(absent=absent):
                self.assert_invalid()


    def test_texture_identity_metadata_cannot_be_self_asserted(self):
        self.setup_family()
        original = copy.deepcopy(self.manifest)
        for field, value in (('flat_index', 1287), ('source_family', 'captured'), ('width', 64),
                             ('height', 32), ('png_sha1', '0' * 40), ('format', 0),
                             ('size', 0), ('size', True)):
            self.manifest = copy.deepcopy(original)
            self.manifest['models'][0]['material_runs'][0]['texture'][field] = value
            self.save()
            with self.subTest(field=field):
                self.assert_invalid()
        self.manifest = copy.deepcopy(original)
        self.manifest['models'][0]['material_runs'][0]['status'] = 'self-asserted'
        self.save()
        self.assert_invalid()


    def test_missing_and_changed_ui_png_reject_even_with_updated_self_hash(self):
        self.setup_family()
        row = self.manifest['models'][0]['material_runs'][0]
        image = self.root / row['texture']['file']
        expected = image.read_bytes()
        image.unlink()
        self.assert_invalid()
        image.write_bytes(expected + b'changed')
        row['texture']['png_sha1'] = hashlib.sha1(image.read_bytes()).hexdigest()
        self.save()
        self.assert_invalid()


    def test_capture_precedence_requires_source_geometry_and_no_ui_proof(self):
        self.setup_family()
        runtime = {(9, 164, 0, 0): {}}
        self.assert_invalid(runtime)
        self.build_manifest(runtime)
        self.assertEqual(self.source, self.mapped)
        result = self.compare(runtime)
        self.assertEqual(0, result['consensus_texture_runs'])
        self.manifest['models'][0]['material_runs'][0][self.field] = {'renderer': 'injected'}
        self.save()
        self.assert_invalid(runtime)


    def test_ui_first_draw_proof_and_png_are_recomputed(self):
        self.setup_family()
        self.assertEqual(1288, self.textures[0].flat_index)
        self.assertEqual(1, self.compare()['consensus_texture_runs'])
        self.manifest['models'][0]['material_runs'][0][self.field]['texture_binding']['selected_flat'] = 1287
        self.save()
        self.assert_invalid()


    def test_later_blink_png_with_matching_self_hash_is_rejected(self):
        self.setup_family()
        run = self.mapped.material_runs[0]
        def remap(binding):
            return replace(binding, flat_index=1287) if binding else binding
        later = replace(run, pixel=remap(run.pixel), palette=remap(run.palette),
                        texture_loads=tuple((remap(b), tile) for b, tile in run.texture_loads))
        texture, _ = models.choose_preview_texture(later, {}, self.payloads)
        self.assertIsNotNone(texture)
        self.assertEqual(1287, texture.flat_index)
        self.assertNotEqual(texture.sha1, self.textures[0].sha1)
        self.manifest['models'][0]['material_runs'][0]['texture'] = self.save_texture(texture, 'textures/later-blink.png')
        self.save()
        self.assert_invalid()

    def test_extra_or_missing_run_cannot_pass_partial_comparison(self):
        self.setup_family()
        original = copy.deepcopy(self.manifest)
        for rows in ([], original['models'][0]['material_runs'] * 2):
            self.manifest = copy.deepcopy(original)
            self.manifest['models'][0]['material_runs'] = rows
            self.save()
            with self.subTest(count=len(rows)):
                self.assert_invalid()

    def write_gltf(self):
        geometry_dir = self.root / 'geometry'
        geometry_dir.mkdir(exist_ok=True)
        joints = tuple(models.parse_attachment_model(self.raw, models.parse_model_geometry)[1]['joints']) or None
        textures = {models.material_name(self.mapped.material_runs[i]): '../' + row['texture']['file']
                    for i, row in enumerate(self.manifest['models'][0]['material_runs']) if row['texture']}
        data, binary = models.encode_gltf(self.entry, 0, self.mapped, textures,
            bank_index=9, character_joints=joints, output_stem='model')
        rows = self.manifest['models'][0]['material_runs']
        data = models.add_rom_texture_state_evidence(data, rows)
        path = geometry_dir / 'model.gltf'
        path.write_bytes(data)
        path.with_suffix('.bin').write_bytes(binary)
        return path, joints, rows


    def test_guarded_gltf_texture_binding_rejects_alternate_valid_png(self):
        self.setup_family()
        path, joints, rows = self.write_gltf()
        self.assertEqual(1, validation.compare_geometry(path, self.mapped, joints, rows,
                                                      preview_root=self.root)['faces'])
        document = validation.read(path)
        image = document['images'][0]
        alternate = self.root / 'textures/alternate.png'
        alternate.write_bytes((self.root / rows[0]['texture']['file']).read_bytes())
        image['uri'] = '../textures/alternate.png'
        validation.write(path, document)
        with self.assertRaisesRegex(ValueError, 'image binding'):
            validation.compare_geometry(path, self.mapped, joints, rows, preview_root=self.root)


    def test_ui_document_and_material_proofs_are_exact_and_required(self):
        self.setup_family()
        path, joints, rows = self.write_gltf()
        original = validation.read(path)
        self.assertEqual(1, validation.compare_geometry(path, self.mapped, joints, rows,
                                                       preview_root=self.root)['faces'])
        for level in ('document', 'material'):
            for value in (None, {'renderer': 'unreviewed'}, {**self.proof, 'source_runs': True}):
                document = copy.deepcopy(original)
                extras = document['extras'] if level == 'document' else document['materials'][0]['extras']
                if value is None:
                    extras.pop('romUiMaterialState')
                else:
                    extras['romUiMaterialState'] = value
                validation.write(path, document)
                with self.subTest(level=level, value=value), self.assertRaisesRegex(ValueError, 'proof|UI material'):
                    validation.compare_geometry(path, self.mapped, joints, rows, preview_root=self.root)

    def test_ui_geometry_rejects_wrong_renderer_and_generic_character_provenance(self):
        self.setup_family()
        path, joints, rows = self.write_gltf()
        original = validation.read(path)
        for level in ('document', 'material'):
            for field in ('characterColorState', 'attachmentColorState', 'attachmentMatrixState'):
                document = copy.deepcopy(original)
                extras = document.setdefault('extras', {}) if level == 'document' else document['materials'][0]['extras']
                extras[field] = {'renderer': 'func_1502CCFC', 'status': 'proven'}
                validation.write(path, document)
                with self.subTest(level=level, field=field), self.assertRaisesRegex(ValueError, 'character|renderer'):
                    validation.compare_geometry(path, self.mapped, joints, rows, preview_root=self.root)

    def test_constructor_state_must_be_rebuilt_before_geometry_check(self):
        self.setup_family()
        path, joints, rows = self.write_gltf()
        # The stored list has different texture state and no ROM UI provenance.
        # Only the independently derived constructor state is an accepted input.
        validation.compare_geometry(path, self.mapped, joints, rows, preview_root=self.root)
        with patch.object(ui, 'apply_preview_geometry', wraps=ui.apply_preview_geometry) as apply:
            geometry, update, proofs = validation.verified_object_preview_geometry(
                self.source, self.raw, self.context, self.payloads, {}, self.manifest['models'][0])
        self.assertEqual(self.mapped, geometry)
        self.assertEqual(self.proof, proofs[self.field])
        self.assertIsNone(update)
        apply.assert_called_once()
        self.assertNotEqual(self.source.material_runs[0].other_mode, geometry.material_runs[0].other_mode)
        self.assertNotEqual(self.source.material_runs[0].combine_mode, geometry.material_runs[0].combine_mode)
        self.assertEqual(self.source.vertices, geometry.vertices)
        self.assertEqual(self.source.faces, geometry.faces)

    def test_cache_dependencies_cover_all_five_proof_families(self):
        rows = []
        for index, field in enumerate(PROOF_FIELDS):
            name = f'textures/dependency-{index}.png'
            image = self.root / name
            image.parent.mkdir(exist_ok=True)
            image.write_bytes(models.encode_rgba_png(1, 1, bytes((index, 20, 30, 255))))
            rows.append({field: {'proof': index}, 'texture': {'file': name}})
        validation.write(self.path, {'models': [{'material_runs': rows}]})
        before = validation.identity(validation.rom_object_material_dependencies(self.path))
        for index, row in enumerate(rows):
            image = self.root / row['texture']['file']
            original = image.read_bytes()
            image.write_bytes(original + b'changed')
            with self.subTest(field=PROOF_FIELDS[index]):
                self.assertNotEqual(before, validation.identity(validation.rom_object_material_dependencies(self.path)))
            image.write_bytes(original)
        image.unlink()
        with self.assertRaises((OSError, ValueError)):
            validation.rom_object_material_dependencies(self.path)


    def test_cache_dependencies_include_manifest_and_optional_runtime_catalog(self):
        validation.write(self.path, {'models': []})
        runtime = self.root / 'runtime.json'
        validation.write(runtime, {'materials': []})
        before = validation.identity(validation.rom_object_material_dependencies(self.path, runtime_path=runtime))
        validation.write(runtime, {'materials': [], 'changed': True})
        self.assertNotEqual(before, validation.identity(validation.rom_object_material_dependencies(self.path, runtime_path=runtime)))
        current = validation.identity(validation.rom_object_material_dependencies(self.path))
        validation.write(self.path, {'models': [], 'changed': True})
        self.assertNotEqual(current, validation.identity(validation.rom_object_material_dependencies(self.path)))


    def test_cache_png_dependency_stays_in_content_snapshot_until_final_verification(self):
        self.setup_family()
        image = self.root / self.manifest['models'][0]['material_runs'][0]['texture']['file']
        before = ContentSnapshot()
        validation.rom_object_material_dependencies(self.path, digest_file=before.digest)
        self.assertIn(image.resolve(), before.hashes)
        self.assertEqual([], before.verify(ContentSnapshot()))
        image.write_bytes(image.read_bytes() + b'changed-after-cache-key')
        self.assertEqual([str(image.resolve())], before.verify(ContentSnapshot()))



if __name__ == "__main__":
    unittest.main()
