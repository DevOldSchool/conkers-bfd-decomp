"""Reviewed interface images outside the 92-entry HUD selector table.

IDs are runtime compressed-size-table IDs. These source-image contracts do not
claim a selector association, runtime placement, or runtime rendering state.
"""
from __future__ import annotations

import hashlib
import html
from pathlib import Path
from typing import Any

try:
    from scripts import texture_assets, texture_native
except ModuleNotFoundError:
    import texture_assets  # type: ignore[no-redef]
    import texture_native  # type: ignore[no-redef]

# name, title, resource IDs, per-resource width/height, source format
ARTWORK = (
    ("nintendo-wordmark", "Nintendo wordmark", (2141, 2142, 2143), 64, 64, "i8"),
    ("rare-logo", "Rare logo", (2204,), 16, 16, "rgba32"),
    ("blue-a-button-pair", "Blue A buttons (dark and bright)", (2164, 2165), 32, 32, "rgba32"),
    ("green-b-button-dark", "Green B button (dark)", (2168,), 32, 32, "rgba32"),
    ("green-b-button-bright", "Green B button (bright)", (2169,), 32, 32, "rgba32"),
    ("red-circular-button", "Red circular button", (2207,), 32, 32, "rgba32"),
    ("green-zero-digit", "Green digit 0", (2226,), 32, 32, "rgba32"),
    ("pink-one-digit", "Pink digit 1", (2192,), 32, 32, "rgba32"),
    ("gold-two-digit", "Gold digit 2", (2219,), 32, 32, "rgba32"),
    ("blue-three-digit", "Blue digit 3", (2216,), 32, 32, "rgba32"),
    ("blue-four-digit", "Blue digit 4", (2178,), 32, 32, "rgba32"),
    ("pink-five-digit", "Pink digit 5", (2177,), 32, 32, "rgba32"),
    ("red-six-digit", "Red digit 6", (2210,), 32, 32, "rgba32"),
    ("green-seven-digit", "Green digit 7", (2209,), 32, 32, "rgba32"),
    ("teal-eight-digit", "Teal digit 8", (2176,), 32, 32, "rgba32"),
    ("blue-nine-digit", "Blue digit 9", (2191,), 32, 32, "rgba32"),
    ("green-dollar-symbol", "Green dollar symbol ($)", (2038,), 32, 32, "rgba32"),
    ("dang-label", "Dang... label", (2173,), 64, 32, "ia8"),
    ("dino-label", "Dino label", (2174,), 64, 32, "ia8"),
    ("poops-label", "Poops label", (2200,), 64, 32, "ia8"),
    ("question-mark-icon", "Question-mark icon", (2201,), 32, 32, "ia8"),
    ("total-label", "Total label", (2217,), 64, 32, "ia8"),
)
MENU_ARTWORK = (
    ("start-button-dark", "START button (dark)", (2206,), 32, 32, "rgba32"),
    ("beach-heading", "BEACH heading", (1977, 1978, 1979), 32, 32, "rgba32"),
    ("skull-icon", "Skull icon", (1980, 1981, 1982, 1983), 32, 32, "rgba32"),
    ("chapters-heading", "CHAPTERS heading", (1994, 1995, 1996), 32, 32, "rgba32"),
    ("game-one-heading", "GAME1 heading", (2011, 2012, 2013), 32, 32, "rgba32"),
    ("game-two-heading", "GAME2 heading", (2014, 2015, 2016), 32, 32, "rgba32"),
    ("game-three-heading", "GAME3 heading", (2017, 2018, 2019), 32, 32, "rgba32"),
    ("options-heading", "OPTIONS heading", (2035, 2036, 2037), 32, 32, "rgba32"),
    ("race-heading", "RACE heading", (2056, 2057, 2058), 32, 32, "rgba32"),
    ("raptor-heading", "RAPTOR heading", (2059, 2060, 2061), 32, 32, "rgba32"),
    ("war-heading", "WAR heading", (2082, 2083, 2084), 32, 32, "rgba32"),
    ("back-heading", "BACK heading", (2097, 2098), 32, 32, "rgba32"),
    ("small-player-badges", "Small P1–P4 badges", (2115,), 32, 32, "rgba32"),
    ("heist-heading", "HEIST heading", (2180, 2181, 2182), 32, 32, "rgba32"),
    ("small-statistics-icons", "Small statistics icons", (2183, 2184), 32, 32, "rgba32"),
    ("multi-heading", "MULTI heading", (2188, 2189, 2190), 32, 32, "rgba32"),
    ("paused-heading", "PAUSED heading", (2193, 2194, 2195), 32, 32, "rgba32"),
    ("tank-heading", "TANK heading", (2212, 2213, 2214), 32, 32, "rgba32"),
)
ARTWORK += MENU_ARTWORK
RESOURCE_IDS = tuple(sorted({index for _, _, indices, *_ in ARTWORK for index in indices}))
# func_151EADFC indexes D_80090074; D_80090B34 corroborates the same order.
DIGIT_RESOURCE_IDS = (2226, 2192, 2219, 2216, 2178, 2177, 2210, 2209, 2176, 2191)
NUMERIC_SYMBOLS = {resource_id: str(digit) for digit, resource_id in enumerate(DIGIT_RESOURCE_IDS)}
NUMERIC_SYMBOLS[2038] = "$"
REFERENCE_PAGES = {
    "nintendo-wordmark": (62741, "Intro Credits reference sheet"),
    "rare-logo": (62741, "Intro Credits reference sheet"),
    "blue-a-button-pair": (62746, "Text reference sheet"),
    "green-b-button-dark": (62746, "Text reference sheet"),
    "green-b-button-bright": (62746, "Text reference sheet"),
}


# All unlisted groups retain their original horizontal tile order.
COMPOSITIONS = {"skull-icon": {"columns": 2, "rows": 2, "order": "column-major"}}
# Regions use coordinates in the composed preview, preserving source RGBA bytes.
REGIONS = {
    "small-player-badges": (
        ("small-p1-badge", "Small red P1 badge", 0, 0, 16, 16),
        ("small-p2-badge", "Small blue P2 badge", 16, 0, 16, 16),
        ("small-p3-badge", "Small green P3 badge", 0, 16, 16, 16),
        ("small-p4-badge", "Small yellow P4 badge", 16, 16, 16, 16),
    ),
    "small-statistics-icons": (
        ("small-stopwatch", "Small stopwatch", 0, 0, 16, 16),
        ("small-money-bag", "Small money bag", 16, 0, 16, 16),
        ("small-rip-gravestone", "Small RIP gravestone", 0, 16, 16, 16),
        ("small-green-roll", "Green roll with pale band", 16, 16, 16, 16),
        ("small-skull", "Small skull", 32, 0, 16, 16),
        ("small-green-crosshair", "Green circular crosshair", 48, 0, 16, 16),
        ("small-gray-projectile", "Gray horizontal projectile", 32, 16, 16, 16),
        ("small-purple-head-impact", "Purple head with red impact marks", 48, 16, 16, 16),
    ),
}
for _name, *_ in MENU_ARTWORK:
    REFERENCE_PAGES[_name] = (
        (62744, "Pause Menu & Multi Results reference sheet")
        if _name in ("paused-heading", "small-player-badges", "small-statistics-icons")
        else (62742, "Main Menu Text & Icons reference sheet")
    )


def render_artwork(assets: dict[int, Any]) -> tuple[list[dict[str, Any]], dict[str, bytes]]:
    """Build exact raw sources, reviewed PNGs and their provenance together."""
    records = []
    files = {}
    for name, title, indices, tile_width, tile_height, texture_format in ARTWORK:
        composition = COMPOSITIONS.get(name, {"columns": len(indices), "rows": 1, "order": "row-major"})
        columns, rows, order = composition["columns"], composition["rows"], composition["order"]
        if columns < 1 or rows < 1 or columns * rows != len(indices) or order not in ("row-major", "column-major"):
            raise ValueError(f"Invalid additional artwork composition: {name}")
        width, height = tile_width * columns, tile_height * rows
        pixels = bytearray(width * height * 4)
        sources = []
        source_positions = {}
        for ordinal, index in enumerate(indices):
            column, tile_row = ((ordinal // rows, ordinal % rows) if order == "column-major"
                else (ordinal % columns, ordinal // columns))
            source_positions[column, tile_row] = index
            if index not in assets:
                raise ValueError(f"Additional artwork is missing runtime resource {index}")
            asset = assets[index]
            expected_size = texture_native.packed_row_size(texture_format, tile_width) * tile_height
            if len(asset.data) != expected_size:
                raise ValueError(f"Additional resource {index} is not exactly {expected_size} bytes")
            linear = texture_native.convert_row_layout(asset.data,
                texture_assets.ROW_LAYOUT_TMEM, texture_format, tile_width, tile_height)
            decoded = texture_native.payload_to_rgba(linear, texture_format)
            for row in range(tile_height):
                target = ((tile_row * tile_height + row) * width + column * tile_width) * 4
                source = row * tile_width * 4
                pixels[target:target + tile_width * 4] = decoded[source:source + tile_width * 4]
            raw_file = f"additional/resources/{index:04d}.bin"
            files[raw_file] = asset.data
            sources.append({"runtime_resource_id": index, "rom_start": f"0x{asset.rom_start:X}",
                "rom_end": f"0x{asset.rom_end:X}", "decoded_size": len(asset.data),
                "sha1": hashlib.sha1(asset.data).hexdigest(), "raw_file": raw_file})
        preview_file = f"additional/{indices[0]:04d}-{name}.png"
        files[preview_file] = texture_assets.encode_rgba_png(width, height, bytes(pixels))
        evidence = "Reviewed source artwork outside the HUD selector table; runtime placement unproven."
        if texture_format == "ia8":
            evidence += " IA8 preserves the separate intensity and alpha nibbles, including transparent 0xF0 background."
        record = {"name": name, "display_name": title, "resource_ids": list(indices),
            "width": width, "height": height, "tile_width": tile_width,
            "tile_height": tile_height, "tile_columns": columns, "tile_rows": rows, "tile_order": order,
            "texture_format": texture_format, "row_layout": texture_assets.ROW_LAYOUT_TMEM,
            "preview_file": preview_file, "sources": sources, "evidence": evidence}
        if name in REFERENCE_PAGES:
            reference, reference_title = REFERENCE_PAGES[name]
            record.update(reference_url=f"https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/{reference}/",
                reference_title=reference_title)
        if len(indices) == 1 and indices[0] in NUMERIC_SYMBOLS:
            record.update(symbol=NUMERIC_SYMBOLS[indices[0]],
                reference_url="https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/",
                reference_title="Pause Menu & Multi Results reference sheet")
            record["evidence"] += " Visually matched to the supplied Pause Menu & Multi Results sheet."
            if indices[0] in DIGIT_RESOURCE_IDS:
                record["evidence"] += " func_151EADFC indexes decimal digits through D_80090074; D_80090B34 contains the same ordering."
        if name in COMPOSITIONS:
            record["evidence"] += " Reference-matched column-major 2×2 tile composition."
        if name in REGIONS:
            record["evidence"] += " Native 16×16 regions are exported without scaling or alpha changes."
            record["regions"] = []
            for region_name, region_title, x, y, region_width, region_height in REGIONS[name]:
                if (x < 0 or y < 0 or region_width < 1 or region_height < 1
                        or x + region_width > width or y + region_height > height
                        or x // tile_width != (x + region_width - 1) // tile_width
                        or y // tile_height != (y + region_height - 1) // tile_height):
                    raise ValueError(f"Invalid additional artwork region: {region_name}")
                resource_id = source_positions[x // tile_width, y // tile_height]
                region_pixels = b"".join(bytes(pixels[((y + row) * width + x) * 4:
                    ((y + row) * width + x + region_width) * 4]) for row in range(region_height))
                region_file = f"additional/regions/{resource_id:04d}-{region_name}.png"
                files[region_file] = texture_assets.encode_rgba_png(region_width, region_height, region_pixels)
                record["regions"].append({"name": region_name, "display_name": region_title,
                    "x": x, "y": y, "width": region_width, "height": region_height,
                    "source_resource_id": resource_id, "preview_file": region_file})
        records.append(record)
    return records, files


def write_preview(assets: dict[int, Any], output: Path) -> list[dict[str, Any]]:
    records, files = render_artwork(assets)
    for relative, data in files.items():
        path = output / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
    return records


def verify_preview(assets: dict[int, Any], output: Path, records: list[dict[str, Any]]) -> None:
    expected, files = render_artwork(assets)
    if records != expected:
        raise ValueError("Additional artwork metadata or runtime resource provenance is stale")
    for relative, data in files.items():
        if (output / relative).read_bytes() != data:
            raise ValueError(f"Additional artwork source or PNG is stale: {relative}")


def gallery_cards(records: list[dict[str, Any]]) -> str:
    cards = []
    for record in records:
        title = html.escape(record["display_name"])
        resource_ids = ", ".join(map(str, record["resource_ids"]))
        search = html.escape(" ".join((record["display_name"], record["name"], resource_ids,
            record["preview_file"], record.get("symbol", ""),
            " ".join(region["display_name"] + " " + region["name"] for region in record.get("regions", [])))).lower(), quote=True)
        preview = html.escape(record["preview_file"], quote=True)
        raw_links = " ".join(f'<a href="{html.escape(source["raw_file"], quote=True)}" download>'
            f'resource {source["runtime_resource_id"]}</a>' for source in record["sources"])
        reference = ""
        if "reference_url" in record:
            reference = f'<p><a href="{html.escape(record["reference_url"], quote=True)}">{html.escape(record["reference_title"])}</a></p>'
        regions = ""
        if record.get("regions"):
            region_links = []
            for region in record["regions"]:
                region_title = html.escape(region["display_name"])
                region_file = html.escape(region["preview_file"], quote=True)
                region_links.append(f'<a class="region" href="{region_file}" download>'
                    f'<span class="images"><img width="48" height="48" src="{region_file}" alt="{region_title}"></span>'
                    f'<span>{region_title} · PNG</span></a>')
            regions = '<p>Individual 16×16 icons</p><div class="regions">' + "".join(region_links) + '</div>'
        cards.append(f'<article class="card" data-kind="additional" data-search="{search}">'
            f'<h2>{title}</h2><p class="source-id">Additional artwork · resource {resource_ids}</p>'
            f'<div class="images"><img style="height:64px" src="{preview}" alt="{title}"></div>'
            f'<p>{record["width"]}×{record["height"]} · {html.escape(record["texture_format"].upper())}</p>'
            f'<p class="downloads"><a href="{preview}" download>PNG</a></p>{regions}'
            f'<details><summary>Source and naming evidence</summary><p>{html.escape(record["evidence"])}</p>'
            f'{reference}<p>{raw_links}</p></details></article>')
    return "".join(cards)
