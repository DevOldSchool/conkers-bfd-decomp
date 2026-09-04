# US callback-table runs and handler block

Evidence kind: `structural_analysis`. These four reviewed ranges remain raw assembly and use offset-derived source names. Historical filenames and original compilation units remain unknown.

All ranges have 16-byte-aligned endpoints, exact owned-ROM words, complete member-span coverage, no conditional branch crossing an endpoint, and exact agreement with the independent function CSV.

## Three-entry callback run: `0xD7420:0xD7630`

Owned consecutive words `8008A05C`, `8008A060`, and `8008A064` select the three contiguous entries `150D7420`, `150D74DC`, and `150D758C`. Neighboring slots point outside this range, establishing the bounded local run.

## Two-entry sparse callback pair: `0x10A870:0x10A930`

Owned words `8008A940` and `8008A948` select the two contiguous entries `1510A870` and `1510A8CC`; the intervening slot at `8008A944` is null. The following non-null slot selects `1519277C` outside this range.

## Three-entry sparse callback run: `0x11E780:0x11EF40`

Owned words `80088FB4`, `80088FC0`, and `80088FCC`, separated by two null slots each, select exactly the three contiguous members `1511EC50`, `1511ED84`, and `1511E780`. The preceding non-null slot `80088FA8` selects the following raw-map entry `1511EF40`, so it is excluded from this range.

## Multi-table handler block: `0x1A99D0:0x1AB930`

This complete raw-map interval contains 37 entries. Thirty-two are selected by owned callback words. The first thirteen form an uninterrupted table run at `8008AFD0:8008B004`; later entries occupy the same continuing table at `8008B004`, `8008B008`, `8008B00C`, `8008B010`, and `8008B024`, plus related engine tables at `80089A78:80089CAC`, `80089B20:80089B8C`, and `8008A41C`.

Three otherwise unselected local helpers are connected by direct calls: `151AA264` is called from `151A9CA0`, `151A9EC0`, and `151AB1C4`; `151AA48C` and `151AB2C4` are called from table-selected `151AAABC`. This accounts for 35 of 37 entries through owned table selection or local calls.

The remaining `151AABC4` uses the same contiguous constant family: `800A8F70`, immediately preceding `800A8F74:800A8F90` used by the opening table run, and `800A8FCC:800A8FDC` before later block constants. Terminal `151AB920` is a compact no-op argument sink at the aligned map endpoint. The next raw interval begins at `0x1AB930`; it is not absorbed into this handler block.

## Excluded candidate

`0x15BAE0:0x15BE50` is not registered. The independent CSV contains an extra entry at `1515BE48` that the raw assembly labels fold into the preceding function, so membership is unresolved.

## Validation

Independent member lists and beta correlations follow. Correlations support entry identity and layout, without proving historical names.

### `src/game/game_1048D0.c`

Range `0xd7420:0xd7630`; 3 entries, 528 bytes.
SHA-1: `35a6ec4d43542915d9fbae3ff969e41b93ce8d2b`.
debug: 3 correlations, 3 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D7420` | `0xbc` |
| `func_150D74DC` | `0xb0` |
| `func_150D758C` | `0xa4` |

### `src/game/game_137D20.c`

Range `0x10a870:0x10a930`; 2 entries, 192 bytes.
SHA-1: `04bc118b903fc6decc9565e36cea53e9989c0330`.
debug: 2 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1510A870` | `0x5c` |
| `func_1510A8CC` | `0x64` |

### `src/game/game_14BC30.c`

Range `0x11e780:0x11ef40`; 3 entries, 1,984 bytes.
SHA-1: `1237c2fad85e5258a889235fc1708c1a4c3c86b1`.
debug: 2 correlations, 0 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1511E780` | `0x4d0` |
| `func_1511EC50` | `0x134` |
| `func_1511ED84` | `0x1bc` |

### `src/game/game_1D6E80.c`

Range `0x1a99d0:0x1ab930`; 37 entries, 8,032 bytes.
SHA-1: `b65eec2a49534fe0e02516977329a90197e3f2a7`.
debug: 36 correlations, 13 strong.
ects: 15 correlations, 7 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151A99D0` | `0xd4` |
| `func_151A9AA4` | `0xfc` |
| `func_151A9BA0` | `0x100` |
| `func_151A9CA0` | `0x120` |
| `func_151A9DC0` | `0x100` |
| `func_151A9EC0` | `0x108` |
| `func_151A9FC8` | `0xd4` |
| `func_151AA09C` | `0xd4` |
| `func_151AA170` | `0xc` |
| `func_151AA17C` | `0x54` |
| `func_151AA1D0` | `0x20` |
| `func_151AA1F0` | `0x20` |
| `func_151AA210` | `0x54` |
| `func_151AA264` | `0xa8` |
| `func_151AA30C` | `0x180` |
| `func_151AA48C` | `0x118` |
| `func_151AA5A4` | `0x134` |
| `func_151AA6D8` | `0x374` |
| `func_151AAA4C` | `0x70` |
| `func_151AAABC` | `0x94` |
| `func_151AAB50` | `0x28` |
| `func_151AAB78` | `0x28` |
| `func_151AABA0` | `0x24` |
| `func_151AABC4` | `0x1f8` |
| `func_151AADBC` | `0x3c` |
| `func_151AADF8` | `0x298` |
| `func_151AB090` | `0xf0` |
| `func_151AB180` | `0x44` |
| `func_151AB1C4` | `0x100` |
| `func_151AB2C4` | `0xe0` |
| `func_151AB3A4` | `0x314` |
| `func_151AB6B8` | `0xd0` |
| `func_151AB788` | `0x50` |
| `func_151AB7D8` | `0x50` |
| `func_151AB828` | `0x2c` |
| `func_151AB854` | `0xcc` |
| `func_151AB920` | `0x10` |

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
