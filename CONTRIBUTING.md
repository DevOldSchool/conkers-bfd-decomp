# Contributing

Human and AI-assisted contributions follow the same clean-room rules and
acceptance gates. Use `./conker` from the repository root. Read this guide once
per task; consult the [workflow reference](docs/decompilation-workflow.md) for
command details.

## Setup

Run `./conker host-setup` once with Python 3.12 or newer. This installs the
pinned host helper and full-suite test dependencies into ignored
`build/host-python`; `./conker` selects it automatically. `host-check`,
`doctor`, matching readiness and batch verification reject missing or stale
dependencies before Docker/build work. Setup never changes global Python.

1. For local work, install Docker and run `./conker doctor`.
2. Supply your own reviewed US ROM at `roms/baserom.us.z64`, then run
   `./conker setup --us roms/baserom.us.z64`. Setup checks `config/roms.json`.
3. Follow [bootstrap](docs/bootstrap.md) to establish the raw baseline. Fresh or
   reset cloud executors use [cloud setup and recovery](docs/cloud-matching.md).

US is the active target; EU/PAL does not gate progress. Read [LEGAL.md](LEGAL.md)
for provenance requirements. ROMs, extracted assets and build outputs stay ignored.
Inspect `git status --short` once and preserve unrelated staged and unstaged work.
Use an isolated worktree unless the user directs work on the current checkout;
never share an implementation checkout between workers.

## Match a function

```sh
./conker next --ready
# Replace only the selected GLOBAL_ASM pragma with C at the same position.
./conker finish <work-item-id>
```

Obey the emitted `allowed-edit`, `target-file-dirty`, `source-unit-state`, required
declarations and `post-match-action`. Stop when overlapping ownership is unclear.
Read/claim an issue only when recorded; `issue: none recorded` needs no GitHub lookup.

Confirm the edit succeeded and inspect its diff before running `finish` in a
separate tool call. Shell preparation must stop on failure (`&&` or equivalent);
inspect partial writes before retrying a failed helper. Record the reason for
unchanged rechecks, and count them, compilation repairs and accidental duplicates
separately from new hypotheses.

Use `types.h` aliases and existing structures. For incomplete local evidence, use
a typed pointer or source-local partial structure. Resolve unknown types from
project evidence and add concrete required declarations before `finish`. Keep
`sb`/`sh` parameters as `s32` unless existing declarations prove otherwise. Never
copy `M2C_FIELD`/`M2C_UNK`, invent an ABI, add inline or handwritten assembly, or
change assembly, compiler flags, shared tooling or headers to force a match.
Extra argument homes, conversions or union spills justify reviewing the callee
contract and its caller family. After an approved declaration change, recheck
affected existing matches; a same-source caller sample is not a complete impact audit.

Use the latest `finish` diagnosis; run `diagnose-diff` only if evidence is stale
or missing. After the initial candidate, the default ceiling is two targeted
manual revisions and one eligible `permute --budget 32` search per distinct
candidate/settings. Permutation requires task permission and an untried supported
transformation that plausibly addresses a purely register-only diff. Classification
alone does not justify search. Honor manual-only restrictions.

Stop after two non-improving revisions unless a concrete new evidence-backed hypothesis and the
task budget justify more. Never repeat an equivalent exhausted search; larger
budgets require evidence or improvement. Exhaustion means `candidate`. When moving
on is authorized, preserve the best candidate with `defer <id> --reason ...`; use `resume` or
`reopen-match` for recovery. See the [manual ledger and sustained workflow](docs/decompilation-workflow.md#sustained-manual-matching).
Carry exhausted hypotheses and task/function budgets across continuations; a lower
score alone does not reset them. Record the expected assembly change and distinguish
real snapshots/cursors from recomputable addresses in the [ledger](docs/decompilation-workflow.md#durable-manual-attempt-ledger).
Immediately [annotate correctness-rejected attempts](docs/decompilation-workflow.md#durable-manual-attempt-ledger)
as invalid with a concrete reason, also recorded in the ledger, before restoring
or deferring. For continued groups, follow [sibling selection and reuse](docs/decompilation-workflow.md#selection-and-reuse).

## Acceptance and integration

- A C match requires US `CURRENT (0)` over the **full registered span** against
  independent raw assembly, plus layout, progress and whitespace gates. Compilation,
  generated candidate assembly and register-insensitive comparisons are not proof.
- `progress/functions.json` owns function matches; `progress/source_units.json`
  owns reviewed boundaries and integration. A function match does not complete its
  source unit. Use supported transactions; never hand-edit inventory or generated
  assembly/progress reports. `./conker progress render` writes ignored local
  reports under `build/progress/`; open `build/progress/progress.md` or use
  `./conker progress` to inspect objdiff freshness and separate inventory totals.
  Commit canonical inventory and evidence changes, never generated reports. `progress check` validates canonical
  inputs and rendering without requiring local snapshots. See the
  [progress guide](docs/progress.md) for migration, inventory-only use and objdiff
  report generation.
- Review original object boundaries and every member before source-unit registration.
  Alignment, a standalone build or a matching function does not prove ownership.
  Keep the evidence comment below the include block. Use `withdraw-source-unit` for
  invalidated boundaries. See [registration and transitions](docs/decompilation-workflow.md#source-unit-boundaries-and-integration).
- Follow `post-match-action` immediately: integrate when a reviewed raw unit enters
  mixed mode, then again when all members match. After integration run
  `./conker progress check` and `git -c core.whitespace=cr-at-eol diff --check`.
- A focused zero followed by layout failure requires layout recovery. Fix failed
  source/layout before retrying; never rerun an unchanged failed batch. Keep focused
  matching, data/rodata proof and boundary confidence separate. External data mappings
  require checksum-validated ROM evidence and cannot hide an incorrect boundary.
  See [reviewed initialized data](docs/main-private-data.md) for the manifest
  contract and the separate shared-integration scope requirement.

Finish each requested group with one clean gate; success is `BATCH_COMPLETE`:

```sh
./conker verify-batch <work-item-id> [<work-item-id>...]
```

For sustained work, follow the [batch schedule](docs/decompilation-workflow.md#builds-and-batch-verification).
Persist pending IDs until clean success and report blocked batches as pending.
[Verified original assembly](docs/decompilation-workflow.md#verified-original-assembly)
can join a batch, but contributes no C matches or completed C source units.

## Review and handoff

Before handoff, commit or PR, complete the clean batch for function changes.
Before merge, record the tested commit and local US results in the PR; contributors
without a ROM can ask a maintainer to verify. Public CI checks do not establish
matching or enforce this local ROM evidence. The owner-approved main workflow
verifies the US build after merge. See [CI and review policy](docs/ci.md).

Keep changes narrow, reproducible and independently verified by the maintainer.
For function work,
report function/source, changed files, shared dependency required (yes/no), US
focused diff, whitespace, status (`matched`/`candidate`/`blocked`) and attempts.
For tooling or documentation changes, report the relevant checks instead.
For timed work, report measured matching and end-to-end durations, including final
audit/handoff; follow the [timing rules](docs/decompilation-workflow.md#measuring-improvement).

## Task references

- [Automation](docs/automation.md): bounded runs, saved outcomes, recovery and pilots;
  use it only when the task permits automation.
- [Library reconstruction](docs/library-track.md): prove text, relocations, data/rodata,
  BSS, archive ownership and full-image equality before `retire-library-units`;
  preserve the source evidence.
- [Runtime tracing](docs/runtime-tracing.md): investigate consumers when static evidence
  is insufficient; distinguish positive hits from bounded negative traces.
- [Beta research](docs/beta-evidence.md): correlations are not US match or boundary proof.
- [Documentation index](docs/README.md): asset workflows and other task-specific guides.
