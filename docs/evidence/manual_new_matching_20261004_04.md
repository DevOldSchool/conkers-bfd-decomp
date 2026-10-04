# Manual matching — batch 4

Fresh Git/inventory eligibility; manual only, no prior session memory.

| Function | Source under `src/game/` | Deferred CURRENT | Attempts |
| --- | --- | ---: | ---: |
| func_15149838 | game_176A00.c | 660 | 3 |
| func_15198570 | effects/characterflamethrower.c | 9204 | 3 |
| func_151C1D5C | game_1ED0F0.c | 2360 | 3 |
| func_151C5F44 | game_1F2730.c | 1597 | 3 |
| func_150006E0 | game_2D540.c | 1220 | 3 |

Best candidates retained beside ASM with inventory reasons. No accepted matches.
US GAME refresh, mapped rodata, progress and whitespace passed. No empty batch verification.

Workflow findings:

- A collision starter invented two leading float arguments; raw callee uses four word/pointer slots.
- Ring arithmetic needs a word index; the starter's signed byte loses raw values.
- Halfword-aligned 18-byte aggregates reproduce unaligned surface copies without special macros.
- Typed spawn records reproduce packet homes and frame; extra volatile fields can worsen scheduling.
- Reset loops must refresh the player-count snapshot after each allocation.
