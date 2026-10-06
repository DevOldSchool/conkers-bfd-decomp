# US child-chain, emission-chain and render-list families

Evidence kind: `structural_analysis`. These are working source families retained from existing raw navigation ranges, not recovered original filenames or proven historical compilation units. All members remain raw ASM.

## Six-child controller: `0xD1C30:0xD2110`

The external factory in `func_15014B60` calls `15149130` at `0x14EEC` with update selector `0x2E`, event/cleanup selector `0x29`, and `0x48` custom bytes copied to object `+0x28`. The generic constructor stores the selectors at object `+0x11/+0x13`. Its owned-ROM update slot `8008A5A0` points to local `150D1C30`; event slot `8008A97C` points to `150D1F6C`; cleanup slots `8008A72C/8008A854` point to `150D20B0/150D20DC`. Both cleanup wrappers call local `150D2054`, which releases six children at custom `+0x24`. The update and event paths consume the same owner, position and flag state. The event path handles `0x30/0x31/0x32` and teardown events `0x4E/0x4F`. This accounts for all five entries without extending the range to the external factory.

## Emission chain: `0xD26F0:0xD3360`

The external setup at `0x15014:0x15074` calls `15149130` with update `0x31`, event `0x2A`, and `0x54` custom bytes. Owned slots `8008A5AC/8008A980` point to local `150D26F0/150D32FC`. Both call `150D278C`; its `0xD28F8` allocation selects update `0x32`, resolving through `8008A5B0` to local `150D2924`, and copies `0x60` custom bytes. That update creates particles through `1513D2F0` at `0xD2CC0` with step `0x26` and draw `0x1F`. Generic particle tables `80089D60/80089E1C` resolve those selectors at `80089DF8/80089E98` to local `150D317C/150D2D6C`. Its `0x30` custom-byte copy at child `+0x110` supplies the state used by these callbacks. All six entries therefore form the setup, repeated emission and particle callback chain.

## Two-list rendering system: `0x188810:0x189900`

`15188810/1518894C` allocate type-0/type-1 list records, payload buffers and owner identity; both call local append helper `15188A58`. Their heads are adjacent globals `800DF7C8/800DF7CC`, links at `+0xC`, owner at `+0x10`, buffer at `+8`, lifetime at `+6`. `15188A9C` expires an owner's records, `15188AD0` unlinks and frees them, `151898C0` sets associated state at `+0x14`.

`15188B74` indexes the head array, updates records through table `8008D580`, and releases them through `8008D588`; owned slots select local update callbacks `15188E48/15188F84` and release callbacks `151895A4/151895CC`. `15188D00` draws the same list through table `8008D590`, selecting local `151895F4/151897A4`. `15189118` traverses the same head array to prepare/interpolate buffer records. This accounts for all 15 entries, including both allocation variants and all six indirect callbacks.

## Boundary and image checks

All six endpoints are existing 16-byte-aligned raw boundaries. Every raw instruction word was compared with the owned US image. Indexed member spans exactly cover each range; whole-image conditional-branch scanning found no crossing edges. Independent function CSV membership is checked below. Beta correlations support entry identity but do not establish historical source boundaries.

### `src/game/game_FF0E0.c`

Range `0xd1c30:0xd2110`; 5 entries, 1,248 bytes.
SHA-1: `c993475a1cc9bf55bdfc1d80d683f9200171c7ec`.
debug: 5 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D1C30` | `0x33c` |
| `func_150D1F6C` | `0xe8` |
| `func_150D2054` | `0x5c` |
| `func_150D20B0` | `0x2c` |
| `func_150D20DC` | `0x34` |

### `src/game/game_FFBA0.c`

Range `0xd26f0:0xd3360`; 6 entries, 3,184 bytes.
SHA-1: `260c8b84976c11fd99041c81687e590af254753f`.
debug: 6 correlations, 6 strong.
ects: 4 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D26F0` | `0x9c` |
| `func_150D278C` | `0x198` |
| `func_150D2924` | `0x448` |
| `func_150D2D6C` | `0x410` |
| `func_150D317C` | `0x180` |
| `func_150D32FC` | `0x64` |

### `src/game/game_1B5CC0.c`

Range `0x188810:0x189900`; 15 entries, 4,336 bytes.
SHA-1: `c71cd7b365383d6eb77152f6f3173e6637b04483`.
debug: 15 correlations, 13 strong.
ects: 7 correlations, 5 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15188810` | `0x13c` |
| `func_1518894C` | `0x10c` |
| `func_15188A58` | `0x44` |
| `func_15188A9C` | `0x34` |
| `func_15188AD0` | `0xa4` |
| `func_15188B74` | `0x18c` |
| `func_15188D00` | `0x148` |
| `func_15188E48` | `0x13c` |
| `func_15188F84` | `0x194` |
| `func_15189118` | `0x48c` |
| `func_151895A4` | `0x28` |
| `func_151895CC` | `0x28` |
| `func_151895F4` | `0x1b0` |
| `func_151897A4` | `0x11c` |
| `func_151898C0` | `0x40` |

## Integration result

All three groups passed the first integration attempt. The complete US game overlay remains byte-identical: 2,072,880 bytes; SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
