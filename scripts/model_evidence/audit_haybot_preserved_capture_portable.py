"""Re-audit exact local Haybot capture inputs into a path-free metadata report.

The reviewed manifest digest must be supplied explicitly. This report does not
replace the independently pinned capture audit required by derive_haybot_contract.
No emulator execution, command-stream replay, or framebuffer proof is performed.
"""
import argparse
import base64
import collections
import gzip
import hashlib
import json
from pathlib import Path
import struct

from .common import encoded, validate_paths, write_new

PACKET_SHA256 = "254846215d32ece3913f2adcb8bef94909f1492fbc95b0d70e11d16f0c16615d"
TRACE_SHA256 = "cceab5ea38d772293946612d3958d2621a3036b841d0185546e4d9fa78e3ab1e"
INPUT_ROLES = ("packet", "quick_result", "topology", "selector_binding", "source_binding",
               "scene_metadata", "save_state", "trace")


def sha(data):
    return hashlib.sha256(data).hexdigest()


def require(condition, label):
    if not condition:
        raise ValueError(label)


def audit(inputs, manifest_path, manifest_sha256):
    """Only the reviewed manifest digest establishes the input trust boundary."""
    require(len(manifest_sha256) == 64 and all(c in "0123456789abcdef" for c in manifest_sha256),
            "manifest digest must be a lowercase SHA256")
    manifest_bytes = manifest_path.read_bytes()
    require(sha(manifest_bytes) == manifest_sha256, "reviewed input manifest changed")
    manifest = json.loads(manifest_bytes)
    records = {(v["bytes"], v["sha256"]) for v in manifest["files"]}
    used = []

    def read(role):
        raw = inputs[role].read_bytes()
        digest = sha(raw)
        require((len(raw), digest) in records, "Input absent from reviewed manifest: " + role)
        if role in ("packet", "trace"):
            require(digest == {"packet": PACKET_SHA256, "trace": TRACE_SHA256}[role],
                    "Pinned capture input changed: " + role)
        used.append({"role": role, "bytes": len(raw), "sha256": digest, "matches_manifest": True})
        return raw

    def read_json(relative):
        return json.loads(read(relative))

    packet = read_json('packet')
    quick = read_json('quick_result')
    paired = read_json('topology')
    binding = read_json('selector_binding')
    source_binding = read_json('source_binding')
    stage = read_json('scene_metadata')
    state_raw = read('save_state')
    trace_raw = read('trace')
    trace = [json.loads(line) for line in trace_raw.splitlines()]
    header, events = trace[0], trace[1:]
    require(len(events) == 54 == quick['events'] == packet['context']['trace_events'], 'Event count mismatch')
    require(sha(trace_raw) == packet['identity']['trace_sha256'] == quick['trace_sha256'] == paired['sha256'], 'Trace identity disagreement')
    require(header['normalized_sha1'] == packet['identity']['rom_sha1'] == source_binding['rom_normalized_sha1'], 'Recorded ROM identities disagree')
    require(sha(state_raw) == packet['identity']['state_sha256'] == stage['files']['State']['sha256'], 'State identity disagreement')

    blocks, block_count = [], 0
    for event in events:
        require(sha(json.dumps(event['state'], sort_keys=True, separators=(',', ':')).encode()) == event['render_state_hash'], 'Canonical event state hash mismatch')
        local = {}
        for item in event['evidence']['memory']:
            raw = base64.b64decode(item['data_base64'], validate=True)
            require(len(raw) == item['length'] and sha(raw) == item['sha256'], 'Captured memory block integrity mismatch')
            require(item['name'] not in local, 'Duplicate captured block name')
            local[item['name']] = (int(item['resolved_address'], 16), raw, item)
            block_count += 1
        blocks.append(local)

    actor_samples = []
    for index, local in enumerate(blocks):
        if 'character-pool' not in local:
            continue
        address, raw, _ = local['character-pool']
        model = events[index]['state']['model']
        offset = 7 * model['record_size']
        actor = raw[offset:offset + model['record_size']]
        require(address + offset == 0x800CD904 and len(actor) == 812, 'Actor location changed')
        require((actor[4], actor[0x68], actor[0x69]) == (75, 15, 5), 'Actor identity or selector changed')
        actor_samples.append({'event': index, 'address': hex(address + offset), 'entry': actor[4], 'selector': actor[0x68], 'phase': actor[0x69], 'record_sha256': sha(actor)})
    require(len(actor_samples) == 14, 'Actor sample count changed')
    expected_samples = {v['hit']: v for v in binding['actor_pool_samples']}
    require(all(v['record_sha256'] == expected_samples[v['event']]['actor_record_sha256'] for v in actor_samples), 'Actor analysis disagreement')

    saved = gzip.decompress(state_raw)
    require(sha(saved) == binding['inputs']['State']['decompressed_sha256'], 'Decompressed State identity mismatch')

    def guest(address, size):
        offset = 0x1BC + (address & 0x7FFFFF)
        first, end = offset - offset % 4, (offset + size + 3) // 4 * 4
        require(end <= len(saved), 'State read outside saved memory')
        data = b''.join(saved[i:i + 4][::-1] for i in range(first, end, 4))
        return data[offset - first:offset - first + size]

    saved_actor = guest(0x800CD904, 812)
    require(sha(saved_actor) == actor_samples[0]['record_sha256'] == binding['actor']['saved_record_sha256'], 'Saved actor does not match captured actor')
    table = struct.unpack('>I', guest(0x800C5464, 4))[0]
    require(table == int(binding['descriptor_table']['base'], 16), 'Descriptor table pointer mismatch')
    descriptors = []
    for expected in binding['descriptors']:
        index = expected['index']
        raw = guest(table + 12 * index, 12)
        pointer, flat, width, height = struct.unpack('>IIHH', raw)
        require((pointer, flat, width, height, sha(raw)) == (int(expected['texture_base'], 16), expected['flat_id'], expected['width'], expected['height'], expected['sha256']), 'Saved descriptor mismatch')
        descriptors.append({'index': index, 'pointer': hex(pointer), 'flat': flat, 'dimensions': [width, height], 'sha256': sha(raw)})
    descriptor15 = next(v for v in descriptors if v['index'] == 15)
    require((descriptor15['pointer'], descriptor15['flat'], descriptor15['dimensions']) == ('0x801b1730', 3823, [64, 64]), 'Selected descriptor changed')

    context = packet['context']
    actor_stage = next(v for v in stage['actors'] if v['slot'] == 7)
    require((stage['scene_id'], actor_stage['entry'], actor_stage['id']) == (context['scene'], 75, context['actor']) == (16, 75, 6), 'Stage context disagreement')
    require(stage['name'] == context['name'] and int(actor_stage['render_pointer'], 16) == int(context['save_renderpointer'], 16), 'Saved context disagreement')
    require(context['selected_parts'] == [0, 1, 2, 3, 6, 7] and context['args'] == [255, 2147686152, 1, 0], 'Packet draw context changed')

    draws = []
    for task_packet in packet['tasks']:
        enter, returned, submitted = task_packet['events']
        require([enter, returned, submitted] in [[15, 22, 26], [42, 49, 53]], 'Unexpected draw event group')
        entry, ret, task = events[enter], events[returned], events[submitted]
        rb, tb = blocks[returned], blocks[submitted]
        q = next(v for v in quick['draws'] if v['entry_event'] == enter)
        paired_draw = next(v for v in paired['draw_calls'] if v['event_index'] == enter)
        args = list(struct.unpack('>4I', blocks[enter]['stack-arguments'][1]))
        require(args == context['args'] == q['arguments'] == paired_draw['arguments'], 'Raw draw arguments disagree')
        require(int(entry['evidence']['registers']['ra'], 16) == int(context['caller'], 16), 'Caller disagreement')
        require([events[i]['render_state_hash'] for i in (enter, returned, submitted)] == task_packet['state_hashes'], 'Packet event-state hashes disagree')
        for probe in task_packet['task_root_probes']:
            actual = tb[probe['name']][2]
            require(all(actual[k] == v for k, v in probe.items()), 'Task root probe disagreement')
        task_header = tb['task'][1]
        require(struct.unpack_from('>I', task_header)[0] == 1, 'Submission is not a graphics task')
        address, command_bytes, _ = rb['character-command-buffer']
        task_address, task_bytes, _ = tb['command-buffer']
        offset = address - task_address
        submission = task_packet['submission']
        require(submission == q['submission'], 'Saved submission analyses disagree')
        require(address == submission['command_buffer_start'] and address + len(command_bytes) == submission['command_buffer_end'], 'Command range mismatch')
        require(sha(command_bytes) == submission['command_sha256'], 'Command range hash mismatch')
        require(offset >= 0 and task_bytes[offset:offset + len(command_bytes)] == command_bytes and task_bytes.count(command_bytes) == 1, 'Task lacks unchanged unique command range')
        parts = []
        for event_index, part, pointer, length, digest in task_packet['parts']:
            part_model = events[event_index]['state']['model']
            require((part_model['display_model_index'], part_model['draw_mode'], part_model['secondary_model_index'], part_model['part_index']) == (75, 1, 0, part), 'Part selection mismatch')
            require(part_model['selected_display_list'] & 0xFFFFFFFF == pointer, 'Part pointer mismatch')
            matches = [raw for name, (a, raw, _) in tb.items() if a == pointer and name.startswith('nested-display-list-')]
            require(len(matches) == 1, 'Selected list absent or ambiguous')
            raw = matches[0]
            require(len(raw) == length and sha(raw) == digest, 'Selected list hash mismatch')
            opcodes = collections.Counter(a >> 24 for a, b in struct.iter_unpack('>II', raw))
            parts.append({'part': part, 'pointer': hex(pointer), 'bytes': length, 'sha256': digest, 'direct_triangle_count': opcodes[5] + 2 * opcodes[6] + 4 * sum(opcodes[i] for i in range(16, 32))})
        require([v['part'] for v in parts] == context['selected_parts'], 'Selected part set mismatch')
        require(sum(v['direct_triangle_count'] for v in parts) == sum(v['triangle_count'] for v in ret['state']['rdp']['draw_runs']) == submission['triangle_count'] == q['selected_faces'] == 868, 'Selected triangle total mismatch')
        target_rows = [task['state']['rdp']['draw_runs'][v['draw_index']] for v in q['rows']]
        require([v['command_offset'] for v in target_rows] == task_packet['triangle_effective_offsets'], 'Target command offsets disagree')
        require(len(target_rows) == 6 and sum(v['triangle_count'] for v in target_rows) == q['target_faces'] == packet['geometry']['target_faces'] == 24, 'Target triangle total mismatch')
        textures = {}
        expected_material = dict(packet['material'], **task_packet.get('material_overrides', {}))
        for row, expected in zip(target_rows, q['rows']):
            require(row['state'] == expected['state'] and row['triangle_count'] == expected['faces'], 'Target row state disagreement')
            require(all(row['state'][k] == v for k, v in expected_material.items()), 'Packet material state mismatch')
            correlations = [v for v in task['state']['rdp']['model_correlations'] if v['runtime_cluster_index'] == row['runtime_cluster_index']]
            require(len(correlations) == 1 and correlations[0]['status'] == 'unique', 'Target source correlation is not unique')
            candidate = correlations[0]['candidates']
            require(len(candidate) == 1, 'Target source candidates ambiguous')
            c = candidate[0]
            require((c['bank'], c['entry'], c['segment'], c['material_run']['index'], c['static_first_face'], c['triangle_count'], c['model_sha1']) == (1, 75, 0, 16, 368, 24, packet['identity']['source_sha1']), 'Target recorded source correlation changed')
            for role, span_name in [('pixel_image', 'pixel'), ('palette_image', 'palette')]:
                image = row['state']['texture'][role]
                name = 'runtime-texture-image-%04d' % image['captured_texture_image_index']
                a, raw, _ = tb[name]
                span = packet['flat3823'][span_name]
                require(a == image['resolved_address'] and len(raw) == span[1] and sha(raw) == span[2] == image['sha256'], 'Captured texture span mismatch')
                textures[span_name] = {'address': hex(a), 'bytes': len(raw), 'sha256': sha(raw)}
        require(textures['pixel']['address'] == '0x801b1730' and textures['palette']['address'] == '0x801b1f30', 'Texture address mismatch')
        part0 = parts[0]
        source_raw = next(raw for name, (a, raw, _) in tb.items() if a == int(part0['pointer'], 16) and name.startswith('nested-display-list-'))
        triangle_bytes = b''.join(source_raw[context['model_runtime_base'] + v - int(part0['pointer'], 16):context['model_runtime_base'] + v - int(part0['pointer'], 16) + 8] for v in packet['source_triangle_offsets'])
        require(len(triangle_bytes) == 48 and all(0x10 <= a >> 24 <= 0x1F for a, b in struct.iter_unpack('>II', triangle_bytes)), 'Source triangle command shape mismatch')

        task_matrices = {v['address']: v for v in task['state']['joint_matrices']}
        matrix_count, changed_raw, max_error = 0, 0, 0.0
        target_matrix_proofs = []
        target_addresses = {v['state']['matrix']['resolved_address'] for v in target_rows}
        for matrix in ret['state']['joint_matrices']:
            if not any(v.get('segment') == 3 for v in matrix['references']):
                continue
            a = matrix['address']
            rm = [raw for _, (addr, raw, _) in rb.items() if addr == a and len(raw) == 64]
            sm = [raw for _, (addr, raw, _) in tb.items() if addr == a and len(raw) == 64]
            require(len(rm) == len(sm) == 1, 'Character matrix capture absent or ambiguous')
            floats = list(struct.unpack('>16f', rm[0]))
            floats[3] = floats[7] = floats[11] = 0.0
            floats[15] = 1.0
            fixed = [(struct.unpack_from('>h', sm[0], 2 * i)[0] << 16) | struct.unpack_from('>H', sm[0], 32 + 2 * i)[0] for i in range(16)]
            require(all(floats[i] == matrix['rows'][i // 4][i % 4] for i in range(16)), 'Float matrix metadata mismatch')
            require(all(fixed[i] / 65536 == task_matrices[a]['rows'][i // 4][i % 4] for i in range(16)), 'Fixed matrix metadata mismatch')
            require(all(round(v * 65536) == n for v, n in zip(floats, fixed)), 'Character matrix is not exact nearest fixed-point conversion')
            error = max(abs(v - n / 65536) for v, n in zip(floats, fixed))
            max_error = max(max_error, error)
            changed_raw += rm[0] != sm[0]
            matrix_count += 1
            if a in target_addresses:
                target_matrix_proofs.append({'address': hex(a), 'return_sha256': sha(rm[0]), 'submit_sha256': sha(sm[0]), 'max_absolute_error': error})
        require(matrix_count == 35 and len(target_matrix_proofs) == 1, 'Character matrix coverage changed')
        draws.append({
            'events': [enter, returned, submitted],
            'arguments': args,
            'caller': context['caller'],
            'parts': parts,
            'haybot_triangle_count': 868,
            'target_triangle_count': 24,
            'command_range': {
                'bytes': len(command_bytes),
                'sha256': sha(command_bytes),
                'unchanged_in_task': True,
                'occurrences_in_task_buffer': 1,
            },
            'texture_spans': textures,
            'target_triangle_command_sha256': sha(triangle_bytes),
            'material_fields_compared': sorted(expected_material),
            'matrix_conversion': {
                'character_segment': 3,
                'matrix_count': matrix_count,
                'changed_raw_matrix_count': changed_raw,
                'nearest_16_16_conversion_exact': True,
                'max_absolute_error': max_error,
                'target_matrices': target_matrix_proofs,
                'excluded': 'Non-segment3 record at 0x800C3E98; no character transform claim for it.',
            },
        })

    return {
        'schema': 'haybot-capture-audit-v1',
        'audit_status': 'specified-checks-passed',
        'method': 'Standard-library decoding and comparisons; no project generator, emulator, UI, ROM extraction, or command-stream replay.',
        'manifest': {
            'bytes': len(manifest_bytes),
            'sha256': sha(manifest_bytes),
        },
        'inputs': used,
        'trace': {
            'events': len(events),
            'verified_state_hash_count': len(events),
            'verified_memory_block_count': block_count,
            'recorded_rom_sha1': header['normalized_sha1'],
        },
        'actor_samples': actor_samples,
        'saved_state': {
            'decompressed_sha256': sha(saved),
            'rdram_offset': '0x1BC',
            'byte_order': 'reverse each four-byte word',
            'actor_sha256': sha(saved_actor),
            'descriptor_table': hex(table),
            'descriptors': descriptors,
        },
        'scene_context': {
            'scene': 16,
            'actor': 6,
            'entry': 75,
            'slot': 7,
            'source_role': 'scene_metadata',
            'verification': 'Compared with hash-verified saved stage1 metadata; scene scalar not independently decoded.',
        },
        'draws': draws,
        'claim_limits': {
            'matrices_changed_after_return': 'Empty packet lists are not byte-immutability proof. Thirty-five character matrices per task change representation from float32 to exact nearest signed16.16; error at most half a fixed-point unit.',
            'executed_once': 'Saved decoder/link result, corroborated here by one unchanged command-range occurrence, graphics task type, selected-list counts, and target draw metadata. Command control flow was not independently replayed.',
            'run16_source_identity': 'Unique source correlation metadata compared with packet. Fresh ROM-derived topology and run digest must be checked separately.',
            'flat3823_identity': 'Captured spans and saved descriptor15 reverified. Archive-wide uniqueness, complete ROM payload/PNG/RGBA identity require separate ROM proof.',
            'geometry_animation_preservation': 'Not tested by this capture audit; requires fresh source/export validation.',
            'capture_context': 'Scene16 from hash-verified scene metadata. The scene scalar was not independently decoded.',
            'native_result': 'No framebuffer, lighting, fog rasterization, pose, visibility, playback timing, or universal default claim.',
        },
        'script': {
            'bytes': Path(__file__).stat().st_size,
            'sha256': sha(Path(__file__).read_bytes()),
        },
    }


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--manifest', type=Path, required=True)
    parser.add_argument('--manifest-sha256', required=True,
                        help='SHA256 of an independently reviewed local file-hash manifest')
    for role in INPUT_ROLES:
        parser.add_argument('--' + role.replace('_', '-'), type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args(argv)
    validate_paths(args, ('manifest', *INPUT_ROLES), ('output',))
    report = audit({role: getattr(args, role) for role in INPUT_ROLES},
                   args.manifest, args.manifest_sha256)
    report['passed'] = True
    report['checks'] = {
        'manifest_input_hashes_and_sizes': True,
        'trace_state_hashes': True,
        'captured_memory_hashes_and_sizes': True,
        'raw_draw_arguments_and_caller': True,
        'actor_selector15_phase5_in_all14_samples': True,
        'saved_state_actor_and_descriptor15': True,
        'stage1_scene16_metadata_matches_packet': True,
        'command_ranges_unchanged_and_present_once': True,
        'selected_parts_and868_triangles': True,
        'target24_triangles_and_recorded_run16_correlation': True,
        'captured_texture_spans_match_packet': True,
        'packet_material_fields_match_target_states': True,
        'character_matrices_exact_nearest16_16_conversion': True,
    }
    report['scope_limits'] = list(report['claim_limits'].values())
    report['matrix_precision'] = [
        {'events': draw['events'], **draw['matrix_conversion']}
        for draw in report['draws']
    ]
    raw = encoded(report)
    write_new(args.output, raw)
    print(json.dumps({'status': report['audit_status'], 'bytes': len(raw), 'sha256': sha(raw), 'input_count': len(report['inputs']), 'event_count': report['trace']['events'], 'memory_block_count': report['trace']['verified_memory_block_count']}))


if __name__ == '__main__':
    main()
