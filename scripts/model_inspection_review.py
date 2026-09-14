"""Expose remaining ROM exports for review without changing curated acceptance."""
from __future__ import annotations

import hashlib
import json
import shutil
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.model_preview_evidence import preview_fingerprint

LABELS = {'review-deferred': 'Fragment or variant', 'review-needed': 'Needs review',
          'material-blocked': 'Material issues', 'appearance-blocked': 'Appearance issues',
          'no-drawable-geometry': 'No drawable faces'}


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write(path, value):
    from scripts.model_inspection import write_if_changed
    write_if_changed(path, (json.dumps(value, indent=2) + '\n').encode())


def collect_review(config, curated, validated_files):
    from scripts.model_batch import missing_material, model_fingerprint, model_key
    from scripts.model_inspection import rom_source_evidence
    published = {(r['rom_source']['bank'], r['rom_source']['entry'], r['rom_source']['segment'])
                 for r in curated if r.get('rom_source', {}).get('kind') != 'static-scene-assembly'}
    reviews = json.loads((ROOT / config['reviews']).read_text())['models']
    records = []
    for bank in (1, 3, 4, 9):
        directory = ROOT / config['model_root'] / f'us-bank-{bank:02x}-preview'
        manifest = json.loads((directory / 'manifest.json').read_text())
        for model in manifest['models']:
            entry, segment = model['bank_entry'], model['segment']
            if (bank, entry, segment) in published:
                continue
            source = (directory / model['gltf_file']).resolve()
            fingerprint = preview_fingerprint(source)
            evidence = rom_source_evidence(source)
            validated = validated_files.get(str(source))
            if (not validated or validated.get('input_fingerprint') != fingerprint
                    or any(validated['checks'].get(k, {}).get('status') != 'passed' for k in ('gltf', 'blender'))):
                raise ValueError(f'review export needs current file validation: {source}')
            key = model_key(bank, entry, segment)
            decision = reviews.get(key, {})
            current = decision.get('fingerprint') == model_fingerprint(model, source)
            missing = [r for r in model['material_runs'] if missing_material(r)]
            status = ('no-drawable-geometry' if not model['face_count'] else
                      'material-blocked' if missing else
                      decision['decision'] if current else 'review-needed')
            if status not in LABELS:
                raise ValueError(f'unsupported extracted review state: {status}')
            missing_faces = sum(r['face_count'] for r in missing)
            reason = (decision.get('reason') if current else None) or ''
            note = f"{model['face_count']:,} exported triangles. "
            if missing:
                note += f'{missing_faces:,} triangles have unresolved materials. '
            if not model['face_count']:
                note += 'The extracted record contains no drawable faces. '
            note += reason or 'Available for visual review; native appearance is not established.'
            records.append({'name': f'review-bank{bank:02x}-{entry:04d}-{segment:02d}-rom',
                'label': f'Bank {bank:02x} / {entry:04d} / {segment:02d}', 'category': 'extracted-review',
                'review_status': status, 'review_label': LABELS[status], 'note': note,
                'bank': bank, 'entry': entry, 'segment': segment, 'face_count': model['face_count'],
                'missing_material_faces': missing_faces,
                'material_blockers': dict(Counter(r['status'] for r in missing)),
                'source': str(source.relative_to(ROOT)), 'source_fingerprint': fingerprint,
                'rom_source': evidence, 'status': 'extracted-for-review', 'native_visual_parity': 'incomplete'})
    rank = {'material-blocked': 0, 'appearance-blocked': 1, 'review-needed': 2,
            'review-deferred': 3, 'no-drawable-geometry': 4}
    return sorted(records, key=lambda r: (rank[r['review_status']], r['bank'], r['entry'], r['segment']))


def prepare_previews(records, cache, validation):
    """Render only missing thumbnails; old unbound PNGs are not freshness proof."""
    blender = Path(shutil.which('blender') or '/Applications/Blender.app/Contents/MacOS/Blender')
    identity = {'blender': digest(blender), 'renderer': digest(ROOT / 'scripts/render_model_preview_blender.py'),
                'worker': digest(Path(__file__)), 'size': 384, 'view': 'three-quarter', 'shading': 'material'}
    cache.mkdir(parents=True, exist_ok=True)
    # Authoritative render records can be reused if their source and PNG still match.
    validated_renders = {r['source']: r for r in validation['renders'] if r.get('image')}
    requests = []
    for record in records:
        if not record['face_count']:
            record['preview_unavailable'] = 'No drawable faces'
            continue
        source = ROOT / record['source']
        prior = validated_renders.get(str(source))
        if prior and prior['check'].get('current_sha256') == digest(Path(prior['image'])):
            record.update(preview=prior['image'], preview_sha256=digest(Path(prior['image'])))
            continue
        key = hashlib.sha256(json.dumps({'fingerprint': record['source_fingerprint'], **identity}, sort_keys=True).encode()).hexdigest()
        evidence_path = cache / (key + '.json')
        image = cache / (key + '.png')
        request = {'path': str(source), 'fingerprint': record['source_fingerprint'],
                   'image': str(image), 'evidence': str(evidence_path), 'key': key, **identity}
        evidence = json.loads(evidence_path.read_text()) if evidence_path.is_file() else {}
        if not (evidence.get('key') == key and image.is_file()
                and evidence.get('image_sha256') == digest(image)):
            requests.append(request)
        record['_preview_request'] = request
    if requests:
        print(f'Extracted review: rendering {len(requests)} current thumbnails', flush=True)
        workers = []
        for index in range(min(2, len(requests))):
            request_path = cache / f'worker-{index}.json'
            write(request_path, requests[index::2])
            log = (cache / f'worker-{index}.log').open('w')
            process = subprocess.Popen([str(blender), '--background', '--factory-startup', '--python-exit-code', '1',
                '--python', str(Path(__file__)), '--', str(request_path)], cwd=ROOT, stdout=log, stderr=subprocess.STDOUT)
            workers.append((process, log))
        failed = False
        for process, log in workers:
            failed |= process.wait() != 0
            log.close()
        if failed:
            raise ValueError(f'extracted review thumbnail worker failed; see {cache}')
    for record in records:
        request = record.pop('_preview_request', None)
        if request:
            evidence = json.loads(Path(request['evidence']).read_text())
            if evidence.get('key') != request['key'] or evidence.get('image_sha256') != digest(Path(request['image'])):
                raise ValueError('missing or stale extracted review thumbnail')
            record.update(preview=request['image'], preview_sha256=evidence['image_sha256'])
        if preview_fingerprint(ROOT / record['source']) != record['source_fingerprint']:
            raise ValueError('extracted review source changed during thumbnail preparation')


def prepare_review(config, curated, report, output, previews):
    from scripts.model_inspection import pack_glb
    files = {r['path']: r for r in report['files']}
    records = collect_review(config, curated, files)
    prepare_previews(records, ROOT / config['cache'], report)
    pending = []
    for record in records:
        glb, evidence = pack_glb(ROOT / record['source'])
        if evidence['source_fingerprint'] != record['source_fingerprint']:
            raise ValueError('extracted review changed before packing')
        record.update(evidence, file='review/' + record['name'] + '.glb')
        pending.append((output / record['file'], glb))
        if record.get('preview'):
            image = Path(record['preview'])
            target = previews / 'review' / (record['name'] + '.png')
            pending.append((target, image.read_bytes()))
            record['preview'] = str(target.relative_to(ROOT))
    return records, pending


def worker(request_path):
    from scripts.render_model_preview_blender import main as render
    requests = json.loads(request_path.read_text())
    for index, request in enumerate(requests):
        source = Path(request['path'])
        if preview_fingerprint(source) != request['fingerprint']:
            raise ValueError('extracted review source changed before rendering')
        render(['--input', str(source), '--output', request['image'], '--size', str(request['size']),
                '--view', request['view'], '--shading', request['shading']])
        if preview_fingerprint(source) != request['fingerprint']:
            raise ValueError('extracted review source changed while rendering')
        write(Path(request['evidence']), {'key': request['key'], 'fingerprint': request['fingerprint'],
              'image_sha256': digest(Path(request['image']))})
        print(f'Review thumbnails {index + 1}/{len(requests)}', flush=True)


if __name__ == '__main__':
    worker(Path(sys.argv[sys.argv.index('--') + 1]))
