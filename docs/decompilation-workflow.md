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

`--function` selects only that ID through the usual eligibility, attempt-freshness,
ownership and readiness checks. Unknown, unavailable, deferred, claimed, excluded
or unchanged-failed items fail before toolchain preparation, without fallback.
It does not discover siblings, reopen candidates, reset budgets or expand scope.
Read-only `next --one` modes also accept it; default selection remains by size.

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
When the lightweight context extraction cannot handle includes, macros or
conditionals, the wrapper uses the pinned IDO preprocessor with the profile's
actual compiler flags. This follows active conditional branches and included
headers; it does not import disabled candidate bodies. Unknown pragmas that
could affect layout fail closed. A failed recovery reports its reason and
keeps the untyped starter. Inspect this path with
`./conker m2c-context --profile us src/game/<source>.c`.
Context-informed output is still not match evidence.

Context artifacts live under `build/m2c/context/<profile>/`, with a JSON sidecar
recording the extraction method, content hash and any failure. Compiler-backed
context is regenerated on each invocation so header and macro changes cannot
silently reuse old declarations; unchanged content retains the m2c parser cache.

To explicitly use a local fork for host generation:

```sh
CONKER_MIPS_TO_C=/absolute/path/to/m2c-conker/m2c.py ./conker next --ready
```

The wrapper validates that path and uses its package directory for Python
imports. Invalid overrides fail rather than falling back to another generator.
Without an override it retains the pinned cached tool. The call-evidence JSON
records the selected generator path, requested options, Python-source hash,
Git revision when available, and source-context hash. The content hash captures
uncommitted generator changes as well as committed versions.

Call context prefers active declarations in the allowed source, then reviewed
SDK aliases. When those are absent, a unique active definition in the registered
US matched source can supply a scalar/pointer signature despite conflicting
prototypes in unrelated callers. The owning source must agree with its definition;
ambiguous definitions and private types cannot override conflicts. Otherwise the
project declarations must agree. Recovery records the selected evidence in
`build/m2c/calls/<work-item-id>.json`. Local declarations are never overwritten,
and candidates still require the ordinary focused and integration gates.

## Shared function declarations

Use `include/<overlay>_functions.h` for reviewed cross-source function
prototypes, starting with `include/game_functions.h`. Include it in each owning
definition and every source that uses a covered function; remove their local
prototype copies, including declarations retained for deferred callers. Keep
shared type definitions in focused headers such as `include/game_command.h`,
which the overlay header includes as needed. Private or partial structures stay
in their owning C file. These headers are maintained source, not generated m2c
output, and are seeded incrementally as interfaces are reviewed.

Use the registered matched C definition as the starting evidence, then audit
all declaration sites and callers before adopting its signature. A matched body
can omit unused parameters, so a self-contained signature alone is insufficient
proof of the full call contract. Review argument count, return use, conversions,
signedness and o32 argument locations; unresolved families remain separate ABI
review work. Never add casts or remove arguments simply to satisfy a header.

Adding a header makes every one of its prototypes visible from the top of each
including translation unit. Audit all references to its functions across those
files, including earlier implicit calls and address-taking. Recheck the affected
matched definitions and callers with full-span US `finish`, then run a clean
`verify-batch`; retain pending IDs until `BATCH_COMPLETE`. The overlay-header
ownership test rejects duplicate local prototypes and missing includes for
active C references; compiler and matching gates still establish type agreement
and instruction preservation.

The m2c starter and `prepare_starter` never redeclare a function owned by a
reviewed `*_functions.h` header. If the source does not already include that
header in its initial include block, `next --ready` lists it under
`required-includes` and automation adds the include after that block; add it
the same way when editing by hand. Initially included header prototypes seed
call recovery as local declarations, and the flattened source context inlines
guarded reviewed headers, so sources need no IDO preprocessing just for them.
A recovered signature that disagrees with the header is omitted and reported as
an ABI review note. Other prototypes are reused only when the IDO
preprocessor proves they come from the initial include block; recovered
declarations are otherwise retained when visibility or type agreement is
uncertain, or source context falls back. The call-context evidence records the
recovered, emitted and header-conflicting declarations and required includes; header reuse does not
change the signature supplied to the decompiler.

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

Reviewed GAME units also support terminal alignment padding when a focused
compilation omits ASM siblings and therefore produces fewer padding bytes. The
complete unit is freshly compiled; every member offset, the exact object
extent, and all linked unit bytes must match their reviewed boundaries and the
checksum-validated ROM. The final 4–12 zero bytes must already exist in that
object, without another symbol or relocation. The comparison retains the full
registered reference span. See the [five-case evidence](evidence/data-layout/us_focused_text_padding.md).

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
### Fast probing

Use `probe` to compare several hypotheses without editing source or recording
attempts:

```sh
./conker probe <work-item-id> build/us/manual-attempts/<task>/a.c build/us/manual-attempts/<task>/b.c
./conker probe <work-item-id> --layout [<variant.c>]
```

Each variant file holds the function definition, optionally preceded by the
declarations it needs; a file containing `#include` is used as the complete
source. Define the function under its regional symbol or the source's profile
macro alias; a differing work-item ID would not emit the scored symbol. Variants are spliced in memory, compiled with the pinned flags under
`build/us/probe/<symbol>/`, and scored with the same focused asm-differ
comparison as `diff`, in one warm-container pass. The table also reports each
frame size against the reference. `--layout` prints the frame size and every
named local's stack offset read from IDO's `.mdebug` symbols. A probe score is
search evidence only: apply the chosen body and run `finish`. One probe batch
counts as one manual revision for the attempt limits; record its hypothesis and
best score in the ledger.

### Diagnosis checklist

Check these before reshaping statements:

- Frame size or every stack offset differs: run `probe --layout`. IDO gives each
  named local, including unused and register-allocated ones, a slot in
  declaration order from the frame top. Compare the count and order of named
  locals with the reference offsets before changing expressions.
- Frame differs although the locals agree: the area below the lowest local is
  outgoing arguments, saved registers and reserved spill words. Some constructs
  reserve an extra word; in `func_150DE7C0`, a variable array index
  (`array[i]`) did and pointer arithmetic (`*(array + i)`) did not.
- A float register differs on a rodata constant load: IDO's FP temporaries
  rotate through `$f4`, `$f6`, `$f8`, `$f10`, `$f16` and `$f18`, never `$f12`
  or `$f14`, so `$f12`/`$f14` mean a register-allocated value. An `extern f32`
  symbol is promoted as a global, whereas a float literal competes as a constant
  with different allocation priority. Read the value from the checksum-validated
  ROM and try the literal; owned literals need a reviewed
  `config/game/us-rodata.ld` mapping and
  [data-layout evidence](evidence/data-layout/README.md).
- Only a few register rows remain and nothing structural differs: try one
  bounded `permute` before more manual passes.

After one failed sweep of a hypothesis family, such as statement orders, change
the hypothesis instead of repeating that family.

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

After a default build, locate the first differing word with (add `--assets`
for the reconstructed-assets output):

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
./conker verify-original-asm <id> [<id>...] --refresh
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
evidence. Name every stale item in one refresh: only the named items may carry a
stale text hash while each is re-verified in turn. Materialization preserves existing verified original assembly.

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

After a match, make at most one bounded sibling lookup within scope. Record a
concrete ASM/ABI hypothesis and prioritise an eligible result with
`next --ready --function <id>`; untouched-only tasks require an untouched sibling.
If rejected, record the blocker and return to ordinary selection. Never clear
history or construct queue-wide exclusions to bypass the selector.

Useful hypotheses demonstrated in prior manual work include returning
a floating-point comparison directly, restoring an evidence-backed unused
parameter that produces an argument-home store, naming mask/offset locals,
correcting pointer types, and shortening local lifetimes. Check each sibling's
assembly and ABI independently. Neither a similar body nor a reused source
pattern establishes a match.

### Edit completion before verification

Follow the [edit and recheck rules](../CONTRIBUTING.md#match-a-function).
Caller checks, changed compiler/declaration inputs and recovery may justify an
unchanged rerun; record its reason separately from new hypotheses.

### Durable manual attempt ledger

Each `finish` saves source, the extractable target definition, input fingerprints,
output, fresh mismatch evidence, command duration, score and terminal action under
`build/us/matching-attempts/<id>/<attempt>/`. Interrupted starts remain visible.
These ignored records do not establish acceptance: focused zero with failed layout
is unaccepted, and `STOP_MATCHED` does not establish `BATCH_COMPLETE`.

Keep reasoning and pending batch IDs in a task-owned Markdown/JSONL ledger under
`build/us/manual-attempts/<task-id>/`; existing ledgers are not parsed automatically.
`next --ready` shows recent history and bounded leads, then checks main reference
assembly and the SDK pin before prewarming. Missing inputs are reported without
changing a submodule or building.

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
./conker matching-history note <id> <attempt> --hypothesis "real cursor" --expected "smaller frame" --assessment structural
./conker matching-history note <id> <attempt> --exhausted
./conker matching-history note <id> <rejected-attempt> --assessment invalid --hypothesis "Unsupported memory access; raw code does not read this field"
./conker matching-history export <id> /private/tmp/attempts.zip
./conker matching-history import /private/tmp/attempts.zip
./conker matching-context <id> --mechanism real-state
./conker matching-callers <changed-callee>
```

Assessments (`unreviewed`, `valid`, `invalid`, `structural`) are reviewer notes,
not correctness checks. Immediately mark each attempt rejected for incorrect
behavior, unsupported accesses or insufficient storage `invalid`, before restoring
or deferring. Put the concrete reason in both its hypothesis annotation and the
task ledger; ledger text alone does not update automatic history. A worse score
or plateau is not an invalidity finding.

The lowest observed score includes only compatible, unchanged, non-invalid
candidates; it does not establish validity. The latest `finish` result remains
visible when context changes exclude it from comparison. Neither is fresh or batch
verification. Deferral warns of a lower compatible score but never restores source.
Review saved `function.c` and its context; restore only the allowed target region.

Export/import verifies snapshot integrity without changing C, inventory, pending
batches or match credit. Carry ledgers separately: ignored evidence does not move
with Git. Changed source, headers, references or tools can invalidate comparisons.
Command duration is separate from workflow wall time.

Ready/finish snapshots distinguish changed or removed local declarations from
additions, including definitions. Caller-review reminders cover changes/removals
and additions referenced by pre-existing active C. Headers or macros may already
provide declarations, so additions are leads, not proof of implicit calls; other
additions are only recorded. Ambiguous/missing bodies and alternatives after
literal `#if 0` retain reminders labelled as uncertain coverage. This comparison
uses local snapshots, not a repository-wide scan.

`matching-callers` searches registered matched C definitions on demand. Direct
spellings omit indirect, macro-expanded and raw ASM callers. Review actual caller
contracts and recheck affected matches; typedef and macro changes need manual review.

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

Measure new clean-batch-verified matches per wall-clock hour, separately from
rechecks and candidate improvements. Report actual model tokens when available;
output bytes are not token usage, and command duration is not workflow time.

Record these milestones:

- Original workflow start and each excluded setup/recovery interval; retain them across restarts.
- Measured matching start and deadline.
- Clean-batch completion and report creation, separately.
- Final audit, handoff and delivery; label unobservable endpoints unavailable.

State the throughput denominator and report measured-window and end-to-end time
separately. Include late audit/handoff work in overruns: an early report timestamp
does not prove completion or zero overrun. Restarts do not erase attempts or effort.

Describe the validation scope accurately: GAME batches verify the rebuilt US GAME
image and mapped data; main/debugger gates require full-ROM equality.

Compare workflow changes on a small, comparable cohort with all acceptance gates.
Keep model settings unchanged unless an experiment is explicitly requested.

## Builds and batch verification

`./conker build` targets US and uses original ROM asset banks by default. This
is the normal C-matching path, including main/debugger integration and
`verify-batch`. It still compiles the integrated C, links the full image, audits
loaded data and requires byte-for-byte equality with the checked ROM. It does
not prove asset reconstruction. GAME has its separate `game-build` gate.

Use `./conker build --assets` when working on assets. This rebuilds reviewed
textures, fonts and MP3 inputs and validates the audio splits. ROM-backed CI
uses `./conker build --all --assets`; `--all` means all active profiles, currently
US. Native data reports explicitly build their reconstructed targets regardless
of the default build mode.

Default ROM/ELF/linker outputs live under `build/us/original-assets/`.
Reconstructed outputs retain `build/us/`. Both share C/SDK objects, but original
bank objects have distinct names from reconstructed asset objects. Use
`./conker first-diff --assets` to inspect the reconstructed ROM and plain
`./conker first-diff` for the default ROM. Low-level Make callers opt into
reconstruction with `ASSETS=1`.

Preparation is cached by the materialized profile, ROM, symbol/relocation maps,
toolchain inputs and generated file contents. Missing or changed generated
files invalidate it. `--refresh` forces a new split; it does not delete editable
asset inputs or force unchanged asset encoders to run. An interrupted split
cannot retain a successful cache stamp. Switching modes preserves separate
linker scripts and checks that the shared assembly still matches.

`CONKER_JOBS` controls Make jobs and objdiff worker pools across builds,
preparation, batch verification and integration (default: 4). For serial runs,
use `CONKER_JOBS=1 ./conker verify-batch <ids...>` or
`CONKER_JOBS=1 ./conker objdiff report`. `build` and `prepare` also accept
`--jobs N`, which overrides the environment for that invocation. The setting
is forwarded into both warm and disposable toolchain containers.

Builds print stage durations and append timestamped results, commands and exit
codes to `build/timings/us-original.jsonl` or `us-rebuilt.jsonl`. SDK, preparation,
asset encoding (when needed), compile/link/verification and build totals are
reported. Nested stage durations overlap; do not sum them. The final shell
summary also includes setup and Docker overhead. For a comparison, use the
same checkout, job count and cache conditions, run modes sequentially, and
label refreshed versus warm builds. These are command timings, not total
interactive workflow time.

Local comparison on 2026-10-10, using the same checkout and pinned Docker
image with four jobs, run sequentially after tests:

| Command | Preparation | Command wall time |
| --- | --- | ---: |
| `./conker build --refresh` | Refreshed, original asset banks | 25.22 s |
| `./conker build` | Cached, original asset banks | 18.86 s |
| `./conker build --assets --refresh` | Refreshed, asset encoders executed | 445.83 s |

All three produced the byte-identical US ROM. The asset run spent 69.28 s in
texture reconstruction (6,865 streams), 1.50 s in fonts and 7.18 s in MP3
packing. Existing SDK objects and editable asset inputs were retained; these
are not fresh-checkout/bootstrap timings. The remaining asset-build cost
includes Make's large dependency graph, object creation, linking and verification.
The refreshed default pathway was 17.7 times faster in this comparison.

The wrapper defaults to four Make jobs. Use `--jobs 1` or `CONKER_JOBS=1` for a
serial build; `--jobs` takes precedence. Reuse the same isolated worktree for a
related batch so unchanged SDK objects, asset parts and report candidates stay
available. Do not share mutable build directories between implementation
checkouts.

US ROM builds also run `data-splits-check`. The ownership manifest
`config/data/us.json` lists both `src/<overlay>/...` and
`src/done/<overlay>/...` alternatives for each source owner; exactly one must
exist. The normal `next --ready` / `finish` / integration flow can move a file
between those paths without editing the manifest. Keep the existing transactional
move rather than copying the source and leaving both files active.

Adding or removing a reviewed linker/private-data placement requires updating its
owner entry in the same change. The key is the loaded hex address plus the input
section; source owners list both paths, while SDK owners identify the archive and
member. An extent-only change at the same address/section needs no owner edit.
`next` and `finish` do not infer owners or grant permission to change shared linker
placements. After an authorized placement change, run `./conker objdiff data-audit`
for a focused check before the normal build/integration gates. A mismatch lists
missing or extra keys in `config/data/us.json`; resolve the ownership evidence
rather than disabling the audit. The audit decompresses the checked GAME archive
and currently takes about 0.4 seconds locally.

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

### Asset reconstruction batches

The [asset acceptance rules](../CONTRIBUTING.md#asset-and-build-changes) also
apply when changing existing reconstruction code: selectors (including
`texture_cpu_*`), packers and their model helpers, encoder contracts, asset
layouts or shared build/preparation dependencies affecting reconstruction.
Run `./conker build --assets` once after the related changes are ready, before
handoff/commit/PR, and record the tested commit and byte-identical US ROM result.
Default builds, `finish`, `verify-batch` and public PR CI do not provide this
asset gate. Without a ROM, mark verification pending for a maintainer to complete
before merge. C-only and documentation-only changes do not require this gate.

After proving a new format with one pilot, work on a cohesive group of assets
using that format; start with 10–25 entries where the existing encoder supports
them. Per asset, verify reconstruction against the independent ROM bytes,
including compression when stored bytes are the report unit. Keep focused
tests around the changed packer, boundaries and reporting contract. Host tests
are useful for iteration; Docker remains the full-suite acceptance runner.

Run the full US ROM build (`./conker build --assets`), Docker suite and native
objdiff report once after the group is ready. Generate the report after the build
and tests finish so its source/link-input checks see stable files. Flush a smaller pending group around
45 minutes, before stopping/handoff/commit/PR, or when a change needs an earlier
integration check. Until the final gates pass, label assets as individually
verified with batch integration pending; do not claim published matching credit.

Avoid a full project report or the complete test suite after every
asset. Rerun affected checks when inputs change or failures require it. For a
small tooling-only follow-up, use the tests appropriate to that change; also run
`./conker build --assets` if it can affect reconstruction. Keep the earlier asset
report explicitly historical if its fingerprint is now stale.
Do not rerun it merely to refresh a progress display during an ongoing batch.

## Regional and progress rules

See [progress reports](progress.md) for reading progress locally. Rendered
reports live in ignored `build/progress/`; commit inventory and evidence only.

`progress/functions.json` is the canonical instruction-match inventory.
`progress/source_units.json` separately tracks reviewed C-file boundaries and
integration state. A registered function may be matched before its containing
source unit is complete.

The generated [progress report](progress.md) counts exact US function bytes and
fully matched source-unit bytes separately. EU/PAL records remain future
metadata and do not gate active work.
