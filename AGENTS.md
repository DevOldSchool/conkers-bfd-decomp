# Conker decompilation agents

Use `./conker` from the repository root. US is the active target; EU/PAL does not gate work.
Read [CONTRIBUTING.md](CONTRIBUTING.md) once per task. Consult the
[workflow reference](docs/decompilation-workflow.md) only for details needed by the task.

## Function matching

1. Run `git status --short` once and preserve existing changes. Use an isolated worktree
   unless the user directs work on their current branch; never share an implementation checkout.
2. Run `./conker next --ready` once per selected item; it selects, prewarms Docker and emits
   declarations, raw US call sites and an m2c starter. Request Docker access on the first
   Docker-backed call when sandboxed. Do not separately run `next`, `m2c`, `doctor` or list the queue.
3. Obey `allowed-edit`, `target-file-dirty`, `source-unit-state` and `post-match-action`.
   Stop if overlapping edits have unclear ownership. Read/claim an issue only when recorded;
   `issue: none recorded` means no GitHub lookup.
4. Inspect the emitted context and allowed source. Before the first candidate, allow at most
   one additional batched lookup in `src/`, `include/` or the emitted raw call sites,
   unless a compiler error identifies a missing declaration.
5. Use `types.h` aliases and existing structures; otherwise use a typed pointer for one aligned
   field or a source-local padded structure. Never copy `M2C_FIELD` or `M2C_UNK` into source.
   Keep `sb`/`sh` parameters as `s32` unless existing declarations prove otherwise. Add concrete
   `required-declarations` not already available; resolve unknown types from project evidence.
6. Replace only the target `GLOBAL_ASM` at its existing position, then immediately run
   `./conker finish <id>`. Do not change assembly, inventory JSON, compiler flags or shared
   tooling/headers to force a function match; never use inline or handwritten assembly bodies.

## Follow the terminal action

- `STOP_MATCHED`: follow `post-match-action` (`stop` or `integrate`); continue only if the
  requested group has more functions. Do not repeat `progress match` or progress rendering.
- `FIX_COMPILE`: fix only the reported C/declaration problem, then rerun `finish`.
- `CONTINUE_MISMATCH`: use the latest `finish` diagnosis. Run `diagnose-diff` only when evidence
  is missing or stale. Diagnosis is a search hint, not proof of equivalent behavior.
  For purely register-only differences, use `permute <id> --budget 32` only when an untried
  transformation supported by the permuter plausibly addresses the diff and the task permits it.
  Register-only classification alone is not a reason to search. Honor manual-only restrictions.
  Otherwise read the saved full diff, make one targeted source revision and rerun `finish`.
  Default limit: two manual revisions and one 32-variant permutation search per distinct
  candidate and settings. Consult the durable manual-attempt ledger before retrying.
  After two non-improving revisions, stop unless a concrete new evidence-backed hypothesis
  and the task budget permit more work. A higher ceiling is not an attempt quota.
  Never repeat an equivalent exhausted search; larger budgets require new evidence or improvement.
  Exhaustion means `candidate`. A focused zero followed by layout failure needs layout recovery.
- `FIX_INTEGRATION`: fix source/layout before retrying a batch; never rerun an unchanged failure.
- `BLOCKED_TOOLING`, unavailable required declarations or unapproved shared changes: stop and
  report `blocked`. Terminal actions remain authoritative even if the surrounding process ends.

When moving past a candidate is authorized, use `defer <id> --reason <text>`; later use
`resume <id>`. Use `reopen-match` for invalidated older match evidence. Never reproduce these
transactions by hand. `permute` applies only exact results through transactional `finish`.

## Sustained matching

- Prioritize short registered spans, concrete declaration/type fixes, and proven sibling
  source patterns. A low `CURRENT` score is not a probability of an easy match.
- After a match, make at most one bounded lookup for nearby or similar raw-assembly siblings
  within the authorized scope. Reuse the source-shape hypothesis, then inspect and `finish`
  each selected function independently. Keep the per-target context lookup limit above.
- Keep a task-owned ledger under `build/us/manual-attempts/<task-id>/`; consult relevant prior
  ledgers across passes and compactions. Record source/input fingerprints, hypotheses, tested
  changes, scores and diagnostic classes, best artifacts, exhausted approaches, and pending
  batch IDs. This is an agent-maintained record, not an existing automatic tool feature or
  a substitute for inventory transactions. See the workflow reference's sustained matching section.
- Keep model settings unchanged unless requested. Evaluate future workflow/model pilots using
  newly batch-verified matches per wall-clock hour and measured tokens when available; distinguish
  rechecks, candidate improvements, and command time.

## Acceptance and scope

- Match only on authoritative US `CURRENT (0)` against an independent raw-assembly reference
  over the full registered span, with layout, progress and whitespace gates passed.
  `progress/functions.json` owns matches; `progress/source_units.json` owns integration state.
  A matched function does not complete its source unit. Generated assembly is not match evidence.
  Regenerate derived progress with `./conker progress render`; never edit generated reports by hand.
- Follow `post-match-action` for integration; afterward run `progress check` and
  `git -c core.whitespace=cr-at-eol diff --check` because integration changed repository state.
- Run one clean `verify-batch <ids...>` after a requested group; success is `BATCH_COMPLETE`.
  During sustained work, aim for 5–10 focused matches per batch; flush a smaller pending group
  at about 45 minutes after its first match, before stopping/handoff/commit/PR, or at a required
  integration boundary. Follow `post-match-action` immediately. Do not run a singleton batch
  merely because one function matched, or an empty batch when there are no pending matches.
  Persist pending IDs and clear them only after clean success. Follow CONTRIBUTING.md for
  shared changes and source-unit transitions; a blocked batch remains pending and must be reported.
- Use `diff --watch` only with interactive stdin/stdout; exit it before authoritative `finish`.
  Keep the warm container across functions; use `./conker stop` only for requested cleanup
  or when the broader contribution is finished with no likely follow-up work.
- Registration, regional aliases and reference caching: [workflow reference](docs/decompilation-workflow.md).
  If static evidence is insufficient, use [runtime tracing](docs/runtime-tracing.md) and distinguish
  positive runtime hits from bounded negative traces.

## Reporting

Give one brief start update; then report failures, blockers or commands exceeding 60 seconds.
For function work, report: function/source; changed files; shared dependency required (yes/no);
US focused diff; whitespace; status (`matched`/`candidate`/`blocked`); attempts.
