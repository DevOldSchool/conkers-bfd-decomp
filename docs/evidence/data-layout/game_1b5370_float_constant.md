# US game_1B5370 fade wrap constant

`func_151880C0` advances each fade phase and wraps it with `6.2831855f`
(compared and subtracted, one pool word). The raw HI16/LO16 pair in
`asm/nonmatchings/game_1B5370/func_151880C0.s` addresses `0x800A7398`. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds big-endian `40C90FDB` there. The preceding
eight bytes (`3C066406 2837065A`, the `D_800A7390` byte table) stay an extern
symbol; the following words belong to other units.

The generated `game_1B5370.o` has 0x10 bytes of `.rodata`: the constant and 12
zero alignment bytes, with no data relocations. No other C function of the
unit produces rodata. `config/game/us-rodata.ld` maps it as an INFO section at
`0x800A7398` with a 0x10 extent assertion and a 4-byte payload;
`config/data/us.json` records the owner. `progress integrate` rebuilt the
integrated game image byte-identically with this mapping. No reference
assembly, compiler flag or verifier change is involved.
