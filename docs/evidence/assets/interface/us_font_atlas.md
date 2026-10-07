# US font atlas and runtime character mapping

The atlas exports all 95 source grayscale RLE glyphs as individual PNGs and a
16-column PNG atlas, with source rectangles, input bytes and logical metrics in
`preview-manifest.json`. The HTML page provides a searchable contact sheet,
downloads and a source-pixel sample-text preview. Generated assets remain under
ignored `build/fonts/us/preview/`.

## Consumer evidence

The original extraction's `codepoint = 0x30 + record_index` is a compatibility
identifier, not the font's character encoding. Existing PGM filenames, manifests
and packing stay compatible. The new preview uses the actual lookup map.

- `func_15015920` reads `D_80082F80`, whose US data words are exactly
  `0x40F10, 0x42450`, and walks that ROM font range by each record's size. It
  passes sequential record indices to `func_15015A38`.
- `func_15015A38` writes four-byte metrics at `D_80085994[index * 4]`:
  source width plus one, source height plus one, header byte 2, header byte 3.
  It builds the corresponding pixel-pointer array at `D_80085990`.
- `func_150428D4` calls the HUD lookup `func_15042C40` and indexes that same
  metrics table. This connects the 95 bytes at `D_80085930` to the extracted
  font records; the connection is not inferred from equal table lengths.
- The lookup folds ASCII lowercase to uppercase. Space uses special index
  `0x60`, advances four logical pixels and contributes a minimum line extent
  of 12. It has no extracted glyph bitmap.
- For ordinary glyphs, measurement adds `source_width + header_byte_2` to the
  horizontal advance. The line extent is `source_height + 1 + header_byte_3`.
  `func_150417AC` uses these unsigned bytes as horizontal and vertical offsets
  in its draw path. The preview calls them offsets, not a typographic baseline.

`scripts/font_preview.py` verifies 65 font-consumer instruction words and the
font-range data, in addition to the existing HUD code/table checks and full US
ROM checksum. An altered consumer or mismatched extraction range fails closed.
The raw references are in `asm/nonmatchings/game_42DD0/func_15015920.s`,
`func_15015A38.s`, and `asm/nonmatchings/game_6EA90/func_15042C40.s`,
`func_150428D4.s`, `func_150417AC.s`.

## Mapping and preview limits

The map contains 93 distinct input bytes. `EA` occurs at glyphs 81 and 83;
`F4` occurs at 89 and 91. Lookup chooses the first occurrence, so glyphs 83 and
91 are explicitly marked shadowed while their original pixels remain exported.
Input-byte labels use Latin-1 for display only; this is not a Unicode font map.
Unsupported sample-text characters are omitted with a visible message. The
runtime's fallback-to-input-byte and text control codes are not emulated.

PNG pixels use white RGB and the exact source intensity as alpha (0 through
240, without normalization to 255). The atlas has two pixels of transparent
padding around each source rectangle. Individual PNGs contain no extra border.
The sample applies logical source offsets and spacing; it does not claim the
runtime's inserted borders, TMEM arrangement, filtering, scaling or effects.

## Reproduction and validation

```sh
./conker font-assets extract
./conker font-assets preview
./conker font-assets verify --preview build/fonts/us/preview
./conker font-assets pack --input build/fonts/us --output build/fonts/us-packed.bin
```

Verification rebuilds all 99 preview files from the checksum-validated ROM,
including every PNG, the atlas, mapping binary, JSON and HTML. It rejects stale
mapping, changed images and stale page output. Source extraction/packing still
reconstructs all 5,440 font-storage bytes exactly.

The focused tests cover atlas pixel placement, preserved intensities,
noncontiguous input mapping, shadowed records, logical metrics, stale/corrupted
output and changed code/range evidence. Browser QA covers lowercase equivalence,
four-pixel spaces, unsupported text, duplicate filtering, downloads and responsive
layout. These checks establish the source preview, not native RDP appearance.

## Complete reference review

All 95 glyphs were visually reviewed against the supplied
[Text sheet](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62746/).
66 glyphs match the reference alpha/intensity pixels exactly. The other 29 are
absent from that sheet; no extraction defect was found and no pixels or input
mapping were changed. Per-glyph coordinates, hashes and limits are recorded in
the [complete interface review](us_interface_reference_review.md) and its JSON.
This bounded font storage is independent of the corrected HUD resource index.

## Chapter selection text

The user-supplied chapter screenshots use this same glyph set for their small
subchapter lists. These are ROM strings rendered through the ordinary font path,
not a separate chapter font:

- Indexed US archive entry `[0x1C, 0, 2]`, compressed ROM extent
  `0x3F8B180..0x3F8B378`, decodes to 864 bytes of chapter/menu strings.
  `func_151E6964` loads its 71 source strings into an 80-slot runtime pointer
  table at `D_800E0B88`.
- `func_151DF574` reads that table and calls `func_15042D94` at `0x151DFDF0`
  with x = 148, y = the current line position plus 15, and flags `0x81`.
  Successive lines advance 11 logical pixels.
- The preceding call to `func_1504332C` at `0x151DFD9C` applies chapter RGB
  values from `D_8008FF08`, modified by the selection/dimming factor, plus alpha.
- `func_15042D94` forwards to `func_15042ECC`, which queues ordinary text.
  `func_15043384` draws the black shadow at offset `(1, 1)` and the coloured
  foreground through `func_150417AC` at `0x15043644` and `0x150436A8`.
  This is the same glyph renderer and metric/lookup path described above.
- The chapter strings contain ordinary ASCII. `func_150417AC` calls the glyph
  lookup at `0x15041BD8` and clears its local font-bank selector to zero at
  `0x15041BDC`. The ordinary glyph path reads bank 0 metrics from `D_80085994`
  at `0x150421A4..0x150421C8` and pixels from `D_80085990` at
  `0x15042300..0x1504230C`. The chapter-list function does not override the
  normal text scale of 1.0; viewport scaling and filtering affect the displayed
  result.
- The only direct `func_15015920` call found in the decompressed US game code,
  at `0x150078F0`, loads font bank 0. Its range is the already exported
  `0x40F10..0x42450`; the next four range-table slots are zero. This bounded
  inspection found no second populated font bank.

The large decorated chapter titles are complete image assets, exported as HUD
selectors 66 through 74 (HUNGOVER through HEIST). The blue CHAPTERS heading is
additional artwork assembled from runtime resources 1994 through 1996.
Their lettering should not be treated as another reusable glyph atlas.

A visual comparison of the BARN BOYS and HUNGOVER lists is saved under ignored
`build/hud-reference-review/chapter-font-comparison.png`. It compares screenshot
crops with the existing glyph pixels at 2x nearest-neighbour and bilinear scale.
The illustrative colours and filtering are not a native RDP pixel match; the
ROM string/consumer chain establishes the font connection independently.
