# Compact US multi-function source units up to 512 bytes

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following compact C units
with two or three recovered functions. Subtracting the game-segment base
`0x2D4B0` gives each range in the US game overlay:

| Source identity | Combined range | Game-overlay range | Recovered US members |
| --- | --- | --- | --- |
| `game_3EFB0.c` | `0x3EFB0:0x3F0F0` | `0x11B00:0x11C40` | `func_15011B00`, `func_15011B94` |
| `game_75810.c` | `0x75810:0x75950` | `0x48360:0x484A0` | `func_15048360`, `func_15048408` |
| `game_334C0.c` | `0x334C0:0x33620` | `0x6010:0x6170` | `func_15006010`, `func_15006140` |
| `game_35D20.c` | `0x35D20:0x35E80` | `0x8870:0x89D0` | `func_15008870`, `func_15008930` |
| `game_439B0.c` | `0x439B0:0x43B20` | `0x16500:0x16670` | `func_15016500`, `func_15016588` |
| `game_35EC0.c` | `0x35EC0:0x36040` | `0x8A10:0x8B90` | `func_15008A10`, `func_15008A60` |
| `game_44A90.c` | `0x44A90:0x44C40` | `0x175E0:0x17790` | `func_150175E0`, `func_15017640` |
| `game_3F1F0.c` | `0x3F1F0:0x3F3D0` | `0x11D40:0x11F20` | `func_15011D40`, `func_15011D60` |
| `game_75A90.c` | `0x75A90:0x75BD0` | `0x485E0:0x48720` | `func_150485E0`, `func_15048664`, `func_150486B8` |
| `game_3D9A0.c` | `0x3D9A0:0x3DB30` | `0x104F0:0x10680` | `func_150104F0`, `func_15010538`, `func_15010600` |
| `game_3C230.c` | `0x3C230:0x3C3D0` | `0xED80:0xEF20` | `func_1500ED80`, `func_1500EE18`, `func_1500EE94` |
| `game_75C90.c` | `0x75C90:0x75E60` | `0x487E0:0x489B0` | `func_150487E0`, `func_15048864`, `func_150488C8` |
| `game_43B20.c` | `0x43B20:0x43D00` | `0x16670:0x16850` | `func_15016670`, `func_15016680`, `func_15016690` |
| `game_76710.c` | `0x76710:0x768F0` | `0x49260:0x49440` | `func_15049260`, `func_150492CC`, `func_15049350` |

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
