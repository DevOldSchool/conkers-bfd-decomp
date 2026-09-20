# Contributing

Human and AI-assisted contributions follow the same clean-room workflow and
acceptance gates. Detailed command behavior lives in the
[decompilation workflow](docs/decompilation-workflow.md); this file keeps the
rules contributors need while editing.

## Setup

1. Install Docker and run `./conker doctor`.
2. Obtain the reviewed US ROM yourself, place it at `roms/baserom.us.z64`, and
   run `./conker setup --us roms/baserom.us.z64`. Setup validates the SHA-1 in
   `config/roms.json`; ROMs and build outputs are ignored by Git.
3. Follow [the bootstrap guide](docs/bootstrap.md) until raw baselines exist.

The active target is US. EU/PAL metadata is preserved for future work and does
not gate progress.

## Select and match a function

Use the supported `./conker` interface. Read this guide once at the start of a
task, inspect `git status --short` once, and preserve unrelated staged and
unstaged work. Use an isolated worktree unless the user explicitly directs
work on the current checkout.

```sh
./conker next --ready
# Replace only the selected GLOBAL_ASM pragma with C at the same position.
./conker finish <work-item-id>
# After a requested group:
./conker verify-batch <work-item-id> [<work-item-id>...]
```

`next --ready` is authoritative for `allowed-edit`, `target-file-dirty`,
`source-unit-state`, declarations, bounded call sites, and `post-match-action`.
Do not edit a dirty or overlapping source when ownership is unclear. If it
reports `issue: none recorded`, do not query GitHub.

Use project scalar aliases and existing declarations. If evidence is local and
incomplete, use a source-local partial structure or a typed pointer. Never put
`M2C_FIELD` or `M2C_UNK` in project source, invent a private ABI, change a
shared header for one function, alter assembly, or add inline assembly.
Preserve `sb`/`sh` parameters as `s32` unless project evidence proves another
type. Copy each concrete required declaration before the first `finish` attempt.

A function matches only when the independent full registered US span reports
`CURRENT (0)`. `finish` also performs the source-unit layout, progress, and
whitespace gates. A focused match does not complete its source unit.
Generated `asm/`, progress reports, and inventory JSON are outputs: do not edit
them by hand. Follow the emitted post-match action; integrate only at the
reviewed source-unit transition.

For a mismatch, use the latest `finish` diagnosis. Make at most three
source-only variants for a bounded manual attempt. Use `diagnose-diff` when
evidence is stale or unavailable, and use `diff --watch` only with interactive
stdin and stdout. A register-only candidate may use one `permute --budget 32` search
per distinct candidate and settings when the task allows it. Increase the budget only
after improvement or a new source shape; never repeat an unchanged search. Otherwise
inspect the saved full diff, make two targeted revisions, and rerun `finish`. If it remains unmatched, report `candidate`.
When explicitly authorized to move on, use `./conker defer <id> --reason ...`;
use `resume` or `reopen-match` for supported recovery. Never reproduce those
transactions by editing inventory JSON.

### Low-usage manual m2c mode

When minimizing model and tool-output usage, use one bounded candidate cycle per
ready function:

```text
./conker next --ready
        |
        v
Use the emitted m2c starter and assembly context
        |
        v
Make one narrow source-only replacement
        |
        v
./conker finish <id>
        |
        +--> CURRENT (0): retain the match
        |
        +--> nonzero: defer the candidate when authorized
```

Prefer small ready functions. Do not repeat `next`, rerun an unchanged
`finish`, or perform broad repository searches after the emitted context is
available. Inspect a full diff or make further variants only when the user
explicitly authorizes additional effort and the diagnosis identifies a narrow,
promising revision. These usage-saving practices never relax the authoritative
`CURRENT (0)`, layout, progress, whitespace, or `verify-batch` gates.

## Source units and registration

Review the US assembly and real object-boundary evidence before registration.
Function registration does not establish an original C file boundary. Use
`register-game` for reviewed game-overlay functions and `register-main` for
main-executable functions. Register a source unit separately only after every
member and its range are reviewed:

```sh
./conker register-source-unit \
  --overlay game --source src/game/<unit>.c \
  --register-members --us-start <offset> --us-end <offset> \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/<unit>.md
```

Accepted evidence kinds are `linker_map`, `object_symbols`, and
`structural_analysis`. Alignment, a successful standalone build, or a matching
function does not prove original ownership. Registration creates an ordered
skeleton without overwriting existing work. If later evidence invalidates a
boundary, use `withdraw-source-unit`; do not edit the skeleton or inventory by
hand. Keep the reviewed source-unit comment directly below its include block.

The two source-unit transitions are:

```sh
./conker progress integrate <work-item-id>  # enter reviewed mixed mode
./conker progress integrate <work-item-id>  # complete after every member matches
```

After integration, rerun `./conker progress check` and
`git -c core.whitespace=cr-at-eol diff --check`.

## Automation

Automation is resumable, bounded, and evidence-backed. It preserves unrelated
source, restores unsuccessful attempts, saves compiler and mismatch artifacts,
and routes exact results through `finish` and the final `verify-batch` gate.
Use a small run while evaluating a change:

```sh
./conker automate --limit 5 --max-attempts 20 --rewrite-budget 32
./conker automate --function <work-item-id> --rewrite-budget 25 \
  --defer-best --skip-final-build
```

Raw and deferred candidates receive compact `diagnose-diff` preflight. Pure
register differences are eligible for bounded search; one to three missing or
extra rows receive a probe capped at 32 variants. Structural differences skip
search. Preparation and compiler failures retain artifacts under
`build/us/automate/artifacts/<work-item-id>/` and restore project source.

### Reuse previous work

Execution runs share fingerprinted outcomes in
`build/us/automate/attempt-history.json`, importing existing execution reports
on first use. Bounded runs and `next --ready` skip unchanged failed attempts.
Source, assembly, relevant declaration evidence, headers, tooling, or search
settings invalidate the applicable cache. History is local to each worktree.
`--restart` retries cached automation outcomes for the selected scope; it never
discards pending batch verification. Identical nonmatching `permute` searches
also reuse their saved result; change source or search settings to search again.

All automation runs use compact output by default; `--verbose` echoes full
commands. Both modes retain command logs. Preparation failures retain the m2c
starter under `build/us/automate/artifacts/<id>/starter.c`.

```sh
./conker blockers --limit 20
./conker blockers --json
./conker automate --function <work-item-id> --restart --rewrite-budget 32
```

The blocker report ranks missing declarations and placeholder families across
saved failures, excludes functions already matched, and shows representative
dependents. It does not revalidate fingerprints, and counts can overlap. Resolve
high-frequency declarations from project evidence, then retry dependents. Inspect
saved starters to develop narrow preparation rules; do not infer unknown types
from blocker counts or replace placeholders indiscriminately.

Completed execution reports include elapsed time, cache hits, attempted IDs,
command-log bytes, and separate newly verified and carried verified match counts.
`--model-tokens N` accepts an externally measured token count for that invocation
and reports new batch-verified matches per 1,000 tokens. Missing token counts stay
null; command-log bytes are not model tokens or the volume displayed to an agent.
Compare the same candidate cohort when evaluating a workflow change.

The full scan is an explicit, long-running operation:

```sh
./conker automate --all --defer-best
```

It writes `build/us/automate/all-report.json` incrementally. An interrupted run
has `scan_complete: false`; resume it with the same command. Do not combine
`--all` with `--max-attempts`. `--analyze` is non-mutating preparation only;
it does not compile, permute, defer, finish, or run a batch gate. A report is
coverage evidence, not match evidence: require `CURRENT (0)`, layout checks,
and `BATCH_COMPLETE`.

## Integration and review

Run one clean `verify-batch` for the requested group before handoff, commit, or
pull request. A failed clean integration must be fixed at its source or linker
layout before retrying; the command records an input fingerprint and rejects an
unchanged retry. Focused instruction matching, linked data/rodata matching, and
source-boundary confidence are separate claims. A ROM-backed external data
mapping must be documented and verified against the checksum-validated ROM; it
must not be used to hide an incorrect source boundary.

The focused reference is independently generated raw assembly. Never compare a
C candidate with an object built from that same C source. Do not mark a function
matched from compilation alone or from register-insensitive comparison.

For a complete Rare library reconstruction, first prove the full object's text,
relocations, data/rodata, BSS ownership, archive mapping, and full-image match;
then use `retire-library-units` with preserved source evidence. Beta ROMs are
research inputs only: `beta-index` correlations do not establish US match or
source-boundary evidence.

AI-assisted changes must be reviewable, narrow, reproducible, and independently
verified by the maintainer. Report function/source, changed files, shared
dependency requirement, US focused result, whitespace result, status, and
attempts for function work.
