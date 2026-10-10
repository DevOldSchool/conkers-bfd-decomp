"""ROM-declared character selector writes, independent of gameplay activation."""
from __future__ import annotations
import hashlib
import struct
from pathlib import Path

try:
    from scripts import hud_assets as h, model_assets as models, model_character_alpha as alpha
    from scripts.rzip_archive import AssetBank
except ModuleNotFoundError:
    import hud_assets as h
    import model_assets as models
    import model_character_alpha as alpha
    from rzip_archive import AssetBank

US_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
UPDATE_SPANS = (
    (0x15061B4C, 2216, '778f796c508ca226bd8703d61321a62d0f05e8d3'),
    (0x1502EEF4, 296, '2da422b7989f9b16b67dc448f60332131031e4f0'),
)
UPDATE_TABLE = (0x8009942C, 12, '2ad45e94a4e6ad60e521d78b1792afa252ebfc8f')
SCRIPT_SPANS = (
    (0x1501d348, 1892, '438ba4bb6e8349c0e0e649dadfad11df5e4c9d25'),
    (0x15022398, 400, '57111be545a15f9f9d05f2ef0a339b9d8fd19a5a'),
    (0x1502a8a0, 592, '99742f426a0b5da3f225112ae76d1b83b0ee4c8b'),
    (0x15023de0, 848, '11567a10d6ce32683563a4256cb2cbca4dad38fb'),
    (0x15024130, 132, '654fd4a1945858b7d11934d538a2c8b3eceaa54c'),
    (0x150241b4, 324, 'd5dc8da1e79f4198e209863ae9f1b059b55790f5'),
    (0x15083e90, 288, '9056d859958dee82b4b70863bd102612d9a0b49c'),
    (0x150242f8, 788, '4b85a67da8029cd004c5fe4c8ccf7fc484171718'),
    (0x150265cc, 13804, '32032af0b879068fc27718c536bcea6e5617b9a0'),
    (0x15029bb8, 3304, '03b20740a59f376ca6d93047aa9cad59ee295b24'),
    (0x1502460c, 8128, '363af55b580310f7cfa3dee99c50a0065274dffd'),
)


def update_choices(manifest, code, code_base, data, data_base):
    native = alpha.checked_spans(code, code_base, UPDATE_SPANS)
    table = alpha.checked_spans(data, data_base, (UPDATE_TABLE,))
    mapping = struct.unpack('>3I', h.data_slice(data, data_base, UPDATE_TABLE[0], UPDATE_TABLE[0] + 12))
    result = {}
    # Exact assignments in 15061B4C; retain a representative state for each
    # outcome, without claiming that gameplay activates it.
    states = {66: [({'animation': 0}, {'10': 13}),
                   ({'animation': 1, 'prior_selector': 13, 'random_low_bits': 1}, {'10': 12}),
                   ({'animation': 1, 'prior_selector': 12, 'random_low_bits': 0}, {'10': 21})],
              91: [({'blink_phase': phase}, {'10': value, '11': value})
                   for phase, value in enumerate(mapping)]}
    for entry, choices in states.items():
        initial = manifest['entries'].get(entry)
        if initial is None:
            continue
        result[entry] = []
        for index, (state, indices) in enumerate(choices):
            name = f'native-update-{entry}-{index}'
            result[entry].append((name, {**initial, 'preset': name,
                'descriptor_indices': {**initial['descriptor_indices'], **indices}}, {
                'family': 'model-update-selector', 'native_consumers': native,
                'selector_table': table, 'representative_state': state,
                'scope': 'native-selector-outcome-no-runtime-activation-claim'}))
    return result


def command_selectors(data: bytes, track_index: int):
    """Read commands from the native fourth directory group, after metadata."""
    tracks = alpha.script_tracks(data)
    if not 0 <= track_index < len(tracks):
        raise ValueError('script selector track is out of range')
    counts = struct.unpack('>4H', models.nested_asset_payload(data, 0))
    if track_index >= counts[2]:
        return []
    child = 1 + 2 * counts[0] + counts[1] + track_index
    table_size = struct.unpack_from('>I', data)[0]
    if child * 8 >= table_size:
        raise ValueError('script selector command group is missing')
    start, flags = struct.unpack_from('>II', data, child * 8)
    size = flags & 0x0FFFFFFF
    if not size:
        return []
    if size < 32 or size % 8 or size // 8 > 65535 or start < table_size or start + size > len(data):
        raise ValueError('script selector command span is invalid')
    result = []
    # Native 150242F8 starts at +0x20, uses signed halfword time markers
    # and accumulates the unsigned delay byte. Preserve every preceding word.
    time = struct.unpack_from('>h', data, start + 2)[0]
    for index in range(4, size // 8):
        offset = start + index * 8
        raw = data[offset:offset + 8]
        opcode, delay, value, axis, extra, tail = struct.unpack('>bBhbbh', raw)
        if not opcode and not delay:
            time = value
            continue
        selector = None
        if axis in (0, 1):
            if opcode == 9 and 0 <= value <= 245:
                selector = (6 + axis, value)
            elif opcode == 5 and value == 111 and 0 <= extra <= 127:
                selector = (10 + axis, extra)
        if selector is not None:
            result.append({'segment': selector[0], 'descriptor_index': selector[1],
                'header_counts': list(counts), 'command_child': child,
                'command_offset': offset, 'command_index': index, 'command_hex': raw.hex(),
                'declared_time': time, 'delay': delay,
                'preceding_commands': [data[p:p + 8].hex() for p in range(start, offset, 8)]})
        time += delay
    return result


def load(root: Path, rom: bytes, manifest: dict):
    if hashlib.sha1(rom).hexdigest() != US_SHA1:
        raise ValueError('character selector reference ROM changed')
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    result = update_choices(manifest, game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    native = alpha.checked_spans(game.code, layout['game_vram'], SCRIPT_SPANS)
    callers = alpha.caller_evidence(rom, layout, game, list(manifest['entries']))
    contexts = {r['entry']: r for r in callers['spawn_contexts']}
    choices = {}
    for scene in callers['scene_script_routes']:
        context = contexts[scene['scene']]
        for script in scene['scripts']:
            start, end = (int(v, 16) for v in script['rom_span'])
            # Resolve compression through the indexed bank, not a magic guess.
            bank = next(b for b in models.parse_asset_banks(rom, layout['asset_table']) if b.index == 6)
            parent = next(e for e in models.parse_asset_entries(rom, bank) if e.index == scene['scene'])
            child = next(e for e in models.parse_asset_entries(rom, AssetBank(parent.index, parent.start, parent.end, 0))
                         if e.index == script['asset_path'][2])
            if (start, end) != (child.start, child.end):
                raise ValueError('script selector indexed source span changed')
            data = models.decode_rzip_chunk(rom[start:end]).data if child.compressed else rom[start:end]
            if hashlib.sha256(data).hexdigest() != script['sha256']:
                raise ValueError('script selector source changed')
            for track in script['matches']:
                entry = track['model'][1]
                for command in command_selectors(data, track['track_index']):
                    key = (entry, command['segment'], command['descriptor_index'])
                    proof = {'family': 'model-script-selector', 'native_consumers': native,
                        'spawn_consumers': callers['consumer_spans'], 'spawn_tables': callers['jump_table_spans'],
                        'script': {k: v for k, v in script.items() if k not in ('tracks', 'matches')},
                        'track': track, 'command': command,
                        'spawn_context': {k: v for k, v in context.items() if k != 'records'},
                        'spawn_record': next((r for r in context['records']
                                              if r['combined_record_index'] == track['combined_record_index']), None),
                        'scope': 'stored-selector-with-initial-type2-actor-binding; conditional-on-retaining-declared-model; no-runtime-activation-or-later-mutation-claim'}
                    # Prefer the shortest preceding sequence. All alternatives
                    # select the same descriptor in the same declared model.
                    if key not in choices or command['command_index'] < choices[key]['command']['command_index']:
                        choices[key] = proof
    for (entry, segment, descriptor), proof in sorted(choices.items()):
        initial = manifest['entries'][entry]
        name = f'script-selector-{segment}-{descriptor}'
        default = {**initial, 'preset': name,
                   'descriptor_indices': {**initial['descriptor_indices'], str(segment): descriptor}}
        result.setdefault(entry, []).append((name, default, proof))
    return result
