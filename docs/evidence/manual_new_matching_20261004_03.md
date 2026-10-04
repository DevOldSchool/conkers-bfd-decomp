# Manual matching — batch 3

Fresh Git/inventory eligibility; manual only, no prior session memory.

| Function | Source under `src/game/` | Deferred CURRENT | Attempts |
| --- | --- | ---: | ---: |
| func_15072B44 | game_981E0.c | 120 | 3 |
| func_1507D4F8 | game_A9D90.c | 879 | 3 |
| func_150CD59C | game_FA360.c | 2665 | 3 |
| func_150F0BEC | game_11D830.c | 135 | 3 + 1 compile repair |
| func_15132B80 | game_15F680.c | 3377 | 3 |

Best candidates retained beside ASM with inventory reasons. No accepted matches.
Changes: five candidate sources, inventory and this report; no shared dependencies.
US GAME refresh, mapped rodata, progress and whitespace passed. No empty batch verification.

Workflow findings:

- Starters misplace sparse-switch defaults and sample flags before calls that precede raw loads.
- A word snapshot read as a halfword needs an explicit storage view; this reduced CURRENT 3773 to 879.
- Matrix translation occupies its final row; use a full 16-float buffer and real corner arrays.
- Typed packet/vector records reproduced the frame and all homes; extra flag locals worsened layout.
