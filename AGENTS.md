# Conker decompilation agents

Use `./conker` from the repository root. US is active; EU/PAL does not gate work.
Read [CONTRIBUTING.md](CONTRIBUTING.md) once per task for source-edit rules,
attempt limits and acceptance requirements. Read the [workflow reference](docs/decompilation-workflow.md)
only as needed. Fresh/reset cloud executors first follow [cloud recovery](docs/cloud-matching.md).

## Function matching

1. Run `git status --short` once and preserve existing work. Use an isolated worktree
   unless the user directs the current branch; never share an implementation checkout.
2. Run `./conker next --ready` once per selected item. It selects, prewarms Docker and
   emits declarations, raw US call sites and an m2c starter. Request Docker access on
   the first Docker-backed call when sandboxed. Do not separately run `next`, `m2c`,
   `doctor` or list the queue.
3. Obey `allowed-edit`, `target-file-dirty`, `source-unit-state` and `post-match-action`.
   Stop on unclear overlapping ownership. Read/claim only recorded issues;
   `issue: none recorded` means no GitHub lookup.
4. Inspect the emitted context and allowed source. Before the first candidate, allow
   at most one additional batched lookup in `src/`, `include/` or emitted call sites,
   except for compiler-reported missing declarations.
5. Use existing types/structures, a typed pointer for one aligned field, or a source-local
   padded structure. Add concrete required declarations; follow CONTRIBUTING's ABI rules.
   Replace only the target `GLOBAL_ASM` at its current position, inspect the successful
   edit's diff, then run `./conker finish <id>` in a separate tool call. Follow the
   [edit and recheck rules](CONTRIBUTING.md#match-a-function); never alter shared
   dependencies or assembly to force a match.

## Follow the terminal action

- `STOP_MATCHED`: follow `post-match-action` (`stop` or `integrate`). Continue only
  within the requested group. Do not repeat `progress match` or progress rendering.
- `FIX_COMPILE`: fix only the reported C/declaration problem, then rerun `finish`.
- `CONTINUE_MISMATCH`: use the latest diagnosis and [manual attempt limits](CONTRIBUTING.md#match-a-function).
  Consult prior ledgers; refresh diagnosis only if missing/stale. Inspect the saved
  full diff, make one targeted revision and rerun `finish`. Permutation needs an
  eligible, untried hypothesis and task permission; honor manual-only restrictions.
  Exhaustion means `candidate`; focused zero with failed layout needs layout recovery.
- `FIX_INTEGRATION`: fix source/layout before retrying; never rerun an unchanged failure.
- `BLOCKED_TOOLING`, unavailable required declarations or unapproved shared changes:
  stop and report `blocked`. Terminal actions remain authoritative if the process ends.

Use `defer <id> --reason <text>` only when moving on is authorized; recover with
`resume` or `reopen-match`. Never reproduce transactions by hand. `permute` applies
only exact results through transactional `finish`.

## Sustained matching

- On a stack, frame or float-register residual, follow the [diagnosis checklist](docs/decompilation-workflow.md#diagnosis-checklist)
  and compare hypotheses with `./conker probe` before reshaping statements by hand.
- Prefer short spans, concrete declaration/type fixes and proven sibling patterns.
  A low `CURRENT` score does not establish an easy match. Make at most one bounded
  sibling lookup after a match, following [selection and reuse](docs/decompilation-workflow.md#selection-and-reuse).
- Consult prior ledgers across passes and compactions. Keep task reasoning and pending
  IDs under `build/us/manual-attempts/<task-id>/`; `finish` saves candidate snapshots.
  Follow the [ledger and annotation rules](docs/decompilation-workflow.md#durable-manual-attempt-ledger).
- Stop plateaued work under CONTRIBUTING's attempt limits; an expanded budget is a
  ceiling, not a quota. Keep model settings unchanged unless requested and follow
  the [measurement rules](docs/decompilation-workflow.md#measuring-improvement).

## Acceptance and scope

- Require independent full-span US `CURRENT (0)`, layout, progress and whitespace gates.
  A matched function does not complete its unit. Follow [integration rules](CONTRIBUTING.md#acceptance-and-integration)
  immediately, including progress/whitespace checks after integration.
- Finish requested groups with clean `verify-batch`; success is `BATCH_COMPLETE`.
  Follow the [batch schedule](docs/decompilation-workflow.md#builds-and-batch-verification):
  aim for 5–10 matches, flush at about 45 minutes or before stopping/handoff/commit/PR
  or required integration. Avoid empty batches and singleton batches merely because
  one function matched. Persist pending IDs until clean success; report blocked batches.
- For changes affecting asset reconstruction, run `./conker build --assets` once
  per completed batch before handoff/commit/PR, following the
  [asset acceptance rules](CONTRIBUTING.md#asset-and-build-changes). Default builds,
  `finish`, `verify-batch` and public PR CI do not verify reconstructed assets.
  Record the tested commit and result; if no ROM is available, report verification
  pending and require a maintainer to complete it before merge.
- Use `diff --watch` only with interactive stdin/stdout; exit before `finish`. Keep the
  container warm across functions; stop it only for requested cleanup or finished work
  with no likely follow-up.
- Consult the workflow for registration, regional aliases and reference caching.
  Use [runtime tracing](docs/runtime-tracing.md) when static evidence is insufficient;
  distinguish positive hits from bounded negative traces.

## Reporting

Commit inventories and evidence, never rendered `build/progress/` reports. See
[progress reports](docs/progress.md).

Give one brief start update; then report failures, blockers or commands over 60 seconds.
For function work report function/source, changed files, shared dependency (yes/no),
US focused diff, whitespace, status (`matched`/`candidate`/`blocked`) and attempts.
For timed work, follow the [timing and validation-scope rules](docs/decompilation-workflow.md#measuring-improvement).
