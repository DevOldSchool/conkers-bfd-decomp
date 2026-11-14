# US game_121A20 rain streak float constants

`func_150F4DEC` accumulates a spawn budget, then emits pairs of streak endpoints around the camera yaw through
`func_150F4570`. Its raw HI16/LO16 pairs in `asm/nonmatchings/game_121A20/func_150F4DEC.s` address the words
0x800A1A98..0x800A1AAB in first-use order. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3D50E561 3E1CAC09 3F360B61 43BE8000
3D99999A` there: the single-precision values of `0.051000003f`, `0.15300001f`, `0.7111111f`, `381.0f` and `0.075f`.

The `381.0f` word comes from the integer literal `381` multiplying the `f32` random value: IDO converts the
constant at compile time and loads it from rodata once, before the loop, for both endpoint radii. `254.0f`, `212.0f`,
`-133.0f`, `180.0f`, `10.0f`, `5.0f` and `1.0f` are built with `lui`. The scale factor `0.075f` is loaded once for
the multiply and the add. With extern symbols the candidate scored CURRENT 961; with the literals the function is
`CURRENT (0)`.

The generated `game_121A20.o` has 0x20 bytes of `.rodata`: the 0x14-byte payload and 12 zero alignment bytes, with
no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A1A98` with a 0x20 extent
assertion and a 0x14 payload; `config/data/us.json` records the owner. The preceding words 0x800A1A64..0x800A1A97
stay extern reads of the unmatched `func_150F4570` and of the double constants `D_800A1A88`/`D_800A1A90` loaded by
another member, so the pool starts at 0x800A1A98, which is 8-aligned. The alignment bytes cover 0x800A1AAC..0x800A1AB7;
they do not describe ROM contents and only the payload is compared. Converting the earlier members' constants to
literals would place them ahead of this pool and requires a literal-pool split as described in
[game rodata literal sub-pools](game_rodata_literal_sub_pools.md). No reference assembly, compiler flag or verifier
change is involved.
