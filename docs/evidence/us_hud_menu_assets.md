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

## Runtime IDs and complete visual review

The compressed-size table `D_80091D20` is authoritative for resource IDs.
`func_1510D0EC` indexes its 7,762 unsigned-halfword entries and returns an empty
sentinel for zero-size slots. `func_1510D374` sums preceding entries onto ROM
base `0x1A37E0`. Slots 1767 and 1768 are empty, so there are 7,760 physical
streams. A physical stream ordinal is not the resource ID. The extractor now
uses `iter_indexed_flat_rzip_entries`, validating every extent and preserving
those slots. The full US ROM hash and loader instruction signatures are checked.

The previous iterator skipped these empty slots, selecting every HUD payload
two streams too late. Earlier I8, size, rotation and extra-tile exceptions were
based on those wrong payloads and are superseded. The corrected 159 sources
all use RGBA32, the code-selected dimensions and standard odd-row TMEM layout.
All 92 selectors now have previews, with no raw-only resources. Selector 26
contains all six analog-stick frames; selectors 59 and 60 are 16x16 C-left and
C-right buttons. Selector 69 is the complete BARN BOYS label.

All 92 selectors and 97 exported PNGs were individually reviewed against the
seven supplied sheets. There are 85 visual matches and seven coherent images
absent from the supplied sheets. Every selector has a descriptive name and
named PNG; unmatched references are explicitly noted. See the
[complete checklist and reference evidence](us_interface_reference_review.md).

The user-identified Uga Buga artwork belongs to selector 10, resource 2220.
Selector 56 is the tank turret icon (resource 2218), corroborated by the
user-supplied Tank setup screenshot; selector 57 is radar. The previous
"Green tank" name remains a search alias and its export filename is retained. The previously pictured Rare
logo is physical stream 2202, runtime resource 2204, outside this selector set.
The complete prior gallery, source and metadata were preserved under
`build/hud-reference-review/before-index-fix/` before regenerating outputs.

Selectors 76–79 share source pixels with 89–92, respectively. The former use
scale 1.0, the latter 85/128. The gallery applies the recorded scale while
keeping both selector IDs and source PNGs. Dark/bright labels describe source
pixels; they do not claim a selected/disabled runtime state.

Selector 26 is independently animation-backed: `func_15043384` compares the
record address with `D_80085AA8` and adds a six-value triangular time offset to
resource ID `0x7e7`. The six reachable runtime IDs are `0x7e7` through `0x7ec`.

## Additional artwork outside the selector table

Correcting the resource index initially removed artwork that had appeared under
incorrect selectors. The gallery now includes 40 named artwork groups from 74
separate runtime resources under **Additional artwork**, without assigning them
a HUD selector or claiming runtime placement. The latest batch adds the 18
menu/icon groups identified by the full reference audit:

| Artwork | Runtime resource IDs | Export size | Source format |
|---|---|---|---|
| Nintendo wordmark | 2141–2143 | 192×64 | I8 |
| Rare logo | 2204 | 16×16 | RGBA32 |
| Blue A buttons, dark and bright | 2164–2165 | 64×32 | RGBA32 |
| Green B button, dark | 2168 | 32×32 | RGBA32 |
| Green B button, bright | 2169 | 32×32 | RGBA32 |
| Red circular button | 2207 | 32×32 | RGBA32 |
| Red six digit | 2210 | 32×32 | RGBA32 |
| Green zero digit | 2226 | 32×32 | RGBA32 |
| Digit 1 | 2192 | 32×32 | RGBA32 |
| Digit 2 | 2219 | 32×32 | RGBA32 |
| Digit 3 | 2216 | 32×32 | RGBA32 |
| Digit 4 | 2178 | 32×32 | RGBA32 |
| Digit 5 | 2177 | 32×32 | RGBA32 |
| Digit 7 | 2209 | 32×32 | RGBA32 |
| Digit 8 | 2176 | 32×32 | RGBA32 |
| Digit 9 | 2191 | 32×32 | RGBA32 |
| Dollar symbol ($) | 2038 | 32×32 | RGBA32 |
| Dang... label | 2173 | 64×32 | IA8 |
| Dino label | 2174 | 64×32 | IA8 |
| Poops label | 2200 | 64×32 | IA8 |
| Question-mark icon | 2201 | 32×32 | IA8 |
| Total label | 2217 | 64×32 | IA8 |
| START button, dark | 2206 | 32×32 | RGBA32 |
| BEACH heading | 1977–1979 | 96×32 | RGBA32 |
| Skull icon | 1980–1983 | 64×64 | RGBA32 |
| CHAPTERS heading | 1994–1996 | 96×32 | RGBA32 |
| GAME1 heading | 2011–2013 | 96×32 | RGBA32 |
| GAME2 heading | 2014–2016 | 96×32 | RGBA32 |
| GAME3 heading | 2017–2019 | 96×32 | RGBA32 |
| OPTIONS heading | 2035–2037 | 96×32 | RGBA32 |
| RACE heading | 2056–2058 | 96×32 | RGBA32 |
| RAPTOR heading | 2059–2061 | 96×32 | RGBA32 |
| WAR heading | 2082–2084 | 96×32 | RGBA32 |
| BACK heading | 2097–2098 | 64×32 | RGBA32 |
| Small P1–P4 badges | 2115 | 32×32 atlas; four 16×16 crops | RGBA32 |
| HEIST heading | 2180–2182 | 96×32 | RGBA32 |
| Small statistics icons | 2183–2184 | 64×32 atlas; eight 16×16 crops | RGBA32 |
| MULTI heading | 2188–2190 | 96×32 | RGBA32 |
| PAUSED heading | 2193–2195 | 96×32 | RGBA32 |
| TANK heading | 2212–2214 | 96×32 | RGBA32 |

The five IA8 images previously used I8, which lost their separate intensity and
alpha nibbles. IA8 correctly retains transparent `0xF0` background pixels;
Nintendo remains I8. These reviewed source-image contracts consume complete
payloads with standard TMEM row conversion, without padding or truncation.
Nintendo and Rare have Intro Credits reference links; A/B artwork has Text
reference links. These identify artwork, not an exact brightness variant or a
runtime screen.

The complete coloured digits 0–9 and dollar symbol also match the Pause Menu &
Multi Results sheet (62744). Every opaque pixel matches the located reference
crop exactly; the PNGs preserve the original ROM alpha. Reference boxes and
PNG hashes are recorded in the machine-readable interface review. These are
individual 32×32 RGBA32 images, not regions cut from a larger atlas.

The ordered digit tables at `D_80090074` and `D_80090B34` contain runtime IDs
`2226, 2192, 2219, 2216, 2178, 2177, 2210, 2209, 2176, 2191`.
`func_151EADFC` divides the displayed number by powers of ten, indexes the first
table with the quotient (`0x151EAEC8`–`0x151EAF28`), and issues RGBA32 commands
with a 32×32 tile extent (`0x151EAF3C`, `0x151EAFD0`–`0x151EAFD4`).
`func_151EB06C` loads dollar resource `0x7F6` (2038) at `0x151EB870`, draws it
through `func_151ED430`, then invokes the decimal renderer. The normalized US
ROM confirms these tables and instruction words; the digit table SHA-1 is
`f86d7092a64500d66e3f92524291d4211e52def1`. The dollar payload SHA-1 is
`bbefdcfc5eb0045640edb74a9471c7e54fb49679`.

The skull combines four tiles in column-major 2×2 order: 1980 at top left,
1981 at bottom left, 1982 at top right and 1983 at bottom right. The other new
multi-resource headings use horizontal tile order. Every source tile retains
its full RGBA32 payload and standard TMEM odd-row conversion.

The two packed groups also provide twelve individual 16×16 PNG downloads.
Resource 2115 contains P1–P4 in top-left, top-right, bottom-left, bottom-right
order. Resource 2183 contains the stopwatch, money bag, RIP gravestone and green
roll; resource 2184 contains the skull, green crosshair, gray projectile and
purple head with impact marks in the same quadrant order. Their two full atlas
previews remain available. Crops copy exact decoded RGBA bytes without scaling,
vertical flipping or alpha changes. Each crop record retains its coordinates
in the composed atlas (`x`/`y`), dimensions, original raw resource ID
(`source_resource_id`) and output path.

Each additional group has a PNG download and raw resource links. The manifest
retains ROM extents, runtime IDs and payload hashes, and verification checks
metadata and every exported byte, including the twelve crops. The forty group
previews and twelve crops make **52 additional PNGs**. Existing selector PNGs,
named copies and raw sources are unchanged. The gallery contains **132 cards:
92 selectors and 40 additional groups**; crops appear within their atlas cards.
Historical exports remain preserved in the recovery snapshot. The full
reference audit records unresolved image families separately; this batch does
not establish complete coverage of every reference sheet.

## Reproduction

```sh
./conker hud-assets survey
./conker hud-assets extract
./conker hud-assets preview
./conker hud-assets verify
```

Verification checks the owned US ROM checksum, consumer and loader instructions,
both raw metadata tables, table boundaries, runtime resource identity, exact ROM
extents, decoded pixels, named PNG equivalence and generated gallery HTML.
Names and reference links describe visual artwork, not runtime screen placement.

The grayscale font has a separately proven connection to the input map; see
[US font atlas](us_font_atlas.md). Its independent storage is unaffected by the
flat-resource indexing fix.
