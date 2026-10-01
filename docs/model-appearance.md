# Model appearance extraction

The model exporter separates ROM geometry, guarded ROM-consumer material state,
and capture-scoped inspection presets. A linked texture is not proof of native
lighting, blending, visibility or animation timing. The active target is the
normalized US ROM, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Inputs and ordinary exports

Follow [setup](../CONTRIBUTING.md#setup) with a ROM you are authorized to use.
Model previews require all six proven texture catalogs. Generate them from the
same ROM, using new output directories or the extractor's explicit refresh
options when catalogs already exist:

```sh
for family in 64x64 1056-proven ci8-proven rgba16-proven native-proven tiled-views; do
  ./conker texture-assets extract --family "$family" --rom roms/baserom.us.z64
done

./conker model-assets preview --bank 01 --rom-defaults \
  --rom roms/baserom.us.z64 \
  --output build/assets/models/rom-only/us-bank-01-preview
for bank in 03 04 09; do
  ./conker model-assets preview --bank "$bank" --rom roms/baserom.us.z64 \
    --output "build/assets/models/rom-only/us-bank-${bank}-preview"
done
```

Catalogs default to `build/assets/textures`. ROMs, captures and generated assets
are not included in the repository. The commands above read local inputs; they
do not start an emulator or establish visual acceptance. See [resumable
batches](model-batches.md) for corpus refresh and review workflows.

## ROM-only corpus validation

The [ROM-only validation config](../config/model-validation-rom-only.json)
uses the four preview directories above without requiring capture catalogs:

```sh
./conker model-assets validate \
  --validation-config config/model-validation-rom-only.json \
  --output build/assets/models/validation-rom-only
```

Optional activity and scene inputs may be omitted or set to `null`; their
evidence remains unobserved. An explicitly specified missing path still fails
validation. This separate configuration does not change the full capture-aware
validation configuration.

For a source-check-only run, append `--skip-blender --skip-renders`. Those options
explicitly leave Blender import and visual/render evidence incomplete. The
optional Khronos glTF validator may also be unavailable; inspect the report for
skipped or missing checks. Source, geometry and material checks must still pass,
and a successful source-only run is not complete visual or native validation.

## Explicit appearance presets

Use the shared dispatcher for a narrowly scoped inspection export:

```sh
./conker model-assets appearance --help
./conker model-assets appearance --preset haybot-captured-selector15 \
  --output build/assets/models/haybot-captured-selector15
./conker model-assets appearance --preset haybot-captured-selector15 \
  --output build/assets/models/haybot-captured-selector15 --verify
```

Generation requires a new directory below `build/`. `--verify` regenerates the
expected files and compares an existing export without overwriting it. `--rom`
and `--textures` select alternate local ROM/catalog inputs. Each module pins its
metadata contract and validates source, material and texture identities; an
arbitrary edited contract is not admitted. Neither generation nor verification
replays a capture or runs Blender/native rendering.

| Preset | Source scope | Material claim |
| --- | --- | --- |
| `scene60-captured-primary-opacity255` | bank01 entries154/162, primary normal part0; 403/508 selected faces | Captured model154 mode2 and model162 mode1, caller opacity255 |
| `library-bat155-captured-primary-opacity255` | bank01 entry155, primary normal part0; 314 selected faces | Captured mode1, caller opacity255, bounded material/load/mip state |
| `haybot-captured-selector15` | bank01 entry75, complete selected source draw pass; 1,226 faces | Captured selector15 material for run16, 24 faces, flat3823 |
| `shc-boat-captured-parent42` | bank09 attachment47; 50 vertices and 36 faces | Captured Soldier88 actor42 context; flat4195 on the eight target faces |
| `haybot-rom-selector-variants` | bank01 entry75; separate selector15/16/17 exports | Conditional ROM-consumer bindings to flat3823/3822/3824, without capture-phase claims |

These choices are implemented by `scripts.model_appearance`,
`scripts.model_scene60_appearance`, `scripts.model_library_bat155_appearance`,
`scripts.model_haybot_appearance`, `scripts.model_shc_boat_appearance` and
`scripts.model_haybot_rom_variants`. The metadata contracts live in `config/`.
Capture-scoped contracts retain reviewed evidence identities; ordinary export
needs the shipped contract and authenticated ROM/catalogs, not raw capture
files. Independent capture re-auditing requires the corresponding evidence
inputs and is a separate operation. See [audit tools and input
requirements](evidence/us_model_evidence_audits.md).

### Scene60 and Library155

The Scene60 preset binds 20 targeted material runs covering 384 faces. The
Library155 preset binds 11 runs covering 186 faces, retaining the reviewed
texture-load histories and seven mip levels. Neither preset changes original
texture alpha. Their opaque, unlit materials are pre-blender black inspection
approximations for the captured primary appearance. Fog colour, framebuffer
blending, fractional edge coverage and native raster parity remain unproved;
`FORCE_BL` being false does not bypass the first blender cycle.

Geometry, UV/rig/animation buffers and the selected part identities are guarded
through the material update. These are not captured-pose or visibility exports.
Library155 has no own bank02 animation companion in the reviewed source; this
does not rule out runtime or borrowed animation. Other unresolved materials are
not admitted merely because the preset's targeted runs are proved.

### Haybot

The captured preset retains 1,625 vertices/UVs, 45 joints and 15 stored clips /
291 frames. All 1,226 source faces are retained, including collinear face 345.
Only run 16 receives the captured selector 15 texture. Initial
descriptor0/default bindings remain unchanged. See [the capture and ROM
proof](evidence/us_haybot_appearance.md).

The ROM variant preset emits three static choices. Its updater/descriptor and
pixel checks support selectors 15/16/17, but do not establish when a phase ran,
texture playback timing, captured pose or native lighting. Normal glTF retains
the stored clips; bind glTF has no animation. Capture-specific evidence is not
used to label these outputs as observed frames.

### SHC boat attachment

The boat preset changes the eight missing attachment47 faces to the proved 32×32
CI8/RGBA16 flat4195 pixels/TLUT. The other 28 faces keep flat4198/4216. Accepted
captured draws 0/2 and excluded draw 1 remain explicit. Source geometry, UVs and
the empty source rig are preserved; no parent eye texture, joint or animation is
invented. Parent transforms are not baked, and animation24/action 74 activation
remains unobserved. This is not a universal Soldier default or native
lighting/raster reproduction.

## Selection, source faces and verification

The Python `extract_model_preview(entry_filter=...)` interface supports an
explicit nonempty set of bank01 entries. It validates unique, nonempty segment 0
bundles before preparing output, retains all bundles for morph checks, and emits
selection metadata. `verify_preview_output(expected_entries=...)` checks exactly
one segment 0 record per selected entry, consistent model/animation accounting,
and the ordinary OBJ/MTL, glTF/binary, rig, animation and bind invariants.
Manifest metadata alone cannot enable subset verification. Preset-specific ROM
identities and animation inventories remain additional guards.

`preserve_zero_area_faces=True` requires explicit bank01 selection and preserves
all triangles in the selected source draw pass, including repeated-index,
duplicate-position and collinear faces. It does not select a different primary
or secondary pass. The default omission behavior is unchanged. Preservation and
omission accounting must agree with the manifest.

The unchanged full-bank verifier expects 2,621 stored clips, 57,732 frames and
zero incompatible clips. Selected exports use their explicit per-entry scope;
passing a selected export is not a full-bank verification result.

## Guarded bank09 consumer materials

The ordinary bank09 export uses fail-closed ROM-consumer contexts when no
capture material takes precedence. Source geometry remains separately available
for validation and accounting.

- [Script object213](evidence/us_script_object_materials.md): selector13 and its
  initial callback-disabled object state bind four faces
- [Particle203](evidence/us_particle203_material.md): the initial type16 renderer
  supplies lookup/combiner state for 20 faces and 4,096 texels; dynamic draw alpha
  remains unknown
- [UI162/164](evidence/us_ui_constructor_materials.md): copied display-list state
  and first-draw texture binding resolve 20/29 faces; later blink state is separate
- [Special attachments165/185](evidence/us_special_attachment_materials.md):
  explicit initial/correlated phase bindings resolve 29/16 faces across six runs;
  model185's remaining external-texture faces are outside those bindings

## Metadata diagnostics and coverage

[Expression constructor
reports](evidence/us_expression_attachment_constructors.md) decode six ordered
requests across five action programs for attachment models 132,15,16,18. The
canonical fields are action fields; expression u16+6 is not an attachment
lifetime and is ignored by these kind 1/2 constructors. Requests do not prove
allocation, placement or playback.

[Event diagnostics](evidence/us_model_event_activation.md) inspect bounded
source-consumer routes:

```sh
./conker model-assets event-activation --scene 30 \
  --output build/assets/models/event-activation-scene30.json
./conker model-assets event-activation --scene 60 \
  --output build/assets/models/event-activation-scene60.json
./conker model-assets coverage \
  --output build/assets/models/us-coverage.json
./conker model-assets coverage --rom-character-presets \
  --output build/assets/models/us-coverage-with-presets.json
```

Scene30 event144 contains six conditional requests for model 66, the purple
flamethrower imp. Model40 is the playable tank. Scene60 contains eight literal
script-start requests, four linked to initial model 162 tracks. Neither report
proves event admission, actor creation, visibility, a gameplay route or
appearance.

[Coverage](evidence/us_model_coverage.md) recomputes guarded ROM material
fallbacks and uses full-source face/run identities. Optional ROM character
inspection presets are a separate, off-by-default dimension. Static missing-PNG
counts, combiner-aware batch blockers, exported faces, runtime observations and
native appearance acceptance measure different things and must not be added
together. Regenerate reports for current backlog counts.

## Regression checks

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model*.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests
```

The suite includes selection/preservation, contract, source/material mutation,
consumer, pixel and accounting checks. ROM/tool-dependent checks can skip when
their required inputs are absent; report skips and actual results for the
current checkout. Unit results alone do not establish real-ROM export
correctness or Blender/native raster equivalence. Run each applicable export's
verification and inspect its explicit scope before treating it as evidence.
