# US switch table for game_CA630

`func_1509D780` dispatches event codes 2 through 41 through a 40-entry jump
table. The raw HI16/LO16 address pair identifies the table at `0x8009F1AC` in
the separately loaded US game-data archive.

The C switch reaches full registered CURRENT (0) when the function returns
`s32` and the null-object path of case 9 returns 0, reproducing the raw
`move v0, zero` that only that path sets; the other cases return without a
value. The earlier `void` candidate scored CURRENT (600). The generated
`build/us/src/game/game_CA630.o` has a 160-byte `.rodata` section with forty
`.text` word relocations and no alignment bytes. Relocated against
`func_1509D780` at `0x1509D780`, unused codes select `1509D8EC`, the shared
return. The 160 bytes equal the checksum-validated US game-data archive at
`0x8009F1AC` (game-data base `0x80082B20`), read with `rom_game_data` from
`scripts/verify_game_rodata.py`.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009F1AC`
as informational data with `SUBALIGN(4)`, an exact 160-byte size assertion
and a 160-byte payload-size symbol. The unit's raw members keep their own
tables outside this payload: `func_1509D180` loads `jtbl_8009F0D4` and the
words `D_8009F1A4` and `D_8009F1A8` directly before this table, and
`func_1509D8FC` loads `jtbl_8009F24C`, which starts where this table ends.
Matching either of them in C would add its rodata to this object, trip the
size assertion and require the mapping to be revisited. No padding is added
and no verification rule is changed.

Focused matching, source-unit integration and clean batch verification remain
separate required checks.
