# Asset extraction roadmap

This roadmap records supported capabilities and the remaining US research.
The inventory below is the **2 October 2026 local checkpoint**, not a live
report. Regenerate coverage and batch reports when extraction inputs change.
Format contracts and commands live in [RZIP and asset extraction](rzip-assets.md),
[model appearance extraction](model-appearance.md) and
[resumable model batches](model-batches.md); byte and consumer proofs live in
the linked evidence records.

The goal is reversible extraction directly from the ROM. Save states, native
captures and external models are comparison references, not substitutes for
ROM geometry or textures. Keep generated assets under ignored `build/` paths
and preserve unrelated code-matching work.

## Current asset families

| Family | Supported | Remaining work |
| --- | --- | --- |
| Grayscale RLE fonts | Reversible glyph extraction, verified character mapping, metrics and PNG atlas | Native text effects and interface integration |
| MP3 audio | Reversible streams, decoder tables and embedded cue timing | Dialogue, speaker and event associations |
| Other audio | Sound-bank graph, samples, sequences, WAV and MIDI previews | Reversible editing and runtime names |
| Textures and materials | Proven indexed/direct formats and guarded ROM selectors | Unsupported formulas and runtime-dependent state |
| Model geometry | Four byte-verified indexed families and separate embedded primitives | Useful review selections and consumer-led classification |
| Animation and expressions | Rigs, skeletal clips, stored morph endpoints and expression records | Runtime triggers, expression playback and native interpolation |
| Scenes and collision | Placements, scene previews and collision geometry | Complete rooms, surface semantics and environmental state |
| Effects | Proven meshes and skeletal emission points | Emitters, material animation and effect associations |

## Models: inventory and inspection

At the checkpoint, all **7,121,632 decoded model bytes** reconstruct against the
US ROM. The **1,487 indexed records** contain **232,162 source faces**; 1,485
records have drawable geometry.

| Bank | Proven model family | Extracted records | Curated standalone entries | Other source records |
| --- | --- | ---: | ---: | ---: |
| `01` | Rigged characters and animated props | 183 | 177 | 6 |
| `03` | Direct object models | 77 | 68 | 9 |
| `04` | Segmented level/model bundles | 765 | 342 | 423 |
| `09` | Direct, relative-address, attachment and effect models | 462 | 288 | 174 |
| **Total** | | **1,487** | **875** | **612** |

The 612 other source records retain their exports and review evidence:

| Review status | Records | Next action |
| --- | ---: | --- |
| Material blocked | 22 | Prove missing texture bindings, layouts or render state |
| Appearance blocked | 1 | Complete the imp's native texture-generation and animation evidence |
| Reviewed fragments and variants | 587 | Inspect useful standalone or scene/effect representations |
| No drawable faces | 2 | Preserve the source records |

Of these records, 221 are represented in approved assemblies, 22 have exact
exported-presentation equivalence to curated models, and 369 retain individual
**Extracted review** cards. Of the 587 deferrals, 344 remain individually visible.
The gallery at `build/assets/models/inspect/index.html` has **1,273 cards**:
904 curated and 369 review cards. Curated categories contain 106 characters,
ten collectables, 601 scene items and 187 parts/effects. The manifest preserves
**921 curated exports**: 875 indexed standalone sources, 44 assemblies and two
embedded primitives. Seventeen curated cards are replaced or consolidated;
source identities and validation records remain distinct.

These are presentation counts, not a count of all appearance defects. The raw
curated frontier still includes 43 unresolved texture faces on Haybot (24),
bank-09 entry 183 (13) and entry 167 (six). Haybot's selected-phase inspection
supplies its 24 faces under an explicit later state; its ROM-default GLB retains
the initial-descriptor gap. Missing combiner state remains unresolved, and a
material-complete record still requires independent visual review.

[Inspection configuration](../config/model-inspection.json) owns categories and
labels; bank, entry and segment remain the ROM identities. The
[standalone review evidence](evidence/us_model_review_selections.md) distinguishes
useful selections, identical exported presentations and descriptive names from
proven runtime identity. The [scene assembly evidence](evidence/us_static_scene_assemblies.md)
and [selection configuration](../config/model-scene-assemblies.json) preserve
all included components and explicit omissions. Their static placements do not
establish simultaneous visibility, animation, lighting or fog.

Supported inspections retain their selected state and limits:

| Inspection | Evidence and remaining boundary |
| --- | --- |
| Character 66 | [Animated texture generation](evidence/us_character66_animated_texgen.md): original Actions and joint-coordinate proof; native state and between-key interpolation remain explicit limits |
| Scene 55 | [Independent texture planes](evidence/us_scene55_dual_texture_inspection.md): both samples and source RGBA; raw assembly GLB preserved |
| Haybot | [Selected phase](evidence/us_haybot_selected_phase_inspection.md): descriptor15 texture, stored SHADE and initialized opacity/colour; not a concurrent native-state claim |
| Embedded type 6 | [Elapsed-zero inspection](evidence/us_embedded_type06_material_inspection.md): proven untextured translucent setup and vertex alpha |
| Embedded type 13 | [Counter-5 inspection](evidence/us_embedded_type13_material_inspection.md): proven I8 texture and cached coordinates |

The [embedded primitive evidence](evidence/us_embedded_effect_geometry.md) covers
types 6, 8/9/12/89 and 13 outside indexed banks. Type 8 still needs its complete
texture/UV contract. Five [type-55/85 variants](evidence/us_embedded_type55_geometry.md)
preserve three shapes and distinct stored colours as geometry diagnostics;
they add no indexed records or gallery cards. Native selector activation,
transforms, timing and raster appearance remain separate work.

```sh
./conker model-assets embedded-geometry
# Other proven primitives: type08, type13, type55-0 through type55-4
./conker model-assets embedded-geometry --primitive type08
```

### Supported model extraction

The exporter preserves container headers, vertices, display lists, auxiliary
regions and empty records for byte-identical reconstruction. Bank 09's indexed
models comprise 296 direct records, 155 attachments and eleven effects.
Primary and selected callable lists retain source face identities, explicit
degeneracy records, load-time matrix ownership, normals, colours, UV transforms,
culling and supported sampler state. OBJ/MTL and glTF remain inspection formats;
unsupported inherited material state is explicit metadata.

| Supported path | Contract and evidence |
| --- | --- |
| ROM character states | [Defaults](evidence/us_rom_character_defaults.md), [draw tables](evidence/us_character_draw_tables.md), [Wise Guys shirts](evidence/us_wise_guys_shirt.md), [Birdy's hay](evidence/us_birdy_hay_material.md); expression/instance/renderer presets stay separately labelled |
| Direct and relative objects | [Placed-object materials](evidence/us_object_material_consensus.md), [bank-09 materials](evidence/us_bank09_object_materials.md), [relative models](evidence/us_bank09_relative_models.md), [effect models](evidence/us_bank09_effect_models.md) |
| Indexed textures | [Odd-width CI4](evidence/us_direct_odd_width_ci4.md), [CI8 wrapping](evidence/us_ci8_tmem_wrapping.md), [detail tiles](evidence/us_detail_indexed_textures.md); native LOD/detail blending is not reproduced by glTF |
| Native colour and intensity | [RGBA16 mipmaps](evidence/us_direct_rgba16_mipmaps.md), [RGBA32 mipmaps](evidence/us_direct_rgba32_mipmaps.md), [I/IA mipmaps and shade alpha](evidence/us_direct_intensity_materials.md), under complete palette/tile/payload bounds |
| Partial texture loads | [Bounded TMEM replay](evidence/us_partial_tmem_loads.md): load destinations, split RGBA32 banks, CI palettes and RGBA8 colour/alpha; every sampled byte needs bounded ROM ownership |
| Object and scene selectors | [Texture animation](evidence/us_object_texture_animation.md), [terrain bindings](evidence/us_scene_texture_bindings.md), [object selectors](evidence/us_object_texture_bindings.md); stored alternatives and chosen inspection phase remain explicit |
| Attachments and callbacks | [Attachment bindings](evidence/us_attachment_texture_bindings.md), [callback bindings](evidence/us_object_callback_texture_bindings.md), [UV updates](evidence/us_attachment_uv_updates.md), [direct pixel segments](evidence/us_direct_segment_texture_bindings.md) |
| Constructors | [Tables and diagnosis](evidence/us_model_constructor_tables.md): selected descriptors, signed callback sentinel, masks and full selector bounds; discovery alone does not prove a renderer |
| UI consumers | [Recovered implementation](evidence/us_ui_constructor_materials.md), originating at `4f80ae55eeb322a170837319257ed0ab9da58c97`; initial state and captured-material precedence remain explicit |
| Submitted parts and poses | [Independent submitted-pose evidence](evidence/us_submitted_model_poses.md); captured diagnostics stay separate from the ROM-only gallery |

Use [model appearance extraction](model-appearance.md) for guarded bank-09
consumer materials, explicit presets and selection/source-face verification.
The evidence links retain exact cohorts and preservation audits, including the
timer's 00:00 preset, attachment frame alternatives and recovered UI sources.
The [special attachment evidence](evidence/us_special_attachment_materials.md)
distinguishes texture-sampling from colour-only faces, which require no texture.
Runtime HUD deformation remains outside the stored-geometry preview.

### Validation evidence

The dated checkpoint reports **5,450 passed file entries** and **975 render
cases: 967 passed, eight incomplete**. The model suite passed 855 tests after
integration.

Byte reconstruction, packed-file checks and reproducible previews do not prove
native lighting, filtering, part visibility, secondary-pass blending or raster
parity. File entries can represent several exports of one model; they are not
additional source identities. Six runtime-draw cases and one submitted-composition
case remain separate comparison evidence. See the
[batch validation guide](evidence/us_model_batch_validation.md) for checks,
fingerprints and reproduction, and the inspection evidence above for scoped
image preservation, Blender/Khronos checks and publication audits.

| Local report | Purpose |
| --- | --- |
| `build/assets/models/us-bank-{01,03,04,09}/manifest.json` | Source inventory |
| `build/assets/models/validation/report.json` and `review.html` | Per-file validation and render outcomes |
| `build/assets/models/inspect/manifest.json` | Published artifacts and source identities |
| `build/assets/models/batch/report.json` | Current triage and review queue |

`./conker model-assets coverage` measures geometry, materials, runtime state,
scene association and naming separately. Regenerate it before quoting a material
backlog, and use the batch report for per-file validation. Its selected corpus
and supplied evidence determine its coverage; see
[coverage semantics](evidence/us_model_coverage.md).

### Resumable batch workflow

```sh
./conker model-assets batch
./conker model-assets batch --run
./conker model-assets batch --constructors --bank 09
```

The first command refreshes triage; `--run` refreshes configured corpora and
approved inspection entries; `--constructors` resumes bounded ROM argument/table
research without granting renderer evidence. Follow
[resumable model batches](model-batches.md) for bank selection, fingerprints,
deferrals, logs, validation and publication. Changed review inputs reopen work;
new render exceptions require review. Reuse unchanged successful test/export
checks, and preserve the independent final source/artifact stability check.

### Next model work

1. Resolve material blockers from specific consumer evidence. The
   [material frontier](evidence/us_model_material_frontier.md) records six
   bank-09 renderer candidates (407–412), short RGBA16 loads and bounded
   negative static/runtime searches. Obtain the missing renderer submission or
   proven command/source-span correction; do not relax payload checks or repeat
   exhausted scans. The [static red flag](evidence/us_static_flag_texture_conflict.md)
   needs submitted CI8 load/palette state, and the
   [I8 mip gap](evidence/us_i8_mipmap_source_gap.md) needs a complete load source.
   Entry 62 needs effective segment-8 offset `0x50`, OtherMode/combiner,
   flat-3436 palette and colour/alpha state; entry 161 needs its actual submitted
   combiner or copied-list rewrite, not just its flat-1558 RGBA32 image.
2. Capture unresolved inherited state. Scene `04:0059:23` requires preceding
   segment writes; follow the [scene-59 audit](evidence/us_scene59_and_entry447_frontier.md).
   Attachment 47 belongs to the SHC Soldier: animation 24 creates action 74 and
   animation 25 removes it. Its last eight faces need inherited segments 6/7
   and effective TLUT state. Default/blink/expression 40x40 eyes do not prove
   its 32x32 layout, and the existing saved attachment lists lack the target.
   Use [attachment animation evidence](evidence/us_attachment_animation_events.md)
   and obtain a positive submission through the ordinary or alternate parent hook.
3. Complete the unpublished character appearance evidence. Entry 66's animated
   inspection retains its native lighting/linear-mode and interpolation limits;
   use its [trace and verification record](evidence/us_character66_animated_texgen.md).
   Entries 154, 155 and 162 need caller opacity, draw mode, part masks and colour
   state. Their zero-alpha palettes and scene-60 spawn/script paths are documented
   in the [alpha frontier](evidence/us_character_alpha_frontier.md) and
   [event activation evidence](evidence/us_model_event_activation.md).
   Do not force opacity or replay the unchanged negative state corpus. The
   ordinary mode-4 wrapper caps opacity at 254; texture-independent colour faces
   require colour/K5 evidence separately.
4. Place and identify useful fragments without multiplying gallery duplicates.
   Extend explicit assembly selections for material-complete bundles, checking
   dynamic placement, conditional visibility, overlapping variants and effect
   planes. The [scene assembly evidence](evidence/us_static_scene_assemblies.md)
   retains held scenes, omissions and the bounded remaining-scene frontier.
   Slot-3 collision ownership is not proof that no indirect renderer exists;
   scene-54 indicators are a state-set lead, and scene 29's coincident faces
   still need state evidence. Promote a standalone fragment only when its
   context makes it useful to inspect.
5. Extend independent native comparisons: vertex-load lighting, projection,
   dynamic materials, attachments, secondary passes and distance-dependent
   filtering remain separate gates. Scene `0024 / 02` has a proven
   intensity-alpha correction, not complete native appearance. Scene 53 still
   needs per-view primitive/environment colours; see the
   [scene combiner limits](evidence/us_static_scene_assemblies.md#curated-combiner-limits-scenes-49-53-and-55).
6. Strengthen names and scene associations from consumers. Distinguish
   descriptive/reference labels from source semantics. For each accepted group,
   regenerate affected previews, verify sources and packed files, and update the
   gallery and dated summary while preserving unrelated exports and open issues.

Use the repository interface from the root for a selected group:

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

Refresh other affected banks through their corresponding preview commands.
Captured comparison corpora remain separate from ROM-only previews.

## Animation and rigs

Supported extraction preserves 3,518 joints across bank 01, all 145 bank-02
companions and 2,621 nonempty clips (57,732 frames) at the proven 30 Hz clock.
Rotation, scale, root motion, masked joint translation, 3,021 logical animation
records and five character-state duration overrides are decoded.
[Morph/expression extraction](evidence/us_character_morph_targets.md) retains
23 stored position endpoints and 258 expression presets across 22 bundles,
including selector, duration and action-program data. Neutral glTF shape-key
weights do not invent playback.

Remaining work: prove expression triggers, caller duration overrides, action
programs, lip-sync and speech associations. Stored morph endpoints are exact;
glTF floating-point interpolation does not reproduce native integer truncation.

`./conker model-assets vertex-color-targets` exports 14 ordered tables from five
scene models, all 302 source indices, target RGB and source RGBA, plus the
bounded integer interpolation rule and eleven conditional controller links.
[Vertex-colour evidence](evidence/us_scene_vertex_color_targets.md) preserves
those contracts; activation, runtime base snapshots and timing remain open.

## Levels, scenes and collision

The two proven `0x44`-byte placement sources supply position, YZX Euler rotation
and scale. Previews cover 48 bank-0C scenes and 716 dispatched bank-0B placements
across 52 scenes; eleven references in scenes 17/62 remain unresolved because
their bank-04 bundles are absent. Loader slots and 1,227 resolved placements
associate 785 model identities with scenes, without proving complete rooms.

Collision extraction preserves 96 static meshes, 98,479 triangle records and
97,071 byte-identical primary surface words, including source degeneracies.
It assembles 1,055 transformed placements into 98 files, with 172 explicit
runtime-flag exclusions and eleven unresolved placements. See the
[scene consumers](evidence/us_model_scene_consumers.md) and
[collision contracts](rzip-assets.md#direct-models-bundles-and-collision).

Remaining work: complete room graphs, portals, conditional render paths,
lights, fog, cameras, triggers and scene display-list relationships. Extend
scene-selected/generated segment-8 evidence without assigning unobserved state
globally. Prove physical and audio surface semantics independently of materials.

## Audio beyond MP3

[Non-MP3 audio evidence](evidence/us_non_mp3_audio_assets.md) establishes bank
`0x17` entries 0–3 as `B1` control, external sound data, wavetable and `S1`
sequences. The extended graph preserves instruments, percussion, sounds,
envelopes, key maps, wavetables, ADPCM books and loops. All 149 compact sequences
round-trip with companion payloads retained; MIDI previews are deterministic
single passes with scheduled releases and Conker loop payloads retained as events.
The 21,705,520-byte wavetable produces source-linked PCM16 WAV previews and
loop checks; the US bank has no RAW16 samples. MP3 `L:` cue timing is extracted
while its six unproven payload bytes remain uninterpreted.

Remaining work: a byte-identical ADPCM encoder, editable compact sequences with
Conker loop extensions, runtime/beta-backed names and indexed-bank insertion.
Insertion requires proven flags, alignment, recompression and unchanged-ROM
behavior; WAV decoding alone does not authorize edited reconstruction.

## Dialogue, cutscenes and interface

The [95-glyph atlas](evidence/us_font_atlas.md) preserves mapping, offsets,
spacing and two shadowed duplicate mappings. [HUD/menu extraction](evidence/us_hud_menu_assets.md)
retains layout-node schema, glyph mapping, 92 sprite selectors and their
159-resource spans; selector-26 animation stays separate from texture payloads.

The interface review records 92 visually named selectors and 97 PNG downloads:
85 selectors match supplied references and seven remain explicitly unmatched.
The two empty runtime slots retain their IDs. Forty additional artwork groups
contain 74 exact raw sources and 52 PNG downloads, including twelve native icon
crops. Eighteen menu/icon groups match 49 US resources, retaining column-major
skull layout and all twelve 16x16 icons. Names do not imply runtime use; the
[reference audit](evidence/us_interface_reference_review.md#full-game-page-coverage-audit)
covers all twelve supplied sheets.

Remaining work: intro graphics, secondary fonts/buttons, story thumbnails,
complete photo compositions and weapon/effect/bee/Haybot artwork. Keep unused
or beta variants separate from retail coverage. Prove runtime texture/palette
interpretations and connect icons, controller symbols and layout nodes to uses.
Recover strings/localization, subtitles, speakers, dialogue timing, MP3 mappings,
cutscene scripts, cameras, event timelines and lip-sync references.

## Effects and recorded data

The eleven [bank-09 effect containers](evidence/us_bank09_effect_models.md) are
included in the indexed inventory. Twenty non-mesh records supply 1,963 skeletal
particle-emission points, reconstructing 31,408 bytes; these do not count as
models or gallery entries. Bank-09 entry 447 remains unclassified: its
[bounded audit](evidence/us_scene59_and_entry447_frontier.md#bank-09-entry-447)
finds point-like syntax without a proven consumer.

`./conker model-assets attachment-controller` preserves attachment 80's two
texture alternatives and conditional UV controller, including 101 exact float32
tile-origin samples; its gallery preset stays unchanged. See
[controller evidence](evidence/us_attachment80_controller.md).
`./conker model-assets texture-sequences` exports 41 images, eight arrays and
59 material-run links across 37 models. [Sequence evidence](evidence/us_model_texture_sequences.md)
retains selector semantics and correlated scene bindings without assuming a
playback clock.

Remaining work: complete emitters, material animation, decals, debris, water,
fire and model/audio associations; identify attract-mode/replay input streams
and other recorded data. Separate progression/configuration tables from code
while preserving their original binary representation.
