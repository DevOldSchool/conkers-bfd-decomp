"""Native bank-0F animation routes, timed events and behavior programs.

Collision records remain outside this codec. Offsets, sentinels and minimal
alignment are derived; no unknown tail or compressed-byte recipe is retained.
"""
from __future__ import annotations
import math
import struct

FORMAT = 'animation-control-native-v1'


def integer(value, bits):
    if type(value) is not int or not 0 <= value < 1 << bits:
        raise ValueError(f'animation control requires an unsigned {bits}-bit integer')
    return value


def fields(record, names):
    if type(record) is not dict or set(record) != set(names):
        raise ValueError('animation control record has unknown or missing fields')


def sequence(value):
    if type(value) is not list:
        raise ValueError('animation control requires a list')
    return value


def align(data, boundary):
    data.extend(bytes((-len(data)) % boundary))


def encode(record):
    fields(record, ('format', 'routes', 'events', 'actions', 'programs', 'behaviors'))
    if record['format'] != FORMAT:
        raise ValueError('unsupported animation control format')
    routes, events, actions, programs, behaviors = [sequence(record[k]) for k in
        ('routes', 'events', 'actions', 'programs', 'behaviors')]
    out = bytearray(16 + (len(routes) + 1) * 8)
    event_offsets = []
    for stream in events:
        event_offsets.append(len(out) - 16)
        for event in sequence(stream):
            fields(event, ('frame', 'opcode', 'argument'))
            frame = event['frame']
            if type(frame) not in (float, int) or not math.isfinite(frame) or not 0 <= frame < 900:
                raise ValueError('animation event frame is outside the native range')
            # The dispatcher reads byte 7 and the full argument at +8.
            out.extend(struct.pack('>fII', frame, integer(event['opcode'], 8), integer(event['argument'], 32)))
        out.extend(struct.pack('>fII', 999.0, 0, 0))
    action_offset = len(out) if actions else 0
    for action in actions:
        fields(action, ('selector', 'sound', 'response', 'phases'))
        phases = sequence(action['phases'])
        if len(phases) != 3:
            raise ValueError('animation action requires three native phases')
        out.extend(struct.pack('>B3xIBx', integer(action['selector'], 8),
                               integer(action['sound'], 32), integer(action['response'], 8)))
        for phase in phases:
            fields(phase, ('animation', 'speed_percent', 'flags'))
            out.extend(struct.pack('>HBB', integer(phase['animation'], 16),
                                   integer(phase['speed_percent'], 8), integer(phase['flags'], 8)))
        out.extend(bytes(2))
    program_offsets = []
    for program in programs:
        program_offsets.append(len(out) - 16)
        start = len(out)
        for instruction in sequence(program):
            if type(instruction) is not dict:
                raise ValueError('behavior instruction requires a typed record')
            if 'marker' in instruction:
                fields(instruction, ('marker',))
                marker = integer(instruction['marker'], 8)
                if marker < 247:
                    raise ValueError('behavior marker is below the native threshold')
                out.append(marker)
            else:
                fields(instruction, ('opcode', 'parameters'))
                opcode = integer(instruction['opcode'], 8)
                parameters = sequence(instruction['parameters'])
                if opcode >= 247 or len(parameters) != 4:
                    raise ValueError('behavior instruction has invalid opcode or parameters')
                out.extend(bytes([opcode] + [integer(v, 8) for v in parameters]))
        if len(out) == start:
            raise ValueError('empty behavior program')
        align(out, 4)
    behavior_offset = len(out) if behaviors else 0
    used_programs = set()
    for binding in behaviors:
        fields(binding, ('selector', 'program'))
        index = integer(binding['program'], 32)
        if index >= len(programs):
            raise ValueError('behavior program reference is outside the table')
        used_programs.add(index)
        out.extend(struct.pack('>IB3x', program_offsets[index], integer(binding['selector'], 8)))
    if behaviors:
        out.extend(bytes(8))
    if used_programs != set(range(len(programs))):
        raise ValueError('unreferenced behavior program')
    used_events = set()
    for index, route in enumerate(routes):
        fields(route, ('descriptor', 'duration_index', 'event'))
        descriptor = integer(route['descriptor'], 16)
        if descriptor & 1 or descriptor == 999:
            raise ValueError('animation route descriptor is not an even native segment')
        event = route['event']
        pointer = 0
        if event is not None:
            integer(event, 32)
            if event >= len(events):
                raise ValueError('animation event reference is outside the table')
            used_events.add(event)
            pointer = event_offsets[event]
        struct.pack_into('>HHI', out, 16 + index * 8, descriptor,
                         integer(route['duration_index'], 16), pointer)
    if used_events != set(range(len(events))):
        raise ValueError('unreferenced animation event stream')
    struct.pack_into('>HHI', out, 16 + len(routes) * 8, 999, 0, 0)
    struct.pack_into('>4I', out, 0, behavior_offset, 0, action_offset, len(actions) * 24)
    align(out, 16)
    return bytes(out)


def decode(data):
    if len(data) < 32 or len(data) % 16:
        raise ValueError('animation control extent is invalid')
    behavior_offset, collision_offset, action_offset, action_size = struct.unpack_from('>4I', data)
    if collision_offset:
        raise ValueError('collision record fields are not fully established')
    if bool(action_offset) != bool(action_size) or action_size % 24:
        raise ValueError('animation action table extent is invalid')
    routes, event_starts, cursor = [], set(), 16
    while cursor + 8 <= len(data):
        descriptor, duration, event = struct.unpack_from('>HHI', data, cursor)
        cursor += 8
        if descriptor == 999:
            if duration or event:
                raise ValueError('animation route sentinel has payload')
            break
        routes.append({'descriptor': descriptor, 'duration_index': duration, 'event': event})
        if event:
            event_starts.add(event + 16)
    else:
        raise ValueError('animation route sentinel is missing')
    events, event_ids = [], {}
    for start in sorted(event_starts):
        if start != cursor:
            raise ValueError('animation events have unexplained gaps or overlaps')
        event_ids[start - 16] = len(events)
        stream = []
        while cursor + 12 <= len(data):
            frame, opcode, argument = struct.unpack_from('>fII', data, cursor)
            cursor += 12
            if frame == 999.0:
                if opcode or argument:
                    raise ValueError('animation event sentinel has payload')
                break
            if not math.isfinite(frame) or not 0 <= frame < 900 or opcode > 255:
                raise ValueError('animation event fields are outside native limits')
            stream.append({'frame': frame, 'opcode': opcode, 'argument': argument})
        else:
            raise ValueError('animation event sentinel is missing')
        events.append(stream)
    for route in routes:
        route['event'] = event_ids[route['event']] if route['event'] else None
    actions = []
    if action_offset:
        if action_offset != cursor or cursor + action_size > len(data):
            raise ValueError('animation action table is not contiguous')
        for start in range(cursor, cursor + action_size, 24):
            selector, sound, response = struct.unpack_from('>B3xIBx', data, start)
            phases = [{'animation': a, 'speed_percent': b, 'flags': c}
                      for a, b, c in struct.iter_unpack('>HBB', data[start + 10:start + 22])]
            actions.append({'selector': selector, 'sound': sound, 'response': response, 'phases': phases})
        cursor += action_size
    raw_bindings, program_starts = [], set()
    if behavior_offset:
        if behavior_offset < cursor or behavior_offset % 4 or behavior_offset + 8 > len(data):
            raise ValueError('behavior map extent is invalid')
        at = behavior_offset
        while at + 8 <= len(data):
            offset, selector = struct.unpack_from('>IB3x', data, at)
            if any(data[at + 5:at + 8]):
                raise ValueError('behavior map alignment bytes are nonzero')
            at += 8
            if not offset:
                if selector:
                    raise ValueError('behavior map sentinel has payload')
                break
            start = offset + 16
            if start < cursor or start >= behavior_offset or start % 4:
                raise ValueError('behavior program offset is invalid')
            program_starts.add(start)
            raw_bindings.append((selector, start))
        else:
            raise ValueError('behavior map sentinel is missing')
    programs, program_ids = [], {}
    starts = sorted(program_starts)
    for index, start in enumerate(starts):
        if start != cursor:
            raise ValueError('behavior programs have unexplained gaps')
        end = starts[index + 1] if index + 1 < len(starts) else behavior_offset
        instructions = []
        while cursor < end:
            # Only 0..3 bytes can be the derived four-byte alignment. Opcode 0
            # is a native no-op, so complete zero instructions remain editable.
            if end - cursor < 4 and not any(data[cursor:end]):
                break
            opcode = data[cursor]
            if opcode >= 247:
                instructions.append({'marker': opcode})
                cursor += 1
            else:
                if cursor + 5 > end:
                    raise ValueError('behavior program has an unexplained instruction tail')
                instructions.append({'opcode': opcode, 'parameters': list(data[cursor + 1:cursor + 5])})
                cursor += 5
        if (cursor + 3) // 4 * 4 != end or any(data[cursor:end]):
            raise ValueError('behavior alignment differs from native bounds')
        cursor = end
        program_ids[start] = len(programs)
        programs.append(instructions)
    bindings = [{'selector': selector, 'program': program_ids[start]} for selector, start in raw_bindings]
    record = {'format': FORMAT, 'routes': routes, 'events': events, 'actions': actions,
              'programs': programs, 'behaviors': bindings}
    if encode(record) != data:
        raise ValueError('animation control contains unexplained padding or storage')
    return record
