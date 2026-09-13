"""ROM animation-event attachment ownership, for discovery only.

An event links an animation route to an action record. It does not prove that
gameplay reaches the animation, or supply textures, visibility or render state.
"""
from collections import Counter
import hashlib
import math
import struct

try:
    from scripts.model_object_texture_animation import checked
except ModuleNotFoundError:
    from model_object_texture_animation import checked


# Guard the route loader/relocator, event argument and parent propagation, and
# action-record protocol against the ROM itself, independently of matched C.
CONSUMERS = (
    (0x1503D438, 36, 'add9aec5cb5ff6df58ba80704156c1463b4a2071'),
    (0x1503D484, 140, '40f757370bbf19e10e675591d24421010455453d'),
    (0x1503D5F0, 112, '6b19502694fdcbcee75fc751b4d136adc57685df'),
    (0x1503D660, 276, '698addad07c12e755805e484a22441109dd90252'),
    (0x1505E650, 380, '7ff7faebb700286719b32f4b7390b9c9f772236b'),
    (0x1505E0C4, 1420, '3e17bb649f54edb53a448676e71fbea0adce0e10'),
    (0x1506AD30, 580, 'd812ac16d841c33e1022eb9989b506c2529fc62f'),
    (0x15072DD8, 96, '2a8ae3cdc55b7c02e48a44fac3cb0011fbc7e16c'),
    (0x15072E38, 68, 'f7b2bfe30013495d529f6e25e7c713328abe595d'),
    (0x15083568, 356, '419012702249e321c26fc2badb49949b0aafa0fc'),
    (0x1505BB80, 164, 'fa60e59b2bef62e539a3b10562d5bb8d541f1555'),
)
OPERATIONS = {105: 'create', 106: 'remove'}


def verify_consumers(code, code_base, data, data_base):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'attachment event consumer changed at 0x{address:08X}')
    if checked(data, data_base, 0x800865A0, 8) != bytes.fromhex('15072dd815072e38'):
        raise ValueError('attachment event dispatch changed')


def parse_events(payload, relative_offset):
    """Read a route's events after the native +0x10 relocation.

    The native event cursor is a byte; do not wrap it or scan through a missing
    time sentinel into another array. Tagged pointers need a separate proof.
    """
    if not relative_offset:
        return []
    if relative_offset & 0x0F000000:
        raise ValueError('tagged event pointer')
    offset = relative_offset + 0x10
    if offset % 4 or offset < 0x18:
        raise ValueError('event pointer alignment or range')
    events = []
    for index in range(256):
        at = offset + index * 12
        raw = checked(payload, 0, at, 12)
        time, command, argument = struct.unpack('>fII', raw)
        if not math.isfinite(time) or time < 0:
            raise ValueError('invalid event time')
        # func_1506AD30 only dispatches times strictly below 900.
        if time >= 900:
            return events
        opcode = command & 255
        if opcode in OPERATIONS:
            events.append({'event_index': index, 'event_offset': at,
                           'time': time, 'opcode': opcode,
                           'operation': OPERATIONS[opcode], 'action': argument,
                           'event_hex': raw.hex()})
    raise ValueError('event cursor would wrap before a time sentinel')


def action_records(data, base, action):
    """Follow one referenced header; do not infer an extent for the action table."""
    if not 1 <= action <= 0x7FFFFFFF:
        raise ValueError('invalid attachment action index')
    header_address = 0x80086CC4 + (action - 1) * 8
    header = checked(data, base, header_address, 8)
    pointer, count = struct.unpack('>IB3x', header)
    records = []
    if count:
        raw = checked(data, base, pointer, count * 16)
        for index in range(count):
            record = raw[index * 16:(index + 1) * 16]
            kind = record[3]
            if kind not in (0, 1, 2):
                raise ValueError('unreviewed action record kind')
            row = {'record_index': index, 'address': f'0x{pointer + index * 16:08X}',
                   'kind': kind, 'record_hex': record.hex()}
            # Kind zero modifies the parent; its first byte is not a bank-09 ID.
            if kind:
                row.update(bank=9, entry=record[0], updater=record[2])
            records.append(row)
    return {'header_address': f'0x{header_address:08X}',
            'header_hex': header.hex(), 'records': records}


def report(models, rom, layout, game):
    verify_consumers(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    banks = {bank.index: bank for bank in models.parse_asset_banks(rom, layout['asset_table'])}
    if banks[15].flags or banks[1].flags:
        raise ValueError('attachment ownership requires ordinary indexed banks')
    _, representatives = models.character_animation_group_routes(game.data, layout['game_data_vram'])
    parents = {}
    for entry in models.parse_asset_entries(rom, banks[1]):
        source = representatives.get(entry.index, entry.index)
        parents.setdefault(source, []).append(entry.index)
    rows, unresolved, actions = [], [], {}
    route_count = list_count = 0
    for entry in models.parse_asset_entries(rom, banks[15]):
        if entry.index not in parents:
            continue
        raw = rom[entry.start:entry.end]
        payload = models.decode_rzip_chunk(raw).data if entry.compressed else raw
        routes = models.parse_character_animation_route_table(payload)
        route_count += len(routes)
        for route in routes:
            if not route['auxiliary_offset']:
                continue
            list_count += 1
            source = {'route_bank': 15, 'route_entry': entry.index,
                      'parent_entries': parents[entry.index], **route,
                      'route_payload_sha1': hashlib.sha1(payload).hexdigest()}
            try:
                events = parse_events(payload, route['auxiliary_offset'])
            except ValueError as error:
                unresolved.append({**source, 'reason': str(error)})
                continue
            for event in events:
                action = event['action']
                if action not in actions:
                    try:
                        actions[action] = action_records(game.data, layout['game_data_vram'], action)
                    except ValueError as error:
                        actions[action] = {'unresolved': str(error)}
                rows.append({**source, **event, 'action_record': actions[action]})
    entries = sorted({record['entry'] for row in rows if row['operation'] == 'create'
                      for record in row['action_record'].get('records', []) if 'entry' in record})
    return {'status': 'discovery-only', 'events': rows, 'unresolved_lists': unresolved,
            'counts': {'routes': route_count, 'event_lists': list_count,
                       'unresolved_lists': len(unresolved), 'events': len(rows),
                       'actions': len(actions), 'attachment_entries': len(entries),
                       **dict(Counter(row['operation'] for row in rows))},
            'attachment_entries': entries,
            'consumer_sha1': {f'0x{a:08X}': h for a, _, h in CONSUMERS},
            'scope': 'Stored create/remove events and their possible parent models. Gameplay reachability, texture bindings and renderer state require separate evidence.',
            'capture_inputs': []}
