# US game_1E6260 oscillator blend constant

`func_151B9214` eases an oscillator's speed and amplitude toward their targets
with `0.0234f`; the else branch loads the constant once and uses it for both
products. The raw HI16/LO16 pair in
`asm/nonmatchings/game_1E6260/func_151B9214.s` addresses `0x800AA564`. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds big-endian `3CBFB15B` there (0.0234f round
trips). The preceding words (`0x800AA540..0x800AA563`) are referenced by the
unit's still-unmatched `func_151B8DB0` and stay extern symbols; the following
words belong to other units.

The generated `game_1E6260.o` has 0x10 bytes of `.rodata`: the constant and 12
zero alignment bytes, with no data relocations. `func_151B8DB0` remains
`GLOBAL_ASM` and produces no rodata. `config/game/us-rodata.ld` maps it as an
INFO section at `0x800AA564` with a 0x10 extent assertion and a 4-byte payload;
`config/data/us.json` records the owner. No reference assembly, compiler flag
or verifier change is involved.
