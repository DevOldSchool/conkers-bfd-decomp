# US switch table for game_A9D90

`func_1507DF10` dispatches selectors 4 through 9 through six word-sized
jump targets. The raw HI16/LO16 address pair identifies the table at
`0x8009B884` in the separately loaded US game-data archive.

| Selector | Target |
| --- | --- |
| 4 | `0x1507DFBC` |
| 5 | `0x1507DFBC` |
| 6 | `0x1507DF88` |
| 7 | `0x1507DF88` |
| 8 | `0x1507DF58` |
| 9 | `0x1507DF34` |

All six relocated words were independently compared with the checksum-validated
US ROM using `rom_game_data` and `verify_bytes` from
`scripts/verify_game_rodata.py`. The object contains a 32-byte `.rodata` section,
six word relocations, 24 payload bytes, and eight zero alignment bytes.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009B884`
as informational data with `SUBALIGN(4)`, an exact 32-byte size assertion,
and a 24-byte payload-size symbol. The existing verifier compares every
relocated payload byte against the ROM and checks that all alignment bytes are
zero. No padding is added and no verification rule is changed. The unchanged
game-data archive supplies these bytes at runtime.

Without the mapping, linking appends the table at `0x151FA130`, expanding the
code payload from 2,072,880 to 2,072,912 bytes. The only differing words within
the original code span are the table address instructions at offsets `0x7DF20`
and `0x7DF28`. Focused matches, source-unit integration and clean batch
verification remain separate required checks.
