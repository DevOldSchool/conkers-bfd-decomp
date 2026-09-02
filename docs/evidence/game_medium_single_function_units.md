# Medium US single-function source units

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following medium-sized
single-function C units. Subtracting the game-segment base `0x2D4B0` gives each
range in the US game overlay:

| Source identity | Combined range | Game-overlay range | Recovered US member |
| --- | --- | --- | --- |
| `game_3D5C0.c` | `0x3D5C0:0x3D6F0` | `0x10110:0x10240` | `func_15010110` |
| `game_F20A0.c` | `0xF20A0:0xF21D0` | `0xC4BF0:0xC4D20` | `func_150C4BF0` |
| `game_3E460.c` | `0x3E460:0x3E5A0` | `0x10FB0:0x110F0` | `func_15010FB0` |
| `game_43620.c` | `0x43620:0x43760` | `0x16170:0x162B0` | `func_15016170` |
| `game_75950.c` | `0x75950:0x75A90` | `0x484A0:0x485E0` | `func_150484A0` |
| `game_3B920.c` | `0x3B920:0x3BA70` | `0xE470:0xE5C0` | `func_1500E470` |
| `game_D5500.c` | `0xD5500:0xD5650` | `0xA8050:0xA81A0` | `func_150A8050` |
| `game_768F0.c` | `0x768F0:0x76A60` | `0x49440:0x495B0` | `func_15049440` |
| `game_2DDF0.c` | `0x2DDF0:0x2DF70` | `0x940:0xAC0` | `func_15000940` |
| `game_3F670.c` | `0x3F670:0x3F820` | `0x121C0:0x12370` | `func_150121C0` |
| `game_3E620.c` | `0x3E620:0x3E7E0` | `0x11170:0x11330` | `func_15011170` |
| `game_360A0.c` | `0x360A0:0x36280` | `0x8BF0:0x8DD0` | `func_15008BF0` |
| `game/entrypoint.c` | `0x34CE0:0x34ED0` | `0x7830:0x7A20` | `func_15007830` |
| `game_32490.c` | `0x32490:0x32720` | `0x4FE0:0x5270` | `func_15004FE0` |
| `game_123FB0.c` | `0x123FB0:0x124260` | `0xF6B00:0xF6DB0` | `func_150F6B00` |
| `game_3C3D0.c` | `0x3C3D0:0x3C6C0` | `0xEF20:0xF210` | `func_1500EF20` |

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Every endpoint already occurs in `config/game/us.yaml`. Each complete range was
checked against the canonical raw US assembly and contains exactly the single
top-level `glabel` listed above. No indented local label crosses a source-unit
endpoint. These are educated structural boundary hypotheses based on the
upstream map, not original linker-map or symbol-table evidence.

The upstream `game/done/` directory placement is not imported as completion
evidence. No C implementation, symbol name, type, or comment was copied.
Function matching still requires a US `CURRENT (0)` focused diff.
