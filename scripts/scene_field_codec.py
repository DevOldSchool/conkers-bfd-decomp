"""Native typed fields within bounded US scene records; unexplained bytes stay raw."""
from __future__ import annotations
import struct
try:
    from scripts.scene_volume_codec import integer, floats, vector16, records
except ModuleNotFoundError:
    from scene_volume_codec import integer, floats, vector16, records

FORMATS = {2: 'conker-scene-model-transforms-v2', 4: 'conker-scene-group-references-v1', 6: 'conker-scene-spawn-fields-v1',
           8: 'conker-scene-view-pose-fields-v1', 10: 'conker-scene-sprite-choices-v1'}
STRIDES = {2: 68, 4: 24, 6: 24, 8: 24, 10: 4}
FIELDS = {2: {'position', 'rotation', 'scale', 'model_source', 'update_handler', 'script_selector', 'initial_state', 'transform_flags'}, 4: {'members'},
          6: {'position', 'view_position', 'view_selector', 'heading', 'spawn_option', 'transition', 'alternate_spawn'},
          8: {'position', 'view_parameters'}, 10: {'sprite', 'flags'}}


def encode(source, child):
    if child not in FORMATS:
        raise ValueError('unsupported scene field child')
    output = []
    for index, record in enumerate(records(source, FORMATS[child])):
        if not isinstance(record, dict) or set(record) != FIELDS[child]:
            raise ValueError('invalid scene field record schema')
        at = index * STRIDES[child]
        if child == 2:
            model = record['model_source']
            if not isinstance(model, dict) or set(model) != {'kind', 'index'}:
                raise ValueError('invalid scene model source')
            selection = struct.pack('>3I', integer(model['kind'], 0, 2), integer(model['index'], 0, 0xFFFFFFFF),
                                 integer(record['update_handler'], 0, 0xFFFFFFFF))
            output.extend([(at, vector16(record['position']) + vector16(record['rotation']) + selection),
                           (at + 32, floats(record['scale'], 3)),
                           (at + 51, struct.pack('>2B', integer(record['script_selector'], 0, 255),
                                                integer(record['initial_state'], 0, 255))),
                           (at + 60, bytes([integer(record['transform_flags'], 0, 255)]))])
        elif child == 4:
            members = record['members']
            if not isinstance(members, list) or not 1 <= len(members) <= 8:
                raise ValueError('scene group must have one to eight native references')
            values = []
            for member in members:
                if not isinstance(member, dict) or set(member) != {'kind', 'index'}:
                    raise ValueError('invalid scene group reference')
                values.append(integer(member['kind'], 0, 15) << 12 | integer(member['index'], 0, 4095))
            output.extend([(at + 2, struct.pack('>H', len(values))),
                           (at + 8, struct.pack(f'>{len(values)}H', *values))])
        elif child == 6:
            payload = (vector16(record['position'])
                + struct.pack('>2B', integer(record['view_selector'], 0, 255), integer(record['heading'], 0, 255))
                + floats(record['view_position'], 3)
                + struct.pack('>Bbb', integer(record['spawn_option'], 0, 255),
                    integer(record['transition'], -128, 127), integer(record['alternate_spawn'], -128, 127)))
            output.append((at, payload))
        elif child == 8:
            output.extend([(at, vector16(record['position'])), (at + 12, floats(record['view_parameters'], 3))])
        else:
            output.append((at, struct.pack('>2H', integer(record['sprite'], 0, 65535), integer(record['flags'], 0, 65535))))
    return output


def decode(data, child):
    if child not in STRIDES or len(data) % STRIDES[child]:
        raise ValueError('invalid scene native record stride')
    result = {'format': FORMATS[child], 'records': []}
    for at in range(0, len(data), STRIDES[child]):
        if child == 2:
            record = {'position': list(struct.unpack_from('>3h', data, at)),
                      'rotation': list(struct.unpack_from('>3h', data, at + 6)),
                      'scale': list(struct.unpack_from('>3f', data, at + 32)),
                      'model_source': {'kind': struct.unpack_from('>I', data, at + 12)[0],
                                       'index': struct.unpack_from('>I', data, at + 16)[0]},
                      'update_handler': struct.unpack_from('>I', data, at + 20)[0],
                      'script_selector': data[at + 51], 'initial_state': data[at + 52],
                      'transform_flags': data[at + 60]}
        elif child == 4:
            count = struct.unpack_from('>H', data, at + 2)[0]
            if not 1 <= count <= 8:
                raise ValueError('invalid scene group member count')
            members = struct.unpack_from(f'>{count}H', data, at + 8)
            record = {'members': [{'kind': value >> 12, 'index': value & 4095} for value in members]}
        elif child == 6:
            selector, heading = struct.unpack_from('>2B', data, at + 6)
            option, transition, alternate = struct.unpack_from('>Bbb', data, at + 20)
            record = {'position': list(struct.unpack_from('>3h', data, at)), 'view_selector': selector,
                      'heading': heading, 'view_position': list(struct.unpack_from('>3f', data, at + 8)),
                      'spawn_option': option, 'transition': transition, 'alternate_spawn': alternate}
        elif child == 8:
            record = {'position': list(struct.unpack_from('>3h', data, at)),
                      'view_parameters': list(struct.unpack_from('>3f', data, at + 12))}
        else:
            sprite, flags = struct.unpack_from('>2H', data, at)
            record = {'sprite': sprite, 'flags': flags}
        result['records'].append(record)
    for at, payload in encode(result, child):
        if payload != data[at:at + len(payload)]:
            raise ValueError('scene field source does not reproduce native storage')
    return result
