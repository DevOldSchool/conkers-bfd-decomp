# US indexed controller and linked view worklist

Evidence type: `structural_analysis`

These working source families use older navigation intervals from local
`mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`, combined base `0x2D4B0`. The relationships below
support raw source grouping, not original filenames or exact historical units.

## Indexed controller: `0x155780:0x156190`

Opening constructor `15155780` allocates type `0x50`, size `0xA0`, and sets
index `+0x10`, mode `+0x11`, resource handle `+0x14` and float parameter
`+0x98`. It acquires resource `0xA6` through `1518C900`. Wrapper `151557FC`
calls local lookup `15155FD4`, creates the object when absent, and sets its
parameter, timer and mode. Both controls `15155F3C/15155F90` use the same
lookup and change that mode.

The lookup traverses `800DCE50:800DD190`, stride `0x1A0`, taking each list
head at `+0x140` (type `0x50` times four), following object `+8`, and comparing
index `+0x10`. Thus its list selection agrees with the constructor's exact type.
Update `1515589C` and draw `15155CFC` consume the shared index/mode, timer,
substate `+0x12`, resource handle and parameter. Owned callback slots
`8008C4E8/8008C4F0` point to those functions.

Cleanup `15155EF8`, referenced by `8008C510/8008C514`, releases the handle
with `1515F10C`, invokes object cleanup, and releases the same resource `0xA6`
through `1518CA04`. Event `15156028` (`8008C504`) derives an actor index
from `800CC2D0`, validates it against `+0x10`, and either releases the object
or exchanges its index for event `0x2D`. All nine entries share this lifecycle.
The beta evidence is weak here; structural relationships carry the mapping.

## Linked view worklist: `0x17E080:0x17EE40`

Constructor `1517E080` appends a `0x34`-byte record to head `800DDD64`,
using next pointer `+0x24`, initializing projected coordinates `+0xC/+0x10`,
state `+0x28/+0x2E`, and option bytes `+0x2F/+0x30`.
`1517E134` unlinks and frees records from exactly that list. `1517E1AC`
walks it, bounds-checks projected coordinates against `800BE620/800BE624`,
samples the halfword buffer at `800BE9C4`, and stores the result at `+0x2A`.

Main traversal `1517E28C` walks the same links and calls local projection and
visibility helpers `1517EAAC/1517EC1C`, then renderer `1517E4A8`.
The renderer consumes the same coordinates and state, shares view scratch
`800DDD60`, and calls local display-list setup `1517EA4C`. That setup emits
three command pairs and returns the advanced display-list pointer.
The projection helpers use the same view context and record fields, including
the sampled `+0x2A` state. The allocation, sampling, projection and rendering
relationships cover all eight entries without borrowing an adjacent family.

## Validation

The independent US function index agrees with all 17 raw entries. Their spans
cover 6,096 bytes and match owned US instructions, delay slots and padding.
Both ends follow complete return sequences. No decoded conditional branch
crosses either range boundary in either direction. No data, rodata or BSS
ownership is assigned. Full US overlay byte equality gates integration; all
members remain raw ASM, not matched C.

### `src/game/game_182C30.c`

Range `0x155780:0x156190`; 9 entries, 2,576 bytes.
SHA-1: `30fbf2692c85a133ade6968e72513e21a0ac8ab4`.
debug: 1 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15155780` | `0x7c` |
| `func_151557FC` | `0xa0` |
| `func_1515589C` | `0x460` |
| `func_15155CFC` | `0x1fc` |
| `func_15155EF8` | `0x44` |
| `func_15155F3C` | `0x54` |
| `func_15155F90` | `0x44` |
| `func_15155FD4` | `0x54` |
| `func_15156028` | `0x168` |

### `src/game/game_1AB530.c`

Range `0x17e080:0x17ee40`; 8 entries, 3,520 bytes.
SHA-1: `798f7ac3ce08a70cc765c775f1b2fc80aa67ea49`.
debug: 6 correlations, 6 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1517E080` | `0xb4` |
| `func_1517E134` | `0x78` |
| `func_1517E1AC` | `0xe0` |
| `func_1517E28C` | `0x21c` |
| `func_1517E4A8` | `0x5a4` |
| `func_1517EA4C` | `0x60` |
| `func_1517EAAC` | `0x170` |
| `func_1517EC1C` | `0x224` |

## Integration result

The first full US overlay gate passed: 2,072,880 identical bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Both groups are integrated
as mixed C/ASM, with all 17 entries remaining raw ASM.
