# US switch table for game_20BDA0

`func_151E2404` copies a ten-byte record and dispatches the record index 0
through 9 through ten word-sized jump targets. The raw HI16/LO16 address pair
(`0x151E247C`/`0x151E2484`) identifies the table at `0x800AB9BC` in the
separately loaded US game-data archive.

| Selector | Target | Body |
| --- | --- | --- |
| 0 | `0x151E2490` | `record[5] = source[4]` |
| 1, 2 | `0x151E249C` | `record[5..6] = source[0xD..0xE]` |
| 3, 4, 6 | `0x151E24CC` | none (shared tail) |
| 5, 7 | `0x151E24B0` | `record[5] = source[0x12]` |
| 8, 9 | `0x151E24BC` | `record[5] = source[7]`, `record[6] = source[0x13]` |

All ten relocated words were independently compared with the checksum-validated
US ROM using `rom_game_data` from `scripts/verify_game_rodata.py` (game-data base
`0x80082B20`). The object contains a 48-byte `.rodata` section, ten word
relocations against `.text`, 40 payload bytes and eight zero alignment bytes.
The ROM words after the table (`0x40490FD0 0x3FC90FD0` at `0x800AB9E4`) belong
to the following unit, so the alignment bytes are checked in the object only.

The mapping in `config/game/us-rodata.ld` places this section at `0x800AB9BC`
as informational data with `SUBALIGN(4)`, an exact 48-byte size assertion and a
40-byte payload-size symbol. The other `game_20BDA0` members are `GLOBAL_ASM`
and emit no `.rodata`; their tables (`jtbl_800AB960`, `jtbl_800AB978`,
`jtbl_800AB994`) and literals precede this table in ROM. When one of them is
matched, the unit needs a `scripts/split_game_rodata.py` layout instead of this
single placement.

## Dispatch shape

IDO schedules the bound check (`sltiu at,v1,10`) and the index shift
(`sll t5,v1,2`) ahead of ten record-copy loads and stores, leaving only
`beqz at` and its `sb` delay slot before `lui`/`addu`/`lw`/`jr`.
`scripts/candidate_tables.py` accepts this distant form only when the guard
immediately precedes the shift, at most eleven stores, loads, `addu`/`subu`/`or`
or `mflo`/`mfhi` instructions (and the delay slot) separate them from the
branch, none writes the index, guard or shift register, the guard is not in a
delay slot, and no direct edge or table target enters the guarded region.
`tests/test_candidate_tables.py` covers the US words and each rejection.

## Call argument

The raw function never writes `a0` after loading `&D_800E0BE0` and calls
`func_150076A0` with it still live. Every source form without an argument
allocates the pointer to `v1`; passing it reproduces the original `a0`.
`func_150076A0` (game_33990.c) has no other caller and ignores its argument,
so the file-local `void func_150076A0(volatile s8 *)` declaration does not
change the callee's code. Its shared definition keeps `(void)` pending review.
