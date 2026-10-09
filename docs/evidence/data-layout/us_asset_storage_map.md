# US asset storage boundaries in the build map

`config/profiles/us.yaml` now replaces the two opaque binaries beginning at ROM
`0x2D4B0` and `0x1A33E8` with 42 named storage segments. `Makefile` links exactly
those generated binary inputs plus the existing boot input. The independent
raw reference map is unchanged.

These are original ROM storage/container boundaries, not historical C-object
boundaries or decoded runtime addresses. Asset banks remain stored binaries;
semantic subresources inside a compressed entry do not create additional ROM
allocations. No data-completion or objdiff matching credit follows from a split.

## Profile organization

`config/profiles/us.yaml` retains profile options, top-level ROM order, group
extents and alignment, and all main/debugger executable mappings. Detailed
binary subsegment lists live beside it under `config/profiles/us/assets/`:
`font.yaml`, `mp3.yaml`, `bank17.yaml` and `flat.yaml`. For example:

```yaml
    subsegments:
      include: us/assets/font.yaml
```

Each `.yaml` fragment is a plain list of `[ROM offset, bin, name]` rows. Paths are
relative to the root profile's directory and must remain within it; subfolders
are supported and their YAML files remain trackable. Only asset
groups support this form; empty fragments, nested includes, repeated files and
code mappings in fragments are rejected. Keep executable mappings inline so
source-integration transactions continue to edit their original locations.

`scripts/profile_config.py` supplies the shared loader and dependency list.
Profile preparation expands the fragments into ordinary Splat YAML at
`build/config/us.yaml`, preserving comments and hexadecimal offsets and quoting
the ROM path as a YAML scalar. This generated file is never edited or committed.
Asset verifiers, data reports and library audits read the same expanded
structure. Make tracks the root and every included fragment when packing
assets; missing or invalid fragments stop ROM/asset builds. Make plans the
US dependencies, asset bins and executable sources in one parse. US goals load
asset lists by default, including aggregate targets and paths prefixed with
`./`. Packing runs only when the dependency graph reaches the font, MP3 or texture asset
objects; code-only compilation does not require the ROM or run the packers.
Housekeeping, independent library, game, reference and diff goals bypass US
asset planning. Game comparison fingerprints likewise exclude the full-ROM
asset map, which is not an input to the independent game build.
EU targets do not load US fragments. The independent raw
reference profile remains separate and does not resolve these asset files.

Moving rows between these files changes no boundaries, linker input names,
asset bytes or report credit. Validate layout edits against the original ROM
contracts and finish with a byte-identical `./conker build --all`.

The initial split was verified on 2026-10-09 against `99cf6c9`: expansion equals
the original parsed profile exactly (96 font, 822 MP3 and 272 bank-17 rows).
The complete 67,108,864-byte US ROM remained byte-identical. All 2,148 Docker
tests passed with eight skips; progress and whitespace checks passed. These are
historical local results, not shared build artifacts. Reproduce the checks with
`./conker test`, `./conker build --all`,
`./conker game-build --profile us --refresh`, `./conker progress check` and
`git -c core.whitespace=cr-at-eol diff --check`. A fresh checkout also needs
`./conker _prepare-reference --profile us` before the game build. The current
PR records the tested commit and current results; private build logs remain local.

## Evidence

The input is the complete 67,108,864-byte US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. All endpoints below are exclusive.

| Storage | ROM interval | Bytes | Boundary evidence |
| --- | --- | ---: | --- |
| Unassigned after main | `0x2D4B0–0x40F10` | 80,480 | Existing main endpoint; next proven font start |
| Font RLE storage | `0x40F10–0x42450` | 5,440 | Runtime font range; 95 decoded records plus 13 alignment bytes |
| Game archive header/index | `0x42450–0x42C50` | 2,048 | First decoded code-chunk offset |
| Game compressed code | `0x42C50–0x186B50` | 1,326,848 | All 507 XOR-indexed RZIP code chunks |
| Game code gap | `0x186B50–0x188328` | 6,104 | Last code offset to archive data-start word |
| Game compressed data | `0x188328–0x19C7D7` | 83,119 | Data-start word and exact decoder consumption |
| Game data gap | `0x19C7D7–0x19EA88` | 8,881 | Compressed stream end to reviewed archive end |
| Unassigned after debugger | `0x1A33E8–0x1A37E0` | 1,016 | Loader-proven debugger end; flat-stream start |
| Flat RZIP assets | `0x1A37E0–0xAB1941` | 9,494,881 | 7,760 sequential chunks decoded to exact stream end |
| Flat alignment gap | `0xAB1941–0xAB1950` | 15 | Original zero-filled bytes before the outer index |
| Outer asset index | `0xAB1950–0xAB1A40` | 240 | First table word: 30 eight-byte records |
| Indexed banks `00–1C` | `0xAB1A40–0x3F8B770` | 55,418,160 | Each original outer-table offset/size record |
| Raw block `1D` | `0x3F8B770–0x3F8B800` | 144 | Outer-table record with flag nibble 8 |
| Unassigned ROM tail | `0x3F8B800–0x4000000` | 477,184 | Final table-record end to ROM end |

The 29 ordinary banks have separate YAML entries, each using its exact original
offset and size. Their inner indices contain 2,518 payload entries. All outer
banks are contiguous; the bank segments include their inner indices and gaps,
so their byte count is intentionally larger than the sum of child payloads.
The raw `1D` record has no inner asset table.

The font range is consumed by `func_15015920` through the two words at
`D_80082F80`; see [font consumer evidence](../assets/interface/us_font_atlas.md).
The [RZIP guide](../../rzip-assets.md) and
[asset inventory evidence](../assets/models/us_asset_inventory.md) describe the
archive contracts. `scripts/rzip_archive.py` validates the outer/inner table
ordering and bounds, each code-chunk offset and decoder consumption. It does
not identify formats by searching for compressed-data signatures.

The gaps are retained byte-for-byte. `game_code_gap`, `game_data_gap`, and the
unassigned ranges are not asserted to be zero, free space or original section
padding. The debugger remains at its existing ROM/VRAM addresses and is not
expanded to absorb adjacent records.

## Link layout and verification

Each new binary follows the preceding segment's link VMA and uses `align: 1` and
`subalign: 1`.
This prevents implicit alignment from moving unaligned ends such as
`0x19C7D7` and `0xAB1941`. These continuing bin VMAs only preserve the existing
ROM link layout; they are not asset load addresses. The build must compare the
entire output ROM against the validated original, and every generated binary
must equal its mapped original slice.

Validation commands:

```sh
./conker font-assets verify --profile us
./conker rzip-extract --profile us --manifest-only --output build/us/data-boundaries/assets
./conker build --all
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

The manifest output directory must be fresh, or deliberately replaced with
`--force`. Generated binaries, manifests and ROMs remain ignored.

Final validation on 2026-10-08: `./conker build --all` passed with the entire
67,108,864-byte output equal to the original US ROM and SHA-1 above. All 43
binary inputs (42 named storage segments plus boot) independently equal their
original ROM slices. All 30 bank extents agree with the original outer table,
and the Makefile binary list equals the YAML bin list exactly. Font verification
passed for 95 glyphs and 5,440 storage bytes. The 131 focused archive, debugger,
repository-safety and project-state tests passed, along with progress and
whitespace checks. Local checksums are saved in
`build/us/data-boundaries/storage-map-verification.json`; the build log is
`build/us/data-boundaries/storage-build.log`.


## Rebuilt font build input

The named `font_rle` group links the output of the existing font encoder.
Its dedicated Makefile rule initializes `build/fonts/us/` from the checked ROM
only when no manifest exists, then packs its 95 editable PGM glyphs and metadata
into `build/us/fonts/font_rle.bin`. `font_rle` is a byte-aligned YAML group with
95 record subsegments and the 13-byte padding at `0x42443`. The build verifies
these against original record headers, writes each rebuilt part, then links
96 separate objects under `build/us/assets/font/`. Raw splat slices remain
independent references. Each rebuilt record must retain its individual extent;
offsetting length changes in two glyphs cannot hide a shifted boundary.

The build repacks when editable inputs, their directories or build dependencies
change, and recovers missing generated parts. Unchanged part contents retain their
timestamps, so a no-change asset build does not relink its objects. Existing inputs are never refreshed
from the ROM automatically. Invalid/missing inputs fail; the manifest must agree
with the reviewed profile, checksum provenance, record count and storage range.
The final full-ROM comparison remains the acceptance gate for any input edit.
All extracted and packed material stays ignored.

```sh
./conker font-assets build --profile us --input build/fonts/us --output build/us/fonts/font_rle.bin
./conker build --all
./conker objdiff report
```

The dependent data-report change counts these rebuilt bytes in ordinary Data,
without a separate Font or Assets category. Its target is independently wrapped
from the checksum-validated ROM slice; its base concatenates the payloads of the
actual per-record build objects. Both use the normal binary linker wrapper, with no injected symbol sizes. Target extent and bytes are
checked, the candidate must equal a fresh encode of current editable inputs,
and all 96 input file hashes (manifest plus glyphs) are recorded and rechecked.
A changed font remains a compared candidate rather than altering the reference.

Native font coverage is 5,440/5,440 matched and completed stored bytes, including
the 13-byte alignment tail. Completion requires the current editable glyphs and
metadata to encode exactly to the actual ROM linker input and original storage.
The published report combines 201,632 loaded initialized-data bytes with these
5,440 font bytes and 7,508,765 bytes of 6,185 rebuilt textures: 7,715,837 total.
The [texture batch](us_texture_reconstruction.md) documents independent PNG and
compression proof. Current matching and completion measures are
recorded in the validated native report; source grouping can change symbol matches.

Font integration validation on 2026-10-08: `./conker build --all` passed with the
complete 67,108,864-byte US ROM byte-identical after linking the rebuilt font.
Tests cover preserved pixel/metadata edits, missing glyph rejection, independent
asset target bytes and completion accounting. The full build log is
`build/us/data-boundaries/font-complete-build.log`; report validation is under
`build/us/objdiff-report/`. See [the published report scope](../../objdiff.md#scope).

## Rebuilt MP3 bank build input

Bank `0x16` is a group in `config/profiles/us.yaml` with 822 explicit subsegments.
It links individual rebuilt inputs for 453 encoded MP3 files, an index containing
462 original records, and 368 verified padding files. Its 23,586,160-byte
stored range is verified by the packer and complete ROM build. MP3 storage is
excluded from the objdiff comparison report. See
[the bank build evidence](us_mp3_bank_build.md) for exact ranges, edit constraints,
report accounting and the complete ROM check.

## Bank-17 sound banks and sequences

Bank `0x17` is now a group with 272 explicit YAML/linker inputs, including
149 individually bounded compact sequences. These raw storage ranges are
currently outside the published report scope. See the
[bank-17 boundary evidence](us_audio_bank17_boundaries.md).


Font record integration was verified on 2026-10-09 against main `1716856`.
The complete US ROM still matches after replacing the aggregate font object
with 96 YAML-driven linker inputs. Log: `build/us/data-boundaries/font-splits-build.log`.
