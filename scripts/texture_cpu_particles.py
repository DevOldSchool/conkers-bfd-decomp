"""Complete particle frames reached through a guarded parent callback chain."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

try:
    from scripts import hud_assets as h, texture_cpu_descriptors as cpu
except ModuleNotFoundError:
    import hud_assets as h
    import texture_cpu_descriptors as cpu


DESCRIPTOR = 0x80090414
DESCRIPTOR_SHA1 = '8e32531a728adb1e49d2ce4304620a01995f3d28'
FRAMES_SHA1 = '7918af4706fc166e37304c21932fd7c8c61c08d8'
# Parent callback arrays, parent type-0x22 row, child type-5 row.
DATA_GUARDS = (
    (0x8008A200, 60, '0fc4f4874e7a7b26018e862d44bcb2435740b271'),
    (0x8008A23C, 72, 'a6d0fbcc3b1605a2ec0f07495389ccce97ace202'),
    (0x8008BB90, 52, '5f8b72518229852324be43cd8e3bdebaa5cf5cae'),
    (0x8008B5AC, 52, 'fda024d76e3a5cf404a4469a0ada50c73c9fe8f2'),
)
CONSUMERS = cpu.CONSUMERS + (
    (0x150DBD70, 2024, 'e7a6a28c07007b7f51ddd3762af6f861048980ad'),
    (0x15147A80, 460, '0013c8831f7641a4d9ef4ea7b75eab12e0442237'),
    (0x15147740, 400, '31335eec718ecc9858ed5f3779bcfac50b9d102f'),
    (0x150DC558, 2376, '26f25f0f9b6e9c942b2af2b4c10defe867231875'),
    (0x150DCEA0, 1952, '6bfd3056636a5db6212789777978a152bc84e5b8'),
    (0x15167D84, 136, '6fe2c0726c02923688161f9540249ea5f93c7280'),
    (0x15167A68, 112, '0825b0b974ca67a92c0a6e7d8665230b02e2b181'),
    (0x15168118, 1348, '86ca4d4c841cfa7c8851e7b596c232a7e1019d7d'),
    (0x15167E0C, 780, '384f0ee19b8fd3abca5b676ca4467f862bf14b39'),
)


def checked(raw, digest, label):
    if hashlib.sha1(raw).hexdigest() != digest:
        raise ValueError(f'CPU particle {label} changed')
    return raw


def verified_descriptor(code, code_base, data, data_base):
    for address, size, digest in CONSUMERS:
        checked(h.data_slice(code, code_base, address, address + size), digest, 'consumer')
    for address, size, digest in DATA_GUARDS:
        checked(h.data_slice(data, data_base, address, address + size), digest, 'callback data')
    if h.data_slice(data, data_base, cpu.SIZE_TABLE, cpu.SIZE_TABLE + 16) != cpu.SIZE_BYTES:
        raise ValueError('CPU particle transfer-size tables changed')
    raw = checked(h.data_slice(data, data_base, DESCRIPTOR, DESCRIPTOR + 12),
                  DESCRIPTOR_SHA1, 'descriptor')
    pointer, count, flags, width, height, fmt, size = struct.unpack('>IBBHHBB', raw)
    if not count or flags or pointer < data_base or pointer & 3:
        raise ValueError('CPU particle requires an unflagged frame-array descriptor')
    frames = checked(h.data_slice(data, data_base, pointer, pointer + count * 4),
                     FRAMES_SHA1, 'frame array')
    resources = list(struct.unpack(f'>{count}I', frames))
    if any(not 0 < resource < h.RUNTIME_FLAT_ASSET_COUNT for resource in resources):
        raise ValueError('CPU particle frame resource is out of range')
    return dict(address=f'0x{DESCRIPTOR:08X}', sha1=DESCRIPTOR_SHA1,
                pointer=pointer, count=count, flags=flags, width=width, height=height,
                format=fmt, size=size, resources=resources, frame_sha1=FRAMES_SHA1)


def load(root: Path, rom: bytes, entries, excluded_ids=()) -> dict[int, dict]:
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('CPU particle reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    record = verified_descriptor(game.code, layout['game_vram'], game.data,
                                 layout['game_data_vram'])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    # 150DBD70 copies the descriptor into parent config +90/+F4. Parent
    # callbacks 150DCEA0/150DC558 put it in packet word zero; 15167D84 copies
    # that packet to child +10. 15168118 selects the descriptor frame using
    # child +1C >> 8, bounded by descriptor.count in update 15167E0C.
    for frame, resource in enumerate(record['resources']):
        if resource in excluded or resource in result or resource not in payloads:
            continue
        contract = cpu.storage_contract(record, payloads[resource])
        if contract is None or not cpu.reversible(contract, payloads[resource]):
            continue
        result[resource] = dict(contract, family='cpu-particle-descriptor', consumer={
            'descriptor': record, 'selected_frame': frame,
            'native_consumers': {f'func_{a:08X}': digest for a, _, digest in CONSUMERS},
            'callback_data': {f'0x{a:08X}': digest for a, _, digest in DATA_GUARDS},
            'parent_type': 0x22, 'parent_callbacks': [4, 4], 'child_type': 5,
            'size_table_bytes': cpu.SIZE_BYTES.hex(), 'pixel_offset': 0, 'dxt': 0,
            'scope': 'complete-declared-storage-no-runtime-activation-claim'})
    return result
