# Deferred matching: 2026-10-04

Manual US ASM-to-C; shared dependencies: no.

| Function | Source under src/game/ | CURRENT | Preserved candidate | Fresh revisions |
| --- | --- | --- | --- | --- |
| 1500BC7C | game_36680.c | 2294 | wrapping index; raw normalization; record home | 2 |
| 150BAA14 | game_E7DE0.c | 298→188 | wrapping arithmetic; actual owner home | 2 |
| 151A743C | game_1D4140.c | 90 | baseline; address/snapshot trials failed | 2 |
| 150AFE64 | game_DC6B0.c | 26→16 | raw matrix-address operand order | 2 |
| 1501FC8C | game_49D30.c | 567 | wrapping slot/record offsets | 2 |

15 target finish calls, ten fresh revisions. All five retain canonical ASM;
no new exact C matches. 34 independent focused CURRENT (0) checks passed.
US BATCH_COMPLETE: integrated GAME/rodata exact; 1,823 tests, 37 skipped
(36.773s); layout/progress/whitespace pass.

Speed leads: owner-home modeling and actual word addresses helped;
extra FP snapshots and volatile matrix storage regressed. Unbenchmarked.
Reject unbounded signed arithmetic before comparing candidate scores.
Limit rechecks to evidenced impact; prior checkpoint audited all 70 game_36680
owners, whose active definitions remain unchanged. Clean GAME equality still gates.
Batch gate omits focused diffs; run them independently.
Speed proposal: build once, compare all required spans, check layout/progress once.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
