"""Conservative, direct-display-list CI8 texture contracts for the US ROM."""

from __future__ import annotations

import hashlib
import json
from collections import Counter, defaultdict
from pathlib import Path

try:
    from scripts import texture_assets as t
except ModuleNotFoundError:
    import texture_assets as t


FAMILY = t.CI8_FAMILY
FAMILY_NAME = t.CI8_FAMILY_NAME

# The direct display-list contract proves the rendered tile bounds and palette
# storage, but it does not always prove the source image's row geometry. Keep
# human-reviewed exceptions explicit rather than selecting them from an
# image-content score. These payloads form continuous images when the
# command-derived width and height are transposed while retaining the normal
# TMEM odd-row conversion. In particular, the 64x32 interpretation of 3091
# creates a false split that looks like two eyes; 32x64 reconstructs one eye.
TRANSPOSED_PREVIEW_INDICES = frozenset({
    1773, 1786, 1787, 1830, 1878, 1929, 1931, 2274, 2396,
    2672, 2736, 2738, 2759, 2801, 2803, 2817, 2867, 2964, 2972,
    2989, 3056, 3061, 3074, 3091, 3308, 3458, 3505, 3527, 3561,
    3574, 3670, 3700, 3715, 3766, 3896, 3930, 3931, 4004, 4088,
    4114, 4137, 4324, 4325, 4340, 4376, 4393, 4395, 4398, 4574,
    4575,
    4638, 4647, 4662, 4672, 4810, 7269,
})

CUSTOM_PREVIEW_GEOMETRY = {
    2376: (16, 128),
}

UNRESOLVED_PREVIEW_INDICES = frozenset({2795, 3560, 4423})

# A hardware watchpoint on D_800B0E58[3358] captured the real loader write at
# guest PC 0x1510D2E8. The caller returned to func_1510CE60 at 0x1510CF54 with
# a null fifth argument, so the mode-one FD10 reference remained at the payload
# base instead of being rebased to payload_end - 0x200. That makes the first
# 512 bytes both CI8 indices and the TLUT, and leaves the final 512 bytes outside
# the reversible pixels-plus-trailing-palette contract used by this extractor.
# Keep the runtime-incompatible record in survey evidence, but do not emit a
# misleading standalone PNG for it.
RUNTIME_INCOMPATIBLE_INDICES = frozenset({3358})
RUNTIME_CONSUMER_EVIDENCE = {
    3358: {
        "status": "excluded-runtime-base-palette-overlaps-pixels",
        "cache_slot_physical": "0x000B42D0",
        "loaded_pointer": "0x80134040",
        "guest_pc_after_cache_store": "0x1510D2E8",
        "parser_return_address": "0x1510CF54",
        "parser_fifth_argument": 0,
        "palette_offset": 0,
        "pixel_palette_overlap_bytes": 512,
    }
}


def preview_contract(
    flat_index: int, render_width: int, render_height: int
) -> tuple[int, int, str, str, str]:
    if flat_index in UNRESOLVED_PREVIEW_INDICES:
        return (
            render_width,
            render_height,
            t.ROW_LAYOUT_TMEM,
            "manual-review-no-supported-reversible-transform",
            "manual-review-unresolved",
        )
    if flat_index in CUSTOM_PREVIEW_GEOMETRY:
        width, height = CUSTOM_PREVIEW_GEOMETRY[flat_index]
        if width * height != render_width * render_height:
            raise ValueError(
                f"CI8 texture {flat_index} preview geometry changes the pixel count"
            )
        return (
            width,
            height,
            t.ROW_LAYOUT_TMEM,
            "manual-review-explicit-preview-geometry",
            "manual-review-preview-geometry",
        )
    if flat_index not in TRANSPOSED_PREVIEW_INDICES:
        return (
            render_width,
            render_height,
            t.ROW_LAYOUT_TMEM,
            "display-list-render-geometry",
            "runtime-appearance-not-verified",
        )
    return (
        render_height,
        render_width,
        t.ROW_LAYOUT_TMEM,
        "manual-review-transposed-preview-geometry",
        "manual-review-preview-geometry",
    )


def scan_contracts(data: bytes, source: str, sizes: dict[int, int]) -> list[dict]:
    """Require local render stride, tile bounds, load length and full TLUT.

    No backwards tile-state guesses: reused, partial and contradictory loads
    remain survey evidence, not extracted textures. FD500000 loads CI pixels
    as 16-bit texels; the render tile must explicitly switch to CI8.
    """
    records = []
    for offset in range(0, len(data) - 7, 8):
        command, index = t.command_words(data, offset)
        if command != t.DIRECT_TEXTURE_IMAGE or index not in sizes:
            continue
        tile = bounds = loaded = palette = tlut = dxt = None
        for cursor in range(offset + 8, min(len(data) - 7, offset + 0x100), 8):
            command, argument = t.command_words(data, cursor)
            opcode = command >> 24
            if opcode in (0xDE, 0xDF) or (
                opcode == 0xFD and command != t.DIRECT_PALETTE_IMAGE
            ):
                break
            if opcode == 0xF3 and loaded is None:
                loaded = (((argument >> 12) & 0xFFF) + 1) * 2
                dxt = argument & 0xFFF
            if opcode == 0xF5 and (argument >> 24) & 7 == 0 and tile is None:
                tile = command
            if opcode == 0xF2 and (argument >> 24) & 7 == 0 and bounds is None:
                bounds = (command, argument)
            if command == t.DIRECT_PALETTE_IMAGE:
                # Bind the TLUT to this image, not a later palette upload.
                if argument != 0x00400000 | index:
                    break
                palette = argument
            if opcode == 0xF0 and palette is not None:
                tlut = t.tlut_entry_count(command, argument)
                break
        if tile is None or t.tile_format_and_size(tile) != (2, 1):
            continue
        record = {"flat_index": index, "source": source,
                  "offset": f"0x{offset:X}", "tile_command": f"0x{tile:08X}",
                  "loaded_bytes": loaded, "load_dxt": dxt, "palette_entries": tlut}
        reason = None
        if bounds is None or loaded is None or palette is None or tlut != 256:
            reason = "incomplete-local-contract"
        else:
            upper, lower = bounds
            uls, ult = (upper >> 12) & 0xFFF, upper & 0xFFF
            lrs, lrt = (lower >> 12) & 0xFFF, lower & 0xFFF
            width, height = (lrs - uls) // 4 + 1, (lrt - ult) // 4 + 1
            record.update(width=width, height=height,
                          tile_bounds=[f"0x{upper:08X}", f"0x{lower:08X}"])
            if (lrs < uls or lrt < ult or (lrs - uls) % 4 or (lrt - ult) % 4
                    or width != ((tile >> 9) & 0x1FF) * 8 or tile & 0x1FF):
                reason = "noncanonical-tile-bounds-or-stride"
            elif loaded != width * height or loaded > 2048:
                reason = "partial-or-mismatched-load"
            elif dxt != 0:
                reason = "unsupported-load-row-conversion"
            elif sizes[index] != width * height + 512:
                reason = "payload-size-disagrees-with-consumer"
        record["status"] = reason or "proven"
        records.append(record)
    return records


def consistent_contracts(references: list[dict]) -> list[dict]:
    proven = [r for r in references if r["status"] == "proven"]
    dimensions = {(r["width"], r["height"]) for r in proven}
    if len(dimensions) != 1 or any(r["status"] not in
            ("proven", "incomplete-local-contract") for r in references):
        return []
    return proven


def extractable_contracts(flat_index: int, references: list[dict]) -> list[dict]:
    if flat_index in RUNTIME_INCOMPATIBLE_INDICES:
        return []
    return consistent_contracts(references)


def survey(profile: str, rom_argument: Path | None):
    rom_path, layout = t.resolve_rom(profile, rom_argument)
    rom, order = t.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    start, end = layout["flat_assets_start"], layout["flat_assets_end"]
    entries = list(t.iter_flat_rzip_entries(rom[start:end]))
    game = t.parse_game_archive(rom[layout["game_start"]:layout["game_end"]])
    # func_1510CE60: mode bit 0 selects payload_end - 512 for the TLUT.
    for address, instruction in {
        0x1510CF0C: 0x00104D83, 0x1510CF4C: 0x0D44343B,
        0x1510CFBC: 0x31390001, 0x1510CFCC: 0x13200006,
        0x1510CFD4: 0x8FAF0424, 0x1510CFD8: 0x004F7021,
        0x1510CFDC: 0x25C2FE00,
    }.items():
        if t.word_at_vram(game.code, layout["game_vram"], address) != instruction:
            raise ValueError(f"CI8 palette loader signature mismatch at 0x{address:X}")
    sizes = {e.index: len(e.data) for e in entries}
    references = []
    for bank in t.parse_asset_banks(rom, layout["asset_table"]):
        if bank.flags:
            continue
        for entry in t.parse_asset_entries(rom, bank):
            raw = rom[entry.start:entry.end]
            data = t.decode_rzip_chunk(raw).data if entry.compressed else raw
            references.extend(scan_contracts(
                data, f"bank-{bank.index:02X}/{entry.index:04d}", sizes))
    grouped = defaultdict(list)
    for reference in references:
        grouped[reference["flat_index"]].append(reference)
    textures = []
    for index, refs in sorted(grouped.items()):
        proven = extractable_contracts(index, refs)
        if not proven:
            continue
        width, height = proven[0]["width"], proven[0]["height"]
        entry = entries[index]
        preview_width, preview_height, row_layout, evidence, preview_status = (
            preview_contract(index, width, height)
        )
        textures.append({
            "flat_index": index, "width": width, "height": height,
            "preview_width": preview_width, "preview_height": preview_height,
            "rom_start": f"0x{start + entry.start:X}",
            "rom_end": f"0x{start + entry.end:X}",
            "decoded_size": len(entry.data),
            "decoded_sha1": hashlib.sha1(entry.data).hexdigest(),
            "palette_offset": width * height, "palette_size": 512,
            "palette_consumer_status": "runtime-fifth-argument-unverified",
            "row_layout": row_layout,
            "row_layout_evidence": "default-tmem-ready-preview-assumption",
            "preview_geometry_evidence": evidence,
            "references": proven,
            "preview_status": preview_status,
            "file": f"{index:04d}.ci8.png",
        })
    manifest = {
        "schema_version": 6, "family": FAMILY, "profile": profile,
        "source_rom": t.manifest_source(rom_path), "source_byte_order": order,
        "normalized_sha1": digest, "source_origin": t.SOURCE_ORIGIN,
        "png_origin": t.PNG_ORIGIN, "texture_count": len(textures),
        "textures": textures, "reference_count": len(references),
        "referenced_texture_count": len(grouped),
        "excluded_texture_count": len(grouped) - len(textures),
        "excluded_flat_indices": sorted(set(grouped) - {r["flat_index"] for r in textures}),
        "reference_status_counts": dict(Counter(r["status"] for r in references)),
        "survey_references": references,
        "classification": (
            "Direct local CI8 command contracts; ambiguous command contracts excluded, "
            "known runtime-incompatible palette consumers excluded; remaining "
            "runtime palette-consumer arguments not yet verified"
        ),
        "palette_pointer_contract": {
            "parser": "func_1510CE60",
            "mode": 1,
            "palette_offset_from_payload_end": -512,
            "requires_non_null_fifth_argument": True,
            "runtime_consumer_status": "captured-null-for-flat-index-3358",
            "runtime_incompatible_flat_indices": sorted(
                RUNTIME_INCOMPATIBLE_INDICES
            ),
            "runtime_evidence": RUNTIME_CONSUMER_EVIDENCE,
        },
        "visual_validation": {
            "status": "incomplete",
            "note": (
                "Proven describes the local CI8 render dimensions, full load and "
                "same-index 256-entry TLUT command. The parser rebases a mode-1 "
                "pointer to payload_end-512 only when its fifth argument is non-null. "
                "A real load of 3358 used a null fifth argument, making its TLUT "
                "overlap the first 512 pixel bytes, so that index is excluded from "
                "this reversible trailing-palette family. Remaining PNGs default to "
                "the reversible TMEM-ready row interpretation. "
                "Fifty-six indices have explicit human-reviewed transposed preview "
                "geometry, including 3091 where the command-derived 64x32 view "
                "creates a false two-eye split. Index 2376 has a reviewed 16x128 "
                "preview. No automatic image-content heuristic is used. Three reviewed "
                "examples remain unresolved."
            ),
            "preview_geometry_overrides": sorted(
                TRANSPOSED_PREVIEW_INDICES | CUSTOM_PREVIEW_GEOMETRY.keys()
            ),
            "transposed_preview_geometry_overrides": sorted(
                TRANSPOSED_PREVIEW_INDICES
            ),
            "custom_preview_geometry_overrides": {
                str(index): list(dimensions)
                for index, dimensions in sorted(CUSTOM_PREVIEW_GEOMETRY.items())
            },
            "follow_up_examples": sorted(UNRESOLVED_PREVIEW_INDICES),
        },
    }
    return manifest, {e.index: e.data for e in entries}


def extract(profile: str, rom_argument: Path | None, output: Path, force: bool):
    manifest, payloads = survey(profile, rom_argument)
    t.prepare_output(output, force)
    for record in manifest["textures"]:
        payload = payloads[record["flat_index"]]
        width, height = record["preview_width"], record["preview_height"]
        row_layout = record["row_layout"]
        png = t.encode_ci8_png(payload, row_layout, width, height)
        if t.decode_ci8_png(png, row_layout, width, height) != payload:
            raise ValueError(f"CI8 texture {record['flat_index']} did not round-trip")
        (output / record["file"]).write_bytes(png)
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def verify(profile: str, rom_argument: Path | None):
    manifest, payloads = survey(profile, rom_argument)
    size = 0
    for record in manifest["textures"]:
        payload = payloads[record["flat_index"]]
        width, height = record["preview_width"], record["preview_height"]
        row_layout = record["row_layout"]
        rebuilt = t.decode_ci8_png(t.encode_ci8_png(
            payload, row_layout, width, height), row_layout, width, height)
        if rebuilt != payload:
            raise ValueError(f"CI8 texture {record['flat_index']} did not round-trip")
        size += len(payload)
    return manifest["texture_count"], size
