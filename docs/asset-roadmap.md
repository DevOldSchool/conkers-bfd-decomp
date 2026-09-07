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
- [x] Model geometry: extract and byte-verify 1,031 records from the four proven
  model-bearing families, including material runs, joint assignments, and
  dynamic segment references. Of these, 1,029 records contain drawable faces.
- [ ] Model semantics: resolve names, complete runtime materials and lighting
  state, and recover the remaining scene consumers and surface-word meanings.

## Model extraction status

The current US model extractor covers every indexed bank with a proven model
container contract. All 6,499,720 extracted model bytes verify against the ROM.
Generated OBJ, MTL, glTF, binary buffers, textures, animations, and manifests
remain below ignored `build/assets/models/` paths.

The Models Resource's external **Conker (Cutscene)** package is useful as a
non-authoritative visual cross-check, but none of its files are copied into the
extractor or generated output. Its Collada scene separates 17 Conker draw groups
(933 triangles) and five frying-pan groups (92 triangles). That does not replace
the ROM contract: the runtime counter in `func_1503D984` counts exactly the same
811 triangles decoded from bank-01 entry `0000`, whose header has no secondary
display list. The external package is therefore a different or post-processed
mesh, not evidence that the ROM exporter omitted 122 triangles. The comparison
also exposed an exporter defect: the ROM model uses repeat, mirror, and clamp
tile modes, which the glTF exporter now preserves per material instead of
forcing every linked texture to repeat.
Reference: <https://models.spriters-resource.com/nintendo_64/conkersbadfurday/asset/348120/>.

| Bank | Proven family | Models | Vertices | Faces | UV coordinates | Current preview status |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `01` | Rigged character containers | 183 | 56,412 | 62,073 | 67,804 | 2,621 clips, decoded CBFD normals, plus 1,338 drawable material runs and 26,395 preview faces linked to 408 conservative runtime-composed PNGs |
| `03` | Direct object models | 77 | 5,062 | 3,894 | 4,945 | 48 assembled bank-12 scenes with 511 placements; CBFD normals on 28 models; 25 material runs linked |
| `04` | Segmented level/model bundles | 765 | 209,274 | 147,723 | 204,493 | 52 assembled bank-11 scenes with 716 dispatched placements; all three collision arrays represented as 96 static-terrain meshes plus 1,055 transformed placements; CBFD normals on 107 models; 1,345 drawable material runs and 36,775 preview faces linked to 442 proven PNGs |
| `09` | Direct-model-compatible subset | 6 | 254 | 256 | 254 | Four CI8 runs and 52 faces linked to two runtime-composed PNGs |
| **Total** |  | **1,031** | **271,002** | **213,946** | **277,496** | **All generated glTF files pass structural verification** |

Completed model work:

- [x] Preserve every proven container and auxiliary region byte-for-byte rather
  than discarding zero-face records or unresolved companion data.
- [x] Decode primary model display lists, vertex loads, standard and packed
  triangle commands, material-state runs, UV transforms, and runtime segment
  references.
- [x] Export OBJ/MTL interchange files and glTF previews with N64 vertex colors,
  proven UVs, decoded CBFD normals in glTF, per-material repeat/mirror/clamp
  sampler state, and only texture bindings supported by extractor evidence.
- [x] Apply the dedicated CBFD normal-stream replay to every model-bearing bank,
  not only characters. Bank `03` contains 79 `DC38000E` normal-base commands
  across 28 models, yielding 3,884 nonzero and 415 zero source-normal corners.
  Bank `04` contains 342 commands across 107 models, yielding 11,634 nonzero
  and 5,643 zero corners. The generic glTF exporter emits those normals and uses
  geometric fallbacks only for the explicitly zero vectors.
- [x] Export all bank-01 character hierarchies with rigid display-matrix
  assignments and validate both animated and animation-free bind glTF files
  for all 183 records. The ROM vertices are joint-local and the joint-table
  floats are parent-relative translations. The exporter accumulates the joint
  hierarchy to obtain model-space pivots, then bakes each rigid run through its
  accumulated pivot and emits the matching inverse-bind matrix. This corrects
  the previously separated limbs, head, and tail caused by treating each local
  translation as an absolute pivot. Interactive Blender import of a
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
- [x] Trace the render-time non-null rewrite path through `func_1510CE60`,
  compose non-overlapping single-`TEXEL0` CI4/CI8 images with their trailing
  runtime TLUTs, and reject packed layouts whose nominal pixel span overlaps
  that palette instead of exporting false diffuse images. Both modes address
  their palette from payload end minus `0x200`; CI4 loads the first 16 entries.
- [x] Preserve every material run's complete `F5` render-tile ladder, including
  the TMEM offsets for lower mip levels. `TEXEL0`/`TEXEL1` runs remain unlinked
  because a base-level diffuse texture would misrepresent the RDP LOD blend and
  dynamic primitive/environment colours.
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
- [ ] Resolve packed or mipmapped character texture layouts and capture the
  proven runtime primitive/environment-colour tables for concrete character
  states; dynamically selected facial slots must likewise be captured with
  their character state rather than assigned one global texture.
- [ ] Resolve scene-selected and renderer-generated segment-8 state from
  reproducible runtime traces; do not assign those references statically.
- [ ] Correlate numeric model IDs with runtime callers before assigning semantic
  character, prop, level, or variant names beyond the verified Conker preview.
- [ ] Recover the remaining level/room scene graph consumers; these are related
  to models but are not standalone model-container extraction.

### Cross-bank model completion plan

The decoded standalone inventory contains 213,946 source faces. Interchange
previews retain 213,566 drawable faces after omitting 380 source zero-area
commands; 63,462 preview faces have evidence-backed texture bindings. The
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
   Unmatched and genuinely ambiguous clusters remain explicit rather than
   receiving a guessed model or texture identity.
2. [x] Generate a texture- and lighting-independent validation atlas for every
   model, using unique colours per rigid joint or material run and several fixed
   camera angles. Record detached or overlapping components, extreme bounds,
   invalid joint assignments, inverted normals, and zero-area triangles before
   a textured preview is accepted. `./conker model-assets atlas --force` now
   software-renders front, side, and top views for all 1,031 records without a
   Blender dependency and writes an HTML atlas plus a machine-readable manifest.
   The current complete pass classifies 408 models as structurally accepted, 623
   for review, and none as structurally rejected. It exposes 380 zero-area faces, 16,826 exact
   coincident triangles, 14,600 source-normal/winding disagreements across the
   three normal-bearing banks, and
   three bank-04 bounds outliers. Disconnected components and normal disagreement
   are review findings rather than automatic corruption claims because rigid
   character parts, double-sided surfaces, and independent level components can
   be intentional. The 380 zero-area faces are explicit source commands across
   standard `0x05`/`0x06` and packed `0x10`-`0x1F` triangle opcodes: 121 repeat a
   vertex index, 136 reference distinct vertices at duplicate positions, and 123
   are collinear. Their face indices, display-list offsets, and opcodes remain in
   the manifests, while OBJ/glTF previews omit them because they cannot rasterize
   a surface. Invalid joints or non-finite bounds remain hard rejection reasons;
   exact coincident triangles remain visible for review because the original
   display list can deliberately redraw a surface in multiple passes.
3. [x] Resolve the mode-one CI8 palette source used outside bank 01. The parser
   contract is consumer-dependent rather than one shared palette: bank-03's
   object loader and bank-04's initial slots plus `D_800B0E50` indexed placement
   instances pass a null fifth argument to `func_1510CE60`, leaving the TLUT at
   payload base and overlapping the first 512 pixel bytes. Those 3,002 and
   70,475 faces remain deliberately unlinked instead of receiving the visually
   plausible but runtime-incorrect trailing palette. Bank-09's
   `func_1502FE10` and `func_1518C900` pass a non-null rewrite table, proving
   `payload_end - 0x200`; its four affected runs and 52 faces now use
   runtime-composed CI8 previews.
4. [x] Translate captured RDP combine, primitive/environment colour, alpha,
   mipmap, and `TEXEL0`/`TEXEL1` state into reusable glTF preview materials,
   retaining the exact unsupported state in metadata whenever glTF cannot
   reproduce it. `./conker model-assets materials --trace <trace.jsonl> --force`
   now validates correlated identities against the exact ROM and aggregates
   matrix-independent runtime material variants. The supplied OpenEmu scene
   yields 75 static material records and 79 variants from 820 correlated draw
   observations: 29 records belong to two bank-01 characters and 46 to thirteen
   bank-04 models. Preview generation accepts that manifest with
   `--runtime-materials`, embeds every captured combiner, tile/TMEM, colour,
   geometry-mode, lighting, and texture address variant in glTF extras, and
   translates unanimous RDP filtering plus alpha/blend state into glTF sampler
   and alpha modes. The current capture contains 27 variants whose base-colour
   product would otherwise map to glTF but has RSP lighting enabled, 17 explicit
   `TEXEL0`/`TEXEL1` LOD variants, four RGB-only mappings with unsupported alpha,
   and 31 other unsupported combiners. None is falsely flattened to a diffuse
   material. The trace decoder now mirrors the dedicated F3DEX2CBFD light path:
   `DB` light count is divided by 48, `DC` selector `0x0A` addresses 48-byte
   extended light records, coordinate-modifier writes are replayed, and opcode
   `0xDD` selects advanced lighting. The supplied task captures 16 unique light
   records through 56 commands with no unresolved address; all 1,066 lit draw
   runs carry decoded light state, split between 11-light and three-light
   configurations, and 791 runs use advanced lighting. The same task contains
   83 resolved selector-`0x0E` normal streams, covering all 791 advanced-lit
   runs. The material manifest retains 96 distinct matrix/normal lighting
   contexts without adding them to the 79 material-variant identities. The
   exporter now mirrors GLideN64's CBFD basic and advanced per-vertex lighting,
   including inverse model-view direction transforms, coordinate modifiers,
   point attenuation, signed vertex flags, and source normal bytes. All 27
   directly translatable lit variants have one unambiguous observed context;
   their 2,267 vertices are baked into floating-point glTF colours. This is
   labelled GLideN64-equivalent evidence, not a hardware-microcode proof.
5. [ ] Apply the same trace records to all 183 bank-01 characters, including
   dynamic facial slots and character-state material variants, rather than
   adding model-specific texture guesses.
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
- [ ] Resolve renderer-provided segment-8 display lists from reproducible
  runtime states rather than forcing them into standalone models.
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
