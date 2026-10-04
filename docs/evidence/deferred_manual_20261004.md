# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared changes: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 1507911C | game_A28B0.c | 740; original retained | 1 |
| 150E05F8 | game_10D7B0.c | 970; original retained | 2 |
| 1502D54C | game_58F80.c | 335 → 135; observed intermediate store | 1 |
| 150C851C | game_F5800.c | 255 → 130; consumed argument reuse | 1 |
| 15072208 | game_981E0.c | 370; original retained | 1 |

11 target finish calls; no new match credit.
Best valid candidates deferred; canonical ASM retained.
D54C full228B opcode/operand/control/count/stack agree; 20 register rows remain.
C851C frame30 agrees; counter initialization recovered, allocation/interleaving remain.
Five existing owners passed focused0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed (34.316s), 37 skipped; repository whitespace passed.

Speed leads: qualify only observed stores; reuse consumed incoming values.
These bounded probes improved candidates; throughput gains are unbenchmarked.
Workflow issue: ready reports target pragma missing after resume; inspect saved source.
Prior checkpoint matched15058EA4 via reused FP bounds; full-span128B CURRENT0.
Prior 47B80 focused-padding issue persists; complete mixed span/ROM were exact.
Pending [1500E738 mapping proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
