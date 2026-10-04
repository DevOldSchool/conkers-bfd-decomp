# Deferred matching: 2026-10-04

Latest five functions; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 15146BF8 | game_173D40.c | 135; wrapping addresses, byte selector | 2 |
| 15156028 | game_182C30.c | 1225; wrapping subtraction, signed division | 2 |
| 151B0050 | game_1DD500.c | 2168; four actual RNG snapshots | 2 |
| 1500FE30 | game_3D2E0.c | 1370; bounded signed counter | 2 |
| 1516ED68 | game_19A8B0.c | 0; incoming index reload | 2 |

15 target finish calls; ten fresh revisions. ED68 full 364B CURRENT (0),
layout/progress/whitespace passed. Four valid candidates deferred; canonical
ASM retained. Six focused zero checks passed. Clean US batch
BATCH_COMPLETE: 1,823 tests, 37 skipped (suite 35.665s).

Speed leads: actual incoming index qualifier matched ED68 361→0; scalar
ABI unchanged, no matched C callers, raw caller unchanged. Signed counter
recovered FE30 frame 38→30 and SLTI guard, 1463→1370; byte trial regressed.
RNG snapshot structure improved 2192→2168; IDO still folds raw multiply by
zero. Selector and mode/index reuse were neutral. Unbenchmarked.
Invalid lower scores excluded. verify-batch still omits focused checks.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
