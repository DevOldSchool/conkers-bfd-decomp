"""Export complete ROM scene/object texture frame sets and their proven bindings."""
from __future__ import annotations

import argparse
import hashlib
import json
from dataclasses import replace
from pathlib import Path

try:
    from scripts import model_assets as models
    from scripts import model_object_texture_animation as animation
    from scripts import model_scene_texture_bindings as scene_bindings
    from scripts import model_texture_sequence_state as sequence_state
except ModuleNotFoundError:
    import model_assets as models
    import model_object_texture_animation as animation
    import model_scene_texture_bindings as scene_bindings
    import model_texture_sequence_state as sequence_state

SCOPE = ('ROM texture frame sets with source model/material and selector links. '
         'Stored frame order and conditional selector rules do not establish '
         'a playback clock, current phase, gameplay visibility or native raster parity.')


def encode_frames(run, context, evidence, payloads, tables):
    """Reproduce every image already admitted by the complete binding contract.

    The existing resolver has checked the unmodified full frame array first.
    A remapped frame must reproduce that resolver's recorded PNG hash; no table,
    palette, image-layout or material evidence is relaxed to obtain a variant.
    """
    is_object = 'texture_animation' in context
    frames = evidence['frames'] if is_object else evidence['decoded_frames']
    result = []
    for frame in frames:
        flat = frame['flat_index']
        pixel = replace(run.pixel, flat_index=flat, mode=0, segment=None, offset=None)
        palette = (replace(run.palette, flat_index=flat, mode=2, segment=None, offset=None)
                   if is_object and run.palette is not None else None)
        mapped = replace(run, pixel=pixel, palette=palette)
        texture, status = models.choose_preview_texture(mapped, {}, payloads)
        if texture is None and is_object and ('lookup-mode-unresolved' in status or status == 'no-proven-texture'):
            texture, status, _ = models.rom_object_preview_texture(mapped, {}, payloads, tables, context)
        if texture is None or texture.png_data is None or texture.sha1 != frame['png_sha1']:
            raise ValueError('sequence frame differs from the complete ROM binding proof')
        result.append((texture, status))
    return result


def build_export(rom_argument=None):
    rom_path, _, digest, bundles, tables = models.load_model_bundles('us', rom_argument, 4)
    # All helpers independently reject changes to the normalized source identity.
    payloads = models.load_flat_asset_payloads('us', rom_argument, digest)
    context = models.load_object_material_context('us', rom_argument, digest, 4)
    _, layout = models.resolve_rom('us', rom_argument)
    rom, _ = models.normalize_rom(rom_path.read_bytes())
    if hashlib.sha1(rom).hexdigest() != digest:
        raise ValueError('texture-sequence ROM changed during extraction')
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    rows = animation.animation_table(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    segments = {(bundle.index, segment.index): segment for bundle in bundles for segment in bundle.segments}
    files, images, arrays, bindings, unbound = {}, {}, {}, [], []

    def array(address, flats):
        previous = arrays.get(address)
        value = {'address': address, 'flat_indices': list(flats)}
        if previous is not None and previous != value:
            raise ValueError('one ROM frame array acquired conflicting contents')
        arrays[address] = value

    for item in context['models']:
        is_object = 'texture_animation' in item
        if not is_object and 'scene_texture_state' not in item:
            continue
        key = (item['entry'], item['segment'])
        segment = segments.get(key)
        if segment is None:
            raise ValueError('texture-sequence model is absent from the ROM')
        geometry = models.parse_segment_geometry(segment, 4)
        source_sha1 = hashlib.sha1(segment.data).hexdigest()
        found = False
        for index, run in enumerate(geometry.material_runs):
            if is_object:
                texture, status, proof = models.rom_object_animation_preview_texture(run, {}, payloads, tables, item)
            else:
                texture, status, proof = models.rom_scene_preview_texture(run, {}, payloads, item)
            if texture is None:
                # A context can apply to an object's update path even when its
                # stored list uses no eligible external texture. Do not turn it
                # into a new material binding based on its placement alone.
                continue
            found = True
            decoded = encode_frames(run, item, proof, payloads, tables)
            shape = (texture.width, texture.height, texture.format, texture.size)
            frame_refs = []
            for frame, frame_status in decoded:
                if (frame.width, frame.height, frame.format, frame.size) != shape:
                    raise ValueError('sequence frame dimensions or format changed')
                flat = frame.flat_index
                name = f'textures/flat-{flat:04d}-{frame.sha1[:12]}.png'
                image = {'flat_index': flat, 'file': name, 'width': frame.width, 'height': frame.height,
                         'format': frame.format, 'size': frame.size, 'png_sha1': frame.sha1,
                         'png_sha256': hashlib.sha256(frame.png_data).hexdigest(),
                         'payload_sha1': hashlib.sha1(payloads[flat]).hexdigest(),
                         'payload_bytes': len(payloads[flat]), 'texture_status': frame_status}
                image_key = (flat, frame.sha1)
                if image_key in images and images[image_key] != image:
                    raise ValueError('sequence image has conflicting decode provenance')
                images[image_key] = image
                files[name] = frame.png_data
                frame_refs.append({'flat_index': flat, 'file': name, 'png_sha1': frame.sha1})
            if is_object:
                selector = item['texture_animation']
                address, flats = selector['frame_array'], selector['frames']
                selection = {'kind': 'object-texture-animation', 'selector': selector,
                             'state_machine': 'func_1511A494'}
                expected_flats = [f['flat_index'] for f in proof['frames']]
            else:
                state = item['scene_texture_state']
                selector = state['bindings'][str(run.pixel.segment)]
                address, flats = selector['frame_array'], selector['frames']
                # Keep the complete sibling binding group. Scene51's offsets
                # and scene26's adjacent frames must remain correlated.
                selection = {'kind': 'primary-scene-texture-state', 'pixel_segment': run.pixel.segment,
                             'selector': selector, 'scene_state': state}
                expected_flats = [f['flat_index'] for f in proof['decoded_frames']]
            if expected_flats != flats or [f['flat_index'] for f in frame_refs] != flats:
                raise ValueError('texture frame order differs from its ROM array')
            array(address, flats)
            bindings.append({'model': [4, *key], 'source_model_sha1': source_sha1,
                             'material_run': index, 'first_face': run.first_face,
                             'source_face_count': run.face_count, 'frames': frame_refs,
                             'renderer': item['renderer'], **selection})
        if not found:
            unbound.append({'model': [4, *key], 'source_model_sha1': source_sha1,
                            'reason': 'Placement context has no eligible material run; no texture binding exported.'})
    # Retain the full original 12-byte descriptor, including unused tail bytes.
    table = []
    for row in rows:
        offset = int(row['address'], 16) - layout['game_data_vram']
        table.append({**row, 'raw_descriptor_hex': game.data[offset:offset + 12].hex()})
    object_records = [b for b in bindings if b['kind'] == 'object-texture-animation']
    scene_records = [b for b in bindings if b['kind'] == 'primary-scene-texture-state']
    summary = {'image_count': len(images), 'frame_array_count': len(arrays),
               'model_count': len({tuple(b['model']) for b in bindings}), 'material_run_count': len(bindings),
               'source_face_count': sum(b['source_face_count'] for b in bindings),
               'object_models': len({tuple(b['model']) for b in object_records}),
               'object_runs': len(object_records), 'object_faces': sum(b['source_face_count'] for b in object_records),
               'primary_scene_models': len({tuple(b['model']) for b in scene_records}),
               'primary_scene_runs': len(scene_records), 'primary_scene_faces': sum(b['source_face_count'] for b in scene_records),
               'pixels': sum(i['width'] * i['height'] for i in images.values()),
               'unbound_context_count': len(unbound)}
    manifest = {'schema_version': 1, 'family': 'rom-scene-object-texture-sequences',
                'normalized_sha1': digest, 'scope': SCOPE, 'capture_inputs': [], 'summary': summary,
                'images': sorted(images.values(), key=lambda r: (r['flat_index'], r['png_sha1'])),
                'frame_arrays': sorted(arrays.values(), key=lambda r: r['address']),
                'bindings': bindings, 'unbound_contexts': unbound,
                'object_animation_table': table, 'object_state_machine': sequence_state.description(),
                'evidence': {'object_consumers': context['consumers'],
                    'animation_consumers': [{'address': f'0x{a:08X}', 'bytes': n, 'sha1': h} for a, n, h in animation.CONSUMERS],
                    'animation_table': {'address': f'0x{animation.TABLE:08X}', 'bytes': animation.TABLE_SIZE, 'sha1': animation.TABLE_SHA1},
                    'scene_consumers': [{'address': f'0x{a:08X}', 'bytes': n, 'sha1': h} for a, n, h in scene_bindings.CONSUMERS],
                    'scene_tables': [{'address': f'0x{a:08X}', 'bytes': n, 'sha1': h} for a, (n, h) in scene_bindings.DATA.items()]}}
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    return manifest, files


def export(output, rom_argument=None, *, verify=False):
    manifest, files = build_export(rom_argument)
    if verify:
        for name, expected in files.items():
            if (output / name).read_bytes() != expected:
                raise ValueError(f'texture-sequence output differs from ROM: {name}')
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
    parser.add_argument('--output', type=Path, default=models.ROOT / 'build/assets/models/texture-sequences')
    parser.add_argument('--verify', action='store_true', help='rederive and compare existing output without writing')
    args = parser.parse_args(argv)
    try:
        manifest = export(args.output.resolve(), args.rom, verify=args.verify)
    except (OSError, ValueError) as error:
        parser.error(str(error))
    summary = manifest['summary']
    print(f"{'Verified' if args.verify else 'Extracted'} {summary['image_count']} texture frames for "
          f"{summary['model_count']} models/{summary['material_run_count']} runs: {args.output / 'manifest.json'}")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
