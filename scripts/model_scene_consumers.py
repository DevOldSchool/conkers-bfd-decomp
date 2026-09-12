"""Recover scene/model edges from the reviewed US loader and consumers."""

from __future__ import annotations

import hashlib
import json
from collections import Counter
from pathlib import Path

try:
    from scripts import model_assets as models
    from scripts.model_coverage import placement_associations
except ModuleNotFoundError:
    import model_assets as models
    from model_coverage import placement_associations


def initial_slot_record(entry: int, segment: models.ModelSegment) -> dict:
    if segment.index not in range(4) or not segment.data:
        raise ValueError("initial scene slot requires a nonempty segment in slots 0..3")
    geometry = models.parse_model_geometry(segment.data)
    slot = segment.index
    return {
        "bank": 4, "entry": entry, "segment": slot,
        "model_sha1": hashlib.sha1(segment.data).hexdigest(),
        "source_face_count": len(geometry.faces),
        "display_list": {"model_offset": geometry.display_list_offset,
                         "size": geometry.display_list_size,
                         "runtime_storage": f"0x{0x800B0E00 + slot * 4:08X}"},
        "vertices": {"model_offset": 0x28, "count": len(geometry.vertices),
                     "runtime_storage": f"0x{0x800B0E10 + slot * 4:08X}"},
        "secondary_region": None if geometry.secondary_region is None else {
            "model_offset": geometry.secondary_region.offset,
            "size": geometry.secondary_region.size,
            "runtime_storage": f"0x{0x800B0E20 + slot * 4:08X}",
            "consumer_status": "unresolved",
        },
        "consumers": ([{"function": "func_1510B9D0", "kind": "conditional-display-list-submission"}]
                      if slot < 3 else []) +
                     ([{"function": "func_15003668", "kind": "collision-input", "collision_array": 0 if slot == 0 else 1}]
                      if slot in (0, 3) else []),
        "runtime_draw_status": "not-established-by-static-consumer-edge",
    }


def build_scene_graph(bundles: list[models.ModelBundle], placements: dict) -> tuple[list[dict], list[dict]]:
    if any(bundle.index not in range(0x45) for bundle in bundles) or any(
        scene["scene_index"] not in range(0x45) for scene in placements["scenes"]
    ):
        raise ValueError("scene source index exceeds reviewed loader domain")
    associations = placement_associations(placements)
    tables = {(scene["bank_index"], scene["scene_index"]): scene for scene in placements["scenes"]}
    bundle_map = {bundle.index: bundle for bundle in bundles}
    scenes = []
    for scene_index in range(0x45):
        bundle = bundle_map.get(scene_index)
        slots = [] if bundle is None else [initial_slot_record(scene_index, segment)
                 for segment in bundle.segments if segment.index < 4 and segment.data]
        for slot in slots:
            associations[(4, scene_index, slot["segment"])].append({
                "kind": "initial-scene-slot", "scene_index": scene_index,
                "source_bank": 4, "slot": slot["segment"], "consumer": "func_150031EC",
                "display_list_storage": slot["display_list"]["runtime_storage"],
                "downstream_consumers": slot["consumers"],
            })
        placement_tables = [tables[(bank, scene_index)] for bank in models.PLACEMENT_BANKS
                            if (bank, scene_index) in tables]
        scenes.append({
            "scene_index": scene_index,
            "bank_04_status": "available" if bundle else "absent",
            "initial_slots": slots,
            "placement_tables": placement_tables,
            "render_order_status": "conditional-runtime-order-unresolved",
            "room_graph_status": "portals-lights-fog-cameras-triggers-unresolved",
        })
    return scenes, [{"bank": key[0], "entry": key[1], "segment": key[2], "associations": value}
                    for key, value in sorted(associations.items())]


def extract_scene_consumers(profile: str, rom: Path | None, output: Path) -> dict:
    rom_path, _, digest, bundles, _ = models.load_model_bundles(profile, rom, 4)
    placements, _ = models.load_object_placement_manifest(profile, rom, include_files=False)
    _, layout = models.resolve_rom(profile, rom)
    normalized, _ = models.normalize_rom(rom_path.read_bytes())
    if hashlib.sha1(normalized).hexdigest() != digest:
        raise ValueError("ROM changed during scene consumer extraction")
    game = models.parse_game_archive(normalized[layout["game_start"]:layout["game_end"]])
    # Hash the complete reviewed functions, including branches and delay slots;
    # consumer meaning comes from review, not a nearby matching instruction.
    spans = {"func_150031EC": (0x31EC, 0x34B4),
             "func_1510B9D0": (0x10B9D0, 0x10BF60),
             "func_15003668": (0x3668, 0x39BC)}
    scenes, associations = build_scene_graph(bundles, placements)
    slots = [slot for scene in scenes for slot in scene["initial_slots"]]
    manifest = {
        "schema_version": 1, "family": "model-scene-consumers", "profile": profile,
        "normalized_sha1": digest,
        "evidence": {
            "kind": "reviewed-static-us-consumer-chain",
            "reference": "docs/evidence/us_model_scene_consumers.md",
            "code_sha256": {name: hashlib.sha256(game.code[start:end]).hexdigest()
                            for name, (start, end) in spans.items()},
            "loader": "func_150031EC", "bank_path": [4, "scene-index"],
            "descriptor_stride": 8, "initial_slot_count": 4,
            "out_of_range_rule": "signed input >= 69 selects bank-04 entry 0; negative inputs are not clamped",
        },
        "scene_index_count": len(scenes), "available_bank_04_scene_count": len(bundles),
        "initial_slot_model_count": len(slots),
        "initial_slot_source_face_count": sum(slot["source_face_count"] for slot in slots),
        "initial_slot_counts": dict(sorted(Counter(str(slot["segment"]) for slot in slots).items())),
        "render_consumer_model_count": sum(slot["segment"] < 3 for slot in slots),
        "collision_consumer_model_count": sum(slot["segment"] in (0, 3) for slot in slots),
        "resolved_placement_count": placements["record_count"] - placements["unresolved_bank_11_record_count"],
        "unresolved_placements": placements["unresolved_bank_11_dispatch_references"],
        "model_association_count": len(associations), "model_associations": associations,
        "scenes": scenes,
        "limitations": [
            "This is a consumer graph, not an observed frame or complete room graph.",
            "Slot 3 has collision evidence only here; do not add it to visible scene geometry.",
            "Slots 0..2 reach conditional renderer paths; loading does not prove a draw in every state.",
            "Scene secondary regions retain exact offsets without invented portal or light semantics.",
            "Missing bank-04 scenes and unreferenced models are retained; no replacement model is inferred.",
        ],
    }
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = output.with_suffix(output.suffix + ".tmp")
    temporary.write_text(json.dumps(manifest, indent=2) + "\n")
    temporary.replace(output)
    return manifest
