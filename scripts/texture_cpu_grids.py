"""Complete US texture storage proven by native UI and effect grid consumers."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

try:
    from scripts import hud_assets as h, rzip_archive, texture_cpu_descriptors as cpu
except ModuleNotFoundError:
    import hud_assets as h
    import rzip_archive
    import texture_cpu_descriptors as cpu


# Descriptor address, columns, rows, native caller. The last argument to
# 151ED430 is zero in each caller; each <=4096-byte source advances one ID.
UI_GRIDS = (
    (0x800917F8, 5, 6, 0x151EC1F0), (0x80091804, 5, 2, 0x151EC1F0),
    (0x80091810, 5, 2, 0x151EC1F0), (0x8009181C, 8, 3, 0x151ED09C),
    (0x80091828, 8, 3, 0x151ED09C),
)
# Descriptor, total width/height, border, frames, producer, descriptor role.
# Object flag 0x10 selects the two-pixel border in 1509629C; frame and grid
# indices advance resource IDs, not pixel offsets or frame-array pointers.
EFFECT_GRIDS = (
    (0x800917EC, 64, 32, 0, 1, 0x1510A930, 'primary'),
    (0x800917F8, 160, 192, 0, 1, 0x150F5420, 'primary'),
    (0x80091930, 270, 124, 2, 1, 0x150F5420, 'primary'),
    (0x8009193C, 270, 124, 2, 1, 0x150F5420, 'primary'),
    (0x80091948, 240, 186, 2, 1, 0x150F5420, 'primary'),
    (0x800918E8, 88, 64, 0, 1, 0x150B76BC, 'primary'),
    (0x800918F4, 64, 64, 0, 1, 0x150B77A8, 'primary'),
    (0x80091900, 64, 1, 0, 1, 0x150B77A8, 'secondary'),
    (0x8009190C, 64, 16, 0, 3, 0x150B791C, 'primary'),
    (0x80091918, 128, 16, 0, 1, 0x150B6E3C, 'mutated-primary'),
    (0x800918DC, 88, 88, 0, 15, 0x150B7560, 'primary'),
    (0x80091924, 16, 16, 0, 2, 0x150B7220, 'primary'),
)
DESCRIPTORS = {
    0x800917F8: 'b1484da603dd46b304df975ab9327a1ca1a4ecc9',
    0x80091804: '24e7fc4033471b66dae5d5b928847d06ae15883a',
    0x80091810: 'bfa6782022953ac1df51168892a21a7d9a8333cb',
    0x8009181C: '84145c561e56d5c0b70062c1f8c5d2f7c4e9db1b',
    0x80091828: 'da878d55b39128152515cf33cc5ab0434a601685',
    0x800917EC: '2a0d180503c5cde42c91e1e6896b83c2086ad542',
    0x80091930: 'c93e06c8b0bec8140b9580894a9ac1b721cdc520',
    0x8009193C: '38546f990f4ccaf63c08180a97bebe1321af4d22',
    0x80091948: 'ffd7122c7a8c52f029f066dcf15cafe9f95a480c',
    0x800918E8: '9ca052672440d03e3df42214dd44863b88c95238',
    0x800918F4: '0b7566393ffd155ae7ce6e88b712249965eded33',
    0x80091900: '51887d80ac6537de19e385f72e3606436d362c27',
    0x8009190C: '43a6fe3a1a4f338380641bf4aad3190e15067867',
    0x80091918: '9dbd1f849aa73dbcaf90ec096ee1fcb572d616dd',
    0x800918DC: 'bcf360a333446a3999578ef9ff09b14d0738a901',
    0x80091924: 'e8c29ca153d064c169a00463c764b25f3423d405',
    0x8009013C: '42b1a0b0b6f53643bbd879483da984853bdba6d4',
}
BANK_DESCRIPTOR = 0x8009013C
BANK_INDEX, BANK_SIZE = 0x1D, 144
BANK_SHA1 = 'c66f10f419e661a795ff367d6284997c1b90c809'
DATA_GUARDS = (
    (0x8008C7C0, 52, '8f868977e289866cbc8713b3370a279cada30169'),
    (0x8008CA20, 44, 'a8503d779b6d0933673fccb21b2e999eed73cc6c'),
)
CONSUMERS = cpu.CONSUMERS + (
    (0x151EC1F0, 504, 'ec5ca71da8804077b6ac8da9b567473aea7b7c74'),
    (0x151ED09C, 324, '9f5a57a2a7d04fb7c82870ec97d3f1143b32047c'),
    (0x151ED29C, 404, 'fd7af04b49a59c9fd024e24de72878095596d257'),
    (0x151ED430, 1244, '900522a88e522f04c6834172be22b92ee7cfe7cd'),
    (0x15169900, 104, '255947ce5466af7d748e2bd2cccf08ae17e54730'),
    (0x15169968, 32, '28cc3a0b34a98f83b56ed81c04fa49b494f30d98'),
    (0x15169988, 192, '1936ba3171761cbd2e1f7f699099365fd8cf2efc'),
    (0x15169A48, 552, '90b6ddce6020c5b73d7976a11110c1b8a3a653e3'),
    (0x15167A68, 112, '0825b0b974ca67a92c0a6e7d8665230b02e2b181'),
    (0x1509629C, 1688, '5ce9c384ee4b28151c78d3e2df80668b4484de53'),
    (0x15094F70, 120, 'feaf43a9d43b1baf9c70caf21784a0a4a3cd8a28'),
    (0x1510A930, 240, '7f8d001ae3575a0aa30794acc8c2d87f5b99df09'),
    (0x150F5420, 368, '8f2760075eaf54b1ab8bcb234ca470039d61eac6'),
    (0x150B76BC, 236, 'e8de4dfc01278f1d2fcd49bb53b591e84295e263'),
    (0x150B77A8, 372, 'b4ba1eb2c4bd78920093e82117ea529bf6d2975f'),
    (0x150B791C, 548, 'a5ed2bdf47d5d2bbba291212a6cda57329cf9774'),
    (0x150B6E3C, 608, '932f61a7033edc0e0ecc1602e2d0e50a39237c60'),
    (0x150B7560, 252, 'f492f6c382a750532864bb1c9899fe9ae929f1ba'),
    (0x150B7220, 464, 'e18a6c5d2a7f680ff47819d2f5e8e12edf471b5d'),
    (0x15168A4C, 80, '41a70fd6b122eeb005b9c01d21f215c154765b9d'),
    (0x151EEBE8, 1032, 'f8676c822d3695673ae88d749ec84129bed293dd'),
    (0x1502B7F0, 240, '8f37332e9c2598c7a996b8d1e0c5d9ea82f44cfd'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x1502B350, 344, 'd789fbbc29db59a4ea107ebe753587f3774b8d51'),
)


def checked(raw: bytes, digest: str, label: str) -> bytes:
    if hashlib.sha1(raw).hexdigest() != digest:
        raise ValueError(f'CPU grid {label} changed')
    return raw


def verified_descriptors(code, code_base, data, data_base, bank_raw):
    for address, size, digest in CONSUMERS:
        checked(h.data_slice(code, code_base, address, address + size), digest, 'consumer')
    for address, size, digest in DATA_GUARDS:
        checked(h.data_slice(data, data_base, address, address + size), digest, 'dispatch data')
    if h.data_slice(data, data_base, cpu.SIZE_TABLE, cpu.SIZE_TABLE + 16) != cpu.SIZE_BYTES:
        raise ValueError('CPU grid transfer-size tables changed')
    checked(bank_raw, BANK_SHA1, 'bank image list')
    if len(bank_raw) != BANK_SIZE:
        raise ValueError('CPU grid bank image list size changed')
    records = {}
    for address, digest in DESCRIPTORS.items():
        raw = checked(h.data_slice(data, data_base, address, address + 12), digest, 'descriptor')
        source, count, flags, width, height, fmt, size = struct.unpack('>IBBHHBB', raw)
        if count != 1 or flags or not 0 <= source < 0x10000000:
            raise ValueError('CPU grid requires a direct resource descriptor')
        records[address] = dict(address=f'0x{address:08X}', sha1=digest, source=source,
                                count=count, flags=flags, width=width, height=height,
                                format=fmt, size=size)
    return records, struct.unpack(f'>{BANK_SIZE // 2}H', bank_raw)


def effect_tiles(record, total_width, total_height, border, frames):
    """Native 1509629C: short first row, short last column, then frame planes."""
    width, height = record['width'], record['height']
    if (border not in (0, 2) or width <= border or height <= border
            or total_width <= 0 or total_height <= 0 or frames <= 0):
        raise ValueError('invalid native effect grid')
    step_x, step_y = width - border, height - border
    columns = (total_width + step_x - 1) // step_x
    rows = (total_height + step_y - 1) // step_y
    for frame in range(frames):
        for column in range(columns):
            for row in range(rows):
                resource = record['source'] + frame * columns * rows + column * rows + row
                shape = dict(record,
                             width=total_width - column * step_x + border if column == columns - 1 else width,
                             height=total_height - (rows - 1) * step_y + border if row == 0 else height)
                yield resource, shape, dict(frame=frame, column=column, row=row,
                                            columns=columns, rows=rows)


def split_contract(record, payload):
    """Two 151ED430 loads reuse one >4096-byte buffer; no opaque remainder."""
    if ((record['format'], record['size']) != (0, 2) or record['height'] % 2
            or len(payload) <= 4096):
        return None
    tile_bytes = record['width'] * record['height'] * 2
    if len(payload) != tile_bytes * 2:
        return None
    tile = cpu.storage_contract(record, payload[:tile_bytes])
    if tile is None:
        return None
    return dict(tile, height=record['height'] * 2, source_origin='top-left')


def load(root: Path, rom: bytes, entries, excluded_ids=()) -> dict[int, dict]:
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('CPU grid reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    bank = rzip_archive.parse_asset_banks(rom, layout['asset_table'])[BANK_INDEX]
    if bank.flags != 8 or bank.end - bank.start != BANK_SIZE:
        raise ValueError('CPU grid bank image list extent or encoding changed')
    records, bank_ids = verified_descriptors(game.code, layout['game_vram'], game.data,
                                             layout['game_data_vram'], rom[bank.start:bank.end])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    common = {'native_consumers': {f'func_{a:08X}': digest for a, _, digest in CONSUMERS},
              'dispatch_data': {f'0x{a:08X}': digest for a, _, digest in DATA_GUARDS},
              'size_table_bytes': cpu.SIZE_BYTES.hex(), 'dxt': 0,
              'scope': 'complete-declared-storage-no-runtime-activation-claim'}

    def add(resource, contract, proof):
        if (contract is not None and resource not in excluded and resource not in result
                and cpu.reversible(contract, payloads[resource])):
            result[resource] = dict(contract, family='cpu-grid-storage', consumer={**common, **proof})

    for address, columns, rows, caller in UI_GRIDS:
        record = records[address]
        if (record['format'], record['size']) not in ((0, 3), (4, 1)):
            raise ValueError('unsupported UI grid transfer format')
        resources = list(range(record['source'], record['source'] + columns * rows))
        contracts = [cpu.storage_contract(record, payloads[r]) if r in payloads else None for r in resources]
        # Advancing an ID is valid only if each preceding tile consumed its
        # entire <=4096-byte source. Never infer later IDs after a split load.
        if any(c is None for c in contracts):
            continue
        for tile, (resource, contract) in enumerate(zip(resources, contracts)):
            add(resource, contract, {'kind': 'ui-grid', 'descriptor': record,
                'caller': f'0x{caller:08X}', 'columns': columns, 'rows': rows,
                'column': tile // rows, 'row': tile % rows, 'pixel_offset': 0, 'tmem_origin': 0})
    for address, width, height, border, frames, caller, role in EFFECT_GRIDS:
        record = records[address]
        for resource, shape, position in effect_tiles(record, width, height, border, frames):
            if resource not in payloads:
                continue
            add(resource, cpu.storage_contract(shape, payloads[resource]), {
                'kind': 'effect-grid', 'descriptor': record, 'caller': f'0x{caller:08X}',
                'total_width': width, 'total_height': height, 'border': border, 'frames': frames,
                'role': role, **position, 'pixel_offset': 0,
                'tmem_origin': 256 if role == 'secondary' else 0})
    record = records[BANK_DESCRIPTOR]
    for resource in sorted(set(bank_ids) - {0}):
        if resource not in payloads:
            continue
        add(resource, split_contract(record, payloads[resource]), {
            'kind': 'bank-split', 'descriptor': record, 'bank': BANK_INDEX,
            'bank_sha1': BANK_SHA1, 'slots': [i for i, value in enumerate(bank_ids) if value == resource],
            'caller': '0x151EEBE8', 'columns': 1, 'rows': 2,
            'pixel_offsets': [0, record['width'] * record['height'] * 2], 'tmem_origin': 0})
    return result
