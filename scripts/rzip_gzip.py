"""Pinned GNU gzip DEFLATE encoding shared by model and texture RZIP assets."""
import functools
import struct
import subprocess
import zlib

try:
    from scripts import rzip_pack
except ModuleNotFoundError:
    import rzip_pack


@functools.lru_cache(maxsize=1)
def require_gnu_gzip():
    try:
        version = subprocess.check_output(['gzip', '--version'], text=True).splitlines()[0]
    except (OSError, subprocess.CalledProcessError, IndexError) as error:
        raise ValueError('asset reconstruction requires GNU gzip 1.12; run the build through ./conker') from error
    if version != 'gzip 1.12':
        raise ValueError('asset reconstruction requires GNU gzip 1.12; run the build through ./conker')


def encode_payload(payload, level):
    if type(level) is not int or level not in (6, 9):
        raise ValueError('unsupported reviewed GNU gzip level')
    require_gnu_gzip()
    gz = subprocess.run(['gzip', '-n', f'-{level}', '-c'], input=payload,
                        stdout=subprocess.PIPE, check=True).stdout
    if (len(gz) < 18 or gz[:8] != bytes.fromhex('1f8b080000000000')
            or struct.unpack('<II', gz[-8:]) != (zlib.crc32(payload), len(payload) & 0xffffffff)):
        raise ValueError('unexpected GNU gzip wrapper or checksum')
    packed = struct.pack('>I', len(payload)) + gz[10:-8]
    try:
        decoded = rzip_pack.decode_rzip_chunk(packed)
    except zlib.error as error:
        raise ValueError('GNU gzip output failed independent decoding') from error
    if decoded.data != payload or decoded.consumed != len(packed):
        raise ValueError('GNU gzip output did not round-trip')
    return packed
