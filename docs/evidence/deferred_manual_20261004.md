# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared changes: no.

| Function | Source under src/game/ | Best valid CURRENT | Revisions |
| --- | --- | --- | --- |
| 151D3E6C | game_200930.c | 2370 → 740; ABI/midpoint repair | 2 |
| 1503EFC4 | game_6B320.c | 145; signed float conversion repaired | 2 |
| 150C5D0C | game_F2820.c | 255; prior candidate retained | 1 |
| 15116058 | game_142A70.c | 1410 → 1165; bank/reload repair | 2 |
| 15055C88 | game_80B80.c | 505 → 25; direct field assignments | 2 |

15 target finish calls, one compile repair; no new match credit.
D3E6C omitted incoming A3; EFC4 converted unsigned underflow to huge floats.
16058 used wrong source/destination banks and cached alias-sensitive count/flag.
Best valid candidates deferred; canonical ASM retained.
55C88 differs only in five register rows; full192B/frame30/stack agree.
Eight existing owners/callers passed focused0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Speed leads: inspect actual arguments, signed conversions and post-store reloads first.
Direct disjoint field assignments recover FP timing without named-local frame growth.
Prior checkpoint matched15058EA4 via reused FP bounds; full-span128B CURRENT0.
Prior 47B80 focused-padding issue persists; complete mixed span/ROM were exact.
Pending [1500E738 mapping proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
