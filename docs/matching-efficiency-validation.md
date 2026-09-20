# Matching efficiency: maintainer validation

The changes are on `feature/automate-improve`. After testing was authorized,
the full Python suite passed: 986 tests, with 6 skipped. After source-order and
call/comparison corrections, the Docker-backed clean batch gate also passed:
the integrated US game binary is byte-identical, metadata and progress are
valid, and whitespace checks passed. The final result is `BATCH_COMPLETE`.

The successful batch covered `func_15181E18`, `func_1514E9DC`, `func_150F237C`,
`func_1507E9E8`, `func_1512D2F8`, `func_1517EFAC`, and `func_151C0644`.
Its log is `build/us/automate/integration-recovery-final.log`.

Run these from the repository root to repeat the focused checks:

```sh
python3 -m unittest discover -s tests -p 'test_attempt_history.py'
python3 -m unittest discover -s tests -p 'test_automate.py'
python3 -m unittest discover -s tests -p 'test_permute.py'
python3 -m unittest discover -s tests -p 'test_declaration_facts.py'
python3 -m unittest discover -s tests -p 'test_project_state.py'
python3 -m unittest discover -s tests -p 'test_repository_safety.py'
git -c core.whitespace=cr-at-eol diff --check
```

In a prepared, isolated checkout with the reviewed US ROM and raw references:

1. Run `./conker blockers --limit 10` and compare its groups with saved reports.
   A fresh worktree has no historical reports until a run or explicit import.
2. Run a small bounded automation group twice with the same settings. The second
   run should skip unchanged failed candidates and advance to fresh ones.
3. Change a relevant declaration or candidate and confirm it becomes eligible
   again. An unrelated object's declaration should not invalidate it.
4. Repeat a nonmatching `permute` call with identical input and settings. It
   should report a cached nonmatch without compiling variants. Change the
   candidate or budget and confirm that search runs again.
5. Interrupt after an exact match or use `--skip-final-build`. A subsequent
   bounded run, including `--restart`, must retain and execute the pending clean
   batch gate before claiming verified progress.
6. Compare a bounded default run with `--verbose`: both retain full command logs;
   the default only prints compact outcomes and artifact paths. Supply an actual
   measured `--model-tokens N` when evaluating matches per token.

Keep authoritative CURRENT (0), layout, progress, whitespace, and BATCH_COMPLETE
requirements. No new function matches are claimed by this tooling change.

## Matched-definition declaration recovery pilot

The resolver now uses the unique active definition in a registered US matched
source when local declarations and reviewed SDK aliases are absent. It recovered
`void func_1516972C(u8 *)` from `src/game/game_1944C0.c`; unrelated speculative
prototypes no longer block this missing call context. It preserves local
contracts, rejects ambiguous/unsupported definitions, records the definition's
source, and invalidates dependent fingerprints when the resolved signature changes.
No shared C header or caller declaration was changed by this pilot.

Three explicit automation runs each used one attempt with `--rewrite-budget 32
--defer-best --skip-final-build`. All passed declaration preparation and compiled,
then stopped at structural mismatch without permutation search. Source was restored;
saved candidate artifacts remain available for inspection.

| Function | Source | US focused diff | Status |
| --- | --- | --- | --- |
| `func_151D4C38` | `src/game/game_200930.c` | CURRENT (1130) | blocked: structural mismatch |
| `func_151B5A9C` | `src/game/game_1E26F0.c` | CURRENT (2372) | blocked: structural mismatch |
| `func_1515BFA8` | `src/game/game_1890A0.c` | CURRENT (1680) | blocked: structural mismatch |

Reports: `build/us/automate/declaration-pilot-<hex-id>.json`. Call-context evidence:
`build/m2c/calls/<function>.json`. No new matches resulted from this cohort, and no
model-token measurement was supplied, so no matches-per-token improvement is claimed.

Validation: 991 Python tests passed, with 6 skipped; whitespace checks passed.
The test log is `build/us/automate/declaration-recovery-tests.log`.
The clean `verify-batch func_1516972C func_15181E18` gate also passed with
`BATCH_COMPLETE`: both existing functions passed their focused checks, the
integrated US binary is byte-identical, and metadata/progress checks passed.
Its log is `build/us/automate/declaration-recovery-batch.log`.

### Bounded manual follow-up: func_151D4C38

Two source-only revisions were tested in `src/game/game_200930.c`. A local record
structure plus switch scored CURRENT (2000); restoring if/else ordering and using
an integer address expression scored CURRENT (1150). Neither improved the saved
starter's CURRENT (1130). Both retained structural differences: the compiler
folded record-pointer accesses into direct object offsets, and control-flow and
scheduling differences remained. No permutation search was justified.

The original compiling candidate was restored and preserved through `./conker
defer func_151D4C38 --reason ...`, which confirmed CURRENT (1130). Status:
**candidate**, zero new matches, two manual attempts. No shared C dependency was
required. The source retains its active GLOBAL_ASM; unrelated source edits were
preserved. The supported defer transaction updated the inventory. Manual versions
and diffs are saved under `build/us/automate/artifacts/func_151D4C38/manual-*`.
Progress and whitespace checks passed.
The clean gate `./conker verify-batch func_151D4668` verified an existing matched
function in the same source unit and completed with `BATCH_COMPLETE`. The integrated
US binary remained byte-identical; 991 tests passed with 6 skipped. This checks
integration safety and does not establish a match for `func_151D4C38`. The log is
`build/us/automate/func_151D4C38-manual-batch.log`.
