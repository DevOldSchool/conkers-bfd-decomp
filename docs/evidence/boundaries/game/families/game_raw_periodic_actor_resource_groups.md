# US periodic effect and actor resource controllers

Evidence type: `structural_analysis`

These working source groups retain older navigation intervals from local
`mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined base `0x2D4B0`). Their state ownership,
calls and concrete callback selectors support the grouping. Original filenames
and exact historical compilation units remain unknown.

## Periodic effect: `0xD2110:0xD2450`

Constructor `150D2110` increments live counter `800D9900`, selects update
`0x2F`, draw 2 and cleanup/event `0x26` through `15149130`, and copies
`0x18` custom bytes to object `+0x28`. That engine stores the selectors at
`+0x11/+0x12/+0x13`. Owned table slots `8008A5A4/8008A678` select
local update `150D21CC` and draw `150D22F4`. The update advances custom
phase `+0x2C`, wraps at `+0x38`, and changes custom active byte `+0x28`;
the draw reads that byte and the two appearance bytes `+0x3C/+0x3D`.

The two cleanup dispatch tables `8008A688/8008A7B0`, indexed by `+0x13`
at `0x1493C8/0x149418`, select local `150D227C/150D22A8` for `0x26`.
Both call `150D22D4` to decrement the same live counter before generic
cleanup. Final callback `150D2374` (`8008A5A8`, update slot `0x30`) is the
periodic spawner: its custom timer expires, it calls local `150D2110` with
the stored timing/appearance parameters, and schedules its next emission.
All seven entries belong to this effect lifecycle.

## Actor resource controller: `0x80500:0x80D20`

Opening `15080500` resolves an actor request, queries local bitset helper
`15080738` (which calls local byte/mask helper `15080718`), writes global
request `800D1940`, and updates actor `+0x31C` state bytes `+0x74/+0x75`.
Setter `15080620` and clear helper `150806A8` address those same bytes through
the `800CC2D0` actor array; `800CC5EC` is its `+0x31C` pointer field. The
high bit marks state that the clear helper preserves.

Loader `15080828` reads that same global request to obtain resources and
owns pointers `800D1944/800D1948/800D194C/800D1998`. It initializes the
indices `800D1994/800D1995` used by local `15080784`, which walks the
halfword resource list at `800D1998`; local event adapter `150807F4` calls
that routine on event `0x20`. The loader explicitly passes `150807F4` in
`a3` to `1516A7B0` at `0x80B70:0x80BC0` and stores the resulting
controller at `800D1950`.

Cleanup `15080BE8` releases the resource controller and the same owned
buffers. Poller `15080C64` checks active state `800D1941` and controller
pointer `800D1950`, calls that cleanup when complete, and uses request
context `800D199C` written by the opening routine. Final `15080CF4` returns
whether the controller is inactive (`800D1941 == 0`). Shared request, state and resource ownership
connect every entry without inferring a higher-level feature name.

## Validation

All eighteen labels agree with the independent US index. Their spans total
2,912 bytes and match owned US instructions, delay slots and padding.
Each boundary follows a complete return; no decoded conditional branch
crosses it in either direction. No data, rodata or BSS ownership is assigned.
Full US overlay byte equality gates integration. All members remain raw ASM,
not matched C.

### `src/game/game_FF5C0.c`

Range `0xd2110:0xd2450`; 7 entries, 832 bytes.
SHA-1: `7f83ab481e0b5564d69d0ae75b73b78c90655204`.
debug: 7 correlations, 5 strong.
ects: 7 correlations, 5 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D2110` | `0xbc` |
| `func_150D21CC` | `0xb0` |
| `func_150D227C` | `0x2c` |
| `func_150D22A8` | `0x2c` |
| `func_150D22D4` | `0x20` |
| `func_150D22F4` | `0x80` |
| `func_150D2374` | `0xdc` |

### `src/game/game_AD9B0.c`

Range `0x80500:0x80d20`; 11 entries, 2,080 bytes.
SHA-1: `6bf2a8aaf3702d03ee56968b8a593a8062bc92db`.
debug: 7 correlations, 7 strong.
ects: 7 correlations, 6 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15080500` | `0x120` |
| `func_15080620` | `0x88` |
| `func_150806A8` | `0x70` |
| `func_15080718` | `0x20` |
| `func_15080738` | `0x4c` |
| `func_15080784` | `0x70` |
| `func_150807F4` | `0x34` |
| `func_15080828` | `0x3c0` |
| `func_15080BE8` | `0x7c` |
| `func_15080C64` | `0x90` |
| `func_15080CF4` | `0x2c` |

## Integration result

Both groups integrated on the first build attempt. The complete US game
overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All eighteen entries remain raw ASM.
