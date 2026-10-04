# Deferred matching: 2026-10-04

Manual US ASM-to-C; shared dependencies: no.

| Function | Source under src/game/ | CURRENT | Preserved candidate | Fresh revisions |
| --- | --- | --- | --- | --- |
| 151B77F4 | game_1E37D0.c | 757 | canonical one-argument helper; vector homes | 2 |
| 1517A1EC | game_1A7490.c | 3405→1975 | wrapping timer/fade arithmetic | 2 |
| 15044380 | game_71820.c | 146 | remove dummy padding; unsigned accumulator | 2 |
| 151934B4 | game_1C0840.c | 17 | wrapping tick arithmetic; vector home remains | 2 |
| 150E0BE0 | game_10E090.c | 720→245→205 | early frame snapshot; reused state local | 2 |

15 target finish calls, ten fresh revisions. All five retain canonical ASM;
no new exact C matches. Seven independent focused CURRENT (0) checks passed.
US BATCH_COMPLETE: integrated GAME/rodata exact; 1,823 tests, 37 skipped
(35.786s); layout/progress/whitespace pass.

Speed leads: correctness repairs recovered substantial scheduling/allocation;
real frame snapshots and state reuse helped. Vector aggregate and RNG snapshot
trials were neutral. Unbenchmarked.
Preflight canonical helper signatures: a preserved call had obsolete extra args.
Reject dummy padding, unbounded signed arithmetic and late aliased reads before tuning.
Batch gate omits focused diffs; run them independently.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
