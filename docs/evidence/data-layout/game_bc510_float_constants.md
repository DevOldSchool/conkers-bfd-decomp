# US game_BC510 sprite pulse float constants

`func_15090630` draws the active entries of `D_800D2460` in two passes. In the first pass each entry in state 1 or 2
is stretched by a wave value: width `size * (0.2f * wave + 1.0f)` and height `size * (-0.2f * wave + 1.0f)`. Its raw
HI16/LO16 pairs in `asm/nonmatchings/game_BC510/func_15090630.s` load the words `0x8009DD20` and `0x8009DD24` once,
before the entry loop. No other reference function touches them. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `BE4CCCCD` (`-0.2f`) at `0x8009DD20` and
`3E4CCCCD` (`0.2f`) at `0x8009DD24`; `1.0f` is built with `lui`. With the two literals the function is `CURRENT (0)`.

The generated `game_BC510.o` has 0x10 bytes of `.rodata`: the two constants in ROM order and 8 zero alignment bytes,
with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x8009DD20` with a 0x10 extent
assertion and a 0x8 payload; `config/data/us.json` records the owner. The neighbouring words belong to raw members of
the same unit and stay extern reads: `0x8009DD1C` (`344.7f`) is loaded by `func_150900F0` and `0x8009DD28` (`0.02f`) by
`func_1509093C`. The informational alignment bytes `0x8009DD28..0x8009DD2F` do not describe ROM contents and only the
payload is compared. Converting `func_150900F0`'s constant to a literal would place it ahead of this pair in the object
and requires a literal-pool split as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md). No
reference assembly, compiler flag or verifier change is involved.
