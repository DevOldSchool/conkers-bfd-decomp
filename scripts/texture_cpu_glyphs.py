"""Texture storage selected by the original glyph renderer's explicit cases.

Glyph selectors can choose frame zero with descriptor byte4 zero, or frame three
with byte4 three. Only the guarded native cases below establish those extents;
this module does not change the generic descriptor count contract.
"""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

try:
    from scripts import hud_assets as h, texture_cpu_descriptors as cpu
except ModuleNotFoundError:
    import hud_assets as h
    import texture_cpu_descriptors as cpu


CONSUMERS = (
    (0x150417AC, 4392, 'a778546ac55048b14f49c93aa0016b5771218e39'),
    (0x15094F70, 120, 'feaf43a9d43b1baf9c70caf21784a0a4a3cd8a28'),
    (0x15095060, 116, '29ae9b967b84e38fc29b3ae88ecfc3d3bed7ed83'),
    (0x150950D4, 1384, 'd8a2113e6fa9599a3110d2f404dadee24165ef7a'),
)
JUMP_TABLE = 0x80098B14
JUMP_COUNT = 27
JUMP_SHA1 = 'bb82701baa65290c194dbfd69518d35c414cecca'
# Character, original case PC, descriptor address, explicit selected frames.
ROUTES = (
    (0xa8, 0x15041d24, 0x800915dc, (0,)),
    (0xa9, 0x15041d34, 0x800915ec, (0,)),
    (0xaa, 0x15041d74, 0x8009162c, (0,)),
    (0xab, 0x15041d84, 0x8009163c, (0,)),
    (0xac, 0x15041d94, 0x8009164c, (0,)),
    (0xad, 0x15041da4, 0x8009165c, (0,)),
    (0xae, 0x15041d44, 0x800915fc, (0,)),
    (0xaf, 0x15041d54, 0x8009160c, (0,)),
    (0xb0, 0x15041d64, 0x8009161c, (0,)),
    (0xb1, 0x15041e7c, 0x80091690, (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)),
    (0xb2, 0x15041db4, 0x800916ac, (0, 1, 2, 3)),
    (0xb3, 0x15041de4, 0x800916e4, (0, 1, 2, 3)),
    (0xb4, 0x15041dcc, 0x800916c8, (0, 1, 2, 3)),
    (0xb5, 0x15041dfc, 0x80091700, (0, 1, 2, 3)),
    (0xb6, 0x15041e14, 0x80091710, (0,)),
    (0xb7, 0x15041e24, 0x80091720, (0,)),
    (0xb8, 0x15041e34, 0x80091730, (0,)),
    (0xb9, 0x15041e44, 0x80091740, (0,)),
    (0xba, 0x15041e54, 0x80091750, (0,)),
    (0xbb, 0x15041e64, 0x80091764, (0, 1)),
)
DESCRIPTORS_SHA1 = 'efd08f0c1dfb1caef5482ba6056fc46920b11a29'
FRAMES_SHA1 = '57c197652d246b340a03a8e3868c834b85421206'


def checked(raw: bytes, expected: str, label: str) -> bytes:
    if hashlib.sha1(raw).hexdigest() != expected:
        raise ValueError(f'glyph texture {label} changed')
    return raw


def verified_records(code: bytes, code_base: int, data: bytes, data_base: int):
    for address, size, digest in CONSUMERS:
        checked(h.data_slice(code, code_base, address, address + size), digest,
                f'consumer 0x{address:08X}')
    def read(address, size):
        return h.data_slice(data, data_base, address, address + size)
    jump = struct.unpack(f'>{JUMP_COUNT}I', checked(
        read(JUMP_TABLE, 4 * JUMP_COUNT), JUMP_SHA1, 'jump table'))
    if read(cpu.SIZE_TABLE, 16) != cpu.SIZE_BYTES:
        raise ValueError('glyph texture transfer-size tables changed')
    descriptors = [read(address, 12) for _, _, address, _ in ROUTES]
    checked(b''.join(descriptors), DESCRIPTORS_SHA1, 'descriptors')
    records, all_frames = [], []
    for (character, case_pc, address, frames), raw in zip(ROUTES, descriptors):
        if (not 0xA8 <= character <= 0xBB or jump[character - 0xA1] != case_pc
                or not frames or tuple(range(len(frames))) != frames):
            raise ValueError('glyph texture selector contract changed')
        pointer, stored_count, padding, width, height, fmt, size = struct.unpack('>IBBHHBB', raw)
        if pointer < 0x80000000 or padding:
            raise ValueError('unsupported glyph texture pointer or padding')
        frame_bytes = read(pointer, 4 * len(frames))
        all_frames.append(frame_bytes)
        records.append({'character': character, 'case_pc': f'0x{case_pc:08X}',
                        'descriptor': f'0x{address:08X}', 'descriptor_sha1': hashlib.sha1(raw).hexdigest(),
                        'pointer': pointer, 'stored_count': stored_count, 'padding': padding,
                        'width': width, 'height': height, 'format': fmt, 'size': size,
                        'frames': list(frames), 'resources': list(struct.unpack(f'>{len(frames)}I', frame_bytes)),
                        'frame_sha1': hashlib.sha1(frame_bytes).hexdigest()})
    checked(b''.join(all_frames), FRAMES_SHA1, 'selected frame words')
    return records


def storage_contract(record: dict, payload: bytes) -> dict | None:
    frames = record['frames']
    if not frames or frames != list(range(len(frames))) or record['padding']:
        return None
    # Supply the explicit selector domain to the shared image geometry check.
    # The original stored_count remains unchanged in the consumer evidence.
    shape = {key: record[key] for key in ('width', 'height', 'format', 'size')}
    shape.update(count=len(frames), flags=record['padding'])
    return cpu.storage_contract(shape, payload)


def load(root: Path, rom: bytes, entries, excluded_ids=()) -> dict[int, dict]:
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('glyph texture reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    records = verified_records(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    consumers = {f'func_{a:08X}': digest for a, _, digest in CONSUMERS}
    for record in records:
        for frame, resource in zip(record['frames'], record['resources']):
            if resource in excluded or resource in result or resource not in payloads:
                continue
            payload = payloads[resource]
            contract = storage_contract(record, payload)
            if contract is None or not cpu.reversible(contract, payload):
                continue
            result[resource] = dict(contract, family='cpu-glyph-selector', consumer={
                'glyph': record, 'selected_frame': frame, 'native_consumers': consumers,
                'jump_table_sha1': JUMP_SHA1, 'frame_extent_source': 'native-glyph-case',
                'loader_call': '0x150420E4', 'pixel_offset': 0, 'dxt': 0,
                'scope': 'complete-declared-storage-no-runtime-activation-claim'})
    return result
