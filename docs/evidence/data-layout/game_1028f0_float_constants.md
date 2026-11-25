# US game_1028F0 emitter constants

`func_150D54C8` advances an emitter timer and, while it exceeds 1.0, spawns
flanking particles through `func_15130280`. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1028F0/func_150D54C8.s` load ten per-function rodata
literals in the order IDO emits them:

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800A0A3C` | `40400001` | 3.0000002f | timer rate base |
| `0x800A0A40` | `3C8EFA35` | 0.017453292f | degrees to radians |
| `0x800A0A44` | `403A0C4A` | 2.907f | speed range (hoisted into `$f30`) |
| `0x800A0A48` | `40C00001` | 6.0000005f | speed base, `case 0` |
| `0x800A0A4C` | `40C00001` | 6.0000005f | speed base, `default` |
| `0x800A0A50` | `3F10624E` | 0.564f | wind x factor |
| `0x800A0A54` | `4049FBE8` | 3.1560001f | vertical speed scale |
| `0x800A0A58` | `3F10624E` | 0.564f | wind z factor |
| `0x800A0A5C` | `3E20C49C` | 0.157f | field54 range |
| `0x800A0A60` | `C0071AA0` | -2.111f | field54 base |

The words were read from the checksum-validated US game-data archive (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) through
`scripts/rom_span.py`. No other reference function loads these addresses. The
remaining float operands (8.0f, 1.0f, 0.5f, 180.0f, 35.0f, -35.0f, 364.0f,
111.0f and 0.0f) are built with `lui`/`mtc1` and need no rodata.

The generated `game_1028F0.o` has a 0x30-byte `.rodata` section (0x28 payload,
eight zero alignment bytes) with no data relocations, which
`config/game/us-rodata.ld` maps as the INFO section `.game_rodata_1028f0` at
`0x800A0A3C` with an exact extent assertion. `config/data/us.json` records the
owner.

The unit's ROM pool is wider. `0x800A0A30..0x800A0A3B` holds `0000006C
0000006D 0000006E`, the three particle ids that the still-raw
`func_150D5A6C` copies to its stack, followed after this range by its own
float literals from `0x800A0A64`, and the constants that matched members read
through externs (`D_800A0AB0`..`D_800A0AC8`). The game-data archive still
supplies those words; when `func_150D5A6C` is matched the mapping must widen
to start at `0x800A0A30`.
