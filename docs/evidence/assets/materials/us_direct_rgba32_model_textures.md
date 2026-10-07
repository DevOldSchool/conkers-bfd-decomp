# US direct RGBA32 model textures

ROM-backed model previews now decode RGBA32 images through the same pixel
layout used by the captured helmet straps and front panel. This removes the
blanket rejection of native storage images when the individual draw provides
the necessary image, load, tile and lookup state.

## Source contract

The pixel binding must be mode zero with image command `FD180000`. The render
tile must explicitly select RGBA32, and the recorded other-mode command must
disable palette lookup. Unknown lookup state remains unresolved.

The decoder requires a zero-origin, zero-DXT `LoadBlock`, a known load tile at
TMEM origin zero, and a render tile at the same origin. RGBA32 uses paired TMEM
banks: the render stride counts two bytes per texel, while source storage uses
four. Image widths must be divisible by four. Odd rows exchange the eight-byte
halves of each sixteen-byte group. The complete base image must fit the loaded
bytes; the complete transfer must fit the ROM payload and 4 KiB of TMEM.

A larger transfer may contain subsequent mip levels or padding. Those bytes
remain in the source and are excluded from the selected base PNG. A combiner
must reference only TEXEL0, or use the already established trilinear base-image
formula with a second tile. Missing combiner state and other multitexture
formulas stay unresolved.

For static RGBA32 materials without a runtime observation, the glTF exporter now
uses the source filter and alpha/blend state. It retains the colour-expression
classification in `staticMaterialPreview`. Primitive/environment constants,
lighting, native LOD interpolation and RDP coverage/raster behaviour are not
proved by decoding the image. Unsupported colour expressions remain marked.

## Verification

All 49 captured RGBA32 observations match the ROM-backed result pixel-for-pixel:
43 in the aggregate material catalog and six in the character-draw catalog.
Every captured pixel payload hash matches the ROM, and image dimensions agree;
there are no exclusions. This verifies source selection against captured
memory. The runtime and static paths share the native PNG encoder, so this is
not an independent proof of the N64 rasterizer.

Three new regressions cover full and prefix loads, eight-byte row swaps,
preserved alpha, invalid lookup/load/stride state, and static blend-state export.
The complete Python suite passes 571 tests. All four model banks reconstruct
byte-identically, and Python compilation and scoped whitespace checks pass.

The refreshed aggregate previews add 272 texture links on 4,414 source faces
across 134 models:

| Bank | Models gaining links | Source faces gaining links |
| --- | ---: | ---: |
| 01 | 19 | 419 |
| 03 | 19 | 206 |
| 04 | 58 | 2,937 |
| 09 | 38 | 852 |

No existing image changes and no texture links are removed. Static coverage
now resolves 8,202 material runs, with 1,218 missing and 170 not requiring a
texture. Runtime observation remains a separate dimension.

All 1,186 model identities and 222,842 source faces are preserved, as are scene
placements and composition geometry. The complete Blender evidence covers
1,546 main glTFs and 1,469 captured-colour review glTFs. The final pass reimports
182 changed main files and 187 changed review files; prior results are retained
only for identical file fingerprints. Haybot and the captured Conker body with
its cigar and helmet retain identical rendered RGBA pixels.

The later [face-culling investigation](us_model_face_culling.md) identifies the
scene-24 segment-2 enclosure as twelve inward-facing black source triangles.
The source remains preserved, and correct scene assembly and complete appearance
are still unverified. Other native image formats and inherited runtime state
remain open.

Before manifests/images, source snapshots, comparison results, regeneration
scripts, renders and verification logs are under
`build/assets/models/reference/direct-native-images/`. The machine-readable
audit is `audit.json`; current coverage is `build/assets/models/us-coverage.json`.
