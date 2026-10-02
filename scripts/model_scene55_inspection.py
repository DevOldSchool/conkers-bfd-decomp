"""Guarded scene55 Blender inspection with independently sampled CI4 planes."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import struct
import subprocess

try:
    from scripts import model_assets as models, model_scene_assemblies as assemblies
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    import model_assets as models
    import model_scene_assemblies as assemblies
    from model_preview_evidence import preview_fingerprint

ROOT = Path(__file__).resolve().parents[1]
CONTRACT = ROOT / 'config/model-scene55-inspection.json'
CONTRACT_SHA256 = '11556bdcc5aaa429735359794870e19e4de704f73f8f56ab0c2e37b0a04a1957'
BLEND = 'scene55-zero-scroll-stored-rgba.blend'


def require(value, message):
    if not value:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def encode(value):
    return (json.dumps(value, indent=2, allow_nan=False) + '\n').encode()


def stable(value):
    return sha(json.dumps(value, sort_keys=True, separators=(',', ':'), allow_nan=False).encode())


def contract():
    raw = CONTRACT.read_bytes()
    require(sha(raw) == CONTRACT_SHA256, 'scene55 contract changed')
    return json.loads(raw)


def decode_planes(run, payload):
    """Admit this full two-plane transfer, not arbitrary nonzero TMEM offsets."""
    require(len(payload) == 2080 and hashlib.sha1(payload).hexdigest() ==
            '6efffd09da18f157c1f2f77daf5f3f7f51873008', 'scene55 payload changed')
    require(run.texture_enabled and run.texture_scale == (0xD7000002, 0xFFFFFFFF), 'scene55 texture scale changed')
    require(run.pixel == models.ModelTextureBinding(0xFD500000, 737, 0,
            load_command=(0xF3000000, 0x073FF000)), 'scene55 pixel transfer changed')
    require(run.palette == models.ModelTextureBinding(0xFD100000, 737, 2,
            load_command=(0xF0000000, 0x0603C000)), 'scene55 palette transfer changed')
    tiles = {i: (word, arg) for i, word, arg in run.render_tiles}
    require(tiles == {0: (0xF5400800, 0x00014060), 1: (0xF5400880, 0x01014060),
                      6: (0xF5600100, 0x06000000), 7: (0xF5500000, 0x07000000)}, 'scene55 tile contract changed')
    require(run.texture_loads == ((run.pixel, tiles[7]), (run.palette, tiles[6])), 'scene55 load-time tiles changed')
    require(run.combine_mode == (0xFC111404, 0xFF13FFFF)
            and run.other_mode == (0xEF18AC3F, 0x0C184A50), 'scene55 combiner or RDP mode changed')
    require(run.tile_bounds is None, 'scene55 inherited tile origin changed')
    planes = []
    for tile in (0, 1):
        word, arg = tiles[tile]
        width, height = 1 << ((arg >> 4) & 15), 1 << ((arg >> 14) & 15)
        stride, start = ((word >> 9) & 511) * 8, (word & 511) * 8
        require((width, height, stride, start) == (64, 32, 32, tile * 1024), 'scene55 plane layout changed')
        require(start + height * stride <= 2048, 'scene55 TMEM span changed')
        rows = [bytes(payload[start+y*stride+(byte ^ (4 if y & 1 else 0))]
                      for byte in range(stride)) for y in range(height)]
        planes.append(models.encode_indexed_png(b''.join(rows) + payload[2048:], 'linear', width, height))
    return planes


def accessor(doc, binary, index):
    a = doc['accessors'][index]; v = doc['bufferViews'][a['bufferView']]
    require('sparse' not in a and v.get('buffer', 0) == 0, 'unsupported scene55 accessor')
    dim = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4}[a['type']]
    fmt = '<' + {5121: 'B', 5123: 'H', 5125: 'I', 5126: 'f'}[a['componentType']] * dim
    size = struct.calcsize(fmt); begin = v.get('byteOffset', 0) + a.get('byteOffset', 0)
    return [struct.unpack_from(fmt, binary, begin+i*v.get('byteStride', size)) for i in range(a['count'])]


def affected_corners(doc, binary, geometry, target):
    primitives = doc['meshes'][target['mesh']]['primitives']
    require(len(primitives) == 1, 'scene55 affected primitive set changed')
    p = primitives[0]; run, = geometry.material_runs
    require(p['material'] == target['material'] and p['extras']['firstFace'] == 0
            and p['extras']['faceCount'] == run.face_count == target['faces'], 'scene55 material span changed')
    require(set(p['attributes']) == {'POSITION', 'COLOR_0', 'TEXCOORD_0'}, 'scene55 attributes changed')
    arrays = {key: accessor(doc, binary, value) for key, value in p['attributes'].items()}
    indices = accessor(doc, binary, p['indices'])
    require(len(indices) == len(geometry.faces)*3, 'scene55 index count changed')
    corners = []
    for fi, face in enumerate(geometry.faces):
        row = []
        for ci, vi in enumerate(face):
            v = geometry.vertices[vi]; index = indices[fi*3+ci][0]
            require(arrays['POSITION'][index] == (v.x, v.y, v.z), 'scene55 source position changed')
            require(arrays['COLOR_0'][index] == v.color and v.color[3] == 126, 'scene55 source RGBA changed')
            uv = arrays['TEXCOORD_0'][index]
            require(max(abs(a-b) for a, b in zip(uv, models.texture_coordinates(v, run))) < 2e-5,
                    'scene55 source UV changed')
            row.append({'position': [v.x, v.y, v.z], 'rgba': list(v.color), 'uv': list(uv),
                        'source_vertex': vi, 'source_st': [v.s, v.t]})
        corners.append(row)
    return corners


def build_files(rom=None):
    expected = contract(); source = ROOT / expected['source_gltf']
    before = preview_fingerprint(source)
    raw, binary = source.read_bytes(), source.with_suffix('.bin').read_bytes()
    require(sha(raw) == expected['source_gltf_sha256'] and sha(binary) == expected['source_binary_sha256'],
            'scene55 assembly source changed')
    doc = json.loads(raw)
    require(doc['buffers'] == [{'uri': 'scene-55.bin', 'byteLength': len(binary)}]
            and len(doc['nodes']) == 22 and len(doc['meshes']) == 10 and len(doc['images']) == 60,
            'scene55 assembly contract changed')
    selected = [s for s in json.loads((ROOT/'config/model-scene-assemblies.json').read_text())['scenes']
                if s['scene_index'] == 55]
    require(selected == [expected['selection']], 'scene55 reviewed selection changed')
    digest, scenes = assemblies.rom_scenes('us', rom)
    require(digest == expected['rom_sha1'] and stable(scenes[55]) == expected['scene_input_sha256'],
            'scene55 fresh ROM placements changed')
    encoded, composed, record = assemblies.compose(scenes[55], expected['selection'],
                                                   ROOT/expected['model_root'], digest)
    require(encoded == raw and composed == binary and stable(record) == expected['assembly_record_sha256'],
            'scene55 assembly provenance changed')
    bundles_by_bank = {}; model_data = {}; files = {'source/geometry/scene-55.gltf': raw,
                                                  'source/geometry/scene-55.bin': binary}
    for component in expected['components']:
        bank, entry, segment = component['model']
        if bank not in bundles_by_bank:
            _, _, identity, bundles, _ = models.load_model_bundles('us', rom, bank)
            require(identity == digest, 'scene55 component ROM changed')
            bundles_by_bank[bank] = bundles
        data = next(s.data for b in bundles_by_bank[bank] if b.index == entry for s in b.segments if s.index == segment)
        require(sha(data) == component['model_sha256']
                and preview_fingerprint(ROOT/component['path']) == component['fingerprint'],
                'scene55 source component changed')
        model_data[tuple(component['model'])] = data
        files[f'source/models/{bank:02}-{entry:04}-{segment:02}.bin'] = data
    path, layout = models.resolve_rom('us', rom); normalized, _ = models.normalize_rom(path.read_bytes())
    require(hashlib.sha1(normalized).hexdigest() == digest, 'scene55 ROM changed during read')
    game = models.parse_game_archive(normalized[layout['game_start']:layout['game_end']])
    for row in expected['consumers']:
        offset = int(row['address'], 16) - layout['game_vram']
        require(sha(game.code[offset:offset+row['size']]) == row['sha256'], 'scene55 native consumer changed')
    offset = 0x80088890 - layout['game_data_vram']
    require(game.data[offset:offset+16] == bytes(16), 'scene55 ROM initial scroll changed')
    payload = models.load_flat_asset_payloads('us', rom, digest)[737]
    files['source/flat0737.bin'] = payload; targets = []; planes = None
    for target in expected['affected']:
        data = model_data[tuple(target['model'])]
        geometry = models.parse_model_geometry(data)
        current = decode_planes(geometry.material_runs[0], payload)
        require(planes is None or planes == current, 'scene55 component texture mismatch')
        planes = current
        targets.append({**target, 'corners': affected_corners(doc, binary, geometry, target)})
    for index, data in enumerate(planes):
        files[f'textures/flat0737-plane{index}.png'] = data
    proof = {'schema_version': 1, 'scene_index': 55, 'rom_sha1': digest,
             'contract_sha256': CONTRACT_SHA256, 'source_gltf_sha256': sha(raw),
             'source_binary_sha256': sha(binary), 'source_fingerprint': before,
             'inspection_state': expected['inspection_state'], 'scope': expected['scope'],
             'targets': targets, 'assembly_record_sha256': stable(record),
             'resources': {name: sha(data) for name, data in files.items()}}
    files['source-proof.json'] = encode(proof)
    require(preview_fingerprint(source) == before, 'scene55 assembly changed during preparation')
    return files, proof


def _checked_output(output):
    require(not Path(output).is_symlink(), 'scene55 output cannot be a symlink')
    output = Path(output).resolve(); build = (ROOT/'build').resolve()
    require(output.is_relative_to(build) and output != build, 'scene55 output must be a child of build/')
    return output


def _worker_command(output, blender=None, *, verify=False):
    blender = blender or Path(shutil.which('blender') or '/Applications/Blender.app/Contents/MacOS/Blender')
    command = [str(blender), '--background', '--factory-startup', '--disable-autoexec', '--python-exit-code', '1',
               '--python', str(ROOT/'scripts/model_scene55_inspection_blender.py'), '--', '--output', str(output)]
    return command + (['--verify'] if verify else [])


def _artifact_snapshot(output):
    files, proof = build_files()
    for name, data in files.items():
        require((output/name).read_bytes() == data, f'scene55 prepared source changed: {name}')
    names = ('artifact.json', BLEND, 'three-quarter.png', 'rear.png')
    contents = {name: (output/name).read_bytes() for name in names}; artifact = json.loads(contents['artifact.json'])
    require(artifact['blend_file'] == BLEND and set(artifact['renders']) == {'three-quarter.png','rear.png'}
            and artifact['scope'] == proof['scope'] and artifact['inspection_state'] == proof['inspection_state']
            and artifact['source_proof_sha256'] == sha(files['source-proof.json'])
            and artifact['source_gltf_sha256'] == proof['source_gltf_sha256'], 'scene55 artifact source identity changed')
    require(artifact['blend_sha256'] == sha(contents[BLEND]), 'scene55 Blend changed')
    for name, digest in artifact['renders'].items():
        require(sha(contents[name]) == digest, 'scene55 preview changed')
    snapshot = {'kind': 'scene55-dual-texture', 'scene_index': 55, 'output': str(output.relative_to(ROOT)),
                'source': contract()['source_gltf'], 'source_fingerprint': proof['source_fingerprint'],
                'source_gltf_sha256': proof['source_gltf_sha256'], 'source_proof_sha256': sha(files['source-proof.json']),
                'blend_sha256': sha(contents[BLEND]), 'preview_sha256': sha(contents['three-quarter.png']),
                'inspection_state': proof['inspection_state'],
                'files': {name: sha(data) for name,data in {**files,**contents}.items()},
                'tools': {name: sha((ROOT/name).read_bytes()) for name in
                          ('scripts/model_inspection_camera.py', 'scripts/model_scene55_inspection.py','scripts/model_scene55_inspection_blender.py',
                           'config/model-scene55-inspection.json','scripts/model_assets.py',
                           'scripts/model_scene_assemblies.py','scripts/model_preview_evidence.py')}}
    return snapshot, contents, proof['scope']


def inspection_artifact(output):
    output = _checked_output(output); before, contents, scope = _artifact_snapshot(output)
    result = subprocess.run(_worker_command(output, verify=True), cwd=ROOT, capture_output=True, text=True)
    require(result.returncode == 0, 'scene55 fresh Blender verification failed: '+(result.stdout+result.stderr)[-4000:])
    after, _, _ = _artifact_snapshot(output)
    require(before == after, 'scene55 inspection inputs changed during verification')
    return {'blend': contents[BLEND], 'preview': contents['three-quarter.png'], 'proof': after, 'scope': scope}


def inspection_artifact_current(output, proof):
    current, _, _ = _artifact_snapshot(_checked_output(output))
    require(current == proof, 'scene55 inspection inputs changed before publication')
    return True


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT/'build/assets/models/scene55-material-inspection')
    parser.add_argument('--blender', type=Path); parser.add_argument('--verify', action='store_true')
    args = parser.parse_args(argv)
    try:
        files, _ = build_files(args.rom); output = _checked_output(args.output)
        if args.verify:
            for name,data in files.items():
                require((output/name).read_bytes() == data, f'scene55 prepared source changed: {name}')
        else:
            output.mkdir(parents=True, exist_ok=False)
            for name,data in files.items():
                (output/name).parent.mkdir(parents=True, exist_ok=True); (output/name).write_bytes(data)
        subprocess.run(_worker_command(output,args.blender,verify=args.verify),cwd=ROOT,check=True)
        current, _ = build_files(args.rom)
        require(current == files and all((output/name).read_bytes() == data for name,data in files.items()),
                'scene55 inputs changed during Blender operation')
    except (OSError, ValueError, subprocess.SubprocessError) as error:
        parser.error(str(error))
    print(f'Verified scene55 selected-state inspection: 84 dual-texture faces; {output}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
