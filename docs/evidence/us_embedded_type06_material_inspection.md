# Type06 elapsed-zero material inspection

The existing embedded primitive at game-data `0x8008D538` has a separate,
self-contained GLB that applies its proven untextured material at an explicitly
selected constructor state. It preserves the original four vertices, three
ordered triangles, normalized byte `COLOR_0`, buffer/accessor layout, local
coordinates and source inventory. No closing face or runtime copy is added.

This is a selected portable presentation, not an observed native first draw.
The setup leaves some geometry flags inherited, including the shading and
smooth-interpolation flags. This artifact explicitly selects linear vertex-color
interpolation. Native RSP/RDP coverage, depth, triangle ordering and framebuffer
quantization remain outside its parity claim.

## Positive source state

The original geometry exporter continues to guard complete source consumer
spans and setup/data bytes; see [the embedded geometry evidence](us_embedded_effect_geometry.md).
The selected material additionally guards all 220 bytes of caller
`func_150D8A34`, SHA-256
`ce0290cea244d44277242557d13a3376ec24efe450fecb2b3fb8a59fcdb39121`.
An independent audit compared 886 raw ASM instructions from that caller and
the constructor, updater, renderer and dispatcher against the decompressed US
ROM. It saved the exact spans and instruction words under
`build/assets/models/reference/resolution-goal-20261002/embedded-type06/material-followup/audit.json`.

The caller requires a non-null actor field at `+0x1D4`. At `0x150D8A74` and
`0x150D8A78` it supplies constructor arguments 15 and 7, stored to stack offsets
`0x10` and `0x14`, before calling `func_151875E0` at `0x150D8A98`. The constructor
stores record elapsed time zero at `0x15187920`, and lifetime
`15 - (random & 7)` at `0x15187940`. Every possible lifetime is therefore a
positive integer from 8 through 15. Object field `+0xA8` also starts at zero,
satisfying the renderer's nonnegative gate in this selected state.

`func_15187A98` reads signed record lifetime/elapsed values at `+0x96`/`+0x94`,
calculates `((lifetime - elapsed) * 255 / lifetime) & 255`, and emits white
primitive RGB with that alpha. With selected elapsed zero, all eight possible
positive lifetimes give exactly 255. No random lifetime needs to be invented.
The updater can advance this state before a draw; the artifact does not assert
that a live effect is ever submitted before that update.

The descriptor at `0x8008B5E0` links this renderer to setup `0x8008D4F0`. The
dispatcher submits the setup before the draw. Its relevant commands are:

| Command | Proven state |
| --- | --- |
| `D7000000 00000000` | Texture disabled |
| `FC323864 FF73FFFF` | RGB and alpha each multiply PRIMITIVE by SHADE |
| `D9FDF9FF 00000000` | Lighting and both culling bits cleared |
| `EF082CAF 00504A50` | One-cycle translucent blending, forced blend, no alpha compare, no depth write |

The active blender mux uses incoming color times incoming alpha plus memory
color times one minus incoming alpha. Primitive RGBA255 leaves the original
vertex values unchanged: vertex 0 is `(255,255,255,16)` and the other three are
`(255,255,255,255)`. All RGB values are at the white endpoint, so an RGB color-space
conversion does not alter them. Alpha remains the linear normalized byte value
`16/255` at vertex 0. All original signed ST values are zero and remain in the
unchanged raw vertex records; no UV attribute is synthesized.

## Minimal derived representation

`scripts/model_embedded_type06_inspection.py` freshly rebuilds and compares all
five original files from `build/assets/models/embedded-geometry`. Those files
remain unchanged. It creates a separate output at
`build/assets/models/embedded-type06-material-inspection` by default.

The source-document changes are one primitive material binding, one material,
a `KHR_materials_unlit` declaration and explicit selected-material metadata.
That material has white base color, `alphaMode: BLEND` and `doubleSided: true`.
Existing diagnostic extras are preserved intact under `sourceDiagnosticExtras`;
the new top-level scope, state, material status and policy describe the selected
material accurately rather than repeating the original material-free status.
The packer retains the original 84 mesh-buffer bytes exactly. The resulting
download is `embedded-type06-8008d538-elapsed0.glb`; its corresponding source
glTF is `geometry/embedded-type06-8008d538-elapsed0.gltf` within the new output.

The source raw GLB is still
`build/assets/models/embedded-geometry/embedded-type06-8008d538.glb`, SHA-256
`80caa8b75f124273739df96971ed0f274ca31386a1e3073ee2a89210f750d786`.
It is retained as evidence. The selected variant is intended for one visible
download, not a second gallery card for the same primitive. No effect identity,
activation, twelve-instance arrangement, random transforms, scale or fade
timeline is inferred.

## Rebuild and validation boundary

The supported embedded-geometry command routes this selected material to the
separate backend. It accepts `--rom`, `--output`, `--blender` and `--verify`:

```sh
./conker model-assets embedded-geometry --primitive type06 --material-inspection elapsed0
./conker model-assets embedded-geometry --primitive type06 --material-inspection elapsed0 --verify
```

Creation refuses any existing output directory. Verification derives the ROM
source, state proof, derived glTF and packed GLB again, then requires exact bytes.
Both derived glTF and packed GLB are freshly checked by the installed Khronos
validator, with zero errors and warnings required. Blender freshly imports the
GLB with auto-execution disabled and checks the single mesh, all ordered faces,
positions, normalized RGBA including alpha16, absence of UVs/images/Actions, and
the actual unlit vertex-color/alpha shader links.

A separate temporary triangle uses that imported material to measure its
portable alpha interpolation against six independent linear-alpha expectations.
Each measurement averages 256 interior pixels over a black background. The
maximum permitted absolute error is 0.02; the reviewed local run measured
0.0003676191. This is a portable material oracle, not an emulator or native
RDP comparison. It never enters the exported GLB.

Two fixed views are rendered at 768 by 768 pixels. Verification reconstructs
both views into a temporary directory and requires exact saved PNG bytes;
timestamp/render-time stamp metadata is disabled for reproducibility. Fresh
verification leaves every candidate file unchanged. A changed Blender importer,
renderer or graphics environment can require a new reviewed output instead of
silently accepting changed previews.

`inspection_artifact(output)` performs fresh ROM/Khronos/Blender checks and
returns `glb`, `preview`, `proof` and `scope`. The proof separates
`source_glb_sha256` (the original diagnostic file) from `derived_glb_sha256`
(the actual download), binds the raw source fingerprint, state, every prepared
and generated file, and current tool/validator code. The final
`inspection_artifact_current(output, proof)` rederives the source and checks that
all bound bytes and tools remain unchanged before publication.

Focused tests exercise the positive lifetime gate, changed caller/constructor
words, alpha/ST/combiner mutations, exact source-document delta, output bounds,
existing-output refusal, stale-artifact rejection, distinct raw/derived hashes,
and fresh validation/admission ordering. Isolated real artifact copies also
test coherently rehashed opaque material, vertex alpha, face order and preview
changes. Their results and unchanged-file snapshots are saved in
`material-followup/supported-validation.json` beside the source audit.
