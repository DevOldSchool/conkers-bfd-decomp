# US game_AC030 search-radius constant

`func_1507FFD8` scans three target groups for the nearest visible target and
starts each comparison with an initial squared-distance limit loaded from
`D_8009BD04`, a per-function rodata literal reached through a HI16/LO16 pair.

The checksum-validated US game-data archive contains big-endian `49742400`
(1000000.0) at `0x8009BD04`. ROM SHA1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base `0x80082B20`.
With the extern symbol the function scores CURRENT 340; the `1000000.0f`
literal reproduces the raw function (CURRENT 0).

The generated `game_AC030.o` has rodata `49742400000000000000000000000000`: the
constant followed by twelve zero alignment bytes, with no data relocations.
The ROM words at `0x8009BD08` and `0x8009BD0C` are also zero. No matched C
function in the unit produces rodata.

The other members still reference earlier unit data as externals that this
mapping does not own: `D_8009BBF0` (used by matched C), the
`func_1507F640` switch table `jtbl_8009BBFC` and its constants `D_8009BCFC`
(0.01f) and `D_8009BD00` (0.1f). They all precede `0x8009BD04`, so there is no
overlap. When `func_1507F640` is matched in C, its table and constants precede
this literal in the unit's `.rodata`, so this mapping must move and its extent
assertion must grow.

The INFO mapping retains linked bytes for verification without appending to
the code-only payload. A size assertion detects unexpected constant-pool
growth. No reference assembly, compiler flag or verifier changes are involved.
Focused matching, source-unit integration and clean batch verification remain
separate required checks.
