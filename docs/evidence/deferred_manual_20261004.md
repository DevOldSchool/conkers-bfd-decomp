# Deferred matching: 2026-10-04

Latest three items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / fresh full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 15039A78 | game_64120.c | Invalid 4x-stride starter repaired; valid 1787 → 1237 | 2 |
| 15012C84 | game_3FC60.c | Candidate 2705 → 1025; restored high-level color-copy loop | 2 |
| 15049EDC | game_770F0.c | Candidate 2354 → 2044; explicit dot-product partial sums | 2 |

Best valid candidates preserved through defer; nine candidate finish calls.
No new match credit. Signatures unchanged; all three retain canonical ASM.
Owners 15039A54/15049C40 rechecked at CURRENT0; layout/progress/whitespace passed.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped. 3FC60 has no matched C owner.

Workflow: fresh scores differ from saved scores; check byte strides before ranking.
Speed leads: high-level loops avoid repeated compiler unrolling; inspect counter
induction and real float lifetimes. Quaternion register hints compiled unchanged.
Ready context misses resumed function bodies; prototype conflicts need canonical checks.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
