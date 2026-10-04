# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared changes: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 15076B94 | game_A28B0.c | 1080; original retained | 0 |
| 151B5240 | game_1E26F0.c | 582; original retained | 1 |
| 1506C32C | game_981E0.c | 645 → 632; wrapping decrement, scalar reuse | 2 |
| 15035714 | game_623D0.c | 1106; original retained | 0 |
| 151CD3CC | game_1FA770.c | 558; original retained | 1 |

9 target finish calls; no new match credit. Best valid C deferred; ASM retained.
6C32C recovered frame38; array offset and instruction scheduling remain.
CD3CC fresh full-span558 supersedes historical458; explicit return was neutral.
Five existing owners passed focused0/layout/progress/whitespace.
1E26F0 has no matched owner; clean GAME covers its canonical ASM.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed (36.251s), 37 skipped; repository whitespace passed.

Speed lead: reject hypotheses already satisfied in the fresh full diff.
Scalar reuse recovered one frame but regressed another; gains unbenchmarked.
Ready still reports missing target pragma after resume; inspect saved source.
Prior checkpoint matched15058EA4 via reused FP bounds; full-span128B CURRENT0.
Prior 47B80 focused-padding issue persists; mixed span/ROM were exact.
Pending [1500E738 mapping proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
