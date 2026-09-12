#!/usr/bin/env python3
"""Render one generated glTF with deterministic Blender framing and lighting."""

from __future__ import annotations

import argparse
import json
import math
import sys
import tempfile
from pathlib import Path


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--size", type=int, default=768)
    parser.add_argument(
        "--view",
        choices=("front", "rear", "left", "right", "three-quarter"),
        default="three-quarter",
    )
    parser.add_argument(
        "--shading",
        choices=("material", "vertex"),
        default="material",
        help="render glTF materials or an untextured vertex-colour geometry check",
    )
    return parser.parse_args(argv)


def blender_arguments() -> list[str]:
    return sys.argv[sys.argv.index("--") + 1 :] if "--" in sys.argv else []


def main(argv: list[str] | None = None) -> int:
    import bpy  # type: ignore[import-not-found]
    from mathutils import Vector  # type: ignore[import-not-found]

    args = parse_args(blender_arguments() if argv is None else argv)
    source = args.input.resolve()
    output = args.output.resolve()
    if source.suffix.lower() != ".gltf" or not source.is_file():
        raise ValueError(f"generated glTF is absent: {source}")
    if not 64 <= args.size <= 4096:
        raise ValueError("render size must be between 64 and 4096")

    bpy.ops.wm.read_factory_settings(use_empty=True)
    # Blender assigns the first imported Action automatically. Review the
    # authored glTF node pose by omitting Actions from this temporary import.
    # Resetting Blender pose bones would also erase required skin corrections.
    gltf = json.loads(source.read_text(encoding="utf-8"))
    if gltf.get("animations"):
        gltf.pop("animations")
        with tempfile.NamedTemporaryFile(
            mode="w", suffix=".gltf", dir=source.parent, encoding="utf-8"
        ) as temporary:
            json.dump(gltf, temporary)
            temporary.flush()
            bpy.ops.import_scene.gltf(filepath=temporary.name)
    else:
        bpy.ops.import_scene.gltf(filepath=str(source))
    bpy.context.view_layer.update()
    meshes = [item for item in bpy.context.scene.objects if item.type == "MESH"]
    if not meshes:
        raise ValueError(f"no mesh imported from {source}")
    corners = [
        item.matrix_world @ Vector(corner)
        for item in meshes
        for corner in item.bound_box
    ]
    minimum = Vector(tuple(min(point[axis] for point in corners) for axis in range(3)))
    maximum = Vector(tuple(max(point[axis] for point in corners) for axis in range(3)))
    center = (minimum + maximum) * 0.5
    extent = maximum - minimum
    diagonal = max(extent.length, 1.0)

    camera_data = bpy.data.cameras.new("PreviewCamera")
    camera = bpy.data.objects.new("PreviewCamera", camera_data)
    bpy.context.scene.collection.objects.link(camera)
    directions = {
        "front": (0.0, -1.0, 0.12),
        "rear": (0.0, 1.0, 0.12),
        "left": (-1.0, 0.0, 0.12),
        "right": (1.0, 0.0, 0.12),
        "three-quarter": (1.15, -2.0, 0.85),
    }
    direction = Vector(directions[args.view]).normalized()
    camera.location = center + direction * diagonal * 2.0
    camera.rotation_euler = (center - camera.location).to_track_quat("-Z", "Y").to_euler()
    camera_data.type = "ORTHO"
    camera_data.ortho_scale = max(extent.x, extent.y, extent.z, 1.0) * 1.45
    camera_data.lens = 50
    # The camera is two diagonals away. Blender's default far plane (1000)
    # clips larger character/scene exports completely despite valid geometry.
    camera_data.clip_start = max(diagonal * 0.0001, 0.001)
    camera_data.clip_end = diagonal * 4.0
    bpy.context.scene.camera = camera

    scene = bpy.context.scene
    if args.shading == "vertex":
        scene.render.engine = "BLENDER_WORKBENCH"
        scene.display.shading.light = "STUDIO"
        scene.display.shading.color_type = "VERTEX"
        scene.display.shading.show_shadows = True
        scene.display.shading.show_cavity = True
        scene.display.shading.cavity_type = "WORLD"
        scene.display.shading.background_type = "VIEWPORT"
        scene.display.shading.background_color = (0.025, 0.03, 0.04)
    else:
        scene.render.engine = "BLENDER_EEVEE"
        world = bpy.data.worlds.new("PreviewWorld")
        world.use_nodes = True
        background = world.node_tree.nodes.get("Background")
        background.inputs["Color"].default_value = (0.025, 0.03, 0.04, 1.0)
        background.inputs["Strength"].default_value = 1.5
        scene.world = world
        for name, vector, strength in (
            ("Key", (-1.0, -1.5, 2.0), 28.0),
            ("Fill", (1.5, 0.5, 0.75), 16.0),
        ):
            light_data = bpy.data.lights.new(name=name, type="AREA")
            light_data.energy = diagonal * diagonal * strength
            light_data.shape = "DISK"
            light_data.size = diagonal * 1.5
            light = bpy.data.objects.new(name, light_data)
            scene.collection.objects.link(light)
            light.location = center + Vector(vector).normalized() * diagonal * 1.5
            light.rotation_euler = (center - light.location).to_track_quat(
                "-Z", "Y"
            ).to_euler()
    scene.render.resolution_x = args.size
    scene.render.resolution_y = args.size
    scene.render.resolution_percentage = 100
    scene.render.image_settings.file_format = "PNG"
    scene.render.film_transparent = False
    scene.render.filepath = str(output)
    scene.render.image_settings.color_mode = "RGBA"
    scene.view_settings.look = "AgX - Medium High Contrast"
    output.parent.mkdir(parents=True, exist_ok=True)
    bpy.ops.render.render(write_still=True)
    if not output.is_file() or output.stat().st_size == 0:
        raise ValueError(f"Blender did not produce preview: {output}")
    if not math.isfinite(diagonal):
        raise ValueError("rendered model bounds are non-finite")
    print(f"Rendered {source} to {output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
