# `Effects/Blood/blood.c` US source-unit boundary

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The owned retail game-data payload contains the retained string
`../Effects/Blood/blood.c` at decompressed data offset `0x2149C`. Code at game
offset `0x13567C`, inside `func_15135670`, constructs its runtime pointer. The
debug build independently retains the same filename and anchors it inside the
corresponding function at debug game offset `0x13A128`.

The reviewed upstream US split map places the containing C unit at combined
offset `0x161520` and its next C unit at `0x168A90`. Subtracting the game base
`0x2D4B0` gives the US game-overlay range `0x134070:0x13B5E0`.

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Both offsets already occur in `config/game/us.yaml`. The local US assembly
recovers 65 top-level function work items in the interval. The retained
`__FILE__` string supplies the original source identity; the external map
supplies the source-unit extent. Neither is function-match evidence.
