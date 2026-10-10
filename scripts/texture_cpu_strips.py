"""Complete I4 source strips inside two oversized native TMEM transfers.

The source contract covers the entire stored 128x16 image. It does not invent
the additional 3072 bytes fetched by the renderer or certify native appearance.
Width is established by the render stride and S bounds; the 30-pixel rectangle
and its 0x222 T step establish the sixteen-row strip independently of file size.
"""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import hud_assets as h, texture_assets as t, texture_cpu_descriptors as cpu
except ModuleNotFoundError:
    import hud_assets as h
    import texture_assets as t
    import texture_cpu_descriptors as cpu


CONSUMERS = ((0x15181EE0, 1936, '350bbafcbd81824c6fc9d8b88425bddce3ece102'),
             (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'))
TABLE = 0x800902C8
IMAGE = 0xFD900000
LOAD_TILE = (0xF5900000, 0x07000000)
LOAD_BLOCK = (0xF3000000, 0x077FF000)
RENDER_TILE = (0xF5801000, 0x0009C270)
BOUNDS = (0xF2002002, 0x001FE0FE)
RECTANGLE_HEIGHT = 30
T_STEP = 0x222  # Signed 5.10 texels per screen pixel, positive in both strips.
LOADS = ((1956, 0x151821A0, 0x15182184, 0x15182220),
         (1957, 0x15182438, 0x15182414, 0x151824C0))


def verified_resources(code, code_base, data, data_base):
    for address, size, digest in CONSUMERS:
        if hashlib.sha1(h.data_slice(code, code_base, address, address + size)).hexdigest() != digest:
            raise ValueError('native strip consumer changed')
    raw = h.data_slice(data, data_base, TABLE, TABLE + 8)
    if raw != struct.pack('>2I', 1956, 1957):
        raise ValueError('native strip resource table changed')
    return struct.unpack('>2I', raw)


def storage_contract(payload):
    # The transfer uses 16-bit units, while the render tile interprets I4.
    fmt, size = (RENDER_TILE[0] >> 21) & 7, (RENDER_TILE[0] >> 19) & 3
    stride = ((RENDER_TILE[0] >> 9) & 0x1FF) * 8
    width = stride * 2
    s_low, s_high = (BOUNDS[0] >> 12) & 0xFFF, (BOUNDS[1] >> 12) & 0xFFF
    height = (RECTANGLE_HEIGHT * T_STEP + 1023) // 1024
    transfer = (((LOAD_BLOCK[1] >> 12) & 0xFFF) + 1) * 2
    if ((fmt, size) != (4, 0) or width != 128 or (s_high - s_low) // 4 + 1 != width
            or height != 16 or transfer != 4096 or LOAD_BLOCK[1] & 0xFFF
            or stride * height != len(payload) or len(payload) != 1024):
        return None
    return {'format': 'i4', 'width': width, 'height': height,
            'row_layout': t.ROW_LAYOUT_TMEM, 'source_origin': 'bottom-left'}


def load(root, rom, entries, excluded_ids=()):
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('native strip reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    verified_resources(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    for resource, call, first, last in LOADS:
        if resource in excluded or resource not in payloads:
            continue
        payload = payloads[resource]
        contract = storage_contract(payload)
        if contract is None or not cpu.reversible(contract, payload):
            continue
        result[resource] = dict(contract, family='cpu-source-strip', consumer={
            'native_consumers': {f'func_{a:08X}': d for a, _, d in CONSUMERS},
            'table_address': f'0x{TABLE:08X}', 'resources': [1956, 1957],
            'loader_call': f'0x{call:08X}', 'source_pointer_offset': 0,
            'command_store_span': [f'0x{first:08X}', f'0x{last:08X}'],
            'image_word': IMAGE, 'load_tile': list(LOAD_TILE),
            'load_block': list(LOAD_BLOCK), 'render_tile': list(RENDER_TILE),
            'sampler_bounds': list(BOUNDS), 'rectangle_height': RECTANGLE_HEIGHT,
            'rectangle_t_step_5_10': T_STEP, 'source_t_span_5_10': RECTANGLE_HEIGHT * T_STEP,
            'source_bytes': 1024, 'transfer_bytes': 4096, 'unmodelled_transfer_bytes': 3072,
            'pixel_offset': 0, 'tmem_origin': 0, 'dxt': 0,
            'scope': 'complete-stored-source-strip-only; additional-transfer-bytes-unknown; '
                     'no-runtime-activation-or-raster-parity-claim'})
    return result
