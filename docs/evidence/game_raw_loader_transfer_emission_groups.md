# US loader, timed transfer and emission groups

Evidence kind: `structural_analysis`. These are working source families, retaining generic offset filenames. Original filenames and historical compilation units remain unknown. All members remain raw ASM.

## Resource loader: `0x16850:0x17300`

`150169A0` owns resource setup for state `800D20FC/800D2100/01/0C/10`. It directly calls local allocation helper `15017114` at `0x16AD0` and local table/resource preparation `15016850` at `0x1706C`. Both helpers read the initialized count and resource state; `15017114` allocates the associated arrays at `800D2104/08`, while `15016850` resolves resources using that count and the shared owner state. All three entries belong to this loader's call graph.

## Timed transfer pair: `0x1DCEF0:0x1DD140`

`151DCEF0` drains the existing operation by calling local `151DCFD8`, then initializes state `800E0A20/24/28/2C` and schedules a timer using queue `80042A78`. `151DCFD8` polls that queue, calls the external transfer helper `151DD4E0`, advances the index and buffer by an eight-byte transfer step, updates remaining bytes, and reschedules or clears the same state. This is the game's stateful wrapper around external transfer/timer functions; those external routines are not included.

## Composite emission pair: `0xE9890:0xE9FE0`

Callback `150E9E34` accumulates emitter state, generates position parameters and directly calls local composite factory `150E9890`, which creates its child effects. The owned pointer at `8008A58C` identifies the callback. The two-entry range contains the callback and its called factory, with no unrelated entries between them.

## Timed burst triplet: `0x1DC6A0:0x1DCDE0`

`151DC8BC` optionally calls local immediate factory `151DC6A0`, then creates a timed object through `15149130` with update selector `0x5B` and 20 custom bytes (`0x1DC914:0x1DC968`). Owned update slot `8008A654` points to local `151DC97C`, which consumes the copied position, timer and mode state to emit children. All three entries participate in the same immediate-plus-timed burst interface.

## Type-1A emitter core: `0x189900:0x189FD0`

`15189900` allocates type `0x1A`, size `0x78`, copies 80 descriptor bytes and initializes emission state `+0x60/+0x64/+0x68/+0x6C/+0x70`. Owned type-table update slot `8008B9F0` points to local `15189A00`. That update creates a parametric element with `15147DA0` and chooses secondary selector 10 when the constructor's mode bit is set (`0x189DEC:0x189E54`). The wrapper stores this at custom byte `+0x21`; table `8008A3F8` slot `8008A420` points to local `15189EBC`. The update copies a four-byte parameter to custom `+0x48`, which that callback uses as its collision/height threshold. The unrelated, unproven callback at `0x189FD0` is explicitly excluded.

## Validation

Endpoints are 16-byte aligned and indexed function starts. Each raw word agrees with the owned US image; entry spans exactly cover each interval. Whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and available beta correlations follow; correlations support entry identity, not historical boundary proof.

### `src/game/game_43D00.c`

Range `0x16850:0x17300`; 3 entries, 2,736 bytes.
SHA-1: `63f239818f87b8a1dec1ea0e9fbb7a743c34b0c4`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15016850` | `0x150` |
| `func_150169A0` | `0x774` |
| `func_15017114` | `0x1ec` |

### `src/game/game_116D40.c`

Range `0xe9890:0xe9fe0`; 2 entries, 1,872 bytes.
SHA-1: `92d114fbb936d086be247306d98fd833a28568b6`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E9890` | `0x5a4` |
| `func_150E9E34` | `0x1ac` |

### `src/game/game_1B6DB0.c`

Range `0x189900:0x189fd0`; 3 entries, 1,744 bytes.
SHA-1: `0715bb1100c84b4137707d157c54f448c8ed7572`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15189900` | `0x100` |
| `func_15189A00` | `0x4bc` |
| `func_15189EBC` | `0x114` |

### `src/game/game_209B50.c`

Range `0x1dc6a0:0x1dcde0`; 3 entries, 1,856 bytes.
SHA-1: `1c9cebc9512d240390c833bbdf04ea3b9e2cfb77`.
debug: 1 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151DC6A0` | `0x21c` |
| `func_151DC8BC` | `0xc0` |
| `func_151DC97C` | `0x464` |

### `src/game/game_20A3A0.c`

Range `0x1dcef0:0x1dd140`; 2 entries, 592 bytes.
SHA-1: `82fb7ea4da8e68ccce042b6a5815a18938bf99dd`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151DCEF0` | `0xe8` |
| `func_151DCFD8` | `0x168` |

## Integration result

All five reviewed units integrated as raw ASM wrappers. The complete 2,072,880-byte US game overlay is byte-identical (SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). No C match is claimed.
