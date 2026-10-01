"""Derived particle proof mutations and an independent every-pixel oracle."""
import copy
import hashlib
import json
import struct
import unittest
import zlib
from contextlib import ExitStack
from dataclasses import replace
from unittest.mock import patch

from scripts import model_assets as models
from scripts import model_particle203_materials as particle


def source_run():
    pixel = models.ModelTextureBinding(0xFD500000, flat_index=332, mode=0,
                                       load_command=(0xF3000000, 0x073FF000))
    palette = models.ModelTextureBinding(0xFD100000, flat_index=332, mode=2,
                                         load_command=(0xF0000000, 0x0603C000))
    return models.ModelMaterialRun(
        first_face=0, face_count=20, texture_enabled=True, pixel=pixel, palette=palette,
        render_tile=(0xF5400800, 0x00098060),
        render_tiles=((0, 0xF5400800, 0x00098060),
                      (6, 0xF5600100, 0x06000000), (7, 0xF5500000, 0x07000000)),
        tile_bounds=(0xF2400400, 0x004FC4FC), texture_scale=(0xD7000002, 0xFFFFFFFF),
        combine_mode=None, other_mode=None, runtime_render_state_offset=None,
        texture_loads=((pixel, (0xF5500000, 0x07000000)),
                       (palette, (0xF5600100, 0x06000000))))


def independent_rgba(payload):
    """PNG order: invert source rows, undo odd-row 32-bit swap, expand CI4 RGB."""
    colors = struct.unpack('>16H', payload[2048:])
    out = bytearray()
    for y in range(63, -1, -1):
        for x in range(64):
            col = (x // 2) ^ (4 if y & 1 else 0)
            value = payload[y * 32 + col]
            index = (value >> (4 if x % 2 == 0 else 0)) & 15
            color = colors[index]
            for shift in (11, 6, 1):
                five = (color >> shift) & 31
                out.append(five * 255 // 31)
            out.append(255)
    return bytes(out)


def png_rgba(png):
    """Independent narrow indexed-PNG reader for the encoder's filter-zero output."""
    chunks = {}
    cursor = 8
    while cursor < len(png):
        size = int.from_bytes(png[cursor:cursor + 4], 'big')
        name = png[cursor + 4:cursor + 8]
        chunks.setdefault(name, []).append(png[cursor + 8:cursor + 8 + size])
        cursor += size + 12
    header = struct.unpack('>IIBBBBB', chunks[b'IHDR'][0])
    if header != (64, 64, 4, 3, 0, 0, 0):
        raise AssertionError(header)
    pixels = zlib.decompress(b''.join(chunks[b'IDAT']))
    palette = b''.join(chunks[b'PLTE'])
    alpha = b''.join(chunks[b'tRNS'])
    out = bytearray()
    for row in range(64):
        if pixels[row * 33] != 0:
            raise AssertionError('unexpected filtered PNG row')
        for value in pixels[row * 33 + 1:row * 33 + 33]:
            for index in (value >> 4, value & 15):
                out.extend(palette[index * 3:index * 3 + 3])
                out.append(alpha[index])
    return bytes(out)


class Particle203MaterialTests(unittest.TestCase):
    code_base = 0x15000000
    data_base = particle.DISPATCH_ADDRESS

    def code(self):
        size = max(address + n for address, n, _ in particle.CONSUMERS) - self.code_base
        data = bytearray(size)
        for address, word in particle.GUARDS:
            struct.pack_into('>I', data, address - self.code_base, word)
        return data

    def context(self, code=None, original=None, data=None):
        code = self.code() if code is None else code
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in particle.CONSUMERS]
        data = struct.pack('>13I', *particle.DISPATCH_WORDS) if data is None else data
        with patch.object(particle, 'CONSUMERS', pins):
            return particle.material_context(code, self.code_base, data, self.data_base)

    def fixture(self):
        # Synthetic distinct RGB colors, including palette alpha zero and one.
        payload = bytes((i * 17 + i // 32 * 3) & 255 for i in range(2048))
        payload += struct.pack('>16H', *(i << 11 | (31-i) << 6 | (i*2) << 1 | (i & 1)
                                        for i in range(16)))
        model = bytes(range(256)) + bytes(range(136))
        stack = ExitStack()
        stack.enter_context(patch.object(particle, 'MODEL_SHA256', hashlib.sha256(model).hexdigest()))
        stack.enter_context(patch.object(particle, 'PAYLOAD_SHA256', hashlib.sha256(payload).hexdigest()))
        self.addCleanup(stack.close)
        return source_run(), payload, model, self.context()['models'][0]

    def resolve(self, run, payload, model, context, identity=(9, 203, 0)):
        return particle.preview_texture(run, {332: payload}, context, model, *identity)

    def test_context_has_only_reviewed_identity_and_state(self):
        record = self.context()
        self.assertEqual([], record['capture_inputs'])
        self.assertEqual(10, len(record['consumers']))
        self.assertEqual([(9, 203, 0)], [tuple(r[k] for k in ('bank', 'entry', 'segment'))
                                      for r in record['models']])
        self.assertEqual('func_15168C4C', record['models'][0]['renderer'])
        self.assertEqual(1, record['models'][0]['particle_texture_state']['object_combiner'])

    def test_every_consumer_full_span_is_pinned(self):
        original = self.code()
        for address, size, _ in particle.CONSUMERS:
            changed = bytearray(original)
            changed[address - self.code_base + size - 1] ^= 1
            with self.subTest(consumer=hex(address)), self.assertRaisesRegex(ValueError, 'consumer changed'):
                self.context(changed, original)
        with self.assertRaisesRegex(ValueError, 'span is missing'):
            self.context(bytearray(8), original)

    def test_semantic_guards_survive_repinning(self):
        original = self.code()
        for address, word in particle.GUARDS:
            changed = bytearray(original)
            struct.pack_into('>I', changed, address - self.code_base, word ^ 1)
            with self.subTest(pc=hex(address)), self.assertRaisesRegex(ValueError, 'instruction changed'):
                self.context(changed)

    def test_dispatch_mutations_and_truncation_are_rejected(self):
        original = struct.pack('>13I', *particle.DISPATCH_WORDS)
        for i in range(13):
            changed = bytearray(original)
            changed[i * 4 + 3] ^= 1
            with self.subTest(word=i), self.assertRaisesRegex(ValueError, 'dispatch changed'):
                self.context(data=changed)
        with self.assertRaisesRegex(ValueError, 'span is missing'):
            self.context(data=original[:-1])

    def test_source_run_pin_matches_reviewed_commands(self):
        self.assertEqual(particle.RUN_SHA256, particle.run_digest(source_run()))
        self.assertEqual('direct-ci4-lookup-mode-unresolved',
                         models.choose_preview_texture(source_run(), {}, {332: bytes(2080)})[1])

    def test_all_4096_pixels_match_independent_decode_with_opaque_alpha(self):
        run, payload, model, ctx = self.fixture()
        saved = copy.deepcopy((run, payload, model, ctx))
        tex, status, proof = self.resolve(run, payload, model, ctx)
        self.assertEqual('rom-particle203-ci4-rgb-texture', status)
        self.assertEqual('us-rom-particle203', tex.family)
        self.assertEqual(independent_rgba(payload), png_rgba(tex.png_data))
        self.assertEqual({255}, set(png_rgba(tex.png_data)[3::4]))
        self.assertEqual(4096, proof['decoded_texel_count'])
        self.assertNotEqual(proof['source_ci4_png_sha1'], proof['texture_png_sha1'])
        self.assertEqual(saved, (run, payload, model, ctx))
        self.assertEqual('rom-object-renderer-unresolved',
                         models.rom_object_preview_texture(run, {}, {332: payload}, [], ctx)[1])

    def test_source_model_payload_or_presence_cannot_change(self):
        run, payload, model, ctx = self.fixture()
        for changed in (model[:-1], model + b'\0', bytes([model[0] ^ 1]) + model[1:]):
            with self.subTest(model=len(changed)), self.assertRaisesRegex(ValueError, 'source model changed'):
                self.resolve(run, payload, changed, ctx)
        for changed in (None, payload[:-1], payload + b'\0', payload[:-1] + bytes([payload[-1] ^ 1])):
            with self.subTest(payload=type(changed)), self.assertRaisesRegex(ValueError, 'source payload changed'):
                self.resolve(run, changed, model, ctx)
        with self.assertRaisesRegex(ValueError, 'source payload changed'):
            particle.preview_texture(run, {}, ctx, model, 9, 203, 0)

    def test_every_material_source_component_is_authenticated(self):
        run, payload, model, ctx = self.fixture()
        changes = [replace(run, first_face=1), replace(run, face_count=19),
                   replace(run, texture_enabled=False), replace(run, texture_coordinates_proven=False),
                   replace(run, other_mode=particle.OTHER_MODE),
                   replace(run, combine_mode=particle.COMBINE_MODE),
                   replace(run, other_mode_partial=(0, 0, 0, 0)),
                   replace(run, matrix_index=0), replace(run, runtime_render_state_offset=0),
                   replace(run, tile_bounds=(0xF2400000, 0x000FC0FC)),
                   replace(run, texture_loads=()),
                   replace(run, pixel=replace(run.pixel, flat_index=333)),
                   replace(run, palette=replace(run.palette, mode=1))]
        for changed in changes:
            with self.subTest(run=changed), self.assertRaisesRegex(ValueError, 'source material run changed'):
                self.resolve(changed, payload, model, ctx)

    def test_context_state_and_identity_cannot_expand(self):
        run, payload, model, ctx = self.fixture()
        for identity in ((1, 203, 0), (9, 202, 0), (9, 203, 1), (9, 203, False)):
            with self.subTest(identity=identity), self.assertRaisesRegex(ValueError, 'identity changed'):
                self.resolve(run, payload, model, ctx, identity)
        for field, value in (('object_mode', 2), ('object_mode', True), ('object_combiner', 0),
                             ('other_mode', [0xEF082CAF, 0x00552230]), ('flat_index', 333),
                             ('payload_sha256', '0'*64), ('model_sha256', '0'*64)):
            changed = copy.deepcopy(ctx)
            changed['particle_texture_state'][field] = value
            with self.subTest(field=field, value=value), self.assertRaisesRegex(ValueError, 'context changed'):
                self.resolve(run, payload, model, changed)
        changed = {**ctx, 'entry': 202}
        with self.assertRaisesRegex(ValueError, 'identity changed'):
            self.resolve(run, payload, model, changed)
        changed = {**ctx, 'renderer': 'func_15132B80'}
        with self.assertRaisesRegex(ValueError, 'context changed'):
            self.resolve(run, payload, model, changed)
        for absent in (None, {}, {'bank': 9, 'entry': 202, 'segment': 0}):
            self.assertEqual((None, 'rom-particle203-context-unresolved', None),
                             self.resolve(run, payload, model, absent))

    def test_evidence_is_retained_in_gltf_without_rewriting_source_modes(self):
        run, payload, model, ctx = self.fixture()
        _, _, evidence = self.resolve(run, payload, model, ctx)
        doc = {'materials': [{'extras': {'materialRun': 0, 'combineMode': None}}]}
        out = models.add_rom_texture_state_evidence(json.dumps(doc).encode(),
                                                    [{'rom_particle_texture_state': evidence}])
        result = json.loads(out)
        extras = result['materials'][0]['extras']
        self.assertEqual(evidence, extras['romParticleTextureState'])
        self.assertIsNone(extras['combineMode'])
        raw = json.dumps(doc).encode()
        self.assertEqual(raw, models.add_rom_texture_state_evidence(raw, [{}]))


if __name__ == '__main__':
    unittest.main()
