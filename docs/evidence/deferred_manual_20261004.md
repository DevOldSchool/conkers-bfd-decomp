# Deferred matching: 2026-10-04

Latest five; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | US CURRENT/status | Fresh revisions |
| --- | --- | --- | --- |
| 150C2700 | game_EF410.c | 625 candidate; raw155 byte constant recovered | 2 |
| 1506A5F0 | game_97AA0.c | 518 → 514 candidate; store order | 2 |
| 1506B634 | game_981E0.c | 840 → 0 matched; full268B | 1 |
| 15087CC0 | game_B4080.c | 844 candidate; original retained | 1 |
| 151218C4 | game_14D110.c | 1215 candidate; original retained | 1 |

12 target finish calls. Best valid candidates deferred; their ASM retained.
B634 plus four affected owners/caller passed full-span/layout/progress/whitespace.
14D110 has no matched owner; clean GAME covers its canonical ASM.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed (35.603s), 37 skipped; repository whitespace passed.

Speed lead: actual u8 index plus distinct u32 remainder restored B634 masks.
Check actual diff rows: C2700 recovered raw155 despite unchanged score.
Workflow issues: ready loses target context after resume; local RNG prototype
can conflict with canonical u32 definition; 63B64 starter double-divides typed pointers.
Throughput gains remain unbenchmarked.
Pending [1500E738 mapping](game_3ba70_jump_table.md); linker unchanged.
47B80 focused-padding,1515942C shared contract,150A6360 span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
