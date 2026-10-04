# Deferred matching: 2026-10-04

Latest five functions; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 15191BE0 | game_1BF090.c | 3280; restored payload mode byte | 2 |
| 1503A678 | game_64120.c | 482; three actual scale snapshots | 2 |
| 1505ED34 | game_83300.c | 715; typed cursor, wrapping word steps | 2 |
| 150C4D20 | game_F21D0.c | 1731; actual timer/velocity state | 2 |
| 1501FE68 | game_49D30.c | 351; wrapping indexed addresses | 2 |

15 target finish calls: one compile failure, ten fresh revisions. Five valid
candidates deferred; canonical ASM retained. No new C matches.
Twelve focused owner/canonical/caller checks passed CURRENT (0); layout,
progress and whitespace passed. Clean US batch BATCH_COMPLETE:
1,823 tests, 37 skipped (35.850s suite).

Speed leads: named actual scale words improved 693→482 and removed array
address setup. Early velocity snapshot/state restored F0/F2 and pre-sound
timer spill, 4988→1731. Typed pointer with word steps restored pool frame28→20,
1097→715. Payload/result grouping regressed; output wrapper was neutral.
Unbenchmarked. Invalid low scores and unsupported workspace tails excluded.
Workflow improvement: preserve declaration context with deferred candidates;
missing payload byte broke resume compilation. Check inventory before treating
visible C as matched; batch gate still omits focused checks.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
