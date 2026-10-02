# Asset extraction roadmap

Current US roadmap. Model inventory and validation checked **2 October 2026**.
This tracks what is supported and what remains to do; detailed byte and consumer
evidence lives in the linked documents. For the integrated material presets,
consumer proofs and diagnostic commands, see [model appearance extraction](model-appearance.md).
The counts below describe this dated local validation checkpoint. Regenerate
coverage and batch reports after source or extraction inputs change.

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

| Bank | Proven model family | Extracted records | Curated standalone entries | Other source records |
| --- | --- | ---: | ---: | ---: |
| `01` | Rigged characters and animated props | 183 | 177 | 6 |
| `03` | Direct object models | 77 | 68 | 9 |
| `04` | Segmented level/model bundles | 765 | 342 | 423 |
| `09` | Direct, relative-address, attachment and effect models | 462 | 288 | 174 |
| **Total** | | **1,487** | **875** | **612** |

Three separate [embedded effect primitives](evidence/us_embedded_effect_geometry.md)
come from game data outside the indexed banks. Address `0x8008D538` supplies
four vertices and three triangles to type 6; `0x8008CD90` supplies six vertices
and four triangles shared by types 8, 9, 12 and 89. Type 13 uses a separate
six-vertex, four-triangle primitive at `0x8008B3E0`.
`./conker model-assets embedded-geometry` exports type 6; add
`--primitive type08` or `--primitive type13` for the other primitives. All preserve source bytes and
produce verified diagnostic glTF/GLB files without changing indexed totals.
Type 6 now has a [selected elapsed-zero GLB inspection](evidence/us_embedded_type06_material_inspection.md)
with its proven untextured translucent setup and original vertex alpha. It adds
one parts/effects card and one download. Type 8 still needs its complete texture
and UV contract. Type 13 now also has a
[selected counter-5 Blender inspection](evidence/us_embedded_type13_material_inspection.md)
with a source-proven I8 texture, cached coordinates and raw-byte RGB/alpha.
It adds one parts/effects card and one download. Native timing, placement,
instance transforms and raster appearance remain unresolved; these primitives
do not establish complete runtime effects.

Five further [type-55/85 source variants](evidence/us_embedded_type55_geometry.md)
are now exported and verified: three distinct shapes, with two pairs retaining
different stored colours (24 vertices and 28 triangles across the five lists).
Use `--primitive type55-0` through `--primitive type55-4`. They remain geometry
diagnostics: native lighting/materials and selector activation are unresolved,
so they add no gallery cards or indexed records. All ten glTF/GLB files pass
Khronos validation and Blender import checks; the previous 16 primitive files
remain byte-identical.

All 612 remaining source records retain their review evidence and exports. Of these,
221 are represented in approved scene assemblies, 22 share an identical exported
presentation with a curated model, and 369 have individual cards in
**Extracted review**. Their source review status is:

| Review status | Records | Next action |
| --- | ---: | --- |
| Material blocked | 22 | Prove missing texture bindings, layouts or render state |
| Appearance blocked | 1 | Verify the imp's native texture-generation state and animated joint behavior |
| Reviewed fragments and variants | 587 | Identify useful standalone exports and inspect variants in scene or effect context |
| No drawable faces | 2 | Preserve source records for completeness |

Material-complete deferrals remain eligible for further standalone review. Missing
combiner state is classified as unresolved, even when texture use is unknown.
The **610 drawable review records** are not a count of missing characters or a
requirement to display every fragment. Published models can still need
appearance fixes. The separate curated frontier contains three models with
**43 faces lacking resolved textures**: Haybot (24), bank-09 entry 183 (13),
and bank-09 entry 167 (six). Haybot's existing card now provides a
[selected-phase Blender inspection](evidence/us_haybot_selected_phase_inspection.md)
that supplies those 24 faces from the proven descriptor15 image while preserving
1,225 faces, 45 joints and 15 Actions. Its original ROM-default GLB retains the
missing initial-descriptor material; the new download explicitly selects the
post-update phase, stored SHADE and initialized opacity/color values. Those
states have not been captured concurrently in a native draw.
A smaller review queue does not count all remaining
material or native-appearance defects. The narrower combiner audit keeps the
raw bank-04 scene exports unchanged. Scene 49 already exports opaque; scene 55
now has a separate supported Blender representation with independently sampled
texture layers, selected ROM-initial zero scroll and stored vertex RGBA. Scene 53
still needs per-view primitive/environment colors and remains held. See the
[precise appearance limits](evidence/us_static_scene_assemblies.md#curated-combiner-limits-scenes-49-53-and-55).

The gallery at `build/assets/models/inspect/index.html` contains **1,273 cards**:
**904 curated cards** and **369 extracted review cards**, split into
**106 characters, ten collectables, 601 scene items and 187 parts/effects**
plus the extracted review tab. The existing bank-01 entry-66 review card now
offers an [animated Blender inspection](evidence/us_character66_animated_texgen.md)
with view-dependent coordinates for its 103 affected faces and all three original
imported Actions. Its raw GLB and original animation source remain preserved.
The joint-coordinate proof covers 294 pose/view samples; Blender's between-key
quaternion interpolation approximation and native gameplay state remain explicit
limits, so its appearance-blocked status and review counts are unchanged.
Scene 55's existing assembly card offers the
[independent texture-plane inspection](evidence/us_scene55_dual_texture_inspection.md),
restoring both samples on 84 faces without changing geometry or source RGBA.
Each of these cards has one visible download. The additional type-13 effect
card retains its raw GLB but links only its selected-state Blend. Adding it
preserved all 1,531 existing records and all 3,062 published model, preview
and Blend files byte-for-byte. Desktop/mobile checks cover all three Blend
downloads and their original-name aliases; two empty records still have no preview.
Haybot publication subsequently preserved all 1,532 raw GLBs and 3,064 unrelated
published files, changed only its preview, and added its single Blend download.
Its desktop/mobile source-name and download-name searches resolve to that same
card. The subsequent type-6 publication preserves all 1,532 existing records
and 3,066 published files, adding only its raw source GLB, selected translucent
GLB and preview. Desktop/mobile checks verify one download and both source-name
and download-name searches. After integration with current main, all 855 model tests pass.
Scenes 1, 4, 7, 10, 16, 19, 38, 39, 48, 55, 56, 58, 61, 64 and 66 each
offer their assembly as one card and one download; sixteen standalone component
cards are replaced. The export manifest retains **921 curated exports**: all
875 indexed standalone source exports, 44 static assemblies and two embedded
primitives for validation and triage.
The recovered attachment cash variant shares the existing cash card: its stored mesh, rig and texture images match, while its distinct alpha mode remains in the export manifest. Thus 17 curated source cards are replaced or consolidated overall.
The assemblies represent **221 otherwise deferred
components** in scene context, whose separate review cards are consolidated;
they do not increase the extracted source-record inventory. Three scene-64
components (5/6/7) were already consolidated through equivalence to scene-58
parts and now use assembly representation. Thus the last 18 represented
components reduce visible review by 15, from 388 to 373, without making any
source newly visible. Open the self-contained GLBs in Blender using
Material Preview. Animation-free `*-bind.gltf` sources remain available for
geometry diagnostics.

**Extracted review** shows the remaining exports with status and bank filters,
current cached thumbnails and downloadable GLBs or the scoped entry-66 Blender
inspection. Two records with no drawable
faces have explicit placeholder cards. Material and appearance blockers remain
labelled, and inclusion here does not change their acceptance state. Consolidation
requires exact component identity, path, dependency fingerprint and ROM provenance;
blocked, stale and excluded components remain visible. Source IDs and old review
filenames remain searchable on the containing assembly or equivalent model.
Presentation equivalence requires a current fingerprint-bound decision plus fresh
comparison of all standard glTF fields and exact buffer/image bytes, ignoring only
asset metadata, names and diagnostic extras. It does not equate runtime roles. Review files live under `inspect/review/` and `previews/review/`; the manifest keeps
`review_models` separate from the curated `models` list.

Four additional bank-09 sources now pass material review using the recovery branch's exact guarded helpers: cash variant 165, Conker HUD head 185, particle polyhedron 203 and tapered spike 213. The head has 112 texture-sampling faces and 58 colour-only faces; those 58 do not request a missing texture. Its runtime HUD deformation remains outside the stored-geometry preview. All three corpora gain 69 textured faces with unchanged geometry, UVs and joints; only these four model records change.

Current [standalone review selections](evidence/us_model_review_selections.md)
include coherent props, explicit barrier variants, a chair, terrain/room
segments, a corner cobweb and four newly selected parts/effects. The latter are
a green/yellow starburst and three distinct lower-leg pieces; their descriptive
labels do not establish actor identity or native effect behavior. The review notes identify **31 records with the same exported glTF
presentation** as a curated entry and distinguish other similar props from
proven matching exports. Runtime roles remain separate questions.

Scenes **0–2, 4, 6, 7, 10–12, 14, 16, 19, 23, 25–28, 30, 35, 36, 38–41,
44–56, 58, 61 and 64–68** combine 473 distinct ROM models in 787 instances using recovered loader slots
and placement records.
They include lava chambers, walkways, industrial shafts, a tiled room and a
mossy chamber. Scenes 38, 39 and 66 add circular chambers, a honeycomb ramp
and shallow mossy passages; they retain primary and secondary surfaces with
native blending and visibility still unresolved. Deferred source notes link
back to their assembled scene context.
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
Scene 10's prior hold is resolved by omitting the initially inactive singleton
prop below the floor through the verified candidate-list route. Candidate 20
remains held for detached elevated arch pieces requiring placement or
conditional visibility evidence.
Scene 16 adds the circular machinery chamber, retaining adjoining door parts
and omitting inactive machinery and a broad water alternative. Scene 19 adds
the stone basin, channels and raised paths, preserving adjoining cap pieces and
blended water while omitting a detached dish and origin-positioned props. Scene 4
adds the fortified beach and surf, retaining all selected water passes and tint
while omitting detached water, an origin-positioned component and inactive debris.
Their 23 newly represented deferred components remain separate ROM source records.
Scenes 1, 56, 58 and 64 add a timber-framed interior, a dark stone chamber, an
industrial corridor and an orange-panelled chamber. Their 45 instances represent
another 16 deferred components. Initial inactive singleton groups are explicitly
omitted, supported by the candidate-list consumer rather than placement bytes
alone; the original roof geometry, tint, culling and material bytes are retained.
Scene 10 adds the metal chamber with pipes and stairs: eight sources in ten
instances, with two further deferred components represented. Its exported
triangles remain intact; the 14-polygon Blender difference is repeated source
indices, not an assembly omission.
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
- [x] Reuse the reviewed UI constructor-material implementation verbatim from
  recovery commit `4f80ae55eeb322a170837319257ed0ab9da58c97`. Bank-09 entries
  162 and 164 recover 49 ROM-only texture-linked faces across four runs, including
  the cash bundle eyes. This integrates existing recovery work, not a new
  discovery. Geometry, UV and joint buffers remain unchanged, captured material
  precedence remains intact, and initial blink state is explicit. Native UI
  opacity, animation, transforms and raster parity remain unresolved. See
  [the reused consumer evidence](evidence/us_ui_constructor_materials.md).
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

### Validation evidence

- All four model banks pass byte-identical reconstruction.
- The completed final 44-assembly validation has **5,450 passed file entries**
  and **975 render cases**: **967 passed; eight remain incomplete**. The earlier
  43-assembly checkpoint (5,449 files; 965 passed renders plus eight incomplete)
  was validated but not separately published.
- The full Python suite has **1,194 tests**: **1,181 passed, 11 skipped and two
  known macOS baseline failures**. Those failures are retained explicitly; this
  is not a claim that the suite is entirely green.
- Fresh ROM/source reproduction, image preservation, packed Khronos validation
  and front/rear review pass for the newly accepted scenes and standalone
  selections. The UI preservation audit reproduces 49 newly linked ROM-only
  faces and keeps the geometry, UV and joint buffers unchanged.
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

1. Resolve the **22 material-blocked records** using ROM consumer evidence.
   Static red flag `03:0090:00` has a specific CI8 load/palette conflict with
   its 160-byte flat-1637 payload. The correctly textured rigged flag is a
   comparison source, not permission to replace those commands. Follow the
   [scene-48 capture target](evidence/us_static_flag_texture_conflict.md) to prove
   the submitted load state before changing that export.
   The constructor diagnosis identifies **six remaining bank-09 models with
   consistent texture decoding but missing renderer proof** (entries 407–412).
   Entry 213 is now resolved through its stored script selector 13. Follow the
   remaining shared helpers, callback state and descriptor/placement paths.
   The bounded constant/table and reverse-reference passes found no sufficient
   submission consumer for these six. Investigate unresolved indirect or runtime-selected consumers
   instead of repeating the unchanged scan. The indirect switch in `151D3480`
   resolves to selectors 52, 77, 87, 88 and 12, not the six remaining target models;
   the 26 saved object caches also contain none of their selectors. A bounded
   live trace reaches nearby selectors 168–171 and one constructor/reference
   write, but none of the targets. Obtain a gameplay trigger or fresh capture
   that constructs selectors 162–167, then follow its callback state to
   submission with `config/model-trace-object-selectors.json`. The five short RGBA16 records
   request 4,096 bytes from 2,560-byte assets; four are exact copies of one
   surface. Their reviewed loaders do not convert the texture or repair the
   load commands. Reopen them only with a concrete conversion, command rewrite
   or complete ROM-backed source-span proof, not a permissive decoder change.
   See [the current material frontier](evidence/us_model_material_frontier.md).
   Bank-09 entry 62 needs an actual run-2 submission proving the segment-8
   render-state table at offset `0x50`, effective OtherMode/combiner, flat-3436
   palette and primitive/environment/SHADE alpha before its two faces can be
   linked. Entry 161 loads flat 1558 as 16 x 16 RGBA32 and stores
   `EF082C3F 005049D8`, but its eight faces inherit a missing FC combiner.
   Reopen it only with the actual consumer's submitted combiner and required
   constant state, or a proven copied-list rewrite; image bytes alone do not
   determine its material. These are specific capture or caller-contract gaps.
   Three I8 models
   have proven renderers but request 368 bytes from 352-byte payloads. The
   [fresh source audit](evidence/us_i8_mipmap_source_gap.md) establishes that the
   missing bytes hold an entire declared fourth mip level; three bank-01 siblings
   use a complete three-level contract. Obtain a submitted load source before
   changing the decoder. Entry 203 now has a guarded source-proven combiner
   binding. The remaining runtime-segment group contains scene `04:0059:23`
   and bank-09 attachment 47; attachments 165 and 185 now use the recovered
   guarded consumer bindings.
   A [bounded scene-59 audit](evidence/us_scene59_and_entry447_frontier.md)
   excludes the existing animation-table rows as a binding for segment 23;
   its preceding runtime segment writes remain required evidence.
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
   Keep caller-selected variants explicit instead of inventing a default.
2. Resolve the four unpublished drawable bank-01 records. Entry `0066` is a
   purple flamethrower imp; it does not select the stationary tank renderer.
   Its white helmet/body/pack surfaces include 103 faces whose source vertices
   use view-dependent `G_TEXTURE_GEN` coordinates. An ignored fixed-view
   diagnostic restores texture detail without changing geometry. The supported
   animated Blender export now preserves its three imported Actions and verifies
   the generated coordinates across 294 pose/view samples. It is available through
   the existing review card. Native lighting/linear-mode state and Blender's
   between-key quaternion interpolation remain separate limits. Entries
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
3. Assemble and identify the **587 reviewed fragments and variants** through
   scene placements and effect consumers. The 44 scene assemblies already
   expose 221 of these components in context; after 22 separately consolidated
   presentation-equivalent records, 344 deferred records still have individual review cards. Extend the same explicit selection
   process to remaining material-complete bundles. Review dynamic object
   placement and conditional visibility before adding omitted components or
   reopening held scenes. Check overlapping variants and effect planes before
   publication. Promote a standalone fragment only when that context makes it
   useful to inspect; avoid duplicate gallery entries. The systematic bank-04
   audit pins 38 slot-3 sources to collision input in the reviewed consumer graph;
   it does not establish that no indirect renderer exists. Scene-54 indicator
   models 14–20 form a same-placement state-set lead, not seven simultaneous
   props or a recovered animation timeline. The bounded remaining-scene frontier
   accounts for all 25 unselected entries; scene 29 still needs state evidence for
   85 coincident faces with different materials, and omitting scene 63's inactive
   placements leaves only its already curated base.
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
- [x] Extract 14 ordered vertex-colour target tables from five scene models,
  preserving all 302 source indices, target RGB and original RGBA references.
  Export the exact bounded integer interpolation rule and eleven conditional
  controller links with `./conker model-assets vertex-color-targets`; see
  [source evidence](evidence/us_scene_vertex_color_targets.md).
- [ ] Resolve vertex-colour activation, runtime base snapshots and timing.

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
  counts; bank-09 entry 447 remains unclassified. Its
  [bounded source audit](evidence/us_scene59_and_entry447_frontier.md#bank-09-entry-447)
  finds point-like syntax but no proven consumer.
- [x] Extract attachment 80's two ROM texture alternatives and conditional UV
  controller, with 101 exact float32 tile-origin samples. Use
  `./conker model-assets attachment-controller`; the existing gallery preset
  stays unchanged. See [controller evidence](evidence/us_attachment80_controller.md).
- [x] Export complete object/scene texture frame sets: 41 images, eight arrays
  and 59 material-run links across 37 models. Native selector semantics and
  correlated scene bindings remain explicit; no playback clock is assumed.
  Use `./conker model-assets texture-sequences`; see
  [sequence export evidence](evidence/us_model_texture_sequences.md).
- [ ] Resolve complete emitter behavior, texture sequences, material animation,
  decals, debris, water, fire and their model/audio references.
- [ ] Identify attract-mode or replay controller streams and other recorded
  demo data.
- [ ] Separate data-driven progression/configuration tables from executable
  code and preserve their original binary representation.

See [effect meshes and emission points](evidence/us_bank09_effect_models.md).
