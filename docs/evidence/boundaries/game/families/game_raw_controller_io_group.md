# US controller I/O and timed feedback group

Evidence type: `structural_analysis`

This working source family retains older navigation interval
`0x1BB20:0x1C730` from local `mkst/conker` commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined base `0x2D4B0`). Shared controller mapping, queue access and local
calls support the eight-entry group. The original filename and exact historical
compilation unit remain unknown.

## Structural evidence

`1501BB20` tests and clears request byte `80084064`, calculates a timer
interval through the main executable's integer helpers, and calls `osSetTimer`
(`10024A40`). `1501BBB8` sets that same request byte after receiving a
message on `800BE900`, obtaining input records, and invoking local
`1501C57C`. It maps controller channels through `80084060` and updates
related input buffers at `800BE708/800BE718/800BE720/800BE930`.

`1501C010` converts a bounded strength setting into two durations and calls
local `1501C0F0`. That routine uses the same `80084060` channel mapping,
checks per-port availability `800BE944`, sets request `800BE93C`, and stores
timing fields in `800BE950/800BE960/800BE970/800BE980`. Local `1501C17C`
clears the same request; `1501C53C` invokes it for all four logical channels.

`1501C1B0` processes four per-port records at `800BE760`, stride `0x68`,
using the same `800BE900` queue. It owns the availability, request and timing
arrays used by the setters, advances the timer and invokes the main executable's
port start/stop routines. This supports the timed feedback interpretation without
claiming an original function name.

The final `1501C57C` is directly called by the input routine at `0x1BC10`.
It processes pending peripheral operations, uses the same queue for its
`151DD460` call at `0x1C5B4`, dispatches the operation selected by
`80082BB4`, and releases its completed request buffer. This concrete call and
queue relationship connects the final routine to the I/O family.

## Validation

All eight labels agree with the independent US index. Their spans total
3,088 bytes and match owned US instructions, delay slots and padding. Both
endpoints follow complete returns; no decoded conditional branch crosses
either boundary in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration. All members remain
raw ASM, not matched C. Beta correlations are weak and are not the basis of
the grouping.

### `src/game/game_48FD0.c`

Range `0x1bb20:0x1c730`; 8 entries, 3,088 bytes.
SHA-1: `45ddbad6b0e425583e114a383b36733541724d5f`.
debug: 2 correlations, 0 strong.
ects: 2 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1501BB20` | `0x98` |
| `func_1501BBB8` | `0x458` |
| `func_1501C010` | `0xe0` |
| `func_1501C0F0` | `0x8c` |
| `func_1501C17C` | `0x34` |
| `func_1501C1B0` | `0x38c` |
| `func_1501C53C` | `0x40` |
| `func_1501C57C` | `0x1b4` |

## Integration result

Integrated on the first build attempt. The complete US game overlay is
byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw ASM.
