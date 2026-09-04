# US table-selected callback collections

Evidence kind: `structural_analysis`. These two working source-family ranges use offset-derived names; original filenames and compilation-unit boundaries remain unknown. All members remain raw assembly.

`src/game/game_DE5A0.c` covers `0xB10F0:0xB1DB0`. All five contiguous members are selected by owned words in the resource/handler table: `80086054` selects `150B10F0`, while `80086030`, `80086038`, `80086040`, and `8008603C` select `150B12FC`, `150B1484`, `150B17DC`, and `150B19E0`.

`src/game/game_11F890.c` covers `0xF23E0:0xF26A0`, the four table-selected callbacks immediately following the previously reviewed helper triplet. Owned words `800898F0`, `80089C24`, `80089C40`, and `8008B148` select `150F23E0`, `150F2480`, `150F2518`, and `150F25A0`. The boundary begins after the first triplet's internal call chain and ends at the existing aligned raw-map endpoint.

Both ranges have 16-byte-aligned endpoints, exact owned-ROM words, complete member-span coverage, no conditional branch crossing an endpoint, and exact raw-label agreement with the independent function CSV.

## Validation

Independent member lists and beta correlations follow. Correlations support entry identity, without proving historical filenames.

### `src/game/game_DE5A0.c`

Range `0xb10f0:0xb1db0`; 5 entries, 3,264 bytes.
SHA-1: `f7a781b9b010b58a7eda674f2346c971d83b0dc4`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B10F0` | `0x20c` |
| `func_150B12FC` | `0x188` |
| `func_150B1484` | `0x358` |
| `func_150B17DC` | `0x204` |
| `func_150B19E0` | `0x3d0` |

### `src/game/game_11F890.c`

Range `0xf23e0:0xf26a0`; 4 entries, 704 bytes.
SHA-1: `045c932b34407c2e69a4c47b9c618b8feb290abd`.
debug: 4 correlations, 4 strong.
ects: 4 correlations, 4 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F23E0` | `0xa0` |
| `func_150F2480` | `0x98` |
| `func_150F2518` | `0x88` |
| `func_150F25A0` | `0x100` |

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
