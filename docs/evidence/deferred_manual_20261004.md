# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared changes: no.

| Function | Source under src/game/ | Best valid CURRENT | Revisions |
| --- | --- | --- | --- |
| 150979CC | game_C4DC0.c | 1559 → 256; nested paths/pointer reuse | 2 |
| 150A2EE4 | game_CDE80.c | 1865 → 1130; descriptor argument repaired | 2 |
| 151D5D60 | game_200930.c | 1085 → 826; scalar reuse/frame recovery | 1 |
| 151DAA88 | game_2062D0.c | 653; prior array candidate retained | 1 |
| 1502B8E0 | game_57FA0.c | 1202 → 523; variadic ABI/local reuse | 2 |

14 target finish calls, one compile repair; no new match credit.
A2EE4 previously passed an offset instead of the full descriptor pointer.
Best valid candidates deferred; canonical ASM retained.
Six existing owners/callers passed focused0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed (35.422s), 37 skipped; repository whitespace passed.

Speed leads: validate callee arguments before optimizing; reuse actual scalar lifetimes.
Standard va_list and unconditional argument reads recovered the variadic loop.
Three-float aggregate layout was neutral; simpler array retained.
Prior checkpoint matched15058EA4 via reused FP bounds; full-span128B CURRENT0.
Prior 47B80 focused-padding issue persists; complete mixed span/ROM were exact.
Pending [1500E738 mapping proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
