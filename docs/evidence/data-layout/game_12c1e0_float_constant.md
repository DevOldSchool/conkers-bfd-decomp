# US game_12C1E0 ray epsilon constant

`func_150FF2D4` compares a ray length against a small epsilon. Its raw HI16/LO16 pair in
`asm/nonmatchings/game_12C1E0/func_150FF2D4.s` (`150FF33C`/`150FF340`) addresses the word `0x800A2120`.
No other reference function touches it. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `38D1B717` there, the single-precision value of the
literal `0.0001f` used in the C source. With `extern f32 D_800A2120` the same body scores CURRENT 60 (one `lw a2`
is scheduled early); as a literal the function is `CURRENT (0)`.

The generated `game_12C1E0.o` has 0x10 bytes of `.rodata`: the constant and 12 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A2120` with a 0x10 extent assertion and a
0x4 payload; `config/data/us.json` records the owner. The informational alignment bytes cover `0x800A2124..0x800A212F`,
which hold `401EE979 3F7FBE78 4131999A` and stay externs of the unmatched member `func_150FF474`; the game-data archive
still supplies them. Matching that function with literals would grow this pool. No reference assembly, compiler flag
or verifier change is involved.
