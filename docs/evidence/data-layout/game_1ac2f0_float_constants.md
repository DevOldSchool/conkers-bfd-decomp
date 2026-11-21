# US game_1AC2F0 camera clamp and fade constants

`func_1517F814` clamps two projected coordinates to `[-10000, 10000]`. The raw
HI16/LO16 pairs in `asm/nonmatchings/game_1AC2F0/func_1517F814.s` address
`0x800A7280`, `0x800A7284` and `0x800A7288`. The checksum-validated US ROM
(SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`)
holds big-endian `461C4000 C61C4000 C61C4000` there: `10000.0f` and two copies
of `-10000.0f`. IDO emits one pool entry for each use of the literal, which
explains the duplicate.

Originally these three words were the unit's only C literals, mapped as one
INFO placement at `0x800A7280` (0x10 extent, 0xC payload). The split below
replaces that placement. No reference assembly, compiler flag or verifier
change is involved.

## func_151814FC split

`func_151814FC` reads six literals through raw HI16/LO16 pairs addressing
`0x800A7294..0x800A72A8`. The ROM holds `3F666666 3C23D70A 3C1374BC 3B83126F
3D4CCCCD BC1374BC` there: `0.9f`, `0.01f`, `0.009f`, `0.004f`, `0.05f` and
`-0.009f`, which the C writes as literals. The two words between the pools
(`0x800A728C`, `0x800A7290`) still belong to the assembly member
`func_15180580` and keep their extern symbols. The generated object now has
0x30 bytes of `.rodata` (the three clamp words, the six fade words and 12 zero
alignment bytes). `game_1AC2F0.o` joins `GAME_SPLIT_RODATA_OBJS`, and
`scripts/split_game_rodata.py` splits it into `.rodata.1ac2f0_0` (0xC at
`0x800A7280`) and `.rodata.1ac2f0_c` (0x18 at `0x800A7294`), each with an exact
linker size assertion and a base symbol, replacing the single 0x10 placement
and its payload symbol. `config/data/us.json` names both sections. See
[literal sub-pools](game_rodata_literal_sub_pools.md).
