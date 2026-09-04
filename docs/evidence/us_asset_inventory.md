# Conker ROM asset inventory survey

This is a ROM-derived boundary and fingerprint survey, not a semantic asset
map. It changes no function inventory, source-unit boundary, or generated
mapping output. No ROM bytes or decoded assets are tracked in the repository.

## Storage inventory

The existing two-level indexed-bank parser was already complete for retail US,
debug, and ECTS. The initial survey found that retail US and debug also carry a
flat RZIP stream before that index, just as ECTS does. Each proposed end was
validated by decoding every entry until the short zero-filled alignment gap
immediately before the configured asset table.

| Profile | Flat ROM range | Alignment gap | Flat entries | Flat decoded bytes | Indexed entries | Indexed RZIP | Total entries |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| US | `0x1A37E0:0xAB1941` | 15 bytes | 7,760 | 16,305,205 | 2,518 | 1,670 | 10,278 |
| Debug beta | `0x199BA0:0xABBCFD` | 3 bytes | 7,808 | 16,422,677 | 2,562 | 1,716 | 10,370 |
| ECTS beta | `0x246E10:0xB802DF` | none | 8,427 | 19,848,186 | 2,457 | 1,674 | 10,884 |

The extractor now fingerprints every decoded flat and indexed entry in the
manifest. This makes `--manifest-only` sufficient for comparisons and avoids
retaining asset payloads merely to find cross-version matches.

## Cross-version signal

Content identity is more reliable than entry number. Retail US has 7,684
unique flat payload hashes and debug has 7,732; 7,644 unique hashes occur in
both profiles, but only 202 entries match at the same numeric index. ECTS
shares 5,071 unique payload hashes with retail US while only 10 same-index
entries match. Any naming or format work should therefore correlate by decoded
fingerprint first, then use table position and loader call sites as supporting
evidence.

The generated full-asset report, which includes both flat and indexed entries,
found 8,715 unique hashes shared by US and debug. Only 1,296 retain the same
locator, while 7,502 shared hashes occur solely at different locators. US and
ECTS share 5,697 unique hashes; only 10 retain the same locator and 5,687 are
relocated. The report retains locator arrays for the 80 US/debug and 62
US/ECTS shared hashes with duplicate occurrences instead of choosing an
arbitrary one-to-one match.

## First semantic format candidate

Retail US has a separate, bounded font collection outside both asset streams.
ROM `0x40F10:0x42443` contains 95 records followed by 13 alignment bytes before
the game archive. Each record has:

- width and height bytes at `+0x0` and `+0x1`;
- two still-unknown metadata bytes at `+0x2` and `+0x3`;
- a big-endian total record size at `+0x4`;
- grayscale RLE bytes from `+0x8`, with the high nibble as intensity and the
  low nibble plus one as run length.

All 95 records were walked using their declared sizes, and every RLE stream
expanded to exactly `width * height` pixels. This is a suitable first
format-specific decoder and packer because its boundary, record count, and
round-trip invariant are already testable.

## First indexed semantic family

The US indexed loader is the `game_57FA0` family. `func_1502AC88` indexes an
eight-byte table record, caches recently used records, DMAs a missing record,
and returns the relative span needed to descend to the next table. The wrapper
at `func_1502B5C8` starts at ROM `0xAB1950`, follows a variadic path of indices,
then loads the selected payload. This independently corroborates the two-level
table parsed by `scripts/rzip_archive.py`.

The exact Rare MP3 playback call path provides a semantic consumer rather than
an inference from payload size. The game loads a selected entry from bank
`0x16`, receives its ROM address and byte length, and supplies both to
`mp3_play_file`; all 453 nonempty entries begin with MPEG frame sync.
`mp3_play_file` then loads `(0x17, 4)` into
`var8009c650`, `(0x17, 5)` into `__conker_mp3_lookup_base`, and `(0x17, 6)`
into `__conker_mp3_huffman_base`. The matching decoder then relocates pointer
slots 1 through 33 from entry 4 against entry 6. The matching assembly utility
uses entry 5 as two lookup halves separated by `0x2200` bytes.

The ROM index agrees with every code-derived constraint:

| Locator | Proven role | Decoded bytes | RZIP |
| --- | --- | ---: | --- |
| `bank-17:0004` | 36 big-endian Huffman offsets | 144 (`0x90`) | no |
| `bank-17:0005` | combined lookup tables | 17,408 (`0x4400`) | no |
| `bank-17:0006` | Huffman data | 42,000 (`0xA410`) | no |

`./conker mp3-assets verify` checks the 453 MP3 streams and reconstructs the
offset table, covering 456 raw payloads in total. Extraction writes the streams
as sparse-indexed `.mp3` files, an editable JSON offset list, and the two
still-opaque binary tables; packing emits exact bank-entry payloads for later
integration. Bank `0x17` entries 0 through 3 are not named from their magic
values alone, and no numeric beta mapping is claimed.

Entry 6 has type flag `0x80`; the table above says it is not RZIP-compressed,
not that all noncompression flag bits are clear. A future bank inserter must
preserve that distinction.

## First visual family

The flat RZIP archive is connected to the renderer by code rather than payload
appearance alone. `func_15003570` walks it from `0x1A37E0` to create compressed-
offset and decoded-size tables. `func_1510D0EC` loads a selected flat index into
the `D_800B0E58` cache, and `func_1510BF60` resolves custom display-list texture
opcode `-3` (`0xFD`) against that cache.

Exactly 704 US entries have the bounded 2,080-byte CI4 layout: 2,048 bytes of
64x64 high-nibble-first indices and a trailing 32-byte, 16-color RGBA5551
palette. Most use TMEM-ready odd scanlines with the two 32-bit halves of every
eight-byte group exchanged. Reversing that permutation lowers median adjacent-
pixel edge energy by 46.6 percent and produces coherent images for 701 of the
704 entries. Flat indices 1296 and 1297 are linear 64-pixel particle textures;
1620 is blank and is unchanged by either layout. Directional artwork also proves
that source rows use a bottom-left origin: reversing the rows makes the `MILK`
and `SAFE` lettering in flat index 1063 upright. The schema-3 manifest records
the selected row layout and both image origins rather than guessing during
packing.

`./conker texture-assets extract` represents the family as indexed four-bit
PNGs, preserving palette order and transparent RGB channels. `pack` reconstructs
the original decoded layout, while `verify` proves all 1,464,320 bytes round-trip
unchanged. `./conker rzip-pack` now preserves unchanged RZIP chunks, recompresses
only edited texture payloads, retains the 15-byte zero loader gap, keeps the
table fixed at `0xAB1950`, and updates the US CIC-6105 header checksum. A no-edit
run must reproduce the entire source ROM byte-for-byte.

The first full-ROM gates pass. Packing all 704 unchanged texture payloads
reproduces SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. A deliberate
one-byte decoded edit to flat index 35 rebuilds and validates all 7,760 entries:
only index 35 changes, the other 7,759 decoded hashes remain identical, bytes
before the flat stream and from `0xAB1950` onward remain identical, and the
15-byte loader gap remains zero.

The next decoded-size group demonstrates why shape cannot be inferred from
payload length. There are 1,840 flat entries of 1,056 bytes. A display-list
survey recognizes only direct references whose commands jointly prove CI4,
the trailing palette at decoded offset 1,024, and the render-tile line width.
Thirteen entries have complete, non-conflicting contracts: eight are 64x32 and
five are 32x64. They round-trip through schema-4 indexed PNG manifests without
changing a byte. Twelve other directly referenced entries use `F548` 8-bit
render tiles with 256-entry TLUT loads; survey schema 4 records them as
incompatible with the 16-entry CI4 contract rather than promoting them by
appearance or decoded size.

The dynamic-loader trace now accounts for most of the remaining set without
guessing their format. `func_15000AD0` selects one of seven base indices through
the pointer table at `0x800891BC` and calls `func_1510D0EC` across exactly 360
consecutive flat entries. The survey verifies those code words and table
pointers against the decoded US game archive before accepting the ranges.
They contain 1,573 unique 1,056-byte candidates.

`func_15111AF4` consumes five bases from each of those seven records and calls
`func_15110CFC` with a fixed 60x30 tile step over a 360x360 view. The renderer's
format tables prove that 1,056-byte members use 64x32 CI4 storage with a
16-entry palette at byte `0x400`; the alternate CI8 path uses a palette at
`0x800` and cannot fit a 1,056-byte allocation. The 35 view ranges cover 1,816
of the 1,840 candidates. The renderer also has an exact conditional substitution
path at `0x151111C4:0x15111204`: its bounded coordinate calculation selects the
six entries `5747:5753` before calling `func_1510D0EC`. Four are CI4 and two are
CI8, raising the runtime-proven CI4 count to 1,820. None are now preload-only
and only five lack a recovered runtime reference. Eight runtime CI4 tiles also
appear in the direct 256-entry-TLUT set, proving that those reference classes
overlap. The extractor now preserves 2,526 runtime-selected sources: the 2,520
ordinary grid entries plus the six conditional substitutions. Correct preview
assembly applies the two-entry phase to the
continuous flat stream rather than wrapping the last two rows independently in
each column. Each preview therefore uses `base - 2` through `base + 69`. This
moves displaced upper structure tiles one column right and carries a face's
final pair across the next view boundary. The union adds eight context-only
records and retains fourteen runtime tails, producing 2,534 reversible sources:
1,822 CI4, 707 full-width CI8, and the five compact CI8 records. None of the
compact records is used by the 35 previews after phase correction. A no-edit
tile pack inserted through `rzip-pack` reproduces the complete US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The five still-unreferenced entries are `515`, `517`, `1482`, `1655`, and
`7231`. Each has the exact 64x32 CI4 plus trailing RGBA5551-palette structure,
produces a coherent decoded image, and has a byte-identical counterpart in both
debug and ECTS. None appears in the bounded display-list scan, preload ranges,
ordinary tiled-view ranges, conditional renderer override, game code/data
display lists, or flat-asset display lists. They remain explicitly unresolved;
appearance and cross-version persistence are not sufficient runtime evidence.

## Reference-project lessons

[GoldenEye 007](https://github.com/n64decomp/007/tree/master/assets) separates
proven semantic classes such as fonts, images, music, model/level data, and
demo data. Its image workflow keeps the ROM offset list and semantic name list
as distinct sources, then rebuilds one combined binary. That avoids assigning
meaning from position alone.

[Banjo-Kazooie](https://github.com/n64decomp/banjo-kazooie) extracts its single
asset binary with a dedicated tool into a YAML-backed tree and reconstructs the
binary for the matching build. Conker should follow the same staged contract:
boundary inventory, content fingerprints, proven semantic decoders, and only
then byte-identical repacking and build integration. Neither reference is
evidence that Conker shares its actual payload formats.

## Next bounded work

1. Add direct assembled-view editing without losing per-tile palette
   boundaries; keep the five unreferenced candidates unresolved until another
   loader path supplies runtime evidence.
2. Add indexed-bank insertion only after its packer can preserve flags,
   alignment, and byte-identical unchanged output.
