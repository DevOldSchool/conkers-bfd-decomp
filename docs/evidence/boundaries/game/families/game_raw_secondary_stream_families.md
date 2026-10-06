# US secondary-update and stream-emitter families

Evidence type: `structural_analysis`

These four working families use older local `mkst/conker` navigation
intervals (commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`) as context. Original filenames and exact historical
compilation units remain unknown. The final two narrow one older range into
separate constructor/callback/helper triplets.

## Secondary-update composite: `0xF4570:0xF51A0`

`150F4570` builds a `1513264C` descriptor at stack `+0x84`. Its
primary update byte at `+0xE5` is `0x16`, its secondary byte at `+0xE6`
is 7, and its event byte at `+0xDC` is 8. The constructor copies these to
object `+0x71`, `+0x72`, and `+0x68`. Owned US tables select local primary
update `150F48D0` at `80089908`, secondary update `150F4A38` at
`80089930`, and event handler `150F4CFC` at `80089A18`.
The event dispatcher indexes `800899F8` from object `+0x68` when flag
`0x100` is enabled; this descriptor supplies flags `0x14900`.
The callbacks consume the constructor's `0x28` custom bytes at `+0x170`;
the event handler changes that state or releases the object.

`150F4D5C` creates an emitter with update `0x56` and 12 custom bytes.
Slot `8008A640` selects local `150F4DEC`, which calls `150F4570` to
produce these children. This connects all six entries through the composite
emitter and the child's two update stages.

## Owner with two children: `0xF6DB0:0xF7470`

`150F6DE4` creates an emitter with update `0x43`, event/cleanup `0x37`,
and `0x78` custom bytes at `+0x28`. It initializes two child slots at custom
`+8/+0xC` and creates particles through `15130280`. Owned slots
`8008A5F4/8008A9B4` select local update `150F706C` and event `150F7310`.
Cleanup slots `8008A764/8008A88C` select `150F740C/150F7438`; both call
local `150F739C`, which releases those two children and calls `1514EDF0`
with the custom owner. The first member `150F6DB0` broadcasts owner pointer
and identity with command `0x3E`; `150F7310` explicitly recognizes that
command and releases the matching emitter. All seven entries are connected.

## Two stream triplets

`0x1B4CD0:0x1B4FE0` contains constructor `151B4CD0`, callback
`151B4E4C`, and emission helper `151B4EA4`. The constructor selects
emitter 8 in its `1513418C` descriptor (`stack +0x4F`, descriptor start
`+0x24`). The engine copies it to object `+0x3B` and dispatches via
`80089A70`; owned slot `80089A90` contains `151B4E4C`, which directly
calls `151B4EA4`.

`0x1B4FE0:0x1B5240` repeats that construction for emitter 9: selector
at stack `+0x47` relative to descriptor start `+0x1C`, owned slot
`80089A94` selecting `151B50A4`, and its direct emission helper
`151B50F4`. Both helpers create their output through `151D9014`.
They remain separate working units because a shared original source file
has not been established.

## Mechanical review

All raw words equal the owned US code image. Independent US beta-index CSV
membership and spans agree. The four ranges are 16-byte aligned with no
missing/overlapping words or conditional branches crossing boundaries.
Debug/ECTS correlations are supplementary; the first stream triplet has none.
All entries remain `raw_asm`, with no matched-C claim.

### `src/game/game_121A20.c`

Range `0xf4570:0xf51a0`; 6 entries, 3,120 bytes.
SHA-1: `87aeec82ffd44f5b97d88c98a6fdca036e25aa52`.
debug: 4 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F4570` | `0x360` |
| `func_150F48D0` | `0x168` |
| `func_150F4A38` | `0x2c4` |
| `func_150F4CFC` | `0x60` |
| `func_150F4D5C` | `0x90` |
| `func_150F4DEC` | `0x3b4` |

### `src/game/game_124260.c`

Range `0xf6db0:0xf7470`; 7 entries, 1,728 bytes.
SHA-1: `1b6e645c864b4eec30def214a493fce98811ee61`.
debug: 5 correlations, 2 strong.
ects: 4 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F6DB0` | `0x34` |
| `func_150F6DE4` | `0x288` |
| `func_150F706C` | `0x2a4` |
| `func_150F7310` | `0x8c` |
| `func_150F739C` | `0x70` |
| `func_150F740C` | `0x2c` |
| `func_150F7438` | `0x38` |

### `src/game/game_1E2180.c`

Range `0x1b4cd0:0x1b4fe0`; 3 entries, 784 bytes.
SHA-1: `095dbbcce267fa3ae506f35d3da8e6a9e51fa844`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B4CD0` | `0x17c` |
| `func_151B4E4C` | `0x58` |
| `func_151B4EA4` | `0x13c` |

### `src/game/game_1E2490.c`

Range `0x1b4fe0:0x1b5240`; 3 entries, 608 bytes.
SHA-1: `e54a1674b4ffc3180a07178f53b6be7a11f06887`.
debug: 2 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B4FE0` | `0xc4` |
| `func_151B50A4` | `0x50` |
| `func_151B50F4` | `0x14c` |

## Integration result

All four reviewed groups integrated on the first attempt. The complete US game overlay remains byte-identical: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. These are raw-ASM mappings, with no new C matches.
