# US game_1ED0F0 trace epsilon constant

`func_151C1D5C` repeats a collision trace, stepping past pass-through surfaces by a small epsilon. Its raw
HI16/LO16 pair in `asm/nonmatchings/game_1ED0F0/func_151C1D5C.s` (`151C1DD0`/`151C1DD4`) addresses the word
`0x800AA9C4`. No other reference function touches it. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3DCCCCCD` there, the
single-precision value of the literal `0.1f` used in the C source. With `extern f32 D_800AA9C4` the deferred body
scored CURRENT 2360; as a literal the function is `CURRENT (0)`.

The matching body also declares its ninth parameter `s8` and passes it straight on to
`func_15081690`. The file-local prototype used by the matched caller `func_151C196C` now says
`s8` as well; that caller's 252 instruction words and relocations in the rebuilt `game_1ED0F0.o` are
identical to the build before the change.

The generated `game_1ED0F0.o` has 0x10 bytes of `.rodata`: the constant and 12 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800AA9C4` with a 0x10 extent assertion
and a 0x4 payload; `config/data/us.json` records the owner. The preceding word `0x800AA9C0` (5000.0) stays an
extern read of `func_151C196C`. The informational alignment bytes cover `0x800AA9C8..0x800AA9D3`
(`00000000 00000000 0000006F`), which are not part of the owned payload. No reference assembly, compiler flag or
verifier change is involved.
