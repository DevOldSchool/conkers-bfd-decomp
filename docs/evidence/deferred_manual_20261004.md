# Deferred matching: 2026-10-04

US, manual only. No shared dependencies changed. Revisions exclude baselines.

| Function | Source under src/ | Result | Revisions |
| --- | --- | --- | --- |
| 150F6484 | done/game/game_1238D0.c | Matched 600→0; unit integrated | 1 |
| 151AA5A4 | game/game_1D6E80.c | Matched 200→0; removed fabricated RNG argument | 1 |
| 1509F284 | game/game_CC4A0.c | Best candidate740; parameter reuse regressed1549 | 1 |
| 15134DAC | game/effects/blood.c | Candidate754→20; four register rows remain | 2 + declaration repair |
| 151AB090 | game/game_1D6E80.c | Candidate1192→170; frame/register differences remain | 2 |
| 15187EC0 | game/game_1B5370.c | Invalid stride corrected; valid candidate3075 retained | 1 |
| 150F7E20 | game/game_124920.c | Candidate784→764; FP/frame/control differences remain | 2 |
| 15030310 | game/game_5D2C0.c | Missing boolean return restored; candidate2735→814 | 2 |

Clean batches passed: byte-identical US GAME overlay; 1823 tests OK (37 skipped),
layout, metadata, progress and whitespace. Wrapper150302F0 rechecked at CURRENT0.

Workflow findings:
- Bootstrap Docker-visible ROMs and repository attempt history into worktrees.
- Audit callee contracts and later same-source declarations before matching.
- Reject wrong pointer strides and omitted returns before ranking scores.
- Reuse fingerprinted build caches; investigate combining integration and batch rebuilds.

Task-branch commits use DevOldSchool-AI-Agent; earlier three author identities corrected.
