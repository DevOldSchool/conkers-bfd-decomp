# US selected particle and resource lifecycle groups

Evidence kind: `structural_analysis`. These are working source families with generic offset filenames. Historical filenames and original compilation-unit boundaries remain unknown. All entries remain raw ASM.

## Secondary element pair: `0xAEEB0:0xAF200`

`150AEEB0` prepares actor-relative element parameters and calls `15147DA0` at `0xAF154` with stack `+0x10` equal to 3 (`0xAF0F4`, `0xAF110`). This becomes custom byte `+0x21`, dispatched through `8008A3F8`; owned slot `8008A404` points to local `150AF1C0`. That callback derives the element's intensity from its lifetime and writes custom byte `+0x1B`. These two entries form the creator and its selected update.

## Directional burst pair: `0xB3AB0:0xB3DD0`

`150B3AB0` selects 8 on stack `+0x20` (`0xB3B64:0xB3B68`) before calling `1514C858`. That directional burst engine reads the selector at its stack `+0xFB` after reserving `0xD8` bytes, and indexes `8008AA00` (`0x14C92C:0x14C940`). Owned slot `8008AA20` points to local `150B3C0C`. Both entries participate in the same burst and child-emission path.

## Type-29 emitter pair: `0xC7020:0xC7350`

`150C7020` builds a descriptor at stack `+0x1C`, writes emitter selector 1 to stack byte `+0x4B`, and calls `15134DAC` twice. That constructor copies the descriptor to object `+0x18`, so the selector becomes object `+0x47`. The emitter table `80089B38` slot `80089B3C` contains local `150C71C0`, which produces the selected children. These are the only two entries in the interval.

## Owner event lifetime: `0x100180:0x100330`

`151001B4` constructs an eight-byte custom object through `15149130`, choosing update `0x4E` and event `0x3B`. Owned slots `8008A620/8008A9C4` point to local `151002BC/15100230`. The custom state retains an owner pointer and type byte; the update checks those values against the owner. `15100180` broadcasts event `0x48` with that same pointer/type payload. `15100230` explicitly handles event `0x48` by comparing the payload and deleting the corresponding object. The broadcast, constructor and two callbacks form one lifecycle.

## Withdrawn candidate: `0x1B5BF0:0x1B6010`

The constructor, update and audio cleanup are related, but independent CSV review identifies an additional eight-byte empty entry at `151B5E8C`. The raw assembly index folds its `jr ra; nop` words into the constructor. No owned pointer to that entry was found, so its membership remains unproved. The boundary was withdrawn through `./conker withdraw-source-unit`; the map is raw ASM again. The three previously registered raw work items remain available without a reviewed source-unit claim. This range contributes no newly mapped bytes.

## Reference-counted resource pair: `0x18C900:0x18CA80`

`1518C900` acquires a resource using count bytes `800DF7D0`, resource pointers `800DF9B8` and auxiliary allocations `800E0148`; it loads the resource on the first reference. `1518CA04` decrements the same indexed byte and releases the resource plus auxiliary allocation when the count reaches zero. Both entries use the same identifier-to-count/pointer mapping and implement the two sides of the lifecycle.

## Validation

The callback values above were read from the owned US data image. All endpoints are 16-byte aligned and indexed function starts. Raw words match the owned code image and entry spans cover the intervals exactly. Whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations follow; correlations identify entries without proving historical file boundaries.

### `src/game/game_DC360.c`

Range `0xaeeb0:0xaf200`; 2 entries, 848 bytes.
SHA-1: `4912677fb1337983c8af48c8da39277771ebfa0e`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150AEEB0` | `0x310` |
| `func_150AF1C0` | `0x40` |

### `src/game/game_E0F60.c`

Range `0xb3ab0:0xb3dd0`; 2 entries, 800 bytes.
SHA-1: `c8b8a450ce024924a4428e0528740d84987ccff5`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B3AB0` | `0x15c` |
| `func_150B3C0C` | `0x1c4` |

### `src/game/game_F44D0.c`

Range `0xc7020:0xc7350`; 2 entries, 816 bytes.
SHA-1: `effdf63afca68940c56916b2889ae1eadfe40d6a`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C7020` | `0x1a0` |
| `func_150C71C0` | `0x190` |

### `src/game/game_12D630.c`

Range `0x100180:0x100330`; 4 entries, 432 bytes.
SHA-1: `d6718073702a094b7bdd90b305e62dea6a1d89ba`.
debug: 3 correlations, 1 strong.
ects: 3 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15100180` | `0x34` |
| `func_151001B4` | `0x7c` |
| `func_15100230` | `0x8c` |
| `func_151002BC` | `0x74` |

### `src/game/game_1B9DB0.c`

Range `0x18c900:0x18ca80`; 2 entries, 384 bytes.
SHA-1: `8761aee1079d8ff4c6b36c561cc6b096b785519f`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1518C900` | `0x104` |
| `func_1518CA04` | `0x7c` |

## Integration result

Five accepted groups retain 12 raw entries and 3,280 bytes. The later ten-group integration also verifies the withdrawal of the ambiguous `0x1B5BF0:0x1B6010` source boundary. The complete US game overlay is byte-identical: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw assembly.
