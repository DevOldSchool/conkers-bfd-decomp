"""Complete stored textures declared by the US CPU renderer's descriptor table.

These contracts identify source storage, not a sampled animation or rendered
appearance. The native caller selects a twelve-byte descriptor and frame; the
loader transfers from offset zero with zero DXT. Every admitted byte belongs
to an explicitly declared image or palette.
"""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

try:
    from scripts import hud_assets as h, texture_assets as t, texture_native, texture_rgba16
except ModuleNotFoundError:
    import hud_assets as h
    import texture_assets as t
    import texture_native
    import texture_rgba16


TABLE = 0x80090B60
COUNT = 207  # The next object, 0x80091514, is a separate flat-resource word.
TABLE_SHA1 = 'e243fa4b32ece0499383b8b2c3edc13737bbcf05'
FRAMES_SHA1 = '504aa79ba2dc001cc869cfb28d76e295da1eaa65'
SIZE_TABLE = 0x8009DEB0
SIZE_BYTES = bytes.fromhex('03010000020100000101020202020203')
CONSUMERS = (
    (0x15094FE8, 120, '2c4f7d72dc31f3c0c877fdb5cde1637a014fcaab'),
    (0x15095060, 116, '29ae9b967b84e38fc29b3ae88ecfc3d3bed7ed83'),
    (0x150950D4, 1384, 'd8a2113e6fa9599a3110d2f404dadee24165ef7a'),
    (0x15142E24, 408, 'c282266cd9d3db78bd02afc30e4d74b6f26264aa'),
    (0x1514306C, 200, '57f7e47b0c58c843d442b744762abafd67645d7e'),
    (0x1515BBF0, 600, '35e39a1a104babd7a81363f322938c7df696a4cc'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
)
FORMATS = {(2, 0): 'ci4', (2, 1): 'ci8', (0, 2): 'rgba16', (0, 3): 'rgba32',
           (3, 0): 'ia4', (3, 1): 'ia8', (3, 2): 'ia16', (4, 0): 'i4', (4, 1): 'i8'}


def verified_descriptors(code: bytes, code_base: int, data: bytes, data_base: int):
    for address, size, expected in CONSUMERS:
        raw = h.data_slice(code, code_base, address, address + size)
        if hashlib.sha1(raw).hexdigest() != expected:
            raise ValueError(f'CPU texture consumer changed: 0x{address:08X}')
    table = h.data_slice(data, data_base, TABLE, TABLE + COUNT * 12)
    if hashlib.sha1(table).hexdigest() != TABLE_SHA1:
        raise ValueError('CPU texture descriptor table changed')
    if h.data_slice(data, data_base, SIZE_TABLE, SIZE_TABLE + 16) != SIZE_BYTES:
        raise ValueError('CPU texture transfer-size tables changed')
    records, frame_bytes = [], []
    for index in range(COUNT):
        raw = table[index * 12:(index + 1) * 12]
        pointer, count, flags, width, height, fmt, size = struct.unpack('>IBBHHBB', raw)
        if pointer >= 0x80000000:
            frames = h.data_slice(data, data_base, pointer, pointer + count * 4)
            frame_bytes.append(frames)
            resources = list(struct.unpack(f'>{count}I', frames))
        else:
            frames, resources = b'', [pointer] if 0 < pointer < 0x10000000 else []
        records.append({'index': index, 'address': f'0x{TABLE + index * 12:08X}',
                        'sha1': hashlib.sha1(raw).hexdigest(), 'pointer': pointer,
                        'count': count, 'flags': flags, 'width': width, 'height': height,
                        'format': fmt, 'size': size, 'resources': resources,
                        'frame_sha1': hashlib.sha1(frames).hexdigest()})
    if hashlib.sha1(b''.join(frame_bytes)).hexdigest() != FRAMES_SHA1:
        raise ValueError('CPU texture frame arrays changed')
    return records


def storage_contract(record: dict, payload: bytes) -> dict | None:
    width, height, fmt, size = (record[k] for k in ('width', 'height', 'format', 'size'))
    detail = (fmt, size) == (5, 2)
    form = 'rgba16' if detail else FORMATS.get((fmt, size))
    if (form is None or record['flags'] or not record['count']
            or not 0 < width <= 1024 or not 0 < height <= 1024):
        return None
    bits = 4 << size
    pixels = width * height
    pixel_bytes = pixels * bits // 8
    detail_bytes = pixels // 2 if detail else 0
    palette_size = (32 if size == 0 else 512) if fmt == 2 else 0
    # Native 0x15095110..0x15095178 computes the LoadBlock transfer count.
    transfers = (pixels + SIZE_BYTES[size] + (pixels // 4 if detail else 0)) >> SIZE_BYTES[4 + size]
    transfer_size = SIZE_BYTES[12 + size]
    stride = (SIZE_BYTES[8 + size] * (width // 2 if size == 0 else width) + 7) >> 3
    if (width * bits % 64 or not 0 < transfers <= 2048
            or transfers * (4 << transfer_size) // 8 != pixel_bytes + detail_bytes
            or stride * 8 != width * bits // 8 // (2 if size == 3 else 1)
            or pixel_bytes + detail_bytes > (2048 if palette_size else 4096)
            or len(payload) != pixel_bytes + detail_bytes + palette_size
            or (detail and width % 16)):
        return None
    contract = {'format': form, 'width': width, 'height': height,
                'row_layout': t.ROW_LAYOUT_TMEM, 'source_origin': 'bottom-left'}
    if detail:
        # Native 0x1509547C..0x15095554 declares I4 at TMEM word N/4,
        # following the N RGBA16 texels, with the same width and height.
        contract.update(mixed_detail=True, palette_size=0, levels=[
            {'level': 0, 'format': 'rgba16', 'role': 'mip', 'offset': 0,
             'width': width, 'height': height, 'bytes': pixel_bytes},
            {'level': 1, 'format': 'i4', 'role': 'detail', 'offset': pixel_bytes,
             'width': width, 'height': height, 'bytes': detail_bytes}])
    return contract


def reversible(contract: dict, payload: bytes) -> bool:
    planes = contract.get('levels', [dict(contract, offset=0, bytes=len(payload))])
    restored = []
    for plane in planes:
        form, width, height = (plane[k] for k in ('format', 'width', 'height'))
        start, count = plane['offset'], plane['bytes']
        raw = payload[start:start + count]
        if form in ('ci4', 'ci8'):
            encode = t.encode_indexed_png if form == 'ci4' else t.encode_ci8_png
            decode = t.decode_indexed_png if form == 'ci4' else t.decode_ci8_png
        elif form == 'rgba16':
            encode, decode = texture_rgba16.encode_png, texture_rgba16.decode_png
        else:
            png = texture_native.encode_png(raw, form, t.ROW_LAYOUT_TMEM, width, height)
            restored.append(texture_native.decode_png(png, form, t.ROW_LAYOUT_TMEM, width, height))
            continue
        restored.append(decode(encode(raw, t.ROW_LAYOUT_TMEM, width, height),
                               t.ROW_LAYOUT_TMEM, width, height))
    return b''.join(restored) == payload


def load(root: Path, rom: bytes, entries, excluded_ids=()) -> dict[int, dict]:
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('CPU texture reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    records = verified_descriptors(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    consumers = {f'func_{address:08X}': digest for address, _, digest in CONSUMERS}
    for record in records:
        for frame, resource in enumerate(record['resources']):
            if resource in excluded or resource in result or resource not in payloads:
                continue
            payload = payloads[resource]
            contract = storage_contract(record, payload)
            if contract is None or not reversible(contract, payload):
                continue
            result[resource] = dict(contract, family='cpu-texture-descriptor', consumer={
                'descriptor': record, 'selected_frame': frame,
                'table_sha1': TABLE_SHA1, 'frame_arrays_sha1': FRAMES_SHA1,
                'size_table_bytes': SIZE_BYTES.hex(), 'native_consumers': consumers,
                'pixel_offset': 0, 'tmem_origin': 0, 'dxt': 0,
                'scope': 'complete-declared-storage-no-runtime-activation-claim'})
    return result
