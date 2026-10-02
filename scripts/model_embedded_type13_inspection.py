"""Source-bound type13 material inspection at explicitly selected counter 5."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

try:
    from scripts import model_assets as models, model_embedded_geometry as embedded
    from scripts import texture_native
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    import model_assets as models
    import model_embedded_geometry as embedded
    import texture_native
    from model_preview_evidence import preview_fingerprint

ROOT=Path(__file__).resolve().parents[1]
SOURCE_ROOT='build/assets/models/embedded-geometry-type13'
SOURCE=SOURCE_ROOT+'/geometry/embedded-type13-8008b3e0.gltf'
BLEND='embedded-type13-counter5.blend'
DEFAULT_OUTPUT=ROOT/'build/assets/models/embedded-type13-material-inspection'
KIND='embedded-type13-counter5'
SCOPE=('One original type13 primitive at explicitly selected source counter 5. '
       'Raw I8 supplies unlit RGB and alpha; cached ST is interpreted after vertex-load '
       'texture scaling. Constructor counter 10 is not selected. No native first draw, '
       'three runtime instances, placement, effect identity or native RSP/raster parity claim.')
STATE={'counter':5,'format':'I8','texture':'flat4275','color_domain':'raw-byte/255',
       'RGB':'TEXEL0','alpha':'TEXEL0','filter':'linear','address':'clamp',
       'UV':'post-load signed10.5 cached ST; no second texture scale','native_parity':False}
CONSUMERS=(
    (0x150950D4,1384,'aeb811e28bae3309dbdafe4d58660070783dacc04cc93b78ac04e166ff8fa367'),
    (0x1510D0EC,648,'4a073d41f9ff67477c0ad6e8dcf73df2b875d7280a472319fbccd8667aff1f4c'),
    (0x15094F70,120,'8d9ae7535f57bf56b9ce25835cb5dc2d6cf8b9fd835967b89a85a095ac263f64'),
    (0x15095060,116,'7e3c0b9009d0e83b9a405b6373de2aacc7545df9c12723db4fc78095317b0b55'),
)
EMULATOR_REFERENCES=(
    'https://raw.githubusercontent.com/gonetz/GLideN64/master/src/uCodes/F3DEX2CBFD.cpp',
    'https://raw.githubusercontent.com/gonetz/GLideN64/master/src/gSP.cpp',
)


def require(value,message):
    if not value:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def encode(value):
    return (json.dumps(value,indent=2,allow_nan=False)+'\n').encode()


def selected_state(counter=5):
    require(type(counter) is int and counter==5,'only the explicit counter5 state is supported')
    s0=0x2800-(counter*4096//10);s1=s0+0x800
    st=[(s0,0x2000),(s0,0x2000),(s0,0x2400),(s1,0x2000),(s1,0x2000),(s1,0x2400)]
    return {'counter':counter,'raw_modified_ST':[list(v)for v in st],
            'cached_ST_uv':[[(s/32-256)/64,1-(t/32-256)/32]for s,t in st]}


def material_contract(code,code_base,data,data_base,payload):
    for address,size,digest in CONSUMERS:
        require(sha(embedded.checked(code,code_base,address,size))==digest,'type13 material consumer changed')
    require(embedded.checked(data,data_base,0x80090548,16)==bytes.fromhex('000010b3800905480100004000200401'),
            'type13 texture descriptor changed')
    tables=embedded.checked(data,data_base,0x8009DEB0,16)
    require(tables==bytes.fromhex('03010000020100000101020202020203'),'type13 loader tables changed')
    require(len(payload)==2048 and sha(payload)=='bb14d7224693e5aa0312bc85e0a86115894c3cf70d76d03f87c3a85a52237f22',
            'type13 I8 payload changed')
    # Reconstruct the complete emitted sequence from the pinned shared loader.
    width,height,fmt,size=64,32,4,1
    loaded=(width*height+tables[size])>>tables[4+size]
    line=(tables[8+size]*width+7)>>3
    commands=[(0xE7000000,0),(0xFD000000|(fmt<<21)|(tables[12+size]<<19),'flat4275-data'),
              (0xF5000000|(fmt<<21)|(tables[12+size]<<19),0x07000000),
              (0xF3000000,0x07000000|((loaded-1)<<12)),
              (0xF5000000|(fmt<<21)|(size<<19)|(line<<9),(2<<18)|(5<<14)|(2<<8)|(6<<4)),
              (0xF2000000|(256*4<<12)|(256*4),((width+255)*4<<12)|((height+255)*4))]
    require(commands==[(0xE7000000,0),(0xFD900000,'flat4275-data'),(0xF5900000,0x07000000),
                       (0xF3000000,0x073FF000),(0xF5881000,0x00094260),(0xF2400400,0x004FC47C)],
            'type13 emitted texture contract changed')
    return [{'command':f'{a:08X}','argument':f'{b:08X}'if isinstance(b,int)else b}for a,b in commands]


def build_files(rom=None):
    manifest,source_files=embedded.build_export(rom,primitive='type13')
    before=preview_fingerprint(ROOT/SOURCE)
    for name,raw in source_files.items():
        require((ROOT/SOURCE_ROOT/name).read_bytes()==raw,'existing type13 source differs from fresh ROM: '+name)
    path,layout=models.resolve_rom('us',rom);normalized,_=models.normalize_rom(path.read_bytes())
    digest=hashlib.sha1(normalized).hexdigest()
    require(digest==manifest['normalized_sha1'],'type13 ROM changed during source preparation')
    game=models.parse_game_archive(normalized[layout['game_start']:layout['game_end']])
    payload=models.load_flat_asset_payloads('us',rom,digest)[4275]
    commands=material_contract(game.code,layout['game_vram'],game.data,layout['game_data_vram'],payload)
    png=texture_native.encode_png(payload,'i8','tmem-odd-row-32bit-swap',64,32)
    require(sha(png)=='7306b180bfcce6b0c7190a676db71c1e57cb76c60cfdaa7984306356da3c138a','type13 decoded I8 image changed')
    files={'source/'+name:raw for name,raw in source_files.items()}
    files['source/flat4275.bin']=payload;files['texture.png']=png
    proof={'schema_version':1,'kind':KIND,'primitive':'type13','counter':5,'rom_sha1':digest,
           'source':SOURCE,'source_fingerprint':before,'source_gltf_sha256':sha(source_files['geometry/embedded-type13-8008b3e0.gltf']),
           'source_glb_sha256':sha(source_files['embedded-type13-8008b3e0.glb']),
           'source_vertices':manifest['vertices'],'ordered_triangles':manifest['triangles'],
           'selected_state':selected_state(),'inspection_state':STATE,'scope':SCOPE,
           'combine':manifest['render_state']['combine_formula'],
           'other_mode':models.decode_other_mode((0xEF082CAF,0x00504B50)),
           'emitted_commands':commands,'additional_consumer_spans':[{'address':hex(a),'bytes':n,'sha256':h}for a,n,h in CONSUMERS],
           'cached_ST_evidence':{'references':list(EMULATOR_REFERENCES),
                                'scope':'Primary emulator-source cross-check for cached ST; not native RSP/raster parity.'},
           'files':{name:sha(raw)for name,raw in files.items()}}
    files['source-proof.json']=encode(proof)
    require(preview_fingerprint(ROOT/SOURCE)==before,'type13 source changed during preparation')
    return files,proof


def _checked_output(output):
    require(not Path(output).is_symlink(),'type13 inspection output cannot be a symlink')
    output=Path(output).resolve();build=(ROOT/'build').resolve()
    require(output.is_relative_to(build)and output!=build,'type13 inspection output must be a child of build/')
    return output


def _worker_command(output,blender=None,*,verify=False):
    blender=blender or Path(shutil.which('blender')or'/Applications/Blender.app/Contents/MacOS/Blender')
    command=[str(blender),'--background','--factory-startup','--disable-autoexec','--python-exit-code','1',
             '--python',str(ROOT/'scripts/model_embedded_type13_inspection_blender.py'),'--','--output',str(output)]
    return command+(['--verify']if verify else [])


def _artifact_snapshot(output):
    files,proof=build_files()
    require(all((output/name).read_bytes()==raw for name,raw in files.items()),'type13 prepared source changed')
    names=('artifact.json',BLEND,'three-quarter.png','rear.png');contents={name:(output/name).read_bytes()for name in names}
    artifact=json.loads(contents['artifact.json'])
    require(artifact['blend_file']==BLEND and artifact['scope']==SCOPE and artifact['inspection_state']==STATE
            and artifact['source_proof_sha256']==sha(files['source-proof.json'])
            and artifact['source_gltf_sha256']==proof['source_gltf_sha256'],'type13 artifact source/state changed')
    require(artifact['blend_sha256']==sha(contents[BLEND])and set(artifact['renders'])=={'three-quarter.png','rear.png'}
            and all(sha(contents[n])==h for n,h in artifact['renders'].items()),'type13 artifact bytes changed')
    snapshot={'kind':KIND,'primitive':'type13','counter':5,'output':str(output.relative_to(ROOT)),
              'source':SOURCE,'source_fingerprint':proof['source_fingerprint'],'source_gltf_sha256':proof['source_gltf_sha256'],
              'source_glb_sha256':proof['source_glb_sha256'],
              'source_proof_sha256':sha(files['source-proof.json']),'blend_sha256':sha(contents[BLEND]),
              'preview_sha256':sha(contents['three-quarter.png']),'inspection_state':STATE,
              'files':{name:sha(raw)for name,raw in {**files,**contents}.items()},
              'tools':{name:sha((ROOT/name).read_bytes())for name in
                       ('scripts/model_embedded_type13_inspection.py','scripts/model_embedded_type13_inspection_blender.py',
                        'scripts/model_embedded_geometry.py','scripts/model_assets.py','scripts/model_preview_evidence.py',
                        'scripts/texture_native.py','scripts/texture_assets.py')}}
    return snapshot,contents,SCOPE


def inspection_artifact(output):
    output=_checked_output(output);before,contents,scope=_artifact_snapshot(output)
    result=subprocess.run(_worker_command(output,verify=True),cwd=ROOT,capture_output=True,text=True)
    require(result.returncode==0,'type13 fresh Blender verification failed: '+(result.stdout+result.stderr)[-4000:])
    after,_,_=_artifact_snapshot(output)
    require(before==after,'type13 inspection changed during verification')
    return {'blend':contents[BLEND],'preview':contents['three-quarter.png'],'proof':after,'scope':scope}


def inspection_artifact_current(output,proof):
    current,_,_=_artifact_snapshot(_checked_output(output))
    require(current==proof,'type13 inspection changed before publication')
    return True


def main(argv=None):
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--rom',type=Path)
    parser.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);parser.add_argument('--blender',type=Path)
    parser.add_argument('--verify',action='store_true');args=parser.parse_args(argv)
    try:
        files,_=build_files(args.rom);output=_checked_output(args.output)
        if args.verify:
            require(all((output/name).read_bytes()==raw for name,raw in files.items()),'type13 prepared source changed')
        else:
            output.mkdir(parents=True,exist_ok=False)
            for name,raw in files.items():
                (output/name).parent.mkdir(parents=True,exist_ok=True);(output/name).write_bytes(raw)
        subprocess.run(_worker_command(output,args.blender,verify=args.verify),cwd=ROOT,check=True)
        current,_=build_files(args.rom)
        require(current==files and all((output/name).read_bytes()==raw for name,raw in files.items()),
                'type13 sources changed during Blender operation')
    except(OSError,ValueError,subprocess.SubprocessError)as error:
        parser.error(str(error))
    print(f'Verified type13 counter5 material inspection: 6 vertices, 4 faces; {output}')
    return 0


if __name__=='__main__':
    raise SystemExit(main())
