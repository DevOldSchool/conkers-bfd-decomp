# US direct CI4 tiles with odd visible widths

The preview exporter supports a CI4 tile whose visible width ends in the high
nibble of its final byte. The native `SetTile` line field still supplies an
aligned byte stride; the unused low nibble and row padding remain in the ROM
payload. This is a preview decoding contract, not a new reversible flat-asset
storage format.

## ROM evidence

| Bank / entry / segment | Material run | Flat asset | Visible dimensions | Textured faces |
| --- | ---: | ---: | --- | ---: |
| `04 / 0029 / 00` | 4 | 1252 | 63 × 64 | 12 |
| `04 / 0029 / 12` | 112 | 1252 | 63 × 64 | 10 |
| `04 / 0045 / 00` | 19 | 2343 | 63 × 63 | 22 |

All three runs use CI4 render tile `F5400800`: 32 bytes per row, starting at
TMEM zero. Their explicit OtherMode enables the RGBA16 lookup table. The
same-index mode-two palette load selects the final 32 payload bytes. Flat 1252
contains 2,048 image bytes followed by its palette; flat 2343 contains 2,016
image bytes followed by its palette. The visible image and every required
odd-row swap fit within the proven load, lower 2 KiB of TMEM and image payload.

## Decoder contract

`direct_runtime_indexed_preview_texture` reads `ceil(width / 2)` bytes per
visible row. It applies the native odd-row four-byte-half swap before selecting
texels. For an odd width it expands only the visible nibbles through the exact
16-entry RGBA5551 palette, using the existing RGBA16 preview PNG encoder.
Palette alpha is preserved. Even-width CI4 previews retain their existing
indexed PNG representation and bytes.

The decoder still rejects an unproven load, palette bank, lookup mode, row
stride, TMEM span or payload extent. It does not infer missing material state,
read capture inputs or extend a transfer to accommodate a nominal tile size.

## Verification and limits

Regression tests cover distinct even and odd rows, transparent palette entries,
unused final nibbles, row padding and rejected short loads or overlapping
palettes. An independent per-pixel ROM lookup checks all 12,033 visible pixels
of the three recovered images. The isolated bank-04 export changes exactly
these three model records and binds 44 additional faces.

Local reproduction evidence is under
`build/assets/models/reference/expansion-20260910-usage-budget/odd-width/`.
Its `read-audit.json` records the export's inputs; `probe.json` records the
native loads and image hashes; `independent-pixel-check.json` records the
pixel comparison. Regenerate accepted sources, run the normal model validation
batch and inspect the final packed GLBs before publication.

Correct texture decoding does not establish native lighting, dynamic colours,
part visibility or complete scene composition. Bank `04 / 0029 / 00` remains a
scattered scene layer; texture recovery alone does not make it suitable for the
inspection gallery.
