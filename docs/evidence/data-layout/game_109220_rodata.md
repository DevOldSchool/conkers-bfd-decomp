# US game_109220 switch table and constants

`func_150DBD70` switches on its `u8` argument (cases 0 through 5) and then
fills a large particle record. The raw dispatch (`sltiu at,a0,6`, four stack
stores, `beqz at` with an `or v1,a0,zero` delay slot, `sll t7,a0,2`) loads
`jtbl_800A0C40` through the HI16/LO16 pair at `0x150DBDA8`/`0x150DBDB0`. This
guard is five words before the branch, so `scripts/candidate_tables.py`
needed the wider guard window described in
[scheduled boolean switch bounds](../matching/scheduled_boolean_switch_bounds.md#wider-guard-window).

| Selector | Target |
| --- | --- |
| 0, 5 | `0x150DBDBC` |
| 1-4 | `0x150DC0FC` |

The function's 38 non-`lui` float literals follow the table in use order:
`0x800A0C58..0x800A0CEC` (`-1938.0f`, `40.4f`, `-693.79346f`, ... `2366.0f`,
`1231.0f`, `0.078f`). The literals from `0x800A0CF0` belong to the raw
`func_150DC558`, which still reads them through extern symbols.

All 44 words were compared with the checksum-validated US ROM using
`build/us/manual-attempts/nov02/lit.py` (game-data base `0x80082B20`). Each
relocated table word plus the unit text base `0x150DBD70` equals the ROM
word, and the 38 literal words are byte-identical. The compiled
`game_109220.o` has a 0xB0-byte `.rodata` section: six R_MIPS_32 relocations
against `.text`, then the literals, with no alignment tail.

`config/game/us-rodata.ld` places this section at `0x800A0C40` as
informational data with `SUBALIGN(4)`, an exact 0xB0-byte size assertion and
a 0xB0-byte payload-size symbol. `config/data/us.json` records the owner.
The raw `func_150DC558` emits no `.rodata`.
