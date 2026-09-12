"""Attach ROM models only through captured renderer and submission evidence."""

from __future__ import annotations

import base64
import copy
import hashlib
import json
import shutil
import struct
from collections import Counter
from dataclasses import replace
from pathlib import Path

try:
    from scripts import model_assets as models
    from scripts.mupen_trace import CHARACTER_POOL_ADDRESS, CHARACTER_POOL_RECORD_SIZE, CHARACTER_POOL_RECORD_COUNT
except ModuleNotFoundError:
    import model_assets as models
    from mupen_trace import CHARACTER_POOL_ADDRESS, CHARACTER_POOL_RECORD_SIZE, CHARACTER_POOL_RECORD_COUNT


def address(value) -> int:
    return (int(value, 0) if isinstance(value, str) else int(value)) & 0xFFFFFFFF


def memory_blocks(event: dict) -> list[tuple[str, int, bytes]]:
    result = []
    for probe in event.get("evidence", {}).get("memory", []):
        if "data_base64" not in probe:
            continue
        raw = base64.b64decode(probe["data_base64"], validate=True)
        if len(raw) != probe["length"] or hashlib.sha256(raw).hexdigest() != probe["sha256"]:
            raise ValueError("attachment capture memory identity changed")
        result.append((probe["name"], address(probe["resolved_address"]), raw))
    return result


def named_block(blocks: list, name: str) -> tuple[int, bytes]:
    found = [(base, raw) for label, base, raw in blocks if label == name]
    if len(found) != 1:
        raise ValueError(f"attachment capture requires one {name} block")
    return found[0]


def memory_at(blocks: list, start: int, size: int) -> bytes:
    found = {raw[start-base:start-base+size] for _, base, raw in blocks
             if base <= start and start + size <= base + len(raw)}
    if len(found) != 1:
        raise ValueError(f"attachment memory is missing or conflicting at 0x{start:08X}")
    return found.pop()


def graphics_snapshot(event: dict) -> dict:
    blocks = memory_blocks(event)
    _, task = named_block(blocks, "task")
    root, commands = named_block(blocks, "command-buffer")
    if (len(task) != 64 or int.from_bytes(task[:4], "big") != 1
            or int.from_bytes(task[48:52], "big") & 0x1FFFFFFF != root & 0x1FFFFFFF
            or int.from_bytes(task[52:56], "big") != len(commands)):
        raise ValueError("attachment submission lacks a matching graphics task header")
    nested = {base: raw for name, base, raw in blocks if name.startswith("nested-display-list-")}
    origins = []
    effective, unresolved = models.flatten_display_lists(commands, nested, root_address=root, origins=origins)
    if unresolved:
        raise ValueError("attachment submission has uncaptured display-list targets")
    return {"blocks": blocks, "root_address": root, "root_bytes": commands,
            "root_sha256": hashlib.sha256(commands).hexdigest(),
            "effective": effective, "origins": origins}


def read_trace(path: Path, digest: str, spec_name: str) -> tuple[str, list[dict]]:
    data = path.read_bytes()
    records = [json.loads(line) for line in data.splitlines() if line.strip()]
    if (not records or records[0].get("record_type") != "session"
            or records[0].get("spec_name") != spec_name
            or records[0].get("normalized_sha1") != digest
            or any(r.get("schema") != "conker.model-draw-state-trace/v1" for r in records)):
        raise ValueError("attachment trace schema, consumer or ROM identity changed")
    return hashlib.sha256(data).hexdigest(), [r for r in records if r.get("record_type") == "draw_state"]


def attachment_draws(events: list[dict]) -> tuple[list[dict], list[dict]]:
    """Pair selections by renderer record and stack, never by event adjacency."""
    pending, draws, incomplete = {}, [], []
    for index, event in enumerate(events):
        kind = event.get("breakpoint")
        if kind not in ("attachment-part-selected", "attachment-draw-return"):
            continue
        expected = 0x15031870 if kind == "attachment-part-selected" else 0x15031914
        if address(event["hook_address"]) != expected:
            raise ValueError("attachment renderer hook changed")
        blocks = memory_blocks(event)
        record_address, record = named_block(blocks, "attachment-record")
        parent_address, parent = named_block(blocks, "parent-character")
        stack_address, stack = named_block(blocks, "attachment-stack")
        if len(record) != 0x5C or len(parent) != CHARACTER_POOL_RECORD_SIZE or len(stack) < 4:
            raise ValueError("attachment renderer record extent changed")
        start = int.from_bytes(stack[:4], "big")
        key = (record_address, stack_address, start)
        state = event["state"]
        if kind == "attachment-part-selected":
            if (address(state["model"]["attachment_address"]) != record_address
                    or address(state["model"]["parent_character_address"]) != parent_address):
                raise ValueError("attachment selected record address changed")
            draw = pending.setdefault(key, {"record_address": record_address, "record": record,
                "parent_address": parent_address, "parent": parent, "command_buffer_start": start,
                "first_event_index": index, "parts": []})
            if draw["record"] != record or draw["parent_address"] != parent_address:
                raise ValueError("attachment identity changes between selected parts")
            draw["parts"].append({"event_index": index,
                "target": address(state["rdp"]["selected_display_list"]),
                "call_address": address(state["rdp"]["call_command_address"])})
        else:
            draw = pending.pop(key, None)
            if draw is None:
                incomplete.append({"event_index": index, "reason": "return-without-selected-parts"})
                continue
            if draw["record"] != record or draw["parent_address"] != parent_address:
                raise ValueError("attachment identity changes at renderer return")
            end = address(state["rdp"]["command_buffer_end"])
            if start >= end or (start | end) & 7 or end - start > 0x10000:
                raise ValueError("attachment renderer range is invalid")
            draw.update(return_event_index=index, command_buffer_end=end)
            following = next((i for i in range(index + 1, len(events))
                              if models.captured_task_type(events[i]) == 1), None)
            if following is None:
                incomplete.append({"event_index": index, "reason": "no-following-graphics-task"})
            else:
                draw["submission_event_index"] = following
                draws.append(draw)
    incomplete.extend({"event_index": r["first_event_index"], "reason": "selected-parts-without-return"}
                      for r in pending.values())
    return draws, incomplete


def subset_faces(geometry, indices: list[int]):
    """Keep original material and face identities while selecting callable parts."""
    selected = set(indices)
    if len(selected) != len(indices) or indices != sorted(indices):
        raise ValueError("attachment source faces are repeated or unordered")
    changes = {}
    for field in ("faces", "face_normal_bytes", "face_preview_normals", "face_command_offsets",
                  "face_command_opcodes", "face_cache_indices", "face_matrix_indices"):
        values = getattr(geometry, field)
        if values:
            changes[field] = tuple(values[i] for i in indices)
    changes["face_source_indices"] = tuple(geometry.face_source_indices[i] if geometry.face_source_indices else i
                                           for i in indices)
    runs, cursor = [], 0
    for run in geometry.material_runs:
        count = sum(i in selected for i in range(run.first_face, run.first_face + run.face_count))
        runs.append(replace(run, first_face=cursor, face_count=count))
        cursor += count
    return replace(geometry, material_runs=tuple(runs), **changes)


def resolve_draw(draw: dict, snapshot: dict, data: bytes) -> list[dict]:
    """Prove selected ROM lists, captured vertex buffers and matrix palettes."""
    geometry, layout = models.parse_attachment_model(data, models.parse_model_geometry)
    record = draw["record"]
    native_base = int.from_bytes(record[0x24:0x28], "big") - layout["pointer_table_offset"]
    if record[0x14] != len(layout["display_list_pointers"]):
        raise ValueError("attachment runtime part count disagrees with its ROM model")
    start, end = draw["command_buffer_start"], draw["command_buffer_end"]
    memory_at(snapshot["blocks"], start, end - start)
    occurrences = Counter(path[-1] for path in snapshot["origins"])
    if any(occurrences[address] != 1 for address in range(start, end, 8)):
        raise ValueError("attachment renderer range does not execute exactly once")
    if len({p["call_address"] for p in draw["parts"]}) != len(draw["parts"]):
        raise ValueError("attachment selection repeats a call site")
    palettes = {}
    segments = {}
    wanted = {p["call_address"] for p in draw["parts"]}
    for path, (command, argument) in zip(snapshot["origins"], struct.iter_unpack(">II", snapshot["effective"])):
        if command & 0xFFFF0000 == 0xDB060000:
            segments[(command & 0xFFFF) // 4] = argument
        if path[-1] in wanted:
            palettes[path[-1]] = dict(segments)
    result = []
    for selected in draw["parts"]:
        call, target = selected["call_address"], selected["target"]
        if not start <= call < end or memory_at(snapshot["blocks"], call, 8) != struct.pack(">II", 0xDE000000, target):
            raise ValueError("attachment selected call disagrees with its submitted command")
        source_start = target - native_base
        if source_start not in layout["display_list_pointers"]:
            raise ValueError("attachment selected list is absent from the ROM part table")
        part = layout["display_list_pointers"].index(source_start)
        source_end = (layout["display_list_pointers"][part+1] if part+1 < layout["display_list_count"]
                      else geometry.display_list_offset + geometry.display_list_size)
        captured = memory_at(snapshot["blocks"], target, source_end - source_start)
        relocations = []
        runtime_data = bytearray(data)
        normal_hashes = {}
        for offset in range(0, len(captured), 8):
            command, argument = struct.unpack_from(">II", captured, offset)
            source_command, source_argument = struct.unpack_from(">II", data, source_start + offset)
            if command != source_command:
                raise ValueError("attachment display-list opcode differs from its ROM source")
            if command & 0xFFFF0000 == 0xDB060000:
                raise ValueError("attachment part changes its vertex or matrix segment contract")
            if command == 0xDC38000E:
                if argument != native_base + source_argument:
                    raise ValueError("attachment normal pointer relocation changed")
                normal_data = memory_at(snapshot["blocks"], argument, 64)
                runtime_data[source_argument:source_argument + 64] = normal_data
                normal_hashes[source_argument] = hashlib.sha256(normal_data).hexdigest()
            elif argument == source_argument:
                continue
            elif command >> 24 == 0xFD:
                relocations.append({"source_offset": source_start + offset, "flat_index": source_argument & 0x3FFFFF,
                                    "mode": source_argument >> 22, "runtime_pointer": argument})
            else:
                raise ValueError("attachment display-list argument differs from its ROM source")
        segment = palettes.get(call, {})
        vertex_base, matrix_base = segment.get(1), segment.get(3)
        if (vertex_base not in struct.unpack_from(">II", record, 0x28)
                or vertex_base is None or matrix_base is None):
            raise ValueError("attachment submitted vertex buffer or matrix segment is unproven")
        indices = [i for i, offset in enumerate(geometry.face_command_offsets) if source_start <= offset < source_end]
        part_geometry = subset_faces(geometry, indices)
        vertices = list(part_geometry.vertices)
        used = {v for face in part_geometry.faces for v in face}
        attribute_changes = []
        for index in sorted(used):
            raw = memory_at(snapshot["blocks"], vertex_base + index * 16, 16)
            values = struct.unpack(">hhhHhh4B", raw)
            if values[:3] != (vertices[index].x, vertices[index].y, vertices[index].z):
                raise ValueError("attachment captured positions disagree with the ROM source")
            if raw != data[24 + index*16:40 + index*16]:
                attribute_changes.append(index)
            runtime_data[24 + index*16:40 + index*16] = raw
        runtime_geometry, _ = models.parse_attachment_model(bytes(runtime_data), models.parse_model_geometry)
        part_geometry = subset_faces(runtime_geometry, indices)
        matrices, matrix_hashes = {}, {}
        for slot in models.geometry_vertex_matrix_indices(part_geometry):
            raw = memory_at(snapshot["blocks"], matrix_base + slot * 64, 64)
            rows = models.decode_rsp_matrix(raw)["rows"]
            if any(rows[i][3] != float(i == 3) for i in range(4)):
                raise ValueError("attachment captured matrix is not affine")
            matrices[slot] = rows
            matrix_hashes[slot] = hashlib.sha256(raw).hexdigest()
        result.append({"geometry": part_geometry, "matrices": matrices,
            "part": part, "source_first_command": source_start, "source_face_count": len(indices),
            "source_cluster_count": len(models.geometry_clusters(data[source_start:source_end])),
            "call_address": call, "target": target, "vertex_base": vertex_base,
            "used_vertex_count": len(used), "runtime_vertex_attribute_changes": attribute_changes,
            "matrix_base": matrix_base, "matrix_sha256": matrix_hashes, "normal_sha256": normal_hashes,
            "texture_relocations": relocations})
    triangles = sum(1 if command >> 24 == 5 else 2 if command >> 24 == 6
                    else 4 if 0x10 <= command >> 24 <= 0x1F else 0
                    for path, (command, _) in zip(snapshot["origins"], struct.iter_unpack(">II", snapshot["effective"]))
                    if any(start <= location < end for location in path))
    if triangles != sum(part["source_face_count"] for part in result):
        raise ValueError("attachment selected parts do not cover every submitted triangle")
    return result


def merge_posed_gltfs(sources: list[tuple[dict, bytes]], stem: str) -> tuple[dict, bytes]:
    """Join already baked generated glTFs without a material-space conversion."""
    arrays = ("bufferViews", "accessors", "images", "samplers", "textures", "materials", "meshes", "nodes")
    output = {name: [] for name in arrays}
    output.update(asset=copy.deepcopy(sources[0][0]["asset"]), scene=0, scenes=[{"nodes": []}],
                  extras=copy.deepcopy(sources[0][0].get("extras", {})))
    binary, extensions = bytearray(), set()
    for source, raw in sources:
        if (source.get("skins") or source.get("animations") or len(source["buffers"]) != 1
                or source["buffers"][0]["byteLength"] != len(raw)):
            raise ValueError("attachment composition requires baked single-buffer glTF inputs")
        while len(binary) % 4:
            binary.append(0)
        byte_offset = len(binary)
        binary.extend(raw)
        offsets = {key: len(output[key]) for key in arrays}
        for key in arrays:
            for item in source.get(key, []):
                item = copy.deepcopy(item)
                if key == "bufferViews":
                    item["buffer"] = 0
                    item["byteOffset"] = item.get("byteOffset", 0) + byte_offset
                elif key == "accessors":
                    if "sparse" in item:
                        raise ValueError("attachment composition cannot merge sparse accessors")
                    item["bufferView"] += offsets["bufferViews"]
                elif key == "images" and "bufferView" in item:
                    item["bufferView"] += offsets["bufferViews"]
                elif key == "textures":
                    item["source"] += offsets["images"]
                    if "sampler" in item:
                        item["sampler"] += offsets["samplers"]
                elif key == "materials":
                    maps = [item.get(name) for name in ("normalTexture", "occlusionTexture", "emissiveTexture")]
                    pbr = item.get("pbrMetallicRoughness", {})
                    maps += [pbr.get(name) for name in ("baseColorTexture", "metallicRoughnessTexture")]
                    for texture in maps:
                        if texture is not None:
                            texture["index"] += offsets["textures"]
                elif key == "meshes":
                    for primitive in item["primitives"]:
                        if primitive.get("targets"):
                            raise ValueError("attachment composition cannot merge morph targets")
                        primitive["indices"] += offsets["accessors"]
                        primitive["material"] += offsets["materials"]
                        primitive["attributes"] = {name: index + offsets["accessors"]
                                                   for name, index in primitive["attributes"].items()}
                elif key == "nodes":
                    if "mesh" in item:
                        item["mesh"] += offsets["meshes"]
                    if "children" in item:
                        item["children"] = [index + offsets["nodes"] for index in item["children"]]
                output[key].append(item)
        output["scenes"][0]["nodes"].extend(index + offsets["nodes"] for index in source["scenes"][source.get("scene", 0)]["nodes"])
        extensions.update(source.get("extensionsUsed", []))
    output["buffers"] = [{"uri": f"{stem}.bin", "byteLength": len(binary)}]
    if extensions:
        output["extensionsUsed"] = sorted(extensions)
    return output, bytes(binary)


def parent_submission(instance: dict, digest: str, cache: dict) -> dict | None:
    """Reload the graphics task named by every cluster of a body composition."""
    submissions = set()
    for cluster in instance.get("resolved_clusters", []):
        appearances = cluster.get("runtime_appearances", [])
        if len(appearances) != 1 or not appearances[0].get("submitted_graphics"):
            return None
        appearance = appearances[0]
        submissions.add((appearance["draw_trace"], appearance["draw_trace_sha256"],
                         int(appearance["submitted_graphics"]["event_index"])))
    if len(submissions) != 1:
        return None
    trace, expected_hash, index = submissions.pop()
    key = (trace, expected_hash, index)
    if key not in cache:
        path = Path(trace)
        if not path.is_absolute():
            path = models.ROOT / path
        observed_hash, events = read_trace(path, digest, "character-model-draw-ranges")
        if observed_hash != expected_hash or not 0 <= index < len(events):
            raise ValueError("attachment parent submission trace identity changed")
        cache[key] = {"snapshot": graphics_snapshot(events[index]), "trace_sha256": observed_hash,
                      "trace": models.display_path(path), "event_index": index}
    submission = cache[key]
    for matrix in instance.get("runtime_matrices", []):
        if matrix.get("status") != "decoded-affine-components":
            continue
        raw = memory_at(submission["snapshot"]["blocks"], address(matrix["address"]), 64)
        if models.decode_rsp_matrix(raw)["rows"] != matrix["rows"]:
            raise ValueError("attachment parent pose disagrees with its submitted matrices")
    return submission


def attach_composition_previews(
    profile: str, rom_argument: Path | None, digest: str, paths: tuple[Path, ...],
    activity: dict, posed_records: list[dict], output: Path,
    runtime_material_path: Path | None, copied_textures: dict,
) -> dict:
    """Add captured attachment instances to matching ordinary posed bodies."""
    report = {"source_attachment_traces": [], "unresolved_attachments": [],
              "attachment_instance_count": 0, "attachment_part_count": 0,
              "attachment_source_cluster_count": 0,
              "attachment_source_face_count": 0, "attachment_face_count": 0}
    for record in posed_records:
        record["attachment_status"] = "unobserved"
        record["attachments"] = []
    if not paths:
        return report
    _, _, _, bundles, _ = models.load_model_bundles(profile, rom_argument, 9)
    sources = {b.index: b.data for b in bundles if models.is_attachment_model(b.data)}
    instance_key = lambda x: (x["state"], int(x["task_submission_index"]), int(x["slot"]),
                              int(x["entry"]), address(x["root_matrix_address"]))
    instances = {instance_key(x): x for x in activity.get("character_composition_instances", [])}
    cache, parents = {}, []
    for record in posed_records:
        instance = instances.get(instance_key(record))
        if instance is None:
            continue
        submission = parent_submission(instance, digest, cache)
        if submission is not None:
            parents.append((record, instance, submission))
    appearance_lookup = models.load_runtime_material_appearance_lookup(runtime_material_path, digest)
    joined_sources, seen, seen_traces = {}, set(), set()
    for trace_path in paths:
        trace_path = trace_path if trace_path.is_absolute() else models.ROOT / trace_path
        trace_hash, events = read_trace(trace_path, digest, "character-attachment-draw-ranges")
        if trace_hash in seen_traces:
            continue
        seen_traces.add(trace_hash)
        draws, incomplete = attachment_draws(events)
        trace_record = {"file": models.display_path(trace_path), "sha256": trace_hash,
                        "paired_draw_count": len(draws), "incomplete_draws": incomplete}
        report["source_attachment_traces"].append(trace_record)
        snapshots = {}
        for draw in draws:
            entry = draw["record"][1]
            index = draw["submission_event_index"]
            if index not in snapshots:
                snapshots[index] = graphics_snapshot(events[index])
            snapshot = snapshots[index]
            if entry not in sources:
                report["unresolved_attachments"].append({"trace": trace_record["file"], "entry": entry,
                    "record_address": draw["record_address"], "reason": "unsupported-bank09-model-format"})
                continue
            original_parts = resolve_draw(draw, snapshot, sources[entry])
            relative = draw["parent_address"] - CHARACTER_POOL_ADDRESS
            slot = relative // CHARACTER_POOL_RECORD_SIZE
            if relative % CHARACTER_POOL_RECORD_SIZE or not 0 <= slot < CHARACTER_POOL_RECORD_COUNT:
                raise ValueError("attachment parent is outside the character pool")
            parent_entry = draw["parent"][4]
            parent_root = int.from_bytes(draw["parent"][0x1D4:0x1D8], "big")
            matches = [(record, instance, submission) for record, instance, submission in parents
                       if record["slot"] == slot and record["entry"] == parent_entry
                       and address(record["root_matrix_address"]) == parent_root
                       and submission["snapshot"]["root_address"] == snapshot["root_address"]
                       and submission["snapshot"]["root_bytes"] == snapshot["root_bytes"]]
            if len(matches) != 1:
                report["unresolved_attachments"].append({"trace": trace_record["file"], "entry": entry,
                    "record_address": draw["record_address"], "reason": "parent-submission-missing-or-ambiguous"})
                continue
            record, instance, submission = matches[0]
            # Resolve again against the body's task. This makes its captured
            # vertices, normals/material observations and matrices authoritative
            # even when a render-target image changed between the two captures.
            parts = resolve_draw(draw, submission["snapshot"], sources[entry])
            if [p["matrix_sha256"] for p in parts] != [p["matrix_sha256"] for p in original_parts]:
                report["unresolved_attachments"].append({"trace": trace_record["file"], "entry": entry,
                    "record_address": draw["record_address"], "reason": "attachment-matrices-differ-between-submissions"})
                continue
            key = (instance_key(record), draw["record_address"], tuple(p["call_address"] for p in parts))
            if key in seen:
                continue
            seen.add(key)
            root_matrix = memory_at(submission["snapshot"]["blocks"],
                                    parent_root + record["origin_matrix_slot"] * 64, 64)
            origin = models.decode_rsp_matrix(root_matrix)["rows"][3][:3]
            selector = appearance_lookup.get((submission["trace_sha256"], submission["event_index"]))
            gltf_path = models._validated_preview_source(output, record["gltf_file"])
            stem = gltf_path.stem
            group = joined_sources.get(stem)
            if group is None:
                document = json.loads(gltf_path.read_text())
                binary_path = models._validated_preview_source(output, record["gltf_binary_file"])
                group = [(document, binary_path.read_bytes())]
                joined_sources[stem] = group
                record["body_source_face_count"] = record["source_face_count"]
                record["body_face_count"] = record["face_count"]
                record["body_source_cluster_count"] = record.get("source_cluster_count", 0)
            attached = {"bank": 9, "entry": entry, "segment": 0,
                "model_sha1": hashlib.sha1(sources[entry]).hexdigest(),
                "record_address": draw["record_address"], "parent_address": draw["parent_address"],
                "parent_bone": draw["record"][2], "parent_hidden_bone_mask": int.from_bytes(draw["parent"][0x9C:0xA0], "big"),
                "trace": trace_record["file"], "trace_sha256": trace_hash,
                "attachment_submission_event_index": index,
                "material_trace": submission["trace"], "material_trace_sha256": submission["trace_sha256"],
                "material_submission_event_index": submission["event_index"],
                "command_buffer_start": draw["command_buffer_start"], "command_buffer_end": draw["command_buffer_end"],
                "submitted_root_sha256": snapshot["root_sha256"], "parts": []}
            for part in parts:
                geometry = part["geometry"]
                runtime_catalog = (models.load_runtime_material_catalog(runtime_material_path, digest, selector,
                    command_range=(part["call_address"], part["call_address"] + 8)) if selector is not None else {})
                materials, textures, statuses = {}, {}, {}
                for run_index, run in enumerate(geometry.material_runs):
                    if not run.face_count:
                        continue
                    material = runtime_catalog.get((9, entry, 0, run_index))
                    if material is None:
                        statuses[run_index] = "attachment-runtime-material-unobserved"
                        continue
                    if material["model_sha1"] != attached["model_sha1"]:
                        raise ValueError("attachment runtime material model identity changed")
                    materials[run_index] = material
                    models.copy_runtime_captured_auxiliary_textures(material, output)
                    texture = models.runtime_captured_texture_choice(material)
                    if texture is None:
                        statuses[run_index] = "attachment-runtime-texture-unresolved"
                        continue
                    if not run.texture_enabled or not run.texture_coordinates_proven:
                        statuses[run_index] = "attachment-runtime-coordinate-state-unresolved"
                        continue
                    filename = models.preview_texture_filename(texture)
                    destination = output / "textures" / filename
                    destination.parent.mkdir(exist_ok=True)
                    if filename not in copied_textures.values():
                        shutil.copyfile(texture.source, destination)
                        copied_textures[texture] = filename
                    textures[run_index] = f"../textures/{filename}"
                    statuses[run_index] = "submitted-task-captured-texture"
                geometry = models.apply_runtime_texture_coordinates(geometry, materials)
                geometry, source_omitted, _ = models.omit_zero_area_preview_faces(geometry)
                geometry = models.bake_character_runtime_pose(geometry, part["matrices"], origin)
                geometry, pose_omitted, _ = models.omit_zero_area_preview_faces(geometry)
                if geometry.faces:
                    encoded, raw = models.encode_gltf(entry, 0, geometry, textures, bank_index=9,
                        output_stem=f"{stem}-attachment-{draw['record_address']:08x}-part-{part['part']}", runtime_materials=materials)
                    document = json.loads(encoded)
                    document["nodes"][0]["extras"] = {"attachment": {"bank": 9, "entry": entry,
                        "record_address": draw["record_address"], "parent_bone": draw["record"][2], "part": part["part"]}}
                    group.append((document, raw))
                details = {k: v for k, v in part.items() if k not in ("geometry", "matrices")}
                colour_maps = {i: models.runtime_vertex_colour_map(material) for i, material in materials.items()}
                details.update(face_count=len(geometry.faces), source_zero_area_face_count=len(source_omitted),
                    runtime_pose_zero_area_face_count=len(pose_omitted), material_statuses=statuses,
                    linked_texture_run_count=len(textures), linked_texture_face_count=sum(geometry.material_runs[i].face_count for i in textures),
                    captured_colour_face_count=sum(
                        geometry.face_source_indices[i] in colours
                        for run_index, colours in colour_maps.items()
                        for i in range(geometry.material_runs[run_index].first_face,
                                       geometry.material_runs[run_index].first_face + geometry.material_runs[run_index].face_count)))
                attached["parts"].append(details)
                record["source_face_count"] += part["source_face_count"]
                record["face_count"] += len(geometry.faces)
                record["source_cluster_count"] = record.get("source_cluster_count", 0) + part["source_cluster_count"]
                for field, wanted in (("transformed_normal_corner_count", True),
                                      ("geometric_normal_fallback_corner_count", False)):
                    record[field] = record.get(field, 0) + sum((normal is not None) == wanted
                        for face in geometry.face_preview_normals for normal in face)
                record["omitted_zero_area_face_count"] += len(source_omitted) + len(pose_omitted)
                record["source_zero_area_face_count"] += len(source_omitted)
                record["runtime_pose_zero_area_face_count"] += len(pose_omitted)
                record["linked_texture_run_count"] += len(textures)
                record["linked_texture_face_count"] += details["linked_texture_face_count"]
                record["task_local_runtime_material_run_count"] += len(materials)
                report["attachment_part_count"] += 1
                report["attachment_source_cluster_count"] += part["source_cluster_count"]
                report["attachment_source_face_count"] += part["source_face_count"]
                report["attachment_face_count"] += len(geometry.faces)
            record["attachments"].append(attached)
            source = {k: attached[k] for k in ("bank", "entry", "segment", "model_sha1")}
            if source not in record["source_models"]:
                record["source_models"] = [*record["source_models"], source]
            record["attachment_status"] = "captured-parts-assembled-from-matching-submission"
            report["attachment_instance_count"] += 1
    for record in posed_records:
        gltf_path = models._validated_preview_source(output, record["gltf_file"])
        sources = joined_sources.get(gltf_path.stem)
        if sources is None:
            continue
        document, raw = merge_posed_gltfs(sources, gltf_path.stem)
        document["extras"]["attachments"] = record["attachments"]
        triangle_count = sum(document["accessors"][p["indices"]]["count"] // 3
                             for mesh in document["meshes"] for p in mesh["primitives"])
        if triangle_count != record["face_count"]:
            raise ValueError("composed attachment triangle count changed")
        gltf_path.write_text(json.dumps(document, indent=2) + "\n")
        models._validated_preview_source(output, record["gltf_binary_file"]).write_bytes(raw)
    return report
