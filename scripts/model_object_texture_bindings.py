"""Checked ROM texture selectors for ordinary placed-object inspection states."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import model_object_materials as objects
    from scripts.model_object_texture_animation import checked
except ModuleNotFoundError:
    import model_object_materials as objects
    from model_object_texture_animation import checked

CONSUMERS = (
    (0x1511A410, 132, '058498eb31b8ec9894eb891adbed369a2fbd0a7a'),
    (0x15113E54, 508, '0f7af2433892c364923128e69e707c3178eb2260'),
)
UPDATE_FUNCTIONS = {24: 0x150DE458, 37: 0x150C4E9C}
PAIR_TABLE = 0x80090204
PAIR_SHA1 = '3f02bf93cf3dd80ad397b01bc25e4a823608403c'


def binding_table(code, code_base, data, data_base):
    # Includes the loader, ordinary renderer, both updaters and every caller
    # of the segment registry. No runtime memory or capture is an input.
    objects.verify_consumers(code, code_base, data)
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError('object texture binding consumer changed')
    for index, function in UPDATE_FUNCTIONS.items():
        if checked(data, data_base, 0x80088C90 + index * 12, 12) != struct.pack('>3I', function, 0, 0):
            raise ValueError('object texture binding update dispatch changed')
    pair = checked(data, data_base, PAIR_TABLE, 8)
    if hashlib.sha1(pair).hexdigest() != PAIR_SHA1:
        raise ValueError('object texture binding pair table changed')
    return struct.unpack('>2I', pair)


def placement_bindings(placements, flats):
    result = {}
    for scene in placements['scenes']:
        if scene['bank_index'] != 11:
            continue
        for record in scene['records']:
            source = record['model_source']
            if (record['dispatch_kind'] not in (1, 2)
                    or record['model_resolution_status'] != 'resolved-bank-04-segment'
                    or source != [4, scene['scene_index'], record['dispatch_index']]
                    or bytes.fromhex(record['bytes_3c_3f'])[0] & 2):
                continue
            update = int(record['word_14'], 16)
            if update == 37:
                # Loader +0x73 = 4; the updater tests its low two bits.
                # Values 0 and 3 also clear UV scroll, so these are the two
                # stationary texture variants, not an animated sequence.
                selector = {'object_offset': '0x73', 'mask': 3, 'loader_value': 4,
                            'selected_value': 0, 'stationary_values': [0, 3]}
                bindings = {'4': {'pixel_segment': 4, 'palette_segment': 5,
                                 'flats': [705, 448], 'selected_index': 0}}
            elif update == 24 and record['dispatch_index'] == 12:
                # Loader +0x7C = 0; updater indexes two words at a stride of
                # eight. Only this row is reviewed; other runtime values are
                # deliberately not advertised as proven variants.
                selector = {'object_offset': '0x7C', 'loader_value': 0,
                            'selected_value': 0, 'table_address': f'0x{PAIR_TABLE:08X}',
                            'table_sha1': PAIR_SHA1, 'row_stride': 8}
                bindings = {str(4 + i * 2): {'pixel_segment': 4 + i * 2,
                    'palette_segment': 5 + i * 2, 'flats': [flat], 'selected_index': 0}
                    for i, flat in enumerate(flats)}
            else:
                continue
            key = tuple(source)
            proof = {'update_function': f'func_{UPDATE_FUNCTIONS[update]:08X}',
                     'selector': selector, 'bindings': bindings,
                     'palette_tail_bytes': 512,
                     'preview_policy': 'ROM loader selector preset; not a sampled gameplay state',
                     'scope': 'Stored geometry and UVs; later scripts, visibility, lighting and native appearance unresolved.'}
            if key in result and {k: v for k, v in result[key].items() if k != 'placements'} != proof:
                raise ValueError('object texture binding has conflicting placements')
            result.setdefault(key, {**proof, 'placements': []})['placements'].append(
                {'scene': scene['scene_index'], 'record': record['index'], 'sha1': record['sha1']})
    return result
