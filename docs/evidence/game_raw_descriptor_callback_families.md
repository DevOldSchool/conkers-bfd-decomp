# US descriptor callback families

Evidence kind: `structural_analysis`. These working source families retain generic offset filenames. Original filenames and historical compilation units remain unknown. All entries remain raw ASM.

## Shared discriminator and four tables

The shared dispatch entries at `150AE0F8`, `150AE108`, `150AE118` and `150AE12C` select tables `80088420`, `8008845C`, `80088498` and `800884D4`, respectively. They converge at `150AE140`, which reads descriptor word `+0`, extracts bits `0xF000`, shifts right by 12, rejects zero, subtracts one and indexes the selected table (`0xAE144:0xAE170`). Thus the same descriptor class selects corresponding slots in all four arrays; adjacent functions need not directly call one another to belong to the same dispatch family.

The descriptor-processing code at `0x9BF64:0x9BF90` and `0x9C0D4:0x9C104` also resolves the third/fourth arrays for their respective dispatch paths. All slot values below were independently read from the owned US data image. A null slot has no function to register.

Each proposed interval contains all the non-null callbacks for one descriptor class. The class-1 interval also contains `1509C8FC`, a helper directly called twice by its local callback `1509C440`. The two groups originally sharing `0x9E640:0x9E900` are split at the aligned entry `0x9E730`, because they belong to different descriptor classes.

These are functional source families, not proof that every class was historically one compilation unit. The discriminator values provide grouping evidence without assigning speculative original function names.

## Owned table values

| Descriptor class | Table 80088420 | Table 8008845C | Table 80088498 | Table 800884D4 |
| --- | --- | --- | --- | --- |
| 1 | null | null | `1509C7C8` | `1509C440` |
| 2 | `15097910` | `150979CC` | `15099C14` | `15097A8C` |
| 3 | null | null | `1509ED74` | `1509E900` |
| 4 | null | null | `150A04D8` | `150A03B0` |
| 5 | null | null | `1509FE0C` | `1509F850` |
| 6 | null | null | `1509E6F0` | `1509E640` |
| 10 | null | null | `1509E8A0` | `1509E730` |
| 12 | null | null | `1509F800` | `1509F818` |
| 14 | `1509D180` | `1509D780` | `1509DBBC` | `1509D8FC` |
| 15 | `1509DF20` | `1509DFB4` | `1509E3DC` | `1509DFC4` |

## Validation

All endpoints are 16-byte aligned and indexed function starts. Raw words match the owned code image, and entry spans cover each interval. Whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations follow; correlations support entry identity, not historical file boundaries.

### `src/game/game_C4DC0.c`

Range `0x97910:0x9b4a0`; 4 entries, 15,248 bytes.
SHA-1: `e1fcdd6cbf861a1574de92a7225f4348b770cfc5`.
debug: 1 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15097910` | `0xbc` |
| `func_150979CC` | `0xc0` |
| `func_15097A8C` | `0x2188` |
| `func_15099C14` | `0x188c` |

### `src/game/game_CA630.c`

Range `0x9d180:0x9dd10`; 4 entries, 2,960 bytes.
SHA-1: `03c94747c5e9998cd5f405df36d12609965af632`.
debug: 3 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509D180` | `0x600` |
| `func_1509D780` | `0x17c` |
| `func_1509D8FC` | `0x2c0` |
| `func_1509DBBC` | `0x154` |

### `src/game/game_CB3D0.c`

Range `0x9df20:0x9e640`; 4 entries, 1,824 bytes.
SHA-1: `aad2035e4822efbece515852ca840a44bd398f0c`.
debug: 2 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509DF20` | `0x94` |
| `func_1509DFB4` | `0x10` |
| `func_1509DFC4` | `0x418` |
| `func_1509E3DC` | `0x264` |

### `src/game/game_CBAF0.c`

Range `0x9e640:0x9e730`; 2 entries, 240 bytes.
SHA-1: `5fcb9b6467d332be2aeeb21dedae0084059576f3`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509E640` | `0xb0` |
| `func_1509E6F0` | `0x40` |

### `src/game/game_CBBE0.c`

Range `0x9e730:0x9e900`; 2 entries, 464 bytes.
SHA-1: `638d3ff7bf479405b3ceda62192f315dbc544d4a`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509E730` | `0x170` |
| `func_1509E8A0` | `0x60` |

### `src/game/game_CBDB0.c`

Range `0x9e900:0x9eff0`; 2 entries, 1,776 bytes.
SHA-1: `205e4656ec6eaae25f982005fff8bf71789cbd40`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509E900` | `0x474` |
| `func_1509ED74` | `0x27c` |

### `src/game/game_CCCB0.c`

Range `0x9f800:0x9f850`; 2 entries, 80 bytes.
SHA-1: `783bdec96aa483e8be6738be84729ac81ff41432`.
debug: 2 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509F800` | `0x18` |
| `func_1509F818` | `0x38` |

### `src/game/game_CCD00.c`

Range `0x9f850:0xa00f0`; 2 entries, 2,208 bytes.
SHA-1: `ba82422d0389fc2cd9de591960827ed2c8f295e9`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509F850` | `0x5bc` |
| `func_1509FE0C` | `0x2e4` |

### `src/game/game_CD860.c`

Range `0xa03b0:0xa09d0`; 2 entries, 1,568 bytes.
SHA-1: `31da687aa35a9aeada3f1f3302930f4df7ea0532`.
debug: 1 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150A03B0` | `0x128` |
| `func_150A04D8` | `0x4f8` |

### `src/game/game_C98F0.c`

Range `0x9c440:0x9ca10`; 3 entries, 1,488 bytes.
SHA-1: `06720b77b9bfadedb5f40b36832553b07cb85702`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509C440` | `0x388` |
| `func_1509C7C8` | `0x134` |
| `func_1509C8FC` | `0x114` |

## Integration result

Ten groups retain 27 raw entries and 27,856 bytes. The complete US game overlay is byte-identical: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw assembly.
