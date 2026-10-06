# Scene 55 independent texture-plane inspection

The supported `scene55-inspection` command creates a self-contained Blender file
for the existing scene 55 assembly. It restores the second CI4 sampling plane on
`04:0055:04` (38 faces) and `04:0055:05` (46 faces), using ROM-data-initial zero
scroll and an explicitly selected stored vertex RGBA state. It does not establish
the scene's native lighting, current animation time, activation, or raster parity.
This is an appearance inspection of existing geometry, not an additional model
extraction or a reason to add another gallery card.

```sh
./conker model-assets scene55-inspection
./conker model-assets scene55-inspection --verify
```

The default output is `build/assets/models/scene55-material-inspection`;
`--output`, `--rom`, and `--blender` are supported. Creation refuses any existing
output directory. Verification compares the prepared files against fresh ROM and
assembly derivation, independently reconstructs the expected Blender scene, then
opens the saved Blend with auto-execution disabled. It preserves existing files
on failure. The normal scene assembly glTF/GLB and its source inventory remain
unchanged.

## Exact source and state

The pinned contract is `config/model-scene55-inspection.json`. The source is
`build/assets/models/rom-scene-assemblies/geometry/scene-55.gltf`, SHA-256
`c637b845aadde253f2975e2e4e66d1242f90f0544f19356105ce847f1e20d232`, with binary
`518f4733d57572cd8efa1ddd84535d36ebd4876b8f7cb3d1fb5c754f62dd39c0`.
All ten component payloads and source fingerprints, fresh scene placements, the
reviewed exclusion of `03:0051:00`, and deterministic assembly composition are
rechecked. The two affected raw model SHA-256 values are:

- `04:0055:04`: `da822d9ddac7f0f4e6e7fec8458b0b93258396e9e0629c1a387a8424d36be6d2`.
- `04:0055:05`: `8a3ce805129422875f5050f0a4798d2e5e4926b381c0756ae125ca6a542a9c35`.

US ROM SHA-1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
Flat asset 737 has 2080 decoded bytes, SHA-1
`6efffd09da18f157c1f2f77daf5f3f7f51873008`. Its compressed ROM interval is
`0x2DA085..0x2DA68C`, SHA-256
`b88ff4038c8bdf1545b90e24b44964e0914f54f37d9655d1283ca7e12450046f`.
The first 2048 bytes contain two 1024-byte CI4 planes; the last 32 bytes are their
shared RGBA16 palette. The exact pixel and palette transfer commands are
`FD500000`, `F3000000 073FF000`, `FD100000`, and `F0000000 0603C000`.
Load-time tiles 7 and 6 are checked separately from final render tiles.

Render tiles 0/1 are `F5400800 00014060` and `F5400880 01014060`:
64 by 32 pixels, 32 bytes per row, TMEM starts 0/1024, and repeat masks 6/5.
Each odd TMEM row swaps the two four-byte halves of every eight-byte word.
The bounded decoder verifies the complete transfer, palette, scale, tile and
combiner contract; it does not relax the shared decoder's nonzero-TMEM guards.
An independent per-pixel byte/nibble/TLUT oracle checks all 4096 decoded pixels.

The two-cycle combiner `FC111404 FF13FFFF`, with mode `EF18AC3F 0C184A50`,
multiplies the two texture samples and SHADE, including alpha. The Blender shader
samples each plane separately, then multiplies their RGB/alpha with the selected
stored source RGBA. It uses raw normalized byte values (`Non-Color` images),
independent linear filtering and repeat addressing. Multiplying texels into one
image before filtering is not equivalent and is not used.

The four ROM-data words `80088890/94/98/9C` are zero. Helper `150CF5E8` then
produces `F2000000 0047E47E` and `F2000000 0147E47E`; repeat-mask dimensions,
not the large tile-size extent, determine the sampling periods. The exporter
rechecks complete ROM consumer spans at `150039E0`, `151137D4`, `1510B9D0`,
`150CF5E8`, `150CF578`, `150D0E90`, and `1510CDB8` against the pinned contract.
This establishes an explicit ROM-data-initial scroll state, not the phase at an
actual scene draw. Neither plane's phase is guessed from a screenshot.

The affected records have no custom normal commands or vertex-color animation.
Their source alpha is uniformly 126/255. Their caller enables lighting, and the
model's geometry-mode command does not clear it. Consequently stored RGB is an
explicit inspection input, not a recovered universal native SHADE value. No
scene 49 alpha change is implied by this work.

## Blender preservation and verification

The existing assembly retains 22 mesh instances and ten source meshes: 3958
exported triangles import as 3948 Blender polygons. The ten preexisting repeated
triangles removed by the importer are unchanged by this material work. Source
positions, placements, UVs, material indices, original attributes and original
material graphs are compared before and after construction and after reopening.
The replaced original materials are retained with fake users. All 60 original
images and both new planes are packed, and exact packed bytes are compared.

Blender imports normalized glTF byte colors through `BYTE_COLOR`, which can
requantize linear RGB. For example, source 254 becomes 255. To retain the source
numbers, the worker adds `_CBFD_STORED_RGBA`, a `FLOAT_COLOR` corner attribute,
while preserving the original `Color` layer. All 252 affected corners are mapped
against original positions and UVs and checked against exact RGBA/255 values.
The shader reads this derived attribute. Source alpha remains 126/255.

Verification reconstructs the scene, original materials, replacement shader,
FLOAT_COLOR values, packed images, camera, lights and view settings before
opening the saved artifact. A coherently changed `artifact.json` and Blend
fingerprint cannot redefine that source-derived expectation. Texts, Actions,
drivers, modifiers, constraints, node groups and added handlers are rejected;
Blender's built-in factory handlers are retained. No external textures or scripts
are needed to inspect the saved file.

The independent sampling check renders 32 constant-coordinate swatches:
plane 0, plane 1, combined RGB and combined alpha at eight fractional UVs.
The CPU oracle reads raw source bytes independently of the production PNG
decoder. On Blender 5.2.1 LTS the maximum channel error was
`0.0020439066090305325`, below the 2/255 threshold. This checks the selected
Blender bilinear representation; native RDP three-point filtering, quantization,
coverage and blending remain outside the claim.

`inspection_artifact()` performs fresh source and Blender verification, checks
before/after stability, and returns the Blend, preview, scope and a proof of kind
`scene55-dual-texture`, scene index 55. The proof binds the original assembly
source/fingerprint, artifact hashes and loader/worker/config bytes.
`inspection_artifact_current()` rederives source and compares the admitted proof
at publication preflight. Gallery integration should replace the single existing
assembly card's visible download while preserving its raw source GLB evidence.
No native completion status or extraction count changes follow from admission.

## Validation and remaining limit

The eleven focused tests in `tests/test_model_scene55_inspection.py` cover the
second-plane/odd-row layout, complete transfer and combiner mutations, source
RGBA/UV mapping, contract mutation, output guards, create/verify behavior, fresh
admission and changed preflight inputs. Actual-ROM create and fresh verify passed
in the ignored `scene53-55/supported-04` checkpoint; both renders were inspected.
Coherently updated shader-offset, exact-color, geometry and image-color-space
artifacts were each rejected without writing any artifact file. Source files
are also compared before and after Blender operations.
Research and diagnostic artifacts remain under
`build/assets/models/reference/resolution-goal-20261002/scene53-55/`.

Scene 53 is deliberately excluded. Its RGB arrays have positive reset/conditional
zero evidence, but the renderer runs an updater before consuming them. The
view-specific gate and runtime updater can change those values; reset evidence
alone does not establish a real draw's colors. Parent research records that
bounded source chain in the sibling `scene53-colour-state/audit.json`. A native
capture must retain the gate, reset/update timing, both color arrays, both scroll
phases and the actual draw state before a scene 53 appearance is admitted.

A later camera-framing check reconstructs the active camera and render framing
before reopening the saved file. It compares camera transforms, orthographic
scale/shifts, sensor fit, clipping, disabled depth of field, render size, pixel
aspect and border/crop settings independently of saved metadata. A copied Blend
with `shift_x=3` and a coherently updated Blend hash is rejected. The canonical
neutral/animated entry-66 and scene-55 files all pass without changes to their
76 combined artifact/source files. Reproducible results are retained under
`build/assets/models/reference/resolution-goal-20261002/camera-framing/`.
