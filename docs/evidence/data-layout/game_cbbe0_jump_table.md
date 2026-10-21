# US switch table for game_CBBE0

`func_1509E730` dispatches its `kind` argument 0 through 6 through seven
word-sized jump targets. The raw HI16/LO16 address pair identifies the table
at `0x8009F3D0` in the separately loaded US game-data archive.

| Selector | Target |
| --- | --- |
| 0 | `0x1509E768` |
| 1 | `0x1509E7B0` |
| 2 | `0x1509E780` |
| 3 | `0x1509E7C4` |
| 4 | `0x1509E80C` |
| 5 | `0x1509E798` |
| 6 | `0x1509E85C` |

All seven relocated words were independently compared with the checksum-validated
US ROM using `rom_game_data` from `scripts/verify_game_rodata.py` (game-data base
`0x80082B20`). The object contains a 32-byte `.rodata` section, seven word
relocations against `.text`, 28 payload bytes, and four zero alignment bytes; the
ROM word after the table at `0x8009F3EC` is also zero.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009F3D0`
as informational data with `SUBALIGN(4)`, an exact 32-byte size assertion,
and a 28-byte payload-size symbol. The existing verifier compares every
relocated payload byte against the ROM and checks that all alignment bytes are
zero. No padding is added and no verification rule is changed.

The remaining `game_CBBE0` members are `GLOBAL_ASM` and emit no `.rodata`.
Focused matches, source-unit integration and clean batch verification remain
separate required checks.
