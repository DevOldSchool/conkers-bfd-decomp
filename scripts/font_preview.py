"""Export and verify a ROM-backed US font atlas, input map and logical metrics."""

from __future__ import annotations

import hashlib
import html
import json
import math
from pathlib import Path

try:
    from scripts import font_assets as fonts, hud_assets as hud, texture_assets as textures
    from scripts.rzip_archive import parse_game_archive
except ModuleNotFoundError:
    import font_assets as fonts
    import hud_assets as hud
    import texture_assets as textures
    from rzip_archive import parse_game_archive


FONT_ROM_RANGE_VRAM = 0x80082F80
FONT_ROM_RANGE = (0x40F10, 0x42450)
FONT_GLYPH_MAP_VRAM = 0x80085930
FONT_GLYPH_MAP_COUNT = 95
FONT_RUNTIME_PIXEL_POINTER_VRAM = 0x80085990
FONT_RUNTIME_METRIC_POINTER_VRAM = 0x80085994

# Loader selects ROM range by font number, starts record index at zero,
# increments it for each record, and walks the big-endian record size at +4.
FONT_LOADER_SIGNATURES = {
    0x15015964: 0x3C188008,
    0x15015968: 0x27182F80,
    0x1501596C: 0x001478C0,
    0x15015974: 0x8E440000,
    0x15015978: 0x8E590004,
    0x15015988: 0x0C001145,
    0x1501598C: 0x03243023,
    0x150159B0: 0x00008825,
    0x150159B8: 0x02202825,
    0x150159BC: 0x0D40568E,
    0x150159C0: 0x02803025,
    0x150159C4: 0x920D0004,
    0x150159C8: 0x92180005,
    0x150159CC: 0x92090006,
    0x150159D0: 0x000D7600,
    0x150159D8: 0x920C0007,
    0x150159EC: 0x00095200,
    0x15015A0C: 0x26310001,
}

# Runtime four-byte metrics are [source_width+1, source_height+1, byte2, byte3].
# The original RLE high nibble is intensity; low nibble +1 is run length.
FONT_HEADER_SIGNATURES = {
    0x15015A64: 0x3C0E8008,
    0x15015A68: 0x25CE5994,
    0x15015A6C: 0x00068880,
    0x15015A7C: 0x00078080,
    0x15015A78: 0x926F0000,
    0x15015A84: 0x25F80001,
    0x15015A88: 0xA1D80000,
    0x15015A90: 0x926F0001,
    0x15015A9C: 0x25F90001,
    0x15015AA0: 0xA1D90001,
    0x15015AA8: 0x926F0002,
    0x15015AB4: 0xA32F0002,
    0x15015ABC: 0x926E0003,
    0x15015AC8: 0xA1EE0003,
    0x15015BBC: 0x3088000F,
    0x15015BC0: 0x25080001,
    0x15015BC8: 0x308300F0,
}

# The measure function calls the same glyph map then indexes metrics by glyph*4.
# At logical scale: advance = source_width + byte2;
# line extent contribution = source_height + 1 + byte3.
# A space is index 0x60, has advance 4, and contributes minimum line extent 12.
FONT_METRIC_SIGNATURES = {
    0x15042968: 0x0D410B10,
    0x15042974: 0x24010060,
    0x1504298C: 0x252A0004,
    0x15042B14: 0x3C098008,
    0x15042B18: 0x8D295994,
    0x15042B1C: 0x00131880,
    0x15042B28: 0x904B0000,
    0x15042B2C: 0x904D0002,
    0x15042B34: 0x014B6021,
    0x15042B38: 0x018D7021,
    0x15042B3C: 0x25CFFFFF,
    0x15042B4C: 0x90590003,
    0x15042B50: 0x90490001,
    0x15042B54: 0x03292021,
}

# Drawing consults the exact same metrics. byte2 offsets x and byte3 offsets y
# after runtime scaling; therefore cautious field names are horizontal_offset
# and vertical_offset, NOT a typographic baseline. Pixel decoder inserts zero
# border before the raw pixels and TMEM row swizzling. A source-PNG sample can
# use these logical offsets while labelling itself a source-pixel preview,
# not an exact emulation of GPU filtering, borders, scaling, or text effects.
FONT_DRAW_SIGNATURES = {
    0x15041BD8: 0x0D410B10,
    0x15041BDC: 0xAFA00130,
    0x15041BEC: 0xA3A201B7,
    0x150421A4: 0x3C0F8008,
    0x150421A8: 0x25EF5994,
    0x150421B0: 0x93BF01B7,
    0x150421BC: 0x001F7080,
    0x150421C8: 0x032E2021,
    0x15042210: 0x90990002,
    0x15042234: 0x90980003,
    0x15042250: 0x4604A500,
    0x15042264: 0x460E5101,
    0x150422A4: 0x4608B580,
    0x150427D8: 0x25CFFFFF,
    0x150427F8: 0x4604A500,
}

# Reuse existing HUD lookup signatures for uppercase folding, the space case,
# and the 95-byte scan. This extra word verifies fallback returns original byte.
# Such fallback bytes may be text controls: never treat them as safe glyph IDs.
FONT_LOOKUP_FALLBACK_SIGNATURES = {0x15042D38: 0x00601025}

FONT_SIGNATURES = {
    **FONT_LOADER_SIGNATURES,
    **FONT_HEADER_SIGNATURES,
    **FONT_METRIC_SIGNATURES,
    **FONT_DRAW_SIGNATURES,
    **FONT_LOOKUP_FALLBACK_SIGNATURES,
}


def validate_font_consumer(code, data, code_vram, data_vram):
    """Call after normalized US ROM hash validation; performs no mutation."""
    for address, expected in FONT_SIGNATURES.items():
        offset = address - code_vram
        if offset < 0 or offset + 4 > len(code):
            raise ValueError(f"font evidence instruction outside code at 0x{address:X}")
        actual = int.from_bytes(code[offset:offset + 4], "big")
        if actual != expected:
            raise ValueError(f"font evidence instruction mismatch at 0x{address:X}")
    offset = FONT_ROM_RANGE_VRAM - data_vram
    expected = b"".join(value.to_bytes(4, "big") for value in FONT_ROM_RANGE)
    if offset < 0 or data[offset:offset + 8] != expected:
        raise ValueError("font loader ROM range does not match extracted font storage")

# Current US map preserves duplicate input bytes: EA -> indices 81 and 83,
# F4 -> 89 and 91. Lookup chooses first match, so 83/91 are shadowed. Retain all
# 95 bitmaps and raw map bytes; do not silently repair the table or invent labels.



def glyph_rgba(glyph):
    """White RGB with unscaled source intensity (0..240) as alpha."""
    return b"".join(bytes((255, 255, 255, value)) for value in glyph.pixels)


def build_artifacts(glyphs, glyph_map, provenance):
    if not glyphs or len(glyphs) != len(glyph_map):
        raise ValueError("font glyph and input map counts differ")
    columns = 16
    cell_width = max(g.width for g in glyphs) + 4
    cell_height = max(g.height for g in glyphs) + 4
    width, height = columns * cell_width, math.ceil(len(glyphs) / columns) * cell_height
    atlas = bytearray(bytes((255, 255, 255, 0)) * width * height)
    files, records = {}, []
    offset = int(provenance["font_start"], 0)
    for index, (glyph, value) in enumerate(zip(glyphs, glyph_map, strict=True)):
        x, y = (index % columns) * cell_width + 2, (index // columns) * cell_height + 2
        rgba = glyph_rgba(glyph)
        filename = f"glyphs/{index:03d}-byte-{value:02x}.png"
        files[filename] = textures.encode_rgba_png(glyph.width, glyph.height, rgba)
        for row in range(glyph.height):
            target = ((y + row) * width + x) * 4
            atlas[target:target + glyph.width * 4] = rgba[row * glyph.width * 4:(row + 1) * glyph.width * 4]
        record_size = 8 + len(glyph.encoded)
        records.append({
            "glyph_index": index, "input_byte": value, "input_hex": f"0x{value:02X}",
            "display_latin1": chr(value), "lookup_first_index": glyph_map.index(value),
            "lookup_status": "first-match" if glyph_map.index(value) == index else "shadowed",
            "source_width": glyph.width, "source_height": glyph.height,
            "runtime_width": glyph.width + 1, "runtime_height": glyph.height + 1,
            "horizontal_offset": glyph.metadata[0], "vertical_offset": glyph.metadata[1],
            "advance": glyph.width + glyph.metadata[0],
            "line_extent": glyph.height + 1 + glyph.metadata[1],
            "metadata_hex": glyph.metadata.hex(),
            "atlas_rect": {"x": x, "y": y, "width": glyph.width, "height": glyph.height},
            "png_file": filename, "legacy_pgm_file": f"{glyph.codepoint:04X}.pgm",
            "rom_start": f"0x{offset:X}", "rom_end": f"0x{offset + record_size:X}",
            "decoded_sha1": hashlib.sha1(glyph.pixels).hexdigest(),
        })
        offset += record_size
    manifest = {
        "schema_version": 1, "family": "us-font-atlas", **provenance,
        "glyph_count": len(records), "distinct_input_byte_count": len(set(glyph_map)),
        "glyph_map_vram": f"0x{FONT_GLYPH_MAP_VRAM:X}",
        "glyph_map_sha1": hashlib.sha1(glyph_map).hexdigest(),
        "atlas": {"file": "atlas.png", "width": width, "height": height, "columns": columns,
                  "pixel_contract": "white RGB; alpha is unscaled source intensity 0..240; top-left origin"},
        "lookup": {"ascii_lowercase": "fold-to-uppercase", "duplicate_rule": "first-match",
                   "space_advance": 4, "space_minimum_line_extent": 12,
                   "unsupported_preview_policy": "omit and report; runtime fallback and controls are not emulated"},
        "glyphs": records,
        "limitations": ["Input-byte labels are not a Unicode character map.",
            "Source-pixel preview with logical offsets; native borders, filtering, scale and text effects are not emulated.",
            "Duplicate input bytes retain all source glyphs; ordinary lookup selects the first.",
            "Legacy PGM names and codepoint fields are ordinal compatibility identifiers, not character mappings."],
    }
    files["atlas.png"] = textures.encode_rgba_png(width, height, bytes(atlas))
    files["glyph-map.bin"] = bytes(glyph_map)
    files["preview-manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    files["index.html"] = preview_html(manifest).encode()
    return manifest, files


def preview_html(manifest):
    cards = []
    for record in manifest["glyphs"]:
        value = record["input_byte"]
        label = html.escape(record["display_latin1"]) if value >= 32 and value != 127 else "control"
        shadow = (f'Shadowed by glyph {record["lookup_first_index"]}'
                  if record["lookup_status"] == "shadowed" else "First-match input")
        cards.append(f'''<article class="glyph" data-search="{html.escape((str(record['glyph_index']) + ' ' + record['input_hex'] + ' ' + record['display_latin1'] + ' ' + record['lookup_status']).lower(), quote=True)}">
<h3>Glyph {record['glyph_index']:02d} <span>{record['input_hex']}</span></h3>
<div class="pixels"><img src="{record['png_file']}" width="{record['source_width'] * 3}" height="{record['source_height'] * 3}" alt="Extracted glyph {record['glyph_index']}"></div>
<p>Input-byte label: <b>{label}</b><br>{shadow}</p>
<p>{record['source_width']} × {record['source_height']} pixels · advance {record['advance']}<br>Offsets {record['horizontal_offset']}, {record['vertical_offset']}</p>
<a href="{record['png_file']}" download>Download PNG</a></article>''')
    payload = json.dumps(manifest, ensure_ascii=True).replace("<", "\\u003c")
    return '''<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Conker US font atlas</title><style>
:root { color-scheme:dark; font-family:system-ui,sans-serif; background:#151a22; color:#edf1f8; }
* { box-sizing:border-box; } body { margin:0 auto; max-width:1280px; padding:32px; } h1 { margin:0 0 12px; font-size:36px; }
h2 { margin:30px 0 14px; } p { line-height:1.55; color:#b9c6d7; } a { color:#a6dbff; }
.kicker { font:12px ui-monospace,monospace; letter-spacing:.15em; color:#a6dbff; }
.downloads { display:flex; gap:18px; flex-wrap:wrap; margin:20px 0; }
.panel,.glyph { background:#202936; border:1px solid #3f5067; border-radius:8px; padding:18px; }
label { display:block; font-size:14px; margin-bottom:8px; }
input { font:inherit; color:#fff; background:#111820; border:1px solid #8193aa; border-radius:5px; padding:12px; width:100%; }
.sample { overflow:auto; margin-top:16px; background:#10151d; padding:16px; }
canvas,img { image-rendering:pixelated; } #sample { display:block; }
#sample-status,#count { font-size:13px; } .grid { display:grid; grid-template-columns:repeat(auto-fill,minmax(min(100%,190px),1fr)); gap:12px; margin-top:18px; }
.glyph h3 { font:14px ui-monospace,monospace; margin:0 0 14px; } .glyph span { color:#9caec4; float:right; }
.glyph p,.glyph a { font-size:12px; } .pixels { height:78px; display:flex; align-items:center; justify-content:center; background:#10151d; }
.atlas-view { max-width:100%; height:auto; background:#10151d; padding:12px; margin-top:12px; }
[hidden] { display:none!important; } details { margin:22px 0; } summary { cursor:pointer; }
@media(max-width:600px) { body { padding:18px; } h1 { font-size:28px; } .panel { padding:14px; } }
</style></head><body><p class="kicker">CONKER / US ROM ASSETS</p><h1>Font atlas</h1>
<p>95 source glyphs, with character lookup and spacing traced to the game code. Two duplicate input mappings are preserved.</p>
<nav class="downloads"><a href="atlas.png" download>Atlas PNG</a><a href="preview-manifest.json" download>Coordinates &amp; metrics JSON</a><a href="glyph-map.bin" download>Original input map</a></nav>
<section class="panel"><h2 style="margin-top:0">Try the font</h2><label for="text">Sample text</label><input id="text" value="Conker's Bad Fur Day! 0123456789" maxlength="120">
<div class="sample"><canvas id="sample" aria-label="Sample rendered with extracted font pixels"></canvas></div><p id="sample-status" role="status">Loading atlas…</p>
<p>Source-pixel preview using logical offsets. ASCII lowercase becomes uppercase; space advances four pixels. Game text effects and unsupported control bytes are not emulated.</p></section>
<details><summary>View the complete atlas and mapping notes</summary><img class="atlas-view" src="atlas.png" alt="All 95 font glyphs in source order"><p>White RGB uses the original 0–240 intensity as alpha. Labels show input bytes interpreted as Latin-1, not a Unicode font encoding. Duplicate input bytes use the first matching glyph; shadowed glyphs remain downloadable.</p></details>
<h2>Glyphs</h2><label for="search">Search by input label, byte, glyph index or “shadowed”</label><input id="search" type="search" placeholder="Try A, 0x41 or shadowed"><p id="count" role="status"></p><main class="grid">''' + ''.join(cards) + '''</main>
<script type="application/json" id="font-data">''' + payload + '''</script><script>
const data = JSON.parse(document.querySelector('#font-data').textContent);
const atlas = new Image(), canvas = document.querySelector('#sample'), field = document.querySelector('#text');
function render() {
  const draws = [], unsupported = []; let pen = 0, extent = 12;
  for (const char of field.value) {
    let byte = char.codePointAt(0); if (byte >= 97 && byte <= 122) byte -= 32;
    if (byte === 32) { pen += 4; continue; }
    const glyph = data.glyphs.find(g => g.input_byte === byte);
    if (!glyph) { unsupported.push(char); continue; }
    draws.push({glyph, x:pen + glyph.horizontal_offset}); pen += glyph.advance;
    extent = Math.max(extent, glyph.line_extent);
  }
  const scale = 3; canvas.width = Math.max(1,pen + 2) * scale; canvas.height = (extent + 2) * scale;
  const context = canvas.getContext('2d'); context.imageSmoothingEnabled = false;
  for (const {glyph:g, x} of draws) { const r=g.atlas_rect;
    context.drawImage(atlas,r.x,r.y,r.width,r.height,x*scale,g.vertical_offset*scale,r.width*scale,r.height*scale); }
  document.querySelector('#sample-status').textContent = `${pen} source pixels wide · ${draws.length} glyphs` + (unsupported.length ? ` · Unsupported input omitted: ${[...new Set(unsupported)].join(' ')}` : '');
}
atlas.onload=render; atlas.onerror=()=>{document.querySelector('#sample-status').textContent='Atlas could not be loaded.';}; atlas.src='atlas.png';
field.addEventListener('input',()=>{if(atlas.complete && atlas.naturalWidth) render();});
const cards=[...document.querySelectorAll('.glyph')], search=document.querySelector('#search');
function filter() { let count=0; const terms=search.value.toLowerCase().trim().split(/\\s+/).filter(Boolean);
 for(const card of cards) { card.hidden=!terms.every(t=>card.dataset.search.includes(t)); count+=Number(!card.hidden); }
 document.querySelector('#count').textContent=`${count} of ${cards.length} glyphs`;
}
search.addEventListener('input',filter); filter();
</script></body></html>
'''


def load_artifacts(profile, rom_argument):
    if profile != "us":
        raise ValueError("font atlas consumer mapping is currently proven only for US")
    rom_path, normalized, source_order, layout, glyphs, padding = fonts.load_profile_fonts(profile, rom_argument)
    archive = parse_game_archive(normalized[layout["game_start"]:layout["game_end"]])
    validate_font_consumer(archive.code, archive.data, layout["game_vram"], layout["game_data_vram"])
    family = hud.parse_hud_assets(archive.code, archive.data, layout["game_vram"], layout["game_data_vram"])
    if (layout["font_start"], layout["font_storage_end"]) != FONT_ROM_RANGE:
        raise ValueError("font layout and consumer range disagree")
    return build_artifacts(glyphs, family.glyph_map, {
        "profile": profile, "source_rom": fonts.manifest_source(rom_path),
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(), "source_byte_order": source_order,
        "font_start": f"0x{layout['font_start']:X}", "font_storage_end": f"0x{layout['font_storage_end']:X}",
        "padding_size": padding, "verified_font_instruction_count": len(FONT_SIGNATURES),
    })


def preview_fonts(profile, rom_argument, output, force=False):
    manifest, files = load_artifacts(profile, rom_argument)
    fonts.prepare_output(output, force)
    for relative, contents in files.items():
        target = output / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(contents)
    return manifest


def verify_preview(profile, rom_argument, directory):
    manifest, files = load_artifacts(profile, rom_argument)
    for relative, expected in files.items():
        if (directory / relative).read_bytes() != expected:
            raise ValueError(f"font preview is stale or corrupted: {relative}")
    return manifest["glyph_count"], len(files)
