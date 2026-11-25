"""Native menu strings with named inline icons and derived halfword alignment."""
from __future__ import annotations

import struct
import zlib

FORMAT = 'menu-text-native-v1'
# These are native descriptor identities, not inferred artwork names.
ICONS = {f'descriptor_{address:08X}': code for address, code in
         ((0x80091710, 0xB6), (0x80091720, 0xB7),
          (0x80091730, 0xB8), (0x80091740, 0xB9))}
# Printable input bytes present in the checked font map, lowercase folding,
# space, and the menu's literal '*' section marker. No arbitrary byte escape.
TEXT = frozenset('0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
                 '&\\^:,$"=!.>#{([<-%+?})];/~\'@ *')
MAX_SIZE = 65536


def encode(source: dict) -> bytes:
    if (type(source) is not dict or set(source) != {'format', 'strings'}
            or source['format'] != FORMAT or type(source['strings']) is not list
            or not 1 <= len(source['strings']) <= 4096):
        raise ValueError('menu text requires a bounded list of native strings')
    out = bytearray()
    for segments in source['strings']:
        if type(segments) is not list or not segments:
            raise ValueError('menu string requires text or icon segments')
        for segment in segments:
            if type(segment) is str and segment and set(segment) <= TEXT:
                out.extend(segment.encode('ascii'))
            elif (type(segment) is dict and set(segment) == {'icon'}
                  and type(segment['icon']) is str and segment['icon'] in ICONS):
                out.append(ICONS[segment['icon']])
            else:
                raise ValueError('unsupported menu text or inline icon')
        # One NUL terminator, then the minimum zero padding for the next u16.
        out.extend(bytes(2 - len(out) % 2))
        if len(out) > MAX_SIZE:
            raise ValueError('menu text exceeds the reviewed size bound')
    return bytes(out)


def decode(data: bytes) -> dict:
    if not data or len(data) > MAX_SIZE or len(data) % 2:
        raise ValueError('menu text must end at a halfword boundary')
    strings, cursor = [], 0
    reverse = {value: name for name, value in ICONS.items()}
    while cursor < len(data):
        end = data.find(b'\0', cursor)
        if end <= cursor:
            raise ValueError('empty or unterminated native menu string')
        segments, text = [], ''
        for byte in data[cursor:end]:
            if byte in reverse:
                if text:
                    segments.append(text)
                    text = ''
                segments.append({'icon': reverse[byte]})
            elif chr(byte) in TEXT:
                text += chr(byte)
            else:
                raise ValueError('unproved menu character code')
        if text:
            segments.append(text)
        strings.append(segments)
        following = end + 2 - end % 2
        if following > len(data) or any(data[end:following]):
            raise ValueError('menu string has invalid halfword alignment')
        cursor = following
    source = {'format': FORMAT, 'strings': strings}
    if encode(source) != data:
        raise ValueError('menu text does not reproduce native storage')
    return source


def compress(data: bytes) -> bytes:
    compressor = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def unpack(blob: bytes) -> bytes:
    if len(blob) < 5:
        raise ValueError('truncated menu text stream')
    size = struct.unpack_from('>I', blob)[0]
    if not 2 <= size <= MAX_SIZE or size % 2:
        raise ValueError('invalid menu text decoded size')
    decoder = zlib.decompressobj(wbits=-15)
    try:
        data = decoder.decompress(blob[4:], size + 1)
    except zlib.error as error:
        raise ValueError('invalid menu text compressed stream') from error
    if (len(data) != size or not decoder.eof or decoder.unused_data
            or decoder.unconsumed_tail):
        raise ValueError('menu text stream has an invalid extent')
    decode(data)
    return data
