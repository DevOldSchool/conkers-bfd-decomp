"""Native dialogue pages, renderer controls and 16-bit audio IDs."""
from __future__ import annotations

import struct
import zlib

try:
    from scripts.menu_text_codec import TEXT
except ModuleNotFoundError:
    from menu_text_codec import TEXT

FORMAT = 'dialogue-pages-native-v1'
MAX_SIZE = 65536
# Dynamic icon frames come from D_800CBD4E, not another source byte.
CONTROLS = {
    'pulse': 0xA6,
    'descriptor_800915DC': 0xA8,
    'descriptor_800915EC': 0xA9,
    'descriptor_800915FC': 0xAE,
    'descriptor_8009160C': 0xAF,
    'descriptor_80091690_animated': 0xB1,
    'descriptor_800916AC_animated': 0xB2,
    'descriptor_800916E4_animated': 0xB3,
    'descriptor_800916C8_animated': 0xB4,
    'descriptor_80091700_animated': 0xB5,
    'descriptor_80091750': 0xBA,
}


def encode(source: dict) -> bytes:
    if (type(source) is not dict or set(source) != {'format', 'pages', 'audio_ids'}
            or source['format'] != FORMAT or type(source['pages']) is not list
            or not 1 <= len(source['pages']) <= 255 or type(source['audio_ids']) is not list
            or len(source['audio_ids']) > 255):
        raise ValueError('invalid native dialogue source')
    pages = []
    for page in source['pages']:
        if type(page) is not list or not page:
            raise ValueError('dialogue page must contain text or controls')
        data = bytearray()
        for segment in page:
            if type(segment) is str and segment and set(segment) <= TEXT | {'\n'}:
                data.extend(segment.encode('ascii'))
            elif (type(segment) is dict and set(segment) == {'control'}
                  and type(segment['control']) is str and segment['control'] in CONTROLS):
                data.append(CONTROLS[segment['control']])
            else:
                raise ValueError('unsupported dialogue text or renderer control')
        pages.append(bytes(data))
    text = b'\xBD'.join(pages)
    text += bytes(2 - len(text) % 2)  # NUL plus minimal halfword alignment.
    if len(text) > MAX_SIZE:
        raise ValueError('dialogue text exceeds size bound')
    for value in source['audio_ids']:
        if type(value) is not int or not 0 <= value <= 0xFFFF:
            raise ValueError('dialogue audio ID must be an unsigned halfword')
    audio = struct.pack(f'>{len(source["audio_ids"])}H', *source['audio_ids'])
    audio_offset = (16 + len(text) + 7) & ~7
    out = bytearray(struct.pack('>4I', 16, len(text), audio_offset, 0x80000000 | len(audio)))
    out.extend(text)
    out.extend(bytes(audio_offset - len(out)))
    out.extend(audio)
    out.extend(bytes((-len(out)) % 8))
    if len(out) > MAX_SIZE:
        raise ValueError('dialogue record exceeds size bound')
    return bytes(out)


def decode(data: bytes) -> dict:
    if not 16 <= len(data) <= MAX_SIZE or len(data) % 8:
        raise ValueError('invalid dialogue record extent')
    offset, text_size, audio_offset, audio_word = struct.unpack_from('>4I', data)
    audio_size = audio_word & 0x0FFFFFFF
    if (offset != 16 or not 2 <= text_size <= len(data) - offset
            or text_size % 2 or audio_word >> 28 != 8 or audio_size % 2
            or audio_offset < offset + text_size or audio_offset + audio_size > len(data)):
        raise ValueError('invalid dialogue child directory')
    text = data[offset:offset + text_size]
    end = text.find(b'\0')
    if end < 1 or text[end:] != bytes(2 - end % 2):
        raise ValueError('dialogue needs one terminator and minimal halfword alignment')
    reverse = {value: name for name, value in CONTROLS.items()}
    pages = []
    for page in text[:end].split(b'\xBD'):
        segments, literal = [], ''
        for byte in page:
            if byte in reverse:
                if literal:
                    segments.append(literal)
                    literal = ''
                segments.append({'control': reverse[byte]})
            elif chr(byte) in TEXT | {'\n'}:
                literal += chr(byte)
            else:
                raise ValueError('unproved dialogue character code')
        if literal:
            segments.append(literal)
        pages.append(segments)
    source = {'format': FORMAT, 'pages': pages,
              'audio_ids': list(struct.unpack_from(f'>{audio_size // 2}H', data, audio_offset))}
    if encode(source) != data:
        raise ValueError('dialogue has unexplained padding or storage')
    return source


def compress(data: bytes) -> bytes:
    stream = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + stream.compress(data) + stream.flush()


def unpack(blob: bytes) -> bytes:
    if len(blob) < 5:
        raise ValueError('truncated dialogue stream')
    size = struct.unpack_from('>I', blob)[0]
    if not 16 <= size <= MAX_SIZE or size % 8:
        raise ValueError('invalid dialogue decoded size')
    stream = zlib.decompressobj(wbits=-15)
    try:
        data = stream.decompress(blob[4:], size + 1)
    except zlib.error as error:
        raise ValueError('invalid compressed dialogue') from error
    if (len(data) != size or not stream.eof or stream.unused_data or stream.unconsumed_tail):
        raise ValueError('invalid dialogue stream extent')
    decode(data)
    return data
