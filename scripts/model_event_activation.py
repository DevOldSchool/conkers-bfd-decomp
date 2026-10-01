"""ROM-only event diagnostics for reviewed scenes 30 and 60.

This decodes bytecode and conditional requests; it does not execute events or
establish a rendered appearance.
"""
from __future__ import annotations

import argparse
from collections import deque
import hashlib
import json
from pathlib import Path
import struct

from scripts import model_assets as models
from scripts.model_character_alpha import checked_spans

ROOT = Path(__file__).resolve().parents[1]
US_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
# 80087358 stores operand count + 1. Opcode zero dispatches through a null
# pointer and is rejected, even though its arity-table byte is one.
ARITY = (0, 3, 3, 3, 3, 3, 2, 2, 2, 3, 3, 3, 3, 3, 2, 1,
         2, 2, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 0, 3, 3)
MODE_NAMES = ('frame-word', 'state-word', 'data-address', 'program-offset',
              'literal', 'return-word', 'native-index')


def decode_program(data: bytes) -> dict:
    """Decode the unrelocated asset, failing closed on unsupported syntax."""
    if len(data) < 34 or len(data) % 2:
        raise ValueError('event program extent is invalid')
    header = struct.unpack_from('>16H', data)
    if (header[2] != len(data) or header[4:7] != (0, 0, 0)
            or any(header[11:]) or header[0] not in (0x1000, 0x1800) or header[1]):
        raise ValueError('unsupported unrelocated event header')
    entries = [0x20, *header[7:11]]
    rows = []
    at = 0x20
    while at < len(data):
        begin = at
        word = struct.unpack_from('>H', data, at)[0]
        opcode = word & 63
        if not 0 < opcode < len(ARITY):
            raise ValueError(f'unsupported event opcode at 0x{at:X}')
        at += 2
        wide = bool(word & 0x40)
        operands = []
        for index in range(ARITY[opcode]):
            mode = (word >> (13 - index * 3)) & 7
            if mode == 7:
                raise ValueError('unsupported event operand mode')
            size = 4 if wide and mode in (3, 4, 6) else 2
            if at + size > len(data):
                raise ValueError('truncated event operand')
            value = struct.unpack_from('>i' if size == 4 else '>h', data, at)[0]
            operands.append({'mode': mode, 'kind': MODE_NAMES[mode], 'value': value,
                             'encoded_offset': at, 'encoded_bytes': size})
            at += size
            if size == 4:
                wide = False
        if wide:
            raise ValueError('wide flag has no immediate operand')
        row = {'offset': begin, 'end': at, 'opcode': opcode, 'word': word,
               'operands': operands}
        if opcode in (15, 16, 17):
            target = operands[-1]
            if target['mode'] != 3:
                raise ValueError('unsupported computed event branch')
            row['target'] = target['value']
        if opcode == 25:
            arg = operands[0]
            if arg['mode'] == 3:
                row.update(dispatch='internal', target=arg['value'])
            elif arg['mode'] == 6 and 0 <= arg['value'] < 14:
                row.update(dispatch='native', target=arg['value'])
            else:
                raise ValueError('unsupported event call target')
        rows.append(row)
    offsets = {r['offset'] for r in rows}
    if any(e not in offsets for e in entries):
        raise ValueError('event entry is not an instruction boundary')
    for row in rows:
        if 'target' in row and row.get('dispatch') != 'native' and row['target'] not in offsets:
            raise ValueError('event branch/call target is not an instruction boundary')
    return {'decoded_bytes': len(data), 'instruction_count': len(rows),
            'declared_state_bytes': header[3], 'entrypoints': entries,
            'instructions': rows}


def _argument_counts(program: dict) -> dict[int, set[int]]:
    """Conservative push-count dataflow, not value or reachability evaluation.

    All five entrypoints and internal callees start with the interpreter's reset
    argument count. Both conditional edges are followed. A native/internal call
    resets the pending count; return has no successor. -1 is unbounded/unknown.
    """
    rows = {r['offset']: r for r in program['instructions']}
    counts = {at: set() for at in rows}
    queue = deque()
    for at in set(program['entrypoints']) | {r['target'] for r in rows.values()
                                            if r.get('dispatch') == 'internal'}:
        counts[at].add(0)
        queue.append(at)
    while queue:
        at = queue.popleft()
        row = rows[at]
        values = counts[at]
        op = row['opcode']
        after = ({0} if op == 25 else
                 {-1 if v < 0 or v >= 256 else v + 1 for v in values}
                 if op == 24 else values)
        successors = ([] if op in (26, 28) else [row['target']] if op == 15 else
                      [row['target'], row['end']] if op in (16, 17) else [row['end']])
        for target in successors:
            if target not in rows:
                raise ValueError('event control flow falls outside instruction extent')
            combined = counts[target] | after
            if combined != counts[target]:
                counts[target] = combined
                queue.append(target)
    return counts


def call_packets(program: dict, data: bytes, scene: int) -> list[dict]:
    """Record adjacent PUSH instructions in native argument order (reversed)."""
    counts = _argument_counts(program)
    rows = program['instructions']
    targets = set(program['entrypoints']) | {r['target'] for r in rows
                                           if 'target' in r and r.get('dispatch') != 'native'}
    calls = []
    for index, row in enumerate(rows):
        if row['opcode'] != 25:
            continue
        args = []
        first = index
        while first and rows[first - 1]['opcode'] == 24:
            first -= 1
            args.append(rows[first]['operands'][0])
        start, end = rows[first]['offset'], row['end']
        complete = (counts[row['offset']] == {len(args)}
                    and not any(start < t <= row['offset'] for t in targets))
        calls.append({'offset': row['offset'], 'scene_context': scene,
                      'dispatch': row['dispatch'], 'target': row['target'],
                      'arguments': args, 'syntactic_argument_count': len(args),
                      'literal_arguments': [a['value'] for a in args]
                      if all(a['mode'] == 4 for a in args) else None,
                      'packet_complete': complete,
                      'pending_argument_counts': sorted(counts[row['offset']]),
                      'packet_span': [start, end],
                      'packet_sha256': hashlib.sha256(data[start:end]).hexdigest()})
    return calls


def scene_event_list(data: bytes) -> dict:
    # The first descriptor is the 0x4c-byte scene header; its byte+0x12
    # supplies the count to 15002FB4. The second descriptor supplies event IDs.
    if len(data) < 16:
        raise ValueError('scene event directory is truncated')
    header_at, header_size, ids_at, flags = struct.unpack_from('>4I', data)
    size = flags & 0x0FFFFFFF
    if (header_at != 16 or header_size != 0x4C or ids_at != 0x60
            or flags >> 28 != 8 or size % 2 or ids_at + size > len(data)
            or len(data) != ((ids_at + size + 7) & ~7)
            or any(data[header_at + header_size:ids_at]) or any(data[ids_at + size:])):
        raise ValueError('unsupported scene event directory layout')
    count = data[header_at + 0x12]
    if size != count * 2 or not count:
        raise ValueError('scene event count and child extent disagree')
    ids = list(struct.unpack_from(f'>{count}H', data, ids_at))
    if len(set(ids)) != len(ids):
        raise ValueError('duplicate scene event ID')
    return {'declared_event_count': count, 'event_ids': ids,
            'count_offset': header_at + 0x12, 'event_ids_span': [ids_at, ids_at + size],
            'runtime_admission': 'unobserved; loader checks and event-state gates still apply'}


def _asset(rom, bank, index):
    if bank.flags:
        raise ValueError('unsupported event asset bank flags')
    entries = [e for e in models.parse_asset_entries(rom, bank) if e.index == index]
    if len(entries) != 1:
        raise ValueError('missing or ambiguous event asset')
    entry = entries[0]
    if entry.type_flags & ~0x90:
        raise ValueError('unsupported event asset flags')
    raw = rom[entry.start:entry.end]
    data = models.decode_rzip_chunk(raw).data if entry.compressed else raw
    return {'asset_path': [bank.index, index],
            'rom_span': [f'0x{x:X}' for x in (entry.start, entry.end)],
            'sha256': hashlib.sha256(data).hexdigest(), 'decoded_bytes': len(data)}, data


CODE_SPANS = (
    (0x15002FB4, 344, '48becdd7d1ee88afcc3bacc66aba4c9ba0327a26'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1509B4A0, 208, 'cd7bc53cf5b4920ed87dff50e7faab869beb3b23'),
    (0x1509B5AC, 344, '353994e75aa927a4fca90b70a49a9259e93d82b6'),
    (0x1509B8FC, 84, '18aa64802ca1109f550c0b3633fdcde96abf2701'),
    (0x1509B950, 180, 'a559ee26892541d56ce86e7adf1d05ff06d4a35f'),
    (0x1509BBA0, 672, '3e1ffc39c4d0762c45e8c0d2ce353dbf5864308b'),
    (0x1509CBD4, 192, '720f2b1fcb3b64dd89609677384360a4355322d7'),
    (0x150ADAF0, 1936, '71289db6b6c195a4238ed75271181abe79c461da'),
    (0x1509C440, 904, '660784476ae5c24758397af140fe5e4b919ca60e'),
)


DATA_SPANS = (
    (0x80087358, 31, '39f4b147a831055ab80290232833a9b15c826df1'),
    (0x800885C0, 228, '2009b3580aac1fd5f509db7cbaeccd0530167eca'),
    (0x800886A4, 56, '2cce018eb4949260a4d75b0e8d7be4e559367f1a'),
    (0x800884D4, 60, '0a12472ea6ec5914bfd74deb4b75e5a513c55d70'),
    (0x8009E440, 24, 'e47969a094ce84c4548add5826e05d4bb5407293'),
)


# Scene30 is a separately bounded native-create audit. It never changes the
# scene60 script-request classifier or admits a model appearance.
SCENE30_PROGRAM_SHA256='947236f9d506dd1dd43e6345d831a4d46ad41475b74be0e46e3da341e63950e7'
SCENE30_CASES=((2,20,0x5C8,0x5DC,6),(3,21,0x61C,0x630,7),
            (5,22,0x6F8,0x70C,8),(10,23,0x98C,0x9A0,9),
            (11,24,0x9E0,0x9F4,10),(12,25,0xA34,0xA48,11))
SCENE30_CODE_SPANS=(
 (0x150AE0F8,156,'975470960e4fa55d46e350b58276333ddaed1908'),
 (0x15097910,188,'8ee6883546fe677fd01ceba87df56302a0424626'),
 (0x15099C14,6284,'e4b98dca758717c7329f9015a34fecf99560489d'),
 (0x150A2AEC,440,'dc6b10f3edd8124557bdffca430ab6e6bdd0e4c0'),
 (0x15083E90,288,'9056d859958dee82b4b70863bd102612d9a0b49c'),
 (0x1505EEF4,220,'1103976ffa718b02f3bddfa0bf52f9bc6d953a34'),
 (0x150A1DA0,1604,'9b34b9a88009fa729779740826f139eb017876a7'),
)
SCENE30_DATA_SPANS=(
 (0x80088420,60,'78ad5cea787d5c2b3c5aa11c54631a3c63f0206f'),
 (0x80088498,60,'056ba4645ea735c490e7cc69ae5d0bd58eda59ae'),
 (0x8009E1B4,396,'53396826b9727e526c39060565fe44556d8315f2'),
)


def scene30_program_requests(data):
    if len(data)!=3390 or hashlib.sha256(data).hexdigest()!=SCENE30_PROGRAM_SHA256:
        raise ValueError('scene30 event144 source changed')
    program=decode_program(data);calls=call_packets(program,data,30)
    if program['instruction_count']!=709:raise ValueError('scene30 event instruction count changed')
    rows={r['offset']:r for r in program['instructions']};packets={c['offset']:c for c in calls}
    def operands(row):return [(a['mode'],a['value']) for a in row['operands']]
    if (rows[0x138]['opcode']!=27 or rows[0x144]['opcode']!=25
            or operands(rows[0x144])!=[(3,0x430)] or rows[0x430]['opcode']!=27
            or rows[0x434].get('target')!=0xC50):
        raise ValueError('scene30 update/controller flow changed')
    phase_branches={}
    for at,row in rows.items():
        if 0xC50<=at<0xD30 and row['opcode']==22:
            ops=operands(row);branch=rows.get(row['end'])
            if len(ops)!=3 or ops[0][0]!=0 or ops[1]!=(1,0x2C) or ops[2][0]!=4 or not branch or branch['opcode']!=17 or operands(branch)[0]!=ops[0]:
                raise ValueError('scene30 phase branch changed')
            phase_branches[ops[2][1]]=branch['target']
    candidates=[c for c in calls if c['dispatch']=='native' and c['target']==3
                and c.get('literal_arguments') in ([0x2000+i] for i in range(6,12))]
    if len(candidates)!=6:raise ValueError('scene30 model66 packet count changed')
    requests=[]
    for phase,region,query_at,create_at,selector in SCENE30_CASES:
        query,create=packets.get(query_at,{}),packets.get(create_at,{})
        if (query.get('dispatch')!='native' or query.get('target')!=5
                or not query.get('packet_complete') or query.get('syntactic_argument_count')!=3
                or query.get('literal_arguments')!=[0x2000,172,0x4000+region]
                or create.get('dispatch')!='native' or create.get('target')!=3
                or not create.get('packet_complete') or create.get('syntactic_argument_count')!=1
                or create.get('literal_arguments')!=[0x2000+selector]
                or phase_branches.get(phase)!=query['packet_span'][0]):
            raise ValueError('scene30 conditional model66 packet changed')
        copy_row=rows[rows[query_at]['end']];gate=rows[copy_row['end']]
        if (copy_row['opcode']!=14 or operands(copy_row)[1]!=(5,0)
                or gate['opcode']!=16 or operands(gate)[0]!=operands(copy_row)[0]
                or gate['end']!=create['packet_span'][0] or gate['target']<=rows[create_at]['end']):
            raise ValueError('scene30 query-result gate changed')
        requests.append({'event_asset_path':[0x14,144],'phase_state_offset':0x2C,'phase':phase,
            'region':region,'query_call_offset':query_at,'query_arguments':query['literal_arguments'],
            'query_packet_sha256':query['packet_sha256'],'query_zero_branch_target':gate['target'],
            'create_call_offset':create_at,'create_packet_sha256':create['packet_sha256'],
            'native_index':3,'selector_class':2,'selector':selector,'model':[1,66,0],
            'condition':'If this controller executes in the stated phase and native5 region-membership query returns nonzero',
            'constructor':'func_15097910','existing_actor_path':'func_15083E90',
            'new_actor_gate_clear_pc':'0x1509796C','new_actor_create_call_pc':'0x15097980',
            'new_actor_constructor':'func_15082A44'})
    return program,calls,requests


def scene30_spawn_records(prefix,scene_data):
    from scripts.model_character_alpha import spawn_records
    if (len(prefix)!=240 or hashlib.sha256(prefix).hexdigest()!='c00f174e84c2718bda836eab7ed50ccb5598f766207758e0a105f9a00c3433be'
            or len(scene_data)!=1344 or hashlib.sha256(scene_data).hexdigest()!='ab38baf18478d0b573d253cbf4995601b8cd056cce8f47aa0da83635ef647eac'):
        raise ValueError('scene30 combined spawn source changed')
    all_records=spawn_records(prefix+scene_data,set(range(256)));result=[]
    for selector,index in zip(range(6,12),range(5,11)):
        found=[r for r in all_records if r['script_selector']==selector]
        if len(found)!=1 or found[0]['record_index']!=index or found[0]['model']!=[1,66,0] or found[0]['spawn_gate_byte']!=1:
            raise ValueError('scene30 selector is not a unique gated model66 spawn')
        result.append(found[0])
    return result


# Every program admitted by report is pinned independently of the ROM digest.
PROGRAM_SOURCES = {
    144: (3390, 709, '0x13176A8', '0x1317B71', SCENE30_PROGRAM_SHA256),
    169: (410, 93, '0x131C658', '0x131C738', '0ceeb45c81aa3b0a4cfd856b61af8c741ee2d7d8c405464b2f09c66d027c0f69'),
    170: (2280, 455, '0x131C738', '0x131CBA7', '9f0caa676ea0bb220bacc3bc8cc11366040b8e627c682d2f43180d4e90979671'),
    171: (5316, 986, '0x131CBA8', '0x131D53A', '7fd8791f1eeed6b78b83388a6fb8d54acbdf1c1c09a80b0e24026bb54e55d5c3'),
    172: (1530, 251, '0x131D540', '0x131D8B2', 'c37a120504c93161b3dd7edcf021db7f6b1379d69d41535f09ca9590e7afdc7c'),
    173: (1660, 344, '0x131D8B8', '0x131DBD7', 'dd7045e208ffaeeb27d08119242dd83633116c2bd38dafdb9dc49e1024dcd7be'),
}
SCENE_SOURCES = {
    30: ('0x132F4F0', '0x132F558', '09a8127b823dd42cae4594153d1c2edc5c1f5660a6b68942e0347b40afba0917', [144]),
    60: ('0x1330130', '0x13301A0', '5eb724f0d783a4a6082dbbe017784bb7541dcd19867d4ab66338df72f13e52fe', [169, 170, 171, 172, 173]),
}
SCENE60_REQUESTS = ((169, 0xC6, 1), (170, 0x60C, 8), (170, 0x7B0, 10),
                    (170, 0x7CE, 11), (170, 0x88E, 12), (171, 0x76C, 15),
                    (171, 0x7FC, 16), (171, 0x89C, 13))
SCOPE = ('Static, state-conditional event requests only. No observed event execution, '
         'natural activation, submitted draw, visibility, material, opacity or appearance admission.')


def scene60_script_requests(programs: list[dict]) -> list[dict]:
    requests = []
    for program in programs:
        for call in program['calls']:
            args = call['literal_arguments']
            if (call['dispatch'] != 'native' or call['target'] != 6 or not args
                    or args[0] & 0xF000 != 0x1000 or len(args) < 2 or args[1] != 1):
                continue
            if not call['packet_complete'] or call['syntactic_argument_count'] != 2 or len(args) != 2:
                raise ValueError('scene60 script request has unsupported packet or scene override')
            requests.append({'event_asset_path': program['asset_path'],
                             'call_offset': call['offset'], 'native_index': 6,
                             'selector_class': 1, 'operation': 1,
                             'script_asset_path': [6, 60, args[0] & 0xFFF],
                             'packet_span': call['packet_span'],
                             'packet_sha256': call['packet_sha256'],
                             'consumer': 'func_1509C440', 'activation_entry': 'func_1501D348',
                             'activation_call_pc': '0x1509C520',
                             'condition': 'If this packet executes, the current scene is 60, slot 0 is idle, and downstream script-loader gates admit it'})
    actual = tuple((r['event_asset_path'][1], r['call_offset'], r['script_asset_path'][2]) for r in requests)
    if actual != SCENE60_REQUESTS:
        raise ValueError('scene60 conditional literal script request set changed')
    return requests


def report(rom: bytes, layout: dict, game, scene: int) -> dict:
    from scripts.model_character_alpha import CALLER_SPANS, CALLER_TABLES, scene_scripts
    if scene not in SCENE_SOURCES:
        raise ValueError('event-activation is bounded to reviewed scenes30 and60')
    if hashlib.sha1(rom).hexdigest() != US_SHA1:
        raise ValueError('event-activation requires the reviewed normalized US ROM')
    guards = checked_spans(game.code, layout['game_vram'], CODE_SPANS + SCENE30_CODE_SPANS + CALLER_SPANS)
    tables = checked_spans(game.data, layout['game_data_vram'], DATA_SPANS + SCENE30_DATA_SPANS + CALLER_TABLES)
    banks = {b.index: b for b in models.parse_asset_banks(rom, layout['asset_table'])}
    source, payload = _asset(rom, banks[0x15], scene)
    start, end, digest, ids = SCENE_SOURCES[scene]
    if source['rom_span'] != [start, end] or source['sha256'] != digest:
        raise ValueError('scene event list source changed')
    listing = {**source, **scene_event_list(payload)}
    if listing['event_ids'] != ids:
        raise ValueError('scene declared event set changed')
    programs = []
    spawns = []
    for event in ids:
        asset, data = _asset(rom, banks[0x14], event)
        length, count, start, end, digest = PROGRAM_SOURCES[event]
        if asset['rom_span'] != [start, end] or len(data) != length or asset['sha256'] != digest:
            raise ValueError('event program source changed')
        if scene == 30:
            program, calls, spawns = scene30_program_requests(data)
        else:
            program = decode_program(data)
            calls = call_packets(program, data, scene)
        if program['instruction_count'] != count:
            raise ValueError('event instruction count changed')
        programs.append({**asset, **program, 'calls': calls})
    spawn_source, spawn_data = _asset(rom, banks[0x0E], scene)
    prefix = rom[0x1A33F0:0x1A34E0]
    branch = struct.unpack_from('>I', game.data, 0x80096760 - layout['game_data_vram'] + (scene - 26) * 4)[0]
    if branch != 0x150169F8 or hashlib.sha256(prefix).hexdigest() != 'c00f174e84c2718bda836eab7ed50ccb5598f766207758e0a105f9a00c3433be':
        raise ValueError('scene spawn prefix selection changed')
    result = {'schema_version': 1, 'family': 'model-event-activation', 'scene': scene,
              'evidence_source': 'Checksum-validated US ROM bytecode, scene tables and complete consumer spans.',
              'normalized_sha1': US_SHA1, 'consumer_spans': guards, 'table_spans': tables,
              'scene_event_list': listing, 'programs': programs, 'scope': SCOPE,
              'conditional_script_requests': [], 'conditional_spawn_requests': spawns,
              'spawn_source': spawn_source,
              'prefix_source': {'rom_span': ['0x1A33F0', '0x1A34E0'],
                                'sha256': hashlib.sha256(prefix).hexdigest()},
              'unresolved': ['Event admission flags and execution paths are not evaluated or observed.',
                             'A request does not establish a new actor, submitted draw, appearance or gameplay route.']}
    if scene == 30:
        records = scene30_spawn_records(prefix, spawn_data)
        for request, spawn in zip(spawns, records):
            request['spawn_record'] = spawn
        result['unresolved'] += ['Controller phase and region membership remain unobserved.',
                                 'Existing actor resolution can take the existing-actor reuse path.',
                                 'Model66 visibility, colour state and native framebuffer reproduction remain unresolved.']
    else:
        if len(spawn_data) != 3216 or spawn_source['sha256'] != '7193517876bc28cd2dbfdad7b4c71d4087d9f2dfd739f9714d840c24896b394c':
            raise ValueError('scene60 spawn source changed')
        routes = scene_scripts(rom, layout, scene, prefix + spawn_data, {154, 155, 162})
        requests = scene60_script_requests(programs)
        by_id = {s['asset_path'][2]: s for s in routes['scripts']}
        for request in requests:
            script = by_id.get(request['script_asset_path'][2])
            if script is None:
                raise ValueError('scene60 literal request has no script asset')
            request['initial_model_matches'] = script['matches']
        result['conditional_script_requests'] = requests
        result['scene_script_routes'] = routes
        result['unresolved'] += ['Static initial-track links cover only models154/155/162; later tracks, dynamic selectors and other activation routes are outside this report.']
    return result


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--scene', type=int, choices=(30, 60), default=60)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args(argv)
    try:
        path, layout = models.resolve_rom('us', args.rom)
        rom, _ = models.normalize_rom(path.read_bytes())
        if hashlib.sha1(rom).hexdigest() != US_SHA1:
            raise ValueError('event-activation requires the reviewed normalized US ROM')
        game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
        result = report(rom, layout, game, args.scene)
        output = args.output or ROOT / f'build/assets/models/event-activation-scene{args.scene}.json'
        output.parent.mkdir(parents=True, exist_ok=True)
        temporary = output.with_suffix(output.suffix + '.tmp')
        temporary.write_text(json.dumps(result, indent=2) + '\n')
        temporary.replace(output)
    except (OSError, ValueError) as exc:
        parser.error(str(exc))
    print(f"Decoded {len(result['programs'])} scene-{args.scene} event programs; "
          f"{len(result['conditional_spawn_requests']) + len(result['conditional_script_requests'])} conditional literal requests")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
