"""Export the ROM texture alternatives and UV controller for attachment 80.

The controller is conditional data, not an authored or observed animation timeline.
The bounded step helper accepts only accumulator/tick inputs that cannot overflow
native signed arithmetic. Existing model and gallery exports are not modified.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
from dataclasses import replace
from pathlib import Path

try:
    from scripts import model_assets as models, model_attachment_updates as updates
    from scripts.model_object_texture_animation import checked
    from scripts.texture_assets import decode_rgba_png_pixels
except ModuleNotFoundError:
    import model_assets as models
    import model_attachment_updates as updates
    from model_object_texture_animation import checked
    from texture_assets import decode_rgba_png_pixels

TABLE_ADDRESS = 0x80090304
TABLE_BYTES = bytes.fromhex('00001c2300000cb1')
TEXTURE_SHA1 = {7203: '42f06a65a9452441a32ed8062f9ab4abe148e59b',
                3249: '8121e5736d5ad8a71860409e5c1446c6d8e62cfb'}
SCALE = struct.unpack('>f', bytes.fromhex('3c23d70a'))[0]
SCOPE = ('Conditional ROM controller and texture alternatives for bank09 entry80; '
         'no gameplay reachability, parent identity, timeline, tick frequency, '
         'visibility or native raster equivalence is claimed.')


def bounded_integer(value, low, high, name):
    if type(value) is not int or not low <= value <= high:
        raise ValueError(f'{name} must be an integer in {low}..{high}')
    return value


def f32(value):
    return struct.unpack('>f', struct.pack('>f', value))[0]


def tile_word(accumulator):
    """Mirror CVT.S.W, two MUL.S operations, ADD.S and TRUNC.W.S."""
    bounded_integer(accumulator, 0, 100, 'accumulator')
    origin = int(f32(f32(f32(f32(accumulator) * SCALE) * f32(120)) + f32(2)))
    return 0xF2002000 | (origin & 0xFFF)


def step(phase, accumulator, texture_flat, *, delta=0, parent_action=0, parent_frame=None):
    """One native updater invocation for bounded inspection inputs.

    Phase and selectors keep their native unsigned field widths. Accumulator
    and delta are restricted to 0..100 so ADDU/SLL/SUBU cannot wrap before their
    native signed clamps. This helper is not a full MIPS emulator.
    """
    bounded_integer(phase, 0, 0xFFFFFFFF, 'phase')
    bounded_integer(accumulator, 0, 100, 'accumulator')
    bounded_integer(texture_flat, 0, 0xFFFF, 'texture_flat')
    bounded_integer(delta, 0, 100, 'delta')
    bounded_integer(parent_action, 0, 0xFFFF, 'parent_action')

    def reached(threshold):
        if parent_frame is None:
            raise ValueError('this parent branch requires parent_frame')
        return f32(threshold) <= f32(parent_frame)  # NaN comparisons remain false.

    if phase == 0:
        accumulator, texture_flat = 50, 7203
        if parent_action == 397 and reached(46):
            phase, texture_flat = 1, 3249
    elif phase == 1:
        accumulator += delta
        if accumulator >= 100:
            phase, accumulator = 2, 100
    elif phase == 2:
        if parent_action == 398 and reached(34):
            phase = 3
    elif phase == 3:
        accumulator -= delta * 4
        if accumulator <= 0:
            phase, accumulator = 4, 0
    return {'phase': phase, 'accumulator': accumulator, 'texture_flat': texture_flat,
            'tile_word': tile_word(accumulator)}


def describe_controller(code, code_base, data, data_base):
    context = updates.material_context(code, code_base, data, data_base)
    if checked(data, data_base, TABLE_ADDRESS, len(TABLE_BYTES)) != TABLE_BYTES:
        raise ValueError('attachment controller texture table changed')
    return {
        'schema_version': 1, 'family': 'rom-attachment-texture-uv-controller',
        'model': [9, 80, 0], 'action': 102, 'updater': 'func_150D83D8',
        'source_model_sha1': updates.MODEL_SHA1, 'capture_inputs': [],
        'scope': SCOPE, 'consumers': context['consumers'],
        'data_spans': [{'address': f'0x{address:08X}', 'hex': raw}
                       for address, raw in updates.DATA_SPANS]
                      + [{'address': f'0x{TABLE_ADDRESS:08X}', 'hex': TABLE_BYTES.hex()}],
        'fields': {'phase': 'descriptor+0x38 u32', 'accumulator': 'descriptor+0x3C s32',
                   'texture_flat': 'descriptor+0x18 u16', 'delta': '0x800BE9E4 s32',
                   'parent_action': 'parent+0x84 u16', 'parent_frame': '*(parent+0x2D0)+0x08 f32'},
        'execution': 'One phase arm per invocation; transition effects in the next arm wait until the next invocation.',
        'transitions': [
            {'phase': 0, 'address': '0x150D8410', 'assign': {'accumulator': 50, 'texture_flat': 7203},
             'condition': {'parent_action': 397, 'parent_frame_gte_f32': 46},
             'when_true': {'phase': 1, 'texture_flat': 3249}},
            {'phase': 1, 'address': '0x150D846C', 'accumulator': 's32(u32(accumulator + delta))',
             'condition': 'signed result >= 100', 'when_true': {'phase': 2, 'accumulator': 100}},
            {'phase': 2, 'address': '0x150D8498',
             'condition': {'parent_action': 398, 'parent_frame_gte_f32': 34},
             'when_true': {'phase': 3}},
            {'phase': 3, 'address': '0x150D84D8', 'accumulator': 's32(u32(accumulator - u32(delta << 2)))',
             'condition': 'signed result <= 0', 'when_true': {'phase': 4, 'accumulator': 0}},
            {'phase': 'all other u32 values, including 4', 'address': '0x150D8408', 'assign': {}}],
        'unchanged_fields': 'Fields not assigned by the selected arm retain their input value; only phase0 writes texture_flat.',
        'uv_update': {'command_offset': 0x340, 'source_command': [0xF2002002, 0x0001E0FE],
                      'unchanged_second_word': 0x0001E0FE, 'affected_material_runs': [0],
                      'affected_faces': 16, 'unchanged_faces': 44, 'image_dimensions': [8, 64],
                      'scale_f32_bits': '3c23d70a',
                      'formula': 'F2002000 | (trunc(f32(f32(120 * f32(f32(accumulator) * scale)) + 2)) & FFF)',
                      'next_F2_restores_remaining_faces': True},
        'sample_domain': {'accumulator': [0, 100], 'delta': [0, 100],
                          'policy': 'Bounded inspection domain, not a proven runtime bound or clock.'},
        'origin_samples': [{'accumulator': value, 'tile_word': tile_word(value),
                            't_origin_quarter_texels': tile_word(value) & 0xFFF,
                            'v_shift_from_stored': ((tile_word(value) & 0xFFF) - 2) / 256}
                           for value in range(101)],
    }


def build_export(rom_argument=None):
    rom_path, layout = models.resolve_rom('us', rom_argument)
    rom, _ = models.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout['normalized_sha1']:
        raise ValueError('attachment controller requires the validated US ROM')
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    manifest = describe_controller(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    bank = next(b for b in models.parse_asset_banks(rom, layout['asset_table']) if b.index == 9)
    entry = next(e for e in models.parse_asset_entries(rom, bank) if e.index == 80)
    payload = rom[entry.start:entry.end]
    if entry.compressed:
        payload = models.decode_rzip_chunk(payload).data
    source = models.parse_geometry_for_bank(payload, 9)
    context = updates.material_context(game.code, layout['game_vram'], game.data, layout['game_data_vram'])['models'][0]
    adjusted, _ = updates.preview_geometry(payload, source, context)
    run = adjusted.material_runs[0]
    flats = models.load_flat_asset_payloads('us', rom_argument, digest)
    files, variants = {}, []
    for flat, expected in TEXTURE_SHA1.items():
        raw = flats[flat]
        if len(raw) != 2048 or hashlib.sha1(raw).hexdigest() != expected:
            raise ValueError('attachment controller texture payload changed')
        mapped = replace(run, pixel=replace(run.pixel, flat_index=flat, mode=0, segment=None, offset=None))
        texture, status = models.choose_preview_texture(mapped, {}, flats)
        if texture is None or (texture.width, texture.height, texture.format, texture.size) != (8, 64, 0, 3):
            raise ValueError('attachment controller RGBA32 layout is unresolved')
        # Independent address indexing: reverse image rows and exchange each
        # odd native row's paired eight-byte halves; check all 512 RGBA pixels.
        expected_rgba = bytes(raw[y * 32 + (x ^ (8 if y % 2 else 0))]
                              for y in range(63, -1, -1) for x in range(32))
        if decode_rgba_png_pixels(texture.png_data, 8, 64) != expected_rgba:
            raise ValueError('attachment controller independent pixel check failed')
        name = f'textures/flat-{flat}.png'
        files[name] = texture.png_data
        variants.append({'flat_index': flat, 'file': name, 'width': 8, 'height': 64,
                         'format': 'RGBA32', 'payload_bytes': len(raw), 'payload_sha1': expected,
                         'png_sha256': hashlib.sha256(texture.png_data).hexdigest(), 'status': status,
                         'selection': 'phase0 reset' if flat == 7203 else 'phase0 threshold branch'})
    manifest.update(normalized_sha1=digest, texture_variants=variants,
                    source_face_count=len(source.faces), independent_pixels_checked=1024,
                    geometry_policy='Source geometry and existing gallery exports remain unchanged.')
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    return manifest, files


def export(output, rom_argument=None, *, verify=False):
    manifest, files = build_export(rom_argument)
    if verify:
        for name, expected in files.items():
            if (output / name).read_bytes() != expected:
                raise ValueError(f'attachment controller output differs from ROM: {name}')
    else:
        output.mkdir(parents=True, exist_ok=False)
        for name, content in files.items():
            path = output / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(content)
    return manifest


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--output', type=Path, default=models.ROOT / 'build/assets/models/attachment80-controller')
    parser.add_argument('--verify', action='store_true', help='rederive and compare an existing export without writing')
    args = parser.parse_args(argv)
    try:
        result = export(args.output.resolve(), args.rom, verify=args.verify)
    except (OSError, ValueError) as error:
        parser.error(str(error))
    print(f"{'Verified' if args.verify else 'Extracted'} attachment80: {len(result['texture_variants'])} textures, "
          f"{len(result['origin_samples'])} UV samples; {args.output / 'manifest.json'}")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
