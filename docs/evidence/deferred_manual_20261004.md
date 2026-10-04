# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 1502B6BC | game_57FA0.c | 566; SDK variadic cursor, actual state fields | 2 |
| 151BD2F8 | game_1E9A30.c | 120; canonical callee, active store order | 2 |
| 150412C0 | game_6E770.c | 7170; separate command snapshots | 2 |
| 150C5F94 | game_F3270.c | 257; canonical calls, actual zero fields | 2 |
| 150C68C4 | game_F3BA0.c | 257; independently checked sibling reuse | 1 |

14 target finish calls; nine fresh revisions. Best valid C deferred;
canonical ASM retained. No new exact matches. Ten matched owner/caller/callee
rechecks passed full-span focused0, layout/progress/whitespace.
BATCH_COMPLETE: US GAME/mapped rodata equal ROM; 1,823 tests (35.554s),
37 skipped. One mistaken deferred-owner check rejected without edits.

Unchanged caller15002FB4 focused300: three trailing NOPs; complete364B linked
span equals raw ROM, SHA256 c1321cd55b1cbbadd1b8e2b08bf884d2042848c1d8d8cfc79e84bd8f02b61802.
This remains a focused padding discrepancy. No zero-diff credit.
A9B0C custom T7 return/A7A48 pre-frame FPR saves remain blocked.
Rejected fixed-argument stack walks, unsupported local gaps and conflicting
callee types. Display-list historical6065 did not reproduce; fresh8300→7170.
Speed lead: canonical ABI audits and supported sibling reuse; C68C4 reached
its sibling's257 in one revision. Unbenchmarked. Starter local declarations
can conflict with canonical definitions; verify-batch omits focused checks.
Pending [1500E738 mapping](game_3ba70_jump_table.md); prior blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
