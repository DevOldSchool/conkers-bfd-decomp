# Deferred matching: 2026-10-04

Latest three items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / fresh full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 15142600 | game_16EE20.c | Invalid scalar-matrix starter repaired; valid 10388 retained | 2 |
| 1505A770 | game_83300.c | Candidate 10800 → 190; restored high-level loop | 2 |
| 1515D6D0 | game_18A8F0.c | Candidate 11850 → 6470; mutable graphics cursor | 2 |

Best valid candidates preserved through defer; regressions restored.
Ten candidate finish calls, including one missing-prototype repair; no new match credit.
ROM float bits: 800994DC=3dcccccd; 800994E0/800994E4=3d4ccccd.
These justify loop literals; constant references and scheduling still differ.
Existing owners/callee: 15142838, 150B9D14, 1505A72C, 1515D69C, 1515EF74.
All five rechecked at CURRENT0; layout/progress/whitespace passed.
Clean verify-batch: BATCH_COMPLETE; US GAME and mapped rodata equal ROM.
1,823 tests passed, 37 skipped. Candidates retain no new match credit.

Speed leads: detect already-unrolled starters before IDO unrolls them again;
use the checksum-validated ROM reader directly for constants; model real matrices.
Ready context still misses resumed function bodies; stored scores were stale.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
