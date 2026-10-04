# Deferred matching: 2026-10-04

Latest three items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / fresh full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 1511F4D0 | game_14C3F0.c | Candidate 6785 → 3279; actual coordinate homes | 2 |
| 151658DC | game_191C30.c | Candidate 9665 → 4020; aggregate copies and field reloads | 2 |
| 151E86E4 | game_215960.c | Candidate 6920 → 5240; packet cursor and coordinate lifetime | 2 |

Nine candidate finish calls; exhausted budgets, best valid candidates deferred.
No new match credit; canonical ASM retained. ABI unchanged.
Six existing C owners passed CURRENT0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; rebuilt US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Workflow: fresh baselines exposed stale saved scores. Actual aggregate copies
reproduced all 24 integer copy instructions; packet cursors restored argument homes.
Volatile homes can regress scheduling, so measure and retain the better valid version.
These are unbenchmarked matching leads. Ready context still misses resumed bodies;
full-span diagnosis can mistake the next function's frame for a leaf's frame.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
