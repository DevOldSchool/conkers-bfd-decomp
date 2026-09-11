#!/usr/bin/env python3
"""Import every generated model preview in Blender and emit a JSON report."""

from __future__ import annotations

import argparse
import json
import math
import sys
from pathlib import Path
from typing import Any

sys.path.insert(0, str(Path(__file__).resolve().parent))
from model_preview_evidence import preview_fingerprint


BANKS = (1, 3, 4, 9)


def collect_preview_records(
    model_root: Path, include_animated: bool = True, banks: tuple[int, ...] = BANKS,
) -> list[dict[str, Any]]:
    if not banks or len(set(banks)) != len(banks) or any(bank not in BANKS for bank in banks):
        raise ValueError('preview bank selection must contain unique supported banks')
    records: list[dict[str, Any]] = []
    for bank in banks:
        preview_root = model_root / f"us-bank-{bank:02x}-preview"
        manifest_path = preview_root / "manifest.json"
        if not manifest_path.is_file():
            raise ValueError(f"missing preview manifest: {manifest_path}")
        manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
        if manifest.get("bank_index") != bank:
            raise ValueError(f"preview manifest bank changed: {manifest_path}")
        models = manifest.get("models", [])
        if len(models) != manifest.get("model_count"):
            raise ValueError(f"preview model count changed: {manifest_path}")
        for model in models:
            source = model.get("bind_gltf_file") if bank == 1 else model.get("gltf_file")
            if not isinstance(source, str):
                raise ValueError(f"model preview path missing in {manifest_path}")
            records.append(
                {
                    "bank": bank,
                    "kind": "bind-model" if bank == 1 else "model",
                    "path": preview_root / source,
                    "expected_face_count": model.get("face_count"),
                }
            )
            if bank == 1 and include_animated:
                animated = model.get("gltf_file")
                if not isinstance(animated, str):
                    raise ValueError(f"animated preview path missing in {manifest_path}")
                records.append(
                    {
                        "bank": bank,
                        "kind": "animated-model",
                        "path": preview_root / animated,
                        "expected_face_count": model.get("face_count"),
                    }
                )
        for scene in manifest.get("assembled_scenes", []):
            source = scene.get("gltf_file")
            if not isinstance(source, str):
                raise ValueError(f"assembled scene path missing in {manifest_path}")
            records.append(
                {
                    "bank": bank,
                    "kind": "assembled-scene",
                    "path": preview_root / source,
                }
            )
        if len(manifest.get("assembled_scenes", [])) != manifest.get(
            "assembled_scene_count", 0
        ):
            raise ValueError(f"assembled scene count changed: {manifest_path}")
    missing = [record["path"] for record in records if not record["path"].is_file()]
    if missing:
        raise ValueError(f"missing generated preview: {missing[0]}")
    return records


def collect_composition_records(root: Path) -> list[dict[str, Any]]:
    manifest_path = root / "manifest.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    if manifest.get("family") != "runtime-character-model-composition-preview":
        raise ValueError(f"composition manifest changed: {manifest_path}")
    records = [
        {
            "bank": 1,
            "kind": "composed-character",
            "path": root / model["gltf_file"],
        }
        for model in manifest.get("models", [])
    ]
    neutral_count = len(records)
    if neutral_count != manifest.get("model_count"):
        raise ValueError(f"composition model count changed: {manifest_path}")
    records.extend(
        {
            "bank": 1,
            "kind": "posed-composed-character",
            "path": root / model["gltf_file"],
        }
        for model in manifest.get("posed_models", [])
    )
    if len(records) - neutral_count != manifest.get("posed_model_count", 0):
        raise ValueError(f"posed composition model count changed: {manifest_path}")
    for field, count_field, kind in (
        ("render_texture_models", "render_texture_model_count", "render-to-texture-character"),
        ("render_texture_posed_models", "render_texture_posed_model_count", "posed-render-to-texture-character"),
    ):
        models = manifest.get(field, [])
        if len(models) != manifest.get(count_field, 0):
            raise ValueError(f"render-to-texture composition count changed: {manifest_path}")
        records.extend({"bank": 1, "kind": kind, "path": root / model["gltf_file"]} for model in models)
    missing = [record["path"] for record in records if not record["path"].is_file()]
    if missing:
        raise ValueError(f"missing generated composition preview: {missing[0]}")
    return records


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--model-root",
        type=Path,
        default=Path("build/assets/models"),
        help="directory containing us-bank-XX-preview outputs",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=Path("build/assets/models/blender-validation.json"),
        help="JSON report path",
    )
    parser.add_argument(
        "--composition-root",
        type=Path,
        help="optional trace-resolved character composition preview directory",
    )
    parser.add_argument(
        "--skip-animated",
        action="store_true",
        help="validate bind geometry but skip bank-01 files containing Actions",
    )
    parser.add_argument("--records", type=Path,
                        help="explicit generated preview records for a cached batch")
    return parser.parse_args(argv)


def blender_arguments() -> list[str]:
    return sys.argv[sys.argv.index("--") + 1 :] if "--" in sys.argv else []


def main(argv: list[str] | None = None) -> int:
    import bpy  # type: ignore[import-not-found]

    args = parse_args(blender_arguments() if argv is None else argv)
    model_root = args.model_root.resolve()
    records = (json.loads(args.records.read_text()) if args.records else
               collect_preview_records(model_root, not args.skip_animated))
    records = [{**record, "path": Path(record["path"]).resolve()} for record in records]
    if args.composition_root is not None and args.records is None:
        records.extend(collect_composition_records(args.composition_root.resolve()))
    totals: dict[str, Any] = {
        "schema_version": 2,
        "family": "blender-model-preview-validation",
        "blender_version": bpy.app.version_string,
        "model_root": str(model_root),
        "include_animated": not args.skip_animated,
        "file_count": len(records),
        "mesh_count": 0,
        "polygon_count": 0,
        "action_count": 0,
        "by_kind": {},
        "by_bank": {},
        "files": [],
    }
    for record in records:
        fingerprint = preview_fingerprint(record["path"])
        bpy.ops.wm.read_factory_settings(use_empty=True)
        bpy.ops.import_scene.gltf(filepath=str(record["path"]))
        meshes = [item for item in bpy.context.scene.objects if item.type == "MESH"]
        source_document = json.loads(record["path"].read_text(encoding="utf-8"))
        empty_source = (record.get("expected_face_count") == 0
                        and source_document.get("extras", {}).get("geometryStatus") == "empty-drawable-geometry"
                        and source_document.get("extras", {}).get("drawableFaceCount") == 0
                        and not source_document.get("meshes"))
        if not meshes and not empty_source:
            raise ValueError(f"no mesh imported from {record['path']}")
        for item in meshes:
            if any(
                not all(math.isfinite(component) for component in vertex.co)
                for vertex in item.data.vertices
            ):
                raise ValueError(f"non-finite vertex imported from {record['path']}")
        mesh_count = len(meshes)
        polygon_count = sum(len(item.data.polygons) for item in meshes)
        action_count = len(bpy.data.actions)
        morph_info = source_document.get("extras", {}).get("romMorphTargets")
        morph_shape_count = 0
        if morph_info is not None:
            expected_names = source_document["meshes"][0]["extras"]["targetNames"]
            morph_meshes = [item for item in meshes if item.data.shape_keys is not None]
            if len(morph_meshes) != 1 or len(expected_names) != morph_info["shapeCount"]:
                raise ValueError(f"imported morph mesh count changed: {record['path']}")
            item = morph_meshes[0]
            blocks = list(item.data.shape_keys.key_blocks)
            if [block.name for block in blocks[1:]] != expected_names:
                raise ValueError(f"imported shape-key names changed: {record['path']}")
            for index, block in enumerate(blocks):
                if len(block.data) != len(item.data.vertices) or not math.isfinite(block.value) or (index > 0 and block.value != 0):
                    raise ValueError(f"imported shape-key extent/default changed: {record['path']}")
                if any(not all(math.isfinite(value) for value in vertex.co) for vertex in block.data):
                    raise ValueError(f"non-finite morph position imported: {record['path']}")
            morph_shape_count = len(blocks) - 1
        expected_culling_materials = sum(
            "faceCulling" in material.get("extras", {})
            for material in source_document.get("materials", [])
        )
        culling_materials = {"back": 0, "double-sided": 0}
        for material in bpy.data.materials:
            evidence = material.get("faceCulling")
            if evidence is None:
                continue
            expected_backface = evidence.get("mode") == "back"
            if material.use_backface_culling != expected_backface:
                raise ValueError(f"imported material culling changed: {record['path']} / {material.name}")
            culling_materials["back" if expected_backface else "double-sided"] += 1
        if sum(culling_materials.values()) != expected_culling_materials:
            raise ValueError(f"imported culling evidence is incomplete: {record['path']}")
        if fingerprint != preview_fingerprint(record["path"]):
            raise ValueError(f"preview changed during import: {record['path']}")
        totals["files"].append({
            "path": str(record["path"].resolve()),
            "bank": record["bank"],
            "kind": record["kind"],
            "status": "validated",
            "fingerprint": fingerprint,
            "mesh_count": mesh_count,
            "polygon_count": polygon_count,
            "action_count": action_count,
            "morph_shape_count": morph_shape_count,
            "culling_materials": culling_materials,
        })
        totals["mesh_count"] += mesh_count
        totals["polygon_count"] += polygon_count
        totals["action_count"] += action_count
        for field, value in (("by_kind", record["kind"]), ("by_bank", str(record["bank"]))):
            current = totals[field].setdefault(
                value,
                {"file_count": 0, "mesh_count": 0, "polygon_count": 0, "action_count": 0},
            )
            current["file_count"] += 1
            current["mesh_count"] += mesh_count
            current["polygon_count"] += polygon_count
            current["action_count"] += action_count

    output = args.output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(totals, indent=2) + "\n", encoding="utf-8")
    print(
        f"Validated {totals['file_count']} glTF files in Blender "
        f"({totals['mesh_count']} meshes, {totals['polygon_count']} polygons, "
        f"{totals['action_count']} Actions)."
    )
    print(f"Report: {output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
