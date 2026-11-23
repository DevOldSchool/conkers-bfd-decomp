# US game_61D10 display float constants

The unit's rodata is a nine-word literal pool at 0x80097D40..0x80097D63. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds:

| Address | Word | Value | Use |
| --- | --- | --- | --- |
| 0x80097D40 | `45FFFF00` | `8191.875f` | `func_15034860`, default scale when `unk_201` is zero |
| 0x80097D44 | `43360B61` | `182.04445f` | `func_15034860`, `unk_201` scale factor |
| 0x80097D48 | `3B808081` | `1.0f / 255.0f` | `func_15034860`, first value |
| 0x80097D4C | `477FFF00` | `65535.0f` | `func_15034860`, second value |
| 0x80097D50 | `3B808081` | `1.0f / 255.0f` | `func_15034860`, second value |
| 0x80097D54 | `45FFFF00` | `8191.875f` | `func_15034860`, default scale when `unk_208` is zero |
| 0x80097D58 | `43360B61` | `182.04445f` | `func_15034860`, `unk_208` scale factor |
| 0x80097D5C | `3B808081` | `1.0f / 255.0f` | `func_15034860`, third value |
| 0x80097D60 | `3A480190` | `0.00076296274f` | `func_15034EB4` |

IDO emits one pool entry per literal occurrence in source order, so the repeated values are separate words. Both
functions are `CURRENT (0)` with the literals; `func_15034EB4` previously read the last word as the extern
`D_80097D60`. The `0.0f` comparison in `func_15034860` is built with `mtc1 $zero` and takes no pool word.

The generated `game_61D10.o` has 0x30 bytes of `.rodata`: the 0x24-byte payload followed by 0xC zero alignment
bytes. `config/game/us-rodata.ld` maps it as an INFO section at `0x80097D40` with a 0x30 extent assertion and a 0x24
payload; `config/data/us.json` records the owner. The alignment bytes fall at 0x80097D64..0x80097D6F, which are zero
in ROM and referenced by no function; the next unit's pool (`game_623D0`) starts at 0x80097D70. No reference
assembly, compiler flag or verifier change is involved.
