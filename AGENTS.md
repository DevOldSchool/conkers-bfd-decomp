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
  If `register-only` is positive and every other count is zero, try `permute <id> --budget 32`
  before manual variants when permitted. Honor task budgets and manual-only restrictions.
  Otherwise read the saved full diff, make one targeted source revision and rerun `finish`.
  Default limit: one manual revision and one permutation search per function; keep plateau
  stopping, never repeat an unchanged search, and expand effort only when the task allows it.
  Exhaustion means `candidate`. A focused zero followed by layout failure needs layout recovery.
- `FIX_INTEGRATION`: fix source/layout before retrying a batch; never rerun an unchanged failure.
- `BLOCKED_TOOLING`, unavailable required declarations or unapproved shared changes: stop and
  report `blocked`. Terminal actions remain authoritative even if the surrounding process ends.

When moving past a candidate is authorized, use `defer <id> --reason <text>`; later use
`resume <id>`. Use `reopen-match` for invalidated older match evidence. Never reproduce these
transactions by hand. `permute` applies only exact results through transactional `finish`.

## Acceptance and scope

- Match only on authoritative US `CURRENT (0)` against an independent raw-assembly reference
  over the full registered span, with layout, progress and whitespace gates passed.
  `progress/functions.json` owns matches; `progress/source_units.json` owns integration state.
  A matched function does not complete its source unit. Generated assembly is not match evidence.
  Regenerate derived progress with `./conker progress render`; never edit generated reports by hand.
- Follow `post-match-action` for integration; afterward run `progress check` and
  `git -c core.whitespace=cr-at-eol diff --check` because integration changed repository state.
- Run one clean `verify-batch <ids...>` after a requested group; success is `BATCH_COMPLETE`.
  Do not batch every single source-local match. The clean gate is required before commit/PR
  or handoff; follow CONTRIBUTING.md for shared changes and source-unit transitions.
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
