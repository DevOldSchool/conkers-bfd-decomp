# Asset extraction roadmap

This roadmap tracks semantic, reversible asset extraction separately from code
matching. Asset work must preserve unrelated mapping and model work, keep all
ROM-derived output under ignored `build/` paths, and assign meanings only after
a runtime consumer or a self-describing format proves them.

## Current families

- [x] Grayscale RLE font glyphs: reversible extraction and packing.
- [x] MP3 streams and decoder tables: reversible extraction and packing.
- [ ] Textures: continue resolving runtime-dependent CI8 and scene-selected
  references without promoting assets by appearance alone.
- [x] Model geometry: extract and byte-verify 1,186 records from the four proven
  model-bearing families, including material runs, joint assignments, and
  dynamic segment references. Of these, 1,184 records contain drawable faces.
- [ ] Model semantics: resolve names, complete runtime materials and lighting
  state, and recover the remaining scene consumers and surface-word meanings.

## Model extraction status

The current US model extractor covers every indexed bank with a proven model
container contract. All 6,805,424 extracted model bytes verify against the ROM.
Generated OBJ, MTL, glTF, binary buffers, textures, animations, and manifests
remain below ignored `build/assets/models/` paths.

The supplied Tediz reference and a Haybot reference now guide visual checks.
The cutscene Conker package is excluded. Both comparisons retain the ROM's
geometry and reveal reusable exporter errors; no reference mesh or texture is
substituted into an export. See the
[reference comparison evidence](evidence/us_model_reference_corrections.md).

| Bank | Proven family | Models | Vertices | Faces | UV coordinates | Current preview status |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `01` | Rigged character containers | 183 | 56,412 | 62,073 | 66,001 | 2,621 clips, decoded CBFD normals, 184 aggregate runtime-correlated material records, 2,449 drawable linked runs and 43,779 linked faces; 730 static or captured PNGs |
| `03` | Direct object models | 77 | 5,062 | 3,894 | 4,945 | 48 assembled bank-12 scenes with 511 placements; CBFD normals on 28 models; five runtime-correlated records, 283 drawable linked runs and 3,641 linked faces; 188 PNGs |
| `04` | Segmented level/model bundles | 765 | 209,274 | 147,723 | 204,493 | 52 assembled bank-11 scenes with 716 dispatched placements; all three collision arrays represented as 96 static-terrain meshes plus 1,055 transformed placements; CBFD normals on 107 models; 367 runtime-correlated records, 5,077 drawable linked runs and 138,735 linked faces; 2,272 PNGs |
| `09` | 155 attachment containers and six direct models | 161 | 10,489 | 9,152 | 10,413 | 47 runtime-correlated records, 556 drawable linked runs and 8,677 linked faces; 299 PNGs; native attachment composition proven for the captured cigar and helmet |
| **Total** |  | **1,186** | **281,237** | **222,842** | **285,852** | **All 1,546 main model, bind, animated, assembled-scene, neutral-composition, and posed-composition glTF files have current Blender validation; all 2,621 Actions load** |

The cross-bank coverage report is now available through
`./conker model-assets coverage`; see the
[consumer evidence and complete invocation](evidence/us_model_scene_consumers.md).
It audits 1,186 model identities and 9,590 material runs against independent
geometry, Blender, texture, runtime-state, composition, scene, and naming evidence.
The current aggregate corpus has 8,341 statically resolved texture runs, 603 observed runtime
material runs, 567 runs with captured images, and 230 runs with exact segment-8
payload evidence. Another 3,600 runs require segment-8 state not observed in the
supplied corpus. These dimensions overlap and are not interchangeable completion
counts. All 1,186 models have byte-verified extraction and current per-file Blender
validation. Semantic names remain outside the machine-readable evidence registry.

Renderer-selected part sequences now disambiguate sibling character lists that
share triangle patterns and a matrix slot. The separate task-local catalog has
236 material records, 1,112 variants and 15,052 observations across 73 appearances;
32 newly resolved records cover 515 source faces. Entry 130's Save-Game-26 normal
composition now has runtime materials on all 68 selected runs, exposing the
captured face behind its visor. See
[selected-part material evidence](evidence/us_selected_part_model_materials.md).

Explicit ROM alpha and filter state now applies to every linked texture format.
This corrects alpha modes in 600 standalone models: 16,868 drawable faces use
blending and 92,288 use opaque rendering instead of the generic alpha-test
fallback. Source geometry, texture pixels and other material values are
preserved. The CI8 visor has source alpha 178/255 and matching static/captured
blend state. See [static raster-state evidence](evidence/us_static_model_raster_state.md).
The main and separate captured-colour review corpora contain 3,015 validated
glTFs in total. All 611 Python tests and four bank byte-verification gates pass.
Neutral aggregate faces and complete native combiner, lighting and raster
appearance remain incomplete.

`./conker model-assets validate` now runs the ROM checks, direct source-to-export
geometry comparisons, captured-image comparisons, Khronos glTF validation,
cached Blender imports and nineteen deterministic render comparisons in one
batch. It writes separate passed, failed and incomplete evidence plus a focused
review page. The first pass found invalid empty meshes in eight exports of
zero-face character records 11 and 72; those now retain their hierarchy without
invented geometry. See [batch validation](evidence/us_model_batch_validation.md)
for setup, cache identities, comparison limits and reproduction.

Explicit IA8, IA16, I4 and I8 draw state now resolves another 139 texture runs on
1,954 faces across 45 models, with the same gains in the captured-colour review
corpus. Existing image selections, geometry and poses are preserved. See
[direct intensity texture evidence](evidence/us_direct_intensity_model_textures.md).

The validator also checks two Tediz instances in one vertex-complete graphics
submission: all 676 submitted triangles and 2,028 corners agree with
the exported joint-local positions and matrix ownership. All 666 textured faces
match captured image pixels; the other ten submitted faces require no texture.
The older posed exports are not paired to these submitted matrices. See
[Tediz submitted-rig evidence](evidence/us_tediz_submitted_rig_validation.md).

Visual inspection exposed two shared exporter errors despite those import checks:
triangles were assigned the matrix active at draw time instead of each cached
vertex's load-time matrix, and separately callable character lists inherited
textures from their stored neighbors. Both are corrected. The matrix fix affects
37,520 faces in 160 models; unsupported flat-image inheritance affected 9,782
faces in 33 models. Unknown secondary-pass materials now remain unbound, which
can produce plain surfaces. Further reference checks corrected runtime texture IDs, missing composition
triangles, ordinary trilinear base bindings, automatic preview animation, and
captured images incorrectly decoded through a disabled palette, and offscreen
render-to-texture geometry incorrectly merged into the body.
Tediz now retains all 338 ROM triangles, up from 180, and Haybot recovers its
metal hands and panels. Runtime vertex colours, secondary-pass blending,
lighting and complete appearance remain open. Model coverage explicitly records
`visual_parity: unverified`; see the
[vertex-load and preview evidence](evidence/us_character_vertex_load_matrices.md).

The report selected bank-04 scene association as the next reusable improvement:
`./conker model-assets scene-consumers` now connects the first four loader slots
across all 59 available scene bundles. Those 149 models contain 116,499 source
faces. Combined with the 1,227 resolved object placements, the graph associates
785 models with scenes; bank-04 association gaps fall from 195 to 46 models
(1,256 source faces). Slots 0–2 have conditional rendering consumers, while slot
3 has collision evidence only here. This is a consumer graph, not a fully
assembled or runtime-observed room. The eleven missing placement references in
scenes 17 and 62 remain explicit. Portals, lights, fog, cameras, triggers, and
conditional rendering remain open.

Completed model work:

- [x] Preserve every proven container and auxiliary region byte-for-byte rather
  than discarding zero-face records or unresolved companion data.
- [x] Decode primary model display lists, vertex loads, standard and packed
  triangle commands, material-state runs, UV transforms, and runtime segment
  references.
- [x] Export OBJ/MTL interchange files and glTF previews with N64 vertex colors,
  proven UVs, decoded CBFD normals in glTF, per-material repeat/mirror/clamp
  sampler state, and only texture bindings supported by extractor evidence.
- [x] Add a reproducible headless Blender validator driven by the preview and
  composition manifests. Current main-corpus evidence covers 1,546 glTF files,
  3,084 meshes, 399,102 polygons, and all 2,621 bank-01 Actions while rejecting
  missing meshes or any non-finite imported vertex. This checks interchange,
  not whether the imported appearance matches the game.
- [x] Apply the dedicated CBFD normal-stream replay to every model-bearing bank,
  not only characters. Bank `03` contains 79 `DC38000E` normal-base commands
  across 28 models, yielding 3,884 nonzero and 415 zero source-normal corners.
  Bank `04` contains 342 commands across 107 models, yielding 11,634 nonzero
  and 5,643 zero corners. The generic glTF exporter emits those normals and uses
  geometric fallbacks only for the explicitly zero vectors.
- [x] Export all bank-01 character hierarchies with rigid vertex-load matrix
  assignments and validate both animated and animation-free bind glTF files
  for all 183 records. The ROM vertices are joint-local and the joint-table
  floats are parent-relative translations. The exporter accumulates the joint
  hierarchy to obtain model-space pivots, then bakes each cached vertex through
  its own accumulated pivot and emits the matching joint and inverse-bind matrix.
  Matrix changes after a vertex load do not reassign that cached vertex; mixed
  joint triangles and source vertices reloaded under another matrix are preserved.
  Interactive Blender import of a
  `*-bind.gltf` file is the recommended geometry check.
- [x] Prove all 1,772 bank-01 texture descriptor records through
  `func_1503DC3C`, including their flat texture indices and stored dimensions;
  every display-list flat texture reference occurs in its model's table.
- [x] Prove the final bank-01 header pair as an optional two-byte procedural
  animation joint-index table. `func_1503DA3C` bounds each lookup by the stored
  size, `func_15033FE0` requests slots zero and one, and `func_15034860` emits
  the corresponding joint-channel overrides. All 208 slots in 104 models are
  either a valid joint index or the `0xFF` absent sentinel.
- [x] Prove the sixth header pair as an alternate display-list pointer table:
  the loader relocates all 43 pointers in 31 models and `func_1502CCFC` selects
  that table for its alternate render path.
- [x] Prove the fifth header pair is runtime-consumed rather than dead data.
  `func_1503D368` recognizes `DC38000E` commands and `func_1503D438` relocates
  their pointers. Across 181 models, all 2,937 commands address the pair's
  182,714-byte auxiliary stream at 32-byte-aligned offsets (five start at the
  procedural-table boundary). GLideN64's dedicated F3DEX2CBFD implementation
  identifies selector `0x0E` as the vertex-normal base: signed X/Y bytes are
  indexed by the destination vertex-cache slot and signed Z comes from the low
  byte of the vertex flag. Replaying that rule exactly matches all 62,073
  decoded triangles. The glTF exports normalized source normals; 2,575 zero and
  111 unavailable face corners use an explicitly recorded geometric preview
  fallback rather than being mistaken for valid unit vectors.
- [x] Recognize the character display lists' RGBA16 transfer-image plus
  same-index TLUT pattern as effective CI4/CI8 state and retain the exact pixel
  and palette load commands in the model manifest.
- [x] Trace the shared mode-bit relocation through `func_1510CE60`,
  compose non-overlapping single-`TEXEL0` CI4/CI8 images with their trailing
  runtime TLUTs, and reject packed layouts whose nominal pixel span overlaps
  that palette instead of exporting false diffuse images. Mode one addresses
  the trailing `0x200` bytes; mode two addresses the trailing `0x20` bytes.
- [x] Preserve every material run's complete `F5` render-tile ladder, including
  the TMEM offsets for lower mip levels. Exact `G_CC_TRILERP` character runs now bind their proven highest-resolution
  image at zero LOD fraction; this restores 574 bank-01 material runs. Other
  two-texture blends remain unlinked. Runtime captures expose native lower
  levels separately; glTF consumers generate their own mipmaps, so native
  distance-dependent filtering and dynamic colours remain unverified.
- [x] Trace those character colours through `func_1502CCFC` and
  `func_1502CC34`: primitive RGB comes from `D_800D9B68`, environment RGB from
  `D_800D9B78`, both at a three-byte stride, while alpha and optional
  `func_1502EC34` effects are runtime state. The glTF records this dependency
  instead of baking one misleading colour into every character material.
- [x] Prove that character texture segments `6`, `7`, `10`, and `11` are filled
  from four character-state texture IDs through `func_1510D0EC`, not fixed
  model-header assets, and preserve them as dynamic material slots.
- [x] Identify the highest-detail Conker model as bank `01`, entry `0000`.
  A pinned Mupen trace reaches `func_150A81D0` with that exact 28-joint table
  and proves bank `02`, entry `0000`, pair `0025`, frame `0` as a live pose.
- [x] Correct the bank-02 angle conversion against all 28 live matrices: stored
  channels are signed full Euler angles. Transposing the runtime's row-vector
  matrices for glTF preserves that sign and uses half-angle quaternion terms.
- [x] Trace `func_1505E0C4`, `func_1502D824`, and `func_150A8A18` far enough to
  prove the descriptor-provided bank-02 frame stride and decode root
  translation, masked joint translation, rotation, and scale channels.
  Descriptor duration, runtime route tables, and keyframe spacing bound 57,732 source frames across
  all 2,621 nonempty clips; 39 empty streams remain explicitly preserved.
  Masked `s16` translations are local-joint adjustments at `1/16` scale. The
  runtime adds them to each joint record's local translation before composing
  that matrix with its parent, so glTF now applies them directly to the same
  local node rather than subtracting a parent adjustment.
- [x] Identify rotation descriptor bit `0x10` as a following per-axis scale
  channel marker, clear it from the angle, and export the runtime's zero-as-unit
  or unsigned-value-over-`16384` scale behavior to glTF.
- [x] Decode bank-15 logical animation routing through `func_1503D660`,
  `func_1503D5F0`, and `func_1505E650`: 3,021 logical records map character
  animation IDs to even bank-02 segments, including Conker animation ID `0`
  selecting pair `0025`. Resolve all five `0xFF` duration descriptors through
  the runtime default or character `0x92` duration table.
- [x] Decode the two proven `0x44`-byte placement sources and assemble bank-03
  objects with runtime position, YZX Euler rotation, and scale.

Remaining model work:

- [x] Resolve the runtime animation clock. `func_1507BDB0` advances animation
  state from `D_800BE9A4`; a Mupen interpreter trace measured that delta as
  exactly `1.0`, while the main scheduler consumes the normal two NTSC video
  retraces per update. Exported descriptor ticks therefore run at 30 Hz.
  Rotation, scale, root motion,
  masked joint translation, and descriptor-relative keyframe timing are already
  exported for every nonempty clip; descriptors may safely provide unused
  channels beyond the highest slot referenced by a model's joint table.
- [ ] Capture more concrete character states. The current runtime corpus decodes
  all 238 observed mip variants into 753 mip-chain images and 213 distinct PNGs.
  Six detail-mode variants are separated into a CI4 `TEXEL0` detail tile and a
  CI8 `TEXEL1` mip chain. Dynamically selected facial slots must continue to be
  captured with their character state rather than assigned one global texture.
- [ ] Extend scene-selected and renderer-generated segment-8 state coverage to
  unobserved models; do not assign those references statically. The supplied
  traces now bind 8,070 material assignments in 138 records to an exact runtime
  list payload whose `EF` command matches the draw's effective OtherMode. The
  correlated set contains 13 unique list payloads, 11 effective at the draw.
  The traces also retain 38 proven bank-03 list calls whose state is later
  overridden and five bank-03 assignments with no captured base rather than
  treating either as an exact final-state match.
- [ ] Correlate numeric model IDs with runtime callers before assigning semantic
  character, prop, level, or variant names beyond the verified Conker preview.
- [ ] Recover the remaining level/room scene graph consumers; these are related
  to models but are not standalone model-container extraction.

### Cross-bank model completion plan

The decoded standalone inventory contains 213,946 source faces. Interchange
previews retain 213,696 faces after omitting 250 source zero-area
commands proven degenerate under one matrix; 65,384 preview faces have
evidence-backed texture bindings. Equal joint-local coordinates alone do not
prove degeneracy when a triangle spans several matrices. The
remaining work is ordered by reusable runtime contract and affected face count
rather than by individual model:

1. [x] Build a generic Mupen draw-state recorder keyed by bank, entry, segment,
   material run, and render-state hash. Capture segment bases, resolved texture
   IDs and TLUT addresses, tile/TMEM state, combine and other modes,
   primitive/environment colour and alpha, and character joint matrices.
   The versioned recorder, safe trace-spec format, identity keys, canonical
   state hash, complete CPU register snapshot, and bounded memory probes are now
   implemented as `./conker mupen-trace`. The first checked-in hook records
   runtime texture-parser resolutions at `0x1510D010`; a pinned Mupen run
   reached the parser during normal US startup and produced a complete smoke
   event: the first qualifying `FD` command was flat texture `7737`, mode `0`,
   with a `0xA00` payload, null rewrite table, and resolved source
   `0x8015EE60`. The reviewed universal submission hook is now the main
   executable's `__osSpRawStartDma` at debugger address `0x10023DF0`; it filters
   the 64-byte DMA to SP DMEM `0xFC0` for graphics task type `1`, follows the
   task's bounded command-buffer pointer and size, and decodes F3DEX2CBFD
   segment, texture, tile/TMEM, combine/other-mode, colour, and triangle state.
   A live startup task contained 391 commands and one eight-triangle geometry
   cluster. Address-normalized command-prefix matching correlated that cluster
   to bank-04 entries `0005`, `0008`, `0032`, and `0037`, whose segment payloads
   share SHA-1 `eb08ec3a86b9f2fd77390945dae46197530cd7f2`; the recorder reports
   `equivalent-aliases` rather than selecting one unsupported entry identity.
   All eight unique nested lists referenced by that task terminated cleanly;
   execution-order inlining expanded the 391 submitted commands to 440
   effective commands with no unresolved targets, so state selected inside a
   child list now reaches later parent draws. The same task exposed 28
   `DA380003` model-view selector. The recorder now snapshots every unique
   resolved 64-byte RSP matrix, decodes its split signed-16.16 representation, and
   attaches its capture index, translation, and evidence hash to each affected
   draw run; the startup geometry used the single zero-translation matrix at
   `0x80089470`. An OpenEmu Mupen64Plus `2.5.9` state with the exact US ROM MD5
   loads in the pinned toolchain without conversion. Its first graphics task
   expands from 1,285 submitted to 3,400 effective commands and proves segment
   3 at `0x80125000`: all 28 slots from offset `0x0` through `0x6C0` resolve to
   finite RSP matrices. All 1,219 draw runs receive a matrix record, while
   geometry correlation uniquely identifies 44 bank-01 entry `0001` clusters
   and six entry `0004` clusters; both models use the same 28-slot character
   hierarchy. Extending each static geometry cluster with its containing
   material run resolves 115 unique model identities plus 19 equivalent
   material aliases without guessing an entry. That gives 134 usable material
   correlations covering 1,093 of the task's 1,219 draw runs and joins 130
   runtime pixel addresses to 43 original flat texture IDs. All 50 comparable
   bank-01 matrix selections agree with the static material-run matrix slot.
   Execution-order nested-list discovery now also resolves all 36 calls in that
   task. Ten are segment-8 calls selecting five distinct runtime OtherMode lists
   at `0x80083140`, `0x80083180`, `0x800831B0`, `0x80083240`, and `0x800832C0`;
   no nested target remains unresolved. The runtime-material manifest records
   these resolution counts and addresses as an auditable input boundary. This
   corrects the captured state for 34 of the 75 material records: all 29 records
   from bank-01 entries `0001` and `0004`, plus five records from bank-04 entries
   `0045` and `0060`, covering 541 correlated draw observations.
   Extending the same bounded capture to all 26 supplied OpenEmu states yields
   19 positive one-task sessions and seven bounded negatives. The positive set
   expands to 92,011 effective commands and 20,597 draw runs. All 1,772 nested
   calls resolve, including 742 segment-8 calls to 22 distinct runtime lists.
   With the character-activity refinement described below, the corrected cached-vertex decoder produces 557
   ROM-correlated material records with 1,873 variants and 13,809 correlated
   draw observations across 85 distinct models: 184 records across eleven bank-01
   models, five records across three bank-03 models, and
   368 records across 71 bank-04 model segments. Those records cover 18,548
   source faces without assigning any ambiguous cluster to one model.
   Unmatched and genuinely ambiguous clusters remain explicit rather than
   receiving a guessed model or texture identity.
2. [x] Generate a texture- and lighting-independent validation atlas for every
   model, using unique colours per rigid joint or material run and several fixed
   camera angles. Record detached or overlapping components, extreme bounds,
   invalid joint assignments, inverted normals, and zero-area triangles before
   a textured preview is accepted. `./conker model-assets atlas --force`
   software-renders front, side, and top views for all 1,186 records without a
   Blender dependency and writes an HTML atlas plus a machine-readable manifest.
   The refreshed pass classifies 470 models as structurally accepted, 716
   for review, and none as structurally rejected. It exposes 250 zero-area faces,
   17,314 exact coincident triangles, 3,966 source-normal/winding disagreements
   across the four normal-bearing banks, three bank-04 bounds outliers and
   one bank-09 bounds outlier. Disconnected components and normal disagreement
   are review findings rather than automatic corruption claims because rigid
   character parts, double-sided surfaces, and independent level components can
   be intentional. The 250 zero-area faces are explicit source commands across
   standard `0x05`/`0x06` and packed `0x10`-`0x1F` triangle opcodes: 121 repeat a
   vertex index, 24 reference distinct vertices at duplicate positions, and 105
   are collinear. Their face indices, display-list offsets, and opcodes remain in
   the manifests, while OBJ/glTF previews omit them because they cannot rasterize
   a surface. Invalid joints or non-finite bounds remain hard rejection reasons;
   exact coincident triangles remain visible for review because the original
   display list can deliberately redraw a surface in multiple passes.
   Triangle-level culling now preserves the proven F3DEX2 `D9` state instead of
   exporting every material as double-sided. Back-face culling is established
   on 148,124 source faces; 6,868 explicitly disable culling and 67,850 retain
   unknown inherited state. Ninety-five material runs are partitioned only in
   glTF, with source run IDs and ordered face coverage checked. The scene-24
   enclosure consists of twelve inward-facing black source triangles; culling
   now reveals the interior geometry and backdrop textures hidden by the old
   preview. Source geometry, textures, placements and composition counts remain
   unchanged. Both full Blender gates also check imported culling flags; all 573
   tests and four bank byte-verification gates pass. Blender preserves two more
   opposite-winding polygons after the partition, confirmed by a minimal import
   reproduction. See [face-culling evidence](evidence/us_model_face_culling.md)
   and `build/assets/models/reference/geometry-culling/`. Inherited state and
   complete native scene appearance remain open.
   Captured-command replay now resolves inherited back-face culling on another
   3,826 source faces across 21 models, including Tediz, Conker and captured
   attachments. It retains explicit ROM state on eight conflicting faces and
   excludes ambiguous material aliases. Source faces, textures and composition
   counts are preserved. The refreshed Blender evidence covers all 3,015 glTFs;
   all 577 tests and four bank byte-verification gates pass. The helmet, posed
   Conker and entry-130 images visibly change; Haybot remains pixel-identical.
   There are still 64,024 source faces with unresolved inherited state, alongside
   the separate native material and scene frontiers. See
   [runtime culling evidence](evidence/us_runtime_model_face_culling.md) and
   `build/assets/models/reference/runtime-face-culling/`.
3. [x] Correct the shared palette relocation used by all four banks.
   Reviewing the complete branch and its delay slot overturns the earlier
   fifth-argument interpretation: `0x1510CFBC` overwrites `$t9` with mode bit 0
   before the palette branch. Mode one selects `payload_end - 0x200`; mode two
   selects `payload_end - 0x20`, independently of the reference bookkeeping
   pointer. Captured pointers and TLUT hashes confirm both offsets. The corrected
   static path resolves 2,713 bank-04 runs/70,475 source faces and 202 bank-03
   runs/3,000 source faces; one bank-03 run with two faces still exceeds its
   payload span. CI4 corrections also resolve previously rejected character and
   attachment textures. All 906 comparable captured CI images match pixel-for-pixel
   (matching dimensions and ROM palette; dynamic/different-size images excluded).
   The regenerated aggregate previews gain texture links on 72,580 source faces
   across 568 models. Incorrect CI4 palettes are removed from 572 faces whose
   actual zero-alpha palette needs additional combiner evidence. All 1,186 model
   identities and geometry counts remain unchanged. The corrected direct CI8
   storage set contains 528 byte-verified textures; the old exclusion of index
   3358 rested on a cache-store observation before palette relocation and has
   been withdrawn. See [palette evidence](evidence/us_model_palette_relocation.md)
   and `build/assets/models/reference/palette-mode-correction/` for comparisons.
   Static texture coverage rises from 4,339 to 7,394 material runs; 2,026 runs
   remain unresolved. Both complete Blender gates pass (1,546 main glTFs and
   1,469 captured-colour review glTFs), and all 564 Python tests pass. Runtime
   material observation remains a separate gap, particularly bank 04's 720
   unobserved models and the remaining 772 static runs without image contracts.
   The subsequent direct CI4 decoder resolves packed base images without
   requiring a standalone pixels-plus-palette storage PNG. Known zero-DXT loads,
   row stride, trailing mode-two TLUT and explicit lookup state establish the
   image; unclamped tile masks also correct image/UV dimensions on 24 runs.
   The aggregate previews gain texture links on 20,501 source faces across 177
   models. Unsupported links are removed from 70 faces, and 14 existing links
   receive corrected image shapes. Static coverage now resolves 7,915 runs,
   with 1,505 missing and 170 not requiring textures. All 1,121 comparable
   captured CI images match pixel-for-pixel; all four banks rebuild identically,
   both Blender inventories remain current, and all 568 Python tests pass.
   Model geometry, placements, poses and attachments are preserved. Unknown
   lookup states, incomplete mask-sized loads, other image formats and native
   LOD/combiner appearance remain open. See
   [direct indexed texture evidence](evidence/us_direct_indexed_model_textures.md)
   and `build/assets/models/reference/direct-indexed-mips/`.
   Direct RGBA32 decoding now applies the proven paired-TMEM layout to
   ROM-backed full images and base-image prefixes. Explicit lookup-disabled
   state, load/stride bounds and combiner texture inputs gate image selection;
   static glTF materials retain the recorded filter and blend state. The
   aggregate previews gain 272 links on 4,414 source faces across 134 models,
   without changing existing images or removing links. All 49 captured RGBA32
   observations match, with no exclusions. Static coverage now resolves 8,202
   runs, with 1,218 missing and 170 not requiring textures. Both complete Blender
   inventories remain current, all four banks rebuild identically, and all 571
   Python tests pass. Source geometry, placements and captured character poses
   are preserved. The subsequent culling investigation identifies the scene-24
   enclosure as inward-facing source geometry; image recovery alone does not
   establish correct scene assembly. Other native formats and inherited
   material state remain open.
   See [RGBA32 evidence](evidence/us_direct_rgba32_model_textures.md) and
   `build/assets/models/reference/direct-native-images/`.
4. [x] Translate captured RDP combine, primitive/environment colour, alpha,
   mipmap, and `TEXEL0`/`TEXEL1` state into reusable glTF preview materials,
   retaining the exact unsupported state in metadata whenever glTF cannot
   reproduce it. `./conker model-assets materials --trace <trace.jsonl> --force`
   now validates correlated identities against the exact ROM and aggregates
   matrix-independent runtime material variants. The first supplied OpenEmu
   scene yielded 75 static material records and 79 variants from 820 correlated
   draw observations. The current 19-trace aggregate yields 557 records and
   1,873 variants from 13,809 correlated draw observations across banks 01, 03,
   and 04. Preview generation accepts that manifest with
   `--runtime-materials`, embeds every captured combiner, tile/TMEM, colour,
   geometry-mode, lighting, and texture address variant in glTF extras, and
   translates unanimous RDP filtering plus alpha/blend state into glTF sampler
   and alpha modes. That first capture contains 27 variants whose base-colour
   product would otherwise map to glTF but has RSP lighting enabled, 17 explicit
   `TEXEL0`/`TEXEL1` LOD variants, four RGB-only mappings with unsupported alpha,
   and 31 other unsupported combiners. None is falsely flattened to a diffuse
   material. Those figures describe the initial translation boundary; the
   current aggregate translator classifies every non-mipmap formula. Of all
   1,873 variants, 291 map directly to glTF base-colour products, 1,236 require
   captured runtime-lighting replay, 343 retain explicit RDP mip blending, two
   retain non-LOD two-texture multiplication, and one retains another combiner
   as metadata. The static preview additionally admits the exact character
   trilinear base at zero LOD fraction, without claiming full mip-filter parity. The trace decoder
   now mirrors the dedicated F3DEX2CBFD light path:
   `DB` light count is divided by 48, `DC` selector `0x0A` addresses 48-byte
   extended light records, coordinate-modifier writes are replayed, and opcode
   `0xDD` selects advanced lighting. That supplied task captures 16 unique light
   records through 56 commands with no unresolved address; all 1,066 lit draw
   runs carry decoded light state, split between 11-light and three-light
   configurations, and 791 runs use advanced lighting. The same task contains
   83 resolved selector-`0x0E` normal streams, covering all 791 advanced-lit
   runs. The material manifest retains 96 distinct matrix/normal lighting
   contexts without adding them to the 79 material-variant identities. The
   initial exporter replay implemented CBFD basic and advanced per-vertex lighting,
   including inverse model-view direction transforms, coordinate modifiers,
   point attenuation, signed vertex flags, and source normal bytes. All 27
   directly translatable lit variants have one unambiguous observed context;
   their 2,267 vertices are baked into floating-point glTF colours. This is
   originally labelled GLideN64-equivalent evidence. The vertex-load/projection
   audit below invalidates that equivalence claim: the old replay uses source
   positions and draw-time state. Those bakes have since been removed; the
   vertex-complete capture workflow below supplies their verified replacement
   only where all required observations are available.
   `SetConvert` (`EC`) capture and deterministic command-buffer replay recover
   task-local conversion state for 1,028 variants, including all 156 K5 formulas.
   The other 414 variants precede any task-local `SetConvert`; their inherited
   coefficient state remains explicitly unresolved instead of being guessed.
   Captured source spans now decode all 238 mip variants into 753 mip-chain
   images, deduplicated to 213 PNGs with exact level, size, source offset, TMEM
   offset, and hash. The self-contained bank-01 and bank-04 previews copy 38 and
   172 mip PNGs respectively and expose them in glTF extras. Six detail-mode
   variants are split into a CI4 `TEXEL0` detail tile and CI8 `TEXEL1` mip
   chain, correcting the earlier base-offset interpretation; standard glTF
   still displays only the base level.
   Both non-LOD two-texture variants now export their shared second 64x32 CI4
   image from source offset `0x400`; their exact multiplication remains glTF
   metadata because core glTF has only one base-colour texture input.
   The aggregate manifest now indexes all 19 captured graphics tasks as stable
   `TRACE_INDEX:EVENT_INDEX` appearances. Preview generation accepts
   `--runtime-appearance` and filters both material variants and lighting
   contexts to the selected task, preventing mutually exclusive scene or
   character states from being collapsed into one preview. Save-Game-13
   appearance `1:0` assigns 22 Conker runs with exactly one task-local variant
   apiece; explicit mip state remains exact metadata.
   A fresh Save-Game-13 capture also snapshots all 98 unique RDRAM pixel/TLUT
   spans used by the task (110,824 bytes, zero unresolved). Material extraction
   preserves source byte hashes, and previews verify every PNG hash. The later
   selected-tile correction distinguishes the CI8 eye draw from the CI4 view of
   the same captured bytes; image addresses alone cannot establish the format.
   Capturing all 19 positive OpenEmu tasks provides 1,474 bounded image variants
   in 512 material records, deduplicated to 289 base PNGs after runtime format
   correction. The task's TLUT enable state and actual render tile now select
   CI, I8, or IA8 decoding; a retained palette is not proof of palette use.
   Unsupported runtime format/coordinate changes remain unbound. The regenerated
   aggregate previews reach 2,285 linked runs and 41,541 faces in bank 01, and
   1,704 linked runs and 46,632 faces in bank 04. See the
   [reference corrections](evidence/us_model_reference_corrections.md) for the
   removed false bindings and the positive secondary-pass vertex capture.
   Including the neutral and task-local character compositions, the current
   Blender 5.2.1 validation boundary is 1,391 glTF files, 2,896 meshes, 387,370
   polygons, and 2,621 Actions. Mesh/polygon totals include Blender's armature
   display shapes; the three additional neutral rigs account for the 240-polygon
   increase, while source triangle totals remain unchanged.
5. [ ] Apply the same trace records to all 183 bank-01 characters, including
   dynamic facial slots and character-state material variants, rather than
   adding model-specific texture guesses. The available state set now proves
   132 material records and 709 variants across entries `0000`, `0001`, `0004`,
   `0067`, `0090`, `0094`, `0115`, `0127`, `0130`, and `0140`; entry `0000` is
   the verified high-detail Conker model. Nine of those entries have captured
   pixel/TLUT images; entry `0067` has runtime material state but no captured
   texture. The other 173 character records remain without correlated runtime
   material state, and 174 remain without captured-image evidence, rather than
   inheriting Conker's state. The texture-enabled
   Save-Game-13 capture proves dynamic segment-11 run 29 and segment-10 run 31.
   Correct base-tile selection resolves run 29 to a 32x32 CI8 eye image, with
   its captured half-texel origin applied to the posed UVs. Run 31 retains a
   different tile/combiner contract; a shared pixel address does not make the
   two draws equivalent. Segment-10 run 30 was not drawn in that task and
   remains unassigned rather than receiving adjacent state by assumption.
   A separate first-task snapshot of the complete 25-record runtime character
   pool now identifies 31 active bank-01 entries across all 26 supplied states.
   Material extraction accepts `--activity-manifest` and uses that evidence only
   when an ambiguous draw also selects the candidate material's exact matrix
   slot (or every original candidate is already in bank 01). This conservatively
   resolves 107 ambiguous correlation groups and 896 draw observations, adding
   16 material records and entry `0115` without using the pool to eliminate an
   object or level candidate. Nine active entries now have runtime materials;
   22 active entries still lack them, and 152 bank-01 entries were not active in
   any supplied snapshot. A second bounded trace hooks the actual character
   renderer entry and return, records its exact output-buffer range, and follows
   16 graphics-task submissions per state. Across the same 26 states it observes
   71 calls in 402 boundaries (400 untyped, two verified graphics tasks) for nine
   entries (`0000`, `0001`, `0067`,
   `0090`, `0094`, `0115`, `0127`, `0130`, and `0140`); all nine have
   correlated materials. Candidate intersection plus strict static-cluster
   ordering resolves 69 calls without guessing. For the remaining two entry
   `0130` calls, each selected runtime address equals one exact ROM
   primary/secondary pointer plus the same loaded-model base, resolving the
   duplicate-looking cluster aliases. All 71 calls are therefore resolved. This
   proves that entries `0000` and `0001` each
   render an offscreen texture-producing pass sourced from entry `0004`.
   The caller `func_15184FA4` selects a 64-wide eight-bit target before invoking
   the character renderer in mode 3. Its 21 calls are now separated from the
   50 ordinary calls, removing the false grey shell from Conker's body preview.
   Nine ordinary neutral-bind glTFs and diagnostic OBJs contain 261 exact
   clusters and all 3,494 source faces. Three separate `render-texture-*`
   neutral glTFs preserve the other 66 clusters and 1,061 source faces, retaining
   1,055 drawable faces. Combined source geometry is unchanged at 327 clusters
   and 4,555 source faces; all 71 calls and every original cluster are retained.
   The renderer-return segment-3
   palette is row-major float data, while the graphics-task submission is
   standard split fixed-point RSP data; replaying
   all 26 states validates 1,415 of 1,721 captures and isolates 306 uninitialized
   snapshots to six Save-Game-24 calls. Forty-four task-local posed glTFs now
   cover all nine drawn entries, with 21 additional offscreen posed exports; only
   six invalid/conflicting Save-Game-24 instances are rejected. The renderer-return
   trace captures 744 referenced
   texture images across 50 of 71 calls with no unresolved address. Refreshing
   correlations from the
   original command bytes produces 183 records and 917 variants; 834 variants
   contain a captured base image, deduplicated to 61 PNGs. All 2,071 resolved
   instance clusters retain exactly one trace/event owner. Passing this catalog
   separately as `--task-runtime-materials` assigns 1,451 ordinary posed runs an exact
   event-local runtime material. The current output links 162 ordinary neutral and 974
   posed runs to 114 copied PNGs; 932 posed runs select a task-local captured
   image, including 24 IA8 bindings. Remaining bindings require independently
   proven static images. A captured image is now excluded when every observed
   one/two-cycle combiner has no texture input, even if lighting or `K5` remains
   unresolved. This removes 457 false bindings over 5,552 faces in 22 poses.
   Exact event ownership does not establish complete appearance: inherited
   texture/coordinate state, runtime vertex colours and secondary-pass blending
   remain unresolved, along with N64 raster parity and unobserved entries.
   `func_1502E474` and `func_150A9984` now close the transform handoff: the
   former selects the active double-buffered palette and count, and the latter
   converts each `0x40`-byte row-major float matrix in place to split signed-16.16
   RSP form. Task traces also show segment 3 rebased to interior palette slots,
   so composition now identifies global slots by renderer root plus absolute
   address rather than by a segment-relative offset. The neutral-bind files
   remain the topology-review artifacts. Posed vertex placement follows the
   proven runtime row-vector transform contract, while lighting, combiner,
   mipmap, and raster parity remain separate preview limitations.
   Posed glTFs now preserve authored surface normals using each corner's
   vertex-load matrix inverse transpose. The 44 ordinary poses retain 55,170
   transformed normal corners and 1,494 geometric fallbacks; 21 offscreen poses
   retain 12,163 transformed corners and 62 fallbacks. This closes the previous
   flat-normal interchange loss without claiming native vertex-lighting parity.
   A subsequent audit of the [pinned GLideN64 vertex consumer](https://github.com/gonetz/GLideN64/blob/41c7ba273a6c9afb43c0574cf3cf5d139182d070/src/gSP.cpp#L1156)
   found that the trace decoder skipped projection
   matrices and retained matrix/light/normal state only at triangle time.
   The decoder now captures projection loads and multiplies, replays model-view
   push/pop and multiply order, and associates each triangle corner with its
   vertex-load state. Hash-checked replay recovers this derived evidence from
   captured bytes without rewriting original material-state hashes. A new
   Save-Game-13 scene-task capture contains 90 matrices and resolves complete
   transforms for all 254 vertex loads; 1,628 of its 6,795 drawn corners retain
   an earlier matrix than the current draw state. Using transformed positions
   changes 706 of 913 captured Conker vertex colour calculations, with a maximum
   channel difference of 0.320858. The second event was subsequently identified
   as an audio task (OSTask type 2) and is excluded from graphics replay.
   These are positive runtime input captures,
   not rendered-frame parity. The exporter now carries per-corner load-time
   colours through material correlation, face filtering, composition and posing.
   A further full-task capture retains 208 vertex-byte spans. Joining exact
   source positions and cache slots (including the different stored TRI4 order)
   proves colour samples for 1,085 faces: 811 in entry 0, 64 in entry 4, and 210
   in bank-04 entry 27. Whole-cluster vertex matching now resolves 17 ambiguous
   material clusters (58 draw observations); identical geometry aliases remain
   ambiguous. This restores Conker's eye bindings and covers all 36 body runs.
   Capture-specific previews bake 876 fully covered faces in 42 material runs
   into 998 floating-point vertex colours, using
   `KHR_materials_unlit` to prevent a second lighting pass. Conflicting or missing
   observations block an aggregate colour consensus. The 161 previous aggregate
   draw-time lighting approximations are removed; all source faces, linked
   texture runs, linked texture faces and copied base PNG counts are unchanged.
   The next step is to expand vertex/projection capture coverage and submitted
   pose coverage. The full Python suite passes 546 tests; all four model banks
   still rebuild byte-identically.
   Blender validates the 1,391 main exports and all 1,314 capture-specific exports.
   The reproducible capture and comparison are under ignored
   `build/assets/models/reference/vertex-light-state/` (`spec.json`, `trace.jsonl`,
   `audit.py`, and `audit.json`).
   The vertex-complete capture and export audit are under
   `build/assets/models/reference/vertex-light-export/`, with its own four-bank
   preview set and Blender validation report. The aggregate material catalog
   includes this additional trace alongside the original 19 task traces. Vertex
   refinement expands the aggregate
   catalog to 561 material identities and 1,879 variants, adding four bank-04
   bindings for 197 faces. Per-model source and drawable face counts remain
   unchanged across all 1,031 models. The new
   `previews/conker-captured-colours-bind.png` is a neutral-pose diagnostic; it
   does not claim submission-matched pose lighting. The character trace now
   filters OSTask type 1 explicitly. A 600-second follow-up captured the initial
   graphics task and two renderer returns, but no following graphics task; that
   dummy-renderer run remains a bounded negative result. The audit and
   regeneration commands are under
   `build/assets/models/reference/submitted-character-lighting/`.
   The optional pinned software-renderer follow-up now reaches two verified
   graphics tasks and proves both renderer ranges execute exactly once in the
   next task. Their matrices and material observations come from that submitted
   range, with command ancestry separating instances of shared lists. Conker's
   slots 13 and 14 change after renderer return; 34 ear triangles collapse,
   leaving 777 drawable body faces from 811 source faces. All 777 retain captured
   vertex colours. Native frames show the green helmet that explains the hidden
   ears. At that stage the composition still lacked the separate helmet; the
   attachment follow-up below closes that captured-state gap. The activity catalog contains
   400 old untyped boundaries plus two verified graphics tasks, with all 71 calls
   and 128 part selections retained. Its draw-material catalog contains 199
   records and 1,033 variants. The new trace, native frames and regeneration
   commands are under `build/assets/models/reference/software-submitted-lighting/`.
   Captured vertex agreement is now required even for a unique command-pattern
   match when vertex bytes are available. This removes seven unsupported
   assignments from the aggregate catalog and fourteen from the new software
   capture, including a false tank-flag match. The aggregate still retains 561
   material records and 1,879 variants; the isolated vertex-colour catalog drops
   from 61 to 58 records. A vertex-complete Tediz capture supplies two distinct
   338-face instances; their differing colours remain separate observations.
   The corrected main exports validate as 1,391 glTFs, 2,896 meshes, 387,338
   polygons and 2,621 Actions. Standalone source geometry remains 1,031 models
   and 213,946 faces.
   A subsequent capture of `func_150311C4` proves two separate attachments on
   parent bone 12: bank-09 entry 29 (cigar, 16 vertices/20 faces) and entry 133
   (helmet, 69 vertices/58 faces). Their selected part-table pointers, relocated
   command words and all 85 captured vertex positions match the ROM. Their
   submitted command buffer and matrix bytes also match the body capture.
   `func_1502FE10` proves their three-pair pointer-table header and vertex base at
   `+0x18`; `func_1502FFD8` supplies the double-buffered vertex copies. The
   bank-09 extractor now includes all 155 containers with 10,235 vertices and
   8,896 faces, alongside the six existing direct-header models. All 120 rigid
   and 35 jointed attachments reconstruct byte-exactly from parsed headers,
   vertices, part pointers, joint records and preserved display-list/normal
   regions. `func_1503F4B0` calls the character pose builder `func_150A81D0`,
   establishing the shared neutral joint hierarchy. Callable parts cannot borrow
   vertex or material state from their stored neighbours. Unknown inherited UV
   state stays unresolved. The 322 other nonempty bank-09 entries remain
   unclassified; the parser does not promote them from opcode signatures.
   The canonical source inventory expands to 1,186 models and 222,842 faces,
   preserving all previous 1,031 models and their geometry counts. Captured
   RGBA32 export now resolves the helmet straps and front panel using the proven
   complete LoadBlock contract, including odd-row eight-byte swaps and alpha.
   The isolated posed comparison retains all 78 attachment faces with captured
   textures and per-corner colours from their submitted command ranges.
   `model-assets compose --attachment-trace <jsonl>` now joins selected native
   parts to the matching parent composition. It requires the same submitted
   command buffer and exact matrix bytes, reloads runtime vertex/normal inputs,
   and selects materials from the body's submitted task and each attachment
   call's ancestry. No model-specific placement is supplied. Save-Game-13 now
   exports 855 drawable faces from 889 source faces: 777 body faces plus the
   cigar's 20 and helmet's 58. The original 34 collapsed ear faces remain
   recorded. Other body poses and all 1,186 standalone models are preserved.
   The new capture spec is `config/model-trace-attachment-draws.json`.
   Coverage records attachment-parent observation separately from unknown scene
   identity. Additional attachment states, animations and native raster parity
   remain open.
   The refreshed aggregate catalog has 603 records and 1,944 variants; the
   draw-specific catalog has 204 records and 1,043 variants. Expanding the
   candidate inventory removes five formerly unique bank-04 assignments rather
   than retaining associations that are no longer supported. Source meshes are
   preserved. The main Blender gate imports 1,546 glTFs, and the separate
   captured-colour set imports 1,469; all 564 unit tests pass.
   Evidence and reproducible scripts are in
   `build/assets/models/reference/software-submitted-lighting/attachments/`.
   Selected base tiles now correct 63 material runs in 29 characters, covering
   931 source faces without changing triangle or run boundaries. Runtime tile
   bounds are replayed from the saved command bytes, and captured images carry
   matching UV dimensions and origins into both standalone and composed exports.
   Wrapped/fractional origins on supported repeating LoadBlock tiles scroll the
   mask-sized image. Native clamp, broader runtime scale/addressing changes,
   complete TMEM history, and intra-task render-target feedback remain open.
   Internal renderer hooks now also preserve the selected normal/extra part
   table, display-model index, part index, and exact display-list address for
   every emitted part. The corpus contains 128 selections across ten display
   model indices. Model-index filtering, sibling part order, and exact
   relocation against each ROM header's primary/secondary pointer table resolve
   all 128 to one static cluster sequence. A separate graphics-boundary header
   sweep
   observes exact part-count and table-address records for 147 of the 183
   non-empty bank-01 entries across the 26 states. The 36 absent entries remain
   explicitly unobserved rather than inheriting a neighbouring model's part
   layout.
6. [ ] Recover complete room and level placement after standalone model
   validation. The bank-11 dispatch contract now resolves 716 of 727 records to
   570 matching bank-04 segments and assembles 52 scene glTFs. All 52 import in
   Blender with finite geometry. Scenes 17 and 62 retain eleven records without
   assembly because their matching bank-04 bundles are absent; no substitute is
   guessed. Static terrain collision is now separated as 58 primary plus 38
   secondary bank-04 meshes, 98,479 portable triangle-offset records, and
   97,071 byte-exact primary surface words. The third collision array is
   represented by 1,055 resolved transformed placements across 98 scene files;
   172 source records are excluded by the runtime flag and eleven remain absent
   with scenes 17 and 62. Remaining layers are portals, lights, fog, cameras,
   triggers, and their scene display lists.

Two other large shared frontiers remain visible in the manifests: 38,063 faces
lack a proven texture-source mapping, and 5,223 faces use runtime-selected
segments. Both should consume the trace schema above instead of acquiring
one-off preview overrides.

## Audio beyond MP3

- [x] Prove indexed bank `0x17` entries `0` through `3` from the main audio
  initialization path.
- [x] Identify the `B1` sound-bank control, external sound-bank data, wavetable,
  and `S1` compact-sequence bank roles.
- [x] Add byte-identical verification and raw extraction of all 149 compact
  sequences while retaining the three sound-bank companion payloads.
- [x] Add deterministic, single-pass Standard MIDI previews with scheduled note
  releases and exact Conker loop payloads retained as sequencer-specific events.
- [x] Parse the complete Conker-extended `B1` graph: instruments, percussion,
  sounds, envelopes, key maps, wavetables, ADPCM books, and loops.
- [x] Split the 21,705,520-byte wavetable into individually bounded samples
  using only sound-bank references.
- [x] Export the US ADPCM samples to source-linked mono PCM16 WAV previews and
  validate decoded loop frames against the retained B1 loop states.
- [x] Extract source-linked timing for every MP3-embedded `L:` cue record while
  retaining its six unproven payload bytes without assigning speaker semantics.
- [ ] Prove a byte-identical ADPCM encoder before accepting edits to the WAV
  previews. (The current US bank contains no RAW16 samples.)
- [ ] Decode compact sequences into an editable representation while retaining
  Conker's loop-marker extensions and byte-identical reconstruction.
- [ ] Correlate sound, instrument, and sequence IDs with runtime callers and
  beta fingerprints before assigning semantic names.
- [ ] Add indexed-bank insertion only after flags, alignment, recompression, and
  unchanged-ROM behavior are proven.

## Animation and rigs

- [x] Locate and export all bank-01 joint hierarchies and rigid display-matrix
  assignments: 3,518 joints across 183 character containers.
- [x] Preserve all 145 bank-02 character-animation companions byte-identically,
  including 123 even paired-segment tables and 22 direct payloads.
- [x] Decode the runtime-traced first pose from bank-02 entry `0000`, pair
  `0025`, and retain it as a named Action and manifest reference. The default
  nodes remain neutral; the paired `0000-00-bind.gltf` contains no animations,
  avoiding Blender's automatic Action selection during geometry inspection.
- [x] Decode all 2,621 nonempty bank-02 skeletal timelines (57,732 source
  frames), including the two formerly exceptional fixed-stride layouts.
- [x] Export all 2,621 nonempty clips to their same-index bank-01 rigs as glTF
  rotation, root-motion, and masked joint-translation channels (57,732
  source frames).
- [x] Attach the bank-15 logical animation IDs to every routed glTF Action and
  resolve all five character-state duration overrides.
- [ ] Resolve the remaining material/lighting state before assigning
  blended-skin, morph, or facial semantics. The exact 30 Hz runtime animation
  clock is already applied to every exported Action.
- [ ] Trace lip-sync or mouth-cue data and connect it to speech assets.
- [ ] Preserve and extend the already proven vertex-colour animation records.

## Levels, scenes, and collision

- [x] Extract the two runtime `0x44`-byte object-record sources, prove position,
  YZX Euler rotation and scale, and assemble 48 direct bank-12 scene previews.
- [x] Resolve bank-11 dispatched placements through
  `[04, scene-index, dispatch-index]` and assemble every scene whose bank-04
  bundle exists: 716 records across 52 scenes. Preserve the eleven records in
  scenes 17 and 62 as unresolved because those two bank-04 bundles are absent.
- [ ] Recover the remaining level/room graphs, portals, lights, fog, cameras,
  triggers, and scene display lists.
- [ ] Extend renderer-provided segment-8 resolution beyond the 138 material
  records and 13 exact list payloads reached by the supplied runtime states;
  unobserved references must not be forced into standalone models.
- [x] Extract static terrain collision geometry and its per-face records.
  `func_15003668` selects bank-04 segments zero and three, and `func_15001460`
  constructs the runtime 12-byte triangle-pointer records from the already
  decoded display lists, so the portable export stores three big-endian
  model-relative vertex byte offsets. The 58 primary and 38 secondary meshes
  contain 98,479 records. The associated 97,071 four-byte surface words are
  copied byte-identically from the primary tables; the secondary layer has no
  installed surface table. All 96 glTF previews import in Blender 5.2.1 with
  98,291 nonzero-area faces; the 188 source zero-area records remain in the
  binary inventories.
- [x] Assemble transformed placement models into the third collision array built
  by `func_15003668`. `func_150039E0` copies source byte `0x32` to runtime byte
  `0x4F`; the collision builder excludes `(flags & 0x60) == 0x20`. The export
  consequently retains 1,055 resolved included placements in 98 glTF scenes,
  records 172 excluded placements, and leaves the eleven included records in
  absent bank-04 scenes 17 and 62 unresolved.
- [ ] Resolve the meanings of surface metadata, including physical and audio
  behavior, without inferring them from visual materials.

## Dialogue, cutscenes, and interface

- [ ] Find string and localization tables, subtitle text, speaker IDs, timing,
  and MP3-to-dialogue mappings.
- [ ] Extract cutscene scripts, camera tracks, event timelines, and lip-sync
  references.
- [x] Recover the code-backed HUD/menu layout-node schema, glyph map, 92 sprite
  selectors, their complete 159-resource spans, all 92 renderer-derived selector
  previews, and the selector-26 animation separately from texture payloads.
  Semantic icon/controller names remain later runtime-correlation work.

## Effects and recorded data

- [ ] Extract particle/emitter descriptors, texture sequences, material
  animation, decals, debris, water, fire, and their model/audio references.
- [ ] Identify attract-mode or replay controller streams and other recorded
  demo data.
- [ ] Separate data-driven progression/configuration tables from executable
  code and preserve their original binary representation.
