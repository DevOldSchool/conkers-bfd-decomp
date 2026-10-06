# Next compact US source-unit boundary hypotheses

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following compact C units.
Subtracting the game-segment base `0x2D4B0` gives each range in the US game
overlay:

| Source identity | Combined range | Game-overlay range | Recovered US members |
| --- | --- | --- | --- |
| `game_3D780.c` | `0x3D780:0x3D9A0` | `0x102D0:0x104F0` | `func_150102D0`, `func_150103E0` |
| `game_433F0.c` | `0x433F0:0x43620` | `0x15F40:0x16170` | `func_15015F40`, `func_15015FBC` |
| `game_3BFE0.c` | `0x3BFE0:0x3C230` | `0xEB30:0xED80` | `func_1500EB30`, `func_1500EBC4` |
| `game_3DC30.c` | `0x3DC30:0x3DF10` | `0x10780:0x10A60` | `func_15010780`, `func_15010880`, `func_150109D0` |
| `game_447B0.c` | `0x447B0:0x44A90` | `0x17300:0x175E0` | `func_15017300`, `func_1501748C`, `func_15017498`, `func_150174C0`, `func_15017578` |
| `game_33660.c` | `0x33660:0x33990` | `0x61B0:0x64E0` | `func_150061B0`, `func_15006234` |
| `game_362B0.c` | `0x362B0:0x36600` | `0x8E00:0x9150` | `func_15008E00`, `func_15008E10` |
| `game_3F820.c` | `0x3F820:0x3FBD0` | `0x12370:0x12720` | `func_15012370`, `func_15012470`, `func_150124A0` |

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
