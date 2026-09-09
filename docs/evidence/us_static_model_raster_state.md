# US static texture alpha and filter state

The exporter applied stored ROM other-mode alpha/filter state only to direct
RGBA32 images. Other linked formats used the generic glTF `MASK` / 0.5 alpha
cutoff even when an explicit source command requested blending or opaque
rendering. The state belongs to the rasterizer and is independent of image
storage format.

`encode_gltf` now uses the existing other-mode translation for every linked
texture when the material has explicit static state and no selected runtime
material. A runtime material still takes precedence. Unknown static state
retains the previous fallback. The glTF evidence retains `source: ROM` and
`nativeRasterParity: unverified`; colour and lighting are separate inputs.

The translation reads literal `EF` other-mode words. Local SDK definitions in
`lib/ultralib/include/PR/gbi.h` establish point filtering, alpha comparison,
translucent Z mode, coverage-times-alpha and force-blend flags. Mapping these
to glTF `OPAQUE`, `MASK` and `BLEND` remains an approximation of RDP blending
and coverage, not a native raster implementation.

## Visor evidence

Bank-01 entry 130 source material run 52 covers 28 faces. Its stored words are
`EF18AC3F 04D049D8`; all 84 source corner alpha values are 178. Two resolved
captured variants independently contain the same other-mode words and select
`BLEND`. Both use the 32-by-32 CI8 image for flat texture 1920, PNG SHA-1
`ae457bd36b74a153ffecd4d68502471538de60f6`.

The old mask threshold treated alpha 178/255 as opaque. The corrected preview
preserves its roughly 70% opacity. Visual inspection confirms that the neutral
visor is translucent; the task-local Save-Game-26 composition additionally
contains the captured face through the
[selected-part material correction](us_selected_part_model_materials.md).

## Corpus effect and preservation

| Bank | Models gaining explicit state | Models with changed alpha mode | Drawable faces MASK to BLEND | Drawable faces MASK to OPAQUE |
| --- | ---: | ---: | ---: | ---: |
| 01 | 23 | 23 | 689 | 0 |
| 03 | 39 | 37 | 84 | 1,138 |
| 04 | 561 | 531 | 16,067 | 91,000 |
| 09 | 9 | 9 | 28 | 150 |
| Total | 632 | 600 | 16,868 | 92,288 |

Explicit static-state evidence is added to 4,687 materials covering 120,698
drawable faces in the primary model exports. Alpha modes change on 3,880
materials. The remaining affected materials already used the correct mask
mode. Applicable filters in this corpus agree with the former bilinear
fallback, so no filter value changes here.

A normalized glTF comparison checks all 3,015 files, excluding only the
intended alpha/filter/evidence fields and resolving sampler deduplication by
image URI and wrap modes. Every binary buffer hash and all other geometry,
scene, material and image values are preserved. No texture is redrawn or
substituted. Of the existing review PNGs, only the neutral entry-130 image
(11,646 pixels) and scene-24 segment-2 diagnostic (2,491 pixels) change in
decoded RGBA comparisons. Haybot, Tediz and the captured posed characters
remain unchanged by this static-state correction.

Ignored evidence and reproduction scripts are under
`build/assets/models/reference/static-texture-raster-state/`, including
`visor-evidence.json`, `raster-audit.json`, `bank-state-counts.json`,
`image-comparison.json`, source/output snapshots and generation logs.

## Validation and remaining limits

Tests cover RGBA16, RGBA32, CI4, CI8, IA8 and I8, point filtering, explicit
opaque state, unknown-state fallback and runtime precedence. All 120 focused
model tests and the full 580-test Python suite pass. Changed Python scripts
compile. All four source banks rebuild byte-identically: 1,186 model records,
281,237 vertices, 222,842 faces and 6,805,424 decoded bytes.

The regenerated Blender evidence covers 1,546 main glTFs / 3,088 meshes /
399,102 polygons / 2,621 Actions and 1,469 separate captured-colour review
glTFs / 2,997 meshes / 370,598 polygons / 2,621 Actions. Every changed input is
reimported; retained validation requires an identical per-file fingerprint.

Static source manifests were also refreshed to incorporate earlier texture
tile and UV corrections. Bank 01 now reports 66,001 source UV coordinates;
the four-bank total is 285,852. Source model identities and binary payloads
are preserved. This metadata refresh does not establish new runtime hits.
Regenerating all three material catalogs against the refreshed source manifests
produces byte-identical catalogs; their existing previews remain current.
Coverage was regenerated after this check. Scoped asset whitespace checks and
separate checks of the new evidence files pass.

Native combiner equations, lighting, coverage, filtering/mip transitions,
inherited state and complete scene assembly still have separate gaps. The
scene-24 image remains an isolated component diagnostic. Import success and
unchanged reference pixels do not establish complete visual parity.
