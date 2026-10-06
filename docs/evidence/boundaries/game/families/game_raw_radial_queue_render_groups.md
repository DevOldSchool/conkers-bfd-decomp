# US radial effects, timed queue and render-object groups

Evidence kind: `structural_analysis`. These working source families retain generic offset filenames. Original filenames and historical compilation units remain unknown. All entries remain raw ASM.

## Composite radial effect: `0xB7B40:0xB89E0`

`150B7B40` directly calls local `150B82D0` and `150B85C0` for child effects. Its radial burst call at `0xB7E5C` passes selector `0x19` on stack `+0x1C` (`0xB7E2C:0xB7E30`). The external `1514C678` dispatcher indexes `8008AA00`; owned slot `8008AA64` points to the fourth local entry, `150B879C`. This connects all four entries to the same composite emission path.

## Paired radial burst: `0xCDBB0:0xCE150`

`150CDBB0` finds an actor-relative ground position, then calls `1514C678` twice, selecting `0x17` at `0xCDC4C:0xCDC50` and `0x18` at `0xCDCA8:0xCDCAC`. Owned radial slots `8008AA5C` and `8008AA60` point to local `150CDCF4` and `150CDF10`. Both callbacks create children from the burst parameters. All three entries are connected through the two explicit selectors.

## Type-5E render object: `0x169900:0x169C70`

`15169900` allocates type `0x5E`, size `0x4C`, through `15167A68` and copies the 60-byte descriptor to object `+0x10`. `15169968` directly wraps that constructor with a default second argument. The type table at `8008B4A8`, with 52-byte rows, puts type-5E update/draw pointers at `8008C7C0/8008C7C8`; the owned values are local `15169988/15169A48`. The update advances descriptor state and handles expiry; the draw consumes the same object's render fields. All four entries belong to this object type.

## Timed bounded queue: `0x18AA10:0x18AD20`

`1518AADC` allocates type `0x1D`, size `0x28`, and initializes queue head/tail `+0x10/+0x14`, capacity `+0x18`, count `+0x1C` and timer `+0x20/+0x22`. Owned type-1D update slot `8008BA8C` is local `1518AA10`, which expires the oldest entry and invokes its payload cleanup through `8008D5C0`.

`1518ABD0` calls local `1518AB60` to allocate a type-1E, 32-byte node, links it into the same head/tail chain, increments count and resets the timer. On overflow it evicts the oldest node through the same cleanup table. The node constructor stores payload `+0x10`, links `+0x14/+0x18` and cleanup selector `+0x1C`. The two constructors, enqueue path and timed eviction callback thus form a complete local family.

## Large custom display object: `0x1B5240:0x1B5BA0`

`151B5240` prepares resource-backed custom state and calls `15149130` at `0x1B52EC`, choosing draw selector 1, event selector `0x15` and `0x5A8` custom bytes. The owned draw slot `8008A674` points to local `151B5328`; event slot `8008A92C` points to local `151B5A9C`. Both access the copied state, including the associated records at custom offsets `+0x580/+0x584/+0x588/+0x58C`. The creator and its two selected callbacks are the only entries in the interval.

## Validation

All callback values above were read from the owned US data image. Endpoints are 16-byte aligned and indexed function starts. Raw words match the owned code image; entry spans cover each interval exactly. Whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations follow; correlations establish entry identity, not original compilation boundaries.

### `src/game/game_E4FF0.c`

Range `0xb7b40:0xb89e0`; 4 entries, 3,744 bytes.
SHA-1: `f977e16d27c622621f912512389d6bf51fb93521`.
debug: 4 correlations, 4 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B7B40` | `0x790` |
| `func_150B82D0` | `0x2f0` |
| `func_150B85C0` | `0x1dc` |
| `func_150B879C` | `0x244` |

### `src/game/game_FB060.c`

Range `0xcdbb0:0xce150`; 3 entries, 1,440 bytes.
SHA-1: `3426301b1baef644ca9ab66fadfd8c856df7cfaf`.
debug: 3 correlations, 3 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150CDBB0` | `0x144` |
| `func_150CDCF4` | `0x21c` |
| `func_150CDF10` | `0x240` |

### `src/game/game_196DB0.c`

Range `0x169900:0x169c70`; 4 entries, 880 bytes.
SHA-1: `c581c9423598f3b636ce946efe902553ea621ee5`.
debug: 2 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15169900` | `0x68` |
| `func_15169968` | `0x20` |
| `func_15169988` | `0xc0` |
| `func_15169A48` | `0x228` |

### `src/game/game_1B7EC0.c`

Range `0x18aa10:0x18ad20`; 4 entries, 784 bytes.
SHA-1: `0a1ef8911bed7d1e1255e641b45ed50cc9a30def`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1518AA10` | `0xcc` |
| `func_1518AADC` | `0x84` |
| `func_1518AB60` | `0x70` |
| `func_1518ABD0` | `0x150` |

### `src/game/game_1E26F0.c`

Range `0x1b5240:0x1b5ba0`; 3 entries, 2,400 bytes.
SHA-1: `d46657a1f61b93564a557d28c2f39f8e8f828747`.
debug: 3 correlations, 3 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B5240` | `0xe8` |
| `func_151B5328` | `0x774` |
| `func_151B5A9C` | `0x104` |

## Integration result

All five reviewed units integrated as raw ASM wrappers. The complete 2,072,880-byte US game overlay is byte-identical (SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). No C match is claimed.
