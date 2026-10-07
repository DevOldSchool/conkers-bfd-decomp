# Matching automation

Use automation only when the task permits it. Manual-only work follows the
[decompilation workflow](decompilation-workflow.md). Automation uses the same
[acceptance gates](../CONTRIBUTING.md#acceptance-and-integration); saved reports
describe coverage and attempts, not independent match evidence.

## Bounded runs

Start with a small cohort when evaluating a change:

```sh
./conker automate --limit 5 --max-attempts 20 --rewrite-budget 32
./conker automate --function <work-item-id> --rewrite-budget 25 \
  --defer-best --skip-final-build
```

The scheduler alternates size-ordered raw work with score-ordered deferred work;
`--function` selects one eligible item directly. Raw starters use evidence-backed
declaration recovery, aligned scalar/pointer field cleanup with signed offsets,
integer-backed address casts for IDO and bounded source-shape rewrites.

Both pools receive compact `diagnose-diff` preflight. Pure register differences
qualify for search; register differences with one to three missing/extra rows
receive a probe capped at 32 variants. Structural mismatches skip search. For raw
candidates that are ineligible for search, the proposed source and diagnostics
are saved and canonical source is restored, even with `--defer-best`.

Compilation must be warning-free. Before restoring a failed attempt, up to three
compiler-guided target-function repairs address proven mechanical problems such
as undefined `NULL` or byte-address pointer arithmetic. Preparation/compilation
failures retain the starter or proposed source, compiler output and structured
diagnostics under `build/us/automate/artifacts/<work-item-id>/`.

For eligible compiling nonzero raw candidates, authorized `--defer-best` preserves
the best result through transactional `defer`. For deferred work, a strictly lower
nonzero score replaces the disabled candidate and inventory score transactionally;
equal or worse results preserve the existing block. Exact results pass through
`finish`; a deferred `CURRENT (0)` goes directly to that authoritative recovery.

## Failed and interrupted attempts

If an exact permutation fails mixed-object layout before a match is recorded,
the host restores source and deferred inventory metadata from the same snapshot.
A focused exact candidate with failed layout retains a `finish`/`layout_gate`
blocker and measured offset delta. Unlabeled retained instructions are not silently
claimed as C or promoted to a new boundary. Use the supported
[layout recovery](decompilation-workflow.md#focused-iteration) flow.

Permutation writes each improved `best.c` immediately. On exit 137/SIGKILL,
automation restores or preserves project source, records the interruption and
advances an `--all` traversal. With `--defer-best`, a completed positive best
score can be preserved; if no permutation finished, the previously measured
initial candidate is preserved instead.

`--skip-final-build` skips only the concluding clean `verify-batch`. Each retained
match still passes focused diff, layout, progress and whitespace through `finish`.
The command prints the pending batch command; work is not ready for commit or
handoff until it succeeds. Do not rerun an unchanged failed integration gate.

## Resume and reuse previous work

Execution runs share fingerprinted outcomes in
`build/us/automate/attempt-history.json`, importing existing execution reports on
first use. Bounded runs and `next --ready` skip unchanged failed attempts. Source,
raw assembly, relevant declarations, headers, tooling or search-setting changes
invalidate applicable outcomes. History is local to each worktree.

Attempted report entries retain the terminal stage, blocker code, repair actions
and stage-specific input fingerprint. Resume skips only matching fingerprints;
preparation, compilation or search changes requeue the affected frontier. Legacy
entries without stage metadata are retried once.

`--restart` explicitly retries saved outcomes in the selected scope; it does not
discard pending batch verification. Identical nonmatching `permute` searches also
reuse their saved result until source or search settings change. Keep manual
hypotheses in the separate [attempt ledger](decompilation-workflow.md#durable-manual-attempt-ledger).

```sh
./conker blockers --limit 20
./conker blockers --json
./conker automate --function <work-item-id> --restart --rewrite-budget 32
```

The blocker report ranks missing declarations and placeholder families from saved
failures, excludes already matched functions and shows representative dependents.
It does not revalidate fingerprints; counts may overlap. Inspect retained starters
and recover declarations from project evidence before retrying. Counts alone do
not prove types or justify indiscriminate placeholder replacement.

```sh
./conker declaration-conflicts
./conker declaration-conflicts --json
```

The declaration conflict report lists externally visible symbols that compiled C
declares differently in different files. It skips `#if 0` deferred candidates,
macro bodies and `static` symbols, and writes
`build/reports/declaration-conflicts.{md,json}`. Typedefs are resolved before
comparison, so one name with different definitions still conflicts. Each symbol
gets the weakest severity that reconciles its variants: qualifier, aggregate name,
aggregate unverified, pointee, signedness, byte placeholder or incompatible.
Differently named structs count as the same shape only when their computed MIPS
o32 layouts match; otherwise compatibility is reported as unknown.

Treat the report as an investigation aid. Its risk shortlist (MIPS o32 argument
or return location changes, float/int values sharing a register, argument counts,
array-vs-pointer, access or element widths) is a heuristic for review, not a
verified or exhaustive defect count. Only leading floating-point arguments use
`$f12`/`$f14`; a float after an integer argument travels in a general register.
Whether a
disagreement matters depends on how each site uses the symbol. A matched C
definition is the strongest signature evidence; other conflicts need caller or
assembly evidence before a shared declaration is chosen. The report is read-only
and does not gate matching.

## Full scans and analysis

A full execution scan is an explicit, long-running operation:

```sh
./conker automate --all --defer-best
```

It has no attempt/match cap, but retains safety exclusions and will not guess
ambiguous declarations or cross source-unit integration transitions. Do not combine
`--all` with `--max-attempts`. The default rewrite budget remains 32.

`build/us/automate/all-report.json` is replaced atomically after each attempt. It
classifies every inventory entry, including matched and excluded functions. A
complete traversal sets `full_scan` and `scan_complete` true with no `not_attempted`
entries. Resume an interrupted scan with the same command. Pending exact matches
are reconciled against current inventory on resume and before the final batch;
reopened/deferred items are excluded from that batch.

For preparation coverage without compiling or applying candidates:

```sh
./conker automate --all --analyze
```

Analysis does not edit tracked source or inventory, compile, permute, defer, finish
or run a batch. Its only outputs are ignored m2c caches and the separately resumable
`build/us/automate/analysis-report.json`. Use `--restart` to rebuild that report.

## Output and evaluation

Output is compact by default: important events and a progress summary every 50
candidates. Add `--verbose` for full live command output. Both modes retain logs
at `build/us/automate/logs/<work-item-id>.log`, with paths in report entries;
preparation failures retain `artifacts/<id>/starter.c`.

Completed execution reports include elapsed time, cache hits, attempted IDs,
command-log bytes, and separate newly verified/carried verified match counts.
`--model-tokens N` accepts externally measured tokens for that invocation and
reports newly batch-verified matches per 1,000 tokens. Missing counts stay null;
log bytes are neither model tokens nor agent-visible output volume. Compare the
same candidate cohort and distinguish command time from end-to-end wall-clock time.

## Maintainer validation

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

Keep authoritative CURRENT (0), layout, progress, whitespace, and
BATCH_COMPLETE requirements. Tooling/cache behavior alone does not establish
new function matches.

## Experimental stack shapes

`diagnose-diff` reports `stack-rows` only when opcode/registers agree and the sole
operand difference is an SP-relative offset. Mixed constants/control flow are
ineligible. The opt-in pilot tries suffix scopes and scalar wrappers without
inventing padding:

```sh
./conker automate --function <work-item-id> --stack-shapes --defer-best
```

It tries at most eight shapes and stops at the first non-improving compiled shape;
`--exhaustive` does not override this stop. Strategy and outcome are fingerprinted.
The [initial pilot](evidence/matching/targeted_candidate_pilot.md) did not establish an
accepted match or batch success. Keep this option off for broad scans until further
integration validation. Instruction zero never replaces layout or clean-batch proof.
