# Deferred matching: 2026-10-04

Latest three items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / fresh full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 1511DBC4 | game_1483E0.c | Valid candidate408→213; both flag stores preserved | 2 |
| 151596BC | game_1865D0.c | Valid candidate3189→2734; result lifetime/center loads repaired | 2 |
| 150F0E48 | game_11D830.c | Valid candidate533 retained; pointer-allocation plateau | 2 |

Best valid candidates preserved through defer; neutral/regressing revisions reverted.
Nine candidate finish calls including baselines; no permutation. No new match credit.
Existing 1511DD98/15159370/150F0A24 rechecked at0; layout/progress/whitespace passed.
Clean verify-batch: BATCH_COMPLETE; full US GAME/external rodata equal ROM.
Suite: 1,823 tests, OK with 37 skipped; metadata/progress/whitespace passed.

Speed observations: register storage and float indexing were neutral for pointer folding;
broader volatile views regressed. Prefer a specific missing access over broad volatility.
Earlier workflow leads remain unbenchmarked: flag prototype conflicts/multi-entry spans during ready;
audit raw load/store widths before register work.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); shared linker unchanged.
1515942C remains blocked by a shared caller contract; 150A6360 by full-span/FPU semantics.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
