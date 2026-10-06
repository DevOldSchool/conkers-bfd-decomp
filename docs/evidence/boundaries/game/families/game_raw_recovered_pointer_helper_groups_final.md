# Further recovered US pointer/helper source group

Evidence kind: `structural_analysis`. This review records one further complete
pointer/helper group found in still-raw US game-overlay text. Its generic
source name derives from the retail-ROM offset; all functions remain raw
assembly.

The raw reference and independent US function CSV agree on every entry and
span. Each outer endpoint is 16-byte aligned, no conditional branch crosses an
endpoint, and every member is selected by owned game data or participates in a
direct call between members of its range.

| Source | US range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/game/game_1FEA80.c` | `0x1D15D0:0x1D22B0` | 6 | 3,296 | `24b4382460bca11445a3e8998be513d68acd9309` |

The group has selections for five of six members at `0x8008A280`,
`0x8008A29C`, `0x8008A2EC`, `0x8008A33C`, and `0x8008A38C`. The two closing
wrappers call the sole unselected local helper `func_151D223C`. Four members
retain debug-beta correlations, two strong. The selections span one compact,
ordered owned-data area and stop before the next unrelated raw function.

Beta correlations support entry identity only. The complete owned selections,
local calls, exact spans, and aligned endpoints provide the boundary evidence.

## Reconciled range at `0x178750:0x178E50`

This 1,792-byte range contains a complete nine-entry pointer/helper family.
The independent US CSV identified the eight-byte `func_151787A4` at
`0x1787A4`, selected by `0x8008CB6C`; the initial raw assembly index had folded
those words into the preceding entry. Explicit raw-map splits at `0x1787A4`
and `0x1787AC` regenerate the independent `func_151787A4` body as exactly
`jr $ra; nop` and make raw and CSV membership agree at nine functions.

Four members are selected by owned data, five local edges connect the family,
and four of six mapped debug-beta members are strong. The range SHA-1 is
`041527227a7e78dee65229ad47a7a53de08dd634`.
