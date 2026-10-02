#!/usr/bin/env python3
"""Create/verify a separate character66 animated inspection in Blender.

All original Actions remain unchanged. No drivers, handlers or embedded scripts
are used: a point-domain Geometry Nodes attribute follows three parented bones.
"""
from __future__ import annotations
import argparse
import json
import math
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import model_character_texgen_blender as neutral
import model_character_animated_texgen as host

require, sha, stable = neutral.require, neutral.digest, neutral.stable
JOINT_ATTRIBUTE = '_CBFD_NATIVE_JOINT'
ANIMATED_ATTRIBUTE = '_CBFD_ANIMATED_TEXGEN_NORMAL'
JOINTS = (6, 13, 19)
HELPERS = tuple(f'CBFD_joint_{j:02d}_deformation' for j in JOINTS)
GROUP = 'CBFD source raw normals through one-hot joint rotation'


def load_inputs(source, audit_path):
    output = audit_path.parent
    audit = json.loads(audit_path.read_text())
    require(audit['kind'] == 'character66-animated-texgen' and audit['scope'] == host.SCOPE,
            'animated scope changed')
    proof, document, resources, faces = neutral.load_inputs(
        source.parent/'character66-texgen.gltf', output/'source-proof.json')
    for name, digest in audit['resources'].items():
        path = (output/name).resolve()
        require(path.is_relative_to(output.resolve()), 'animated resource escapes output')
        require(sha(path.read_bytes()) == digest, f'animated resource changed: {name}')
    require(audit['neutral_source_proof_sha256'] == sha((output/'source-proof.json').read_bytes())
            and audit['gltf_sha256'] == sha(source.read_bytes()), 'animated source identity changed')
    original = json.loads((output/'source/geometry/0066-00.gltf').read_text())
    binary = (output/'source/geometry/0066-00.bin').read_bytes()
    expected = dict(document); expected['animations'] = original['animations']
    animated = json.loads(source.read_text())
    require(animated == expected, 'animated glTF differs from original clips plus neutral source')
    domain = host.animation_contract(original, binary, proof)
    require(domain == audit['animation_domain'], 'animated source domain changed')
    return audit, proof, animated, resources, faces, original, binary


def select_neutral(armature):
    from mathutils import Matrix
    import bpy
    armature.animation_data.action = None
    for track in armature.animation_data.nla_tracks:
        track.mute = True
    for bone in armature.pose.bones:
        bone.matrix_basis = Matrix.Identity(4)
    bpy.context.view_layer.update()


def framing_neutral(obj):
    from mathutils import Vector
    import bpy
    scene = bpy.context.scene
    corners = [obj.matrix_world@v.co for v in obj.data.vertices]
    low = Vector([min(v[i] for v in corners) for i in range(3)])
    high = Vector([max(v[i] for v in corners) for i in range(3)])
    center = (low+high)*.5; extent = high-low; diagonal = max(extent.length, 1)
    scene.camera.data.ortho_scale = max(*extent, 1)*1.45
    scene.camera.data.clip_start = max(diagonal*.0001, .001)
    scene.camera.data.clip_end = diagonal*4
    for name, direction, strength in [('Key', (-1, -1.5, 2), 28), ('Fill', (1.5, .5, .75), 16)]:
        light = scene.objects[name]; light.data.energy = diagonal*diagonal*strength
        light.data.size = diagonal*1.5
        light.location = center+Vector(direction).normalized()*diagonal*1.5
        light.rotation_euler = (center-light.location).to_track_quat('-Z', 'Y').to_euler()
    framing = {'center': list(center), 'diagonal': diagonal}
    neutral.set_view(framing, 'three-quarter')
    return framing


def add_geometry_nodes(obj, armature, proof):
    import bpy
    from mathutils import Matrix
    attribute = obj.data.attributes.new(JOINT_ATTRIBUTE, 'INT', 'POINT')
    for vertex in obj.data.vertices:
        groups = [g for g in vertex.groups if g.weight > 0]
        require(len(groups) == 1 and groups[0].weight == 1, 'import changed one-hot weights')
        name = obj.vertex_groups[groups[0].group].name
        require(name.startswith('joint_'), 'import joint name changed')
        attribute.data[vertex.index].value = int(name.split('_')[-1])
    for row in proof['faces']:
        for index, corner in zip(obj.data.polygons[row['face']].vertices, row['corners']):
            require(attribute.data[index].value == corner['matrix_index'], 'imported corner joint changed')
    helpers = {}
    for joint, name in zip(JOINTS, HELPERS):
        helper = bpy.data.objects.new(name, None); bpy.context.scene.collection.objects.link(helper)
        helper.parent = armature; helper.parent_type = 'BONE'; helper.parent_bone = f'joint_{joint:02d}'
        helper.matrix_parent_inverse = (armature.matrix_world@armature.data.bones[helper.parent_bone].matrix_local).inverted()
        helper.matrix_basis = Matrix.Identity(4); helper.hide_render = True
        helpers[joint] = helper
    bpy.context.view_layer.update()
    group = bpy.data.node_groups.new(GROUP, 'GeometryNodeTree')
    group.interface.new_socket(name='Geometry', in_out='INPUT', socket_type='NodeSocketGeometry')
    group.interface.new_socket(name='Geometry', in_out='OUTPUT', socket_type='NodeSocketGeometry')
    nodes, links = group.nodes, group.links
    source, target = nodes.new('NodeGroupInput'), nodes.new('NodeGroupOutput')
    raw = nodes.new('GeometryNodeInputNamedAttribute'); raw.data_type = 'FLOAT_VECTOR'
    raw.inputs['Name'].default_value = neutral.ATTRIBUTE
    separate = nodes.new('ShaderNodeSeparateXYZ'); links.new(raw.outputs['Attribute'], separate.inputs[0])
    negate = nodes.new('ShaderNodeMath'); negate.operation = 'MULTIPLY'; negate.inputs[1].default_value = -1
    links.new(separate.outputs['Z'], negate.inputs[0])
    convert = nodes.new('ShaderNodeCombineXYZ')
    links.new(separate.outputs['X'], convert.inputs['X']); links.new(negate.outputs[0], convert.inputs['Y'])
    links.new(separate.outputs['Y'], convert.inputs['Z'])
    ids = nodes.new('GeometryNodeInputNamedAttribute'); ids.data_type = 'INT'; ids.inputs['Name'].default_value = attribute.name
    vectors = []
    for joint, helper in helpers.items():
        info = nodes.new('GeometryNodeObjectInfo'); info.transform_space = 'RELATIVE'; info.inputs['Object'].default_value = helper
        rotate = nodes.new('FunctionNodeTransformDirection')
        links.new(info.outputs['Transform'], rotate.inputs['Transform']); links.new(convert.outputs['Vector'], rotate.inputs['Direction'])
        compare = nodes.new('ShaderNodeMath'); compare.operation = 'COMPARE'
        compare.inputs[1].default_value = joint; compare.inputs[2].default_value = .1
        links.new(ids.outputs['Attribute'], compare.inputs[0])
        scale = nodes.new('ShaderNodeVectorMath'); scale.operation = 'SCALE'
        links.new(rotate.outputs['Direction'], scale.inputs[0]); links.new(compare.outputs[0], scale.inputs['Scale'])
        vectors.append(scale.outputs[0])
    combined = vectors[0]
    for vector in vectors[1:]:
        add = nodes.new('ShaderNodeVectorMath'); add.operation = 'ADD'
        links.new(combined, add.inputs[0]); links.new(vector, add.inputs[1]); combined = add.outputs[0]
    store = nodes.new('GeometryNodeStoreNamedAttribute'); store.data_type = 'FLOAT_VECTOR'; store.domain = 'POINT'
    store.inputs['Name'].default_value = ANIMATED_ATTRIBUTE
    links.new(source.outputs['Geometry'], store.inputs['Geometry']); links.new(combined, store.inputs['Value'])
    links.new(store.outputs['Geometry'], target.inputs['Geometry'])
    modifier = obj.modifiers.new('CBFD animated raw normals', 'NODES'); modifier.node_group = group


def add_shaders(obj, proof):
    neutral.add_shader(obj, proof)
    for index in neutral.AFFECTED:
        material = obj.data.materials[index]; nodes, links = material.node_tree.nodes, material.node_tree.links
        previous = next(n for n in nodes if n.label == 'Native XYZ to Blender X,-Z,Y')
        attribute = nodes.new('ShaderNodeAttribute'); attribute.attribute_name = ANIMATED_ATTRIBUTE
        attribute.label = 'Raw signed normal rotated by its one-hot joint; do not normalize'
        for link in list(previous.outputs[0].links):
            target = link.to_socket; links.remove(link); links.new(attribute.outputs['Vector'], target)


def serialized(value):
    import bpy
    if isinstance(value, bpy.types.ID):
        return {'id_type': value.bl_rna.identifier, 'name': value.name}
    if isinstance(value, (str, int, float, bool)) or value is None:
        return value
    return [serialized(v) for v in value]


def graph_signature(group):
    nodes = []
    for node in group.nodes:
        row = {'name': node.name, 'type': node.bl_idname, 'mute': node.mute,
               'inputs': [(s.identifier, serialized(s.default_value)) for s in node.inputs if hasattr(s, 'default_value')]}
        for key in ('operation', 'data_type', 'domain', 'transform_space', 'input_type'):
            if hasattr(node, key): row[key] = getattr(node, key)
        nodes.append(row)
    return {'nodes': nodes, 'links': sorted((l.from_node.name, l.from_socket.identifier,
                                           l.to_node.name, l.to_socket.identifier) for l in group.links),
            'interface': [(s.name, s.in_out, s.socket_type) for s in group.interface.items_tree if s.item_type == 'SOCKET']}


def action_signature():
    import bpy
    result = {}
    for action in bpy.data.actions:
        rows = []
        for layer in action.layers:
            for strip in layer.strips:
                for bag in strip.channelbags:
                    for curve in bag.fcurves:
                        require(not list(curve.modifiers), 'unexpected animation curve modifier')
                        rows.append({'path': curve.data_path, 'index': curve.array_index, 'mute': curve.mute,
                                     'extrapolation': curve.extrapolation,
                                     'keys': [{key: serialized(getattr(k, key)) for key in
                                              ('co', 'handle_left', 'handle_right', 'handle_left_type', 'handle_right_type',
                                               'interpolation', 'easing', 'amplitude', 'back', 'period')}
                                              for k in curve.keyframe_points]})
        result[action.name] = rows
    return result


def no_execution(domain):
    import bpy
    require(not list(bpy.data.texts) and not list(bpy.data.libraries), 'animated file has text or external libraries')
    require(sorted(a.name for a in bpy.data.actions) == sorted(c['name'] for c in domain['clips']),
            'original action set changed')
    blocks = [*bpy.data.objects, *bpy.data.materials, *bpy.data.node_groups, *bpy.data.scenes,
              *bpy.data.worlds, *bpy.data.meshes, *bpy.data.armatures, *bpy.data.images, *bpy.data.cameras, *bpy.data.lights, *bpy.data.shape_keys]
    blocks += [m.node_tree for m in [*bpy.data.materials, *bpy.data.worlds, *bpy.data.scenes] if getattr(m, 'node_tree', None)]
    require(all(not getattr(b, 'animation_data', None) or not b.animation_data.drivers for b in blocks),
            'animated file has drivers')


def scene_signature(obj, armature):
    import bpy
    helpers = {}
    for name in HELPERS:
        helper = bpy.data.objects[name]
        require(helper.type == 'EMPTY' and not helper.constraints, 'helper object or constraints changed')
        helpers[name] = {'parent': helper.parent.name, 'parent_type': helper.parent_type, 'parent_bone': helper.parent_bone,
                         'parent_inverse': serialized(helper.matrix_parent_inverse), 'basis': serialized(helper.matrix_basis),
                         'hide_render': helper.hide_render, 'hide_viewport': helper.hide_viewport}
    require({o.name for o in bpy.context.scene.objects if o.type == 'EMPTY'} == set(HELPERS), 'extra transform helper')
    require(armature.animation_data.action is None, 'saved pose is not neutral')
    require(all(not b.constraints for b in armature.pose.bones)
            and not obj.constraints and not armature.constraints, 'unexpected rig constraints')
    return json.loads(json.dumps({'geometry': neutral.geometry_signature(obj), 'actions': action_signature(),
        'materials': {str(i): neutral.material_signature(m) for i, m in enumerate(obj.data.materials)},
        'material_node_states': {str(i): [(n.name, n.mute, getattr(n, 'attribute_type', None))
                                        for n in m.node_tree.nodes] for i, m in enumerate(obj.data.materials)},
        'image_states': {im.name: (im.source, im.type, im.alpha_mode, im.colorspace_settings.name)
                         for im in bpy.data.images if im.type == 'IMAGE' and im.source == 'FILE'},
        'rest_bones': {b.name: {'matrix': serialized(b.matrix_local), 'parent': b.parent.name if b.parent else None,
                               'use_deform': b.use_deform, 'inherit_scale': b.inherit_scale}
                       for b in armature.data.bones},
        'helpers': helpers, 'geometry_nodes': graph_signature(bpy.data.node_groups[GROUP]),
        'modifiers': [(m.name, m.type, m.show_viewport, m.show_render,
                       m.node_group.name if m.type == 'NODES' else m.object.name if m.type == 'ARMATURE' else None)
                      for m in obj.modifiers],
        'nla': [(t.name, t.mute, [(s.name, s.action.name, s.frame_start, s.frame_end, s.action_frame_start,
                                 s.action_frame_end, s.scale, s.repeat, s.influence, s.blend_type, s.extrapolation)
                                for s in t.strips]) for t in armature.animation_data.nla_tracks]}))


def prepare(source, inputs):
    import bpy
    audit, proof, document, resources, faces, original, binary = inputs
    obj, _ = neutral.setup(source, document)
    armature = next(o for o in bpy.context.scene.objects if o.type == 'ARMATURE')
    select_neutral(armature); framing = framing_neutral(obj)
    attribute = neutral.verify_attribute(obj, proof, faces)
    before_actions = action_signature()
    add_geometry_nodes(obj, armature, proof); add_shaders(obj, proof)
    require(action_signature() == before_actions, 'original Actions changed')
    no_execution(audit['animation_domain'])
    return obj, armature, framing, attribute


def coordinate_proof(obj, armature, framing, inputs):
    """Compare independent inverse-axis rig oracle; glTF SLERP is a separate result."""
    import bpy
    from mathutils import Vector
    audit, proof, _, _, faces, original, binary = inputs
    scene = bpy.context.scene; actions = {a.name: a for a in bpy.data.actions}
    samples = []; maximum = 0; source_key = 0; source_between = 0; source_position = {'key': 0, 'between': 0}
    for clip in audit['animation_domain']['clips']:
        select_neutral(armature); armature.animation_data.action = actions[clip['name']]
        armature.animation_data.action_slot = actions[clip['name']].slots[0]
        for seconds in clip['sample_times']:
            frame = seconds*scene.render.fps*scene.render.fps_base
            scene.frame_set(int(frame), subframe=frame-int(frame)); bpy.context.view_layer.update()
            source_world = host.world_matrices(original, binary, clip['index'], seconds)
            key = seconds in clip['key_times']
            for view in neutral.VIEWS:
                neutral.set_view(framing, view); cam = scene.camera
                deps = bpy.context.evaluated_depsgraph_get(); evaluated = obj.evaluated_get(deps); mesh = evaluated.to_mesh()
                try:
                    attribute = mesh.attributes[ANIMATED_ATTRIBUTE]; raw_attribute = mesh.attributes[neutral.ATTRIBUTE]
                    joint = {j: armature.matrix_world@armature.pose.bones[f'joint_{j:02d}'].matrix
                             @armature.data.bones[f'joint_{j:02d}'].matrix_local.inverted()@neutral.c_matrix() for j in JOINTS}
                    rig_axes = {j: [((cam.matrix_world.inverted()@m).to_3x3().inverted()@Vector(a)).normalized()
                                    for a in ((1, 0, 0), (0, 1, 0))] for j, m in joint.items()}
                    shader_axes = [(obj.matrix_world.inverted().to_3x3()@cam.matrix_world.to_3x3()@Vector(a)).normalized()
                                   for a in ((1, 0, 0), (0, 1, 0))]
                    camera = [list(r)[:3] for r in cam.matrix_world][:3]
                    view_conversion = host.multiply(host.inverse(camera), [[1, 0, 0], [0, 0, -1], [0, 1, 0]])
                    source_axes = {j: [host.normalize(host.transform(host.inverse(host.multiply(view_conversion,
                                     [r[:3] for r in source_world[j][:3]])), a)) for a in ((1, 0, 0), (0, 1, 0))] for j in JOINTS}
                    worst, source_worst, position_worst = 0, 0, 0
                    for fi, row in faces.items():
                        tile = proof['tile_states'][str(row['material_run'])]
                        def uv(d):
                            return [((d[0]+1)*512*tile['scale_s']-tile['uls']/4)/tile['width'],
                                    ((d[1]+1)*512*tile['scale_t']-tile['ult']/4)/tile['height']]
                        for index, corner in zip(mesh.polygons[fi].vertices, row['corners']):
                            raw = Vector([v/127 for v in corner['normal_bytes']]); j = corner['matrix_index']
                            require(max(abs(a-b) for a, b in zip(raw, raw_attribute.data[index].vector)) < 1e-7,
                                    'deformation changed raw normal attribute')
                            generated = uv([a.dot(attribute.data[index].vector) for a in shader_axes])
                            rig = uv([a.dot(raw) for a in rig_axes[j]])
                            source_uv = uv([host.dot(a, raw) for a in source_axes[j]])
                            worst = max(worst, max(abs(a-b) for a, b in zip(generated, rig)))
                            source_worst = max(source_worst, max(abs(a-b) for a, b in zip(generated, source_uv)))
                            expected_position = Vector(host.transform(source_world[j], corner['source_position']+[1])[:3])
                            position_worst = max(position_worst, ((evaluated.matrix_world@mesh.vertices[index].co)
                                                                 -(neutral.c_matrix()@expected_position)).length)
                    require(worst < 2e-6, 'animated generated coordinates disagree with evaluated rig')
                    maximum = max(maximum, worst)
                    if key:
                        source_key = max(source_key, source_worst)
                        require(source_worst < 2e-6 and position_worst < .0002, 'source key pose differs from original glTF')
                    else:
                        source_between = max(source_between, source_worst)
                        require(source_worst < .0003 and position_worst < .08, 'imported interpolation exceeds measured scope')
                    position_kind = 'key' if key else 'between'
                    source_position[position_kind] = max(source_position[position_kind], position_worst)
                    samples.append({'clip': clip['index'], 'seconds': seconds, 'source_key': key, 'view': view,
                                    'corners': 309, 'evaluated_rig_uv_error': worst, 'original_gltf_uv_error': source_worst,
                                    'original_gltf_position_error': position_worst})
                finally:
                    evaluated.to_mesh_clear()
    select_neutral(armature); scene.frame_set(0); neutral.set_view(framing, 'three-quarter')
    require(len(samples) == 294, 'animation sample domain changed')
    return {'sample_views': len(samples), 'evaluated_rig_max_uv_error': maximum,
            'original_gltf_key_max_uv_error': source_key, 'original_gltf_between_max_uv_error': source_between,
            'original_gltf_position_error': source_position, 'samples': samples}


def build(source, audit_path, output):
    import bpy
    require(not any((output/name).exists() or (output/name).is_symlink() for name in
                    ('artifact.json', host.BLEND, 'three-quarter.png', 'rear.png')), 'animated output already exists')
    inputs = load_inputs(source, audit_path); obj, armature, framing, attribute = prepare(source, inputs)
    coordinates = coordinate_proof(obj, armature, framing, inputs)
    signature = scene_signature(obj, armature); bpy.ops.file.pack_all()
    packed = neutral.verify_packed_images(obj, inputs[2], inputs[3]); no_execution(inputs[0]['animation_domain'])
    bpy.context.scene['CBFD_animated_texgen_scope'] = host.SCOPE
    bpy.context.scene['CBFD_animated_source_proof_sha256'] = sha(audit_path.read_bytes())
    obj['CBFD_animated_texgen_scope'] = host.SCOPE
    blend = output/host.BLEND; bpy.ops.wm.save_as_mainfile(filepath=str(blend)); renders = {}
    for view in neutral.VIEWS:
        neutral.set_view(framing, view); path = output/f'{view}.png'; bpy.context.scene.render.filepath = str(path)
        bpy.ops.render.render(write_still=True); renders[path.name] = sha(path.read_bytes())
    result = {'schema_version': 1, 'scope': host.SCOPE, 'blender_version': bpy.app.version_string,
              'animation_proof_sha256': sha(audit_path.read_bytes()), 'source_gltf_sha256': sha(source.read_bytes()),
              'blend_file': host.BLEND, 'blend_sha256': sha(blend.read_bytes()), 'attribute': attribute,
              'scene_signature': signature, 'packed_image_sha256': packed, 'framing': framing,
              'coordinate_proof': coordinates, 'renders': renders, 'actions': 3, 'drivers': 0, 'text_blocks': 0}
    (output/'artifact.json').write_text(json.dumps(result, indent=2, allow_nan=False)+'\n')
    return {'output': str(output), 'blend_sha256': result['blend_sha256'], 'sample_views': 294}


def verify(source, audit_path, output):
    import bpy
    require('--disable-autoexec' in sys.argv, 'verify requires auto-execution disabled')
    inputs = load_inputs(source, audit_path); saved = json.loads((output/'artifact.json').read_text())
    require(saved['blend_file'] == host.BLEND and set(saved['renders']) == {'three-quarter.png', 'rear.png'},
            'animated output names changed')
    blend = output/host.BLEND
    require(saved['scope'] == host.SCOPE and saved['source_gltf_sha256'] == sha(source.read_bytes())
            and saved['animation_proof_sha256'] == sha(audit_path.read_bytes())
            and saved['blend_sha256'] == sha(blend.read_bytes()), 'animated artifact identity changed')
    obj, armature, framing, attribute = prepare(source, inputs)
    expected_signature = scene_signature(obj, armature)
    expected_camera = neutral.camera_framing(bpy.context.scene)
    require(saved['scene_signature'] == expected_signature and saved['attribute'] == attribute
            and saved['framing'] == framing, 'animated audit differs from freshly rebuilt source scene')
    bpy.ops.wm.open_mainfile(filepath=str(blend), use_scripts=False); bpy.context.view_layer.update()
    require(neutral.camera_framing(bpy.context.scene) == expected_camera, 'saved animated camera framing differs from source reconstruction')
    obj = neutral.mesh_object(); armature = next(o for o in bpy.context.scene.objects if o.type == 'ARMATURE')
    no_execution(inputs[0]['animation_domain'])
    require(bpy.context.scene.get('CBFD_animated_texgen_scope') == host.SCOPE
            and obj.get('CBFD_animated_texgen_scope') == host.SCOPE
            and bpy.context.scene.get('CBFD_animated_source_proof_sha256') == sha(audit_path.read_bytes()),
            'saved animated scope/source metadata changed')
    require(scene_signature(obj, armature) == expected_signature, 'saved animated scene differs from source reconstruction')
    require(neutral.verify_attribute(obj, inputs[1], inputs[4]) == attribute, 'saved raw normal data changed')
    require(neutral.verify_packed_images(obj, inputs[2], inputs[3]) == saved['packed_image_sha256'], 'saved textures changed')
    coordinates = coordinate_proof(obj, armature, framing, inputs)
    require(coordinates == saved['coordinate_proof'], 'saved animated coordinate proof changed')
    for name, digest in saved['renders'].items():
        require(sha((output/name).read_bytes()) == digest, 'saved animated preview changed')
    return {'verified': True, 'output': str(output), 'sample_views': 294, 'verify_writes': False}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, required=True); parser.add_argument('--audit', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True); parser.add_argument('--verify', action='store_true')
    args = parser.parse_args(argv if argv is not None else sys.argv[sys.argv.index('--')+1:])
    print(json.dumps((verify if args.verify else build)(args.source.resolve(), args.audit.resolve(), args.output.resolve()), sort_keys=True))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
