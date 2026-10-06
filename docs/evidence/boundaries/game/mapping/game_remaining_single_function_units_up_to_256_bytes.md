# Remaining US single-function source units up to 256 bytes

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map identifies the following single-function C
units. Subtracting the game-segment base `0x2D4B0` from each combined-binary
boundary gives its range in the US game overlay:

| Source identity | Combined range | Game-overlay range | Recovered US member |
| --- | --- | --- | --- |
| `game_34ED0.c` | `0x34ED0:0x34F20` | `0x7A20:0x7A70` | `func_15007A20` |
| `game_D5160.c` | `0xD5160:0xD51B0` | `0xA7CB0:0xA7D00` | `func_150A7CB0` |
| `game_D5250.c` | `0xD5250:0xD52A0` | `0xA7DA0:0xA7DF0` | `func_150A7DA0` |
| `game_FC3C0.c` | `0xFC3C0:0xFC410` | `0xCEF10:0xCEF60` | `func_150CEF10` |
| `game_43820.c` | `0x43820:0x43880` | `0x16370:0x163D0` | `func_15016370` |
| `game_10ECB0.c` | `0x10ECB0:0x10ED10` | `0xE1800:0xE1860` | `func_150E1800` |
| `game_1A6300.c` | `0x1A6300:0x1A6360` | `0x178E50:0x178EB0` | `func_15178E50` |
| `game_119960.c` | `0x119960:0x1199D0` | `0xEC4B0:0xEC520` | `func_150EC4B0` |
| `game_36600.c` | `0x36600:0x36680` | `0x9150:0x91D0` | `func_15009150` |
| `game_3C6C0.c` | `0x3C6C0:0x3C740` | `0xF210:0xF290` | `func_1500F210` |
| `game_D51B0.c` | `0xD51B0:0xD5250` | `0xA7D00:0xA7DA0` | `func_150A7D00` |
| `game_32200.c` | `0x32200:0x322B0` | `0x4D50:0x4E00` | `func_15004D50` |
| `game_323E0.c` | `0x323E0:0x32490` | `0x4F30:0x4FE0` | `func_15004F30` |
| `game_71770.c` | `0x71770:0x71820` | `0x442C0:0x44370` | `func_150442C0` |
| `game_39690.c` | `0x39690:0x39750` | `0xC1E0:0xC2A0` | `func_1500C1E0` |
| `game_43760.c` | `0x43760:0x43820` | `0x162B0:0x16370` | `func_150162B0` |
| `game_BC430.c` | `0xBC430:0xBC510` | `0x8EF80:0x8F060` | `func_1508EF80` |

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Every endpoint already occurs in `config/game/us.yaml`. Each complete range was
checked against the canonical raw US assembly and contains exactly the single
top-level `glabel` listed above. No indented local label crosses a source-unit
endpoint. These are educated structural boundary hypotheses based on the
upstream map, not original linker-map or symbol-table evidence.

The upstream `game/done/` directory placement is not imported as completion
evidence. No C implementation, symbol name, type, or comment was copied.
Function matching still requires a US `CURRENT (0)` focused diff.
