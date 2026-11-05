# US game_1E37D0 record intensity constant

`func_151B6420` scales a record's elapsed time by `0.49400002f` to get its
intensity. The raw HI16/LO16 pair in
`asm/nonmatchings/game_1E37D0/func_151B6420.s` addresses `0x800AA470`. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds big-endian `3EFCED92` there. `0.494f`
encodes as `3EFCED91`, so the literal is spelled `0.49400002f`, which round
trips to the ROM word. The following words (`0x800AA474..0x800AA487`) are
referenced by the unit's still-unmatched `GLOBAL_ASM` functions
(`func_151B65D4`, `func_151B7144`, `func_151B7328`, `func_151B7998`) and stay
extern symbols; the preceding words belong to other units.

The generated `game_1E37D0.o` has 0x10 bytes of `.rodata`: the constant and 12
zero alignment bytes, with no data relocations. No other C function of the
unit produces rodata. `config/game/us-rodata.ld` maps it as an INFO section at
`0x800AA470` with a 0x10 extent assertion and a 4-byte payload;
`config/data/us.json` records the owner. No reference assembly, compiler flag
or verifier change is involved.
