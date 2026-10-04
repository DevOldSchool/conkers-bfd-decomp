# Deferred matching: 2026-10-04

Latest three items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Best valid full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 1515F850 | game_18A8F0.c | 1704 → 154; only 20 stack rows differ | 2 |
| 151D5E90 | game_203340.c | 12483 → 6213; snapshot and packet cursor | 2 |
| 150D3FD4 | game_100810.c | 8073 → 6598; ABI/index repair and snapshots | 2 |

Nine candidate finish calls. Invalid baselines: 1747, 13808, 8133 respectively.
Best valid candidates deferred at the limit; canonical ASM retained; no new match credit.
Frames (hex): color28/30, graphics40/98 and trailB8/90 remain unresolved.
Local declarations are called only by their respective disabled targets.
Five existing owners/callers passed CURRENT0/layout/progress/whitespace.
Graphics unit has no active C owners; full US integration covers canonical ASM.
Clean verify-batch: BATCH_COMPLETE; rebuilt US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Workflow: local prototypes again conflict with concrete callee definitions.
Check ABI/index widths before ranking. The real color array removed every opcode,
control-flow and register difference; typed packet cursors also improved the score.
These are unbenchmarked speed leads. Resumed-body context still omits the function.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
