# Character 66 animated texture-generation inspection

This is a separate, source-preserving Blender inspection export for bank01 entry66.
It retains the three original Blender-imported Actions and makes the existing
source-normal texture-generation shader follow their evaluated joint rotations.
The supported neutral export remains unchanged and reproducible. This export does
not establish native gameplay lighting, camera/look-at state, visibility, or
pixel/raster parity.

The ROM/model/material attribution and selected lit, nonlinear, canonical-look-at
state are the same guarded contract documented in
[the neutral inspection evidence](us_character66_texgen.md). The input model is
SHA256 `57c4a724b2302de7f9515e058fad86c600bcc709991009e0410c361b3b0d1c17`;
the original glTF is
`ce9d4d11fdc5fd4650226e2ec13acdade2662b6dc93fb1dece87a5c66caaafd3`,
and its 54,384-byte binary is
`a8033a444cf314c24828674c84f78601962d8ea63549ba3b91cbb9d7ea34e953`.
`model_character_animated_texgen.build_files()` calls the existing neutral source
preparation, preserves every returned byte, and adds a separate custom glTF with
exactly the original three animation definitions plus `animation-proof.json`.
There is no alternate ROM decoder or source curve generation.

## Per-vertex joint proof

All 529 exported weighted vertex records have exact one-hot weights `(1,0,0,0)`.
The 309 generated-coordinate corners correspond to 103 source-proven faces.
Their original `JOINTS_0` values and bind positions agree with the native vertex
cache audit; the imported raw normal attribute remains signed byte /127 without
normalization.

| Material primitive | Source run | Source faces | Joint corner counts |
| --- | --- | --- | --- |
| 20 | 20 | 279–299 | 19:45, 13:18 |
| 21 | 21 | 300–301 | 6:6 |
| 31 | 31 | 365–405 | 19:123 |
| 32 | 32 | 406–419 | 19:42 |
| 33 | 32 | 420–438 | 6:57 |
| 34 | 32 | 439–444 | 13:18 |

Faces285–290 contain corners belonging to different joints. A single basis per
material, or even per triangle, would therefore be incorrect. Three ordinary
bone-parented Empty objects track the deformation transforms for joints6,13,19,
with inverse rest transforms. A Geometry Nodes modifier selects the exact
original joint per point and stores the rotated raw vector in a new point
attribute. The source normal attribute, vertex groups, UVMap and mesh topology
remain intact. Six material image-vector inputs consume the new attribute.
No fragment normal is substituted or normalized.

Every bind transform and inverse bind is a translation. All three source clips
contain only unit-quaternion rotation and translation channels, with no scale
channels. For an orthogonal joint rotation `R`, source raw vector `n`, and
camera-to-object axis `a`,

```text
n dot normalize(inverse(R) * a) = (R * n) dot normalize(a)
```

The worker applies the fixed native-to-Blender axis conversion consistently.
The shader normalizes the camera basis vectors separately, never `n`. Computing
the rotated vector on the point domain preserves the per-corner result across
mixed-joint triangles before interpolation. Original texture scale, tile origin
and half-texel rules are unchanged. Arbitrary nonuniform object or joint scaling
is outside this proven domain.

## Animation and verification scope

The original clips have respectively 11,10,30 source keys; their channel counts
are 28 rotations plus 2,3,2 translations. The original timing and animation
metadata are preserved. No Action is resampled, baked, or replaced. Blender's
imported Action curves use component-linear quaternion interpolation. That
interpolation differs slightly from the original glTF spherical interpolation
between source keys; this is a pre-existing import approximation, separate from
texture-coordinate generation.

The worker samples every source key plus 0.37 and midpoint positions in every
interval:147 poses, each from three-quarter and rear views. It performs two
separate checks:

- Against an inverse-axis oracle derived directly from evaluated imported
  pose-bone/rest matrices, the isolated prototype's maximum coordinate difference
  was `2.10e-7` across all294 pose/view samples.
- Against independently decoded original glTF matrices with spherical quaternion
  interpolation, source keys agreed within `2.40e-7` UV and `7.36e-5` source
  position units. Between-key differences reached `0.0002363` UV and `0.07304`
  position units. These differences are explicitly retained in the artifact
  report; they are not presented as native parity.

The prototype also reopened with automatic script execution disabled and rendered
two non-neutral source-key poses from both views. Independently baked source UV
references agreed analytically; image mean absolute channel differences were
`0.00023`–`0.00051`, with local differences up to `0.208`. This is a diagnostic
render comparison, not a pixel-equality claim. All445 faces,421 imported points,
28 bones,3 Actions and17 packed PNGs were preserved. No drivers, embedded Text
blocks or saved execution handlers are used.

## Supported output contract

```sh
./conker model-assets texgen-animation-inspection
./conker model-assets texgen-animation-inspection --verify
```

The default output is
`build/assets/models/character66-animated-texgen-inspection/`. Creation refuses an
existing output directory. The Blend opens in the neutral pose with the original
three Actions available for selection in Blender's Action Editor. Its neutral
three-quarter/rear thumbnails do not imply a captured native default. The
original source glTF and all animation/resource bytes remain in the output.

Verification first rederives all prepared files from the guarded ROM and current
canonical source. In a fresh Blender process it reconstructs expected mesh,
attributes, rig, exact Action curves, material nodes, image settings, Geometry
Nodes graph, helper transforms and NLA state before opening the saved Blend.
It compares that reconstruction with the saved scene, checks exact packed PNG
bytes, and repeats all294 coordinate comparisons. Verification does not rewrite
outputs and requires `--disable-autoexec`.

Publication uses the same two-stage snapshot boundary as the neutral export:
fresh source/artifact/tool hashes before and after the Blender check, followed
by another current-byte check immediately before publishing. Selection is an
explicit gallery mode, not an inference from a directory name. This file does
not authorize or perform gallery publication.

The frozen ignored prototype and reproducible audits are under
`build/assets/models/reference/resolution-goal-20261002/character66-visibility/animation-prototype/`.
Its audit SHA256 is
`1f56f7d0a6747c4fb8c8b05628097244ae2094088595eac7ed1862b52341ef7a`.

A later camera-framing check reconstructs the active camera and render framing
before reopening the saved file. It compares camera transforms, orthographic
scale/shifts, sensor fit, clipping, disabled depth of field, render size, pixel
aspect and border/crop settings independently of saved metadata. A copied Blend
with `shift_x=3` and a coherently updated Blend hash is rejected. The canonical
neutral/animated entry-66 and scene-55 files all pass without changes to their
76 combined artifact/source files. Reproducible results are retained under
`build/assets/models/reference/resolution-goal-20261002/camera-framing/`.

## Native submission evidence, 2 October 2026

An untouched copied save-game10 now reaches event144's imp spawn through ordinary
controller input. Four complete submitted graphics tasks select model66 part0 at
`8020B310`; exact relocated-list comparison accounts for all 445 source faces in
order. The 103 generated-coordinate faces retain the source XYZ, zero stored ST,
and all 309 signed-normal corners. Their three image/palette spans agree with
ROM flats3521,2373 and1343. Run21's two-triangle signature is disambiguated by the
complete 4,896-byte selected list and its ordered loads and geometry.

Task-order replay establishes the state at every affected vertex load, before
triangle emission: `LIGHTING` and `TEXGEN` are enabled and `TEXGEN_LINEAR` is
clear. Both observed geometry modes are `0x660005` and `0x660405`. The actual
signed LOOKAT vectors are `[126,0,-18]` and `[-1,127,-9]` in the first task,
then `[-1,127,-10]` for the second vector in the other three tasks. Raw matrices,
lights, normals and the last LOOKAT writes are retained independently. The normal
bytes stay constant while the submitted matrices change.

This is positive evidence for those four draws, not universal visibility or
pixel parity. It removes the need to guess the three mode bits for this native
context; it does not yet equate the inspection camera axes and neutral pose to
the captured LOOKAT and animated matrices. The capture stopped at submission,
so its earlier screenshot does not show the imp. Native visible-frame comparison
and the exact generated-coordinate comparison remain pending; the appearance
review stays open. No gallery or source artifact was changed by this audit.

Evidence is under `build/assets/models/reference/resolution-goal-20261002/`
`runtime/imp66/save-game10-early-combat/`. The task replay is
`task-state-audit/summary.json` (SHA-256
`a85b9969b08c84b0d1bb6e25661fb1df3b0b835acc8ae352cdc24349ec5793c5`),
and the independent source/material review is
`independent-material-review/review.json` (SHA-256
`bc461f4383f5f84978883539a351b85d06fc7bb3012f91b9762d14e5de6e4a8d`).

The subsequent independent calculation derives all 1,236 affected corners across
those four tasks. Supplying the same captured LOOKAT vectors to the inspection
shader algebra agrees within `3.83e-6` UV. Substituting the final render-camera
axes instead differs by up to `0.04853` UV, or `1.553` texels. This exceeds the
small fixed-matrix quantization difference; a universal angular correction is
not justified.

The source producer explains why the axes need not match. `1512C490` calls
`15047B80`, whose leaf `15047700` builds a base view and writes signed LOOKAT
components using `trunc(min(axis*128,127))`. Later operations can modify the
view without rewriting LOOKAT. The LOOKAT bank is also shared per buffer rather
than per camera. These captures do not distinguish a particular later view
effect from a subsequent camera's write. Exact captured-state inspection must
retain the two independently supplied axes.

A separate reframed diagnostic retains all 445 faces and 1,335 source corners,
using captured per-load matrices and original ROM images. The large pale parts
have the same approximately `0.88` rigid edge scale as other geometry; they are
not selectively enlarged. Applying generated UVs restores varying metallic
texture on them. All corners of the first task lie outside the native right
clip plane, so these reframed unlit images are comparison references, not native
screenshots. They support the texture-coordinate cause while leaving visible
native appearance under review.

The additional frozen reports in `independent-material-review/` are
`uv-review.json` (SHA-256
`82b0598829088f780189324e70e7efb73313b04e8f1621c25127dcdbbfd6b005`),
`lookat-producer-review.json` (SHA-256
`7e80b70a2357c9225c73ced48541d8b4c3436371d8c4b8b9b54681ecf378f914`),
and `pose-diagnostic/summary.json` (SHA-256
`ce6810d8685663475e0b85e1d9d5009c353921399d9173dc5a260c6d21ca779e`).
The coordinate derivation follows the primary CBFD implementation's semantics;
it is not an observation of exact CXD4 post-RSP rounding.
