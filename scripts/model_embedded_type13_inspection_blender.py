"""Blender worker for one source-preserving type13 counter5 material inspection."""
from pathlib import Path
import argparse
import hashlib
import json
import math
import sys
import tempfile

import bpy
from mathutils import Vector

OUT = None
BLEND = 'embedded-type13-counter5.blend'
FACTORY_HANDLERS = {name: frozenset((f.__module__, f.__qualname__) for f in getattr(bpy.app.handlers,name))
                    for name in dir(bpy.app.handlers) if isinstance(getattr(bpy.app.handlers,name),list)}


def require(value,message):
    if not value:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def stable(value):
    return sha(json.dumps(value,sort_keys=True,allow_nan=False).encode())


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

def render_setup(scene,width,height):
    available={x.identifier for x in scene.render.bl_rna.properties['engine'].enum_items}
    scene.render.engine=next(x for x in ('BLENDER_EEVEE_NEXT','BLENDER_EEVEE') if x in available)
    scene.render.resolution_x=width;scene.render.resolution_y=height;scene.render.resolution_percentage=100
    scene.render.image_settings.file_format='PNG';scene.render.image_settings.color_mode='RGBA'
    scene.render.image_settings.color_depth='8';scene.render.dither_intensity=0
    scene.view_settings.view_transform='Raw';scene.view_settings.look='None'
    scene.view_settings.exposure=0;scene.view_settings.gamma=1
    scene.render.film_transparent=False

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

def set_view(framing, direction):
    scene=bpy.context.scene; cam=scene.camera; center=Vector(framing['center'])
    cam.location=center+Vector(direction).normalized()*framing['diagonal']*2
    cam.rotation_euler=(center-cam.location).to_track_quat('-Z','Y').to_euler(); bpy.context.view_layer.update()

def framing_signature(scene):
    # ORTHO framing depends on lens shifts, sensor fit and render aspect/crop
    # as well as the camera transform and scale. Pin the disabled DOF state.
    return {'camera':{key:getattr(scene.camera.data,key) for key in
                     ('type','ortho_scale','shift_x','shift_y','sensor_fit','clip_start','clip_end')},
            'depth_of_field':scene.camera.data.dof.use_dof,
            'render':{key:getattr(scene.render,key) for key in
                      ('resolution_x','resolution_y','resolution_percentage','pixel_aspect_x','pixel_aspect_y',
                       'use_border','use_crop_to_border','border_min_x','border_max_x','border_min_y','border_max_y')}}

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
            'engine':scene.render.engine,'transparent':scene.render.film_transparent,'framing':framing_signature(scene),
            'scene_count':len(bpy.data.scenes)}

def source_pixels():
    payload=(OUT/'source/flat4275.bin').read_bytes();require(len(payload)==2048,'pixel span')
    return [payload[y*64+(x^(4 if y&1 else 0))]/255 for y in range(32) for x in range(64)]

def texture():
    im=bpy.data.images.load(str(OUT/'texture.png'),check_existing=False);im.name='Type13_flat4275_raw_I8'
    im.colorspace_settings.name='Non-Color';im.alpha_mode='STRAIGHT'
    pixels=source_pixels();expected=[x for x in pixels for _ in range(4)]
    require(len(im.pixels)==8192 and max(abs(a-b)for a,b in zip(im.pixels[:],expected))<1e-7,'all2048rawI8pixelvalues')
    return im

def shader(im,uv=None,alpha_oracle=False):
    mat=bpy.data.materials.new('Type13_counter5_I8');mat.use_nodes=True
    nodes=mat.node_tree.nodes;nodes.clear();links=mat.node_tree.links
    out=nodes.new('ShaderNodeOutputMaterial');emit=nodes.new('ShaderNodeEmission');emit.inputs['Strength'].default_value=1
    tex=nodes.new('ShaderNodeTexImage');tex.name='TEXEL0';tex.image=im;tex.interpolation='Linear';tex.extension='EXTEND'
    if uv is None:
        coords=nodes.new('ShaderNodeUVMap');coords.uv_map='Counter5UV';links.new(coords.outputs['UV'],tex.inputs['Vector'])
    else:
        coords=nodes.new('ShaderNodeCombineXYZ');coords.inputs[0].default_value=uv[0];coords.inputs[1].default_value=uv[1]
        links.new(coords.outputs[0],tex.inputs['Vector'])
    links.new(tex.outputs['Alpha'if alpha_oracle else 'Color'],emit.inputs['Color'])
    if uv is not None:links.new(emit.outputs[0],out.inputs['Surface'])
    else:
        transparent=nodes.new('ShaderNodeBsdfTransparent');mix=nodes.new('ShaderNodeMixShader')
        links.new(tex.outputs['Alpha'],mix.inputs[0]);links.new(transparent.outputs[0],mix.inputs[1]);links.new(emit.outputs[0],mix.inputs[2]);links.new(mix.outputs[0],out.inputs['Surface'])
        mat.surface_render_method='DITHERED';mat.use_backface_culling=False
    return mat

def sample(pixels,u,v):
    x,y=u*64-.5,v*32-.5;ix,iy=math.floor(x),math.floor(y);fx,fy=x-ix,y-iy
    return sum(pixels[max(0,min(31,iy+dy))*64+max(0,min(63,ix+dx))]*wx*wy
               for dx,wx in ((0,1-fx),(1,fx))for dy,wy in((0,1-fy),(1,fy)))

def oracle():
    bpy.ops.wm.read_factory_settings(use_empty=True);im=texture();scene=bpy.context.scene;render_setup(scene,768,128)
    pixels=source_pixels();coords=[(-.25,.5),(1.25,.5),(0,0),(1,1)]+[((x+.73)/64,(y+.19)/32)for x,y in((0,16),(4,16),(8,16),(16,16),(24,12),(32,18),(48,15),(63,16))]
    rows=[]
    for row in range(2):
        for col,uv in enumerate(coords):
            mat=shader(im,uv,alpha_oracle=bool(row));mesh=bpy.data.meshes.new('Swatch')
            mesh.from_pydata([(col,row,0),(col+1,row,0),(col+1,row+1,0),(col,row+1,0)],[],[(0,1,2,3)])
            obj=bpy.data.objects.new('Swatch',mesh);scene.collection.objects.link(obj);mesh.materials.append(mat)
            rows.append({'row':row,'col':col,'UV':uv,'expected':sample(pixels,*uv)})
    cd=bpy.data.cameras.new('Oracle');cam=bpy.data.objects.new('Oracle',cd);scene.collection.objects.link(cam)
    cd.type='ORTHO';cd.ortho_scale=12;cam.location=(6,1,10);scene.camera=cam
    with tempfile.TemporaryDirectory(prefix='type13-oracle-')as temp:
        path=Path(temp)/'sampling.png';scene.render.filepath=str(path);bpy.ops.render.render(write_still=True)
        result=bpy.data.images.load(str(path),check_existing=False);result.colorspace_settings.name='Non-Color';data=list(result.pixels[:])
    maximum=0
    for r in rows:
        x=r['col']*64+32;y=r['row']*64+32;rgb=data[(y*768+x)*4:(y*768+x)*4+3]
        error=max(abs(a-r['expected'])for a in rgb);maximum=max(maximum,error);r.update(actual=rgb,error=error)
    require(maximum<2/255,'I8 RGB/alpha/clamp bilinear oracle')
    return {'samples':24,'maximum_error':maximum,'threshold':2/255, 'expected_sha256':stable([{k:v for k,v in r.items()if k not in ('actual','error')}for r in rows]), 'scope':'Independent raw I8 byte CPU/GPU bilinear-clamp RGB and alpha oracle; not native RDP filtering proof.'}

def geometry(obj):
    mesh=obj.data
    return {'positions':[list(v.co)for v in mesh.vertices],'faces':[list(p.vertices)for p in mesh.polygons],
            'matrix':[list(r)for r in obj.matrix_world],
            'original_color':{'domain':mesh.color_attributes['Color'].domain,'type':mesh.color_attributes['Color'].data_type,
                              'values':[list(c.color)for c in mesh.color_attributes['Color'].data]}}

def verify_geometry(obj,proof):
    expected=[[v['position'][0],-v['position'][2],v['position'][1]]for v in proof['source_vertices']]
    # glTF importer may remap indices; verify every ordered corner by rawsource position.
    require(len(obj.data.vertices)==6 and len(obj.data.polygons)==4,'primitivecount')
    require(sorted(tuple(v.co)for v in obj.data.vertices)==sorted(tuple(v)for v in expected),'sourcepositions')
    for polygon,face in zip(obj.data.polygons,proof['ordered_triangles']):
        require([list(obj.data.vertices[i].co)for i in polygon.vertices]==[expected[i]for i in face],'orderedsourceface')
    require(all(all(x==0 for x in c.color)for c in obj.data.color_attributes['Color'].data),'rawzeroRGBApreserved')

def apply_uv(obj,proof,create):
    if create:obj.data.uv_layers.new(name='Counter5UV')
    require(len(obj.data.uv_layers)==1 and obj.data.uv_layers[0].name=='Counter5UV','selected UV layer')
    uv=obj.data.uv_layers['Counter5UV'];selected=proof['selected_state']['raw_modified_ST']
    values=[]
    for poly,face in zip(obj.data.polygons,proof['ordered_triangles']):
        for loop,vi in zip(poly.loop_indices,face):
            s,t=selected[vi];expected=((s/32-256)/64,(t/32-256)/32)
            if create:uv.data[loop].uv=expected
            require(tuple(uv.data[loop].uv)==expected,'cached ST normalized without second texture scale')
            values.append(list(expected))
    return values

def snapshot(obj,proof):
    verify_geometry(obj,proof);no_execution()
    require(len([im for im in bpy.data.images if im.source=='FILE'])==1 and len(obj.data.materials)==1,'single texture/material')
    im=bpy.data.images['Type13_flat4275_raw_I8'];require(im.packed_file and sha(bytes(im.packed_file.data))==sha((OUT/'texture.png').read_bytes()),'packed PNG')
    require(im.colorspace_settings.name=='Non-Color'and im.alpha_mode=='STRAIGHT','byte color domain')
    require(tuple(im.size)==(64,32) and len(im.pixels)==8192,'reopened I8 pixel dimensions')
    require(max(abs(a-b)for a,b in zip(im.pixels[:],[p for p in source_pixels()for _ in range(4)]))<1e-7,'reopenedrawI8')
    require(obj['source_vertex_bytes_hex']==(OUT/'source/source/vertices-8008b3e0.bin').read_bytes().hex(),'rawsourcebytes')
    require(obj['scope']==proof['scope'] and obj['counter']==5 and obj['source_proof_sha256']==sha((OUT/'source-proof.json').read_bytes()),'embedded scope/source identity')
    require(len(obj.data.color_attributes)==1 and obj.data.shape_keys is None,'original attribute set')
    require(getattr(bpy.context.scene,'compositing_node_group',None) is None and getattr(bpy.context.scene,'node_tree',None) is None,'unexpected compositor')
    return {'geometry':geometry(obj),'uvs':apply_uv(obj,proof,False),'material':material_signature(obj.data.materials[0]),
            'image_sha256':sha(bytes(im.packed_file.data)),'image_domain':im.colorspace_settings.name, 'all_materials':{m.name:material_signature(m)for m in bpy.data.materials},'scene':scene_signature()}

def setup(proof):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.import_scene.gltf(filepath=str(OUT/'source/geometry/embedded-type13-8008b3e0.gltf'));bpy.context.view_layer.update()
    objs=[o for o in bpy.data.objects if o.type=='MESH'];require(len(objs)==1,'oneoriginalmesh');obj=objs[0]
    verify_geometry(obj,proof);baseline=geometry(obj);apply_uv(obj,proof,True);im=texture();mat=shader(im)

    for original in obj.data.materials:original.use_fake_user=True
    obj.data.materials.clear();obj.data.materials.append(mat)
    require(geometry(obj)==baseline,'sourcegeometrychanged')
    obj['scope']=proof['scope'];obj['counter']=5
    obj['source_vertex_bytes_hex']=(OUT/'source/source/vertices-8008b3e0.bin').read_bytes().hex()
    obj['source_proof_sha256']=sha((OUT/'source-proof.json').read_bytes())
    scene=bpy.context.scene;render_setup(scene,768,768)
    # Raw view exposes byte-domain source emission without an artistic transform.
    scene.world=bpy.data.worlds.new('InspectionBackground');scene.world.use_nodes=True
    scene.world.node_tree.nodes['Background'].inputs['Color'].default_value=(.025,.03,.04,1)
    cd=bpy.data.cameras.new('Camera');cam=bpy.data.objects.new('Camera',cd);scene.collection.objects.link(cam)
    cd.type='ORTHO';cd.ortho_scale=470;cd.clip_end=3000;scene.camera=cam
    framing={'center':[-200,0,0],'diagonal':500};set_view(framing,(.3,-2,.65))
    bpy.ops.file.pack_all();return obj,framing,snapshot(obj,proof)


def main(argv=None):
    global OUT
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--verify',action='store_true')
    args=parser.parse_args(argv if argv is not None else sys.argv[sys.argv.index('--')+1:])
    require('--disable-autoexec' in sys.argv,'auto-execution must be disabled')
    OUT=args.output.resolve();proof=json.loads((OUT/'source-proof.json').read_text())
    require(proof['schema_version']==1 and proof['kind']=='embedded-type13-counter5'
            and proof['primitive']=='type13' and proof['counter']==5,'selected source state changed')
    source_before={'source-proof.json':(OUT/'source-proof.json').read_bytes()}
    for name,digest in proof['files'].items():
        path=(OUT/name).resolve();require(path.is_relative_to(OUT),'source resource outside output')
        source_before[name]=path.read_bytes();require(sha(source_before[name])==digest,'prepared source changed')
    names=('artifact.json',BLEND,'three-quarter.png','rear.png')
    before={name:(OUT/name).read_bytes()for name in names}if args.verify else None
    if not args.verify:
        require(not any((OUT/name).exists()for name in names),'inspection artifact already exists')
    # Reconstruct expected source mesh, original diagnostic material, selected UVs,
    # exact raw-byte image shader and framing before opening the saved Blend.
    numeric=oracle();obj,framing,expected=setup(proof)
    if args.verify:
        saved=json.loads(before['artifact.json'])
        require(saved['schema_version']==1 and saved['blend_file']==BLEND and saved['snapshot']==expected
                and saved['scope']==proof['scope'] and saved['inspection_state']==proof['inspection_state']
                and saved['source_proof_sha256']==sha(source_before['source-proof.json'])
                and saved['source_gltf_sha256']==proof['source_gltf_sha256'],
                'saved audit differs from fresh source reconstruction')
        require(saved['blend_sha256']==sha(before[BLEND]),'saved Blend bytes changed')
        require(set(saved['renders'])=={'three-quarter.png','rear.png'} and
                all(sha(before[name])==digest for name,digest in saved['renders'].items()),'preview bytes changed')
        require(saved['sampling_oracle']['samples']==24 and saved['sampling_oracle']['threshold']==2/255
                and saved['sampling_oracle']['expected_sha256']==numeric['expected_sha256']
                and 0<=saved['sampling_oracle']['maximum_error']<2/255,'saved sampler proof changed')
    else:
        bpy.ops.wm.save_as_mainfile(filepath=str(OUT/BLEND));renders={}
        for name,direction in [('three-quarter',(.3,-2,.65)),('rear',(-.2,2,.25))]:
            set_view(framing,direction);bpy.context.scene.render.filepath=str(OUT/(name+'.png'))
            bpy.ops.render.render(write_still=True);renders[name+'.png']=sha((OUT/(name+'.png')).read_bytes())
        saved={'schema_version':1,'snapshot':expected,'sampling_oracle':numeric,'scope':proof['scope'],
               'inspection_state':proof['inspection_state'],'source_proof_sha256':sha(source_before['source-proof.json']),
               'source_gltf_sha256':proof['source_gltf_sha256'],'blend_file':BLEND,
               'blend_sha256':sha((OUT/BLEND).read_bytes()),'renders':renders,'blender_version':bpy.app.version_string}
    bpy.ops.wm.open_mainfile(filepath=str(OUT/BLEND),load_ui=False,use_scripts=False);bpy.context.view_layer.update()
    objects=[o for o in bpy.data.objects if o.type=='MESH'];require(len(objects)==1,'saved mesh instance set changed')
    require(snapshot(objects[0],proof)==expected,'saved scene differs from fresh source reconstruction')
    require(all((OUT/name).read_bytes()==raw for name,raw in source_before.items()),'source inputs changed during Blender')
    if args.verify:
        require(all((OUT/name).read_bytes()==raw for name,raw in before.items()),'verification wrote artifact files')
    else:
        (OUT/'artifact.json').write_text(json.dumps(saved,indent=2,allow_nan=False)+'\n')
    print(json.dumps({'verified':True,'vertices':6,'faces':4,'source_I8_pixels':2048,
                      'sampler_checks':24,'maximum_error':numeric['maximum_error'],'verify_writes':False if args.verify else None}))
    return 0


if __name__=='__main__':
    raise SystemExit(main())
