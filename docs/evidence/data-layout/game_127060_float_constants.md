# US game_127060 burst and transform float constants

`func_150FB188` stores the same per-function rodata constant `D_800A1DC0` into two transform fields before calling `func_15157DEC`. With the extern symbol IDO allocates the function differently (CURRENT 654); the `0.3f` literal reproduces the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3E99999A` (0.3) at 0x800A1DC0, followed by zero words.

`func_150F9BB0` spawns a burst owner, two sparks and two glows. Its raw HI16/LO16 pairs in `asm/nonmatchings/game_127060/func_150F9BB0.s` address 13 words at 0x800A1D60..0x800A1D93 in first-use order:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A1D60` | `4170B96F` | 15.045272f |
| `0x800A1D64` | `40BBC3D6` | 5.8676558f |
| `0x800A1D68` | `4141C87A` | 12.111444f |
| `0x800A1D6C` | `3ECAD752` | 0.396174f |
| `0x800A1D70` | `3DD58454` | 0.1042563f |
| `0x800A1D74` | `3F050D7E` | 0.5197371f |
| `0x800A1D78` | `3EB026C8` | 0.34404588f |
| `0x800A1D7C` | `434F8000` | 207.5f |
| `0x800A1D80` | `42493333` | 50.3f |
| `0x800A1D84` | `41F73333` | 30.9f |
| `0x800A1D88` | `3DCCCCCD` | 0.1f |
| `0x800A1D8C` | `3F333333` | 0.7f |
| `0x800A1D90` | `358637BD` | 0.000001f |

`0.5f`, `160.0f`, `95.0f`, `100.0f` and `1.0f` are built with `lui`. The raw function was never matched before; with these literals and local spark, glow and event records it is `CURRENT (0)`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_127060.o` has 0x40 bytes of `.rodata` with no data relocations: the `func_150F9BB0` words at object offset 0, the `func_150FB188` word at object offset 0x34 and 8 zero alignment bytes. Between the two ROM ranges lie `0x800A1D94..0x800A1DBF` (`3FA72B03` .. `3E3851EC`), read through externs by other members (`D_800A1D94`, `D_800A1DB8`, `D_800A1DBC`) and raw functions; the game-data archive still supplies them. `scripts/split_game_rodata.py` therefore cuts the object pool into `.rodata.127060_0` (0x34 bytes) and `.rodata.127060_34` (0x4 bytes), and `config/game/us-rodata.ld` maps them as INFO sections at `0x800A1D60` and `0x800A1DC0` with exact extent assertions and per-range base symbols, as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md). `config/data/us.json` records both owners. No reference assembly, compiler flag or verifier change is involved.
