"""Read frozen Library155 capture bytes; no display-list or emulator replay."""
import base64
import hashlib
import math
import struct


def require(value, message):
    if not value:
        raise ValueError(message)


def probes(event):
    result = {}
    for probe in event['evidence']['memory']:
        if 'data_base64' not in probe:
            continue
        raw = base64.b64decode(probe['data_base64'], validate=True)
        require(len(raw) == probe['length'], 'capture probe length changed')
        require(hashlib.sha256(raw).hexdigest() == probe['sha256'],
                'capture probe hash changed')
        require(probe['name'] not in result, 'duplicate capture probe name')
        result[probe['name']] = (int(probe['resolved_address'], 0), raw)
    return result


def matrix_bytes(probe_map):
    result = {}
    for name, (address, raw) in probe_map.items():
        if name.startswith('runtime-matrix-'):
            require(len(raw) == 64, 'matrix byte count changed')
            require(address not in result or result[address] == raw,
                    'conflicting matrix probes')
            result[address] = raw
    return result


def verify_raw_closure(events, packet, quick_result, paired_topology):
    """events excludes session header; other arguments are decoded JSON objects."""
    results = []
    for task in packet['tasks']:
        entry, returned, submitted = (task[k] for k in ('entry', 'return', 'task'))
        matches = [d for d in quick_result['draws']
                   if (d['entry_event'], d['return_event'], d['task_event'])
                   == (entry, returned, submitted)]
        require(len(matches) == 1, 'ambiguous quick-result draw')
        draw = matches[0]
        matches = [d for d in paired_topology['draw_calls'] if d['event_index'] == entry]
        require(len(matches) == 1, 'ambiguous paired draw')
        paired = matches[0]
        before, after = probes(events[returned]), probes(events[submitted])
        root_address, root = after['command-buffer']
        task_address, task_bytes = after['task']
        require(len(task_bytes) == 64, 'task header size changed')
        header = struct.unpack('>16I', task_bytes)
        require(header[0] == 1 and header[12] & 0x1fffffff == root_address & 0x1fffffff
                and header[13] == len(root), 'task header/root mismatch')
        require(int(events[submitted]['hook_address'], 0) == 0x10023DF0,
                'submission hook changed')
        submission = task['submission']
        start, end = (submission[k] for k in ('command_buffer_start', 'command_buffer_end'))
        require(root_address <= start < end <= root_address + len(root),
                'renderer range is outside root buffer')
        renderer_bytes = root[start - root_address:end - root_address]
        require(hashlib.sha256(renderer_bytes).hexdigest() == submission['command_sha256'],
                'renderer range hash changed')
        require(before['character-command-buffer'] == (start, renderer_bytes),
                'renderer commands changed between return and submit')

        fog = task['effective_fog']
        require(len(fog['origin']) == 1, 'fog source must be in root buffer')
        origin = fog['origin'][0]
        require(start <= origin and origin + 8 <= end, 'fog lies outside renderer range')
        fog_words = struct.unpack_from('>II', root, origin - root_address)
        require(fog_words == tuple(fog['words']) == (0xf8000000, 255),
                'raw fog words disagree with packet')
        draw_runs = events[submitted]['state']['rdp']['draw_runs']
        offsets = [draw_runs[row['draw_index']]['command_offset'] for row in draw['rows']]
        require(all(offset > fog['offset'] for offset in offsets),
                'target command precedes recorded flattened fog offset')

        source, target = matrix_bytes(before), matrix_bytes(after)
        addresses = [matrix['address'] for matrix in paired['runtime_matrices']]
        require(len(addresses) == len(set(addresses)) == 35,
                'captured target matrix inventory changed')
        errors = []
        for address in addresses:
            require(address in source and address in target, 'target matrix probe absent')
            floats = struct.unpack('>16f', source[address])
            integers = struct.unpack('>16h', target[address][:32])
            fractions = struct.unpack('>16H', target[address][32:])
            fixed = [integer + fraction / 65536 for integer, fraction in zip(integers, fractions)]
            # CBFD's fourth float column is scratch data, not an affine component.
            for row in range(4):
                for column in range(3):
                    index = row * 4 + column
                    require(math.isfinite(floats[index]), 'nonfinite source matrix')
                    errors.append(abs(floats[index] - fixed[index]))
        require(max(errors) <= 1 / 65536, 'matrix changed beyond fixed-point precision')
        results.append({
            'entry_event': entry, 'return_event': returned, 'submit_event': submitted,
            'task_address': task_address, 'root_address': root_address,
            'fog_origin': origin, 'fog_root_buffer_offset': origin - root_address,
            'verified_fog_words': list(fog_words),
            'recorded_flattened_fog_offset': fog['offset'],
            'flattened_fog_offset_independently_recomputed': False,
            'target_draw_offsets': [min(offsets), max(offsets)],
            'matrix_count': len(addresses), 'affine_components_compared': len(errors),
            'matrix_maximum_absolute_error': max(errors), 'matrix_tolerance': 1 / 65536,
            'matrix_byte_blocks_changed': sum(source[a] != target[a] for a in addresses),
            'matrix_status': 'float-to-split-fixed-affine-components-agree-within-precision',
        })
    return results
