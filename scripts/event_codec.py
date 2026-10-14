"""Typed US event instructions, labels and NUL-terminated constant strings."""
from __future__ import annotations

import struct
import zlib

try:
    from scripts.model_event_activation import ARITY, MODE_NAMES
except ModuleNotFoundError:
    from model_event_activation import ARITY, MODE_NAMES

FORMAT = 'conker-event-programs-v1'
PROGRAM_FIELDS = {'flags', 'state_bytes', 'entrypoints', 'instructions', 'strings'}


def integer(value, low, high, label):
    if type(value) is not int or not low <= value <= high:
        raise ValueError(f'event {label} is outside its native integer domain')
    return value


def string_section(strings):
    if not isinstance(strings, list) or len(strings) > 32768:
        raise ValueError('invalid event string list')
    offsets, result = [], bytearray()
    for text in strings:
        if (not isinstance(text, str) or any(ord(c) not in (9, 10, 13, 27)
                and not 32 <= ord(c) <= 126 for c in text)):
            raise ValueError('event strings require reviewed ASCII text without embedded NULs')
        offsets.append(len(result))
        result.extend(text.encode('ascii') + b'\0')
    if strings:
        # The native source allocation includes 1..4 trailing zero bytes.
        result.extend(bytes(4 - len(result) % 4))
    return offsets, bytes(result)


def instruction_layout(instructions):
    if not isinstance(instructions, list) or not 1 <= len(instructions) <= 32751:
        raise ValueError('invalid event instruction list')
    offsets, widths, cursor = [], [], 32
    for instruction in instructions:
        if not isinstance(instruction, dict) or set(instruction) != {'opcode', 'wide', 'operands'}:
            raise ValueError('invalid event instruction schema')
        opcode = integer(instruction['opcode'], 1, len(ARITY) - 1, 'opcode')
        wide, operands = instruction['wide'], instruction['operands']
        if type(wide) is not bool or not isinstance(operands, list) or len(operands) != ARITY[opcode]:
            raise ValueError('event operand count or width flag differs from native instruction')
        sizes = []
        for operand in operands:
            if not isinstance(operand, dict) or operand.get('mode') not in MODE_NAMES:
                raise ValueError('invalid event operand mode')
            mode = MODE_NAMES.index(operand['mode'])
            field = 'string' if mode == 2 else 'target' if mode == 3 else 'value'
            if set(operand) != {'mode', field}:
                raise ValueError('invalid event operand fields')
            size = 4 if wide and mode in (3, 4, 6) else 2
            if size == 4:
                wide = False
            sizes.append(size)
        if wide:
            raise ValueError('event wide flag has no immediate operand')
        offsets.append(cursor)
        widths.append(sizes)
        cursor += 2 + sum(sizes)
    return offsets, widths, cursor


def encode_program(program):
    if not isinstance(program, dict) or set(program) != PROGRAM_FIELDS:
        raise ValueError('invalid event program schema')
    flags = integer(program['flags'], 0, 0x3800, 'flags')
    state = integer(program['state_bytes'], 0, 65535, 'state size')
    if flags & ~0x3800 or state % 4:
        raise ValueError('unsupported event flags or state alignment')
    offsets, widths, code_end = instruction_layout(program['instructions'])
    entries = program['entrypoints']
    if not isinstance(entries, list) or len(entries) != 5:
        raise ValueError('event requires five instruction entrypoints')
    targets = [offsets[integer(i, 0, len(offsets) - 1, 'entrypoint')] for i in entries]
    if targets[0] != 32:
        raise ValueError('first event entrypoint must be the first instruction')
    strings, constants = string_section(program['strings'])
    total = integer(code_end + len(constants), 34, 65535, 'program size')
    header = struct.pack('>16H', flags, 0, total, state, code_end if constants else 0,
                         0, 0, *targets[1:], 0, 0, 0, 0, 0)
    code = bytearray()
    referenced_strings = set()
    for instruction, sizes in zip(program['instructions'], widths):
        op, operands = instruction['opcode'], instruction['operands']
        if op in (15, 16, 17) and operands[-1]['mode'] != 'program-offset':
            raise ValueError('event branch requires an instruction label')
        if op == 25:
            mode = operands[0]['mode']
            if mode not in ('program-offset', 'native-index'):
                raise ValueError('event call requires an internal label or native index')
            if mode == 'native-index':
                integer(operands[0]['value'], 0, 13, 'native call index')
        word = op | (0x40 if instruction['wide'] else 0)
        encoded = bytearray()
        for index, (operand, size) in enumerate(zip(operands, sizes)):
            mode = MODE_NAMES.index(operand['mode'])
            word |= mode << (13 - index * 3)
            if mode == 2:
                if op != 24:
                    raise ValueError('reviewed event strings are passed through PUSH only')
                label = integer(operand['string'], 0, len(strings) - 1, 'string label')
                referenced_strings.add(label)
                value = strings[label]
            elif mode == 3:
                value = offsets[integer(operand['target'], 0, len(offsets) - 1, 'instruction label')]
            else:
                value = operand['value']
            integer(value, -(1 << (size * 8 - 1)), (1 << (size * 8 - 1)) - 1, 'operand')
            encoded.extend(struct.pack('>i' if size == 4 else '>h', value))
        code.extend(struct.pack('>H', word) + encoded)
    if referenced_strings != set(range(len(strings))):
        raise ValueError('event constant strings must all have native data-address references')
    return header + code + constants


def decode_program(data):
    if len(data) < 34 or len(data) % 2:
        raise ValueError('invalid event source extent')
    header = struct.unpack_from('>16H', data)
    if (header[0] & ~0x3800 or header[1] or header[2] != len(data)
            or header[3] % 4 or any(header[5:7]) or any(header[11:])):
        raise ValueError('unsupported unrelocated event header')
    end = header[4] or len(data)
    if not 34 <= end <= len(data) or end % 2:
        raise ValueError('invalid event constant-data boundary')
    instructions, offsets, string_offsets = [], [], set()
    cursor = 32
    while cursor < end:
        offsets.append(cursor)
        word = struct.unpack_from('>H', data, cursor)[0]
        cursor += 2
        op = integer(word & 63, 1, len(ARITY) - 1, 'opcode')
        wide = bool(word & 0x40)
        row = {'opcode': op, 'wide': wide, 'operands': []}
        for index in range(ARITY[op]):
            mode = integer((word >> (13 - index * 3)) & 7, 0, 6, 'operand mode')
            size = 4 if wide and mode in (3, 4, 6) else 2
            if cursor + size > end:
                raise ValueError('truncated event operand')
            value = struct.unpack_from('>i' if size == 4 else '>h', data, cursor)[0]
            cursor += size
            if size == 4:
                wide = False
            field = 'string' if mode == 2 else 'target' if mode == 3 else 'value'
            row['operands'].append({'mode': MODE_NAMES[mode], field: value})
            if mode == 2:
                string_offsets.add(value)
        if wide:
            raise ValueError('event wide flag has no immediate operand')
        instructions.append(row)
    labels = {offset: index for index, offset in enumerate(offsets)}
    string_labels, strings, at = {}, [], end
    for offset in sorted(string_offsets):
        if end == len(data) or offset != at - end:
            raise ValueError('event string references do not cover a contiguous constant pool')
        stop = data.find(b'\0', at)
        if stop < 0:
            raise ValueError('unterminated event constant string')
        try:
            strings.append(data[at:stop].decode('ascii'))
        except UnicodeDecodeError as error:
            raise ValueError('event constant is not reviewed ASCII text') from error
        string_labels[offset] = len(strings) - 1
        at = stop + 1
    for row in instructions:
        for operand in row['operands']:
            if operand['mode'] in ('program-offset', 'data-address'):
                field, lookup = ('target', labels) if operand['mode'] == 'program-offset' else ('string', string_labels)
                if operand[field] not in lookup:
                    raise ValueError('event operand target is not a typed label')
                operand[field] = lookup[operand[field]]
    entries = [32, *header[7:11]]
    if any(entry not in labels for entry in entries):
        raise ValueError('event entrypoint is not an instruction boundary')
    result = {'flags': header[0], 'state_bytes': header[3],
              'entrypoints': [labels[e] for e in entries], 'instructions': instructions, 'strings': strings}
    if encode_program(result) != data:
        raise ValueError('event typed fields do not reproduce all source bytes')
    return result


def encode_bank(records):
    if (not isinstance(records, dict) or set(records) != {'format', 'programs'}
            or records['format'] != FORMAT or not isinstance(records['programs'], list)
            or not 1 <= len(records['programs']) <= 1024):
        raise ValueError('invalid event bank schema')
    programs = records['programs']
    output, table = bytearray(len(programs) * 8), []
    for index, program in enumerate(programs):
        output.extend(bytes(-len(output) % 8))
        offset, size = len(output), 0
        if program is not None:
            payload = encode_program(program)
            compressor = zlib.compressobj(level=6, wbits=-15)
            packed = struct.pack('>I', len(payload)) + compressor.compress(payload) + compressor.flush()
            output.extend(packed)
            size = len(packed) | 0x10000000
        table.append((offset, size | (0x80000000 if index == len(programs) - 1 else 0)))
    output.extend(bytes(-len(output) % 8))
    output[:len(programs) * 8] = b''.join(struct.pack('>II', *row) for row in table)
    return bytes(output)
