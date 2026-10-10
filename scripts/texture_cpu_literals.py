"""Full images from reviewed native flat-loader calls and emitted RDP commands.

The records below transcribe the guarded original functions, not a constant or
payload-size scan. Each successful loader result becomes SetTextureImage's
unmodified address. Conditions select these sources; activation is not claimed.
"""
from __future__ import annotations

import hashlib
from pathlib import Path

try:
    from scripts import hud_assets as h, texture_assets as t, texture_cpu_descriptors as cpu
except ModuleNotFoundError:
    import hud_assets as h
    import texture_assets as t
    import texture_cpu_descriptors as cpu


CONSUMERS = (
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
    (0x1507DB6C, 736, '55454c9011182da625ebaf0c7c49fb7b1c6f224b'),
    (0x150918EC, 7980, 'da0fd8ba0b3e3d3872fab60a19f3377e9b04fe28'),
    (0x15093B58, 3432, '424bb071bcc6fcab8193ebb54d9161a93a314e74'),
    (0x151D2830, 640, '197315edbb908d8635f948b9eede0f878d49ea2c'),
    (0x151EEBE8, 1032, 'f8676c822d3695673ae88d749ec84129bed293dd'),
    (0x151E966C, 1708, '211ed25aadc17a46e42678195b167854a72a5531'),
    (0x151E9D18, 1092, '1f3fb02bec5206ed4defac9ba441fa0ad9404fd4'),
)
# Resources, loader call PC, first/last command-store PC, SetTextureImage,
# load tile, LoadBlock, render tile, tile bounds. Syncs carry no storage state.
# 3313/3314 are the two arms of the native flag-0x40 selection at 0x15093138.
RECORDS = (
    ((3343,), 0x1507DBB0, 0x1507DBC0, 0x1507DC68, 0xFD180000,
     (0xF5180000, 0x07080200), (0xF3000000, 0x073FF000),
     (0xF5181000, 0x00080200), (0xF2000000, 0x0007C07C)),
    ((3347,), 0x15092B04, 0x15092B18, 0x15092BB4, 0xFD100000,
     (0xF5100000, 0x07094250), (0xF3000000, 0x073FF000),
     (0xF5101000, 0x00094250), (0xF2000000, 0x0007C07C)),
    ((3313, 3314), 0x15093150, 0x15093160, 0x15093200, 0xFD700000,
     (0xF5700000, 0x07098260), (0xF3000000, 0x077FF000),
     (0xF5681000, 0x00098260), (0xF2000000, 0x000FC0FC)),
    ((3315,), 0x15093C68, 0x15093C8C, 0x15093D2C, 0xFD700000,
     (0xF5700000, 0x07094250), (0xF3000000, 0x071FF000),
     (0xF5680800, 0x00094250), (0xF2000000, 0x0007C07C)),
    ((2632,), 0x151D28F0, 0x151D2904, 0x151D29AC, 0xFD700000,
     (0xF5700000, 0x07018060), (0xF3000000, 0x077FF000),
     (0xF5681000, 0x00018060), (0xF2000000, 0x000FC0FC)),
    ((2043,), 0x151EEC44, 0x151EEC5C, 0x151EECFC, 0xFD100000,
     (0xF5100000, 0x07054260), (0xF3000000, 0x075FF000),
     (0xF5101800, 0x00054260), (0xF2000000, 0x000BC07C)),
    ((3348,), 0x151E96CC, 0x151E971C, 0x151E97BC, 0xFD180000,
     (0xF5180000, 0x07094250), (0xF3000000, 0x073FF000),
     (0xF5181000, 0x00094250), (0xF2000000, 0x0007C07C)),
    # 0x151E9D68..0x151E9DA4 pairs 3344 with s0=32 and 3345/3346
    # with s0=16. The guarded consumer emits 32*s0 RGBA32 texels,
    # line=(2*s0+7)>>3, and bounds ((s0-1)*4, 31*4).
    ((3344,), 0x151E9DC0, 0x151E9DF8, 0x151E9ED0, 0xFD180000,
     (0xF5180000, 0x07094250), (0xF3000000, 0x073FF000),
     (0xF5181000, 0x00094250), (0xF2000000, 0x0007C07C)),
    ((3345, 3346), 0x151E9DC0, 0x151E9DF8, 0x151E9ED0, 0xFD180000,
     (0xF5180000, 0x07094250), (0xF3000000, 0x071FF000),
     (0xF5180800, 0x00094250), (0xF2000000, 0x0003C07C)),
)


def verified_records(code: bytes, base: int):
    for address, size, digest in CONSUMERS:
        raw = h.data_slice(code, base, address, address + size)
        if hashlib.sha1(raw).hexdigest() != digest:
            raise ValueError(f'literal texture consumer changed: 0x{address:08X}')
    return RECORDS


def storage_contract(record, payload: bytes) -> dict | None:
    _, _, _, _, image, load, block, render, bounds = record
    fmt, size = (render[0] >> 21) & 7, (render[0] >> 19) & 3
    form = cpu.FORMATS.get((fmt, size))
    # This reviewed family has no palettes, offsets, fractional tile origins,
    # or partial rows. Reject those instead of inferring missing storage.
    if form not in ('rgba16', 'rgba32', 'ia8'):
        return None
    transfer_size = (image >> 19) & 3
    if (image != 0xFD000000 | (fmt << 21) | (transfer_size << 19)
            or load[0] != 0xF5000000 | (fmt << 21) | (transfer_size << 19)
            or load[1] >> 24 != 7 or render[1] >> 24 != 0
            or (load[1] & 0xFFFFFF) != render[1]
            or render[0] >> 24 != 0xF5 or render[0] & 0x1FF
            or block[0] != 0xF3000000 or block[1] >> 24 != 7
            or block[1] & 0xFFF or bounds[0] != 0xF2000000
            or bounds[1] >> 24 or bounds[1] & 0x003003):
        return None
    width, height = ((bounds[1] >> 12) & 0xFFF) // 4 + 1, (bounds[1] & 0xFFF) // 4 + 1
    row_bytes = width * (4 << size) // 8
    transfer_bytes = (((block[1] >> 12) & 0xFFF) + 1) * (4 << transfer_size) // 8
    stride = ((render[0] >> 9) & 0x1FF) * 8
    if (width * (4 << size) % 64 or row_bytes * height != len(payload)
            or transfer_bytes != len(payload) or not 0 < len(payload) <= 4096
            or stride != row_bytes // (2 if size == 3 else 1)):
        return None
    return {'format': form, 'width': width, 'height': height,
            'row_layout': t.ROW_LAYOUT_TMEM, 'source_origin': 'bottom-left'}


def load(root: Path, rom: bytes, entries, excluded_ids=()) -> dict[int, dict]:
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('literal texture reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    records = verified_records(game.code, layout['game_vram'])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    consumers = {f'func_{a:08X}': digest for a, _, digest in CONSUMERS}
    for record in records:
        resources, call, first, last, image, load_tile, block, render, bounds = record
        for resource in resources:
            if resource in excluded or resource not in payloads:
                continue
            payload = payloads[resource]
            contract = storage_contract(record, payload)
            if contract is None or not cpu.reversible(contract, payload):
                continue
            result[resource] = dict(contract, family='cpu-literal-image', consumer={
                'native_consumers': consumers, 'loader_call': f'0x{call:08X}',
                'resource_alternatives': list(resources), 'loader_arguments': [resource, 0, 3, 0],
                'command_store_span': [f'0x{first:08X}', f'0x{last:08X}'],
                'image_word': image, 'load_tile': list(load_tile), 'load_block': list(block),
                'render_tile': list(render), 'tile_bounds': list(bounds),
                'pixel_offset': 0, 'tmem_origin': 0, 'dxt': 0,
                'scope': 'complete-declared-storage-no-runtime-activation-claim'})
    return result
