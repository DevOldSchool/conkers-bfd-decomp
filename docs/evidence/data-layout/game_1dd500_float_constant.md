# US game_1DD500 quarter-turn constant

`func_151B14AC` builds a rotated quad and offsets its angle by a quarter turn. Its raw HI16/LO16 pair in
`asm/nonmatchings/game_1DD500/func_151B14AC.s` (`151B15C0`/`151B15C4`) addresses the word `0x800AA2FC`.
No other reference function touches it. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3FC90FDB` there, the single-precision value of the
literal `1.5707964f` (pi / 2) used in the C source. With `extern f32 D_800AA2FC` the same body scores CURRENT 330
(the `0.25f` constant is scheduled before the limit load); as a literal the function is `CURRENT (0)`.

The generated `game_1DD500.o` has 0x10 bytes of `.rodata`: the constant and 12 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800AA2FC` with a 0x10 extent assertion and a
0x4 payload; `config/data/us.json` records the owner. The informational alignment bytes cover `0x800AA300..0x800AA30B`,
which belong to the next unit's unmatched `func_151B1B34` (game_1DEF60) and are still supplied by the game-data
archive. No reference assembly, compiler flag or verifier change is involved.
