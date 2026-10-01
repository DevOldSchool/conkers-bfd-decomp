"""Fixed captured SHC boat material export, retaining native geometry."""
from __future__ import annotations

import argparse
from dataclasses import asdict, replace
import hashlib
import json
from pathlib import Path

from scripts import model_assets as models, model_validation

ROOT = Path(__file__).resolve().parents[1]
PRESET = "shc-boat-captured-parent42"
CONTRACT_PATH = ROOT / "config/model-shc-boat-captured-appearance.json"
CONTRACT_SHA256 = "ab58986d62efdb3f2ac708c797da78e5688fab032a66fc263f805d9860bca556"
SCOPE = (
    "Fixed captured SHC boat attachment 47 on Soldier 88 actor 42, source part 0. "
    "Runs 2/3 use proven flat 4195 CI8/RGBA16 at 32x32; the first 28 faces retain "
    "flats 4198/4216. All 50 source vertices/UVs and 36 faces are retained. "
    "The attachment has zero source joints; the required parent transform is not baked. "
    "Animation 24/action 74 activation remains unobserved; no universal Soldier default is inferred. "
    "The preserved draw proof accepts draws 0/2 and excludes draw 1. No local capture "
    "replay, captured parent pose, animation timeline, native lighting, or hardware "
    "raster parity is claimed."
)


def _require(condition, message):
    if not condition:
        raise ValueError("SHC boat " + message)


def _json_bytes(value):
    return (json.dumps(value, indent=2) + "\n").encode()


def contract():
    raw = CONTRACT_PATH.read_bytes()
    _require(hashlib.sha256(raw).hexdigest() == CONTRACT_SHA256, "contract changed")
    return json.loads(raw)


def guard_context(evidence, *, preset=PRESET, bank=9, entry=47, part=0):
    _require(evidence == contract(), "captured evidence changed")
    _require(all(type(value) is int for value in (bank, entry, part))
             and (preset, bank, entry, part) == (PRESET, 9, 47, 0), "appearance context changed")


def checked_model(raw, digest, evidence):
    guard_context(evidence)
    identity = evidence["identity"]
    _require(digest == identity["rom_sha1"], "ROM identity changed")
    _require(len(raw) == identity["model_bytes"]
             and hashlib.sha1(raw).hexdigest() == identity["model_sha1"], "model identity changed")
    geometry, layout = models.parse_attachment_model(raw, models.parse_model_geometry)
    _require((len(geometry.vertices), models.texture_coordinate_count(geometry),
              len(geometry.faces), len(layout["joints"]), layout["display_list_count"])
             == (50, 50, 36, 0, 1), "source geometry/rig changed")
    regions = {section["name"]: raw[section["offset"]:section["offset"] + section["size"]]
               for section in layout["sections"]}
    _require(models.encode_attachment_model(geometry, layout, regions) == raw,
             "native reconstruction changed")
    checked_runs(geometry, evidence)
    return geometry, layout


def checked_runs(geometry, evidence):
    guard_context(evidence)
    _require(len(geometry.material_runs) == 4, "material count changed")
    for index, run in enumerate(geometry.material_runs):
        actual = json.loads(json.dumps(asdict(run)))
        _require(actual == evidence["materials"][index]["source_contract"],
                 f"source material {index} changed")


def map_geometry(geometry, evidence, *, preset=PRESET, bank=9, entry=47, part=0):
    """Change only two inherited bindings; keep cumulative loads and source state."""
    guard_context(evidence, preset=preset, bank=bank, entry=entry, part=part)
    checked_runs(geometry, evidence)
    runs = list(geometry.material_runs)
    for index in (2, 3):
        source = runs[index]
        runs[index] = replace(
            source,
            pixel=replace(source.pixel, flat_index=4195, mode=0, segment=None, offset=None),
            palette=replace(source.palette, flat_index=4195, mode=1, segment=None, offset=None),
        )
        _require(replace(runs[index], pixel=source.pixel, palette=source.palette) == source,
                 "non-binding material state changed")
        state = models.texture_coordinate_state(runs[index])
        _require((state["width"], state["height"], state["format"], state["size"])
                 == (32, 32, 2, 1), "CI8 coordinate state changed")
    mapped = replace(geometry, material_runs=tuple(runs))
    _require(replace(mapped, material_runs=geometry.material_runs) == geometry,
             "non-material source geometry changed")
    return mapped


def checked_flat(payload, evidence):
    guard_context(evidence)
    flat = evidence["flat4195"]
    _require(len(payload) == flat["decoded_bytes"]
             and hashlib.sha256(payload).hexdigest() == flat["decoded_sha256"],
             "flat4195 identity changed")
    for name in ("pixels", "palette"):
        span = flat[name]
        start = int(span["decoded_offset"], 16)
        _require(hashlib.sha256(payload[start:start + span["bytes"]]).hexdigest() == span["sha256"],
                 f"flat4195 {name} changed")


def decode_textures(mapped, payloads, evidence):
    checked_flat(payloads.get(4195, b""), evidence)
    textures = []
    for index, run in enumerate(mapped.material_runs):
        texture, status = models.choose_preview_texture(run, {}, payloads)
        expected = evidence["materials"][index]
        _require(texture is not None and texture.png_data is not None
                 and texture.sha1 == expected["decoded_png_sha1"]
                 and hashlib.sha1(texture.png_data).hexdigest() == expected["decoded_png_sha1"]
                 and (texture.width, texture.height) == (expected["captured_texture"]["width"],
                                                        expected["captured_texture"]["height"]),
                 f"run {index} captured PNG changed")
        _require(status == expected["decode_status"], f"run {index} decode status changed")
        textures.append(texture)
    return textures


def encode_files(geometry, mapped, layout, textures, evidence, *, raw, digest):
    """Recheck the native source before emitting its identity or preservation claims."""
    _require(checked_model(raw, digest, evidence) == (geometry, layout),
             "encoded geometry/layout differs from verified source")
    checked_runs(geometry, evidence)
    _require(map_geometry(geometry, evidence) == mapped, "mapped geometry changed")
    _require((len(geometry.vertices), models.texture_coordinate_count(geometry), len(geometry.faces))
             == (50, 50, 36), "source geometry counts changed")
    _require(layout["joints"] == [], "attachment rig changed")
    _require(len(textures) == 4, "texture inventory changed")
    files, texture_files, mtl_files, records = {}, {}, {}, []
    for index, (run, texture) in enumerate(zip(mapped.material_runs, textures)):
        expected = evidence["materials"][index]
        _require(texture.png_data is not None
                 and hashlib.sha1(texture.png_data).hexdigest() == expected["decoded_png_sha1"],
                 f"run {index} encoded texture changed")
        name = "textures/" + models.preview_texture_filename(texture)
        files[name] = texture.png_data
        texture_files[index] = "../" + name
        mtl_files[models.material_name(run)] = "../" + name
        records.append({"material_run": index, "face_count": run.face_count,
                        "source_face_count": run.face_count, "omitted_zero_area_face_count": 0,
                        "runtime_material": None, "texture": {"file": name,
                        "flat_index": texture.flat_index, "width": texture.width,
                        "height": texture.height, "png_sha1": texture.sha1}})
    _require(len(records) == 4, "texture inventory changed")
    gltf, binary = models.encode_gltf(47, 0, mapped, texture_files=texture_files,
                                     bank_index=9, character_joints=())
    baseline_gltf, baseline_binary = models.encode_gltf(47, 0, geometry, bank_index=9,
                                                       character_joints=())
    _require(binary == baseline_binary, "source geometry binary changed")
    document, baseline = json.loads(gltf), json.loads(baseline_gltf)
    for key in ("meshes", "nodes", "skins", "accessors", "bufferViews", "buffers", "animations"):
        _require(document.get(key) == baseline.get(key), f"source {key} changed")
    _require(not document.get("skins") and not document.get("animations"), "invented rig/animation")
    capture = {"preset": PRESET, "scope": SCOPE, "contract_sha256": CONTRACT_SHA256,
               "capture_replayed_locally": False, "parent_transform_baked": False,
               "source_joint_count": 0, "animation24_action74_activation": "unobserved",
               "provenance": evidence["provenance"]}
    document.setdefault("extras", {})["capturedBoatAppearance"] = capture
    for material in document["materials"]:
        index = material["extras"]["materialRun"]
        captured = evidence["materials"][index]
        # The inherited captured mode is separate from the unchanged source run.
        _require(captured["other_mode_decoded"]["gltf_alpha_mode"] == "OPAQUE",
                 "captured opacity changed")
        material["alphaMode"] = "OPAQUE"
        material.pop("alphaCutoff", None)
        material["extras"]["capturedBoatMaterial"] = {
            "other_mode_words": captured["other_mode_words"],
            "combine_words": captured["combine_words"],
            "colours": captured["captured_colours"],
            "native_lighting_and_raster_parity": "unverified",
        }
    # Captured tile mode uses bilinear sampling, with no distance-dependent mip claim.
    for sampler in document["samplers"]:
        sampler.update(magFilter=9729, minFilter=9729)
    files.update({"geometry/0047-00.gltf": _json_bytes(document),
                  "geometry/0047-00.bin": binary,
                  "geometry/0047-00.obj": models.encode_obj(47, 0, mapped, 9),
                  "geometry/0047-00.mtl": models.encode_mtl(47, 0, mapped, mtl_files, 9)})
    manifest = {"family": "explicit-captured-attachment-appearance", "preset": PRESET,
                "reconstruction": evidence["reconstruction"], "scope": SCOPE,
                "rom_sha1": evidence["identity"]["rom_sha1"], "bank_index": 9,
                "contract_sha256": CONTRACT_SHA256, "capture_replayed_locally": False,
                "capture_evidence": evidence, "model_count": 1, "linked_face_count": 36,
                "newly_linked_face_count": 8, "linked_material_run_count": 4,
                "full_source_geometry_preserved": True,
                "models": [{"entry": 47, "segment": 0, "source_sha1": evidence["identity"]["model_sha1"],
                            "vertex_count": 50, "texture_coordinate_count": 50,
                            "source_face_count": 36, "face_count": 36, "joint_count": 0,
                            "omitted_zero_area_face_count": 0, "animation_clip_count": 0,
                            "animation_frame_count": 0, "parent_transform_baked": False,
                            "parent_transform_status": evidence["context"]["parent_transform"],
                            "native_round_trip_verified": True, "material_runs": records,
                            "gltf_file": "geometry/0047-00.gltf",
                            "gltf_binary_file": "geometry/0047-00.bin",
                            "object_file": "geometry/0047-00.obj",
                            "material_file": "geometry/0047-00.mtl"}]}
    files["manifest.json"] = _json_bytes(manifest)
    files["README.txt"] = (SCOPE + "\n").encode()
    return files, manifest


def build_files(rom, texture_root=None):
    """Load only authorized US inputs; decode textures directly from guarded ROM flats."""
    evidence = contract()
    path, _ = models.resolve_rom("us", rom)
    normalized, _ = models.normalize_rom(path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    _require(digest == evidence["identity"]["rom_sha1"], "ROM identity changed")
    flat = evidence["flat4195"]
    start, end = (int(flat[key], 16) for key in ("compressed_rom_start", "compressed_rom_end"))
    _require(hashlib.sha256(normalized[start:end]).hexdigest() == flat["compressed_sha256"],
             "compressed flat4195 changed")
    _, _, other_digest, bundles, _ = models.load_model_bundles("us", rom, 9)
    _require(digest == other_digest, "ROM changed during extraction")
    selected = [bundle for bundle in bundles if bundle.index == 47]
    _require(len(selected) == 1 and len(selected[0].segments) == 1
             and selected[0].segments[0].index == 0, "attachment part inventory changed")
    raw = selected[0].segments[0].data
    geometry, layout = checked_model(raw, digest, evidence)
    mapped = map_geometry(geometry, evidence)
    payloads = models.load_flat_asset_payloads("us", rom, digest)
    textures = decode_textures(mapped, payloads, evidence)
    files, manifest = encode_files(geometry, mapped, layout, textures, evidence,
                                   raw=raw, digest=digest)
    return files, geometry, layout, manifest


def verify_files(output, files, geometry, layout, manifest):
    output = Path(output).resolve()
    for name, expected in files.items():
        path = output / name
        _require(path.resolve().is_relative_to(output) and path.is_file()
                 and path.read_bytes() == expected, "output changed: " + name)
    record = manifest["models"][0]
    document = json.loads((output / record["gltf_file"]).read_text())
    _require(layout["joints"] == [] and not document.get("skins")
             and not document.get("animations"), "output rig/animation changed")
    return model_validation.compare_geometry(output / record["gltf_file"], geometry, (),
                                             record["material_runs"])


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--preset", required=True, choices=[PRESET])
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--textures", type=Path, help="accepted for appearance CLI compatibility")
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--verify", action="store_true")
    args = parser.parse_args(argv)
    output, build = args.output.resolve(), (ROOT / "build").resolve()
    _require(output != build and output.is_relative_to(build), "output must be a child of build/")
    files, geometry, layout, manifest = build_files(args.rom, args.textures)
    if not args.verify:
        output.mkdir(parents=True, exist_ok=False)
        for name, data in files.items():
            destination = output / name
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_bytes(data)
    report = verify_files(output, files, geometry, layout, manifest)
    print(f"Verified captured boat attachment 47: {report['faces']} source faces, 8 newly textured faces; zero source joints")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
