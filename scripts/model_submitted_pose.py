"""Export and check character poses from one hash-checked graphics submission.

Instance identity comes from per-corner palette addresses. Renderer-return
palettes from another capture are never paired with this task's materials.
"""

from __future__ import annotations

import json
import hashlib
import sys
from pathlib import Path
from urllib.parse import unquote

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from scripts import model_assets as models, model_runtime_validation as runtime
from scripts.model_preview_evidence import preview_fingerprint


def source_corners(row: dict) -> list:
    rotation = row['rotation']
    corners = row['corners']
    return corners[-rotation:] + corners[:-rotation] if rotation else corners


def instance_palette(reference: dict, root: int) -> dict:
    matrices = {}
    for row in reference['instances'][root]:
        for actual, expected in zip(source_corners(row), reference['faces'][row['face']]['corners']):
            slot = expected['joint']
            if slot in matrices and matrices[slot] != actual['matrix']:
                raise ValueError('one submitted instance changes a joint matrix between vertex loads')
            matrices[slot] = actual['matrix']
            if (len(actual['matrix']) != 4 or any(len(r) != 4 for r in actual['matrix'])
                    or [r[3] for r in actual['matrix']] != [0, 0, 0, 1]):
                raise ValueError('submitted pose matrix is not affine')
    if not matrices:
        raise ValueError('submitted pose has no captured joint matrices')
    return matrices


def verify_material_samples(record: dict, reference: dict, geometry,
                            require_captured_images: bool = True) -> None:
    rdp = reference['event']['state']['rdp']
    sources = models.captured_vertex_sources(reference['event'])
    if len(record['variants']) != 1:
        raise ValueError('submitted material has conflicting variants')
    for evidence in record['variants'][0]['evidence']:
        draw = rdp['draw_runs'][evidence['draw_run_index']]
        if evidence['source_material_state_hash'] != draw['material_state_hash']:
            raise ValueError('submitted material belongs to another draw')
        evidence['face_culling'] = draw['replayed_face_culling']
        fresh = models.replay_draw_vertex_colours(
            draw, rdp['replayed_vertex_loads'], sources, geometry, evidence['source_first_face'])
        if fresh is None or fresh != evidence.get('vertex_lighting'):
            raise ValueError('submitted colour evidence differs from captured vertex-load replay')
    if require_captured_images and models.runtime_material_references_texels(record) is not False and models.runtime_captured_texture_choice(record) is None:
        raise ValueError('submitted textured material has no unique captured image')


def instance_materials(case: dict, digest: str, reference: dict, root: int,
                       geometry) -> dict:
    draws = {row['draw'] for row in reference['instances'][root]}
    catalog = models.load_runtime_material_catalog(
        ROOT / case['materials'], digest, (0, case['event_index']), draw_indices=draws)
    selected = {key[3]: record for key, record in catalog.items() if key[:3] == tuple(case['target'])}
    for index, run in enumerate(geometry.material_runs):
        record = selected.get(index)
        if record is None:
            raise ValueError(f'submitted material {index} is absent')
        verify_material_samples(record, reference, geometry)
        colours = models.runtime_vertex_colour_map(record)
        if set(colours) != set(range(run.first_face, run.first_face + run.face_count)):
            raise ValueError('submitted material has incomplete per-face colour evidence')
    if set(selected) != set(range(len(geometry.material_runs))):
        raise ValueError('submitted material coverage differs from source model')
    return selected


def compare_pose(path: Path, reference: dict, root: int, geometry, materials: dict,
                 origin: list | None = None, require_captured_images: bool = True) -> dict:
    """Check emitted corners against raw captured vertices and fixed matrices.

    UV and colour checks separately establish exporter consistency with the
    captured tile state and replayed lighting. They are not RSP raster proof.
    """
    from scripts.model_validation import accessor, float32, rgba

    preview_fingerprint(path)
    document = json.loads(path.read_text())
    if (reference.get('selected_call') is not None and document.get('extras', {}).get(
            'submittedPose', {}).get('selectedCall') != reference['selected_call']):
        raise ValueError('submitted pose selected-call evidence changed or is missing')
    if document.get('skins') or document.get('animations') or any(
            any(k in node for k in ('matrix', 'translation', 'rotation', 'scale'))
            for node in document['nodes']):
        raise ValueError('submitted baked pose contains unexpected transforms')
    buffers = [(path.parent / unquote(b['uri'])).read_bytes() for b in document['buffers']]
    rows = {row['face']: row for row in reference['instances'][root]}
    palette = instance_palette(reference, root)
    origin = palette[min(palette)][3][:3] if origin is None else origin
    seen = set()
    max_error = 0.0
    uv_count = colour_count = 0
    collapsed_faces = 0
    compared_images = set()
    unresolved_image_faces = set()
    for mesh in document['meshes']:
        for primitive in mesh['primitives']:
            if primitive.get('mode', 4) != 4 or primitive.get('targets'):
                raise ValueError('submitted pose is not a plain triangle mesh')
            material = document['materials'][primitive['material']]
            run_index = material['extras']['materialRun']
            run = geometry.material_runs[run_index]
            record = materials[run_index]
            consensus = models.runtime_material_consensus(record)
            colours = models.runtime_vertex_colour_map(record)
            factor = consensus['baseColorFactor'] or [1.0] * 4
            if material['pbrMetallicRoughness']['baseColorFactor'] != factor:
                raise ValueError('submitted combiner colour factor changed')
            if 'KHR_materials_unlit' not in material.get('extensions', {}):
                raise ValueError('submitted baked lighting would be lit a second time')
            attrs = {k: accessor(document, v, buffers) for k, v in primitive['attributes'].items()}
            indices = [r[0] for r in accessor(document, primitive['indices'], buffers)]
            first, count = primitive['extras']['firstFace'], primitive['extras']['faceCount']
            if count * 3 != len(indices):
                raise ValueError('submitted primitive face extent changed')
            if not run.first_face <= first < first + count <= run.first_face + run.face_count:
                raise ValueError('submitted primitive exceeds its source material')
            capture = record['variants'][0].get('captured_texture')
            texels = models.runtime_material_references_texels(record)
            binding = material.get('pbrMetallicRoughness', {}).get('baseColorTexture')
            if texels is False:
                if binding:
                    raise ValueError('submitted untextured combiner acquired a texture')
            elif not capture and not require_captured_images:
                unresolved_image_faces.update(range(first, first + count))
            elif run_index not in compared_images:
                if not binding or not capture:
                    raise ValueError('submitted texture binding is absent')
                image = document['images'][document['textures'][binding['index']]['source']]
                sampler = document['samplers'][document['textures'][binding['index']]['sampler']]
                address_mode = models.texture_address_mode(run)['gltf']
                filtering = consensus['sampler'] or {'magFilter': 9729, 'minFilter': 9987}
                expected_sampler = {key: address_mode[key] for key in ('wrapS', 'wrapT')}
                expected_sampler.update(filtering)
                if sampler != expected_sampler:
                    raise ValueError('submitted sampler differs from captured tile state')
                actual = (path.parent / unquote(image['uri'])).read_bytes()
                expected = models._validated_preview_source(record['_source_root'], capture['file']).read_bytes()
                if rgba(actual, capture['width'], capture['height']) != rgba(expected, capture['width'], capture['height']):
                    raise ValueError('submitted texture pixels differ from captured image')
                compared_images.add(run_index)
            for offset in range(count):
                face = first + offset
                source_face = geometry.face_source_indices[face] if geometry.face_source_indices else face
                if face in seen or face not in rows:
                    raise ValueError('submitted source face coverage changed')
                seen.add(face)
                row = rows[face]
                draw = reference['event']['state']['rdp']['draw_runs'][row['draw']]
                culling = draw['replayed_face_culling']
                if culling['known_bits'] != 0x600 or culling['mode'] not in (0, 0x400):
                    raise ValueError('submitted culling cannot be represented by glTF')
                if material.get('doubleSided', False) != (culling['mode'] == 0):
                    raise ValueError(f'submitted face {face} culling differs from captured draw: {material.get("doubleSided")} vs {culling["mode"]:#x}')
                other = models.decode_other_mode(tuple(draw['state']['other_mode']))
                if material.get('alphaMode', 'OPAQUE') != other['gltf_alpha_mode']:
                    raise ValueError('submitted alpha mode differs from captured draw')
                positions = [attrs['POSITION'][i] for i in indices[offset * 3:offset * 3 + 3]]
                if not any(models._triangle_cross(tuple(positions))):
                    collapsed_faces += 1
                for corner, (i, actual) in enumerate(zip(indices[offset * 3:offset * 3 + 3], source_corners(row))):
                    expected = tuple(sum(actual['xyz'][k] * actual['matrix'][k][axis] for k in range(3))
                                     + actual['matrix'][3][axis] - origin[axis] for axis in range(3))
                    max_error = max(max_error, max(abs(a - b) for a, b in zip(attrs['POSITION'][i], expected)))
                    if attrs['POSITION'][i] != float32(expected):
                        raise ValueError('submitted pose vertex differs from its captured matrix transform')
                    if run.texture_enabled and run.texture_coordinates_proven:
                        vertex = geometry.vertices[geometry.faces[face][corner]]
                        if (vertex.s, vertex.t) != tuple(actual['st']):
                            raise ValueError('submitted texture coordinates differ from source VTX bytes')
                        if attrs.get('TEXCOORD_0', [None] * len(attrs['POSITION']))[i] != float32(models.texture_coordinates(vertex, run)):
                            raise ValueError('submitted UV differs from captured tile-coordinate replay')
                        uv_count += 1
                    if consensus['exact'] and consensus['usesVertexColor'] is False:
                        if 'COLOR_0' in attrs:
                            raise ValueError('submitted constant-colour combiner acquired vertex colours')
                    else:
                        colour = colours[source_face][corner]
                        if models.is_character_trilinear_base(run) or (consensus['baseColorFactor'] is not None and consensus['vertexAlphaMode'] == 'one'):
                            colour = (*colour[:3], 1.0)
                        if attrs.get('COLOR_0', [None] * len(attrs['POSITION']))[i] != float32(colour):
                            raise ValueError('submitted vertex colour differs from captured lighting replay')
                        colour_count += 1
    if seen != set(rows):
        raise ValueError('submitted pose omits source faces')
    return {'status': 'passed', 'face_count': len(seen), 'corner_count': len(seen) * 3,
            'max_float32_position_error': max_error, 'uv_corner_count': uv_count,
            'colour_corner_count': colour_count, 'captured_image_count': len(compared_images),
            'captured_texture_status': 'incomplete' if unresolved_image_faces else 'passed',
            'unresolved_texture_face_count': len(unresolved_image_faces),
            'collapsed_face_count': collapsed_faces,
            'zero_scale_matrix_slots': sorted(slot for slot, matrix in palette.items()
                                             if not any(v for r in matrix[:3] for v in r[:3])),
            'scope': 'same-submission matrix transforms, UV and lighting replay, available captured pixels, culling and alpha; unresolved texture coverage reported separately; native raster parity incomplete'}


def export_cases(config_path: Path) -> dict:
    config = json.loads(config_path.read_text())
    digest, inventory = models.runtime_material_inventory('us', None)
    clusters = models.load_model_cluster_index()
    records = []
    for case in config.get('runtime_draw_cases', []):
        if not case.get('exports'):
            continue
        target = tuple(case['target'])
        if target[0] != 1:
            raise ValueError('submitted pose currently requires a character rig')
        hashes = {row['model_sha1'] for key, row in inventory.items() if key[:3] == target}
        if len(hashes) != 1:
            raise ValueError('submitted case does not identify one ROM model')
        sha = next(iter(hashes))
        inputs = runtime.runtime_inputs({k: v for k, v in case.items() if k != 'exports'}, sha, clusters)
        reference = runtime.submitted_rig_reference(case, digest, inputs)
        # This also verifies the catalog and its exact source trace identity.
        runtime.compare_submitted_rig({k: v for k, v in case.items() if k != 'exports'}, digest, inputs)
        payload = ROOT / f'build/assets/models/us-bank-01/bundles/{target[1]:04d}/segment-{target[2]:02d}.bin'
        geometry = models.parse_character_model_geometry(payload.read_bytes())[0]
        for export in case['exports']:
            root = int(export['palette_root'], 0)
            matrices = instance_palette(reference, root)
            materials = instance_materials(case, digest, reference, root, geometry)
            path = ROOT / export['path']
            if path.suffix != '.gltf' or not path.resolve().is_relative_to(ROOT / 'build/assets/models'):
                raise ValueError('submitted export must be a glTF under build/assets/models')
            path.parent.mkdir(parents=True, exist_ok=True)
            texture_files = {}
            for index, record in materials.items():
                texture = models.runtime_captured_texture_choice(record)
                if texture is not None:
                    filename = models.preview_texture_filename(texture)
                    destination = path.parent.parent / 'textures' / filename
                    destination.parent.mkdir(parents=True, exist_ok=True)
                    destination.write_bytes(texture.source.read_bytes())
                    texture_files[index] = '../textures/' + filename
                models.copy_runtime_captured_auxiliary_textures(record, path.parent.parent)
            textured = models.apply_runtime_texture_coordinates(geometry, materials)
            posed = models.bake_character_runtime_pose(textured, matrices, matrices[min(matrices)][3][:3])
            gltf, binary = models.encode_gltf(target[1], target[2], posed, texture_files=texture_files,
                                            bank_index=1, output_stem=path.stem, runtime_materials=materials)
            document = json.loads(gltf)
            document.setdefault('extras', {})['submittedPose'] = {
                'traceSha256': inputs['dependencies'][str(ROOT / case['trace'])],
                'eventIndex': case['event_index'], 'paletteRoot': export['palette_root'],
                'origin': matrices[min(matrices)][3][:3], 'originMatrixSlot': min(matrices),
                'coordinateSpace': 'captured-model-view-centered-on-lowest-used-slot',
                'nativeVisualParity': 'incomplete'}
            if reference.get('selected_call') is not None:
                document['extras']['submittedPose']['selectedCall'] = reference['selected_call']
            path.with_suffix('.bin').write_bytes(binary)
            path.write_text(json.dumps(document, indent=2) + '\n')
            check = compare_pose(path, reference, root, textured, materials)
            records.append({'case': case['id'], **export, **check,
                            'selected_call': reference.get('selected_call'), 'fingerprint': preview_fingerprint(path)})
        if runtime.runtime_inputs({k: v for k, v in case.items() if k != 'exports'}, sha, clusters) != inputs:
            raise ValueError('submitted pose inputs changed during export')
    return {'schema_version': 1, 'normalized_sha1': digest, 'models': records}


def compare_composition(case: dict, digest: str, inventory: dict, clusters: list) -> dict:
    """Verify a selected-part pose against its byte-paired submitted task."""
    target = tuple(case['target'])
    hashes = {r['model_sha1'] for k, r in inventory.items() if k[:3] == target}
    if len(hashes) != 1 or target[0] != 1:
        raise ValueError('submitted composition requires one ROM character model')
    sha = next(iter(hashes))
    input_case = {**case, 'exports': [{'path': case['path']}]}
    inputs = runtime.runtime_inputs(input_case, sha, clusters)
    _, _, _, bundles, _ = models.load_model_bundles('us', None, 1)
    validated = models.load_character_draw_trace(
        ROOT / case['trace'], digest, {k[1] for k in inventory if k[0] == 1},
        models.character_display_list_topology(bundles), clusters)
    calls = [c for c in validated['draw_calls'] if c['entry'] == target[1]
             and c['slot'] == case['slot'] and c['task_submission_index'] == case['task_submission_index']
             and c['render_pass']['kind'] == 'caller-managed-target']
    if len(calls) != 1:
        raise ValueError('submitted composition does not identify one ordinary renderer call')
    call = calls[0]
    submission = call.get('submitted_graphics')
    if not submission or submission['event_index'] != case['event_index']:
        raise ValueError('submitted composition lacks a matching graphics task')
    part_map = models.selected_part_material_candidates(validated, inventory)[case['event_index']]
    selected = {index: record['candidate'] for index, record in part_map.items()
                if record['evidence']['return_event_index'] == call['return_event_index']}
    source_faces = {i for candidate in selected.values() for i in range(
        candidate['static_first_face'], candidate['static_first_face'] + candidate['triangle_count'])}
    if len(source_faces) != case['expected_source_face_count']:
        raise ValueError('submitted composition selected face count changed')
    reference = runtime.submitted_rig_reference(case, digest, inputs,
        {'clusters': selected, 'source_faces': source_faces})
    root = call['root_matrix_address']
    sequence = models.resolve_character_call_from_part_selections(call['part_selections'])
    source = sequence['source_model']
    if tuple(source[k] for k in ('bank', 'entry', 'segment')) != target or source['model_sha1'] != sha:
        raise ValueError('submitted part sequence belongs to another source model')
    source_geometry = next(r['_geometry'] for k, r in inventory.items() if k[:3] == target)
    ordered = sorted(({**source, **cluster} for cluster in sequence['resolved_clusters']),
                     key=lambda c: c['static_cluster_index'])
    geometry = models.merge_character_composition_geometry({(*target, sha): source_geometry}, ordered)
    if len(geometry.faces) != len(source_faces):
        raise ValueError('submitted composition repeats selected source faces')
    source_to_output = {source_face: i for i, source_face in enumerate(geometry.face_source_indices)}
    reference['faces'] = {source_to_output[i]: reference['faces'][i] for i in source_faces}
    reference['instances'][root] = [{**row, 'face': source_to_output[row['face']]}
                                    for row in reference['instances'][root]]
    material_path = ROOT / case['materials']
    manifest = json.loads(material_path.read_text())
    models.verify_runtime_material_output(material_path.parent, manifest)
    if (manifest['normalized_sha1'] != digest or len(manifest['source_traces']) != 1
            or manifest['source_traces'][0]['sha256'] != hashlib.sha256((ROOT / case['trace']).read_bytes()).hexdigest()):
        raise ValueError('submitted composition material catalog belongs to another capture')
    draws = {row['draw'] for row in reference['instances'][root]}
    catalog = models.load_runtime_material_catalog(material_path, digest, (0, case['event_index']), draw_indices=draws)
    materials = {}
    verified_runs = set()
    for i, cluster in enumerate(ordered):
        key = (*target, cluster['material_run'])
        record = catalog[key]
        current = inventory[key]
        if (record['model_sha1'], record['source_first_face'], record['source_face_count']) != (
                sha, current['first_face'], current['face_count']):
            raise ValueError('submitted composition material source identity changed')
        if key not in verified_runs:
            verify_material_samples(record, reference, source_geometry, require_captured_images=False)
            verified_runs.add(key)
        materials[i] = record
    geometry = models.apply_runtime_texture_coordinates(geometry, materials)
    matrices = {r['matrix_slot']: r for r in call['runtime_matrices']}
    origin_slot = 0 if 0 in matrices else min(models.geometry_vertex_matrix_indices(geometry))
    checked = compare_pose(ROOT / case['path'], reference, root, geometry, materials,
                           matrices[origin_slot]['translation'], require_captured_images=False)
    if checked['unresolved_texture_face_count'] != case.get('expected_unresolved_texture_face_count', 0):
        raise ValueError('submitted composition captured texture coverage changed')
    if runtime.runtime_inputs(input_case, sha, clusters) != inputs:
        raise ValueError('submitted composition inputs changed during comparison')
    return {**checked, 'selected_cluster_count': len(selected),
            'submitted_event_index': case['event_index'], 'return_event_index': call['return_event_index']}


def discovery_plans(context: dict | None, event_index: int, previous_boundary: int,
                    targets: set[tuple]) -> list[dict]:
    """Prefer attributed calls; retain task-wide discovery only for other draws."""
    plans, reserved = [], set()
    unknown_source = False
    for call in context['trace']['draw_calls'] if context is not None else []:
        submission = call.get('submitted_graphics', {})
        paired = submission.get('event_index') == event_index
        pending = not submission and previous_boundary < call['return_event_index'] < event_index
        if not paired and not pending:
            continue
        plan = {'draw_call': runtime.draw_call_selector(call)}
        sequence = models.resolve_character_call_from_part_selections(call.get('part_selections', []))
        if sequence is not None:
            target = tuple(sequence['source_model'][key] for key in ('bank', 'entry', 'segment'))
            reserved.add(target)
            plan['target'] = list(target)
        else:
            candidates = {tuple(c[key] for key in ('bank', 'entry', 'segment'))
                          for r in call.get('model_correlations', []) for c in r.get('candidates', [])}
            reserved.update(candidates)
            unknown_source |= not candidates
            plan['reason'] = 'renderer-selected ROM parts remain unresolved'
        if not paired or submission.get('status') != 'captured-range-executed-once-in-next-graphics-task':
            plan['reason'] = 'renderer call lacks a positive byte-paired graphics submission'
        plans.append(plan)
    # Do not turn missing attribution into a task-wide success for the same
    # source. Unrelated objects/effects without a character call remain eligible.
    if not unknown_source:
        plans.extend({'target': list(target)} for target in sorted(targets - reserved))
    return plans


def discover_cases(trace_path: Path, material_path: Path, model_root: Path) -> dict:
    """Find complete captured instances; report each unresolved input explicitly."""
    from scripts.mupen_trace import captured_task_type

    digest, inventory = models.runtime_material_inventory('us', None)
    clusters = models.load_model_cluster_index()
    manifest = json.loads(material_path.read_text())
    lines = [json.loads(line) for line in trace_path.read_text().splitlines() if line.strip()]
    if not lines or lines[0].get('normalized_sha1') != digest:
        raise ValueError('submitted discovery trace belongs to another ROM')
    models.verify_runtime_material_output(material_path.parent, manifest)
    if (manifest['normalized_sha1'] != digest or len(manifest['source_traces']) != 1
            or manifest['source_traces'][0]['sha256'] != hashlib.sha256(trace_path.read_bytes()).hexdigest()):
        raise ValueError('submitted discovery material catalog belongs to another capture')
    context = (runtime.load_submitted_call_context(trace_path, digest, inventory, clusters)
               if lines[0].get('spec_name') == 'character-model-draw-ranges' else None)
    events = [line for line in lines if line.get('record_type') == 'draw_state']
    records = []
    previous_boundary = -1
    for event_index, event in enumerate(events):
        if captured_task_type(event) != 1:
            continue
        # Audio boundaries do not consume pending renderer calls: the byte
        # pairing also searches for the next graphics task specifically.
        before = previous_boundary
        previous_boundary = event_index
        targets = {(r['bank'], r['entry'], r['segment']) for r in manifest['materials']
                          if r['bank'] == 1 and any(e['event_index'] == event_index
                              for v in r['variants'] for e in v['evidence'])}
        for plan in discovery_plans(context, event_index, before, targets):
            if 'reason' in plan:
                records.append({**plan, 'event_index': event_index, 'status': 'unresolved-call'})
                continue
            target = tuple(plan['target'])
            entry, segment = target[1:]
            source = model_root / 'us-bank-01-preview/geometry' / f'{entry:04d}-{segment:02d}-bind.gltf'
            if not source.is_file():
                source = source.with_name(f'{entry:04d}-{segment:02d}.gltf')
            case = {'id': f'{trace_path.stem}-event-{event_index:03d}-entry-{entry:04d}',
                    'target': list(target), 'event_index': event_index,
                    'source': models.display_path(source), 'trace': models.display_path(trace_path),
                    'materials': models.display_path(material_path)}
            if 'draw_call' in plan:
                case['draw_call'] = plan['draw_call']
                case['id'] += f"-return-{plan['draw_call']['return_event_index']:03d}"
            row = {'case': case, 'status': 'unresolved-rig'}
            try:
                hashes = {r['model_sha1'] for key, r in inventory.items() if key[:3] == target}
                if len(hashes) != 1:
                    raise ValueError('discovery target does not identify one ROM model')
                inputs = runtime.runtime_inputs(case, next(iter(hashes)), clusters)
                if 'draw_call' in case:
                    selection = runtime.select_submitted_call(case, inputs['model_sha1'], context)
                    row['selected_call'] = selection['evidence']
                    case['expected_instances'] = 1
                    case['palette_roots'] = [selection['evidence']['palette_root']]
                    _, faces = runtime.load_rig(source)
                    if selection['source_faces'] != set(faces):
                        reference = runtime.submitted_rig_reference(
                            {key: value for key, value in case.items() if key != 'draw_call'}, digest, inputs, selection)
                        instance_palette(reference, selection['root'])
                        row.update(status='partial-composition', source_face_count=len(faces),
                                   submitted_face_count=len(reference['matches']),
                                   reason='selected parts verified; complete-source export requires a composition')
                        records.append(row)
                        continue
                reference = runtime.submitted_rig_reference(case, digest, inputs, call_context=context)
                case['expected_instances'] = len(reference['instances'])
                case['palette_roots'] = [f'0x{root:08X}' for root in sorted(reference['instances'])]
                runtime.compare_submitted_rig(case, digest, inputs, call_context=context)
                row.update(status='rig-only', face_count=len(reference['faces']),
                           submitted_face_count=len(reference['matches']))
                geometry = next(r['_geometry'] for key, r in inventory.items() if key[:3] == target)
                for root in reference['instances']:
                    instance_palette(reference, root)
                    instance_materials(case, digest, reference, root, geometry)
                row['status'] = 'exportable'
            except (OSError, ValueError, KeyError, IndexError, TypeError) as error:
                row['reason'] = str(error)
            records.append(row)
    return {'schema_version': 1, 'family': 'submitted-model-discovery',
            'normalized_sha1': digest, 'candidates': records,
            'scope': 'Renderer calls separated by verified selected parts and submitted command bytes; '
                     'unattributed task draws checked separately. Partial compositions are not complete rigs. '
                     'Exportable does not establish native raster parity.'}
