# US pointer-selected raw subranges

Evidence kind: `structural_analysis`. These ten working source-family subranges contain only owned table-selected functions. Their generic names derive from the raw ROM offsets; historical filenames and original compilation-unit boundaries remain unknown. All entries remain raw assembly.

Each range is bounded to exclude a neighboring unselected entry. All endpoints are 16-byte aligned. Owned-ROM words and member spans are exact, no conditional branch crosses an endpoint, and the raw labels agree exactly with the independent function CSV.

| Source | US range | Entries | Bytes | Owned selections |
| --- | --- | ---: | ---: | --- |
| `src/game/game_DF2D0.c` | `0xb1e20:0xb2480` | 4 | 1,632 | `0x800896e4` → `func_150B1E20`<br>`0x8008f97c` → `func_150B1EE0`<br>`0x8008a60c` → `func_150B1F90`<br>`0x800896c4` → `func_150B2340` |
| `src/game/game_EEB70.c` | `0xc16c0:0xc19c0` | 2 | 768 | `0x8008aa08` → `func_150C16C0`<br>`0x8008a40c` → `func_150C1978` |
| `src/game/game_105760.c` | `0xd82b0:0xd8590` | 3 | 736 | `0x8008cd08` → `func_150D82B0`<br>`0x800841c4` → `func_150D82BC`<br>`0x8008420c` → `func_150D83D8` |
| `src/game/game_108AE0.c` | `0xdb630:0xdb9e0` | 2 | 944 | `0x80089d88` → `func_150DB630`<br>`0x80089e3c` → `func_150DB714` |
| `src/game/game_10D280.c` | `0xdfdd0:0xe0300` | 3 | 1,328 | `0x800841f0` → `func_150DFDD0`<br>`0x8008a628` → `func_150DFEFC`<br>`0x8008a9cc` → `func_150E02C0` |
| `src/game/game_1136E0.c` | `0xe6230:0xe68b0` | 4 | 1,664 | `0x80089cf4` → `func_150E6230`<br>`0x80089e58` → `func_150E63A0`<br>`0x80089db4` → `func_150E679C`<br>`0x80088a10` → `func_150E67D0` |
| `src/game/game_137ED0.c` | `0x10aa20:0x10aee0` | 3 | 1,216 | `0x8008cd38` → `func_1510AA20`<br>`0x80088eb8` → `func_1510AA44`<br>`0x80088ec4` → `func_1510ADD8` |
| `src/game/game_1C02A0.c` | `0x192df0:0x193390` | 3 | 1,440 | `0x8008a548` → `func_15192DF0`<br>`0x8008a918` → `func_15193234`<br>`0x8008a930` → `func_151932E0` |
| `src/game/game_1DFE00.c` | `0x1b2950:0x1b2fd0` | 5 | 1,664 | `0x8008fb70` → `func_151B2950`<br>`0x8008a670` → `func_151B2974`<br>`0x8008a924` → `func_151B2EC4`<br>`0x8008a920` → `func_151B2F04`<br>`0x8008faf4` → `func_151B2FA0` |
| `src/game/game_204310.c` | `0x1d6e60:0x1d71b0` | 4 | 848 | `0x8008adac` → `func_151D6E60`<br>`0x800888ac` → `func_151D7000`<br>`0x800888b4` → `func_151D70CC`<br>`0x8008adc0` → `func_151D710C` |

The excluded neighboring entries receive no source-boundary credit. Table selection establishes the membership of every accepted function but does not recover the historical source name.

## Validation

### `src/game/game_DF2D0.c`

Range `0xb1e20:0xb2480`; 4 entries, 1,632 bytes.
SHA-1: `cfed22fc4b36f02fd1539674fdc231b77c8f94f8`.
debug: 3 correlations, 3 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B1E20` | `0xc0` |
| `func_150B1EE0` | `0xb0` |
| `func_150B1F90` | `0x3b0` |
| `func_150B2340` | `0x140` |

### `src/game/game_EEB70.c`

Range `0xc16c0:0xc19c0`; 2 entries, 768 bytes.
SHA-1: `76ad74573f0f5a1c4cdb013f318200b017b5e3d4`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C16C0` | `0x2b8` |
| `func_150C1978` | `0x48` |

### `src/game/game_105760.c`

Range `0xd82b0:0xd8590`; 3 entries, 736 bytes.
SHA-1: `d6c37bcc7e6c5b1a488c104e2bd44fd9ccfd65a7`.
debug: 3 correlations, 2 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D82B0` | `0xc` |
| `func_150D82BC` | `0x11c` |
| `func_150D83D8` | `0x1b8` |

### `src/game/game_108AE0.c`

Range `0xdb630:0xdb9e0`; 2 entries, 944 bytes.
SHA-1: `ddcc0e380f5343ae831f53764bb6c78421ecdc3d`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150DB630` | `0xe4` |
| `func_150DB714` | `0x2cc` |

### `src/game/game_10D280.c`

Range `0xdfdd0:0xe0300`; 3 entries, 1,328 bytes.
SHA-1: `14cf4d288d4c7e3fdc621f065b753bfab0b4f931`.
debug: 3 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150DFDD0` | `0x12c` |
| `func_150DFEFC` | `0x3c4` |
| `func_150E02C0` | `0x40` |

### `src/game/game_1136E0.c`

Range `0xe6230:0xe68b0`; 4 entries, 1,664 bytes.
SHA-1: `d50d0184885c4c99fcdc8bfeae167020a9013160`.
debug: 4 correlations, 3 strong.
ects: 3 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E6230` | `0x170` |
| `func_150E63A0` | `0x3fc` |
| `func_150E679C` | `0x34` |
| `func_150E67D0` | `0xe0` |

### `src/game/game_137ED0.c`

Range `0x10aa20:0x10aee0`; 3 entries, 1,216 bytes.
SHA-1: `a5c07ae01687df5dc98d1129df428faf9b4dec19`.
debug: 3 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1510AA20` | `0x24` |
| `func_1510AA44` | `0x394` |
| `func_1510ADD8` | `0x108` |

### `src/game/game_1C02A0.c`

Range `0x192df0:0x193390`; 3 entries, 1,440 bytes.
SHA-1: `498329cd26f36e410605f15448998be81e92b1db`.
debug: 3 correlations, 1 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15192DF0` | `0x444` |
| `func_15193234` | `0xac` |
| `func_151932E0` | `0xb0` |

### `src/game/game_1DFE00.c`

Range `0x1b2950:0x1b2fd0`; 5 entries, 1,664 bytes.
SHA-1: `51e9a18566356dae40f9309da694855b6b6e77d6`.
debug: 5 correlations, 4 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B2950` | `0x24` |
| `func_151B2974` | `0x550` |
| `func_151B2EC4` | `0x40` |
| `func_151B2F04` | `0x9c` |
| `func_151B2FA0` | `0x30` |

### `src/game/game_204310.c`

Range `0x1d6e60:0x1d71b0`; 4 entries, 848 bytes.
SHA-1: `7c6ff27e17f9deccd7cf775ae3bea3e24f6d269a`.
debug: 4 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151D6E60` | `0x1a0` |
| `func_151D7000` | `0xcc` |
| `func_151D70CC` | `0x40` |
| `func_151D710C` | `0xa4` |

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
