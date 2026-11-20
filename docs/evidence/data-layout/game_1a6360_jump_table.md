# US switch table for game_1A6360

`func_15179008` advances the animated emission controller and dispatches its state
`D_800DD446` (0 through 4) through five word-sized jump targets. The raw HI16/LO16
address pair (`151790D8`/`151790E0`) identifies `jtbl_800A71F0_game` in the separately
loaded US game-data archive (ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`).

| State | Target |
| --- | --- |
| 0 | `0x151790EC` |
| 1 | `0x151791D0` |
| 2 | `0x151792C4` |
| 3 | `0x1517936C` |
| 4 | `0x15179430` |

All five words were checked against the ROM (`151790EC 151791D0 151792C4 1517936C
15179430` at `0x800A71F0..0x800A7203`). The compiler emits them as text-relative
`R_MIPS_32` entries, 0x14 payload bytes and twelve zero alignment bytes in a 0x20-byte
`.rodata` section; no other function in the unit produces rodata. `config/game/us-rodata.ld`
maps `game_1A6360.o(.rodata)` to `0x800A71F0` as an informational section with
`SUBALIGN(4)`, an exact 0x20-byte size assertion and a 0x14-byte payload-size symbol,
and `config/data/us.json` records the owner. The alignment bytes fall at
`0x800A7204..0x800A720F`, over `0.88889f` and `-10000.0f`, which the compiled
`func_151797B0` and `func_15179B14` still read through the extern symbols
`D_800A7204` and `D_800A7208`; they do not describe ROM contents and only the payload
is compared. No reference assembly, compiler flag or verifier change is involved.
