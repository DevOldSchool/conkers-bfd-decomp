"""Complete texture selectors from the reviewed scene-47 event program."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

try:
    from scripts import hud_assets as h, model_assets as models
    from scripts import model_character_alpha as alpha, model_event_activation as events
except ModuleNotFoundError:
    import hud_assets as h
    import model_assets as models
    import model_character_alpha as alpha
    import model_event_activation as events

PROGRAM_SHA256 = '9063ed0feb352943a0a311a13c91501ae98551174d08a59e1dc2628c0ebe7709'
BLOCK_SHA256 = '577d6daec0d0930c9c790754cdf7f9a4b50186ac4173c2ca83f149ee00d1c74c'
SOURCES = {
    (0x14, 164): (1944, PROGRAM_SHA256),
    (0x15, 47): (104, 'eee676c531d2220c31e431779906822cc36af92bd277d9320cb8468de1171fc2'),
    (0x0E, 47): (768, 'eb5e6d9721892e088f34afcc827725376fa3b324bb770924b4579381196448fa'),
}
NATIVE_SPANS = events.CODE_SPANS + alpha.CALLER_SPANS + (
    (0x150AE0F8, 156, '975470960e4fa55d46e350b58276333ddaed1908'),
    (0x15097910, 188, '8ee6883546fe677fd01ceba87df56302a0424626'),
    (0x1505EEF4, 220, '1103976ffa718b02f3bddfa0bf52f9bc6d953a34'),
    (0x15083E90, 288, '9056d859958dee82b4b70863bd102612d9a0b49c'),
    (0x15097A8C, 8584, '652bb7dc25c580be9d73f138b68687333da7ce6d'),
)
TABLE_SPANS = events.DATA_SPANS + alpha.CALLER_TABLES + (
    (0x80088420, 60, '78ad5cea787d5c2b3c5aa11c54631a3c63f0206f'),
    (0x8009DF50, 568, '6765968de57df1af29310d6de91016be03e2ec88'),
)
CASES = ((0x686, 110, 0, 8), (0x69A, 110, 1, 10), (0x6AE, 111, 0, 2))


def program_requests(data: bytes) -> list[dict]:
    if len(data) != 1944 or hashlib.sha256(data).hexdigest() != PROGRAM_SHA256:
        raise ValueError('event-selector program source changed')
    if hashlib.sha256(data[0x64E:0x6B2]).hexdigest() != BLOCK_SHA256:
        raise ValueError('event-selector constructor block changed')
    program = events.decode_program(data)
    calls = events.call_packets(program, data, 47)
    rows = {r['offset']: r for r in program['instructions']}
    packets = {c['offset']: c for c in calls}
    targets = set(program['entrypoints']) | {r['target'] for r in rows.values()
              if 'target' in r and r.get('dispatch') != 'native'}
    if program['instruction_count'] != 370 or any(0x64E < at < 0x6B2 for at in targets):
        raise ValueError('event-selector constructor control flow changed')

    def operands(record):
        return [(a['mode'], a['value']) for a in record['operands']]

    create = packets.get(0x652, {})
    if (create.get('dispatch') != 'native' or create.get('target') != 3
            or not create.get('packet_complete') or create.get('syntactic_argument_count') != 1
            or create.get('literal_arguments') != [0x2018]
            or create.get('packet_span') != [0x64E, 0x656]):
        raise ValueError('event-selector actor constructor changed')
    for at, end, expected in ((0x656, 0x65C, [(0, -8), (5, 0)]),
                              (0x65C, 0x662, [(1, 36), (0, -8)])):
        row = rows.get(at)
        if row is None or row['opcode'] != 14 or row['end'] != end or operands(row) != expected:
            raise ValueError('event-selector actor handle assignment changed')
    # Operation 61 changes actor+0x94 flags; the guarded native arm preserves
    # the model and the actor handle before the three selector writes.
    expected_calls = ((0x672, 61, 1, 2), *CASES)
    result = []
    for at, operation, axis, descriptor in expected_calls:
        call = packets.get(at, {})
        args = [(a['mode'], a['value']) for a in call.get('arguments', [])]
        if (call.get('dispatch') != 'native' or call.get('target') != 6
                or not call.get('packet_complete') or call.get('syntactic_argument_count') != 4
                or call.get('packet_span') != [at - 16, at + 4]
                or args != [(1, 36), (4, operation), (4, axis), (4, descriptor)]):
            raise ValueError('event-selector native packet changed')
        if operation in (110, 111):
            result.append({'segment': (6 if operation == 110 else 10) + axis,
                'descriptor_index': descriptor, 'constructor': create, 'call': call,
                'actor_handle': {'return_to_frame': -8, 'frame_to_state': 36},
                'constructor_block_span': [0x64E, 0x6B2],
                'constructor_block_sha256': BLOCK_SHA256})
    return result


def load(root: Path, rom: bytes, manifest: dict) -> dict:
    if hashlib.sha1(rom).hexdigest() != events.US_SHA1:
        raise ValueError('event-selector reference ROM changed')
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    native = alpha.checked_spans(game.code, layout['game_vram'], NATIVE_SPANS)
    tables = alpha.checked_spans(game.data, layout['game_data_vram'], TABLE_SPANS)
    banks = {b.index: b for b in models.parse_asset_banks(rom, layout['asset_table'])}
    sources = {}
    for path, (size, digest) in SOURCES.items():
        source, data = events._asset(rom, banks[path[0]], path[1])
        if len(data) != size or hashlib.sha256(data).hexdigest() != digest:
            raise ValueError('event-selector indexed source changed')
        sources[path] = source, data
    listing = events.scene_event_list(sources[(0x15, 47)][1])
    if listing['event_ids'] != [164, 165]:
        raise ValueError('event-selector scene route changed')
    branch = struct.unpack_from('>I', game.data, 0x80096760 - layout['game_data_vram'] + 21 * 4)[0]
    prefix = rom[0x1A33F0:0x1A34E0]
    if (branch != 0x150169F8 or hashlib.sha256(prefix).hexdigest()
            != 'c00f174e84c2718bda836eab7ed50ccb5598f766207758e0a105f9a00c3433be'):
        raise ValueError('event-selector scene prefix changed')
    spawns = alpha.spawn_records(prefix + sources[(0x0E, 47)][1], set(range(256)))
    spawn = next((s for s in spawns if s['script_selector'] == 24), None)
    if spawn is None or spawn['record_index'] != 9 or spawn['model'] != [1, 141, 0]:
        raise ValueError('event-selector first actor binding changed')
    initial = manifest['entries'][141]
    result = []
    for request in program_requests(sources[(0x14, 164)][1]):
        segment, descriptor = request['segment'], request['descriptor_index']
        name = f'event164-selector-{segment}-{descriptor}'
        default = {**initial, 'preset': name,
                   'descriptor_indices': {**initial['descriptor_indices'], str(segment): descriptor}}
        proof = {'family': 'model-event-selector', 'native_consumers': native, 'native_tables': tables,
            'program_source': sources[(0x14, 164)][0],
            'scene_source': {**sources[(0x15, 47)][0], **listing},
            'spawn_source': sources[(0x0E, 47)][0], 'spawn_record': spawn,
            'prefix_source': {'rom_span': ['0x1A33F0', '0x1A34E0'],
                              'sha256': hashlib.sha256(prefix).hexdigest()},
            'request': request,
            'scope': 'stored-event-selector; conditional-on-successful-actor-resolution-and-declared-model-retention; no-runtime-activation-claim'}
        result.append((name, default, proof))
    return {141: result}
