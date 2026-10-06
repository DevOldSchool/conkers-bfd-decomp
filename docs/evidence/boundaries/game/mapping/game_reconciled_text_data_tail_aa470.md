# Reconciled callable tail after text-resident data at `0xAA470`

Evidence kind: `structural_analysis`. The raw range
`0xA9C40:0xAA4D0` combines 2,096 bytes of text-resident constants and format
strings with one callable 96-byte function. This review assigns the function
tail separately and classifies `D_150A9C40` as data.

| Source | US range | Bytes | Function | Direct callers |
| --- | --- | ---: | --- | ---: |
| `src/game/game_D7920.c` | `0xAA470:0xAA4D0` | 96 | `func_150AA470` | 7 |

The raw assembly has an explicit `func_150AA470` label at `0xAA470`, and the
next reviewed source unit begins at `0xAA4D0`. Seven `jal func_150AA470`
instructions occur in the already reviewed `0xAA4D0:0xAB1F0` unit. The
function returns at `0xAA4C8`, with its delay slot at `0xAA4CC`; no branch
crosses either endpoint. The range SHA-1 is
`ce75edb015630fc8fa967fc2732d8a80d236ae6f`.

This split prevents the function-only inventory from treating
`D_150A9C40:0xAA470` as executable function coverage. The canonical `data`
subsegment is named `game/data/D_150A9C40` and retains `.text` linker ordering,
which preserves its retail position without claiming C or function progress.
