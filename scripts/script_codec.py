"""Native script positions, bindings, value keys, commands and encoded text."""
import math
import struct
import zlib
FORMAT = 'conker-script-tracks-v1'


def align(data, size):
    return data + bytes(-len(data) % size)


def decode(data):
    """Read the loader's five segment groups, rejecting uncovered storage."""
    if len(data) < 16 or len(data) % 8:
        raise ValueError('script bundle length')
    table = struct.unpack_from('>I', data)[0]
    if not 8 <= table <= len(data) or table % 8:
        raise ValueError('script directory extent')
    parts = []
    cursor = table
    for i in range(table // 8):
        at, flags = struct.unpack_from('>II', data, i * 8)
        size = flags & 0x0FFFFFFF
        aligned = (cursor + 7) & ~7
        if at != aligned or flags >> 28 != (8 if i == table // 8 - 1 else 0) or at + size > len(data) or any(data[cursor:at]):
            raise ValueError('script segment extent or flags')
        parts.append(data[at:at + size])
        cursor = at + size
    if align(data[:cursor], 8) != data:
        raise ValueError('script trailing padding')
    if len(parts[0]) != 8:
        raise ValueError('script counts')
    n, a, b, c = struct.unpack('>4H', parts[0])
    if len(parts) != 1 + 2 * n + a + b + c:
        raise ValueError('script track counts')
    pos = parts[1:1 + n]
    bindings = parts[1 + n:1 + 2 * n]
    floats = parts[1 + 2 * n:1 + 2 * n + a]
    commands = parts[1 + 2 * n + a:1 + 2 * n + a + b]
    texts = parts[1 + 2 * n + a + b:]
    result = {'format': FORMAT, 'position_tracks': [], 'bindings': [], 'value_tracks': [], 'command_tracks': [], 'texts': []}
    for p in pos:
        if len(p) % 8:
            raise ValueError('position stride')
        result['position_tracks'].append([{'position': list(v[:3]), 'control': v[3]} for v in struct.iter_unpack('>3hH', p)])
    # The native table stride is eight bytes. Its kind/selector/target/height
    # fields occupy six; this reviewed format requires a two-byte zero tail.
    for p in bindings:
        if len(p) != 8 or p[6:] != bytes(2):
            raise ValueError('binding padding')
        kind, selector, target, height = struct.unpack('>HBbh', p[:6])
        if kind not in range(8):
            raise ValueError('binding kind')
        result['bindings'].append({'kind': kind, 'selector': selector, 'target': target, 'height_offset': height})
    for p in floats:
        if len(p) % 8:
            raise ValueError('value key stride')
        values = [{'value': v, 'interpolation': i, 'channel': c, 'time': t} for v, i, c, t in struct.iter_unpack('>fBBh', p)]
        if any((not math.isfinite(x['value']) or x['channel'] > 14 for x in values)):
            raise ValueError('value track field')
        result['value_tracks'].append(values)
    for p in commands:
        if len(p) % 8:
            raise ValueError('command stride')
        values = [{'opcode': op, 'time_delta': dt, 'selector': sel, 'argument_a': a, 'argument_b': b, 'argument_c': c} for op, dt, sel, a, b, c in struct.iter_unpack('>bBhbbh', p)]
        if any((x['opcode'] not in range(-3, 18) for x in values)):
            raise ValueError('command opcode')
        result['command_tracks'].append(values)
    for p in texts:
        if not p:
            result['texts'].append(None)
            continue
        end = p.index(0)
        if align(p[:end] + b'\x00', 2) != p:
            raise ValueError('text trailing content')
        result['texts'].append(p[:end].decode('latin1'))
    return result


def _encode(source):
    """Derive counts, offsets and padding from typed fields only."""
    if set(source) != {'format', 'position_tracks', 'bindings', 'value_tracks', 'command_tracks', 'texts'} or source['format'] != FORMAT:
        raise ValueError('script schema')
    n = len(source['position_tracks'])
    if len(source['bindings']) != n:
        raise ValueError('binding count')
    parts = [struct.pack('>4H', n, len(source['value_tracks']), len(source['command_tracks']), len(source['texts']))]
    for p in source['position_tracks']:
        parts.append(b''.join((struct.pack('>3hH', *v['position'], v['control']) for v in p)))
    for b in source['bindings']:
        parts.append(align(struct.pack('>HBbh', b['kind'], b['selector'], b['target'], b['height_offset']), 8))
    for p in source['value_tracks']:
        parts.append(b''.join((struct.pack('>fBBh', v['value'], v['interpolation'], v['channel'], v['time']) for v in p)))
    for p in source['command_tracks']:
        parts.append(b''.join((struct.pack('>bBhbbh', v['opcode'], v['time_delta'], v['selector'], v['argument_a'], v['argument_b'], v['argument_c']) for v in p)))
    for p in source['texts']:
        if p is None:
            parts.append(b'')
            continue
        if '\x00' in p:
            raise ValueError('embedded text terminator')
        parts.append(align(p.encode('latin1') + b'\x00', 2))
    data = bytearray(8 * len(parts))
    for i, p in enumerate(parts):
        data.extend(bytes(-len(data) % 8))
        struct.pack_into('>II', data, i * 8, len(data), len(p) | (0x80000000 if i == len(parts) - 1 else 0))
        data.extend(p)
    result = align(bytes(data), 8)
    if decode(result) != source:
        raise ValueError('noncanonical script source')
    return result
SCHEMAS = {'bindings': {'kind': (0, 7), 'selector': (0, 255), 'target': (-128, 127), 'height_offset': (-32768, 32767)}, 'value_tracks': {'value': None, 'interpolation': (0, 255), 'channel': (0, 14), 'time': (-32768, 32767)}, 'command_tracks': {'opcode': (-3, 17), 'time_delta': (0, 255), 'selector': (-32768, 32767), 'argument_a': (-128, 127), 'argument_b': (-128, 127), 'argument_c': (-32768, 32767)}}


def checked_integer(value, low, high):
    if type(value) is not int or not low <= value <= high:
        raise ValueError('script field exceeds native integer width')


def validate_source(source):
    fields = {'format', 'position_tracks', 'bindings', 'value_tracks', 'command_tracks', 'texts'}
    if not isinstance(source, dict) or set(source) != fields or source['format'] != FORMAT:
        raise ValueError('invalid script source schema')
    for field in fields - {'format'}:
        if not isinstance(source[field], list) or len(source[field]) > 65535:
            raise ValueError('script track count exceeds native header width')
    if len(source['bindings']) != len(source['position_tracks']):
        raise ValueError('script binding count disagrees with position tracks')
    for track in source['position_tracks']:
        if not isinstance(track, list):
            raise ValueError('invalid position track')
        for key in track:
            if not isinstance(key, dict) or set(key) != {'position', 'control'} or (not isinstance(key['position'], list)) or (len(key['position']) != 3):
                raise ValueError('invalid script position key')
            for value in key['position']:
                checked_integer(value, -32768, 32767)
            checked_integer(key['control'], 0, 65535)
    for family, schema in SCHEMAS.items():
        tracks = [source[family]] if family == 'bindings' else source[family]
        for track in tracks:
            if not isinstance(track, list):
                raise ValueError('invalid script track')
            for key in track:
                if not isinstance(key, dict) or set(key) != set(schema):
                    raise ValueError('invalid script key schema')
                for field, limits in schema.items():
                    value = key[field]
                    if limits is None:
                        if type(value) not in (int, float) or not math.isfinite(value):
                            raise ValueError('script value must be a finite native float')
                    else:
                        checked_integer(value, *limits)
    for text in source['texts']:
        if text is not None and (not isinstance(text, str) or '\x00' in text):
            raise ValueError('invalid script encoded text')


def encode(source):
    validate_source(source)
    try:
        return _encode(source)
    except (KeyError, TypeError, IndexError, struct.error, OverflowError, UnicodeError) as error:
        raise ValueError('invalid native script fields') from error


def encode_container(parts, *, compressed):
    """Derive eight-byte archive records and zero alignment from child payloads."""
    if not parts or len(parts) > 65535:
        raise ValueError('invalid script container slot count')
    output = bytearray(8 * len(parts))
    for index, payload in enumerate(parts):
        output.extend(bytes(-len(output) % 8))
        flags = 0x80000000 if index == len(parts) - 1 else 0
        if compressed and payload:
            flags |= 0x10000000
        if len(payload) >= 1 << 28:
            raise ValueError('script payload exceeds native length width')
        struct.pack_into('>II', output, index * 8, len(output), flags | len(payload))
        output.extend(payload)
    return align(bytes(output), 8)


def encode_bank(records):
    if not isinstance(records, dict) or set(records) != {'format', 'scenes'} or records['format'] != FORMAT or (not isinstance(records['scenes'], list)):
        raise ValueError('invalid script bank schema')
    scenes = []
    for scene in records['scenes']:
        if scene is None:
            scenes.append(b'')
            continue
        if not isinstance(scene, dict) or set(scene) != {'scripts'} or (not isinstance(scene['scripts'], list)):
            raise ValueError('invalid script scene schema')
        scripts = []
        for script in scene['scripts']:
            if script is None:
                scripts.append(b'')
                continue
            data = encode(script)
            compressor = zlib.compressobj(level=6, wbits=-15)
            scripts.append(struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush())
        scenes.append(encode_container(scripts, compressed=True))
    return encode_container(scenes, compressed=False)
