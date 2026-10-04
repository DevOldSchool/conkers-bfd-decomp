# Deferred matching: 2026-10-04

- **Matched:** `func_150F6484`, 44 bytes, CURRENT600 → 0 in one revision.
  Corrected the local call contract and preserved raw parameter-home reloads.
- **Integrated:** `src/done/game/game_1238D0.c`; byte-identical US GAME overlay.
- **Validated:** BATCH_COMPLETE; 1823 tests passed (37 skipped), layout,
  metadata, progress and whitespace passed. No shared dependencies changed.
- **Candidate:** `func_1509F284` retains CURRENT740; parameter reuse regressed1549.
  Narrow-call normalization/scheduling remain; no justified target-local ABI fix.

Workflow improvements to investigate:

- Bootstrap Docker-visible ROMs and attempt history into isolated worktrees.
- Surface conflicting matched-caller declarations in ready context.
- Reuse fingerprinted build caches; combine integration and clean-batch work
  while retaining independent validation. No tooling changes made.
