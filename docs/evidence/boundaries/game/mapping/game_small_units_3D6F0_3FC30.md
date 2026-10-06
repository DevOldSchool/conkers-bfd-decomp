# Selected small US source-unit boundaries from `game_3D6F0.c` through `game_3FC30.c`

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following small C units.
Subtracting the game-segment base `0x2D4B0` from each combined-binary boundary
gives its range in the US game overlay:

| Source identity | Combined range | Game-overlay range | Recovered US member |
| --- | --- | --- | --- |
| `game_3D6F0.c` | `0x3D6F0:0x3D770` | `0x10240:0x102C0` | `func_15010240` |
| `game_3D770.c` | `0x3D770:0x3D780` | `0x102C0:0x102D0` | `func_150102C0` |
| `game_3DB30.c` | `0x3DB30:0x3DB50` | `0x10680:0x106A0` | `func_15010680` |
| `game_3DB50.c` | `0x3DB50:0x3DB60` | `0x106A0:0x106B0` | `func_150106A0` |
| `game_3DB60.c` | `0x3DB60:0x3DB80` | `0x106B0:0x106D0` | `func_150106B0` |
| `game_3DB80.c` | `0x3DB80:0x3DC30` | `0x106D0:0x10780` | `func_150106D0` |
| `game_3E5A0.c` | `0x3E5A0:0x3E620` | `0x110F0:0x11170` | `func_150110F0` |
| `game_3E7E0.c` | `0x3E7E0:0x3E810` | `0x11330:0x11360` | `func_15011330` |
| `game_3E810.c` | `0x3E810:0x3E890` | `0x11360:0x113E0` | `func_15011360` |
| `game_3F0F0.c` | `0x3F0F0:0x3F120` | `0x11C40:0x11C70` | `func_15011C40` |
| `game_3F3D0.c` | `0x3F3D0:0x3F450` | `0x11F20:0x11FA0` | `func_15011F20` |
| `game_3F450.c` | `0x3F450:0x3F4D0` | `0x11FA0:0x12020` | `func_15011FA0` |
| `game_3F4D0.c` | `0x3F4D0:0x3F560` | `0x12020:0x120B0` | `func_15012020` |
| `game_3FBD0.c` | `0x3FBD0:0x3FC20` | `0x12720:0x12770` | `func_15012720` |
| `game_3FC20.c` | `0x3FC20:0x3FC30` | `0x12770:0x12780` | `func_15012770` |
| `game_3FC30.c` | `0x3FC30:0x3FC60` | `0x12780:0x127B0` | `func_15012780` |

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Every endpoint already occurs in `config/game/us.yaml`. Each complete range was
checked against the canonical raw US assembly and contains exactly the single
top-level `glabel` listed above. No indented local label crosses a source-unit
endpoint. Larger intervening source units are deliberately left unregistered.

The upstream `game/done/` directory placement is not imported as completion
evidence. No C implementation, symbol name, type, or comment was copied; this
records only independently checked source-unit boundaries and raw-assembly
membership. Function matching still requires a US `CURRENT (0)` focused diff.
