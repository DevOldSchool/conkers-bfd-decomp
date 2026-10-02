"""Admit the selected embedded primitive independently of indexed model banks."""
from __future__ import annotations

import copy
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile

try:
    from scripts import model_embedded_type13_inspection as backend
    from scripts.model_inspection_options import embedded_type13_output
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    import model_embedded_type13_inspection as backend
    from model_inspection_options import embedded_type13_output
    from model_preview_evidence import preview_fingerprint

NAME = 'embedded-type13-8008b3e0'


def digest(data):
    return hashlib.sha256(data).hexdigest()


def validator_identity(root):
    node = shutil.which('node')
    package = root / 'build/tools/model-validation/node_modules/gltf-validator'
    adapter = root / 'scripts/gltf_validate_models.cjs'
    if (not node or not package.is_dir() or
            json.loads((package / 'package.json').read_text()).get('version') != '2.0.0-dev.3.10'):
        raise ValueError('embedded inspection requires the pinned local Khronos validator')
    paths = [Path(node).resolve(), adapter] + sorted(p for p in package.rglob('*') if p.is_file())
    return node, package, adapter, {str(p): digest(p.read_bytes()) for p in paths}


def validate_source(root, source, fingerprint):
    node, package, adapter, tools = validator_identity(root)
    with tempfile.TemporaryDirectory(prefix='conker-embedded-validation-') as temporary:
        directory = Path(temporary)
        result_path = directory / 'result.json'
        request = directory / 'request.json'
        request.write_text(json.dumps([{'path': str(source), 'fingerprint': fingerprint,
            'key': fingerprint['gltf_sha256'], 'output': str(result_path)}]))
        subprocess.run([node, str(adapter), str(package), str(request)], check=True,
                       capture_output=True, text=True, cwd=root)
        result = json.loads(result_path.read_text())
    if (result.get('key') != fingerprint['gltf_sha256']
            or result.get('result', {}).get('status') != 'passed'
            or preview_fingerprint(source) != fingerprint
            or validator_identity(root)[3] != tools):
        raise ValueError('embedded source failed current Khronos validation')
    return {'gltf': result['result'], 'tools': tools}


def prepare_type13(options, root, output, previews):
    """Return one card and deferred writes only after both independent checks."""
    try:
        from scripts.model_inspection import pack_glb
    except ModuleNotFoundError:
        from model_inspection import pack_glb
    root = Path(root).resolve()
    destination = embedded_type13_output(options, root)
    artifact = backend.inspection_artifact(destination)
    proof = artifact['proof']
    source = root / backend.SOURCE
    fingerprint = preview_fingerprint(source)
    if (proof.get('kind') != 'embedded-type13-counter5' or proof.get('primitive') != 'type13'
            or type(proof.get('counter')) is not int or proof['counter'] != 5
            or proof.get('source') != backend.SOURCE or proof.get('source_fingerprint') != fingerprint
            or proof.get('source_gltf_sha256') != fingerprint['gltf_sha256']
            or proof.get('output') != str(destination.relative_to(root))
            or proof.get('inspection_state') != backend.STATE):
        raise ValueError('embedded inspection source or selected state changed')
    blend, image = artifact['blend'], artifact['preview']
    if (digest(blend) != proof.get('blend_sha256') or digest(image) != proof.get('preview_sha256')
            or artifact['scope'] != backend.SCOPE):
        raise ValueError('embedded inspection bytes or scope changed')
    glb, evidence = pack_glb(source)
    if (evidence['source_fingerprint'] != fingerprint
            or evidence['glb_sha256'] != proof.get('source_glb_sha256')):
        raise ValueError('embedded inspection source GLB changed')
    validation = validate_source(root, source, fingerprint)
    manifest = source.parent.parent / 'manifest.json'
    manifest_bytes = manifest.read_bytes()
    geometry = json.loads(manifest_bytes)
    if (geometry.get('family') != 'rom-embedded-effect-geometry'
            or geometry.get('object_type') != 13 or geometry.get('indexed_model_bank') is not None
            or geometry.get('source_vertex_address') != '0x8008B3E0'
            or geometry.get('vertex_count') != 6 or geometry.get('triangle_count') != 4):
        raise ValueError('embedded primitive identity changed')
    record = {'name': NAME, 'label': 'Tapered effect primitive — type 13',
        'category': 'parts-effects', 'aliases': ['embedded primitive', 'type13', '8008B3E0', 'counter5'],
        'note': '6 vertices and 4 triangles from ROM game data, outside the indexed model banks. ' + artifact['scope'],
        'source': backend.SOURCE, **evidence, 'file': NAME + '.glb',
        'download_file': NAME + '-counter5.blend', 'download_format': 'blend',
        'download_sha256': digest(blend), 'preview': str((previews / (NAME + '.png')).relative_to(root)),
        'preview_sha256': digest(image), 'status': 'ready-for-inspection', 'native_visual_parity': 'incomplete',
        'rom_source': {'kind': 'embedded-effect-primitive', 'source': 'ROM', 'capture_inputs': [],
            'object_type': 13, 'vertex_address': '0x8008B3E0', 'manifest_sha256': digest(manifest_bytes),
            'normalized_sha1': geometry['normalized_sha1']},
        'embedded_type13_inspection': copy.deepcopy(proof), 'independent_validation': validation}
    pending = [(output / record['file'], glb), (output / record['download_file'], blend),
               (root / record['preview'], image)]

    def current(path, expected):
        if (preview_fingerprint(source) != fingerprint or manifest.read_bytes() != manifest_bytes
                or validator_identity(root)[3] != validation['tools']):
            raise ValueError('embedded source or validation tools changed before publication')
        return backend.inspection_artifact_current(path, expected)

    return record, pending, (current, destination, proof)
