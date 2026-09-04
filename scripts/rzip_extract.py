#!/usr/bin/env python3
"""Separate Conker's game code/data and indexed assets from their RZIP containers."""

from __future__ import annotations

import argparse
import hashlib
import json
import shutil
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import (
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
        parse_game_archive,
    )
except ModuleNotFoundError:
    from rzip_archive import (  # type: ignore[no-redef]
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
        parse_game_archive,
    )


ROOT = Path(__file__).resolve().parent.parent
LAYOUTS_FILE = ROOT / "config" / "rzip_layouts.json"


def load_profiles() -> tuple[str, ...]:
    config = json.loads(LAYOUTS_FILE.read_text(encoding="utf-8"))
    if config.get("schema_version") != 1 or not isinstance(config.get("profiles"), dict):
        raise ValueError("config/rzip_layouts.json has an unsupported schema")
    return tuple(config["profiles"])


def load_layout(profile: str) -> dict[str, Any]:
    config = json.loads(LAYOUTS_FILE.read_text(encoding="utf-8"))
    if config.get("schema_version") != 1:
        raise ValueError("config/rzip_layouts.json has an unsupported schema")
    try:
        raw = config["profiles"][profile]
    except KeyError as error:
        raise ValueError(f"unknown RZIP profile: {profile}") from error
    layout = dict(raw)
    for key, value in raw.items():
        if key.endswith(("_start", "_end", "_vram")) or key == "asset_table":
            layout[key] = int(value, 0)
    layout.setdefault("game_format", "rzip")
    return layout


def display_path(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def manifest_source(path: Path) -> str:
    """Return useful ROM provenance without recording the host directory."""

    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return path.name


def prepare_output(path: Path, force: bool) -> None:
    if path.exists():
        if not force:
            raise ValueError(f"output already exists: {display_path(path)}; pass --force to replace it")
        if not path.is_dir():
            raise ValueError(f"refusing to replace non-directory output: {display_path(path)}")
        shutil.rmtree(path)
    path.mkdir(parents=True)


def write_bytes(path: Path, data: bytes, manifest_only: bool) -> str | None:
    if manifest_only:
        return None
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return str(path)


def extract(profile: str, rom_path: Path, output: Path, keep_rzip: bool, manifest_only: bool) -> dict[str, Any]:
    layout = load_layout(profile)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(
            f"{profile} normalized ROM SHA-1 mismatch: got {digest}; expected one of "
            + ", ".join(layout["normalized_sha1"])
        )

    game_start = layout["game_start"]
    game_end = layout["game_end"]
    if game_end > len(normalized):
        raise ValueError("configured game archive extends beyond the ROM")
    game_dir = output / "game"
    game_payload = normalized[game_start:game_end]
    if layout["game_format"] == "rzip":
        game = parse_game_archive(game_payload)
        game_code = game.code
        game_data = game.data
        game_manifest: dict[str, Any] = {
            "format": "rzip",
            "rom_start": f"0x{game_start:X}",
            "rom_end": f"0x{game_end:X}",
            "vram": f"0x{layout['game_vram']:X}",
            "data_vram": f"0x{layout['game_data_vram']:X}",
            "code_chunk_count": len(game.code_offsets) - 1,
            "code_compressed_end": f"0x{game_start + game.code_end:X}",
            "data_compressed_start": f"0x{game_start + game.data_start:X}",
            "data_compressed_end": f"0x{game_start + game.data_end:X}",
            "code_padding_size": len(game.code_padding),
            "data_padding_size": len(game.data_padding),
        }
        if not manifest_only:
            write_bytes(game_dir / "code-padding.bin", game.code_padding, False)
            write_bytes(game_dir / "data-padding.bin", game.data_padding, False)
            if keep_rzip:
                write_bytes(
                    game_dir / "raw" / "code.rzip.bin",
                    game_payload[: game.code_end],
                    False,
                )
                write_bytes(
                    game_dir / "raw" / "data.rzip",
                    game_payload[game.data_start : game.data_end],
                    False,
                )
    elif layout["game_format"] == "raw":
        code_end = layout["game_code_end"]
        if not game_start < code_end <= game_end:
            raise ValueError("configured raw game code boundary is outside the game range")
        game_code = normalized[game_start:code_end]
        game_data = normalized[code_end:game_end]
        game_manifest = {
            "format": "raw",
            "rom_start": f"0x{game_start:X}",
            "rom_end": f"0x{game_end:X}",
            "code_rom_end": f"0x{code_end:X}",
            "vram": f"0x{layout['game_vram']:X}",
            "data_vram": f"0x{layout['game_data_vram']:X}",
            "code_chunk_count": 0,
            "code_padding_size": 0,
            "data_padding_size": 0,
        }
    else:
        raise ValueError(f"unsupported game format: {layout['game_format']}")

    write_bytes(game_dir / "code.bin", game_code, manifest_only)
    write_bytes(game_dir / "data.bin", game_data, manifest_only)
    game_manifest.update(
        {
            "code_size": len(game_code),
            "code_file": "game/code.bin" if not manifest_only else None,
            "data_size": len(game_data),
            "data_file": "game/data.bin" if not manifest_only else None,
        }
    )

    flat_manifest: dict[str, Any] | None = None
    if "flat_assets_start" in layout:
        flat_start = layout["flat_assets_start"]
        flat_end = layout["flat_assets_end"]
        if not 0 <= flat_start < flat_end <= len(normalized):
            raise ValueError("configured flat RZIP range is outside the ROM")
        flat_records: list[dict[str, Any]] = []
        flat_decoded_size = 0
        for entry in iter_flat_rzip_entries(normalized[flat_start:flat_end]):
            relative = Path("flat") / f"{entry.index:04d}.bin"
            raw = normalized[flat_start + entry.start : flat_start + entry.end]
            write_bytes(output / "assets" / relative, entry.data, manifest_only)
            if keep_rzip:
                write_bytes(
                    output / "assets" / "flat" / "rzip" / f"{entry.index:04d}.rzip",
                    raw,
                    manifest_only,
                )
            flat_records.append(
                {
                    "index": entry.index,
                    "rom_start": f"0x{flat_start + entry.start:X}",
                    "rom_end": f"0x{flat_start + entry.end:X}",
                    "decoded_size": len(entry.data),
                    "decoded_sha1": hashlib.sha1(entry.data).hexdigest(),
                    "file": str(relative) if not manifest_only else None,
                }
            )
            flat_decoded_size += len(entry.data)
        flat_manifest = {
            "rom_start": f"0x{flat_start:X}",
            "rom_end": f"0x{flat_end:X}",
            "file_count": len(flat_records),
            "decoded_size": flat_decoded_size,
            "files": flat_records,
        }

    banks = parse_asset_banks(normalized, layout["asset_table"])
    bank_manifests: list[dict[str, Any]] = []
    total_assets = 0
    compressed_assets = 0
    for bank in banks:
        bank_record: dict[str, Any] = {
            "index": bank.index,
            "rom_start": f"0x{bank.start:X}",
            "rom_end": f"0x{bank.end:X}",
            "flags": bank.flags,
            "entries": [],
        }
        if bank.flags:
            raw_name = f"raw-{bank.index:02X}.bin"
            raw_block = normalized[bank.start : bank.end]
            write_bytes(output / "assets" / raw_name, raw_block, manifest_only)
            bank_record["raw_file"] = raw_name if not manifest_only else None
            bank_record["raw_sha1"] = hashlib.sha1(raw_block).hexdigest()
            bank_manifests.append(bank_record)
            continue

        for entry in parse_asset_entries(normalized, bank):
            raw = normalized[entry.start : entry.end]
            decoded = decode_rzip_chunk(raw).data if entry.compressed else raw
            relative = Path(f"bank-{bank.index:02X}") / f"{entry.index:04d}.bin"
            write_bytes(output / "assets" / relative, decoded, manifest_only)
            if keep_rzip and entry.compressed:
                write_bytes(
                    output / "assets" / f"bank-{bank.index:02X}" / "rzip" / f"{entry.index:04d}.rzip",
                    raw,
                    manifest_only,
                )
            bank_record["entries"].append(
                {
                    "index": entry.index,
                    "rom_start": f"0x{entry.start:X}",
                    "rom_end": f"0x{entry.end:X}",
                    "type_flags": entry.type_flags,
                    "compressed": entry.compressed,
                    "decoded_size": len(decoded),
                    "decoded_sha1": hashlib.sha1(decoded).hexdigest(),
                    "file": str(relative) if not manifest_only else None,
                }
            )
            total_assets += 1
            compressed_assets += int(entry.compressed)
        bank_manifests.append(bank_record)

    manifest = {
        "schema_version": 1,
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "game": game_manifest,
        "assets": {
            "table_start": f"0x{layout['asset_table']:X}",
            "bank_count": sum(not bank.flags for bank in banks),
            "table_entry_count": len(banks),
            "raw_block_count": sum(bool(bank.flags) for bank in banks),
            "file_count": total_assets,
            "compressed_file_count": compressed_assets,
            "banks": bank_manifests,
        },
    }
    if flat_manifest is not None:
        manifest["assets"]["flat"] = flat_manifest
        manifest["assets"]["total_file_count"] = total_assets + flat_manifest["file_count"]
        manifest["assets"]["total_compressed_file_count"] = (
            compressed_assets + flat_manifest["file_count"]
        )
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    return manifest


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profile", choices=tuple(load_profiles()), required=True)
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--keep-rzip", action="store_true", help="also retain raw compressed chunks")
    parser.add_argument("--manifest-only", action="store_true", help="validate every chunk without writing decoded assets")
    parser.add_argument("--force", action="store_true", help="replace the exact output directory if it exists")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        layout = load_layout(args.profile)
        if args.rom is None:
            default_rom = layout.get("default_rom")
            if not default_rom:
                raise ValueError(f"--rom is required for the {args.profile} profile")
            rom_path = ROOT / default_rom
        else:
            rom_path = args.rom if args.rom.is_absolute() else ROOT / args.rom
        if not rom_path.is_file():
            raise ValueError(f"ROM does not exist: {display_path(rom_path)}")
        output = args.output or (ROOT / "build" / "rzip" / args.profile)
        if not output.is_absolute():
            output = ROOT / output
        prepare_output(output, args.force)
        manifest = extract(
            args.profile,
            rom_path,
            output,
            keep_rzip=args.keep_rzip,
            manifest_only=args.manifest_only,
        )
    except (OSError, ValueError, json.JSONDecodeError) as error:
        print(f"error: {error}")
        return 1

    game = manifest["game"]
    assets = manifest["assets"]
    print(
        f"Extracted {args.profile}: game code={game['code_size']} bytes, "
        f"game data={game['data_size']} bytes, asset files={assets.get('total_file_count', assets['file_count'])} "
        f"({assets.get('total_compressed_file_count', assets['compressed_file_count'])} RZIP)"
    )
    print(f"Manifest: {display_path(output / 'manifest.json')}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
