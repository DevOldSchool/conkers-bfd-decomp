# US direct RGBA16 mipmap previews

Bank `04 / 0035` uses four RGBA16 mip chains, flat assets 1116–1119. The
preview exporter validates the complete declared chain and exports its
32 × 32 base image. Distance-dependent native mip blending remains outside
the glTF preview.

## Native contract

The runs use explicit OtherMode `EF192C3F / 0C192230`: two cycles, LOD enabled,
clamped detail and no texture lookup table. `D7002002 / FFFFFFFF` selects base
tile zero and four lower levels. The first combiner cycle interpolates TEXEL0
and TEXEL1 by LOD fraction. The second accepts either `(COMBINED -
ENVIRONMENT) * SHADE + PRIMITIVE` or `COMBINED * SHADE` colour. The first cycle's alpha follows the same interpolation and the second
multiplies it by shade alpha. At LOD fraction zero, the selected source is the
base image with its stored RGBA5551 alpha.

| Level | Dimensions | TMEM byte offset | Row stride | End of required span |
| ---: | --- | ---: | ---: | ---: |
| 0 | 32 × 32 | 0 | 64 | 2,048 |
| 1 | 16 × 16 | 2,048 | 32 | 2,560 |
| 2 | 8 × 8 | 2,560 | 16 | 2,688 |
| 3 | 4 × 4 | 2,688 | 8 | 2,720 |
| 4 | 2 × 2 | 2,720 | 8 | 2,736 |

The native LoadBlock uses RGBA16 at TMEM zero with zero DXT. Each payload has
2,752 bytes. Every level has the expected format, halving masks and matching
S/T shifts, with no overlap or read beyond the declared load or 4 KiB TMEM.
Lower-level data and padding remain in the original payload.

## Supported exports

The contract binds 234 faces in bank `04 / 0035 / 00` and 95 faces in segment
`01`. The standard shaded formula also binds segments `08`, `10`, `11`, `12`
and `13`: 34 faces across eight runs. Both formulas retain identical source
RGBA5551 image bytes and the same complete load/mipmap gates. The covered
material runs total 363 faces across 16 runs. Other material state remains
unresolved where it does not satisfy the contract.

Tests preserve the base image and palette-independent RGBA alpha, verify that
lower-level image changes do not alter the selected base, and reject missing
levels, wrong shifts, overlapping spans, short payloads, changed combiner or
OtherMode, and unsupported load conversion. Independent ROM-to-PNG checks cover
all 4,096 pixels of the four base images.

Local source audits and pixel checks are under
`build/assets/models/reference/expansion-20260910-usage-budget/odd-width/`;
that isolated export includes both this contract and the odd-width CI4 decoder.
Use the normal model validation and packed-GLB gates for publication. Dynamic
colour state, native filtering and complete scene appearance remain separate
verification work.

The shaded formula is checked with three focused tests covering both accepted
formulas, pixel identity, missing levels, changed alpha formulas, partial
OtherMode and short payloads. Its five model exports and four independently
decoded RGBA5551 base images are included in
`build/assets/models/reference/callback-cohort-20260912/`. The dark surface
panels use descriptive labels; their scene placement and secondary-pass
appearance are not established by this texture proof.
