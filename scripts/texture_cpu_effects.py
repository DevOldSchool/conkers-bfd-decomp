"""Native effect, literal-image and glyph descriptors with complete storage.

The pointer table, direct callers and compact output descriptors are separate
from the indexed CPU table. Keep their evidence separate so existing source
contracts remain stable. These contracts make no runtime activation claim.
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


POINTER_TABLE = 0x8008CA4C
POINTER_COUNT = 70
POINTER_SHA1 = '1fb1c60fa07f94d3bd658a7bdcd0fbde4180ca58'
POINTER_DESCRIPTORS_SHA1 = '2fe0ddc4b23e442e062b8920f0f45a46f035774c'
POINTER_FRAMES_SHA1 = 'e9d415fa261196531d81c104eff6e29a15a5a104'
CALLBACKS = (0x15164EE4, 0x1515C158, 0x151787A4)
# Ordered native a1 descriptor arguments to 0x15094F70, including the
# 0x150417AC glyph selector's declared frame arrays. Not a shape scan.
LITERALS = (
    0x8009054C, 0x80091840, 0x80090614, 0x800903BC,
    0x8009056C, 0x8009057C, 0x8009058C, 0x8009059C,
    0x800903F4, 0x8009055C, 0x800916AC, 0x800916C8,
    0x800916E4, 0x80091700, 0x80091710, 0x80091720,
    0x80091730, 0x80091740, 0x80091750, 0x80091764,
)
LITERAL_SHA1 = '1ad7c739ada61261d8cdabf60471f3576824208f'
LITERAL_FRAMES_SHA1 = 'c2d113ee6d259f82f41d948f2d0a11713e241b65'
COMPACT = (
    (0x800903AC, '955036d232a214271063f03606db17bc5c50c6d6'),
    (0x800915A4, 'eed89aa914c5401fa0f2c87c720898c231ede933'),
)
COMPACT_ARRAY = 0x80091564
COMPACT_ARRAY_COUNT = 16
COMPACT_ARRAY_SHA1 = '1bacc6ad50dd535f73c0c53749e68c20ddaa80c3'
CONSUMERS = cpu.CONSUMERS + (
    (0x1516706C, 84, 'dba52353d7db1fb5a93ffa611169f6f328737b3c'),
    (0x1516D738, 612, '6bd4d690e7cf7ed6c855016f0060451e0fdb0457'),
    (0x15167C58, 300, '6677ff4442f4123b43b69f7a309b508bd2665d8d'),
    (0x15094F70, 120, 'feaf43a9d43b1baf9c70caf21784a0a4a3cd8a28'),
    (0x15166F6C, 108, '10c4b4a7a34169fdd0140b7923b0b8bdc833d580'),
    (0x15090630, 780, 'a48a719176cc700d322395f7bb10f506fc284cde'),
    (0x1517A9A8, 120, 'e15203d563d0d968caef5b92e4665ff4d909221b'),
    (0x150368C4, 940, 'e96e5057c4ad77c4f8411029b049167221a1da74'),
    (0x1516B6BC, 4540, 'b249dabf50910c66d2018a6f96261e19d5dfa103'),
    (0x1517E4A8, 1444, '5ca108382f914c2c329408a28a149d6485988e60'),
    (0x1514803C, 2184, 'bd44fa1c8242afa31d2f10b99b7f79c5cc09b672'),
    (0x151668B8, 232, 'f27068062e162589616a1312769fd9a343adf3ae'),
    (0x150417AC, 4392, 'a778546ac55048b14f49c93aa0016b5771218e39'),
)


def checked(raw: bytes, expected: str, label: str) -> bytes:
    if hashlib.sha1(raw).hexdigest() != expected:
        raise ValueError(f'CPU effect {label} changed')
    return raw


def verified_descriptors(code: bytes, code_base: int, data: bytes, data_base: int):
    def read(address, size):
        return h.data_slice(data, data_base, address, address + size)

    for address, size, digest in CONSUMERS:
        checked(h.data_slice(code, code_base, address, address + size), digest,
                f'consumer 0x{address:08X}')
    if read(cpu.SIZE_TABLE, 16) != cpu.SIZE_BYTES:
        raise ValueError('CPU effect transfer-size tables changed')
    pointers = struct.unpack(f'>{POINTER_COUNT}I', checked(
        read(POINTER_TABLE, POINTER_COUNT * 4), POINTER_SHA1, 'pointer table'))
    if read(POINTER_TABLE + POINTER_COUNT * 4, 12) != struct.pack('>3I', *CALLBACKS):
        raise ValueError('CPU effect pointer table boundary changed')
    records = []
    groups = (
        ('pointer', [(i, a) for i, a in enumerate(pointers) if a],
         POINTER_DESCRIPTORS_SHA1, POINTER_FRAMES_SHA1),
        ('literal', list(enumerate(LITERALS)), LITERAL_SHA1, LITERAL_FRAMES_SHA1),
    )
    for kind, addresses, descriptor_digest, frame_digest in groups:
        raws = [read(a, 12) for _, a in addresses]
        checked(b''.join(raws), descriptor_digest, f'{kind} descriptors')
        frame_arrays = []
        for (selector, address), raw in zip(addresses, raws):
            pointer, count, flags, width, height, fmt, size = struct.unpack('>IBBHHBB', raw)
            frames = read(pointer, count * 4) if pointer >= 0x80000000 else b''
            if pointer >= 0x80000000:
                frame_arrays.append(frames)
                resources = list(struct.unpack(f'>{count}I', frames))
            else:
                resources = [pointer] if 0 < pointer < 0x10000000 else []
            records.append({'kind': kind, 'selector': selector,
                            'address': f'0x{address:08X}', 'sha1': hashlib.sha1(raw).hexdigest(),
                            'pointer': pointer, 'count': count, 'flags': flags,
                            'width': width, 'height': height, 'format': fmt, 'size': size,
                            'resources': resources, 'frame_sha1': hashlib.sha1(frames).hexdigest(),
                            'descriptor_group_sha1': descriptor_digest,
                            'frame_group_sha1': frame_digest})
        checked(b''.join(frame_arrays), frame_digest, f'{kind} frame arrays')
    array = checked(read(COMPACT_ARRAY, COMPACT_ARRAY_COUNT * 4), COMPACT_ARRAY_SHA1,
                    'compact resource array')
    for address, digest in COMPACT:
        raw = checked(read(address, 12), digest, 'compact descriptor')
        source, width, height, fmt, size, flags, pad = struct.unpack('>IHHBBBB', raw)
        if flags not in (0, 1) or pad:
            raise ValueError('unsupported compact descriptor flags')
        resources = list(struct.unpack(f'>{COMPACT_ARRAY_COUNT}I', array)) if source == 0 else [source]
        records.append({'kind': 'compact', 'address': f'0x{address:08X}', 'sha1': digest,
                        'pointer': source, 'width': width, 'height': height,
                        'format': fmt, 'size': size, 'flags': flags, 'resources': resources,
                        'resource_array_address': f'0x{COMPACT_ARRAY:08X}' if source == 0 else None,
                        'resource_array_sha1': COMPACT_ARRAY_SHA1 if source == 0 else None,
                        'explicit_pixel_frame_offset': 0})
    return records


def load(root: Path, rom: bytes, entries, excluded_ids=()) -> dict[int, dict]:
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('CPU effect reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    records = verified_descriptors(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    payloads, excluded, result = {e.index: e.data for e in entries}, set(excluded_ids), {}
    consumers = {f'func_{a:08X}': digest for a, _, digest in CONSUMERS}
    for record in records:
        # Both compact callers supply an explicit zero pixel-frame offset to
        # 0x150950D4. Preserve their original flags in the proof, not the input
        # descriptor layout. No arbitrary flagged descriptor is normalized.
        shape = dict(record, count=1, flags=0) if record['kind'] == 'compact' else record
        for frame, resource in enumerate(record['resources']):
            if resource in excluded or resource in result or resource not in payloads:
                continue
            payload = payloads[resource]
            contract = cpu.storage_contract(shape, payload)
            if contract is None or not cpu.reversible(contract, payload):
                continue
            result[resource] = dict(contract, family='cpu-effect-descriptor', consumer={
                'descriptor': record, 'selected_frame': frame,
                'pointer_table_sha1': POINTER_SHA1, 'native_consumers': consumers,
                'size_table_bytes': cpu.SIZE_BYTES.hex(), 'pixel_offset': 0, 'dxt': 0,
                'scope': 'complete-declared-storage-no-runtime-activation-claim'})
    return result
