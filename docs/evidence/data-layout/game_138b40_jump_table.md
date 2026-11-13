# US switch table for game_138B40

`func_1510B9D0` dispatches the scene selector `D_800BE9F0` through
`switch (D_800BE9F0)` with cases `0x13`, `0x14`, `0x1A`, `0x33` and `0x35`.
IDO subtracts the lowest case (`addiu t2,t1,-19`), bounds the index with
`sltiu at,t2,35` and loads the target through the HI16/LO16 pair at
`0x1510BB38`/`0x1510BB40`, which identifies the table at `0x800A2C2C` in the
separately loaded US game-data archive.

| Selector | Target | Body |
| --- | --- | --- |
| `0x13` | `0x1510BB6C` | `gdl = func_150DFBD0(gdl)` |
| `0x14` | `0x1510BB4C` | `gdl = func_150C8600(gdl)` |
| `0x1A` | `0x1510BB5C` | `gdl = func_15100464(gdl)` |
| `0x33` | `0x1510BB8C` | `gdl = func_150D765C(gdl)` |
| `0x35` | `0x1510BB7C` | `gdl = func_150CF5E8(gdl)` |
| other `0x13`-`0x35` | `0x1510BB98` | none (switch exit) |

All thirty-five relocated words were independently compared with the
checksum-validated US ROM using `build/us/manual-attempts/nov02/lit.py`
(game-data base `0x80082B20`): each object word plus the unit text base
`0x1510B690` equals the ROM word, with thirty entries pointing at the shared
exit. The object contains a 144-byte `.rodata` section, thirty-five word
relocations against `.text`, 140 payload bytes and four zero alignment bytes.
The ROM word at `0x800A2CB8` is also zero, but only the payload is checked
against ROM; the literal `0x38C90FDB` at `0x800A2CC0` belongs to a following
unit.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A2C2C`
as informational data with `SUBALIGN(4)`, an exact 144-byte size assertion and
a 140-byte payload-size symbol. Every other `game_138B40` member is C and
emits no `.rodata`, so the table is the object's whole read-only section.
