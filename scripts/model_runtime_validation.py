"""Compare an exported rigid rig with hash-checked submitted CBFD inputs.

The reference comes from captured VTX bytes and vertex-cache replay, not the
ROM geometry parser or pose baker. A rig evaluated under captured matrices is
distinct from proving that an older posed export belongs to that submission.
"""

from __future__ import annotations

import hashlib
import json
import struct
from collections import Counter, defaultdict
from pathlib import Path
from urllib.parse import unquote

from scripts import model_assets as models, mupen_trace as trace
from scripts.model_preview_evidence import preview_fingerprint

ROOT = Path(__file__).resolve().parents[1]
LOCAL_TOLERANCE = 0.0001  # glTF float32 bind positions and inverse-bind translations.


def load_rig(path: Path) -> tuple[dict, dict]:
    from scripts.model_validation import accessor

    preview_fingerprint(path)
    document = json.loads(path.read_text())
    if len(document.get('skins', [])) != 1:
        raise ValueError('submitted rig comparison requires one skin')
    for node in document['nodes']:
        if 'mesh' in node and (node.get('skin') != 0 or any(k in node for k in
                ('matrix', 'translation', 'rotation', 'scale'))):
            raise ValueError('rig mesh node has an unsupported transform or skin')
    buffers = [(path.parent / unquote(b['uri'])).read_bytes() for b in document['buffers']]
    skin = document['skins'][0]
    inverse = accessor(document, skin['inverseBindMatrices'], buffers)
    if len(inverse) != len(skin['joints']):
        raise ValueError('inverse-bind matrix count differs from joints')
    if any(tuple(matrix[i] for i in (3, 7, 11, 15)) != (0, 0, 0, 1) for matrix in inverse):
        raise ValueError('rig inverse-bind matrix is not affine')
    faces = {}
    for mesh in document['meshes']:
        for primitive in mesh['primitives']:
            if primitive.get('mode', 4) != 4:
                raise ValueError('submitted rig requires triangle primitives')
            if primitive.get('targets'):
                raise ValueError('submitted rig morph targets require a separate comparison')
            attrs = {key: accessor(document, value, buffers)
                     for key, value in primitive['attributes'].items()}
            indices = [row[0] for row in accessor(document, primitive['indices'], buffers)]
            first = primitive['extras']['firstFace']
            if len(indices) % 3 or primitive['extras']['faceCount'] * 3 != len(indices):
                raise ValueError('rig primitive face extent changed')
            for offset in range(0, len(indices), 3):
                corners = []
                for i in indices[offset:offset + 3]:
                    if not 0 <= i < len(attrs['POSITION']):
                        raise ValueError('rig triangle references an invalid vertex')
                    if attrs['WEIGHTS_0'][i] != (1.0, 0.0, 0.0, 0.0):
                        raise ValueError('submitted rig requires unit rigid weights')
                    joint = attrs['JOINTS_0'][i][0]
                    if not 0 <= joint < len(inverse):
                        raise ValueError('rig joint index is invalid')
                    matrix_slot = document['nodes'][skin['joints'][joint]]['extras']['matrixIndex']
                    position = attrs['POSITION'][i] + (1.0,)
                    # glTF matrices are column-major. Recover the original
                    # joint-local vertex without consulting ROM bind pivots.
                    local = tuple(sum(inverse[joint][col * 4 + row] * position[col]
                                      for col in range(4)) for row in range(3))
                    corners.append({'xyz': local, 'joint': matrix_slot,
                                    'uv': attrs.get('TEXCOORD_0', [None] * len(attrs['POSITION']))[i]})
                index = first + offset // 3
                if index in faces:
                    raise ValueError('rig contains overlapping source face spans')
                faces[index] = {'corners': corners, 'material': primitive['material']}
    if not faces or set(faces) != set(range(len(faces))):
        raise ValueError('rig source face coverage is empty or incomplete')
    return document, faces


def match_cluster(faces: dict, triangles: list, first: int, count: int) -> list | None:
    """Match winding-preserving corners and infer one absolute palette root.

    TRI4 command order differs from archive face order. Reorder whole faces
    and rotate their corners, but never reverse winding or drop duplicates.
    """

    unused = set(range(first, first + count))
    if len(triangles) != count or not unused.issubset(faces):
        return None
    selected = []
    for draw, actual in triangles:
        options = []
        for index in sorted(unused):
            corners = faces[index]['corners']
            for rotation in range(3):
                expected = corners[rotation:] + corners[:rotation]
                error = max(abs(a['xyz'][axis] - e['xyz'][axis])
                            for a, e in zip(actual, expected) for axis in range(3))
                roots = {a['matrix_address'] - 64 * e['joint'] for a, e in zip(actual, expected)}
                if error <= LOCAL_TOLERANCE and len(roots) == 1:
                    options.append((index, rotation, next(iter(roots)), error))
        if not options:
            return None
        # Exact duplicate faces consume separate occurrences. Different joint
        # ownership/root interpretations are genuinely ambiguous.
        if len({(root, tuple((c['xyz'], c['joint']) for c in
                            (faces[i]['corners'][rot:] + faces[i]['corners'][:rot])))
                for i, rot, root, _ in options}) != 1:
            return None
        index, rotation, root, error = options[0]
        unused.remove(index)
        expected = faces[index]['corners'][rotation:] + faces[index]['corners'][:rotation]
        world_error = max(abs(sum((a['xyz'][k] - e['xyz'][k]) * a['matrix'][k][axis]
                                  for k in range(3)))
                          for a, e in zip(actual, expected) for axis in range(3))
        selected.append({'root': root, 'face': index, 'rotation': rotation,
                         'local_error': error, 'world_error': world_error,
                         'draw': draw, 'corners': actual})
    if unused or len({row['root'] for row in selected}) != 1:
        return None
    return selected


def instance_coverage(matches: list, face_count: int, expected_instances: int,
                      expected_roots: set[int] | None = None,
                      source_faces: set[int] | None = None) -> dict:
    instances = defaultdict(list)
    for match in matches:
        instances[match['root']].append(match)
    if len(instances) != expected_instances or expected_instances < 1:
        raise ValueError(f'expected {expected_instances} submitted instances, found {len(instances)}')
    if expected_roots is not None and set(instances) != expected_roots:
        raise ValueError('inferred palettes differ from the captured reference roots')
    for root, rows in instances.items():
        counts = Counter(row['face'] for row in rows)
        expected_faces = set(range(face_count)) if source_faces is None else source_faces
        if not expected_faces or not expected_faces.issubset(range(face_count)):
            raise ValueError('submitted source face selection is invalid')
        if counts != Counter(expected_faces):
            raise ValueError(f'palette {root:#x}: submitted/exported face coverage differs')
    return instances


def runtime_inputs(case: dict, expected_sha1: str, cluster_index: list) -> dict:
    source = ROOT / case['source']
    target = tuple(case['target'])
    clusters = [row for row in cluster_index if tuple(row[k] for k in ('bank', 'entry', 'segment')) == target]
    payload = ROOT / f'build/assets/models/us-bank-{target[0]:02x}/bundles/{target[1]:04d}/segment-{target[2]:02d}.bin'
    if hashlib.sha1(payload.read_bytes()).hexdigest() != expected_sha1 or not clusters or any(
            row['model_sha1'] != expected_sha1 for row in clusters):
        raise ValueError('runtime cluster source does not match the active ROM model')
    catalog = ROOT / case['materials']
    manifest = json.loads(catalog.read_text())
    dependencies = {str(catalog): hashlib.sha256(catalog.read_bytes()).hexdigest(),
                    str(ROOT / case['trace']): hashlib.sha256((ROOT / case['trace']).read_bytes()).hexdigest()}
    for record in manifest['materials']:
        for variant in record['variants']:
            image = variant.get('captured_texture')
            if image:
                for item in [image, *models.runtime_captured_auxiliary_textures(image)]:
                    path = models._validated_preview_source(catalog.parent, item['file'])
                    dependencies[str(path)] = hashlib.sha256(path.read_bytes()).hexdigest()
    exports = {export['path']: preview_fingerprint(ROOT / export['path']) for export in case.get('exports', [])}
    return {'case': case, 'gltf': preview_fingerprint(source), 'exports': exports, 'dependencies': dependencies,
            'model_sha1': expected_sha1, 'clusters': clusters}


def draw_call_selector(call: dict) -> dict:
    """Stable, JSON-safe identity; the active entry may differ from the source."""
    return {**{key: call[key] for key in ('return_event_index', 'entry', 'slot', 'task_submission_index')},
            'render_pass': call['render_pass']['kind']}


def load_submitted_call_context(path: Path, digest: str, inventory: dict | None = None,
                                clusters: list | None = None) -> dict:
    if inventory is None:
        actual_digest, inventory = models.runtime_material_inventory('us', None)
        if actual_digest != digest:
            raise ValueError('submitted call ROM identity changed')
    if clusters is None:
        clusters = models.load_model_cluster_index()
    _, _, _, bundles, _ = models.load_model_bundles('us', None, 1)
    validated = models.load_character_draw_trace(
        path, digest, {key[1] for key in inventory if key[0] == 1},
        models.character_display_list_topology(bundles), clusters)
    return {'trace': validated, 'parts': models.selected_part_material_candidates(validated, inventory)}


def select_submitted_call(case: dict, model_sha1: str, context: dict) -> dict:
    """Select only ROM parts positively byte-paired with this graphics task."""
    selector = case['draw_call']
    calls = [call for call in context['trace']['draw_calls'] if draw_call_selector(call) == selector]
    if len(calls) != 1:
        raise ValueError('submitted selector does not identify exactly one renderer call')
    call = calls[0]
    submission = call.get('submitted_graphics', {})
    if (submission.get('status') != 'captured-range-executed-once-in-next-graphics-task'
            or submission.get('event_index') != case['event_index']):
        raise ValueError('selected renderer call lacks a positive matching graphics submission')
    sequence = models.resolve_character_call_from_part_selections(call.get('part_selections', []))
    if sequence is None:
        raise ValueError('selected renderer call has unresolved ROM parts')
    source = sequence['source_model']
    if ([source[key] for key in ('bank', 'entry', 'segment')] != case['target']
            or source['model_sha1'] != model_sha1):
        raise ValueError('selected renderer call belongs to another source model')
    selected = {index: record['candidate'] for index, record in context['parts'].get(case['event_index'], {}).items()
                if record['evidence']['return_event_index'] == call['return_event_index']}
    expected = Counter((c['static_cluster_index'], c['first_face'], c['face_count'], c['material_run'])
                       for c in sequence['resolved_clusters'])
    actual = Counter((c['static_cluster_index'], c['static_first_face'], c['triangle_count'], c['material_run']['index'])
                     for c in selected.values())
    if not selected or actual != expected or any(
            any(c.get(key) != value for key, value in source.items()) for c in selected.values()):
        raise ValueError('selected renderer parts do not cover their submitted clusters exactly')
    faces = [i for c in selected.values() for i in range(c['static_first_face'], c['static_first_face'] + c['triangle_count'])]
    if len(faces) != len(set(faces)):
        raise ValueError('selected renderer call repeats source faces')
    root = call['root_matrix_address']
    if case.get('expected_instances', 1) != 1 or (case.get('palette_roots') is not None
            and {int(value, 0) for value in case['palette_roots']} != {root}):
        raise ValueError('selected renderer call differs from the expected instance or palette')
    return {'clusters': selected, 'source_faces': set(faces), 'root': root,
            'evidence': {'selector': selector, 'source_model': source,
                         'submitted_event_index': case['event_index'],
                         'command_sha256': call['command_sha256'],
                         'palette_root': f'0x{root:08X}', 'selected_cluster_count': len(selected),
                         'selected_face_count': len(faces), 'submission_status': submission['status']}}


def require_complete_call_faces(selection: dict, faces: dict) -> None:
    if selection['source_faces'] != set(faces):
        raise ValueError('selected renderer call is a partial composition, not a complete source rig')


def submitted_rig_reference(case: dict, normalized_sha1: str, inputs: dict,
                            selection: dict | None = None, *, call_context: dict | None = None) -> dict:
    """Resolve each source face to captured vertex inputs in one submission."""

    path = ROOT / case['source']
    document, faces = load_rig(path)
    call_evidence = None
    if 'draw_call' in case:
        if selection is not None:
            raise ValueError('submitted case cannot combine a call selector and an explicit face selection')
        context = call_context if call_context is not None else load_submitted_call_context(
            ROOT / case['trace'], normalized_sha1)
        selection = select_submitted_call(case, inputs['model_sha1'], context)
        require_complete_call_faces(selection, faces)
        call_evidence = selection['evidence']
    lines = [json.loads(line) for line in (ROOT / case['trace']).read_text().splitlines() if line.strip()]
    if not lines or lines[0].get('record_type') != 'session' or lines[0].get('normalized_sha1') != normalized_sha1:
        raise ValueError('submitted rig trace does not identify the active ROM')
    events = [line for line in lines if line.get('record_type') == 'draw_state']
    event = events[case['event_index']]
    if trace.captured_task_type(event) != 1:
        raise ValueError('submitted rig reference is not a captured graphics task')
    trace.refresh_trace_model_correlations(event, inputs['clusters'])
    rdp = event['state']['rdp']
    loads = rdp['replayed_vertex_loads']
    sources = models.captured_vertex_sources(event)
    if not sources:
        raise ValueError('submitted rig has no verified captured vertex spans')
    draws_by_cluster = defaultdict(list)
    for draw_index, draw in enumerate(rdp['draw_runs']):
        draws_by_cluster[draw.get('runtime_cluster_index')].append((draw_index, draw))
    matches = []
    unmatched = []
    matched_clusters = set()
    for correlation in rdp['model_correlations']:
        candidates = correlation['candidates']
        if selection is not None:
            candidate = selection['clusters'].get(correlation['runtime_cluster_index'])
            if candidate is None:
                continue
            if candidate not in candidates:
                raise ValueError('selected part candidate is absent from submitted command replay')
            candidates = [candidate]
        if not candidates:
            continue
        triangles = []
        for draw_index, draw in draws_by_cluster[correlation['runtime_cluster_index']]:
            load_faces = draw['replayed_vertex_load_indices']
            cache_faces = draw['replayed_vertex_cache_indices']
            if len(load_faces) != draw['triangle_count'] or len(cache_faces) != len(load_faces):
                raise ValueError('captured triangle cache coverage changed')
            for load_indices, cache_indices in zip(load_faces, cache_faces):
                corners = []
                for load_index, cache_index in zip(load_indices, cache_indices):
                    if not isinstance(load_index, int) or not 0 <= load_index < len(loads):
                        raise ValueError('triangle uses an uncaptured vertex load')
                    load = loads[load_index]
                    local = cache_index - load['first_cache_index']
                    if not 0 <= local < load['vertex_count']:
                        raise ValueError('triangle cache slot is outside its vertex load')
                    address = load['resolved_address'] + 16 * local
                    payloads = {data[address - base:address - base + 16] for base, data, _ in sources
                                if base <= address and address + 16 <= base + len(data)}
                    if len(payloads) != 1:
                        raise ValueError('submitted vertex bytes are missing or conflicting')
                    raw = next(iter(payloads))
                    processing = load.get('processing_matrices') or {}
                    if len(processing.get('model_view_sha256', [])) != 1:
                        raise ValueError('rig comparison requires a single captured load matrix')
                    corners.append({'xyz': struct.unpack_from('>hhh', raw),
                                    'st': struct.unpack_from('>hh', raw, 8),
                                    'vertex_hex': raw.hex(),
                                    'load_index': load_index, 'cache_index': cache_index,
                                    'matrix_address': load['state']['matrix']['resolved_address'],
                                    'matrix_segment': load['state']['matrix'].get('segment'),
                                    'segment_base': load['state']['matrix'].get('segment_base_address'),
                                    'matrix': processing['model_view_rows']})
                if len(corners) != 3:
                    raise ValueError('captured triangle does not have three corners')
                triangles.append((draw_index, corners))
        candidates = [match for candidate in candidates
                      if (match := match_cluster(faces, triangles, candidate['static_first_face'],
                                                 correlation['triangle_count'])) is not None]
        if len(candidates) != 1:
            unmatched.append(correlation['runtime_cluster_index'])
        else:
            matches.extend(candidates[0])
            matched_clusters.add(correlation['runtime_cluster_index'])
    if selection is not None and matched_clusters != set(selection['clusters']):
        raise ValueError('selected submitted clusters are missing, ambiguous or disagree with the rig')
    expected_roots = ({int(value, 0) for value in case['palette_roots']}
                      if case.get('palette_roots') else None)
    if call_evidence is not None:
        expected_roots = {selection['root']}
    # Discovery may infer the number of instances, but still requires every
    # face exactly once per palette and positive segment-base evidence. Saved
    # validation cases additionally pin their expected count and roots.
    expected_instances = case.get('expected_instances', len({row['root'] for row in matches}))
    instances = instance_coverage(matches, len(faces), expected_instances, expected_roots,
                                  selection['source_faces'] if selection else None)
    for root, rows in instances.items():
        corners = [corner for row in rows for corner in row['corners']]
        bases = {corner['segment_base'] for corner in corners}
        if root not in bases or any(corner['matrix_segment'] != 3 for corner in corners) or any(
                not isinstance(base, int) or base < root or (base - root) % 64 for base in bases):
            raise ValueError('palette root lacks captured segment-3 base/rebase evidence')
    if unmatched:
        raise ValueError(f'{len(unmatched)} target command clusters remain ambiguous or disagree with the rig')

    return {'document': document, 'faces': faces, 'event': event,
            'matches': matches, 'instances': instances, 'matched_cluster_count': len(matched_clusters),
            'selected_call': call_evidence}


def compare_submitted_rig(case: dict, normalized_sha1: str, inputs: dict, *, call_context: dict | None = None) -> dict:
    from scripts.model_validation import rgba

    reference = submitted_rig_reference(case, normalized_sha1, inputs, call_context=call_context)
    document, faces = reference['document'], reference['faces']
    matches, instances = reference['matches'], reference['instances']
    rdp = reference['event']['state']['rdp']
    path = ROOT / case['source']
    material_path = ROOT / case['materials']
    manifest = json.loads(material_path.read_text())
    models.verify_runtime_material_output(material_path.parent, manifest)
    if manifest['normalized_sha1'] != normalized_sha1 or len(manifest['source_traces']) != 1:
        raise ValueError('runtime rig material catalog must identify one matching trace')
    source_trace = manifest['source_traces'][0]
    if source_trace['sha256'] != hashlib.sha256((ROOT / case['trace']).read_bytes()).hexdigest():
        raise ValueError('rig material catalog belongs to another capture')
    images_by_draw = {}
    matched_draws = {row['draw'] for row in matches}
    for record in manifest['materials']:
        if [record[k] for k in ('bank', 'entry', 'segment')] != case['target']:
            continue
        if record['model_sha1'] != inputs['model_sha1']:
            raise ValueError('rig material record belongs to another model')
        for variant in record['variants']:
            for evidence in variant['evidence']:
                if evidence['event_index'] != case['event_index']:
                    continue
                index = evidence['draw_run_index']
                if index not in matched_draws:
                    continue
                if evidence['source_material_state_hash'] != rdp['draw_runs'][index]['material_state_hash']:
                    raise ValueError('rig material observation does not match the submitted draw')
                if index in images_by_draw and images_by_draw[index] != variant.get('captured_texture'):
                    raise ValueError('conflicting captured images for one draw')
                images_by_draw[index] = variant.get('captured_texture')
    comparisons = Counter()
    image_cache = {}
    for row in matches:
        material = document['materials'][faces[row['face']]['material']]
        draw = rdp['draw_runs'][row['draw']]
        culling = draw['replayed_face_culling']
        bits = material.get('extras', {}).get('faceCulling', {}).get('sourceBits')
        mode = culling.get('mode')
        represented = ((mode == 0 and material.get('doubleSided', False))
                       or (mode == 0x400 and not material.get('doubleSided', False)))
        same_culling = (culling.get('known_bits') == 0x600 and bits is not None
                        and int(bits, 0) == mode and represented)
        comparisons['culling_faces_match' if same_culling else 'culling_faces_incomplete'] += 1
        other = models.decode_other_mode(tuple(draw['state']['other_mode'])) if draw['state'].get('other_mode') else None
        comparisons['alpha_mode_faces_match' if other and material.get('alphaMode', 'OPAQUE') == other['gltf_alpha_mode']
                    else 'alpha_mode_faces_incomplete'] += 1
        binding = material.get('pbrMetallicRoughness', {}).get('baseColorTexture')
        capture = images_by_draw.get(row['draw'])
        usage = models.runtime_material_references_texels({'variants': [{'state': draw['state']}]})
        if binding is None and usage is False:
            comparisons['texture_faces_not_required'] += 1
            continue
        if not binding or not capture:
            comparisons['texture_faces_incomplete'] += 1
            continue
        image = document['images'][document['textures'][binding['index']]['source']]
        exported = path.parent / unquote(image['uri'])
        captured = models._validated_preview_source(material_path.parent, capture['file'])
        key = (str(exported), str(captured), capture['width'], capture['height'])
        if key not in image_cache:
            try:
                image_cache[key] = rgba(exported.read_bytes(), capture['width'], capture['height']) == rgba(
                    captured.read_bytes(), capture['width'], capture['height'])
            except ValueError:
                image_cache[key] = False
        comparisons['texture_faces_match' if image_cache[key] else 'texture_faces_incomplete'] += 1
    export_checks = []
    if case.get('exports'):
        from scripts.model_submitted_pose import instance_materials, compare_pose
        bank, entry, segment = case['target']
        payload = ROOT / f'build/assets/models/us-bank-{bank:02x}/bundles/{entry:04d}/segment-{segment:02d}.bin'
        geometry = models.parse_character_model_geometry(payload.read_bytes())[0]
        for export in case['exports']:
            root = int(export['palette_root'], 0)
            selected = instance_materials(case, normalized_sha1, reference, root, geometry)
            textured = models.apply_runtime_texture_coordinates(geometry, selected)
            export_checks.append({**export, **compare_pose(ROOT / export['path'], reference, root, textured, selected)})
    scope = ('rig and posed exports checked against the same submitted vertex inputs; native raster parity incomplete'
             if export_checks else 'rig evaluated under captured vertex-load matrices; not an aligned posed export or raster proof')
    return {'status': 'passed', 'submitted_exports': export_checks, 'scope': scope,
            'selected_call': reference['selected_call'],
            'model_sha1': inputs['model_sha1'], 'source_face_count': len(faces),
            'submitted_instance_count': len(instances), 'submitted_face_count': len(matches),
            'submitted_corner_count': len(matches) * 3, 'matched_cluster_count': reference['matched_cluster_count'],
            'max_local_coordinate_error': max(row['local_error'] for row in matches),
            'local_coordinate_tolerance': LOCAL_TOLERANCE,
            'max_world_coordinate_error': max(row['world_error'] for row in matches),
            'instances': [{'palette_root': f'0x{root:08X}', 'face_count': len(rows),
                           'captured_segment_3_bases': [f'0x{base:08X}' for base in sorted({
                               c['segment_base'] for row in rows for c in row['corners']})],
                           'source_faces': sorted(row['face'] for row in rows)} for root, rows in sorted(instances.items())],
            'material_comparison': {'status': 'incomplete', 'counts': dict(comparisons),
                                    'scope': 'bound pixels, culling and alpha mode; UV sampling, combiner constants, lighting and raster parity remain separate'},
            'native_visual_parity': {'status': 'incomplete'}}
