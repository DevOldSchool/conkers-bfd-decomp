# Selected small US multi-function source units

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following small C units with
two or three recovered functions. Subtracting the game-segment base `0x2D4B0`
from each combined-binary boundary gives its range in the US game overlay:

| Source identity | Combined range | Game-overlay range | Recovered US members |
| --- | --- | --- | --- |
| `game_323B0.c` | `0x323B0:0x323E0` | `0x4F00:0x4F30` | `func_15004F00`, `func_15004F10` |
| `game_14D0D0.c` | `0x14D0D0:0x14D110` | `0x11FC20:0x11FC60` | `func_1511FC20`, `func_1511FC2C`, `func_1511FC44` |
| `game_36040.c` | `0x36040:0x360A0` | `0x8B90:0x8BF0` | `func_15008B90`, `func_15008BB0` |
| `game_75BD0.c` | `0x75BD0:0x75C90` | `0x48720:0x487E0` | `func_15048720`, `func_15048758` |
| `game_3F120.c` | `0x3F120:0x3F1F0` | `0x11C70:0x11D40` | `func_15011C70`, `func_15011CA0`, `func_15011CC0` |
| `game_322B0.c` | `0x322B0:0x323B0` | `0x4E00:0x4F00` | `func_15004E00`, `func_15004E80` |
| `game_3F560.c` | `0x3F560:0x3F670` | `0x120B0:0x121C0` | `func_150120B0`, `func_1501214C` |
| `game_122650.c` | `0x122650:0x122760` | `0xF51A0:0xF52B0` | `func_150F51A0`, `func_150F51BC`, `func_150F51E8` |

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Every endpoint already occurs in `config/game/us.yaml`. Each complete range was
checked against the canonical raw US assembly; the top-level `glabel` entries
listed above account for every recovered member, and no indented local label
crosses a source-unit endpoint. These are educated structural boundary
hypotheses based on the upstream map, not original linker-map or symbol-table
evidence.

The upstream `game/done/` directory placement is not imported as completion
evidence. No C implementation, symbol name, type, or comment was copied.
Function matching still requires a US `CURRENT (0)` focused diff.
