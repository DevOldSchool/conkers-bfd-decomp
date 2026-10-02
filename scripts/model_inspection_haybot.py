"""Select one verified cyclic Haybot appearance on its existing gallery card."""
from __future__ import annotations

import copy


def prepare_haybot(options, records, root, output, pending):
    try:
        from scripts import model_haybot_inspection as backend
        from scripts.model_inspection import digest
        from scripts.model_inspection_options import haybot_output
        from scripts.model_preview_evidence import preview_fingerprint
    except ModuleNotFoundError:
        import model_haybot_inspection as backend
        from model_inspection import digest
        from model_inspection_options import haybot_output
        from model_preview_evidence import preview_fingerprint
    destination = haybot_output(options, root)
    name = 'haybot-rom-defaults'
    candidates = [r for r in records if r.get('name') == name]
    if len(candidates) != 1:
        raise ValueError('Haybot inspection requires one current curated record')
    record = candidates[0]
    source = record.get('rom_source', {})
    if (record.get('category') != 'characters' or record.get('status') != 'ready-for-inspection'
            or record.get('native_visual_parity') != 'incomplete'
            or record.get('file') != name + '.glb' or record.get('source') != backend.SOURCE
            or source.get('source') != 'ROM' or source.get('kind') is not None
            or (source.get('bank'), source.get('entry'), source.get('segment')) != (1, 75, 0)
            or source.get('capture_inputs') != []
            or any(record.get(k) for k in ('gallery_replaced_by', 'gallery_represented_by', 'gallery_equivalent_to'))):
        raise ValueError('Haybot inspection identity or scope changed')
    raw = [data for path, data in pending if path == output / record['file']]
    if len(raw) != 1 or digest(raw[0]) != record.get('glb_sha256'):
        raise ValueError('Haybot inspection raw GLB evidence changed')
    artifact = backend.inspection_artifact(destination)
    proof, blend, image, scope = (artifact[k] for k in ('proof', 'blend', 'preview', 'scope'))
    if (not isinstance(proof, dict) or proof.get('kind') != 'haybot-selected-phase0'
            or proof.get('entry') != 75 or type(proof.get('phase')) is not int or proof['phase'] != 0
            or proof.get('descriptor') != 15 or proof.get('inspection_state') != backend.STATE
            or proof.get('output') != str(destination.relative_to(root))
            or proof.get('source') != record['source']
            or proof.get('source_fingerprint') != record['source_fingerprint']
            or proof.get('source_gltf_sha256') != record['source_fingerprint']['gltf_sha256']
            or proof.get('source_glb_sha256') != record['glb_sha256']
            or preview_fingerprint(root / record['source']) != record['source_fingerprint']):
        raise ValueError('Haybot artifact does not match the current source or selected phase')
    if (not isinstance(blend, bytes) or not blend or not isinstance(image, bytes)
            or not image.startswith(b'\x89PNG\r\n\x1a\n') or scope != backend.SCOPE
            or digest(blend) != proof.get('blend_sha256') or digest(image) != proof.get('preview_sha256')):
        raise ValueError('Haybot inspection bytes or scope changed')
    if not record.get('preview'):
        raise ValueError('Haybot inspection requires the current preview')
    target = root / record['preview']
    if sum(path == target for path, _ in pending) != 1:
        raise ValueError('Haybot preview publication is ambiguous')
    download = name + '-phase0.blend'
    pending[:] = [(p, b) for p, b in pending if p != target]
    pending.extend(((output / download, blend), (target, image)))
    record.update(download_file=download, download_sha256=digest(blend), download_format='blend',
                  preview_sha256=digest(image), haybot_inspection=copy.deepcopy(proof),
                  label='Haybot — selected texture phase and original animations',
                  note=scope + ' Original ROM-default export: ' + record['note'])
    return backend.inspection_artifact_current, destination, proof
