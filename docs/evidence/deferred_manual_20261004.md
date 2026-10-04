# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 150D82BC | game_105760.c | 1250 retained; loop strength reduction | 1 |
| 151897A4 | game_1B5CC0.c | 2147; removed dummy padding, reused cursor | 2 |
| 1502B4A8 | game_57FA0.c | 3440; repaired wrapping addresses | 2 |
| 150A3194 | game_CDE80.c | 318; do-loop, direct coordinates | 2 |
| 1517D690 | game_1A89B0.c | 478; wrapping addresses, cursor reuse | 2 |

14 target finish calls; nine bounded revisions. Prior budgets carried.
Best valid C deferred; canonical ASM retained. No new exact matches.
Five existing owners passed full-span focused0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed (35.712s), 37 skipped; whitespace passed.

Speed leads: natural do-loop recovered A3194 tail/global lifetimes
(2346 → 392); direct coordinates restored frame (→ 318).
Actual cursor reuse improved 1897A4 and 17D690; no throughput benchmark.
Reject dummy padding and signed address overflow before score comparisons.
151898C0 focused200 omits two padding NOPs; unchanged C, full64B linked span
including eight zero bytes equals raw ROM. This is not focused0.
AB04 focused10 symbolic alias remains; full388B linked span equals ROM.
verify-batch omits individual focused checks: run finish first.
Pending [1500E738 mapping](game_3ba70_jump_table.md); linker unchanged.
47B80 padding,1515942C contract,150A6360 span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
