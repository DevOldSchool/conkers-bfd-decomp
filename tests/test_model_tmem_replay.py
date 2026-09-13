from dataclasses import replace
import json
import struct
import unittest

from scripts import model_assets as m
from scripts.texture_assets import decode_ci8_png, decode_rgba_png_pixels


def fixture(split=False, barrier=None):
    setup = [(0x01003006, 0x01000000), (0xD7000102, 0xFFFFFFFF),
             (0xFCFF9880, 0xF514FEFF), (0xF5080200, 0x0100C030),
             (0xF2000000, 0x0101C01C)]  # Tile 1: 8 by 8, stride 8.

    def load(flat, count):
        return [(0xFD100000, flat), (0xF5100000, 0x07000000),
                (0xF3000000, 0x07000000 | ((count // 2 - 1) << 12)),
                (0xFD100000, flat | 0x400000), (0xF5000100, 0x06000000),
                (0xF0000000, 0x063FC000)]

    commands = setup + load(1, 64) + [(0x05000204, 0)]
    if split:
        commands += [(0xDF000000, 0)] + setup
    if barrier:
        commands.append(barrier)
    commands += load(2, 16) + [(0xF5080400, 0x00010040),  # Later tile 0 stays unselected.
                              (0x05000204, 0), (0xDF000000, 0)]
    vertices = b''.join(struct.pack('>hhhHhh4B', *xyz, 0, 0, 0, 255, 255, 255, 255)
                        for xyz in ((0, 0, 0), (1, 0, 0), (0, 1, 0)))
    display = b''.join(struct.pack('>II', *pair) for pair in commands)
    data = struct.pack('>10I', 40 + len(vertices), len(display), 0, 0, 0, 0, 0, 0, 0, 0x80000000) + vertices + display
    geometry = m.parse_model_geometry(data, independent_display_lists=split)
    palette = b''.join(struct.pack('>H', (i << 1) | 1) for i in range(256))
    return geometry, {1: bytes(range(64)) + palette, 2: bytes([201]) * 16 + palette}


class TextureMemoryReplayTests(unittest.TestCase):
    def rgba8_run(self, full=False):
        geometry, payloads = fixture()
        run = geometry.material_runs[-1]
        count = 32 if full else 8
        payloads[2] = bytes(c for i in range(count) for c in (10 + i, 100 + i, 200 + i, 250 - i))
        pixel = replace(run.pixel, image_command=0xFD180000,
                        load_command=(0xF3000000, 0x07000000 | ((count - 1) << 12)))
        return replace(run, pixel=pixel, palette=None,
                       other_mode=(0xEF182C3F, 0x04D049D8),
                       texture_loads=run.texture_loads[:2] + ((pixel, (0xF5180000, 0x07000000)),)), payloads

    def test_rgba32_load_splits_banks_and_rgba8_fetch_uses_byte_alpha(self):
        run, payloads = self.rgba8_run()
        texture, status = m.choose_preview_texture(run, {}, payloads)
        self.assertEqual('runtime-composed-rgba8-tmem-texture', status)
        self.assertEqual((0, 1, 8, 8), (texture.format, texture.size, texture.width, texture.height))
        rgba = decode_rgba_png_pixels(texture.png_data, 8, 8)
        rows = [rgba[y * 32:(y + 1) * 32] for y in reversed(range(8))]
        self.assertEqual(bytes(c for p in (10, 100, 11, 101, 12, 102, 13, 103) for c in [p] * 4), rows[0])
        self.assertEqual(bytes(c for p in (16, 106, 17, 107, 14, 104, 15, 105) for c in [p] * 4), rows[1])
        self.assertEqual(bytes(c for p in range(16, 24) for c in [p] * 4), rows[2])
        self.assertEqual((16, 32), texture.tmem_load_sizes)
        # BA never enters lower TMEM, and the RGBA32 write invalidates the TLUT.
        _, _, _, _, last_pixel, palette = m.replay_lower_tmem(run, payloads, rgba32=True)
        self.assertEqual(run.pixel, last_pixel)
        self.assertIsNone(palette)

    def test_rgba32_can_fully_replace_the_selected_rgba8_tile(self):
        run, payloads = self.rgba8_run(full=True)
        texture, _ = m.choose_preview_texture(run, {}, payloads)
        self.assertIsNotNone(texture)
        self.assertEqual((32,), texture.tmem_load_sizes)
        self.assertEqual([2], [load[0] for load in texture.tmem_source_loads])
        # Full replacement does not depend on unknown earlier memory.
        self.assertEqual(texture, m.choose_preview_texture(run, {}, {2: payloads[2]})[0])

    def test_rgba8_rejects_unknown_bytes_and_incompatible_draw_state(self):
        run, payloads = self.rgba8_run()
        for sources in ({2: payloads[2]}, {**payloads, 2: b'short'}):
            self.assertIsNone(m.choose_preview_texture(run, {}, sources)[0])
        for candidate in (replace(run, other_mode=None),
                          replace(run, other_mode=(0xEF18AC3F, 0x04D049D8)),
                          replace(run, other_mode=(0xEF192C3F, 0x04D049D8)),
                          replace(run, other_mode_partial=(0, 0, 0, 0)),
                          replace(run, combine_mode=None),
                          replace(run, render_tile=(0xF5080201, run.render_tile[1])),
                          replace(run, texture_loads=run.texture_loads[:-1])):
            with self.subTest(candidate=candidate):
                self.assertIsNone(m.rgba8_tmem_preview_texture(candidate, payloads)[0])

    def test_partial_load_preserves_prior_indices_and_selected_tile(self):
        geometry, payloads = fixture()
        run = geometry.material_runs[-1]
        texture, status = m.choose_preview_texture(run, {}, payloads)
        self.assertEqual('runtime-composed-character-tmem-texture', status)
        self.assertEqual((8, 8), (texture.width, texture.height))
        decoded = decode_ci8_png(texture.png_data, 'linear', 8, 8)
        self.assertEqual(bytes([201]) * 16, decoded[:16])
        self.assertEqual(bytes(range(16, 24)), decoded[16:24])
        self.assertEqual(bytes([28, 29, 30, 31, 24, 25, 26, 27]), decoded[24:32])
        self.assertEqual(payloads[2][-512:], decoded[64:])
        self.assertEqual([1, 2], [item[0] for item in texture.tmem_source_loads])
        self.assertIsNone(texture.pixel_byte_offset)  # No single source payload.
        self.assertEqual(0xF5100000, run.texture_loads[0][1][0])

    def test_independent_lists_and_unknown_writes_do_not_inherit_memory(self):
        for split, barrier in ((True, None), (False, (0xF4000000, 0)),
                               (False, (0xDE000000, 0x08000200))):
            with self.subTest(split=split, barrier=barrier):
                geometry, payloads = fixture(split, barrier)
                self.assertIsNone(m.choose_preview_texture(geometry.material_runs[-1], {}, payloads)[0])

    def test_unknown_or_short_earlier_load_cannot_fill_the_tail(self):
        geometry, payloads = fixture()
        run = geometry.material_runs[-1]
        for candidate in ({2: payloads[2]}, {1: b'short', 2: payloads[2]}):
            self.assertIsNone(m.choose_preview_texture(run, {}, candidate)[0])
        binding, tile = run.texture_loads[0]
        for change in (replace(binding, mode=1), replace(binding, segment=6),
                       replace(binding, image_command=0xFD180000),
                       replace(binding, load_command=(0xF3000000, 0x0701F001))):
            changed = replace(run, texture_loads=((change, tile),) + run.texture_loads[1:])
            self.assertIsNone(m.choose_preview_texture(changed, {}, payloads)[0])

    def test_latest_palette_and_draw_identity_are_required(self):
        geometry, payloads = fixture()
        run = geometry.material_runs[-1]
        for change in (replace(run, palette=replace(run.palette, flat_index=1)),
                       replace(run, pixel=replace(run.pixel, flat_index=1)),
                       replace(run, texture_loads=run.texture_loads[:-1]),
                       replace(run, combine_mode=None)):
            self.assertIsNone(m.character_tmem_preview_texture(change, payloads)[0])
        self.assertIsNone(m.character_tmem_preview_texture(run, {**payloads, 2: bytes(528)})[0])

    def test_packed_material_keeps_replay_provenance(self):
        loads = [{'flat_index': 1, 'payload_sha1': 'abc', 'tmem_byte_offset': 0, 'loaded_bytes': 64}]
        document = {'materials': [{'extras': {'materialRun': 0}}]}
        result = json.loads(m.add_rom_texture_state_evidence(json.dumps(document).encode(),
                            [{'texture': {'tmem_source_loads': loads}}]))
        self.assertEqual(loads, result['materials'][0]['extras']['romTextureMemory']['source_loads'])


if __name__ == '__main__':
    unittest.main()
