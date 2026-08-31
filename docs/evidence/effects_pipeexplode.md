# `Effects/PipeExplode/pipeexplode.c` US source-unit boundary

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The owned retail game-data payload contains the retained string
`../Effects/PipeExplode/pipeexplode.c` beginning at decompressed data offset
`0x1CE50`. Code at game offset `0xB31C0`, inside `func_150B3188`, constructs its
runtime pointer. The debug beta independently retains the same filename and
anchors it inside the strongly correlated `func_150B22C8` at debug game offset
`0xB2300`.

The reviewed upstream US split map places the containing unit at combined
offset `0xDFBF0` and the next unit at `0xE0F60`. Subtracting the game base
`0x2D4B0` gives the US game-overlay range `0xB2740:0xB3AB0`.

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>

Both offsets already occur in `config/game/us.yaml`. The retained source string
supplies the original source identity; the reviewed external map supplies the
source-unit extent. Beta correlation corroborates identity only. None of these
signals is function-match evidence.
