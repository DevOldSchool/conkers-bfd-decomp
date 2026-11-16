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

The generated `game_100810.o` has a 0x20-byte `.rodata` section: these 28
payload bytes in this order followed by four zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at
`0x800A09E8` with a 0x20 extent assertion and a 0x1C payload;
`config/data/us.json` records the owner. The alignment bytes span
`0x800A0A04..0x800A0A07` informationally; that word (`40066666`, 2.1f) and the
following `0x800A0A08`/`0x800A0A0C` stay externs of the raw `func_150D3A68`,
and `D_800A0A10`/`D_800A0A14` are externs of other members. The game-data
archive still supplies them. Matching `func_150D3A68` with literals would grow
this pool. The words before `0x800A09E8` (`D_800A09C0` and the two vectors at
`D_800A09D0`/`D_800A09DC`) are read by matched members through externs and are
not owned by this mapping.

The match also corrects two local record shapes. The spawn record passed to
`func_15147A80` is 0x1C bytes: that callee reads `+0xE` and `+0x15` of its
first argument and copies 0x1C bytes from it with `func_10022EC0` (reference
`15147B18`..`15147B20`), so the record keeps a trailing word that this caller
leaves unwritten. `Game100810Link`, the record at `object + 0x98`, grows from
0xC to 0x1C bytes (an `active` byte, two effect handles at `+0xC`/`+0x10` and
two floats at `+0x14`/`+0x18`); `func_150D3360` copies 0x1C bytes into it, and
`func_150D4C2C` already reads the two handles at `+0xC` and `+0x10`.
`func_150D49C0` uses only the unchanged leading fields.
