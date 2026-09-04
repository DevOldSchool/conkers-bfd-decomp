# US descriptor records, transforms and actor state

Evidence kind: `structural_analysis`. These are working source families with generic offset filenames. Original filenames and historical compilation-unit boundaries remain unknown. All entries remain raw ASM.

## Descriptor-class-11 records: `0xA00F0:0xA03B0`

The shared descriptor dispatcher described in `game_raw_descriptor_callback_families.md` selects class 11 through table index 10. Owned slots `80088448`, `800884FC` and `800884C0` point to local `150A0264`, `150A02D0` and `150A0374`. These operate on 12-byte records at `800D3010`: the first activates/configures a record, the second sets mode bits or the value at `+4`, and the third reads that value.

The two preceding entries belong to the same state system. `150A00F0` resets active bits and clears record values/timers through `800D3088`; `150A019C` walks the same 12-byte records and advances timers using `800BE9E4`, with rate/configuration tables `80088510/1C`. The three selected callbacks and reset/update helpers therefore form one local family.

## Four-entry actor state cache: `0x11F980:0x11FC20`

`1511F980` resets the count at `800DBFC0`. `1511F990` searches and populates the eight-byte records at `800DBFC8`, using that count and a four-entry capacity check. It compares and updates actor mode bits in byte `+0x73` across the cached actors. Reset and state processing use the same cache representation.

## Actor render wrapper/core: `0x1B320:0x1B660`

`1501B640` directly wraps local `1501B320` at `0x1B648`, forwarding the call's arguments. The core builds display commands using actor/render state. These two connected entries end at aligned `0x1B660`; the following independent display routine is excluded because its membership is not established.

## Validation

Endpoints are 16-byte aligned and indexed function starts. Raw words match the owned US image and entry spans cover every interval. Whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations follow; correlations support entry identity without proving original compilation boundaries.

## Retained candidate

The transform-processing range `0xAC9C0:0xAD770` remains unregistered. Its raw entry at `150AC9C0` is absent from the independent function CSV; the raw assembly and indexed membership must be reconciled before claiming this boundary.

### `src/game/game_CD5A0.c`

Range `0xa00f0:0xa03b0`; 5 entries, 704 bytes.
SHA-1: `eb5dab9fb2252fdab7e1b32a2e14f62b98463fe3`.
debug: 5 correlations, 5 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150A00F0` | `0xac` |
| `func_150A019C` | `0xc8` |
| `func_150A0264` | `0x6c` |
| `func_150A02D0` | `0xa4` |
| `func_150A0374` | `0x3c` |

### `src/game/game_14CE30.c`

Range `0x11f980:0x11fc20`; 2 entries, 672 bytes.
SHA-1: `36500fbdfadd1050de6328f5047a07eabd92212b`.
debug: 2 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1511F980` | `0x10` |
| `func_1511F990` | `0x290` |

### `src/game/game_487D0.c`

Range `0x1b320:0x1b660`; 2 entries, 832 bytes.
SHA-1: `afad74ae21e0f035ec6badb4fdacab960da89667`.
debug: 2 correlations, 1 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1501B320` | `0x320` |
| `func_1501B640` | `0x20` |

## Integration result

Three accepted groups contain nine raw entries and 2,208 bytes. Their first complete US game-overlay gate passes: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The discrepant transform range remains unregistered.
