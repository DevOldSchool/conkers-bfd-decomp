# Future asset editing and recomp integration

This document covers reversible asset editing and ROM insertion intended for a
future recompilation project. The current decompilation project uses the asset
tools for extraction, classification, and round-trip verification; edited
assets are not part of its build.

All generated files belong below `build/` and are untracked. Commands reject
the verified source ROM as an output path.

## Grayscale fonts

Extract the RLE font table, edit its generated PGM glyphs, then rebuild the
table and alignment padding into a separate file:

```sh
./conker font-assets extract --profile us
./conker font-assets pack \
  --input build/fonts/us \
  --output build/fonts/us.bin
```

The encoder preserves scanline boundaries and the original maximum 16-pixel
run contract.

## MP3 streams

Extract the sparse stream bank, edit or replace supported stream files, then
rebuild the bank payloads into a separate directory:

```sh
./conker mp3-assets extract
./conker mp3-assets pack \
  --input build/assets/mp3/us \
  --output build/assets/mp3/us-packed
```

The packer retains sparse indices and the three decoder assets. Whole-bank ROM
insertion is not implemented yet.

## Indexed texture PNGs

The ordinary texture families are edited through their indexed PNG files.
Palette order, duplicate colors, alpha values, and pixel indices are preserved
when pixels are unchanged.

```sh
./conker texture-assets extract
./conker texture-assets pack \
  --input build/assets/textures/us \
  --output build/assets/textures/us-packed

./conker texture-assets extract --family 1056-proven
./conker texture-assets pack \
  --input build/assets/textures/us-1056-proven \
  --output build/assets/textures/us-1056-proven-packed

./conker texture-assets extract --family tiled-views
./conker texture-assets pack \
  --input build/assets/textures/us-tiled-views \
  --output build/assets/textures/us-tiled-views-packed
```

## Assembled tiled views

The 360x360 files under `views/` may be edited directly. Save them as
non-interlaced RGB or RGBA PNGs with eight-bit channels, keep the original
indexed files under `tiles/` beside them, and run:

```sh
./conker texture-assets pack --views \
  --input build/assets/textures/us-tiled-views \
  --output build/assets/textures/us-tiled-views-edited-packed
```

The indexed tiles provide each region's palette, transparent RGB values, and
pixels outside the visible 60x30 area. Every edited pixel must exactly match a
color in that tile's existing palette. New colors, blended edges, and
intermediate alpha values are rejected with the view, pixel position, and tile
index. There is no automatic quantization or palette replacement.

Unchanged pixels retain their original indices even when multiple palette
slots contain the same color. The importer also validates the continuous
two-entry stream phase, rejects stale mappings and conflicting edits to shared
tiles, and validates all edits before replacing its output. Source PNGs are
never rewritten.

Without `--views`, texture packing reads the indexed tiles and ignores the
assembled views. The two modes cannot be combined: view import rejects indexed
tiles whose payload hashes differ from the extraction. Older manifests without
continuous-phase metadata require a fresh extraction into another directory.

## Standalone CI8 candidates

The standalone CI8 family remains suitable for reversible experiments, but not
for final artwork replacement yet:

```sh
./conker texture-assets extract --family ci8-proven
./conker texture-assets pack \
  --input build/assets/textures/us-ci8-proven \
  --output build/assets/textures/us-ci8-proven-packed
```

Its local display-list commands prove dimensions, stride, load length, and a
same-index 256-entry TLUT. They do not yet prove that every list is consumed
with the non-null parser argument required to select the trailing 512-byte
palette. Several previews also await runtime appearance validation. Consult
[RZIP and asset extraction](rzip-assets.md#direct-ci8-storage-contracts) before
editing this family.

## Insert packed textures into a ROM

Insert one packed texture set into a newly generated ROM:

```sh
./conker rzip-pack \
  --profile us \
  --input build/assets/textures/us-packed \
  --output build/rzip/us-packed.z64
```

Use the corresponding packed directory for another supported texture family.
Unchanged RZIP chunks are copied byte-for-byte; changed payloads alone are
recompressed. The rebuilt 7,760-entry stream must fit its original
`0x1A37E0:0xAB1941` span. The packer preserves the 15-byte loader gap before the
fixed table at `0xAB1950`, validates every rebuilt entry, and recalculates the
US CIC-6105 header checksum.

An unchanged pack must reproduce source SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. A valid image edit may still be
rejected if its recompressed stream exceeds the fixed ROM capacity.

## Verified editing behavior

A no-edit assembled-view import retains all 2,534 payloads and reproduces the
source ROM byte-for-byte. A controlled 8x8 palette-color edit at the top left
of `group-04-view-1` changed only flat index `5385`; its rebuilt stream occupied
9,494,848 of 9,494,881 available bytes. A separate single-pixel experiment
exceeded capacity by one byte and was correctly rejected. These are packing
checks, not in-emulator validation of edited artwork.
