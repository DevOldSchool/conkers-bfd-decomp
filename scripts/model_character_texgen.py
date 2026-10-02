"""Derive a guarded, neutral-pose Blender inspection of character 66.

Generated coordinates are an explicit inspection state, not a captured default.
Original source geometry, ST, images, rig and animation bytes remain preserved.
"""
from __future__ import annotations

import argparse
import copy
import hashlib
import json
import os
import shutil
import struct
import subprocess
from collections import Counter
from pathlib import Path

try:
    from scripts import model_assets as models
except ModuleNotFoundError:
    import model_assets as models

ROOT = Path(__file__).resolve().parents[1]
CONTRACT = ROOT / 'config/model-character66-texgen-inspection.json'
CONTRACT_SHA256 = 'c8f8657eae815c87bdda4cac4427b21b7075c67e33123cd281675569cb2f6df6'
ATTRIBUTE = '_CBFD_TEXGEN_NORMAL'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def encode(value):
    return (json.dumps(value, indent=2) + '\n').encode()


def contract():
    raw = CONTRACT.read_bytes()
    require(sha(raw) == CONTRACT_SHA256, 'texgen inspection contract changed')
    return json.loads(raw)


def replay(data, expected):
    """Attribute texgen at each vertex load, including retained cache entries."""
    require(sha(data) == expected['model_sha256'], 'texgen model source changed')
    geometry, _ = models.parse_character_model_geometry(data)
    cache, records, replayed = {}, [], []
    normal_base, matrix, generated, linear = None, 0, None, None
    for pc in range(0x1D60, 0x3080, 8):
        word, argument = struct.unpack_from('>II', data, pc)
        opcode = word >> 24
        if opcode == 0xD9:
            keep = word & 0xFFFFFF
            if argument & 0x40000:
                generated = True
            elif not keep & 0x40000:
                generated = False
            if argument & 0x80000:
                linear = True
            elif not keep & 0x80000:
                linear = False
        if word == 0xDA380003:
            require(argument >> 24 == 3 and (argument & 0xFFFFFF) % 64 == 0,
                    'texgen joint matrix command changed')
            matrix = (argument & 0xFFFFFF) // 64
        if word == 0xDC38000E:
            normal_base = argument
        if opcode == 1:
            count = word >> 12 & 255
            start = (word >> 1 & 127) - count
            offset = (argument & 0xFFFFFF) - 0x38
            require(count > 0 and start >= 0 and argument >> 24 == 1
                    and offset >= 0 and offset % 16 == 0 and normal_base is not None,
                    'texgen vertex load changed')
            for j in range(count):
                index, slot = offset // 16 + j, start + j
                x, y = struct.unpack_from('>bb', data, normal_base + slot * 2)
                vertex = geometry.vertices[index]
                z = vertex.flag & 255
                cache[slot] = {'load_offset': pc, 'source_vertex': index,
                               'cache_slot': slot, 'matrix_index': matrix,
                               'texgen': generated, 'linear': linear,
                               'normal_bytes': [x, y, z - 256 if z >= 128 else z],
                               'source_st': [vertex.s, vertex.t],
                               'source_position': [vertex.x, vertex.y, vertex.z]}
        if opcode == 5:
            indices = tuple(b // 2 for b in word.to_bytes(4, 'big')[1:])
        elif opcode == 6:
            indices = tuple(b // 2 for b in word.to_bytes(4, 'big')[1:]
                            + argument.to_bytes(4, 'big')[1:])
        elif 0x10 <= opcode <= 0x1F:
            indices = models.packed_four_triangle_indices(word, argument)
        else:
            continue
        for start in range(0, len(indices), 3):
            corners = [cache[i].copy() for i in indices[start:start + 3]]
            face = len(replayed)
            replayed.append(tuple(c['source_vertex'] for c in corners))
            require(tuple(tuple(c['normal_bytes']) for c in corners)
                    == geometry.face_normal_bytes[face], 'source normal replay differs')
            if any(c['texgen'] is True for c in corners):
                require(all(c['texgen'] is True for c in corners), 'mixed texgen triangle')
                run = next(i for i, r in enumerate(geometry.material_runs)
                           if r.first_face <= face < r.first_face + r.face_count)
                records.append({'face': face, 'command_offset': pc,
                                'material_run': run, 'corners': corners})
    require(tuple(replayed) == geometry.faces and len(replayed) == 445,
            'source face replay differs')
    require(dict(Counter(str(r['material_run']) for r in records)) == expected['affected_runs'],
            'texgen face spans changed')
    require(len(records) == 103, 'texgen face count changed')
    return {'faces': records, 'source_face_count': 445, 'source_normal_corners': 1335,
            'tile_states': {run: models.texture_coordinate_state(geometry.material_runs[int(run)])
                            for run in expected['affected_runs']}}


def accessor(document, binary, index):
    a = document['accessors'][index]
    require('sparse' not in a and 'bufferView' in a, 'unsupported texgen accessor')
    view = document['bufferViews'][a['bufferView']]
    require(view['buffer'] == 0, 'texgen accessor buffer changed')
    width = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}[a['type']]
    fmt = '<' + {5121: 'B', 5123: 'H', 5125: 'I', 5126: 'f'}[a['componentType']] * width
    size = struct.calcsize(fmt)
    stride = view.get('byteStride', size)
    offset = view.get('byteOffset', 0) + a.get('byteOffset', 0)
    require(stride >= size and offset >= 0 and offset + (a['count'] - 1) * stride + size
            <= len(binary), 'texgen accessor outside buffer')
    return [struct.unpack_from(fmt, binary, offset + i * stride) for i in range(a['count'])]


def neutral_translations(document):
    parents = {child: i for i, node in enumerate(document['nodes'])
               for child in node.get('children', [])}
    worlds = {}
    visiting = set()

    def world(index):
        if index not in worlds:
            require(index not in visiting, 'cyclic texgen node hierarchy')
            visiting.add(index)
            node = document['nodes'][index]
            require(not any(k in node for k in ('rotation', 'scale', 'matrix')),
                    'texgen requires neutral translation-only joints')
            parent = world(parents[index]) if index in parents else [0, 0, 0]
            worlds[index] = [a + b for a, b in zip(parent, node.get('translation', [0, 0, 0]))]
            visiting.remove(index)
        return worlds[index]

    return {str(node['extras']['matrixIndex']): world(i)
            for i, node in enumerate(document['nodes'])
            if 'matrixIndex' in node.get('extras', {})}


def add_attribute(document, binary, proof):
    """Append raw normals without modifying existing attributes or buffer bytes."""
    document = copy.deepcopy(document)
    output = bytearray(binary)
    faces = {row['face']: row for row in proof['faces']}
    mapping, spans = {}, []
    for primitive in document['meshes'][0]['primitives']:
        first, count = primitive['extras']['firstFace'], primitive['extras']['faceCount']
        affected = [first + i in faces for i in range(count)]
        if not any(affected):
            continue
        require(all(affected), 'mixed texgen primitive')
        material = primitive['material']
        run = proof['material_runs'].get(str(material))
        require(run is not None and all(faces[first + i]['material_run'] == run for i in range(count)),
                'texgen primitive material span changed')
        uv = primitive['attributes']['TEXCOORD_0']
        indices = accessor(document, binary, primitive['indices'])
        rows = mapping.setdefault(uv, {})
        require(len(indices) == count * 3, 'texgen index count changed')
        for i in range(count):
            for k, corner in enumerate(faces[first + i]['corners']):
                index = indices[i * 3 + k][0]
                normal = tuple(value / 127 for value in corner['normal_bytes'])
                require(index not in rows or rows[index] == normal, 'conflicting texgen normal')
                rows[index] = normal
        spans.append({'material_index': material, 'source_material_run': run,
                      'first_face': first, 'face_count': count})
    require(sum(s['face_count'] for s in spans) == 103, 'texgen primitive coverage changed')
    additions = {}
    for uv, rows in mapping.items():
        count = document['accessors'][uv]['count']
        require(set(rows) == set(range(count)), 'incomplete texgen attribute')
        payload = b''.join(struct.pack('<3f', *rows[i]) for i in range(count))
        output.extend(b'\0' * (-len(output) % 4))
        view = len(document['bufferViews'])
        document['bufferViews'].append({'buffer': 0, 'byteOffset': len(output),
                                       'byteLength': len(payload), 'target': 34962})
        output.extend(payload)
        additions[uv] = len(document['accessors'])
        document['accessors'].append({'bufferView': view, 'componentType': 5126,
                                     'count': count, 'type': 'VEC3'})
    for primitive in document['meshes'][0]['primitives']:
        uv = primitive['attributes']['TEXCOORD_0']
        if uv in additions:
            primitive['attributes'][ATTRIBUTE] = additions[uv]
    document.pop('animations', None)
    document['buffers'][0] = {'uri': 'character66-texgen.bin', 'byteLength': len(output)}
    return document, bytes(output), spans


def build_files(rom=None):
    expected = contract()
    _, _, digest, bundles, _ = models.load_model_bundles('us', rom, 1)
    require(digest == expected['rom_sha1'], 'texgen ROM identity changed')
    source = next(b.data for b in bundles if b.index == 66)
    proof = replay(source, expected)
    gltf = ROOT / expected['source_gltf']
    raw = gltf.read_bytes()
    require(sha(raw) == expected['source_gltf_sha256'], 'texgen source glTF changed')
    document = json.loads(raw)
    resources = {}
    for uri, resource_digest in expected['resources'].items():
        path = (gltf.parent / uri).resolve()
        require(path.is_relative_to(gltf.parent.parent.resolve()), 'nonlocal texgen resource')
        resources[uri] = path.read_bytes()
        require(sha(resources[uri]) == resource_digest, f'texgen source resource changed: {uri}')
    binary = resources[document['buffers'][0]['uri']]
    proof.update({'schema_version': 1, 'model': [1, 66, 0], 'rom_sha1': digest,
                  'model_sha256': sha(source), 'contract_sha256': CONTRACT_SHA256,
                  'inspection_state': expected['inspection_state'], 'scope': expected['scope'],
                  'material_runs': expected['material_runs'],
                  'joint_world_translations': neutral_translations(document)})
    custom, updated, spans = add_attribute(document, binary, proof)
    files = {'source/model-0066.bin': source, 'source/geometry/0066-00.gltf': raw}
    for uri, data in resources.items():
        relative = Path(os.path.normpath('source/geometry/' + uri))
        require(relative.is_relative_to('source'), 'texgen source resource escapes output')
        files[relative.as_posix()] = data
    for image in custom['images']:
        target = Path(os.path.normpath('source/geometry/' + image['uri']))
        image['uri'] = os.path.relpath(target, 'geometry')
    files['geometry/character66-texgen.gltf'] = encode(custom)
    files['geometry/character66-texgen.bin'] = updated
    proof['affected_materials'] = expected['material_runs']
    proof['source'] = {'gltf_sha256': sha(files['geometry/character66-texgen.gltf']),
                       'resources': {r['uri']: sha(files[os.path.normpath('geometry/' + r['uri'])])
                                     for r in custom['buffers'] + custom['images']}}
    proof['primitive_spans'] = spans
    proof['source_gltf_sha256'] = sha(raw)
    proof['source_binary_sha256'] = sha(binary)
    proof['resources'] = {name: sha(data) for name, data in files.items()}
    files['source-proof.json'] = encode(proof)
    return files, proof



def _checked_output(output):
    output = Path(output).resolve()
    require(output.is_relative_to((ROOT / 'build').resolve()) and output != ROOT / 'build',
            'texgen output must be a child of build/')
    return output


def _worker_command(output, blender=None, *, verify=False):
    blender = blender or Path(shutil.which('blender') or '/Applications/Blender.app/Contents/MacOS/Blender')
    command = [str(blender), '--background', '--factory-startup', '--disable-autoexec',
               '--python-exit-code', '1', '--python',
               str(ROOT / 'scripts/model_character_texgen_blender.py'), '--',
               '--source', str(output / 'geometry/character66-texgen.gltf'),
               '--audit', str(output / 'source-proof.json'), '--output', str(output)]
    return command + (['--verify'] if verify else [])


def _artifact_snapshot(output):
    files, proof = build_files()
    for name, data in files.items():
        require((output / name).read_bytes() == data, f'texgen prepared source changed: {name}')
    artifact_raw = (output / 'artifact.json').read_bytes()
    artifact = json.loads(artifact_raw)
    require(artifact['blend_file'] == 'character66-neutral-texgen.blend'
            and set(artifact['renders']) == {'three-quarter.png', 'rear.png'},
            'texgen artifact output selection changed')
    require(artifact['source_proof_sha256'] == sha(files['source-proof.json'])
            and artifact['source_gltf_sha256'] == sha(files['geometry/character66-texgen.gltf']),
            'texgen artifact source identity changed')
    contents = {name: (output / name).read_bytes()
                for name in ('artifact.json', 'character66-neutral-texgen.blend', 'three-quarter.png', 'rear.png')}
    require(sha(contents[artifact['blend_file']]) == artifact['blend_sha256'], 'texgen Blend changed')
    for name, digest in artifact['renders'].items():
        require(sha(contents[name]) == digest, 'texgen preview changed')
    try:
        from scripts.model_preview_evidence import preview_fingerprint
    except ModuleNotFoundError:
        from model_preview_evidence import preview_fingerprint
    expected = contract()
    snapshot = {'kind': 'character66-neutral-texgen', 'model': [1, 66, 0],
                'output': str(output.relative_to(ROOT)), 'source': expected['source_gltf'],
                'source_fingerprint': preview_fingerprint(ROOT / expected['source_gltf']),
                'source_gltf_sha256': expected['source_gltf_sha256'],
                'source_proof_sha256': sha(files['source-proof.json']),
                'blend_sha256': sha(contents['character66-neutral-texgen.blend']),
                'preview_sha256': sha(contents['three-quarter.png']),
                'inspection_state': proof['inspection_state'],
                'files': {name: sha(data) for name, data in {**files, **contents}.items()},
                'tools': {name: sha((ROOT / name).read_bytes()) for name in
                          ('scripts/model_inspection_camera.py', 'scripts/model_character_texgen.py', 'scripts/model_character_texgen_blender.py',
                           'config/model-character66-texgen-inspection.json')}}
    return snapshot, contents, proof['scope']


def inspection_artifact(output):
    """Admit one inspection download only after fresh source and Blender checks."""
    output = _checked_output(output)
    before, contents, scope = _artifact_snapshot(output)
    result = subprocess.run(_worker_command(output, verify=True), cwd=ROOT,
                            capture_output=True, text=True)
    require(result.returncode == 0, 'texgen fresh Blender verification failed: '
            + (result.stdout + result.stderr)[-4000:])
    after, _, _ = _artifact_snapshot(output)
    require(before == after, 'texgen inspection inputs changed during verification')
    return {'blend': contents['character66-neutral-texgen.blend'],
            'preview': contents['three-quarter.png'], 'proof': after, 'scope': scope}


def inspection_artifact_current(output, proof):
    """Recheck all admitted bytes immediately before atomic gallery publication."""
    current, _, _ = _artifact_snapshot(_checked_output(output))
    require(current == proof, 'texgen inspection inputs changed before publication')
    return True


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/assets/models/character66-texgen-inspection')
    parser.add_argument('--blender', type=Path)
    parser.add_argument('--verify', action='store_true')
    args = parser.parse_args(argv)
    try:
        files, proof = build_files(args.rom)
        output = _checked_output(args.output)
        if args.verify:
            for name, data in files.items():
                require((output / name).read_bytes() == data, f'texgen prepared source changed: {name}')
        else:
            output.mkdir(parents=True, exist_ok=False)
            for name, data in files.items():
                path = output / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(data)
        subprocess.run(_worker_command(output, args.blender, verify=args.verify), cwd=ROOT, check=True)
    except (OSError, ValueError, subprocess.SubprocessError) as error:
        parser.error(str(error))
    print(f'Verified character66 neutral texgen inspection:103 faces; {output}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
