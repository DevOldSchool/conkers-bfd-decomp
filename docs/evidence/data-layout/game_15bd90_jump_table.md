# US switch table for game_15BD90

`func_1512FE00` dispatches selectors 1 through 30 through thirty word-sized
jump targets. The raw HI16/LO16 address pair identifies the table at
`0x800A376C` in the separately loaded US game-data archive.

The C switch reaches full registered CURRENT (0). The generated
`build/us/src/game/game_15BD90.o` has a 128-byte `.rodata` section with
thirty `.text` word relocations, 120 payload bytes and eight zero alignment
bytes. Relocated against `func_1512FE00` at `0x1512FE00`, the payload is
`1512FE34 1512FE58 1512FE88 15130214 15130214 15130214 15130214 1512FEB8
1512FEE4 15130214 1512FF1C 1512FF48 1512FF74 1512FFC8 15130214 1512FFA4
15130214 1512FFEC 1513001C 15130214 1513004C 15130074 151300D8 15130108
151300AC 15130138 15130164 15130190 151301C8 15130208`; the `0x15130214`
entries are the shared default return. These 120 bytes equal the
checksum-validated US game-data archive at `0x800A376C` (game-data base
`0x80082B20`), read with `rom_game_data` from
`scripts/verify_game_rodata.py`.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A376C`
as informational data with `SUBALIGN(4)`, an exact 128-byte size assertion
and a 120-byte payload-size symbol, so the verifier compares only the
relocated payload and checks that the alignment bytes are zero. It ends at
`0x800A37EC`, before the `game_15D730` tables at `0x800A3800`. No padding is
added and no verification rule is changed.

The unit's other member, `func_1512E8E0`, remains raw assembly and loads
eleven literals from `D_800A3740` through `D_800A3768`, directly before the
table. Those words lie outside this mapping's payload. Matching that function
in C would place its literals ahead of the table in this object's `.rodata`,
trip the size assertion and require the mapping to move to `0x800A3740`.

Focused matching, source-unit integration and clean batch verification remain
separate required checks.
