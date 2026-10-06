# US direct intensity model textures

Model previews now select ROM-backed IA8, IA16, I4 and I8 base images when the
draw provides a complete transfer and render-tile contract. This resolves
139 previously unlinked material runs on 1,954 source and drawable faces across
45 models. Bank 04 accounts for 138 runs and 1,944 faces; bank 09 entry 431
accounts for one IA16 run and ten faces. Both the main and captured-colour
preview corpora receive these gains.

## Source contract

The pixel reference must use mode zero and a known flat asset. `FD700000`
selects a 16-bit IA transfer and `FD900000` a 16-bit intensity transfer. The
render tile independently establishes the effective IA8, IA16, I4 or I8 format.
Palette lookup must be explicitly disabled; a storage PNG cannot override
missing or incompatible draw state.

The decoder requires a zero-origin, zero-DXT `LoadBlock`, a known load tile at
TMEM origin zero with the matching transfer format/size, and a render tile at
the same origin. The packed row must be eight-byte aligned and exactly match
the render tile's stride. Odd I4 widths remain unresolved. The complete image
must fit the loaded bytes, and the complete transfer must fit the ROM payload
and 4 KiB of TMEM. Following mip levels or padding are preserved in the source
and excluded from the selected base PNG.

The shared native encoder exchanges four-byte halves of each eight-byte group
on odd rows and flips image rows for the existing export UV convention. IA8
expands separate four-bit intensity and alpha values; IA16 retains separate
eight-bit values. I4 and I8 repeat intensity into RGB and alpha.

Only one- or two-cycle draws referencing TEXEL0 without TEXEL1 are admitted.
Transparent materials additionally require one-cycle operation and the exact
TEXEL0-times-SHADE alpha formula in both selector banks. Opaque materials retain
their source opaque mode. Missing state, other alpha formulas, unsupported row
conversion and incomplete transfers remain explicitly unresolved.

This proves image selection and decoding. It does not establish complete
native primitive/environment colour, lighting, filtering, LOD or raster parity.
Those material limitations remain recorded by the exporter and coverage report.

## Verification

The exact pre-change extractor and the new selector agree on every previously
selected image. No existing links are removed or existing image selections
changed. The new source-face coverage is:

| Format | Source faces gaining a texture |
| --- | ---: |
| IA8 | 473 |
| IA16 | 44 |
| I4 | 427 |
| I8 | 1,010 |

The regenerated corpora preserve model identities, source/drawable face counts,
UV counts, joints, animation records, poses, runtime material observations and
scene placements. Only 114 glTF dependency fingerprints change; the other
2,901 remain identical, including all character and composition exports.

Four new regression tests cover the four formats' actual RGBA values, distinct
alpha values, odd-row swaps, full and prefix loads, invalid source/load/lookup
state, stride and TMEM bounds, unsupported combiners, and exported blend versus
opaque state. All 605 Python tests pass. Python compilation and scoped
whitespace checks also pass.

The batch validator checks all four ROM banks byte-identically and validates
all 3,015 glTFs through Khronos and Blender. It performs only 114 fresh glTF
checks and Blender imports, reusing the other 2,901 file results. Main evidence
retains 1,546 files, 3,084 meshes, 399,102 polygons and 2,621 Actions; the
captured-colour corpus retains 1,469 files, 2,993 meshes, 370,598 polygons and
2,621 Actions.

Twenty-five newly comparable IA8 observations match the captured texture
pixels exactly. All previously matching observations remain matching. Across
the three catalogs there are 1,949 passed and 1,170 incomplete comparisons,
with no failures. These are potentially overlapping observations, not distinct
textures. The additional captured matches cover IA8; this pass does not claim
new captured-pixel evidence for I4, I8 or IA16. Source selection is checked
against captured memory, while both paths share the native PNG encoder.

Canonical static texture coverage rises from 8,202 to 8,341 resolved runs;
1,079 remain missing and 170 do not require textures. Runtime-observation
coverage remains a separate dimension.

Four saved pre-change render cases cover IA8, IA16, combined I4/I8 scenery and
the bank-09 attachment. They extend the standard validation configuration to
nineteen cases. Their reference images remain unchanged when running
`./conker model-assets validate`; differences require interpretation and do not
automatically become new baselines.

The nineteen render comparisons report fourteen unchanged images and five
differences: the four intensity cases and the existing scene-24 segment-2
case. Only those five renders run again. Before/after inspection confirms the
expected texture and alpha changes: cave surfaces gain rock/floor detail, solid
web planes gain their cutout image, the IA16 strip gains its alpha pattern,
and the bank-09 sheet gains its translucent gradient. Scene 24's existing black
source enclosure remains visible and unresolved. The five changed images stay
in the review report against preserved references, with the inspection notes
recorded in `verification-summary.json`; native appearance is still incomplete.

Source snapshots, before manifests and renders, command logs, source-selection
comparisons and export-preservation evidence are under
`build/assets/models/reference/direct-intensity-images/integration/`.
