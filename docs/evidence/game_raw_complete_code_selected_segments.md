# Complete US code-selected raw segments

Evidence kind: `structural_analysis`. These three existing raw-map segments are
complete working source families supported by exact function-address selection,
internal calls, and cross-version preservation. Generic source names derive
from retail-ROM offsets; all functions remain raw assembly.

The raw assembly index and independent US function CSV agree on every entry and
span. The segment endpoints are 16-byte aligned and no conditional branch
crosses them.

| Source | US range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/game/game_1188E0.c` | `0xEB430:0xEBEC0` | 5 | 2,704 | `eea218b5207cac9dc402fa3d08bfffb99f8a6cfe` |
| `src/game/game_13F9D0.c` | `0x112520:0x1150B0` | 22 | 11,152 | `44456aa6efefd7e60b267acf5c8b3e199b5b61f6` |
| `src/game/game_1E73B0.c` | `0x1B9F00:0x1BC370` | 12 | 9,328 | `9c206db048c323fd99f9cc81afb563ca3cca8c7d` |

## `0xEB430:0xEBEC0`

Code at `0x106B0:0x106C0` constructs opening `func_150EB430` and stores it to
live callback slot `0x800E0930`. The opening calls local `func_150EB484`, which
calls closing `func_150EBC80`. Owned word `0x80088EA0` independently selects
middle `func_150EB614`. The remaining controller is enclosed by these two
selector-backed paths inside the complete raw segment.

## `0x112520:0x1150B0`

This range is a preserved state/render family. Internal links include
`func_151135C4` -> `func_151137D4`, `func_1511473C` ->
`func_15114348`, and `func_1511490C` -> `func_151148A8`.
`func_15114D24` constructs local `func_15114CC4` at
`0x114EBC:0x114EC8` and passes it to a factory; `func_15114F04` constructs
the same pointer at `0x114F20:0x114F30` for a second registration call.

Eighteen of the 22 functions correlate strongly and in order with the debug
beta. Thirteen correlate with ECTS, eight strongly. The two exact callback uses,
local call chains, preserved order, and complete aligned segment establish the
working boundary.

## `0x1B9F00:0x1BC370`

Owned word `0x80089C34` selects `func_151BA084`. Local
`func_151BB0E0` is constructed at `0x1BB054:0x1BB05C`,
`0x1BB3B0:0x1BB3E4`, and `0x1BB4B4:0x1BB4E8` and passed as a callback to
the relevant factories. The later routines form a second internal chain:
`func_151BB61C` and `func_151BBA9C` both call `func_151BBEE4` and
`func_151BBFBC`.

Seven members correlate with the debug beta, five strongly, and four retain
ECTS candidates. The selections and local chains cover the early, middle, and
late portions of the exact complete raw segment.
