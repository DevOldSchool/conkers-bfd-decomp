# US scene/model consumer graph

The initial coverage audit found 195 bank-04 models without a recovered scene
association, containing 117,755 source faces. Following the common loader closes
149 of those associations across 59 bundles, covering 116,499 faces. The remaining
46 bank-04 models contain 1,256 source faces. These are consumer relationships;
they do not establish that all associated geometry appears in one frame.

## Loader and downstream consumers

`func_150031EC` loads `[04, scene-index]` at `0x15003218–0x15003230` and stores
the relocated descriptor table in `D_800B0E50`. Its signed comparison at
`0x15003208` sends inputs at least `0x45` to bank-04 entry zero. Negative inputs
are not clamped by that comparison. The report covers the reviewed nonnegative
scene domain `0..68` and preserves missing bundles explicitly.

The loop at `0x15003304–0x15003424` advances eight bytes per descriptor. It skips
null/zero-sized segments, relocates header offsets `0x00`, `0x08`, and `0x10`,
and treats indices below four specially at `0x1500335C`. Those initial slots
install the main display-list pointer at `D_800B0E00[slot]`, the vertex base
`model + 0x28` at `D_800B0E10[slot]`, and the secondary-region pointer at
`D_800B0E20[slot]`. `D_800B0E40[slot]` receives the vertex count computed from
the display-list/vertex-base difference divided by sixteen. Later descriptors
remain available through the indexed model table used by object placements.

| Slot | Nonempty models | Display-list storage | Reviewed downstream use |
| --- | ---: | --- | --- |
| 0 | 59 | `0x800B0E00` | Conditional rendering and collision array 0 |
| 1 | 39 | `0x800B0E04` | Conditional rendering |
| 2 | 13 | `0x800B0E08` | Conditional rendering |
| 3 | 38 | `0x800B0E0C` | Collision array 1; no rendering edge claimed here |

`func_1510B9D0` provides concrete rendering edges. It emits a `DE000000`
display-list call from slot zero at `0x1510BD70–0x1510BD7C`, with other conditional
paths emitting that same slot or passing it to `func_150A50C0`. It emits slot one
at `0x1510BDE4–0x1510BDF4` after a null check and scene-dependent state setup.
Slot two is checked at `0x1510BEE4–0x1510BEF4` and emitted at
`0x1510BF18–0x1510BF2C`. The graph therefore records 111 models with a static
path to conditional rendering, without asserting their visibility or a common
material state.

`func_15003668` selects collision array zero, then passes slot zero to
`func_15002724` and `func_15001460` at `0x150036B4–0x150036C8`. It selects array
one and passes slot three at `0x150036DC–0x150036F0`. These are 97 potential
nonempty collision inputs, not a replacement count for the existing 96 exported
static collision meshes, whose primary surface-table acceptance is stricter.
Slot three must not be added to visible scene geometry based on this evidence.

The five initial-slot secondary regions retain their source offsets and runtime
storage locations. Their meanings are still unresolved. An earlier bounded US
symbol-reference search found no direct use of `D_800B0E20..2C` beyond the
loader; this is static negative evidence, not proof that indirect consumers do
not exist. No new emulator trace was needed for the positive edges above.

## Generated evidence and coverage

```sh
./conker model-assets scene-consumers
./conker model-assets coverage \
  --runtime-materials build/assets/models/us-runtime-materials-all-states-with-textures/manifest.json \
  --task-runtime-materials build/assets/models/us-runtime-materials-character-draws/manifest.json \
  --activity-manifest build/assets/models/us-character-activity/manifest.json \
  --scene-manifest build/assets/models/us-scene-consumers.json
```

The first command writes `build/assets/models/us-scene-consumers.json`. Its 69
scene records join initial slots with both existing placement sources:
`[0B, scene]` and `[0C, scene, 2]`. All 1,227 resolved placements retain their
original record identity and transforms. Eleven records in scenes 17 and 62
retain their missing bank-04 model references. The graph reaches 785 distinct
models: 719 in bank 04 and 66 in bank 03. Hashes of the three reviewed ROM-code
spans and the normalized ROM identity are recorded alongside the graph.

The second command writes `build/assets/models/us-coverage.json`. Model keys are
`bank:entry:segment`; material-run keys append the run index. Bank numbers are
hexadecimal in keys, while entry, segment, and run numbers are decimal. Numeric
fields are also provided. Each run links to its model record through `model_key`.

Evidence dimensions remain independent:

- Standalone model bytes are compared to the normalized ROM, and bank-04
  descriptor bundles must rebuild byte-identically.
- Blender validation requires a matching per-file record for the current glTF
  and every external buffer/image it imports. Legacy totals, missing files, and
  stale fingerprints do not grant validation credit.
- Static texture coverage follows the conservative exporter and proven loader
  contracts. Runtime material observations and captured PNGs are counted
  separately. A captured material without image bytes does not resolve a texture.
- Segment-8 coverage requires an exact captured list payload for that run's
  offset. A known segment base is insufficient. Later-overridden lists remain
  distinct from lists matching the effective draw state.
- Character composition coverage unions exact source-face spans. Partially
  observed runs stay partial; overlapping catalogs do not inflate face counts.
- A resolved scene edge means a recovered consumer association. Naming requires
  a reviewed machine-readable ID/caller registry; none is supplied, so names are
  recorded as unknown even where prose documentation identifies a character.

The initial audit also found that the stored bank-03 extraction manifest's
placement section predated bank-04 dispatch resolution. Coverage uses the current
ROM-backed placement decoder instead of trusting those older summary fields.
The bank-03 extraction manifest was regenerated during this work.

The report ranks gap families by source faces in affected models or runs. This
is an impact measure, not a count of triangles observed in captured draws, and
different gap dimensions overlap. The largest remaining bank-04 families are
runtime material observation (5,164 runs, 134,826 source faces) and static
mode-one CI8 texture policy (2,713 runs, 70,475 faces). Scene graph recovery still
needs portals, lights, fog, cameras, triggers, and conditional render order.
No name, material, or scene replacement is inferred from appearance.

The current validation covers 1,031 standalone models, 8,989 material runs, and
213,946 source faces. All 1,367 existing preview/composition glTF files import
in Blender 5.2.1 with 2,869 meshes, 382,895 polygons, and 2,621 Actions. No glTF
geometry changed in this slice; the validator now retains per-file fingerprints.
Import success does not establish N64 lighting, combiner, mipmap, or raster parity.

The final checks passed for all four `model-assets verify --bank XX` commands,
11 focused coverage tests, the full 487-test Python suite, `py_compile` on the
changed Python files, and asset-file whitespace checks. The existing matrix
format and absolute palette-address corrections were preserved. This slice did
not edit mapping, progress, or C decompilation files; concurrent changes to those
files in the shared checkout were left untouched.

Implementation files for this slice: `scripts/model_coverage.py`,
`scripts/model_scene_consumers.py`, `scripts/model_preview_evidence.py`,
`scripts/model_assets.py`, `scripts/validate_model_previews_blender.py`,
`scripts/conker.sh`, `tests/test_model_coverage.py`, `docs/asset-roadmap.md`, and
this evidence note. Generated coverage, consumer graphs, the refreshed bank-03
extraction manifest, and Blender evidence remain under ignored `build/` paths.
