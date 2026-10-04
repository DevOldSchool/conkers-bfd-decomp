# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 150229E4 | game_49D30.c | 2640; integer field address | 2 |
| 1504ADD0 | game_77BE0.c | 900; six accessed buffer bytes | 1 |
| 1507E7E4 | game_AB760.c | 258; canonical timer argument, frame recovered | 2 |
| 1509563C | game_C2350.c | 800; wrapping addresses, output snapshots | 2 |
| 150A29C8 | game_CDE80.c | 485; typed wrapping addresses | 1 |

14 target finish calls; eight bounded revisions, one compile repair.
Best valid C deferred; canonical ASM retained. No new exact matches.
Five owners and three recorded matched callers passed full-span focused0,
layout/progress/whitespace. Clean verify-batch: BATCH_COMPLETE.
US GAME/mapped rodata equal ROM; 1,823 tests (35.485s), 37 skipped.

Legacy issues: ADD0 four-byte buffer passed to SDK bzero(length6);
E7E4 narrow timer formal conflicts with existing word declaration;
9563C sequential stores violate raw output overlap semantics
(aliased finite-value example: raw −10, old C −101).
Speed leads: narrow real local scopes/remove consumed byte snapshots
recovered E7E4 frame; consumed FP arguments preserved both outputs (→800).
A29C8 starter emits byte indexing for raw word loads; explicit loads retained.
verify-batch omits focused checks: run finish first. Gains unbenchmarked.
151898C0 padding/AB04 symbolic alias remain nonzero focused discrepancies;
complete linked spans equal ROM. Pending [1500E738 mapping](game_3ba70_jump_table.md).
47B80 padding,1515942C contract,150A6360 span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
