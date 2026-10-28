# US switch table for game_1BFCB0

`func_151928B0` tests the byte at offset 4 of its record. Values 0 through 4
dispatch through a five-entry jump table, value `0x53` is handled by a
separate compare and every other value returns zero. The raw HI16/LO16
address pair identifies the table at `0x800A8160` in the separately loaded
US game-data archive.

The C switch reaches full registered CURRENT (0) once the default case
assigns the zero result explicitly; the earlier candidate initialized the
result at its declaration and scored CURRENT (265). The generated
`build/us/src/game/game_1BFCB0.o` has a 32-byte `.rodata` section with five
`.text` word relocations, 20 payload bytes and twelve zero alignment bytes.
Relocated against `func_15192800` at `0x15192800`, all five entries are
`151928F4`, the shared body for values 0 through 4. These 20 bytes equal the
checksum-validated US game-data archive at `0x800A8160` (game-data base
`0x80082B20`), read with `rom_game_data` from
`scripts/verify_game_rodata.py`.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A8160`
as informational data with `SUBALIGN(4)`, an exact 32-byte size assertion
and a 20-byte payload-size symbol, so the verifier compares only the
relocated payload and checks that the alignment bytes are zero. The table
starts exactly where the owned `game_1BF090` payload ends
([game_1BF090 literal pool](game_1bf090_literal_pool.md)); that section's
twelve zero alignment bytes span this address range but are not compared
against ROM. The section ends before the `game_1C1150` sections at
`0x800A8258`. No padding is added and no verification rule is changed.

Focused matching, source-unit integration and clean batch verification remain
separate required checks.
