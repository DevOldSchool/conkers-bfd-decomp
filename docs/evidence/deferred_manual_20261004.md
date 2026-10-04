# Deferred matching: 2026-10-04

Latest five functions; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 1500AC14 | game_36680.c | 1688; unsigned size rounding | 2 |
| 1517EAAC | game_1AB530.c | 583; wrapping view addresses | 2 |
| 151A91AC | game_1D6570.c | 106; init order, actual RNG snapshots | 2 |
| 1508EE0C | game_B4080.c | 4543; switch, shared decoded operand | 2 |
| 15103AA0 | game_130CB0.c | 785; callback signature, unsigned shift | 2 |

15 target finish calls: one compile failure, ten fresh revisions. Five valid
candidates deferred; canonical ASM retained. No new C matches.
Five focused owner checks passed CURRENT (0); layout/progress/whitespace
passed. Clean US batch BATCH_COMPLETE: 1,823 tests, 37 skipped (35.440s suite).

Speed leads: particle init order improved 584→122, three actual RNG snapshots
122→106; eight frame/stack rows remain. View word addresses improved 743→583;
workspace grouping regressed. Two-case switch improved 4678→4543. Narrow load
types and phase-word reuse regressed. Unbenchmarked.
Workflow issues: resumed callback failed its existing local declaration; repaired
without shared edits. Invalid lower scores excluded. Batch gate omits focused checks.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
