"""Derive metadata from authenticated local capture inputs and the US ROM.

No capture, emulator replay, model export, or native framebuffer claim.
"""
import argparse
from dataclasses import asdict
import hashlib
import json
from pathlib import Path
import struct
from .library155_raw_closure import verify_raw_closure

from .common import encoded, source_reader, validate_event_hashes, validate_paths, write_new

INPUTS = {'packet': {'bytes': 125111,
            'sha256': 'c282311b2f49b955ad936f29dfa173a444609a510ba3ed58428c2ae15ab0c346'},
 'save_state': {'bytes': 2039172,
                'sha256': 'f24065bf126ee41943e0cb6d14879bd77ad55d28c1bbed567384ce6aa1072650'},
 'screenshot': {'bytes': 403929,
                'sha256': '2c269d93a9d82e0abc3990c1c8c63c46d5e268071c2d757a643047f6475957f3'},
 'save_metadata': {'bytes': 527,
                   'sha256': '2a1aef970419b8a8e11c94cf5a4f0078c912f5d2ee48d2b374f9e3267da532dd'},
 'material_proof': {'bytes': 2868895,
                    'sha256': '8764bb216095cd963f8d66d7742cc5ff93ab1334a44e03776191afe1ffba42eb'},
 'trace': {'bytes': 51128281,
           'sha256': '9978ebe2a61e38724fbb7df4a1c2cad9fa18a90b32f28da123676c1ab4647b89'},
 'scene_metadata': {'bytes': 2959,
                    'sha256': '972a6e7d52777756193968611206adb2a330c9f02c27c80bde0ce20185ca6283'},
 'topology': {'bytes': 1838398,
              'sha256': '2286b48cdadf7049f6dbebfe81df96f7e4658e0766919b33157a103ff886564c'}}
PACKET_SHA256 = 'c282311b2f49b955ad936f29dfa173a444609a510ba3ed58428c2ae15ab0c346'
PRESET = 'library-bat155-captured-primary-opacity255'
SCOPE = ('Scene60 Library bats 2 model155 captured primary normal part0, mode1, '
         'opacity255, secondary0, caller1502CBD0, actor35/slot13 only. Original '
         'zero-alpha PNGs retained. OPAQUE unlit pre-blender black inspection '
         'approximation; native fog, framebuffer blending, visibility and fractional '
         'edge coverage are not reproduced. Additive effective fog evidence is black '
         'RGBA(0,0,0,255), separate from the unchanged recorded material-state '
         'hashes. No native per-pixel framebuffer parity, captured-pose export, '
         'runtime-animation absence or universal default admission.')


def sha(data):
    return hashlib.sha256(data).hexdigest()


def check(condition, message):
    if not condition:
        raise ValueError(message)


def derive(rom_path, inputs):
    from scripts import model_assets as models, model_scene60_appearance as scene, texture_assets
    read, provenance = source_reader(inputs, INPUTS)
    packet_bytes = read('packet')
    check(sha(packet_bytes) == PACKET_SHA256, 'Library155 packet changed')
    packet = json.loads(packet_bytes)
    identity = packet['identity']
    for name, key in (('save_state', 'state_sha256'), ('screenshot', 'screenshot_sha256'),
                      ('save_metadata', 'plist_sha256'), ('material_proof', 'original_proof_sha256'),
                      ('trace', 'trace_sha256')):
        data = read(name)
        check(sha(data) == identity[key], 'packet identity mismatch: ' + key)
        if name == 'material_proof':
            proof = json.loads(data)
        if name == 'trace':
            trace = [json.loads(line) for line in data.splitlines()]
    stage = json.loads(read('scene_metadata'))
    check(stage['scene_id'] == 60 and any(record['slot'] == 13 and record['entry'] == 155 and record['id'] == 35 for record in stage['target_records']), 'saved actor context changed')
    session = trace[0]
    events = [item for item in trace if item.get('record_type') == 'draw_state']
    validate_event_hashes(events)
    check(session['normalized_sha1'] == identity['rom_sha1'] and proof['trace_sha256'] == identity['trace_sha256'], 'trace identity changed')
    check((proof['source_sha1'], proof['source_faces'], proof['blocked_faces']) == (identity['source_sha1'], 314, 186), 'proof source identity changed')
    paired_topology = json.loads(read('topology'))
    raw_closure = verify_raw_closure(events, packet, proof, paired_topology)
    states = {}
    run_states = {}
    tasks = []
    for task, draw in zip(packet['tasks'], proof['draws'], strict=True):
        check((task['entry'], task['return'], task['task']) == (draw['entry_event'], draw['return_event'], draw['task_event']), 'task indexing differs')
        check(task['state_hashes'] == [events[index]['render_state_hash'] for index in (task['entry'], task['return'], task['task'])], 'task recorded state hashes differ')
        check(draw['caller'] == '0x1502CBD0' and draw['arguments'] == [255,2147686152,1,0], 'captured caller/arguments changed')
        check(task['submission'] == draw['submission'] and task['submission']['triangle_count'] == 314 and not task['submission']['matrices_changed_after_return'], 'submission differs')
        check(sum(row['faces'] for row in draw['rows']) == 186, 'captured blocked coverage differs')
        for row in draw['rows']:
            captured = events[task['task']]['state']['rdp']['draw_runs'][row['draw_index']]
            check(row['state'] == captured['state'], 'proof material state differs from raw trace')
            numeric = {key: row['state'][key] for key in ('other_mode', 'combine_mode', 'convert_mode', 'colours')}
            state_id = sha(json.dumps(numeric, sort_keys=True).encode())
            states[state_id] = numeric
            run_states.setdefault(row['run'], set()).add(state_id)
        check(task['all_target_fog_identical'] and task['effective_fog']['words'] == [0xF8000000, 255] and len(task['effective_fog']['origin']) == 1, 'additive fog evidence changed')
        part = task['parts'][0]
        check(len(task['parts']) == 1 and (part['table'], part['display_model_index'], part['secondary_model_index'], part['draw_mode'], part['part_index']) == ('normal',155,0,1,0), 'primary part changed')
        tasks.append({'events': [task['entry'], part['event_index'], task['return'], task['task']],
                      'event_columns': ['entry','part','return','submit'], 'state_sha256': task['state_hashes'],
                      'probes': task['probes'], 'submission': task['submission'], 'triangles': 314,
                      'execution_count': 1,
                      'matrix_evidence': raw_closure[len(tasks)],
                      'recorded_matrix_report': task['submission']['matrices_changed_after_return'],
                      'effective_fog': {'words': ['F8000000', '000000FF'], 'rgba': [0,0,0,255],
                                        'flattened_byte_offset': task['effective_fog']['offset'],
                                        'origin': task['effective_fog']['origin'][0],
                                        'applies_to': 'Every blocked triangle according to the pinned additive analysis; last preceding F8, no unresolved targets',
                                        'flattened_offset_independently_recomputed': False}})
    state_a = '8421a7e9037b90fb81f00b1a04c958d65ccd873cf8c5115bd127ff088be06e34'
    state_b = '6d27162ffa5036aa3ddee7609a127fc9753db90589b02670231bddb5710d6f91'
    check(set(states) == {state_a, state_b}, 'Library155 captured material subset changed')
    for row in packet['runs']:
        check(run_states[row[0]] == {state_a if row[3] == 903 else state_b}, 'Library155 per-run captured state differs')
    common = states[state_a]
    check(common['convert_mode'] == [0xEC000000,255] and states[state_b]['convert_mode'] == common['convert_mode'] and states[state_b]['colours'] == common['colours'], 'common conversion/colour state differs')
    evidence = {'schema_version': 1, 'preset': PRESET, 'scope': SCOPE, 'inspection_scope': SCOPE,
                'provenance': {'packet_sha256': PACKET_SHA256, 'sources': provenance,
                             'verification_scope': 'Pinned source byte identities, raw-trace material row equality and recorded event hashes, independently checked ROM source/load histories and all seven image levels. Raw task headers, renderer range bytes, fog words and 35 transforms per task independently checked. Float-to-fixed matrix components agree within native quantization; memory bytes change. Effective last-preceding fog coverage/flattened offsets remain separately recorded analysis; no local command replay, new capture or native framebuffer validation.'},
                'identities': {key: identity[key] for key in ('rom_sha1', 'state_sha256', 'screenshot_sha256', 'plist_sha256', 'original_proof_sha256', 'trace_sha256', 'source_sha1', 'source_sha256', 'source_bytes')},
                'task': {'event_indexing': 'Zero-based draw_state events excluding session', 'scene':60, 'actor':35, 'slot':13,
                         'caller':'1502CBD0', 'submissions':tasks},
                'captured_states': {alias: {'other_mode': [f'{word:08X}' for word in states[key]['other_mode']],
                                          'combine_mode': [f'{word:08X}' for word in states[key]['combine_mode']],
                                          'state_subset_sha256': key} for alias,key in (('A',state_a),('B',state_b))},
                'captured_state_common': {'convert_mode': [f'{word:08X}' for word in common['convert_mode']],
                                         'colours':common['colours'], 'K5':255, 'alpha_cvg_select':True,
                                         'cvg_times_alpha':False, 'force_blend':False, 'alpha_compare':0},
                'models': {}, 'source_contracts': {}, 'textures': {}, 'texture_common': {'palette_sha256':sha(bytes(32))},
                'local_source_guards': {'origin':'Full canonical ROM states checked against exact integration-packet contracts.', 'material_run_sha256': {'155':{}}},
                'material_contracts': packet['contracts']}
    part = packet['tasks'][0]['parts'][0]
    evidence['models']['155'] = {'source_sha1':identity['source_sha1'], 'source_sha256':identity['source_sha256'],
                                'source_bytes':identity['source_bytes'], 'vertices':335, 'joints':36,
                                'whole_model_faces':314, 'selected_primary_faces':314, 'blocked_faces':186,
                                'caller_arguments':[255,2147686152,1,0], 'runs':[row[:7] for row in packet['runs']],
                                'stored_clips':0, 'runtime_animation_absence_proven':False,
                                'source_dl_sha256':packet['geometry']['display_list_sha256'],
                                'source_vertex_sha256':packet['geometry']['vertex_block_sha256'],
                                'selected_part':{'table':'normal','part':0,'display_model':155,'secondary_model':0,'draw_mode':1,
                                                 'table_slot_address':part['part_table_slot_address'], 'display_list_address':part['selected_display_list'],
                                                 'display_list_bytes':part['display_list_byte_count'], 'display_list_sha256':part['display_list_sha256']}}
    rom_path, layout = models.resolve_rom('us', rom_path)
    rom, _ = models.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    check(digest == identity['rom_sha1'] and digest in layout['normalized_sha1'], 'ROM identity differs')
    banks = {bank.index:bank for bank in models.parse_asset_banks(rom, layout['asset_table'])}
    asset = next(item for item in models.parse_asset_entries(rom,banks[1]) if item.index == 155)
    raw = rom[asset.start:asset.end]
    if asset.compressed: raw = models.decode_rzip_chunk(raw).data
    check(sha(raw) == identity['source_sha256'], 'model SHA256 differs')
    geometry, _, _ = scene.checked_model(155,raw,digest,evidence)
    check(sha(raw[0x38:0x38+335*16]) == packet['geometry']['vertex_block_sha256'], 'vertex source span differs')
    check(sha(raw[geometry.display_list_offset:geometry.display_list_offset+geometry.display_list_size]) == packet['geometry']['display_list_sha256'], 'display-list source span differs')
    check(155 not in {entry.index for entry in models.parse_asset_entries(rom,banks[2])}, 'entry155 acquired stored animation companion')
    for row in packet['runs']:
        index, first, count, flat, matrix, first_command, last_command, observations, contract_hash = row
        run = geometry.material_runs[index]
        check(json.loads(json.dumps(asdict(run))) == packet['contracts'][str(index)], 'full ROM material history differs')
        check(scene.run_digest(run) == contract_hash, 'canonical material digest differs')
        check((run.first_face,run.face_count,run.matrix_index) == (first,count,matrix) and geometry.face_command_offsets[first] == first_command and geometry.face_command_offsets[first+count-1] == last_command, 'source face coverage differs')
        evidence['local_source_guards']['material_run_sha256']['155'][str(index)] = contract_hash
        spec = {key:json.loads(json.dumps(getattr(run,key))) for key in ('render_tile','tile_bounds','texture_scale','combine_mode','runtime_render_state_offset')}
        spec.update(pixel_load=list(run.pixel.load_command),captured_state='A' if flat == 903 else 'B')
        if str(flat) in evidence['source_contracts']:
            check(evidence['source_contracts'][str(flat)] == spec, 'effective per-flat contracts disagree')
        evidence['source_contracts'][str(flat)] = spec
    check(evidence['source_contracts']['926']['runtime_render_state_offset'] == 64, 'flat926 reused scene60 offset112')
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    sizes = struct.unpack_from(f'>{models.RUNTIME_FLAT_ASSET_COUNT}H',game.data,models.RUNTIME_FLAT_SIZE_TABLE-layout['game_data_vram'])
    cursor = layout['flat_assets_start']; payloads = {}; levels_verified = texels = 0
    for index,size in enumerate(sizes):
        start,end = cursor,cursor+size;cursor=end
        if str(index) not in packet['textures']: continue
        info = packet['textures'][str(index)]; compressed=rom[start:end];data=models.decode_rzip_chunk(compressed).data
        check(len(data) == info['flat_bytes'] and sha(data) == info['flat_sha256'] and hashlib.sha1(data).hexdigest() == info['flat_sha1'], 'flat source differs')
        check(sha(data[:info['captured_pixel_bytes']]) == info['captured_pixel_sha256'], 'captured pixels differ')
        palette=data[info['palette_offset']:]
        check(palette == bytes(32) and sha(palette) == info['palette_sha256'], 'original palette differs')
        payloads[index] = data
        for level in info['levels']:
            width,height=level['width'],level['height'];offset=level['source_byte_offset'];stride=max(8,width//2)
            check(offset+stride*height <= info['captured_pixel_bytes'], 'mip level exceeds captured load')
            pixels=bytes(data[offset+y*stride+(x^(4 if y&1 else 0))] for y in range(height) for x in range(width//2))
            png=models.encode_indexed_png(pixels+palette,'linear',width,height)
            rgba=texture_assets.indexed_payload_rgba(pixels+palette,4,'linear',width,height)
            check(hashlib.sha1(png).hexdigest() == level['png_sha1'] and sha(rgba) == level['rgba_sha256'] and rgba == bytes(width*height*4), 'mip PNG/RGBA differs')
            levels_verified+=1;texels+=width*height
        evidence['textures'][str(index)]={**info,'compressed_rom_range':[f'0x{start:X}',f'0x{end:X}'],'compressed_sha256':sha(compressed)}
    for row in evidence['models']['155']['runs']:
        scene.decode_image(geometry.material_runs[row[0]],row[0],geometry,155,payloads,evidence)
    check((levels_verified,texels) == (7,5456), 'mip closure changed')
    return evidence, {'faces':314,'vertices':335,'joints':36,'blocked_faces':186,'runs':11,
                      'full_source_load_records':sum(len(run['texture_loads']) for run in packet['contracts'].values()),
                      'render_tile_records':sum(len(run['render_tiles']) for run in packet['contracts'].values()),
                      'verified_image_levels':levels_verified,'verified_texels':texels,'stored_clips':0}


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
