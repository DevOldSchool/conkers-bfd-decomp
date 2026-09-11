# US direct RGBA16 mipmap previews

Bank `04 / 0035` uses four RGBA16 mip chains, flat assets 1116–1119. The
preview exporter validates the complete declared chain and exports its
32 × 32 base image. Distance-dependent native mip blending remains outside
the glTF preview.

## Native contract

The runs use explicit OtherMode `EF192C3F / 0C192230`: two cycles, LOD enabled,
clamped detail and no texture lookup table. `D7002002 / FFFFFFFF` selects base
tile zero and four lower levels. The first combiner cycle interpolates TEXEL0
and TEXEL1 by LOD fraction; the second applies shade, environment and primitive
colour. The first cycle's alpha follows the same interpolation and the second
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
`01`: 329 faces across eight material runs. Other parts in the bundle retain
unresolved mode metadata where their state does not satisfy this contract.

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
