# Deferred matching: 2026-10-04

Latest five items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Best valid full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 1512D980 | game_15ABA0.c | 3944 → 2045; call snapshots/FP homes | 2 |
| 151CD7BC | game_1FA770.c | 5037; vector/call-lifetime repairs | 2 |
| 15094AB8 | game_C1D70.c | 11032 → 9301; concrete record loop | 2 |
| 150611E8 | game_83300.c | 20162 → 10964; path pointer/loop | 2 |
| 151438D8 | game_16EE20.c | 9169 → 2428; actual saved masks | 2 |

15 candidate finish calls. Invalid: D980=5244, CD7BC=9095/7640, 611E8=20177.
Best valid candidates deferred; canonical ASM retained; no new match credit.
Frames (candidate/raw, hex): 28/28, E0/C0, 30/40, 38/38, 40/60.
D980 stack rows exact; CD7BC six FP save offsets exact.
94AB8 retains input reloads after output stores; unroll4 versus raw2 remains.
611E8 retains the raw uninitialized saved-index behavior; no invented default.
438D8 native u16 accumulators were neutral; earlier candidate restored.
Local clamp declaration has no indexed matched C callers (incomplete coverage).
Nine existing owners/callers passed CURRENT0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; rebuilt US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Workflow: check pointer-load widths and field loads across calls before ranking.
Recover contiguous vectors and one unsigned conversion; do not duplicate correction.
Simple loops can recover frames/unrolls, but compare the complete registered span.
Actual saved masks greatly improved 438D8; speed leads remain unbenchmarked.
Resumed-body context still omits the function; canonical ABI conflict warning useful.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
