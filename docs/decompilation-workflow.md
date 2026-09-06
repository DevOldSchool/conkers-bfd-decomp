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

## Match one function

Replace only the selected function's `GLOBAL_ASM` pragma, at the same source
position, then run the authoritative focused gate:

```sh
./conker finish <work-item-id>
```

`finish` compiles the candidate once. A nonzero result prints the focused US
diff and leaves the inventories unchanged. `CURRENT (0)` records the match,
regenerates progress, and checks generated output and whitespace in the same
command.

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

For the narrow subset of clean candidates whose m2c bodies need no manual
changes or generated placeholder declarations, use the conservative automation:

```sh
./conker automate-simple --limit 5 --max-attempts 20
```

It restores every failed candidate, retains only exact matches, and runs one
clean batch verification for the matches it keeps.

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
