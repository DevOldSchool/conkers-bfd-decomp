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
   For a known in-scope sibling, use `next --ready --function <id>` through the same gates.
3. Obey `allowed-edit`, `target-file-dirty`, `source-unit-state` and `post-match-action`.
   Stop on unclear overlapping ownership. Read/claim only recorded issues;
   `issue: none recorded` means no GitHub lookup.
4. Inspect the emitted context and allowed source. Before the first candidate, allow
   at most one additional batched lookup in `src/`, `include/` or emitted call sites,
   except for compiler-reported missing declarations.
5. Use existing types/structures, a typed pointer for one aligned field, or a source-local
   padded structure. Add concrete required declarations; follow CONTRIBUTING's ABI rules.
   Replace only the target `GLOBAL_ASM` at its current position and immediately run
   `./conker finish <id>`. Never alter shared dependencies or assembly to force a match.
   Confirm the edit succeeded and inspect its diff first. A failed helper stops the
   sequence; inspect any partial changes before retrying. Use separate tool calls
   for editing/inspection and `finish`; shell preparation steps must propagate errors
   with `&&` or equivalent. Unchanged reruns need an
   explicit recheck reason and never count as new hypotheses.

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

- Prefer short spans, concrete declaration/type fixes and proven sibling patterns.
  A low `CURRENT` score does not establish an easy match. After a match, make at most
  one bounded sibling lookup within scope. Prefer an eligible sibling with a recorded
  ASM/ABI hypothesis via `next --ready --function <id>` before returning to size-based
  selection; inspect and `finish` each independently. Do not broaden scope, clear
  exhausted history or construct queue-wide exclusions to force a selection.
- Keep a task-owned ledger under `build/us/manual-attempts/<task-id>/` and consult
  relevant prior ledgers across passes and compactions. Record fingerprints, hypotheses,
  tested changes, scores/classes, best artifacts, exhausted approaches and pending IDs.
  `finish` also saves portable candidate/result snapshots; annotate useful hypotheses
  and exhaustion with `matching-history note`. Follow
  the [ledger reference](docs/decompilation-workflow.md#durable-manual-attempt-ledger).
- Stop plateaued work under CONTRIBUTING's attempt rules; an expanded budget is a ceiling,
  not a quota. Keep model settings unchanged unless requested. Measure newly batch-verified
  matches per wall-clock hour and actual tokens; separate rechecks and candidate improvements.

## Acceptance and scope

- Require independent full-span US `CURRENT (0)`, layout, progress and whitespace gates.
  A matched function does not complete its unit. Follow [integration rules](CONTRIBUTING.md#acceptance-and-integration)
  immediately, including progress/whitespace checks after integration.
- Finish requested groups with clean `verify-batch`; success is `BATCH_COMPLETE`.
  Follow the [batch schedule](docs/decompilation-workflow.md#builds-and-batch-verification):
  aim for 5–10 matches, flush at about 45 minutes or before stopping/handoff/commit/PR
  or required integration. Avoid empty batches and singleton batches merely because
  one function matched. Persist pending IDs until clean success; report blocked batches.
- Use `diff --watch` only with interactive stdin/stdout; exit before `finish`. Keep the
  container warm across functions; stop it only for requested cleanup or finished work
  with no likely follow-up.
- Consult the workflow for registration, regional aliases and reference caching.
  Use [runtime tracing](docs/runtime-tracing.md) when static evidence is insufficient;
  distinguish positive hits from bounded negative traces.

## Reporting

Give one brief start update; then report failures, blockers or commands over 60 seconds.
For function work report function/source, changed files, shared dependency (yes/no),
US focused diff, whitespace, status (`matched`/`candidate`/`blocked`) and attempts.
For timed work, distinguish setup/restarts, clean verification, report creation and
end-to-end completion. Include final audit/handoff in workflow time; if final-delivery
timing is unavailable, say so. A saved report does not establish zero final overrun.
