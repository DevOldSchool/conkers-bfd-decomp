# Remaining US texture consumer research

This note records bounded exclusions after the passing texture batch at
`b6a07200276891d06b4a84f7023a217a8b60daa1`. It adds no reconstructed assets or
matching credit. That batch contains 6,865 textures; its validation is recorded
in [texture reconstruction](us_texture_reconstruction.md).

All addresses below refer to the original US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Runtime resource IDs include the two
empty slots at 1767 and 1768; physical stream ordinals do not.

## Direct loader coverage

A fresh word-aligned J/JAL scan of the checksum-validated CPU intervals returned
by `scripts/rom_span.py` found the following direct calls:

| Target | GAME calls | Main calls | Debugger calls |
| --- | ---: | ---: | ---: |
| `1510D0EC` flat loader | 64 | 0 | 0 |
| `1510CE60` display-list resource resolver | 10 | 0 | 0 |
| `150950D4` CPU texture upload | 5 | 0 | 0 |

There were no J tail calls to these targets. No aligned literal pointers to
these three functions occur in GAME or debugger data. A bounded lexical search
for a matching LUI plus ADDIU/ORI within 32 instructions found no additional
function-address construction leads. This is not proof against arbitrary
computed indirect calls, and the pointer scan does not cover main data.

## Descriptor-only character resources

The complete native display-list regions in models 7, 30, 35 and 62 contain
90 SetTextureImage commands and produce 63 parsed material runs. Every image
command addresses a direct flat resource. None uses texture segments 6, 7,
10 or 11. Thus a missed segmented image command in these models does not explain
these unused descriptor entries:

| Resource | Model / descriptor | Declared dimensions | Payload bytes |
| --- | --- | --- | ---: |
| 944 | 7 / 2; 35 / 13 | 32 by 32 | 1,536 |
| 1938 | 7 / 3; 35 / 14 | 32 by 32 | 1,536 |
| 1973 | 30 / 7 | 44 by 44 | 2,624 |
| 4599 | 62 / 4 | 16 by 32 | 1,216 |
| 7717 | 62 / 3 | 16 by 32 | 1,216 |

This does not exclude another CPU consumer or runtime command mutation. The
sizes and descriptor dimensions alone do not establish an image format.

## Resource 3775 and source-plane offsets

Pointer-table selector 66 identifies descriptor `80091858`: resource 3775,
count 1, flags 0, I4, 64 by 64. Its payload is 4,096 bytes. The reviewed upload
uses 1,024 16-bit transfer words, covering 2,048 bytes.

`15095060` copies the descriptor into the compact upload structure. The upload
at `150951BC..150951D0` can advance its source by twice the transfer count times
argument 4. A value of one would reach a second 2,048-byte plane, but all five
direct upload call sites explicitly pass zero:
`15094FD0`, `15095048`, `150D1970`, `151481B0` and `1517E8DC`.
The pointer-table effect route `1516D738 -> 15142E24 -> 15094FE8` also uses zero.
A second plane therefore needs different consumer or mutation evidence; this
route does not establish one. Nonzero bytes in the tail must not be called
padding merely to obtain a complete contract.

## HUD selectors

`150911F4` loads four resource halfwords from `800D2578..800D257E` at
`15091430`, `15091464`, `15091498` and `150914CC`. Reviewed stores in
`1509093C` choose among these original-ROM values, according to counter
thresholds 480, 960 and 1200:

| Original halfword | Runtime resource | Physical stream | Already selected |
| --- | ---: | ---: | --- |
| `8009025A` | 1937 | 1935 | yes |
| `80090262` | 1946 | 1944 | yes |
| `80090266` | 1942 | 1940 | yes |
| `8009026E` | 3649 | 3647 | yes |
| `80090272` | 3657 | 3655 | yes |

This source-store review does not exclude arbitrary later alias writes.

The three direct callers of `15091534` pass argument 1 as zero, zero and one
at `1509227C`, `15092448` and `15092830`. Its `3350 + argument1` resources are
both already selected.

The timer renderer `150938BC` forms its resource as `4525 + signed remainder
modulo 10`. Even allowing negative timer values, the conservative resource
range is 4516 through 4534. Only 4522, 4523 and 4524 in that range remain
unselected; their payloads are 2,560, 1,440 and 1,536 bytes respectively. None
is a complete instance of the timer model's 16-by-32 IA4 image (256 bytes).
This excludes a new full-payload timer contract without asserting that negative
timers are reachable or that these resources lack other uses.

## Remaining uncertainty

These checks narrow specific consumer hypotheses. They do not prove global
texture exhaustion. Further matches require a verified full-payload storage
contract, including any palette, extra plane, mip level or nonzero tail, and
an exact PNG inverse and fresh compression result. Broader dynamic resource
bindings, later mutations and indirect consumers remain distinct research
questions. Repeating the exclusions above without new evidence is not a new
matching attempt.
