# US game_1CC440 trail bound constant

`func_1519F4F0` expires a trail point when either horizontal coordinate leaves
the `20000.0f` play bound; the constant is loaded once and compared against
`fabsf(x)` and `fabsf(z)`. The raw HI16/LO16 pair in
`asm/nonmatchings/game_1CC440/func_1519F4F0.s` addresses `0x800A8CF0`. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds big-endian `469C4000` there (20000.0f round
trips). Only `func_1519F4F0` references that word. The preceding words
(`0x800A8CE0..0x800A8CEF`) are read by already-compiled siblings through extern
symbols, and the following words (`0x800A8CF4..0x800A8D00`) are referenced by
the unit's still-unmatched `func_1519F7F0` and `func_1519FE6C`, so they stay
extern symbols.

The generated `game_1CC440.o` has 0x10 bytes of `.rodata`: the constant and 12
zero alignment bytes, with no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at `0x800A8CF0` with a 0x10 extent assertion and a
4-byte payload; `config/data/us.json` records the owner. `30.0f` is emitted as
a `lui` immediate and needs no rodata. No reference assembly, compiler flag or
verifier change is involved.
