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
words `D_8009F1A4` and `D_8009F1A8` directly before this table. Matching it in
C would add its rodata to this object, trip the size assertion and require the
mapping to be revisited. The `func_1509D8FC` table, which starts where this
table ends, is covered by the section below. No padding is added
and no verification rule is changed.

Focused matching, source-unit integration and clean batch verification remain
separate required checks.

## func_1509D8FC table

`func_1509D8FC` is a `switch (arg0)` over codes 11 through 52. Its raw dispatch
is `sltiu $at,$t6,0x2A` at `1509D910`, then `lui`/`lw` of `jtbl_8009F24C_game`
at `1509D91C`/`1509D924` (unit text offsets 0x79C/0x7A4). The bound is 42 and
the table is 42 words at `0x8009F24C..0x8009F2F3`, starting where the
`func_1509D780` table ends. The checksum-validated ROM words are:

`1509DB08 1509DB08 1509DB08 1509DB08 1509DBAC 1509DBAC 1509DB94 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DAC0 1509DA68 1509DA3C 1509DA14 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509D9BC 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509D9A0 1509DBAC 1509DBAC 1509DBAC 1509DBAC 1509D960 1509DBAC 1509D930`

The object `.rodata` grows from 0xA0 to 0x150 bytes: the unchanged 0xA0-byte
table, the new 0xA8-byte table at object offset 0xA0, and 8 zero alignment
bytes. Every relocated word of both tables differs from its ROM word by exactly
0x1509D180, the unit text base (`[0x9D180, c, game/game_CA630]`). The mapping
keeps base `0x8009F1AC`; its section assertion is now 0x150 and the payload
size 0x148. The ROM words at `0x8009F2F4..0x8009F2FF` are zero.

Like `func_1509D780`, the function returns `s32`: the out-of-range path of case
0x1C returns 1 (the raw `li v0,1`) and every other path returns without a
value. A `void` function loses that `li` (CURRENT 605), and a trailing
`return 0;` scores 825. An earlier zero candidate padded the frame with an
oversized `s8 first[8]`; the accepted source has `s8 first[4]` and two used
`s32` locals, `index` (case 0x1C) and `kind` (cases 0xB..0xE).
