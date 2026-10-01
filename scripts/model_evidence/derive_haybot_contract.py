"""Derive Haybot ROM evidence, optionally binding the authenticated capture audit.

The full contract requires the exact independently reviewed capture-audit file.
A newly generated portable report is a separate check, not a substitute.
"""
import argparse
import copy
from dataclasses import asdict
import hashlib
import json
from pathlib import Path
from .common import encoded, require, validate_paths as validate_file_paths, write_new

PACKET_SHA256 = "254846215d32ece3913f2adcb8bef94909f1492fbc95b0d70e11d16f0c16615d"
TRACE_SHA256 = "cceab5ea38d772293946612d3958d2621a3036b841d0185546e4d9fa78e3ab1e"
CAPTURE_AUDIT_SHA256 = "99e3b3f1b3eab6b7834718e7007ceff69a987147d2531e9513db7f6aac8ce382"
UPDATER_SHA1 = "25d117471183b27fc8cda611ef624343a0d1f559"


def validate_paths(args):
    require((args.capture_audit is None) == (args.output is None),
            "capture audit and output must be supplied together")
    validate_file_paths(args, ("rom", "packet", "capture_audit"), ("rom_report", "output"))


def checked_capture_audit(path):
    raw = path.read_bytes()
    require(hashlib.sha256(raw).hexdigest() == CAPTURE_AUDIT_SHA256,
            "independently reviewed capture audit changed")
    capture = json.loads(raw)
    require(capture.get("passed") is True, "capture audit did not pass")
    require(capture.get("checks") and all(value is True for value in capture["checks"].values()),
            "capture audit has incomplete checks")
    inputs = capture.get("inputs", [])
    require(any(item.get("sha256") == TRACE_SHA256 for item in inputs),
            "capture audit lacks the pinned trace")
    require(any(item.get("sha256") == PACKET_SHA256 for item in inputs),
            "capture audit lacks the pinned packet")
    return raw


def audit_rom(packet, rom_path):
    """Check source/texture/animation evidence against a normalized US ROM.

    Callers must authenticate the packet before using this result as a contract.
    This function does not validate raw captured bytes or assert native rendering.
    """
    from scripts import model_assets as models, model_character_parts as parts

    rom_path, rom_layout = models.resolve_rom("us", rom_path)
    rom, _ = models.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    require(digest == packet["identity"]["rom_sha1"] == "4cbadd3c4e0729dec46af64ad018050eada4f47a", "US ROM identity changed")
    _, _, bundle_digest, bundles, tables = models.load_model_bundles("us", rom_path, 1)
    require(bundle_digest == digest, "ROM changed during source loading")
    raw = next(item for item in bundles if item.index == 75).segments[0].data
    require(len(raw) == packet["identity"]["source_bytes"] == 42488, "source model size changed")
    require(hashlib.sha256(raw).hexdigest() == packet["identity"]["source_sha256"], "source model hash changed")
    geometry, layout = models.parse_character_model_geometry(raw)
    require((len(geometry.vertices), len(geometry.faces), models.texture_coordinate_count(geometry), len(layout["joints"]))
            == (1625, 1226, 1625, 45), "full source geometry/rig changed")
    require(layout["procedural_animation_joint_indices"] == [20, None], "procedural joints changed")
    for name, offset, size, expected in packet["geometry"]["sections"]:
        start = int(offset, 16)
        require(hashlib.sha1(raw[start:start + size]).hexdigest() == expected, "source section changed: " + name)
    primary, draw = parts.primary_preview(raw, geometry, layout)
    require(primary == geometry and draw is None, "full-primary source geometry changed")
    actual = json.loads(json.dumps(asdict(geometry.material_runs[16])))
    run_digest = hashlib.sha256(json.dumps(actual, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
    expected_run = packet["run16"]
    for key, value in expected_run.items():
        if not key.startswith("load_history"):
            require(actual[key] == value, "packet run16 field changed: " + key)
    shared = expected_run["load_history_shared"]
    loads = []
    for i, (flat, mode, segment, offset, second) in enumerate(expected_run["load_history"]):
        pixel = i % 2 == 0
        loads.append([dict(image_command=shared["image_command"], flat_index=flat, mode=mode,
                           segment=segment, offset=offset, external=False,
                           load_command=[shared["pixel_load_first" if pixel else "palette_load_first"], second]),
                      shared["pixel_tile" if pixel else "palette_tile"]])
    require(actual["texture_loads"] == loads, "complete packet load history changed")
    offsets = geometry.face_command_offsets[368:392]
    require(list(dict.fromkeys(offsets)) == packet["source_triangle_offsets"], "source triangle offsets changed")
    require(all(offsets.count(offset) == 4 for offset in packet["source_triangle_offsets"]), "source command triangle multiplicity changed")
    require(hashlib.sha256(b"".join(raw[offset:offset + 8] for offset in packet["source_triangle_offsets"])).hexdigest()
            == "18449082404fb1f83ad6847586ac582e445b3908f879aba509a95f251b80e7c8", "captured/source triangle commands differ")

    payloads = models.load_flat_asset_payloads("us", rom_path, digest)
    data = payloads[3823]
    require(len(data) == 2080 and hashlib.sha256(data).hexdigest() == packet["flat3823"]["sha256"], "flat3823 identity changed")
    for key in ("pixel", "palette"):
        start, size, expected = packet["flat3823"][key]
        require(hashlib.sha256(data[start:start + size]).hexdigest() == expected, "flat3823 " + key + " span changed")
    start, end = (int(value, 16) for value in packet["flat3823"]["compressed_rom_range"])
    require(hashlib.sha256(rom[start:end]).hexdigest() == packet["flat3823"]["compressed_sha256"], "compressed texture source changed")
    rows = bytes(data[y * 32 + (x ^ (4 if y & 1 else 0))] for y in range(64) for x in range(32))
    png = models.encode_indexed_png(rows + data[2048:], "linear", 64, 64)
    require(hashlib.sha256(png).hexdigest() == packet["flat3823"]["png_sha256"], "decoded PNG changed")
    rgba = bytearray()
    for y in range(63, -1, -1):
        for x in range(64):
            packed = data[y * 32 + ((x // 2) ^ (4 if y % 2 else 0))]
            index = (packed >> (4 if x % 2 == 0 else 0)) & 15
            word = int.from_bytes(data[2048 + index * 2:2050 + index * 2], "big")
            rgba.extend(((word >> 11 & 31) * 255 // 31, (word >> 6 & 31) * 255 // 31,
                         (word >> 1 & 31) * 255 // 31, 255 if word & 1 else 0))
    rgba_digest = hashlib.sha256(rgba).hexdigest()
    require(rgba_digest == packet["flat3823"]["rgba_sha256"] and set(rgba[3::4]) == {255}, "independent scalar RGBA mismatch")
    require(layout["texture_descriptors"][15] == dict(record_index=15, runtime_pointer_slot_initial_value=3823,
            flat_index=3823, width=64, height=64), "descriptor15 binding changed")
    require(layout["texture_descriptors"][0]["flat_index"] == 3839 and len(payloads[3839]) == 1888, "initializer binding changed")
    game = models.parse_game_archive(rom[rom_layout["game_start"]:rom_layout["game_end"]])
    start = 0x15061FA8 - rom_layout["game_vram"]
    require(hashlib.sha1(game.code[start:start + 0xE4]).hexdigest() == UPDATER_SHA1, "native updater source changed")
    animation_manifest, animation_files = models.load_character_animation_manifest("us", rom_path, include_files=True)
    companion = next(item for item in animation_manifest["entries"] if item["bank_entry"] == 75)
    require(tuple(companion[key] for key in ("decoded_size", "decoded_sha1", "logical_animation_route_count", "clip_pair_count"))
            == (21736, "83fb569f9ca8c7eeec4fe22f808ae7d656b31827", 20, 15), "animation companion changed")
    clips, incompatible = models.character_animation_clips_for_model(75, 45, animation_manifest, animation_files)
    require([len(clip.frames) for clip in clips] == packet["geometry"]["clip_frame_counts"]
            == [13,13,19,14,9,9,48,13,12,20,19,5,21,64,12], "stored clip frame inventory changed")
    require([clip.pair_index for clip in clips] == list(range(15)) and incompatible == 0, "stored clip pair inventory changed")
    _, omitted, by_run = models.omit_zero_area_preview_faces(geometry)
    require(tuple(omitted) == (345,) and by_run[13] == 1, "ordinary omitted face changed")
    defaults = models.model_character_defaults.preview_defaults(models.load_character_defaults("us", rom_path, digest), 75)
    texture, status, _ = models.rom_default_preview_texture(geometry.material_runs[16], defaults, layout["texture_descriptors"], payloads, tables)
    require(texture is None and status == "rom-default-payload-span-unresolved", "initializer material frontier changed")

    report = {
        "schema": "haybot-rom-audit-v1", "passed": True,
        "packet_sha256": PACKET_SHA256, "rom_sha1": digest,
        "source_sha256": hashlib.sha256(raw).hexdigest(), "source_bytes": len(raw),
        "source_run_sha256": run_digest, "source_section_checks": len(packet["geometry"]["sections"]),
        "full_source": {"vertices": 1625, "faces": 1226, "uvs": 1625, "joints": 45,
                        "procedural_joints": [20, None], "ordinary_omitted_face": 345},
        "animation": {"clips": 15, "frames": 291, "logical_routes": 20,
                      "frame_counts": [len(clip.frames) for clip in clips], "incompatible": incompatible},
        "texture": {"flat": 3823, "bytes": len(data), "independently_decoded_texels": 4096,
                    "png_sha256": hashlib.sha256(png).hexdigest(), "rgba_sha256": rgba_digest, "alpha_values": [255]},
        "updater_sha1": UPDATER_SHA1, "baseline_run16_status": status,
        "limits": ["ROM parsing and packet comparison, not native rendering or captured pose reproduction."],
    }
    return report


def build_contract(packet, report):
    """Format checked evidence; authentication must precede this operation."""
    report_bytes = encoded(report)
    evidence = copy.deepcopy(packet)
    evidence["preset"] = "haybot-captured-selector15"
    evidence["context"].pop("timestamp", None)
    evidence["context"]["core"] = "Mupen64Plus2.5.9"
    evidence["source_run_sha256"] = report["source_run_sha256"]
    evidence["selector_evidence"] = {
        "scope": "Fixed preserved selector 15/phase 5 only; no phase cycle or playback timeline is inferred here.",
        "actor_field": "0x68", "captured_selector": 15, "captured_phase": 5,
        "updater_range": ["15061FA8", "1506208C"], "updater_sha1": UPDATER_SHA1,
    }
    evidence["reconstruction"] = {
        "schema": "haybot-captured-appearance-v1",
        "classification": "Derived from captured renderer evidence and the authenticated US ROM.",
        "preserved_packet_sha256": PACKET_SHA256, "preserved_trace_sha256": TRACE_SHA256,
        "rom_audit_sha256": hashlib.sha256(report_bytes).hexdigest(),
        "capture_audit_sha256": CAPTURE_AUDIT_SHA256,
        "scene_identification": "Scene 16 is identified by preserved stage1 save metadata; its scene scalar was not independently redecoded.",
        "submission_scope": "Two unchanged, single-occurrence captured renderer command ranges; 868 selected triangles and 24 target run 16 triangles each. No new native execution or framebuffer replay.",
        "matrix_qualification": "For each of the two submissions, all 35 segment-3 character matrices equal nearest signed 16.16 conversion of return float32 affine matrices, round(f32 * 65536), with unused fourth column canonicalized to (0,0,0,1). Maximum decoded absolute error is 7.62939453125e-06, half a 16.16 unit. Raw bytes differ by representation. Non-segment-3 address 0x800C3E98 is excluded.",
        "output_scope": "All 1226 ROM source faces, 1625 vertices/UVs, 45 joints and 15 clips/291 frames; only run 16 receives the captured selector 15 texture. Captured pose, visibility, playback timing and native framebuffer equivalence are not reproduced.",
    }
    return evidence


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--packet", type=Path, required=True)
    parser.add_argument("--rom-report", type=Path, required=True)
    parser.add_argument("--capture-audit", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args(argv)
    validate_paths(args)
    if args.capture_audit is not None:
        checked_capture_audit(args.capture_audit)
    packet_bytes = args.packet.read_bytes()
    require(hashlib.sha256(packet_bytes).hexdigest() == PACKET_SHA256, "preserved packet bytes changed")
    packet = json.loads(packet_bytes)
    require(packet["identity"]["trace_sha256"] == TRACE_SHA256, "packet names another trace")
    report = audit_rom(packet, args.rom)
    report_bytes = encoded(report)
    write_new(args.rom_report, report_bytes)
    if args.output is not None:
        evidence = build_contract(packet, report)
        output = encoded(evidence)
        write_new(args.output, output)
        print(json.dumps({"contract_sha256": hashlib.sha256(output).hexdigest(), "contract_bytes": len(output),
                          "rom_audit_sha256": hashlib.sha256(report_bytes).hexdigest()}))
    else:
        print(json.dumps({"rom_audit_sha256": hashlib.sha256(report_bytes).hexdigest(), "passed": True}))


if __name__ == "__main__":
    main()
