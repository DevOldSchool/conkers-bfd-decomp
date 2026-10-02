"""Admit one selected-opacity primitive without adding an indexed-bank identity."""
from __future__ import annotations

import copy
import json
from pathlib import Path


def prepare_type06(options, root, output, previews):
    try:
        from scripts import model_embedded_type06_inspection as backend
        from scripts.model_inspection import digest, pack_glb
        from scripts.model_inspection_embedded import validate_source, validator_identity
        from scripts.model_inspection_options import embedded_type06_output
        from scripts.model_preview_evidence import preview_fingerprint
    except ModuleNotFoundError:
        import model_embedded_type06_inspection as backend
        from model_inspection import digest, pack_glb
        from model_inspection_embedded import validate_source, validator_identity
        from model_inspection_options import embedded_type06_output
        from model_preview_evidence import preview_fingerprint
    root = Path(root).resolve()
    destination = embedded_type06_output(options, root)
    artifact = backend.inspection_artifact(destination)
    proof = artifact['proof']
    source = root / backend.SOURCE
    fingerprint = preview_fingerprint(source)
    if (proof.get('kind') != 'embedded-type06-elapsed0' or proof.get('primitive') != 'type06'
            or type(proof.get('elapsed')) is not int or proof['elapsed'] != 0
            or proof.get('source') != backend.SOURCE or proof.get('source_fingerprint') != fingerprint
            or proof.get('source_gltf_sha256') != fingerprint['gltf_sha256']
            or proof.get('output') != str(destination.relative_to(root))
            or proof.get('inspection_state') != backend.STATE):
        raise ValueError('type06 inspection source or selected state changed')
    derived_glb, image = artifact['glb'], artifact['preview']
    if (not isinstance(derived_glb, bytes) or not derived_glb.startswith(b'glTF')
            or not isinstance(image, bytes) or not image.startswith(b'\x89PNG\r\n\x1a\n')
            or digest(derived_glb) != proof.get('derived_glb_sha256')
            or digest(image) != proof.get('preview_sha256') or artifact['scope'] != backend.SCOPE):
        raise ValueError('type06 inspection bytes or scope changed')
    raw_glb, evidence = pack_glb(source)
    if (evidence['source_fingerprint'] != fingerprint
            or evidence['glb_sha256'] != proof.get('source_glb_sha256')):
        raise ValueError('type06 original source GLB changed')
    derived = destination / backend.DERIVED_GLTF
    derived_fingerprint = preview_fingerprint(derived)
    packed, derived_evidence = pack_glb(derived)
    if packed != derived_glb or derived_evidence['source_fingerprint'] != derived_fingerprint:
        raise ValueError('type06 derived GLB differs from its current glTF')
    validation = {'source': validate_source(root, source, fingerprint),
                  'derived': validate_source(root, derived, derived_fingerprint)}
    manifest = source.parent.parent / 'manifest.json'
    manifest_bytes = manifest.read_bytes()
    geometry = json.loads(manifest_bytes)
    if (geometry.get('family') != 'rom-embedded-effect-geometry'
            or geometry.get('object_type') != 6 or geometry.get('indexed_model_bank') is not None
            or geometry.get('source_vertex_address') != '0x8008D538'
            or geometry.get('vertex_count') != 4 or geometry.get('triangle_count') != 3):
        raise ValueError('type06 primitive identity changed')
    name = 'embedded-type06-8008d538'
    record = {'name': name, 'label': 'Tapered effect primitive — type 6',
        'category': 'parts-effects', 'aliases': ['embedded primitive', 'type06', '8008D538', 'elapsed0'],
        'note': '4 vertices and 3 triangles from ROM game data, outside the indexed model banks. ' + artifact['scope'],
        'source': backend.SOURCE, **evidence, 'file': name + '.glb',
        'download_file': name + '-elapsed0.glb', 'download_format': 'glb',
        'download_sha256': digest(derived_glb), 'preview': str((previews / (name + '.png')).relative_to(root)),
        'preview_sha256': digest(image), 'status': 'ready-for-inspection', 'native_visual_parity': 'incomplete',
        'rom_source': {'kind': 'embedded-effect-primitive', 'source': 'ROM', 'capture_inputs': [],
            'object_type': 6, 'vertex_address': '0x8008D538', 'manifest_sha256': digest(manifest_bytes),
            'normalized_sha1': geometry['normalized_sha1']},
        'embedded_type06_inspection': copy.deepcopy(proof), 'independent_validation': validation}
    pending = [(output / record['file'], raw_glb), (output / record['download_file'], derived_glb),
               (root / record['preview'], image)]

    def current(path, expected):
        tools = validator_identity(root)[3]
        if (preview_fingerprint(source) != fingerprint or preview_fingerprint(derived) != derived_fingerprint
                or manifest.read_bytes() != manifest_bytes
                or any(value['tools'] != tools for value in validation.values())):
            raise ValueError('type06 source or validation tools changed before publication')
        return backend.inspection_artifact_current(path, expected)

    return record, pending, (current, destination, proof)
