"""Source-only geometry for the five embedded type55/85 display-list variants.

No indexed bank identity, native material, object transform or activation is
invented. This module has no exporter/inspection imports and performs no writes.
"""
from __future__ import annotations

import hashlib
import json
import struct

CONSUMERS = (
    (0x151674F8, 1392, '1a4cc2434666765a39feb16096d26a83d4b8fcc3'),
    (0x151580B0, 296, '245f256fa6f56f8569af3c594f97fec803883e8f'),
    (0x151582C8, 708, 'fbfe9a770dc1694858e8e48fc9e202480daca985'),
)
SELECTOR_TABLE_ADDRESS = 0x8008AFB8
DESCRIPTOR_ADDRESSES = {55: 0x8008BFD4, 85: 0x8008C5EC}
# Pointer-table order, deliberately not ascending display-list/vertex address.
VARIANTS = (
    (0x8008AE60, 0x800A6080, 5, 6),
    (0x8008AEA8, 0x800A60D0, 4, 4),
    (0x8008AF38, 0x800A6170, 5, 6),
    (0x8008AF80, 0x800A61C0, 4, 4),
    (0x8008AEE0, 0x800A6110, 6, 8),
)
SCOPE = ('One selected ROM game-data geometry source shared by object types55 and85. '
         'Native local positions, ordered triangles and all vertex RGBA bytes are preserved. '
         'The five known pointer-table entries are source variants, not proof of five '
         'active effects. No effect name, native instance, placement, activation or timeline is inferred.')
DIAGNOSTIC = ('No glTF material, normals or normalized UVs are assigned. The viewer default '
              'material is diagnostic and normally treats alpha as opaque. COLOR_0 preserves '
              'the source bytes, not a reconstructed native material result. Raw flags and '
              'signed ST remain in the source vertex file and manifest. Runtime matrix, '
              'combiner, OtherMode, primitive/environment colour, lighting and texture '
              'state are not simulated.')
DATA_SPANS = (
    (0x8008AFB8, bytes.fromhex(
        '8008ae608008aea88008af388008af808008aee0')),
    (0x8008BFD4, bytes.fromhex(
        '1515822400000000151582c8000000008008add0000000000000000015158b3c'
        '000000008008adf015158aa415158ad001000000')),
    (0x8008C5EC, bytes.fromhex(
        '1515822400000000151582c8000000008008add0000000000000000015158b3c'
        '000000008008adf015158aa415158ad001000000')),
    (0x8008AE60, bytes.fromhex(
        'e7000000000000000100500a800a608005000204000000000500040600000000'
        '0500060200000000050208040000000005040806000000000506080200000000'
        'df00000000000000')),
    (0x8008AEA8, bytes.fromhex(
        'e70000000000000001004008800a60d005000204000000000500060200000000'
        '05020604000000000504060000000000df00000000000000')),
    (0x8008AF38, bytes.fromhex(
        'e7000000000000000100500a800a617005000204000000000500040600000000'
        '0500060200000000050208040000000005040806000000000506080200000000'
        'df00000000000000')),
    (0x8008AF80, bytes.fromhex(
        'e70000000000000001004008800a61c005000204000000000500060200000000'
        '05020604000000000504060000000000df00000000000000')),
    (0x8008AEE0, bytes.fromhex(
        'e7000000000000000100600c800a61100500020a0000000005000a0600000000'
        '05000608000000000500080200000000050a02040000000005060a0400000000'
        '05080604000000000502080400000000df00000000000000')),
    (0x800A6080, bytes.fromhex(
        '0000ff81ff01000000000000ffff00ff000000190000000000000000c8c800ff'
        'ffeafff40000000000000000a05014ff0016fff40000000000000000648212ff'
        '0000003300ff000000000000804000ff')),
    (0x800A60D0, bytes.fromhex(
        '00000019ff01000000000000c8aa14ffffeafff4ff01000000000000802008ff'
        '0016fff4ff01000000000000646400ff0000000000ff000000000000804000ff')),
    (0x800A6170, bytes.fromhex(
        '0000ff81ff01000000000000fc5205ff000000190000000000000000fe8d30ff'
        'ffeafff40000000000000000f0621cff0016fff40000000000000000f95b14ff'
        '0000003300ff000000000000852900ff')),
    (0x800A61C0, bytes.fromhex(
        '00000019ff01000000000000f85814ffffeafff4ff01000000000000c63e03ff'
        '0016fff4ff01000000000000fe8f3dff0000000000ff000000000000fc5205ff')),
    (0x800A6110, bytes.fromhex(
        '000000ff0000000000000000ff00004000ff00000000000000000000ff000040'
        '0000ff010000000000000000ff000040ff0100000000000000000000ff000040'
        '0000000000ff000000000000ff00004000000000ff01000000000000ff000040')),
    (0x8008ADD0, bytes.fromhex('e700000000000000da38000380089470d700000280008000df00000000000000')),
    (0x8008ADF0, bytes.fromhex('d700000000000000df00000000000000')),
)


def _selector(value):
    if type(value) is not int or not 0 <= value < len(VARIANTS):
        raise ValueError('embedded type55 selector must be an integer from0 through4')
    return value


def name(selector):
    selector = _selector(selector)
    return f'embedded-type55-{selector}-{VARIANTS[selector][1]:08x}'


def _checked(blob, base, address, size):
    at = address - base
    if at < 0 or at + size > len(blob):
        raise ValueError(f'embedded type55 source outside image at0x{address:08X}')
    return blob[at:at + size]


def _decode(selector):
    """Decode only the exact source records; no runtime vertex cache is assumed."""
    selector = _selector(selector)
    source = dict(DATA_SPANS)
    list_address, vertex_address, count, triangle_count = VARIANTS[selector]
    table = struct.unpack('>5I', source[SELECTOR_TABLE_ADDRESS])
    if table[selector] != list_address:
        raise ValueError('embedded type55 source table disagrees with selector')
    display, raw = source[list_address], source[vertex_address]
    if len(display) != 8 * (triangle_count + 3) or len(raw) != count * 16:
        raise ValueError('embedded type55 source extent changed')
    if display[:8] != bytes.fromhex('e700000000000000'):
        raise ValueError('embedded type55 pipe sync changed')
    load, pointer = struct.unpack_from('>II', display, 8)
    if load != (0x01000000 | count << 12 | count << 1) or pointer != vertex_address:
        raise ValueError('embedded type55 vertex load changed')
    vertices = []
    for index, record in enumerate(struct.iter_unpack('>hhhHhhBBBB', raw)):
        vertices.append({'index': index, 'source_address': f'0x{vertex_address + 16 * index:08X}',
                         'position': list(record[:3]), 'flag': record[3],
                         'st_s16': list(record[4:6]), 'rgba_u8': list(record[6:])})
    triangles, commands = [], []
    for offset in range(16, len(display) - 8, 8):
        word, argument = struct.unpack_from('>II', display, offset)
        indices = [(word >> shift) & 255 for shift in (16, 8, 0)]
        if word >> 24 != 5 or argument or any(i & 1 or i // 2 >= count for i in indices):
            raise ValueError('embedded type55 ordered triangle changed')
        triangles.append([i // 2 for i in indices])
        commands.append({'source_address': f'0x{list_address + offset:08X}',
                         'command': f'0x{word:08X}', 'argument': '0x00000000'})
    if display[-8:] != bytes.fromhex('df00000000000000'):
        raise ValueError('embedded type55 list termination changed')
    return {
        'schema_version': 1, 'family': 'rom-embedded-effect-geometry', 'scope': SCOPE,
        'source_kind': 'game-data', 'indexed_model_bank': None, 'object_types': [55, 85],
        'selector': selector, 'selector_table_address': f'0x{SELECTOR_TABLE_ADDRESS:08X}',
        'source_vertex_address': f'0x{vertex_address:08X}',
        'source_list_address': f'0x{list_address:08X}',
        'vertex_count': count, 'triangle_count': triangle_count,
        'vertices': vertices, 'triangles': triangles,
        'vertex_load_command': f'0x{load:08X}', 'triangle_commands': commands,
        'vertex_bytes_sha1': hashlib.sha1(raw).hexdigest(),
        'display_list_bytes_sha1': hashlib.sha1(display).hexdigest(),
        'source_reconstruction': f'All{len(raw)} vertex bytes and all{len(display)} display-list bytes preserved exactly.',
        'consumers': [{'address': f'0x{a:08X}', 'size': n, 'sha1': h} for a, n, h in CONSUMERS],
        'data_spans': [{'address': f'0x{a:08X}', 'size': len(b), 'hex': b.hex(),
                        'sha1': hashlib.sha1(b).hexdigest()} for a, b in DATA_SPANS],
        'constructor': {'function': 'func_151580B0', 'parameter_copy': '0x15158128..0x15158134',
                        'source_bytes': 68, 'object_destination_offset': '0x10',
                        'caller_selector_offset': '0x06', 'object_selector_offset': '0x16',
                        'object_type': 'Fourth argument low byte zero selects55; nonzero selects85.',
                        'selector_scope': 'Renderer reads an unsigned byte without a bounds check. Export supports only the five proven source entries; no caller activation is inferred.'},
        'render_state': {
            'dispatcher': 'func_151674F8', 'renderer': 'func_151582C8',
            'descriptors': {str(t): f'0x{a:08X}' for t, a in DESCRIPTOR_ADDRESSES.items()},
            'setup_display_list': '0x8008ADD0', 'teardown_display_list': '0x8008ADF0',
            'geometry_submission': '0x15158550..0x15158574',
            'matrix_submission': 'Runtime object+0x58+64*D_800BE9C0 (frame-buffer index); not baked.',
            'material_status': 'caller-and-runtime-dependent-not-reconstructed',
            'diagnostic_export_policy': DIAGNOSTIC,
        },
        'runtime_instancing': {'policy': 'One source primitive at native local coordinates; no runtime object or world transform is exported.'},
    }


def describe_geometry(code, code_base, data, data_base, selector):
    _selector(selector)
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(_checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'embedded type55 consumer changed at0x{address:08X}')
    for address, expected in DATA_SPANS:
        if _checked(data, data_base, address, len(expected)) != expected:
            raise ValueError(f'embedded type55 data changed at0x{address:08X}')
    # These words also bind the documented constructor and list-selection ABI.
    words = {0x151580F0: 0x24040055, 0x151580F4: 0x24040037,
             0x15158128: 0x26840010, 0x1515812C: 0x02002825,
             0x15158130: 0x0C008BB0, 0x15158134: 0x24060044,
             0x15158550: 0x3C0FDE00, 0x15158554: 0xAC8F0000,
             0x15158558: 0x92180016, 0x1515855C: 0x3C088009,
             0x15158564: 0x0018C880, 0x15158568: 0x01194021,
             0x1515856C: 0x8D08AFB8, 0x15158574: 0xAC880004}
    for address, expected in words.items():
        if _checked(code, code_base, address, 4) != struct.pack('>I', expected):
            raise ValueError('embedded type55 constructor or list submission changed')
    return _decode(selector)


def geometry_files(manifest):
    """Return deterministic source and glTF files, accepting only derived geometry."""
    expected = _decode(manifest.get('selector'))
    if any(manifest.get(key) != value for key, value in expected.items()):
        raise ValueError('embedded type55 manifest differs from pinned source')
    selector = manifest['selector']
    stem = name(selector)
    list_address, vertex_address, count, triangle_count = VARIANTS[selector]
    positions = [v['position'] for v in manifest['vertices']]
    binary = b''.join(struct.pack('<3f', *p) for p in positions)
    colors_offset = len(binary)
    binary += bytes(c for v in manifest['vertices'] for c in v['rgba_u8'])
    index_offset = len(binary)
    indices = [i for t in manifest['triangles'] for i in t]
    binary += struct.pack(f'<{len(indices)}H', *indices)
    binary += b'\0' * (-len(binary) % 4)
    document = {
        'asset': {'version': '2.0', 'generator': 'Conker US embedded geometry diagnostic'},
        'scene': 0, 'scenes': [{'nodes': [0]}], 'nodes': [{'mesh': 0, 'name': stem}],
        'meshes': [{'name': stem, 'primitives': [{'attributes': {'POSITION': 0, 'COLOR_0': 1},
                                               'indices': 2, 'mode': 4}]}],
        'buffers': [{'uri': stem + '.bin', 'byteLength': len(binary)}],
        'bufferViews': [
            {'buffer': 0, 'byteOffset': 0, 'byteLength': colors_offset, 'target': 34962},
            {'buffer': 0, 'byteOffset': colors_offset, 'byteLength': index_offset - colors_offset, 'target': 34962},
            {'buffer': 0, 'byteOffset': index_offset, 'byteLength': len(indices) * 2, 'target': 34963}],
        'accessors': [
            {'bufferView': 0, 'componentType': 5126, 'count': count, 'type': 'VEC3',
             'min': [min(p[i] for p in positions) for i in range(3)],
             'max': [max(p[i] for p in positions) for i in range(3)]},
            {'bufferView': 1, 'componentType': 5121, 'count': count, 'type': 'VEC4', 'normalized': True},
            {'bufferView': 2, 'componentType': 5123, 'count': triangle_count * 3, 'type': 'SCALAR'}],
        'extras': {'sourceKind': 'embedded-game-data', 'sourceAddress': manifest['source_vertex_address'],
                   'sourceVertexSha1': manifest['vertex_bytes_sha1'],
                   'sourceListAddress': manifest['source_list_address'], 'sourceSelector': selector,
                   'normalizedRomSha1': manifest.get('normalized_sha1'), 'scope': SCOPE,
                   'materialStatus': 'caller-and-runtime-dependent-not-reconstructed',
                   'diagnosticMaterialPolicy': DIAGNOSTIC, 'nativeRenderState': manifest['render_state']},
    }
    source = dict(DATA_SPANS)
    files = {'geometry/' + stem + '.bin': binary,
             'geometry/' + stem + '.gltf': (json.dumps(document, indent=2) + '\n').encode()}
    for kind, address in [('vertices', vertex_address), ('display-list', list_address),
                          ('selector-table', SELECTOR_TABLE_ADDRESS),
                          ('descriptor-type55', DESCRIPTOR_ADDRESSES[55]),
                          ('descriptor-type85', DESCRIPTOR_ADDRESSES[85]),
                          ('setup-list', 0x8008ADD0), ('teardown-list', 0x8008ADF0)]:
        files[f'source/{kind}-{address:08x}.bin'] = source[address]
    return files
