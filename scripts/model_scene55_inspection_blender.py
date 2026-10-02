"""Blender worker for source-bounded scene55 dual-texture inspection.

Verification reconstructs expected geometry, materials and exact source colors
before opening the existing Blend with execution disabled.
"""
from pathlib import Path
import argparse
import base64
import hashlib
import json
import math
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from model_inspection_camera import camera_framing
import tempfile

import bpy
from mathutils import Vector

SOURCE_RGBA = '_CBFD_STORED_RGBA'
BLEND = 'scene55-zero-scroll-stored-rgba.blend'
SCOPE = ''
FACTORY_HANDLERS = {name: frozenset((f.__module__, f.__qualname__) for f in getattr(bpy.app.handlers, name)) for name in dir(bpy.app.handlers)
                    if isinstance(getattr(bpy.app.handlers, name), list)}


def require(value, message):
    if not value:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def stable(value):
    return sha(json.dumps(value, sort_keys=True, allow_nan=False).encode())


def vector(value):
    try:
        return list(value)
    except TypeError:
        return value


def material_signature(mat):
    nodes = []
    for n in mat.node_tree.nodes:
        require(n.type not in ('GROUP', 'SCRIPT'), 'unexpected executable or group shader')
        row = {'name': n.name, 'type': n.bl_idname,
               'inputs': [(s.identifier, vector(s.default_value)) for s in n.inputs if hasattr(s, 'default_value')],
               'outputs': [(s.identifier, vector(s.default_value)) for s in n.outputs if hasattr(s, 'default_value')]}
        for key in ('operation', 'attribute_name', 'layer_name', 'uv_map', 'vector_type', 'convert_from', 'convert_to',
                    'interpolation', 'extension', 'projection', 'blend_type', 'use_clamp', 'mute'):
            if hasattr(n, key):
                row[key] = getattr(n, key)
        if n.type == 'TEX_IMAGE':
            row['image'] = n.image.name if n.image else None
        nodes.append(row)
    settings = {k: vector(getattr(mat, k)) for k in ('diffuse_color', 'roughness', 'metallic',
                'use_nodes', 'surface_render_method', 'use_backface_culling', 'use_transparency_overlap')
                if hasattr(mat, k)}
    return json.loads(json.dumps({'settings': settings, 'nodes': nodes,
           'links': sorted((l.from_node.name,l.from_socket.identifier,l.to_node.name,l.to_socket.identifier)
                           for l in mat.node_tree.links)}))


def source_pixels(payload, tile):
    # Independent per-pixel source byte/nibble/TLUT oracle, in Blender bottom-up order.
    require(len(payload) == 2080 and tile in (0, 1), 'source pixel layout')
    result = []
    for y in range(32):
        for x in range(64):
            byte = payload[tile*1024 + y*32 + ((x//2) ^ (4 if y & 1 else 0))]
            nibble = (byte >> (0 if x & 1 else 4)) & 15
            color = int.from_bytes(payload[2048+nibble*2:2050+nibble*2], 'big')
            result.append(tuple(((color >> shift) & 31)*255//31 for shift in (11,6,1)) + (255*(color & 1),))
    return result


def pixel_planes(output):
    images, expected = [], []
    payload = (output/'source/flat0737.bin').read_bytes()
    for i in (0, 1):
        pixels = source_pixels(payload, i)
        im = bpy.data.images.load(str(output/f'textures/flat0737-plane{i}.png'), check_existing=False)
        im.name = f'CBFD_flat737_plane{i}_raw_bytes'
        im.colorspace_settings.name = 'Non-Color'; im.alpha_mode = 'STRAIGHT'
        actual = list(im.pixels[:])
        require(len(actual) == 8192 and max(abs(a-b/255) for a,b in zip(actual,
                [c for p in pixels for c in p])) < 1e-7, 'independent source pixel oracle differs')
        images.append(im); expected.append(pixels)
    return images, expected


def sample(pixels, u, v):
    x, y = u*64-.5, v*32-.5
    ix, iy = math.floor(x), math.floor(y); fx, fy = x-ix, y-iy
    return [sum(pixels[((iy+dy)%32)*64+(ix+dx)%64][c]*wx*wy/255
                for dx,wx in ((0,1-fx),(1,fx)) for dy,wy in ((0,1-fy),(1,fy))) for c in range(4)]


def shader(mat, images, *, uv=None, layer=None, rgba=None, oracle_output=None):
    mat.use_nodes = True; nodes = mat.node_tree.nodes; nodes.clear(); links=mat.node_tree.links
    out=nodes.new('ShaderNodeOutputMaterial'); out.name='Output'
    if uv is None:
        coordinate=nodes.new('ShaderNodeUVMap'); coordinate.uv_map='UVMap'; coords=coordinate.outputs['UV']
    else:
        coordinate=nodes.new('ShaderNodeCombineXYZ'); coordinate.inputs[0].default_value=uv[0]
        coordinate.inputs[1].default_value=uv[1]; coords=coordinate.outputs['Vector']
    textures=[]
    for i,im in enumerate(images):
        offset=nodes.new('ShaderNodeVectorMath'); offset.name=f'ROM_initial_tile{i}_origin'
        offset.operation='ADD'; offset.inputs[1].default_value=(0,0,0); links.new(coords,offset.inputs[0])
        texture=nodes.new('ShaderNodeTexImage'); texture.name=f'TEXEL{i}'; texture.image=im
        texture.interpolation='Linear'; texture.extension='REPEAT'; links.new(offset.outputs[0],texture.inputs['Vector'])
        textures.append(texture)
    if layer:
        shade=nodes.new('ShaderNodeVertexColor'); shade.name='Stored_source_RGBA'; shade.layer_name=layer
        color,alpha=shade.outputs['Color'],shade.outputs['Alpha']
    else:
        shade=nodes.new('ShaderNodeRGB'); shade.name='Oracle_source_RGBA'; shade.outputs[0].default_value=rgba
        alphan=nodes.new('ShaderNodeValue'); alphan.outputs[0].default_value=rgba[3]
        color,alpha=shade.outputs[0],alphan.outputs[0]
    product=nodes.new('ShaderNodeVectorMath'); product.name='Independent_sample_product'; product.operation='MULTIPLY'
    links.new(textures[0].outputs['Color'],product.inputs[0]); links.new(textures[1].outputs['Color'],product.inputs[1])
    shaded=nodes.new('ShaderNodeVectorMath'); shaded.name='Product_times_source_RGB'; shaded.operation='MULTIPLY'
    links.new(product.outputs[0],shaded.inputs[0]); links.new(color,shaded.inputs[1])
    a=nodes.new('ShaderNodeMath'); a.name='Independent_alpha_product'; a.operation='MULTIPLY'
    links.new(textures[0].outputs['Alpha'],a.inputs[0]); links.new(textures[1].outputs['Alpha'],a.inputs[1])
    sa=nodes.new('ShaderNodeMath'); sa.name='Product_times_source_alpha'; sa.operation='MULTIPLY'
    links.new(a.outputs[0],sa.inputs[0]); links.new(alpha,sa.inputs[1])
    emission=nodes.new('ShaderNodeEmission'); emission.name='Selected_combiner_RGB'; emission.inputs['Strength'].default_value=1
    selected = ([t.outputs['Color'] for t in textures]+[shaded.outputs[0],sa.outputs[0]])[oracle_output] if oracle_output is not None else shaded.outputs[0]
    links.new(selected,emission.inputs['Color'])
    if oracle_output is not None: links.new(emission.outputs[0],out.inputs['Surface'])
    else:
        transparent=nodes.new('ShaderNodeBsdfTransparent'); mix=nodes.new('ShaderNodeMixShader')
        links.new(sa.outputs[0],mix.inputs[0]); links.new(transparent.outputs[0],mix.inputs[1])
        links.new(emission.outputs[0],mix.inputs[2]); links.new(mix.outputs[0],out.inputs['Surface'])
        mat.surface_render_method='DITHERED'; mat.use_backface_culling=False
    mat['CBFD_scope']=SCOPE


def render_setup(scene,width,height):
    available={x.identifier for x in scene.render.bl_rna.properties['engine'].enum_items}
    scene.render.engine=next(x for x in ('BLENDER_EEVEE_NEXT','BLENDER_EEVEE') if x in available)
    scene.render.resolution_x=width;scene.render.resolution_y=height;scene.render.resolution_percentage=100
    scene.render.image_settings.file_format='PNG';scene.render.image_settings.color_mode='RGBA'
    scene.render.image_settings.color_depth='8';scene.render.dither_intensity=0
    scene.view_settings.view_transform='Raw';scene.view_settings.look='None'
    scene.view_settings.exposure=0;scene.view_settings.gamma=1
    scene.render.film_transparent=False



def geometry_signature():
    result=[]
    for o in sorted((o for o in bpy.context.scene.objects if o.type=='MESH'),key=lambda o:o.name):
        mesh=o.data
        attrs={}
        for a in mesh.attributes:
            if a.name.startswith('.') or a.name==SOURCE_RGBA:continue
            attrs[a.name]={'domain':a.domain,'type':a.data_type,'data':
                [list(v.vector) if hasattr(v,'vector') else list(v.color) if hasattr(v,'color') else v.value for v in a.data]}
        result.append({'name':o.name,'matrix':[list(r) for r in o.matrix_world],
                       'vertices':[list(v.co) for v in mesh.vertices],
                       'faces':[(list(p.vertices),p.material_index,p.use_smooth) for p in mesh.polygons],
                       'uvs':{u.name:[list(v.uv) for v in u.data] for u in mesh.uv_layers},'attributes':attrs})
    return stable(result)



def source_colors(obj, target, *, create):
    mesh = obj.data; corners = target['corners']
    require(len(mesh.polygons) == target['faces'] == len(corners), 'source face count')
    require(len(mesh.color_attributes) == (1 if create else 2), 'source color attribute set')
    original = mesh.color_attributes['Color']
    require(original.domain == 'CORNER' and original.data_type == 'BYTE_COLOR', 'imported color domain')
    attr = mesh.color_attributes.get(SOURCE_RGBA)
    if create:
        require(attr is None, 'derived attribute already exists')
        attr = mesh.color_attributes.new(SOURCE_RGBA, 'FLOAT_COLOR', 'CORNER')
    require(attr is not None and attr.domain == 'CORNER' and attr.data_type == 'FLOAT_COLOR', 'exact RGBA attribute')
    checked = 0; maximum = 0
    for face, row in zip(mesh.polygons, corners):
        require(len(face.vertices) == len(row) == 3, 'source triangle')
        for loop, corner in zip(face.loop_indices, row):
            x,y,z = corner['position']
            require((mesh.vertices[mesh.loops[loop].vertex_index].co-Vector((x,-z,y))).length < 1e-5,
                    'source corner position mapping')
            u,v = corner['uv']
            require(max(abs(a-b) for a,b in zip(mesh.uv_layers['UVMap'].data[loop].uv,(u,1-v))) < 2e-5,
                    'source corner UV mapping')
            rgba = tuple(c/255 for c in corner['rgba'])
            maximum = max(maximum,max(abs(a-b) for a,b in zip(original.data[loop].color,rgba)))
            if create:
                attr.data[loop].color = rgba
            require(max(abs(a-b) for a,b in zip(attr.data[loop].color,rgba)) < 1e-7, 'exact source RGBA value')
            checked += 1
    return {'corners': checked, 'maximum_original_import_color_error': maximum,
            'policy': 'Original imported Color retained; exact normalized source RGBA copied to FLOAT_COLOR corners.'}


def load_inputs(output):
    global SCOPE
    raw = (output/'source-proof.json').read_bytes(); proof = json.loads(raw)
    require(proof['schema_version'] == 1 and proof['scene_index'] == 55
            and [r['model'] for r in proof['targets']] == [[4,55,4],[4,55,5]], 'source proof layout')
    for name,digest in proof['resources'].items():
        path = (output/name).resolve()
        require(path.is_relative_to(output) and sha(path.read_bytes()) == digest, 'prepared resource changed')
    require(sha((output/'source/geometry/scene-55.gltf').read_bytes()) == proof['source_gltf_sha256'], 'source GLTF changed')
    SCOPE = proof['scope']
    return proof


def no_execution():
    require(not bpy.data.texts and not bpy.data.actions and not bpy.data.node_groups and not bpy.data.libraries,
            'inspection has text, actions, node groups or external libraries')
    blocks = []
    for attr in dir(bpy.data):
        collection = getattr(bpy.data,attr)
        if isinstance(collection,bpy.types.bpy_prop_collection):
            blocks.extend(collection)
    blocks += [m.node_tree for m in bpy.data.materials if m.node_tree]
    blocks += [w.node_tree for w in bpy.data.worlds if w.node_tree]
    require(all(not getattr(b,'animation_data',None) for b in blocks), 'inspection has animation or drivers')
    require(all(not o.modifiers and not o.constraints for o in bpy.data.objects), 'inspection has modifiers or constraints')
    # Factory reset can register Blender's pose-library callbacks twice.
    require({name: frozenset((f.__module__, f.__qualname__) for f in getattr(bpy.app.handlers,name))
             for name in FACTORY_HANDLERS} == FACTORY_HANDLERS,
            'inspection registered non-factory handlers')


def packed_images(output):
    doc = json.loads((output/'source/geometry/scene-55.gltf').read_text())
    expected = [sha(base64.b64decode(i['uri'].split(',',1)[1])) for i in doc['images']]
    expected += [sha((output/f'textures/flat0737-plane{i}.png').read_bytes()) for i in (0,1)]
    images = [im for im in bpy.data.images if im.source == 'FILE']
    require(len(images) == 62 and all(im.packed_file for im in images), 'source image packing changed')
    require(sorted(expected) == sorted(sha(bytes(im.packed_file.data)) for im in images), 'packed source bytes changed')
    for i in (0,1):
        im = bpy.data.images[f'CBFD_flat737_plane{i}_raw_bytes']
        require(im.colorspace_settings.name == 'Non-Color' and im.alpha_mode == 'STRAIGHT', 'raw image domain changed')
        values = list(im.pixels[:]); pixels = source_pixels((output/'source/flat0737.bin').read_bytes(),i)
        require(len(values) == 8192 and max(abs(a-b/255) for a,b in zip(values,[c for p in pixels for c in p])) < 1e-7,
                'saved texture pixels changed')
    return {im.name:{'sha256':sha(bytes(im.packed_file.data)), 'colorspace':im.colorspace_settings.name,
                    'alpha_mode':im.alpha_mode, 'size':list(im.size)} for im in images}


def oracle(output, proof):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    images,pixels = pixel_planes(output); scene = bpy.context.scene; render_setup(scene,512,256)
    colors = sorted({tuple(c['rgba']) for t in proof['targets'] for row in t['corners'] for c in row})
    coords = [((x+.73)/64,(y+.19)/32) for x,y in ((0,0),(17,7),(48,4),(63,31),(3,12),(29,21),(8,16),(50,29))]
    expected = []
    for row in range(4):
        for col,uv in enumerate(coords):
            rgba = tuple(c/255 for c in colors[col%len(colors)])
            a,b = [sample(p,*uv) for p in pixels]; combined = [a[c]*b[c]*rgba[c] for c in range(4)]
            rgb = (a[:3],b[:3],combined[:3],[combined[3]]*3)[row]
            mat = bpy.data.materials.new(f'Oracle_{row}_{col}'); shader(mat,images,uv=uv,rgba=rgba,oracle_output=row)
            mesh = bpy.data.meshes.new('Swatch')
            mesh.from_pydata([(col,row,0),(col+1,row,0),(col+1,row+1,0),(col,row+1,0)],[],[(0,1,2,3)])
            obj = bpy.data.objects.new('Swatch',mesh); scene.collection.objects.link(obj); mesh.materials.append(mat)
            expected.append({'row':row,'column':col,'uv':uv,'source_RGBA':rgba,'expected_RGB':rgb})
    cd = bpy.data.cameras.new('OracleCamera'); cam = bpy.data.objects.new('OracleCamera',cd)
    scene.collection.objects.link(cam); cam.location=(4,2,10); cam.rotation_euler=(0,0,0)
    cd.type='ORTHO'; cd.ortho_scale=8; scene.camera=cam
    with tempfile.TemporaryDirectory(prefix='conker-scene55-oracle-') as temporary:
        path = Path(temporary)/'oracle.png'; scene.render.filepath=str(path); bpy.ops.render.render(write_still=True)
        im = bpy.data.images.load(str(path),check_existing=False); im.colorspace_settings.name='Non-Color'
        rendered = list(im.pixels[:])
    maximum = 0
    for check in expected:
        x=check['column']*64+32; y=check['row']*64+32; actual=rendered[(y*512+x)*4:(y*512+x)*4+3]
        maximum=max(maximum,max(abs(a-b) for a,b in zip(actual,check['expected_RGB'])))
    require(maximum < 2/255, 'independent two-plane GPU oracle failed')
    return {'expected_samples_sha256':stable(expected),'sample_count':32,'maximum_error':maximum,'threshold':2/255,
            'scope':'Independent source-byte CPU repeat/bilinear versus GPU plane0, plane1, combined RGB and alpha. Not native RDP filtering proof.'}


def set_view(framing, direction):
    scene=bpy.context.scene; cam=scene.camera; center=Vector(framing['center'])
    cam.location=center+Vector(direction).normalized()*framing['diagonal']*2
    cam.rotation_euler=(center-cam.location).to_track_quat('-Z','Y').to_euler(); bpy.context.view_layer.update()


def scene_signature():
    scene=bpy.context.scene
    objects={o.name:{'type':o.type,'matrix':[list(r) for r in o.matrix_world],
                    'hidden':[o.hide_render,o.hide_viewport],
                    'materials':[m.name for m in o.data.materials] if o.type=='MESH' else None,
                    'data':{k:vector(getattr(o.data,k)) for k in
                            (('type','ortho_scale','clip_start','clip_end') if o.type=='CAMERA' else
                             ('type','energy','shape','size','color') if o.type=='LIGHT' else ())}}
             for o in scene.objects}
    return {'objects':objects,'materials':{m.name:material_signature(m) for m in bpy.data.materials},
            'world':material_signature(scene.world), 'camera':scene.camera.name,
            'view':{k:getattr(scene.view_settings,k) for k in ('view_transform','look','exposure','gamma')},
            'engine':scene.render.engine,'transparent':scene.render.film_transparent,
            'scene_count':len(bpy.data.scenes)}


def setup(output, proof):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.import_scene.gltf(filepath=str(output/'source/geometry/scene-55.gltf')); bpy.context.view_layer.update()
    baseline=geometry_signature(); original={m.name:material_signature(m) for m in bpy.data.materials}
    meshes=[o for o in bpy.context.scene.objects if o.type=='MESH']
    require(len(meshes)==22 and sum(len(o.data.polygons) for o in meshes)==3948, 'imported assembly structure changed')
    images,_=pixel_planes(output); changes=[]
    for target in proof['targets']:
        matches=[o for o in meshes if list(o.get('model',[]))==target['model']]
        require(len(matches)==1, 'affected source instance set changed'); obj=matches[0]
        rgba=source_colors(obj,target,create=True)
        require(len(obj.data.materials)==1 and len(obj.data.uv_layers)==1
                and obj.data.uv_layers[0].name=='UVMap', 'source material/UV count')
        old=obj.data.materials[0]; old.use_fake_user=True
        mat=bpy.data.materials.new(f'CBFD_scene55_{target["model"][2]}_dual_plane')
        shader(mat,images,layer=SOURCE_RGBA); obj.data.materials[0]=mat
        changes.append({'object':obj.name,'model':target['model'],'source_material':old.name,
                        'new_material':mat.name,'faces':len(obj.data.polygons),'RGBA_proof':rgba})
    require(geometry_signature()==baseline, 'source geometry, original colors or UV changed')
    require(all(material_signature(bpy.data.materials[name])==sig for name,sig in original.items()), 'original material changed')
    scene=bpy.context.scene; render_setup(scene,768,768)
    scene.view_settings.view_transform='AgX'; scene.view_settings.look='AgX - Medium High Contrast'
    corners=[o.matrix_world@Vector(c) for o in meshes for c in o.bound_box]
    low=Vector([min(p[i] for p in corners) for i in range(3)]); high=Vector([max(p[i] for p in corners) for i in range(3)])
    center=(low+high)*.5; extent=high-low; diagonal=extent.length
    cd=bpy.data.cameras.new('PreviewCamera'); cam=bpy.data.objects.new('PreviewCamera',cd)
    scene.collection.objects.link(cam); scene.camera=cam; cd.type='ORTHO'; cd.ortho_scale=max(extent)*1.45
    cd.clip_end=diagonal*4; cd.clip_start=max(diagonal*.0001,.001)
    world=bpy.data.worlds.new('PreviewWorld'); world.use_nodes=True; scene.world=world
    world.node_tree.nodes['Background'].inputs['Color'].default_value=(.025,.03,.04,1)
    world.node_tree.nodes['Background'].inputs['Strength'].default_value=1.5
    for name,direction,strength in [('Key',(-1,-1.5,2),28),('Fill',(1.5,.5,.75),16)]:
        ld=bpy.data.lights.new(name,'AREA'); ld.energy=diagonal*diagonal*strength; ld.shape='DISK'; ld.size=diagonal*1.5
        light=bpy.data.objects.new(name,ld); scene.collection.objects.link(light)
        light.location=center+Vector(direction).normalized()*diagonal*1.5
        light.rotation_euler=(center-light.location).to_track_quat('-Z','Y').to_euler()
    framing={'center':list(center),'diagonal':diagonal}; set_view(framing,(1.15,-2,.85))
    scene['CBFD_scene55_scope']=proof['scope']; scene['CBFD_scene55_state']=json.dumps(proof['inspection_state'],sort_keys=True)
    scene['CBFD_scene55_source_proof_sha256']=sha((output/'source-proof.json').read_bytes())
    bpy.ops.file.pack_all(); no_execution()
    return {'geometry_signature':baseline,'original_materials':original,'changed_materials':changes,
            'packed_images':packed_images(output),'scene':scene_signature(),'framing':framing}


def verify_saved(output, proof, expected, expected_camera):
    blend=output/BLEND
    bpy.ops.wm.open_mainfile(filepath=str(blend),load_ui=False,use_scripts=False); bpy.context.view_layer.update()
    no_execution(); scene=bpy.context.scene
    require(camera_framing(scene) == expected_camera, 'saved camera framing differs from source reconstruction')
    require(scene.get('CBFD_scene55_scope')==proof['scope'] and
            json.loads(scene['CBFD_scene55_state'])==proof['inspection_state'] and
            scene.get('CBFD_scene55_source_proof_sha256')==sha((output/'source-proof.json').read_bytes()), 'saved inspection metadata changed')
    require(geometry_signature()==expected['geometry_signature'], 'saved original geometry/UV/colors changed')
    for target in proof['targets']:
        change=next(c for c in expected['changed_materials'] if c['model']==target['model'])
        obj=bpy.data.objects[change['object']]
        require(list(obj.get('model',[]))==target['model'] and
                source_colors(obj,target,create=False)==change['RGBA_proof'], 'saved exact source colors changed')
    require(scene_signature()==expected['scene'], 'saved scene or shader contract changed')
    require(packed_images(output)==expected['packed_images'], 'saved packed image contract changed')


def main(argv=None):
    parser=argparse.ArgumentParser(description=__doc__); parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--verify',action='store_true')
    args=parser.parse_args(argv if argv is not None else sys.argv[sys.argv.index('--')+1:])
    require('--disable-autoexec' in sys.argv, 'requires --disable-autoexec')
    output=args.output.resolve(); proof=load_inputs(output)
    source_before = {name:(output/name).read_bytes() for name in [*proof['resources'],'source-proof.json']}
    names=('artifact.json',BLEND,'three-quarter.png','rear.png')
    before={name:(output/name).read_bytes() for name in names} if args.verify else None
    if not args.verify:
        require(not any((output/name).exists() for name in names), 'scene55 inspection output already exists')
    # The sampler oracle and full scene expectations are built from prepared source
    # before opening any existing Blend; saved audit fields are never authority.
    sampling=oracle(output,proof); expected=setup(output,proof)
    expected_camera=camera_framing(bpy.context.scene)
    if args.verify:
        saved=json.loads(before['artifact.json'])
        require(saved['schema_version']==1 and saved['blend_file']==BLEND and saved['scope']==proof['scope']
                and saved['inspection_state']==proof['inspection_state'] and saved['structure']==expected
                and saved['source_gltf_sha256']==proof['source_gltf_sha256']
                and saved['source_proof_sha256']==sha((output/'source-proof.json').read_bytes())
                and saved['blend_sha256']==sha(before[BLEND]), 'saved audit differs from fresh source expectations')
        require(saved['sampling_oracle']['expected_samples_sha256']==sampling['expected_samples_sha256']
                and saved['sampling_oracle']['sample_count']==32
                and saved['sampling_oracle']['threshold']==2/255
                and 0 <= saved['sampling_oracle']['maximum_error'] < 2/255, 'saved oracle changed')
        require(set(saved['renders'])=={'three-quarter.png','rear.png'} and
                all(sha(before[n])==h for n,h in saved['renders'].items()), 'saved preview changed')
        verify_saved(output,proof,expected,expected_camera)
        require(all((output/name).read_bytes()==data for name,data in before.items()), 'verification changed artifact bytes')
    else:
        bpy.ops.wm.save_as_mainfile(filepath=str(output/BLEND))
        renders={}
        for view,direction in [('three-quarter',(1.15,-2,.85)),('rear',(0,1,.12))]:
            set_view(expected['framing'],direction); scene=bpy.context.scene
            scene.render.filepath=str(output/(view+'.png')); bpy.ops.render.render(write_still=True)
            renders[view+'.png']=sha((output/(view+'.png')).read_bytes())
        verify_saved(output,proof,expected,expected_camera)
        saved={'schema_version':1,'blend_file':BLEND,'blend_sha256':sha((output/BLEND).read_bytes()),
               'source_gltf_sha256':proof['source_gltf_sha256'],'source_proof_sha256':sha((output/'source-proof.json').read_bytes()),
               'scope':proof['scope'],'inspection_state':proof['inspection_state'],'blender_version':bpy.app.version_string,
               'structure':expected,'sampling_oracle':sampling,'renders':renders}
        (output/'artifact.json').write_text(json.dumps(saved,indent=2,allow_nan=False)+'\n')
    require(all((output/name).read_bytes()==data for name,data in source_before.items()), 'prepared inputs changed during Blender operation')
    print(json.dumps({'verified':True,'faces':3948,'affected_faces':84,'packed_images':62,
                      'sampling_error':sampling['maximum_error'],'verify_writes':False if args.verify else None}))
    return 0


if __name__=='__main__':
    raise SystemExit(main())
