# US switch table for game_B21B0

`func_150859AC` dispatches selectors 0 through 6 through seven word-sized
jump targets. The raw HI16/LO16 address pair identifies the table at
`0x8009D9A0` in the separately loaded US game-data archive.

| Selector | Target |
| --- | --- |
| 0 | `0x150859F8` |
| 1 | `0x15085A10` |
| 2 | `0x15085A2C` |
| 3 | `0x15085A48` |
| 4 | `0x15085A64` |
| 5 | `0x15085A80` |
| 6 | `0x15085A9C` |

All seven relocated words were independently compared with the checksum-validated
US ROM using `rom_game_data` from `scripts/verify_game_rodata.py` (game-data base
`0x80082B20`). The object contains a 32-byte `.rodata` section, seven word
relocations against `.text`, 28 payload bytes, and four zero alignment bytes; the
ROM word after the table at `0x8009D9BC` is also zero.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009D9A0`
as informational data with `SUBALIGN(4)`, an exact 32-byte size assertion,
and a 28-byte payload-size symbol. The existing verifier compares every
relocated payload byte against the ROM and checks that all alignment bytes are
zero. No padding is added and no verification rule is changed. The unchanged
game-data archive supplies these bytes at runtime.

The matched function takes `s16` selector arguments (raw `sll`/`sra` prologue
on both registers); the remaining `game_B21B0` members are `GLOBAL_ASM` and emit
no `.rodata`. Focused matches, source-unit integration and clean batch
verification remain separate required checks.
