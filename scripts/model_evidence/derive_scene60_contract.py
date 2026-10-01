"""Derive metadata from authenticated local capture inputs and the US ROM.

No capture, emulator replay, model export, or native framebuffer claim.
"""
import argparse
from dataclasses import asdict
import hashlib
import json
from pathlib import Path
import struct

from .common import encoded, source_reader, validate_event_hashes, validate_paths, write_new

PACKET_SHA256 = '0bebc53e7ac41acd51c849b891b869d3b784f4d402a8ac27909ff5551a6a887f'
INPUTS = {'packet': {'bytes': 11679,
            'sha256': '0bebc53e7ac41acd51c849b891b869d3b784f4d402a8ac27909ff5551a6a887f'},
 'material_proof': {'bytes': 291429,
                    'sha256': '27726010630fbf5e588a64f9c04c8b7768303be7c36cf6cb269f262f952abc34'},
 'save_state': {'bytes': 1976101,
                'sha256': 'c6c7d6006f2adcfefd9931796a977463b478c4ab454fcc87e139606147a81642'},
 'screenshot': {'bytes': 301210,
                'sha256': 'dd821fce4ba9029c9ae1fa0cf1ae60fe62f79ac40323293d6e12cbe0ece9a48c'},
 'trace': {'bytes': 33179747,
           'sha256': '877b32beb7d22dea28c59daac1bab003c8e625a6923e860d8e9daa5472c54008'},
 'save_metadata': {'bytes': 533,
                   'sha256': '8bb4e503b64528b61221618a995d62bfcefcbb7315a262fc63c7b91576eb9ca4'}}
PRESET = 'scene60-captured-primary-opacity255'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def check(condition, message):
    if not condition:
        raise ValueError(message)


def derive(rom_path, inputs):
    from scripts import model_assets as models, model_scene60_appearance as scene
    read, provenance = source_reader(inputs, INPUTS)
    packet_bytes = read('packet')
    check(sha(packet_bytes) == PACKET_SHA256, 'scene60 packet changed')
    packet = json.loads(packet_bytes)
    proof_bytes = read('material_proof')
    check(sha(proof_bytes) == packet['proof_sha256'], 'packet proof identity changed')
    proof = json.loads(proof_bytes)
    for filename, key in (('save_state', 'state_sha256'), ('screenshot', 'screenshot_sha256'), ('trace', 'trace_sha256')):
        data = read(filename)
        check(sha(data) == packet[key], 'packet identity changed: ' + key)
        if filename == 'trace':
            trace = [json.loads(line) for line in data.splitlines()]
    read('save_metadata')
    session = trace[0]
    events = [item for item in trace if item.get('record_type') == 'draw_state']
    validate_event_hashes(events)
    check(session['normalized_sha1'] == packet['rom_sha1'], 'trace ROM identity changed')
    check(proof['trace_sha256'] == packet['trace_sha256'], 'proof trace identity changed')
    check(events[packet['task']['event']]['render_state_hash'] == packet['task']['state_hash'], 'task state hash changed')
    check(proof['task_event'] == packet['task']['event'] and proof['task_state_hash'] == packet['task']['state_hash'] and proof['task_probes'] == packet['task']['probes'], 'task proof changed')

    rom_path, layout = models.resolve_rom('us', rom_path)
    rom, _ = models.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    check(digest == packet['rom_sha1'] and digest in layout['normalized_sha1'], 'ROM identity changed')
    bank = next(item for item in models.parse_asset_banks(rom, layout['asset_table']) if item.index == 1)
    entries = {item.index: item for item in models.parse_asset_entries(rom, bank)}
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    sizes = struct.unpack_from(f'>{models.RUNTIME_FLAT_ASSET_COUNT}H', game.data, models.RUNTIME_FLAT_SIZE_TABLE - layout['game_data_vram'])
    spans = {}
    cursor = layout['flat_assets_start']
    for index, size in enumerate(sizes):
        if str(index) in packet['textures']:
            spans[index] = (cursor, cursor + size)
        cursor += size

    state_ids = list(packet['states'])
    aliases = dict(zip(state_ids, ('A', 'B', 'C')))
    captured = {}
    first_state = packet['states'][state_ids[0]]
    common = {'convert_mode': [f'0x{word:08X}' for word in first_state['convert_mode']],
              'colours': first_state['colours'], 'K5': 255,
              **{key: packet['alpha'][key] for key in ('alpha_cvg_select', 'cvg_times_alpha', 'force_blend', 'alpha_compare')}}
    for state_id, state in packet['states'].items():
        check(sha(json.dumps(state, sort_keys=True).encode()) == state_id, 'captured state subset digest changed')
        check(state['convert_mode'] == first_state['convert_mode'] and state['colours'] == first_state['colours'], 'captured common state changed')
        captured[aliases[state_id]] = {'other_mode': [f'0x{x:08X}' for x in state['other_mode']],
                                      'combine_mode': [f'0x{x:08X}' for x in state['combine_mode']],
                                      'state_subset_sha256': state_id}
    evidence = {'schema_version': 1, 'preset': PRESET,
                'inspection_scope': scene.SCOPE,
                'scope': packet['scope'],
                'provenance': {'packet_sha256': PACKET_SHA256, 'sources': provenance,
                             'verification_scope': 'Source byte identities, retained packet/proof consistency, recorded trace event hashes, and independent ROM geometry/material/pixel checks. No local raw-trace command replay or native framebuffer validation.'},
                'identities': {key: packet[key] for key in ('rom_sha1', 'state_sha256', 'screenshot_sha256', 'trace_sha256', 'proof_sha256')},
                'task': packet['task'], 'models': {}, 'captured_states': captured, 'captured_state_common': common,
                'source_contracts': {}, 'textures': {}, 'texture_common': {'palette_sha256': sha(bytes(32))},
                'local_source_guards': {'origin': 'New ROM checks against the independently preserved full blocked-run contracts.', 'material_run_sha256': {}}}
    for flat, spec in packet['source_contracts'].items():
        state_id = next(key for key in state_ids if key.startswith(packet['state_map'][flat]))
        evidence['source_contracts'][flat] = {key: spec[key] for key in ('render_tile', 'tile_bounds', 'texture_scale', 'combine_mode', 'runtime_render_state_offset')}
        evidence['source_contracts'][flat].update(pixel_load=spec['pixel']['load_command'], captured_state=aliases[state_id])
    payloads = {}
    for flat, info in packet['textures'].items():
        start, end = spans[int(flat)]
        compressed = rom[start:end]
        data = models.decode_rzip_chunk(compressed).data
        check(len(data) == info['flat_bytes'] and sha(data) == info['flat_sha256'] and hashlib.sha1(data).hexdigest() == info['flat_sha1'], 'flat ROM identity changed')
        check(sha(data[:info['captured_pixel_bytes']]) == info['captured_pixel_sha256'], 'captured pixel prefix differs from ROM')
        payloads[int(flat)] = data
        evidence['textures'][flat] = {**info, 'compressed_rom_range': [f'0x{start:X}', f'0x{end:X}'], 'compressed_sha256': sha(compressed)}
    reports = {}
    for entry, context in packet['models'].items():
        expected = proof['entries'][entry]
        for key, value in context.items():
            if key not in ('runs', 'run_columns'):
                check(expected[key] == value, 'packet/proof model field differs: ' + entry + '/' + key)
        check(expected['caller'] == '0x1502CBD0', 'captured caller changed')
        check(events[context['entry_event']]['render_state_hash'] == context['entry_state_hash'] and events[context['return_event']]['render_state_hash'] == context['return_state_hash'], 'model event hash changed')
        part = context['selected_parts'][0]
        check(len(context['selected_parts']) == 1, 'unexpected selected parts')
        converted = {key: context[key] for key in ('source_sha1', 'source_bytes', 'whole_model_faces', 'selected_primary_faces', 'blocked_faces', 'runs')}
        converted.update(vertices=context['vertex_count'], joints=context['joint_count'], caller_arguments=context['arguments'],
                         selected_part={'table': part['table'], 'part': part['part_index'], 'display_model': part['display_model_index'],
                                        'secondary_model': part['secondary_model_index'], 'draw_mode': part['draw_mode'],
                                        'table_slot_address': part['part_table_slot_address'], 'display_list_address': part['selected_display_list'],
                                        'display_list_bytes': part['display_list_byte_count'], 'display_list_sha256': part['display_list_sha256']},
                         capture_events={key: context[key] for key in ('entry_event', 'return_event', 'entry_state_hash', 'return_state_hash', 'submission')})
        evidence['models'][entry] = converted
        asset = entries[int(entry)]
        raw = rom[asset.start:asset.end]
        if asset.compressed:
            raw = models.decode_rzip_chunk(raw).data
        geometry, _, _ = scene.checked_model(int(entry), raw, digest, evidence)
        guards = {}
        observed_runs = {row['run']: row for row in expected['blocked_runs']}
        for row in context['runs']:
            index, first, count, flat, matrix, first_command, last_command = row
            run = geometry.material_runs[index]
            observed = observed_runs[index]
            run_record = json.loads(json.dumps(asdict(run)))
            check(all(run_record[key] == value for key, value in observed['contract'].items()), 'ROM run differs from captured proof contract')
            check(list(geometry.face_command_offsets[first:first + count]) == observed['source_face_command_offsets'], 'source face offsets differ from proof')
            state_id = next(key for key in state_ids if key.startswith(packet['state_map'][str(flat)]))
            check(sum(item['faces'] for item in observed['observations']) == count and all(item['state_id'] == state_id for item in observed['observations']), 'proof run state/count differs')
            guards[str(index)] = scene.run_digest(run)
        check(sum(row[2] for row in context['runs']) == context['blocked_faces'], 'blocked face accounting changed')
        evidence['local_source_guards']['material_run_sha256'][entry] = guards
        for row in context['runs']:
            png, flat = scene.decode_image(geometry.material_runs[row[0]], row[0], geometry, int(entry), payloads, evidence)
            check(hashlib.sha1(png).hexdigest() == packet['textures'][str(flat)]['png_sha1'], 'decoded PNG differs')
        reports[entry] = {'source_faces': len(geometry.faces), 'blocked_faces': context['blocked_faces'], 'runs': len(guards), 'run_contracts_match_proof': True}
    return evidence, reports


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path, required=True)
    for role in INPUTS:
        parser.add_argument('--' + role.replace('_', '-'), type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args(argv)
    validate_paths(args, ('rom', *INPUTS), ('output',))
    evidence, report = derive(args.rom, {role: getattr(args, role) for role in INPUTS})
    raw = encoded(evidence)
    write_new(args.output, raw)
    print(json.dumps({'contract_sha256': sha(raw), 'verification': report}, sort_keys=True))


if __name__ == '__main__':
    main()
