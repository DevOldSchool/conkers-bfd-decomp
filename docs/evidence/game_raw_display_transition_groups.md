# US display-object and transition-state groups

Evidence type: `structural_analysis`

These working families retain older local `mkst/conker` navigation intervals
(commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`). Original filenames and exact historical compilation
units remain unknown; generic filenames retain raw offset plus `0x2D4B0`.

## Display type 4: `0x165F80:0x1669A0`

Both constructors `15165F80/15166118` call `15167A68` with type 4 and
allocation size `0xA8`, initialize fields around `+0x90`, and attach the
result through `1517E05C`. Owned type row `8008B578` selects local update
`15166204`, draw `15166268`, and setup `151668B8`. The update changes
lifetime state at `+0x92/+0x9E`; draw consumes the same state plus the
constructor's display parameters. Setup prepares the rendering resources.
Thus every one of the five entries belongs to this type's construction and
registered callbacks.

## Display type `0xD`: `0x1669A0:0x167010`

`151669A0` allocates type `0xD`, size `0xE0`, initializes fields
`+0xD0:+0xD8`, and attaches through `1517E05C`. Owned row `8008B74C`
selects update `15166B50`, draw `15166D68`, setup `15166F6C`, and
additional hook `15166FD8` at row `+0x20`. Update and draw share the
constructor's `+0xD0` resource state. This accounts for all five entries;
the next `0x167010` interval starts the common object engine.

## Transition records: `0x187EC0:0x188810`

All six entries operate on the same record array `800DF700` and count
`800DF7B4`. `15187EC0` allocates and initializes a 36-byte record, including
current/target byte triples, scalar state, and a cleared 12-byte transition
area. `15187F90` clears the full `0xB4`-byte array and resets its count.
`15187FC0` reads the selected record's current triple. `15188010/1518804C`
read/write its scalar at record `+0xC` (global base `800DF70C`). The final
`151880C0` iterates the same records, advances their transition state with
`151EF610`, and updates the stored values. This shared allocation, access,
and update cycle supports one family without relying on adjacent addresses.

## Mechanical review

Raw instruction words equal the owned US image. Independent US beta-index
CSV membership and spans agree. All endpoints are 16-byte aligned with no
missing/overlapping words or conditional branches crossing the boundaries.
Beta correlations are supplementary. All entries remain `raw_asm`; no C
instruction-match claim is made.

### `src/game/game_193430.c`

Range `0x165f80:0x1669a0`; 5 entries, 2,592 bytes.
SHA-1: `a0765faeeffbc969cb447439cf4734dc0c8dd220`.
debug: 3 correlations, 3 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15165F80` | `0x198` |
| `func_15166118` | `0xec` |
| `func_15166204` | `0x64` |
| `func_15166268` | `0x650` |
| `func_151668B8` | `0xe8` |

### `src/game/game_193E50.c`

Range `0x1669a0:0x167010`; 5 entries, 1,648 bytes.
SHA-1: `3f95afd4d65830cd0c4b2e1903e8307746524610`.
debug: 3 correlations, 3 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151669A0` | `0x1b0` |
| `func_15166B50` | `0x218` |
| `func_15166D68` | `0x204` |
| `func_15166F6C` | `0x6c` |
| `func_15166FD8` | `0x38` |

### `src/game/game_1B5370.c`

Range `0x187ec0:0x188810`; 6 entries, 2,384 bytes.
SHA-1: `2dfd86760326acd912618894fe126d57e9906d40`.
debug: 6 correlations, 5 strong.
ects: 6 correlations, 5 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15187EC0` | `0xd0` |
| `func_15187F90` | `0x30` |
| `func_15187FC0` | `0x50` |
| `func_15188010` | `0x3c` |
| `func_1518804C` | `0x74` |
| `func_151880C0` | `0x750` |

## Integration result

Integrated on the first attempt. The complete US game overlay remains byte-identical: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw ASM; no C matches were added.
