"""Conditional ROM-proven Haybot selector variants, without playback timing."""
from __future__ import annotations
import argparse
import copy
import hashlib
import json
from pathlib import Path
from scripts import model_assets as models,model_haybot_appearance as haybot,model_scene60_appearance as common

PRESET='haybot-rom-selector-variants'
CONTRACT_PATH=common.ROOT/'config/model-haybot-rom-variants.json'
CONTRACT_SHA256='343edae4fab6b7b994c7f52fee124c7f1209ba8adaf75ce8ff425d900b9c2131'
SCOPE=('Conditional ROM-consumer texture variants for Haybot actor+0x68 selectors15/16/17 only. '
       'Static inspection choices, without captured-phase, timing, pose or visibility claims. '
       'All source parts, geometry, rig and stored clips retained. Native lighting/fog/blending '
       'and framebuffer parity unverified; initializer descriptor0/defaults unchanged.')


def contract():
    raw=CONTRACT_PATH.read_bytes()
    if hashlib.sha256(raw).hexdigest()!=CONTRACT_SHA256:raise ValueError('Haybot ROM variant contract changed')
    return json.loads(raw)


def selector_for_phase(phase):
    if type(phase) is not int or phase not in range(6):raise ValueError('Haybot phase outside proven cycle')
    return 15+(phase if phase<3 else 5-phase)


def decode_variant(selector,data,layout,evidence):
    if evidence!=contract() or type(selector) is not int or selector not in (15,16,17):raise ValueError('Haybot ROM variant selection changed')
    info=evidence['variants'][str(selector)];descriptor=layout['texture_descriptors'][selector]
    if descriptor!=dict(record_index=selector,runtime_pointer_slot_initial_value=info['flat'],flat_index=info['flat'],width=64,height=64):raise ValueError('Haybot ROM descriptor binding changed')
    if len(data)!=2080 or hashlib.sha256(data).hexdigest()!=info['sha256']:raise ValueError('Haybot ROM variant payload changed')
    if hashlib.sha256(data[:2048]).hexdigest()!=info['pixel_sha256'] or hashlib.sha256(data[2048:]).hexdigest()!=info['palette_sha256']:raise ValueError('Haybot ROM variant spans changed')
    rows=bytes(data[y*32+(x^(4 if y&1 else 0))] for y in range(64) for x in range(32))
    png=models.encode_indexed_png(rows+data[2048:],'linear',64,64)
    if hashlib.sha256(png).hexdigest()!=info['png_sha256']:raise ValueError('Haybot ROM variant PNG changed')
    return png


OLD_IMAGE = 'textures/haybot-captured-selector15-flat3823.png'
CAPTURE_MARKERS = (b'capturedTexturePreset', b'capture_evidence', b'captured_texture_preset',
                   b'capture_provenance', b'capture_replayed_locally',
                   b'captured-haybot-selector15-inspection')


def guard_baseline(manifest, evidence):
    if evidence != contract():
        raise ValueError('Haybot ROM variant evidence changed')
    if manifest.get('selected_entries') != [75] or manifest.get('model_count') != 1 or manifest.get('source_zero_area_faces_preserved') is not True:
        raise ValueError('Haybot source selection changed')
    captured = manifest['capture_evidence']
    haybot.guard_evidence(captured)
    if (captured['identity']['rom_sha1'] != evidence['rom_sha1']
            or captured['identity']['source_sha256'] != evidence['model_sha256']
            or captured['selector_evidence']['updater_sha1'] != evidence['updater_sha1']):
        raise ValueError('Haybot source/consumer identities disagree')
    record = manifest['models'][0]
    fields = ('bank_entry', 'segment', 'source_face_count', 'face_count', 'vertex_count',
              'texture_coordinate_count', 'joint_count', 'omitted_zero_area_face_count',
              'animation_clip_count', 'animation_frame_count', 'incompatible_animation_clip_count')
    if tuple(record.get(key) for key in fields) != (75, 0, 1226, 1226, 1625, 1625, 45, 0, 15, 291, 0):
        raise ValueError('Haybot geometry/rig/animation inventory changed')
    return record


def variant_files(base, base_manifest, selector, png, evidence):
    """Replace the one guarded image binding, preserving every source buffer."""
    source_record = guard_baseline(base_manifest, evidence)
    if type(selector) is not int or selector not in (15, 16, 17):
        raise ValueError('Haybot variant selector changed')
    info = evidence['variants'][str(selector)]
    if hashlib.sha256(png).hexdigest() != info['png_sha256'] or hashlib.sha1(png).hexdigest() != info['png_sha1']:
        raise ValueError('Haybot variant image changed')
    files = dict(base)
    manifest = copy.deepcopy(base_manifest)
    record = manifest['models'][0]
    proof = {'preset': PRESET, 'scope': SCOPE, 'contract_sha256': CONTRACT_SHA256,
             'source': 'US ROM consumer', 'selector': selector, 'flat': info['flat'],
             'descriptor_cycle': evidence['descriptor_cycle'], 'updater_sha1': evidence['updater_sha1'],
             'observed_phase': None, 'playback_timing': None}
    image_name = f'textures/haybot-rom-selector{selector}-flat{info["flat"]}.png'
    if OLD_IMAGE not in files:
        raise ValueError('Haybot baseline image absent')
    files.pop(OLD_IMAGE)
    files[image_name] = png
    for gltf_field, binary_field, bind in (('gltf_file', 'gltf_binary_file', False), ('bind_gltf_file', 'bind_gltf_binary_file', True)):
        name = record[gltf_field]
        before = json.loads(base[name])
        haybot.guard_animations(source_record, before, bind)
        document = copy.deepcopy(before)
        document['extras'].pop('capturedTexturePreset')
        document['extras']['romConsumerTextureVariant'] = proof
        images = [image for image in document.get('images', []) if image.get('uri') == '../' + OLD_IMAGE]
        if len(images) != 1:
            raise ValueError('Haybot baseline image binding changed')
        images[0]['uri'] = '../' + image_name
        materials = [material for material in document['materials'] if material['extras']['materialRun'] == 16]
        if len(materials) != 1:
            raise ValueError('Haybot source material coverage changed')
        binding = materials[0]['pbrMetallicRoughness']['baseColorTexture']['index']
        texture_source = document['textures'][binding]['source']
        if document['images'][texture_source] is not images[0]:
            raise ValueError('Haybot material points at a different image')
        materials[0]['extras'].pop('capturedTexturePreset')
        materials[0]['extras']['romConsumerTextureVariant'] = proof
        common.guard_document_preservation(before, document, base[record[binary_field]], files[record[binary_field]])
        haybot.guard_animations(record, document, bind)
        files[name] = (json.dumps(document, indent=2) + '\n').encode()
    run = record['material_runs'][16]
    if run['status'] != 'captured-haybot-selector15-inspection' or run['texture']['file'] != OLD_IMAGE:
        raise ValueError('Haybot baseline material changed')
    run.pop('captured_texture_preset')
    run['status'] = 'rom-consumer-selector-inspection'
    run['rom_consumer_texture_variant'] = proof
    texture = {**run['texture'], 'flat_index': info['flat'], 'file': image_name,
               'png_sha1': info['png_sha1'], 'source_family': 'rom-consumer-haybot-selector'}
    run['texture'] = texture
    if sum(item['file'] == OLD_IMAGE for item in manifest['textures']) != 1:
        raise ValueError('Haybot manifest image coverage changed')
    manifest['textures'] = [texture if item['file'] == OLD_IMAGE else item for item in manifest['textures']]
    for key in ('capture_evidence', 'capture_provenance', 'capture_replayed_locally'):
        manifest.pop(key)
    manifest.update(family='explicit-ROM-consumer-character-texture-variants', rom_only=True,
                    preset=PRESET, scope=SCOPE, rom_consumer_evidence=evidence, selected_texture_variant=proof)
    for key in ('status_run_counts', 'status_face_counts'):
        count = manifest[key].pop('captured-haybot-selector15-inspection')
        manifest[key]['rom-consumer-selector-inspection'] = count
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    files['README.txt'] = (SCOPE + '\n').encode()
    if {name: data for name, data in files.items() if name.endswith('.bin')} != {name: data for name, data in base.items() if name.endswith('.bin')}:
        raise ValueError('Haybot source binary changed')
    for name, data in files.items():
        if name.endswith(('.json', '.gltf')) and any(marker in data for marker in CAPTURE_MARKERS):
            raise ValueError('Haybot variant retained capture-specific provenance')
    return files, manifest


def build_files(rom, texture_root):
    evidence = contract()
    base, geometry, layout, draw, base_manifest = haybot.build_files(rom, texture_root)
    guard_baseline(base_manifest, evidence)
    payloads = models.load_flat_asset_payloads('us', rom, evidence['rom_sha1'])
    output, records = {}, {}
    for selector in (15, 16, 17):
        info = evidence['variants'][str(selector)]
        png = decode_variant(selector, payloads[info['flat']], layout, evidence)
        files, manifest = variant_files(base, base_manifest, selector, png, evidence)
        output.update({f'selector{selector}/{name}': data for name, data in files.items()})
        records[selector] = (files, manifest)
    output['README.txt'] = (SCOPE + '\nSelectors15/16/17 are separate static exports.\n').encode()
    return output, geometry, layout, draw, records


def verify_files(output, files, geometry, layout, draw, records):
    for name, data in files.items():
        path = output / name
        if not path.resolve().is_relative_to(output.resolve()) or path.read_bytes() != data:
            raise ValueError('Haybot ROM variant output changed: ' + name)
    return {selector: haybot.verify_files(output / f'selector{selector}', local, geometry, layout, draw, manifest)
            for selector, (local, manifest) in records.items()}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--preset', required=True, choices=[PRESET])
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--textures', type=Path, default=common.ROOT / 'build/assets/textures')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--verify', action='store_true')
    args = parser.parse_args(argv)
    output = args.output.resolve()
    if not output.is_relative_to((common.ROOT / 'build').resolve()) or output == (common.ROOT / 'build').resolve():
        raise ValueError('appearance output must be a child of build/')
    files, geometry, layout, draw, records = build_files(args.rom, args.textures)
    if not args.verify:
        output.mkdir(parents=True, exist_ok=False)
        for name, data in files.items():
            path = output / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
    verify_files(output, files, geometry, layout, draw, records)
    print('Verified Haybot ROM selectors15/16/17:1226 source faces,45 joints; normal retains15 clips/291 frames, bind has no animations; timing unproved')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
