# US game_121A20 streak float constants

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

`func_150F4570`, the streak spawner called by `func_150F4DEC`, loads eight words from `0x800A1A64..0x800A1A83` in
first-use order: `40C90FDB 3E4CCCCD 3DA3D70B 40C90FDB 41AF3959 C12F3959 41AF3959 C12F3959`, the values of
`6.2831855f`, `0.2f`, `0.080000006f`, `6.2831855f`, `21.903002f`, `-10.951501f`, `21.903002f` and `-10.951501f`. With
extern symbols the candidate scored CURRENT 300; with the literals, its byte parameters typed `u8` as the raw `lbu`
homes show (also in the local prototype used by `func_150F4DEC`, which stays `CURRENT (0)`) and the descriptor's
`field69` typed `s8`, the function is `CURRENT (0)`.

The generated `game_121A20.o` has 0x40 bytes of `.rodata`: the `func_150F4570` words at object offset 0, the
`func_150F4DEC` words at object offset 0x20 and 12 zero alignment bytes, with no data relocations. Between the two
ROM ranges lie a zero word at `0x800A1A84` and the doubles `D_800A1A88`/`D_800A1A90` that `func_150F4A38` still reads
through extern symbols; as literals those doubles would be 8-aligned at object offset 0x20 rather than at the ROM's
relative offset 0x24, so they stay extern. `scripts/split_game_rodata.py` therefore cuts the object pool into
`.rodata.121a20_0` (0x20 bytes) and `.rodata.121a20_20` (0x14 bytes), and `config/game/us-rodata.ld` maps them as INFO
sections at `0x800A1A64` and `0x800A1A98` with exact extent assertions and per-range base symbols, as described in
[game rodata literal sub-pools](game_rodata_literal_sub_pools.md). `config/data/us.json` records both owners. No
reference assembly, compiler flag or verifier change is involved.
