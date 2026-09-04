# US complete callback and local-helper clusters

Evidence kind: `structural_analysis`. These are working source-family ranges with offset-derived names. Original filenames and historical compilation-unit boundaries remain unknown. All entries remain raw assembly.

Every member in each accepted range is either selected by an owned function-pointer word or participates in a direct call to another local member. Each range has 16-byte-aligned endpoints, exact owned-ROM words, complete entry-span coverage, no conditional branch crossing an endpoint, and exact raw-label agreement with the independent function CSV.

| Source | US range | Entries | Bytes | Owned pointer selections | Direct local calls |
| --- | --- | ---: | ---: | --- | --- |
| `src/game/game_DF930.c` | `0xb2480:0xb2740` | 3 | 704 | `0x8008a094` → `func_150B2480`<br>`0x8008a104` → `func_150B2494`<br>`0x8008aa1c` → `func_150B2570` | none |
| `src/game/game_EEE70.c` | `0xc19c0:0xc1f60` | 4 | 1,440 | `0x8008a088` → `func_150C1A2C`<br>`0x8008a0ec` → `func_150C1A40`<br>`0x8008aa00` → `func_150C1E34` | `func_150C1A40` → `func_150C19C0` at `0xc1aac` |
| `src/game/game_F4B20.c` | `0xc7670:0xc7770` | 2 | 256 | `0x8008992c` → `func_150C7670`<br>`0x80089998` → `func_150C773C` | none |
| `src/game/game_F4D20.c` | `0xc7870:0xc7e00` | 7 | 1,424 | `0x80088dd4` → `func_150C7870`<br>`0x80088df8` → `func_150C78E0`<br>`0x80088e04` → `func_150C7930`<br>`0x80088e10` → `func_150C7968`<br>`0x8008cd24` → `func_150C79BC`<br>`0x80088dc8` → `func_150C7C90`<br>`0x80089098` → `func_150C7D7C` | none |
| `src/game/game_F8590.c` | `0xcb0e0:0xcbf80` | 10 | 3,744 | `0x8008a098` → `func_150CB1E0`<br>`0x8008a10c` → `func_150CB1F4`<br>`0x80089c98` → `func_150CB7CC`<br>`0x8008aa3c` → `func_150CB800`<br>`0x80089dbc` → `func_150CBA30`<br>`0x8008aa38` → `func_150CBABC`<br>`0x8008977c` → `func_150CBCE0`<br>`0x800898b8` → `func_150CBE88`<br>`0x8008d5c8` → `func_150CBF5C` | `func_150CB1F4` → `func_150CB0E0` at `0xcb224` |
| `src/game/game_FE850.c` | `0xd13a0:0xd1530` | 4 | 400 | `0x800860b4` → `func_150D13A0`<br>`0x80086008` → `func_150D1410`<br>`0x80086010` → `func_150D146C`<br>`0x8008a608` → `func_150D149C` | none |
| `src/game/game_FEFF0.c` | `0xd1b40:0xd1c30` | 2 | 240 | `0x8008a604` → `func_150D1B40`<br>`0x800896ec` → `func_150D1BD0` | none |
| `src/game/game_1114C0.c` | `0xe4010:0xe41c0` | 3 | 432 | `0x8008fbd4` → `func_150E4010`<br>`0x8008fbd8` → `func_150E411C`<br>`0x80089d40` → `func_150E4174` | none |
| `src/game/game_118400.c` | `0xeaf50:0xeb1c0` | 3 | 624 | `0x8008a0a0` → `func_150EB030`<br>`0x8008a11c` → `func_150EB090` | `func_150EB090` → `func_150EAF50` at `0xeb0c0` |
| `src/game/game_1199D0.c` | `0xec520:0xed1d0` | 7 | 3,248 | `0x8008a64c` → `func_150EC520`<br>`0x8008a650` → `func_150EC6B0`<br>`0x8008a9ec` → `func_150ECB4C`<br>`0x8008a65c` → `func_150ECB8C`<br>`0x800896b4` → `func_150ECC70` | `func_150ECC00` → `func_150ECA68` at `0xecc58` |
| `src/game/game_122760.c` | `0xf52b0:0xf5340` | 2 | 144 | `0x800896f8` → `func_150F52B0`<br>`0x8008cd58` → `func_150F5310` | none |
| `src/game/game_12BD10.c` | `0xfe860:0xfed30` | 3 | 1,232 | `0x8008fc84` → `func_150FEBC8` | `func_150FE860` → `func_150FEC28` at `0xfebac` |
| `src/game/game_135780.c` | `0x1082d0:0x108850` | 3 | 1,408 | `0x8008a580` → `func_151082D0`<br>`0x800897c0` → `func_15108658`<br>`0x8008a968` → `func_151087FC` | none |
| `src/game/game_183640.c` | `0x156190:0x157010` | 10 | 3,712 | `0x8008bd98` → `func_151563B8`<br>`0x8008c584` → `func_151563B8`<br>`0x8008bda0` → `func_151564F8`<br>`0x8008c58c` → `func_151564F8`<br>`0x8008a504` → `func_15156B54`<br>`0x8008bdc0` → `func_15156FB8`<br>`0x8008c5ac` → `func_15156FB8`<br>`0x8008bdc4` → `func_15156FE4`<br>`0x8008c5b0` → `func_15156FE4` | `func_15156388` → `func_15156190` at `0x1563a0`<br>`func_15156B54` → `func_15156D24` at `0x156c20`<br>`func_15156D24` → `func_151568F8` at `0x156f7c`<br>`func_15156FB8` → `func_15156F94` at `0x156fc4`<br>`func_15156FE4` → `func_15156F94` at `0x156ff0` |
| `src/game/game_197120.c` | `0x169c70:0x16a770` | 4 | 2,816 | `0x8008ca28` → `func_15169C70`<br>`0x8008c9e4` → `func_1516A3F4`<br>`0x8008ca2c` → `func_1516A538`<br>`0x8008cbbc` → `func_1516A648` | none |
| `src/game/game_1B81D0.c` | `0x18ad20:0x18b6b0` | 5 | 2,448 | `0x8008991c` → `func_1518AD20`<br>`0x80089920` → `func_1518B1AC`<br>`0x80089924` → `func_1518B1D8` | `func_1518B264` → `func_1518B2A8` at `0x18b290` |
| `src/game/game_1C0840.c` | `0x193390:0x193660` | 2 | 720 | `0x8008a4c4` → `func_15193390`<br>`0x8008ca04` → `func_151934B4` | none |
| `src/game/game_1DCA70.c` | `0x1af5c0:0x1b0050` | 7 | 2,704 | `0x8008a09c` → `func_151AF6C0`<br>`0x8008a114` → `func_151AF6D4`<br>`0x80089c9c` → `func_151AFBD4`<br>`0x80089db8` → `func_151AFC08`<br>`0x8008aa40` → `func_151AFC88`<br>`0x80089778` → `func_151AFEA4` | `func_151AF6D4` → `func_151AF5C0` at `0x1af70c` |

The three-entry `0x1082D0:0x108850` block is the previously retained update/child/event callback candidate. Its owned selections are now explicit: `8008A580` selects `151082D0`, `800897C0` selects `15108658`, and `8008A968` selects `151087FC`. This accounts for every member without relying on adjacency.

The `0xEAF50:0xEB1C0` block similarly accounts for every member: table words select `150EB030` and `150EB090`, and the latter directly calls the local helper `150EAF50`.

For larger ranges, the table and call coverage is complete rather than sample-based. Correlation data below supports identity, without proving historical filenames.

## Validation

### `src/game/game_DF930.c`

Range `0xb2480:0xb2740`; 3 entries, 704 bytes.
SHA-1: `5bfd532577cf5e80e638af3eb7dec5e8df2cf9a3`.
debug: 3 correlations, 2 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B2480` | `0x14` |
| `func_150B2494` | `0xdc` |
| `func_150B2570` | `0x1d0` |

### `src/game/game_EEE70.c`

Range `0xc19c0:0xc1f60`; 4 entries, 1,440 bytes.
SHA-1: `dd122df3d66c2b1521f39c16b069a80c9bf152d4`.
debug: 4 correlations, 3 strong.
ects: 3 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C19C0` | `0x6c` |
| `func_150C1A2C` | `0x14` |
| `func_150C1A40` | `0x3f4` |
| `func_150C1E34` | `0x12c` |

### `src/game/game_F4B20.c`

Range `0xc7670:0xc7770`; 2 entries, 256 bytes.
SHA-1: `3cd2c7f4e9a75812d12ced16720e2de680a31d96`.
debug: 1 correlations, 0 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C7670` | `0xcc` |
| `func_150C773C` | `0x34` |

### `src/game/game_F4D20.c`

Range `0xc7870:0xc7e00`; 7 entries, 1,424 bytes.
SHA-1: `0448bf27c04115490324313b6842aa17543d50fc`.
debug: 5 correlations, 5 strong.
ects: 4 correlations, 4 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C7870` | `0x70` |
| `func_150C78E0` | `0x50` |
| `func_150C7930` | `0x38` |
| `func_150C7968` | `0x54` |
| `func_150C79BC` | `0x2d4` |
| `func_150C7C90` | `0xec` |
| `func_150C7D7C` | `0x84` |

### `src/game/game_F8590.c`

Range `0xcb0e0:0xcbf80`; 10 entries, 3,744 bytes.
SHA-1: `6958cd029fe5f0a5ed32221559998c8f9473346b`.
debug: 8 correlations, 3 strong.
ects: 5 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150CB0E0` | `0x100` |
| `func_150CB1E0` | `0x14` |
| `func_150CB1F4` | `0x5d8` |
| `func_150CB7CC` | `0x34` |
| `func_150CB800` | `0x230` |
| `func_150CBA30` | `0x8c` |
| `func_150CBABC` | `0x224` |
| `func_150CBCE0` | `0x1a8` |
| `func_150CBE88` | `0xd4` |
| `func_150CBF5C` | `0x24` |

### `src/game/game_FE850.c`

Range `0xd13a0:0xd1530`; 4 entries, 400 bytes.
SHA-1: `b4229bb44441e474549086906cf948363884b77a`.
debug: 4 correlations, 4 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D13A0` | `0x70` |
| `func_150D1410` | `0x5c` |
| `func_150D146C` | `0x30` |
| `func_150D149C` | `0x94` |

### `src/game/game_FEFF0.c`

Range `0xd1b40:0xd1c30`; 2 entries, 240 bytes.
SHA-1: `d538017ff68c94ccf8c2cc21980691770e42ce7c`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D1B40` | `0x90` |
| `func_150D1BD0` | `0x60` |

### `src/game/game_1114C0.c`

Range `0xe4010:0xe41c0`; 3 entries, 432 bytes.
SHA-1: `786357c81cca1b531498f1a2335a578701370ae8`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E4010` | `0x10c` |
| `func_150E411C` | `0x58` |
| `func_150E4174` | `0x4c` |

### `src/game/game_118400.c`

Range `0xeaf50:0xeb1c0`; 3 entries, 624 bytes.
SHA-1: `8ac38dc593d9622c0c6e51cf06037047f368db1b`.
debug: 3 correlations, 2 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150EAF50` | `0xe0` |
| `func_150EB030` | `0x60` |
| `func_150EB090` | `0x130` |

### `src/game/game_1199D0.c`

Range `0xec520:0xed1d0`; 7 entries, 3,248 bytes.
SHA-1: `6069dd10cda97156f1ff45512184088ac63adbb2`.
debug: 7 correlations, 6 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150EC520` | `0x190` |
| `func_150EC6B0` | `0x3b8` |
| `func_150ECA68` | `0xe4` |
| `func_150ECB4C` | `0x40` |
| `func_150ECB8C` | `0x74` |
| `func_150ECC00` | `0x70` |
| `func_150ECC70` | `0x560` |

### `src/game/game_122760.c`

Range `0xf52b0:0xf5340`; 2 entries, 144 bytes.
SHA-1: `c29daceb4f56c48474f8fafce23dcf6fff7780e9`.
debug: 1 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F52B0` | `0x60` |
| `func_150F5310` | `0x30` |

### `src/game/game_12BD10.c`

Range `0xfe860:0xfed30`; 3 entries, 1,232 bytes.
SHA-1: `ee6ddd3a13f0d1a5158df0d0ac8f163f131861ba`.
debug: 1 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150FE860` | `0x368` |
| `func_150FEBC8` | `0x60` |
| `func_150FEC28` | `0x108` |

### `src/game/game_135780.c`

Range `0x1082d0:0x108850`; 3 entries, 1,408 bytes.
SHA-1: `ef048c57d8db28eb174752b88b84c5bd2a485748`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151082D0` | `0x388` |
| `func_15108658` | `0x1a4` |
| `func_151087FC` | `0x54` |

### `src/game/game_183640.c`

Range `0x156190:0x157010`; 10 entries, 3,712 bytes.
SHA-1: `93305939efa020e14cfdb1efc01ef84282307f3c`.
debug: 8 correlations, 5 strong.
ects: 4 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15156190` | `0x1f8` |
| `func_15156388` | `0x30` |
| `func_151563B8` | `0x140` |
| `func_151564F8` | `0x400` |
| `func_151568F8` | `0x25c` |
| `func_15156B54` | `0x1d0` |
| `func_15156D24` | `0x270` |
| `func_15156F94` | `0x24` |
| `func_15156FB8` | `0x2c` |
| `func_15156FE4` | `0x2c` |

### `src/game/game_197120.c`

Range `0x169c70:0x16a770`; 4 entries, 2,816 bytes.
SHA-1: `413f903cbdd6056fc7038be12693cd6bd7a6a98a`.
debug: 4 correlations, 4 strong.
ects: 4 correlations, 4 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15169C70` | `0x784` |
| `func_1516A3F4` | `0x144` |
| `func_1516A538` | `0x110` |
| `func_1516A648` | `0x128` |

### `src/game/game_1B81D0.c`

Range `0x18ad20:0x18b6b0`; 5 entries, 2,448 bytes.
SHA-1: `f0372fd49a265f61969b945933da2039509a5b14`.
debug: 5 correlations, 5 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1518AD20` | `0x48c` |
| `func_1518B1AC` | `0x2c` |
| `func_1518B1D8` | `0x8c` |
| `func_1518B264` | `0x44` |
| `func_1518B2A8` | `0x408` |

### `src/game/game_1C0840.c`

Range `0x193390:0x193660`; 2 entries, 720 bytes.
SHA-1: `409d8b557079a54d2841c9090753188bdc0c9468`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15193390` | `0x124` |
| `func_151934B4` | `0x1ac` |

### `src/game/game_1DCA70.c`

Range `0x1af5c0:0x1b0050`; 7 entries, 2,704 bytes.
SHA-1: `d717c1f202d59847c85b3fc4a64ba5af0915cd65`.
debug: 5 correlations, 2 strong.
ects: 4 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151AF5C0` | `0x100` |
| `func_151AF6C0` | `0x14` |
| `func_151AF6D4` | `0x500` |
| `func_151AFBD4` | `0x34` |
| `func_151AFC08` | `0x80` |
| `func_151AFC88` | `0x21c` |
| `func_151AFEA4` | `0x1ac` |

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
