# US game_173D40 func_15146970 ids and switch table

`func_15146970` switches on its `u32` argument (0 through 8). Case 6 passes a
local `const s32 ids[5]` (`0x401D`..`0x4021`) to `func_150A2AEC`. IDO keeps
that initialiser in `.rodata` ahead of the jump table, so the function owns
`0x800A56D0..0x800A5707`:

| Range | Content |
| --- | --- |
| `0x800A56D0..0x800A56E3` | `0000401D 0000401E 0000401F 00004020 00004021` |
| `0x800A56E4..0x800A5707` | `jtbl_800A56E4`, nine entries |

The jump table entries by selector:

| Selector | Target | Result |
| --- | --- | --- |
| 0 | `0x151469C0` | 0 |
| 1 | `0x151469C8` | 1, or 3/6 when `D_800BE9F0 == 4` |
| 2 | `0x151469B8` | 2 |
| 3 | `0x15146A0C` | 3 |
| 4 | `0x15146A04` | 4 |
| 5 | `0x151469B0` | 5 |
| 6 | `0x15146A14` | 6, or -1 if `func_150A2AEC` fails |
| 7 | `0x151469A8` | 0xF |
| 8 | `0x151469A0` | 0x10 |

The raw guard (`sltiu` five words before `beqz at`) needed the wider guard
window described in
[scheduled boolean switch bounds](../matching/scheduled_boolean_switch_bounds.md#wider-guard-window).
The compiled `game_173D40.o` (unit text base `0x15146890`) has a 0x70-byte
`.rodata` section. Every word of the ids and the relocated table equals the
checksum-validated US ROM word (game-data base `0x80082B20`); the table's
HI16/LO16 pair is at text offsets 0xFC/0x104. The three existing literal
pools follow at object offsets 0x38, 0x50 and 0x58, at unchanged addresses.

`scripts/split_game_rodata.py` now lists five ranges for `game_173D40`. The
new sections are `.rodata.173d40_0` and `.rodata.173d40_14`, and the old `_0`,
`_18` and `_20` pools are renamed `_38`, `_50` and `_58`.
`config/game/us-rodata.ld` maps each section with an exact size assertion and
base symbol, `config/data/us.json` records each owner, and the
[sub-pool record](game_rodata_literal_sub_pools.md) lists the ranges.
