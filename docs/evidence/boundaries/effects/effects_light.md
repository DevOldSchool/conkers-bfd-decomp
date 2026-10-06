# `Effects/Light/light.c` US source-unit boundary

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The owned retail game-data payload contains the retained string
`../Effects/Light/light.c` at decompressed data offset `0x23B78`. Code at game
offset `0x16060C`, inside `func_15160600`, constructs its runtime pointer. The
debug build independently retains the same filename and anchors it inside the
corresponding function at debug game offset `0x164C18`.

The reviewed upstream US split map places the containing C unit at combined
offset `0x18D770` and its next unit at `0x191C30`. Subtracting the game base
`0x2D4B0` gives the US game-overlay range `0x1602C0:0x164780`.

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Both offsets already occur in `config/game/us.yaml`. The local US assembly
recovers 78 top-level function work items in the interval. The retained
`__FILE__` string supplies the original source identity; the external map
supplies the source-unit extent. Neither is function-match evidence.
