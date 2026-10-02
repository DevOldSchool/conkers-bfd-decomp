"""Derive gallery representation from already verified scene component evidence.

Call after the publisher's independent final provenance checks. The caller must
supply current collect_review records and freshly verified curated records;
this module does not replace ROM, source, review-decision or file validation.
"""
from __future__ import annotations

import copy
import re
from pathlib import PurePosixPath


def _identity(values, label):
    if (not isinstance(values, (list, tuple)) or len(values) != 3
            or any(type(v) is not int or v < 0 for v in values)):
        raise ValueError(f'invalid {label} model identity')
    return tuple(values)


def _sha256(value):
    return isinstance(value, str) and re.fullmatch(r'[0-9a-f]{64}', value) is not None


def _fingerprint(value):
    return (isinstance(value, dict) and _sha256(value.get('gltf_sha256'))
            and isinstance(value.get('dependencies_sha256'), dict)
            and all(isinstance(uri, str) and _sha256(sha)
                    for uri, sha in value['dependencies_sha256'].items()))


def _source_identity(source):
    if (not isinstance(source, dict) or source.get('source') != 'ROM'
            or source.get('capture_inputs') != []
            or source.get('kind') == 'static-scene-assembly'
            or not _sha256(source.get('manifest_sha256'))):
        raise ValueError('represented review source lacks ordinary ROM provenance')
    return _identity([source.get(k) for k in ('bank', 'entry', 'segment')], 'review provenance')


def _base_note(record):
    note = record.get('note', '')
    old = record.get('review_representation_note')
    if not isinstance(note, str) or (old is not None and not isinstance(old, str)):
        raise ValueError('invalid assembly representation note')
    if old:
        if note == old:
            return ''
        if not note.endswith(' ' + old):
            raise ValueError('previous assembly representation note changed')
        return note[:-(len(old) + 1)]
    return note


def apply_representation(curated, review_records):
    """Update presentation metadata in place; return derived representation counts.

    Only drawable, currently deferred, material-complete review records qualify.
    A visible scene assembly must contain the exact source identity, path,
    dependency fingerprint, nested ROM provenance and face count. Conflicting
    evidence raises before any record is changed. Multiple containing assemblies
    are retained as a sorted gallery_represented_by list; no arbitrary winner is
    chosen. Source exports and review/native-appearance decisions are untouched.
    """
    candidates = {}
    for record in review_records:
        if record.get('review_status') != 'review-deferred':
            continue
        faces, missing = record.get('face_count'), record.get('missing_material_faces')
        if type(faces) is not int or faces < 0 or type(missing) is not int or missing < 0:
            raise ValueError('invalid represented review face counts')
        if faces == 0 or missing:
            continue
        key = _identity([record.get(k) for k in ('bank', 'entry', 'segment')], 'review')
        if _source_identity(record.get('rom_source')) != key:
            raise ValueError('represented review identity differs from ROM provenance')
        if key in candidates:
            raise ValueError('duplicate represented review model identity')
        if (not isinstance(record.get('source'), str) or not record['source']
                or not _fingerprint(record.get('source_fingerprint'))
                or not isinstance(record.get('name'), str) or not record['name']
                or not isinstance(record.get('file'), str) or not record['file']
                or not isinstance(record.get('label'), str)):
            raise ValueError('represented review lacks source or gallery metadata')
        candidates[key] = record

    relations = {key: [] for key in candidates}
    assemblies, seen_names = [], set()
    for target in curated:
        proof = target.get('rom_source', {})
        if proof.get('kind') != 'static-scene-assembly':
            continue
        if target.get('gallery_replaced_by') is not None or target.get('gallery_represented_by'):
            continue
        name = target.get('name')
        if not isinstance(name, str) or not name or name in seen_names:
            raise ValueError('duplicate or invalid containing assembly name')
        seen_names.add(name)
        if (proof.get('source') != 'ROM' or proof.get('capture_inputs') != []
                or not _sha256(proof.get('manifest_sha256'))
                or type(proof.get('scene_index')) is not int or proof['scene_index'] < 0
                or not isinstance(proof.get('components'), list)):
            raise ValueError('containing assembly lacks verified ROM components')
        contained, seen_models = [], set()
        for component in proof['components']:
            key = _identity(component.get('model'), 'assembly component')
            if key in seen_models:
                raise ValueError('duplicate model in assembly component evidence')
            seen_models.add(key)
            record = candidates.get(key)
            if record is None:
                continue
            if (component.get('path') != record['source']
                    or component.get('fingerprint') != record['source_fingerprint']
                    or component.get('rom_source') != record['rom_source']
                    or component.get('face_count') != record['face_count']):
                raise ValueError(f'assembly component evidence conflicts with review source: {name}, {key}')
            relations[key].append(name)
            contained.append(record)
        assemblies.append((target, contained))

    # Prepare every mutation first so a bad alias/note cannot leave partial links.
    updates = []
    for target, contained in assemblies:
        aliases = target.get('aliases', [])
        if not isinstance(aliases, list) or any(not isinstance(v, str) for v in aliases):
            raise ValueError('invalid containing assembly aliases')
        aliases = list(aliases)
        components = []
        for record in sorted(contained, key=lambda r: (r['bank'], r['entry'], r['segment'])):
            key = (record['bank'], record['entry'], record['segment'])
            rom_id = f'{key[0]:02x}:{key[1]:04d}:{key[2]:02d}'
            for alias in (record['label'], record['name'], record['file'],
                          PurePosixPath(record['file']).name, rom_id):
                if alias not in aliases:
                    aliases.append(alias)
            components.append({'model': list(key), 'review_name': record['name'],
                               'review_file': record['file'], 'rom_id': rom_id})
        note = _base_note(target)
        suffix = ''
        if components:
            count = len(components)
            noun = 'component' if count == 1 else 'components'
            suffix = (f'This scene assembly includes {count} source {noun} from Extracted review. '
                      'Their individual review records and unresolved native appearance are retained.')
            note = (note + ' ' if note else '') + suffix
        updates.append((target, aliases, components, note, suffix))

    for record in review_records:
        record.pop('gallery_represented_by', None)
    for key, names in relations.items():
        if names:
            candidates[key]['gallery_represented_by'] = sorted(names)
    for target, aliases, components, note, suffix in updates:
        target['aliases'] = aliases
        target['note'] = note
        if components:
            target['represented_review_components'] = copy.deepcopy(components)
            target['review_representation_note'] = suffix
        else:
            target.pop('represented_review_components', None)
            target.pop('review_representation_note', None)
    return {'represented_review_count': sum(bool(v) for v in relations.values()),
            'representing_assembly_count': sum(bool(rows) for _, rows in assemblies)}
