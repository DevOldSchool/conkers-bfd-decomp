# Direct RGBA32 mip-chain preview

Bank `03`, entry `85`, segment `0` is a green hanging canister with 40 faces.
The descriptive gallery name does not claim a recovered gameplay identity.
Its last two faces use flat asset `2733` for the hanging ring. All other faces
already have proven CI8 bindings.

## ROM contract

The draw explicitly selects RGBA32, no TLUT, two cycles, LOD and clamp detail.
Its first cycle blends TEXEL0 and TEXEL1 by LOD fraction in both channels.
The second cycle retains combined RGB and multiplies combined alpha by
ENVIRONMENT. Neither output uses SHADE. The preview shows the base mip;
it does not claim native LOD blending or a recovered runtime environment alpha.

The zero-DXT load is `F3000000 072A7000`: 2,720 bytes from a 2,816-byte payload.
The base image is 32 × 16. Each RGBA32 texel occupies two bytes in each TMEM
bank. The checked chain is:

| Level | Dimensions | TMEM offset per bank | Row stride per bank | Source span |
| --- | --- | ---: | ---: | --- |
| 0 | 32 × 16 | 0 | 64 | 0–2,048 |
| 1 | 16 × 8 | 1,024 | 32 | 2,048–2,560 |
| 2 | 8 × 4 | 1,280 | 16 | 2,560–2,688 |
| 3 | 4 × 2 | 1,344 | 8 | 2,688–2,720 |

Extraction checks every declared tile, mask, shift, stride, non-overlap and
loaded span before decoding. The base uses the existing RGBA32 odd-row
8-byte swap and vertical image orientation. Authored half-texel tile origins
remain part of the UV calculation.

The glTF keeps the original colour bytes in `_SOURCE_COLOR_0` and omits the
unused `COLOR_0` multiplier only for this proven texture-only formula. The
export verifier requires the matching ROM material status, complete render
state, original colour accessor and exact image binding. Other materials
retain the existing colour requirement.

## Verification and limits

A scan across all four supported banks finds exactly one matching run:
`03 / 85 / 0`, material run 3, two faces. Independent byte indexing verifies
all 512 exported RGBA pixels. Numeric checks cover all 40 faces and 120 UV
corners. Source colours remain `(254, 254, 254, 255)` for the four ring vertices.
The export read audit permits ROM and texture inputs and rejects save-state,
trace and other model-export inputs.

Regression checks reject missing tile/scale state, partial render state,
changed formulas, absent or overlapping mip levels, insufficient loads and
payloads, missing source colours and altered texture bindings. Changing lower
mip bytes does not change the base image.

The corrected render resolves the former white rectangle into a hanging ring.
The completed batch passes 5,406 file checks and 797 render cases, with eight
existing incomplete appearance comparisons. The published self-contained GLB
imports into Blender with all 40 faces and four embedded textures, and passes
Khronos validation with zero errors or warnings. All 1,560 previously published
GLB and preview files remain byte-identical.
Native filtering, environment alpha, lighting and gameplay appearance remain
separate comparison work.

Local reproduction evidence is under
`build/assets/models/reference/expansion-20260910-usage-budget/rgba32-mip/`:
`rom-proof.json`, `read-audit-bank03.json`, the isolated `preview-bank03/`,
and the reviewed `0085-00.png`. The batch report is under
`build/assets/models/batch/`.
