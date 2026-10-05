# Deferred matching: 2026-10-04

Manual US ASM-to-C; shared dependencies: no.

| Function | Source under src/game/ | CURRENT | Preserved candidate | Fresh revisions |
| --- | --- | --- | --- | --- |
| 15108120 | game_1355D0.c | 2234→911 | actual incoming byte home | 2 |
| 151669A0 | game_193E50.c | 781 | baseline; zero union regressed | 1 |
| 15013DE8 | game_40490.c | 4781→3102 | real scalars separate from descriptor | 2 |
| 15146E84 | game_173D40.c | 774 | remove dummy pads; canonical byte parameter | 2 |
| 1500B8F4 | game_36680.c | 4848 | wrapping index; actual incoming record home | 2 |

14 target finish calls, nine fresh revisions; one malformed ID failed before compilation.
All five retain canonical ASM; no new exact C matches.
96 independent focused CURRENT (0) checks passed. US BATCH_COMPLETE:
integrated GAME/rodata exact; 1,823 tests, 37 skipped (37.121s);
layout/progress/whitespace pass.

Speed leads: actual incoming homes and descriptor/scalar separation improved
allocation. Zero-union transport regressed. Unbenchmarked.
Reject dummy frame padding and unbounded signed arithmetic before tuning;
lower invalid scores (750/4535) are excluded from best-candidate selection.
Batch gate omits focused diffs; run them independently.
Speed proposal: build once, compare all required spans, then check layout/progress once.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
