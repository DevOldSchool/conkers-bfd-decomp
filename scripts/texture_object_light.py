"""Complete scene28 texture sources selected by authored light phase callbacks.

A finite transition witness establishes row1 of the object texture table.
This is a source-storage contract, not observed gameplay or raster parity.
"""
from __future__ import annotations

import copy
import hashlib
import math
import struct

try:
    from scripts import hud_assets as h
    from scripts.rzip_archive import AssetBank
except ModuleNotFoundError:
    import hud_assets as h
    from rzip_archive import AssetBank


CONSUMERS = (
    (0x15017930, 496, '1d10415e266535b4781290cc22658bd25fe7dd65'),
    (0x15017b20, 1156, '74b6a2734f896eff5c1f715080bc802eb04de812'),
    (0x150092dc, 88, '090462902c9d181dfe597823b9fa8e675080c555'),
    (0x15009334, 676, 'b231dfe5319d821c5d9eea5c92696ef83f367ff3'),
    (0x1500a94c, 68, 'ceacead0ebfca163eb80242f6a49ae8c46667cac'),
    (0x15009990, 168, 'f58e7ff49115d8106e7bf96f848836067dfb97fa'),
    (0x1516295c, 460, '7be5e6587d3aab0103cc265d789807d6fb2af912'),
    (0x15162b28, 976, 'cf2a0c61fcec43918215e73dde5bbcbf35e784b5'),
    (0x15162ef8, 88, 'b22800103be74537c6809b327731c75c7deacba0'),
    (0x15162f50, 92, 'fec9ffae822607980d8432047712b3f86ab154ff'),
    (0x151149ac, 112, 'a831c20eb614451ce4fc3c1acbd67b004a69cf0a'),
    (0x150039e0, 2964, 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66'),
    (0x150de458, 640, 'b7cfbca973185e0ea1a28d3f92bf09fe84789268'),
    (0x1516037c, 128, 'bcdaa006b0cc0da46ff35e4152c75c1f0aaed35d'),
    (0x151603fc, 164, '1ea73b90fe4cef3b7ad03972af11e34f3823834d'),
)
DATA = (
    (0x80082c5c, '15009990150099901500999015009990'),
    (0x80095b60, '010203041718191af6f3edf0'),
    (0x8008b364, '15162ef815162f50'),
    (0x80090204, '00000692000006930000069400000695'),
    (0x800a6880, '0000000042480000424800004248000042480000000000004170000041700000417000004170000000000000000000004178000041f80000423a000041200000414000004140000041400000414000004120000041c8000041c8000041c8000041c800004120000000000000000000000000000000000000'),
    (0x8008B120, '15162b28'),
    (0x80095B78, '15009390'),
)
LIGHT_SHA1 = '89e976a550fa2ed7c7ac953ebf22f18aa4a41111'
MODEL_SHA1 = '09f009709a08538634b0ed25724f9ec80c03b102'
PLACEMENTS = {
    8: (246, '0822ad69a9bdad9860eb148662be3f100c370acf'),
    11: (243, '60970894a473804291d83442f9995f35ccdc4636'),
    14: (240, '10e1cee47510653d11e3ed7305c7fae606238837'),
    17: (237, 'b2c397b19d80db615f2f48a0688221950b8ac714'),
}
LIGHT_LINKS = ((35, 24, 246, 8), (39, 25, 243, 11),
               (40, 26, 237, 17), (41, 27, 240, 14))


def verified_native(code, code_base, data, data_base):
    for address, size, digest in CONSUMERS:
        raw = h.data_slice(code, code_base, address, address + size)
        if hashlib.sha1(raw).hexdigest() != digest:
            raise ValueError('object light consumer changed')
    for address, expected in DATA:
        raw = bytes.fromhex(expected)
        if h.data_slice(data, data_base, address, address + len(raw)) != raw:
            raise ValueError('object light table changed')
    return struct.unpack('>2I', h.data_slice(data, data_base, 0x8009020C, 0x80090214))


def phase_callback(time, previous_phase):
    """Parameter1's bounded native phase transition before the 62-tick wrap."""
    if not math.isfinite(time) or not 0 <= time < 62 or previous_phase not in range(4):
        raise ValueError('unreviewed light phase witness')
    phase = 0 if time < 12 else 1 if time < 37 else 3
    callback = (-1, 0, -1, 1)[phase]
    return callback if phase != previous_phase and callback >= 0 else None


def checked_sources(light_data, placements):
    if len(light_data) != 4160 or hashlib.sha1(light_data).hexdigest() != LIGHT_SHA1:
        raise ValueError('object light scene source changed')
    targets = set(value[0] for value in PLACEMENTS.values())
    observed = []
    for scene in placements['scenes']:
        if scene['scene_index'] != 28:
            continue
        for record in scene['records']:
            raw = bytes.fromhex(record['raw_hex'])
            if raw[0x33] not in targets:
                continue
            expected = PLACEMENTS.get(record['index']) if scene['bank_index'] == 11 else None
            if (expected != (raw[0x33], hashlib.sha1(raw).hexdigest())
                    or record['model_source'] != [4, 28, 12]
                    or record['dispatch_kind'] != 1 or int(record['word_14'], 16) != 24):
                raise ValueError('object light target placement changed or is ambiguous')
            observed.append(raw[0x33])
    if sorted(observed) != sorted(targets):
        raise ValueError('object light targets are missing or duplicated')
    for index, callback, object_id, placement in LIGHT_LINKS:
        row = light_data[index * 52:(index + 1) * 52]
        if (row[0x15] >> 2 != 9 or struct.unpack_from('>I', row, 0x20)[0] != callback
                or PLACEMENTS[placement][0] != object_id):
            raise ValueError('object light descriptor changed')
    if phase_callback(12, 0) != 0:
        raise ValueError('light phase witness no longer sets the selector')


def load(root, rom, entries, excluded_ids=()):
    try:
        from scripts import model_assets as models, texture_model_catalog as catalog
    except ModuleNotFoundError:
        import model_assets as models
        import texture_model_catalog as catalog
    path = root / 'roms/baserom.us.z64'
    _, layout = h.resolve_rom('us', path)
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout['normalized_sha1']:
        raise ValueError('object light reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    resources = verified_native(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    if set(resources) <= set(excluded_ids):
        return {}
    bank = next(b for b in models.parse_asset_banks(rom, layout['asset_table']) if b.index == 12)
    scene = next(e for e in models.parse_asset_entries(rom, bank) if e.index == 28)
    if bank.flags or scene.type_flags:
        raise ValueError('object light scene directory changed')
    entry = next(e for e in models.parse_asset_entries(rom, AssetBank(28, scene.start, scene.end, 0))
                 if e.index == 5)
    if entry.type_flags & ~0x90:
        raise ValueError('object light source flags changed')
    raw = rom[entry.start:entry.end]
    light_data = models.decode_rzip_chunk(raw).data if entry.compressed else raw
    placements, _ = models.load_object_placement_manifest('us', path, include_files=False)
    checked_sources(light_data, placements)
    _, _, _, bundles, tables = models.load_model_bundles('us', path, 4)
    bundle = next(b for b in bundles if b.index == 28)
    segment = next(s for s in bundle.segments if s.index == 12)
    if hashlib.sha1(segment.data).hexdigest() != MODEL_SHA1:
        raise ValueError('object light model changed')
    geometry = models.parse_segment_geometry(segment, 4)
    context = copy.deepcopy(next(c for c in models.load_object_material_context('us', path, digest, 4)['models']
                                 if c['entry'] == 28 and c['segment'] == 12))
    binding = context['texture_binding']
    binding['selector'].update(selected_value=1, table_sha1=hashlib.sha1(
        h.data_slice(game.data, layout['game_data_vram'], 0x80090204, 0x80090214)).hexdigest())
    binding['preview_policy'] = 'Authored light phase transition witness; not sampled gameplay'
    binding['scope'] = 'Source storage under light callback0 setting object selector1'
    for key, resource in zip(('4', '6'), resources):
        binding['bindings'][key]['flats'] = [resource]
    payloads, result = {e.index: e.data for e in entries}, {}
    for index, run in enumerate(geometry.material_runs[:2]):
        resource = resources[index]
        if resource in excluded_ids:
            continue
        preview, status, evidence = models.rom_object_binding_preview_texture(run, {}, payloads, tables, context)
        if preview is None or preview.flat_index != resource:
            raise ValueError('object light material binding changed')
        contract = catalog.full_payload_contract(preview, payloads[resource])
        if contract is None:
            raise ValueError('object light source is not completely reversible')
        result[resource] = dict(contract, family='object-light-phase', consumer={
            'model': [4, 28, 12], 'material_run': index, 'model_sha1': MODEL_SHA1,
            'light_source': [12, 28, 5], 'light_sha1': LIGHT_SHA1,
            'links': [list(link) for link in LIGHT_LINKS],
            'native_consumers': {f'func_{a:08X}': d for a, _, d in CONSUMERS},
            'native_data': {f'0x{a:08X}': raw for a, raw in DATA},
            'phase_witness': {'light_callback': 24, 'parameter': 1, 'time': 12,
                              'previous_phase': 0, 'callback': 0, 'object_selector': 1},
            'binding_evidence': evidence, 'status': status,
            'scope': 'Complete stored source under authored light phase; activation and raster parity unobserved'})
    return result
