# US direct helper and callback pairs

Evidence kind: `structural_analysis`. These eleven ranges are working source-family boundaries named from their raw ROM offsets. Original filenames and historical compilation units remain unknown. All entries remain raw assembly.

Each accepted range has 16-byte-aligned endpoints, exact owned-ROM words, complete entry coverage, no conditional branch crossing an endpoint, and exact raw-label agreement with the independent function CSV. Every pair or triplet is connected by a direct local call. Owned callback-table words add selection evidence where present.

- `src/game/game_A9820.c`, `0x7C370:0x7C8E0`: `1507C370` directly calls its sole following local member `1507C3E0` at `0x7C3AC`.
- `src/game/game_E7DE0.c`, `0xBA930:0xBABE0`: owned table words `8008A090` and `8008A0FC` select `150BAA00` and `150BAA14`; the latter calls local helper `150BA930` at `0xBAA44`.
- `src/game/game_F2730.c`, `0xC5280:0xC5370`: table words `8008ADB8` and `80089910` select wrappers `150C52CC` and `150C5310`; both call local helper `150C5280`.
- `src/game/game_114740.c`, `0xE7290:0xE76D0`: `150E7290` directly calls its sole local companion `150E75A0` at `0xE743C`.
- `src/game/game_120950.c`, `0xF34A0:0xF43F0`: table word `80086068` selects `150F34F4`, which calls local helper `150F34A0` at `0xF42F0`.
- `src/game/game_1286F0.c`, `0xFB240:0xFB2E0`: table word `8008AD9C` selects `150FB29C`, which calls local helper `150FB240` at `0xFB2C0`.
- `src/game/game_147C70.c`, `0x11A7C0:0x11AF30`: table word `80088E28` selects `1511A838`, which calls local helper `1511A7C0` at `0x11AB70`.
- `src/game/game_197C20.c`, `0x16A770:0x16AA70`: `1516A7B0` calls the preceding local helper `1516A770` at `0x16A8EC`.
- `src/game/game_19EAB0.c`, `0x171600:0x1718F0`: `15171600` calls its sole local companion `151717FC` four times at `0x1716A0`, `0x171708`, `0x171778`, and `0x1717E4`.
- `src/game/game_1D3420.c`, `0x1A5F70:0x1A6350`: table word `8008A988` selects `151A5F70`, which calls local `151A6068` at `0x1A6038`.
- `src/game/game_1FC0C0.c`, `0x1CEC10:0x1CF120`: table word `8008A278` selects `151CEC54`, which calls local helper `151CEC10` at `0x1CECD8`.

The neighboring proposed subranges at `0x84D70`, `0x85710`, `0xFE860`, `0x18BA90`, and `0x18D1C0` remain unregistered. Although each contains local call edges, one or more intervening members are not connected by that evidence. Adjacency alone is insufficient.

## Validation

Independent member lists and beta correlations follow. Correlations support entry identity, without proving an original source filename or compilation boundary.

### `src/game/game_A9820.c`

Range `0x7c370:0x7c8e0`; 2 entries, 1,392 bytes.
SHA-1: `8db72a227fc4144f0214de143ebd638f405d7cd3`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1507C370` | `0x70` |
| `func_1507C3E0` | `0x500` |

### `src/game/game_E7DE0.c`

Range `0xba930:0xbabe0`; 3 entries, 688 bytes.
SHA-1: `6165d6595179c170564233bcd540ddae32168215`.
debug: 2 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150BA930` | `0xd0` |
| `func_150BAA00` | `0x14` |
| `func_150BAA14` | `0x1cc` |

### `src/game/game_F2730.c`

Range `0xc5280:0xc5370`; 3 entries, 240 bytes.
SHA-1: `47c496ba81a0f0bb6834b061d731b5cc0ecaa3e1`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C5280` | `0x4c` |
| `func_150C52CC` | `0x44` |
| `func_150C5310` | `0x60` |

### `src/game/game_114740.c`

Range `0xe7290:0xe76d0`; 2 entries, 1,088 bytes.
SHA-1: `fa8e5ebe91979e92c763f547d147617dd9d858c3`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E7290` | `0x310` |
| `func_150E75A0` | `0x130` |

### `src/game/game_120950.c`

Range `0xf34a0:0xf43f0`; 2 entries, 3,920 bytes.
SHA-1: `c634b04f516a38d013bc209c995cce9530df753c`.
debug: 1 correlations, 0 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F34A0` | `0x54` |
| `func_150F34F4` | `0xefc` |

### `src/game/game_1286F0.c`

Range `0xfb240:0xfb2e0`; 2 entries, 160 bytes.
SHA-1: `b2e12bfb2dd6afa302a82b45c3c4375fcda0f186`.
debug: 2 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150FB240` | `0x5c` |
| `func_150FB29C` | `0x44` |

### `src/game/game_147C70.c`

Range `0x11a7c0:0x11af30`; 2 entries, 1,904 bytes.
SHA-1: `8ff4ef5f30b3231fe620c3b1d05fa779e4e0f92e`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1511A7C0` | `0x78` |
| `func_1511A838` | `0x6f8` |

### `src/game/game_197C20.c`

Range `0x16a770:0x16aa70`; 2 entries, 768 bytes.
SHA-1: `b2d5e3fedddccae8b8d912f2777cea8756be1961`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1516A770` | `0x40` |
| `func_1516A7B0` | `0x2c0` |

### `src/game/game_19EAB0.c`

Range `0x171600:0x1718f0`; 2 entries, 752 bytes.
SHA-1: `f712523678e43f033b1a6eadabab63cb6d85ed90`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15171600` | `0x1fc` |
| `func_151717FC` | `0xf4` |

### `src/game/game_1D3420.c`

Range `0x1a5f70:0x1a6350`; 2 entries, 992 bytes.
SHA-1: `19dd39ebf09287196cdf8eac2ed2c99735816638`.
debug: 1 correlations, 1 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151A5F70` | `0xf8` |
| `func_151A6068` | `0x2e8` |

### `src/game/game_1FC0C0.c`

Range `0x1cec10:0x1cf120`; 2 entries, 1,296 bytes.
SHA-1: `5792d99a970b40c95a34a51a13b0e6e356bbd287`.
debug: 1 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151CEC10` | `0x44` |
| `func_151CEC54` | `0x4cc` |

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
