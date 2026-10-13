"""Native MPEG-2 mono scalefactor and quantized-coefficient reconstruction.

The default encoder returns complete frames. The partial mode also regenerates
remaining headers and whole coefficient bytes before the final reservoir bit.
Incomplete bytes, opaque post-frame cues and other trailing storage are excluded.
"""
from __future__ import annotations

from functools import lru_cache
from pathlib import Path

try:
    from scripts import mp3_assets, mp3_table_codec
except ModuleNotFoundError:
    import mp3_assets
    import mp3_table_codec

ROOT = Path(__file__).resolve().parent.parent
FORMAT = 'conker-mpeg2-coefficients-v1'
SEED_SOURCE = Path('lib/libultrare/src/libultrare/mp3/decoder.c')
# Literal decoder.c tables: var700577d8, var70057860[VERSION_2][0],
# and mp3dec00041600's non-intensity-stereo scalefactor partition counts.
LINBITS = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           1, 2, 3, 4, 6, 8, 10, 13, 4, 5, 6, 7, 8, 9, 11, 13, -1, -1)
LONG_BOUNDS = (6, 12, 18, 24, 30, 36, 44, 54, 66, 80, 96, 116,
               140, 168, 200, 238, 284, 336, 396, 464, 522, 576)
SCALE_COUNTS = (((6, 5, 5, 5), (9, 9, 9, 9), (6, 9, 9, 9)),
                ((6, 5, 7, 3), (9, 9, 12, 6), (6, 9, 12, 6)),
                ((11, 10, 0, 0), (18, 18, 0, 0), (15, 18, 0, 0)))
HEADER_FIELDS = (('sync', 11), ('version', 2), ('layer', 2), ('protection', 1),
                 ('bitrate', 4), ('sample_rate', 2), ('padding', 1), ('private', 1),
                 ('mode', 2), ('mode_extension', 2), ('copyright', 1),
                 ('original', 1), ('emphasis', 2))
SIDE_PREFIX = (('main_data_begin', 8), ('private_bit', 1), ('part2_3_length', 12),
               ('big_values', 9), ('global_gain', 8), ('scalefac_compress', 9),
               ('window_switching', 1))
SIDE_SUFFIX = (('scalefac_scale', 1), ('count1table_select', 1))
FRAME_FIELDS = {'header', 'side_info', 'scalefactors', 'big_pairs', 'count1_quads'}


def fixed(value, width):
    if type(value) is not int or not 0 <= value < 1 << width:
        raise ValueError('MPEG integer outside its native field width')
    return format(value, f'0{width}b') if width else ''


@lru_cache(maxsize=1)
def huffman_tables():
    seeds = mp3_table_codec.seed_records((ROOT / SEED_SOURCE).read_text())
    books = [None] + [seeds['codebooks'][name] for name in seeds['table_codebooks'][1:]]
    tries, codes = [], []
    for book in books:
        trie, lookup = {}, {}
        for x, y, width, code in book or []:
            bits = ''.join(str((code >> i) & 1) for i in range(width))
            cursor = trie
            for bit in bits:
                cursor = cursor.setdefault(int(bit), {})
            cursor['leaf'] = (x, y)
            lookup[x, y] = bits
        tries.append(trie)
        codes.append(lookup)
    return tries, codes


class Reader:
    def __init__(self, data, start=0):
        self.data, self.at = data, start

    def read(self, width):
        if self.at < 0 or width < 0 or self.at + width > len(self.data) * 8:
            raise ValueError('MPEG bit read exceeds its reservoir')
        if not width:
            return 0
        start, end = self.at // 8, (self.at + width + 7) // 8
        shift = end * 8 - self.at - width
        value = (int.from_bytes(self.data[start:end], 'big') >> shift) & ((1 << width) - 1)
        self.at += width
        return value

    def symbol(self, book):
        tables = huffman_tables()[0]
        if type(book) is not int or not 0 <= book < len(tables) or book in (4, 14) or not tables[book]:
            raise ValueError('invalid or empty MPEG Huffman codebook')
        cursor = tables[book]
        while 'leaf' not in cursor:
            bit = self.read(1)
            if bit not in cursor:
                raise ValueError('invalid MPEG Huffman code')
            cursor = cursor[bit]
        return cursor['leaf']


def encode_header(header):
    if not isinstance(header, dict) or set(header) != {name for name, _ in HEADER_FIELDS}:
        raise ValueError('invalid MPEG header schema')
    bits = ''.join(fixed(header[name], width) for name, width in HEADER_FIELDS)
    if (any(header[name] != value for name, value in
            (('sync', 0x7ff), ('version', 2), ('layer', 1), ('protection', 1),
             ('sample_rate', 0), ('mode', 3))) or not 1 <= header['bitrate'] <= 14):
        raise ValueError('unsupported MPEG version, rate, channels, CRC or bitrate')
    return int(bits, 2).to_bytes(4, 'big')


def frame_size(header):
    encode_header(header)
    return 72000 * mp3_assets.MPEG2_LAYER3_BITRATES[header['bitrate']] // 22050 + header['padding']


def encode_side(side):
    common = {name for name, _ in SIDE_PREFIX + SIDE_SUFFIX} | {
        'block_type', 'mixed_block_flag', 'table_select'}
    if not isinstance(side, dict) or 'window_switching' not in side:
        raise ValueError('invalid MPEG side-info schema')
    extra = {'subblock_gain'} if side['window_switching'] else {'region0_count', 'region1_count'}
    if set(side) != common | extra:
        raise ValueError('invalid MPEG side-info fields')
    bits = ''.join(fixed(side[name], width) for name, width in SIDE_PREFIX)
    if side['big_values'] > 288:
        raise ValueError('MPEG big-values region exceeds 576 coefficients')
    tables = side['table_select']
    if not isinstance(tables, list) or len(tables) != 3:
        raise ValueError('MPEG requires three table selectors')
    table_bits = [fixed(value, 5) for value in tables]
    fixed(side['block_type'], 2)
    fixed(side['mixed_block_flag'], 1)
    if side['window_switching']:
        if not side['block_type'] or tables[2] != 0:
            raise ValueError('invalid switched MPEG block')
        gains = side['subblock_gain']
        if not isinstance(gains, list) or len(gains) != 3:
            raise ValueError('MPEG requires three subblock gains')
        bits += fixed(side['block_type'], 2) + fixed(side['mixed_block_flag'], 1)
        bits += ''.join(table_bits[:2]) + ''.join(fixed(value, 3) for value in gains)
    else:
        if side['block_type'] or side['mixed_block_flag']:
            raise ValueError('long MPEG block has switched-block fields')
        bits += ''.join(table_bits) + fixed(side['region0_count'], 4) + fixed(side['region1_count'], 3)
        if (side['big_values'] * 2 > LONG_BOUNDS[side['region0_count']]
                and side['region0_count'] + side['region1_count'] + 1 >= len(LONG_BOUNDS)):
            raise ValueError('MPEG region index exceeds the scalefactor bands')
    bits += ''.join(fixed(side[name], width) for name, width in SIDE_SUFFIX)
    return int(bits, 2).to_bytes(9, 'big')


def parse_side(raw):
    if len(raw) != 9:
        raise ValueError('truncated MPEG side information')
    reader = Reader(raw)
    side = {name: reader.read(width) for name, width in SIDE_PREFIX}
    if side['window_switching']:
        side.update(block_type=reader.read(2), mixed_block_flag=reader.read(1),
                    table_select=[reader.read(5), reader.read(5), 0],
                    subblock_gain=[reader.read(3) for _ in range(3)])
    else:
        side.update(block_type=0, mixed_block_flag=0,
                    table_select=[reader.read(5) for _ in range(3)],
                    region0_count=reader.read(4), region1_count=reader.read(3))
    side.update({name: reader.read(width) for name, width in SIDE_SUFFIX})
    if encode_side(side) != raw:
        raise ValueError('MPEG side information does not round-trip')
    return side


def scale_widths(side):
    value = side['scalefac_compress']
    if value < 400:
        widths, group = [(value >> 4) // 5, (value >> 4) % 5, (value % 16) >> 2, value % 4], 0
    elif value < 500:
        widths, group = [((value - 400) >> 2) // 5, ((value - 400) >> 2) % 5, (value - 400) % 4, 0], 1
    else:
        widths, group = [(value - 500) // 3, (value - 500) % 3, 0, 0], 2
    mode = side['mixed_block_flag'] + 1 if side['window_switching'] and side['block_type'] == 2 else 0
    return [width for width, count in zip(widths, SCALE_COUNTS[group][mode]) for _ in range(count)]


def region_bounds(side):
    limit = side['big_values'] * 2
    if not side['window_switching']:
        first = min(LONG_BOUNDS[side['region0_count']], limit)
        second = min(LONG_BOUNDS[side['region0_count'] + side['region1_count'] + 1], limit) if first < limit else limit
    else:
        first = min(36 if side['block_type'] == 2 and not side['mixed_block_flag'] else LONG_BOUNDS[7], limit)
        second = limit
    return first, second, limit


def decode_granule(main, start, side):
    reader = Reader(main, start)
    scales = [reader.read(width) for width in scale_widths(side)]
    pairs, quads, count = [], [], 0
    for book, end in zip(side['table_select'], region_bounds(side)):
        while count < end:
            values = []
            for value in reader.symbol(book) if book else (0, 0):
                if value == 15 and LINBITS[book] > 0:
                    value += reader.read(LINBITS[book])
                if value and reader.read(1):
                    value = -value
                values.append(value)
            pairs.append(values)
            count += 2
    while reader.at < start + side['part2_3_length'] and count < 576:
        pattern, _ = reader.symbol(side['count1table_select'] + 32)
        quad = []
        for bit in (3, 2, 1, 0):
            value = (pattern >> bit) & 1
            if value and reader.read(1):
                value = -value
            quad.append(value)
        quads.append(quad)
        count += 4
    if reader.at != start + side['part2_3_length']:
        raise ValueError('MPEG granule does not consume its exact declared bit extent')
    return {'scalefactors': scales, 'big_pairs': pairs, 'count1_quads': quads}


def encode_granule(frame):
    side = frame['side_info']
    widths, scales = scale_widths(side), frame['scalefactors']
    if not isinstance(scales, list) or len(scales) != len(widths):
        raise ValueError('MPEG scalefactor count differs from its partitions')
    chunks = [fixed(value, width) for value, width in zip(scales, widths)]
    pairs, quads = frame['big_pairs'], frame['count1_quads']
    if (not isinstance(pairs, list) or len(pairs) != side['big_values']
            or not isinstance(quads, list) or len(quads) > (576 - 2 * len(pairs) + 3) // 4):
        raise ValueError('MPEG coefficient count differs from its declared regions')
    codes = huffman_tables()[1]
    at = 0
    for book, end in zip(side['table_select'], region_bounds(side)):
        while at * 2 < end:
            pair = pairs[at]
            at += 1
            if not isinstance(pair, list) or len(pair) != 2 or any(type(v) is not int for v in pair):
                raise ValueError('MPEG pair must contain two signed integers')
            if not book:
                if pair != [0, 0]:
                    raise ValueError('MPEG null codebook requires zero coefficients')
                continue
            magnitudes = [abs(v) for v in pair]
            symbol = tuple(min(v, 15) if LINBITS[book] > 0 else v for v in magnitudes)
            if symbol not in codes[book]:
                raise ValueError('MPEG coefficient pair is absent from its codebook')
            chunks.append(codes[book][symbol])
            for value, magnitude, small in zip(pair, magnitudes, symbol):
                if small == 15 and LINBITS[book] > 0:
                    chunks.append(fixed(magnitude - 15, LINBITS[book]))
                if magnitude:
                    chunks.append(str(int(value < 0)))
    book = side['count1table_select'] + 32
    for quad in quads:
        if (not isinstance(quad, list) or len(quad) != 4
                or any(type(v) is not int or v not in (-1, 0, 1) for v in quad)):
            raise ValueError('MPEG count1 region requires signed unit coefficients')
        pattern = sum(abs(v) << (3 - i) for i, v in enumerate(quad))
        chunks.append(codes[book][pattern, pattern])
        chunks.extend(str(int(v < 0)) for v in quad if v)
    bits = ''.join(chunks)
    if len(bits) != side['part2_3_length']:
        raise ValueError('MPEG encoded granule length differs from side information')
    return bits


def encode_stream(records, *, include_partial=False):
    """Encode complete frames, optionally including bounded final-frame fields.

    A byte containing any unproved reservoir bits is omitted in its entirety.
    Headers and side information are independent typed fields in every frame.
    """
    if (not isinstance(records, dict) or set(records) != {'format', 'frames'}
            or records['format'] != FORMAT or not isinstance(records['frames'], list)
            or not 1 <= len(records['frames']) <= 100000):
        raise ValueError('invalid MPEG coefficient source schema')
    layout, physical, main_size = [], 0, 0
    for frame in records['frames']:
        if not isinstance(frame, dict) or set(frame) != FRAME_FIELDS:
            raise ValueError('invalid MPEG frame source fields')
        header = encode_header(frame['header'])
        info = encode_side(frame['side_info'])
        size = frame_size(frame['header'])
        layout.append((physical, main_size, size, header, info))
        physical += size + (9 if frame['header']['copyright'] else 0)
        main_size += size - 13
    # A bit per byte keeps writes and exact-range checks simple; each stream is
    # bounded independently. No original bitstream is available to this encoder.
    reservoir = bytearray(b'0' * (main_size * 8))
    previous_end = 0
    for frame, (_, position, _, _, _) in zip(records['frames'], layout):
        start = (position - frame['side_info']['main_data_begin']) * 8
        bits = encode_granule(frame).encode()
        end = start + len(bits)
        if start < previous_end or end > len(reservoir):
            raise ValueError('MPEG granules overlap or exceed the bit reservoir')
        reservoir[start:end] = bits
        previous_end = end
    main = int(reservoir, 2).to_bytes(main_size, 'big')
    spans = []
    for offset, position, size, header, info in layout:
        end = position + size - 13
        if end * 8 > previous_end and not include_partial:
            break
        # Floor at the last encoded bit; never invent the rest of its byte.
        proved_end = min(end, max(position, previous_end // 8)) if include_partial else end
        payload = header + info + main[position:proved_end]
        if spans and spans[-1][0] + len(spans[-1][1]) == offset:
            spans[-1][1].extend(payload)
        else:
            spans.append([offset, bytearray(payload)])
    if not spans:
        raise ValueError('MPEG stream has no fully reconstructed physical frames')
    return [(offset, bytes(payload)) for offset, payload in spans]


def scan_stream(data):
    """Read native framing and reservoir coordinates without decoding coefficients."""
    frames, positions, main, offset = [], [], bytearray(), 0
    while (parsed := mp3_assets.parse_mpeg_layer3_header(data, offset)) is not None:
        if offset + parsed.frame_size > len(data):
            raise ValueError('MPEG frame exceeds original stream')
        reader = Reader(data[offset:offset + 4])
        header = {name: reader.read(width) for name, width in HEADER_FIELDS}
        if frame_size(header) != parsed.frame_size:
            raise ValueError('MPEG frame extent differs from independent header parser')
        side = parse_side(data[offset + 4:offset + 13])
        positions.append(len(main))
        main.extend(data[offset + 13:offset + parsed.frame_size])
        frames.append({'header': header, 'side_info': side})
        offset += parsed.frame_size
        if header['copyright']:
            if data[offset:offset + 2] != b'L:' or len(data[offset:offset + 9]) != 9 or data[offset + 8] != 0:
                raise ValueError('unsupported opaque post-frame cue framing')
            offset += 9
    if not frames:
        raise ValueError('MPEG stream has no reviewed frames')
    return frames, positions, main, offset


def reviewed_ranges(data, *, include_partial=False):
    """Derive physical frame ranges from independently parsed original framing."""
    frames, positions, main, _ = scan_stream(data)
    previous_end = 0
    for frame, position in zip(frames, positions):
        side = frame['side_info']
        start = (position - side['main_data_begin']) * 8
        end = start + side['part2_3_length']
        if start < previous_end or end > len(main) * 8:
            raise ValueError('original MPEG reservoir extents overlap or exceed storage')
        previous_end = end
    ranges, offset, selected = [], 0, 0
    for frame, position in zip(frames, positions):
        size = frame_size(frame['header'])
        if (position + size - 13) * 8 > previous_end and not include_partial:
            break
        proved_size = 13 + min(size - 13, max(0, previous_end // 8 - position)) if include_partial else size
        end = offset + proved_size
        if ranges and ranges[-1][1] == offset:
            ranges[-1][1] = end
        else:
            ranges.append([offset, end])
        offset += size + (9 if frame['header']['copyright'] else 0)
        selected += 1
    if not ranges:
        raise ValueError('original MPEG stream has no whole creditable frames')
    return ranges, len(frames), selected


def decode_stream(data):
    """Recover semantic records, independently checking every granule and span."""
    frames, positions, main, _ = scan_stream(data)
    original_bits = ''.join(f'{value:08b}' for value in main)
    for frame, position in zip(frames, positions):
        start = (position - frame['side_info']['main_data_begin']) * 8
        frame.update(decode_granule(main, start, frame['side_info']))
        encoded = encode_granule(frame)
        if encoded != original_bits[start:start + len(encoded)]:
            raise ValueError('MPEG coefficients fail independent original-bit comparison')
    records = {'format': FORMAT, 'frames': frames}
    for start, payload in encode_stream(records):
        if payload != data[start:start + len(payload)]:
            raise ValueError('MPEG frame records fail independent original-byte comparison')
    return records
