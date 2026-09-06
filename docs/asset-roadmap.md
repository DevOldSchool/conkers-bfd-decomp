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
- [ ] Model semantics: resolve companion regions, names, complete runtime
  materials, unresolved character auxiliary regions, and compressed animation
  channels.

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
| `01` | Rigged character containers | 183 | 56,412 | 62,073 | 67,804 | 183 glTF skins and 3,518 joints; entry `0000` has a decoded Conker pose |
| `03` | Direct object models | 77 | 5,062 | 3,894 | 4,945 | 48 assembled bank-12 scenes with 511 placements; 25 material runs linked |
| `04` | Segmented level/model bundles | 765 | 209,274 | 147,723 | 204,493 | 1,346 material runs and 36,800 faces linked to 442 proven PNGs |
| `09` | Direct-model-compatible subset | 6 | 254 | 256 | 254 | Geometry and UVs exported; runtime materials remain unlinked |
| **Total** |  | **1,031** | **271,002** | **213,946** | **277,496** | **All generated glTF files pass structural verification** |

Completed model work:

- [x] Preserve every proven container and auxiliary region byte-for-byte rather
  than discarding zero-face records or unresolved companion data.
- [x] Decode primary model display lists, vertex loads, standard and packed
  triangle commands, material-state runs, UV transforms, and runtime segment
  references.
- [x] Export OBJ/MTL interchange files and glTF previews with N64 vertex colors,
  proven UVs, per-material repeat/mirror/clamp sampler state, and only texture
  bindings supported by extractor evidence.
- [x] Export all bank-01 character hierarchies with rigid display-matrix
  assignments and validate all 183 glTF files through Blender 5.2.1.
- [x] Prove all 1,772 bank-01 texture descriptor records through
  `func_1503DC3C`, including their flat texture indices and stored dimensions;
  every display-list flat texture reference occurs in its model's table.
- [x] Recognize the character display lists' RGBA16 transfer-image plus
  same-index TLUT pattern as effective CI4/CI8 state and retain the exact pixel
  and palette load commands in the model manifest.
- [x] Identify the highest-detail Conker model as bank `01`, entry `0000`, and
  apply the first pose decoded from bank `02`, entry `0000`, pair `0006`.
- [x] Decode the two proven `0x44`-byte placement sources and assemble bank-03
  objects with runtime position, YZX Euler rotation, and scale.

Remaining model work:

- [ ] Decode complete bank-02 animation timelines and export glTF animation
  channels instead of applying only Conker's selected first pose.
- [ ] Resolve the preserved bank-01 auxiliary and tail regions from an actual
  runtime consumer before assigning skinning, attachment, morph, facial, or
  colour-animation semantics to them.
- [ ] Recover character-material texture sources and the RDP
  primitive/environment-color state required for faithful bank-01 materials.
- [ ] Resolve scene-selected and renderer-generated segment-8 state from
  reproducible runtime traces; do not assign those references statically.
- [ ] Correlate numeric model IDs with runtime callers before assigning semantic
  character, prop, level, or variant names beyond the verified Conker preview.
- [ ] Recover the remaining level/room scene graph and collision consumers; these
  are related to models but are not standalone model-container extraction.

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
- [x] Decode and apply the first pose from bank-02 entry `0000`, pair `0006`,
  to the highest-detail Conker glTF preview.
- [ ] Decode skeletal clip channels and trace the unresolved character auxiliary
  regions before assigning attachment, blended-skin, morph, or facial semantics.
- [ ] Trace lip-sync or mouth-cue data and connect it to speech assets.
- [ ] Preserve and extend the already proven vertex-colour animation records.

## Levels, scenes, and collision

- [x] Extract the two runtime `0x44`-byte object-record sources, prove position,
  YZX Euler rotation and scale, and assemble 48 direct bank-12 scene previews.
- [ ] Recover the remaining level/room graphs, bank-11 dispatched placements,
  portals, lights, fog, cameras, triggers, and scene display lists.
- [ ] Resolve renderer-provided segment-8 display lists from reproducible
  runtime states rather than forcing them into standalone models.
- [ ] Extract collision geometry and its 12-byte surface records.
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
