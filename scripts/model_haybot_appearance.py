"""Captured Haybot selector15 texture, preserving complete source geometry."""
from __future__ import annotations
import argparse
import copy
from dataclasses import asdict
import hashlib
import json
from pathlib import Path
import tempfile
from scripts import model_assets as models, model_character_parts as parts, model_scene60_appearance as common, model_validation

PRESET = 'haybot-captured-selector15'
CONTRACT_PATH = common.ROOT/'config/model-haybot-captured-appearance.json'
CONTRACT_SHA256 = 'c29be223ad110b8a489c60e5ecb7aea1e8166f11d5eed4fb59f843e019c610d4'
PACKET_SHA256 = '254846215d32ece3913f2adcb8bef94909f1492fbc95b0d70e11d16f0c16615d'
CAPTURE_AUDIT_SHA256 = '99e3b3f1b3eab6b7834718e7007ceff69a987147d2531e9513db7f6aac8ce382'
MATRIX_EVIDENCE = ('All 35 segment3 character matrices in each of the two submissions equal nearest signed 16.16 '
                   'quantization of float32 return affine matrices using round(f32 * 65536), with the unused fourth '
                   'column canonicalized to (0,0,0,1). Maximum decoded absolute error is 7.62939453125e-06, '
                   'half a 16.16 unit. The non-segment3 address 0x800C3E98 is excluded. '
                   'All 35 raw matrix byte representations per task differ. Raw matrix byte immutability is not asserted.')
SCOPE = ('Fixed documented scene16 Haybot selector15/phase5 static texture inspection on source run16 only. '
         'All 1226 source faces, including the collinear triangle, '
         '45 joints and 15 animation clips/291 frames are retained. Descriptor0 remains unchanged. '
         'No captured visibility/pose reconstruction, native framebuffer/raster equivalence, local raw-trace replay, '
         'universal default replacement or texture-animation timeline claim. ' + MATRIX_EVIDENCE)
FRAMES = (13,13,19,14,9,9,48,13,12,20,19,5,21,64,12)


def capture_provenance():
    return {'source':'captured renderer evidence and authenticated US ROM',
            'contract_sha256':CONTRACT_SHA256,'packet_sha256':PACKET_SHA256,
            'capture_audit_sha256':CAPTURE_AUDIT_SHA256,
            'capture_replayed_locally':False,
            'matrix_evidence':MATRIX_EVIDENCE}


def contract():
    raw=CONTRACT_PATH.read_bytes()
    if hashlib.sha256(raw).hexdigest()!=CONTRACT_SHA256:
        raise ValueError('Haybot captured contract changed')
    return json.loads(raw)


def guard_evidence(evidence):
    if evidence != contract():raise ValueError('Haybot captured context/submission changed')


def checked_model(raw, digest, evidence):
    guard_evidence(evidence);identity=evidence['identity']
    if digest!=identity['rom_sha1'] or len(raw)!=identity['source_bytes'] or hashlib.sha256(raw).hexdigest()!=identity['source_sha256']:
        raise ValueError('Haybot source identity changed')
    geometry,layout=models.parse_character_model_geometry(raw)
    if (len(geometry.vertices),len(geometry.faces),models.texture_coordinate_count(geometry),len(layout['joints']))!=(1625,1226,1625,45):
        raise ValueError('Haybot source geometry/rig changed')
    if layout['procedural_animation_joint_indices'] != [20,None]:
        raise ValueError('Haybot procedural joints changed')
    for _,offset,size,sha1 in evidence['geometry']['sections']:
        start=int(offset,16)
        if hashlib.sha1(raw[start:start+size]).hexdigest()!=sha1:raise ValueError('Haybot source section changed')
    selected,draw=parts.primary_preview(raw,geometry,layout)
    if selected != geometry:raise ValueError('Haybot full primary geometry changed')
    return geometry,layout,draw


def checked_run(geometry,evidence):
    run=geometry.material_runs[16]
    if common.run_digest(run)!=evidence['source_run_sha256']:raise ValueError('Haybot full material state changed')
    # Independently compare every packet field and expanded cumulative history.
    actual=json.loads(json.dumps(asdict(run)));expected=evidence['run16']
    for key,value in expected.items():
        if key not in ('load_history','load_history_shared','load_history_columns') and actual[key]!=value:
            raise ValueError('Haybot packet source contract mismatch')
    shared=expected['load_history_shared'];loads=[]
    for i,(flat,mode,segment,offset,second) in enumerate(expected['load_history']):
        pixel=i%2==0
        loads.append([dict(image_command=shared['image_command'],flat_index=flat,mode=mode,segment=segment,offset=offset,
            external=False,load_command=[shared['pixel_load_first' if pixel else 'palette_load_first'],second]),shared['pixel_tile' if pixel else 'palette_tile']])
    if actual['texture_loads']!=loads:raise ValueError('Haybot cumulative load history changed')
    offsets=geometry.face_command_offsets[368:392]
    if list(dict.fromkeys(offsets))!=evidence['source_triangle_offsets'] or any(offsets.count(offset)!=4 for offset in set(offsets)):
        raise ValueError('Haybot triangle provenance changed')
    return run


def decode_image(geometry,data,evidence):
    run=checked_run(geometry,evidence);info=evidence['flat3823']
    if len(data)!=2080 or hashlib.sha256(data).hexdigest()!=info['sha256']:raise ValueError('Haybot flat identity changed')
    for key in ('pixel','palette'):
        start,size,digest=info[key]
        if hashlib.sha256(data[start:start+size]).hexdigest()!=digest:raise ValueError('Haybot captured texture span changed')
    state=models.texture_coordinate_state(run)
    if (state['width'],state['height'],state['size'])!=(64,64,0) or run.texture_scale!=(0xD7000002,0xFFFFFFFF):
        raise ValueError('Haybot texture dimensions/mip selection changed')
    rows=bytes(data[y*32+(x^(4 if y&1 else 0))] for y in range(64) for x in range(32))
    png=models.encode_indexed_png(rows+data[2048:],'linear',64,64)
    if hashlib.sha256(png).hexdigest()!=info['png_sha256']:raise ValueError('Haybot original PNG changed')
    return png


def guard_animations(record,document,bind=False):
    if tuple(record.get(k) for k in ('animation_clip_count','animation_frame_count','incompatible_animation_clip_count'))!=(15,291,0):
        raise ValueError('Haybot animation inventory changed')
    actual=[(a.get('extras',{}).get('sourceBank'),a.get('extras',{}).get('sourceEntry'),a.get('extras',{}).get('sourcePair'),a.get('extras',{}).get('sourceFrameCount')) for a in document.get('animations',[])]
    if actual != ([] if bind else [(2,75,i,n) for i,n in enumerate(FRAMES)]):raise ValueError('Haybot clip pairs/frames changed')


def apply_document(document,geometry,evidence):
    guard_evidence(evidence);run=checked_run(geometry,evidence);result=copy.deepcopy(document)
    result.setdefault('extras',{})['capturedTexturePreset']={'preset':PRESET,'scope':SCOPE,'contract_sha256':CONTRACT_SHA256,'capture_replayed_locally':False,'capture_provenance':capture_provenance(),'evidence':evidence}
    found=0
    for mat in result['materials']:
        if mat['extras']['materialRun']!=16:continue
        found+=1
        images=result.setdefault('images',[]);image=len(images);images.append({'uri':'../textures/haybot-captured-selector15-flat3823.png'})
        samplers=result.setdefault('samplers',[]);sampler=len(samplers);address=models.texture_address_mode(run)['gltf']
        samplers.append({'magFilter':9729,'minFilter':9729,'wrapS':address['wrapS'],'wrapT':address['wrapT']})
        textures=result.setdefault('textures',[]);texture=len(textures);textures.append({'source':image,'sampler':sampler})
        mat['pbrMetallicRoughness']['baseColorTexture']={'index':texture}
        mat['extras']['capturedTexturePreset']={'preset':PRESET,'scope':SCOPE,'flat':3823,'source_alpha_preserved':True,'effective_material':evidence['material']}
    if found!=1:raise ValueError('Haybot affected material changed')
    common.guard_document_preservation(document,result)
    return result


def build_files(rom,texture_root):
    evidence=contract();guard_evidence(evidence)
    path,layout=models.resolve_rom('us',rom);normalized,_=models.normalize_rom(path.read_bytes());digest=hashlib.sha1(normalized).hexdigest()
    game=models.parse_game_archive(normalized[layout['game_start']:layout['game_end']]);start=0x15061FA8-layout['game_vram']
    if hashlib.sha1(game.code[start:start+0xE4]).hexdigest()!=evidence['selector_evidence']['updater_sha1']:raise ValueError('Haybot selector updater changed')
    _,_,other_digest,bundles,_=models.load_model_bundles('us',rom,1)
    if digest!=other_digest:raise ValueError('Haybot ROM changed during extraction')
    raw=next(b for b in bundles if b.index==75).segments[0].data;geometry,model_layout,draw=checked_model(raw,digest,evidence)
    payloads=models.load_flat_asset_payloads('us',rom,digest);png=decode_image(geometry,payloads[3823],evidence)
    start,end=map(lambda v:int(v,16),evidence['flat3823']['compressed_rom_range'])
    if hashlib.sha256(normalized[start:end]).hexdigest()!=evidence['flat3823']['compressed_sha256']:raise ValueError('Haybot compressed payload changed')
    with tempfile.TemporaryDirectory() as temp:
        base=Path(temp)/'baseline'
        manifest=models.extract_model_preview('us',rom,texture_root,base,False,1,rom_defaults=True,entry_filter=frozenset({75}),preserve_zero_area_faces=True)
        files={str(p.relative_to(base)):p.read_bytes() for p in base.rglob('*') if p.is_file()}
    source_binaries={name:data for name,data in files.items() if name.endswith('.bin')}
    animation_manifest,_=models.load_character_animation_manifest('us',rom,include_files=False)
    companion=next(item for item in animation_manifest['entries'] if item['bank_entry']==75)
    if (companion['decoded_size'],companion['decoded_sha1'],companion['logical_animation_route_count'],companion['clip_pair_count'])!=(21736,'83fb569f9ca8c7eeec4fe22f808ae7d656b31827',20,15):
        raise ValueError('Haybot stored animation companion/routes changed')
    record=manifest['models'][0]
    if (record['face_count'],record['vertex_count'],record['texture_coordinate_count'],record['joint_count'],record['omitted_zero_area_face_count'])!=(1226,1625,1625,45,0):raise ValueError('Haybot full-source preservation changed')
    for bind in (False,True):
        name=record['bind_gltf_file' if bind else 'gltf_file'];before=json.loads(files[name]);guard_animations(record,before,bind)
        after=apply_document(before,geometry,evidence);guard_animations(record,after,bind)
        common.guard_document_preservation(before,after,files[name.replace('.gltf','.bin')],files[name.replace('.gltf','.bin')])
        files[name]=(json.dumps(after,indent=2)+'\n').encode()
    run=record['material_runs'][16]
    if run['status']!='rom-default-payload-span-unresolved' or run['texture'] is not None:raise ValueError('Haybot default frontier changed')
    run['status']='captured-haybot-selector15-inspection';run['captured_texture_preset']={'preset':PRESET,'scope':SCOPE}
    info={'flat_index':3823,'file':'textures/haybot-captured-selector15-flat3823.png','png_sha1':evidence['flat3823']['png_sha1'],'width':64,'height':64,'source_family':'captured-haybot-ROM-decoded','format':2,'size':0,'pixel_byte_offset':0,'palette_byte_offset':2048}
    run['texture']=info;files[info['file']]=png;manifest['textures'].append(info)
    for field in ('object_file','material_file'):files.pop(record[field],None);record[field]=None
    manifest.update(family='explicit-captured-character-texture-preset',rom_only=False,preset=PRESET,scope=SCOPE,capture_replayed_locally=False,capture_evidence=evidence,capture_provenance=capture_provenance(),linked_material_run_count=manifest['linked_material_run_count']+1,linked_face_count=manifest['linked_face_count']+24,copied_texture_count=len(manifest['textures']))
    from collections import Counter
    runs=record['material_runs'];manifest['status_run_counts']=dict(Counter(r['status'] for r in runs));manifest['status_face_counts']={s:sum(r['face_count'] for r in runs if r['status']==s) for s in manifest['status_run_counts']}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();files['README.txt']=(SCOPE+'\n'+json.dumps(capture_provenance(),indent=2)+'\n').encode()
    if source_binaries!={name:data for name,data in files.items() if name.endswith('.bin')}:raise ValueError('Haybot source binary changed')
    return files,geometry,model_layout,draw,manifest


def verify_files(output,files,geometry,layout,draw,manifest):
    for name,data in files.items():
        path=output/name
        if not path.resolve().is_relative_to(output.resolve()) or path.read_bytes()!=data:raise ValueError('Haybot output changed: '+name)
    record=manifest['models'][0];reports={}
    for bind in (False,True):
        path=output/record['bind_gltf_file' if bind else 'gltf_file'];guard_animations(record,json.loads(path.read_text()),bind)
        reports['bind' if bind else 'normal']=model_validation.compare_geometry(path,geometry,tuple(layout['joints']),record['material_runs'],draw_pass=draw)
    return reports


def main(argv=None):
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--preset',required=True,choices=[PRESET]);parser.add_argument('--rom',type=Path);parser.add_argument('--textures',type=Path,default=common.ROOT/'build/assets/textures');parser.add_argument('--output',type=Path,required=True);parser.add_argument('--verify',action='store_true');args=parser.parse_args(argv)
    output=args.output.resolve()
    if not output.is_relative_to((common.ROOT/'build').resolve()) or output==(common.ROOT/'build').resolve():raise ValueError('appearance output must be a child of build/')
    files,geometry,layout,draw,manifest=build_files(args.rom,args.textures)
    if not args.verify:
        output.mkdir(parents=True,exist_ok=False)
        for name,data in files.items():
            p=output/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)
    reports=verify_files(output,files,geometry,layout,draw,manifest)
    print('Verified captured Haybot selector15: 24 newly linked faces; complete source faces', [r['faces'] for r in reports.values()])
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
