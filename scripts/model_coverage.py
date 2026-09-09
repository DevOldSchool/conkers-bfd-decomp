"""Join ROM model identities with independent, explicitly bounded evidence."""

from __future__ import annotations

import hashlib
import json
from collections import Counter, defaultdict
from pathlib import Path

try:
    from scripts import model_assets as models
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    import model_assets as models
    from model_preview_evidence import preview_fingerprint


def read_manifest(path: Path, digest: str, family: str | None = None) -> dict:
    document = json.loads(path.read_text())
    if document.get("normalized_sha1") != digest:
        raise ValueError(f"coverage manifest belongs to a different ROM: {path}")
    if family is not None and document.get("family") != family:
        raise ValueError(f"coverage manifest family changed: {path}")
    return document


def blender_status(path: Path, evidence: dict[str, dict]) -> str:
    if not path.is_file():
        return "missing-preview"
    record = evidence.get(str(path.resolve()))
    if record is None or record.get("status") != "validated":
        return "unvalidated"
    try:
        current = preview_fingerprint(path)
    except (OSError, ValueError):
        return "stale-validation"
    return "validated" if current == record.get("fingerprint") else "stale-validation"


def runtime_coverage(records: list[dict], model_hash: str, first: int, count: int,
                     segment_8_offset: int | None) -> tuple[dict, dict, dict]:
    variants, images, observations, exact_lists, effective_lists = set(), set(), set(), set(), set()
    resolution_statuses = Counter()
    for record in records:
        if (record.get("model_sha1"), record.get("source_first_face"),
            record.get("source_face_count")) != (model_hash, first, count):
            raise ValueError("runtime coverage model or material span changed")
        for variant in record.get("variants", []):
            evidence = variant.get("evidence", [])
            if not evidence:
                continue
            variants.add(variant["material_state_hash"])
            captured = variant.get("captured_texture")
            if captured and captured.get("file") and captured.get("png_sha1"):
                source = models._validated_preview_source(record["_source_root"], captured["file"])
                if hashlib.sha1(source.read_bytes()).hexdigest() != captured["png_sha1"]:
                    raise ValueError("runtime coverage texture hash changed")
                images.add(captured["png_sha1"])
            for item in evidence:
                # Trace path plus event/draw identity deduplicates overlapping catalogs;
                # catalog-local trace_index values alone are not globally unique.
                observations.add((item["trace"], item["event_index"], item["draw_run_index"]))
                resolution = item.get("runtime_segment_8_resolution")
                if resolution is None or segment_8_offset is None:
                    continue
                if int(resolution["offset"], 16) != segment_8_offset:
                    raise ValueError("runtime coverage segment-8 offset changed")
                status = resolution["status"]
                resolution_statuses[status] += 1
                if status in ("exact-runtime-list-effective-state", "exact-runtime-list-state-later-overridden"):
                    if not resolution.get("payload_sha256"):
                        raise ValueError("runtime coverage exact list lacks a payload hash")
                    exact_lists.add(resolution["payload_sha256"])
                    if status == "exact-runtime-list-effective-state":
                        effective_lists.add(resolution["payload_sha256"])
    return (
        {"status": "observed" if variants else "unobserved", "variant_count": len(variants),
         "draw_observation_count": len(observations)},
        {"status": "observed" if images else "unobserved", "image_count": len(images)},
        {"status": "not-required" if segment_8_offset is None else "observed" if exact_lists else "missing",
         "offset": segment_8_offset, "exact_payload_count": len(exact_lists),
         "effective_payload_count": len(effective_lists), "observation_status_counts": dict(sorted(resolution_statuses.items()))},
    )


def placement_associations(placements: dict) -> dict[tuple[int, int, int], list[dict]]:
    result = defaultdict(list)
    for scene in placements["scenes"]:
        for record in scene["records"]:
            if not record["model_resolution_status"].startswith("resolved-"):
                continue
            source = record["model_source"]
            key = tuple(source) if len(source) == 3 else (*source, 0)
            result[key].append({"kind": "object-placement", "scene_index": scene["scene_index"],
                                "source_bank": scene["bank_index"], "record": record["index"],
                                "consumer": "func_150039E0"})
    return result


def summarize(model_records: list[dict], rows: list[dict]) -> dict:
    def counts(records: list[dict], field: str) -> dict:
        return dict(sorted(Counter(record[field]["status"] for record in records).items()))

    return {
        "model_count": len(model_records), "material_run_count": len(rows),
        "source_face_count": sum(record["source_face_count"] for record in model_records),
        "standalone_geometry": counts(model_records, "standalone_geometry"),
        "blender_interchange": counts(model_records, "blender_interchange"),
        "scene_association": counts(model_records, "scene_association"),
        "semantic_name": counts(model_records, "semantic_name"),
        "runtime_material_observed_model_count": len({
            row["model_key"] for row in rows if row["runtime_material"]["status"] == "observed"
        }),
        "runtime_texture_observed_model_count": len({
            row["model_key"] for row in rows if row["runtime_texture"]["status"] == "observed"
        }),
        **{field: counts(rows, field) for field in (
            "static_texture", "runtime_material", "runtime_texture", "dynamic_segment_8", "character_composition", "attachment_composition", "render_to_texture")},
    }


def rank_gaps(model_records: list[dict], rows: list[dict]) -> list[dict]:
    gaps = defaultdict(list)
    for row in rows:
        for field, statuses in (
            ("static_texture", {"missing"}), ("runtime_material", {"unobserved"}),
            ("dynamic_segment_8", {"missing"}), ("character_composition", {"unobserved", "partial"}),
            ("attachment_composition", {"unobserved", "partial"}),
        ):
            state = row[field]
            if state["status"] in statuses:
                gaps[(row["bank"], field, state.get("reason", state["status"]))].append(row)
    for record in model_records:
        if record["scene_association"]["status"] == "missing":
            gaps[(record["bank"], "scene_association", "missing")].append(record)
    result = []
    for (bank, dimension, reason), members in gaps.items():
        keys = sorted({(item["bank"], item["entry"], item["segment"]) for item in members})
        result.append({"bank": bank, "dimension": dimension, "reason": reason,
                       "model_count": len(keys), "material_run_count": sum("material_run" in item for item in members),
                       "source_faces_in_affected_models_or_runs": sum(item["source_face_count"] for item in members),
                       "model_keys": [f"{b:02x}:{e:04d}:{s:02d}" for b, e, s in keys]})
    return sorted(result, key=lambda item: (-item["source_faces_in_affected_models_or_runs"], item["bank"], item["dimension"], item["reason"]))


def attachment_source_faces(data: bytes, records: list[dict]) -> tuple[set[int], set[int], set[int]]:
    """Validate composed part spans against native pointers, preserving scene uncertainty."""
    geometry, layout = models.parse_attachment_model(data, models.parse_model_geometry)
    faces, owners, bones = set(), set(), set()
    digest = hashlib.sha1(data).hexdigest()
    for record in records:
        attachment = record["attachment"]
        if attachment["model_sha1"] != digest:
            raise ValueError("attachment coverage model identity changed")
        for part in attachment["parts"]:
            index = part["part"]
            if not isinstance(index, int) or not 0 <= index < layout["display_list_count"]:
                raise ValueError("attachment coverage references an absent part")
            start = layout["display_list_pointers"][index]
            end = (layout["display_list_pointers"][index+1] if index+1 < layout["display_list_count"]
                   else geometry.display_list_offset + geometry.display_list_size)
            selected = {i for i, offset in enumerate(geometry.face_command_offsets) if start <= offset < end}
            if part["source_first_command"] != start or part["source_face_count"] != len(selected):
                raise ValueError("attachment coverage source span changed")
            faces.update(selected)
        owners.add(record["parent_entry"])
        bones.add(attachment["parent_bone"])
    return faces, owners, bones


def extract_coverage(profile: str, rom: Path | None, root: Path, textures: Path,
                     output: Path, runtime_paths: tuple[Path, ...] = (),
                     activity_path: Path | None = None, blender_path: Path | None = None,
                     scene_path: Path | None = None) -> dict:
    _, _, digest, _, _ = models.load_model_bundles(profile, rom, 9)
    inputs = {}

    def remember(path: Path) -> None:
        inputs[models.manifest_source(path)] = hashlib.sha256(path.read_bytes()).hexdigest()

    runtime = defaultdict(list)
    for path in dict.fromkeys(runtime_paths):
        remember(path)
        for key, value in models.load_runtime_material_catalog(path, digest).items():
            runtime[key].append(value)
    composition_faces = defaultdict(set)
    composition_owners = defaultdict(set)
    render_texture_faces = defaultdict(set)
    render_texture_owners = defaultdict(set)
    if activity_path is not None:
        activity = read_manifest(activity_path, digest, "runtime-character-model-activity")
        remember(activity_path)
        for composition in activity.get("character_compositions", []):
            for cluster in composition.get("resolved_clusters", []):
                key = tuple(cluster[field] for field in ("bank", "entry", "segment", "material_run"))
                composition_faces[(key, cluster["model_sha1"])].update(range(cluster["first_face"], cluster["first_face"] + cluster["face_count"]))
                composition_owners[key].add(composition["entry"])
        for composition in activity.get("render_texture_compositions", []):
            for cluster in composition.get("resolved_clusters", []):
                key = tuple(cluster[field] for field in ("bank", "entry", "segment", "material_run"))
                render_texture_faces[(key, cluster["model_sha1"])].update(range(cluster["first_face"], cluster["first_face"] + cluster["face_count"]))
                render_texture_owners[key].add(composition["entry"])
    blender = {}
    if blender_path is not None and blender_path.is_file():
        validation = json.loads(blender_path.read_text())
        if validation.get("family") != "blender-model-preview-validation":
            raise ValueError("unsupported Blender validation report")
        remember(blender_path)
        for record in validation.get("files", []):
            key = str(Path(record["path"]).resolve())
            if key in blender:
                raise ValueError("duplicate Blender validation file")
            blender[key] = record

    attachment_records = defaultdict(list)
    attachment_path = root / "us-character-compositions/manifest.json"
    attachment_trace_count = 0
    if attachment_path.is_file():
        composed = read_manifest(attachment_path, digest, "runtime-character-model-composition-preview")
        remember(attachment_path)
        attachment_trace_count = len(composed.get("source_attachment_traces", []))
        for body in composed.get("posed_models", []):
            for attachment in body.get("attachments", []):
                if body.get("attachment_status") != "captured-parts-assembled-from-matching-submission":
                    raise ValueError("attachment composition has no submission proof")
                key = tuple(attachment[field] for field in ("bank", "entry", "segment"))
                if key[0] != 9 or key[2] != 0:
                    raise ValueError("attachment coverage references an unsupported source family")
                preview_path = models._validated_preview_source(attachment_path.parent, body["gltf_file"])
                attachment_records[key].append({"attachment": attachment, "parent_entry": body["entry"],
                    "preview": {"file": models.manifest_source(preview_path), "status": blender_status(preview_path, blender)}})
        if sum(len(records) for records in attachment_records.values()) != composed.get("attachment_instance_count", 0):
            raise ValueError("attachment composition instance count changed")

    flat_payloads = models.load_flat_asset_payloads(profile, rom, digest)
    catalog = models.load_preview_texture_catalog(textures, digest, tuple(flat_payloads))
    for family in models.PREVIEW_TEXTURE_FAMILIES:
        remember(textures / family / "manifest.json")
    placements, _ = models.load_object_placement_manifest(profile, rom, include_files=False)
    associations = placement_associations(placements)
    if scene_path is not None:
        scenes = read_manifest(scene_path, digest, "model-scene-consumers")
        remember(scene_path)
        for record in scenes["model_associations"]:
            key = tuple(record[field] for field in ("bank", "entry", "segment"))
            for association in record["associations"]:
                if association not in associations[key]:
                    associations[key].append(association)

    model_records, rows = [], []
    seen_runtime = set()
    seen_composition = set()
    seen_attachments = set()
    for bank in models.BANK_INDICES:
        _, _, bank_digest, bundles, _ = models.load_model_bundles(profile, rom, bank)
        if bank_digest != digest:
            raise ValueError("ROM changed during coverage scan")
        extraction_root = root / f"us-bank-{bank:02x}"
        preview_root = root / f"us-bank-{bank:02x}-preview"
        extracted = {}
        if (extraction_root / "manifest.json").is_file():
            path = extraction_root / "manifest.json"
            manifest = read_manifest(path, digest)
            remember(path)
            extracted = {(bundle["bank_entry"], segment["index"]): segment
                         for bundle in manifest["bundles"] for segment in bundle["segments"]}
        previews = {}
        if (preview_root / "manifest.json").is_file():
            path = preview_root / "manifest.json"
            manifest = read_manifest(path, digest)
            remember(path)
            previews = {(item["bank_entry"], item["segment"]): item for item in manifest["models"]}
        for bundle in bundles:
            rebuilt = models.encode_model_bundle(bundle.segments) if bank == 4 else bundle.segments[0].data
            if bank == 9 and models.is_attachment_model(bundle.data):
                geometry, layout = models.parse_attachment_model(bundle.data, models.parse_model_geometry)
                regions = {part["name"]: bundle.data[part["offset"]:part["offset"] + part["size"]] for part in layout["sections"]}
                rebuilt = models.encode_attachment_model(geometry, layout, regions)
            if rebuilt != bundle.data:
                raise ValueError("coverage model bundle did not rebuild byte-identically")
            for segment in bundle.segments:
                if not segment.data:
                    continue
                key = (bank, bundle.index, segment.index)
                model_hash = hashlib.sha1(segment.data).hexdigest()
                geometry = models.parse_geometry_for_bank(segment.data, bank)
                is_attachment = bank == 9 and models.is_attachment_model(segment.data)
                attached_faces, attached_owners, attached_bones = (attachment_source_faces(segment.data, attachment_records[key])
                    if is_attachment else (set(), set(), set()))
                if is_attachment:
                    seen_attachments.add(key)
                exported = extracted.get(key[1:])
                standalone = "missing-extraction"
                if exported is not None:
                    if exported["sha1"] != model_hash:
                        raise ValueError(f"extracted model manifest identity changed: {key}")
                    source = models._validated_preview_source(extraction_root, exported["file"])
                    if source.read_bytes() != segment.data:
                        raise ValueError(f"extracted model differs from ROM: {key}")
                    standalone = "extracted-byte-verified"
                preview = previews.get(key[1:])
                files = []
                if preview is not None:
                    if preview["source_face_count"] != len(geometry.faces):
                        raise ValueError(f"preview source span changed: {key}")
                    for field in ("gltf_file", "bind_gltf_file"):
                        if preview.get(field):
                            path = preview_root / preview[field]
                            files.append({"file": models.manifest_source(path), "status": blender_status(path, blender)})
                statuses = {item["status"] for item in files}
                model_record = {
                    "key": f"{bank:02x}:{bundle.index:04d}:{segment.index:02d}",
                    "bank": bank, "entry": bundle.index, "segment": segment.index,
                    "model_sha1": model_hash, "source_face_count": len(geometry.faces),
                    "standalone_geometry": {"status": standalone, "rom_rebuild": "byte-identical"},
                    "blender_interchange": {"status": "validated" if statuses == {"validated"} else "missing-preview" if not files else "stale-validation" if "stale-validation" in statuses else "unvalidated", "files": files},
                    "scene_association": {"status": "resolved" if associations.get(key) else "missing", "associations": associations.get(key, [])},
                    "semantic_name": {"status": "unknown", "name": None},
                    "vertex_transforms": {
                        "status": "vertex-load-matrix-assignment" if bank == 1 or is_attachment else "no-local-character-palette",
                        "faces_differing_from_draw_matrix": models.vertex_matrix_mismatch_face_count(geometry),
                    },
                    "visual_parity": {"status": "unverified"},
                    "attachment_composition": {"status": "not-applicable" if not is_attachment else "unobserved" if not attached_faces else "observed" if len(attached_faces) == len(geometry.faces) else "partial",
                        "observed_source_face_count": len(attached_faces), "parent_entries": sorted(attached_owners),
                        "parent_bones": sorted(attached_bones), "previews": [r["preview"] for r in attachment_records[key]]},
                }
                model_records.append(model_record)
                for index, run in enumerate(geometry.material_runs):
                    run_key = (*key, index)
                    texture, reason = models.choose_preview_texture(
                        run, catalog, flat_payloads)
                    material, captured, dynamic = runtime_coverage(runtime[run_key], model_hash, run.first_face, run.face_count, run.runtime_render_state_offset)
                    seen_runtime.add(run_key)
                    faces = composition_faces.get((run_key, model_hash), set())
                    texture_faces = render_texture_faces.get((run_key, model_hash), set())
                    attached_run_faces = attached_faces.intersection(range(run.first_face, run.first_face + run.face_count))
                    seen_composition.add((run_key, model_hash))
                    if faces.difference(range(run.first_face, run.first_face + run.face_count)):
                        raise ValueError("composition coverage escapes source material run")
                    if texture_faces.difference(range(run.first_face, run.first_face + run.face_count)):
                        raise ValueError("render-to-texture coverage escapes source material run")
                    rows.append({
                        "key": f"{model_record['key']}:{index:04d}", "model_key": model_record["key"],
                        "bank": bank, "entry": bundle.index, "segment": segment.index, "material_run": index,
                        "source_first_face": run.first_face, "source_face_count": run.face_count,
                        "static_texture": {"status": "resolved" if texture else "not-required" if run.texture_enabled is False else "missing", "reason": reason, "png_sha1": texture.sha1 if texture else None},
                        "runtime_material": material, "runtime_texture": captured, "dynamic_segment_8": dynamic,
                        "character_composition": {"status": "not-applicable" if bank != 1 else "unobserved" if not faces else "observed" if len(faces) == run.face_count else "partial", "observed_source_face_count": len(faces), "renderer_entries": sorted(composition_owners.get(run_key, set()))},
                        "attachment_composition": {"status": "not-applicable" if not is_attachment else "unobserved" if not attached_run_faces else "observed" if len(attached_run_faces) == run.face_count else "partial",
                            "observed_source_face_count": len(attached_run_faces), "parent_entries": sorted(attached_owners)},
                        "render_to_texture": {"status": "not-applicable" if bank != 1 else "unobserved" if not texture_faces else "observed" if len(texture_faces) == run.face_count else "partial", "observed_source_face_count": len(texture_faces), "renderer_entries": sorted(render_texture_owners.get(run_key, set()))},
                    })
    if set(runtime).difference(seen_runtime):
        raise ValueError("runtime coverage refers to a missing model or material run")
    if set(composition_faces).difference(seen_composition):
        raise ValueError("composition coverage refers to a missing or changed model or material run")
    if set(render_texture_faces).difference(seen_composition):
        raise ValueError("render-to-texture coverage refers to a missing or changed model or material run")
    if {key for key, values in attachment_records.items() if values}.difference(seen_attachments):
        raise ValueError("attachment coverage refers to a missing model")
    result = {
        "schema_version": 1, "family": "model-coverage-gaps", "profile": profile,
        "normalized_sha1": digest, "input_manifests_sha256": dict(sorted(inputs.items())),
        "evidence_availability": {
            "runtime_material_catalog_count": len(set(runtime_paths)),
            "character_activity": "supplied" if activity_path else "not-supplied",
            "scene_consumers": "supplied" if scene_path else "placements-only",
            "blender_file_records": len(blender),
            "semantic_name_registry": "not-supplied",
            "attachment_trace_count": attachment_trace_count,
        },
        "summary": summarize(model_records, rows),
        "by_bank": {f"{bank:02x}": summarize([r for r in model_records if r["bank"] == bank], [r for r in rows if r["bank"] == bank]) for bank in models.BANK_INDICES},
        "gap_families": rank_gaps(model_records, rows), "models": model_records, "material_runs": rows,
        "unresolved_placements": placements["unresolved_bank_11_dispatch_references"],
        "limitations": [
            "Material rows inherit geometry, interchange, scene and naming evidence through model_key.",
            "Runtime observation is existential within the supplied corpus, not exhaustive state or face coverage.",
            "Static texture status uses the conservative exporter policy, including known runtime loader contracts.",
            "Missing scene association means absent from recovered consumers, not unused by the game.",
            "A captured attachment parent does not establish a numeric scene identity; those dimensions remain separate.",
            "Semantic names require a reviewed numeric-ID/caller registry; none is supplied here.",
            "Legacy aggregate Blender reports do not validate individual current files.",
            "Interchange validation does not establish N64 lighting, combiner, mipmap or raster parity.",
        ],
    }
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = output.with_suffix(output.suffix + ".tmp")
    temporary.write_text(json.dumps(result, indent=2) + "\n")
    temporary.replace(output)
    return result
