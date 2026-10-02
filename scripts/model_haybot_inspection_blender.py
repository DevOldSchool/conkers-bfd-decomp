"""Create and freshly verify the selected Haybot material without changing its rig."""
from pathlib import Path
import argparse
import json
import sys

import bpy

sys.path.insert(0, str(Path(__file__).resolve().parent))
import model_haybot_inspection as host
import model_character_texgen_blender as common
import model_character_animated_texgen_blender as animated
import model_embedded_type13_inspection_blender as signatures

require, sha = host.require, host.sha
FACTORY_HANDLERS = {name: frozenset((f.__module__, f.__qualname__) for f in getattr(bpy.app.handlers, name))
                    for name in dir(bpy.app.handlers) if isinstance(getattr(bpy.app.handlers, name), list)}


def mesh_object():
    meshes = [o for o in bpy.context.scene.objects if o.type == 'MESH']
    source = [o for o in meshes if any(m.type == 'ARMATURE' for m in o.modifiers)]
    shapes = {b.custom_shape for a in bpy.context.scene.objects if a.type == 'ARMATURE'
              for b in a.pose.bones if b.custom_shape is not None}
    require(len(source) == 1 and all(o in source or o in shapes for o in meshes), 'Haybot source mesh set changed')
    return source[0]


def setup(source):
    bpy.ops.wm.read_factory_settings(use_empty=True); bpy.ops.import_scene.gltf(filepath=str(source))
    obj = mesh_object(); scene = bpy.context.scene
    camera_data = bpy.data.cameras.new('PreviewCamera'); camera_data.type = 'ORTHO'
    camera = bpy.data.objects.new('PreviewCamera', camera_data); scene.collection.objects.link(camera); scene.camera = camera
    available = {i.identifier for i in scene.render.bl_rna.properties['engine'].enum_items}
    scene.render.engine = next(v for v in ('BLENDER_EEVEE_NEXT', 'BLENDER_EEVEE') if v in available)
    world = bpy.data.worlds.new('PreviewWorld'); world.use_nodes = True; scene.world = world
    background = world.node_tree.nodes.get('Background'); background.inputs['Color'].default_value = (.025, .03, .04, 1)
    background.inputs['Strength'].default_value = 1.5
    for name in ('Key', 'Fill'):
        data = bpy.data.lights.new(name, type='AREA'); data.shape = 'DISK'
        light = bpy.data.objects.new(name, data); scene.collection.objects.link(light)
    scene.render.resolution_x = scene.render.resolution_y = 512; scene.render.resolution_percentage = 100
    scene.render.image_settings.file_format = 'PNG'; scene.render.image_settings.color_mode = 'RGBA'
    scene.render.film_transparent = False; scene.view_settings.look = 'AgX - Medium High Contrast'
    return obj


def inputs(output):
    proof = json.loads((output/'source-proof.json').read_text())
    require(proof['kind'] == host.KIND and proof['inspection_state'] == host.STATE and proof['scope'] == host.SCOPE
            and proof['phase'] == 0 and proof['descriptor'] == 15 and proof['entry'] == 75,
            'Haybot inspection input state changed')
    for name, digest in proof['files'].items():
        path = (output/name).resolve()
        require(path.is_relative_to(output.resolve()) and sha(path.read_bytes()) == digest,
                'Haybot prepared input changed: '+name)
    source = output/'source/geometry/0075-00.gltf'
    require(sha(source.read_bytes()) == host.SOURCE_GLTF_SHA256, 'Haybot original glTF changed')
    document = json.loads(source.read_text())
    require(proof['actions'] == [a['name'] for a in document['animations']]
            and proof['affected_faces'] == list(range(367, 391)) and proof['affected_material'] == 16,
            'Haybot action or material span changed')
    return proof, document, source


def image_signature():
    result = {}
    for image in bpy.data.images:
        if image.type != 'IMAGE':
            continue
        require(image.source == 'FILE' and image.packed_file, 'Haybot has an unpacked or non-file image')
        result[image.name] = {'bytes': sha(bytes(image.packed_file.data)),
                              'color_space': image.colorspace_settings.name, 'alpha_mode': image.alpha_mode,
                              'size': list(image.size)}
    return result


def no_execution(proof):
    require(not bpy.data.texts and not bpy.data.libraries and not bpy.data.node_groups and not bpy.data.shape_keys,
            'Haybot has unexpected text, external library, node group or shape key')
    require(sorted(a.name for a in bpy.data.actions) == sorted(proof['actions']), 'Haybot original Actions changed')
    blocks = []
    for key in dir(bpy.data):
        value = getattr(bpy.data, key)
        if isinstance(value, bpy.types.bpy_prop_collection):
            blocks.extend(value)
    blocks += [x.node_tree for x in [*bpy.data.materials, *bpy.data.worlds, *bpy.data.scenes] if getattr(x, 'node_tree', None)]
    require(all(not getattr(b, 'animation_data', None) or not b.animation_data.drivers for b in blocks),
            'Haybot has animation drivers')
    require(all(not o.constraints for o in bpy.data.objects)
            and all(not b.constraints for a in bpy.data.objects if a.type == 'ARMATURE' for b in a.pose.bones),
            'Haybot has unexpected constraints')
    require({name: frozenset((f.__module__, f.__qualname__) for f in getattr(bpy.app.handlers, name))
             for name in FACTORY_HANDLERS} == FACTORY_HANDLERS, 'Haybot registered non-factory handlers')


def scene_signature(obj, armature):
    require(armature.animation_data.action is None, 'Haybot saved pose is not neutral')
    require(len(armature.data.bones) == 45 and len(obj.data.polygons) == 1225, 'Haybot geometry/rig count changed')
    require(all(m.type == 'ARMATURE' and m.object == armature for m in obj.modifiers)
            and len(obj.modifiers) == 1, 'Haybot modifier contract changed')
    bones = {b.name: {'matrix': animated.serialized(b.matrix_local), 'parent': b.parent.name if b.parent else None,
                      'use_deform': b.use_deform, 'inherit_scale': b.inherit_scale} for b in armature.data.bones}
    modifier = obj.modifiers[0]
    return json.loads(json.dumps({'geometry': common.geometry_signature(obj),
        'vertex_group_names': [g.name for g in obj.vertex_groups], 'actions': animated.action_signature(),
        'rest_bones': bones, 'images': image_signature(), 'scene': signatures.scene_signature(),
        'modifier': {key: getattr(modifier, key) for key in ('name', 'show_viewport', 'show_render',
             'use_deform_preserve_volume', 'use_vertex_groups', 'use_bone_envelopes', 'vertex_group', 'invert_vertex_group')},
        'nla': [(t.name, t.mute, [(s.name, s.action.name, s.frame_start, s.frame_end, s.action_frame_start,
                                 s.action_frame_end, s.scale, s.repeat, s.influence, s.blend_type, s.extrapolation)
                                for s in t.strips]) for t in armature.animation_data.nla_tracks]}))


def selected_image(output, proof):
    image = bpy.data.images.load(str(output/'textures/descriptor15.png'), check_existing=False)
    image.name = 'Haybot selected descriptor15 flat3823 raw RGBA16'
    image.colorspace_settings.name = 'Non-Color'; image.alpha_mode = 'STRAIGHT'
    expected = [v/255 for v in host.raw_rgba((output/'source/flat3823.bin').read_bytes())]
    require(list(image.size) == [64, 64] and len(image.pixels) == len(expected)
            and max(abs(a-b) for a, b in zip(image.pixels[:], expected)) < 1e-7,
            'Haybot all4096 source pixel values differ')
    require(set(expected[3::4]) == {1.0}, 'Haybot used image alpha is not opaque')
    # Decode the two other source images independently, but they do not create
    # additional materials, objects, animations or packaged model appearances.
    for row in proof['variants'][1:]:
        other = bpy.data.images.load(str(output/f'textures/descriptor{row["descriptor"]}.png'), check_existing=False)
        other.colorspace_settings.name = 'Non-Color'; other.alpha_mode = 'STRAIGHT'
        pixels = [v/255 for v in host.raw_rgba((output/f'source/flat{row["flat_index"]}.bin').read_bytes())]
        require(len(other.pixels) == len(pixels) and max(abs(a-b) for a, b in zip(other.pixels[:], pixels)) < 1e-7,
                'Haybot alternate source pixels differ')
        bpy.data.images.remove(other)
    return image


def add_material(obj, image, proof):
    require([p.index for p in obj.data.polygons if p.material_index == 16] == proof['affected_faces'],
            'Haybot affected material faces changed')
    color = obj.data.color_attributes['Color']
    require(all(tuple(color.data[loop].color) == (1., 1., 1., 1.)
                for p in obj.data.polygons if p.material_index == 16 for loop in p.loop_indices),
            'Haybot imported stored white SHADE changed')
    old = obj.data.materials[16]; old.use_fake_user = True
    material = old.copy(); material.name = 'Haybot source-selected phase0 run16'
    material.use_fake_user = False; obj.data.materials[16] = material
    nodes, links = material.node_tree.nodes, material.node_tree.links; nodes.clear()
    output = nodes.new('ShaderNodeOutputMaterial'); emission = nodes.new('ShaderNodeEmission')
    tex = nodes.new('ShaderNodeTexImage'); tex.name = 'TEXEL0'; tex.image = image
    tex.interpolation = 'Linear'; tex.extension = 'EXTEND'
    uv = nodes.new('ShaderNodeUVMap'); uv.uv_map = obj.data.uv_layers[0].name
    links.new(uv.outputs['UV'], tex.inputs['Vector'])
    shade = nodes.new('ShaderNodeVertexColor'); shade.layer_name = color.name; shade.name = 'Stored SHADE RGBA'
    environment = nodes.new('ShaderNodeRGB'); environment.name = 'Source-initial ENVIRONMENT'
    environment.outputs[0].default_value = (0, 0, 0, 1)
    primitive = nodes.new('ShaderNodeRGB'); primitive.name = 'Source-initial PRIMITIVE'
    primitive.outputs[0].default_value = (0, 0, 0, 0)
    subtract = nodes.new('ShaderNodeVectorMath'); subtract.operation = 'SUBTRACT'
    multiply = nodes.new('ShaderNodeVectorMath'); multiply.operation = 'MULTIPLY'
    add = nodes.new('ShaderNodeVectorMath'); add.operation = 'ADD'
    links.new(shade.outputs['Color'], subtract.inputs[0]); links.new(environment.outputs[0], subtract.inputs[1])
    links.new(subtract.outputs[0], multiply.inputs[0]); links.new(tex.outputs['Color'], multiply.inputs[1])
    links.new(multiply.outputs[0], add.inputs[0]); links.new(primitive.outputs[0], add.inputs[1])
    links.new(add.outputs[0], emission.inputs['Color'])
    alpha0 = nodes.new('ShaderNodeMath'); alpha0.operation = 'MULTIPLY'; alpha0.name = 'TEXEL0 alpha times SHADE alpha'
    alpha1 = nodes.new('ShaderNodeMath'); alpha1.operation = 'MULTIPLY'; alpha1.name = 'COMBINED alpha times ENVIRONMENT alpha'
    alpha1.inputs[1].default_value = host.STATE['environment_rgba'][3]/255
    links.new(tex.outputs['Alpha'], alpha0.inputs[0]); links.new(shade.outputs['Alpha'], alpha0.inputs[1])
    links.new(alpha0.outputs[0], alpha1.inputs[0])
    # For this selected state every used texel, stored vertex alpha and ENV
    # alpha is exactly one. The explicit formula therefore yields opaque
    # output, matching 80083140+40 rather than inventing a translucent pass.
    mix = nodes.new('ShaderNodeMixShader'); transparent = nodes.new('ShaderNodeBsdfTransparent')
    links.new(alpha1.outputs[0], mix.inputs[0]); links.new(transparent.outputs[0], mix.inputs[1])
    links.new(emission.outputs[0], mix.inputs[2]); links.new(mix.outputs[0], output.inputs['Surface'])
    material['CBFD_scope'] = host.SCOPE


def prepare(output, proof, document, source):
    obj = setup(source)
    armature = next(o for o in bpy.context.scene.objects if o.type == 'ARMATURE')
    animated.select_neutral(armature); framing = animated.framing_neutral(obj)
    before_geometry = common.geometry_signature(obj); before_actions = animated.action_signature()
    originals = {m.name: signatures.material_signature(m) for m in bpy.data.materials}
    for action in bpy.data.actions:
        action.use_fake_user = True
    image = selected_image(output, proof); add_material(obj, image, proof)
    require(common.geometry_signature(obj) == before_geometry and animated.action_signature() == before_actions,
            'Haybot shader changed original geometry, UV, RGBA, rig or Actions')
    require(all(signatures.material_signature(bpy.data.materials[name]) == value for name, value in originals.items()),
            'Haybot shader changed an original material')
    bpy.ops.file.pack_all()
    original_images = {sha((source.parent/r['uri']).read_bytes()) for r in document['images']}
    packed = image_signature()
    require(len(packed) == 19 and {v['bytes'] for v in packed.values()} ==
            original_images | {sha((output/'textures/descriptor15.png').read_bytes())}, 'Haybot packed image set changed')
    no_execution(proof)
    obj['CBFD_inspection_scope'] = host.SCOPE
    bpy.context.scene['CBFD_inspection_state'] = json.dumps(host.STATE, sort_keys=True)
    bpy.context.scene['CBFD_source_proof_sha256'] = sha((output/'source-proof.json').read_bytes())
    return obj, armature, framing


def run(output, verify):
    proof, document, source = inputs(output)
    obj, armature, framing = prepare(output, proof, document, source)
    expected = scene_signature(obj, armature)
    blend = output/host.BLEND
    if verify:
        saved = json.loads((output/'artifact.json').read_text())
        require(saved['blend_file'] == host.BLEND and saved['blend_sha256'] == sha(blend.read_bytes())
                and saved['source_proof_sha256'] == sha((output/'source-proof.json').read_bytes())
                and saved['source_gltf_sha256'] == host.SOURCE_GLTF_SHA256
                and saved['inspection_state'] == host.STATE and saved['scope'] == host.SCOPE
                and saved['scene_signature'] == expected and saved['framing'] == framing,
                'Haybot artifact audit differs from fresh source reconstruction')
        require('--disable-autoexec' in sys.argv, 'Haybot verify requires disabled autoexec')
        bpy.ops.wm.open_mainfile(filepath=str(blend), use_scripts=False)
        bpy.context.view_layer.update(); obj = mesh_object()
        armature = next(o for o in bpy.context.scene.objects if o.type == 'ARMATURE')
        no_execution(proof)
        require(scene_signature(obj, armature) == expected, 'reopened Haybot differs from fresh source reconstruction')
        require(obj.get('CBFD_inspection_scope') == host.SCOPE
                and bpy.context.scene.get('CBFD_inspection_state') == json.dumps(host.STATE, sort_keys=True)
                and bpy.context.scene.get('CBFD_source_proof_sha256') == sha((output/'source-proof.json').read_bytes()),
                'Haybot embedded inspection metadata changed')
        require(set(saved['renders']) == {'three-quarter.png', 'rear.png'}
                and all(sha((output/name).read_bytes()) == digest for name, digest in saved['renders'].items()),
                'Haybot preview changed')
        return {'verified': True, 'faces': 1225, 'joints': 45, 'actions': 15, 'packed_images': 19, 'writes': False}
    bpy.ops.wm.save_as_mainfile(filepath=str(blend))
    renders = {}
    for view in common.VIEWS:
        common.set_view(framing, view); path = output/(view+'.png'); bpy.context.scene.render.filepath = str(path)
        bpy.ops.render.render(write_still=True); renders[path.name] = sha(path.read_bytes())
    artifact = {'schema_version': 1, 'blend_file': host.BLEND, 'blend_sha256': sha(blend.read_bytes()),
                'source_gltf_sha256': host.SOURCE_GLTF_SHA256,
                'source_proof_sha256': sha((output/'source-proof.json').read_bytes()),
                'scope': host.SCOPE, 'inspection_state': host.STATE, 'scene_signature': expected,
                'framing': framing, 'renders': renders, 'blender_version': bpy.app.version_string,
                'source_pixel_checks': {'variants': 3, 'pixels_per_variant': 4096, 'used_alpha': 255}}
    (output/'artifact.json').write_bytes(host.encode(artifact))
    return {'created': True, 'blend_sha256': artifact['blend_sha256'], 'faces': 1225, 'joints': 45, 'actions': 15}


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--verify', action='store_true')
    args = parser.parse_args(sys.argv[sys.argv.index('--')+1:])
    print(json.dumps(run(args.output.resolve(), args.verify), sort_keys=True))


if __name__ == '__main__':
    main()
