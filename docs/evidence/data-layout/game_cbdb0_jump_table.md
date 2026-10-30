# US switch table for game_CBDB0

`func_1509ED74` dispatches its query selector 19 through 35 through seventeen
word-sized jump targets. The raw HI16/LO16 address pair (`jtbl_8009F43C_game`,
code offsets `0x9EDBC` and `0x9EDC4`) identifies the table at `0x8009F43C` in
the separately loaded US game-data archive.

| Selector | Target | Selector | Target |
| --- | --- | --- | --- |
| 19 | `0x1509EDD0` | 28 | `0x1509EEF0` |
| 20 | `0x1509EDE4` | 29 | `0x1509EF00` |
| 21 | `0x1509EE10` | 30 | `0x1509EF08` |
| 22 | `0x1509EE6C` | 31 | `0x1509EF10` |
| 23 | `0x1509EE90` | 32 | `0x1509EF18` |
| 24 | `0x1509EEB0` | 33 | `0x1509EF2C` |
| 25 | `0x1509EEB8` | 34 | `0x1509EF68` |
| 26 | `0x1509EED8` | 35 | `0x1509EFC8` |
| 27 | `0x1509EEE0` | | |

All seventeen words were read from the checksum-validated US ROM (normalized
SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`); every target lies
inside `func_1509ED74`. The object contains an 80-byte `.rodata` section with
seventeen word relocations against `.text`, 68 payload bytes and twelve zero
alignment bytes.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009F43C`
as informational data with `SUBALIGN(4)`, an exact 80-byte size assertion and a
68-byte payload-size symbol. The existing verifier compares every relocated
payload byte with the ROM and checks that the alignment bytes are zero. No
padding is added and no verification rule is changed.

The other member, `func_1509E900`, is still `GLOBAL_ASM`; its own table
`jtbl_8009F3F0` (0x8009F3F0 to 0x8009F43C) stays an external reference and is
not owned by this mapping. When that function is matched in C, the unit's
`.rodata` begins with its table, so this mapping must move to `0x8009F3F0` and
its extent assertion must grow. Focused matching, source-unit integration and
clean batch verification remain separate required checks.
