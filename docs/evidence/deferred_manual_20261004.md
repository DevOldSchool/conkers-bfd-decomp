# Deferred matching: 2026-10-04

Latest three items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / fresh full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 151B3A7C | effects/holtenrope.c | Invalid vector/ABI starter repaired; candidate 9401 → 3908 | 2 |
| 1508BF14 | game_B4080.c | Invalid widths/strides repaired; candidate 12806 → 4799 | 2 |
| 151CDB94 | game_1FA770.c | Invalid fabsf ABI repaired; candidate 5385 → 2460 | 2 |

Best valid candidates preserved through defer; ten candidate finish calls,
including one compile repair. No new match credit; canonical ASM retained.
Rope pointer prototype corrected locally; fade fabsf uses a local float intrinsic.
Graph retains the assembly's connected-input requirement for its selected index.

Six existing C owners: CURRENT0/layout/progress/whitespace passed.
Clean verify-batch: BATCH_COMPLETE; rebuilt US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; no new match credit.

Workflow: validate field widths, strides, contiguous locals and implicit calls
before ranking candidates. Simple loops avoid repeated compiler unrolling;
snapshot constants at the lifetimes shown in ASM. These are unbenchmarked leads.
Ready context still misses resumed bodies; declaration conflicts need canonical checks.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
