# US internal-call and callback clusters

Evidence kind: `structural_analysis`. These are working source-family boundaries with names derived from the raw ROM offsets. Original filenames and historical compilation-unit boundaries remain unknown. Every entry remains raw assembly.

The ranges below were selected from still-raw US map intervals. Every accepted range has 16-byte-aligned endpoints, exact owned-ROM words, complete entry-span coverage, no conditional branch crossing an endpoint, and exact agreement between the raw assembly labels and the independent function CSV. Direct local calls and owned callback-table words establish the member relationships.

## Local dispatcher and helper clusters

- `src/game/game_61490.c`, `0x33FE0:0x344A0`: `15033FE0` directly calls each of the four following local entries (`150341BC`, `15034340`, `150343B0`, and `15034420`).
- `src/game/game_7FC10.c`, `0x52760:0x52EF0`: table word `80086044` selects `150528C8`; that routine directly calls the preceding local helper `15052760` at `0x52E7C`.
- `src/game/game_808E0.c`, `0x53430:0x536D0`: `150535F4` calls `15053430`, which calls local `15053694`, forming one three-entry chain.
- `src/game/game_D3040.c`, `0xA5B90:0xA6210`: both larger entries call local helper `150A613C` three times, at `0xA5D10/28/40` and `0xA5FF8/6014/6030`.
- `src/game/game_10C090.c`, `0xDEBE0:0xDEC90`: `150DEBE0` directly calls local `150DEC28` at `0xDEBF8`; table word `8008A4E4` selects the caller.
- `src/game/game_10CD70.c`, `0xDF8C0:0xDFBD0`: table word `8008CD20` selects `150DF920`, which calls local helper `150DF8C0` at `0xDFA3C`.
- `src/game/game_115D70.c`, `0xE88C0:0xE8A80`: table word `8008A5BC` selects `150E88C0`, which directly calls local `150E8930` at `0xE8918`.
- `src/game/game_13AAE0.c`, `0x10D630:0x10D720`: `1510D630` directly calls local `1510D694` at `0x10D660`.

## Mirrored action callback families

Two adjacent ranges have the same three-entry shape and remain separate. Each has a compact table-selected callback, a larger callback that calls the first local helper, and a second independently selected compact callback.

- `src/game/game_EBE60.c`, `0xBE9B0:0xBEC30`: owned table words `8008A0A8` and `8008A13C` select `150BEAA8` and `150BEACC`; `150BEACC` calls `150BE9B0` at `0xBEAFC`.
- `src/game/game_EC0E0.c`, `0xBEC30:0xBEEB0`: owned table words `8008A0AC` and `8008A144` select `150BED28` and `150BED4C`; `150BED4C` calls `150BEC30` at `0xBED7C`.

## Callback wrappers and shared helpers

- `src/game/game_105D90.c`, `0xD88E0:0xD8B10`: owned table words `8008A08C` and `8008A0F4` select `150D8A20` and `150D8A34`; the latter calls local `150D88E0` at `0xD8A5C`.
- `src/game/game_11D710.c`, `0xF0260:0xF02C0`: table words `8008F950` and `8008F95C` select `150F0260` and `150F0280`; both wrappers call shared local helper `150F02A0`.
- `src/game/game_11F780.c`, `0xF22D0:0xF23E0`: table words `8008A0A4` and `8008A124` select `150F237C` and `150F2390`; the latter calls local `150F22D0` at `0xF23B8`.
- `src/game/game_1E0480.c`, `0x1B2FD0:0x1B3040`: table words `8008A6D4` and `8008A7FC` select wrappers `151B2FE8` and `151B3014`; both call local helper `151B2FD0`.
- `src/game/game_1E5820.c`, `0x1B8370:0x1B8400`: table words `8008A330` and `8008A380` select wrappers `151B83A0` and `151B83CC`; both call local helper `151B8370`.

## Excluded candidates

`0xA6210:0xA6360` and `0xAA9A0:0xAB1F0` are not registered. Their raw labels include entries absent from the independent CSV, so their membership must be reconciled first. The larger neighboring ranges are not pulled into these units merely because they are adjacent.

## Validation

Independent member lists and beta correlations follow. Correlations support entry identity, without proving an original source filename or compilation boundary.

### `src/game/game_61490.c`

Range `0x33fe0:0x344a0`; 5 entries, 1,216 bytes.
SHA-1: `7bb23436f62fd62099b5609896aeec5f41d23a71`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15033FE0` | `0x1dc` |
| `func_150341BC` | `0x184` |
| `func_15034340` | `0x70` |
| `func_150343B0` | `0x70` |
| `func_15034420` | `0x80` |

### `src/game/game_7FC10.c`

Range `0x52760:0x52ef0`; 2 entries, 1,936 bytes.
SHA-1: `bfac00a3f3ed66d83832e889c2efe2ba3def0bac`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15052760` | `0x168` |
| `func_150528C8` | `0x628` |

### `src/game/game_808E0.c`

Range `0x53430:0x536d0`; 3 entries, 672 bytes.
SHA-1: `6a6d9e33ab75cdc7135cc94927cddca64bc9d45c`.
debug: 3 correlations, 3 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15053430` | `0x1c4` |
| `func_150535F4` | `0xa0` |
| `func_15053694` | `0x3c` |

### `src/game/game_D3040.c`

Range `0xa5b90:0xa6210`; 3 entries, 1,664 bytes.
SHA-1: `d65bddbf94993e03c0fde917d61fdd38d6f6d41d`.
debug: 3 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150A5B90` | `0x2b4` |
| `func_150A5E44` | `0x2f8` |
| `func_150A613C` | `0xd4` |

### `src/game/game_EBE60.c`

Range `0xbe9b0:0xbec30`; 3 entries, 640 bytes.
SHA-1: `65e9067a7015a5917b27461b4c2597695f009810`.
debug: 3 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150BE9B0` | `0xf8` |
| `func_150BEAA8` | `0x24` |
| `func_150BEACC` | `0x164` |

### `src/game/game_EC0E0.c`

Range `0xbec30:0xbeeb0`; 3 entries, 640 bytes.
SHA-1: `1ea53ebc2e6fb5b4e76e2dd6595c41538ec7389c`.
debug: 3 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150BEC30` | `0xf8` |
| `func_150BED28` | `0x24` |
| `func_150BED4C` | `0x164` |

### `src/game/game_105D90.c`

Range `0xd88e0:0xd8b10`; 3 entries, 560 bytes.
SHA-1: `daae86a7921ab9dbaf891a1aaf7b3aa083e111a2`.
debug: 3 correlations, 2 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D88E0` | `0x140` |
| `func_150D8A20` | `0x14` |
| `func_150D8A34` | `0xdc` |

### `src/game/game_10C090.c`

Range `0xdebe0:0xdec90`; 2 entries, 176 bytes.
SHA-1: `417a55b0d51ac4965260c55b4c4e22063f70e91c`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150DEBE0` | `0x48` |
| `func_150DEC28` | `0x68` |

### `src/game/game_10CD70.c`

Range `0xdf8c0:0xdfbd0`; 2 entries, 784 bytes.
SHA-1: `62074fe0accf57a414e64af1834067f5212a8967`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150DF8C0` | `0x60` |
| `func_150DF920` | `0x2b0` |

### `src/game/game_115D70.c`

Range `0xe88c0:0xe8a80`; 2 entries, 448 bytes.
SHA-1: `57fabb4a4a2fdf19081edd3cb7dec663b2de9cea`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E88C0` | `0x70` |
| `func_150E8930` | `0x150` |

### `src/game/game_11D710.c`

Range `0xf0260:0xf02c0`; 3 entries, 96 bytes.
SHA-1: `375745821edf1e4a3c5d697157b8598e89c0ad8e`.
debug: 3 correlations, 1 strong.
ects: 3 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F0260` | `0x20` |
| `func_150F0280` | `0x20` |
| `func_150F02A0` | `0x20` |

### `src/game/game_11F780.c`

Range `0xf22d0:0xf23e0`; 3 entries, 272 bytes.
SHA-1: `2cb0a0c2d77ca2ac35a97db1cfccd620ceaa49a1`.
debug: 3 correlations, 2 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F22D0` | `0xac` |
| `func_150F237C` | `0x14` |
| `func_150F2390` | `0x50` |

### `src/game/game_13AAE0.c`

Range `0x10d630:0x10d720`; 2 entries, 240 bytes.
SHA-1: `615258e5a36778d68e351e922b1b9dd6dd6c5f74`.
debug: 2 correlations, 1 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1510D630` | `0x64` |
| `func_1510D694` | `0x8c` |

### `src/game/game_1E0480.c`

Range `0x1b2fd0:0x1b3040`; 3 entries, 112 bytes.
SHA-1: `f083f60ff5537c84f8d252a123548e9ad5291b75`.
debug: 3 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B2FD0` | `0x18` |
| `func_151B2FE8` | `0x2c` |
| `func_151B3014` | `0x2c` |

### `src/game/game_1E5820.c`

Range `0x1b8370:0x1b8400`; 3 entries, 144 bytes.
SHA-1: `e26b6efc42ca24d681532fa6091775e858f05608`.
debug: 3 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B8370` | `0x30` |
| `func_151B83A0` | `0x2c` |
| `func_151B83CC` | `0x34` |

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
