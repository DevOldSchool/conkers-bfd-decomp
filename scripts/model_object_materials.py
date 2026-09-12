"""ROM evidence for the ordinary placed-object material submission path."""

from __future__ import annotations

import hashlib
import struct


# Complete reviewed US functions, checked against decompressed ROM code.
CONSUMERS = (
    (0x150039E0, 2964, 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66'),
    (0x151135C4, 528, '04f7c62d81e7232c89b3309fdeade178adab34aa'),
    (0x151137D4, 1204, '95326ee5c7b73267556e889aedfdef799930e221'),
    (0x1510CDB8, 168, '282363991e81e8426bba40fac6a6d38fe7dc2b54'),
    (0x150CF5E8, 152, '8774c883ae32954af463d41925ff90e1564c273f'),
    (0x1510D8C0, 176, '93a912bad5e9ddc0bebe3f683c48b2a06d31a773'),
    (0x1510D874, 76, 'ca5d61ecce77fe21f7b613e7d2c8a3e3860c6fe1'),
    (0x1511A494, 616, 'c896da27caa019639fe040e1d5bf9034f2663673'),
    (0x150DE458, 640, 'b7cfbca973185e0ea1a28d3f92bf09fe84789268'),
    (0x150C4E9C, 912, 'cd3797f43b47bc33b480ac40ed4970e74946a9b5'),
)
OVERRIDE_CALLS = (0x150C5210, 0x150DE69C, 0x1511A6C8)
OBJECT_TABLE = 0x800A26C0


def verify_consumers(code: bytes, base: int, data: bytes) -> list[dict]:
    records = []
    for address, size, expected in CONSUMERS:
        offset = address - base
        if offset < 0 or offset + size > len(code):
            raise ValueError('object material consumer is outside ROM code')
        actual = hashlib.sha1(code[offset:offset + size]).hexdigest()
        if actual != expected:
            raise ValueError(f'object material consumer changed: 0x{address:08X}')
        records.append({'function': f'func_{address:08X}', 'size': size, 'sha1': actual})
    calls = []
    for offset in range(0, len(code) - 3, 4):
        word = struct.unpack_from('>I', code, offset)[0]
        if word >> 26 in (2, 3):
            target = ((base + offset + 4) & 0xF0000000) | ((word & 0x3FFFFFF) << 2)
            if target == 0x1510D874:
                calls.append(base + offset)
    if tuple(calls) != OVERRIDE_CALLS:
        raise ValueError('object segment override callers changed')
    if any(struct.unpack_from('>I', data, offset)[0] == 0x1510D874
           for offset in range(0, len(data) - 3, 4)):
        raise ValueError('object segment override has an unreviewed data pointer')
    return records


def placement_contexts(placements: dict, data: bytes, base: int) -> list[dict]:
    """Keep only resolved placements with a proven ordinary direct draw path.

    Bank 03 flags come from its twelve-byte ROM defaults, overriding placement
    flags. Bank 04 dispatch kinds one/two use the placement flags. A rewritten
    display-list path (runtime +0x70 bit 1) is deliberately outside this scope.
    """
    contexts = {}
    for scene in placements['scenes']:
        for record in scene['records']:
            source = record['model_source']
            kind = record['dispatch_kind']
            if (scene['bank_index'] == 0x0C and kind == 0 and len(source) == 2
                    and source[0] == 3
                    and record['model_resolution_status'] == 'resolved-bank-03-model'):
                offset = OBJECT_TABLE - base + source[1] * 12
                if offset < 0 or offset + 12 > len(data):
                    raise ValueError('object material defaults exceed ROM data')
                default = data[offset:offset + 12]
                flags = default[9] & 0xF7
                flag_source = {'address': f'0x{base + offset:08X}',
                               'sha1': hashlib.sha1(default).hexdigest(),
                               'flags_offset': 9}
                key = (3, source[1], 0)
            elif (scene['bank_index'] == 0x0B and kind in (1, 2) and len(source) == 3
                  and source[0] == 4 and source[1] == scene['scene_index']
                  and record['model_resolution_status'] == 'resolved-bank-04-segment'):
                flags = bytes.fromhex(record['bytes_3c_3f'])[0] & 0xF7
                flag_source = {'placement_offset': 0x3C}
                key = tuple(source)
            else:
                continue
            if flags & 2:
                continue
            contexts.setdefault(key, []).append({
                'source_bank': scene['bank_index'], 'scene': scene['scene_index'],
                'record': record['index'], 'record_sha1': record['sha1'],
                'dispatch_kind': kind, 'initial_flags_70': flags,
                'flag_source': flag_source,
            })
    return [{'bank': key[0], 'entry': key[1], 'segment': key[2],
             'placements': records, 'renderer': 'func_151137D4',
             'segment_8_bases': ['0x80083D40', '0x80083EC0'],
             'scope': 'Ordinary direct placement draw path; visibility, rewritten lists, runtime colours and raster parity unresolved.'}
            for key, records in sorted(contexts.items())]
