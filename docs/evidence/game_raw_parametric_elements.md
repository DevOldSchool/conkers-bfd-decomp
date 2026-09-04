# US parametric element-system family

Evidence type: `structural_analysis`

The working range `0x147DA0:0x149130` retains the older local `mkst/conker`
navigation interval (commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`). Original filename and exact historical compilation
unit remain unknown. The generic filename uses raw offset plus `0x2D4B0`.

## Constructor and callback relationships

`15147DA0` wraps the element-system constructor `15147A80`. It sets the
caller descriptor's `+0x10` field to 1 (the eventual event/cleanup selector),
requests primary update 1, draw 1, and 20-byte elements, and allocates
`0x48` custom bytes plus the caller's additional size. It copies the
parameter block into custom storage at object `+0x98`, then records its
additional selector bytes at custom `+0x20/+0x21/+0x22` and other parameters.

Owned top-level callback slots `8008A204/8008A2A8` select local update
`15147EB8` and draw `1514803C`. Cleanup selector 1 resolves through
`8008A2F4/8008A344` to local `15149104` before generic release.

`15147EB8` then dispatches the custom selectors through:

| Custom field | Owned table | Local members selected |
| --- | --- | --- |
| `+0x20` | `8008A3E0` | `151488C4`, `15148AF4`, `15148BA4`, `15148DE0` |
| `+0x21` | `8008A3F8` | `151490C8` at slot `8008A410` |
| `+0x22` | `8008A42C` | `15148EF8` at slot `8008A434` |

The first four callbacks operate on the system's element buffer `+0x94`
and custom parameters. `15148EF8` switches custom `+0x20` to mode 4;
`151490C8` updates custom intensity byte `+0x1B` from the system lifetime.
The remaining factory `15148F1C` directly calls local `15147DA0` with its
prepared parameters. This accounts for all eleven entries through actual
construction and dispatch, without assuming that every adjacent generic
effect routine belongs to this family. The next `15149130` starts a
different emitter constructor and is excluded.

## Mechanical review

All raw instruction words equal the owned US code image. Independent US
beta-index CSV entries and spans agree. Both endpoints are 16-byte aligned,
there are no missing or overlapping words, and no conditional branch crosses
a boundary. Beta correspondences are supplementary. All members remain
`raw_asm`; this is source grouping, not a matched-C claim.

### `src/game/game_175250.c`

Range `0x147da0:0x149130`; 11 entries, 5,008 bytes.
SHA-1: `1b811d25fd607816c8837fb482bba99744f9d2d3`.
debug: 9 correlations, 8 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15147DA0` | `0x118` |
| `func_15147EB8` | `0x184` |
| `func_1514803C` | `0x888` |
| `func_151488C4` | `0x230` |
| `func_15148AF4` | `0xb0` |
| `func_15148BA4` | `0x23c` |
| `func_15148DE0` | `0x118` |
| `func_15148EF8` | `0x24` |
| `func_15148F1C` | `0x1ac` |
| `func_151490C8` | `0x3c` |
| `func_15149104` | `0x2c` |

## Integration result

All reviewed members integrated on the first attempt. The complete US game
overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw
ASM; this verifies layout preservation.
