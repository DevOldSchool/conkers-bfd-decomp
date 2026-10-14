# US bank-00 sprite reconstruction

Follow-up: [EOF-bounded compression](us_bounded_compression.md) extends the
selection while preserving the historical validation recorded below.

The reviewed source rebuilds **51 entries, 183 frames and 236,457 stored ROM
bytes** from editable PNGs. Each frame contains an RGBA5551 color plane and a
four-bit intensity plane. Five compressed entries (4, 5, 19, 47, 63), the bank
index and alignment remain uncredited. The decoded sources cover 610,240 bytes;
these do not add a second allocation to native Data totals.

## Original consumer evidence

The checksum-validated US ROM supplies the full registered functions and data
spans recorded in [the independent audit](us_sprite_reconstruction.json).
`1500AC14` resolves bank 00 through `1502B020` and `1502AC88`. The 69 ten-byte
records at `80095CE0` supply frame count, frame byte length and width. Height
is `2 * frame_bytes / (5 * width)`, exactly integral for every selected entry.
`1517BBAC` allocates the complete frame sequence, derives each frame pointer
by that byte stride and writes the corresponding texture bounds. `1517CFC4`
expands the compressed sequence into those buffers.

`1517D7B0` selects the same pointers from `800DD478` using the vertex frame
index. It emits an RGBA16 LoadBlock, an RGBA16 render tile with `2 * width`
byte stride, and an I4 render tile with `width / 2` byte stride at TMEM byte
`2 * width * height`. The second tile has the full frame width and height.
The complete state list at `8008CFA0` disables TLUT; `1510CDB8` changes only
primitive/environment colors. No palette interpretation is inferred from
pixel appearance.

The upload uses DXT `ceil(2048 / (width / 4))` and a zero-stride load tile.
It transfers `width * ceil(5 * height / 4)` 16-bit texels. At 64 by 22 this
reads 64 bytes beyond the frame, but neither validated render plane samples
those bytes. Reconstruction covers only the actual 3,520-byte frame.

## PNG layout

PNG rows follow increasing tile T coordinates. The source preserves every
RGBA5551 component, including the one-bit alpha, in the color PNG and every
four-bit value in a grayscale intensity PNG. These are separate source
planes, not a composited screenshot or a claim about final lighting.

For each byte, the codec reverses both the upload's DXT-dependent exchange
of 32-bit halves and the render tile's odd-row exchange. The I4 row stride
differs from the upload stride, so treating both planes as ordinary linear
storage would be incorrect. A separate forward TMEM simulation checks every
selected decoded byte. This interpretation agrees with the pinned SDK's
`CALC_DXT` definition and paraLLEl-RDP's
[16-bit upload](https://github.com/Themaister/parallel-rdp/blob/1cecd042b2619bc505c12bfdc713808386f2b54d/parallel-rdp/shaders/tmem_update.comp#L297)
and [texture sampling](https://github.com/Themaister/parallel-rdp/blob/1cecd042b2619bc505c12bfdc713808386f2b54d/parallel-rdp/shaders/texture.h#L257).

## Build and accounting

`./conker sprite-assets build` initializes
`build/assets/sprites/us/manifest.json`, two PNGs per frame and a preserved
`backing.bin`. Every subsequent build reads the current PNGs, reconstructs
both native planes and freshly compresses the selected entry using its
reviewed zlib or GNU gzip level. Six selected entries are uncompressed.
Malformed, missing or changed inputs fail without being overwritten.
`./conker sprite-assets recover` first backs up the entire source directory.

Only uncredited ranges come from the backing file. Its hash is checked and
edits are preserved, rather than silently replaced. `ASSETS=1` links the
whole `asset_bank_00.o` from the resulting rebuilt bank. Native report
preparation validates that actual linker object against current inputs,
then compares only the 51 selected entry spans with independent original
ROM targets. The raw remainder keeps the index, padding and five excluded
entries. Total Data allocation is unchanged.

The audit checks fresh encoding of all selected entries, **732 pixel
mutations** across both planes and **20 endpoint mutations** across eight
full code spans and two data spans. Tests cover all five observed dimension
pairs, input preservation/recovery, source races, missing Make prerequisites
and stale actual linker objects. Final full-build and native-report
acceptance is recorded separately below when complete.

## Accepted validation

The complete asset build reproduces all 67,108,864 original US ROM bytes
(SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`) in 96 seconds. The full
Docker suite passes 2,529 tests with eight skips (124.597 seconds in the
runner). Native objdiff, progress and whitespace gates pass. These are
command timings, not total workflow duration.

Matched Data increases by **236,457 bytes** to **60,670,547 / 65,120,512
(93.16657%)**. Complete Data is 60,669,779 bytes (93.16539%). All 10,623
previous asset proofs and 25,503 previous source-file hashes remain
unchanged. Code and the Data denominator are unchanged. Native objdiff has
11,638 units, 10,948 complete, with no compile errors.

Base commit: `094102644c4c2f5aefaa0fc4b609416918f66f58`.
Validated source fingerprint:
`e25753fbf2dce10e99aab28fb7ae24985dde1f05e3e5c64fcbbd198885d2ba06`.
Report SHA-256:
`7bbb7d0d3a40b703a654b92cf5296c54e1d20e1f9b5bbc4c923da66cbe2e4fba`.
The independently audited snapshot was current; the result is local and
has not been published to decomp.dev.
