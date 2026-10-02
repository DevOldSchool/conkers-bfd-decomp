"""Represent current review sources by equal, visible standard glTF exports.

Call only after independent publication validation. The decision binder supplies
presentation_equivalent_to solely from current fingerprint-bound decisions. This
module rechecks files and ordinary ROM provenance; it never equates ROM consumers,
placements, native dynamic state or gameplay identities.
"""
from __future__ import annotations

import copy
import hashlib
import json
import re
from pathlib import Path, PurePosixPath

try:
    from scripts.model_batch import missing_material, model_fingerprint
    from scripts.model_inspection import resource, rom_source_evidence
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    from model_batch import missing_material, model_fingerprint
    from model_inspection import resource, rom_source_evidence
    from model_preview_evidence import preview_fingerprint


SUPPORTED_EXTENSIONS = {'KHR_materials_unlit'}


def _hash(value, length=64):
    return isinstance(value, str) and re.fullmatch(r'[0-9a-f]{' + str(length) + '}', value) is not None


def _identity(proof):
    if (not isinstance(proof, dict) or proof.get('source') != 'ROM'
            or proof.get('capture_inputs') != [] or proof.get('kind') is not None
            or not _hash(proof.get('manifest_sha256'))):
        raise ValueError('equivalent source lacks ordinary ROM provenance')
    key = tuple(proof.get(k) for k in ('bank', 'entry', 'segment'))
    if (any(type(v) is not int or v < 0 for v in key) or key[0] not in (1, 3, 4, 9)):
        raise ValueError('invalid equivalent ROM model identity')
    return key


def _source_record(record, root):
    key = _identity(record.get('rom_source'))
    fp = record.get('source_fingerprint')
    if (not isinstance(fp, dict) or not _hash(fp.get('gltf_sha256'))
            or not isinstance(fp.get('dependencies_sha256'), dict)
            or any(not isinstance(uri, str) or not _hash(sha)
                   for uri, sha in fp['dependencies_sha256'].items())):
        raise ValueError('equivalent source lacks a complete fingerprint')
    for field in ('source', 'name', 'file', 'label'):
        if not isinstance(record.get(field), str) or not record[field]:
            raise ValueError('equivalent source lacks gallery metadata')
    path = (root / record['source']).resolve()
    if path.suffix != '.gltf' or not path.is_relative_to(root):
        raise ValueError('equivalent source is outside the glTF workspace')
    if preview_fingerprint(path) != fp or rom_source_evidence(path) != record['rom_source']:
        raise ValueError('stale equivalent source fingerprint or ROM provenance')
    manifest = json.loads((path.parent.parent / 'manifest.json').read_text())
    if not _hash(manifest.get('normalized_sha1'), 40):
        raise ValueError('equivalent source lacks normalized ROM identity')
    relative = str(path.relative_to(path.parent.parent))
    model, = [m for m in manifest['models']
              if relative in (m.get('gltf_file'), m.get('bind_gltf_file'))]
    if (manifest.get('bank_index'), model['bank_entry'], model['segment']) != key:
        raise ValueError('equivalent source identity differs from its manifest record')
    return path, key, model, manifest['normalized_sha1']


def _verify(record, root):
    path, key, model, rom = _source_record(record, root)
    faces = model.get('face_count')
    if (type(faces) is not int or faces <= 0
            or any(missing_material(run) for run in model['material_runs'])):
        raise ValueError('equivalent target or source has incomplete materials or geometry')
    return path, key, faces, rom


def _canonical(path):
    document = json.loads(path.read_text())
    if document.get('asset', {}).get('version') != '2.0':
        raise ValueError('equivalence requires standard glTF 2.0')
    extensions = set(document.get('extensionsUsed', [])) | set(document.get('extensionsRequired', []))

    def inspect(value):
        if isinstance(value, dict):
            for key, item in value.items():
                if key == 'extensions':
                    if not isinstance(item, dict):
                        raise ValueError('invalid glTF extension metadata')
                    extensions.update(item)
                if key != 'extras':
                    inspect(item)
        elif isinstance(value, list):
            for item in value:
                inspect(item)

    inspect(document)
    if extensions - SUPPORTED_EXTENSIONS:
        return None
    document.pop('asset')

    def clean(value):
        if isinstance(value, dict):
            return {key: clean(item) for key, item in value.items() if key not in ('name', 'extras')}
        if isinstance(value, list):
            return [clean(item) for item in value]
        return value

    raw_resources = []
    for item in document.get('buffers', []) + document.get('images', []):
        if 'uri' in item:
            data = resource(path, item['uri'])
            # The exact byte tuple is compared too; hashes are compact metadata.
            item['uri'] = {'sha256': hashlib.sha256(data).hexdigest(), 'bytes': len(data)}
            raw_resources.append(data)
    document = clean(document)
    digest = hashlib.sha256(json.dumps(document, sort_keys=True, separators=(',', ':')).encode()).hexdigest()
    return document, tuple(raw_resources), digest


def _target_base(target):
    aliases = target.get('aliases', [])
    old_aliases = target.get('equivalence_search_aliases', [])
    if (not isinstance(aliases, list) or not isinstance(old_aliases, list)
            or any(not isinstance(v, str) for v in aliases + old_aliases)):
        raise ValueError('invalid equivalence search aliases')
    aliases = [v for v in aliases if v not in old_aliases]
    note, old = target.get('note', ''), target.get('equivalence_representation_note', '')
    if not isinstance(note, str) or not isinstance(old, str):
        raise ValueError('invalid equivalence representation note')
    if old:
        if note == old:
            note = ''
        elif note.endswith(' ' + old):
            note = note[:-(len(old) + 1)]
        else:
            raise ValueError('previous equivalence representation note changed')
    return aliases, note


def bind_equivalence_decisions(review_records, root: Path, reviews_path: Path):
    """Bind explicit intent only while its full source review fingerprint matches.

    Stale decisions bind nothing. Stale caller evidence, conflicting source
    identities and malformed current target names fail before records change.
    This stays outside the thumbnail worker, whose own identity is cache-bound.
    """
    root = Path(root).resolve()
    path = (root / reviews_path).resolve()
    decision_bytes = path.read_bytes()
    decisions = json.loads(decision_bytes).get('models')
    if not isinstance(decisions, dict):
        raise ValueError('invalid equivalence review decisions')
    updates, checked = [], []
    for source in review_records:
        if source.get('review_status') != 'review-deferred':
            continue
        key = tuple(source.get(k) for k in ('bank', 'entry', 'segment'))
        if any(type(v) is not int or v < 0 for v in key):
            raise ValueError('invalid equivalent review identity')
        decision = decisions.get(f'{key[0]:02x}:{key[1]:04d}:{key[2]:02d}', {})
        if (decision.get('decision') != 'review-deferred'
                or 'presentation_equivalent_to' not in decision):
            continue
        source_path, source_key, model, _ = _source_record(source, root)
        if source_key != key:
            raise ValueError('equivalent review identity differs from its source')
        checked.append((source_path, source))
        if model_fingerprint(model, source_path) != decision.get('fingerprint'):
            continue
        name = decision['presentation_equivalent_to']
        if not isinstance(name, str) or re.fullmatch(r'[a-z0-9]+(?:-[a-z0-9]+)*', name) is None:
            raise ValueError('invalid explicit equivalence target name')
        updates.append((source, name))
    if path.read_bytes() != decision_bytes:
        raise ValueError('equivalence decisions changed while binding')
    for source_path, source in checked:
        if (preview_fingerprint(source_path) != source['source_fingerprint']
                or rom_source_evidence(source_path) != source['rom_source']):
            raise ValueError('equivalence source changed while binding')
    for source in review_records:
        source.pop('presentation_equivalent_to', None)
    for source, name in updates:
        source['presentation_equivalent_to'] = name
    return {'bound_equivalence_count': len(updates)}


def apply_equivalence(curated, review_records, root: Path):
    """Derive links atomically; preserve source exports and review/native claims.

    Unsupported extensions keep the review card visible. An otherwise eligible
    claim with missing, hidden, blocked, stale or unequal targets fails closed.
    Prior derived links and search metadata are rebuilt so repeated calls are
    idempotent and newly ineligible sources become visible again.
    """
    root = Path(root).resolve()
    targets = {}
    for target in curated:
        name = target.get('name')
        if not isinstance(name, str) or not name or name in targets:
            raise ValueError('duplicate or invalid equivalence target name')
        targets[name] = target
    relations, checked, source_updates, seen = {}, {}, [], set()
    for source in review_records:
        if (source.get('review_status') != 'review-deferred'
                or source.get('gallery_represented_by')
                or source.get('gallery_replaced_by') is not None):
            continue
        name = source.get('presentation_equivalent_to')
        if name is None:
            continue
        faces, missing = source.get('face_count'), source.get('missing_material_faces')
        if type(faces) is not int or faces < 0 or type(missing) is not int or missing < 0:
            raise ValueError('invalid equivalent review face counts')
        if not faces or missing:
            continue
        target = targets.get(name) if isinstance(name, str) else None
        if (target is None or target.get('gallery_replaced_by') is not None
                or target.get('gallery_represented_by') or target.get('gallery_equivalent_to')
                or target.get('review_status') is not None
                or target.get('status') != 'ready-for-inspection'):
            raise ValueError('equivalence target is missing, hidden or not curated')
        source_path, source_id, actual_faces, source_rom = _verify(source, root)
        target_path, target_id, target_faces, target_rom = _verify(target, root)
        if (any(type(source.get(k)) is not int for k in ('bank', 'entry', 'segment'))
                or source_id != tuple(source.get(k) for k in ('bank', 'entry', 'segment'))
                or source_id == target_id or faces != actual_faces or faces != target_faces
                or source_rom != target_rom or source_id in seen):
            raise ValueError('equivalent source identity or face count conflicts')
        seen.add(source_id)
        checked[source_path] = source
        checked[target_path] = target
        left, right = _canonical(source_path), _canonical(target_path)
        if left is None or right is None:
            continue
        if left[:2] != right[:2]:
            raise ValueError('claimed standard glTF presentations differ')
        rom_id = f'{source_id[0]:02x}:{source_id[1]:04d}:{source_id[2]:02d}'
        evidence = {'model': list(source_id), 'rom_id': rom_id,
                    'review_name': source['name'], 'review_file': source['file'],
                    'source': source['source'], 'source_fingerprint': copy.deepcopy(source['source_fingerprint']),
                    'rom_source': copy.deepcopy(source['rom_source']), 'canonical_sha256': left[2]}
        relations.setdefault(name, []).append((source, evidence))
        source_updates.append((source, name))

    updates = []
    derived_fields = ('equivalent_review_sources', 'equivalence_search_aliases', 'equivalence_representation_note')
    for name, target in targets.items():
        if name not in relations and not any(field in target for field in derived_fields):
            continue
        aliases, note = _target_base(target)
        added, evidence = [], []
        for source, item in sorted(relations.get(name, []), key=lambda row: row[1]['model']):
            for alias in (source['label'], source['name'], source['file'],
                          PurePosixPath(source['file']).name, item['rom_id']):
                if alias not in aliases:
                    aliases.append(alias)
                    added.append(alias)
            evidence.append(item)
        suffix = ''
        if evidence:
            count = len(evidence)
            noun = 'record has' if count == 1 else 'records have'
            suffix = (f'{count} distinct ROM source {noun} this same stored glTF presentation. '
                      'Their Extracted review decisions and source identities are retained; '
                      'gameplay consumers, placements, dynamic state and native appearance are not equated.')
            note = (note + ' ' if note else '') + suffix
        updates.append((target, aliases, note, added, evidence, suffix))
    for path, record in checked.items():
        if (preview_fingerprint(path) != record['source_fingerprint']
                or rom_source_evidence(path) != record['rom_source']):
            raise ValueError('equivalent inputs changed during comparison')

    for source in review_records:
        source.pop('gallery_equivalent_to', None)
    for source, name in source_updates:
        source['gallery_equivalent_to'] = name
    for target, aliases, note, added, evidence, suffix in updates:
        target['aliases'], target['note'] = aliases, note
        for field in derived_fields:
            target.pop(field, None)
        if evidence:
            target['equivalent_review_sources'] = evidence
            target['equivalence_search_aliases'] = added
            target['equivalence_representation_note'] = suffix
    return {'equivalent_review_count': len(source_updates), 'equivalent_target_count': len(relations)}
