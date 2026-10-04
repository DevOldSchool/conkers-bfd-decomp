# Deferred matching: 2026-10-04

Latest four items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / fresh full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 15095B08 | game_C2350.c | Candidate 9905 → 2690; leaf frame/cached stores match | 2 |
| 1516D0CC | game_197F20.c | Starter reads corrected; valid 3769 → 3528, frame/homes match | 2 |
| 15058F24 | game_83300.c | Candidate 6755 → 2480; actual register float lifetimes | 2 |
| 151106A8 | game_13D350.c | Candidate 6018 → 4062; mutable command cursor | 2 |

Best valid candidates preserved through defer; neutral revisions restored to simpler C.
12 candidate finish calls: four baselines and eight revisions. No new match credit.
Existing 15095A48/15095A90/1516D2D8/1505841C/15110600 rechecked at 0;
full-span/layout/progress/whitespace gates passed. Clean verify-batch: BATCH_COMPLETE.
Full US GAME/external rodata equal ROM; 1,823 tests, OK with 37 skipped.

Workflow issue: ready context searches only the target pragma (project_state.py);
after resume it misses the enabled candidate and shows the header. Include its body.
Speed lead (unbenchmarked): inspect actual float lifetimes and duplicate unsigned
corrections first; register hints alone left the command-cursor revision unchanged.
Stored scores differed from all four fresh baselines; rank using current evidence.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
