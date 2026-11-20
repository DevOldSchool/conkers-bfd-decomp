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

## func_151B7998 split (round-29)

`func_151B7998` loads `1198.0f` through its raw HI16/LO16 pair at
`151B79F8`/`151B7A00`, addressing `0x800AA484` (ROM `4495C000`); no other
reference function reads that word. The four words between the two constants
(`0x800AA474..0x800AA483`: `0.003722f`, `4.409548f`, `1.056747f`, `1700.0f`)
are still read through extern symbols by `func_151B65D4`, `func_151B7144` and
`func_151B7328`, so the constants cannot share one contiguous placement. The
object `.rodata` keeps its 0x10 extent: `0.49400002f` at offset 0,
`1198.0f` at offset 4 (the function follows `func_151B6420` in text) and 8
zero alignment bytes. `game_1E37D0.o` joins `GAME_SPLIT_RODATA_OBJS`, and
`scripts/split_game_rodata.py` splits it into `.rodata.1e37d0_0` (0x4 at
`0x800AA470`) and `.rodata.1e37d0_4` (0x4 at `0x800AA484`), each with an exact
linker size assertion and a base symbol, replacing the single 0x10 placement
and its payload symbol; `config/data/us.json` names both sections. The literal
sites are bound by the splitter from their LO16 addends; no text or reference
assembly changes.
