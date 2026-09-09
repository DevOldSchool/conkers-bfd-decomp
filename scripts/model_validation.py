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
    # Parser helpers can affect data checks. Broad source identity avoids stale
    # successes when a shared dependency changes without changing an artifact.
    return {str(path.relative_to(ROOT)): digest(path)
            for path in sorted((ROOT / 'scripts').glob('*.py'))}


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


def compare_geometry(path: Path, geometry, joints, run_records: list[dict]) -> dict:
    """Compare emitted corner order/positions/UVs/joints with decoded source data.

    This is exporter consistency, not an independent proof of the ROM decoder.
    It reads the actual glTF buffers, never a second call to encode_gltf.
    """
    document = read(path)
    preview_fingerprint(path)  # Validate dependency locality before opening buffers.
    buffers = [(path.parent / unquote(b['uri'])).read_bytes() for b in document.get('buffers', [])]
    models.verify_gltf_material_spans(document, run_records)
    expected = models.validation_face_records(geometry, joints)
    cursor = uv_corners = joint_corners = 0
    for mesh in document.get('meshes', []):
        for primitive in mesh['primitives']:
            if primitive.get('mode', 4) != 4:
                raise ValueError('source triangle export changed primitive mode')
            attrs = {name: accessor(document, i, buffers) for name, i in primitive['attributes'].items()}
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


def _validate_batch(config_path: Path, output: Path, *, blender: Path | None = None,
                   skip_blender: bool = False, skip_renders: bool = False) -> dict:
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
                                (blender_worker, read, write, digest)})
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

    # Actual ROM geometry is shared between corpora; the emitted buffers differ.
    source_geometry = {}
    for bank in models.BANK_INDICES:
        _, _, _, bundles, _ = models.load_model_bundles('us', None, bank)
        for bundle in bundles:
            for segment in bundle.segments:
                if not segment.data:
                    continue
                joints = None
                if bank == 1:
                    geometry, layout = models.parse_character_model_geometry(segment.data)
                    joints = tuple(layout['joints'])
                elif bank == 9 and models.is_attachment_model(segment.data):
                    geometry, layout = models.parse_attachment_model(segment.data, models.parse_model_geometry)
                    joints = tuple(layout['joints']) or None
                else:
                    geometry = models.parse_geometry_for_bank(segment.data, bank)
                source_geometry[(bank, bundle.index, segment.index)] = (geometry, joints)

    records = []
    for corpus in config['corpora']:
        root = ROOT / corpus['root']
        collected = collect_preview_records(root)
        if corpus.get('compositions'):
            collected += collect_composition_records(ROOT / corpus['compositions'])
        for record in collected:
            records.append({**record, 'path': str(record['path'].resolve()), 'corpus': corpus['name']})
        for bank in models.BANK_INDICES:
            directory = root / f'us-bank-{bank:02x}-preview'
            manifest_path = directory / 'manifest.json'
            manifest = read(manifest_path)
            manifest_digest = digest(manifest_path)
            runtime_path = manifest.get('runtime_material_manifest')
            runtime = runtime_catalogs.get(str((ROOT / runtime_path).resolve()), {}) if runtime_path else {}
            for record in manifest['models']:
                key = (bank, record['bank_entry'], record['segment'])
                geometry, joints = source_geometry[key]
                geometry, _, _ = models.omit_zero_area_preview_faces(geometry)
                material_records = {index: runtime[(*key, index)] for index in range(len(geometry.material_runs))
                                    if (*key, index) in runtime}
                geometry = models.apply_runtime_texture_coordinates(geometry, material_records)
                path = directory / (record.get('bind_gltf_file') or record['gltf_file'])
                model_key = f'{bank:02x}:{key[1]:04d}:{key[2]:02d}'
                inputs = {'rom': rom_key, 'fingerprint': preview_fingerprint(path),
                          'manifest': manifest_digest, 'model': model_key}
                comparison = stage('geometry', inputs, lambda p=path, g=geometry, j=joints, r=record:
                                   compare_geometry(p, g, j, r['material_runs']))
                report['models'].append({'key': model_key, 'corpus': corpus['name'],
                    'checks': {'export_geometry': comparison,
                               'native_visual_parity': {'status': 'incomplete', 'reason': 'no-complete-aligned-runtime-reference'}}})
            if digest(manifest_path) != manifest_digest:
                raise ValueError(f'preview manifest changed during validation: {manifest_path}')

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
    for row in report['files']:
        if row.get('input_fingerprint'):
            current = checked(lambda row=row: {'value': preview_fingerprint(Path(row['path']))})
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
                row['check'] = (checked(lambda r=row: compare_images(Path(r['reference']), Path(r['image']),
                                output / 'differences' / (r['id'] + '.png'))) if reference.is_file() else
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
    report['summary']['fresh_gltf_checks'] = len(pending_gltf)
    report['summary']['runtime_draw_cases'] = dict(Counter(
        row['status'] for key, row in report['checks'].items() if key.startswith('runtime-draw:')))
    if code_identity() != codes or digest(config_path) != report['config_sha256'] or digest(rom_path) != rom_key:
        report['checks']['input-stability'] = {'status': 'failed', 'error': 'code, configuration or ROM changed during validation'}
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
