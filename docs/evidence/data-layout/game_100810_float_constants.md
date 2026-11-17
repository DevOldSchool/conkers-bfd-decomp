# US game_100810 spawn effect constants

`func_150D3360` spawns an owner object and two attached effects (a glow and a
spark). Its raw function loads seven per-function rodata literals through
HI16/LO16 pairs, in the order IDO emits them:

| Address | Word | Literal | Load site |
| --- | --- | --- | --- |
| `0x800A09E8` | `3D4CCCCD` | 0.05f | `150D366C` (glow values 4 and 5) |
| `0x800A09EC` | `3EE66666` | 0.45f | `150D3684` |
| `0x800A09F0` | `3E99999A` | 0.3f | `150D368C` |
| `0x800A09F4` | `358637BD` | 0.000001f | `150D3694` |
| `0x800A09F8` | `3DCCCCCD` | 0.1f | `150D3854` (spark values 4 and 5) |
| `0x800A09FC` | `3F4CCCCD` | 0.8f | `150D3860` |
| `0x800A0A00` | `358637BD` | 0.000001f | `150D3868` |

The words were read from the checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`). No
other reference function loads these addresses. The remaining float operands
(200.0f, 40.0f, 20.0f, 500.0f, 100.0f, 45.0f, 25.5f, 1.0f) are built with
`lui` and need no rodata.

`func_150D4D58` emits a burst of particles around a yaw. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_100810/func_150D4D58.s` address five words in
first-use order:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A0A18` | `43360B61` | 182.04445f (yaw scale) |
| `0x800A0A1C` | `3F4E147C` | 0.80500007f (speed base) |
| `0x800A0A20` | `3E645A1D` | 0.223f (speed range) |
| `0x800A0A24` | `3F256042` | 0.646f |
| `0x800A0A28` | `BF4B4396` | -0.794f |

With extern symbols its deferred candidate scored CURRENT 2653; with these
literals and `arg3` typed `u8` (the raw passes the low byte on), the function
is `CURRENT (0)`. `233.0f`, `199.0f`, `10.0f`, `5.0f` and `1.0f` are built
with `lui`.

The generated `game_100810.o` has a 0x30-byte `.rodata` section with no data
relocations: the seven `func_150D3360` words at object offset 0 and the five
`func_150D4D58` words at object offset 0x1C. Between the two ROM ranges lie
`0x800A0A04..0x800A0A17`: `40066666 3E4CCCCD 3EB33334` (2.1f, 0.2f,
0.35000002f), externs of the raw `func_150D3A68`, and `D_800A0A10`
(`3C888889`) and `D_800A0A14` (`3F266667`), externs of matched members. The
game-data archive still supplies them. `scripts/split_game_rodata.py`
therefore cuts the object pool into `.rodata.100810_0` (0x1C bytes) and
`.rodata.100810_1c` (0x14 bytes), and `config/game/us-rodata.ld` maps them as
INFO sections at `0x800A09E8` and `0x800A0A18` with exact extent assertions
and per-range base symbols, as described in
[game rodata literal sub-pools](game_rodata_literal_sub_pools.md).
`config/data/us.json` records both owners. The word after the second range,
`0x800A0A2C`, is zero. The words before `0x800A09E8` (`D_800A09C0` and the
two vectors at `D_800A09D0`/`D_800A09DC`) are read by matched members through
externs and are not owned by this mapping.

The match also corrects two local record shapes. The spawn record passed to
`func_15147A80` is 0x1C bytes: that callee reads `+0xE` and `+0x15` of its
first argument and copies 0x1C bytes from it with `func_10022EC0` (reference
`15147B18`..`15147B20`), so the record keeps a trailing word that this caller
leaves unwritten. `Game100810Link`, the record at `object + 0x98`, grows from
0xC to 0x1C bytes (an `active` byte, two effect handles at `+0xC`/`+0x10` and
two floats at `+0x14`/`+0x18`); `func_150D3360` copies 0x1C bytes into it, and
`func_150D4C2C` already reads the two handles at `+0xC` and `+0x10`.
`func_150D49C0` uses only the unchanged leading fields.
