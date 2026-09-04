# US animated render and emission-controller groups

Evidence type: `structural_analysis`

These are working source-family boundaries, retaining navigation intervals from
local `mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`, combined-image base `0x2D4B0`. Calls, matching
producer/consumer fields and concrete callback selectors support the grouping.
Original filenames and exact historical compilation-unit limits remain unknown.

## Animated render lifecycle: `0x171CA0:0x172C50`

`15171CA0` allocates types `0xF` or `0x43`, base size `0x60`, and initializes
lifetime `+0x50`, animation state `+0x52`, increment `+0x54`, template index
`+0x58` and flags `+0x59`. Both constructors `15171D4C/15171F04` call it,
consult template table `8008CA4C`, and invoke geometry setup through
`15172B20/151725FC`; the former helper also calls the latter.

Update `15171FC0` consumes precisely those lifetime, animation and template
fields, and releases expired objects. Draw `151720C4` consumes the same
`8008CA4C` templates and shared rendering workspace at `800DD1B4:800DD1C6`.
Owned callback slots `8008B7B4/8008C244` point to the update; companion
slots `8008B7BC/8008C24C` point to the draw routine. The two constructors,
common allocator, update/draw pair and two geometry helpers form one lifecycle.

## Emission controller: `0x178EB0:0x179DB0`

Initializer `15178EB0`, shutdown `15178EFC` and hub `15179008` share controller
state `800DD432:800DD446`, including child array `800DD440` and count
`800DD436`. The hub calls `15179600`, `15179AB8`, `151794C8`, and
`15179B14`. `151794C8` sets the position at `800DD438`; both constructors
and callbacks consume this controller or its associated `800DBFF0` actor.
`15179600` appends allocated children to `800DD440` and increments the count;
`15179AB8` walks those children, while shutdown releases them and their array.

The callback pairing is concrete. `15179600` stores selector 1 at stack
`+0xCA` (`0x179628`) with its descriptor at `+0x28`; `15179B14` stores
selector `0xE` at `+0xEA` (`0x179C4C`) with its descriptor at `+0x48`.
Both therefore set descriptor `+0xA2`. Engine constructor `15168800` copies
`0xA8` bytes to object `+0x10`, making this object `+0xB2`. Update engine
`15168870` reads that field (`0x1689D4`), loads table `8008C9C8`
(`0x1689EC`), and calls the selected entry (`0x1689F8`). Owned slot 1
(`8008C9CC`) is local `151797B0`; slot `0xE` (`8008CA00`) is local
`15179CB0`. These callbacks update the constructed objects and the same
controller state, closing the source-family graph.

## Validation

All 16 raw entries agree with the independent US function index. Ordered spans
cover 7,856 bytes exactly; every instruction, delay slot and padding word agrees
with the owned US payload. No decoded conditional branch crosses either
endpoint in either direction. Endpoints follow returns, delay slots and alignment
padding. No data, rodata or BSS ownership is assigned. Beta correlations are
supporting continuity evidence, not proof of original source filenames.
Full US overlay byte equality gates integration. All entries remain raw ASM.

### `src/game/game_19F150.c`

Range `0x171ca0:0x172c50`; 7 entries, 4,016 bytes.
Range SHA-1: `41514cf606bf86442ddf49238bc6f467ebcccbdd`.
debug: 5 correlations, 5 strong.
ects: 4 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15171CA0` | `0xac` |
| `func_15171D4C` | `0x1b8` |
| `func_15171F04` | `0xbc` |
| `func_15171FC0` | `0x104` |
| `func_151720C4` | `0x538` |
| `func_151725FC` | `0x524` |
| `func_15172B20` | `0x130` |

### `src/game/game_1A6360.c`

Range `0x178eb0:0x179db0`; 9 entries, 3,840 bytes.
Range SHA-1: `1bf0af05695e5256b2fecfb368421dd4ca3e75e6`.
debug: 7 correlations, 6 strong.
ects: 7 correlations, 6 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15178EB0` | `0x4c` |
| `func_15178EFC` | `0x10c` |
| `func_15179008` | `0x4c0` |
| `func_151794C8` | `0x138` |
| `func_15179600` | `0x1b0` |
| `func_151797B0` | `0x308` |
| `func_15179AB8` | `0x5c` |
| `func_15179B14` | `0x19c` |
| `func_15179CB0` | `0x100` |

## Integration result

The first complete US overlay integration passed: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Both groups are integrated
as mixed C/ASM; all 16 entries remain raw ASM.
