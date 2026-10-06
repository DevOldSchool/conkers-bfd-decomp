# US shared model palette relocation

The previous decoder incorrectly tied palette relocation to the fifth argument
of `func_1510CE60`. The complete register and delay-slot trace shows that the
palette mode bits control it independently. This correction restores texture
bindings across all four model banks without changing model geometry.

## Control flow

The fifth argument at stack offset `0x440` controls creation of a table of
referenced flat IDs. The branch at `0x1510CF78` can skip bitmap bookkeeping,
but both paths reach `0x1510CFB4` and the same palette adjustment:

| Address | Operation | Consequence |
| --- | --- | --- |
| `0x1510CF0C` | `$t1 = encoded_reference >> 22` | Retains the texture mode bits. |
| `0x1510CF6C` | Load fifth argument into `$t9`. | Used for the bookkeeping branch at `0x1510CF78`. |
| `0x1510CFBC` | Delay slot: `$t9 = $t1 & 1`. | Overwrites the fifth-argument value on both branch outcomes. |
| `0x1510CFC4` | Branch-likely if mode is zero. | Nonzero modes annul its delay-slot load of `$t9`. |
| `0x1510CFCC` | Branch if `$t9 == 0`. | Tests mode bit 0, not the fifth argument. |
| `0x1510CFD4–0x1510CFE4` | Add decoded payload length, subtract `0x200`, store pointer. | Mode one selects the trailing 256-entry TLUT. |
| `0x1510CFE8–0x1510CFFC` | Test mode bit 1; add length, subtract `0x20`, store. | Mode two selects the trailing 16-entry TLUT. |

Mode zero retains the loaded payload base. Mode bits 2–5 are reapplied to the
address after this adjustment; they do not change the low-two-bit palette rule.
The direct CI8 survey checks the reviewed US instruction words against ROM.

The earlier watchpoint on flat 3358 stopped at the payload cache store in
`func_1510D0EC`, before these palette instructions execute. It established the
cache pointer, but could not establish the final `FD` palette pointer. The
unsupported exclusion of that texture has been removed.

## Captured checks

The existing runtime material corpus independently confirms pointer offsets and
TLUT hashes for 378 bank-04 mode-one observations and 230 bank-01 mode-two
observations. Examples include:

| Source | Flat ID | Payload bytes | Captured palette minus pixel pointer | Expected |
| --- | ---: | ---: | ---: | ---: |
| Bank 04, entry 4, segment 0, run 1 | 2685 | 1920 | 1408 | `1920 - 512` |
| Bank 01, entry 0, segment 0, run 8 | 4519 | 1504 | 1472 | `1504 - 32` |
| Bank 03, entry 3, segment 0, run 0 | 187 | 2080 | 2048 | `2080 - 32` |

The full pointer audit retains mismatches; runtime-selected or modified images
are not assumed to equal static ROM images. A separate pixel comparison selects
captured CI images with matching output dimensions and ROM-identical palettes.
All 906 selected observations match the corrected exported RGBA pixels:
373 bank-01 CI8, 110 bank-01 CI4, 370 bank-04 CI8 and 53 bank-09 CI8.
This is a texture-image check, not complete RDP combiner or raster parity.

## Generated impact

The corrected static decoder resolves 2,713 bank-04 mode-one runs containing
70,475 source faces, plus 202 bank-03 runs containing 3,000 source faces. One
bank-03 run with two faces still exceeds its available payload and remains
unresolved. Character and attachment CI4 previews now select the trailing
32-byte palette, rather than reading unrelated bytes 512 bytes from the end.

Compared with the previous aggregate previews, 568 models gain texture links on
72,580 source faces. Some runs were already resolved from captured images, so
the aggregate gain differs from the static coverage gain. The correction removes
572 face links whose real CI4 palette is entirely zero-alpha and needs further
combiner handling. It does not preserve an incorrect opaque palette to make a
surface appear textured.

Static texture coverage increases from 4,339 to 7,394 material runs, leaving
2,026 unresolved. All 1,186 model identities and their geometry counts are preserved. Four model
banks and the 528-entry direct CI8 storage set verify byte-identically. The
complete Python suite passes 564 tests, including a CI4 regression with distinct
palettes at the two previously confused offsets. The complete Blender gates
pass for 1,546 main glTFs and 1,469 captured-colour review glTFs. Haybot and the captured
helmet-and-cigar Conker render remain pixel-identical to their previous images.

Reproduction, before/after images, input hashes, runtime pointer observations,
pixel comparisons and validation logs are under
`build/assets/models/reference/palette-mode-correction/`. The coverage report
retains separate static texture, runtime material, placement and attachment
dimensions. Unsupported image layouts, additional character states, complete
scene assembly and native rendering remain open.
