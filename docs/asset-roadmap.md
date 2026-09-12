# Asset extraction roadmap

Current US roadmap. Model inventory and validation checked **11 September 2026**.
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

| Bank | Proven model family | Extracted records | In gallery | Outside gallery |
| --- | --- | ---: | ---: | ---: |
| `01` | Rigged characters and animated props | 183 | 177 | 6 |
| `03` | Direct object models | 77 | 66 | 11 |
| `04` | Segmented level/model bundles | 765 | 326 | 439 |
| `09` | Direct, relative-address, attachment and effect models | 462 | 233 | 229 |
| **Total** | | **1,487** | **802** | **685** |

All records outside the gallery are already extracted. Their current status is:

| Unpublished status | Records | Next action |
| --- | ---: | --- |
| Material blocked | 75 | Prove missing texture bindings, layouts or render state |
| Appearance blocked | 1 | Resolve stationary tank part visibility and colour state |
| Reviewed fragments and variants | 607 | Retain as diagnostics; revisit with scene or effect context |
| No drawable faces | 2 | Preserve source records for completeness |

Every currently material-complete candidate has been reviewed. Missing
combiner state is classified as unresolved, even when texture use is unknown.
The **683 unpublished drawable records** are not a count of missing characters or a
requirement to display every fragment. Published models can still need
appearance fixes.

The gallery at `build/assets/models/inspect/index.html` contains only
ROM-derived exports, split into **106 characters, ten collectables, 549 scene
items and 137 parts/effects**. Open its self-contained GLBs in Blender using
Material Preview. Animation-free `*-bind.gltf` sources remain available for
geometry diagnostics.

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
- [x] Resolve the reviewed scene/object texture-animation table through its
  placement updater and renderer. Preserve all stored frame indices and decode
  every frame; show the first stored frame as an explicit inspection preset.
  Current bindings cover water surfaces, waterfalls, animated B-pad sides and
  glowing fragments. Gameplay phase and UV animation remain separate.
- [x] Resolve primary terrain texture selectors for four scenes, preserving
  their frame alternatives, texture type groups and per-segment phase offsets.
  Inspection states remain explicit; current gameplay state is not inferred.
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
[scene texture bindings](evidence/us_scene_texture_bindings.md).

### Current validation

- All four model banks pass byte-identical reconstruction.
- The completed batch has **5,406 passed file entries** and **826 render cases**:
  **818 passed; eight remain incomplete**.
- Six runtime-draw cases and one submitted-composition case pass as separate
  comparison evidence.
- ROM-only source audits and packed Blender/Khronos checks support gallery
  publication. File entries include multiple exports of a model; they are not
  additional model identities.
- **All 788 Python tests pass.**

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
  `build/assets/models/reference/scene-bindings-20260911/`.
- Full Python suite: `build/assets/models/batch/logs/tests.log`.

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

See [resumable model batches](model-batches.md) for bank selection, deferrals,
logs and the boundary between automated checks and visual approval. The current
triage report is `build/assets/models/batch/report.json`; review decisions live
in `config/model-batch-reviews.json`.

### Next model work

1. Resolve the **75 material-blocked records** using ROM consumer evidence.
   The runtime-segment group contains 18 records: three bank-04 object
   segments and fifteen bank-09 object/effect models. Prioritize their
   object/attachment consumers, then the 20 CI4 lookup-state records. Keep
   caller-selected variants explicit instead of inventing a default.
2. Resolve the four unpublished drawable bank-01 records. Entry `0066` has
   white helmet/body/pack surfaces despite selecting the proven stationary
   renderer descriptor; investigate part visibility and colour state. Entries
   `0154`, `0155` and `0162` use zero-alpha CI4 palettes whose effective alpha
   and render modes remain unresolved. Do not force them opaque.
3. Assemble and identify the **607 reviewed fragments and variants** through
   scene placements and effect consumers. Promote a fragment only when that
   context makes it useful to inspect; avoid duplicate gallery entries.
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
