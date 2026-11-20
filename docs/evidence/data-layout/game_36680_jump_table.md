# US switch table for game_36680

`func_15009334` handles a level point by its action type (`type >> 2`) and
dispatches types 9 through 24 through sixteen word-sized jump targets. The raw
HI16/LO16 address pair (`1500937C`/`15009384`) identifies `jtbl_80095B78_game`
in the separately loaded US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`).

| Type | Target | Type | Target |
| --- | --- | --- | --- |
| 9 | `0x15009390` | 17 | `0x150095C8` |
| 10 | `0x15009390` | 18 | `0x150095C8` |
| 11 | `0x150095C8` | 19 | `0x150095C8` |
| 12 | `0x150095C8` | 20 | `0x150095C8` |
| 13 | `0x150095C8` | 21 | `0x150095C8` |
| 14 | `0x150095C8` | 22 | `0x150095C8` |
| 15 | `0x15009538` | 23 | `0x150095C8` |
| 16 | `0x15009390` | 24 | `0x15009584` |

`0x150095C8` is the shared default. All sixteen words at
`0x80095B78..0x80095BB7` were checked against the checksum-validated US ROM.
The compiler emits them as text-relative `R_MIPS_32` entries in a 0x40-byte
`.rodata` section with no alignment bytes; no other compiled function in the
unit produces rodata. The words before (`D_80095B70`, `D_80095B74`) and the
float constants from `0x80095BB8` stay extern reads in other members.
`config/game/us-rodata.ld` maps `game_36680.o(.rodata)` to `0x80095B78` as an
informational section with `SUBALIGN(4)`, an exact 0x40-byte size assertion
and a 0x40-byte payload-size symbol, and `config/data/us.json` records the
owner. No reference assembly, compiler flag or verifier change is involved.
