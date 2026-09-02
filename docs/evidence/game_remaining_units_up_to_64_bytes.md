# Selected remaining US source units up to 64 bytes

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following small C units.
Subtracting the game-segment base `0x2D4B0` from each combined-binary boundary
gives its range in the US game overlay:

| Source identity | Combined range | Game-overlay range | Recovered US member |
| --- | --- | --- | --- |
| `game_32720.c` | `0x32720:0x32740` | `0x5270:0x5290` | `func_15005270` |
| `game_33620.c` | `0x33620:0x33660` | `0x6170:0x61B0` | `func_15006170` |
| `game_35CF0.c` | `0x35CF0:0x35D20` | `0x8840:0x8870` | `func_15008840` |
| `game_35E80.c` | `0x35E80:0x35EC0` | `0x89D0:0x8A10` | `func_150089D0` |
| `game_36280.c` | `0x36280:0x362B0` | `0x8DD0:0x8E00` | `func_15008DD0` |
| `game_49D10.c` | `0x49D10:0x49D20` | `0x1C860:0x1C870` | `func_1501C860` |
| `game_49D20.c` | `0x49D20:0x49D30` | `0x1C870:0x1C880` | `func_1501C870` |
| `game_77A90.c` | `0x77A90:0x77AD0` | `0x4A5E0:0x4A620` | `func_1504A5E0` |
| `game_D4C20.c` | `0xD4C20:0xD4C40` | `0xA7770:0xA7790` | `func_150A7770` |
| `game_D5030.c` | `0xD5030:0xD5070` | `0xA7B80:0xA7BC0` | `func_150A7B80` |
| `game_10B7C0.c` | `0x10B7C0:0x10B7D0` | `0xDE310:0xDE320` | `func_150DE310` |
| `game_10C140.c` | `0x10C140:0x10C170` | `0xDEC90:0xDECC0` | `func_150DEC90` |
| `game_129EB0.c` | `0x129EB0:0x129EE0` | `0xFCA00:0xFCA30` | `func_150FCA00` |
| `game_12D7E0.c` | `0x12D7E0:0x12D7F0` | `0x100330:0x100340` | `func_15100330` |
| `game_15A830.c` | `0x15A830:0x15A840` | `0x12D380:0x12D390` | `func_1512D380` |
| `game_193420.c` | `0x193420:0x193430` | `0x165F70:0x165F80` | `func_15165F70` |
| `game_1BFC70.c` | `0x1BFC70:0x1BFCB0` | `0x1927C0:0x192800` | `func_151927C0` |
| `game_1CC420.c` | `0x1CC420:0x1CC440` | `0x19EF70:0x19EF90` | `func_1519EF70` |

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Every endpoint already occurs in `config/game/us.yaml`. Each complete range was
checked against the canonical raw US assembly and contains exactly the single
top-level `glabel` listed above. No indented local label crosses a source-unit
endpoint. These are educated structural boundary hypotheses based on the
upstream map, not original linker-map or symbol-table evidence.

The upstream `game/done/` directory placement is not imported as completion
evidence. No C implementation, symbol name, type, or comment was copied.
Function matching still requires a US `CURRENT (0)` focused diff.
