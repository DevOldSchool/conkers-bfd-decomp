# US model-anchor helpers and owner-bound callback pair

Evidence type: `structural_analysis`

The older local `mkst/conker` navigation interval `0x1C62D0:0x1C71A0`
(commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`, combined-image base `0x2D4B0`) contains two
separately supported cores. The aligned return boundary at `0x1C6EA0`
separates model-anchor helpers from an owner-bound constructor/update pair.
These are working source-family boundaries; original filenames and exact
historical compilation-unit boundaries remain unknown.

## Model-anchor core: `0x1C62D0:0x1C6EA0`

`151C62D0` and `151C6A28` use the same indexed model offsets at
`800AAB00`, position records at `800AAB08` and companion records at
`800AAB38/800AAB50`. Both invoke final emission helper `151C6D70`,
which consumes those same offsets and positions with `800AAB20` and passes
them to `15102B38`. This connects both larger emission paths to the final
helper through specific model-anchor data.

Intervening wrappers `151C6974/151C69A0` call `151C69CC` with index 0/1.
It uses the same `800AAB00` offsets into actor model `+0x1D4` and
`800AAB08` position records. Thus all six entries share a concrete
model-anchor representation, rather than only generic allocation calls.

## Owner-bound pair: `0x1C6EA0:0x1C71A0`

Constructor `151C6EA0` sets selector `0x17` at stack `+0x95`
(`0x1C6FAC`), with descriptor base `+0x34`: descriptor byte `+0x61`.
The call to `1513264C` copies the descriptor into object `+0x10`, placing
this selector at object `+0x71`. Engine update `151321D0` reads it at
`0x132244` and dispatches through `800898B0` at `0x132258/0x132264`.
Owned slot `0x17`, address `8008990C`, is local callback `151C7038`.

The constructor also places its owner pointer at descriptor `+0x6C`
(stack `+0xA0`, store `0x1C6FD8`), becoming object `+0x7C`.
The callback reads exactly that owner field, checks owner type `0xE9`,
uses `15142A5C` to update flags, and derives object alpha from owner `+0x4C`.
This closes a concrete producer/consumer and callback relationship for the pair.
The broader neighboring group is not assigned merely because it is adjacent.

## Validation

All eight entries agree with the independent US function index; ordered spans
cover 3,792 bytes exactly. Every instruction, delay slot and padding word
matches the owned US payload. All endpoints follow complete return/delay-slot
sequences, and no decoded conditional branch crosses them in either direction.
No data, rodata or BSS ownership is assigned. Full US overlay byte equality
is required for integration. All entries remain raw ASM, not matched C.

### `src/game/game_1F3780.c`

Range `0x1c62d0:0x1c6ea0`; 6 entries, 3,024 bytes.
SHA-1: `cc1fbf33dfba5f82d300661c18abfbfca8c597ec`.
debug: 3 correlations, 3 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151C62D0` | `0x6a4` |
| `func_151C6974` | `0x2c` |
| `func_151C69A0` | `0x2c` |
| `func_151C69CC` | `0x5c` |
| `func_151C6A28` | `0x348` |
| `func_151C6D70` | `0x130` |

### `src/game/game_1F4350.c`

Range `0x1c6ea0:0x1c71a0`; 2 entries, 768 bytes.
SHA-1: `cdc4091da685b1312ebc7c7d39a9a70ea9649d6a`.
debug: 1 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151C6EA0` | `0x198` |
| `func_151C7038` | `0x168` |

## Integration result

The first complete US overlay integration passed: all 2,072,880 bytes match
the owned payload, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
Both groups are integrated as mixed C/ASM; their eight entries remain raw ASM.
