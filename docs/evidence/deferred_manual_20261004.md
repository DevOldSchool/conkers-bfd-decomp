# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 15031E7C | game_5D2C0.c | 1205; unsigned index, FP result reuse | 2 |
| 151E4EE8 | game_20F9A0.c | 170; wrapping arithmetic, one state word | 2 |
| 15010880 | game_3DC30.c | 210; wrapping packet pointers | 2 |
| 151572D0 | game_1844C0.c | 2291; wrapping duration subtraction | 1 |
| 1516EED4 | game_19A8B0.c | 2997; valid word timer address | 2 |

14 target finish calls; nine fresh revisions. Best valid C deferred;
canonical ASM retained. No new exact matches. Five owner rechecks passed full-span
focused0, layout/progress/whitespace. BATCH_COMPLETE: US GAME/mapped rodata
equal ROM; 1,823 tests (35.662s), 37 skipped.

E4EE8 improved3785→170 with only register differences. Explicit unsigned
FP conversion and actual state reuse are useful leads; no speed benchmark.
Packet access qualifiers regressed210→1115 through address materialization.
Timer index snapshot was neutral2997; invalid2667 array form rejected.
Carry E8930 register plateau without duplicate attempts. Earlier alias,
padding and custom-ABI blockers remain. verify-batch omits focused checks.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
