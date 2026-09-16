# Asset extraction roadmap

Current US roadmap. Model inventory and validation checked **16 September 2026**.
This tracks what is supported and what remains to do; detailed byte and consumer
evidence lives in the linked documents.

The goal is reversible extraction directly from the ROM. Save states, native
captures and external models are comparison references, not substitutes for ROM
geometry or textures. Keep generated assets under ignored `build/` paths and
preserve unrelated code-matching work.

## Current asset families

| Family | Current state | Remaining work |
| --- | --- | --- |
| Grayscale RLE fonts | Reversible glyph extraction and packing | Semantic use and interface integration |
| MP3 audio | Reversible stream and decoder-table extraction | Dialogue, speaker and event associations |
| Other audio | Sound-bank graph, samples, sequences and previews extracted | Reversible editing and runtime names |
| Textures and materials | Proven indexed/direct formats and guarded ROM selectors supported | Unsupported material formulas and runtime-dependent state |
| Model geometry | 1,487 records byte-verified across four proven families | Review and publish usable exports; investigate unclassified data only with consumer evidence |
| Animation and expressions | Rigs, skeletal clips, stored morph endpoints and expression records extracted | Runtime triggers, expression playback and native interpolation |
| Scenes and collision | Placements, scene previews and collision geometry extracted | Complete rooms, surface semantics and environmental state |
| Effects | Proven effect meshes and skeletal emission points extracted | Complete emitter behavior, material animation and effect associations |

## Models: inventory and inspection

All **7,121,632 decoded model bytes** reconstruct against the US ROM. The
inventory contains **232,162 source faces**; 1,485 of its 1,487 records have
drawable geometry.

| Bank | Proven model family | Extracted records | Curated standalone entries | Extracted review tab |
| --- | --- | ---: | ---: | ---: |
| `01` | Rigged characters and animated props | 183 | 177 | 6 |
| `03` | Direct object models | 77 | 68 | 9 |
| `04` | Segmented level/model bundles | 765 | 341 | 424 |
| `09` | Direct, relative-address, attachment and effect models | 462 | 278 | 184 |
| **Total** | | **1,487** | **864** | **623** |

All remaining records are available in the **Extracted review** tab. Their current status is:

| Review status | Records | Next action |
| --- | ---: | --- |
| Material blocked | 26 | Prove missing texture bindings, layouts or render state |
| Appearance blocked | 1 | Resolve stationary tank part visibility and colour state |
| Reviewed fragments and variants | 594 | Identify useful standalone exports and inspect variants in scene or effect context |
| No drawable faces | 2 | Preserve source records for completeness |

Material-complete deferrals remain eligible for further standalone review. Missing
combiner state is classified as unresolved, even when texture use is unknown.
The **621 drawable review records** are not a count of missing characters or a
requirement to display every fragment. Published models can still need
appearance fixes.

The gallery at `build/assets/models/inspect/index.html` contains **1,516 entries**:
**893 curated exports** and **623 extracted review records**. The curated set
contains 864 standalone models and 29 static scene assemblies, split into
**106 characters, ten collectables, 600 scene items and 177 parts/effects**.
The assemblies expose **169 otherwise deferred components** in scene context;
they do not increase the extracted source-record inventory. Open the self-contained GLBs in Blender using
Material Preview. Animation-free `*-bind.gltf` sources remain available for
geometry diagnostics.

**Extracted review** shows the remaining exports with status and bank filters,
current cached thumbnails and downloadable GLBs. Two records with no drawable
faces have explicit placeholder cards. Material and appearance blockers remain
labelled, and inclusion here does not change their acceptance state. Review
files live under `inspect/review/` and `previews/review/`; the manifest keeps
`review_models` separate from the curated `models` list.

Current [standalone review selections](evidence/us_model_review_selections.md)
include coherent props, explicit barrier variants, a chair and two terrain/room
segments. The review notes identify **31 records with the same exported glTF
presentation** as a curated entry and distinguish other similar props from
proven matching exports. Runtime roles remain separate questions.

Scenes **0, 2, 6, 11, 12, 14, 23, 25–28, 30, 35, 36, 40, 41, 44–47, 49–54, 65, 67 and 68**
combine 356 distinct ROM models in 589 instances using recovered loader slots
and placement records.
They include lava chambers, walkways, industrial shafts, a tiled room and a
mossy chamber. Deferred source notes link back to their assembled scene context.
Scene 54 explicitly selects intact walls and unlit indicators, omitting
overlapping alternatives, untextured effect planes and collision-only slot 3.
Other selections also omit identified effect planes and untextured surfaces
whose appearance needs runtime state; each omission is recorded.
Scenes 28 and 41 omit colocated debris pending fracture/visibility state; scenes
49 and 53 use explicit surface alternatives. Candidate assemblies 57 and 60
remain unpublished because detached elevated geometry needs visibility or
placement investigation. Scene 45 selects the map easel instead of the colocated
tower. Scene 65 combines the graveyard and water cavern, retaining textured
surface 11 and omitting overlapping surface 15 and untextured corner panel 16.
Scene 36 includes all recovered renderable placements in a circular stone arena.
Scene 52 assembles the tiered industrial yard while omitting paired doors and
isolated untextured surfaces. Matching placement matrices alone do not establish
alternative geometry: its two door meshes extend in opposite local directions,
so their complementary or conditional visibility remains unresolved.
Scene 6 combines the spiral stone tower, meadow and ruins, selecting barrier
segment 30 while omitting colocated parts 28/29 and untextured effects. Scene 14
combines the fortified courtyard and bridges; its origin-positioned platform and
four beams remain omitted pending runtime placement or visibility evidence.
Scene 2 combines the lava caverns and stone structures with explicit surface
variants, omitting repeated weights and unresolved fragments. Scene 12 combines
the windmill clearing and wooden fixtures, retaining the animal head while
omitting its colocated fragments.
Scene 0 combines the cavern workshop and target fixtures, retaining grate 15
instead of colocated untextured surface 13. Scene 18 remains held: its main
room has prominent white surfaces whose effective appearance is unresolved,
even after omitting secondary untextured surfaces and platform 03:0049:00.
Candidate 10 is held for loose geometry below the floor; candidate 20 is held
for detached elevated arch pieces. These require placement or conditional
visibility evidence before publication.
These are static inspection selections; native visibility, animation, lighting
and fog remain unresolved. See [the assembly evidence](evidence/us_static_scene_assemblies.md)
and [the reproducible selections](../config/model-scene-assemblies.json).

[The inspection configuration](../config/model-inspection.json) controls the
published models, categories and searchable labels. Names supported only by
visual references retain that identification basis; bank, entry and segment
remain the ROM identities.

### Supported model extraction

- [x] Preserve proven container headers, vertices, display lists, auxiliary data
  and zero-face records for byte-identical reconstruction. Bank 09 includes
  296 direct models, 155 attachments and eleven effect models.
- [x] Decode primary and selected callable display lists, packed triangle
  commands, material runs, UV transforms and runtime segment references.
  Assign each cached vertex to its load-time matrix; preserve source geometry
  and explicit degeneracy records.
- [x] Export OBJ/MTL and glTF with rigid joints, source normals and colours,
  proven face culling, sampler state and evidence-backed texture bindings.
  Preserve unsupported inherited state as unresolved metadata.
- [x] Decode supported CI4/CI8, RGBA16/RGBA32, IA4/IA8/IA16 and I4/I8 images
  under checked palette, tile, TMEM and payload contracts. Supported paths
  include odd-width CI4, wrapped CI8 addressing, RGBA16/RGBA32/IA4/IA8 mip chains and
  shade-only intensity alpha. Detail-texture previews record the selected
  ordinary mip and its own UV state. glTF does not reproduce native N64 LOD
  or detail blending.
- [x] Replay partial RGBA16 and split-bank RGBA32 LoadBlocks within a
  single callable list. Every sampled byte must come from a bounded ROM load;
  later tile definitions do not change earlier load destinations. CI8 uses the
  selected trailing palette; CI4 can select a bank of a full 256-entry palette.
  RGBA8 without TLUT expands each byte into colour
  and alpha. Attachments `09:0026`, `0027`, `0098`, `0107` and `0157` have
  complete texture coverage and are published with descriptive labels.
  Blue hexagonal canister `09:0110:00` also has all 20 faces textured, using
  retained flat-1552 indices and the flat-1553 palette. See
  [the bounded replay evidence](evidence/us_partial_tmem_loads.md).
- [x] Resolve the reviewed scene/object texture-animation table through its
  placement updater and renderer. Preserve all stored frame indices and decode
  every frame; show the first stored frame as an explicit inspection preset.
  Current bindings cover water surfaces, waterfalls, animated B-pad sides and
  glowing fragments. Gameplay phase and UV animation remain separate.
- [x] Resolve primary terrain texture selectors for four scenes, preserving
  their frame alternatives, texture type groups and per-segment phase offsets.
  Inspection states remain explicit; current gameplay state is not inferred.
- [x] Resolve the two reviewed ordinary-object CI8 selector paths, preserving
  their segment pairs, trailing palettes and explicit loader-selector presets.
- [x] Resolve reviewed bank-09 attachment action/updater texture bindings,
  checking inline CI4/CI8 palette offsets and all retained screen frames.
  The lit cigarette, yellow handheld console and faceted grey attachment have
  complete texture coverage; dynamic colours and attachment poses remain
  separate appearance work.
- [x] Resolve the two complementary four-selector loops in bank-09 constructor
  `1513A6E0`, preserving their six ROM selection masks and full 32-bit flags.
  Eight orange-fur fragments and surface variants have complete texture links;
  effect assembly and motion remain separate work.
- [x] Decode all 20 constructor descriptors selected by the reviewed actor-type
  switch, two-entry mask loops and static attachment actions. Apply shared
  I8/IA mip and shade-alpha handling under complete payload bounds. A ROM-only
  constructor report separates missing renderer proof from decoder failures;
  discovery alone never grants export eligibility.
- [x] Resolve type-selected fragment arrays through the signed `-1` callback
  sentinel, preserving callback-enabled type exclusions and full selector bounds.
  Support the standard shaded RGBA16 mipmap formula under the existing complete
  mip-chain and payload checks.
- [x] Resolve two reviewed object callbacks through their constructor payloads
  and CI8 descriptor tables. Two clothing fragments and two effect surfaces
  have complete texture links. Preserve correlated texture alternatives and
  label the selected constructor state as an inspection preset.
- [x] Resolve direct pixel segments for the four-digit timer and a kind-2
  animated attachment. The timer displays an explicit 00:00 preset and retains
  all ten IA4 glyphs; the attachment retains both RGBA32 frames. Parent pose,
  animation playback and current gameplay state remain separate.
- [x] Resolve ordinary character facial textures from ROM defaults, with
  separately labelled expression, instance and renderer-state presets.
  Current coverage includes Wise Guys shirts, Birdy's transparent hay, Carl's
  inactive eyelids, stationary tank headlights and The Experiment's undamaged
  state. Presets do not claim to represent every gameplay appearance.
- [x] Preserve selected character parts, attachments and submitted poses for
  independent native comparisons. Keep those captured-state diagnostics
  separate from the ROM-only inspection gallery.
- [x] Automate geometry checks, deterministic previews, per-file validation,
  packed GLB checks and publication. Reject unsupported texture guesses and
  incomplete dependencies rather than silently substituting assets.

Evidence: [ROM character defaults](evidence/us_rom_character_defaults.md),
[character draw tables](evidence/us_character_draw_tables.md),
[placed-object materials](evidence/us_object_material_consensus.md),
[bank-09 object materials](evidence/us_bank09_object_materials.md),
[relative-address models](evidence/us_bank09_relative_models.md),
[effect models](evidence/us_bank09_effect_models.md),
[Wise Guys shirts](evidence/us_wise_guys_shirt.md),
[Birdy's hay](evidence/us_birdy_hay_material.md), and
[submitted poses](evidence/us_submitted_model_poses.md),
[odd-width CI4](evidence/us_direct_odd_width_ci4.md),
[RGBA16 mipmaps](evidence/us_direct_rgba16_mipmaps.md),
[RGBA32 mipmaps](evidence/us_direct_rgba32_mipmaps.md),
[intensity materials and mipmaps](evidence/us_direct_intensity_materials.md),
[CI8 TMEM wrapping](evidence/us_ci8_tmem_wrapping.md), and
[scene detail textures](evidence/us_detail_indexed_textures.md), and
[object texture animation](evidence/us_object_texture_animation.md), and
[scene texture bindings](evidence/us_scene_texture_bindings.md), and
[object texture selectors](evidence/us_object_texture_bindings.md), and
[attachment texture selectors](evidence/us_attachment_texture_bindings.md), and
[object callback texture selectors](evidence/us_object_callback_texture_bindings.md), and
[direct pixel-segment selectors](evidence/us_direct_segment_texture_bindings.md), and
[attachment texture and UV updates](evidence/us_attachment_uv_updates.md), and
[constructor tables and cohort diagnosis](evidence/us_model_constructor_tables.md), and
[partial texture-memory loads](evidence/us_partial_tmem_loads.md), and
[remaining material evidence](evidence/us_model_material_frontier.md).

### Current validation

- All four model banks pass byte-identical reconstruction.
- The current validation has **5,424 passed file entries** and **905 render cases**:
  **897 passed; eight remain incomplete**.
- Six runtime-draw cases and one submitted-composition case pass as separate
  comparison evidence.
- ROM-only source audits and packed Blender/Khronos checks support gallery
  publication. File entries include multiple exports of a model; they are not
  additional model identities.
- **Eight focused texture-memory replay tests** cover CI8 partial loads,
  RGBA32 bank separation, RGBA8 alpha, byte ownership and rejection of
  unsupported or missing inputs. Reuse their successful evidence until the
  relevant extractor or validation code changes.
- An independent ROM audit verifies all 8,192 pixels in the four recovered
  RGBA8 textures. The four-bank comparison preserves all 1,487 parsed geometry
  records and the exact images of 9,163 previously linked material runs.

The batch still reports incomplete native appearance. Import success and
reproducible preview baselines do not prove original-game lighting, filtering,
part visibility, secondary-pass blending or raster parity.

Current local reports:

- Inventory: `build/assets/models/us-bank-{01,03,04,09}/manifest.json`.
- Validation: `build/assets/models/validation/report.json` and
  `build/assets/models/validation/review.html`.
- Publication: `build/assets/models/inspect/manifest.json`.
- ROM-only and packed-file audits:
  `build/assets/models/reference/expansion-20260910-usage-budget/` and
  `build/assets/models/reference/blocked-batch-20260911/` and
  `build/assets/models/reference/scene-bindings-20260911/` and
  `build/assets/models/reference/attachment-bindings-20260912/` and
  `build/assets/models/reference/ci4-array-bindings-20260912/` and
  `build/assets/models/reference/material-cohort-20260912/` and
  `build/assets/models/reference/callback-cohort-20260912/` and
  `build/assets/models/reference/runtime-bindings-20260912/` and
  `build/assets/models/reference/timer-model-20260912/` and
  `build/assets/models/reference/attachment80-20260913/` and
  `build/assets/models/batch/rgba8-replay/`.
- Focused tests: `build/assets/models/reference/timer-model-20260912/test-proof.json`.

The [batch validation guide](evidence/us_model_batch_validation.md) documents
cache fingerprints, comparison boundaries and reproduction.
`./conker model-assets coverage` reports geometry, materials, runtime state,
scene association and naming separately. Its results depend on the selected
corpus and supplied evidence; regenerate it before quoting a material backlog,
and use the batch report for current per-file validation.

### Resumable batch workflow

`./conker model-assets batch` writes a compact blocker report and review queue.
`./conker model-assets batch --run` runs tests, verifies and refreshes the four
banks across the configured corpora, then validates and refreshes approved
inspection entries. Successful export steps resume only when their inputs and
outputs match. Changed visual-review inputs and decoder changes reopen the
corresponding deferred work. New render exceptions stop publication for review.
Run tests when extractor or validation code changes; reuse successful test
evidence for export-only batches. Check the affected sources, previews and final
packed files without repeating unchanged, already-passed checks.

`./conker model-assets batch --constructors --bank 09` resumes bounded argument
and initial ROM-table analysis in the same journal. It records candidate calls
and unsupported paths without granting renderer evidence. Validation reuses
unchanged dependencies and hashes shared files once per phase, including an
independent final stability check. Unrelated ASM automation edits do not
invalidate model export evidence; unchanged Python suite results are reusable.
Regression-image comparisons also resume from image and comparison-code hashes;
changed inputs and missing difference images are checked again.

See [resumable model batches](model-batches.md) for bank selection, deferrals,
logs and the boundary between automated checks and visual approval. The current
triage report is `build/assets/models/batch/report.json`; review decisions live
in `config/model-batch-reviews.json`.

Triage verifies each scene assembly set once per read phase and repeats the
verification independently before returning the report. Each report needs two
whole-set checks regardless of the number of published assemblies; component,
selection and output changes still fail the final check.

### Next model work

1. Resolve the **26 material-blocked records** using ROM consumer evidence.
   The constructor diagnosis identifies **seven bank-09 models with consistent
   texture decoding but missing renderer proof**. Follow their shared helpers,
   callback state and descriptor/placement paths as a group (entry 213 and
   entries 407–412). The bounded constant/table pass has no submission candidate
   for these seven; the bounded reverse-reference pass also found no sufficient
   consumer. Investigate unresolved indirect or runtime-selected consumers
   instead of repeating the unchanged scan. The indirect switch in `151D3480`
   resolves to selectors 52, 77, 87, 88 and 12, not the seven target models;
   the 26 saved object caches also contain none of their selectors. A bounded
   live trace reaches nearby selectors 168–171 and one constructor/reference
   write, but none of the targets. Obtain a gameplay trigger or fresh capture
   that constructs selector 13 or 162–167, then follow its callback state to
   submission with `config/model-trace-object-selectors.json`. The five short RGBA16 records
   request 4,096 bytes from 2,560-byte assets; four are exact copies of one
   surface. Their reviewed loaders do not convert the texture or repair the
   load commands. Reopen them only with a concrete conversion, command rewrite
   or complete ROM-backed source-span proof, not a permissive decoder change.
   See [the current material frontier](evidence/us_model_material_frontier.md).
   Three I8 models
   have proven renderers but request 368 bytes from 352-byte payloads; establish
   the complete load source before changing the decoder. Entry 203 still needs
   combiner and inherited-state evidence. The wider runtime-segment group has
   four records: scene `04:0059:23` and bank-09 attachments 47, 165 and 185.
   The [animation-event lookup](evidence/us_attachment_animation_events.md)
   identifies parent/action references for 45 attachments. It establishes
   attachment 47's SHC Soldier parent: animation 24 creates action 74, and
   animation 25 removes it. Its last eight faces need inherited segments 6/7;
   the parent's default 40 x 40 eyes do not match their 32 x 32 layout.
   Normal blink states and both stored expressions also select 40 x 40 images;
   none supplies the attachment layout. All 26 saved attachment lists lack entry
   47. Obtain a fresh animation-24 submission to resolve segment lifetime and
   effective TLUT state. The attachment trace covers both ordinary and alternate
   per-parent submission writes; the new alternate hook still needs a positive
   live capture.
   Attachments 165 and 185 have no references in this event protocol.
   Keep caller-selected variants explicit instead of inventing a default.
2. Resolve the four unpublished drawable bank-01 records. Entry `0066` has
   white helmet/body/pack surfaces despite selecting the proven stationary
   renderer descriptor; investigate part visibility and colour state. Entries
   `0154`, `0155` and `0162` have 570 textured faces using zero-alpha CI4
   palettes. The [ROM alpha audit](evidence/us_character_alpha_frontier.md)
   proves opacity-dependent segment-8 selection: the full-opacity ordinary
   path replaces combiner alpha with coverage, while the blending path does
   not. Actual caller opacity, draw mode, part masks and colour state remain
   unresolved. All three have concrete bank-0E spawn records in **scene 60**:
   one each for 154/162 and seven for 155. All nine records have byte `+2 = 1`,
   so the ordinary spawn routine skips them before distance checks. ROM script
   **`[6,60,7]`** has type-2 descriptors selecting both 154 and 162; follow its
   natural activation through `1501D348`, then capture submitted draws using
   the existing character trace. Scripts 8–12 also select 162, and script 14
   selects 154. None of scene 60's 16 populated scripts selects the seven 155
   records through the reviewed initial type-2 route; later commands and its
   player-selection route remain open. Five supplied scene-60 states contain
   the exact spawn records but no active target actors or loaded primary tables;
   slot 0 is inactive with no pending script. Recover the gameplay event that
   requests script 7 before tracing: scene 60 lists bank-14 event programs
   169–173, while its 120 bank-0C trigger records contain no direct script-start
   class. Event-interpreter control flow remains the lead; do not repeat the
   unchanged trigger or literal scans. The 26-state draw corpus
   contains none of these IDs; do not replay it unchanged. The ordinary wrapper's mode-4 opacity
   is capped at 254 and selects the blending table, while other modes still
   depend on live actor state. Do not repeat the palette scan or force opacity.
   Their 25 texture-independent colour faces
   already do not count as missing textures and still need colour/K5 evidence.
3. Assemble and identify the **594 reviewed fragments and variants** through
   scene placements and effect consumers. The 29 scene assemblies already
   expose 169 of these components in context. Extend the same explicit selection
   process to remaining material-complete bundles. Review dynamic object
   placement and conditional visibility before adding omitted components or
   reopening held scenes. Check overlapping variants and effect planes before
   publication. Promote a standalone fragment only when that context makes it
   useful to inspect; avoid duplicate gallery entries.
4. Extend independent native comparisons for published characters and objects:
   vertex-load lighting, projection, dynamic materials, attachment state,
   secondary passes and distance-dependent filtering remain separate gates.
   The published `0024 / 02` scene has a proven intensity-alpha correction,
   but its overall scene appearance remains unresolved.
5. Strengthen names and scene associations from runtime consumers. Keep
   descriptive and reference-based labels distinct from proven source semantics.
6. For each accepted group, regenerate affected previews, validate sources and
   final packed files, then update the inspection gallery and this roadmap.
   Preserve unrelated exports and record unresolved appearance issues.

Use the repository interface from the root:

```sh
./conker model-assets verify --bank 01
./conker model-assets verify --bank 03
./conker model-assets verify --bank 04
./conker model-assets verify --bank 09
./conker model-assets constructors --bank 09
./conker model-assets preview --bank 01 --rom-defaults \
  --output build/assets/models/rom-only/us-bank-01-preview --force
./conker model-assets validate
./conker model-assets inspect
```

The preview command above regenerates the ROM-only character corpus; refresh
other affected bank previews through their corresponding supported commands.
Captured comparison corpora remain separate.

## Animation and rigs

- [x] Extract 3,518 joints across all 183 bank-01 containers, with rigid
  vertex-load matrix ownership and neutral bind hierarchies.
- [x] Preserve all 145 bank-02 companions and export all 2,621 nonempty skeletal
  clips: 57,732 frames with rotation, scale, root motion and masked joint
  translation. The proven runtime clock is 30 Hz.
- [x] Decode 3,021 bank `0x0F` logical animation records and all five character-state
  duration overrides.
- [x] Extract 23 stored bank `0x13` position morph endpoints for Conker and
  Fire Imp as ROM-default glTF shape keys, with neutral default weights.
- [x] Preserve 258 bank `0x11` expression presets across 22 default bundles,
  including their selector, morph, duration and action-program data.
- [ ] Resolve runtime expression triggers, caller duration overrides and action
  program semantics without inventing authored timelines.
- [ ] Verify intermediate morph behavior. Stored endpoints are exact; glTF's
  floating-point interpolation does not reproduce native integer truncation.
- [ ] Trace lip-sync and mouth cues and connect them to speech assets.
- [ ] Extend proven vertex-colour animation support.

See [morph and expression evidence](evidence/us_character_morph_targets.md).

## Levels, scenes and collision

- [x] Decode position, YZX Euler rotation and scale for the two proven
  `0x44`-byte placement sources. Assemble 48 bank `0x0C` scene previews.
- [x] Resolve 716 bank `0x0B` dispatched placements across 52 available scene
  previews. Eleven placement references in scenes 17 and 62 remain unresolved
  because their bank-04 bundles are absent.
- [x] Associate 785 model identities with scenes through verified loader slots
  and 1,227 resolved placements. Scene association does not prove a complete
  assembled or runtime-observed room.
- [x] Export 96 static-terrain collision meshes, retaining 98,479 triangle
  records and 97,071 byte-identical primary surface words. Preserve source
  zero-area records in the binary inventories.
- [x] Assemble 1,055 included transformed collision placements across 98 scene
  files. Record 172 runtime-flag exclusions and eleven unresolved placements.
- [ ] Recover complete room/level graphs, conditional render paths, portals,
  lights, fog, cameras, triggers and scene display-list relationships.
- [ ] Extend scene-selected and renderer-generated segment-8 evidence without
  assigning unobserved state globally.
- [ ] Prove surface metadata meanings, including physical and audio behavior,
  independently of visual materials.

See [scene consumers](evidence/us_model_scene_consumers.md).

## Audio beyond MP3

- [x] Identify indexed bank `0x17` entries 0–3 as the `B1` sound-bank control,
  external sound data, wavetable and `S1` compact-sequence bank.
- [x] Parse the Conker-extended `B1` graph: instruments, percussion, sounds,
  envelopes, key maps, wavetables, ADPCM books and loops.
- [x] Extract and byte-verify all 149 compact sequences while preserving their
  companion payloads. Export deterministic single-pass MIDI previews with
  scheduled releases and Conker loop payloads retained as sequencer events.
- [x] Split the 21,705,520-byte wavetable using sound-bank references. Export
  source-linked mono PCM16 WAV previews and check decoded loops against B1 state.
  The US bank contains no RAW16 samples.
- [x] Extract timing for every MP3-embedded `L:` cue while preserving its six
  unproven payload bytes without assigning speaker semantics.
- [ ] Prove a byte-identical ADPCM encoder before accepting WAV edits.
- [ ] Provide editable compact sequences with Conker loop extensions and
  byte-identical reconstruction.
- [ ] Correlate sound, instrument and sequence IDs with runtime callers and beta
  fingerprints before assigning names.
- [ ] Add indexed-bank insertion only after flags, alignment, recompression and
  unchanged-ROM behavior are proven.

## Dialogue, cutscenes and interface

- [x] Extract the code-backed HUD/menu layout-node schema, glyph map, 92 sprite
  selectors, their 159-resource spans and renderer-derived selector previews.
  Preserve selector-26 animation separately from its texture payloads.
- [ ] Prove remaining runtime-dependent texture and palette interpretations.
- [ ] Correlate HUD icons, controller symbols and layout nodes with runtime uses.
- [ ] Find string/localization tables, subtitle text, speaker IDs, timing and
  MP3-to-dialogue mappings.
- [ ] Extract cutscene scripts, camera tracks, event timelines and lip-sync
  references.

## Effects and recorded data

- [x] Extract and byte-verify the eleven proven bank-09 effect model containers,
  included in the 462 bank-09 model records above.
- [x] Extract 1,963 skeletal particle-emission points across twenty non-mesh
  records, reconstructing 31,408 bytes. These are excluded from model and gallery
  counts; bank-09 entry 447 remains unclassified.
- [ ] Resolve complete emitter behavior, texture sequences, material animation,
  decals, debris, water, fire and their model/audio references.
- [ ] Identify attract-mode or replay controller streams and other recorded
  demo data.
- [ ] Separate data-driven progression/configuration tables from executable
  code and preserve their original binary representation.

See [effect meshes and emission points](evidence/us_bank09_effect_models.md).
