"""Fresh RZIP encoding with the independently authored bounded DEFLATE profile."""
import struct
import zlib

try:
    from scripts import deflate_encoder
except ModuleNotFoundError:
    import deflate_encoder


# Keep the reviewed on-disk contract: implementation changes do not alter inputs.
ENCODER = {'format': 'rzip-bounded-deflate-v1', 'level': 6,
           'window_bits': -15, 'hash_bits': 15, 'token_buffer': 16384}


def encode_payload(payload, level=6):
    if type(level) is not int or level != 6:
        raise ValueError('unsupported reviewed bounded DEFLATE level')
    if not isinstance(payload, bytes) or len(payload) > 0xffffffff:
        raise ValueError('bounded DEFLATE requires a native-sized byte payload')
    packed = deflate_encoder.encode(payload)
    try:
        decoder = zlib.decompressobj(-15)
        decoded = decoder.decompress(packed) + decoder.flush()
    except zlib.error as error:
        raise ValueError('bounded DEFLATE failed independent decoding') from error
    if decoded != payload or not decoder.eof or decoder.unused_data or decoder.unconsumed_tail:
        raise ValueError('bounded DEFLATE did not exactly round-trip')
    return struct.pack('>I', len(payload)) + packed
