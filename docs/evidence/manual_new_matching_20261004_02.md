# Manual matching — batch 2

Fresh eligibility checked against Git/inventory; no prior session memory or automated search.

| Function | Source under `src/game/` | Result / CURRENT | Attempts |
| --- | --- | --- | ---: |
| func_1509EFF0 | game_CC4A0.c | Blocked: return contracts | 0 |
| func_15115368 | game_142560.c | Deferred / 5503 | 3; one invalid |
| func_1515BBF0 | game_1890A0.c | Deferred / 2231 | 3 |
| func_15195AA8 | effects/characterflamethrower.c | Deferred / 1786 | 3 |
| func_151B9408 | game_1E67C0.c | Deferred / 1305 | 3 |

Best C candidates retained beside ASM; blockers/residuals saved in inventory.
Changes: four candidate sources, inventory/progress outputs and this report; shared dependencies unchanged.
US GAME refresh and progress/whitespace: passed. No accepted matches; no empty batch check.

Workflow findings:

- A caller consumes returns from helpers declared `void`; repair the contract family before attempting that caller.
- Packet starter samples a texture byte too early; retain raw sampling order across calls.
- Matrix starter passes one scalar to a 16-float writer; use a real array before tuning layout.
- Separate branch indices reduced register mismatches from 76 to 3; separating matrix/source storage aligned all stack homes.
