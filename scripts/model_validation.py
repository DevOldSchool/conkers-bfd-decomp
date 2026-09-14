"""Cached ROM, glTF, runtime-image and render checks; missing proof is explicit."""

from __future__ import annotations

import hashlib
import html
import inspect
import json
import math
import shutil
import struct
import subprocess
import sys
from collections import Counter
from pathlib import Path
from urllib.parse import unquote

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts import model_assets as models, texture_assets as textures
from scripts.model_preview_evidence import preview_fingerprint
from scripts.model_evidence_cache import ContentSnapshot, source_identity
from scripts.mupen_trace import TraceError
from scripts.validate_model_previews_blender import collect_preview_records, collect_composition_records

VALIDATOR_VERSION = "2.0.0-dev.3.10"
COMPONENTS = {5120: ('b', 1), 5121: ('B', 1), 5122: ('h', 2), 5123: ('H', 2),
              5125: ('I', 4), 5126: ('f', 4)}
WIDTHS = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def identity(value) -> str:
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def read(path: Path):
    return json.loads(path.read_text())


def write(path: Path, value) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix(path.suffix + '.tmp')
    temporary.write_text(json.dumps(value, indent=2) + '\n')
    temporary.replace(path)


def cached(path: Path, key: str):
    try:
        item = read(path)
        if item.get('key') == key and item.get('result', {}).get('status') in ('passed', 'failed', 'incomplete'):
            return item['result']
    except (OSError, ValueError):
        pass
    return None


def checked(callable_):
    try:
        return {'status': 'passed', **(callable_() or {})}
    except (OSError, ValueError, KeyError, IndexError, TypeError, struct.error, TraceError) as error:
        return {'status': 'failed', 'error': str(error)}


def code_identity() -> dict:
    return source_identity(ROOT, ['scripts/model_validation.py'], digest)


def accessor(document: dict, index: int, buffers: list[bytes]) -> list[tuple]:
    item = document['accessors'][index]
    if 'sparse' in item:
        raise ValueError('sparse accessors require a separate numeric comparison')
    component, size = COMPONENTS[item['componentType']]
    width = WIDTHS[item['type']]
    view = document['bufferViews'][item['bufferView']]
    offset = item.get('byteOffset', 0)
    stride = view.get('byteStride', size * width)
    count = item['count']
    if count < 0 or offset < 0 or stride < size * width:
        raise ValueError('invalid accessor count, offset or stride')
    extent = offset + (count - 1) * stride + size * width if count else offset
    data = buffers[view['buffer']]
    base = view.get('byteOffset', 0)
    if base < 0 or extent > view['byteLength'] or base + view['byteLength'] > len(data):
        raise ValueError('accessor exceeds its buffer view')
    values = [struct.unpack_from('<' + component * width, data, base + offset + i * stride)
              for i in range(count)]
    if any(not math.isfinite(v) for row in values for v in row):
        raise ValueError('non-finite accessor value')
    return values


def float32(values) -> tuple:
    return struct.unpack('<' + 'f' * len(values), struct.pack('<' + 'f' * len(values), *values))


def verified_detail_preview_geometry(geometry, run_records: list[dict], flat: dict,
                                     runtime: dict, directory: Path):
    """Recompute a detail preview selection from ROM before accepting its UVs."""
    runs = []
    for index, run in enumerate(geometry.material_runs):
        record = run_records[index]
        evidence = record.get('rom_detail_texture_preview')
        expected = None
        captured = models.runtime_captured_texture_choice(runtime.get(index))
        if (captured is None and models.runtime_material_references_texels(runtime.get(index)) is not False
                and run.pixel is not None and run.pixel.image_command == 0xFD500000
                and run.detail_tile_bounds and run.face_count):
            payload = flat.get(run.pixel.flat_index)
            texture, status = (models.direct_detail_indexed_preview_texture(run, payload)
                               if payload is not None else (None, None))
            if texture is not None:
                run = models.replace(run, preview_coordinate_state=texture.preview_coordinate_state)
                expected = models.detail_texture_preview_record(run)
                source = record.get('texture')
                if (record.get('status') != status or not source
                        or source.get('source_family') != texture.family
                        or (source.get('width'), source.get('height')) != (texture.width, texture.height)
                        or models._validated_preview_source(directory, source['file']).read_bytes() != texture.png_data):
                    raise ValueError(f'ROM detail texture differs for run {index}')
        if evidence != expected:
            raise ValueError(f'ROM detail preview selection differs for run {index}')
        if record.get('status') == 'direct-detail-indexed-base' and expected is None:
            raise ValueError(f'ROM detail preview has no source proof for run {index}')
        runs.append(run)
    return models.replace(geometry, material_runs=tuple(runs))


def compare_geometry(path: Path, geometry, joints, run_records: list[dict], morph_record: dict | None = None,
                     draw_pass: dict | None = None, *, flat_payloads: dict | None = None,
                     runtime_materials: dict | None = None, preview_root: Path | None = None,
                     attachment_update: dict | None = None) -> dict:
    """Compare emitted corner order/positions/UVs/joints with decoded source data.

    This is exporter consistency, not an independent proof of the ROM decoder.
    It reads the actual glTF buffers, never a second call to encode_gltf.
    """
    document = read(path)
    if document.get('extras', {}).get('romAttachmentUpdate') != attachment_update:
        raise ValueError('exported attachment texture/UV update differs from ROM')
    if flat_payloads is not None:
        geometry = verified_detail_preview_geometry(geometry, run_records, flat_payloads,
                                                   runtime_materials or {}, preview_root or path.parent)
        geometry = models.apply_runtime_texture_coordinates(geometry, runtime_materials or {})
    if document.get('extras', {}).get('romCharacterDrawPass') != draw_pass:
        raise ValueError('exported character draw-pass selection differs from ROM')
    preview_fingerprint(path)  # Validate dependency locality before opening buffers.
    buffers = [(path.parent / unquote(b['uri'])).read_bytes() for b in document.get('buffers', [])]
    models.verify_gltf_material_spans(document, run_records)
    for material in document.get('materials', []):
        extras = material.get('extras', {})
        index = extras.get('materialRun')
        if isinstance(index, int) and extras.get('romTextureStateConsensus') != run_records[index].get('rom_texture_state_consensus'):
            raise ValueError('exported ROM texture-state evidence differs from source')
        if isinstance(index, int) and extras.get('romObjectTextureAnimation') != run_records[index].get('rom_object_texture_animation'):
            raise ValueError('exported ROM texture-animation evidence differs from source')
        if isinstance(index, int) and extras.get('romObjectTextureBinding') != run_records[index].get('rom_object_texture_binding'):
            raise ValueError('glTF ROM object texture binding differs from manifest')
        if isinstance(index, int) and extras.get('romSceneTextureState') != run_records[index].get('rom_scene_texture_state'):
            raise ValueError('exported ROM scene texture evidence differs from source')
        if isinstance(index, int):
            run = geometry.material_runs[index]
            detail = (models.detail_texture_preview_record(run)
                      if run.preview_coordinate_state is not None else None)
            if extras.get('romDetailTexturePreview') != detail:
                raise ValueError('exported ROM detail preview evidence differs from source')
            if detail is not None:
                texture_index = material['pbrMetallicRoughness']['baseColorTexture']['index']
                image = document['images'][document['textures'][texture_index]['source']]
                actual = (path.parent / unquote(image['uri'])).resolve()
                source = models._validated_preview_source(preview_root or path.parent, run_records[index]['texture']['file'])
                if actual != source.resolve():
                    raise ValueError('exported ROM detail image binding differs from source')
    expected = models.validation_face_records(geometry, joints)
    morph_deltas = models.model_morphs.target_deltas(morph_record, geometry) if morph_record else []
    morph_info = document.get('extras', {}).get('romMorphTargets')
    if morph_record:
        if not morph_info or any(morph_info.get(key) != value for key, value in {
                'sourceSha1': morph_record['source_sha1'], 'modelSha1': morph_record['model_sha1'],
                'shapeCount': len(morph_deltas), 'vertexStarts': morph_record['vertex_starts'],
                'partVertexCounts': morph_record['part_vertex_counts']}.items()):
            raise ValueError('exported morph provenance differs from ROM')
    elif morph_info:
        raise ValueError('unexpected morph targets without a ROM source record')
    cursor = uv_corners = joint_corners = morph_corners = 0
    for mesh in document.get('meshes', []):
        if morph_record and (mesh.get('weights') != [0.0] * len(morph_deltas)
                or mesh.get('extras', {}).get('targetNames') != [target['name'] for target in morph_record['targets']]):
            raise ValueError('morph names or neutral default weights changed')
        for primitive in mesh['primitives']:
            if primitive.get('mode', 4) != 4:
                raise ValueError('source triangle export changed primitive mode')
            attrs = {name: accessor(document, i, buffers) for name, i in primitive['attributes'].items()}
            targets = primitive.get('targets', [])
            if len(targets) != len(morph_deltas) or any(set(target) != {'POSITION'} for target in targets):
                raise ValueError('morph target count or attributes changed')
            morph_values = [accessor(document, target['POSITION'], buffers) for target in targets]
            if any(len(values) != len(attrs['POSITION']) for values in morph_values):
                raise ValueError('morph accessor does not cover the base vertices')
            indices = [v[0] for v in accessor(document, primitive['indices'], buffers)]
            if len(indices) % 3:
                raise ValueError('incomplete exported triangle')
            run_index = document['materials'][primitive['material']]['extras']['materialRun']
            run = geometry.material_runs[run_index]
            for offset in range(0, len(indices), 3):
                face = expected[cursor]
                if face['run_index'] != run_index:
                    raise ValueError(f'face {cursor}: material assignment changed')
                for corner, index in enumerate(indices[offset:offset + 3]):
                    if index < 0 or index >= len(attrs['POSITION']):
                        raise ValueError(f'face {cursor}: invalid vertex index {index}')
                    if attrs['POSITION'][index] != float32(face['positions'][corner]):
                        raise ValueError(f'face {cursor} corner {corner}: position differs from ROM bind geometry')
                    for deltas, values in zip(morph_deltas, morph_values):
                        wanted = float32(deltas.get(face['source_indices'][corner], (0, 0, 0)))
                        if values[index] != wanted:
                            raise ValueError(f'face {cursor} corner {corner}: morph delta differs from ROM')
                        morph_corners += 1
                    if 'TEXCOORD_0' in attrs:
                        vertex = geometry.vertices[face['source_indices'][corner]]
                        uv = float32(models.texture_coordinates(vertex, run))
                        if attrs['TEXCOORD_0'][index] != uv:
                            raise ValueError(f'face {cursor} corner {corner}: UV differs from selected coordinate state')
                        uv_corners += 1
                    if joints:
                        wanted = (face['vertex_matrix_indices'][corner], 0, 0, 0)
                        if attrs.get('JOINTS_0', [])[index] != wanted:
                            raise ValueError(f'face {cursor} corner {corner}: vertex-load joint differs')
                        if attrs.get('WEIGHTS_0', [])[index] != (1.0, 0.0, 0.0, 0.0):
                            raise ValueError(f'face {cursor} corner {corner}: rigid weights differ')
                        joint_corners += 1
                cursor += 1
    if cursor != len(expected):
        raise ValueError('exported triangle count differs from decoded source')
    return {'faces': cursor, 'uv_corners': uv_corners, 'joint_corners': joint_corners,
            'morph_target_count': len(morph_deltas), 'morph_corners': morph_corners,
            'scope': 'ROM-decoder-to-export consistency; native rendering unverified'}


def rgba(png: bytes, width: int, height: int) -> bytes:
    depth, kind = png[24:26]
    if kind == 6:
        return textures.decode_rgba_png_pixels(png, width, height)
    if kind != 3 or depth not in (4, 8):
        raise ValueError('unsupported comparison PNG format')
    decode = textures.decode_indexed_png if depth == 4 else textures.decode_ci8_png
    payload = decode(png, 'linear', width, height)
    return textures.indexed_payload_rgba(payload, depth, 'linear', width, height)


def compare_images(reference: Path, current: Path, difference: Path) -> dict:
    before, after = reference.read_bytes(), current.read_bytes()
    if before[:8] != b'\x89PNG\r\n\x1a\n' or after[:8] != before[:8]:
        raise ValueError('image comparison requires PNG files')
    width, height = struct.unpack('>II', before[16:24])
    if (width, height) != struct.unpack('>II', after[16:24]):
        return {'status': 'failed', 'reason': 'image-dimensions-changed'}
    left, right = rgba(before, width, height), rgba(after, width, height)
    changed = sum(left[i:i + 4] != right[i:i + 4] for i in range(0, len(left), 4))
    result = {'status': 'passed' if not changed else 'incomplete',
              'reason': 'unchanged-regression-image' if not changed else 'changed-image-needs-review',
              'changed_pixels': changed, 'pixel_count': width * height,
              'max_channel_delta': max((abs(a - b) for a, b in zip(left, right)), default=0),
              'reference_sha256': digest(reference), 'current_sha256': digest(current),
              'scope': 'regression comparison; not native visual parity'}
    if changed:
        pixels = b''.join(bytes((255, min(255, max(abs(a - b) for a, b in
                         zip(left[i:i + 4], right[i:i + 4])) * 4), 0, 255))
                         if left[i:i + 4] != right[i:i + 4] else bytes((0, 0, 0, 255))
                         for i in range(0, len(left), 4))
        difference.parent.mkdir(parents=True, exist_ok=True)
        difference.write_bytes(textures.encode_rgba_png(width, height, pixels))
        result['difference_image'] = str(difference)
    return result


def image_comparison_identity() -> dict:
    # Model constructor/export edits do not change PNG comparison semantics.
    return {'functions': {f.__name__: inspect.getsource(f) for f in
                          (compare_images, rgba, digest)},
            'dependencies': source_identity(ROOT, ['scripts/texture_assets.py'], digest)}


def cached_image_comparison(reference, current, difference, cache_root, snapshot, code):
    inputs = {'reference': snapshot.digest(reference), 'current': snapshot.digest(current),
              'difference': str(difference)}
    key = identity({'code': code, 'inputs': inputs})
    destination = cache_root / 'image-comparisons' / (key + '.json')
    result = cached(destination, key)
    if result and result.get('difference_image'):
        image = Path(result['difference_image'])
        if (image != difference or not image.is_file()
                or digest(image) != read(destination).get('difference_sha256')):
            result = None
    if result is not None:
        return {**result, 'cached': True}
    result = checked(lambda: compare_images(reference, current, difference))
    for field in ('reference', 'current'):
        if result.get(field + '_sha256', inputs[field]) != inputs[field]:
            return {'status': 'failed', 'reason': 'image-changed-during-comparison', 'cached': False}
    record = {'key': key, 'result': result}
    if result.get('difference_image'):
        # The comparison may just have regenerated a missing/corrupt artifact.
        record['difference_sha256'] = digest(difference)
    write(destination, record)
    return {**result, 'cached': False}


def capture_comparisons(path: Path, inventory: dict, flat: dict, catalog: dict) -> dict:
    manifest = read(path)
    models.verify_runtime_material_output(path.parent, manifest)
    for trace in manifest['source_traces']:
        if digest(ROOT / trace['file']) != trace['sha256']:
            raise ValueError(f'captured trace changed: {trace["file"]}')
    observations = []
    for record in manifest['materials']:
        key = tuple(record[k] for k in ('bank', 'entry', 'segment', 'material_run'))
        source = inventory[key]
        for field, source_field in (('model_sha1', 'model_sha1'),
                                    ('source_first_face', 'first_face'), ('source_face_count', 'face_count')):
            if record[field] != source[source_field]:
                raise ValueError(f'{key}: runtime source identity or face span changed')
        run = source['_run']
        static, status = models.choose_preview_texture(run, catalog, flat)
        for variant in record['variants']:
            captured = variant.get('captured_texture')
            row = {'model_key': f'{key[0]:02x}:{key[1]:04d}:{key[2]:02d}',
                   'material_run': key[3], 'variant': variant['material_state_hash']}
            reason = None
            if captured is None:
                reason = 'no-captured-image'
            elif static is None:
                reason = status
            elif (static.width, static.height) != (captured['width'], captured['height']):
                reason = 'different-runtime-image-dimensions'
            elif {(0, 2): 'rgba16', (0, 3): 'rgba32', (2, 0): 'ci4', (2, 1): 'ci8',
                  (3, 0): 'ia4', (3, 1): 'ia8', (3, 2): 'ia16', (4, 0): 'i4',
                  (4, 1): 'i8'}.get((static.format, static.size)) != captured.get('format'):
                reason = 'different-runtime-render-format'
            elif captured.get('source_byte_offset', 0) != (static.pixel_byte_offset or 0):
                reason = 'different-runtime-pixel-window'
            elif run.pixel is None or run.pixel.flat_index not in flat:
                reason = 'no-static-pixel-source'
            else:
                payload = flat[run.pixel.flat_index]
                if not captured_pixel_prefix_matches(run, static, captured, variant['state'], payload):
                    reason = 'different-runtime-pixel-source'
                if captured.get('format') in ('ci4', 'ci8'):
                    length = 32 if captured['format'] == 'ci4' else 512
                    if captured.get('palette_sha256') != hashlib.sha256(payload[-length:]).hexdigest():
                        reason = 'different-runtime-palette'
            if reason:
                observations.append({**row, 'status': 'incomplete', 'reason': reason})
                continue
            actual_path = models._validated_preview_source(path.parent, captured['file'])
            actual = actual_path.read_bytes()
            if hashlib.sha1(actual).hexdigest() != captured['png_sha1']:
                raise ValueError(f'{key}: captured image hash changed')
            wanted = static.png_data if static.png_data is not None else static.source.read_bytes()
            same = rgba(wanted, static.width, static.height) == rgba(actual, static.width, static.height)
            observations.append({**row, 'status': 'passed' if same else 'failed',
                                 'reason': 'captured-pixels-match' if same else 'captured-pixels-disagree'})
    counts = dict(Counter(row['status'] for row in observations))
    return {'status': 'failed' if counts.get('failed') else
            'incomplete' if counts.get('incomplete') or not counts.get('passed') else 'passed', 'counts': counts,
            'observations': observations, 'scope': 'same-source captured texture pixels; excludes native raster parity'}


def captured_pixel_prefix_matches(run, texture, captured: dict, state: dict, payload: bytes) -> bool:
    """Compare the actual captured LoadBlock extent, excluding a separate TLUT."""
    pixel_image = (state.get('texture') or {}).get('pixel_image') or {}
    length = pixel_image.get('byte_length')
    if not isinstance(length, int) or not 0 < length <= len(payload):
        return False
    row_bytes = (texture.width * (4 << texture.size) + 7) // 8
    stride = ((run.render_tile[0] >> 9) & 0x1FF) * 8 or row_bytes
    if (texture.format, texture.size) == (0, 3):
        stride *= 2
    end = (texture.pixel_byte_offset or 0) + (texture.height - 1) * stride + row_bytes
    return (end <= length and pixel_image.get('sha256') == captured.get('pixel_sha256')
            and hashlib.sha256(payload[:length]).hexdigest() == captured['pixel_sha256'])


def run_logged(args: list[str], log: Path) -> int:
    with log.open('w') as stream:
        return subprocess.run(args, cwd=ROOT, stdout=stream, stderr=subprocess.STDOUT).returncode


def blender_worker(request_path: Path) -> None:
    import bpy
    from scripts.validate_model_previews_blender import main as validate
    from scripts.render_model_preview_blender import main as render
    request = read(request_path)
    scratch = request_path.parent / 'blender-single.json'
    single_output = request_path.parent / 'blender-single-result.json'
    for record in request['files']:
        write(scratch, [record])
        try:
            validate(['--records', str(scratch), '--output', str(single_output)])
            if read(single_output)['files'][0]['fingerprint'] != record['fingerprint']:
                raise ValueError('preview changed between scheduling and Blender import')
            result = {'status': 'passed', 'blender_version': bpy.app.version_string,
                      'validation': read(single_output)['files'][0]}
        except Exception as error:
            result = {'status': 'failed', 'error': str(error)}
        write(Path(record['output']), {'key': record['key'], 'result': result})
    for case in request['renders']:
        try:
            if preview_fingerprint(Path(case['path'])) != case['fingerprint']:
                raise ValueError('preview changed before rendering')
            render(['--input', case['path'], '--output', case['image'],
                    '--view', case['view'], '--shading', case['shading'], '--size', str(case['size'])])
            if preview_fingerprint(Path(case['path'])) != case['fingerprint']:
                raise ValueError('preview changed during rendering')
            result = {'status': 'passed', 'blender_version': bpy.app.version_string,
                      'image': case['image'], 'image_sha256': digest(Path(case['image']))}
        except Exception as error:
            result = {'status': 'failed', 'error': str(error)}
        write(Path(case['output']), {'key': case['key'], 'result': result})


def summarize_status(checks: dict) -> str:
    states = {item['status'] for item in checks.values()}
    return 'failed' if 'failed' in states else 'incomplete' if not states or 'incomplete' in states else 'passed'


def evidence_checks(model: dict, runs: list[dict]) -> dict:
    """An observed material or valid import cannot fill another evidence gap."""
    result = {}
    for dimension in ('static_texture', 'runtime_material', 'dynamic_segment_8',
                      'character_composition', 'attachment_composition'):
        counts = Counter(run[dimension]['status'] for run in runs)
        result[dimension] = {'status': 'incomplete' if any(state in counts for state in
            ('missing', 'unobserved', 'partial')) else 'passed', 'counts': dict(counts)}
    for dimension in ('scene_association', 'semantic_name'):
        state = model[dimension]['status']
        result[dimension] = {'status': 'passed' if state in ('resolved', 'known') else 'incomplete',
                             'evidence': state}
    return result


def compare_rom_object_materials(path: Path, flat: dict, catalog: dict, runtime: dict) -> dict:
    manifest = read(path)
    bank = manifest['bank_index']
    if bank not in (3, 4, 9):
        raise ValueError('object material proof requires bank 03, 04 or 09')
    _, _, digest_rom, bundles, tables = models.load_model_bundles('us', None, bank)
    context = models.load_object_material_context('us', None, digest_rom, bank)
    if manifest.get('rom_object_material_context') != context:
        raise ValueError('exported object material provenance differs from ROM')
    contexts = {(r['bank'], r['entry'], r['segment']): r for r in context['models']}
    records = {(r['bank_entry'], r['segment']): r for r in manifest['models']}
    linked = faces = 0
    for bundle in bundles:
        for segment in bundle.segments:
            if not segment.data:
                continue
            geometry = models.parse_segment_geometry(segment, bank)
            key = (bank, bundle.index, segment.index)
            material_records = {i: runtime[(*key, i)] for i in range(len(geometry.material_runs)) if (*key, i) in runtime}
            geometry, attachment_update = models.apply_rom_attachment_preview_update(
                segment.data, geometry, contexts.get(key), material_records)
            if records[key[1:]].get('rom_attachment_update') != attachment_update:
                raise ValueError('attachment texture/UV manifest update differs from ROM')
            geometry, _, _ = models.omit_zero_area_preview_faces(geometry)
            for index, run in enumerate(geometry.material_runs):
                record = records[key[1:]]['material_runs'][index]
                if (*key, index) in runtime:
                    if record.get('rom_texture_state_consensus') or record.get('rom_object_texture_animation') or record.get('rom_scene_texture_state') or record.get('rom_object_texture_binding'):
                        raise ValueError('captured material was replaced with ROM object consensus')
                    continue
                texture, status = models.choose_preview_texture(run, catalog, flat)
                evidence = None
                if texture is None and ('lookup-mode-unresolved' in status or status == 'no-proven-texture'):
                    texture, status, evidence = models.rom_object_preview_texture(
                        run, catalog, flat, tables, contexts.get(key))
                animation_evidence = None
                if texture is None and status == 'runtime-segment':
                    texture, animation_status, animation_evidence = models.rom_object_animation_preview_texture(
                        run, catalog, flat, tables, contexts.get(key))
                    if texture is not None:
                        status = animation_status
                if animation_evidence is not None or record.get('rom_object_texture_animation'):
                    if (texture is None or animation_evidence is None or record['status'] != status
                            or record.get('rom_object_texture_animation') != animation_evidence
                            or not record.get('texture')
                            or models._validated_preview_source(path.parent, record['texture']['file']).read_bytes() != texture.png_data):
                        raise ValueError(f'ROM object texture animation differs for {key}:{index}')
                    linked += 1
                    faces += run.face_count
                binding_evidence = None
                if texture is None and status == 'runtime-segment':
                    texture, binding_status, binding_evidence = models.rom_object_binding_preview_texture(
                        run, catalog, flat, tables, contexts.get(key))
                    if texture is not None:
                        status = binding_status
                if binding_evidence is not None or record.get('rom_object_texture_binding'):
                    if (texture is None or binding_evidence is None or record['status'] != status
                            or record.get('rom_object_texture_binding') != binding_evidence
                            or not record.get('texture')
                            or models._validated_preview_source(path.parent, record['texture']['file']).read_bytes() != texture.png_data):
                        raise ValueError(f'ROM object texture binding differs for {key}:{index}')
                    linked += 1
                    faces += run.face_count
                scene_evidence = None
                if texture is None and status == 'runtime-segment':
                    texture, status, scene_evidence = models.rom_scene_preview_texture(
                        run, catalog, flat, contexts.get(key))
                if scene_evidence is not None or record.get('rom_scene_texture_state'):
                    if (texture is None or scene_evidence is None or record['status'] != status
                            or record.get('rom_scene_texture_state') != scene_evidence
                            or not record.get('texture')
                            or models._validated_preview_source(path.parent, record['texture']['file']).read_bytes() != texture.png_data):
                        raise ValueError(f'ROM scene texture state differs for {key}:{index}')
                    linked += 1
                    faces += run.face_count
                if evidence is not None or record.get('rom_texture_state_consensus'):
                    if (texture is None or evidence is None or record['status'] != status
                            or record.get('rom_texture_state_consensus') != evidence
                            or not record.get('texture')
                            or models._validated_preview_source(path.parent, record['texture']['file']).read_bytes() != texture.png_data):
                        raise ValueError(f'ROM object texture differs for {key}:{index}')
                    linked += 1
                    faces += run.face_count
    return {'consensus_texture_runs': linked, 'consensus_texture_faces': faces,
            'export_capture_inputs': [], 'scope': 'Texture bytes on reviewed object and scene draw paths with explicit preview states; native appearance incomplete'}


def compare_rom_defaults(path: Path, captures: list[dict], flat: dict, catalog: dict) -> dict:
    manifest = read(path)
    if manifest.get('runtime_material_manifest') or manifest.get('runtime_material_record_count'):
        raise ValueError('ROM-only corpus contains runtime material inputs')
    _, _, digest_rom, bundles, tables = models.load_model_bundles('us', None, 1)
    defaults = models.load_character_defaults('us', None, digest_rom)
    if identity(json.loads(json.dumps(defaults))) != identity(manifest['rom_character_defaults']):
        raise ValueError('exported default provenance differs from ROM')
    records = {r['bank_entry']: r for r in manifest['models']}
    linked = faces = consensus_runs = consensus_faces = 0
    for bundle in bundles:
        geometry, layout = models.parse_character_model_geometry(bundle.data)
        geometry, selection = models.model_character_parts.primary_preview(bundle.data, geometry, layout)
        if records[bundle.index].get('character_draw_pass') != selection:
            raise ValueError('exported primary draw-table provenance differs from ROM')
        geometry, _, _ = models.omit_zero_area_preview_faces(geometry)
        for i, run in enumerate(geometry.material_runs):
            if not run.face_count:
                continue
            if run.pixel is None or run.pixel.segment not in (6, 7, 10, 11):
                record = records[bundle.index]['material_runs'][i]
                texture, status = models.choose_preview_texture(run, catalog, flat)
                evidence = None
                if texture is None and ('lookup-mode-unresolved' in status or status == 'no-proven-texture'):
                    texture, status, evidence = models.rom_render_state_preview_texture(run, catalog, flat, tables)
                if evidence is not None or record.get('rom_texture_state_consensus'):
                    if (texture is None or evidence is None or record['status'] != status
                            or record['rom_texture_state_consensus'] != evidence
                            or not record.get('texture')
                            or models._validated_preview_source(path.parent, record['texture']['file']).read_bytes() != texture.png_data):
                        raise ValueError(f'ROM texture-state consensus differs for {bundle.index}:{i}')
                    consensus_runs += 1
                    consensus_faces += run.face_count
                continue
            texture, status, evidence = models.rom_default_preview_texture(
                run, models.model_character_defaults.preview_defaults(defaults, bundle.index),
                layout['texture_descriptors'], flat, tables)
            record = records[bundle.index]['material_runs'][i]
            if record['status'] != status or record['rom_default_texture'] != evidence:
                raise ValueError(f'ROM default resolution changed for {bundle.index}:{i}')
            if texture is not None:
                png = models._validated_preview_source(path.parent, record['texture']['file']).read_bytes()
                if png != texture.png_data:
                    raise ValueError(f'ROM default PNG differs for {bundle.index}:{i}')
                linked += 1
                faces += run.face_count
            elif record.get('texture'):
                raise ValueError('unresolved ROM default was assigned an image')
    compared = 0
    for case in captures:
        capture_path = ROOT / case['materials']
        capture = read(capture_path)
        if capture['normalized_sha1'] != digest_rom:
            raise ValueError('comparison capture uses a different ROM')
        for run_index in case['runs']:
            record = records[case['entry']]['material_runs'][run_index]
            if record['status'] != 'rom-default-indexed':
                raise ValueError('capture comparison requires a resolved ROM default')
            png = models._validated_preview_source(path.parent, record['texture']['file']).read_bytes()
            variants = [v['captured_texture'] for r in capture['materials']
                        if (r['bank'], r['entry'], r['segment'], r['material_run']) == (1, case['entry'], 0, run_index)
                        for v in r['variants'] if v.get('captured_texture')]
            matching = [v for v in variants if v.get('png_sha1') == hashlib.sha1(png).hexdigest()]
            if not matching or any(models._validated_preview_source(capture_path.parent, v['file']).read_bytes() != png for v in matching):
                raise ValueError(f'ROM default pixels differ from capture for {case["entry"]}:{run_index}')
            compared += 1
    return {'resolved_runs': linked, 'resolved_faces': faces, 'capture_compared_runs': compared,
            'consensus_texture_runs': consensus_runs, 'consensus_texture_faces': consensus_faces,
            'export_capture_inputs': [], 'scope': 'ROM default texture bytes; expressions and native raster parity incomplete'}


def _validate_batch(config_path: Path, output: Path, *, blender: Path | None = None,
                   skip_blender: bool = False, skip_renders: bool = False) -> dict:
    before = ContentSnapshot()
    digest = before.digest
    preview_fingerprint = before.fingerprint
    config = read(config_path)
    if not isinstance(config, dict) or config.get('schema_version') != 1:
        raise ValueError('unsupported model validation configuration')
    output.mkdir(parents=True, exist_ok=True)
    cache_root = output / 'cache'
    logs = output / 'logs'
    logs.mkdir(exist_ok=True)
    codes = code_identity()
    # Report formatting or ROM-comparison changes do not affect Blender's
    # implementation. Include the worker and every helper it executes instead.
    worker_identity = identity({f.__name__: inspect.getsource(f) for f in
                                (blender_worker, read, write, globals()['digest'])})
    report = {'schema_version': 1, 'family': 'model-batch-validation',
              'status': 'incomplete', 'summary': {'completed': False},
              'config_sha256': digest(config_path), 'code_sha256': codes,
              'checks': {}, 'files': [], 'models': [], 'renders': [], 'review_queue': [],
              'limits': ['Regressions and source consistency do not prove native visual parity.',
                         'Uncaptured poses, materials, scene state and unaligned native screenshots remain incomplete.']}
    write(output / 'report.json', report)
    (output / 'review.html').write_text('<!doctype html><meta charset="utf-8"><title>Model validation running</title>'
        '<h1>Validation is running</h1><p>No completed result is available for this run. '
        '<a href="report.json">Current report</a></p>')

    def stage(name, inputs, operation):
        key = identity({'code': codes, 'inputs': inputs})
        destination = cache_root / name / (key + '.json')
        result = cached(destination, key)
        hit = result is not None
        if result is None:
            result = checked(operation)
            write(destination, {'key': key, 'result': result})
        return {**result, 'cached': hit}

    # Hash the actual ROM, not an earlier manifest's claimed identity.
    rom_path, _ = models.resolve_rom('us', None)
    rom_key = digest(rom_path)
    for bank in models.BANK_INDICES:
        report['checks'][f'rom-bank-{bank:02x}'] = stage('rom', {'bank': bank, 'rom': rom_key},
            lambda bank=bank: {'counts': list(models.verify_models('us', None, bank))})
    rom_digest, inventory = models.runtime_material_inventory('us', None)
    flat = models.load_flat_asset_payloads('us', None, rom_digest)
    texture_root = ROOT / config['textures']
    catalog = models.load_preview_texture_catalog(texture_root, rom_digest, tuple(flat))
    static_images = {str(texture.source): digest(texture.source) for choices in catalog.values()
                     for texture in choices if texture.source is not None}
    runtime_catalogs = {}
    for source in config['runtime_catalogs']:
        path = ROOT / source
        def verify_capture(path=path):
            return capture_comparisons(path, inventory, flat, catalog)
        # The catalog refers to trace files and PNGs; include every referenced
        # source in the cache key, including mip/secondary images.
        manifest = read(path)
        deps = {source: digest(path)}
        for trace in manifest['source_traces']:
            deps[trace['file']] = digest(ROOT / trace['file'])
        for item in manifest['materials']:
            for variant in item['variants']:
                capture = variant.get('captured_texture')
                if capture:
                    images = [capture, *capture.get('mip_levels', []), *capture.get('texture1_mip_levels', [])]
                    if capture.get('texture1_image'):
                        images.append(capture['texture1_image'])
                    for image in images:
                        target = models._validated_preview_source(path.parent, image['file'])
                        deps[str(target)] = digest(target)
        report['checks']['capture:' + source] = stage('capture', {'rom': rom_key, 'dependencies': deps,
                                                               'static_images': static_images}, verify_capture)
        runtime_catalogs[str(path.resolve())] = models.load_runtime_material_catalog(path, rom_digest)

    if config.get('runtime_draw_cases'):
        from scripts.model_runtime_validation import runtime_inputs, compare_submitted_rig
        cluster_index = models.load_model_cluster_index()
        for case in config['runtime_draw_cases']:
            def compare_case(case=case):
                target = tuple(case['target'])
                hashes = {row['model_sha1'] for key, row in inventory.items() if key[:3] == target}
                if len(hashes) != 1:
                    raise ValueError('runtime draw case does not identify one ROM model')
                model_sha1 = next(iter(hashes))
                inputs = runtime_inputs(case, model_sha1, cluster_index)
                result = stage('runtime-draw', {'rom': rom_key, **inputs},
                               lambda: compare_submitted_rig(case, rom_digest, inputs))
                if runtime_inputs(case, model_sha1, cluster_index) != inputs:
                    raise ValueError('runtime draw inputs changed during comparison')
                return result
            report['checks']['runtime-draw:' + case['id']] = checked(compare_case)

    if config.get('submitted_composition_cases'):
        from scripts.model_runtime_validation import runtime_inputs
        from scripts.model_submitted_pose import compare_composition
        cluster_index = models.load_model_cluster_index()
        for case in config['submitted_composition_cases']:
            def compare_selected(case=case):
                hashes = {row['model_sha1'] for key, row in inventory.items()
                          if key[:3] == tuple(case['target'])}
                if len(hashes) != 1:
                    raise ValueError('submitted composition does not identify one ROM model')
                model_sha1 = next(iter(hashes))
                input_case = {**case, 'exports': [{'path': case['path']}]}
                inputs = runtime_inputs(input_case, model_sha1, cluster_index)
                result = stage('submitted-composition', {'rom': rom_key, **inputs},
                    lambda: compare_composition(case, rom_digest, inventory, cluster_index))
                if runtime_inputs(input_case, model_sha1, cluster_index) != inputs:
                    raise ValueError('submitted composition inputs changed during comparison')
                return result
            report['checks']['submitted-composition:' + case['id']] = checked(compare_selected)
            result = report['checks']['submitted-composition:' + case['id']]
            if result['status'] == 'passed':
                report['checks']['submitted-composition-textures:' + case['id']] = {
                    'status': result['captured_texture_status'],
                    'unresolved_face_count': result['unresolved_texture_face_count'],
                    'scope': 'captured texture pixels only; native raster parity incomplete'}

    # Actual ROM geometry is shared between corpora; the emitted buffers differ.
    source_geometry = {}
    source_primary_geometry = {}
    source_morphs = {}
    attachment_inputs = {}
    for bank in models.BANK_INDICES:
        _, _, bank_digest, bundles, _ = models.load_model_bundles('us', None, bank)
        update_contexts = ({(r['bank'], r['entry'], r['segment']): r
                           for r in models.load_object_material_context('us', None, bank_digest, bank)['models']
                           if r.get('geometry_update')} if bank == 9 else {})
        if bank == 1:
            morph_manifest = models.load_character_morph_manifest('us', None, bundles)
            source_morphs = {record['character_entry']: record for record in morph_manifest['models']}
        for bundle in bundles:
            for segment in bundle.segments:
                if not segment.data:
                    continue
                joints = None
                if bank == 1:
                    geometry, layout = models.parse_character_model_geometry(segment.data)
                    joints = tuple(layout['joints'])
                    source_primary_geometry[(bank, bundle.index, segment.index)] = models.model_character_parts.primary_preview(
                        segment.data, geometry, layout)
                elif bank == 9 and models.is_attachment_model(segment.data):
                    geometry, layout = models.parse_attachment_model(segment.data, models.parse_model_geometry)
                    joints = tuple(layout['joints']) or None
                else:
                    geometry = models.parse_segment_geometry(segment, bank)
                source_geometry[(bank, bundle.index, segment.index)] = (geometry, joints)
                if (bank, bundle.index, segment.index) in update_contexts:
                    attachment_inputs[(bank, bundle.index, segment.index)] = (
                        segment.data, update_contexts[(bank, bundle.index, segment.index)])

    records = []
    for corpus in config['corpora']:
        root = ROOT / corpus['root']
        banks = tuple(corpus.get('banks', models.BANK_INDICES))
        collected = collect_preview_records(root, banks=banks)
        if corpus.get('compositions'):
            collected += collect_composition_records(ROOT / corpus['compositions'])
        for record in collected:
            records.append({**record, 'path': str(record['path'].resolve()), 'corpus': corpus['name']})
        for bank in banks:
            directory = root / f'us-bank-{bank:02x}-preview'
            manifest_path = directory / 'manifest.json'
            manifest = read(manifest_path)
            manifest_digest = digest(manifest_path)
            if bank == 1 and manifest.get('rom_character_defaults') is not None:
                morph_path = models._validated_preview_source(directory, manifest['character_morphs']['file'])
                if identity(read(morph_path)) != identity(morph_manifest):
                    raise ValueError('exported character morph manifest differs from ROM')
            if manifest.get('rom_character_defaults') is not None:
                captures = corpus.get('default_texture_captures', [])
                dependencies = {str(manifest_path): manifest_digest}
                for r in manifest['models']:
                    for run in r['material_runs']:
                        if run.get('texture') and (run.get('rom_default_texture') or run.get('rom_texture_state_consensus')):
                            image = models._validated_preview_source(directory, run['texture']['file'])
                            dependencies[str(image)] = digest(image)
                for case in captures:
                    capture_path = ROOT / case['materials']
                    dependencies[str(capture_path)] = digest(capture_path)
                    for r in read(capture_path)['materials']:
                        if r['entry'] == case['entry'] and r['material_run'] in case['runs']:
                            for variant in r['variants']:
                                if variant.get('captured_texture'):
                                    image = models._validated_preview_source(capture_path.parent, variant['captured_texture']['file'])
                                    dependencies[str(image)] = digest(image)
                report['checks']['rom-defaults:' + corpus['name']] = stage(
                    'rom-defaults', {'rom': rom_key, 'dependencies': dependencies, 'captures': captures},
                    lambda: compare_rom_defaults(manifest_path, captures, flat, catalog))
            runtime_path = manifest.get('runtime_material_manifest')
            runtime = runtime_catalogs.get(str((ROOT / runtime_path).resolve()), {}) if runtime_path else {}
            if bank in (3, 4, 9):
                dependencies = {str(manifest_path): manifest_digest}
                if runtime_path:
                    dependencies[runtime_path] = digest(ROOT / runtime_path)
                for record in manifest['models']:
                    for run in record['material_runs']:
                        if run.get('texture') and (run.get('rom_texture_state_consensus') or run.get('rom_object_texture_animation') or run.get('rom_scene_texture_state') or run.get('rom_object_texture_binding')):
                            image = models._validated_preview_source(directory, run['texture']['file'])
                            dependencies[str(image)] = digest(image)
                report['checks'][f'rom-objects:{corpus["name"]}:{bank:02x}'] = stage(
                    'rom-objects', {'rom': rom_key, 'dependencies': dependencies},
                    lambda: compare_rom_object_materials(manifest_path, flat, catalog, runtime))
            for record in manifest['models']:
                key = (bank, record['bank_entry'], record['segment'])
                geometry, joints = source_geometry[key]
                draw_pass = None
                if bank == 1 and manifest.get('rom_character_defaults') is not None:
                    geometry, draw_pass = source_primary_geometry[key]
                    if record.get('character_draw_pass') != draw_pass:
                        raise ValueError('preview character draw-pass selection differs from ROM')
                material_records = {index: runtime[(*key, index)] for index in range(len(geometry.material_runs))
                                    if (*key, index) in runtime}
                attachment_update = None
                if key in attachment_inputs:
                    data, context = attachment_inputs[key]
                    geometry, attachment_update = models.apply_rom_attachment_preview_update(
                        data, geometry, context, material_records)
                if record.get('rom_attachment_update') != attachment_update:
                    raise ValueError('preview attachment texture/UV update differs from ROM')
                geometry, _, _ = models.omit_zero_area_preview_faces(geometry)
                path = directory / (record.get('bind_gltf_file') or record['gltf_file'])
                model_key = f'{bank:02x}:{key[1]:04d}:{key[2]:02d}'
                inputs = {'rom': rom_key, 'fingerprint': preview_fingerprint(path),
                          'manifest': manifest_digest, 'model': model_key}
                morph = source_morphs.get(key[1]) if bank == 1 and manifest.get('rom_character_defaults') is not None else None
                comparison = stage('geometry', inputs, lambda p=path, g=geometry, j=joints, r=record, m=morph, d=draw_pass, rm=material_records, au=attachment_update:
                                   compare_geometry(p, g, j, r['material_runs'], m, d,
                                                    flat_payloads=flat, runtime_materials=rm, preview_root=directory,
                                                    attachment_update=au))
                if morph or draw_pass or any(run.get('rom_texture_state_consensus') or run.get('rom_object_texture_animation') or run.get('rom_scene_texture_state') or run.get('rom_object_texture_binding') for run in record['material_runs']):
                    animated = directory / record['gltf_file']
                    report['checks'][f'animated-geometry:{corpus["name"]}:{model_key}'] = stage(
                        'geometry', {**inputs, 'fingerprint': preview_fingerprint(animated)},
                        lambda p=animated, g=geometry, j=joints, r=record, m=morph, d=draw_pass, rm=material_records, au=attachment_update:
                            compare_geometry(p, g, j, r['material_runs'], m, d,
                                             flat_payloads=flat, runtime_materials=rm, preview_root=directory,
                                             attachment_update=au))
                report['models'].append({'key': model_key, 'corpus': corpus['name'],
                    'checks': {'export_geometry': comparison,
                               'native_visual_parity': {'status': 'incomplete', 'reason': 'no-complete-aligned-runtime-reference'}}})
            if globals()['digest'](manifest_path) != manifest_digest:
                raise ValueError(f'preview manifest changed during validation: {manifest_path}')

    for case in config.get('runtime_draw_cases', []):
        for export in case.get('exports', []):
            records.append({'path': str((ROOT / export['path']).resolve()), 'bank': case['target'][0],
                            'kind': 'submitted-character-pose', 'corpus': 'submitted'})
    for case in config.get('submitted_composition_cases', []):
        records.append({'path': str((ROOT / case['path']).resolve()), 'bank': case['target'][0],
                        'kind': 'submitted-character-composition', 'corpus': 'submitted'})
    recorded_paths = {record['path'] for record in records}
    for directory in config.get('additional_compositions', []):
        for record in collect_composition_records(ROOT / directory):
            path = str(record['path'].resolve())
            if path not in recorded_paths:
                records.append({**record, 'path': path, 'corpus': 'submitted-compositions'})
                recorded_paths.add(path)

    for directory in config.get('scene_assemblies', []):
        from scripts.model_scene_assemblies import verify_assemblies
        root = ROOT / directory
        manifest_path = root / 'manifest.json'
        manifest = read(manifest_path)
        before.digest(manifest_path)
        before.digest(ROOT / manifest['config'])
        for record in manifest['models']:
            for component in record['components']:
                source = ROOT / component['path']
                before.fingerprint(source)
                before.digest(source.parent.parent / 'manifest.json')
            records.append({'path': str((root / record['gltf_file']).resolve()),
                            'bank': 4, 'kind': 'static-scene-assembly', 'corpus': 'scene-assemblies'})
        report['checks']['scene-assemblies:' + directory] = checked(
            lambda root=root: verify_assemblies(root, fresh_rom=True))

    node = shutil.which('node')
    package = ROOT / 'build/tools/model-validation/node_modules/gltf-validator'
    package_json = package / 'package.json'
    khronos_identity = None
    if node and package_json.is_file() and read(package_json).get('version') == VALIDATOR_VERSION:
        khronos_identity = {'node': digest(Path(node).resolve()),
            'adapter': digest(ROOT / 'scripts/gltf_validate_models.cjs'),
            'package': {str(p.relative_to(package)): digest(p) for p in sorted(package.rglob('*')) if p.is_file()}}
    blender = blender or (Path(shutil.which('blender')) if shutil.which('blender') else
                          Path('/Applications/Blender.app/Contents/MacOS/Blender'))
    blender_identity = None
    if not skip_blender and blender.is_file():
        version = subprocess.run([str(blender), '--version'], capture_output=True, text=True, check=True).stdout
        blender_identity = {'binary': digest(blender), 'version': version,
                            'validator': digest(ROOT / 'scripts/validate_model_previews_blender.py'),
                            'fingerprint': digest(ROOT / 'scripts/model_preview_evidence.py')}
    pending_gltf, pending_blender, pending_renders = [], [], []
    for record in records:
        path = Path(record['path'])
        fingerprint = checked(lambda: {'value': preview_fingerprint(path)})
        row = {**record, 'checks': {}}
        report['files'].append(row)
        if fingerprint['status'] == 'failed':
            row['checks']['dependencies'] = fingerprint
            continue
        fingerprint = fingerprint['value']
        row['input_fingerprint'] = fingerprint
        for name, tool, pending in (('gltf', khronos_identity, pending_gltf),
                                    ('blender', blender_identity, pending_blender)):
            if tool is None:
                row['checks'][name] = {'status': 'incomplete', 'reason': 'tool-disabled-or-unavailable'}
                continue
            cache_key = identity({'path': str(path), 'fingerprint': fingerprint, 'tool': tool,
                                  'worker': worker_identity if name == 'blender' else None})
            destination = cache_root / name / (cache_key + '.json')
            result = cached(destination, cache_key)
            row['checks'][name] = {**result, 'cached': True} if result else {'status': 'incomplete', 'reason': 'pending'}
            if result is None:
                destination.parent.mkdir(parents=True, exist_ok=True)
                pending.append({**record, 'fingerprint': fingerprint, 'key': cache_key, 'output': str(destination)})
            row[name + '_cache'] = {'path': str(destination), 'key': cache_key}
    for case in config.get('render_cases', []):
        path = ROOT / case['source']
        settings = {'view': case.get('view', 'three-quarter'), 'shading': case.get('shading', 'material'), 'size': case.get('size', 768)}
        row = {'id': case['id'], 'source': str(path), 'reference': str(ROOT / case['reference']), 'settings': settings}
        report['renders'].append(row)
        if skip_renders or blender_identity is None:
            row['check'] = {'status': 'incomplete', 'reason': 'rendering-disabled-or-unavailable'}
            continue
        fingerprint = preview_fingerprint(path)
        cache_key = identity({'input': fingerprint, 'settings': settings, 'blender': blender_identity,
                              'renderer': digest(ROOT / 'scripts/render_model_preview_blender.py'),
                              'worker': worker_identity})
        directory = cache_root / 'renders'
        destination = directory / (cache_key + '.json')
        result = cached(destination, cache_key)
        if result and result['status'] == 'passed':
            image = Path(result['image'])
            if not image.is_file() or digest(image) != result['image_sha256']:
                result = None
        if result is None:
            directory.mkdir(parents=True, exist_ok=True)
            pending_renders.append({'path': str(path), **settings, 'key': cache_key, 'fingerprint': fingerprint,
                                    'output': str(destination), 'image': str(directory / (cache_key + '.png'))})
        row['cache'] = {'path': str(destination), 'key': cache_key, 'hit': result is not None}
    if pending_gltf:
        request = output / 'gltf-request.json'
        write(request, pending_gltf)
        report['gltf_process_exit'] = run_logged([node, str(ROOT / 'scripts/gltf_validate_models.cjs'),
            str(package), str(request)], logs / 'gltf.log')
    if pending_blender or pending_renders:
        request = output / 'blender-request.json'
        write(request, {'files': pending_blender, 'renders': pending_renders})
        print(f'Blender: {len(pending_blender)} changed/unvalidated files, {len(pending_renders)} changed renders', flush=True)
        report['blender_process_exit'] = run_logged([str(blender), '--background', '--factory-startup',
            '--python', str(Path(__file__)), '--', '--worker', str(request)], logs / 'blender.log')
    after = ContentSnapshot()
    for row in report['files']:
        if row.get('input_fingerprint'):
            current = checked(lambda row=row: {'value': after.fingerprint(Path(row['path']))})
            if current['status'] == 'failed' or current['value'] != row['input_fingerprint']:
                row['checks']['dependencies'] = {'status': 'failed', 'error': 'preview changed during batch validation'}
        for name in ('gltf', 'blender'):
            source = row.get(name + '_cache')
            if source and row['checks'][name].get('reason') == 'pending':
                row['checks'][name] = {**(cached(Path(source['path']), source['key']) or
                    {'status': 'incomplete', 'reason': 'worker-did-not-return-evidence'}), 'cached': False}
        row['status'] = summarize_status(row['checks'])
        if row['status'] == 'failed':
            report['review_queue'].append({'kind': 'validation-failure', 'path': row['path'],
                                            'checks': row['checks']})
    comparison_code = image_comparison_identity()
    for row in report['renders']:
        source = row.get('cache')
        if source:
            result = cached(Path(source['path']), source['key'])
            if not result:
                row['check'] = {'status': 'incomplete', 'reason': 'render-worker-did-not-return-evidence'}
            elif result['status'] == 'failed':
                row['check'] = result
            else:
                row['image'] = result['image']
                reference = Path(row['reference'])
                row['check'] = (checked(lambda r=row: cached_image_comparison(
                                Path(r['reference']), Path(r['image']), output / 'differences' / (r['id'] + '.png'),
                                cache_root, before, comparison_code)) if reference.is_file() else
                                {'status': 'incomplete', 'reason': 'no-regression-reference'})
        if (row['check']['status'] == 'failed' or row['check'].get('reason') in
                ('changed-image-needs-review', 'no-regression-reference')):
            report['review_queue'].append({'kind': 'render-difference', **row})
    for row in report['models']:
        row['status'] = summarize_status(row['checks'])
        if row['checks']['export_geometry']['status'] == 'failed':
            report['review_queue'].append({'kind': 'geometry-disagreement', **row})
    # Emit fresh, compatible Blender evidence without overwriting the caller's
    # canonical reports. Only results checked against this tool identity enter it.
    for corpus in config['corpora']:
        validations = [row['checks']['blender']['validation'] for row in report['files']
                       if row['corpus'] == corpus['name'] and
                       row['checks'].get('blender', {}).get('status') == 'passed']
        write(output / (corpus['name'] + '-blender-validation.json'), {
            'schema_version': 3, 'family': 'blender-model-preview-validation',
            'blender_version': blender_identity['version'].splitlines()[0] if blender_identity else None,
            'tool_identity': blender_identity, 'file_count': len(validations), 'files': validations,
            **{field: sum(v[field] for v in validations) for field in ('mesh_count', 'polygon_count', 'action_count')}})
    try:
        from scripts.model_coverage import extract_coverage
        coverage = extract_coverage('us', None, ROOT / config['corpora'][0]['root'], texture_root,
            output / 'coverage.json', tuple(ROOT / p for p in config['runtime_catalogs']),
            ROOT / config['activity'], output / (config['corpora'][0]['name'] + '-blender-validation.json'),
            ROOT / config['scenes'])
        by_model = {row['key']: row for row in coverage['models']}
        runs_by_model = {}
        for run in coverage['material_runs']:
            runs_by_model.setdefault(run['model_key'], []).append(run)
        for row in report['models']:
            row['checks'].update(evidence_checks(by_model[row['key']], runs_by_model.get(row['key'], [])))
            row['status'] = summarize_status(row['checks'])
        report['checks']['coverage'] = {'status': 'passed', 'summary': coverage['summary']}
    except (OSError, ValueError, KeyError) as error:
        report['checks']['coverage'] = {'status': 'failed', 'error': str(error)}
    report['summary'] = {name: dict(Counter(row['status'] for row in report[name])) for name in ('models', 'files')}
    report['summary']['completed'] = True
    report['summary']['unique_model_count'] = len({row['key'] for row in report['models']})
    report['summary']['renders'] = dict(Counter(row['check']['status'] for row in report['renders']))
    report['summary']['review_count'] = len(report['review_queue'])
    report['review_queue'].sort(key=lambda row: (row['kind'] == 'render-difference',
                                               str(row.get('key', row.get('path', row.get('id', ''))))))
    report['summary']['fresh_blender_imports'] = len(pending_blender)
    report['summary']['fresh_renders'] = len(pending_renders)
    report['summary']['fresh_image_comparisons'] = sum(r['check'].get('cached') is False for r in report['renders'])
    report['summary']['fresh_gltf_checks'] = len(pending_gltf)
    report['summary']['runtime_draw_cases'] = dict(Counter(
        row['status'] for key, row in report['checks'].items() if key.startswith('runtime-draw:')))
    report['summary']['submitted_composition_cases'] = dict(Counter(
        row['status'] for key, row in report['checks'].items() if key.startswith('submitted-composition:')))
    changed = before.verify(after)
    if code_identity() != codes or changed:
        report['checks']['input-stability'] = {'status': 'failed',
            'error': 'validation inputs changed during validation', 'changed_files': changed}
    report['summary']['content_reads'] = {'before': before.read_count, 'after': after.read_count,
        'bytes_before': before.bytes_read, 'bytes_after': after.bytes_read}
    for name, result in report['checks'].items():
        if result['status'] == 'failed':
            report['review_queue'].append({'kind': 'evidence-disagreement', 'key': name,
                                            'checks': {name: result}})
    report['summary']['review_count'] = len(report['review_queue'])
    report['status'] = 'failed' if (any(c['status'] == 'failed' for c in report['checks'].values()) or
        any(row['status'] == 'failed' for row in report['models'] + report['files']) or
        any(row['check']['status'] == 'failed' for row in report['renders'])) else 'incomplete'
    write(output / 'report.json', report)
    cards = []
    for row in report['review_queue']:
        label = row.get('id', row.get('path', row.get('key', row['kind'])))
        details = row.get('check', row.get('checks', {}))
        if row['kind'] == 'evidence-disagreement':
            details = {name: {**result, 'observations': [v for v in result.get('observations', [])
                        if v['status'] == 'failed']} for name, result in details.items()}
        detail = html.escape(json.dumps(details, indent=2))
        images = ''.join(f'<figure><figcaption>{name}</figcaption><img src="{html.escape(str(Path(value).relative_to(output)) if Path(value).is_relative_to(output) else Path(value).as_uri(), quote=True)}"></figure>'
                         for name, value in (('Reference', row.get('reference')), ('Current', row.get('image')),
                                              ('Difference', row.get('check', {}).get('difference_image'))) if value)
        cards.append(f'<article><h2>{html.escape(str(label))}</h2><div>{images}</div><pre>{detail}</pre></article>')
    (output / 'review.html').write_text('<!doctype html><meta charset="utf-8"><title>Model validation review</title>'
        '<style>body{font:15px system-ui;margin:32px;background:#171b20;color:#eee}article{border-top:1px solid #666;padding:20px 0}div{display:flex}figure{margin:8px}img{max-width:28vw}pre{white-space:pre-wrap}</style>'
        '<h1>Model validation review</h1><pre>' + html.escape(json.dumps(report['summary'], indent=2)) +
        '</pre><p>Only disagreements and changed regression images appear here. '
        'An empty queue does not establish native visual parity. '
        '<a href="report.json">Full evidence report</a></p>' + ''.join(cards))
    print(json.dumps(report['summary'], sort_keys=True), flush=True)
    return report


def validate_batch(config_path: Path, output: Path, **options) -> dict:
    """Never leave a previous successful report in place after an input failure."""
    try:
        return _validate_batch(config_path, output, **options)
    except (OSError, ValueError, KeyError, IndexError, TypeError, subprocess.SubprocessError, TraceError) as error:
        result = {'schema_version': 1, 'family': 'model-batch-validation', 'status': 'failed',
                  'checks': {'batch-input': {'status': 'failed', 'error': str(error)}},
                  'summary': {'completed': False}, 'files': [], 'models': [], 'renders': [],
                  'review_queue': [{'kind': 'batch-input', 'error': str(error)}]}
        write(output / 'report.json', result)
        (output / 'review.html').write_text('<!doctype html><meta charset="utf-8"><title>Model validation failed</title>'
            '<h1>Validation could not complete</h1><pre>' + html.escape(str(error)) + '</pre>')
        return result


if __name__ == '__main__':
    args = sys.argv[sys.argv.index('--') + 1:] if '--' in sys.argv else sys.argv[1:]
    if len(args) == 2 and args[0] == '--worker':
        blender_worker(Path(args[1]))
    else:
        raise SystemExit('Use ./conker model-assets validate')
