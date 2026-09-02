# `game_3E890.c` US source-unit boundary hypothesis

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map places `game_3E890.c` at combined offset
`0x3E890` and the next C unit at `0x3EFB0`. Subtracting the game-segment base
`0x2D4B0` gives the US game-overlay range `0x113E0:0x11B00`.

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Both endpoints already occur in `config/game/us.yaml`. The canonical raw US
assembly contains exactly three top-level members in the complete range:
`func_150113E0`, `func_1501175C`, and `func_15011A78`. No indented local label
crosses either endpoint.

This is an educated structural boundary hypothesis based on the upstream map,
not original linker-map or symbol-table evidence. No upstream C implementation,
type, or comment was copied. Function matching still requires a US `CURRENT
(0)` focused diff.
