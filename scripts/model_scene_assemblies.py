"""Static inspection scenes composed from ROM models and ROM placements."""
from __future__ import annotations

import base64
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts import model_assets as models
from scripts.model_preview_evidence import preview_fingerprint
from scripts.model_scene_consumers import build_scene_graph

FAMILY = 'rom-static-scene-assemblies'
IDENTITY = [1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1.]
SCOPE = ('Static inspection selection; ROM geometry, textures and placement transforms. '
         'Conditional visibility, animation, lighting, fog and native appearance remain unresolved.')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def rom_scenes(profile='us', rom=None):
    _, _, sha1, bundles, _ = models.load_model_bundles(profile, rom, 4)
    placements, _ = models.load_object_placement_manifest(profile, rom, include_files=False)
    scenes, _ = build_scene_graph(bundles, placements)
    return sha1, {s['scene_index']: s for s in scenes}


def select_instances(scene, selection):
    """Keep source identities on nodes; never treat initial collision slot 3 as visible."""
    excluded = {tuple(r['model']): r['reason'] for r in selection.get('exclude_models', [])}
    if any(not reason for reason in excluded.values()):
        raise ValueError('scene omissions require a review reason')
    instances, omissions, matched = [], [], set()
    for slot in scene['initial_slots']:
        source = [4, scene['scene_index'], slot['segment']]
        if slot['segment'] == 3:
            omissions.append({'model': source, 'reason': 'collision-only initial slot'})
            continue
        if not any(c['kind'] == 'conditional-display-list-submission' for c in slot['consumers']):
            raise ValueError('initial scene slot lacks a rendering consumer')
        instances.append({'model': source, 'kind': 'initial-scene-slot', 'slot': slot['segment'],
                          'model_sha1': slot['model_sha1'], 'matrix': IDENTITY})
    for table in scene['placement_tables']:
        for record in table['records']:
            source = record.get('model_source')
            if not source or source[0] not in (3, 4):
                raise ValueError('scene has an unresolved placement')
            source = source if len(source) == 3 else [*source, 0]
            instances.append({'model': source, 'kind': 'object-placement',
                              'placement_bank': table['bank_index'], 'record': record,
                              'matrix': models.placement_transform_matrix(record)})
    selected = []
    for instance in instances:
        key = tuple(instance['model'])
        if key in excluded:
            matched.add(key)
            omissions.append({**instance, 'reason': excluded[key]})
        else:
            selected.append(instance)
    if matched != set(excluded) or not selected:
        raise ValueError('scene selection contains an absent exclusion or no visible instances')
    return selected, omissions


def source_model(model_root, key, rom_sha1):
    from scripts.model_inspection import resource, rom_source_evidence

    bank, entry, segment = key
    directory = model_root / f'us-bank-{bank:02x}-preview'
    manifest = json.loads((directory / 'manifest.json').read_text())
    if manifest['normalized_sha1'] != rom_sha1:
        raise ValueError('scene component belongs to another ROM')
    record, = [r for r in manifest['models'] if (r['bank_entry'], r['segment']) == (entry, segment)]
    for run in record['material_runs']:
        formula = run.get('combine_formula')
        if (run['face_count'] and run['status'] != 'untextured' and not run.get('texture')
                and (formula is None or set(formula['inputs']) & {'TEXEL0', 'TEXEL1'})):
            raise ValueError(f'scene component has unresolved materials: {key}')
    source = (directory / record['gltf_file']).resolve()
    evidence = rom_source_evidence(source)
    document = json.loads(source.read_text())
    # The placement encoder accepts one untransformed static mesh. Fail closed
    # if a future component needs skinning, morphs or another material channel.
    if (document.get('skins') or len(document.get('meshes', [])) != 1
            or document.get('scene', 0) != 0 or document['scenes'][0]['nodes'] != [0]
            or len(document.get('nodes', [])) != 1
            or set(document['nodes'][0]) - {'mesh', 'name'}
            or document['nodes'][0].get('mesh') != 0
            or set(document.get('extensionsUsed', [])) - {'KHR_materials_unlit'}
            or any('targets' in p for p in document['meshes'][0]['primitives'])):
        raise ValueError(f'scene component requires unsupported composition: {key}')
    for material in document['materials']:
        if any(k in material for k in ('normalTexture', 'occlusionTexture', 'emissiveTexture')) or \
                'metallicRoughnessTexture' in material.get('pbrMetallicRoughness', {}):
            raise ValueError('scene composer only supports existing base-colour materials')
    fingerprint = preview_fingerprint(source)
    for image in document.get('images', []):
        data = resource(source, image['uri'])
        if not data.startswith(b'\x89PNG\r\n\x1a\n'):
            raise ValueError('scene component image is not PNG')
        image['uri'] = 'data:image/png;base64,' + base64.b64encode(data).decode()
    binary = resource(source, document['buffers'][0]['uri'])
    if preview_fingerprint(source) != fingerprint:
        raise ValueError('scene component changed while composing')
    return (document, binary), {'model': list(key), 'path': str(source.relative_to(ROOT)),
        'fingerprint': fingerprint, 'rom_source': evidence, 'face_count': record['face_count']}


def compose(scene, selection, model_root, rom_sha1):
    instances, omissions = select_instances(scene, selection)
    keys = list(dict.fromkeys(tuple(i['model']) for i in instances))
    sources, provenance = {}, []
    for index, key in enumerate(keys):
        sources[index], evidence = source_model(model_root, key, rom_sha1)
        provenance.append(evidence)
    # Reuse the existing mesh/material/buffer relocation. Replace its bank-local
    # node metadata with the exact mixed-bank source and placement identities.
    placeholders = [{'index': i, 'model_index': keys.index(tuple(row['model'])), 'sha1': '',
                     'position_s16_00': [0, 0, 0], 'rotation_degrees_s16_06': [0, 0, 0],
                     'scale_f32_20': [1, 1, 1]} for i, row in enumerate(instances)]
    encoded, binary = models.encode_placement_scene_gltf(scene['scene_index'], placeholders, sources)
    document = json.loads(encoded)
    document['asset']['generator'] = 'conker ROM static scene assembler'
    document['scenes'][0]['name'] = f"ROM scene {scene['scene_index']} — static selection"
    for node, instance in zip(document['nodes'], instances):
        bank, entry, segment = instance['model']
        suffix = (f"slot{instance['slot']}" if instance['kind'] == 'initial-scene-slot' else
                  f"bank{instance['placement_bank']:02x}_record{instance['record']['index']:03d}")
        node.update(name=f'bank{bank:02x}_{entry:04d}_{segment:02d}_{suffix}',
                    matrix=instance['matrix'], extras=instance)
    document['extras'] = {'source': 'ROM', 'sceneIndex': scene['scene_index'],
        'rotationOrder': 'YZX', 'coordinateConversion': 'none-native-axes', 'scope': SCOPE}
    record = {'scene_index': scene['scene_index'], 'selection': selection, 'components': provenance,
        'instance_count': len(instances), 'unique_model_count': len(keys),
        'face_count': sum(provenance[keys.index(tuple(i['model']))]['face_count'] for i in instances),
        'omissions': omissions, 'gltf_file': f"geometry/scene-{scene['scene_index']:02d}.gltf"}
    return (json.dumps(document, indent=2) + '\n').encode(), binary, record


def export_assemblies(config_path, model_root, output, profile='us', rom=None):
    config = json.loads(config_path.read_text())
    if config.get('schema_version') != 1:
        raise ValueError('unsupported scene assembly configuration')
    sha1, scenes = rom_scenes(profile, rom)
    selections = config['scenes']
    indices = [s['scene_index'] for s in selections]
    if len(indices) != len(set(indices)):
        raise ValueError('duplicate scene assembly selection')
    manifest = {'schema_version': 1, 'family': FAMILY, 'profile': profile, 'normalized_sha1': sha1,
        'model_root': str(model_root.relative_to(ROOT)), 'config': str(config_path.relative_to(ROOT)),
        'config_sha256': digest(config_path.read_bytes()), 'scene_inputs': [scenes[i] for i in indices],
        'models': [], 'scope': SCOPE}
    pending = []
    for selection in selections:
        gltf, binary, record = compose(scenes[selection['scene_index']], selection, model_root, sha1)
        path = output / record['gltf_file']
        pending.extend([(path, gltf), (path.with_suffix('.bin'), binary)])
        manifest['models'].append(record)
    from scripts.model_inspection import write_if_changed
    for path, data in pending:
        write_if_changed(path, data)
    write_if_changed(output / 'manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    return manifest


def verify_assemblies(root, *, fresh_rom=False):
    """Recompose every byte; validation additionally compares the scene inputs to ROM."""
    manifest_bytes = (root / 'manifest.json').read_bytes()
    manifest = json.loads(manifest_bytes)
    if manifest.get('family') != FAMILY or manifest.get('profile') != 'us':
        raise ValueError('invalid ROM scene assembly manifest')
    config_path = ROOT / manifest['config']
    if digest(config_path.read_bytes()) != manifest['config_sha256']:
        raise ValueError('scene selection changed since export')
    selections = json.loads(config_path.read_text())['scenes']
    if selections != [r['selection'] for r in manifest['models']]:
        raise ValueError('scene assembly differs from reviewed selections')
    scenes = {s['scene_index']: s for s in manifest['scene_inputs']}
    if fresh_rom:
        sha1, actual = rom_scenes()
        if sha1 != manifest['normalized_sha1'] or any(s != actual[i] for i, s in scenes.items()):
            raise ValueError('scene assembly inputs differ from ROM')
    for record in manifest['models']:
        encoded, binary, current = compose(scenes[record['scene_index']], record['selection'],
            ROOT / manifest['model_root'], manifest['normalized_sha1'])
        path = root / record['gltf_file']
        if current != record or path.read_bytes() != encoded or path.with_suffix('.bin').read_bytes() != binary:
            raise ValueError('scene assembly differs from its ROM components or transforms')
    return {'manifest_sha256': digest(manifest_bytes), 'scene_count': len(manifest['models']),
            'instance_count': sum(r['instance_count'] for r in manifest['models'])}


def inspection_evidence(source, *, verification_cache=None):
    """Share whole-set recomposition only within one caller-owned read phase."""
    root = source.parent.parent
    verified = verification_cache.get(root) if verification_cache is not None else None
    if verified is None:
        verified = verify_assemblies(root)
        if verification_cache is not None:
            verification_cache[root] = verified
    manifest_bytes = (root / 'manifest.json').read_bytes()
    if digest(manifest_bytes) != verified['manifest_sha256']:
        raise ValueError('scene assembly manifest changed during inspection')
    manifest = json.loads(manifest_bytes)
    record, = [r for r in manifest['models'] if r['gltf_file'] == str(source.relative_to(root))]
    return {'source': 'ROM', 'kind': 'static-scene-assembly', 'capture_inputs': [],
            'scene_index': record['scene_index'], 'components': record['components'], **verified}
