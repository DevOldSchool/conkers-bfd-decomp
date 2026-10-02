#!/usr/bin/env python3
"""Build or verify a guarded, neutral-pose character66 Blender inspection file.

Run with Blender --background --disable-autoexec --python this-file -- ... .
The caller derives source-proof.json freshly from guarded ROM bytes. This worker
checks that proof against the exact imported glTF and saved Blender artifact;
it does not establish native lighting, look-at state or animation parity.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import math
from pathlib import Path
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from model_inspection_camera import camera_framing

ATTRIBUTE = '_CBFD_TEXGEN_NORMAL'
AFFECTED = {20: 20, 21: 21, 31: 31, 32: 32, 33: 32, 34: 32}
STATE = {'lighting': True, 'linear': False, 'lookat_enabled': True,
         'view_axes': [[1, 0, 0], [0, 1, 0]],
         'pose': 'neutral translation-only',
         'normal_scale': 'signed byte /127 without normalization'}
SCOPE = ('Character66 neutral-pose inspection only. Selected lighting enabled, '
         'nonlinear texture generation and canonical camera look-at axes. Raw '
         'signed normals /127 are preserved without normalization. Camera '
         'movement is supported; joint posing and animation are unsupported. '
         'Source UVMap, geometry and textures are preserved. Native gameplay '
         'camera, inherited state and pixel raster parity are not established.')
VIEWS = {'three-quarter': (1.15, -2, .85), 'rear': (0, 1, .12)}


def require(value, message):
    if not value:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def stable(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':'),
                             allow_nan=False).encode())


def load_inputs(source, audit_path):
    proof = json.loads(audit_path.read_text())
    doc = json.loads(source.read_text())
    require(digest(source.read_bytes()) == proof['source']['gltf_sha256'],
            'custom glTF fingerprint changed')
    require(proof['inspection_state'] == STATE, 'unsupported inspection state')
    require({int(k): v for k, v in proof['affected_materials'].items()} == AFFECTED,
            'affected material contract changed')
    require(not doc.get('animations'), 'neutral inspection input has animations')
    require(len(doc['meshes']) == 1 and len(doc['images']) == 17,
            'character mesh/image contract changed')
    uris = {r['uri'] for r in doc['buffers'] + doc['images']}
    require(set(proof['source']['resources']) == uris, 'source resource set changed')
    resources = {}
    for uri in sorted(uris):
        require(not uri.startswith(('data:', 'http:', 'https:')), 'external resource unsupported')
        path = (source.parent / uri).resolve()
        resources[uri] = path.read_bytes()
        require(digest(resources[uri]) == proof['source']['resources'][uri],
                f'source resource fingerprint changed: {uri}')
    require(len(doc['buffers']) == 1, 'expected one geometry buffer')
    data = resources[doc['buffers'][0]['uri']]
    require(len(data) == doc['buffers'][0]['byteLength'], 'buffer length changed')
    parents = {child: i for i, n in enumerate(doc['nodes']) for child in n.get('children', [])}
    translations = {}
    def world(index):
        if index in translations:
            return translations[index]
        n = doc['nodes'][index]
        require(not any(k in n for k in ('matrix', 'rotation', 'scale')),
                'source pose has a nontranslation transform')
        t = n.get('translation', [0, 0, 0])
        p = world(parents[index]) if index in parents else [0, 0, 0]
        translations[index] = [a + b for a, b in zip(p, t)]
        return translations[index]
    joint_world = {str(n['extras']['matrixIndex']): world(i)
                   for i, n in enumerate(doc['nodes']) if 'matrixIndex' in n.get('extras', {})}
    require(all(joint_world.get(k) == v for k, v in proof['joint_world_translations'].items()),
            'neutral joint translations changed')
    require(joint_world == proof['joint_world_translations'] and len(joint_world) == 28,
            'source joint set changed')
    faces = {r['face']: r for r in proof['faces']}
    require(len(proof['faces']) == len(faces) == 103 and
            sum(len(r['corners']) for r in faces.values()) == 309,
            'generated face/corner count changed')
    require(set(faces) == set(range(279, 302)) | set(range(365, 445)),
            'generated face span changed')
    require(set(proof['tile_states']) == {'20', '21', '31', '32'}, 'tile run set changed')
    for key, s in proof['tile_states'].items():
        require((s['width'], s['height'], s['uls'], s['ult'], s['scale_s'],
                 s['scale_t'], s['shift_s'], s['shift_t']) ==
                (32, 16 if key == '20' else 32, 2, 2, 1/32,
                 1/64 if key == '20' else 1/32, 0, 0), 'tile contract changed')
    def accessor(ai):
        a = doc['accessors'][ai]; v = doc['bufferViews'][a['bufferView']]
        require('sparse' not in a and not a.get('normalized'), 'unsupported source accessor')
        dim = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}[a['type']]
        fmt = '<' + {5121: 'B', 5123: 'H', 5125: 'I', 5126: 'f'}[a['componentType']] * dim
        size = struct.calcsize(fmt); offset = v.get('byteOffset', 0) + a.get('byteOffset', 0)
        return [struct.unpack_from(fmt, data, offset + i*v.get('byteStride', size))
                for i in range(a['count'])]
    seen = set(); total = 0; spans = []
    for primitive in doc['meshes'][0]['primitives']:
        first = primitive['extras']['firstFace']; count = primitive['extras']['faceCount']
        ids = accessor(primitive['indices']); require(len(ids) == count*3, 'face index extent changed')
        total += count; affected = primitive['material'] in AFFECTED
        require((ATTRIBUTE in primitive['attributes']) == affected, 'normal attribute scope changed')
        if not affected:
            require(not any(i in faces for i in range(first, first+count)), 'affected face omitted')
            continue
        spans.append({'material_index': primitive['material'], 'source_material_run': AFFECTED[primitive['material']],
                      'first_face': first, 'face_count': count})
        normals = accessor(primitive['attributes'][ATTRIBUTE])
        for j in range(count):
            row = faces[first+j]
            require(row['material_run'] == AFFECTED[primitive['material']], 'material face attribution changed')
            for k, corner in enumerate(row['corners']):
                require(corner['matrix_index'] in (6, 13, 19) and corner['texgen'] is True,
                        'vertex load texgen/joint changed')
                require(corner['source_st'] == [0, 0], 'affected source ST changed')
                require(len(corner['source_position']) == 3 and
                        all(math.isfinite(x) for x in corner['source_position']), 'invalid source position')
                expected = tuple(x/127 for x in corner['normal_bytes'])
                actual = normals[ids[j*3+k][0]]
                require(max(abs(a-b) for a, b in zip(actual, expected)) < 1e-7,
                        'source raw normal attribute changed')
            seen.add(first+j)
    require(total == 445 and seen == set(faces), 'source triangle coverage changed')
    require(spans == proof['primitive_spans'], 'source material spans changed')
    return proof, doc, resources, faces


def c_matrix():
    from mathutils import Matrix
    return Matrix(((1, 0, 0, 0), (0, 0, -1, 0), (0, 1, 0, 0), (0, 0, 0, 1)))


def mesh_object():
    import bpy
    meshes = [o for o in bpy.context.scene.objects if o.type == 'MESH']
    source = [o for o in meshes if o.data.attributes.get(ATTRIBUTE) is not None]
    require(len(source) == 1, 'inspection source mesh count changed')
    shapes = {b.custom_shape for o in bpy.context.scene.objects if o.type == 'ARMATURE'
              for b in o.pose.bones if b.custom_shape is not None}
    require(all(o in source or o in shapes for o in meshes), 'unexpected imported mesh')
    return source[0]


def verify_attribute(obj, proof, faces):
    from mathutils import Vector
    attr = obj.data.attributes.get(ATTRIBUTE)
    require(attr is not None and attr.domain == 'POINT' and attr.data_type == 'FLOAT_VECTOR',
            'raw normal attribute missing or converted')
    require(len(obj.data.polygons) == 445, 'imported face count changed')
    C = c_matrix(); checked = 0; nonunit = 0
    for fi, row in faces.items():
        polygon = obj.data.polygons[fi]
        require(len(polygon.vertices) == 3, 'imported triangle changed')
        for vi, corner in zip(polygon.vertices, row['corners']):
            expected = Vector([x/127 for x in corner['normal_bytes']])
            actual = attr.data[vi].vector
            require(max(abs(a-b) for a,b in zip(actual, expected)) < 1e-7,
                    'import normalized or changed raw normal')
            p = Vector(corner['source_position']) + Vector(proof['joint_world_translations'][str(corner['matrix_index'])])
            require(((obj.matrix_world @ obj.data.vertices[vi].co) - C @ p).length < 4e-5,
                    'imported source XYZ/joint mapping changed')
            nonunit += abs(actual.length-1) > .001; checked += 1
    require(checked == 309 and nonunit == 309, 'raw nonunit normal contract changed')
    return {'attribute': ATTRIBUTE, 'domain': attr.domain, 'data_type': attr.data_type,
            'vertices': len(attr.data), 'corners_checked': checked, 'nonunit_corners': nonunit}


def vector(value):
    try:
        return list(value)
    except TypeError:
        return value


def material_signature(mat):
    nodes = []
    for n in mat.node_tree.nodes:
        row = {'name': n.name, 'type': n.bl_idname,
               'inputs': [(s.identifier, vector(s.default_value)) for s in n.inputs if hasattr(s, 'default_value')]}
        for key in ('operation', 'attribute_name', 'vector_type', 'convert_from', 'convert_to',
                    'interpolation', 'extension', 'projection', 'blend_type'):
            if hasattr(n, key): row[key] = getattr(n, key)
        if n.type == 'TEX_IMAGE': row['image'] = n.image.name if n.image else None
        nodes.append(row)
    settings = {k: vector(getattr(mat, k)) for k in ('diffuse_color', 'roughness', 'metallic',
                'use_nodes', 'surface_render_method', 'use_backface_culling', 'use_transparency_overlap')
                if hasattr(mat, k)}
    return json.loads(json.dumps({'settings': settings, 'nodes': nodes, 'links': sorted((l.from_node.name, l.from_socket.identifier,
                                             l.to_node.name, l.to_socket.identifier)
                                            for l in mat.node_tree.links)}))


def geometry_signature(obj):
    import bpy
    mesh = obj.data
    # Include original UVs, topology, vertex groups, pose transforms and raw
    # attributes, independently of the source proof's affected subset.
    attrs = {}
    for a in mesh.attributes:
        if a.name.startswith('.'):
            continue
        values = []
        for v in a.data:
            for key in ('vector', 'color', 'value'):
                if hasattr(v, key):
                    values.append(vector(getattr(v, key))); break
        attrs[a.name] = {'domain': a.domain, 'type': a.data_type, 'values': values}
    return stable({'vertices': [list(v.co) for v in mesh.vertices],
                   'polygons': [(list(p.vertices), p.material_index, p.use_smooth) for p in mesh.polygons],
                   'groups': [[(g.group,g.weight) for g in v.groups] for v in mesh.vertices],
                   'uv_layers': {u.name: [list(v.uv) for v in u.data] for u in mesh.uv_layers},
                   'attributes': attrs,
                   'objects': {o.name: {'type': o.type, 'matrix': [list(r) for r in o.matrix_world],
                                       'bones': {b.name: [list(r) for r in b.matrix] for b in o.pose.bones}
                                                if o.type == 'ARMATURE' else None}
                               for o in bpy.context.scene.objects if o.type in ('ARMATURE','MESH')}})


def verify_no_execution():
    import bpy
    require(not list(bpy.data.texts) and not list(bpy.data.actions), 'inspection has text or actions')
    blocks = [*bpy.data.objects, *bpy.data.materials, *bpy.data.node_groups,
              *bpy.data.scenes, *bpy.data.worlds, *bpy.data.meshes, *bpy.data.armatures]
    blocks += [m.node_tree for m in bpy.data.materials if m.node_tree]
    require(all(not getattr(b, 'animation_data', None) or not b.animation_data.drivers
                for b in blocks), 'inspection has animation drivers')


def setup(source, doc):
    import bpy
    from mathutils import Vector
    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.import_scene.gltf(filepath=str(source))
    bpy.context.view_layer.update()
    obj = mesh_object(); scene = bpy.context.scene
    corners = [obj.matrix_world @ Vector(v) for v in obj.bound_box]
    lo = Vector([min(v[i] for v in corners) for i in range(3)])
    hi = Vector([max(v[i] for v in corners) for i in range(3)])
    center = (lo+hi)*.5; extent = hi-lo; diagonal = max(extent.length,1)
    camdata = bpy.data.cameras.new('PreviewCamera'); cam = bpy.data.objects.new('PreviewCamera',camdata)
    scene.collection.objects.link(cam); scene.camera = cam
    camdata.type = 'ORTHO'; camdata.ortho_scale = max(*extent,1)*1.45
    camdata.lens = 50; camdata.clip_start = max(diagonal*.0001,.001); camdata.clip_end = diagonal*4
    available = {i.identifier for i in scene.render.bl_rna.properties['engine'].enum_items}
    scene.render.engine = next(v for v in ('BLENDER_EEVEE_NEXT','BLENDER_EEVEE') if v in available)
    world = bpy.data.worlds.new('PreviewWorld'); world.use_nodes = True
    bg = world.node_tree.nodes.get('Background'); bg.inputs['Color'].default_value = (.025,.03,.04,1)
    bg.inputs['Strength'].default_value = 1.5; scene.world = world
    for name, direction, strength in [('Key',(-1,-1.5,2),28),('Fill',(1.5,.5,.75),16)]:
        ld = bpy.data.lights.new(name,type='AREA'); ld.energy = diagonal*diagonal*strength
        ld.shape = 'DISK'; ld.size = diagonal*1.5
        light = bpy.data.objects.new(name,ld); scene.collection.objects.link(light)
        light.location = center + Vector(direction).normalized()*diagonal*1.5
        light.rotation_euler = (center-light.location).to_track_quat('-Z','Y').to_euler()
    scene.render.resolution_x = scene.render.resolution_y = 512
    scene.render.resolution_percentage = 100; scene.render.image_settings.file_format = 'PNG'
    scene.render.image_settings.color_mode = 'RGBA'; scene.render.film_transparent = False
    scene.view_settings.look = 'AgX - Medium High Contrast'
    framing = {'center': list(center), 'diagonal': diagonal}
    set_view(framing, 'three-quarter')
    return obj, framing


def set_view(framing, view):
    import bpy
    from mathutils import Vector
    center = Vector(framing['center']); cam = bpy.context.scene.camera
    cam.location = center + Vector(VIEWS[view]).normalized()*framing['diagonal']*2
    cam.rotation_euler = (center-cam.location).to_track_quat('-Z','Y').to_euler()
    bpy.context.view_layer.update()


def add_shader(obj, proof):
    records = []
    for material_index, run in AFFECTED.items():
        mat = obj.data.materials[material_index]; nodes = mat.node_tree.nodes; links = mat.node_tree.links
        original = material_signature(mat)
        attr = nodes.new('ShaderNodeAttribute'); attr.attribute_name = ATTRIBUTE
        attr.label = 'CBFD raw signed normal /127; do not normalize'
        sep = nodes.new('ShaderNodeSeparateXYZ'); links.new(attr.outputs['Vector'],sep.inputs[0])
        neg = nodes.new('ShaderNodeMath'); neg.operation='MULTIPLY'; neg.inputs[1].default_value=-1
        links.new(sep.outputs['Z'],neg.inputs[0])
        conv = nodes.new('ShaderNodeCombineXYZ'); conv.label='Native XYZ to Blender X,-Z,Y'
        links.new(sep.outputs['X'],conv.inputs['X']); links.new(neg.outputs[0],conv.inputs['Y']); links.new(sep.outputs['Y'],conv.inputs['Z'])
        coordinates = nodes.new('ShaderNodeCombineXYZ'); state = proof['tile_states'][str(run)]
        for i, (axis,scale,origin,size) in enumerate([((1,0,0),state['scale_s'],state['uls'],state['width']),
                                                     ((0,1,0),state['scale_t'],state['ult'],state['height'])]):
            transform = nodes.new('ShaderNodeVectorTransform'); transform.vector_type='VECTOR'
            transform.convert_from='CAMERA'; transform.convert_to='OBJECT'; transform.inputs['Vector'].default_value=axis
            norm = nodes.new('ShaderNodeVectorMath'); norm.operation='NORMALIZE'; links.new(transform.outputs['Vector'],norm.inputs[0])
            dot = nodes.new('ShaderNodeVectorMath'); dot.operation='DOT_PRODUCT'
            links.new(norm.outputs['Vector'],dot.inputs[0]); links.new(conv.outputs['Vector'],dot.inputs[1])
            uv = nodes.new('ShaderNodeMath'); uv.operation='MULTIPLY_ADD'
            uv.inputs[1].default_value=512*scale/size; uv.inputs[2].default_value=512*scale/size-origin/(4*size)
            links.new(dot.outputs['Value'],uv.inputs[0]); links.new(uv.outputs[0],coordinates.inputs[i])
        images = [n for n in nodes if n.type=='TEX_IMAGE']; require(len(images)==1,'affected material image count changed')
        target = images[0].inputs['Vector']; removed = [[l.from_node.name,l.from_socket.identifier,l.to_node.name,l.to_socket.identifier] for l in target.links]
        for link in list(target.links): links.remove(link)
        links.new(coordinates.outputs['Vector'],target)
        current = material_signature(mat); oldnames={n['name'] for n in original['nodes']}
        require([n for n in current['nodes'] if n['name'] in oldnames] == original['nodes'], 'existing material node changed')
        require([l for l in current['links'] if l[0] in oldnames and l[2] in oldnames] ==
                [l for l in original['links'] if l not in removed], 'unrelated material link changed')
        records.append({'material':material_index,'source_run':run,'original':original,
                        'removed_vector_links':removed,'result':current})
    return records


def coordinate_proof(obj, proof, faces, framing):
    import bpy
    from mathutils import Matrix, Vector
    results=[]; C=c_matrix()
    for view in VIEWS:
        set_view(framing,view); cam=bpy.context.scene.camera
        shader_axes=[(obj.matrix_world.inverted().to_3x3() @ cam.matrix_world.to_3x3() @ Vector(a)).normalized()
                     for a in ((1,0,0),(0,1,0))]
        native_axes={k:[((cam.matrix_world.inverted() @ C @ Matrix.Translation(Vector(t))).to_3x3().inverted() @ Vector(a)).normalized()
                        for a in ((1,0,0),(0,1,0))] for k,t in proof['joint_world_translations'].items()}
        max_delta=0; uvrows=[]
        for fi,row in sorted(faces.items()):
            state=proof['tile_states'][str(row['material_run'])]
            for corner in row['corners']:
                raw=Vector([v/127 for v in corner['normal_bytes']]); joint=str(corner['matrix_index'])
                d=[a.dot(raw) for a in native_axes[joint]]
                sd=[a.dot(C.to_3x3() @ raw) for a in shader_axes]
                native=[((d[0]+1)*512*state['scale_s']-state['uls']/4)/state['width'],
                        ((d[1]+1)*512*state['scale_t']-state['ult']/4)/state['height']]
                shader=[sd[0]*512*state['scale_s']/state['width']+512*state['scale_s']/state['width']-state['uls']/(4*state['width']),
                        sd[1]*512*state['scale_t']/state['height']+512*state['scale_t']/state['height']-state['ult']/(4*state['height'])]
                max_delta=max(max_delta,max(abs(a-b) for a,b in zip(native,shader)));uvrows.append(native)
        require(len(uvrows)==309 and max_delta<2e-6,'native vertex/shader coordinate disagreement')
        results.append({'view':view,'corners':len(uvrows),'max_uv_difference':max_delta,
                        'native_uv_sha256':stable(uvrows),'camera_matrix_world':[list(r) for r in cam.matrix_world],
                        'scope':'Analytic per-vertex source-normal coordinates versus exact node formula; no raster parity claim.'})
    set_view(framing,'three-quarter')
    return results


def verify_packed_images(obj, doc, resources):
    import bpy
    images=[im for im in bpy.data.images if im.type=='IMAGE' and im.source=='FILE']
    require(len(images)==17 and all(im.packed_file for im in images),'source image packing changed')
    expected=sorted(digest(resources[r['uri']]) for r in doc['images'])
    actual=sorted(digest(bytes(im.packed_file.data)) for im in images)
    require(actual==expected,'packed image bytes differ from source')
    return actual


def build(source, audit_path, output):
    import bpy
    proof,doc,resources,faces=load_inputs(source,audit_path)
    require(not any((output/name).exists() for name in ('artifact.json', 'character66-neutral-texgen.blend',
                                                       'three-quarter.png', 'rear.png')),
            'inspection output already exists')
    obj,framing=setup(source,doc); attribute=verify_attribute(obj,proof,faces)
    baseline_geometry=geometry_signature(obj)
    baseline_materials={str(i):material_signature(m) for i,m in enumerate(obj.data.materials)}
    records=add_shader(obj,proof)
    require(geometry_signature(obj)==baseline_geometry,'shader changed source mesh/UVMap/rig')
    for i,m in enumerate(obj.data.materials):
        if i not in AFFECTED:require(material_signature(m)==baseline_materials[str(i)],'unrelated material changed')
    views=coordinate_proof(obj,proof,faces,framing)
    verify_no_execution(); bpy.ops.file.pack_all(); packed=verify_packed_images(obj,doc,resources)
    obj['CBFD_texgen_scope']=SCOPE
    bpy.context.scene['CBFD_texgen_inspection_state']=json.dumps(STATE,sort_keys=True)
    bpy.context.scene['CBFD_texgen_source_proof_sha256']=digest(audit_path.read_bytes())
    output.mkdir(parents=True, exist_ok=True)
    blend=output/'character66-neutral-texgen.blend'
    bpy.ops.wm.save_as_mainfile(filepath=str(blend))
    renders={}
    for view in VIEWS:
        set_view(framing,view); path=output/f'{view}.png'; bpy.context.scene.render.filepath=str(path)
        bpy.ops.render.render(write_still=True); renders[path.name]=digest(path.read_bytes())
    result={'schema_version':1,'scope':SCOPE,'blender_version':bpy.app.version_string,
            'source_gltf_sha256':digest(source.read_bytes()),'source_proof_sha256':digest(audit_path.read_bytes()),
            'blend_file':blend.name,'blend_sha256':digest(blend.read_bytes()),'attribute':attribute,
            'geometry_signature':baseline_geometry,'materials':{str(i):material_signature(m) for i,m in enumerate(obj.data.materials)},
            'changed_materials':records,'packed_image_sha256':packed,'framing':framing,'views':views,'renders':renders,
            'inspection_state':STATE,'actions':0,'drivers':0,'text_blocks':0,'task_handlers':0}
    (output/'artifact.json').write_text(json.dumps(result,indent=2,allow_nan=False)+'\n')
    return {'output':str(output),'blend_sha256':result['blend_sha256'],'views':views}


def verify(source, audit_path, output):
    import bpy
    proof,doc,resources,faces=load_inputs(source,audit_path)
    saved=json.loads((output/'artifact.json').read_text());blend=output/saved['blend_file']
    require(digest(blend.read_bytes())==saved['blend_sha256'],'saved blend fingerprint changed')
    require(saved['source_gltf_sha256']==digest(source.read_bytes()) and
            saved['source_proof_sha256']==digest(audit_path.read_bytes()),'artifact source proof changed')
    require(saved['scope']==SCOPE and saved['inspection_state']==STATE,'artifact scope changed')
    require('--disable-autoexec' in sys.argv,'verify requires --disable-autoexec')
    # Rebuild expectations from authenticated source; artifact.json is an audit,
    # not an authority that could bless a coherently modified Blend.
    expected_obj, expected_framing = setup(source, doc)
    expected_attribute = verify_attribute(expected_obj, proof, faces)
    expected_geometry = geometry_signature(expected_obj)
    expected_changes = add_shader(expected_obj, proof)
    expected_materials = {str(i): material_signature(m) for i,m in enumerate(expected_obj.data.materials)}
    expected_views = coordinate_proof(expected_obj, proof, faces, expected_framing)
    expected_camera = camera_framing(bpy.context.scene)
    require(saved['attribute'] == expected_attribute and saved['geometry_signature'] == expected_geometry
            and saved['materials'] == expected_materials and saved['changed_materials'] == expected_changes
            and saved['framing'] == expected_framing and saved['views'] == expected_views,
            'artifact audit differs from freshly derived source expectations')
    bpy.ops.wm.open_mainfile(filepath=str(blend),use_scripts=False)
    bpy.context.view_layer.update(); obj=mesh_object();verify_no_execution()
    require(camera_framing(bpy.context.scene) == expected_camera, 'saved camera framing differs from source reconstruction')
    require(obj.get('CBFD_texgen_scope')==SCOPE,'saved scope metadata changed')
    require(bpy.context.scene.get('CBFD_texgen_source_proof_sha256')==digest(audit_path.read_bytes()),'embedded source proof changed')
    require(json.loads(bpy.context.scene['CBFD_texgen_inspection_state'])==STATE,'saved state changed')
    require(verify_attribute(obj,proof,faces)==saved['attribute'],'saved raw attribute changed')
    require(geometry_signature(obj)==saved['geometry_signature'],'saved geometry/UVMap/pose changed')
    require({str(i):material_signature(m) for i,m in enumerate(obj.data.materials)}==saved['materials'],
            'saved shader node topology/defaults changed')
    require(verify_packed_images(obj,doc,resources)==saved['packed_image_sha256'],'saved textures changed')
    views=coordinate_proof(obj,proof,faces,saved['framing'])
    require(views==saved['views'],'saved two-view coordinate proof changed')
    for name,expected in saved['renders'].items():require(digest((output/name).read_bytes())==expected,'preview fingerprint changed')
    return {'verified':True,'output':str(output),'blend_sha256':saved['blend_sha256'],
            'corners_per_view':309,'packed_images':17,'verify_writes':False}


def main(argv=None):
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source',type=Path,required=True);parser.add_argument('--audit',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True);parser.add_argument('--verify',action='store_true')
    args=parser.parse_args(argv if argv is not None else sys.argv[sys.argv.index('--')+1:])
    result=(verify if args.verify else build)(args.source.resolve(),args.audit.resolve(),args.output.resolve())
    print(json.dumps(result,sort_keys=True));return 0


if __name__=='__main__':
    raise SystemExit(main())
