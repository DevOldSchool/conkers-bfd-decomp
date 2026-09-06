# US HUD/menu metadata evidence

The US game overlay has one shared text/layout path whose consumers prove two
small metadata tables without relying on filename, payload-size, or visual
guesses. `./conker hud-assets extract` exports those bytes and a descriptive
manifest under `build/assets/interface/us/`; it does not duplicate textures.

## Glyph mapping

`func_15042C40` folds ASCII `a` through `z` to uppercase, returns glyph index
`0x60` for a space, and scans 95 bytes beginning at `D_80085930`. The table is
therefore an input-byte-to-glyph-index order, not a font bitmap. The extractor
preserves all 95 bytes in `glyph-map.bin` and lists their Latin-1 values in the
manifest. The actual grayscale font glyph bitmaps remain owned by
`./conker font-assets`.

## Dynamic layout records

`func_15042ECC` allocates `0x5c` bytes for each linked layout record and fills
the code-observed fields: attached-object pointer, scale, signed X/Y, raw flags,
kind selector, two four-byte color/metadata groups, next pointer, and a 64-byte
inline text buffer. A kind of zero follows the text renderer. A nonzero kind is
decremented and multiplied by eight before indexing `D_800859E0`.

These records are built dynamically from runtime text/control templates. The
manifest records the layout schema, but does not pretend that the current static
evidence provides complete named screens or final per-language placements.
It also records every direct code call site: 87 calls supply X/Y and a template
to `func_15042D94`, 35 use the current position through `func_15042E3C`, and 18
update that position through `func_150432FC`. Most template pointers are loaded
from runtime/localization tables, so those call addresses are a reproducible
frontier rather than guessed screen names.

## Sprite selector table

The table begins at `D_800859E0`. Its end is exact: `D_80085CC0` is the parser's
next separately addressed object and begins with `%s%s        \0`. The resulting
`0x2e0` bytes contain 92 eight-byte records.

`func_15043384` reads bytes 0 and 1 as nested tile counts, byte 2 as a scale
multiplied by `1/128`, byte 3 as raw flag bits, and the big-endian word at +4 as
a resource index. `func_151ED430` copies that word to its image descriptor and
passes it to `func_1510D0EC`, proving that it is a flat-asset index. The 92
records reference 86 distinct base indices. Their raw distributions are:

- tile columns: 33 one-column, 42 two-column, 17 three-column;
- tile rows: all one row;
- scale bytes: 88 at `0x80`, four at `0x55`;
- flags: 75 zero, 15 one, two two.

The flag bits retain their numeric value because the renderer establishes
behavior, not stable semantic names. Bit 1 has one concrete image effect:
`func_15043384` changes both descriptor dimensions from 32 to 16 before drawing
selectors 59 and 60. Bit 0 selects an additional tinted render pass, but the
tool does not assign that pass a semantic label.

The shared renderer descriptor at `D_80090060` defaults each tile to 32 by 32
RGBA32 pixels. The nested renderer loop advances through the full resource span,
so the preview follows every selector rather than exporting only the base
indices. This reaches 159 flat entries. RGBA32 uses paired 64-bit TMEM words, so
the PNG conversion exchanges the two eight-byte halves of each 16-byte group on
odd rows. Applying the four-byte half swap used by narrower formats corrupts
edges and produces horizontal breaks; flat index 2023's joystick is a reviewed
example. The conversion does not vertically flip the source: these sprites are
stored top-to-bottom, unlike the bottom-origin texture families. That
distinction is visible in directional artwork and menu words such as `GAME`.

Visual review establishes that the shared RGBA32/TMEM rule is not a truthful
preview rule for every referenced payload. Flat index 2202 forms coherent
RGBA32 artwork only in linear row order and backs selector 57. The 2,048-byte
payloads at flat indices 2171, 2198, and 2215 are not 32x32 RGBA5551 images:
that construction halves their horizontal resolution and invents magenta and
green colour. They instead form clean 64x32 I8 `Dang...`, `Poops`, and `Total`
labels after the narrower odd-row TMEM word swap.

The Spriters Resource
[Pause Menu & Multi Results sheet](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/)
provides a visual cross-check for several smaller assets. Selector 4's
1,024-byte flat 2199 is a 32x32 I8 question-mark icon, and selector 52's
2,048-byte flat 2172 is a 64x32 I8 `Dino` label. Both require the narrower
odd-row TMEM word swap. The same sheet also exposes selector 59's failure as a
source-size problem: all 4,096 bytes of flat 2224 form the green `0` digit as a
32x32 RGBA32 image, while the selector's flag still records a 16x16 renderer
dimension. The manifest retains both dimensions and labels these three reviewed
identities explicitly.

Selectors 76 and 89 deliberately share flat indices 2147-2148. The ROM table
distinguishes them with scale bytes rather than different pixels: selector 76
uses `0x80` (1.0), while selector 89 uses `0x55` (0.6640625). Their extracted
source PNGs are consequently byte-identical. The HTML gallery applies the
recorded scale to its displayed thumbnails and labels the relationship so this
runtime reuse is not mistaken for an extraction duplicate.

Flat index 2041 (selector 23) and flat index 2225 (selector 60) remain raw-only.
The reference sheet narrows the expected artwork but does not supply the missing
storage contract. Flat 2041 is 3,072 bytes and does not contain the 4,096-byte
RGBA32 window selected by its 32x32 renderer metadata. Flat 2225 is 1,440 bytes;
none of its aligned 1,024-byte windows forms the 16x16 RGBA32 image selected by
its flag, and bounded RGBA16, intensity, and CI alternatives remain incoherent.
The tool therefore does not replace either payload with a visual guess.
Selector 69 remains a valid three-tile TMEM preview: it is a rolling window
across adjacent menu-label fragments, not one standalone named sprite.

Selector 61 has a reviewed identification from a supplied visual reference: it
is the N64 directional C-button row, ordered C-left, C-up, C-right, C-down. Its
1,024-byte base payload at flat index 2222 is a 16x16 TMEM-ordered RGBA32 C-left
button, not a 32x8 linear strip. The adjacent flat index 2223 is the matching
C-right button. Pixel comparison against the reference establishes C-up and
C-down as clockwise and counter-clockwise quarter-turns of the C-left pixels.
The manifest records those presentation transforms and their source indices;
the raw payloads remain byte-identical.

Selector 87 has a reviewed identification as the Nintendo wordmark. Its two
runtime-span resources, flat indices 2139 and 2140, are not useful RGBA32
previews: that construction compresses four intensity samples into one coloured
pixel. Treating each 4,096-byte resource as a 64x64 I8 tile and undoing the
narrower-format odd-row TMEM word swap reconstructs only `Ninten`. The adjacent
flat 2141 is the matching `do` plus registered-mark continuation. The preview
therefore records the runtime span as 2139-2140 while separately recording the
reviewed logical composition 2139-2141; the latter produces the complete
monochrome wordmark without hiding the metadata discrepancy.

The resulting preview contains 159 resource PNGs and 90 previewable selectors
while preserving all 161 raw payloads. A short payload that contains a whole
number of source rows is emitted at that encoded height rather than padded. The
manifest records the code-selected renderer size separately from any reviewed
source-pixel dimensions, along with preview size, format, row layout, bytes
used, trailing-byte count, and any raw-only reason for every resource.

Selector 26 is independently animation-backed. `func_15043384` compares its
selected record address with `D_80085AA8` and adds a six-value triangular time
offset to base flat index `0x7e7`. The manifest records the reachable indices
`0x7e7` through `0x7ec` without naming the animation.

## Reproduction

```sh
./conker hud-assets survey
./conker hud-assets extract
./conker hud-assets preview
./conker hud-assets verify
```

Verification checks the owned US ROM checksum, the relevant game-code
instructions, both raw data tables, the exact table boundary, the generated
manifest, and byte identity of the extracted binary metadata.
