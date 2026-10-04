# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared changes: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 150C2424 | game_EF410.c | 840 → 130; observed argument home | 2 |
| 15063B64 | game_90840.c | 261 → 250; actual scalar reuse | 1 |
| 1515BE50 | game_1890A0.c | 88 → 30; pointer reuse, local order | 2 |
| 15183C28 | game_1B0740.c | 183; original retained | 1 |
| 15189900 | game_1B6DB0.c | 320; original retained | 2 |

13 target finish calls; no new match credit. Best valid C deferred; ASM retained.
BE50 full256B opcodes/control/count/stack agree; six FP register rows remain.
C2424 full248B frame/homes/registers agree; four load/constant order rows remain.
Four existing owners passed focused0/layout/progress/whitespace.
1B6DB0 has no matched owner; clean GAME covers its canonical ASM.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed (35.971s), 37 skipped; repository whitespace passed.

Workflow issue: 63B64 starter divides typed pointer difference by812 again.
At actor1 this produces1; raw ASM and preserved candidate correctly produce2.
Ready also reports missing target pragma after resume; inspect saved source.
Speed leads: qualify observed homes; merge actual pointer lifetimes, then order locals.
These improved candidates; throughput gains remain unbenchmarked.
Prior checkpoint matched15058EA4; full-span128B CURRENT0.
Pending [1500E738 mapping proposal](game_3ba70_jump_table.md); linker unchanged.
47B80 focused-padding,1515942C shared contract and150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
