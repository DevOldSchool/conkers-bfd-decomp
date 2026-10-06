# US pointer-table raw runs

Evidence kind: `structural_analysis`. These working source-family ranges contain only functions selected by owned-ROM pointer tables. Their generic names derive from raw ROM offsets; historical filenames and original compilation-unit boundaries remain unknown. All entries remain raw assembly.

Every member of each accepted range has a pointer-table selection. All endpoints are 16-byte aligned, owned-ROM words and member spans are exact, no conditional branch crosses an endpoint, and the raw labels agree exactly with the independent function CSV.

| Source | US range | Entries | Bytes | Owned selections |
| --- | --- | ---: | ---: | --- |
| `src/game/game_97AA0.c` | `0x6a5f0:0x6aae0` | 10 | 1,264 | `0x80086110` -> `func_1506A5F0`<br>`0x80086114` -> `func_1506A6FC`<br>`0x80086118` -> `func_1506A724`<br>`0x8008611c` -> `func_1506A760`<br>`0x80086120` -> `func_1506A79C`<br>`0x80086124` -> `func_1506A83C`<br>`0x80086128` -> `func_1506A864`<br>`0x8008612c` -> `func_1506A968`<br>`0x80086130` -> `func_1506AA08`<br>`0x80086134` -> `func_1506AA48` |
| `src/game/game_E5E90.c` | `0xb89e0:0xb9560` | 2 | 2,944 | `0x80089938` -> `func_150B89E0`<br>`0x80089978` -> `func_150B8F44` |
| `src/game/game_E8710.c` | `0xbb260:0xbb700` | 4 | 1,184 | `0x80089768` -> `func_150BB260`<br>`0x8008d5c4` -> `func_150BB408`<br>`0x80089c88` -> `func_150BB450`<br>`0x8008aa18` -> `func_150BB498` |
| `src/game/game_FC5F0.c` | `0xcf140:0xcf530` | 2 | 1,008 | `0x8008a5d0` -> `func_150CF140`<br>`0x8008a984` -> `func_150CF484` |
| `src/game/game_10A350.c` | `0xdcea0:0xdded0` | 2 | 4,144 | `0x8008a24c` -> `func_150DCEA0`<br>`0x8008a2b4` -> `func_150DD640` |
| `src/game/game_10BC70.c` | `0xde7c0:0xdebe0` | 3 | 1,056 | `0x8008a660` -> `func_150DE7C0`<br>`0x80089d58` -> `func_150DEACC`<br>`0x80089eb4` -> `func_150DEB58` |
| `src/game/game_117FC0.c` | `0xeab10:0xeaf50` | 2 | 1,088 | `0x8008a598` -> `func_150EAB10`<br>`0x8008b13c` -> `func_150EAE24` |
| `src/game/game_11CC60.c` | `0xef7b0:0xefb80` | 4 | 976 | `0x80089f14` -> `func_150EF7B0`<br>`0x80089f48` -> `func_150EF860`<br>`0x80089f78` -> `func_150EF910`<br>`0x8008f940` -> `func_150EFA4C` |
| `src/game/game_11FF10.c` | `0xf2a60:0xf33b0` | 7 | 2,384 | `0x8008cd5c` -> `func_150F2A60`<br>`0x8008ab44` -> `func_150F2C8C`<br>`0x8008a658` -> `func_150F2D14`<br>`0x8008a9e8` -> `func_150F3194`<br>`0x80089f8c` -> `func_150F31D4`<br>`0x80089d50` -> `func_150F3214`<br>`0x80089eb0` -> `func_150F337C` |
| `src/game/game_122A40.c` | `0xf5590:0xf56b0` | 3 | 288 | `0x8008ca44` -> `func_150F5590`<br>`0x8008ca48` -> `func_150F55C8`<br>`0x8008cd4c` -> `func_150F568C` |
| `src/game/game_123960.c` | `0xf64b0:0xf6890` | 3 | 992 | `0x8008a024` -> `func_150F64B0`<br>`0x8008a63c` -> `func_150F64DC`<br>`0x8008a9e0` -> `func_150F6850` |
| `src/game/game_12E540.c` | `0x101090:0x101f50` | 14 | 3,776 | `0x80089efc` -> `func_15101090`<br>`0x80089f30` -> `func_15101148`<br>`0x80089f00` -> `func_151011E8`<br>`0x80089f34` -> `func_15101210`<br>`0x8008b224` -> `func_15101238`<br>`0x8008b2cc` -> `func_15101260`<br>`0x80089818` -> `func_15101288`<br>`0x80089848` -> `func_151012B0`<br>`0x80089fa0` -> `func_151012D8`<br>`0x80089fe8` -> `func_15101300`<br>`0x80089828` -> `func_15101328`<br>`0x80089858` -> `func_15101350`<br>`0x80089d0c` -> `func_15101378`<br>`0x80089e64` -> `func_151019C4` |
| `src/game/game_142560.c` | `0x1150b0:0x1155c0` | 7 | 1,296 | `0x80088d98` -> `func_151150B0`<br>`0x80088ffc` -> `func_151150BC`<br>`0x80088cc0` -> `func_1511515C`<br>`0x80088f3c` -> `func_151151FC`<br>`0x80088f24` -> `func_1511529C`<br>`0x80088cd8` -> `func_151152A8`<br>`0x80088ce4` -> `func_15115368` |
| `src/game/game_1435C0.c` | `0x116110:0x1163c0` | 3 | 688 | `0x80088f0c` -> `func_15116110`<br>`0x80088ef4` -> `func_1511617C`<br>`0x80088e1c` -> `func_151162D4` |
| `src/game/game_144950.c` | `0x1174a0:0x1174f0` | 2 | 80 | `0x8008902c` -> `func_151174A0`<br>`0x80089044` -> `func_151174C8` |
| `src/game/game_177480.c` | `0x149fd0:0x14a6a0` | 6 | 1,744 | `0x80089e24` -> `func_15149FD0`<br>`0x80089d70` -> `func_1514A19C`<br>`0x80089d74` -> `func_1514A380`<br>`0x80089d78` -> `func_1514A498`<br>`0x80089ccc` -> `func_1514A4EC`<br>`0x80089cd0` -> `func_1514A594` |
| `src/game/game_1B9210.c` | `0x18bd60:0x18c900` | 6 | 2,976 | `0x8008baf4` -> `func_1518BD60`<br>`0x8008a3f4` -> `func_1518C0B8`<br>`0x8008a3fc` -> `func_1518C540`<br>`0x8008a438` -> `func_1518C57C`<br>`0x8008a454` -> `func_1518C69C`<br>`0x8008bb10` -> `func_1518C850` |
| `src/game/game_1BBFC0.c` | `0x18eb10:0x18f1a0` | 5 | 1,680 | `0x80089e34` -> `func_1518EB10`<br>`0x80089cd4` -> `func_1518EF54`<br>`0x80089cd8` -> `func_1518F058`<br>`0x80089d7c` -> `func_1518F108`<br>`0x80089d80` -> `func_1518F15C` |
| `src/game/game_1BDA00.c` | `0x190550:0x1906e0` | 3 | 400 | `0x8008fc68` -> `func_15190550`<br>`0x8008d67c` -> `func_151905BC`<br>`0x8008d680` -> `func_151906C4` |
| `src/game/game_1D4AC0.c` | `0x1a7610:0x1a7950` | 4 | 832 | `0x80089b00` -> `func_151A7610`<br>`0x8008ca18` -> `func_151A77C0`<br>`0x8008ca1c` -> `func_151A787C`<br>`0x80089980` -> `func_151A7908` |
| `src/game/game_1D9A00.c` | `0x1ac550:0x1aca60` | 5 | 1,296 | `0x8008a458` -> `func_151AC550`<br>`0x8008aa30` -> `func_151AC61C`<br>`0x80089e48` -> `func_151AC810`<br>`0x80089ce4` -> `func_151AC9EC`<br>`0x80089da4` -> `func_151ACA20` |
| `src/game/game_1DEF60.c` | `0x1b1ab0:0x1b2060` | 3 | 1,456 | `0x8008f858` -> `func_151B1AB0`<br>`0x8008a53c` -> `func_151B1B34`<br>`0x8008a91c` -> `func_151B1FAC` |
| `src/game/game_1E67C0.c` | `0x1b9310:0x1b9660` | 2 | 848 | `0x8008999c` -> `func_151B9310`<br>`0x8008b10c` -> `func_151B9408` |
| `src/game/game_1ED080.c` | `0x1bfbd0:0x1bfc40` | 2 | 112 | `0x8008a8d4` -> `func_151BFBD0`<br>`0x8008a9fc` -> `func_151BFBFC` |

The neighboring entries outside each range receive no source-boundary credit. Table selection establishes membership for every accepted function but does not recover the historical source name.

`game_ECC10` (`0xbf760:0xbffe0`) was excluded because the pointer review selected a function outside its proposed two-member range; that disagreement needs separate boundary work. `game_105ED0` (`0xd8a20:0xd8b10`) was excluded because both functions already belong to the reviewed `game_105D90` range.

## Validation

### `src/game/game_97AA0.c`

Range `0x6a5f0:0x6aae0`; 10 entries, 1,264 bytes.
SHA-1: `e342ebd90c2b64d5e1598770048ff1759109d68c`.
debug: 10 correlations, 6 strong.
ects: 10 correlations, 6 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1506A5F0` | `0x10c` |
| `func_1506A6FC` | `0x28` |
| `func_1506A724` | `0x3c` |
| `func_1506A760` | `0x3c` |
| `func_1506A79C` | `0xa0` |
| `func_1506A83C` | `0x28` |
| `func_1506A864` | `0x104` |
| `func_1506A968` | `0xa0` |
| `func_1506AA08` | `0x40` |
| `func_1506AA48` | `0x98` |

### `src/game/game_E5E90.c`

Range `0xb89e0:0xb9560`; 2 entries, 2,944 bytes.
SHA-1: `94bdd2acd8623a273a78f1fcf30028ea83c51cc8`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B89E0` | `0x564` |
| `func_150B8F44` | `0x61c` |

### `src/game/game_E8710.c`

Range `0xbb260:0xbb700`; 4 entries, 1,184 bytes.
SHA-1: `a48e292a6052a516f75925131ca0505514ceeec6`.
debug: 3 correlations, 2 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150BB260` | `0x1a8` |
| `func_150BB408` | `0x48` |
| `func_150BB450` | `0x48` |
| `func_150BB498` | `0x268` |

### `src/game/game_FC5F0.c`

Range `0xcf140:0xcf530`; 2 entries, 1,008 bytes.
SHA-1: `011032f37c72141db693b42cde1d35683afbae9b`.
debug: 2 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150CF140` | `0x344` |
| `func_150CF484` | `0xac` |

### `src/game/game_10A350.c`

Range `0xdcea0:0xdded0`; 2 entries, 4,144 bytes.
SHA-1: `2de061097e1d51363bdb19fbfe37744423a161cd`.
debug: 1 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150DCEA0` | `0x7a0` |
| `func_150DD640` | `0x890` |

### `src/game/game_10BC70.c`

Range `0xde7c0:0xdebe0`; 3 entries, 1,056 bytes.
SHA-1: `3784c459da242a8b256cab4665a9052a7bae436e`.
debug: 3 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150DE7C0` | `0x30c` |
| `func_150DEACC` | `0x8c` |
| `func_150DEB58` | `0x88` |

### `src/game/game_117FC0.c`

Range `0xeab10:0xeaf50`; 2 entries, 1,088 bytes.
SHA-1: `ae214a98104d8d540d37ed1f865b5e4f74a64a8c`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150EAB10` | `0x314` |
| `func_150EAE24` | `0x12c` |

### `src/game/game_11CC60.c`

Range `0xef7b0:0xefb80`; 4 entries, 976 bytes.
SHA-1: `46a5499ab899742b05662a01b4186041bff6edeb`.
debug: 4 correlations, 2 strong.
ects: 4 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150EF7B0` | `0xb0` |
| `func_150EF860` | `0xb0` |
| `func_150EF910` | `0x13c` |
| `func_150EFA4C` | `0x134` |

### `src/game/game_11FF10.c`

Range `0xf2a60:0xf33b0`; 7 entries, 2,384 bytes.
SHA-1: `526d630ae1c75931cf98e2ad9ac802ae39c4423f`.
debug: 5 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F2A60` | `0x22c` |
| `func_150F2C8C` | `0x88` |
| `func_150F2D14` | `0x480` |
| `func_150F3194` | `0x40` |
| `func_150F31D4` | `0x40` |
| `func_150F3214` | `0x168` |
| `func_150F337C` | `0x34` |

### `src/game/game_122A40.c`

Range `0xf5590:0xf56b0`; 3 entries, 288 bytes.
SHA-1: `a8e9c38423bc457116436cab94216378903d8621`.
debug: 3 correlations, 2 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F5590` | `0x38` |
| `func_150F55C8` | `0xc4` |
| `func_150F568C` | `0x24` |

### `src/game/game_123960.c`

Range `0xf64b0:0xf6890`; 3 entries, 992 bytes.
SHA-1: `09f84e40c8219429c51df8d498dec8f69e1a3149`.
debug: 3 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F64B0` | `0x2c` |
| `func_150F64DC` | `0x374` |
| `func_150F6850` | `0x40` |

### `src/game/game_12E540.c`

Range `0x101090:0x101f50`; 14 entries, 3,776 bytes.
SHA-1: `5354505ee43de9096c4d2a50f8ddc548a40dbb0e`.
debug: 13 correlations, 3 strong.
ects: 12 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15101090` | `0xb8` |
| `func_15101148` | `0xa0` |
| `func_151011E8` | `0x28` |
| `func_15101210` | `0x28` |
| `func_15101238` | `0x28` |
| `func_15101260` | `0x28` |
| `func_15101288` | `0x28` |
| `func_151012B0` | `0x28` |
| `func_151012D8` | `0x28` |
| `func_15101300` | `0x28` |
| `func_15101328` | `0x28` |
| `func_15101350` | `0x28` |
| `func_15101378` | `0x64c` |
| `func_151019C4` | `0x58c` |

### `src/game/game_142560.c`

Range `0x1150b0:0x1155c0`; 7 entries, 1,296 bytes.
SHA-1: `e2a6b1c49baf80abcc833ded5ae19354c56450ba`.
debug: 7 correlations, 2 strong.
ects: 7 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151150B0` | `0xc` |
| `func_151150BC` | `0xa0` |
| `func_1511515C` | `0xa0` |
| `func_151151FC` | `0xa0` |
| `func_1511529C` | `0xc` |
| `func_151152A8` | `0xc0` |
| `func_15115368` | `0x258` |

### `src/game/game_1435C0.c`

Range `0x116110:0x1163c0`; 3 entries, 688 bytes.
SHA-1: `74c104a619dc9c2be99585c095c63e340289af79`.
debug: 3 correlations, 3 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15116110` | `0x6c` |
| `func_1511617C` | `0x158` |
| `func_151162D4` | `0xec` |

### `src/game/game_144950.c`

Range `0x1174a0:0x1174f0`; 2 entries, 80 bytes.
SHA-1: `fa94b6198384e11901a34fb2c18405ef42c95e66`.
debug: 2 correlations, 0 strong.
ects: 2 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151174A0` | `0x28` |
| `func_151174C8` | `0x28` |

### `src/game/game_177480.c`

Range `0x149fd0:0x14a6a0`; 6 entries, 1,744 bytes.
SHA-1: `9f59108cbed9e4aec7e42bf5c968f7112560642b`.
debug: 6 correlations, 4 strong.
ects: 5 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15149FD0` | `0x1cc` |
| `func_1514A19C` | `0x1e4` |
| `func_1514A380` | `0x118` |
| `func_1514A498` | `0x54` |
| `func_1514A4EC` | `0xa8` |
| `func_1514A594` | `0x10c` |

### `src/game/game_1B9210.c`

Range `0x18bd60:0x18c900`; 6 entries, 2,976 bytes.
SHA-1: `f0a2fd327eed04016aa61c3b3b4e1241811794cb`.
debug: 4 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1518BD60` | `0x358` |
| `func_1518C0B8` | `0x488` |
| `func_1518C540` | `0x3c` |
| `func_1518C57C` | `0x120` |
| `func_1518C69C` | `0x1b4` |
| `func_1518C850` | `0xb0` |

### `src/game/game_1BBFC0.c`

Range `0x18eb10:0x18f1a0`; 5 entries, 1,680 bytes.
SHA-1: `08358edff14ec4be397b7642c6e06fd0ad0b1895`.
debug: 5 correlations, 3 strong.
ects: 4 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1518EB10` | `0x444` |
| `func_1518EF54` | `0x104` |
| `func_1518F058` | `0xb0` |
| `func_1518F108` | `0x54` |
| `func_1518F15C` | `0x44` |

### `src/game/game_1BDA00.c`

Range `0x190550:0x1906e0`; 3 entries, 400 bytes.
SHA-1: `c8ebfc8b717cdfa2c1d77b3651f89cb3023cd208`.
debug: 3 correlations, 3 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15190550` | `0x6c` |
| `func_151905BC` | `0x108` |
| `func_151906C4` | `0x1c` |

### `src/game/game_1D4AC0.c`

Range `0x1a7610:0x1a7950`; 4 entries, 832 bytes.
SHA-1: `3538691ae1876cb9c42284dbeded47a43f5febc3`.
debug: 4 correlations, 4 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151A7610` | `0x1b0` |
| `func_151A77C0` | `0xbc` |
| `func_151A787C` | `0x8c` |
| `func_151A7908` | `0x48` |

### `src/game/game_1D9A00.c`

Range `0x1ac550:0x1aca60`; 5 entries, 1,296 bytes.
SHA-1: `49679c7f3e4d71d14bc5ffa542d1d51fbe1129d3`.
debug: 4 correlations, 2 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151AC550` | `0xcc` |
| `func_151AC61C` | `0x1f4` |
| `func_151AC810` | `0x1dc` |
| `func_151AC9EC` | `0x34` |
| `func_151ACA20` | `0x40` |

### `src/game/game_1DEF60.c`

Range `0x1b1ab0:0x1b2060`; 3 entries, 1,456 bytes.
SHA-1: `772c015fae99ad239f073190ec6cfc0da9b4f402`.
debug: 3 correlations, 1 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B1AB0` | `0x84` |
| `func_151B1B34` | `0x478` |
| `func_151B1FAC` | `0xb4` |

### `src/game/game_1E67C0.c`

Range `0x1b9310:0x1b9660`; 2 entries, 848 bytes.
SHA-1: `2a8d73f977794d8e89fc5e5a92fa99fad76c1c43`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B9310` | `0xf8` |
| `func_151B9408` | `0x258` |

### `src/game/game_1ED080.c`

Range `0x1bfbd0:0x1bfc40`; 2 entries, 112 bytes.
SHA-1: `8dc9b3103652db197c61e11ef74a1f95d3a6da15`.
debug: 1 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151BFBD0` | `0x2c` |
| `func_151BFBFC` | `0x44` |

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
