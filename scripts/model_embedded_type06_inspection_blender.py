"""Fresh-import structural and material oracle for the type06 elapsed-zero GLB."""
from pathlib import Path
import argparse
import hashlib
import json
import sys
import tempfile

import bpy
from mathutils import Vector

GLB = 'embedded-type06-8008d538-elapsed0.glb'


def require(value, message):
    if not value:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def encode(value):
    return (json.dumps(value, indent=2, allow_nan=False)+'\n').encode()


def vector(value):
    try:
        return list(value)
    except TypeError:
        return value


def material_signature(mat):
    return {'double_sided':not mat.use_backface_culling, 'render_method':mat.surface_render_method,
            'nodes':[{'name':n.name, 'type':n.type, 'mute':n.mute,
                      'layer_name':getattr(n,'layer_name',None),
                      'inputs':[(s.identifier,vector(s.default_value)) for s in n.inputs if hasattr(s,'default_value')]}
                     for n in mat.node_tree.nodes],
            'links':sorted((l.from_node.name,l.from_socket.name,l.to_node.name,l.to_socket.identifier)
                           for l in mat.node_tree.links)}


def material_contract(mat):
    require(mat.use_nodes and not mat.use_backface_culling, 'unlit double-sided material')
    nodes = list(mat.node_tree.nodes)
    require(sorted(n.type for n in nodes) == sorted(['EMISSION','LIGHT_PATH','BSDF_TRANSPARENT',
            'MIX_SHADER','MIX_SHADER','OUTPUT_MATERIAL','VERTEX_COLOR']), 'unexpected imported unlit shader')
    require(all(not n.mute for n in nodes), 'muted material node')
    by_type = {n.type:n for n in nodes if n.type != 'MIX_SHADER'}
    emit, color, output = (by_type[k] for k in ('EMISSION','VERTEX_COLOR','OUTPUT_MATERIAL'))
    require(color.layer_name in ('','Color') and emit.inputs['Strength'].default_value == 1,
            'source color attribute or emission strength changed')
    incoming = lambda socket: [(l.from_node,l.from_socket.name) for l in socket.links]
    require(incoming(emit.inputs['Color']) == [(color,'Color')], 'unlit RGB must use original COLOR_0')
    outer = output.inputs['Surface'].links[0].from_node
    require(outer.type == 'MIX_SHADER' and incoming(outer.inputs[0]) == [(color,'Alpha')]
            and incoming(outer.inputs[1]) == [(by_type['BSDF_TRANSPARENT'],'BSDF')], 'source alpha must mix transparency')
    inner = outer.inputs[2].links[0].from_node
    require(inner.type == 'MIX_SHADER' and incoming(inner.inputs[0]) == [(by_type['LIGHT_PATH'],'Is Camera Ray')]
            and incoming(inner.inputs[1]) == [(by_type['BSDF_TRANSPARENT'],'BSDF')]
            and incoming(inner.inputs[2]) == [(emit,'Emission')], 'unlit camera emission changed')
    require(len(mat.node_tree.links) == 8, 'unexpected material links')


def source_geometry(obj, proof):
    mesh = obj.data
    require(len(mesh.vertices) == 4 and len(mesh.polygons) == 3 and not mesh.uv_layers
            and len(mesh.color_attributes) == 1 and mesh.shape_keys is None, 'original primitive structure')
    expected = [[v['position'][0],-v['position'][2],v['position'][1]] for v in proof['source_vertices']]
    require(sorted(tuple(v.co) for v in mesh.vertices) == sorted(tuple(v) for v in expected), 'original positions')
    colors = mesh.color_attributes['Color']
    require(colors.domain in ('CORNER','POINT') and mesh.color_attributes.render_color_index == 0,
            'unsupported imported color domain or render attribute')
    corners = []
    for poly, face in zip(mesh.polygons,proof['ordered_triangles']):
        require([list(mesh.vertices[i].co) for i in poly.vertices] == [expected[i] for i in face], 'ordered source faces')
        for loop, source_index in zip(poly.loop_indices,face):
            index = loop if colors.domain == 'CORNER' else mesh.loops[loop].vertex_index
            value = list(colors.data[index].color)
            rgba = [v/255 for v in proof['source_vertices'][source_index]['rgba_u8']]
            require(max(abs(a-b) for a,b in zip(value,rgba)) < 1e-7, 'original RGBA including alpha16')
            corners.append(value)
    require(all(v['st_s16'] == [0,0] for v in proof['source_vertices']), 'raw source ST changed')
    require(len(obj.data.materials) == 1 and all(p.material_index == 0 for p in mesh.polygons), 'single selected material')
    require(not bpy.data.images and not bpy.data.actions and not bpy.data.texts and not bpy.data.node_groups
            and not bpy.data.libraries and all(not o.modifiers and not o.constraints for o in bpy.data.objects),
            'unexpected executable, animated or external data')
    material_contract(mesh.materials[0])
    return {'positions':[list(v.co) for v in mesh.vertices], 'faces':[list(p.vertices) for p in mesh.polygons],
            'matrix':[list(r) for r in obj.matrix_world], 'color_domain':colors.domain,
            'color_type':colors.data_type, 'ordered_corner_RGBA':corners,
            'material':material_signature(mesh.materials[0])}


def render_setup(scene, size):
    available = {x.identifier for x in scene.render.bl_rna.properties['engine'].enum_items}
    scene.render.engine = next(x for x in ('BLENDER_EEVEE_NEXT','BLENDER_EEVEE') if x in available)
    scene.render.resolution_x = size; scene.render.resolution_y = size; scene.render.resolution_percentage = 100
    scene.render.image_settings.file_format = 'PNG'; scene.render.image_settings.color_mode = 'RGBA'
    scene.render.image_settings.color_depth = '8'; scene.render.dither_intensity = 0
    # Date/render-time PNG metadata otherwise changes across fresh verification.
    for name in dir(scene.render):
        if name == 'use_stamp' or name.startswith('use_stamp_'):
            setattr(scene.render,name,False)
    scene.render.film_transparent = False
    scene.view_settings.view_transform = 'Raw'; scene.view_settings.look = 'None'
    scene.view_settings.exposure = 0; scene.view_settings.gamma = 1
    scene.world = bpy.data.worlds.new('InspectionBackground'); scene.world.use_nodes = True
    scene.world.node_tree.nodes['Background'].inputs['Color'].default_value = (.025,.03,.04,1)
    cd = bpy.data.cameras.new('Camera'); cam = bpy.data.objects.new('Camera',cd); scene.collection.objects.link(cam)
    cd.type = 'ORTHO'; cd.clip_end = 10000; scene.camera = cam
    return cam


def import_source(output, proof):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.import_scene.gltf(filepath=str(output/GLB)); bpy.context.view_layer.update()
    objects = list(bpy.data.objects)
    require(len(objects) == 1 and objects[0].type == 'MESH', 'one original mesh without runtime instances')
    obj = objects[0]
    signature = source_geometry(obj,proof)
    return obj, signature


def alpha_oracle(output, proof):
    # Render the actual imported material on a temporary triangle. Geometry is
    # diagnostic only and never written to the derived GLB or source inventory.
    obj, _ = import_source(output,proof); mat = obj.data.materials[0]
    bpy.data.objects.remove(obj,do_unlink=True)
    scene = bpy.context.scene; cam = render_setup(scene,256)
    scene.world.node_tree.nodes['Background'].inputs['Color'].default_value = (0,0,0,1)
    cam.location = (0,0,3); cam.data.ortho_scale = 2
    mesh = bpy.data.meshes.new('AlphaOracle'); mesh.from_pydata([(-1,-1,0),(1,-1,0),(-1,1,0)],[],[(0,1,2)])
    triangle = bpy.data.objects.new('AlphaOracle',mesh); scene.collection.objects.link(triangle); mesh.materials.append(mat)
    colors = mesh.color_attributes.new(name='Color',type='FLOAT_COLOR',domain='CORNER')
    for c, alpha in zip(colors.data,(16/255,1,1)):
        c.color = (1,1,1,alpha)
    with tempfile.TemporaryDirectory(prefix='type06-alpha-oracle-') as temporary:
        path = Path(temporary)/'alpha.png'; scene.render.filepath = str(path); bpy.ops.render.render(write_still=True)
        im = bpy.data.images.load(str(path),check_existing=False); im.colorspace_settings.name = 'Non-Color'
        pixels = list(im.pixels[:])
    errors = []
    for cx,cy in ((32,32),(96,32),(160,32),(32,96),(64,128),(32,160)):
        actual = sum(pixels[(y*256+x)*4] for y in range(cy-8,cy+8) for x in range(cx-8,cx+8))/256
        expected = 16/255 + (1-16/255)*(cx+cy)/256
        errors.append(abs(actual-expected))
    require(max(errors) < .02, 'portable interpolated vertex alpha render oracle')
    print(json.dumps({'alpha_oracle_maximum_error':max(errors),'sample_errors':errors}))
    return {'samples':6, 'threshold':.02,
            'scope':'Imported unlit shader over black; mean of256 interior pixels per sample versus linear COLOR_0 alpha. Not native RDP parity.'}


def render_views(directory):
    scene = bpy.context.scene; cam = render_setup(scene,768); cam.data.ortho_scale = 1450
    renders = {}
    for name,direction in [('three-quarter.png',(.25,-2,.7)),('rear.png',(-.25,2,.7))]:
        cam.location = Vector(direction).normalized()*2600
        cam.rotation_euler = (-cam.location).to_track_quat('-Z','Y').to_euler(); bpy.context.view_layer.update()
        scene.render.filepath = str(directory/name); bpy.ops.render.render(write_still=True)
        renders[name] = (directory/name).read_bytes()
    return renders


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,required=True); parser.add_argument('--verify',action='store_true')
    args = parser.parse_args(argv if argv is not None else sys.argv[sys.argv.index('--')+1:])
    require('--disable-autoexec' in sys.argv, 'auto-execution must be disabled')
    output = args.output.resolve(); raw_proof = (output/'source-proof.json').read_bytes(); proof = json.loads(raw_proof)
    require(proof['schema_version'] == 1 and proof['kind'] == 'embedded-type06-elapsed0'
            and proof['primitive'] == 'type06' and proof['elapsed'] == 0, 'selected source state changed')
    source_before = {'source-proof.json':raw_proof}
    for name,digest in proof['files'].items():
        path = output/name
        require(not path.is_symlink() and path.resolve().is_relative_to(output), 'source outside output')
        source_before[name] = path.read_bytes(); require(sha(source_before[name]) == digest, 'prepared source changed')
    names = ('artifact.json','three-quarter.png','rear.png')
    before = {name:(output/name).read_bytes() for name in names} if args.verify else None
    require(args.verify or not any((output/name).exists() for name in names), 'inspection artifact already exists')
    numeric = alpha_oracle(output,proof)
    obj, snapshot = import_source(output,proof)
    expected = {'schema_version':1, 'glb_file':GLB, 'derived_glb_sha256':sha(source_before[GLB]),
                'source_proof_sha256':sha(raw_proof), 'scope':proof['scope'], 'inspection_state':proof['inspection_state'],
                'blender_version':bpy.app.version_string, 'snapshot':snapshot, 'alpha_oracle':numeric}
    if args.verify:
        saved = json.loads(before['artifact.json']); hashes = saved.pop('renders')
        require(saved == json.loads(encode(expected)), 'fresh imported geometry or shader differs from artifact')
        require(set(hashes) == {'three-quarter.png','rear.png'}
                and all(sha(before[name]) == digest for name,digest in hashes.items()), 'preview bytes changed')
        with tempfile.TemporaryDirectory(prefix='type06-preview-verify-') as temporary:
            fresh_renders = render_views(Path(temporary))
        require(all(before[name] == raw for name,raw in fresh_renders.items()), 'fresh preview reconstruction differs')
    else:
        expected['renders'] = {name:sha(raw) for name,raw in render_views(output).items()}
        (output/'artifact.json').write_bytes(encode(expected))
    require(all((output/name).read_bytes() == raw for name,raw in source_before.items()), 'source changed during Blender operation')
    require(before is None or all((output/name).read_bytes() == raw for name,raw in before.items()), 'verification wrote artifact')
    print(json.dumps({'status':'passed','vertices':4,'faces':3,'alpha_oracle':numeric,'verify':args.verify}))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
