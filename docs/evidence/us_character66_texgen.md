# Character 66: generated-coordinate inspection

The US bank-01 character 66 model contains 103 faces whose vertex loads have
texture-coordinate generation enabled. Its stored zero ST values cannot
represent the native view-dependent mapping. In the ordinary glTF export this
made the final helmet and equipment surfaces sample one nearly white texture
location. The geometry itself is retained; this finding does not establish a
part-visibility or deformation correction.

`./conker model-assets texgen-inspection` produces a separate neutral-pose
Blender inspection artifact, two 512-pixel previews, and source/verification
reports. `--verify` rederives the guarded ROM/source inputs and independently
checks the saved artifact without rewriting it. The existing review card offers
this single Blender download and its new preview; the raw GLB and ordinary
glTF exports retain their existing scope. This inspection is not a captured
gameplay default or an appearance-complete promotion.

## Source contract

The normalized US ROM SHA-1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; the decoded model SHA-256 is
`57c4a724b2302de7f9515e058fad86c600bcc709991009e0410c361b3b0d1c17`.
The guard in `config/model-character66-texgen-inspection.json` pins the current
ROM-only glTF and all 18 external resources. Extraction preserves its original
54,384-byte binary, 329 accessors, 35 primitives, geometry, source ST, materials,
17 images, rig and three animation clips in the accompanying source files.
The custom import appends four raw-normal attribute streams and omits Actions
from the inspection input; it does not replace the source files.

The single primary list begins at model offset `0x1D60`. Independent cache
replay accounts for all 445 faces and 1,335 source-normal corners. Attribute
state is recorded when a vertex enters the cache, rather than inferred from
the later triangle command. The generated spans are:

| Source material run | Faces | Triangle count | glTF material slots |
| --- | --- | --- | --- |
| 20 | 279–299 | 21 | 20 |
| 21 | 300–301 | 2 | 21 |
| 31 | 365–405 | 41 | 31 |
| 32 | 406–444 | 39 | 32, 33, 34 |

Model offset `0x2F38` emits `D9FFFFFF 00040000`, enabling texture generation;
`0x3070` emits `D9FBFFFF 00000000`, clearing it. An earlier enabled span runs
from `0x29B0` to `0x2AB0`. The 103 faces use joints 6, 13 and 19, all with
translation-only transforms in the authored neutral pose. All affected source
ST pairs are zero. The model has one primary display list: actor `+0x94` bit
zero would hide the whole list, rather than selectively hiding these pieces.

## Coordinate interpretation and selected state

The CBFD vertex path obtains signed X/Y normal bytes from the auxiliary normal
stream and signed Z from the vertex flag byte. Each component is divided by
127; the resulting vector is **not normalized**. The known CBFD implementation
transforms the look-at axes into current model-view space, normalizes each axis,
and computes the nonlinear generated coordinate as `(dot(axis, normal)+1)*512`.
The source references are GLideN64's
[`gSP.cpp`](https://github.com/gonetz/GLideN64/blob/master/src/gSP.cpp) and
[`F3DEX2CBFD.cpp`](https://github.com/gonetz/GLideN64/blob/master/src/uCodes/F3DEX2CBFD.cpp).
These are semantic references, not a pin of an emulator executable.

The model-local command stream proves texture generation at these loads. It
does not alone prove the inherited lighting, linear-generation bit or active
look-at vectors. The inspection explicitly selects lighting enabled, nonlinear
generation and canonical view X/Y look-at axes. The native renderer has
conditional lighting setup, so that selection is retained in the artifact's
scope and metadata.

The Blender shader reads `_CBFD_TEXGEN_NORMAL` as a POINT/FLOAT_VECTOR attribute.
It converts native XYZ to Blender `(x,-z,y)`, transforms camera X/Y basis vectors
into object space, normalizes those basis vectors separately, then takes the
dot products. It never substitutes a normalized fragment Normal. Interpolation
of these dot products preserves the vertex operation for this neutral pose.

For each axis, the Blender image coordinate is

```
(dot + 1) * 512 * texture_scale / image_dimension
    - tile_origin_quarter_texels / (4 * image_dimension)
```

Run 20 uses a 32×16 image, S scale 1/32 and T scale 1/64. Runs 21, 31 and 32 use
32×32 images and scale 1/32 on both axes. All four runs have tile origins
`uls=ult=2` and zero tile shifts. Blender's glTF import reverses the glTF V
coordinate; the node output therefore uses the nonflipped T expression above.
Only the image-vector input in the six affected materials changes. Source UVMap
values remain available and unchanged for every face.

## Verification and limits

The worker checks all 309 affected imported corners against their source signed
normal values and native positions plus the authenticated joint translations.
Every affected normal remains nonunit. All original material nodes and all
unaffected material links are preserved. Mesh topology, attributes, UV layers,
vertex weights and neutral rig transforms are fingerprinted before and after
the shader change. The 17 packed PNG byte strings must match source bytes.

The supported worker was exercised with Blender 5.2.1. At the existing
three-quarter and rear inspection views, an independent per-joint model-view
calculation and the shader formula differ by at most `4.10e-8` and `3.36e-8`
in normalized UV coordinates across 309 corners per view. Earlier isolated
32-bit UV-output renders also agreed within raster precision; textured renders
were not pixel identical. Texture filtering and native raster parity are not
claimed. Both supported previews were visually inspected.

Fresh verification uses `--disable-autoexec` and opens the file with scripts
disabled. It rebuilds expected geometry, material node topology, constants and
two-view coordinate results from authenticated inputs before comparing the
saved file. It rejects altered raw source bytes, a changed shader accompanied
by updated artifact hashes, and changed geometry accompanied by updated audit
hashes. Those rejection checks and an existing-output refusal made no output
writes. The file contains no Actions, drivers or text blocks; the worker adds
no handlers. Blender's importer-generated bone display shape is retained and
is distinguished from the single source mesh.

Camera/view-dependent coordinates are supported for this neutral pose. Joint
posing and animated joint rotations are unsupported: a generic point attribute
does not follow the native per-joint normal transform during animation. The
original clips remain in the preserved source glTF. A later animation solution
must prove that transformation explicitly. Native primitive/environment colour,
lighting and gameplay-camera state remain separate questions.

Ignored reproduction and verification artifacts are under
`build/assets/models/reference/resolution-goal-20261002/character66-visibility/`:
`texgen-audit.json`, `fixed-view/`, `blend-prototype/`,
`supported-worker-validated/`, and `worker-boundary-validation/`.

Publication rederives all prepared inputs from the ROM and pinned source files,
freshly verifies the Blend with auto-execution disabled, and compares before/after
source and artifact hashes. A final recheck runs before any gallery write.
Only the existing entry-66 card changes its visible download and thumbnail;
its source record, raw GLB hash, appearance-blocked status and inventory counts
remain intact.

The published artifact SHA-256 is
`cc28779b39b9e962909e51ad2d82e1f6cb7c5e3287a1225bc39e0a3c919c3b98`.
The publication check verifies all 1,531 existing raw GLBs remain byte-identical,
as do the 1,528 unrelated preview files. Two existing empty records still have
no preview. Desktop and mobile checks verify the single Blender link, exact
download/preview hashes, source-name search and unchanged card counts. The
ignored publication proof is `character66-publication.json` at the parent
resolution-goal reference directory.

A later camera-framing check reconstructs the active camera and render framing
before reopening the saved file. It compares camera transforms, orthographic
scale/shifts, sensor fit, clipping, disabled depth of field, render size, pixel
aspect and border/crop settings independently of saved metadata. A copied Blend
with `shift_x=3` and a coherently updated Blend hash is rejected. The canonical
neutral/animated entry-66 and scene-55 files all pass without changes to their
76 combined artifact/source files. Reproducible results are retained under
`build/assets/models/reference/resolution-goal-20261002/camera-framing/`.
