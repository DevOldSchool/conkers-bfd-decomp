"""Typed bank-02 descriptors and packed source-frame channels, without opaque tails."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import model_assets
except ModuleNotFoundError:
    import model_assets


CLIP_FIELDS = {'header_bytes', 'optional_words', 'translation_mask_words',
               'rotation_channels', 'descriptor_padding', 'frames', 'stream_padding'}
FRAME_FIELDS = {'joint_translations', 'root_offsets', 'rotation_offsets', 'scale_offsets'}
HEADER_FORMAT = '>bBbBbBBBBB'
SPECIAL_DURATION_ENTRIES = (0x92, 0xB7, 0xB8, 0xB9)
FIXED_DURATION_ENTRIES = (0xB7, 0xB8, 0xB9)


def clip_records(descriptor: bytes, stream: bytes, *, runtime_duration: int = 255) -> dict:
    layout = model_assets.parse_character_animation_descriptor(descriptor)
    if layout.frame_trailing_size:
        raise ValueError('animation has unresolved per-frame storage')
    count, tail, _ = model_assets.character_animation_frame_span(
        descriptor, layout, stream, runtime_duration=runtime_duration)
    if len(tail) > 7 or any(tail):
        raise ValueError('animation has unresolved post-duration storage')
    optional_count = bool(layout.flags & 0x40) + bool(layout.flags & 0x20)
    offset = 10 + 2 * optional_count
    mask_size = ((layout.joint_count + 15) // 16) * 2 if layout.flags & 0x80 else 0
    result = {
        'header_bytes': list(struct.unpack_from(HEADER_FORMAT, descriptor)),
        'optional_words': list(struct.unpack_from(f'>{optional_count}H', descriptor, 10)),
        'translation_mask_words': list(struct.unpack_from(f'>{mask_size // 2}H', descriptor, offset)),
        'rotation_channels': [[c.base_value, c.bit_width, c.scale_base_value, c.scale_bit_width]
                              for c in layout.rotation_channels],
        'descriptor_padding': layout.descriptor_padding_size,
        'frames': [], 'stream_padding': len(tail),
    }
    translation_count = sum(layout.joint_translation_mask)
    for index in range(count):
        frame = stream[index * layout.frame_byte_size:(index + 1) * layout.frame_byte_size]
        start = translation_count * 6
        reader = model_assets.CharacterAnimationBitReader(frame[start:])
        roots = [reader.read(width) for width in layout.root_bit_widths]
        rotations, scales = [], []
        for channel in layout.rotation_channels:
            rotations.append(reader.read(channel.bit_width))
            scales.append(None if channel.scale_bit_width is None else reader.read(channel.scale_bit_width))
        alignment_bits = (-reader.bit_offset) % 8
        if reader.read(alignment_bits):
            raise ValueError('animation has nonzero packed alignment bits')
        result['frames'].append({
            'joint_translations': [list(row) for row in struct.iter_unpack('>3h', frame[:start])],
            'root_offsets': roots, 'rotation_offsets': rotations, 'scale_offsets': scales,
        })
    return result


def _padding(size: int) -> bytes:
    if type(size) is not int or not 0 <= size <= 7:
        raise ValueError('animation alignment exceeds seven bytes')
    return bytes(size)


def encode_clip(records: dict, *, runtime_duration: int = 255) -> tuple[bytes, bytes]:
    if not isinstance(records, dict) or set(records) != CLIP_FIELDS:
        raise ValueError('invalid animation clip schema')
    descriptor = bytearray(struct.pack(HEADER_FORMAT, *records['header_bytes']))
    for field in ('optional_words', 'translation_mask_words'):
        descriptor.extend(struct.pack(f'>{len(records[field])}H', *records[field]))
    for base, width, scale_base, scale_width in records['rotation_channels']:
        if (type(base) is not int or not 0 <= base <= 0xffe0 or base & 31
                or type(width) is not int or not 0 <= width <= 15):
            raise ValueError('invalid animation rotation channel')
        if (scale_base is None) != (scale_width is None):
            raise ValueError('incomplete animation scale descriptor')
        descriptor.extend(struct.pack('>H', base | width | (16 if scale_width is not None else 0)))
        if scale_width is not None:
            if (type(scale_base) is not int or not 0 <= scale_base <= 0xfff0 or scale_base & 15
                    or type(scale_width) is not int or not 0 <= scale_width <= 15):
                raise ValueError('invalid animation scale channel')
            descriptor.extend(struct.pack('>H', scale_base | scale_width))
    descriptor.extend(_padding(records['descriptor_padding']))
    descriptor = bytes(descriptor)
    layout = model_assets.parse_character_animation_descriptor(descriptor)
    stream = bytearray()
    for frame in records['frames']:
        if not isinstance(frame, dict) or set(frame) != FRAME_FIELDS:
            raise ValueError('invalid animation frame schema')
        if (len(frame['joint_translations']) != sum(layout.joint_translation_mask)
                or len(frame['root_offsets']) != 3
                or len(frame['rotation_offsets']) != len(layout.rotation_channels)
                or len(frame['scale_offsets']) != len(layout.rotation_channels)):
            raise ValueError('animation frame channel counts disagree with descriptor')
        start = len(stream)
        for xyz in frame['joint_translations']:
            stream.extend(struct.pack('>3h', *xyz))
        values = list(zip(frame['root_offsets'], layout.root_bit_widths))
        for value, scale, channel in zip(frame['rotation_offsets'], frame['scale_offsets'], layout.rotation_channels):
            values.append((value, channel.bit_width))
            if channel.scale_bit_width is None:
                if scale is not None:
                    raise ValueError('animation has an undeclared scale channel')
            else:
                values.append((scale, channel.scale_bit_width))
        bits, width_total = 0, 0
        for value, width in values:
            if type(value) is not int or not 0 <= value < 1 << width:
                raise ValueError('animation offset exceeds its native bit width')
            bits = (bits << width) | value
            width_total += width
        align = (-width_total) % 8
        stream.extend((bits << align).to_bytes((width_total + 7) // 8, 'big'))
        if len(stream) - start != layout.frame_byte_size:
            raise ValueError('animation frame does not cover its native stride')
    stream.extend(_padding(records['stream_padding']))
    stream = bytes(stream)
    if clip_records(descriptor, stream, runtime_duration=runtime_duration) != records:
        raise ValueError('animation records disagree with their native descriptor')
    return descriptor, stream


def animation_segments(payload: bytes) -> tuple[model_assets.ModelSegment, ...]:
    """The animation loader accepts one or more descriptor/stream pairs."""
    if len(payload) < 16:
        raise ValueError('animation is shorter than one descriptor/stream table')
    table_size = struct.unpack_from('>I', payload)[0]
    if table_size < 16 or table_size % 16 or table_size > len(payload):
        raise ValueError('invalid animation paired-segment table')
    parts, cursor = [], table_size
    count = table_size // 8
    for index in range(count):
        offset, flags = struct.unpack_from('>II', payload, index * 8)
        size = flags & 0x0fffffff
        final = bool(flags & 0x80000000)
        if (flags & 0x70000000 or offset != cursor or offset % 8 or size % 8
                or offset + size > len(payload) or final != (index == count - 1)):
            raise ValueError('invalid animation segment extent, alignment or flags')
        parts.append(model_assets.ModelSegment(index, offset, size, final, payload[offset:offset + size]))
        cursor += size
    if cursor != len(payload):
        raise ValueError('animation segments leave uncovered storage')
    return tuple(parts)


def animation_records(payload: bytes, *, entry: int | None = None,
                      runtime_duration: int | None = None) -> dict:
    fixed = runtime_duration is not None
    if fixed:
        if (type(entry) is not int or entry not in FIXED_DURATION_ENTRIES
                or type(runtime_duration) is not int or not 0 < runtime_duration <= 65535):
            raise ValueError('invalid fixed character animation duration')
    elif entry in SPECIAL_DURATION_ENTRIES:
        raise ValueError('character-specific animation duration requires separate native evidence')
    segments = animation_segments(payload)
    result = {'format': 'character-animation-native', 'clips': [
        clip_records(a.data, b.data, runtime_duration=runtime_duration if fixed else 255)
        for a, b in zip(segments[::2], segments[1::2])]}
    if fixed:
        result.update(format='character-animation-fixed-duration', character_entry=entry,
                      runtime_duration=runtime_duration)
    return result


def encode_animation_records(records: dict) -> bytes:
    if not isinstance(records, dict):
        raise ValueError('invalid native animation schema')
    fixed = records.get('format') == 'character-animation-fixed-duration'
    fields = {'format', 'clips', 'character_entry', 'runtime_duration'} if fixed else {'format', 'clips'}
    if set(records) != fields or records['format'] not in ('character-animation-native', 'character-animation-fixed-duration'):
        raise ValueError('invalid native animation schema')
    duration = records['runtime_duration'] if fixed else 255
    if fixed and (type(records['character_entry']) is not int or records['character_entry'] not in FIXED_DURATION_ENTRIES
                  or type(duration) is not int or not 0 < duration <= 65535):
        raise ValueError('invalid fixed character animation duration')
    try:
        parts = [part for clip in records['clips'] for part in encode_clip(clip, runtime_duration=duration)]
        if not parts:
            raise ValueError('animation requires at least one descriptor/stream pair')
        output = bytearray(8 * len(parts))
        for index, part in enumerate(parts):
            struct.pack_into('>II', output, index * 8, len(output),
                             len(part) | (0x80000000 if index == len(parts) - 1 else 0))
            output.extend(part)
        payload = bytes(output)
    except (TypeError, KeyError, IndexError, struct.error, OverflowError) as error:
        raise ValueError('invalid native animation fields') from error
    context = {'entry': records['character_entry'], 'runtime_duration': duration} if fixed else {}
    if animation_records(payload, **context) != records:
        raise ValueError('animation records disagree with their native bundle')
    return payload


def verify_fixed_duration(data: bytes, base: int) -> int:
    """Pin the scalar read by the 0xB7/0xB8/0xB9 branch of func_1505E0C4."""
    offset = model_assets.CHARACTER_ANIMATION_SPECIAL_DURATION_ADDRESS - base
    if offset < 0 or data[offset:offset + 4] != struct.pack('>f', 641.0):
        raise ValueError('ROM fixed character animation duration changed')
    return 641


CONSUMER_SPANS = (
    (0x1502AF04, 284, 'b8f786b34a0b0f6db12c039c68a860a08bd52d1b'),
    (0x1502B110, 276, '34a60e9d42e7e0e2a914bc3a2f37c13d0aba4f8a'),
    (0x150A81D0, 4876, '56cae2497377b0bc66714a4175a2a27a0d78de0a'),
    (0x1502D824, 764, 'e4854df5924f1d8f104a242c76187da4401a88b2'),
    (0x1505E0C4, 1420, '3e17bb649f54edb53a448676e71fbea0adce0e10'),
    (0x1503D484, 140, '40f757370bbf19e10e675591d24421010455453d'),
)


def verify_consumers(code: bytes, base: int) -> None:
    for address, size, digest in CONSUMER_SPANS:
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != digest:
            raise ValueError(f'ROM animation consumer changed at 0x{address:08X}')
