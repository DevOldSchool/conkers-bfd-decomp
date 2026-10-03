# Decompilation workflow

This guide explains the supported command flow for turning a reviewed raw
assembly work item into matched C. Contribution policy and review requirements
remain in [CONTRIBUTING.md](../CONTRIBUTING.md); the clean-room baseline and ROM
setup live in [the bootstrap guide](bootstrap.md).

The active target is US. Contributor commands use that profile by default, and
EU/PAL remains non-gating future metadata.

## Toolchain lifecycle

Local builds use Docker; managed executors may use the supported
[cloud namespace adapter](cloud-matching.md). The first build-tool command starts a repository-scoped, network-disabled container using the pinned image.
Source changes are visible through the existing workspace mounts, so later
`m2c`, `diff`, and build commands reuse the warm container.

`next --ready` starts the container before editing. Keep it running across
consecutive functions and follow-up work; use `./conker stop` only for explicit
cleanup or when the broader contribution is finished. If the pinned image
changes, the wrapper replaces the stale container automatically.

The pinned `mips_to_c` files are copied into the ignored
`build/host-tools/` cache and run with the existing host Python. This avoids
repeated amd64 emulation without installing an additional host dependency.

For an optional second opinion, `./conker objdiff compare <id> [<id>...]` runs
the pinned native objdiff CLI alongside the existing diff adapter. See the
[objdiff comparison guide](objdiff.md) for setup, saved evidence, and limitations.

## Select and inspect a work item

Use the bounded ready path for ordinary source-local work:

```sh
./conker next --ready
```

It selects the smallest available function, prewarms the toolchain, and emits
the local inventory, issue metadata, allowed source, source-unit state, nearby
declarations, generated assembly, bounded raw US call sites, and an m2c starter.
Treat its `allowed-edit`, `target-file-dirty`, `source-unit-state`, and
`post-match-action` fields as authoritative.

To prioritise one already identified sibling within the task's scope, use:

```sh
./conker next --ready --function <known-work-item-id>
```

This selects that exact ID through the same validation, raw-item eligibility,
attempt-freshness, ownership context and readiness path. Unknown, unavailable,
deferred, claimed, excluded or unchanged-failed items fail before toolchain
preparation; no alternative is selected. It does not discover siblings, reopen
candidates, reset attempt budgets or expand the task's scope. The read-only
`next --one` modes also accept `--function`. Without it, selection remains by size.

For parallel workers in isolated worktrees, omit sources owned by another worker:

```sh
./conker next --ready --exclude-source src/game/first.c --exclude-source src/game/second.c
```

Each exclusion matches only the exact repository-relative inventory source path,
not a directory, prefix, or glob. It also works with `next --one`, including
`--details`. Selection still validates the project, skips ineligible and unchanged
failed attempts, and emits the same readiness context. If no eligible source
remains, selection fails before toolchain preparation. Exclusions do not claim or
lock files; coordinate source ownership and keep one integrator.

`./conker next` lists the broader queue in ascending US byte size. Use
`./conker next --one --details` only when bounded read-only context is wanted
without prewarming and generating the starter. When the output says
`issue: none recorded`, no GitHub lookup is required.

For an already selected work item, generate a starter directly:

```sh
./conker m2c <work-item-id> > /tmp/<work-item-id>.c
```

The output is a starting point, not type-correct or match evidence. Replace
guessed declarations and placeholder types with project declarations before
testing the candidate.

The command also generates a preprocessed context from `include/types.h` and
the work item's canonical source file, then supplies it to `mips_to_c`. Context
and parser caches remain under ignored `build/m2c/context/` output. Keep private
or partial structures in their owning C file; promote them to a real header only
when recovered cross-source use requires one. This improves starter field names
and type propagation without creating a second maintained copy of declarations.
Sources with unsupported conditional preprocessing safely fall back to an
untyped starter. Context-informed output is still not match evidence.

Call context prefers active declarations in the allowed source, then reviewed
SDK aliases. When those are absent, a unique active definition in the registered
US matched source can supply a scalar/pointer signature despite conflicting
prototypes in unrelated callers. The owning source must agree with its definition;
ambiguous definitions and private types cannot override conflicts. Otherwise the
project declarations must agree. Recovery records the selected evidence in
`build/m2c/calls/<work-item-id>.json`. Local declarations are never overwritten,
and candidates still require the ordinary focused and integration gates.

## Match one function

Replace only the selected function's `GLOBAL_ASM` pragma, at the same source
position, then run the authoritative focused gate:

```sh
./conker finish <work-item-id>
```

`finish` compiles the focused candidate, then compiles its complete reviewed
mixed source object and checks every member offset plus the aligned object
extent. A nonzero focused result or a shifted mixed layout leaves the
inventories unchanged. Only `CURRENT (0)` with preserved layout records the
match, regenerates progress, and checks generated output and whitespace.

On a focused mismatch, `finish` reuses the same JSON evidence to print the raw
`CURRENT` score, four mismatch-category counts, a recommendation, and at most
five differing rows. It saves the complete plain-text comparison and original
JSON under `build/<profile>/diff/<regional-symbol>/mismatch.{txt,json}` and
prints their paths. These files describe the last focused mismatch and are
overwritten by the next one. `./conker diff <work-item-id>` still displays the
full live diff. Classification is a conservative search hint, not proof of
equivalent control flow or stack layout; it never starts permutation or changes
the match gates. A failure to read or save diagnostic evidence reports
`BLOCKED_TOOLING`.

The terminal action states describe the next step:

- `AGENT_ACTION: STOP_MATCHED` means the function matched. Follow the previously
  emitted post-match action.
- `AGENT_ACTION: FIX_COMPILE` means only the reported C or declaration problem
  should be corrected before rerunning `finish`.
- `AGENT_ACTION: CONTINUE_MISMATCH` means the candidate compiled but still
  differs.
- `AGENT_ACTION: FIX_INTEGRATION` means the source or unit layout must change
  before a batch gate is retried.
- `AGENT_ACTION: BLOCKED_TOOLING` is a tooling stop rather than a C mismatch.

`./conker diff --record` and `./conker progress match` remain compatibility
paths. Do not run `progress match` after a successful `finish`, and do not edit
the progress inventories manually.

### Switch tables and linked data

At instruction zero, US game switches receive an additional check in
`diagnose-diff`, `permute` and authoritative focused diffs. Candidate-object switch
relocations are resolved and case targets compared with the checksum-validated
ROM. Unsupported dispatches fail closed; layout and clean-batch verification
remain required.

US game candidates with different address-bearing data aliases may use linked comparison.
Both original objects are linked independently at the registered address; their
entire registered spans must equal each other and the checksum-validated ROM before
those bytes enter the same bounded asm-differ gate. Unsupported relocations retain
symbolic comparison; original objects still supply switch-table evidence. Watch
mode remains symbolic and requires a fresh `finish` afterward.

## Focused iteration

In an interactive terminal, a persistent watcher avoids restarting the focused
compiler and differ:

```sh
./conker diff --watch <work-item-id>
```

The watcher detects main versus game-overlay work from the inventory, rebuilds
the candidate after C or header changes, and keeps the previous result for a
three-way comparison. Exit it and run `finish` once for authoritative evidence.
Noninteractive callers receive `AGENT_ACTION: USE_FINISH_LOOP` and should edit
and rerun `finish` instead.

Focused comparison always uses an independently generated raw-assembly object.
The reference map converts canonical C ranges back to raw assembly so a
candidate is never compared with an object compiled from the same source.

To preserve a useful nonzero candidate while advancing the automatic queue,
use the supported deferral flow after agreeing to move past it:

```sh
./conker defer <work-item-id> --reason "<remaining mismatch>"
./conker next --ready

# Restore the candidate later.
./conker resume <work-item-id>
```

`defer` measures and records the current score, preserves the C in a disabled
source block, restores the canonical pragma, and excludes the item from
automatic selection. `resume` restores the candidate byte-for-byte.

An exact focused candidate that fails its reviewed source-unit layout may also
be deferred. This path reruns the exact comparison and layout check, then
archives the candidate source, mixed object, comparison log and fingerprinted
failure receipt under `build/us/deferred-layout/` before restoring assembly.
Only a measured member-offset or extent mismatch permits this recovery;
successful layout, compilation/tool failures and stale evidence do not. The
item remains raw assembly with preserved C, receives no match credit, and must
pass the unchanged `finish` and clean-batch gates after genuine layout recovery.

If a raw item cannot enter the C candidate loop at all (for example, its
registered span is `.word`-only and the starter finds no instructions), use a
separate, reversible blocker transaction after reviewing the evidence:

```sh
./conker block-raw <work-item-id> --reason "<specific tooling or registration blocker>"
./conker next --ready
# Once the underlying blocker is resolved:
./conker unblock-raw <work-item-id>
```

`block-raw` requires an untouched canonical `GLOBAL_ASM`, records the reason,
and changes only the inventory state and derived progress. It does not claim a
match or fabricate a C candidate. Do not use it for a compiling nonzero C
candidate; use `defer` for that case.

Two bounded helpers reduce blind source-shaping work:

```sh
./conker diagnose-diff <work-item-id>
./conker permute <work-item-id> --budget 32
```

`diagnose-diff` works with active and preserved deferred candidates and reports
register-only, operand/constant, control-flow, and missing/extra categories.
For relative branches, classification compares the displacement using validated
instruction/target addresses, so relocation within an object is not an operand
change. Different displacements and absolute jump targets remain differences.
Nonzero results include a five-row excerpt and save the full text and JSON
under `build/us/diff/<work-item-id>/`, using the same comparison evidence.
Reuse the latest `finish` diagnosis when its source and compile inputs are
unchanged. Follow the [manual attempt rules](../CONTRIBUTING.md#match-a-function)
for revision/search budgets, task permission and plateau stopping. Diagnosis is a
search hint, not behavior proof. A focused zero with failed layout needs layout
recovery, not permutation.

`permute` searches deterministic declaration-order and first-assignment
lifetime variants with the pinned compiler. A nonzero best result is written
below `build/us/permute/` while project source remains untouched. An exact
variant is restored to source and immediately sent through `finish`.
Each search initializes its own differ settings. Compiler-rejected variants may
be skipped; scorer failures stop with `BLOCKED_TOOLING` and diagnostic evidence,
preserving any already scored best candidate. If no candidate was scored, the
command reports that explicitly and does not claim a saved best file.
If an older focused match is invalidated by mixed-object layout evidence, do
not edit progress JSON. Reopen it transactionally:

```sh
./conker reopen-match <work-item-id> --reason "<layout evidence>"
```

The command preserves the old C body as a deferred candidate, restores its
canonical `GLOBAL_ASM` pragma and TODO entry, removes invalid match evidence,
and regenerates progress.

## Automation

For authorized automated work, use the [automation reference](automation.md).
It covers bounded runs, declaration recovery, saved outcomes, interruption recovery,
full scans and experimental search. Automation retains the same focused and clean
batch gates; manual-only tasks must not use it.

## Game reference assembly and work registration

The US profile has reviewed raw-assembly boundaries for the complete
decompressed game overlay:

```sh
./conker game-asm
```

Generated output is ignored under `reference/game/<profile>/asm/`. These splits
make the assembly manageable; they do not by themselves add C sources, match
evidence, or original source-unit boundaries.

For game work, `m2c` first reuses an existing ROM-derived split and then a
validated raw per-function block under `asm/nonmatchings/`. It prepares the
complete game reference only when neither exists. `game-m2c` and `game-diff`
remain compatibility aliases.

Review US proposals before registering a function:

```sh
./conker game-index
./conker register-game \
  --id <work-item-id> \
  --us <us-symbol> \
  --source src/game/<source>.c
```

Use `./conker register-main` for a reviewed main-executable function.
`game-index` is a shortlist, not match evidence. Function registration creates
a work item but does not claim that one function equals one original source
file.

After a full build, locate the first differing word with:

```sh
./conker first-diff
```

## Source-unit boundaries and integration

Register a source unit only after independently establishing its original
object boundary and complete membership. Either name every registered member:

```sh
./conker register-source-unit \
  --overlay game \
  --source src/game/<unit>.c \
  --function <first-id> --function <second-id> \
  --us-start <offset> --us-end <offset> \
  --evidence-kind object_symbols \
  --evidence-reference docs/evidence/<record>.md
```

Or deliberately derive all members from a reviewed range:

```sh
./conker register-source-unit \
  --overlay game \
  --source src/game/<unit>.c \
  --register-members \
  --us-start <offset> --us-end <offset> \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/<record>.md
```

`--overlay game` is the compatibility default; specify `--overlay main` for
main-executable work or `--overlay debugger` for the US debugger image.
Accepted evidence kinds are `linker_map`,
`object_symbols`, and `structural_analysis`.

Registration preserves existing sources and otherwise creates a minimal
skeleton with one ordered pragma per unmatched member. Put a reviewed raw unit
into the canonical mixed C/ASM build with:

```sh
./conker progress integrate <work-item-id>
```

Run integration when a reviewed raw unit first enters mixed mode. Run it again
only after every function in that mixed unit matches; successful verification
then moves the assembly-free source from `src/<path>.c` to
`src/done/<path>.c`, preserving every source subdirectory. For example,
`src/game/camera/example.c` becomes `src/done/game/camera/example.c`.
The path rule is generic and supports main, game and debugger sources. Use
`./conker progress integrate --all-reviewed` to promote eligible reviewed
units transactionally, building the full ROM and/or game image as needed.
Incomplete raw main units remain pending until fully matched.
`./conker normalize-done-sources` migrates legacy
completed-source paths, mappings and inventory together; verify main and game
with a clean `verify-batch` before handoff.

For an individual debugger function, use `./conker register-debugger --id <id>
--us <symbol> --source src/debugger/<file>.c`, then the normal `next --ready`,
`m2c`, `finish` and `verify-batch` commands. Reference extraction and build
verification use the full ROM; debugger code is never read from the compressed
game overlay. Full-span US ROM bytes and debugger jump tables remain required
focused-match evidence. There is no reviewed EU/PAL debugger range.

Debugger source-unit offsets are absolute ROM offsets within
`0x19EA88:0x1A2178`; virtual addresses begin at `0x16000000`. The image uses
8-byte boundary alignment. Existing C collections are provisional scaffolds,
so registering a function does not establish a source-unit boundary. Only an
explicit `register-source-unit --overlay debugger` with reviewed evidence may
adopt an exact existing C mapping as mixed C/ASM. Once every member matches,
integration verifies the full ROM and moves the unit to `src/done/debugger/`.
Keep the loaded data and privileged TLB routine raw unless separately reviewed.

If later evidence invalidates an untouched game boundary, use
`./conker withdraw-source-unit --source src/game/<unit>.c`. It restores the
range to raw assembly while retaining its function work items and refuses to
discard modified or matched C work.

## Verified original assembly

Reviewed handwritten main/game/debugger routines may remain unchanged `GLOBAL_ASM` bodies
with independent full-span ROM proof (for example, routines with a custom ABI):

```sh
./conker verify-original-asm <id> --reason "reviewed custom ABI" --evidence-reference docs/evidence/<review>.md
./conker verify-original-asm <id> --check
./conker verify-original-asm <id> --refresh
```

The command assembles/links the original body, verifies its entire registered ROM
span including embedded data, and records proof transactionally. The `original_asm`
state excludes the item from C-candidate selection and reports it separately. It
contributes no C matches/matched bytes and cannot complete a C source unit.
`verify-batch` accepts these items alongside C matches and revalidates their proofs.

Use `--refresh` when regenerated assembly text changes but the routine's recorded
ROM bytes remain identical. It reassembles the complete span and updates the text
hash transactionally, preserving the existing classification. Changed ROM/span
hashes are rejected; normal validation and `--check` continue to reject stale
evidence. Materialization preserves existing verified original assembly.

Main proofs use the checksum-validated CPU interval, excluding the boot blob and
RSP payloads. Main and debugger batches require full-ROM equality; game batches require the
independently rebuilt game overlay. This does not enable mixed main C/ASM integration
or turn internal branch labels into ordinary C-function entries.

## Sustained manual matching

Use this workflow for an authorized continuing group of functions. Keep the
normal `next --ready`, source ownership, immediate `finish`, and transactional
`defer`/`resume` rules. It does not authorize broader scans, tooling changes,
shared declarations, model changes, or concurrent writers in one checkout.

### Selection and reuse

Prefer a short registered span with a concrete hypothesis: a successful sibling
pattern, an evidence-backed declaration/type correction, or an identifiable
expression/lifetime mismatch. Do not rank solely by `CURRENT`: a small register
mismatch may resist many changes, while a larger structural mismatch may have
a direct fix. Refresh diagnostics when relevant inputs have changed.

After a match, make one bounded lookup for nearby or similar raw-assembly
siblings within the authorized scope; keep the existing per-target lookup
limit. If it yields an eligible sibling with a concrete ASM/ABI hypothesis,
record that lead and prioritise it with `next --ready --function <id>` before
returning to size-based selection. For an untouched-only task, the sibling must
also be untouched. If the selector rejects it, retain the lead with its blocker
and return to ordinary selection; do not clear history or construct queue-wide
source exclusions to force it through.

Useful hypotheses demonstrated in prior manual work include returning
a floating-point comparison directly, restoring an evidence-backed unused
parameter that produces an argument-home store, naming mask/offset locals,
correcting pointer types, and shortening local lifetimes. Check each sibling's
assembly and ABI independently. Neither a similar body nor a reused source
pattern establishes a match.

### Edit completion before verification

Confirm each edit helper returned success and inspect the resulting diff before
running `finish`. Separate tool calls make that boundary explicit. If combining
an edit and preparation steps in a shell command, use `&&` to propagate failure;
a newline or semicolon alone continues after a failed edit. The exit-status guard
does not replace diff inspection. For example, run `edit-command && git diff --
<allowed-source>`, inspect the output, then invoke `./conker finish <id>` in a
separate tool call. A helper may write partially before failing, so inspect the
source before repairing or retrying it.

Do not run an unchanged candidate as a new hypothesis. Explicit caller rechecks,
changed compiler/declaration inputs or recovery verification may require a rerun;
record that reason and count it separately. Log compilation repairs and accidental
duplicates separately from distinct tested source hypotheses.

### Durable manual attempt ledger

Every ordinary `./conker finish` saves a unique attempt under
`build/us/matching-attempts/<id>/<attempt>/` before running the existing gates.
It retains full source, the exact target definition when extractable, input
fingerprints, output, newly emitted mismatch evidence, command time, score and
terminal action. Interrupted starts remain visible. These are local, ignored
records, not inventory or verification evidence. A focused zero with a failed
layout gate remains unaccepted; `STOP_MATCHED` does not establish `BATCH_COMPLETE`.

Use a task-owned Markdown/JSONL ledger under `build/us/manual-attempts/<task-id>/`
for reasoning and pending batch IDs. Existing ledgers are not migrated or parsed
automatically. `next --ready` shows recent automatic history plus bounded matching
leads; it checks main reference assembly and the SDK pin before prewarming Docker.
The readiness check reports missing inputs without changing a submodule or building.

Record one compact entry per tested hypothesis:

| Field | What to retain |
| --- | --- |
| Target | Function ID, source path, timestamp, and task ID |
| Inputs | Hashes of candidate body and relevant declarations, headers, raw reference, compiler/tool inputs; profile and search settings |
| Hypothesis | Expected instruction, operand, control-flow, or lifetime change |
| Attempt | Exact source change or saved candidate artifact and attempt number |
| Result | Full-span `CURRENT` score, diagnostic classes, terminal action, and evidence paths |
| Best and exhausted | Best candidate artifact/hash, tried source shapes, and why further work stopped |
| Verification | Pending batch IDs, time the first pending match was added, and clean batch outcome |

Save enough context to recover the hypothesis after compaction. Shared diff and
permutation output paths may be overwritten; copy useful best candidates and
diagnostics into the task-owned directory before that happens. Keep pending
batch IDs in a small checkpoint updated after each match and clean batch.

```sh
./conker matching-history show <id>
./conker matching-history note <id> <attempt> --hypothesis "real cursor, derived row address" --expected "frame contracts; cursor advance unchanged" --assessment structural
./conker matching-history note <id> <attempt> --exhausted
./conker matching-history export <id> /private/tmp/attempts.zip
./conker matching-history import /private/tmp/attempts.zip
./conker matching-context <id> --mechanism real-state
./conker matching-callers <changed-callee>
```

Assessments are `unreviewed`, `valid`, `invalid`, or `structural`: reviewer notes,
not automated correctness checks. The lowest observed score is reported only for
compatible recorded context, excluding explicitly invalid or changed candidates.
It is distinct from a useful structural experiment or a reviewed valid candidate.
The latest recorded `finish` action and score remain visible separately, even when
context changes such as generated TODO cleanup exclude that attempt from comparable
scores. This is a historical result, not fresh verification or batch acceptance;
the source/context hashes and comparison rules remain strict.
Deferral warns about a lower compatible archived score but never restores source
automatically. Review the saved `function.c` and its context before using it in the
allowed target region; never replace a whole unit to recover one function.

Export/import carries source snapshots, results and notes with integrity checks;
it does not alter C, inventory, pending batches or match credit. Carry the task
ledger separately, since ignored evidence does not move with Git commits. New
source, header, raw-reference or tool inputs can invalidate old comparisons.
Commands report accumulated command duration separately from workflow wall time.
The ready snapshot and successive finish snapshots distinguish changed/removed
source-local declarations from additions, including new function definitions.
Caller-review reminders cover changes/removals and additions referenced by
pre-existing active local C bodies. Such additions are review leads, not proof of
implicit calls: headers or macros may already supply a declaration. Other additions
are recorded without a caller-review command. This classification uses only the
two source snapshots, not a repository-wide caller scan. Ambiguous or unavailable
existing definition bodies retain a conservative reminder for additions, explicitly
labelled as uncertain coverage. Alternatives after literal `#if 0` also retain
this reminder because the local active-text filter may omit those branches.
`matching-callers` searches registered
matched definitions on demand; direct C spellings are incomplete leads, excluding
indirect, macro-expanded and raw ASM callers. Review these contracts and recheck
affected matches. Typedef-definition or expanded-macro changes need manual review.

Consult the ledger before `resume` or another search. Unchanged inputs and an
exhausted hypothesis should be skipped. A changed fingerprint permits review,
but does not by itself justify repeating the same failed approach: identify
how the change addresses the remaining mismatch. Existing automation and
permutation caches complement this ledger; they do not record every manual
hypothesis. Never edit inventory JSON or automatic cache records to maintain it.

Follow the [manual attempt limits](../CONTRIBUTING.md#match-a-function) when
consulting exhausted hypotheses. Preserve candidates transactionally when moving
on is authorized.

### Low-usage manual m2c mode

When minimizing model/tool-output usage, use one candidate cycle per ready function:
`next --ready`, inspect the emitted starter/assembly, make one narrow source-only
replacement, then `finish`. Prefer small functions. Do not repeat context commands,
rerun unchanged `finish`, or search broadly after context is available. Inspect more
diffs or make further variants only when additional effort is authorized and a
narrow, promising hypothesis exists. Defer nonzero candidates when moving on is
authorized; all focused, layout, progress, whitespace and batch gates still apply.

### Measuring improvement

Track newly clean-batch-verified functions per wall-clock hour, keeping rechecks
and deferred-score improvements separate. Record actual model tokens only when
available; command output bytes are not token usage. Separate command duration
from end-to-end workflow time. Save these timing boundaries explicitly:

- Original workflow start, plus the start/end of each excluded setup or recovery interval.
- Measured matching start and its deadline; retain the original start if a restart is necessary.
- Clean-batch completion and report-file creation as separate milestones.
- Completion of final audit/handoff and final delivery, when observable; otherwise label
  the endpoint unavailable or state the last observed time instead of claiming completion.

Final review, checkpointing and handoff are workflow work, even after the report
file has been saved. Compute measured-window and end-to-end durations separately,
identify the denominator used for throughput, and include late final work in
overrun reporting. Do not turn an early report timestamp into a zero-overrun claim
while later work remains. Setup exclusions and restarts must stay visible; an
interrupted start does not erase attempts, selected targets or elapsed effort.

Describe exactly what validation checked: game batches verify the independently
rebuilt US GAME image and mapped data, while main/debugger gates require full-ROM
equality. Do not relabel a game-image comparison as a whole-ROM rebuild.

Compare workflow or model changes on a small,
comparable candidate cohort and retain all acceptance gates. Keep current model
settings unless a model experiment is explicitly requested; medium versus high
reasoning remains an experiment, not an established improvement for this project.

## Builds and batch verification

`./conker build` targets US by default. `./conker build --all` verifies every
active profile and remains the clean baseline command for CI and future
multi-profile activation.

`./conker game-build` incrementally rebuilds the canonical game overlay and
verifies mixed or completed source units against the decompressed payload. Use
`./conker game-build --refresh` before a pull request, after shared build or
configuration changes, or while diagnosing stale generated state.

After the final function in a logical group, run one composed clean gate.
During sustained matching, aim for 5–10 focused matches per group. Flush a
smaller pending group at about 45 minutes after its first match, before stopping,
handoff, commit/PR, or at a required integration boundary. Follow
`post-match-action` immediately; batch scheduling does not postpone required
source-unit transitions. Avoid singleton full batches merely because a function
matched, and do not run empty batches. Record pending IDs durably and clear them
only after clean success. If blocked, report the pending group and its blocker.

```sh
./conker verify-batch <work-item-id> [<work-item-id>...]
```

It accepts matched C and verified `original_asm` items, selects the required
main/game builds, revalidates original-assembly proofs, runs the Python suite, and
checks metadata, generated progress and whitespace. `--incremental` is available for repeated local iteration, but the
default clean form is required before committing, handing off, or opening a
pull request.

Do not rerun an unchanged failed clean batch. The command records the build
input fingerprint and rejects an identical retry; change the source or layout
first.

## Regional and progress rules

`progress/functions.json` is the canonical instruction-match inventory.
`progress/source_units.json` separately tracks reviewed C-file boundaries and
integration state. A registered function may be matched before its containing
source unit is complete.

The generated [progress report](progress.md) counts exact US function bytes and
fully matched source-unit bytes separately. EU/PAL records remain future
metadata and do not gate active work.
