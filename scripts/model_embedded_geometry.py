"""Export a proven embedded effect primitive without inventing a runtime instance.

This source lives in the game data image, outside the indexed model banks.
The glTF is diagnostic geometry: its default material is not native appearance.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
import tempfile
from pathlib import Path

try:
    from scripts import model_assets as models
    from scripts.model_inspection import pack_glb
except ModuleNotFoundError:
    import model_assets as models
    from model_inspection import pack_glb

CONSUMERS = (
    (0x151674F8, 1392, '1a4cc2434666765a39feb16096d26a83d4b8fcc3'),
    (0x151875E0, 920, '4a3d8d5343c1a47014ffc4c7551897e3eeb5c6c3'),
    (0x15187978, 288, '8cc428786a1ddea876f0cd501c799dc24f977f6f'),
    (0x15187A98, 724, '57240400027c3c203cd122ec5387ae58336fed56'),
    (0x15187D6C, 340, 'da3f2f65e100988423a3e91aae0221d175d5274d'),
)
VERTEX_ADDRESS = 0x8008D538
VERTEX_BYTES = bytes.fromhex(
    'fd8f00000000000000000000ffffff10'
    '0271001f0000000000000000ffffffff'
    '0271ffe1001f000000000000ffffffff'
    '0271ffe1ffe1000000000000ffffffff')
DATA_SPANS = (
    (0x8008B5E0, bytes.fromhex(
        '151879780000000015187a98000000008008d4f00000000000000000'
        '00000000000000008008d520000000000000000001000000')),
    (0x8008D4F0, bytes.fromhex(
        'd700000000000000e700000000000000fc323864ff73ffff'
        'd9fdf9ff00000000ef082caf00504a50df00000000000000')),
    (0x8008D520, bytes.fromhex('da38000380089470e700000000000000df00000000000000')),
    (VERTEX_ADDRESS, VERTEX_BYTES),
)
NAME = 'embedded-type06-8008d538'
SCOPE = ('One ROM game-data primitive, four native vertices and three ordered triangles. '
         'No effect name, runtime instance transforms, activation, timeline, '
         'complete native frame or native opacity is inferred.')
DIAGNOSTIC = ('No glTF material is assigned. The viewer default material is diagnostic '
              'and normally treats alpha as opaque; COLOR_0 preserves original vertex '
              'RGBA bytes, not the native result of primitive-alpha multiplication '
              'and RDP blending. Native transforms and other inherited geometry flags '
              'are not reconstructed.')

TYPE08_NAME = 'embedded-type08-8008cd90'
TYPE08_CONSUMERS = (
    CONSUMERS[0],
    # Complete constructor/update/draw/helper family, including padding and the
    # matched setup/adapter functions between the independent raw ASM spans.
    (0x15179FE0, 3024, '695b7d3f515a5c4ee888aba10551844fcc18f751'),
)
TYPE08_VERTICES = bytes.fromhex(
    '00070004000000002412209ffefefeff'
    'fff90004000000002008208efefefeff'
    '000000010003000022101fabfefefeff'
    '0007000e0000000023f22350fefefeff'
    'fff9000e0000000020152340fefefeff'
    '000000150004000021fa25defefefeff')
TYPE08_LIST = bytes.fromhex(
    '0100600c8008cd90'
    '05000204000000000500060200000000'
    '0508020600000000050a080600000000'
    'df00000000000000')
TYPE08_DATA = (
    (0x8008CD90, TYPE08_VERTICES),
    (0x8008CDF0, TYPE08_LIST),
    (0x8008B648, bytes.fromhex('1517a1ec000000001517a3a0000000008008ce201517a95800000000000000000000000000000000000000000000000001000000')),
    (0x8008B67C, bytes.fromhex('1517a84c000000001517a3a0000000008008ce201517a95800000000000000000000000000000000000000000000000001000000')),
    (0x8008B718, bytes.fromhex('1517a1ec000000001517a3a0000000008008ce401517a95800000000000000001517ab7c80087408000000000000000001000000')),
    (0x8008C6BC, bytes.fromhex('1517a1ec000000001517a3a0000000008008ce401517a95800000000000000001517ab7c00000000000000000000000001000000')),
    (0x8008CE20, bytes.fromhex('e700000000000000e200001c005049d8de0000008008ce60df00000000000000')),
    (0x8008CE40, bytes.fromhex('e700000000000000e200001c00504240de0000008008ce60df00000000000000')),
    (0x8008CE60, bytes.fromhex('e3000a0100000000fc121624ff2fffffe3000f0000000000d7000002ffffffffd9eef9ff00000000e3000d0100000000e300120100002000f510000007000000df00000000000000')),
    (0x80087408, bytes.fromhex('df00000000000000')),
    (0x8009060C, bytes.fromhex('00000bae00000bac8009060c02000020002c0201')),
)
TYPE08_SCOPE = ('One ROM game-data primitive shared by effect types 8, 9, 12 and 89. '
                'Six native vertices and four ordered triangles are preserved. '
                'No effect name, runtime instance, placement, scale, visibility, '
                'texture selection, animation or native appearance is inferred.')
TYPE08_DIAGNOSTIC = ('No glTF material, texture or normalized UVs are assigned. '
                    'The default viewer material is diagnostic. COLOR_0 preserves '
                    'original RGBA bytes; native alpha instead multiplies texture '
                    'alpha by runtime primitive alpha. Raw signed ST is preserved '
                    'in the source and manifest, without assuming tile state, '
                    'filtering or coordinate normalization.')


def checked(blob, base, address, size):
    offset = address - base
    if offset < 0 or offset + size > len(blob):
        raise ValueError(f'embedded geometry source outside image at0x{address:08X}')
    return blob[offset:offset + size]


def immediate_pair(code, base, first, second, *, signed=False):
    """Read the pinned LUI/ORI or LUI/ADDIU pair that builds a native word."""
    hi, = struct.unpack('>I', checked(code, base, first, 4))
    lo, = struct.unpack('>I', checked(code, base, second, 4))
    rt = (hi >> 16) & 31
    if (hi >> 26 != 15 or (hi >> 21) & 31 or lo >> 26 != (9 if signed else 13)
            or (lo >> 21) & 31 != rt or (lo >> 16) & 31 != rt):
        raise ValueError('embedded geometry immediate construction changed')
    low = lo & 0xFFFF
    if signed and low & 0x8000:
        low -= 0x10000
    return (((hi & 0xFFFF) << 16) + low) & 0xFFFFFFFF


def describe_geometry(code, code_base, data, data_base):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'embedded geometry consumer changed at0x{address:08X}')
    for address, expected in DATA_SPANS:
        if checked(data, data_base, address, len(expected)) != expected:
            raise ValueError(f'embedded geometry data changed at0x{address:08X}')
    address = immediate_pair(code, code_base, 0x15187B18, 0x15187B28, signed=True)
    load = immediate_pair(code, code_base, 0x15187CC8, 0x15187CCC)
    count, end = (load >> 12) & 0xFF, (load >> 1) & 0x7F
    if load >> 24 != 1 or count != 4 or end != count or address != VERTEX_ADDRESS:
        raise ValueError('embedded geometry vertex load changed')
    raw = checked(data, data_base, address, count * 16)
    vertices = []
    for i, record in enumerate(struct.iter_unpack('>hhhHhhBBBB', raw)):
        vertices.append({'index': i, 'source_address': f'0x{address + i * 16:08X}',
                         'position': list(record[:3]), 'flag': record[3],
                         'st_s16': list(record[4:6]), 'rgba_u8': list(record[6:])})
    if b''.join(struct.pack('>hhhHhhBBBB', *v['position'], v['flag'],
                            *v['st_s16'], *v['rgba_u8']) for v in vertices) != raw:
        raise ValueError('embedded vertices did not round-trip')
    commands, triangles = [], []
    for first in (0x15187CE0, 0x15187CF8, 0x15187D10):
        word = immediate_pair(code, code_base, first, first + 4)
        indices = [(word >> shift) & 0xFF for shift in (16, 8, 0)]
        if word >> 24 != 5 or any(i & 1 or i // 2 >= count for i in indices):
            raise ValueError('embedded triangle command changed')
        triangles.append([i // 2 for i in indices])
        commands.append({'instruction_address': f'0x{first:08X}',
                         'command': f'0x{word:08X}', 'argument': '0x00000000'})
    return {
        'schema_version': 1, 'family': 'rom-embedded-effect-geometry', 'scope': SCOPE,
        'source_kind': 'game-data', 'indexed_model_bank': None, 'object_type': 6,
        'source_vertex_address': f'0x{address:08X}', 'vertex_count': count,
        'triangle_count': len(triangles), 'vertices': vertices, 'triangles': triangles,
        'vertex_load_command': f'0x{load:08X}', 'triangle_commands': commands,
        'vertex_bytes_sha1': hashlib.sha1(raw).hexdigest(),
        'source_reconstruction': 'All64 original vertex bytes reconstructed exactly.',
        'consumers': [{'address': f'0x{a:08X}', 'size': n, 'sha1': h} for a, n, h in CONSUMERS],
        'data_spans': [{'address': f'0x{a:08X}', 'size': len(b), 'hex': b.hex(),
                        'sha1': hashlib.sha1(b).hexdigest()} for a, b in DATA_SPANS],
        'render_state': {
            'setup_display_list': '0x8008D4F0', 'teardown_display_list': '0x8008D520',
            'dispatcher': 'func_151674F8', 'setup_submission': '0x1516774C..0x1516776C',
            'texture_enabled': False,
            'combine_mode': ['0xFC323864', '0xFF73FFFF'],
            'combine_formula': models.decode_combine_mode((0xFC323864, 0xFF73FFFF)),
            'other_mode': ['0xEF082CAF', '0x00504A50'],
            'geometry_mode_clear_mask': '0x00020600',
            'cleared_geometry_modes': ['lighting', 'front-cull', 'back-cull'],
            'remaining_geometry_modes': 'Inherited; not fully specified by this setup.',
            'primitive_color': {'rgb': [255, 255, 255],
                                'alpha': 'Runtime ((remaining * 255) / lifetime) &255; not baked.',
                                'command': '0xFA000100', 'write_address': '0x15187C20..0x15187C88'},
            'diagnostic_export_policy': DIAGNOSTIC,
        },
        'runtime_instancing': {'draw_loop_count': 12, 'effect_record_stride': 160,
                               'policy': 'Primitive exported once at native local coordinates; runtime matrices, random initializer state and primitive alpha omitted.'},
    }


def geometry_files(manifest):
    """Encode source-local positions, byte RGBA and ordered indices only."""
    vertices, triangles = manifest['vertices'], manifest['triangles']
    positions = [v['position'] for v in vertices]
    raw = b''.join(struct.pack('>hhhHhhBBBB', *v['position'], v['flag'],
                               *v['st_s16'], *v['rgba_u8']) for v in vertices)
    if raw != VERTEX_BYTES:
        raise ValueError('embedded geometry vertices differ from pinned source')
    binary = b''.join(struct.pack('<3f', *p) for p in positions)
    colors_offset = len(binary)
    binary += bytes(c for v in vertices for c in v['rgba_u8'])
    index_offset = len(binary)
    binary += struct.pack('<9H', *(i for t in triangles for i in t))
    binary += b'\0' * (-len(binary) % 4)
    document = {
        'asset': {'version': '2.0', 'generator': 'Conker US embedded geometry diagnostic'},
        'scene': 0, 'scenes': [{'nodes': [0]}], 'nodes': [{'mesh': 0, 'name': NAME}],
        'meshes': [{'name': NAME, 'primitives': [{'attributes': {'POSITION': 0, 'COLOR_0': 1}, 'indices': 2, 'mode': 4}]}],
        'buffers': [{'uri': NAME + '.bin', 'byteLength': len(binary)}],
        'bufferViews': [
            {'buffer': 0, 'byteOffset': 0, 'byteLength': colors_offset, 'target': 34962},
            {'buffer': 0, 'byteOffset': colors_offset, 'byteLength': index_offset - colors_offset, 'target': 34962},
            {'buffer': 0, 'byteOffset': index_offset, 'byteLength': 18, 'target': 34963}],
        'accessors': [
            {'bufferView': 0, 'componentType': 5126, 'count': 4, 'type': 'VEC3',
             'min': [min(p[i] for p in positions) for i in range(3)],
             'max': [max(p[i] for p in positions) for i in range(3)]},
            {'bufferView': 1, 'componentType': 5121, 'count': 4, 'type': 'VEC4', 'normalized': True},
            {'bufferView': 2, 'componentType': 5123, 'count': 9, 'type': 'SCALAR'}],
        'extras': {'sourceKind': 'embedded-game-data', 'sourceAddress': manifest['source_vertex_address'],
                   'sourceVertexSha1': manifest['vertex_bytes_sha1'],
                   'normalizedRomSha1': manifest.get('normalized_sha1'),
                   'scope': SCOPE, 'materialStatus': 'native-setup-known-runtime-alpha-unresolved',
                   'diagnosticMaterialPolicy': DIAGNOSTIC, 'nativeRenderState': manifest['render_state']},
    }
    return {'source/vertices-8008d538.bin': raw,
            'geometry/' + NAME + '.bin': binary,
            'geometry/' + NAME + '.gltf': (json.dumps(document, indent=2) + '\n').encode()}


def describe_type08_geometry(code, code_base, data, data_base):
    """Follow the shared renderer's pinned display-list submission."""
    for address, size, expected in TYPE08_CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'embedded geometry consumer changed at0x{address:08X}')
    for address, expected in TYPE08_DATA:
        if checked(data, data_base, address, len(expected)) != expected:
            raise ValueError(f'embedded geometry data changed at0x{address:08X}')
    list_address = immediate_pair(code, code_base, 0x1517A618, 0x1517A61C, signed=True)
    if list_address != 0x8008CDF0:
        raise ValueError('embedded geometry list address changed')
    for address, expected in ((0x1517A620, 0x3C0ADE00),
                              (0x1517A624, 0xAC4A0000), (0x1517A628, 0xAC490004)):
        if checked(code, code_base, address, 4) != struct.pack('>I', expected):
            raise ValueError('embedded geometry list submission changed')
    display = checked(data, data_base, list_address, len(TYPE08_LIST))
    load, vertex_address = struct.unpack_from('>II', display)
    count, end = (load >> 12) & 255, (load >> 1) & 127
    if load >> 24 != 1 or count != 6 or end != count or vertex_address != 0x8008CD90:
        raise ValueError('embedded geometry vertex load changed')
    raw = checked(data, data_base, vertex_address, count * 16)
    vertices = []
    for index, record in enumerate(struct.iter_unpack('>hhhHhhBBBB', raw)):
        vertices.append({'index': index, 'source_address': f'0x{vertex_address + index * 16:08X}',
                         'position': list(record[:3]), 'flag': record[3],
                         'st_s16': list(record[4:6]), 'rgba_u8': list(record[6:])})
    triangles, commands = [], []
    for offset in range(8, 40, 8):
        word, argument = struct.unpack_from('>II', display, offset)
        indices = [(word >> shift) & 255 for shift in (16, 8, 0)]
        if word >> 24 != 5 or argument or any(i & 1 or i // 2 >= count for i in indices):
            raise ValueError('embedded triangle command changed')
        triangles.append([i // 2 for i in indices])
        commands.append({'source_address': f'0x{list_address + offset:08X}',
                         'command': f'0x{word:08X}', 'argument': '0x00000000'})
    if struct.unpack_from('>II', display, 40) != (0xDF000000, 0):
        raise ValueError('embedded geometry list termination changed')
    return {
        'schema_version': 1, 'family': 'rom-embedded-effect-geometry', 'scope': TYPE08_SCOPE,
        'source_kind': 'game-data', 'indexed_model_bank': None, 'object_types': [8, 9, 12, 89],
        'source_vertex_address': f'0x{vertex_address:08X}', 'source_list_address': f'0x{list_address:08X}',
        'vertex_count': count, 'triangle_count': len(triangles), 'vertices': vertices, 'triangles': triangles,
        'vertex_load_command': f'0x{load:08X}', 'triangle_commands': commands,
        'vertex_bytes_sha1': hashlib.sha1(raw).hexdigest(),
        'source_reconstruction': 'All96 original vertex bytes and all48 display-list bytes preserved exactly.',
        'consumers': [{'address': f'0x{a:08X}', 'size': n, 'sha1': h} for a, n, h in TYPE08_CONSUMERS],
        'data_spans': [{'address': f'0x{a:08X}', 'size': len(b), 'hex': b.hex(),
                        'sha1': hashlib.sha1(b).hexdigest()} for a, b in TYPE08_DATA],
        'render_state': {
            'dispatcher': 'func_151674F8', 'renderer': 'func_1517A3A0',
            'setup_display_lists': {'8': '0x8008CE20', '9': '0x8008CE20',
                                    '12': '0x8008CE40', '89': '0x8008CE40'},
            'shared_setup_display_list': '0x8008CE60',
            'geometry_submission': '0x1517A618..0x1517A628',
            'combine_mode': ['0xFC121624', '0xFF2FFFFF'],
            'combine_formula': models.decode_combine_mode((0xFC121624, 0xFF2FFFFF)),
            'texture_selector': {'object_offset': '0x9F', 'helper': 'func_1517A9A8',
                                 'descriptor_address': '0x80090614', 'table_address': '0x8009060C',
                                 'stored_flat_indices': [2990, 2988],
                                 'status': 'Selector bytes recorded; complete loader, tile and UV contract not reconstructed.'},
            'primitive_alpha': {'object_offset': '0xB3', 'cache_address': '0x800DD450',
                                'write_address': '0x1517A5AC..0x1517A5CC', 'policy': 'Not baked.'},
            'diagnostic_export_policy': TYPE08_DIAGNOSTIC,
        },
        'runtime_instancing': {'policy': 'Export one source-local primitive shared by four dispatch types; no runtime instance synthesized.',
                               'position_and_angle_halfwords': 'object+0x90..0x9A',
                               'scale_float': 'object+0xA8',
                               'matrix_address': 'object+0x10+(D_800BE9C0<<6)'},
    }


def type08_geometry_files(manifest):
    """Preserve the native shape without manufacturing its material or UVs."""
    vertices, triangles = manifest['vertices'], manifest['triangles']
    positions = [v['position'] for v in vertices]
    raw = b''.join(struct.pack('>hhhHhhBBBB', *v['position'], v['flag'],
                            *v['st_s16'], *v['rgba_u8']) for v in vertices)
    if raw != TYPE08_VERTICES or triangles != [[0, 1, 2], [0, 3, 1], [4, 1, 3], [5, 4, 3]]:
        raise ValueError('embedded type08 geometry differs from pinned source')
    binary = (b''.join(struct.pack('<3f', *p) for p in positions)
              + bytes(c for v in vertices for c in v['rgba_u8'])
              + struct.pack('<12H', *(i for triangle in triangles for i in triangle)))
    document = {
        'asset': {'version': '2.0', 'generator': 'Conker US embedded geometry diagnostic'},
        'scene': 0, 'scenes': [{'nodes': [0]}], 'nodes': [{'mesh': 0, 'name': TYPE08_NAME}],
        'meshes': [{'name': TYPE08_NAME, 'primitives': [{'attributes': {'POSITION': 0, 'COLOR_0': 1}, 'indices': 2, 'mode': 4}]}],
        'buffers': [{'uri': TYPE08_NAME + '.bin', 'byteLength': len(binary)}],
        'bufferViews': [
            {'buffer': 0, 'byteOffset': 0, 'byteLength': 72, 'target': 34962},
            {'buffer': 0, 'byteOffset': 72, 'byteLength': 24, 'target': 34962},
            {'buffer': 0, 'byteOffset': 96, 'byteLength': 24, 'target': 34963}],
        'accessors': [
            {'bufferView': 0, 'componentType': 5126, 'count': 6, 'type': 'VEC3',
             'min': [min(p[i] for p in positions) for i in range(3)],
             'max': [max(p[i] for p in positions) for i in range(3)]},
            {'bufferView': 1, 'componentType': 5121, 'count': 6, 'type': 'VEC4', 'normalized': True},
            {'bufferView': 2, 'componentType': 5123, 'count': 12, 'type': 'SCALAR'}],
        'extras': {'sourceKind': 'embedded-game-data', 'sourceAddress': manifest['source_vertex_address'],
                   'sourceVertexSha1': manifest['vertex_bytes_sha1'],
                   'normalizedRomSha1': manifest.get('normalized_sha1'),
                   'rawSignedST': [v['st_s16'] for v in vertices],
                   'scope': TYPE08_SCOPE, 'materialStatus': 'native-texture-and-runtime-state-unresolved',
                   'diagnosticMaterialPolicy': TYPE08_DIAGNOSTIC, 'nativeRenderState': manifest['render_state']},
    }
    return {'source/vertices-8008cd90.bin': raw, 'source/list-8008cdf0.bin': TYPE08_LIST,
            'geometry/' + TYPE08_NAME + '.bin': binary,
            'geometry/' + TYPE08_NAME + '.gltf': (json.dumps(document, indent=2) + '\n').encode()}


TYPE13_NAME = 'embedded-type13-8008b3e0'
TYPE13_CONSUMERS = (
    CONSUMERS[0],
    (0x151669A0, 1648, '3f95afd4d65830cd0c4b2e1903e8307746524610'),
)
TYPE13_VERTICES = bytes.fromhex(
    'fe70ffdeffd800000000000000000000'
    'fe70ffde002800000000000000000000'
    'fe700022000000000000000000000000'
    '0000ffdeffd800000000000000000000'
    '0000ffde002800000000000000000000'
    '00000022000000000000000000000000')
TYPE13_DATA = (
    (0x8008B3E0, TYPE13_VERTICES),
    (0x8008B440, bytes.fromhex(
        'd9ffffff00000400d7000002ffffffffe700000000000000fcfffffffffcf279'
        'f900000000000001ef082caf00504b50df00000000000000')),
    (0x8008B74C, bytes.fromhex(
        '15166b500000000015166d68000000008008b44015166f6c00000000'
        '0000000015166fd800000000000000000000000001000000')),
    (0x80090548, bytes.fromhex('000010b3800905480100004000200401')),
)
TYPE13_SCOPE = ('One ROM game-data primitive used by effect type 13. Six local vertices '
                'and four ordered triangles are preserved. No effect name, runtime '
                'instance, placement, scale, visibility, timeline or native appearance is inferred.')
TYPE13_DIAGNOSTIC = ('No glTF material, texture or normalized UVs are assigned. '
                    'The viewer default material is diagnostic. All six source RGBA '
                    'and ST values are zero; native texture-only shading does not use '
                    'these zero colors. The draw updates all six cached ST pairs from '
                    'runtime object state before emitting triangles. Neither those '
                    'coordinates nor the three runtime instance matrices are baked.')


def describe_type13_geometry(code, code_base, data, data_base):
    for address, size, expected in TYPE13_CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'embedded geometry consumer changed at0x{address:08X}')
    for address, expected in TYPE13_DATA:
        if checked(data, data_base, address, len(expected)) != expected:
            raise ValueError(f'embedded geometry data changed at0x{address:08X}')
    address = immediate_pair(code, code_base, 0x15166D9C, 0x15166DD0, signed=True)
    load = immediate_pair(code, code_base, 0x15166DB0, 0x15166DBC)
    if address != 0x8008B3E0 or load != 0x0100600C:
        raise ValueError('type13 vertex load changed')
    # Full-span pins authenticate the producer/consumer path; these guards
    # separately connect the proven address and command registers to the stores.
    for at, expected in ((0x15166DFC, 0xAC720000), (0x15166E00, 0xAC6D0004)):
        if checked(code, code_base, at, 4) != struct.pack('>I', expected):
            raise ValueError('type13 vertex submission changed')
    triangles, commands = [], []
    for first in (0x15166ECC, 0x15166EE4, 0x15166EFC, 0x15166F14):
        word = immediate_pair(code, code_base, first, first + 4)
        encoded = [(word >> shift) & 255 for shift in (16, 8, 0)]
        if word >> 24 != 5 or any(i & 1 or i // 2 >= 6 for i in encoded):
            raise ValueError('type13 triangle command changed')
        triangles.append([i // 2 for i in encoded])
        commands.append({'instruction_address': f'0x{first:08X}',
                         'command': f'0x{word:08X}', 'argument': '0x00000000'})
    vertices = [{'index': i, 'source_address': f'0x{address + i * 16:08X}',
                 'position': list(v[:3]), 'flag': v[3], 'st_s16': list(v[4:6]),
                 'rgba_u8': list(v[6:])}
                for i, v in enumerate(struct.iter_unpack('>hhhHhhBBBB', TYPE13_VERTICES))]
    return {
        'schema_version': 1, 'family': 'rom-embedded-effect-geometry', 'scope': TYPE13_SCOPE,
        'source_kind': 'game-data', 'indexed_model_bank': None, 'object_type': 13,
        'source_vertex_address': f'0x{address:08X}', 'vertex_count': 6, 'triangle_count': 4,
        'vertices': vertices, 'triangles': triangles, 'vertex_load_command': f'0x{load:08X}',
        'triangle_commands': commands, 'vertex_bytes_sha1': hashlib.sha1(TYPE13_VERTICES).hexdigest(),
        'source_reconstruction': 'All 96 original vertex bytes reconstructed exactly.',
        'consumers': [{'address': f'0x{a:08X}', 'size': n, 'sha1': h} for a, n, h in TYPE13_CONSUMERS],
        'data_spans': [{'address': f'0x{a:08X}', 'size': len(b), 'hex': b.hex(),
                        'sha1': hashlib.sha1(b).hexdigest()} for a, b in TYPE13_DATA],
        'render_state': {
            'setup_display_list': '0x8008B440', 'setup_callback': '0x15166F6C',
            'dispatcher': 'func_151674F8', 'texture_enabled': True,
            'combine_mode': ['0xFCFFFFFF', '0xFFFCF279'],
            'combine_formula': models.decode_combine_mode((0xFCFFFFFF, 0xFFFCF279)),
            'other_mode': ['0xEF082CAF', '0x00504B50'],
            'blend_color': ['0xF9000000', '0x00000001'],
            'texture_descriptor': '0x8009054C', 'texture_index': 4275,
            'texture_limit': 'Descriptor and loader call are proven; complete texture/TMEM/filter contract is unresolved.',
            'dynamic_st': {
                'source': '15166E08..15166EC0, unsigned object byte +0xD0',
                's0': '0x2800 - trunc((object_D0 << 12) / 10)',
                's1': 's0 + 0x800',
                'cache_pairs': [['s0', 0x2000], ['s0', 0x2000], ['s0', 0x2400],
                                ['s1', 0x2000], ['s1', 0x2000], ['s1', 0x2400]],
                'policy': 'Raw zero ST retained; G_MODIFYVTX results not synthesized.'},
            'diagnostic_export_policy': TYPE13_DIAGNOSTIC,
        },
        'runtime_instancing': {'draw_loop_count': 3, 'matrix_offsets': [0x10, 0x50, 0x90],
                               'policy': 'Primitive exported once; constructor randomness, caller scale and runtime matrices omitted.'},
    }


def type13_geometry_files(manifest):
    vertices, triangles = manifest['vertices'], manifest['triangles']
    raw = b''.join(struct.pack('>hhhHhhBBBB', *v['position'], v['flag'],
                               *v['st_s16'], *v['rgba_u8']) for v in vertices)
    if raw != TYPE13_VERTICES:
        raise ValueError('type13 vertices differ from pinned source')
    positions = [v['position'] for v in vertices]
    binary = b''.join(struct.pack('<3f', *p) for p in positions)
    binary += bytes(c for v in vertices for c in v['rgba_u8'])
    binary += struct.pack('<12H', *(i for t in triangles for i in t))
    doc = {
        'asset': {'version': '2.0', 'generator': 'Conker US embedded geometry diagnostic'},
        'scene': 0, 'scenes': [{'nodes': [0]}], 'nodes': [{'mesh': 0, 'name': TYPE13_NAME}],
        'meshes': [{'name': TYPE13_NAME, 'primitives': [{'attributes': {'POSITION': 0, 'COLOR_0': 1}, 'indices': 2, 'mode': 4}]}],
        'buffers': [{'uri': TYPE13_NAME + '.bin', 'byteLength': len(binary)}],
        'bufferViews': [{'buffer': 0, 'byteOffset': 0, 'byteLength': 72, 'target': 34962},
                        {'buffer': 0, 'byteOffset': 72, 'byteLength': 24, 'target': 34962},
                        {'buffer': 0, 'byteOffset': 96, 'byteLength': 24, 'target': 34963}],
        'accessors': [{'bufferView': 0, 'componentType': 5126, 'count': 6, 'type': 'VEC3',
                       'min': [min(p[i] for p in positions) for i in range(3)],
                       'max': [max(p[i] for p in positions) for i in range(3)]},
                      {'bufferView': 1, 'componentType': 5121, 'count': 6, 'type': 'VEC4', 'normalized': True},
                      {'bufferView': 2, 'componentType': 5123, 'count': 12, 'type': 'SCALAR'}],
        'extras': {'sourceKind': 'embedded-game-data', 'sourceAddress': manifest['source_vertex_address'],
                   'sourceVertexSha1': manifest['vertex_bytes_sha1'], 'normalizedRomSha1': manifest.get('normalized_sha1'),
                   'rawSignedST': [v['st_s16'] for v in vertices], 'scope': TYPE13_SCOPE,
                   'materialStatus': 'native-texture-and-runtime-state-unresolved',
                   'diagnosticMaterialPolicy': TYPE13_DIAGNOSTIC, 'nativeRenderState': manifest['render_state']},
    }
    return {'source/vertices-8008b3e0.bin': raw, 'geometry/' + TYPE13_NAME + '.bin': binary,
            'geometry/' + TYPE13_NAME + '.gltf': (json.dumps(doc, indent=2) + '\n').encode()}


PRIMITIVES = ('type06', 'type08', 'type13', *(f'type55-{i}' for i in range(5)))


def build_export(rom_argument=None, *, primitive='type06'):
    if primitive not in PRIMITIVES:
        raise ValueError('unsupported embedded primitive')
    path, layout = models.resolve_rom('us', rom_argument)
    rom, _ = models.normalize_rom(path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout['normalized_sha1']:
        raise ValueError('embedded geometry requires the validated US ROM')
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    if primitive.startswith('type55-'):
        try:
            from scripts import model_embedded_type55 as backend
        except ModuleNotFoundError:
            import model_embedded_type55 as backend
        selector = int(primitive.removeprefix('type55-'))
        primitive_name = backend.name(selector)
        make_files = backend.geometry_files
        manifest = backend.describe_geometry(
            game.code, layout['game_vram'], game.data, layout['game_data_vram'], selector)
    else:
        describe, make_files, primitive_name = {
            'type06': (describe_geometry, geometry_files, NAME),
            'type08': (describe_type08_geometry, type08_geometry_files, TYPE08_NAME),
            'type13': (describe_type13_geometry, type13_geometry_files, TYPE13_NAME),
        }[primitive]
        manifest = describe(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    manifest['normalized_sha1'] = digest
    files = make_files(manifest)
    # Reuse the existing byte-preserving packer. The temporary paths never enter
    # artifacts; verification leaves the destination untouched.
    with tempfile.TemporaryDirectory(prefix='conker-embedded-geometry-') as temporary:
        temp = Path(temporary)
        for name, content in files.items():
            target = temp / name
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(content)
        packed, evidence = pack_glb(temp / 'geometry' / (primitive_name + '.gltf'))
    files[primitive_name + '.glb'] = packed
    manifest['packing'] = evidence
    manifest['files'] = {name: {'size': len(content), 'sha256': hashlib.sha256(content).hexdigest()}
                         for name, content in files.items()}
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    return manifest, files


def export(output, rom_argument=None, *, verify=False, primitive='type06'):
    manifest, files = build_export(rom_argument, primitive=primitive)
    if verify:
        for name, expected in files.items():
            if (output / name).read_bytes() != expected:
                raise ValueError(f'embedded geometry output differs from ROM: {name}')
    else:
        output.mkdir(parents=True, exist_ok=False)
        for name, content in files.items():
            path = output / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(content)
    return manifest


def material_inspection(argv):
    """Keep the selected material artifact separate from source geometry outputs."""
    try:
        from scripts import model_embedded_type13_inspection as backend
    except ModuleNotFoundError:
        import model_embedded_type13_inspection as backend
    return backend.main(argv)


def material_inspection_type06(argv):
    try:
        from scripts import model_embedded_type06_inspection as backend
    except ModuleNotFoundError:
        import model_embedded_type06_inspection as backend
    return backend.main(argv)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--primitive', choices=PRIMITIVES, default='type06',
                        help='stored primitive; type55-0 through type55-4 select five source list variants')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--material-inspection', choices=('counter5', 'elapsed0'),
                        help='separate selected-state material inspection: type13 counter5 or type06 elapsed0')
    parser.add_argument('--blender', type=Path, help='Blender executable for material inspection only')
    parser.add_argument('--verify', action='store_true', help='rederive and compare an existing export without rewriting it')
    args = parser.parse_args(argv)
    if args.material_inspection:
        required = {'counter5': 'type13', 'elapsed0': 'type06'}[args.material_inspection]
        if args.primitive != required:
            parser.error(f'{args.material_inspection} material inspection requires --primitive {required}')
        forwarded = []
        for option, value in (('--rom', args.rom), ('--output', args.output), ('--blender', args.blender)):
            if value is not None:
                forwarded.extend((option, str(value)))
        if args.verify:
            forwarded.append('--verify')
        return (material_inspection if required == 'type13' else material_inspection_type06)(forwarded)
    if args.blender is not None:
        parser.error('--blender requires --material-inspection')
    if args.output is None:
        directory = 'embedded-geometry' if args.primitive == 'type06' else 'embedded-geometry-' + args.primitive
        args.output = models.ROOT / 'build/assets/models' / directory
    try:
        result = export(args.output.resolve(), args.rom, verify=args.verify, primitive=args.primitive)
    except (OSError, ValueError) as error:
        parser.error(str(error))
    print(f"{'Verified' if args.verify else 'Extracted'} embedded primitive: "
          f"{result['vertex_count']} vertices, {result['triangle_count']} triangles; {args.output / 'manifest.json'}")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
