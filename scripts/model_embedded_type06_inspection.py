"""One type06 primitive with an explicitly selected elapsed-zero material."""
from __future__ import annotations

import argparse
import copy
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile

try:
    from scripts import model_assets as models, model_embedded_geometry as embedded
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    import model_assets as models
    import model_embedded_geometry as embedded
    from model_preview_evidence import preview_fingerprint

ROOT = Path(__file__).resolve().parents[1]
SOURCE_ROOT = 'build/assets/models/embedded-geometry'
SOURCE = SOURCE_ROOT + '/geometry/embedded-type06-8008d538.gltf'
GLB = 'embedded-type06-8008d538-elapsed0.glb'
DERIVED_GLTF = 'geometry/embedded-type06-8008d538-elapsed0.gltf'
DEFAULT_OUTPUT = ROOT / 'build/assets/models/embedded-type06-material-inspection'
KIND = 'embedded-type06-elapsed0'
STATE = {'elapsed': 0, 'positive_lifetime_range': [8, 15], 'primitive_rgba_u8': [255]*4,
         'vertex_rgba': 'original normalized COLOR_0 bytes; vertex0 alpha16, others255',
         'RGB': 'PRIMITIVE * SHADE', 'alpha': 'PRIMITIVE * SHADE',
         'texture_enabled': False, 'lighting_enabled': False, 'culling_enabled': False,
         'portable_material': 'unlit; BLEND; double-sided',
         'interpolation': 'selected portable linear vertex-color interpolation', 'native_parity': False}
SCOPE = ('One original type06 primitive at selected constructor elapsed 0 with proven positive '
         'lifetimes 8..15 and white primitive RGBA255. Original vertex RGBA includes alpha16 '
         'at vertex0. Portable linear vertex-color interpolation is selected; inherited native '
         'shading flags and RSP/RDP parity remain unresolved. No native first draw, activation, '
         'effect identity, twelve runtime instances, transforms or fade timeline is inferred.')
CALLER = (0x150D8A34, 220, 'ce0290cea244d44277242557d13a3376ec24efe450fecb2b3fb8a59fcdb39121')
WORDS = {0x150D8A74: 0x240F000F, 0x150D8A78: 0x24180007,
         0x150D8A7C: 0xAFB80014, 0x150D8A80: 0xAFAF0010, 0x150D8A98: 0x0D461D78,
         0x15187678: 0x8FB60060, 0x151876BC: 0x8FB70064, 0x15187920: 0xA5E00094,
         0x15187928: 0x00577024, 0x15187930: 0x02CEC023, 0x15187940: 0xA5180096,
         0x15187694: 0xA62000A8}
TOOLS = ('scripts/model_embedded_type06_inspection.py', 'scripts/model_embedded_type06_inspection_blender.py',
         'scripts/model_embedded_geometry.py', 'scripts/model_assets.py', 'scripts/model_inspection.py',
         'scripts/model_preview_evidence.py')
VALIDATOR = 'build/tools/model-validation/node_modules/gltf-validator'


def require(value, message):
    if not value:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def encode(value):
    return (json.dumps(value, indent=2, allow_nan=False) + '\n').encode()


def selected_alpha(lifetime, elapsed=0):
    require(type(lifetime) is int and 8 <= lifetime <= 15, 'only proven positive lifetime8..15 is supported')
    require(type(elapsed) is int and elapsed == 0, 'only explicit elapsed0 is supported')
    return ((lifetime - elapsed) * 255 // lifetime) & 255


def material_contract(code, base, manifest):
    address, size, digest = CALLER
    require(sha(embedded.checked(code, base, address, size)) == digest, 'type06 caller changed')
    for address, word in WORDS.items():
        require(embedded.checked(code, base, address, 4) == word.to_bytes(4, 'big'), 'type06 initial-state instruction changed')
    state = manifest['render_state']
    require(state['texture_enabled'] is False and state['geometry_mode_clear_mask'] == '0x00020600'
            and state['combine_mode'] == ['0xFC323864', '0xFF73FFFF']
            and state['other_mode'] == ['0xEF082CAF', '0x00504A50'], 'type06 native material setup changed')
    vertices = manifest['vertices']
    require([v['rgba_u8'] for v in vertices] == [[255,255,255,16]] + [[255]*4]*3
            and all(v['st_s16'] == [0,0] for v in vertices), 'type06 source color or ST changed')
    lifetime_base = int.from_bytes(embedded.checked(code, base, 0x150D8A74, 4), 'big') & 0xFFFF
    mask = int.from_bytes(embedded.checked(code, base, 0x150D8A78, 4), 'big') & 0xFFFF
    lifetimes = [lifetime_base - (i & mask) for i in range(mask + 1)]
    require(lifetimes == list(range(15,7,-1)), 'type06 positive lifetime range changed')
    alphas = [selected_alpha(life) for life in lifetimes]
    require(alphas == [255]*8, 'type06 elapsed0 primitive alpha changed')
    return {'caller': '150D8A34 -> 151875E0 at150D8A98', 'caller_gate': 'actor+1D4 nonnull; invocation not inferred',
            'caller_span': {'address': hex(CALLER[0]), 'bytes': CALLER[1], 'sha256': CALLER[2]},
            'lifetime_argument': lifetime_base, 'random_mask_argument': mask, 'lifetime_values': lifetimes,
            'record_elapsed_initial': 0, 'object_A8_initial': 0, 'draw_gate': 'object+A8>=0',
            'primitive_alphas': alphas, 'not_a_first_draw': True}


def derived_document(original):
    require(not original.get('materials') and not original.get('extensionsUsed')
            and len(original['meshes']) == 1 and len(original['meshes'][0]['primitives']) == 1,
            'type06 original material or mesh structure changed')
    primitive = original['meshes'][0]['primitives'][0]
    require(primitive == {'attributes': {'POSITION':0, 'COLOR_0':1}, 'indices':2, 'mode':4},
            'type06 original primitive changed')
    result = copy.deepcopy(original)
    result['meshes'][0]['primitives'][0]['material'] = 0
    result['materials'] = [{'name': 'Type06_selected_elapsed0', 'doubleSided': True, 'alphaMode': 'BLEND',
        'pbrMetallicRoughness': {'baseColorFactor':[1,1,1,1], 'metallicFactor':0, 'roughnessFactor':1},
        'extensions': {'KHR_materials_unlit': {}}, 'extras': {'inspection_state':STATE, 'scope':SCOPE}}]
    result['extensionsUsed'] = ['KHR_materials_unlit']
    result['extras'] = {'sourceDiagnosticExtras':copy.deepcopy(original.get('extras',{})),
                        'scope':SCOPE, 'inspection_state':STATE,
                        'materialStatus':'selected-elapsed0-unlit-vertex-rgba',
                        'materialPolicy':'An unlit BLEND material uses original vertex RGBA at selected primitive RGBA255; native parity is incomplete.'}
    return result


def build_files(rom=None):
    manifest, raw_files = embedded.build_export(rom, primitive='type06')
    fingerprint = preview_fingerprint(ROOT / SOURCE)
    for name, raw in raw_files.items():
        require((ROOT / SOURCE_ROOT / name).read_bytes() == raw, 'existing type06 source differs from fresh ROM: ' + name)
    path, layout = models.resolve_rom('us', rom)
    normalized, _ = models.normalize_rom(path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    require(digest == manifest['normalized_sha1'], 'type06 ROM changed during preparation')
    game = models.parse_game_archive(normalized[layout['game_start']:layout['game_end']])
    state_proof = material_contract(game.code, layout['game_vram'], manifest)
    raw_gltf = 'geometry/' + embedded.NAME + '.gltf'
    binary = 'geometry/' + embedded.NAME + '.bin'
    document = derived_document(json.loads(raw_files[raw_gltf]))
    files = {'source/' + name: raw for name, raw in raw_files.items()}
    files[DERIVED_GLTF] = encode(document)
    files[binary] = raw_files[binary]
    with tempfile.TemporaryDirectory(prefix='conker-type06-derived-') as temporary:
        temp = Path(temporary)
        for name in (DERIVED_GLTF, binary):
            (temp/name).parent.mkdir(parents=True, exist_ok=True)
            (temp/name).write_bytes(files[name])
        files[GLB], packing = embedded.pack_glb(temp / DERIVED_GLTF)
    proof = {'schema_version':1, 'kind':KIND, 'primitive':'type06', 'elapsed':0, 'rom_sha1':digest,
             'source':SOURCE, 'source_fingerprint':fingerprint,
             'source_gltf_sha256':sha(raw_files[raw_gltf]), 'source_glb_sha256':sha(raw_files[embedded.NAME+'.glb']),
             'derived_glb_sha256':sha(files[GLB]), 'source_vertices':manifest['vertices'],
             'ordered_triangles':manifest['triangles'], 'inspection_state':STATE, 'scope':SCOPE,
             'initial_state_proof':state_proof, 'native_render_state':manifest['render_state'],
             'other_mode':models.decode_other_mode((0xEF082CAF,0x00504A50)), 'packing':packing,
             'files':{name:sha(raw) for name,raw in files.items()}}
    files['source-proof.json'] = encode(proof)
    require(preview_fingerprint(ROOT / SOURCE) == fingerprint, 'type06 source changed during preparation')
    return files, proof


def _checked_output(output):
    require(not Path(output).is_symlink(), 'type06 inspection output cannot be a symlink')
    output = Path(output).resolve()
    build = (ROOT/'build').resolve()
    require(output.is_relative_to(build) and output != build, 'type06 inspection output must be a child of build/')
    return output


def _read(output, name):
    path = output/name
    require(not path.is_symlink() and path.resolve().is_relative_to(output), 'type06 resource escapes output')
    return path.read_bytes()


def _worker_command(output, blender=None, *, verify=False):
    blender = blender or Path(shutil.which('blender') or '/Applications/Blender.app/Contents/MacOS/Blender')
    command = [str(blender), '--background', '--factory-startup', '--disable-autoexec', '--python-exit-code','1',
               '--python',str(ROOT/'scripts/model_embedded_type06_inspection_blender.py'), '--', '--output',str(output)]
    return command + (['--verify'] if verify else [])


def validate_gltf(output):
    """Fresh validator checks of source glTF and packed download; never writes."""
    node = shutil.which('node')
    require(node is not None, 'type06 inspection requires Node and the installed Khronos validator')
    script = r'''
const fs=require('node:fs'), path=require('node:path'), v=require(process.argv[1]);
const root=process.argv[2], gltf=process.argv[3], glb=process.argv[4];
(async()=>{const reports={};for(const name of [gltf,glb]) {
 const data=fs.readFileSync(path.join(root,name));
 const options={uri:path.basename(name),maxIssues:1000,externalResourceFunction:async uri=>{
   if(uri!=='embedded-type06-8008d538.bin')throw new Error('unlisted resource');
   return new Uint8Array(fs.readFileSync(path.join(root,'geometry',uri)));}};
 const r=name.endsWith('.glb')?await v.validateBytes(new Uint8Array(data),options):await v.validateString(data.toString('utf8'),options);
 reports[name]={issues:r.issues,version:v.version()};
}console.log(JSON.stringify(reports));})().catch(e=>{console.error(e);process.exitCode=1;});
'''
    result = subprocess.run([node,'-e',script,str(ROOT/VALIDATOR),str(output),DERIVED_GLTF,GLB],
                            cwd=ROOT, capture_output=True, text=True, check=True)
    reports = json.loads(result.stdout)
    require(set(reports) == {DERIVED_GLTF,GLB} and all(r['issues']['numErrors'] == 0
            and r['issues']['numWarnings'] == 0 for r in reports.values()), 'type06 Khronos validation failed')
    return reports


def _artifact_snapshot(output, rom=None):
    files, proof = build_files(rom)
    require(all(_read(output,name) == raw for name,raw in files.items()), 'type06 prepared source or derived GLB changed')
    contents = {name:_read(output,name) for name in ('artifact.json','validation.json','three-quarter.png','rear.png')}
    artifact = json.loads(contents['artifact.json'])
    require(artifact['glb_file'] == GLB and artifact['scope'] == SCOPE and artifact['inspection_state'] == STATE
            and artifact['source_proof_sha256'] == sha(files['source-proof.json'])
            and artifact['derived_glb_sha256'] == sha(files[GLB]), 'type06 artifact source/state changed')
    require(set(artifact['renders']) == {'three-quarter.png','rear.png'}
            and all(sha(contents[n]) == h for n,h in artifact['renders'].items()), 'type06 artifact bytes changed')
    tools = {name:sha((ROOT/name).read_bytes()) for name in TOOLS}
    tools.update({VALIDATOR+'/'+n:sha((ROOT/VALIDATOR/n).read_bytes())
                  for n in ('index.js','gltf_validator.dart.js','package.json')})
    snapshot = {'kind':KIND, 'primitive':'type06', 'elapsed':0, 'output':str(output.relative_to(ROOT)),
                'source':SOURCE, 'source_fingerprint':proof['source_fingerprint'],
                'source_gltf_sha256':proof['source_gltf_sha256'], 'source_glb_sha256':proof['source_glb_sha256'],
                'derived_glb_sha256':sha(files[GLB]), 'preview_sha256':sha(contents['three-quarter.png']),
                'inspection_state':STATE, 'files':{name:sha(raw) for name,raw in {**files,**contents}.items()},
                'tools':tools}
    return snapshot, {**files,**contents}, SCOPE


def inspection_artifact(output):
    output = _checked_output(output)
    before, contents, scope = _artifact_snapshot(output)
    require(validate_gltf(output) == json.loads(contents['validation.json']), 'type06 current Khronos result changed')
    result = subprocess.run(_worker_command(output, verify=True), cwd=ROOT, capture_output=True, text=True)
    require(result.returncode == 0, 'type06 fresh Blender verification failed: '+(result.stdout+result.stderr)[-4000:])
    after, _, _ = _artifact_snapshot(output)
    require(before == after, 'type06 inspection changed during verification')
    return {'glb':contents[GLB], 'preview':contents['three-quarter.png'], 'proof':after, 'scope':scope}


def inspection_artifact_current(output, proof):
    current, _, _ = _artifact_snapshot(_checked_output(output))
    require(current == proof, 'type06 inspection changed before publication')
    return True


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom',type=Path); parser.add_argument('--output',type=Path,default=DEFAULT_OUTPUT)
    parser.add_argument('--blender',type=Path); parser.add_argument('--verify',action='store_true')
    args = parser.parse_args(argv)
    try:
        files, _ = build_files(args.rom); output = _checked_output(args.output)
        before = None
        if args.verify:
            before, _, _ = _artifact_snapshot(output,args.rom)
        else:
            output.mkdir(parents=True,exist_ok=False)
            for name,raw in files.items():
                (output/name).parent.mkdir(parents=True,exist_ok=True); (output/name).write_bytes(raw)
        validation = encode(validate_gltf(output))
        if args.verify:
            require(_read(output,'validation.json') == validation, 'type06 current Khronos result changed')
        else:
            (output/'validation.json').write_bytes(validation)
        subprocess.run(_worker_command(output,args.blender,verify=args.verify),cwd=ROOT,check=True)
        after, _, _ = _artifact_snapshot(output,args.rom)
        require(before is None or before == after, 'type06 inspection changed during verification')
        require(build_files(args.rom)[0] == files, 'type06 sources changed during Blender operation')
    except (OSError,ValueError,KeyError,subprocess.SubprocessError) as error:
        parser.error(str(error))
    print(f'Verified type06 elapsed0 material inspection: 4 vertices, 3 faces; {output}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
