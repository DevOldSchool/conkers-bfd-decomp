# Contributing

Human and AI-assisted contributions follow the same clean-room rules and
acceptance gates. Use `./conker` from the repository root. Read this guide once
per task; consult the [workflow reference](docs/decompilation-workflow.md) for
command details.

## Setup

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

Run `finish` only after the edit succeeds and its diff has been inspected, using
separate tool calls for editing/inspection and verification. Shell preparation
steps must stop on failure with `&&` or equivalent; that exit-status guard does
not replace diff inspection. On helper failure, inspect possible partial changes before
retrying. An unchanged rerun requires an explicit verification reason and is not
a new matching hypothesis.

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
Carry exhausted hypotheses and the overall task/function allocation across
continuations. A falling score alone does not reset that allocation or establish
a credible route to completion. Keep real snapshots/cursors distinct from
recomputable address locals, and record the predicted assembly change as well as
the score. `finish` saves each candidate automatically; history annotations and
imported records never establish correctness or replace acceptance gates.
When rejecting a candidate for incorrect behavior, unsupported accesses or insufficient
storage, immediately annotate its saved attempt with `matching-history note <id>
<attempt> --assessment invalid --hypothesis "<reason>"` before restoring or deferring.
Record the reason in the ledger too; ledger text alone does not update automatic history.
Within a continuing group, prioritise one proven sibling found by the permitted
bounded lookup using `./conker next --ready --function <id>`. It retains normal
eligibility/readiness checks and never falls back to another item. Record the
independent ASM/ABI hypothesis; similarity alone does not justify new attempts.

## Acceptance and integration

- A C match requires US `CURRENT (0)` over the **full registered span** against
  independent raw assembly, plus layout, progress and whitespace gates. Compilation,
  generated candidate assembly and register-insensitive comparisons are not proof.
- `progress/functions.json` owns function matches; `progress/source_units.json`
  owns reviewed boundaries and integration. A function match does not complete its
  source unit. Use supported transactions; never hand-edit inventory or generated
  assembly/progress reports. Regenerate reports with `./conker progress render`.
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
For timed pilots, distinguish the original workflow start, excluded setup/restart
intervals, clean-batch completion, report creation and final audit/handoff. Report
end-to-end elapsed time and any overrun separately from the measured matching
window. Mark final-delivery timing unavailable when it cannot yet be observed;
do not use report creation as the endpoint for an end-to-end or zero-overrun claim.

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
