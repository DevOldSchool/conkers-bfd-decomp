"""Typed Conker compact-sequence events and native back-reference encoding."""
from __future__ import annotations

import struct

try:
    from scripts import audio_assets, audio_consumers
except ModuleNotFoundError:
    import audio_assets
    import audio_consumers


class RecordReader(audio_assets.CompactTrackReader):
    def __init__(self, *args):
        super().__init__(*args)
        self.logical_offset = 0
        self.references = []

    def read_byte(self):
        start = self.cursor
        backup = self.backup_remaining
        value = super().read_byte()
        if not backup and self.data[start] == 0xFE and self.data[start + 1] != 0xFE:
            self.references.append([self.logical_offset,
                                    int.from_bytes(self.data[start + 1:start + 3], 'big'),
                                    self.data[start + 3]])
        self.logical_offset += 1
        return value

    def physical(self, length):
        if self.backup_remaining:
            raise ValueError('loop payload overlaps an active back-reference')
        result = self.read_physical(length)
        self.logical_offset += length
        return result

    def variable(self):
        value = 0
        for width in range(1, 6):
            byte = self.read_byte()
            value = (value << 7) | (byte & 127)
            if not byte & 128:
                if value > 0x0FFFFFFF:
                    raise ValueError('sequence variable-length value exceeds its supported range')
                return value, width
        raise ValueError('sequence variable-length value exceeds five bytes')


def parse_records(data):
    if len(data) < 68:
        raise ValueError('sequence header is truncated')
    words = struct.unpack_from('>17I', data)
    offsets, division = list(words[:16]), words[16]
    active = sorted(o for o in offsets if o)
    if (not active or len(active) != len(set(active)) or active[0] != 68
            or active[-1] >= len(data) or not 0 < division <= 0x7FFF):
        raise ValueError('sequence header has unsupported ranges or division')
    tracks = []
    for index, start in enumerate(offsets):
        if not start:
            tracks.append(None)
            continue
        end = next((o for o in active if o > start), len(data))
        reader = RecordReader(data, start, end, index)
        events, running = [], 0
        for _ in range(1_000_000):
            delta, width = reader.variable()
            event = {'delta': delta, 'delta_width': width}
            status = reader.read_byte()
            if status == 255:
                kind = reader.read_byte()
                if kind == 0x51:
                    event.update(kind='tempo', tempo_us=int.from_bytes(bytes(reader.read_byte() for _ in range(3)), 'big'))
                elif kind == 0x2E:
                    event.update(kind='loop_start', marker_value=(reader.read_byte() << 8) | reader.read_byte())
                elif kind == 0x2D:
                    raw = reader.physical(6)
                    event.update(kind='loop_end', repeat_count=raw[0], current_count=raw[1],
                                 back_offset=int.from_bytes(raw[2:], 'big'))
                elif kind == 0x2F:
                    event.update(kind='end')
                    events.append(event)
                    break
                else:
                    raise ValueError('unsupported sequence meta-event')
                running = 0
            else:
                explicit = status if status & 128 else None
                if explicit is not None:
                    if not 0x80 <= explicit <= 0xEF:
                        raise ValueError('unsupported sequence MIDI status')
                    running = (explicit & 0xF0) | index
                    first = reader.read_byte()
                else:
                    if not running:
                        raise ValueError('sequence running status is unset')
                    first = status
                values = [first]
                message_type = running & 0xF0
                if message_type not in (0xC0, 0xD0):
                    values.append(reader.read_byte())
                if any(value & 128 for value in values):
                    raise ValueError('sequence MIDI data has its high bit set')
                duration, duration_width = reader.variable() if message_type == 0x90 else (None, None)
                event.update(kind='midi', status=explicit, data=values, duration=duration, duration_width=duration_width)
            events.append(event)
        else:
            raise ValueError('sequence event limit exceeded')
        if reader.cursor != end or reader.backup_remaining:
            raise ValueError('sequence track leaves unconsumed physical or referenced bytes')
        tracks.append({'events': events, 'back_references': reader.references})
    return {'format': 'conker-compact-sequence', 'track_offsets': offsets,
            'division': division, 'tracks': tracks}


def variable(value, width):
    if type(value) is not int or type(width) is not int or not 1 <= width <= 5:
        raise ValueError('invalid sequence variable-length field')
    data = audio_assets._encode_varlen(value)
    if len(data) > width:
        raise ValueError('sequence variable-length width is too short')
    return bytes([128]) * (width - len(data)) + data


def unsigned(value, width):
    if type(value) is not int or not 0 <= value < (1 << (8 * width)):
        raise ValueError('invalid native unsigned sequence field')
    return value.to_bytes(width, 'big')


def logical_track(events, track):
    if not isinstance(events, list) or not events:
        raise ValueError('sequence track has no events')
    data, physical = bytearray(), []
    running = 0
    def add(value, raw=False):
        data.extend(value)
        physical.extend([raw] * len(value))
    base = {'delta', 'delta_width', 'kind'}
    for position, event in enumerate(events):
        if not isinstance(event, dict) or not base <= set(event):
            raise ValueError('invalid sequence event schema')
        add(variable(event['delta'], event['delta_width']))
        kind = event['kind']
        if kind == 'midi':
            if set(event) != base | {'status', 'data', 'duration', 'duration_width'}:
                raise ValueError('invalid MIDI event fields')
            status = event['status']
            if status is not None:
                if type(status) is not int or not 0x80 <= status <= 0xEF:
                    raise ValueError('invalid MIDI status')
                add(bytes([status]))
                running = (status & 0xF0) | track
            if not running:
                raise ValueError('sequence running status is unset')
            message_type = running & 0xF0
            values = event['data']
            if (not isinstance(values, list) or len(values) != (1 if message_type in (0xC0, 0xD0) else 2)
                    or any(type(v) is not int or not 0 <= v < 128 for v in values)):
                raise ValueError('invalid MIDI data fields')
            add(bytes(values))
            if message_type == 0x90:
                add(variable(event['duration'], event['duration_width']))
            elif event['duration'] is not None or event['duration_width'] is not None:
                raise ValueError('duration belongs only to note-on events')
        else:
            running = 0
            if kind == 'tempo' and set(event) == base | {'tempo_us'}:
                add(b'\xff\x51' + unsigned(event['tempo_us'], 3))
            elif kind == 'loop_start' and set(event) == base | {'marker_value'}:
                add(b'\xff\x2e' + unsigned(event['marker_value'], 2))
            elif kind == 'loop_end' and set(event) == base | {'repeat_count', 'current_count', 'back_offset'}:
                add(b'\xff\x2d')
                add(unsigned(event['repeat_count'], 1) + unsigned(event['current_count'], 1)
                    + unsigned(event['back_offset'], 4), raw=True)
            elif kind == 'end' and set(event) == base and position == len(events) - 1:
                add(b'\xff\x2f')
            else:
                raise ValueError('invalid sequence meta-event fields or position')
    if events[-1]['kind'] != 'end':
        raise ValueError('sequence track lacks end-of-track')
    return bytes(data), physical


def pack_track(record, track):
    if not isinstance(record, dict) or set(record) != {'events', 'back_references'}:
        raise ValueError('invalid sequence track schema')
    logical, physical = logical_track(record['events'], track)
    refs, previous_end = {}, 0
    if not isinstance(record['back_references'], list):
        raise ValueError('invalid sequence back-reference list')
    for row in record['back_references']:
        if not isinstance(row, list) or len(row) != 3 or any(type(v) is not int for v in row):
            raise ValueError('invalid sequence back-reference fields')
        offset, distance, length = row
        if (offset < previous_end or not 0 <= distance <= 65535 or distance >> 8 == 0xFE
                or not 1 <= length <= 255 or offset + length > len(logical)
                or any(physical[offset:offset + length])):
            raise ValueError('unsupported sequence back-reference range')
        refs[offset] = distance, length
        previous_end = offset + length
    output, cursor = bytearray(), 0
    while cursor < len(logical):
        if cursor in refs:
            distance, length = refs[cursor]
            output.extend(struct.pack('>BHB', 0xFE, distance, length))
            cursor += length
        else:
            value = logical[cursor]
            output.append(value)
            if value == 0xFE and not physical[cursor]:
                output.append(value)
            cursor += 1
    return bytes(output)


def encode_records(records):
    if (not isinstance(records, dict) or set(records) != {'format', 'track_offsets', 'division', 'tracks'}
            or records['format'] != 'conker-compact-sequence'
            or not isinstance(records['tracks'], list) or len(records['tracks']) != 16
            or not isinstance(records['track_offsets'], list) or len(records['track_offsets']) != 16):
        raise ValueError('invalid sequence record schema')
    try:
        output = bytearray(b''.join(unsigned(value, 4)
                                   for value in [*records['track_offsets'], records['division']]))
        active = []
        for index, (offset, track) in enumerate(zip(records['track_offsets'], records['tracks'])):
            if not offset:
                if track is not None:
                    raise ValueError('inactive sequence track contains events')
            else:
                active.append((offset, index, pack_track(track, index)))
        for offset, index, data in sorted(active):
            if offset != len(output):
                raise ValueError('sequence tracks overlap or leave an uncovered gap')
            output.extend(data)
    except (struct.error, TypeError, OverflowError, AttributeError) as error:
        raise ValueError('invalid native sequence field') from error
    payload = bytes(output)
    if parse_records(payload) != records:
        raise ValueError('sequence events or back-references disagree after encoding')
    return payload


def verify_consumers(rom):
    audio_consumers.verify_spans(rom, audio_consumers.SEQUENCE, 'compact-sequence')
