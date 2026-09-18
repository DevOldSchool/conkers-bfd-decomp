# Decompilation workflow

This guide explains the supported command flow for turning a reviewed raw
assembly work item into matched C. Contribution policy and review requirements
remain in [CONTRIBUTING.md](../CONTRIBUTING.md); the clean-room baseline and ROM
setup live in [the bootstrap guide](bootstrap.md).

The active target is US. Contributor commands use that profile by default, and
EU/PAL remains non-gating future metadata.

## Toolchain lifecycle

Docker is the only supported host dependency. The first build-tool command
starts a repository-scoped, network-disabled container using the pinned image.
Source changes are visible through the existing workspace mounts, so later
`m2c`, `diff`, and build commands reuse the warm container.

`next --ready` starts the container before editing. Keep it running across
consecutive functions and follow-up work; use `./conker stop` only for explicit
cleanup or when the broader contribution is finished. If the pinned image
changes, the wrapper replaces the stale container automatically.

The pinned `mips_to_c` files are copied into the ignored
`build/host-tools/` cache and run with the existing host Python. This avoids
repeated amd64 emulation without installing an additional host dependency.

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
unchanged; a separate diagnosis is then unnecessary. Agents route purely
register-only differences to bounded permutation first when the task permits
it. Otherwise they inspect the saved full diff, make one targeted source
revision, and rerun `finish`. The default per-function budget is one manual
revision and one search of up to 32 variants, with plateau stopping retained;
an explicit task budget overrides this default. Exhaustion produces a candidate
report, followed by deferral only when moving past it is authorized. A focused
zero followed by a layout failure requires layout recovery, not permutation.
`permute` searches deterministic declaration-order and first-assignment
lifetime variants with the pinned compiler. A nonzero best result is written
below `build/us/permute/` while project source remains untouched. An exact
variant is restored to source and immediately sent through `finish`.
Each search initializes its own differ settings. Compiler-rejected variants may
be skipped; scorer failures stop with `BLOCKED_TOOLING` and diagnostic evidence,
preserving any already scored best candidate. If no candidate was scored, the
command reports that explicitly and does not claim a saved best file.
When `automate` applies this search to deferred work, a strictly lower nonzero
score replaces the disabled candidate and inventory score transactionally;
equal or worse results preserve the existing source block.
The permutation search writes each improved `best.c` immediately. If the
subprocess is killed with exit 137/SIGKILL, `automate` restores or preserves
project source, records the interrupted candidate, and advances rather than
terminating an `--all` traversal. With `--defer-best`, a completed positive
best score can still be preserved before advancing; if no permutation finished,
the previously measured initial C candidate is preserved instead.

If an older focused match is invalidated by mixed-object layout evidence, do
not edit progress JSON. Reopen it transactionally:

```sh
./conker reopen-match <work-item-id> --reason "<layout evidence>"
```

The command preserves the old C body as a deferred candidate, restores its
canonical `GLOBAL_ASM` pragma and TODO entry, removes invalid match evidence,
and regenerates progress.

Use the unified automation for raw m2c starters and preserved deferred
candidates:

```sh
./conker automate --limit 5 --max-attempts 20 --rewrite-budget 250
```

Target one eligible raw or deferred function without waiting for scheduler
order with:

```sh
./conker automate --function func_15012C84 --rewrite-budget 25 \
  --defer-best --skip-final-build
```

The scheduler alternates between size-ordered raw work and score-ordered
deferred work. Raw starters use evidence-backed declaration recovery, aligned
scalar or pointer field cleanup with expression bases and signed offsets,
explicit integer-backed address casts for IDO, and bounded source-shape
rewrites. Both pools use compact `diagnose-diff` preflight before permutation.
Pure register-allocation differences qualify; register differences with only
one to three missing/extra rows receive a probe capped at 32 variants.
Structural mismatches skip search. Raw candidates preserve the proposed source
and diagnostic log under `build/us/automate/artifacts/<work-item-id>/` and
restore project source even with `--defer-best`. The
command requires warning-free compilation, restores unsuccessful source
attempts, and retains only `CURRENT (0)` results through `finish`. Compiler
failures retain the proposed source, complete output, and structured diagnostics
under `build/us/automate/artifacts/<work-item-id>/`. Before restoration, up to
three compiler-guided target-function repairs cover proven mechanical failures
such as undefined `NULL` and byte-address pointer arithmetic. A deferred
`CURRENT (0)` candidate is sent directly through authoritative recovery rather
than being classified as a structural mismatch. A focused exact candidate that
still fails mixed-object layout is preserved with a `finish`/`layout_gate`
blocker and the measured offset delta; retained unlabeled instructions are not
silently claimed as C or promoted to a new function boundary. With explicit authorization,
`--defer-best` preserves the best compiling nonzero raw candidate through the
ordinary transactional `defer` path.

The exact-permutation handoff is also transactional. If `finish` rejects the
mixed-object layout before recording a match, the source file and deferred
inventory metadata are restored from the same host-side snapshot.

Add `--skip-final-build` for a quick local automation experiment. This skips
only the concluding clean `verify-batch`; each retained function still passes
its focused diff, mixed-object layout, progress, and whitespace checks through
`finish`. The command prints the exact batch command still required. Until it
succeeds, the result is intentionally not commit-ready or handoff-ready.

To consider every function in the active US inventory, use:

```sh
./conker automate --all --defer-best
```

Full mode has no attempt or match cap but keeps the same safety exclusions. It
does not guess ambiguous declarations or cross source-unit integration
transitions. `build/us/automate/all-report.json` is replaced atomically after
each attempt and classifies every inventory entry, including already matched
and explicitly excluded functions. A complete traversal sets `full_scan` and
`scan_complete` to true and leaves no `not_attempted` entries. Do not combine
`--all` with `--max-attempts`. An interrupted run resumes completed outcomes
from the report. Pending exact matches are reconciled against the current
inventory both on resume and before the final batch gate, so functions reopened
or deferred by later mixed-source integration are not sent to `verify-batch`.
Add `--restart` when changed automation should reconsider prior outcomes.

Full scans use compact output to avoid terminal backpressure. Detailed
subprocess output is written to
`build/us/automate/logs/<work-item-id>.log`, and the corresponding report entry
records that path. Stdout contains important events and a progress summary
every 50 candidates. Add `--verbose` to restore the complete live stream.

Attempted report entries include the terminal pipeline stage, a blocker code,
repair actions, and a fingerprint over the candidate source, canonical
assembly, and only that stage's relevant tooling and options. Resume skips only
entries whose stage fingerprint still matches, so preparation, compilation,
or search changes selectively requeue the affected frontier. Legacy entries
without stage metadata are retried once.

Run `./conker automate --all --analyze` to measure preparation coverage without
editing tracked source or inventory and without compiling, permuting, deferring,
finishing, or running the batch gate. It writes the separately resumable
`build/us/automate/analysis-report.json`; ignored m2c caches and that report are
the only outputs. Use `--restart` to intentionally rebuild the complete
analysis report.

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
main-executable work. Accepted evidence kinds are `linker_map`,
`object_symbols`, and `structural_analysis`.

Registration preserves existing sources and otherwise creates a minimal
skeleton with one ordered pragma per unmatched member. Put a reviewed raw unit
into the canonical mixed C/ASM build with:

```sh
./conker progress integrate <work-item-id>
```

Run integration when a reviewed raw unit first enters mixed mode. Run it again
only after every function in that mixed unit matches; successful verification
then moves the assembly-free source under `src/game/done/`. Use
`./conker progress integrate --all-reviewed` to promote multiple reviewed raw
units transactionally.

If later evidence invalidates an untouched game boundary, use
`./conker withdraw-source-unit --source src/game/<unit>.c`. It restores the
range to raw assembly while retaining its function work items and refuses to
discard modified or matched C work.

## Builds and batch verification

`./conker build` targets US by default. `./conker build --all` verifies every
active profile and remains the clean baseline command for CI and future
multi-profile activation.

`./conker game-build` incrementally rebuilds the canonical game overlay and
verifies mixed or completed source units against the decompressed payload. Use
`./conker game-build --refresh` before a pull request, after shared build or
configuration changes, or while diagnosing stale generated state.

After the final function in a logical group, run one composed clean gate:

```sh
./conker verify-batch <work-item-id> [<work-item-id>...]
```

It verifies that every listed item is matched, selects the required main or
game builds, runs the Python suite, and checks metadata, generated progress, and
whitespace. `--incremental` is available for repeated local iteration, but the
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
