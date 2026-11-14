# US game_179F30 attachment selector switch tables

`func_1514CA80` dispatches through four jump tables. They are contiguous in
the US game-data archive and come first in the unit's `.rodata`:

| Table | Selector | Entries | Size | HI16 / LO16 text offsets |
| --- | --- | --- | --- | --- |
| `0x800A59AC` | `record[4]`, 0..0xBA | 187 | 0x2EC | 0x14 / 0x1C |
| `0x800A5C98` | `D_800BE9F0`, 0..0x35 | 54 | 0xD8 | 0x200 / 0x208 |
| `0x800A5D70` | `record[0x3B]`, 7..25 | 19 | 0x4C | 0x518 / 0x520 |
| `0x800A5DBC` | `record[0x3B]`, 6..15 | 10 | 0x28 | 0x598 / 0x5A0 |

The second dispatch places its guard (`sltiu at,t6,0x36`) five words before
`beqz at`, with four `addiu tN,zero,imm` constants in between and a fifth in
the delay slot. `scripts/candidate_tables.py` accepts this form through the
wider guard window in
[scheduled boolean switch bounds](../matching/scheduled_boolean_switch_bounds.md#wider-guard-window).
The recognizer reads the bounds 187, 54, 19 and 10 from the four raw guards.

Every relocated target in the compiled `game_179F30.o` (unit text base
`0x1514CA80`) equals the checksum-validated US ROM word (game-data base
`0x80082B20`). The tables end at `0x800A5DE4`. The words
`0x800A5DE4..0x800A5DF0` stay extern reads of the matched `func_1514D564`,
so the unit remains split. The object's `.rodata` grows from 0x40 to 0x470
bytes: 0x438 bytes of tables, the 0x10-byte `func_1514D64C` pool and the
0x28-byte `func_1514EA1C` table, with no alignment tail.

`scripts/split_game_rodata.py` now lists six ranges for `game_179F30`. The
four new table sections are `.rodata.179f30_0`, `_2ec`, `_3c4` and `_410`.
The existing pool and table are renamed `_438` and `_448` and keep their
addresses `0x800A5DF4` and `0x800A5E20`. `config/game/us-rodata.ld` maps each
section with an exact size assertion and base symbol, and `config/data/us.json`
records each owner. The
[sub-pool record](game_rodata_literal_sub_pools.md) lists the ranges.
