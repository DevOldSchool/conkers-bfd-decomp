"""Extract guarded ROM scene vertex-color targets and bounded RGB interpolation.

Stored targets and conditional controller links are not an animation timeline.
This exporter does not change geometry, alpha, models or gallery defaults.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

try:
    from scripts import model_assets as models
except ModuleNotFoundError:
    import model_assets as models

CONSUMERS = (
    (0x15003120, 204, '3d917f11eef25bd8cf376178f84c6b2fed203180'),
    (0x150031EC, 712, 'ed48d58ffb38dab90c140a0d547dbdae13f3225a'),
    (0x150039E0, 2964, 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66'),
    (0x150127B0, 1236, '9ab76db4fe57dc8da87681f84438c89e92362269'),
    (0x15012C84, 596, '7074ea6f82d21bac0f15971befb7edb1e0e81f78'),
    (0x15113E54, 508, '0f7af2433892c364923128e69e707c3178eb2260'),
    (0x1511C638, 1268, '059855ea41f389410ea7e2230323188d6ea8cab3'),
    (0x151739B0, 688, '9b41bacec4b3981885419cc7d5185700cae3a273'),
    (0x15173C60, 48, '5caacf9686feb55261a827ff2b999b9966ddb4b2'),
)
DISPATCH_ADDRESS = 0x80088D5C
DISPATCH_BYTES = bytes.fromhex('1511c6380000000000000000')
MODEL_SHA1 = {
    (1, 0): '8e4b1cadd343a8f5f4eb1846c98909adda41e577',
    (1, 11): 'a3d8bed02f4ef2346aa7c8c567ed13989295bf07',
    (4, 0): '15bc17e0a6b647b1caaecac2b9cea1cc226cb521',
    (7, 9): 'fb4228093a63353e7a7f484441dbced5c88bd39c',
    (28, 0): 'c5847056b7dec44a298a6b4de6884787477d0877',
}
# Exact bank-11 source records: scene, record, model segment, target selector, SHA-1.
PLACEMENTS = (
    (4, 6, 18, 3, '22162d585d4e215cad71dd229ac06c82d6c612b6'),
    (4, 9, 17, 2, 'c79df0121f41a27001eb0433fdf38843b2248d26'),
    (4, 12, 16, 1, '633dd26950bb59af05903ab2e41dbca1d510258c'),
    (4, 15, 15, 0, '0afdb6bb7a29d658beba57249025b0c3499c0f40'),
    (4, 19, 23, 0, 'dc21ea80713c81b4e2576ecc7790cc9fe4d9d96c'),
    (28, 0, 17, 0, '0332f58185a7b11318a8b1948b6988388fbacd8d'),
    (28, 2, 18, 1, '58c5e5e4fe72716ec47002fa0ef723effed484df'),
    (28, 4, 19, 2, 'b028474bdd6b7a7f25d1e8f1414dd8a4d23bbd6c'),
    (28, 6, 20, 3, 'f55b757e62d683df4e7589a1222adeea8756bc3a'),
    (28, 22, 21, 4, '121bce7e9e39b2f2573dc2fd2215a304e60632fd'),
    (28, 24, 22, 5, 'cf4518034fa2a34a1ec27564b7a6f173c06eca54'),
)
SCOPE = ('Ordered ROM RGB targets, original vertex indices and stored source RGBA; '
         'conditional controller metadata only. Runtime base snapshots, activation, '
         'timeline, clock, visibility, lighting and native raster parity remain unobserved.')


def checked(raw, base, address, size):
    offset = address - base
    if offset < 0 or offset + size > len(raw):
        raise ValueError('vertex-color evidence exceeds ROM region')
    return raw[offset:offset + size]


def integer(value, low, high, name):
    if type(value) is not int or not low <= value <= high:
        raise ValueError(f'{name} must be an integer in {low}..{high}')
    return value


def channels(values, count, name):
    if not isinstance(values, (list, tuple)) or len(values) != count:
        raise ValueError(f'{name} requires {count} channels')
    return tuple(integer(value, 0, 255, name) for value in values)


def interpolate_rgba(base_rgba, target_rgb, factor):
    """Mirror RGB stores for explicit byte inputs and factor 0..255.

    The native arithmetic shift rounds negative products downward. Factor255
    is intentionally not normalized to 1.0; no alpha store occurs in this path.
    Inputs are supplied by the caller, not inferred current runtime state.
    """
    base = channels(base_rgba, 4, 'base_rgba')
    target = channels(target_rgb, 3, 'target_rgb')
    integer(factor, 0, 255, 'factor')
    return tuple(base[i] + (((target[i] - base[i]) * factor) >> 8)
                 for i in range(3)) + (base[3],)


def verify_consumers(code, code_base, data, data_base):
    consumers = []
    for address, size, expected in CONSUMERS:
        raw = checked(code, code_base, address, size)
        if hashlib.sha1(raw).hexdigest() != expected:
            raise ValueError(f'vertex-color consumer changed: 0x{address:08X}')
        consumers.append({'address': f'0x{address:08X}', 'size': size, 'sha1': expected})
    if checked(data, data_base, DISPATCH_ADDRESS, len(DISPATCH_BYTES)) != DISPATCH_BYTES:
        raise ValueError('vertex-color updater dispatch changed')
    return consumers


def encode_descriptor_arrays(record):
    """Reconstruct ordered index, target and stored source arrays from JSON."""
    entries = record['vertices']
    if type(record['vertex_count']) is not int or record['vertex_count'] != len(entries):
        raise ValueError('vertex-color reference count changed')
    indices, targets, sources = bytearray(), bytearray(), bytearray()
    for entry in entries:
        index = integer(entry['vertex_index'], 0, 65535, 'vertex_index')
        indices.extend(struct.pack('>H', index))
        targets.extend(channels(entry['target_rgb'], 3, 'target_rgb'))
        sources.extend(channels(entry['stored_source_rgba'], 4, 'stored_source_rgba'))
    return bytes(indices), bytes(targets), bytes(sources)


def decode_model(payload, expected_sha1):
    if hashlib.sha1(payload).hexdigest() != expected_sha1:
        raise ValueError('vertex-color source model changed')
    geometry = models.parse_model_geometry(payload)
    if not geometry.vertex_color_animation_descriptors:
        raise ValueError('vertex-color source has no target descriptors')
    descriptors, reconstructed = [], bytearray()
    for index, descriptor in enumerate(geometry.vertex_color_animation_descriptors):
        count = descriptor.vertex_count
        indices_raw = payload[descriptor.vertex_index_offset:descriptor.vertex_index_offset + count * 2]
        target_raw = payload[descriptor.color_data_offset:descriptor.color_data_offset + count * 3]
        indices = struct.unpack(f'>{count}H', indices_raw)
        entries, source_raw = [], bytearray()
        for offset, vertex_index in enumerate(indices):
            rgba = payload[0x28 + vertex_index * 16 + 12:0x28 + vertex_index * 16 + 16]
            if tuple(rgba) != geometry.vertices[vertex_index].color:
                raise ValueError('vertex-color independent source RGBA check failed')
            source_raw.extend(rgba)
            entries.append({'vertex_index': vertex_index, 'stored_source_rgba': list(rgba),
                            'target_rgb': list(target_raw[offset * 3:offset * 3 + 3])})
        record = {'target_index': index, 'color_data_offset': descriptor.color_data_offset,
                  'vertex_index_offset': descriptor.vertex_index_offset, 'vertex_count': count,
                  'indices_sha256': hashlib.sha256(indices_raw).hexdigest(),
                  'target_rgb_sha256': hashlib.sha256(target_raw).hexdigest(),
                  'stored_source_rgba_sha256': hashlib.sha256(source_raw).hexdigest(),
                  'changed_rgb_reference_count': sum(v['stored_source_rgba'][:3] != v['target_rgb'] for v in entries),
                  'vertices': entries}
        # Verify after JSON transport, independently repacking all native arrays.
        if encode_descriptor_arrays(json.loads(json.dumps(record))) != (indices_raw, target_raw, bytes(source_raw)):
            raise ValueError('vertex-color arrays failed byte reconstruction')
        reconstructed.extend(struct.pack('>III', descriptor.color_data_offset,
                                         descriptor.vertex_index_offset, count))
        descriptors.append(record)
    table_offset = geometry.vertex_color_animation_offset
    table_size = geometry.vertex_color_animation_table_size
    table = payload[table_offset:table_offset + table_size]
    terminator = struct.unpack('>III', table[-12:])
    reconstructed.extend(struct.pack('>III', *terminator))
    if reconstructed != table:
        raise ValueError('vertex-color descriptor table failed byte reconstruction')
    return {'source_model_sha1': expected_sha1, 'source_model_bytes': len(payload),
            'source_vertex_count': len(geometry.vertices), 'source_face_count': len(geometry.faces),
            'descriptor_table': {'offset': table_offset, 'size': table_size,
                                 'sha256': hashlib.sha256(table).hexdigest(),
                                 'terminator_words': list(terminator)},
            'descriptor_count': len(descriptors),
            'vertex_reference_count': sum(d['vertex_count'] for d in descriptors),
            'targets': descriptors}


def controller_links(placements):
    records = {(scene['scene_index'], record['index']): record
               for scene in placements['scenes'] if scene['bank_index'] == 11
               for record in scene['records']}
    result = []
    for scene, index, segment, selector, expected in PLACEMENTS:
        record = records.get((scene, index))
        if record is None or hashlib.sha1(bytes.fromhex(record['raw_hex'])).hexdigest() != expected:
            raise ValueError('vertex-color controller placement changed')
        if (record['model_source'] != [4, scene, segment]
                or int(record['word_14'], 16) != 17 or int(record['word_18'], 16) != selector):
            raise ValueError('vertex-color controller placement interpretation changed')
        result.append({'scene': scene, 'placement_record': index, 'placement_sha1': expected,
                       'controller_model': record['model_source'], 'updater_index': 17,
                       'target_model': [4, scene, 0], 'target_index': selector,
                       'placement_word_18': record['word_18'],
                       'initial_inactive_byte_34': bytes.fromhex(record['raw_hex'])[0x34]})
    return result


def build_export(rom_argument=None):
    rom_path, layout = models.resolve_rom('us', rom_argument)
    rom, _ = models.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout['normalized_sha1']:
        raise ValueError('vertex-color targets require the validated US ROM')
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    consumers = verify_consumers(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    bank = next(b for b in models.parse_asset_banks(rom, layout['asset_table']) if b.index == 4)
    entries = {entry.index: entry for entry in models.parse_asset_entries(rom, bank)}
    bundles = {}
    for index in sorted({key[0] for key in MODEL_SHA1}):
        entry = entries[index]
        payload = rom[entry.start:entry.end]
        if entry.compressed:
            payload = models.decode_rzip_chunk(payload).data
        bundles[index] = {segment.index: segment.data for segment in models.parse_model_bundle(payload)}
    records = [{'model': [4, entry, segment], **decode_model(bundles[entry][segment], expected)}
               for (entry, segment), expected in MODEL_SHA1.items()]
    placements, _ = models.load_object_placement_manifest('us', rom_argument, include_files=False)
    links = controller_links(placements)
    record_map = {tuple(record['model']): record for record in records}
    for link in links:
        if not 0 <= link['target_index'] < record_map[tuple(link['target_model'])]['descriptor_count']:
            raise ValueError('vertex-color controller selector exceeds model targets')
    manifest = {
        'schema_version': 1, 'family': 'rom-scene-vertex-color-targets',
        'normalized_sha1': digest, 'scope': SCOPE, 'capture_inputs': [],
        'consumers': consumers,
        'data_spans': [{'address': f'0x{DISPATCH_ADDRESS:08X}', 'hex': DISPATCH_BYTES.hex()}],
        'model_count': len(records), 'descriptor_count': sum(r['descriptor_count'] for r in records),
        'vertex_reference_count': sum(r['vertex_reference_count'] for r in records),
        'changed_rgb_reference_count': sum(t['changed_rgb_reference_count'] for r in records for t in r['targets']),
        'models': records, 'controller_links': links,
        'interpolation': {'consumer': 'func_151739B0', 'formula': 'base + (((target - base) * factor) >> 8)',
                          'rounding': 'signed arithmetic right shift; negative products round downward',
                          'bounded_factor_domain': [0, 255], 'written_vertex_offsets': [12, 13, 14],
                          'alpha': 'unchanged at vertex+15',
                          'factor255_is_exact_target': False,
                          'descriptor_order': 'Source order retained; selector255 requests all descriptors.',
                          'base': 'Runtime snapshot selected by scene flags; stored_source_rgba records only original ROM values.'},
        'conditional_controller': {
            'updater': 'func_1511C638', 'terrain_wrapper': 'func_15173C60',
            'selector': 'placement+0x18 -> object+0x3C; value255 suppresses this updater call',
            'initial_fields': {'object+0x73': 4, 'object+0x80': 0},
            'reset_branch': 'When object+0x73 low two bits equal1, invoke factor0 for the selected target.',
            'rising_branch': 'At1511CAA4..1511CAE8, object+0x80 += 30 * s32[800BE9E4]; clamp signed values>=255 to255, then invoke selected target.',
            'limits': 'Branch admission and preceding state transitions are not modeled; delta range, timing, activation and visibility are not inferred.'},
        'verification': {'descriptor_tables': 'byte-identical reconstruction',
                         'ordered_indices_and_rgb': 'byte-identical reconstruction after JSON round trip',
                         'stored_source_rgba': 'independent raw vertex-byte comparison',
                         'geometry_policy': 'No source vertices, faces, UVs, textures or existing exports are rewritten.'},
    }
    return manifest, {'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode()}


def export(output, rom_argument=None, *, verify=False):
    manifest, files = build_export(rom_argument)
    if verify:
        for name, expected in files.items():
            if (output / name).read_bytes() != expected:
                raise ValueError(f'vertex-color output differs from ROM: {name}')
    else:
        output.mkdir(parents=True, exist_ok=False)
        for name, content in files.items():
            (output / name).write_bytes(content)
    return manifest


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--output', type=Path, default=models.ROOT / 'build/assets/models/vertex-color-targets')
    parser.add_argument('--verify', action='store_true', help='rederive and compare an existing export without writing')
    args = parser.parse_args(argv)
    try:
        result = export(args.output.resolve(), args.rom, verify=args.verify)
    except (OSError, ValueError) as error:
        parser.error(str(error))
    print(f"{'Verified' if args.verify else 'Extracted'} vertex-color targets: {result['model_count']} models, "
          f"{result['descriptor_count']} targets, {result['vertex_reference_count']} references; {args.output / 'manifest.json'}")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
