# US game_115F30 effect constants

`func_150E8B1C` reads three float constants. The raw HI16/LO16 pairs in
`asm/nonmatchings/game_115F30/func_150E8B1C.s` address `0x800A1384`,
`0x800A1388` and `0x800A138C`. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
big-endian `3F85F40A 3EA25D8D 4A45C100` there, reproduced by `1.04651f`,
`0.31712f` and `3240000.0f`. With extern symbols IDO assigned different float
registers; as literals the function matches.

`func_150E8D5C` spawns spinning billboards around its owner. It loads eight words from `0x800A1390..0x800A13AF`,
which hold `3F785879 40C90FDB 4568F000 47C34580 3727C5AC 43EB8000 C49B4000 3C23D70A` in the same ROM: `0.9701f`
(the spin rate), `6.2831855f` (loaded once for both random angles), `3727.0f`, `99979.0f`, `0.00001f`, `471.0f`,
`-1242.0f` and `0.01f`. `59.0f`, `80.0f` and `20.0f` are built with `lui`. With extern symbols the candidate scored
CURRENT 6055; with the literals, the descriptor's `flags58` typed `u32` and the `func_15130374` prototype taking
`void *` as its definition in `game_15D730.c` does, the function is `CURRENT (0)`. Its words directly follow the
`func_150E8B1C` pool in source order.

`func_150E9178` accumulates a spawn budget, walks a weighted region list and spawns a sprite at a sampled
point when it lies within range of a reference position. Its raw HI16/LO16 pairs address `0x800A13B8..0x800A13C7`,
which hold `47C34FF3 3EA0C5EB 3E45E0B5 49EF4200` in the same ROM: `99999.9f`, `0.31401f`, `0.19324f` and the squared
range `1960000.0f`. With extern symbols the candidate scored CURRENT 585; with the literals the function is
`CURRENT (0)`.

The generated `game_115F30.o` has 0x40 bytes of `.rodata`: the three `func_150E8B1C` and eight `func_150E8D5C` words
at object offset 0, the four `func_150E9178` words at object offset 0x2C and four zero alignment bytes, with no data
relocations. The words `0x800A13B0`/`0x800A13B4` between the two pools belong to the matched `func_150E90DC`, which
keeps its extern symbols, so the unit is split as described in
[game rodata literal sub-pools](game_rodata_literal_sub_pools.md): `scripts/split_game_rodata.py` cuts the object
pool into `.rodata.115f30_0` (0x2C bytes) and `.rodata.115f30_2c` (0x10 bytes), and `config/game/us-rodata.ld` maps
them as INFO sections at `0x800A1384` and `0x800A13B8` with exact extent assertions and per-range base symbols.
`config/data/us.json` records both owners. The earlier matched member reads `0x800A137C` and `0x800A1380`, and
`func_150E93DC` reads `0x800A13C8` onward, through extern symbols outside these mappings. The mappings sit after the
`game_114B80` sections. No reference assembly, compiler flag or verifier change is involved.
