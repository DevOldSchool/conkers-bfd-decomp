# Deferred matching: 2026-10-04

Latest five functions; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 1501E05C | game_49D30.c | 0; distinct early returns, wrapping addresses | 2 |
| 1502B350 | game_57FA0.c | 1571; actual allocation/result lifetimes | 2 |
| 1502F264 | game_58F80.c | 4130; wrapping copy/address arithmetic | 2 |
| 1504715C | game_71820.c | 1740; word coordinates/table addressing | 2 |
| 150F3214 | game_11FF10.c | 36; wrapping transform address | 2 |

15 target finish calls; ten fresh revisions. E05C full 344B CURRENT (0),
layout/progress/whitespace passed. Four best valid candidates deferred;
canonical ASM retained. Five focused zero checks passed; clean US batch
BATCH_COMPLETE: 1,823 tests, 37 skipped (suite 35.409s).

Speed leads: distinct early returns replaced m2c shared failure gotos and
matched E05C 2125→0. Removing redundant allocation aliases recovered S0,
frame 48→38 and 3092→1571; register hint was neutral. Unbenchmarked.
Unsigned actor literal multiplication produced long chains; shared stride
regressed further. FP snapshots and owner reuse did not improve this cohort.
Invalid lower scores excluded. Earlier alias/padding/custom-ABI blockers
remain; verify-batch omits focused checks.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
