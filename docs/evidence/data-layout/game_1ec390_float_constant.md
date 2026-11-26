# US game_1EC390 counter placement scale float constant

`func_151BF340` builds the two-digit counter display: one model placed with a copied `Vec3f` position and
an X/Y scale, then one or two digit sprites. Its raw HI16/LO16 pair in
`asm/nonmatchings/game_1EC390/func_151BF340.s` loads the word `0x800AA914` once and stores it to both scale fields of
the placement record. No other reference function touches it. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3E9A1CAD` (`0.30100003f`) at
`0x800AA914`. With the literal the function is `CURRENT (0)`.

The generated `game_1EC390.o` has 0x10 bytes of `.rodata`: the constant and 12 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800AA914` with a 0x10 extent assertion and a
0x4 payload; `config/data/us.json` records the owner. The neighbouring words stay extern reads: `0x800AA910`
(`3FF3D70B`, `1.905f`) is loaded by the same function earlier and stays the extern `D_800AA910`; `0x800AA904..0x800AA90C`
are read by `func_151BF0C8` and `0x800AA918..0x800AA92C` by `func_151BF81C` through their existing externs. The informational alignment bytes `0x800AA918..0x800AA923` do not
describe ROM contents and only the payload is compared. The layout mirrors
[game_BC510 sprite pulse float constants](game_bc510_float_constants.md). No reference assembly, compiler flag or
verifier change is involved.
