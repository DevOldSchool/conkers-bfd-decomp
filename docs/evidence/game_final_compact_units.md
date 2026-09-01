# Additional compact US source-unit boundary hypotheses

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following compact C units.
Subtracting the game-segment base `0x2D4B0` gives each range in the US game
overlay:

| Source identity | Combined range | Game-overlay range | Recovered US members |
| --- | --- | --- | --- |
| `game_DAE50.c` | `0xDAE50:0xDAFA0` | `0xAD9A0:0xADAF0` | `func_150AD9A0`, `func_150ADA20`, `func_150ADA68`, `func_150ADACC` |
| `game_75E60.c` | `0x75E60:0x75FC0` | `0x489B0:0x48B10` | `func_150489B0`, `func_15048A40`, `func_15048A70`, `func_15048AD0` |
| `game_21D5F0.c` | `0x21D5F0:0x21D800` | `0x1F0140:0x1F0350` | `func_151F0140`, `func_151F01E0` |

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Every endpoint already occurs in `config/game/us.yaml`. Each complete range was
checked against the canonical raw US assembly; the top-level `glabel` entries
listed above account for every recovered member, and no indented local label
crosses a source-unit endpoint. These are educated structural boundary
hypotheses based on the upstream map, not original linker-map or symbol-table
evidence.

No upstream C implementation, type, or comment was copied. Function matching
still requires a US `CURRENT (0)` focused diff.
