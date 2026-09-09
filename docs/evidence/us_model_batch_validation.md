# Automated US model validation

For human inspection, run `./conker model-assets inspect` after validation. It
packages the selection in `config/model-inspection.json` into clearly named,
self-contained GLB files under `build/assets/models/inspect/`, with a browsable
index and source/dependency hashes. Geometry buffers, rigs, animation Actions,
material definitions, and image bytes are preserved. Conker's recommended neutral
copy uses the captured-colour export with resolved eyes. The command rejects stale
source fingerprints or missing successful glTF/Blender import checks.

`build/assets/models/previews/` contains current inspection images. Regression
references live separately in `build/assets/models/validation/baselines/` and are
not changed by the inspection command. Older exports and preview iterations are
preserved outside the working model folder in
`build/assets/model-archive/2026-09-09-inspection-cleanup/`; its relocation manifest
records original paths and hashes. `build/assets/models/START-HERE.md` describes
the active outputs and the archive.

Run the current corpus through one command:

```sh
./conker model-assets validate
```

The command writes `build/assets/models/validation/report.json` and
`review.html`. It reads the ROM, extracted models, captured material catalogs
and configured regression images. It does not rewrite those references,
regenerate model exports, or launch a new emulator capture.

The default configuration is `config/model-validation.json`: both the main
and captured-colour preview corpora, character compositions, three runtime
catalogs and nineteen representative render cases. Use `--validation-config`
and `--output` for a separate corpus/report. `--blender` selects an executable;
otherwise the command checks PATH and the standard macOS application path.

Install the pinned Khronos dependency once, under ignored build output:

```sh
npm install --prefix build/tools/model-validation --ignore-scripts \
  --no-audit --no-fund --save-exact gltf-validator@2.0.0-dev.3.10
```

This is the official [Khronos glTF Validator](https://github.com/KhronosGroup/glTF-Validator).
The adapter loads only declared local buffers/images and emits issue codes and
JSON pointers. Missing Node, a missing/wrong validator version, or disabled
Blender/rendering produces incomplete evidence. `--skip-blender` and
`--skip-renders` support explicit checks without those tools.

## Checks and their limits

1. All four model banks reconstruct byte-identically from the actual ROM.
2. Standalone exports are compared numerically with decoded ROM geometry:
   triangle order, per-corner bind-space positions, selected UV coordinates,
   rigid vertex-load joints/weights and material spans. The comparison reads
   glTF accessors and buffers directly, without calling the exporter again.
   It proves consistency between the decoder and exporter; a shared decoder
   error still requires independent runtime evidence to detect.
3. Captured material state, source identities, trace hashes, texture hashes and
   recorded lighting samples are checked. Static and captured texture pixels
   are compared only when format, dimensions, source bytes, palette and source
   window agree. Different runtime inputs are classified as incomplete for
   this comparison, not assigned a guessed equivalent image.
4. Khronos checks every configured glTF. Blender checks imports, finite mesh
   coordinates and recorded culling flags. Zero-face source records must carry
   explicit empty-geometry metadata and matching manifest evidence; an absent
   mesh in an ordinary model remains an error.
5. Configured renders use fixed views, settings and the existing preview
   renderer. The report compares decoded RGBA pixels and creates a difference
   PNG for each changed image. References are never replaced by this command.
6. Configured `runtime_draw_cases` compare exported rigid rigs against captured
   submitted VTX bytes and vertex-load matrices. The first case covers two
   complete Tediz instances, with separate material and native-appearance
   evidence. See [submitted-rig validation](us_tediz_submitted_rig_validation.md).

The report keeps static textures, observed runtime material state, segment-8
state, composition, scene association, semantic naming and native visual
parity separate. A successful data/import check cannot fill another dimension.
Captured texture agreement is not a full comparison against the N64 rasterizer.
Complete posed geometry, lighting, combiner and raster parity still require
additional aligned runtime evidence.

## Caching and review

Caches are keyed by input content and relevant validation/tool identities.
glTF fingerprints include external buffers and images. Import identity includes
the Blender binary/version and validation implementation; render identity also
includes camera/shading/size settings and renderer code. Captured comparisons
include trace and image contents. Source checks include ROM and Python source
identities. Inputs are checked for changes during processing.

Successful unchanged imports and renders are reused. The command records how
many checks/imports/renders were executed versus cached. Worker logs and
per-file results remain under the report directory, so an interrupted batch
can reuse completed checks on the next invocation.

`review.html` contains concrete validation failures and changed or unreferenced
render cases. Missing runtime evidence stays in the machine-readable report;
it does not create thousands of image-review cards. A changed render is
incomplete pending interpretation: it may be an intended correction rather
than a regression. An unchanged reference image passes only the regression
comparison, never native correctness.

A new run immediately replaces the previous report with an incomplete running
record. Input failures write a failed report, and interruption leaves the
current run incomplete. Completed per-file cache entries remain reusable.

The CLI returns 1 for failed checks and 0 when no checked consistency rule
fails. A zero exit code may still accompany `status: incomplete`; automation
must inspect the report before claiming complete model correctness.

## First detected export defect

The first Khronos pass rejected eight glTFs for bank-01 entries 11 and 72:
bind and animated files in each preview corpus. Both source records contain
zero faces. Empty glTF mesh/material arrays are invalid even though Blender
previously accepted them. They now export their hierarchy and source metadata
without an invented mesh, while retaining inverse-bind data. Source records
and binary payloads remain preserved.

## Initial verified corpus

The completed checks cover 1,186 distinct source models and 2,372 standalone
exports across the two corpora. All numeric geometry comparisons pass. All
3,015 glTF files pass Khronos and Blender checks; all fifteen regression
images retain identical RGBA pixels. Eight empty-record JSON files changed,
while the other 3,007 glTF dependency fingerprints are preserved.

There are 1,924 matching captured-image comparisons and 1,195 incomplete
observations across the three catalogs, with no pixel mismatches. These are
catalog observations, which may overlap; they are not 1,924 distinct textures
or models. The captured pixel hash is checked over the recorded loaded byte
extent, with a separate palette hash. The captured extent must contain the
complete selected image, including its row stride and source offset.

The main Blender evidence contains 1,546 files, 3,084 meshes, 399,102 polygons
and 2,621 Actions. The separate captured-colour evidence contains 1,469 files,
2,993 meshes, 370,598 polygons and 2,621 Actions. Removing the invalid empty
meshes changes mesh counts without removing source faces or records.

All 601 Python tests pass, along with Python compilation, shell syntax and
scoped whitespace checks. Regression tests cover changed vertex positions,
triangle order, accessor bounds/non-finite data, empty model preservation,
image differences without reference replacement, captured pixel/TLUT extent,
separate evidence dimensions, cache identities, fatal input errors and
interruption. The real Khronos adapter also rejects an invalid empty mesh.
Before inputs, verification logs and preservation checks are under
`build/assets/models/reference/batch-validation/`.

The final cached run exits successfully and reuses all 3,015 glTF checks and
Blender imports plus all fifteen renders: zero fresh Khronos checks, zero
Blender imports and zero renders. Its review queue is empty while model
correctness remains explicitly incomplete. `verification-summary.json` records
the report hash and counts; `cached-validation.log` contains the CLI result.

The later [direct intensity correction](us_direct_intensity_model_textures.md)
adds four pre-change render references to exercise IA8, IA16, I4 and I8 image
selection. These bring the current configuration to nineteen cases. Deliberate
appearance changes remain visible as differences; an earlier cached regression
pass is not carried forward across changed glTF or image inputs.
