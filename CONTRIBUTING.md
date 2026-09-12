# Contributing

Thank you for helping with the decompilation. Human and AI-assisted
contributions use the same workflow and review standard.

This document defines contribution policy and acceptance gates. See the
[decompilation workflow](docs/decompilation-workflow.md) for the detailed
command behavior, focused iteration loop, registration flow, and Docker cache
lifecycle.

## First-time setup

1. Install and start Docker.
2. Run `./conker doctor`.
3. Obtain the supported US ROM yourself, copy it to the ignored `roms/`
   directory, then run setup. It validates the reviewed SHA-1 already pinned
   in `config/roms.json`:

   ```sh
   cp /path/to/your-us-rom.z64 roms/baserom.us.z64
   ./conker setup --us roms/baserom.us.z64
   ```

   The canonical ROM filenames are used by every build command and are ignored
   by Git.

4. Follow [the bootstrap guide](docs/bootstrap.md) until the raw baselines are
   available. Then use `./conker next --ready` to select the smallest available
   function, print its bounded local context and starter, and prewarm Docker.

Maintainers add game-overlay work with `./conker game-index` followed by
`./conker register-game`. Main-executable functions use `./conker register-main`.
Review the US assembly body before registering either kind of work.
Function registration updates the function inventory and generated progress;
it does not claim that one function equals one original C source file.

Register a source unit separately only after reviewing real object-boundary
evidence. The range must already exist in the active map. Either name every
already-registered function explicitly:

```sh
./conker register-source-unit \
  --overlay game \
  --source src/game/<unit>.c \
  --function <first-id> --function <second-id> \
  --us-start <offset> --us-end <offset> \
  --evidence-kind object_symbols \
  --evidence-reference <reviewed-file-or-note>
```

or deliberately register the complete recovered membership from that reviewed
range:

```sh
./conker register-source-unit \
  --overlay game \
  --source src/game/<unit>.c \
  --register-members \
  --us-start <offset> --us-end <offset> \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/<unit>.md
```

`--overlay game` is the default for compatibility; use `--overlay main` with
main-executable sources registered through `register-main`. Accepted evidence
kinds are `linker_map`, `object_symbols`, and
`structural_analysis`. Sixteen-byte alignment or a successful standalone build
does not by itself prove an original source-file boundary. Successful source-unit
registration creates a minimal C skeleton if the path does not exist and never
overwrites existing work. The skeleton contains one ordered `GLOBAL_ASM` pragma
per unmatched member. Its assembly is generated locally from the owned ROM and
remains ignored. After registration, run `./conker progress integrate --profile
us <symbol>` to map the reviewed unit into the real build as one mixed C/ASM
object. The transaction is retained only when the complete build remains
byte-identical.

If later evidence invalidates a game boundary, use
`./conker withdraw-source-unit --source src/game/<unit>.c`. This restores the
range to raw ASM and retains the function work items; it rejects modified
skeletons and any active or matched C work.

Keep the reviewed source-unit comment at the top of every assigned C file,
immediately below its contiguous `#include` block and before declarations or
definitions. Project validation rejects reviewed headers that drift lower in a
file.

## Function workflow

If the selected inventory record includes issue metadata, claim and read that
GitHub issue before editing. If `next --ready` reports `issue: none
recorded`, no remote issue lookup is required. Work in a branch or separate Git
worktree, and keep a pull request focused on one C source file unless a
maintainer approves a shared dependency change.

```sh
./conker next --ready
# Replace that function's GLOBAL_ASM pragma with C at the same position.
./conker finish <work-item-id>
# After the final function in a requested group:
./conker verify-batch <work-item-id> [<work-item-id>...]
# For repeated local iteration only (still run the clean form before handoff):
./conker verify-batch --incremental <work-item-id> [<work-item-id>...]
# For a raw reviewed unit, integrate once to enter mixed mode.
# For a mixed unit, integrate only after its final function is matched.
./conker progress integrate <work-item-id>  # when one condition above applies
# If integration ran, repeat these because it changed repository state:
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

Treat the `allowed-edit`, `target-file-dirty`, `source-unit-state`, and
`post-match-action` fields from `next --ready` as authoritative. A function is
matched only when its US focused diff reports `CURRENT (0)`. Use `finish` so the
same compilation records the match and performs the per-function generated and
whitespace checks. Do not edit progress JSON or generated nonmatching assembly
by hand.

The automation entry point processes both raw m2c starters and preserved
deferred candidates. Existing changes in a source file are preserved; each
attempt replaces only its canonical pragma and restores the complete
pre-attempt file when it cannot safely retain a result:

```sh
./conker automate --limit 5 --max-attempts 20 --rewrite-budget 250
```

Use `--function <work-item-id>` instead of `--limit` to exercise one eligible
raw or deferred candidate without waiting for scheduler order. For example:

```sh
./conker automate --function func_15012C84 --rewrite-budget 25 \
  --defer-best --skip-final-build
```

It resolves placeholder declarations only from unique compatible active
declarations or definitions under `src/` and `include/`, sanitizes scalar and
pointer fields with expression bases or signed offsets, makes integer-backed
address assignments explicit for IDO, searches bounded semantics-preserving
source forms, and diagnoses deferred candidates before permuting pure
register-only differences. A raw compile warning or error gets up to three
diagnostic-guided, target-function-only repairs for proven mechanical cases
such as undefined `NULL` and byte-address pointer arithmetic. An already
deferred `CURRENT (0)` candidate goes directly through the authoritative
permutation/`finish` recovery path instead of being rejected as non-register-only.
If that focused match is shorter than its reviewed raw span, automation
preserves it as a `finish`/`layout_gate` result with the exact offset delta.
This commonly identifies intentionally retained unlabeled return or padding
words that cannot be credited as ordinary C without stronger boundary evidence.
Raw and deferred candidates are interleaved. Exact matches pass through
an initial warning-free `diff` preflight and then `finish`; the retained group
receives one final clean `verify-batch`. Compiler failures and warnings retain
the complete proposed source, log, and structured diagnostics under
`build/us/automate/artifacts/<work-item-id>/` while restoring project source.

Before generating a starter, m2c imports unique, self-contained active project
prototypes for direct callees. For a straight-line wrapper with one direct call
and a discarded result, it can also recover forwarded integer-register
arguments from a validated raw callee's contiguous o32 argument-home stores.
Pointer use in the callee entry block supplies pointer arguments; other word
arguments remain `s32`. It regenerates m2c with this context and emits the
required declarations with the starter. Evidence is retained under
`build/m2c/calls/<symbol>.json`.

Raw call-site declarations carry `CONKER_ABI_DISCARDED_RETURN`: they describe
only calls that discard the result and are excluded from general return-type
evidence. Conflicting declarations, unsupported types, stack arguments,
variadic register-save areas, and unsupported wrapper control flow remain
blocked. Prototype and raw-callee changes invalidate affected resume
fingerprints automatically. This recovery is enabled by default in `m2c`,
`next --ready`, and `automate`; the normal focused, layout, and batch gates
still apply.

Do not discard a useful nonzero candidate merely to keep a mixed unit
byte-identical. With explicit agreement to move past it, add `--defer-best` or
use the supported deferral flow:

```sh
./conker defer <work-item-id> --reason "<remaining mismatch>"
./conker next --ready
# Later:
./conker resume <work-item-id>
```

`defer` and `resume` preserve the candidate and update the inventory
transactionally. Do not reproduce their changes manually.

Use `./conker diagnose-diff <work-item-id>` to classify a live or preserved
candidate before spending manual attempts. When the remaining differences are
primarily compiler register allocation, `./conker permute <work-item-id>
--budget <variants>` performs a deterministic, bounded search over
semantics-preserving declaration order and first-assignment lifetime variants.
It writes the best nonzero result below `build/<profile>/permute/` without
changing project source. It restores and finishes the candidate automatically
only after finding `CURRENT (0)`. Applying an exact permutation and running
`finish` is transactional: if the layout gate fails before a match is recorded,
both source and deferred inventory metadata are rolled back together. When
unified automation finds a strictly
better nonzero permutation for an already deferred function, it replaces the
canonical disabled candidate and its recorded score transactionally; an equal
or worse result leaves the existing block untouched.
If a permutation subprocess is externally killed (exit 137/SIGKILL), unified
automation restores or preserves the candidate, records the outcome in its
coverage report, and continues with the next function instead of aborting the
complete scan. Any best score completed before the kill is written
incrementally and may be deferred when `--defer-best` is active. If the kill
occurs before the first permutation completes, the already measured initial C
candidate is deferred instead.

For quick local experiments, `--skip-final-build` omits only that concluding
clean build and prints the exact `verify-batch` command that remains required
before committing or handing off the changes. It does not bypass any
per-function `finish` gate.

To consider the complete active US inventory, run:

```sh
./conker automate --all --defer-best
```

This removes the match and attempt limits but retains all safety exclusions.
It atomically updates `build/us/automate/all-report.json` after every candidate.
To avoid terminal backpressure during a full scan, detailed subprocess output
is written to `build/us/automate/logs/<work-item-id>.log`; stdout is limited to
important events and one progress summary every 50 candidates. Each attempted
report entry records its `command_log` when one exists. Add `--verbose` only
when the complete live command stream is useful.
The report includes already matched functions and explicit exclusion reasons,
so a completed run proves every inventory entry was considered even when some
functions still require manual work. An interrupted run has `scan_complete:
false`; rerunning is safe because exact matches and deferred candidates are
selected from their current inventory states and completed attempts are resumed
from the report. Before resuming or running the final batch gate, automation
reconciles its pending match list with the authoritative inventory. A function
reopened or deferred by a later mixed-source integration is dropped from that
batch instead of being passed to `verify-batch`. Add `--restart` to deliberately
reconsider prior outcomes after changing the automation. Do not combine `--all`
with `--max-attempts`.

Each attempted result records its pipeline stage, blocker code, applied repair
actions, and a fingerprint of the target source and canonical raw assembly plus
only that stage's relevant tools and options. A later full run resumes an
outcome only while that stage fingerprint still matches; changing declaration,
compile-repair, or permutation tooling selectively requeues its own frontier.
Legacy entries without stage metadata are safely retried once.

Use `./conker automate --all --analyze` for a non-mutating preparation pass. It
generates and sanitizes raw starters, checks that each candidate can replace
exactly one canonical pragma, classifies deferred candidates, and writes
`build/us/automate/analysis-report.json`. It may update ignored m2c caches and
the report, but does not edit tracked source/inventory, compile candidates,
permute, defer, finish, or run the batch gate. Analysis results use the same
fingerprints and resume unchanged work; add `--restart` to recompute all of
them.

`finish` also compiles the complete reviewed mixed source object and verifies
every member offset plus the aligned object extent before recording a match.
This catches missing post-return instructions or padding that a focused
`--stop-at-ret` comparison cannot see. If older zero-difference evidence is
invalidated by this layout gate, use `./conker reopen-match <work-item-id>
--reason <text>` to preserve its C body, restore `GLOBAL_ASM`, and update
inventory/progress atomically.

Batch the full build and Python checks after a logical group rather than after
every small function. Run the default clean `verify-batch` before committing,
handing off, or opening a pull request. If an integrated binary mismatch records
an input fingerprint, change the source or layout before retrying the same clean
batch.

Use `diff --watch` only in an interactive terminal and always exit it before the
final `finish`. Keep the repository-scoped container between consecutive
functions; use `./conker stop` only for explicit cleanup or when the broader
work is finished.

`progress integrate` is reserved for the two source-unit transitions shown in
the command block: entering the canonical mixed build, then completing an
assembly-free unit after every member matches. Full command semantics and the
compatibility paths are documented in the
[decompilation workflow](docs/decompilation-workflow.md).

For a complete Rare library reconstruction, first verify the whole object's
text, relocations, data/rodata and BSS ownership, then link its archive mapping
and pass the full US image comparison. After that gate, retire its old work
items with `./conker retire-library-units --evidence-reference <path> --source
<src/libultrare/path.c> --preserved-source <lib/libultrare/src/libultrare/path.c>`.
This mode requires every active function to be matched, an exact archive text
range and an independent raw reference, and a byte-identical C copy at the
corresponding library path. It keeps that library copy and removes the duplicate
source and inventory entries. The command does not run the full-image gate for
you. Without `--preserved-source`, retirement still only accepts untouched raw
skeletons; it cannot discard modified source work.

The focused diff's target object always comes from a separately generated raw
assembly map. The reference generator converts canonical `c` ranges back to
`asm`; do not point comparison tooling at the mixed build object.

EU/PAL is a future target. Its existing profile maps and inventory metadata are
preserved, but contributors do not need its ROM or diff evidence and it does
not count toward the current progress percentage.

Do not alter target assembly, hand-write `GLOBAL_ASM` bodies, use inline assembly
to force a match, or mark a function matched based only on a compilation result
or a register-insensitive comparison.

## Beta evidence

Owned debug and ECTS beta ROMs are non-gating research inputs. Run
`./conker beta-index` to generate cached cross-version function correlations and
retained source-path leads. A `strong` beta correlation is still not US match
evidence, and a retained source filename is not an object boundary. Before
registering a source unit, independently review its exact US start/end against
the active split map and record that evidence under `docs/evidence/`.

## AI-assisted work

AI assistance is welcome. Its changes must be reviewable, limited in scope,
and reproducible with the commands above. Agents should first report a
read-only analysis, then edit only an isolated worktree. Treat an agent's
result as a patch proposal until a maintainer independently verifies the US
diff.
