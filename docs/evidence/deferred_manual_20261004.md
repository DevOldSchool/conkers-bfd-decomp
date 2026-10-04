# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 15075938 | game_A28B0.c | 305 retained; selector registers/scheduling | 2 |
| 150FC818 | game_128D70.c | 1585 retained; pointer/branch scheduling | 2 |
| 15148DE0 | game_175250.c | 1050 retained; flag/loop scheduling | 1 |
| 1502AF04 | game_57FA0.c | 1121; wrapping addresses, 8-byte records | 2 |
| 15063E84 | game_90840.c | 1885 retained; A3 spill/pointer colors | 1 |

13 target finish calls; best valid C deferred, canonical ASM retained.
No new exact matches; eight bounded revisions. Prior budgets carried.
Five existing owners passed full-span focused0/layout/progress/whitespace.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed (35.541s), 37 skipped; whitespace passed.

Starter issues: FC818 word load at arg1+4 emitted as byte;
75938 desired count-2 emitted unsigned byte without a lower-bound proof.
Speed lead: actual 8-byte records recovered AF04 loop strength reduction
(4221 → 1121); historical921 rejected for signed-offset overflow.
Reject already-correct homes/types before editing; stop regressing patterns.
Throughput gains remain unbenchmarked. Prior checkpoint matched B634 full268B.
Pending [1500E738 mapping](game_3ba70_jump_table.md); linker unchanged.
47B80 padding,1515942C contract,150A6360 span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
