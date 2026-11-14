# US switch table for game_C3E20

`func_15096D78` dispatches its script-command selector 2 through 27 through
twenty-six word-sized jump targets. The raw HI16/LO16 address pair
(`jtbl_8009DED0_game`, code offsets `0x96DE4` and `0x96DEC`) identifies the
table at `0x8009DED0` in the separately loaded US game-data archive.

| Selector | Target | Selector | Target |
| --- | --- | --- | --- |
| 2 | `0x15097218` | 15 | `0x150972A8` |
| 3 | `0x15097268` | 16 | `0x150972E8` |
| 4 | `0x15096F38` | 17 | `0x15097328` |
| 5 | `0x15096F5C` | 18 | `0x150973A8` |
| 6 | `0x15096F70` | 19 | `0x150973CC` |
| 7 | `0x15097004` | 20 | `0x150973F0` |
| 8 | `0x15096FB0` | 21 | `0x15097458` |
| 9 | `0x1509701C` | 22 | `0x15097498` |
| 10 | `0x1509702C` | 23 | `0x150974A4` |
| 11 | `0x1509711C` | 24 | `0x150974C8` |
| 12 | `0x15096DF8` | 25 | `0x1509752C` |
| 13 | `0x15097584` | 26 | `0x15097558` |
| 14 | `0x15097150` | 27 | `0x15097568` |

All twenty-six words were read from the checksum-validated US ROM (normalized
SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`); every target lies
inside `func_15096D78`. The object contains a 112-byte `.rodata` section with
twenty-six word relocations against `.text`, 104 payload bytes and eight zero
alignment bytes. The preceding unit's pool (`game_C2350`, `0x8009DEC0` to
`0x8009DED0`) ends where this table begins.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009DED0`
as informational data with `SUBALIGN(4)`, an exact 112-byte size assertion and
a 104-byte payload-size symbol. The existing verifier compares every relocated
payload byte with the ROM and checks that the alignment bytes are zero. No
padding is added and no verification rule is changed.

`func_1509759C` is still `GLOBAL_ASM`; its five-entry table `jtbl_8009DF38`
(0x8009DF38 to 0x8009DF4C) and the `D_8009DF4C` constant (`3FC90FDB`, pi/2)
stay external references and are not owned by this mapping. When that function
is matched in C, they follow this table in the unit's `.rodata`, so the extent
assertion must grow. Focused matching, source-unit integration and clean batch
verification remain separate required checks.
