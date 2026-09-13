"""ROM-only constructor call discovery and material cohort diagnosis.

This report never grants an export context. Only the separate, pinned renderer
proofs do that. A candidate prologue is a search boundary, not a claimed source
function boundary. No speculative register slice is used as model identity.
"""
from collections import Counter
from dataclasses import replace
import hashlib
import struct
try:
    from scripts.model_constructor_flow import analyze
    from scripts import model_attachment_events
except ModuleNotFoundError:
    from model_constructor_flow import analyze
    import model_attachment_events

SUBMISSIONS = {
    0x1513264C: 'object constructor', 0x15132A4C: 'object constructor wrapper',
    0x15151D6C: 'random array helper', 0x15152190: 'random array helper',
    0x1515080C: 'callback array helper', 0x15138424: 'descriptor constructor',
    0x1518C900: 'direct bank-09 loader',
}


def discover_calls(code, base):
    words = struct.unpack(f'>{len(code) // 4}I', code[:len(code) // 4 * 4])
    starts = [i for i, word in enumerate(words) if word & 0xFFFF8000 == 0x27BD8000]
    starts.append(len(words))
    owner = 0
    rows = []
    for index, word in enumerate(words):
        if word >> 26 != 3:
            continue
        target = ((base + index * 4 + 4) & 0xF0000000) | ((word & 0x3FFFFFF) << 2)
        if target not in SUBMISSIONS:
            continue
        while owner + 1 < len(starts) and starts[owner + 1] <= index:
            owner += 1
        begin, end = starts[owner], starts[owner + 1] if owner + 1 < len(starts) else len(words)
        row = {'call_pc': f'0x{base + index * 4:08X}', 'callee': f'func_{target:08X}',
               'family': SUBMISSIONS[target], 'status': 'requires-consumer-review'}
        if begin <= index and end - begin <= 16384:
            raw = code[begin * 4:end * 4]
            row.update(candidate_start=f'0x{base + begin * 4:08X}',
                       candidate_size=len(raw), candidate_sha1=hashlib.sha1(raw).hexdigest())
        rows.append(row)
    return rows


def trace_calls(code, base, data, data_base, lookup):
    rows = discover_calls(code, base)
    functions = {}
    for row in rows:
        start = row.get('candidate_start')
        if start is None:
            row['argument_analysis'] = {'status': 'incomplete', 'barriers': ['no candidate prologue']}
            continue
        if start not in functions:
            offset = int(start, 16) - base
            functions[start] = analyze(code[offset:offset + row['candidate_size']], int(start, 16), data, data_base)
        result = functions[start]
        evidence = result['calls'].get(row['call_pc'], {})
        row['argument_analysis'] = {'status': result['status'], 'barriers': result['barriers'], **evidence}
        candidates = []
        callee = int(row['callee'][5:], 16)
        if callee in (0x1513264C, 0x15132A4C):
            selector = evidence.get('template_fields', {}).get('selector')
            if selector is not None and selector < len(lookup):
                candidates.append(lookup[selector])
        elif callee in (0x15151D6C, 0x15152190, 0x1515080C):
            candidates += [lookup[s] for s in evidence.get('initial_array_words', []) if s < len(lookup)]
        elif callee == 0x1518C900:
            value = evidence.get('arguments', {}).get('a0', {})
            if value.get('kind') == 'constant':
                candidates.append(value['value'])
        row['review_candidate_entries'] = sorted(set(candidates))
    return rows, functions


def diagnose_run(models, run, payloads, tables, context):
    """Separate missing renderer proof from failed decoding without admitting it."""
    texture, _, _ = models.rom_render_state_preview_texture(run, {}, payloads, tables)
    if texture is not None:
        return {'blocker': 'renderer-evidence-missing' if context is None else 'eligible',
                'texture_consensus': True, 'renderer': (context or {}).get('renderer')}
    failures = Counter()
    for table in tables:
        entry = next((e for e in table['entries']
                      if int(e['offset'], 16) == run.runtime_render_state_offset), None)
        if entry is None:
            failures['inherited-render-state-unavailable'] += 1
            continue
        candidate = replace(run, other_mode=tuple(int(w, 16) for w in entry['other_mode']))
        texture, status = models.choose_preview_texture(candidate, {}, payloads)
        state = models.texture_coordinate_state(candidate)
        if texture is None and state and state['format'] in (3, 4) and run.pixel.flat_index in payloads:
            payload = payloads[run.pixel.flat_index]
            texture, detail = models.character_intensity_mipmap_preview_texture(candidate, payload)
            if 'combiner-unresolved' not in detail:
                status = detail
        if texture is None:
            failures[status] += 1
    pixel = run.pixel
    span = {}
    if pixel and pixel.load_command and pixel.flat_index in payloads:
        loaded = (((pixel.load_command[1] >> 12) & 0xFFF) + 1) * 2
        span = {'flat_index': pixel.flat_index, 'load_bytes': loaded,
                'payload_bytes': len(payloads[pixel.flat_index])}
    return {'blocker': 'texture-decoder-unresolved', 'texture_consensus': False,
            'renderer': (context or {}).get('renderer'), 'table_failures': dict(failures), **span}


def report(models, profile, rom_argument, bank):
    path, layout = models.resolve_rom(profile, rom_argument)
    rom, _ = models.normalize_rom(path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if profile != 'us' or digest not in layout['normalized_sha1']:
        raise ValueError('constructor discovery requires the validated US ROM')
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    _, _, source_digest, bundles, tables = models.load_model_bundles(profile, rom_argument, bank)
    if digest != source_digest:
        raise ValueError('constructor discovery ROM changed')
    context = models.load_object_material_context(profile, rom_argument, digest, bank)
    contexts = {(r['entry'], r['segment']): r for r in context['models']}
    payloads = models.load_flat_asset_payloads(profile, rom_argument, digest)
    rows = []
    for bundle in bundles:
        for segment in bundle.segments:
            if not segment.data:
                continue
            geometry = models.parse_segment_geometry(segment, bank)
            runs = []
            for index, run in enumerate(geometry.material_runs):
                texture, status = models.choose_preview_texture(run, {}, payloads)
                if texture is not None or 'lookup-mode-unresolved' not in status:
                    continue
                result = diagnose_run(models, run, payloads, tables,
                                      contexts.get((bundle.index, segment.index)))
                runs.append({'run': index, 'faces': run.face_count, 'source_status': status, **result})
            if runs:
                rows.append({'bank': bank, 'entry': bundle.index, 'segment': segment.index,
                             'runs': runs, 'blockers': sorted({r['blocker'] for r in runs})})
    lookup_raw = models.model_bank09_materials._slice(game.data, layout['game_data_vram'],
        models.model_bank09_materials.MODEL_TABLE, models.model_bank09_materials.MODEL_COUNT * 4)
    calls, functions = trace_calls(game.code, layout['game_vram'], game.data,
                                  layout['game_data_vram'], struct.unpack('>233I', lookup_raw))
    unresolved = [r for r in rows if 'renderer-evidence-missing' in r['blockers']]
    targets = [{'entry': row['entry'], 'segment': row['segment'],
                'candidate_calls': [c['call_pc'] for c in calls if row['entry'] in c.get('review_candidate_entries', [])],
                'status': 'requires-consumer-review'} for row in unresolved] if bank == 9 else []
    return {'schema_version': 3, 'normalized_sha1': digest, 'bank': bank,
            'scope': 'ROM discovery and texture diagnosis only. No model is exported or admitted by this report.',
            'counts': dict(Counter(blocker for row in rows for blocker in row['blockers'])),
            'models': rows, 'constructor_calls': calls, 'target_queue': targets,
            'argument_analysis': {'functions': functions,
                'counts': dict(Counter(r['status'] for r in functions.values())),
                'scope': 'Bounded candidate functions and initial ROM data only; runtime writes and renderer selection require pinned consumer proof.'},
            **({'attachment_events': model_attachment_events.report(models, rom, layout, game)}
               if bank == 9 else {}),
            'reviewed_contexts': context, 'capture_inputs': []}
