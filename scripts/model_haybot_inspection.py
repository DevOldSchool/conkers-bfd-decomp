"""Source-bound Haybot inspection at an explicitly selected texture phase."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import struct
import subprocess

try:
    from scripts import model_assets as models, texture_assets
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    import model_assets as models
    import texture_assets
    from model_preview_evidence import preview_fingerprint

ROOT = Path(__file__).resolve().parents[1]
SOURCE_ROOT = 'build/assets/models/rom-only/us-bank-01-preview'
SOURCE = SOURCE_ROOT + '/geometry/0075-00.gltf'
BLEND = 'haybot-phase0.blend'
DEFAULT_OUTPUT = ROOT/'build/assets/models/haybot-phase0-inspection'
KIND = 'haybot-selected-phase0'
STATE = {'phase': 0, 'segment10_descriptor': 15, 'segment11_descriptor': 0,
         'shade': 'stored-RGBA', 'primitive_rgb': [0, 0, 0], 'environment_rgba': [0, 0, 0, 255],
         'opacity': 'source-initial-full-opacity', 'other_mode': ['0xEF18AC3F', '0x04D12078'],
         'texture': 'CI4/RGBA16 flat3823', 'color_domain': 'raw-byte/255',
         'RGB': '(SHADE - ENVIRONMENT) * TEXEL0 + PRIMITIVE',
         'alpha': 'TEXEL0 * SHADE * ENVIRONMENT', 'filter': 'linear', 'address': 'clamp',
         'native_parity': False}
SCOPE = ('Haybot at selected post-update phase 0 (segment 10 descriptor 15; segment 11 stays 0), '
         'with source-initial full opacity and zero primitive/environment RGB, and stored vertex RGBA. '
         'Only material run 16 on 24 faces gains its source image. Original geometry, UVs, rig, '
         '15 Actions and other materials remain intact; the saved pose is neutral. '
         'These source states are not a captured concurrent state, initializer texture, first draw or '
         'universal default. Texture-cycle timing, other texture scrolling, runtime lighting, '
         'visibility and native animation/raster parity remain unresolved.')
SOURCE_GLTF_SHA256 = 'a02f92412a139bc528d6fc51d0d17f2153312edcbb2a9e573e35aa5d93ed9ce4'
SOURCE_BINARY_SHA256 = 'bd9fefc58b3bab6e74158cafbe8b8e39bb9a6cc7d62fd8deb6c20862b181a417'
VARIANTS = ((15, 3823, '6c0857a5cd8a7cccd98e77179c69e4ed8a7e3c75b3228d8ea6810613315af04d',
             '0c984d18d271a89a163e648c9b7801bd6ad8b7984df56f419390ee087c31f78d'),
            (16, 3822, 'ec904c32f940e8de54a0fc09033dbd3f1471976dc5b1133562a5fa4af2b5af10',
             '1290ef17797b01c2c9d01272c1ab0842f1f02d3092ef53263d8d9ab23e291999'),
            (17, 3824, '7a2225bc44fe95f69a88a3ac86fe9456624c13a5303a88d6083b61925742c4b7',
             'c09a6887c481458b29463c423aad762d1b383e413f9412945e9cf72ac38d1479'))
CONSUMERS = (
    (0x15061B4C, 2216, 'f207cf478ac06fa00c877b8c069fe7f693ff7fdd4573f166ee8d6f1446e193fe'),
    (0x15062D10, 276, '2b7d78b9c42e156ace1cc8a39679824c8e85cab22f537fc34be7994090ca22a2'),
    (0x1502F01C, 584, 'fc77bd44e23ded1b024c7a76f599e4a7b49b61abd20878dd50feb1b36710a4ca'),
    (0x150006E0, 608, 'e989a97feca8a9e41b908ed17c3a84cb563124a0b43a3644e1e2bc85d23abb3e'),
    (0x1502CC34, 200, '58de27ed770a0f6b4857d824a6a45f3cbef6e0a82004232cedc517562a3b23f0'),
    (0x1502CCFC, 2128, 'decbb35d617c4af15ac94f625006dc1fa2a96f0d78337fc36c989503a158d130'),
    (0x1505F188, 272, 'f40509518bd60c31bd037ae4b24a8f20b4869676ea8541108c6b5f0d10134c65'),
    (0x150615DC, 48, 'd511aee1db07c50148a5d7ee2cc886d136806fa6c3cfe9c22789c281b1b28415'),
    (0x1506160C, 432, '92846202af33090980242b32633917b0ee4a2bcf290cb3947143e9d404a53e70'),
    (0x15082A44, 2152, '6326624baf172e51e75f070a0c4375a70fe25fd4a5616aa9669beaf9f74b23b9'),
    (0x1502C974, 704, 'd4e76253ff7fd4f721038bbe95e83f77aae70818f6d262fd46ec258bc1f4451d'),
    (0x1501878C, 1648, '5c3fb4784448084a751c6175b07270540a55247037a4e7ca820a708e35f276b9'),
    (0x15019130, 740, 'db23322789f9b3e81cddb0417c857bd1d4cd58255f6612a88b96548354c9ec49'),
    (0x150195A0, 860, 'fd2f7d19ffcc1cb0fd851d02f4c49595af84bb6a830108f8298ddbe0b6ae192a'),
    (0x15018DFC, 140, 'f1013354e4ea836a931d26a933ff5b409b0d138778cad36af5d65c51d860754e'),
    (0x1502378C, 228, 'b79d8c8945079f304e9cb9e73313c096ad8b9b4d027d7d8be0735028050b4df2'),
    (0x1504A730, 1696, '94b88ff9f7f4683ebe5cb6e1fa81a3db2ef88e5130fec3d41f7948fa8e7c110b'),
)
SPAWNS = ((16, 0, '81aca9192aa6bfbb4a0d9c246cf0e39a789f20f3c733d8c1b7b7ac4cab808ad0',
           '002001024b00ff14001d01a215018408280100000000000000000263282800004000000040000000060000000001ff00'),
          (24, 48, '3e8dce3f7a033ee9cf2848c5d8da99ebd4d6c0decd9a782dc1f86ba47bcf5afc',
           '002001024b0000f7fedf08e63d010108080000000000000000000043323200004000000040000000070003e800000000'))


def require(value, message):
    if not value:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def encode(value):
    return (json.dumps(value, indent=2, allow_nan=False)+'\n').encode()


def selected_state(phase=0):
    require(type(phase) is int and phase == 0, 'only explicit post-update phase0 is supported')
    return {'phase': 0, 'previous_phase': 5, 'actor68': 15, 'actor69': 0,
            'initializer_actor68': 0, 'initializer_actor69': 0,
            'cycle_by_updated_phase': [15, 16, 17, 17, 16, 15],
            'gate': 'live actor, actor+2FA != 0, shared byte800CC2A7 >= 4',
            'timer_scope': 'shared; checked per qualifying control, not once per frame',
            'other_scroll_commands': ['0x7598', '0x75A8', '0x75B8'],
            'target_tile_command': '0x7630'}


def raw_rgba(payload):
    """Independent full CI4/TLUT oracle, in native bottom-up image order."""
    require(len(payload) == 2080, 'Haybot CI4 payload span changed')
    colors = [int.from_bytes(payload[2048+i*2:2050+i*2]) for i in range(16)]
    result = bytearray()
    for y in range(64):
        for x in range(64):
            packed = payload[y*32+((x//2) ^ (4 if y & 1 else 0))]
            index = packed >> 4 if not x & 1 else packed & 15
            color = colors[index]
            result.extend([((color >> s) & 31)*255//31 for s in (11, 6, 1)])
            result.append(255 if color & 1 else 0)
    return bytes(result)


def material_contract(run, geometry):
    require(run.face_count == 24 and run.first_face == 367 and run.texture_enabled
            and run.texture_coordinates_proven, 'Haybot affected face/coordinate span changed')
    require(run.pixel.segment == run.palette.segment == 10
            and run.pixel.offset == 0 and run.palette.offset == 2048
            and run.pixel.load_command == (0xF3000000, 0x073FF000)
            and run.palette.load_command == (0xF0000000, 0x0603C000)
            and run.render_tile == (0xF5000800, 0x00098260)
            and run.tile_bounds == (0xF2002002, 0x000FE0FE)
            and run.combine_mode == (0xFCFF9880, 0xF514FEFF)
            and run.runtime_render_state_offset == 64,
            'Haybot image/tile/combiner contract changed')
    require(all(geometry.vertices[i].color == (255, 255, 255, 255)
                for face in geometry.faces[367:391] for i in face), 'stored Haybot SHADE changed')
    return models.decode_combine_mode(run.combine_mode)


def _consumer_contract(code, base):
    for address, count, expected in CONSUMERS:
        offset = address-base
        require(offset >= 0 and offset+count <= len(code)
                and sha(code[offset:offset+count]) == expected, 'Haybot native consumer changed')
    offset = 0x1506196C-base
    require(hashlib.sha1(code[offset:offset+60]).hexdigest() == 'd8ea7ef06bfdcfef9cdbf35db05257f62ea68fbb',
            'Haybot exact full-opacity consumer changed')


def spawn_contract(payload, scene, offset, digest, record_hex):
    record = bytes.fromhex(record_hex)
    require(sha(payload) == digest and payload[offset:offset+len(record)] == record
            and int.from_bytes(record[:2]) == 0x20 and not int.from_bytes(record[:2]) & 6
            and record[2:5] == bytes((1, 2, 75)), 'Haybot source spawn flags changed')
    return {'scene': scene, 'offset': offset, 'record_sha256': sha(record), 'flags': '0x0020',
            'script_gated': True, 'constructor_fade_override': False}


def build_files(rom=None):
    before = preview_fingerprint(ROOT/SOURCE)
    require(before['gltf_sha256'] == SOURCE_GLTF_SHA256, 'Haybot source glTF changed')
    _, _, digest, bundles, tables = models.load_model_bundles('us', rom, 1)
    bundle = next(b for b in bundles if b.index == 75)
    require(sha(bundle.data) == '09f6c4551ca0d12b46109a45f01703fb21ba7f10d15764aa807a4c9701936e81',
            'Haybot model payload changed')
    geometry, layout = models.parse_character_model_geometry(bundle.data)
    geometry, draw = models.model_character_parts.primary_preview(bundle.data, geometry, layout)
    geometry, omitted, _ = models.omit_zero_area_preview_faces(geometry)
    require(len(geometry.faces) == 1225 and len(omitted) == 1, 'Haybot source face omission changed')
    formula = material_contract(geometry.material_runs[16], geometry)
    manifest, animation_files = models.load_character_animation_manifest('us', rom, include_files=True)
    clips, _ = models.character_animation_clips_for_model(75,
        max(j['animation_index'] for j in layout['joints'])+1, manifest, animation_files)
    pair = models.CHARACTER_REFERENCE_POSE_PAIRS.get(75)
    if pair is not None:
        clips = tuple(sorted(clips, key=lambda clip: clip.pair_index != pair))
    require(len(clips) == 15 and len(layout['joints']) == 45, 'Haybot rig or clip set changed')
    morph = models.load_character_morph_manifest('us', rom, bundles)
    morph_record = next((r for r in morph['models'] if r['character_entry'] == 75), None)
    records = json.loads((ROOT/SOURCE_ROOT/'manifest.json').read_text())
    row = next(r for r in records['models'] if r['bank_entry'] == 75)
    runs = row['material_runs']
    require(len(runs) == len(geometry.material_runs) == 62, 'Haybot material set changed')
    mapping = {r['material']: '../'+r['texture']['file'] for r in runs if r['texture']}
    raw, binary = models.encode_gltf(75, 0, geometry, mapping, 1, tuple(layout['joints']), None, None,
        clips, runtime_materials={}, character_morphs=morph_record, character_draw_pass=draw)
    raw = models.add_rom_texture_state_evidence(raw, runs)
    require(sha(raw) == SOURCE_GLTF_SHA256 and sha(binary) == SOURCE_BINARY_SHA256
            and raw == (ROOT/SOURCE).read_bytes()
            and binary == (ROOT/SOURCE).with_suffix('.bin').read_bytes(), 'fresh ROM Haybot reconstruction differs')
    files = {'source/geometry/0075-00.gltf': raw, 'source/geometry/0075-00.bin': binary,
             'source/model75.bin': bundle.data}
    defaults = models.model_character_defaults.preview_defaults(models.load_character_defaults('us', rom, digest), 75)
    require(defaults['descriptor_indices'] == {'6': 7, '7': 21, '10': 0, '11': 0}, 'Haybot initializer changed')
    flat = models.load_flat_asset_payloads('us', rom, digest)
    for run, record in zip(geometry.material_runs, runs):
        texture, _ = models.choose_preview_texture(run, {}, flat)
        if run.pixel and run.pixel.segment in (6, 7, 10, 11):
            texture, _, _ = models.rom_default_preview_texture(run, defaults, layout['texture_descriptors'], flat, tables)
        require(bool(texture) == bool(record['texture']), 'Haybot original material resolution changed')
        if texture:
            name = record['texture']['file']; path = (ROOT/SOURCE_ROOT/name).resolve()
            require(path.is_relative_to((ROOT/SOURCE_ROOT).resolve()) and path.read_bytes() == texture.png_data,
                    'Haybot original image differs from fresh ROM')
            files['source/'+name] = texture.png_data
    doc = json.loads(raw)
    require(len(doc['images']) == 18 and len(doc['animations']) == 15, 'Haybot glTF image/animation set changed')
    variants = []
    for selector, index, payload_hash, png_hash in VARIANTS:
        selected = {**defaults, 'preset': 'explicit-post-update-phase0-evidence',
                    'descriptor_indices': {**defaults['descriptor_indices'], '10': selector}}
        descriptor = layout['texture_descriptors'][selector]; payload = flat[index]
        require(descriptor['flat_index'] == index and sha(payload) == payload_hash, 'Haybot texture descriptor changed')
        texture, status, evidence = models.rom_default_preview_texture(
            geometry.material_runs[16], selected, layout['texture_descriptors'], flat, tables)
        require(status == 'rom-default-indexed' and texture and sha(texture.png_data) == png_hash,
                'Haybot strict CI4 decoder changed')
        rgba = raw_rgba(payload)
        require(set(rgba[3::4]) == {255}, 'Haybot used texture alpha is no longer opaque')
        files[f'textures/descriptor{selector}.png'] = texture.png_data
        files[f'source/flat{index}.bin'] = payload
        variants.append({'descriptor': selector, 'flat_index': index, 'payload_sha256': payload_hash,
                         'png_sha256': png_hash, 'raw_rgba_sha256': sha(rgba), 'pixels': 4096,
                         'used_alpha': [255], 'evidence': evidence})
    path, rom_layout = models.resolve_rom('us', rom); normalized, _ = models.normalize_rom(path.read_bytes())
    require(hashlib.sha1(normalized).hexdigest() == digest, 'Haybot ROM changed during preparation')
    game = models.parse_game_archive(normalized[rom_layout['game_start']:rom_layout['game_end']])
    _consumer_contract(game.code, rom_layout['game_vram'])
    bank = next(b for b in models.parse_asset_banks(normalized, rom_layout['asset_table']) if b.index == 14)
    entries = {e.index: e for e in models.parse_asset_entries(normalized, bank)}
    spawns = []
    for scene, offset, expected, record_hex in SPAWNS:
        entry = entries[scene]; compressed = normalized[entry.start:entry.end]
        payload = models.decode_rzip_chunk(compressed).data if entry.compressed else compressed
        spawns.append(spawn_contract(payload, scene, offset, expected, record_hex))
        files[f'source/spawn-scene{scene}.bin'] = payload
    selected_table = next(t for t in tables if t['base_address'] == '0x80083140')
    other = next(e for e in selected_table['entries'] if int(e['offset'], 0) == 64)
    require(other['other_mode'] == STATE['other_mode'], 'Haybot ordinary opaque render state changed')
    try:
        from scripts.model_inspection import pack_glb
    except ModuleNotFoundError:
        from model_inspection import pack_glb
    glb, _ = pack_glb(ROOT/SOURCE)
    proof = {'schema_version': 1, 'kind': KIND, 'entry': 75, 'phase': 0, 'descriptor': 15,
             'rom_sha1': digest, 'source': SOURCE, 'source_fingerprint': before,
             'source_gltf_sha256': sha(raw), 'source_glb_sha256': sha(glb),
             'selected_state': selected_state(), 'inspection_state': STATE, 'scope': SCOPE,
             'combine': formula, 'other_mode': models.decode_other_mode(tuple(int(x, 0) for x in STATE['other_mode'])),
             'source_faces': 1225, 'affected_faces': list(range(367, 391)), 'affected_material': 16,
             'joints': 45, 'actions': [a['name'] for a in doc['animations']], 'original_images': 18,
             'variants': variants, 'consumers': [{'address': hex(a), 'bytes': n, 'sha256': h} for a, n, h in CONSUMERS],
             'opacity_source': {'spawns': spawns, 'initializer': '1505F188 -> 150615DC',
                                'actor_fields': {'+7': 255, '+B..E': 255},
                                'ordinary_draw': '1502C974 -> 1506196C -> 1502CCFC, mode0..2',
                                'limits': 'Selected initialized bytes; subsequent handler/VM mutations not excluded. '
                                          'Queue15035FE8 alpha is dynamic and is not this proof.'},
             'files': {name: sha(data) for name, data in files.items()}}
    files['source-proof.json'] = encode(proof)
    require(preview_fingerprint(ROOT/SOURCE) == before, 'Haybot source changed during preparation')
    return files, proof


def _checked_output(output):
    require(not Path(output).is_symlink(), 'Haybot output cannot be a symlink')
    output = Path(output).resolve(); build = (ROOT/'build').resolve()
    require(output.is_relative_to(build) and output != build, 'Haybot output must be a child of build/')
    return output


def _worker_command(output, blender=None, *, verify=False):
    blender = blender or Path(shutil.which('blender') or '/Applications/Blender.app/Contents/MacOS/Blender')
    command = [str(blender), '--background', '--factory-startup', '--disable-autoexec', '--python-exit-code', '1',
               '--python', str(ROOT/'scripts/model_haybot_inspection_blender.py'), '--', '--output', str(output)]
    return command+(['--verify'] if verify else [])


def _artifact_snapshot(output):
    files, proof = build_files()
    require(all((output/name).read_bytes() == raw for name, raw in files.items()), 'Haybot prepared source changed')
    contents = {name: (output/name).read_bytes() for name in ('artifact.json', BLEND, 'three-quarter.png', 'rear.png')}
    artifact = json.loads(contents['artifact.json'])
    require(artifact['blend_file'] == BLEND and artifact['scope'] == SCOPE and artifact['inspection_state'] == STATE
            and artifact['source_proof_sha256'] == sha(files['source-proof.json'])
            and artifact['source_gltf_sha256'] == proof['source_gltf_sha256'], 'Haybot artifact source/state changed')
    require(artifact['blend_sha256'] == sha(contents[BLEND]) and set(artifact['renders']) == {'three-quarter.png', 'rear.png'}
            and all(sha(contents[n]) == h for n, h in artifact['renders'].items()), 'Haybot artifact bytes changed')
    names = ('model_haybot_inspection', 'model_haybot_inspection_blender', 'model_assets', 'model_preview_evidence',
             'model_character_defaults', 'model_character_parts', 'model_morphs', 'model_inspection',
             'model_character_texgen_blender', 'model_character_animated_texgen_blender',
             'model_embedded_type13_inspection_blender', 'model_inspection_camera', 'texture_assets', 'texture_native')
    snapshot = {key: proof[key] for key in ('kind', 'entry', 'phase', 'descriptor', 'source', 'source_fingerprint',
                                          'source_gltf_sha256', 'source_glb_sha256', 'inspection_state')}
    snapshot.update(output=str(output.relative_to(ROOT)), scope=SCOPE,
                    source_proof_sha256=sha(files['source-proof.json']), blend_sha256=sha(contents[BLEND]),
                    preview_sha256=sha(contents['three-quarter.png']),
                    files={name: sha(raw) for name, raw in {**files, **contents}.items()},
                    tools={'scripts/'+name+'.py': sha((ROOT/'scripts'/(name+'.py')).read_bytes()) for name in names})
    return snapshot, contents


def inspection_artifact(output):
    output = _checked_output(output); before, contents = _artifact_snapshot(output)
    result = subprocess.run(_worker_command(output, verify=True), cwd=ROOT, capture_output=True, text=True)
    require(result.returncode == 0, 'Haybot fresh Blender verification failed: '+(result.stdout+result.stderr)[-4000:])
    after, _ = _artifact_snapshot(output)
    require(before == after, 'Haybot inspection changed during verification')
    return {'blend': contents[BLEND], 'preview': contents['three-quarter.png'], 'proof': after, 'scope': SCOPE}


def inspection_artifact_current(output, proof):
    current, _ = _artifact_snapshot(_checked_output(output))
    require(current == proof, 'Haybot inspection changed before publication')
    return True


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--rom', type=Path)
    parser.add_argument('--output', type=Path, default=DEFAULT_OUTPUT); parser.add_argument('--blender', type=Path)
    parser.add_argument('--verify', action='store_true'); args = parser.parse_args(argv)
    try:
        files, _ = build_files(args.rom); output = _checked_output(args.output)
        if args.verify:
            require(all((output/name).read_bytes() == raw for name, raw in files.items()), 'Haybot prepared source changed')
        else:
            output.mkdir(parents=True, exist_ok=False)
            for name, raw in files.items():
                (output/name).parent.mkdir(parents=True, exist_ok=True); (output/name).write_bytes(raw)
        subprocess.run(_worker_command(output, args.blender, verify=args.verify), cwd=ROOT, check=True)
        current, _ = build_files(args.rom)
        require(current == files and all((output/name).read_bytes() == raw for name, raw in files.items()),
                'Haybot source changed during Blender operation')
    except (OSError, ValueError, subprocess.SubprocessError) as error:
        parser.error(str(error))
    print(f'Verified Haybot selected phase0 inspection: 1225 faces, 45 joints, 15 Actions; {output}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
