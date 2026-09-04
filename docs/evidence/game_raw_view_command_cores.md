# US view setup and animated resource cores

Evidence type: `structural_analysis`

Two working source cores refine the older `0x10B070:0x10CB10` navigation
interval from local `mkst/conker` at `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined-image base `0x2D4B0`). They contain ten
raw entries and 4,560 bytes. The intervening four routines remain raw and
unassigned. Original source filenames and exact historical object limits
remain unknown.

| Source under `src/game/` | US range | Entries | Bytes | Debug (strong) | ECTS (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_138520.c` | `0x10B070:0x10B690` | 7 | 1,568 | 3 (3) | 2 (2) |
| `game_139410.c` | `0x10BF60:0x10CB10` | 3 | 2,992 | 3 (3) | 1 (0) |

## View setup core

Opening `1510B070` initializes shared view dimensions `800D9B1C/800D9B20`
from signed halfwords `800DD2F2/800DD2F4`, builds a projection workspace,
and uses the view records at `800BE628`. `1510B128` and `1510B458`
consume those dimensions. Wrapper `1510B32C` and loop `1510B3B0` call
`1510B128`; both that function and `1510B458/1510B51C` call final
matrix helper `1510B5F8`. The loops and wrappers populate/read shared
arrays at `800D9AC0/800D9AF0` and `800D9AF8/800D9B18`. This ties the
opening initializer to all six helper members through specific state and calls.
The final helper uses the same `0x180`-stride view records and writes the
resulting matrix. The new end follows its return/nop at `0x10B688/0x10B68C`.

## Animated resource core

`1510C4AC` allocates a `0x14`-byte record, stores it through `800D9E60`,
and increments count `800D9E64`. It calls opening resource parser
`1510BF60` twice, using the two resource roots at `800B0E00/800B0E04`.
The results initialize two allocated arrays at record `+0/+4` and counts at
`+8/+9`, together with mode and timing fields at `+0xC/+0xE/+0x10/+0x12`.

Final updater `1510C8A8` walks exactly the same pointer table/count and
uses the two arrays, counts and timing fields to update their records over
time. It also accesses the same resource information family at `800B0E10`.
This producer/consumer relationship joins the final routine to the constructor
and parser without assigning the preceding larger drawing routine.
The new start follows return/nop at `0x10BF58/0x10BF5C`; the outer end
follows the final return, stack-restoring delay slot and alignment padding.

## Validation and membership

Both internal endpoints are 16-byte aligned. All ten raw labels agree with
the US function index, and their spans cover both intervals exactly. Every
instruction, delay slot and padding word equals the owned US payload. No
decoded conditional branch crosses either endpoint in either direction.
No data, rodata or BSS ownership is assigned. Full US overlay equality gates
integration. These are structural raw-ASM mappings, not matched C.

### `src/game/game_138520.c`

Range SHA-1: `58b632ef473868a0763339f808bd9ebbae68e4d9`.

| Entry | Raw span |
| --- | ---: |
| `func_1510B070` | `0xb8` |
| `func_1510B128` | `0x204` |
| `func_1510B32C` | `0x84` |
| `func_1510B3B0` | `0xa8` |
| `func_1510B458` | `0xc4` |
| `func_1510B51C` | `0xdc` |
| `func_1510B5F8` | `0x98` |

### `src/game/game_139410.c`

Range SHA-1: `1845bd449cc8c0a1855ab17d6b7b9d823b59cbe7`.

| Entry | Raw span |
| --- | ---: |
| `func_1510BF60` | `0x54c` |
| `func_1510C4AC` | `0x3fc` |
| `func_1510C8A8` | `0x268` |


## Integration result

The first complete-overlay integration passed for both cores. All 2,072,880
US bytes are identical to the owned original payload, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. No C implementation credit.
