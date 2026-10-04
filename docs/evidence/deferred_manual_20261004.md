# Deferred manual matching: 2026-10-04

## Verified checkpoint

`func_150F6484` now matches the full registered 44-byte US span. Its reviewed
source unit was finalized as `src/done/game/game_1238D0.c`.

The preserved candidate declared `func_151411A4(void)` and omitted its argument.
Raw US assembly homes the incoming argument and reloads it in both call delay
slots. An existing matched caller in `src/done/game/game_11D770.c` declares
`func_151411A4(s32)`. The source-local declaration and call now use that contract;
a volatile parameter retains the observed home/reloads across the empty helper.
No shared header, callee definition, compiler setting or assembly was changed.
Other callers have independent source-local declarations.

| Measurement | Result |
| --- | --- |
| Preserved score | Historical CURRENT (500) |
| Fresh restored baseline | Full-span CURRENT (600) |
| One targeted revision | Full-span CURRENT (0) |
| Attempts | One baseline recheck, one source hypothesis; no permutation |
| Integration | Byte-identical US GAME overlay; source unit complete |
| Clean batch | BATCH_COMPLETE for func_150F6484 |
| Python suite | 1823 tests, OK, 37 skipped |
| Metadata, progress, whitespace | Passed |

Validation covers the rebuilt US GAME image and mapped data. This checkpoint
does not claim a main/debugger full-ROM build or EU/PAL validation.

## Workflow observations

- An absolute ROM symlink into another checkout fails inside the isolated Docker
  mounts. Copying the ROM into the worktree fixes this. A supported worktree
  bootstrap should prepare Docker-visible ROM/reference/tool inputs and transfer
  relevant ignored attempt ledgers. The existing primary SDK change was preserved.
- Ready context used the local `void` declaration, while a matched caller elsewhere
  provided the useful `s32` contract. A bounded conflicting-declaration cross-check
  would expose this lead sooner. Caller declarations remain hypotheses requiring
  raw evidence and focused verification.
- Cold worktree integration rebuilt pinned libraries and prepared 2699 ASM members;
  clean batch then rebuilt the overlay again. Consider fingerprinted cache reuse
  for isolated worktrees and a combined integration/clean-batch transaction. Any
  optimization must retain independent full-span, layout and clean image gates.

These are observations and proposals; no matching-tool changes were made.
Ignored detailed attempt records remain under
`build/us/manual-attempts/deferred-20261004/` and
`build/us/matching-attempts/func_150F6484/` in the isolated worktree.
