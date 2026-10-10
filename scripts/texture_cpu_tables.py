"""Complete stored images from the guarded native table at 0x80090298.

Storage width comes from the render stride and height from the exact transfer
extent. Sampler bounds remain separate: the renderer retains its half-texel
64x64 bounds when it later loads a 32x32 image. This is a source-storage proof,
not a claim about runtime activation or the visible sampled rectangle.
"""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

try:
    from scripts import hud_assets as h, texture_assets as t, texture_cpu_descriptors as cpu
except ModuleNotFoundError:
    import hud_assets as h
    import texture_assets as t
    import texture_cpu_descriptors as cpu


TABLE = 0x80090298
TABLE_SHA1 = 'de23e45cebe8e8e6c11ac714ec5c0f1475032261'
CONSUMERS = (
    (0x15180580, 3964, 'f168760af2baa81b9cbff9598bf6cee031f86d2a'),
    (0x1517FB9C, 2532, '2767ea4d9f23d7141b5ae17491ce5a9cb0ea8e2b'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
)
# Table words, loader call, SetTextureImage, load tile, LoadBlock, render tile.
# The 1517FB9C helper emits rectangles only; it preserves the inherited bounds.
LOADS = (
    ((1,), 0x15180F8C, 0xFD900000, (0xF5900000, 0x07000000),
     (0xF3000000, 0x077FF000), (0xF5881000, 0x00098260)),
    ((2,), 0x15181088, 0xFD700000, (0xF5700000, 0x07000000),
     (0xF3000000, 0x077FF000), (0xF5681000, 0x00098260)),
    ((3, 4, 5), 0x15181164, 0xFD100000, (0xF5100000, 0x07000000),
     (0xF3000000, 0x073FF000), (0xF5101000, 0x00094250)),
)


def verified_resources(code, code_base, data, data_base):
    for address, size, digest in CONSUMERS:
        if hashlib.sha1(h.data_slice(code, code_base, address, address + size)).hexdigest() != digest:
            raise ValueError('native table texture consumer changed')
    raw = h.data_slice(data, data_base, TABLE, TABLE + 24)
    if hashlib.sha1(raw).hexdigest() != TABLE_SHA1:
        raise ValueError('native texture resource table changed')
    resources = struct.unpack('>6I', raw)
    if resources != (3929, 1968, 4417, 4414, 4415, 4416):
        raise ValueError('native texture resource roles changed')
    return resources


def storage_contract(record, payload):
    _, _, image, load, block, render = record
    fmt, size = (render[0] >> 21) & 7, (render[0] >> 19) & 3
    form = cpu.FORMATS.get((fmt, size))
    if form not in ('i8', 'ia8', 'rgba16'):
        return None
    if (image != (0xFD100000 | fmt << 21)
            or load != (0xF5100000 | fmt << 21, 0x07000000)
            or block[0] != 0xF3000000 or block[1] >> 24 != 7
            or block[1] & 0xFFF or render[0] >> 24 != 0xF5
            or render[0] & 0x1FF or render[1] >> 24):
        return None
    row_bytes = ((render[0] >> 9) & 0x1FF) * 8
    extent = (((block[1] >> 12) & 0xFFF) + 1) * 2
    if not row_bytes or not 0 < extent <= 4096 or extent % row_bytes or len(payload) != extent:
        return None
    width, height = row_bytes * 8 // (4 << size), extent // row_bytes
    return {'format': form, 'width': width, 'height': height,
            'row_layout': t.ROW_LAYOUT_TMEM, 'source_origin': 'bottom-left'}


def load(root: Path, rom: bytes, entries, excluded_ids=()):
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('native table texture reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    resources = verified_resources(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    for record in LOADS:
        indices, call, image, load_tile, block, render = record
        for index in indices:
            resource = resources[index]
            if resource in excluded or resource not in payloads:
                continue
            payload = payloads[resource]
            contract = storage_contract(record, payload)
            if contract is None or not cpu.reversible(contract, payload):
                continue
            # The u8 counter selects table[3+counter]. The original successor
            # at 1518121C..15181238 increments 0/1 and resets >=2 to zero.
            # Admit only its declared 0,1,2 cycle, not arbitrary byte states.
            result[resource] = dict(contract, family='cpu-table-image', consumer={
                'native_consumers': {f'func_{a:08X}': digest for a, _, digest in CONSUMERS},
                'table_address': f'0x{TABLE:08X}', 'table_sha1': TABLE_SHA1,
                'table_word': index, 'loader_call': f'0x{call:08X}',
                'loader_arguments': [resource, 0, 3, 0],
                'counter': None if index < 3 else {
                    'base_address': '0x800DDD78', 'selected_state': index - 3,
                    'declared_states': [0, 1, 2], 'successor_span': ['0x1518121C', '0x1518123C']},
                'image_word': image, 'load_tile': list(load_tile),
                'load_block': list(block), 'render_tile': list(render),
                'sampler_bounds': [0xF2002002, 0x000FE0FE],
                'sampler_bounds_inherited': index != 1,
                'pixel_offset': 0, 'tmem_origin': 0, 'dxt': 0,
                'scope': 'complete-declared-storage-conditional-on-table-binding-and-declared-counter-state; no-runtime-activation-claim'})
    return result
