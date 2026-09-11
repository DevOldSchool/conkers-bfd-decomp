"""ROM skeletal particle-emission points, distinct from bank-09 meshes."""

from __future__ import annotations

import hashlib
import math
import struct


ENTRIES = (432, 434, 435, 436, 437, 438, 439, 440, 441, 442,
           443, 444, 446, 445, 448, 449, 450, 451, 452, 433)


def verify_consumers(code: bytes, base: int, data: bytes, data_base: int) -> None:
    for address, size, expected in (
        (0x151D2AB0, 156, "615898c1c5d6b9b244fa8d497321115ec67a9bc1"),
        (0x1518F8E0, 804, "0ce8ad245793e47b0e4ef4090938e9757a460e4e"),
    ):
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != expected:
            raise ValueError(f"ROM emission-point consumer changed at 0x{address:08X}")
    offset = 0x800AB140 - data_base
    if offset < 0 or data[offset:offset + 40] != struct.pack(">20H", *ENTRIES):
        raise ValueError("ROM emission-point selector table changed")


def encode_points(record: dict) -> bytes:
    if len(record['points']) != record['point_count']:
        raise ValueError('emission-point count changed')
    result = bytearray()
    for point in record['points']:
        padding = bytes.fromhex(point['reserved_bytes'])
        xyz = point['local_xyz']
        if len(padding) != 3 or len(xyz) != 3 or not all(math.isfinite(v) for v in xyz):
            raise ValueError('emission point has invalid reserved bytes or coordinates')
        result.extend(struct.pack('>B3s3f', point['matrix_slot'], padding, *xyz))
    return bytes(result)


def parse_points(payload: bytes) -> dict:
    if not payload or len(payload) % 16:
        raise ValueError('emission-point payload is not a complete nonempty record array')
    points = []
    for slot, padding, x, y, z in struct.iter_unpack('>B3s3f', payload):
        if not all(math.isfinite(v) for v in (x, y, z)):
            raise ValueError('emission point has nonfinite coordinates')
        points.append({'matrix_slot': slot, 'reserved_bytes': padding.hex(),
                       'local_xyz': [x, y, z]})
    result = {'point_count': len(points), 'decoded_size': len(payload),
              'sha1': hashlib.sha1(payload).hexdigest(), 'points': points}
    if encode_points(result) != payload:
        raise ValueError('emission points failed decoded-byte reconstruction')
    return result


def make_manifest(payloads: dict[int, bytes], code: bytes, base: int,
                  data: bytes, data_base: int, rom_sha1: str) -> dict:
    verify_consumers(code, base, data, data_base)
    records = []
    for selector, entry in enumerate(ENTRIES):
        if entry not in payloads:
            raise ValueError(f'ROM emission-point entry {entry} is missing')
        records.append({'selector': selector, 'bank_entry': entry,
                        **parse_points(payloads[entry])})
    return {'schema_version': 1, 'family': 'skeletal-particle-emission-points',
            'bank_index': 9, 'normalized_sha1': rom_sha1,
            'asset_count': len(records),
            'point_count': sum(record['point_count'] for record in records),
            'decoded_size': sum(record['decoded_size'] for record in records),
            'records': records,
            'runtime_evidence': {'loader': 'func_151D2AB0', 'consumer': 'func_1518F8E0',
                                 'selector_table': '0x800AB140', 'record_stride': 16,
                                 'matrix_slot_offset': 0, 'local_xyz_offset': 4,
                                 'matrix_pointer_actor_offset': '0x1D4', 'matrix_stride': 64},
            'scope': 'Local points transformed by an actor matrix for particle emission. '
                     'These records contain no triangles. Actor bindings and emitted particles '
                     'remain runtime dependent; no model preview is synthesized.'}
