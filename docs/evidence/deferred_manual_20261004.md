# Deferred matching: 2026-10-04

Manual US ASM-to-C; shared dependencies: no.

| Function | Source under src/game/ | CURRENT | Status | Fresh revisions |
| --- | --- | --- | --- | --- |
| 1502FBE8 | game_58F80.c | 979 | candidate; word actor subtraction | 2 |
| 1503F62C | game_6C960.c | 1095 | candidate; wrapping count shift | 1 |
| 15144CEC | game_16EE20.c | 4258→3547 | candidate; early vertical product | 2 |
| 15157DEC | game_1844C0.c | 320→90→0 | matched; reused matrix cursor | 2 |
| 151A361C | game_1D0840.c | 190→115 | candidate; ring-index snapshot | 2 |

14 target finish calls, nine fresh revisions. Four candidates retain canonical
ASM. 15157DEC passed full 404-byte focused, layout, progress and whitespace gates.
All 20 independent focused checks passed CURRENT (0). Clean US BATCH_COMPLETE: integrated
GAME/rodata exact; 1,823 tests, 37 skipped (36.295s); metadata/progress/whitespace pass.

Speed lead: one actual cursor fixed matrix register allocation; unsigned word
addition fixed the remaining operand order. Interpolation pointer-home assignment
was eliminated by IDO; ring snapshots helped. Unbenchmarked.
Reject unsupported signed arithmetic and late aliased loads even when near-matching.
Selection now skips recorded exhausted barriers. Batch gate omits focused diffs.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
