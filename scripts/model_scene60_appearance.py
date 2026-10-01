"""Captured scene-60 primary texture inspection; no generic alpha/default change."""
from __future__ import annotations
import argparse
import copy
from dataclasses import asdict, replace
import hashlib
import json
from pathlib import Path
import tempfile

from scripts import model_assets as models, model_character_parts as parts, model_validation

ROOT = Path(__file__).resolve().parents[1]
PRESET = 'scene60-captured-primary-opacity255'
CONTRACT_PATH = ROOT/'config/model-scene60-captured-appearance.json'
CONTRACT_SHA256 = '26b0f4c65e09bdeda8ca2bef19a75385f8dda4d83bc9bd0e27518a2833e835d3'
SCOPE = ('Only captured scene60 primary appearances: model154 mode2 and model162 mode1, '
         'opacity255, normal part0, secondary0. Original zero-alpha PNGs are retained; '
         'OPAQUE unlit material is a pre-blender black inspection approximation; native fog colour, '
         'framebuffer blending and visibility are not reproduced. Fog RGBA was not captured; '
         'FORCE_BL false does not bypass the first blender cycle. Fractional edge coverage and '
         'native framebuffer parity remain unproved. No local raw-trace replay, captured pose, '
         'model155 or universal default admission.')


def contract():
    raw = CONTRACT_PATH.read_bytes()
    if hashlib.sha256(raw).hexdigest() != CONTRACT_SHA256:
        raise ValueError('scene60 appearance contract changed')
    evidence = json.loads(raw)
    evidence['contract_sha256'] = CONTRACT_SHA256
    return evidence


def guard(evidence):
    if evidence != contract():
        raise ValueError('scene60 appearance evidence changed')
    if evidence['preset'] != PRESET or set(evidence['models']) != {'154', '162'}:
        raise ValueError('scene60 appearance selection changed')
    for entry in (154, 162):
        context_guard(entry, evidence['models'][str(entry)], evidence)


def guard_evidence(evidence):
    """Accept only one of the two independently pinned captured contracts."""
    if evidence.get('preset') == PRESET:
        guard(evidence)
    else:
        from scripts import model_library_bat155_appearance as library
        library.guard(evidence)


def context_guard(entry, context, evidence):
    if entry not in (154, 155, 162) or str(entry) not in evidence['models'] or context != evidence['models'][str(entry)]:
        raise ValueError('scene60 captured model/context changed')
    part = context['selected_part']
    expected_mode = 2 if entry == 154 else 1
    if (context['caller_arguments'][0] != 255 or context['caller_arguments'][2] != expected_mode
            or part['draw_mode'] != expected_mode or part['part'] != 0 or part['table'] != 'normal'
            or part['secondary_model'] != 0 or part['display_model'] != entry):
        raise ValueError('scene60 appearance is not its proved opaque primary draw')
    for name, state in evidence['captured_states'].items():
        high, low = [int(word, 16) for word in state['other_mode']]
        if low & 0x2000 == 0 or low & (0x1000 | 0x4000 | 3):
            raise ValueError('scene60 appearance coverage/alpha mode changed')
        if models.decode_other_mode((high, low))['texture_lut'] != 'rgba16':
            raise ValueError('scene60 appearance lookup mode changed')
        common = evidence['captured_state_common']
        if (common['K5'] != 255 or not common['alpha_cvg_select'] or common['cvg_times_alpha']
                or common['force_blend'] or common['alpha_compare'] != 0):
            raise ValueError('scene60 captured alpha/conversion interpretation changed')
        numeric = {'other_mode': [high, low],
                   'combine_mode': [int(w, 16) for w in state['combine_mode']],
                   'convert_mode': [int(w, 16) for w in common['convert_mode']],
                   'colours': common['colours']}
        if hashlib.sha256(json.dumps(numeric, sort_keys=True).encode()).hexdigest() != state['state_subset_sha256']:
            raise ValueError('scene60 captured colour/combiner/conversion state changed')


def checked_model(entry, raw, digest, evidence):
    context = evidence['models'].get(str(entry))
    context_guard(entry, context, evidence)
    if digest != evidence['identities']['rom_sha1']:
        raise ValueError('scene60 ROM identity changed')
    if len(raw) != context['source_bytes'] or hashlib.sha1(raw).hexdigest() != context['source_sha1']:
        raise ValueError('scene60 model identity changed')
    geometry, layout = models.parse_character_model_geometry(raw)
    if (len(geometry.faces) != context['whole_model_faces'] or len(geometry.vertices) != context['vertices']
            or len(layout['joints']) != context['joints']):
        raise ValueError('scene60 source geometry/rig changed')
    selected, draw_pass = parts.primary_preview(raw, geometry, layout)
    selected, _, _ = models.omit_zero_area_preview_faces(selected)
    if len(selected.faces) != context['selected_primary_faces']:
        raise ValueError('scene60 primary selection changed')
    return selected, layout, draw_pass



def run_digest(run):
    return hashlib.sha256(json.dumps(asdict(run), sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def guard_flat903_mips(run):
    if run.texture_scale != (0xD7001802, 0xFFFFFFFF):
        raise ValueError('scene60 flat903 mip selection changed')
    loaded = (((run.pixel.load_command[1] >> 12) & 4095) + 1) * 2
    if loaded != 736:
        raise ValueError('scene60 flat903 mip transfer changed')
    tiles = {i: (command, argument) for i, command, argument in run.render_tiles}
    for level, (start, dimension, stride) in enumerate(((0,32,16),(512,16,8),(640,8,8),(704,4,8))):
        if level not in tiles:
            raise ValueError('scene60 flat903 mip tile missing')
        command, argument = tiles[level]
        # Stored masks specify the sampled dimensions; shifts select the mip.
        mask = 5-level
        if ((command & 511)*8 != start or ((command >> 9)&511)*8 != stride
                or (command >> 19)&3 != 0 or (command >> 21)&7 != 0
                or (argument >> 20)&15 != 0
                or (argument >> 4)&15 != mask or (argument >> 14)&15 != mask
                or argument&15 != level or (argument >> 10)&15 != level
                or 1 << mask != dimension or start + stride*dimension > loaded):
            raise ValueError('scene60 flat903 mip layout changed')


ANIMATION_FRAMES = (19,19,19,19,19,19,19,14,11,11,11,11,11,16,16,10)
PRESERVED_DOCUMENT_FIELDS = ('meshes','nodes','skins','accessors','bufferViews','buffers','animations')


def guard_animation_inventory(entry, record, document, *, bind=False):
    expected = (0,0,0) if entry in (154,155) else (16,244,0) if entry == 162 else None
    if expected is None or tuple(record.get(key) for key in (
            'animation_clip_count','animation_frame_count','incompatible_animation_clip_count')) != expected:
        raise ValueError('scene60 pinned animation inventory changed')
    animations = document.get('animations', [])
    actual = [(a.get('extras',{}).get('sourceBank'), a.get('extras',{}).get('sourceEntry'),
               a.get('extras',{}).get('sourcePair'), a.get('extras',{}).get('sourceFrameCount')) for a in animations]
    wanted = [] if bind or entry in (154,155) else [(2,162,pair,frames) for pair,frames in enumerate(ANIMATION_FRAMES)]
    if actual != wanted:
        raise ValueError('scene60 animation pairs/frame counts or bind exclusion changed')


def guard_document_preservation(before, after, before_binary=None, after_binary=None):
    for key in PRESERVED_DOCUMENT_FIELDS:
        if (key in before) != (key in after) or before.get(key) != after.get(key):
            raise ValueError(f'scene60 material edit changed source {key}')
    if before_binary != after_binary:
        raise ValueError('scene60 material edit changed source binary')

def checked_run(run, index, geometry, entry, evidence):
    context = evidence['models'][str(entry)]
    row = next((r for r in context['runs'] if r[0] == index), None)
    if row is None or run != geometry.material_runs[index]:
        raise ValueError('scene60 unlisted or changed source material')
    expected_digest = evidence['local_source_guards']['material_run_sha256'][str(entry)][str(index)]
    if run_digest(run) != expected_digest:
        raise ValueError('scene60 canonical source material state changed')
    _, first, faces, flat, matrix, first_command, last_command = row
    spec = evidence['source_contracts'][str(flat)]
    if (run.first_face, run.face_count, run.matrix_index) != (first, faces, matrix):
        raise ValueError('scene60 source material coverage changed')
    offsets = geometry.face_command_offsets[first:first+faces]
    if (offsets[0], offsets[-1]) != (first_command, last_command):
        raise ValueError('scene60 source triangle provenance changed')
    for key in ('render_tile', 'tile_bounds', 'texture_scale', 'combine_mode'):
        if list(getattr(run, key) or ()) != spec[key]:
            raise ValueError('scene60 source tile/combiner/coordinate contract changed')
    if (run.runtime_render_state_offset != spec['runtime_render_state_offset']
            or run.other_mode is not None or run.other_mode_partial is not None
            or not run.texture_enabled or not run.texture_coordinates_proven):
        raise ValueError('scene60 source mode/texture contract changed')
    for name, mode, load in [('pixel', 0, spec['pixel_load']), ('palette', 2, [0xF0000000, 0x0603C000])]:
        binding = getattr(run, name)
        if (binding is None or binding.flat_index != flat or binding.mode != mode or binding.image_command != 0xFD100000
                or binding.segment is not None or binding.offset is not None or binding.external
                or list(binding.load_command or ()) != load):
            raise ValueError('scene60 source image/palette binding changed')
    if flat == 903:
        guard_flat903_mips(run)
    return flat, spec


def decode_image(run, index, geometry, entry, payloads, evidence):
    flat, spec = checked_run(run, index, geometry, entry, evidence)
    info = evidence['textures'][str(flat)]; data = payloads.get(flat, b'')
    if len(data) != info['flat_bytes'] or hashlib.sha256(data).hexdigest() != info['flat_sha256']:
        raise ValueError('scene60 flat payload identity changed')
    if hashlib.sha256(data[:info['captured_pixel_bytes']]).hexdigest() != info['captured_pixel_sha256']:
        raise ValueError('scene60 captured pixel prefix changed')
    if info['palette_offset'] != len(data) - 32:
        raise ValueError('scene60 trailing palette pointer changed')
    palette = data[info['palette_offset']:]
    if palette != bytes(32) or hashlib.sha256(palette).hexdigest() != evidence['texture_common']['palette_sha256']:
        raise ValueError('scene60 original zero palette changed')
    state = models.texture_coordinate_state(run)
    width, height = 32, info['height']
    if (state['width'], state['height'], state['size']) != (width, height, 0):
        raise ValueError('scene60 indexed image dimensions changed')
    stride = ((run.render_tile[0] >> 9) & 511) * 8
    start = (run.render_tile[0] & 511) * 8
    if stride != 16 or start != 0 or height * stride > min(info['captured_pixel_bytes'], info['palette_offset']):
        raise ValueError('scene60 pixel/TLUT source span changed')
    rows = bytes(data[y*stride + (x ^ (4 if y&1 else 0))] for y in range(height) for x in range(16))
    png = models.encode_indexed_png(rows + palette, 'linear', width, height)
    if hashlib.sha1(png).hexdigest() != info['png_sha1']:
        raise ValueError('scene60 original-alpha PNG hash changed')
    return png, flat


def apply_document(document, entry, evidence, textures, geometry):
    guard_evidence(evidence)
    preset, scope, contract_sha = evidence.get('preset', PRESET), evidence.get('inspection_scope', SCOPE), evidence.get('contract_sha256', CONTRACT_SHA256)
    result = copy.deepcopy(document)
    proof = {'preset': preset, 'scope': scope, 'contract_sha256': contract_sha,
             'capture_replayed_locally': False, 'identities': evidence['identities'],
             'submitted_task': evidence['task'], 'captured_model': evidence['models'][str(entry)]}
    result.setdefault('extras', {})['capturedTexturePreset'] = proof
    used = set()
    for material in result['materials']:
        index = material['extras']['materialRun']
        if index not in textures:
            continue
        flat, uri = textures[index]
        images = result.setdefault('images', [])
        image_record = {'uri': uri}
        if image_record not in images: images.append(image_record)
        image_index = images.index(image_record)
        samplers = result.setdefault('samplers', [])
        addressing = models.texture_address_mode(geometry.material_runs[index])['gltf']
        sampler_record = {'magFilter':9729,'minFilter':9987,
                          'wrapS':addressing['wrapS'],'wrapT':addressing['wrapT']}
        if sampler_record not in samplers: samplers.append(sampler_record)
        sampler = samplers.index(sampler_record)
        texture = len(result.setdefault('textures', []));result['textures'].append({'source':image_index,'sampler':sampler})
        material['pbrMetallicRoughness']['baseColorTexture'] = {'index':texture}
        material['pbrMetallicRoughness']['baseColorFactor'] = [1,1,1,1]
        material['alphaMode'] = 'OPAQUE';material.pop('alphaCutoff', None)
        material.setdefault('extensions', {})['KHR_materials_unlit'] = {}
        material['extras']['capturedTexturePreset'] = {'preset':preset,'run':index,'flat':flat,
            'source_alpha_preserved':True,'alphaMode':'OPAQUE','scope':scope,
            'captured_state': evidence['captured_states'][evidence['source_contracts'][str(flat)]['captured_state']],
            'captured_common':evidence['captured_state_common']}
        used.add(index)
    if used != set(textures):
        raise ValueError('scene60 glTF material coverage changed')
    extensions = result.setdefault('extensionsUsed', [])
    if 'KHR_materials_unlit' not in extensions:extensions.append('KHR_materials_unlit')
    guard_document_preservation(document, result)
    return result


def build_files(rom, texture_root, evidence=None):
    evidence = contract() if evidence is None else evidence
    guard_evidence(evidence)
    preset, scope = evidence.get('preset', PRESET), evidence.get('inspection_scope', SCOPE)
    path, _ = models.resolve_rom('us', rom); normalized, _ = models.normalize_rom(path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    _, _, found_digest, bundles, _ = models.load_model_bundles('us', rom, 1)
    if found_digest != digest:raise ValueError('scene60 ROM changed during extraction')
    payloads = models.load_flat_asset_payloads('us', rom, digest)
    for info in evidence['textures'].values():
        start, end = (int(v,16) for v in info['compressed_rom_range'])
        if hashlib.sha256(normalized[start:end]).hexdigest() != info['compressed_sha256']:
            raise ValueError('scene60 compressed flat span changed')
    checked = {}
    for entry in map(int, evidence['models']):
        raw = next(b for b in bundles if b.index == entry).segments[0].data
        checked[entry] = checked_model(entry, raw, digest, evidence)
    with tempfile.TemporaryDirectory() as temporary:
        base = Path(temporary)/'baseline'
        manifest = models.extract_model_preview('us', rom, texture_root, base, False, 1,
            rom_defaults=True, entry_filter=frozenset(checked))
        files = {str(p.relative_to(base)):p.read_bytes() for p in base.rglob('*') if p.is_file()}
    manifests = {r['bank_entry']:r for r in manifest['models']}
    source_binaries = {name: data for name,data in files.items() if name.endswith('.bin')}
    for entry, (geometry, layout, draw_pass) in checked.items():
        selected = {}
        for row in evidence['models'][str(entry)]['runs']:
            index = row[0];png, flat = decode_image(geometry.material_runs[index], index, geometry, entry, payloads, evidence)
            filename = f'textures/scene60-original-alpha-{flat}.png';files[filename] = png
            selected[index] = (flat, '../'+filename)
        for name in (f'geometry/{entry:04d}-00.gltf', f'geometry/{entry:04d}-00-bind.gltf'):
            original = json.loads(files[name])
            guard_animation_inventory(entry, manifests[entry], original, bind='-bind.gltf' in name)
            doc = apply_document(original, entry, evidence, selected, geometry)
            guard_animation_inventory(entry, manifests[entry], doc, bind='-bind.gltf' in name)
            binary_name = name.replace('.gltf','.bin')
            guard_document_preservation(original, doc, source_binaries[binary_name], files[binary_name])
            files[name] = (json.dumps(doc,indent=2)+'\n').encode()
        record = manifests[entry]
        record['captured_texture_preset'] = {'preset':preset,'scope':scope,'runs':sorted(selected)}
        for index,(flat,uri) in selected.items():
            run = record['material_runs'][index]
            if run['status'] != 'character-indexed-combiner-preview-unresolved' or run['texture'] is not None:
                raise ValueError('scene60 baseline material contract changed')
            run['status'] = 'captured-scene60-opaque-inspection'
            run['captured_texture_preset'] = {'preset':preset,'source_alpha_preserved':True,'scope':scope}
            info=evidence['textures'][str(flat)]
            run['texture']={'flat_index':flat,'file':uri[3:],'png_sha1':info['png_sha1'],'width':32,'height':info['height'],
                            'source_family':'captured-scene60-ROM-decoded','format':2,'size':0,
                            'pixel_byte_offset':0,'palette_byte_offset':info['palette_offset']}
        # OBJ/MTL remain source geometry, but their material language cannot express
        # this coverage interpretation. Omit them rather than imply equivalent output.
        for field in ('object_file','material_file'):
            files.pop(record[field],None);record[field]=None
    manifest.update(family='explicit-captured-character-texture-preset',rom_only=False,
        preset=preset,scope=scope,capture_replayed_locally=False,capture_evidence=evidence,
        linked_material_run_count=manifest['linked_material_run_count']+sum(len(m['runs']) for m in evidence['models'].values()),
        linked_face_count=manifest['linked_face_count']+sum(m['blocked_faces'] for m in evidence['models'].values()))
    for flat, info in evidence['textures'].items():
        manifest['textures'].append({'flat_index':int(flat),'format':2,'size':0,'width':32,
            'height':info['height'],'source_family':'captured-scene60-ROM-decoded',
            'file':f'textures/scene60-original-alpha-{flat}.png','png_sha1':info['png_sha1'],
            'pixel_byte_offset':0,'palette_byte_offset':info['palette_offset']})
    manifest['copied_texture_count'] = len(manifest['textures'])
    # Recompute status summaries rather than retaining the baseline's unresolved counts.
    from collections import Counter
    runs=[r for m in manifest['models'] for r in m['material_runs']]
    manifest['status_run_counts']=dict(Counter(r['status'] for r in runs))
    manifest['status_face_counts']={s:sum(r['face_count'] for r in runs if r['status']==s) for s in manifest['status_run_counts']}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
    files['README.txt']=(scope+'\nOnly glTF/GLB materials express this inspection preset.\n').encode()
    if source_binaries != {name:data for name,data in files.items() if name.endswith('.bin')}:
        raise ValueError('scene60 source buffers changed during material export')
    return files, checked, manifest


def verify_files(output, expected, checked, manifest):
    for name,data in expected.items():
        path=output/name
        if not path.resolve().is_relative_to(output.resolve()) or path.read_bytes()!=data:
            raise ValueError(f'scene60 captured output changed: {name}')
    reports={}
    for record in manifest['models']:
        entry=record['bank_entry'];geometry,layout,draw_pass=checked[entry]
        for field, bind in (('gltf_file',False),('bind_gltf_file',True)):
            path = output/record[field]
            guard_animation_inventory(entry, record, json.loads(path.read_text()), bind=bind)
            reports[f'{entry}-bind' if bind else str(entry)] = model_validation.compare_geometry(
                path,geometry,tuple(layout['joints']),record['material_runs'],draw_pass=draw_pass)
    return reports


def main(argv=None):
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--preset',required=True,choices=[PRESET])
    parser.add_argument('--rom',type=Path)
    parser.add_argument('--textures',type=Path,default=ROOT/'build/assets/textures')
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--verify',action='store_true')
    args=parser.parse_args(argv); output=args.output.resolve()
    if not output.is_relative_to((ROOT/'build').resolve()) or output==(ROOT/'build').resolve():
        raise ValueError('appearance output must be a child of build/')
    files,checked,manifest=build_files(args.rom,args.textures)
    if not args.verify:
        output.mkdir(parents=True,exist_ok=False)
        for name,data in files.items():
            p=output/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)
    reports=verify_files(output,files,checked,manifest)
    print(f'Verified scene60 primary preset: 384 newly linked faces, source faces {[r["faces"] for r in reports.values()]}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
