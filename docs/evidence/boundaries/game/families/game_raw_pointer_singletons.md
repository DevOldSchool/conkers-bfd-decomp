# US pointer-selected singleton working units

Evidence kind: `structural_analysis`. These minimal working units isolate game-overlay functions selected by owned-ROM callback pointers. Each range is exactly one independently indexed raw function. Generic names derive from the raw ROM offsets; historical filenames and original compilation-unit boundaries remain unknown. All entries remain raw assembly.

The parent raw groups have exact agreement with the independent function CSV and no review errors or escaping branches at their outer endpoints. The singleton bounds use the indexed function start and raw span, and both endpoints are 16-byte aligned. Neighboring unselected functions receive no source-boundary credit.

| Source | US range | Bytes | Function | Owned selections | Parent raw group |
| --- | --- | ---: | --- | --- | --- |
| `src/game/game_D3D10.c` | `0xa6860:0xa6fa0` | 1,856 | `func_150A6860` | `0x8008B788` -> `func_150A6860` | `game_D3D10` |
| `src/game/game_E35C0.c` | `0xb6110:0xb6450` | 832 | `func_150B6110` | `0x8008A600` -> `func_150B6110` | `game_E35C0` |
| `src/game/game_E3C90.c` | `0xb67e0:0xb6bc0` | 992 | `func_150B67E0` | `0x8008968C` -> `func_150B67E0` | `game_E3C90` |
| `src/game/game_EB020.c` | `0xbdb70:0xbde90` | 800 | `func_150BDB70` | `0x800860A4` -> `func_150BDB70` | `game_EB020` |
| `src/game/game_F52B0.c` | `0xc7e00:0xc8350` | 1,360 | `func_150C7E00` | `0x80089688` -> `func_150C7E00` | `game_F52B0` |
| `src/game/game_FBBF0.c` | `0xce740:0xcef10` | 2,000 | `func_150CE740` | `0x80086090` -> `func_150CE740` | `game_FBBF0` |
| `src/game/game_FDD70.c` | `0xd08c0:0xd0e90` | 1,488 | `func_150D08C0` | `0x800896E8` -> `func_150D08C0` | `game_FDD70` |
| `src/game/game_FE9E0.c` | `0xd1530:0xd1810` | 736 | `func_150D1530` | `0x800896C0` -> `func_150D1530` | `game_FE9E0` |
| `src/game/game_FECC0.c` | `0xd1810:0xd1b40` | 816 | `func_150D1810` | `0x800891E0` -> `func_150D1810` | `game_FECC0` |
| `src/game/game_10E240.c` | `0xe0d90:0xe1060` | 720 | `func_150E0D90` | `0x800896A0` -> `func_150E0D90` | `game_10E240` |
| `src/game/game_147470.c` | `0x119fc0:0x11a410` | 1,104 | `func_15119FC0` | `0x80088D50` -> `func_15119FC0` | `game_142560` |
| `src/game/game_1FBB80.c` | `0x1ce6d0:0x1cea20` | 848 | `func_151CE6D0` | `0x8008A56C` -> `func_151CE6D0` | `game_1FA770` |

## Validation

### `src/game/game_D3D10.c`

Range `0xa6860:0xa6fa0`; one entry, 1,856 bytes.
Entry: `func_150A6860`; raw span `0x740`.
SHA-1: `f511144b790f4566641da5cb6081ecfa874f1738`.
Reference assembly: `reference/game/us/asm/A6860.s`.

### `src/game/game_E35C0.c`

Range `0xb6110:0xb6450`; one entry, 832 bytes.
Entry: `func_150B6110`; raw span `0x340`.
SHA-1: `010d048f0803690fa737616a69b3444964ac5b12`.
Reference assembly: `reference/game/us/asm/B58F0.s`.

### `src/game/game_E3C90.c`

Range `0xb67e0:0xb6bc0`; one entry, 992 bytes.
Entry: `func_150B67E0`; raw span `0x3e0`.
SHA-1: `abd4c45edcadb71f9af70ce25c28c1f39846d152`.
Reference assembly: `reference/game/us/asm/B67E0.s`.

### `src/game/game_EB020.c`

Range `0xbdb70:0xbde90`; one entry, 800 bytes.
Entry: `func_150BDB70`; raw span `0x320`.
SHA-1: `05a42a2ef0bb9ca548a780c5d50b877547040aee`.
Reference assembly: `reference/game/us/asm/BDB70.s`.

### `src/game/game_F52B0.c`

Range `0xc7e00:0xc8350`; one entry, 1,360 bytes.
Entry: `func_150C7E00`; raw span `0x550`.
SHA-1: `6e3361f56303fcb933ee6f6c700da3a83e4ec3f2`.
Reference assembly: `reference/game/us/asm/C7E00.s`.

### `src/game/game_FBBF0.c`

Range `0xce740:0xcef10`; one entry, 2,000 bytes.
Entry: `func_150CE740`; raw span `0x7d0`.
SHA-1: `a22324f00fd449a4e85cec66f9760648937df1ef`.
Reference assembly: `reference/game/us/asm/CE150.s`.

### `src/game/game_FDD70.c`

Range `0xd08c0:0xd0e90`; one entry, 1,488 bytes.
Entry: `func_150D08C0`; raw span `0x5d0`.
SHA-1: `1464b544d706c104db2b63ae5afb92d16192d64e`.
Reference assembly: `reference/game/us/asm/D08C0.s`.

### `src/game/game_FE9E0.c`

Range `0xd1530:0xd1810`; one entry, 736 bytes.
Entry: `func_150D1530`; raw span `0x2e0`.
SHA-1: `e2c702159fff1bbf9f216783e00d00d39c82e15a`.
Reference assembly: `reference/game/us/asm/D1530.s`.

### `src/game/game_FECC0.c`

Range `0xd1810:0xd1b40`; one entry, 816 bytes.
Entry: `func_150D1810`; raw span `0x330`.
SHA-1: `dea6e5c2599a8339a7f69d9df3f648fa4a3dc93b`.
Reference assembly: `reference/game/us/asm/D1810.s`.

### `src/game/game_10E240.c`

Range `0xe0d90:0xe1060`; one entry, 720 bytes.
Entry: `func_150E0D90`; raw span `0x2d0`.
SHA-1: `4fe41a2d89cec852efb90471c590dd20a3ea935d`.
Reference assembly: `reference/game/us/asm/E0D90.s`.

### `src/game/game_147470.c`

Range `0x119fc0:0x11a410`; one entry, 1,104 bytes.
Entry: `func_15119FC0`; raw span `0x450`.
SHA-1: `909c4aa6336d2bcda3e46b811f50f88f6eea2913`.
Reference assembly: `reference/game/us/asm/1150B0.s`.

### `src/game/game_1FBB80.c`

Range `0x1ce6d0:0x1cea20`; one entry, 848 bytes.
Entry: `func_151CE6D0`; raw span `0x350`.
SHA-1: `f093e0ab903542a7a8df646fb9187fb79048733c`.
Reference assembly: `reference/game/us/asm/1CD2C0.s`.

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
