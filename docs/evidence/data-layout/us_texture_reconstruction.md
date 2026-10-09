# US texture reconstruction

The canonical flat YAML now selects **6,861 distinct textures**. This batch
adds one captured boat source and nine attachment animation textures to the
passing 6,851-texture checkpoint committed as `ead4fc1`.
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
| Additional native renderer selectors | 3 |
| Stored script selectors with initial actor bindings | 14 |
| Native character-update selectors | 4 |
| CPU renderer descriptors | 210 |
| Effect, literal-image and glyph descriptors | 113 |
| Native UI and effect grid storage | 271 |
| Parent-selected particle frames | 5 |
| Stored event selectors with constructor bindings | 3 |
| Direct native-loader images | 11 |
| Native table images with complete stored extents | 5 |
| Captured boat source storage | 1 |
| Native attachment frame witnesses | 9 |
| **Total** | **6,861** |

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

## Effect, literal-image and glyph descriptors

`scripts/texture_cpu_effects.py` adds a separate guarded family after all prior
catalogs. The 113 new physical streams come from three native routes:

- 77 come from the 70-pointer table at `0x8008CA4C`. Null slots are retained.
  `0x1516D738` indexes that table with the actor's byte selector and passes its
  descriptor and frame to `0x15142E24`. The next three words at `0x8008CB64`
  belong to the callback array consumed by `0x1516706C`, not the descriptor
  table. Pointer bytes, descriptor bytes and complete frame arrays are guarded.
- 34 come from 20 literal input descriptors passed to `0x15094F70`. Reviewed
  callers are `0x15166F6C`, `0x15090630`, `0x1517A9A8`, `0x150368C4`,
  `0x1516B6BC`, `0x151668B8` and `0x150417AC`. The last two supply five
  animated frames and 19 special glyph images respectively. Ordinary RLE font
  glyphs are outside this family. Frame order and every declared frame-array
  byte are preserved; this does not claim a runtime activation trace.
- Two come from the distinct compact output layout `>IHHBBBB` at
  `0x800903AC` and `0x800915A4`. The full native callers `0x1517E4A8` and
  `0x1514803C` pass zero pixel-frame offset to `0x150950D4`. The second caller
  fills its resource word from the 16-entry array at `0x80091564`. Original
  flags, descriptor bytes, array order and full caller hashes remain in the
  evidence; flagged input descriptors do not acquire a general exemption.

Every route uses the reviewed native transfer-size tables and complete source
storage checks from the CPU descriptor family. The seven RGBA16/I4 sources
require both same-size image planes. Pointer selector 66/resource 3775 remains
excluded: its declared I4 image covers only half the payload. Unknown tails,
partial palettes and invalid strides cannot qualify.

The additions reproduce **76,481 compressed bytes** and **236,032 decoded
bytes** from **120 PNGs**. Whole-function native guards cover the direct
callers, selector, loader and resource resolver. All 6,422 earlier contracts
and input hashes are checked before accepting the expanded batch.

## Native UI grids, effect grids and split images

`scripts/texture_cpu_grids.py` adds 271 distinct sources after the earlier
families: 98 UI-grid tiles, 130 effect-grid sources and 43 bank-selected images.
The additions reproduce 333,724 stored bytes and 919,520 decoded bytes from
271 PNGs. All 6,535 earlier contracts and input hashes remain unchanged.

The UI callers `0x151EC1F0` and `0x151ED09C` pass five literal descriptors
to `0x151ED430`. Every preceding tile must consume its entire source within
4,096 bytes before the next resource ID is admitted. The grid is preflighted
as a whole, including sources already covered by other families.

Type-0x5E effect constructors and callback mutation select the descriptors,
frame counts, dimensions and border flags consumed by `0x15169A48` and
`0x1509629C`. The native grid is column-major, with a short first row and short
last column; two-pixel borders are included in stored tile dimensions. Frame
planes advance resource IDs. Whole-function hashes, the type dispatch row,
callback array, descriptor bytes and native transfer-size tables are guarded.

`0x151EEBE8` selects resource IDs from the complete 144-byte raw bank `0x1D`
and writes descriptor `0x8009013C`. `0x151ED430` consumes each 5,632-byte image
through two consecutive 2,816-byte RGBA16 loads. The resulting 64-by-44 PNG
preserves top-left source order. The even 22-row split preserves the odd-row
TMEM phase. The shared RGBA16 codec now accepts this explicit origin while
retaining its previous default and exact channel/alpha checks. Resource 3018
is excluded because its 8,064-byte payload would leave an unconsumed tail.

These contracts prove complete native storage consumption, not runtime
activation. Every admitted payload independently round-trips through PNG and
fresh compression before selection.

## Particle callback frames and renderer states

Five RGBA32 frames, runtime resources 4051 through 4055, come from the
five-frame descriptor at `0x80090414` and its array at `0x80090400`.
`0x150DBD70` copies this descriptor into the type-0x22 parent configuration.
The parent constructor selects callback index 4 in both callback arrays;
`0x150DC558` and `0x150DCEA0` copy the configured descriptor into the child
packet. `0x15167D84` creates a type-5 child and copies that packet. Its draw
function `0x15168118` selects the frame through `0x15142E24`, and its update
`0x15167E0C` bounds the phase using the descriptor's frame count. Whole native
functions, both dispatch rows, both callback arrays, the descriptor, every
frame-array byte and the transfer-size tables are guarded. The five complete
32-by-32 sources add 3,860 stored bytes and 20,480 decoded bytes.

Three CI8 sources come from additional states of model `01:123` (Experiment).
The native model-ID branch calls `0x150F1CB0`. Animation 20 selects descriptor
27 for segment 10; other animations select 12. Segment 11 starts with 19,
changes to 20 when both low damage bits are set, and then changes to 23 when
both next damage bits are set. The latter assignment wins when both tests pass.
The catalog enumerates all outcomes while retaining other initializer selectors.
Native code and model binding evidence are verified before the existing model
load, TLUT and full-payload inverse checks. Resources 7160, 7167 and 7168 add
4,003 stored bytes and 5,632 decoded bytes. Tank movement states were also
checked; all their complete sources were already selected.

All eight additions use default zlib and independently reconstruct their PNGs,
palettes and freshly compressed streams exactly. Every earlier 6,806 source
contract and input hash is preserved. These are complete storage contracts;
they do not establish runtime activation or permit edited assets.

## Character-update and stored script selectors

Four additional CI8 sources follow complete native selector writes in
`0x15061B4C` and the blink-phase producer `0x1502EEF4`. Model 66 selects
segment-10 descriptors 12 and 21 through animation and random-bit branches;
model 91 maps blink phases through the three-word table at `0x8009942C`.
The latter contributes descriptors 18 and 11. Initializer selectors for other
segments are preserved. The two model-66 resources include all four stored
mipmap levels, including padded storage for the last level.

Fourteen sources follow stored bank-6 script commands. The native loader
`0x1501D348` identifies the fourth directory group from all three relevant
header counts. The queue producer `0x150242F8` skips four metadata records,
uses signed time markers and accumulates unsigned delays. Queue insertion,
sorting and dispatch are guarded through `0x150241B4`, `0x15024130` and
`0x1502A8A0`. In `0x1502460C`, opcode 9 writes expression selectors and
opcode 5/subcommand 111 writes segment-10/11 selectors. Only supported signed
operands and axes are admitted.

Each command retains its indexed source, whole decoded-script hash, track,
preceding records, initial type-2 actor descriptor and first matching spawn
record. Existing native spawn and scene-prefix evidence binds that initial
actor to its declared model. This establishes stored selector contracts
conditional on retaining that model; it does not establish runtime activation,
complete gameplay history or the absence of later actor mutation. The catalog
requires independently validated model loads, palettes and a complete payload
inverse for every admitted source. Partial previews remain excluded.

All eighteen additions reproduce their PNG-derived payloads and freshly
compressed streams exactly with default zlib. They add 21,769 stored bytes
and 34,240 decoded bytes. All 6,814 earlier contracts and input hashes are
unchanged. Native function spans, selector tables and the reference ROM are
checksum guarded.

## Event constructor selectors and direct native images

Scene 47 lists event 164. Its reviewed constructor packet requests actor
selector 24, whose first scene spawn declares model 141. The program copies
the returned handle through frame slot -8 into state slot 36. Three subsequent
native-6 packets write segment-6 descriptor 8, segment-7 descriptor 10 and
segment-10 descriptor 2. The intervening operation changes actor flags only.
Whole event, scene, spawn, native dispatch and selector-table sources are
checksum guarded. No branch enters the middle of the constructor block.
The three CI8 contracts remain conditional on successful actor resolution and
retention of the declared model; they do not claim runtime activation.

Eleven additional sources follow direct calls to flat loader `0x1510D0EC`.
The complete guarded callers pass resource IDs and use the returned pointer
unchanged in SetTextureImage. Their emitted load tiles, zero-DXT LoadBlock
transfers, render strides and tile bounds account for each complete payload:

| Runtime resources | Format | Dimensions | Native caller |
| --- | --- | --- | --- |
| 3343 | RGBA32 | 32 x 32 | `0x1507DB6C` |
| 3347 | RGBA16 | 32 x 32 | `0x150918EC` |
| 3313, 3314 | IA8 | 64 x 64 | `0x150918EC` |
| 3315 | IA8 | 32 x 32 | `0x15093B58` |
| 2632 | IA8 | 64 x 64 | `0x151D2830` |
| 2043 | RGBA16 | 48 x 32 | `0x151EEBE8` |
| 3348 | RGBA32 | 32 x 32 | `0x151E966C` |
| 3344 | RGBA32 | 32 x 32 | `0x151E9D18` |
| 3345, 3346 | RGBA32 | 16 x 32 | `0x151E9D18` |

The flag branch at `0x15093138` supplies both 3313 and 3314. The selector
branches at `0x151E9D68..0x151E9DA4` pair 3344 with width 32 and 3345/3346
with width 16 before the shared renderer. These are declared source layouts,
not a claim that every branch has been observed in gameplay. Partial loads,
unknown selectors and size-only candidates remain excluded.

Together the fourteen additions contribute 14,543 stored bytes and 42,496
decoded bytes. Thirteen use default zlib and one uses GNU gzip. All previous
6,832 contracts and source-input hashes remain unchanged.

## Native table images and inherited sampling bounds

The renderer `0x15180580` loads five additional resources from the guarded
six-word table at `0x80090298`. Table word zero identifies geometry and is
excluded. Words one and two select resources 1968 (I8) and 4417 (IA8), each
64 x 64. Words three through five select resources 4414, 4415 and 4416,
each RGBA16 with complete 32 x 32 storage.

The native counter at `0x800DDD78 + instance` selects `table[3 + counter]`.
The successor at `0x1518121C..0x15181238` increments states zero and one and
resets values at least two to zero. Only the declared zero/one/two cycle is
admitted; this does not claim all runtime counter values or observed activation.
The table binding, native caller, loader and rectangle helper are checksum
guarded. All loader results become unmodified image-base addresses.

Storage dimensions are derived from explicit render strides and zero-DXT
LoadBlock extents, not guessed from compressed or decoded sizes. Resource
1968 installs half-texel sampler bounds covering 64 x 64; subsequent loads
inherit those bounds. The final three sources transfer 2,048 bytes with a
64-byte RGBA16 row stride, establishing 32 x 32 stored images despite the
larger retained sampling bounds. The helper `0x1517FB9C` only emits rectangle
draw commands and preserves that state. These contracts describe complete
stored sources, not the appearance of every possible sampled rectangle.

The five sources add 1,184 stored bytes and 14,336 decoded bytes. Three use
default zlib and two use GNU gzip. All 6,846 preceding contracts and source
input hashes are preserved.

## Captured boat source and attachment animation frames

Resource 4195 is a complete CI8 32 x 32 source with a 512-byte palette.
The existing `shc-boat-captured-parent42` contract binds it to runs 2 and 3 of
model 09:0047:00. Its ROM/model hashes, contract checksum, recorded context and
capture provenance are preserved; both runs must independently invert to the
same complete payload. This reuses the recorded Soldier 88 / actor 42 draw
binding. The capture was not replayed, the parent pose is not baked into the
source, and this does not establish a universal Soldier default or activation
of animation 24 / action 74.

Action 76 declares attachment model 49 and updater `0x150F56B0`. With a
non-null parent animation and animation ID 174, explicit frame witnesses
select eight additional words of the table at `0x80090274`:

| Frame witness | Table index | Runtime resource |
| ---: | ---: | ---: |
| 52 | 0 | 3250 |
| 49 | 1 | 3251 |
| 46 | 2 | 3252 |
| 43 | 3 | 3253 |
| 40 | 4 | 3254 |
| 37 | 5 | 3255 |
| 61 | 7 | 3257 |
| 64 | 8 | 3258 |

These are CI4 32 x 32 sources with complete 32-byte palettes. Table index six
was already selected. The reviewed selector arms retain single-precision
arithmetic and the original `0x800A1B40` constant (float32 1/6). Other animation
arms and runtime activation are not inferred from this finite witness set.

Action 9 declares model 19 and updater `0x150D82BC`. Parent animation 13 at
frame 23 selects resource 1351 from `0x800902B4`. The updater writes the first
F2 command's upper-left coordinate to two at this frame, exactly preserving
its original `F2002002 000FE07E` command. The model therefore proves complete
CI8 64 x 32 storage with a 512-byte palette without assuming later shifted
coordinates. Shared constructors, action records, updater dispatch, full
native functions, tables, constants and model bytes are guarded. The ordinary
renderer binds the selected descriptor resource to segment six.

All ten new sources invert completely from PNG and freshly recompress to the
original streams: two with default zlib and eight with GNU gzip. They add
2,916 stored bytes and 8,448 decoded bytes. All 6,851 earlier contracts and
source-input hashes remain unchanged. These contracts establish source
storage under explicit bindings, not observed gameplay activation.

## Exact reconstruction

All 6,861 texture source bundles round-trip to their complete original payloads.
Default zlib level-9 compression reproduces 6,320 entries. The remaining 541
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

Selected storage is **8,280,264 bytes**, with **14,232,624 decoded bytes**.
The selection requires 8,317 PNGs. The flat archive has 7,184 nonoverlapping rows:
6,861 rebuilt entries and 323 raw intervals. The selected Data denominator is
**8,487,336 bytes**, including 201,632 initialized CPU bytes and 5,440 font
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

## Passing CPU descriptor checkpoint validation (`f2f3cbc`)

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

## Passing effect and glyph descriptor checkpoint (`52318e9`)

- 63 focused descriptor, catalog, storage and reconstruction tests passed.
- The independent selection audit admits exactly 113 new textures. All 7,979
  PNG inputs verify, and all 6,422 earlier contracts and input hashes remain
  unchanged.
- Full US ROM build passed in 401.96 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,233 tests, 8 skipped, no failures; 182.711 seconds in
  the runner and 187.74 seconds command elapsed time.
- All 6,535 native texture units are fully matched and complete, totaling
  7,898,265 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 472.52 seconds.
- Aggregate Data: 7,904,809 / 8,105,337 matched bytes (97.525980%) and
  7,904,041 complete bytes (97.516500%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`1f50499b3646c4afd208a04bd0d30861da773d82201797885fcd9f44b903b39f`.

These timings measure individual commands, not total workflow duration.

## Passing UI and effect grid checkpoint (`b5cd304`)

- 77 focused descriptor, grid, codec, catalog and reconstruction tests passed.
- The independent selection audit admits exactly 271 new textures. All 8,250
  PNG inputs verify, and all 6,535 earlier contracts and input hashes remain
  unchanged.
- Full US ROM build passed in 423.03 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,243 tests, 8 skipped, no failures; 183.260 seconds in
  the runner and 188.84 seconds command elapsed time.
- All 6,806 native texture units are fully matched and complete, totaling
  8,231,989 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 482.34 seconds.
- Aggregate Data: 8,238,533 / 8,439,061 matched bytes (97.62381%) and
  8,237,765 complete bytes (97.61471%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`b657442ac14db6c0d6cfb24510e572358518c1c18b29b1341aa52ad1f5eb93e9`.

These timings measure individual commands, not total workflow duration.

## Passing particle and Experiment batch validation

- 84 focused descriptor, selector, codec, catalog and reconstruction tests passed.
- The independent selection audit admits exactly eight new textures. All 8,258
  PNG inputs verify, and all 6,806 earlier contracts and input hashes remain
  unchanged.
- Full US ROM build passed in 423.86 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,250 tests, 8 skipped, no failures; 189.231 seconds in
  the runner and 194.81 seconds command elapsed time.
- All 6,814 native texture units are fully matched and complete, totaling
  8,239,852 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 493.30 seconds.
- Aggregate Data: 8,246,396 / 8,446,924 matched bytes (97.62602%) and
  8,245,628 complete bytes (97.61693%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`266854067a0116026e154e251f53d7d492a885e938690a862aecd8615baf0c2a`.

These timings measure individual commands, not total workflow duration.

## Passing character-update and script-selector batch validation

- 91 focused selector-provenance, descriptor, codec, catalog and reconstruction
  tests passed.
- The independent selection audit admits exactly eighteen new textures. All
  8,288 PNG inputs verify, and all 6,814 earlier contracts and input hashes
  remain unchanged.
- Full US ROM build passed in 421.58 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,257 tests, 8 skipped, no failures; 182.318 seconds in
  the runner and 187.91 seconds command elapsed time.
- All 6,832 native texture units are fully matched and complete, totaling
  8,261,621 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 494.10 seconds.
- Aggregate Data: 8,268,165 / 8,468,693 matched bytes (97.632126%) and
  8,267,397 complete bytes (97.623055%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`0575aea665e1ea027f81e4b1e2fe60e661d8e5c1d2a57b26f3669b49b129dcc4`.

These timings measure individual commands, not total workflow duration.

## Passing event-constructor and direct-image batch validation

- 119 focused provenance, descriptor, codec, catalog and reconstruction tests
  passed after updating the catalog's synthetic provider fixture.
- The independent selection audit admits exactly fourteen new textures. All
  8,302 PNG inputs verify, and all 6,832 earlier contracts and input hashes
  remain unchanged.
- Full US ROM build passed in 422.21 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,267 tests, 8 skipped, no failures; 184.727 seconds in
  the runner and 189.70 seconds command elapsed time.
- All 6,846 native texture units are fully matched and complete, totaling
  8,276,164 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 498.96 seconds.
- Aggregate Data: 8,282,708 / 8,483,236 matched bytes (97.636185%) and
  8,281,940 complete bytes (97.627140%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`de3986da1fd0cf6726683737d1d641e8e8ff106a8b7802d0fbe76b5d6b1b6bcf`.

These timings measure individual commands, not total workflow duration.

## Passing native-table batch validation

- 122 focused provenance, descriptor, codec, catalog and reconstruction tests
  passed.
- The independent selection audit admits exactly five new textures. All 8,307
  PNG inputs verify, and all 6,846 earlier contracts and input hashes remain
  unchanged.
- Full US ROM build passed in 418.19 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,270 tests, 8 skipped, no failures; 181.558 seconds in
  the runner and 186.43 seconds command elapsed time.
- All 6,851 native texture units are fully matched and complete, totaling
  8,277,348 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 498.78 seconds.
- Aggregate Data: 8,283,892 / 8,484,420 matched bytes (97.636510%) and
  8,283,124 complete bytes (97.627464%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`390901bd50da61798acaedf10a29260029e1063f290dddd7341bdfa9d77f3b42`.

These timings measure individual commands, not total workflow duration.

## Passing captured-boat and attachment-frame batch validation

- 71 focused model, provenance, codec, catalog and reconstruction tests passed.
- The independent selection audit admits exactly ten new textures. All 8,317
  PNG inputs verify, and all 6,851 earlier contracts and source-input hashes
  remain unchanged.
- Full US ROM build passed in 423.94 seconds. Independent comparison confirms
  all 67,108,864 bytes match the original US ROM.
- Full container suite: 2,274 tests, 8 skipped, no failures; 183.834 seconds in
  the runner and 189.19 seconds command elapsed time.
- All 6,861 native texture units are fully matched and complete, totaling
  8,280,264 stored bytes. There are no compile errors and the snapshot is current.
- Native report command elapsed time: 491.74 seconds.
- Aggregate Data: 8,286,808 / 8,487,336 matched bytes (97.637330%) and
  8,286,040 complete bytes (97.628280%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`3863945a04433ffd7ee1d503c700724198cd95b7686bf646d9d72e5773b2d6af`.

These timings measure individual commands, not total workflow duration.
