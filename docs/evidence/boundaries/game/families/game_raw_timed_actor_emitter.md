# US timed actor-emitter family

Evidence kind: `structural_analysis`. The working range is `0xE1060:0xE1570`, named `src/game/game_10E510.c` from its raw offset. Its original filename and historical compilation-unit boundary remain unknown. All entries remain raw assembly.

## Membership

The constructor `150E1060` selects an actor/resource using `800A0FE0` and `151149AC`, prepares a 16-byte state record, and calls the generic owner factory `15149130` at `0xE1110`. It explicitly passes update selector `0x1F` in `a2` at `0xE10FC`. That factory stores the selector in object byte `+0x11` at `0x1491B8:0x1491BC`; its update dispatcher `15149264` indexes the callback table at `8008A4E8` and calls the selected entry at `0x1492A8:0x1492B0`. The owned word at `8008A4E8 + 0x1F * 4 = 8008A564` is `150E114C`, the other entry in this range.

The constructor copies its record to object `+0x28` at `0xE1120:0xE1130`. The callback derives the same state pointer at `0xE11C0`, advances the timer at state `+0xC`, reads the resource at state `+8`, and creates emissions with `15130374` when the timer crosses a whole interval. This connects the constructor and update callback through a concrete selected slot and a shared state layout.

The preceding entry `150E0D90` is excluded. The split at `0xE1060` follows its complete return and delay slot. Both range endpoints are 16-byte aligned. Raw words match the owned US image, entry spans cover the interval, and whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations are recorded below; correlations support entry identity, not original source-file provenance.

### `src/game/game_10E510.c`

Range `0xe1060:0xe1570`; 2 entries, 1,296 bytes.
SHA-1: `0704548514bd98b204e373c2b65d2ae523d96648`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E1060` | `0xec` |
| `func_150E114C` | `0x424` |

## Integration result

The first complete US game-overlay gate passes: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Both entries remain raw assembly.
