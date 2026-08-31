# `game_2DF70.c` US source-unit boundary

Evidence type: `structural_analysis`

Reviewed upstream revision: `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`

The reviewed upstream US split map starts the game segment at combined-binary
offset `0x2D4B0`, maps `game_2DF70.c` at `0x2DF70`, and maps the next C unit,
`game_305D0.c`, at `0x305D0`. Subtracting the game-segment base gives the game
overlay range `0xAC0:0x3120`.

- Boundary map: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml>
- Membership cross-check: <https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/src/game_2DF70.c>

Both offsets already occur as independently checked raw-assembly boundaries in
`config/game/us.yaml`. The owned US game payload recovers 25 top-level function
work items in this interval, from `func_15000AC0` through `func_15002FB4`.
Indented local labels at `0x1B08` and `0x310C` remain inside their containing
work items and do not create extra source-unit members.

The debug game payload also preserves the same function-order neighborhood for
the first member: retail `0x15000940 -> 0x15000AC0 -> 0x15000AD0` corresponds to
debug `0x150008D0 -> 0x15000A50 -> 0x15000A60`. This corroborates the function
boundary but is not used as match evidence.

No C implementation, symbol name, type, or comment was imported. Only the raw
source-unit boundary and membership were reviewed.
