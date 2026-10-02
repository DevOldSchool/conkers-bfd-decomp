"""Source-preserving animated character66 inspection, separate from neutral export.

Original Blender-imported Actions are retained. Their between-key quaternion
interpolation is compared separately with the original glTF spherical oracle.
"""
from __future__ import annotations

import argparse
import bisect
import copy
import json
import math
from pathlib import Path
import shutil
import subprocess

try:
    from scripts import model_character_texgen as neutral
except ModuleNotFoundError:
    import model_character_texgen as neutral

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_OUTPUT = ROOT / 'build/assets/models/character66-animated-texgen-inspection'
ANIMATED_SOURCE = 'geometry/character66-animated-texgen.gltf'
BLEND = 'character66-animated-texgen.blend'
SCOPE = ('Character66 animated inspection using the original three Blender-imported '
         'Actions. Selected lighting enabled, nonlinear texture generation and '
         'canonical camera look-at axes; raw signed normals /127 remain unnormalized. '
         'Generated coordinates follow the evaluated imported rig. Blender quaternion '
         'interpolation between source keys approximates original glTF spherical '
         'interpolation; measured differences are recorded separately. Original '
         'translation/rotation clips only; nonuniform scaling, gameplay inherited '
         'state and native pixel/raster parity are unsupported. Neutral pose is '
         'selected initially; choose one source Action to inspect animation.')
require, sha, encode = neutral.require, neutral.sha, neutral.encode


def dot(a, b):
    return sum(x*y for x, y in zip(a, b))


def normalize(value):
    length = math.sqrt(dot(value, value))
    require(math.isfinite(length) and length > 0, 'invalid animation vector')
    return [x/length for x in value]


def multiply(a, b):
    return [[dot(row, col) for col in zip(*b)] for row in a]


def transform(matrix, vector):
    return [dot(row, vector) for row in matrix]


def inverse(matrix):
    """General inverse: the oracle does not assume the forward-vector shortcut."""
    size = len(matrix)
    rows = [list(row)+[float(i == j) for j in range(size)] for i, row in enumerate(matrix)]
    for k in range(size):
        pivot = max(range(k, size), key=lambda i: abs(rows[i][k]))
        rows[k], rows[pivot] = rows[pivot], rows[k]
        divisor = rows[k][k]
        require(abs(divisor) > 1e-12, 'singular animation matrix')
        rows[k] = [v/divisor for v in rows[k]]
        for i in range(size):
            if i != k:
                coefficient = rows[i][k]
                rows[i] = [x-coefficient*y for x, y in zip(rows[i], rows[k])]
    return [row[size:] for row in rows]


def slerp(first, second, fraction):
    first, second = normalize(first), normalize(second)
    cosine = dot(first, second)
    if cosine < 0:
        second, cosine = [-v for v in second], -cosine
    if cosine > .999999:
        return normalize([(1-fraction)*a+fraction*b for a, b in zip(first, second)])
    angle = math.acos(min(cosine, 1))
    divisor = math.sin(angle)
    return [(math.sin((1-fraction)*angle)*a+math.sin(fraction*angle)*b)/divisor
            for a, b in zip(first, second)]


def local_matrix(translation, quaternion):
    x, y, z, w = normalize(quaternion)
    rotation = [[1-2*(y*y+z*z), 2*(x*y-z*w), 2*(x*z+y*w)],
                [2*(x*y+z*w), 1-2*(x*x+z*z), 2*(y*z-x*w)],
                [2*(x*z-y*w), 2*(y*z+x*w), 1-2*(x*x+y*y)]]
    return [row+[translation[i]] for i, row in enumerate(rotation)]+[[0, 0, 0, 1]]


def animation_domain(document, binary):
    """Reject source changes outside the proven orthogonal animation domain."""
    animations = document.get('animations', [])
    require(len(animations) == 3, 'expected three original animation clips')
    result = []
    expected_channels = [(28, 2), (28, 3), (28, 2)]
    for index, animation in enumerate(animations):
        targets, times, rotations, translations = set(), set(), 0, 0
        for channel in animation['channels']:
            target = channel['target']; path, node = target['path'], target['node']
            require(type(node) is int and 0 <= node < 28 and path in ('rotation', 'translation'),
                    'unsupported animation target or scale channel')
            require((node, path) not in targets, 'duplicate animation channel')
            targets.add((node, path))
            sampler = animation['samplers'][channel['sampler']]
            require(sampler.get('interpolation', 'LINEAR') == 'LINEAR', 'unsupported source interpolation')
            keys = [r[0] for r in neutral.accessor(document, binary, sampler['input'])]
            values = neutral.accessor(document, binary, sampler['output'])
            require(len(keys) == len(values) and len(keys) >= 2 and keys[0] == 0
                    and all(math.isfinite(t) for t in keys)
                    and all(a < b for a, b in zip(keys, keys[1:])), 'invalid animation times')
            require(all(len(v) == (4 if path == 'rotation' else 3)
                        and all(math.isfinite(x) for x in v) for v in values), 'invalid animation values')
            if path == 'rotation':
                require(all(abs(math.sqrt(dot(q, q))-1) < 1e-6 for q in values),
                        'source quaternion is not unit length')
                rotations += 1
            else:
                translations += 1
            times.update(keys)
        require((rotations, translations) == expected_channels[index], 'source animation channel set changed')
        keys = sorted(times)
        require(len(keys) == (11, 10, 30)[index], 'source animation key count changed')
        samples = sorted(set(keys+[(a*.63+b*.37) for a, b in zip(keys, keys[1:])]
                             +[(a+b)/2 for a, b in zip(keys, keys[1:])]))
        result.append({'index': index, 'name': animation['name'], 'rotation_channels': rotations,
                       'translation_channels': translations, 'key_times': keys, 'sample_times': samples,
                       'source_metadata': animation.get('extras', {})})
    return result


def animation_contract(document, binary, proof):
    require(len(document['skins']) == 1 and document['skins'][0]['joints'] == list(range(28)),
            'source joint mapping changed')
    require(neutral.neutral_translations(document) == proof['joint_world_translations'],
            'source bind pose changed')
    inverse_bind = neutral.accessor(document, binary, document['skins'][0]['inverseBindMatrices'])
    require(len(inverse_bind) == 28, 'inverse bind count changed')
    for joint, matrix in enumerate(inverse_bind):
        expected = local_matrix([-x for x in proof['joint_world_translations'][str(joint)]], [0, 0, 0, 1])
        require(max(abs(matrix[c*4+r]-expected[r][c]) for r in range(4) for c in range(4)) < 4e-5,
                'inverse bind is not the proven translation')
    faces = {r['face']: r for r in proof['faces']}
    counts, total, corners = {}, 0, 0
    for primitive in document['meshes'][0]['primitives']:
        attributes = primitive['attributes']
        joints = neutral.accessor(document, binary, attributes['JOINTS_0'])
        weights = neutral.accessor(document, binary, attributes['WEIGHTS_0'])
        require(len(joints) == len(weights) and all(w == (1, 0, 0, 0) for w in weights)
                and all(0 <= j[0] < 28 for j in joints), 'source weights are not one-hot')
        total += len(weights)
        if str(primitive['material']) not in proof['affected_materials']:
            continue
        positions = neutral.accessor(document, binary, attributes['POSITION'])
        indices = neutral.accessor(document, binary, primitive['indices'])
        count = {}
        for k, row in enumerate(indices):
            corner = faces[primitive['extras']['firstFace']+k//3]['corners'][k % 3]
            index, joint = row[0], corner['matrix_index']
            require(joints[index][0] == joint and joint in (6, 13, 19), 'source corner joint changed')
            expected = [a+b for a, b in zip(corner['source_position'], proof['joint_world_translations'][str(joint)])]
            require(max(abs(a-b) for a, b in zip(positions[index], expected)) < 4e-5,
                    'source corner bind position changed')
            count[str(joint)] = count.get(str(joint), 0)+1; corners += 1
        counts[str(primitive['material'])] = count
    require(total == 529 and corners == 309, 'source weight/corner count changed')
    mixed = [fi for fi, row in faces.items() if len({c['matrix_index'] for c in row['corners']}) > 1]
    require(mixed == list(range(285, 291)), 'mixed joint face set changed')
    return {'clips': animation_domain(document, binary), 'weighted_vertices': total,
            'source_corners': corners, 'joints_by_material': counts, 'mixed_joint_faces': mixed,
            'pose_domain': 'original translation and unit-quaternion rotation; no scale channels',
            'interpolation_scope': 'Original imported Actions unchanged; glTF SLERP comparison is separate.'}


def world_matrices(document, binary, clip_index, seconds):
    """Independent glTF LINEAR translation / shortest-path spherical rotation oracle."""
    require(type(clip_index) is int and 0 <= clip_index < 3 and math.isfinite(seconds), 'invalid oracle sample')
    parents = {c: i for i, n in enumerate(document['nodes']) for c in n.get('children', [])}
    translations = {i: n.get('translation', [0, 0, 0]) for i, n in enumerate(document['nodes'])}
    rotations = {i: [0, 0, 0, 1] for i in range(len(document['nodes']))}
    clip = document['animations'][clip_index]
    for channel in clip['channels']:
        sampler = clip['samplers'][channel['sampler']]
        times = [v[0] for v in neutral.accessor(document, binary, sampler['input'])]
        values = neutral.accessor(document, binary, sampler['output'])
        first = min(max(bisect.bisect_right(times, seconds)-1, 0), len(times)-1)
        second = min(first+1, len(times)-1)
        fraction = 0 if first == second else max(0, min(1, (seconds-times[first])/(times[second]-times[first])))
        target = channel['target']
        if target['path'] == 'rotation':
            rotations[target['node']] = slerp(values[first], values[second], fraction)
        else:
            translations[target['node']] = [(1-fraction)*a+fraction*b for a, b in zip(values[first], values[second])]
    worlds = {}
    def world(index):
        if index not in worlds:
            local = local_matrix(translations[index], rotations[index])
            worlds[index] = multiply(world(parents[index]), local) if index in parents else local
        return worlds[index]
    return {i: world(i) for i in range(28)}


def build_files(rom=None):
    files, proof = neutral.build_files(rom)
    files = dict(files)
    original = json.loads(files['source/geometry/0066-00.gltf'])
    binary = files['source/geometry/0066-00.bin']
    domain = animation_contract(original, binary, proof)
    document = json.loads(files['geometry/character66-texgen.gltf'])
    document['animations'] = copy.deepcopy(original['animations'])
    files[ANIMATED_SOURCE] = encode(document)
    audit = {'schema_version': 1, 'kind': 'character66-animated-texgen', 'model': [1, 66, 0],
             'scope': SCOPE, 'neutral_source_proof_sha256': sha(files['source-proof.json']),
             'gltf_sha256': sha(files[ANIMATED_SOURCE]), 'animation_domain': domain,
             'resources': {name: sha(data) for name, data in files.items()}}
    files['animation-proof.json'] = encode(audit)
    return files, audit


def _checked_output(path):
    require(not Path(path).is_symlink(), 'animated texgen output cannot be a symlink')
    return neutral._checked_output(path)


def _worker_command(output, blender=None, *, verify=False):
    blender = blender or Path(shutil.which('blender') or '/Applications/Blender.app/Contents/MacOS/Blender')
    command = [str(blender), '--background', '--factory-startup', '--disable-autoexec',
               '--python-exit-code', '1', '--python', str(ROOT / 'scripts/model_character_animated_texgen_blender.py'),
               '--', '--source', str(output / ANIMATED_SOURCE), '--audit', str(output / 'animation-proof.json'),
               '--output', str(output)]
    return command+(['--verify'] if verify else [])


def _artifact_snapshot(output):
    files, proof = build_files()
    for name, data in files.items():
        require((output / name).read_bytes() == data, f'animated prepared source changed: {name}')
    contents = {name: (output / name).read_bytes() for name in ('artifact.json', BLEND, 'three-quarter.png', 'rear.png')}
    artifact = json.loads(contents['artifact.json'])
    require(artifact['blend_file'] == BLEND and artifact['scope'] == SCOPE
            and set(artifact['renders']) == {'three-quarter.png', 'rear.png'}, 'animated artifact selection/scope changed')
    require(artifact['animation_proof_sha256'] == sha(files['animation-proof.json'])
            and artifact['source_gltf_sha256'] == sha(files[ANIMATED_SOURCE]), 'animated source identity changed')
    require(sha(contents[BLEND]) == artifact['blend_sha256'], 'animated Blend changed')
    for name, digest in artifact['renders'].items():
        require(sha(contents[name]) == digest, 'animated preview changed')
    try:
        from scripts.model_preview_evidence import preview_fingerprint
    except ModuleNotFoundError:
        from model_preview_evidence import preview_fingerprint
    expected = neutral.contract()
    snapshot = {'kind': 'character66-animated-texgen', 'model': [1, 66, 0],
                'output': str(output.relative_to(ROOT)), 'source': expected['source_gltf'],
                'source_fingerprint': preview_fingerprint(ROOT / expected['source_gltf']),
                'source_gltf_sha256': expected['source_gltf_sha256'],
                'source_proof_sha256': sha(files['source-proof.json']),
                'animation_proof_sha256': sha(files['animation-proof.json']),
                'blend_sha256': sha(contents[BLEND]), 'preview_sha256': sha(contents['three-quarter.png']),
                'files': {name: sha(data) for name, data in {**files, **contents}.items()},
                'tools': {name: sha((ROOT / name).read_bytes()) for name in
                          ('scripts/model_inspection_camera.py', 'scripts/model_character_animated_texgen.py', 'scripts/model_character_animated_texgen_blender.py',
                           'scripts/model_character_texgen.py', 'scripts/model_character_texgen_blender.py',
                           'config/model-character66-texgen-inspection.json')}}
    return snapshot, contents, proof['scope']


def inspection_artifact(output):
    output = _checked_output(output)
    before, contents, scope = _artifact_snapshot(output)
    result = subprocess.run(_worker_command(output, verify=True), cwd=ROOT, capture_output=True, text=True)
    require(result.returncode == 0, 'animated fresh Blender verification failed: '+(result.stdout+result.stderr)[-4000:])
    after, _, _ = _artifact_snapshot(output)
    require(before == after, 'animated inspection changed during verification')
    return {'blend': contents[BLEND], 'preview': contents['three-quarter.png'], 'proof': after, 'scope': scope}


def inspection_artifact_current(output, proof):
    current, _, _ = _artifact_snapshot(_checked_output(output))
    require(current == proof, 'animated inspection changed before publication')
    return True


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--output', type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument('--blender', type=Path)
    parser.add_argument('--verify', action='store_true')
    args = parser.parse_args(argv)
    try:
        files, _ = build_files(args.rom)
        output = _checked_output(args.output)
        if args.verify:
            for name, data in files.items():
                require((output / name).read_bytes() == data, f'animated prepared source changed: {name}')
        else:
            output.mkdir(parents=True, exist_ok=False)
            for name, data in files.items():
                path = output / name; path.parent.mkdir(parents=True, exist_ok=True); path.write_bytes(data)
        subprocess.run(_worker_command(output, args.blender, verify=args.verify), cwd=ROOT, check=True)
    except (OSError, ValueError, KeyError, subprocess.SubprocessError) as error:
        parser.error(str(error))
    print(f'Verified character66 animated texgen inspection: 103 faces, 3 source Actions; {output}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
