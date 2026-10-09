# US texture reconstruction

The canonical flat YAML now selects **6,422 distinct textures**. The new batch
adds 210 complete texture-storage sources to the fully passing 6,212-texture
checkpoint committed as `a68eb77`.
Batch validation is recorded below; earlier passing checkpoints are retained.

## Selection and resource identity

The game has 7,762 runtime flat-resource slots but 7,760 physical streams.
Runtime slots **1767 and 1768 are empty**. Source contracts therefore resolve
consumer IDs through the validated compressed-size table at `0x80091D20`.
File and linker-part names retain physical stream ordinals; runtime IDs are
recorded explicitly in each extended source manifest. The size table must cover
the whole archive, and every nonempty extent must equal its decoded RZIP span.

The selected families, deduplicated in this order, are:

| Source contract | Distinct textures |
| --- | ---: |
| Existing square CI4 | 704 |
| Direct CI8 | 757 |
| Direct RGBA16 | 10 |
| Direct native formats | 144 |
| Direct rectangular CI4 | 15 |
| Runtime tiled ranges | 2,524 |
| Reviewed HUD selector resources | 159 |
| Additional reviewed HUD/menu artwork | 74 |
| Model material consumers | 1,190 |
| ROM animation frame sets | 24 |
| ROM defaults and texture bindings | 64 |
| Complete declared TMEM storage | 261 |
| Additional character selectors | 80 |
| Additional complete storage layouts | 170 |
| Bound selector storage | 5 |
| Specialized attachment storage | 1 |
| Indexed mipmaps with IA4 detail | 3 |
| Explicit authored storage tiles | 4 |
| Attachment-action expression selectors | 2 |
| Complete object/attachment binding variants | 21 |
| CPU renderer descriptors | 210 |
| **Total** | **6,422** |

The tiled runtime catalog has 2,526 resources before deduplication: 1,822 CI4
and 704 CI8 payloads. Two already have direct contracts. Only actual runtime
ranges and the validated six-resource override qualify; the legacy gallery's
neighbor/phase adjustment is not used for matching. Direct sources use
consumer dimensions, not legacy preview-shape overrides. Reviewed HUD sources
retain their top-left origin; the other texture codecs preserve their existing
bottom-left source interpretation. A partial HUD preview cannot qualify as a
full reconstruction. Additional artwork has reviewed source-pixel contracts;
this does not establish its runtime placement.

The audit supersedes an uncommitted 3,873-entry trial that used older surveys'
physical indices as runtime IDs. That trial passed byte reconstruction, but
its consumer associations were not sufficient evidence. Corrected runtime
bundles live at `build/assets/texture-build/us/runtime/<physical-index>/`.
Earlier local bundles, including the pilot and all square sources, are
preserved without overwriting them. Existing gallery extraction behavior is
unchanged; the build explicitly supplies runtime-indexed entries to the surveys.

## Model consumer evidence

The additional catalog parses model banks 01, 03, 04 and 09 and reuses their
validated texture resolvers. It also checks ROM render-state consensus,
animation frame arrays, character defaults, object/scene bindings and reviewed
attachment/UI state. Each source manifest records its concrete model/material
consumer or frame-set binding. Runtime resource IDs remain distinct from
physical storage ordinals.

A preview qualifies only when decoding its PNG recovers the **entire original
payload**, including all palette entries. Cropped images, transformed alpha,
unrepresented mip levels and trailing bytes receive no credit. Missing consumer
evidence or a changed reference ROM fails closed. Overlapping consumers are
counted once and all 4,387 previous source bundles retain their hashes.

The independent census found 1,278 new complete payloads, totaling 1,821,586
stored bytes. Fresh compression reproduced all of them: 1,250 with default
zlib and 28 with GNU gzip. The production catalog returns exactly the same
resource set as the independent model, frame and binding audits.

## Complete mipmaps and character selectors

The TMEM expansion uses the descriptor captured at LoadBlock time, rather than
assuming that the final render tile still describes the transfer. It requires
an explicit zero-DXT load covering the complete pixel payload, valid TMEM
capacity, a matching same-resource TLUT for indexed formats and an explicit
contiguous chain of render tiles. Tile masks, shifts, formats, strides and
offsets must agree. Gaps, overlaps, missing levels and unrepresented tails do
not qualify. RGBA32 strides and offsets account for both TMEM banks.

The 261 resources comprise 245 mip chains and 16 complete single-level views.
They contain 136 CI8, 106 CI4, 11 I8, three IA8, three RGBA32 and two IA4
payloads. Each declared level becomes its own PNG, including texels outside
the visible bounds when the tile's row stride is wider. Indexed level PNGs
each preserve the full shared palette; packing requires those palettes to
agree and appends the palette exactly once. All source bytes are represented
by images; no opaque tail or copied ROM bytes supply missing content.

Source manifest schema 2 records the level file list, offsets, storage and
visible dimensions, and palette size. Every PNG participates in input hashing,
Make invalidation and race checks. Existing schema-1 bundles are unchanged.

The selector expansion checks initializers, both additional three-state blink
table entries, verified instance variants and stored expressions. Native
consumer hashes guard the three-byte blink-table stride and the expression
application path. With a zero action selector, texture selector writes follow
the morph writes unconditionally; the matching-only resolver therefore retains
the original morph record while resolving its texture choices. It does not
change the gallery's stricter expression preview policy or claim to render that
morph state. Nonzero actions, reserved state and overflowing blink codes remain
excluded. Zero texture overrides retain initializer selections.

Independent audits found exactly the same 341 additional resources as the
production catalog. Every level round-trips and fresh compression recovers
all 351,130 added stored bytes: 327 default-zlib and 14 GNU-gzip streams.
All 5,665 prior source contracts and input hashes are preserved.

## Additional storage layouts

The next complete-consumer audit adds 169 resources: 112 CI8, 52 CI4, four
RGBA16 and one IA8. Every prior contract is resolved first, so the 6,006
checkpoint bundles retain their exact manifests and image hashes.

Of these additions, 152 have unloaded zero alignment after the explicit image
levels: 151 have 16 bytes and one has 48 bytes. The pixel storage ends at the
next 64-byte boundary, followed by the full palette when indexed. Schema 3
records the alignment offset and size. Initialization verifies the original
bytes are zero; packing generates those zeros. There is no opaque tail input.
Nonzero tails, missing image levels and any different alignment fail closed.

Fourteen resources explicitly load 2,112 CI8 pixel bytes with a 48-byte stride
and 44 rows, followed by a full TLUT upload. All stored texels, including stride
texels outside the visible 44-column bounds, are PNG inputs. The source contract
records the 64-byte pixel/TLUT overlap. It proves the source storage, not that
every source texel remains visible after the later palette upload. Shared
renderer decoders retain their existing lower-TMEM restrictions.

Three complete mip chains have clamped non-power-of-two dimensions. Each
non-power-of-two axis must be clamped, its mask period must equal the next
power of two, and its mip shifts, strides, offsets and loaded extent must
still agree. No additional row or omitted level is supplied to satisfy a load.

The initial first-consumer census found 137 candidates. Examining every
consumer recovered 24 more whose later consumers explicitly load another mip
level. The five native-format alignment cases and three clamped chains bring
the independently checked total to 169. Fresh PNG reconstruction and compression
recover all 209,329 additional stored bytes: 162 default-zlib and seven GNU-gzip
streams. Source inputs now contain 7,580 PNGs.

Independent texture reference objects use four bounded workers. Each worker
keeps its own output directory, fresh compression and actual-link-input checks.
Results retain catalog order, worker errors propagate, and the report still
rechecks all source, link-input and reference hashes before publishing a local
snapshot. The change does not cache away any verification gate.

## Bound sources and mixed detail storage

Five additional CI8 resources use authenticated character-selector pointers:
runtime IDs 1300, 2616, 3268, 3266 and 3826. The existing ROM-default resolver
must accept the chosen initializer or blink state. Only zero-origin pixels and
the same segment's exact trailing palette are relocated into a direct storage
contract; all captured load bindings remain consistent. The complete-storage
gates then validate every declared level. Specialized attachment state proves
one additional complete CI8 source, runtime ID 1288, from model 09:165 run 5.

Runtime resources 2689, 3525 and 1141 each contain five indexed mip levels and
one native IA4 detail plane. The existing detail resolver proves the render
state, source bindings, formats, bounds, load span and mip/detail semantics.
The matching contract additionally requires the declared planes to cover
contiguous source storage. Schema 4 records each plane's format and role.
Indexed PNGs retain their entire shared palette; the IA4 PNG has no palette.
Packing joins all six image planes, generates the verified zero alignment
where present, and appends the shared palette once. The CI8 resource has 16
alignment bytes; both CI4 resources have none. Missing detail images, changed
texels, disagreeing palettes, gaps and unrepresented tails fail closed.

RGBA32 runtime resource 2733 has 2,720 declared image bytes followed by 96
verified zero bytes to a 128-byte source boundary, accounting for both TMEM
banks. Only RGBA32 permits this doubled alignment; other formats retain the
64-byte rule. Fresh PNG reconstruction and compression recover all ten new
streams, totaling 14,404 stored bytes, with default zlib. All 6,175 prior
contracts and source inputs are unchanged.

## Authored storage tiles and attachment-action selectors

Four CI8 sources, runtime IDs 4255, 4252, 4254 and 1553, have explicit tile-0
storage declarations immediately after their pixel and palette loads. The
actual draw keeps tile 1 and can combine bytes retained from previous loads.
The matching resolver verifies the exact native command sequence through the
first face, including source IDs, load commands, SetTile and SetTileSize. It
rejects inherited tile state and any intervening transfer or call. The source
contract records both tile identities, command offsets, bytes and a hash.
Complete storage is 16 by 32 or 32 by 32 CI8 texels with all 256 palette entries.
This adds 2,333 stored bytes without changing the shared composed-TMEM preview.

Two further CI8 resources, runtime IDs 3650 and 3651, are selected by Conker's
stored expression records 22, 23 and 31. Their nonzero actions are separately
verified by `model_expression_constructors`: exact whole-function and source
hashes guard the selector tables, dispatcher, constructor and loaders. Every
admitted operation is an attachment constructor (dispatch kind 1 or 2); parent
modification dispatch is excluded. The expression caller ignores the action
return value and writes the texture selectors afterwards. Matching records the
original action, preset, complete program and consumer hashes. It does not
claim action activation, allocation success, attachment placement or a rendered
morph state, and the shared gallery's expression policy is unchanged.

Both expression textures pass the existing full-payload preview inverse gate.
They add 969 stored bytes. All six new sources round-trip and freshly compress
exactly with default zlib. All 6,185 earlier contracts and input hashes remain
unchanged at this intermediate six-source stage.

## Complete binding variants

Existing object, attachment, callback, timer and UI resolvers validate every
image in each admitted binding list, while their previews select one image.
The matching catalog now also considers the remaining already-validated
variants. It reproduces each resolver-recorded PNG hash without changing the
binding list, original selector state or shared preview policy, then requires
the inverse PNG to recover the complete payload. Image shape, format, source
identity and full palette semantics must agree with the original binding proof.

The independent audit checked 72 variant occurrences covering 38 resources.
Twenty-one add new storage: nine CI8, two CI4, one RGBA32 and nine IA4 timer
digits. They total 17,180 stored bytes; twenty use default zlib and one uses
GNU gzip. Each manifest retains the complete original binding evidence and
the chosen variant record. No playback time or composed runtime state is
claimed. Combined with the six authored/action sources, this batch adds 27
textures and 20,482 stored bytes. All 6,185 earlier source contracts and inputs
are preserved, and the complete selection contains 7,644 PNGs.

## CPU renderer descriptor storage

The table at `0x80090B60` contains 207 twelve-byte descriptors, ending before
the independently consumed resource word at `0x80091514`. Each descriptor
declares a resource or frame-array pointer, frame count, dimensions, format
and texel size. Whole-function hashes guard the descriptor selector, loader,
cache helper, draw caller and resource loader. The complete descriptor table,
all referenced frame arrays in table order, and the transfer-size tables at
`0x8009DEB0` are independently pinned. Altered native code or data is rejected.

The native loader starts at byte zero and uses zero-DXT LoadBlock transfers.
Its size tables determine transfer count and render stride; the catalog
requires both to cover the complete stored image without truncation or row
padding. Indexed formats require their full palette immediately after the
pixels. Unsupported fields, partial payloads, extra bytes, oversized loads and
unaligned rows do not qualify. Every accepted image also passes its PNG inverse.

This adds 205 single-image sources: 140 RGBA32, 34 I8, 13 IA8, six RGBA16,
six I4, five IA16 and one CI8. The CI8 descriptor stores resource ID 1844
directly; the native selector's literal-resource branch supplies its pixels
and all 256 palette entries. Physical stream 1842 retains the canonical name.

Five further descriptors use native format 5. The renderer explicitly loads
an RGBA16 base and a same-sized I4 detail image, with the second tile beginning
after all base pixels. Both images are required source PNGs. Schema 4 admits
this exact two-plane combination with no palette, alongside the existing
indexed/IA4 contracts. Different formats, plane counts, shapes, gaps, edits,
missing inputs and changes during packing fail closed.

All 210 additions freshly reproduce 292,537 compressed bytes and 671,168
decoded bytes: 190 streams use default zlib and 20 use GNU gzip. The complete
selection has 7,859 PNGs. All 6,212 prior source contracts and input hashes are
unchanged. The contracts prove declared storage; they do not claim that every
frame or descriptor is activated in gameplay.

## Exact reconstruction

All 6,422 texture source bundles round-trip to their complete original payloads.
Default zlib level-9 compression reproduces 5,932 entries. The remaining 490
select **GNU gzip 1.12 at level 9**; every selected encoder must reproduce the
original compressed bytes before any output in the batch is replaced.

The GNU encoder uses `-n -9 -c`. Its fixed header and CRC/size trailer are
validated and removed, leaving freshly encoded raw DEFLATE with a new RZIP
length header. No compressed ROM bytes or token recipes are used as source.
Every output is decoded independently and checked for exact extent and hash.
Changed pixels, palettes, manifests, encoder output or concurrent source
changes fail closed. This workflow does not support asset editing.

`./conker texture-assets build` runs in the pinned toolchain container, which
provides GNU gzip 1.12. Surveys and extraction retain host dispatch.

Selected storage is **7,821,784 bytes**, with **12,951,440 decoded bytes**.
The entire flat archive is partitioned into 6,799 nonoverlapping rows:
6,422 rebuilt entries and 377 raw intervals. The selected Data denominator is
**8,028,856 bytes**, including 201,632 initialized CPU bytes and 5,440 font
bytes. Decoded bytes and raw ranges receive no additional credit.

Raw means ROM-backed storage, not necessarily unidentified content. Exhausting
these reviewed contracts does not prove that all remaining flat payloads are
non-textures. Broader coverage needs new complete format/consumer evidence.

## Historical passing checkpoint

Commit `94cdf4564690c7492e14afbfe20c145cf0a83fc1` reconstructed **663 square
CI4 textures**, totaling **1,089,881 stored bytes**. All 663 native units were
fully matched and complete, with no compile errors and a current snapshot.
The full US ROM was identical. The suite ran 2,179 tests with 8 skips and no
failures; canonical progress and whitespace checks passed.

Its report fingerprint was
`49b3e287b65cb540ac25639ec4da37e88edf5d2b432d4cb679fc429c2cdaaab5`.
Aggregate Data was 1,096,425 / 1,296,953 matched bytes (84.53853%) and
1,095,657 complete bytes (84.47932%). Code totals were unchanged.

Command elapsed times were 334.24 seconds for the build, 543.44 seconds for
tests (532.065 seconds in the runner), and 778.85 seconds for the report.
Another checkout was running six permutation containers, so these are not
isolated performance benchmarks or total workflow duration.

The 41 remaining square entries could not be reproduced by 2,835 standard
zlib configurations per entry or installed Apple gzip levels 1–9. GNU gzip
subsequently recovered them. An encoder-only experiment with the official
[zlib 1.1.3 source](https://zlib.net/fossils/zlib-1.1.3.tar.gz) reproduced the
same default-zlib exact set for the earlier trial, with no recoveries.
Archive SHA-256:
`cae5847bc0e1cf113d3f70d037400da3e47c2e2b7b1c96b0b08447a5fbb906f4`.
That experiment is not a build dependency.

## Evidence and validation

Ignored per-entry census and command logs live under
`build/us/texture-exhaustion-validation/`; reconstruction proofs are under
`build/us/textures/`, and independent native comparisons are under
`build/us/objdiff-report/`. The canonical YAML records every selected physical
ROM boundary. Generated reports and ROM-derived images are not committed.

Passing 4,387-texture checkpoint validation (commit `f2f7e20`):

- Fresh PNG-derived compression: all 4,387 streams exactly match, totaling
  5,112,316 bytes; command elapsed time 58.74 seconds.
- Full US ROM build passed in 315.87 seconds. Independent comparison confirms
  all 67,108,864 bytes match and SHA-1 is
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Full container suite: 2,188 tests, 8 skipped, no failures; 219.949 seconds in
  the runner and 225.81 seconds command elapsed time.
- All 663 checkpoint source bundles retain their original hashes.
- All 159 HUD selector PNGs match the independent reviewed preview pixels;
  the additional artwork renderer validates 40 groups covering 74 resources.
- Native report: all 4,387 texture units fully matched and complete, totaling
  5,112,316 stored bytes, with no compile errors and snapshot status `current`.
  Command elapsed time: 604.00 seconds.
- Canonical progress validation, progress rendering and whitespace checks passed.
- Aggregate Data: 5,118,860 / 5,319,388 matched bytes (96.23025%) and
  5,118,092 complete bytes (96.215805%). Code totals are unchanged.

Report source fingerprint:
`575bafcfe96e4450b918c8a3d4ac0e5066c50c3412232b773bd19a4a9d71c833`.

These are command timings, not total workflow duration.

## Passing model checkpoint validation (`3746d1d`)

- 37 focused catalog, reconstruction and Make tests passed.
- All 4,387 committed source bundles retain their hashes.
- Full US ROM build passed in 442.46 seconds; independent comparison confirms
  byte equality with the original 67,108,864-byte US ROM.
- Full container suite: 2,192 tests, 8 skipped, no failures; 254.961 seconds in
  the runner and 262.51 seconds command elapsed time.
- All 5,665 PNG-derived compressed sources match, totaling 6,933,902 bytes.
- Native report: all 5,665 texture units fully matched and complete, with no
  compile errors and snapshot status `current`. Command elapsed time: 752.12 seconds.
- Aggregate Data: 6,940,446 / 7,140,974 matched bytes (97.19187%) and
  6,939,678 complete bytes (97.181114%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`058543eab17a71aa79cac5b9988f520e941ba8e32821a54fce4684b18f0166b1`.

## Passing mipmap and selector checkpoint validation (`5613921`)

- 48 focused reconstruction, catalog, storage-contract and Make tests passed.
- All 6,800 PNG inputs verify; all 5,665 prior source bundles retain their hashes.
- Full US ROM build passed in 352.97 seconds. Independent comparison confirms
  all 67,108,864 bytes are identical to the original US ROM.
- Full container suite: 2,203 tests, 8 skipped, no failures; 168.989 seconds in
  the runner and 174.18 seconds command elapsed time. The first run exposed a
  missing dependency in the miniature Make test fixture; the corrected fixture
  and full-suite rerun both passed. No second full ROM build was needed.
- All 6,006 PNG-derived compressed sources match, totaling 7,285,032 bytes.
- Native report: all 6,006 texture units fully matched and complete, with no
  compile errors and snapshot status `current`. Command elapsed time: 615.42 seconds.
- Aggregate Data: 7,291,576 / 7,492,104 matched bytes (97.32348%) and
  7,290,808 complete bytes (97.313225%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`1b437e6e8a69f5a309331fd127ebaa934b6931dbb23b63ef20ee21f8b6c04324`.

These timings measure individual commands, not total workflow duration.

## Passing storage-extension checkpoint validation (`f07d713`)

- 106 focused catalog, storage, reconstruction, Make and report tests passed,
  with two skips. Parallel-reference tests prove a four-worker bound, ordered
  results and error propagation; existing source/link-input race gates remain.
- All 7,580 PNG inputs verify; all 6,006 prior bundles retain their hashes.
- Full US ROM build passed in 364.85 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,209 tests, 8 skipped, no failures; 186.708 seconds in
  the runner and 191.90 seconds command elapsed time.
- All 6,175 native texture units are fully matched and complete, totaling
  7,494,361 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 452.11 seconds, compared with 615.42
  seconds for the preceding 6,006-texture checkpoint. This is an observed run
  comparison, not an isolated benchmark or a guarantee of total workflow time.
- Aggregate Data: 7,500,905 / 7,701,433 matched bytes (97.396225%) and
  7,500,137 complete bytes (97.38625%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`5098fd5fced8cc13369655aef1685a7b126e5a8e78d29347cc88d40c95472036`.

## Passing mixed-detail and bound-source checkpoint validation (`439ac4f`)

- 41 focused reconstruction and storage-contract tests passed.
- All 7,617 PNG inputs verify; all 6,175 prior bundles retain their hashes.
- Full US ROM build passed in 379.62 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,214 tests, 8 skipped, no failures; 163.254 seconds in
  the runner and 168.06 seconds command elapsed time. The first run exposed two
  shared-fixture imports incompatible with container test discovery. The import
  fallback was corrected and the full suite rerun; the ROM build did not restart.
- All 6,185 native texture units are fully matched and complete, totaling
  7,508,765 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 455.20 seconds.
- Aggregate Data: 7,515,309 / 7,715,837 matched bytes (97.401085%) and
  7,514,541 complete bytes (97.391136%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`f8c03ad7aebfa852dfd34f6604a1579639b513f71336f1b7af905b5e215a33e3`.

These timings measure individual commands, not total workflow duration.

## Passing authored-storage, action-selector and binding-variant checkpoint validation (`a68eb77`)

- 56 focused storage, catalog, reconstruction and constructor tests passed.
- All 7,644 PNG inputs verify; all 6,185 prior bundles retain their input hashes.
- Full US ROM build passed in 376.11 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,220 tests, 8 skipped, no failures; 181.811 seconds in
  the runner and 186.91 seconds command elapsed time.
- All 6,212 native texture units are fully matched and complete, totaling
  7,529,247 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 461.36 seconds.
- Aggregate Data: 7,535,791 / 7,736,319 matched bytes (97.407970%) and
  7,535,023 complete bytes (97.398030%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`987992e78b9d40ebd4c337136b47192ef9958828e451c28966c591c8b0875e3b`.

The initial six-source selection also passed a full build and suite. The batch
was expanded before its native report to cover all 27 sources together; the
results above apply to that final selection. These timings measure individual
commands, not total workflow duration.

## Passing CPU descriptor batch validation

- 58 focused descriptor, catalog, storage and reconstruction tests passed.
- The independent selection audit admits exactly 210 new textures. All 7,859
  PNG inputs verify, and all 6,212 earlier bundles retain their input hashes.
- Full US ROM build passed in 396.45 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,228 tests, 8 skipped, no failures; 181.541 seconds in
  the runner and 186.70 seconds command elapsed time.
- All 6,422 native texture units are fully matched and complete, totaling
  7,821,784 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 460.04 seconds.
- Aggregate Data: 7,828,328 / 8,028,856 matched bytes (97.502410%) and
  7,827,560 complete bytes (97.492840%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`ba0dc209988a2cc929474e059265d949ca02592f10242ffb9aabc5fec4ed4d62`.

These timings measure individual commands, not total workflow duration.
