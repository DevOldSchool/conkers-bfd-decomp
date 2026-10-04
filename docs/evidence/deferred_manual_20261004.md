# Deferred matching: 2026-10-04

- **Matched:** `func_150F6484`, 44 bytes, CURRENT600 → 0 in one revision.
  Corrected the local call contract and preserved raw parameter-home reloads.
- **Integrated:** `src/done/game/game_1238D0.c`; byte-identical US GAME overlay.
- **Validated:** BATCH_COMPLETE; 1823 tests, OK (37 skipped), layout,
  metadata, progress and whitespace passed. No shared dependencies changed.
- **Candidate:** `func_1509F284` retains CURRENT740; parameter reuse regressed1549.
  Narrow-call normalization/scheduling remain; no justified target-local ABI fix.
- **Improved candidate:** `func_15134DAC`, CURRENT754 → 20; four register rows
  remain. Two revisions plus one local return-declaration repair; best retained.

Workflow improvements to investigate:

- Bootstrap Docker-visible ROMs and attempt history into isolated worktrees.
- Surface conflicting declarations before ready/resume, including later
  same-source declarations (`func_15134DAC` previously failed compilation).
- Reuse fingerprinted build caches; combine integration and clean-batch work
  while retaining independent validation. No tooling changes made.
