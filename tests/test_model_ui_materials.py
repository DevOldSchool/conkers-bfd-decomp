import hashlib
import struct
import unittest
from dataclasses import dataclass, replace
from unittest import mock

from scripts import model_assets as models
try:
    from scripts import model_ui_materials as ui
except ImportError:
    import model_ui_materials as ui


@dataclass(frozen=True)
class GeometryFixture:
    vertices: tuple
    faces: tuple
    material_runs: tuple
    preserved_field: bytes = b'unchanged'


class UITextureTests(unittest.TestCase):
    def code_fixture(self):
        base = min(a for a, _, _ in ui.CONSUMERS)
        end = max(a + n for a, n, _ in ui.CONSUMERS)
        code = bytearray(end - base)
        for address, word in ui.GUARDS:
            struct.pack_into('>I', code, address - base, word)
        data_base = ui.DATA[0][0]
        data = bytearray(max(a + len(bytes.fromhex(h)) for a, h in ui.DATA) - data_base)
        for address, raw in ui.DATA:
            data[address - data_base:address - data_base + len(bytes.fromhex(raw))] = bytes.fromhex(raw)
        pins = tuple((a, n, hashlib.sha1(code[a-base:a-base+n]).hexdigest())
                     for a, n, _ in ui.CONSUMERS)
        return code, base, data, data_base, pins

    def context(self, entry=164):
        return ui.model_context(entry)

    def geometry_fixture(self, entry=164):
        pixel = models.ModelTextureBinding(0xFD100000, segment=7, offset=0)
        palette = models.ModelTextureBinding(0xFD100000, segment=7, offset=2048)
        if entry == 162:
            pixel = replace(pixel, flat_index=4349, mode=0, segment=None, offset=None)
            palette = None
        run = models.ModelMaterialRun(0, 1, True, pixel, palette, None, (), None,
            None, (0xFC000000, 123), (0xEF010C3F, 0xDEADBEEF), None,
            texture_loads=((pixel, None), (palette, None)))
        geometry = GeometryFixture(((0, 0, 0),), ((0, 0, 0),), (run,))
        parser = mock.patch.object(ui, '_source_geometry', return_value=geometry)
        parser.start()
        self.addCleanup(parser.stop)
        blob = b'fixture UI source'
        payloads = {1287: b'a' * 2560, 1288: b'b' * 2560}
        model_pin = {entry: (len(blob), hashlib.sha1(blob).hexdigest(), 1, 1)}
        texture_pins = {flat: (len(raw), hashlib.sha1(raw).hexdigest())
                        for flat, raw in payloads.items()}
        return geometry, blob, payloads, model_pin, texture_pins

    def test_context_is_only_two_reviewed_entries(self):
        code, base, data, db, pins = self.code_fixture()
        with mock.patch.object(ui, 'CONSUMERS', pins):
            result = ui.material_context(code, base, data, db)
        self.assertEqual([r['entry'] for r in result['models']], [162, 164])
        self.assertEqual(result['capture_inputs'], [])

    def test_consumer_body_mutation_fails_without_repinning(self):
        code, base, data, db, pins = self.code_fixture()
        code[0] ^= 1
        with mock.patch.object(ui, 'CONSUMERS', pins), self.assertRaisesRegex(ValueError, 'consumer changed'):
            ui.material_context(code, base, data, db)

    def test_semantic_guards_reject_changes_even_with_new_body_hash(self):
        # Model identity, low-mode rewrite, FC removal, segment, RNG range,
        # initial blink counter and texture ID each independently fail closed.
        for address in (0x151EB5AC, 0x151EDAB0, 0x151EDB0C, 0x151EDEB8,
                        0x151EDE60, 0x151ED964, 0x151EDE8C):
            with self.subTest(address=hex(address)):
                code, base, data, db, _ = self.code_fixture()
                code[address-base+3] ^= 1
                pins = tuple((a,n,hashlib.sha1(code[a-base:a-base+n]).hexdigest()) for a,n,_ in ui.CONSUMERS)
                with mock.patch.object(ui, 'CONSUMERS', pins), self.assertRaisesRegex(ValueError, 'instruction changed'):
                    ui.material_context(code, base, data, db)

    def test_initial_global_and_setup_list_are_pinned(self):
        for index in (0, -1):
            code, base, data, db, pins = self.code_fixture()
            data[index] ^= 1
            with mock.patch.object(ui, 'CONSUMERS', pins), self.assertRaisesRegex(ValueError, 'data changed'):
                ui.material_context(code, base, data, db)

    def test_first_draw_is_invariant_for_every_rng_low_byte(self):
        self.assertEqual({ui.first_draw_flat(1, n) for n in range(256)}, {1288})
        self.assertEqual(ui.first_draw_flat(7), 1287)
        self.assertEqual(ui.first_draw_flat(8), 1288)
        self.assertEqual(ui.first_draw_flat(0), 1288)

    def test_copied_state_and_inline_palette_preserve_geometry(self):
        g, blob, payloads, mp, tp = self.geometry_fixture()
        with mock.patch.object(ui, 'MODELS', mp), mock.patch.object(ui, 'PAYLOADS', tp):
            result, evidence = ui.apply_preview_geometry(g, blob, self.context(), payloads)
        self.assertIs(result.vertices, g.vertices)
        self.assertIs(result.faces, g.faces)
        self.assertEqual(result.preserved_field, g.preserved_field)
        run = result.material_runs[0]
        self.assertEqual(run.other_mode, (0xEF000C3F, 0x005041C8))
        self.assertEqual(run.combine_mode, (0xFC12FE25, 0xFFFFFBFD))
        self.assertEqual((run.pixel.flat_index, run.pixel.mode, run.pixel.segment), (1288, 0, None))
        self.assertEqual((run.palette.flat_index, run.palette.mode, run.palette.offset), (1288, 1, None))
        self.assertEqual(run.texture_loads[0][0], run.pixel)
        self.assertEqual(run.texture_loads[1][0], run.palette)
        self.assertEqual(evidence['texture_binding']['selected_flat'], 1288)
        self.assertEqual(g.material_runs[0].pixel.segment, 7)

    def test_equivalent_cli_dataclass_identity_preserves_full_field_guard(self):
        from dataclasses import make_dataclass, fields
        g, blob, payloads, mp, tp = self.geometry_fixture()
        OtherGeometry = make_dataclass('OtherGeometry', [(f.name, object) for f in fields(g)])
        other = OtherGeometry(*(getattr(g, f.name) for f in fields(g)))
        with mock.patch.object(ui, 'MODELS', mp), mock.patch.object(ui, 'PAYLOADS', tp):
            mapped, proof = ui.apply_preview_geometry(other, blob, self.context(), payloads)
            self.assertEqual(g.faces, mapped.faces)
            self.assertEqual(g.vertices, mapped.vertices)
            with self.assertRaisesRegex(ValueError, 'differs from the pinned model'):
                ui.apply_preview_geometry(replace(other, preserved_field='changed'), blob,
                                          self.context(), payloads)

    def test_gltf_provenance_uses_actual_ui_renderer_and_source_transform_scope(self):
        import json
        from test_model_attachment_format import payload
        source = bytearray(payload(jointed=True, parts=2))
        _, native = models.parse_attachment_model(bytes(source), models.parse_model_geometry)
        struct.pack_into(">I", source, native["display_list_pointers"][1], 0xD7000002)
        geometry, native = models.parse_attachment_model(bytes(source), models.parse_model_geometry)
        for entry in (162, 164):
            with self.subTest(entry=entry):
                g, blob, payloads, mp, tp = self.geometry_fixture(entry)
                with mock.patch.object(ui, 'MODELS', mp), mock.patch.object(ui, 'PAYLOADS', tp):
                    _, proof = ui.apply_preview_geometry(g, blob, self.context(entry), payloads)
                encoded, binary = models.encode_gltf(entry, 0, geometry, bank_index=9,
                    character_joints=tuple(native['joints']))
                before = json.loads(encoded)
                self.assertTrue(binary)
                self.assertGreater(len(before['materials']), 1)
                self.assertTrue(all('characterColorState' in m['extras'] for m in before['materials']))
                # One model-level proof applies to all materials, including a
                # run without its own repeated evidence annotation.
                rows = [{} for _ in geometry.material_runs]
                rows[0]['rom_ui_material_state'] = proof
                out = json.loads(models.add_rom_texture_state_evidence(encoded, rows))
                self.assertEqual(proof, out['extras']['romUiMaterialState'])
                self.assertEqual(proof, out['materials'][0]['extras']['romUiMaterialState'])
                self.assertEqual('func_151EDBDC', out['extras']['attachmentColorState']['renderer'])
                self.assertEqual('dynamic-colour-opacity-unresolved', out['extras']['attachmentColorState']['status'])
                self.assertEqual('stored-geometry-neutral-joints', out['extras']['attachmentMatrixState']['status'])
                self.assertNotIn('selector', out['extras']['attachmentMatrixState'])
                self.assertTrue(all('characterColorState' not in m['extras'] for m in out['materials']))
                self.assertEqual(before['skins'], out['skins'])
                self.assertEqual(before['meshes'], out['meshes'])
                self.assertEqual(before['accessors'], out['accessors'])
                for old, new in zip(before['materials'], out['materials']):
                    expected = {**old, 'extras': dict(old['extras'])}
                    expected['extras'].pop('characterColorState')
                    actual = {**new, 'extras': dict(new['extras'])}
                    actual['extras'].pop('romUiMaterialState', None)
                    self.assertEqual(expected, actual)

    def test_direct_rgba_entry_keeps_its_flat_binding(self):
        g, blob, payloads, mp, tp = self.geometry_fixture(162)
        with mock.patch.object(ui, 'MODELS', mp):
            result, evidence = ui.apply_preview_geometry(g, blob, self.context(162), {})
        self.assertIs(result.material_runs[0].pixel, g.material_runs[0].pixel)
        self.assertNotIn('texture_binding', evidence)

    def test_unrelated_context_is_unchanged(self):
        g, blob, payloads, _, _ = self.geometry_fixture()
        self.assertEqual(ui.apply_preview_geometry(g, blob, {'entry': 185}, payloads), (g, None))

    def test_capture_precedence_skips_entire_ui_model(self):
        g, blob, payloads, _, _ = self.geometry_fixture()
        self.assertEqual(ui.apply_preview_geometry(g, blob, self.context(), payloads,
                         {0: {'capture': 'present'}}), (g, None))

    def test_every_context_field_and_integer_type_is_guarded(self):
        g, blob, payloads, mp, tp = self.geometry_fixture()
        mutations = {'model_pointer': '0x8009005C', 'animation_selector': 8,
                     'scope': 'native appearance proven', 'segment': False,
                     'bank': 9.0, 'entry': 164.0,
                     'renderer': 'func_15132B80', 'constructor': 'func_15157010',
                     'ui_material_state': 'later-blink', 'unexpected_field': True}
        with mock.patch.object(ui, 'MODELS', mp), mock.patch.object(ui, 'PAYLOADS', tp):
            for key, value in mutations.items():
                context = {**self.context(), key: value}
                with self.subTest(field=key), self.assertRaisesRegex(ValueError, 'context identity'):
                    ui.apply_preview_geometry(g, blob, context, payloads)

    def test_source_payload_and_geometry_guards(self):
        g, blob, payloads, mp, tp = self.geometry_fixture()
        with mock.patch.object(ui, 'MODELS', mp), mock.patch.object(ui, 'PAYLOADS', tp):
            for b, geom, inputs, message in (
                (blob + b'x', g, payloads, 'source model'),
                (blob, replace(g, faces=()), payloads, 'geometry accounting'),
                (blob, replace(g, vertices=((1, 0, 0),)), payloads, 'geometry differs'),
                (blob, g, {**payloads, 1287: b'x' * 2560}, 'blink payload'),
                (blob, g, {**payloads, 1288: b'x' * 2560}, 'blink payload'),
            ):
                with self.subTest(message=message), self.assertRaisesRegex(ValueError, message):
                    ui.apply_preview_geometry(geom, b, self.context(), inputs)

    def test_segment_palette_and_partial_mode_mutations_fail(self):
        g, blob, payloads, mp, tp = self.geometry_fixture()
        run = g.material_runs[0]
        cases = [replace(run, pixel=replace(run.pixel, segment=5)),
                 replace(run, palette=replace(run.palette, offset=1024)),
                 replace(run, palette=replace(run.palette, segment=6)),
                 replace(run, other_mode_partial=(0, 0, 0, 0)),
                 replace(run, runtime_render_state_offset=8)]
        with mock.patch.object(ui, 'MODELS', mp), mock.patch.object(ui, 'PAYLOADS', tp):
            for changed in cases:
                geom = replace(g, material_runs=(changed,))
                with self.subTest(run=changed), mock.patch.object(ui, '_source_geometry', return_value=geom), self.assertRaises(ValueError):
                    ui.apply_preview_geometry(geom, blob, self.context(), payloads)


if __name__ == '__main__':
    unittest.main()
