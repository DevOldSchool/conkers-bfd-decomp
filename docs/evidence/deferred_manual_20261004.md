# Deferred matching: 2026-10-04

Latest five items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Best valid full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 15086D94 | game_B4080.c | 10823 → 7578; crossing lifetimes/homes | 2 |
| 151B65D4 | game_1E37D0.c | 4723 → 4548; vectors, ABI and steps | 2 |
| 1510F8D8 | game_13BB20.c | 1955; repaired 16-byte stride | 2 |
| 151179BC | game_144C70.c | 12233 → 10629; widths, ABI and homes | 2 |
| 1510AA44 | game_137ED0.c | 4788 → 3310; counter/quotient schedule | 2 |

15 candidate finish calls; invalid baselines: B65D4=7717, F8D8=2250, 179BC=11800.
Best valid candidates deferred; canonical ASM retained; no new match credit.
Frames (candidate/raw, hex): 98/90, C0/B8, 18/18, 48/58, 70/40.
Raw 15086D94 reads an uninitialized saved slot; no invented initialization.
1510F8D8 raw passes zero to matched 1510F800(void); contract unchanged.
Local declaration repairs affect disabled candidates only; 151B77F4 unchanged.
12 existing owners/callers passed CURRENT0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; rebuilt US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Workflow: validate packed/index widths, contiguous vectors and concrete callee ABI
before ranking. Cache the raw quotient lifetime before its floating-point consumer.
Simple-loop and call-home rewrites regressed here; restore the best valid candidate.
These are unbenchmarked speed leads. Resumed-body context still omits the function.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
