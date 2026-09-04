# US model-backed debris family

Evidence type: `structural_analysis`

The working family `0x174BF0:0x177410` retains the older local
`mkst/conker` navigation interval (commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`).
Original filenames and exact historical compilation units remain unknown.
Its generic filename uses the combined base `0x2D4B0`.

## Constructor, update, and rendering links

`15174BF0` allocates type `0xA`, size `0xF8`, via `15167A68` at
`0x174CF8:0x174D08`. Owned type-table row `8008B6B0` selects local
update `15175958` and draw `15176DF0`. `15174FA4` allocates type
`0x13`, also size `0xF8`, at `0x175030:0x175040`. Its row `8008B884`
selects local update `1517685C` and draw `151770C8`. Both specialized
callbacks call the first type's shared update/draw helpers.

The third constructor `15175390` allocates the same size, choosing its type
from the caller's base plus a bounded random variant at `0x175498:0x1754FC`.
It shares the model selection scheme with the first constructor: both index
20-byte records starting at `800DDE88`, store their selected model at object
`+0x94`, and their variant at `+0xED` (`0x174E48:0x174E68` and
`0x1757DC:0x175804`). Owned type rows `0x14:0x18`, `0x44`, and `0x45`
also select shared update/draw members from this family. `15176B84`, used
by rows `0x15:0x18`, calls `15175958` and uses the same model table and
variant state. The routines maintain related motion, lifetime and rendering
fields within that common object allocation.

## Model geometry helper

The final member `1517725C` indexes the same `800DDE88` model records at
stride 20 and the `8008D0B0` parameter records at stride `0x38`. It updates
model vertex coordinates from those angular parameters. The central update
`15175958` independently indexes that same `8008D0B0` table at
`0x175BCC:0x175BE4`. The first and third constructors and `15176B84`
load the model resources modified by this helper; the draw routines consume
those models. This connects the ninth entry through specific resource and
parameter tables, beyond adjacency alone.

## Boundary and byte review

All nine indexed entries exactly fill the aligned range. The raw words match
the owned US image, the independent US beta-index CSV confirms all members
and spans, and no conditional branch crosses either boundary. The final
helper returns and pads to `0x177410`. Beta correlations are corroboration,
not proof of historical source ownership. All members remain `raw_asm`.

### `src/game/game_1A20A0.c`

Range `0x174bf0:0x177410`; 9 entries, 10,272 bytes.
SHA-1: `c6eada1f9c6a587d708cce3aba17de7ab7e651f9`.
debug: 1 correlations, 0 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15174BF0` | `0x3b4` |
| `func_15174FA4` | `0x3ec` |
| `func_15175390` | `0x5c8` |
| `func_15175958` | `0xf04` |
| `func_1517685C` | `0x328` |
| `func_15176B84` | `0x26c` |
| `func_15176DF0` | `0x2d8` |
| `func_151770C8` | `0x194` |
| `func_1517725C` | `0x1b4` |

## Integration result

Registered and integrated all reviewed members as raw ASM. The complete US
game overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Integration passed on its
first attempt. This verifies layout preservation, not original filenames.
