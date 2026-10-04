# Deferred matching: 2026-10-04

Latest five candidates; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Best valid full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 150C5DC0 | game_F3270.c | 265; owner argument repaired | 2 |
| 15079F6C | game_A28B0.c | 50; original retained | 1 |
| 150D2054 | game_FF0E0.c | 435 → 25; counter increment lifetime | 2 |
| 15167010 | game_1944C0.c | 550; original retained | 1 |
| 1519F168 | game_1CC440.c | 635 → 465; original owner lifetime | 2 |

14 candidate finish calls. C5DC0 baseline invalid: missing required owner argument.
D2054 compile repair retains existing s32 formal/wrapper contracts.
Best valid candidates deferred; canonical ASM retained; no new match credit.
D2054 has only four register rows; all opcodes/control/stack/count match.
Native u8 next-index revision regressed235; restored25.
Explicit address/end-pointer probes were neutral; simpler candidates restored.
Seven existing owners/callers passed CURRENT0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Speed leads: separate real counter increment from next-index masking;
check required arguments before spending effort on delay slots.
Historical scores omit current span/context differences; remeasure before ranking.
Prior 47B80 focused-padding issue: unchanged code; complete mixed span/ROM exact.
Pending [1500E738 mapping proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
