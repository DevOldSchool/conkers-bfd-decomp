# Conker's Bad Fur Day decompilation

An independently authored decompilation project for *Conker's Bad Fur Day*.
The North American release is the active target; Europe/PAL is preserved as a
future goal and does not currently gate progress.

[![US progress](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2FDevOldSchool%2Fconkers-bfd-decomp%2Fmain%2Fprogress%2Fbadge-us.json)](docs/progress.md)
[![EU progress](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2FDevOldSchool%2Fconkers-bfd-decomp%2Fmain%2Fprogress%2Fbadge-eu.json)](docs/progress.md)

The repository contains no ROMs or extracted game assets. Please read
[LEGAL.md](LEGAL.md) before contributing.

## Quick start

Docker is the only supported host dependency. It keeps the IDO-compatible
toolchain identical on Linux, Intel macOS, and Apple Silicon.

```sh
git clone https://github.com/DevOldSchool/conkers-bfd-decomp.git
cd conkers-bfd-decomp
./conker doctor
```

The active and future ROM revisions are pinned in `config/roms.json`:

| Release | Status | SHA-1 |
| --- | --- | --- |
| North America | Active target | `4cbadd3c4e0729dec46af64ad018050eada4f47a` |
| Europe/PAL | Future target | `ee7bc6656fd1e1d9ffb3d19add759f28b88df710` |

Copy your owned US ROM into the ignored `roms/` directory using the canonical
filename. It is never committed:

```sh
cp /path/to/your-us-rom.z64 roms/baserom.us.z64
./conker setup --us roms/baserom.us.z64
```

`setup` validates the checksum and records the local setup state used by the
build tooling. The helper also accepts ROMs held elsewhere. Maintainers may
optionally record the future ROM with `--eu`, but it is not required by active
commands or progress.

Use `./conker rom-info <path>` to inspect a ROM before setup if needed.

The initial raw split map and exact raw-assembly baselines are ready.
The normal contributor workflow is:

```sh
./conker build
./conker next --ready
# Replace the selected GLOBAL_ASM pragma with the emitted C starter.
./conker finish func_XXXXXXXX
./conker progress integrate func_XXXXXXXX
```

`./conker next` reports each function's US byte size and orders available work
from smallest to largest, using the work-item symbol to break equal-size ties.
It also prints the starter command. Use `next --ready` for the agent-optimized
path: it prints only the next item plus its local inventory, issue metadata,
source context, generated assembly, and m2c C starter while prewarming the
toolchain container. `--one --details` remains available when only the bounded
read-only context is wanted. When the detail view says `issue: none recorded`,
no GitHub lookup is needed. `m2c` reads the inventory and automatically selects
main-ROM or game-overlay input, so contributors do not need to choose a
different overlay-specific command.

US is the default profile for contributor commands. Use `--profile <region>`
only when intentionally overriding it; explicit `--profile us` remains
supported for scripts and CI.

`m2c` prepares the ignored US reference output, and `diff` reuses that output.
If the reference assembly is missing, `diff` prepares it once automatically;
you do not need to run `prepare` first. `build` targets US by default;
`build --all` remains available for CI or future multi-profile verification.

`./conker diff` never runs `clean`. `clean` may remove all generated assembly,
assets, build products, and raw-reference output; the next command recreates
only the generated material it needs.

The first build-tool command starts one repository-scoped, network-disabled
toolchain container. `next --ready` deliberately starts it before editing so the
first focused diff is warm. Later `m2c`, `diff`, and build commands reuse it
instead of paying Docker's startup cost each time. Source changes are visible
immediately through the existing workspace mounts. Keep the container across
consecutive functions and follow-up work; run `./conker stop` only for explicit
cleanup or when the broader contribution is finished. A changed pinned image is
replaced automatically.
Because `mips_to_c` is pure Python, its pinned files are also copied from that
container into ignored `build/host-tools/` cache and run with the existing host
Python. This avoids amd64 emulation on repeated `m2c` calls without installing
or downloading a separate host dependency.

For a faster interactive-terminal edit loop, keep a focused diff open in one
Docker container:

```sh
./conker diff --watch <work-item-id>
```

The watcher detects main versus game-overlay work from the inventory, rebuilds
only the focused candidate on C or header changes, and preserves the previous
result as a three-way comparison. Exit it and run `finish` once so the
authoritative comparison records progress and runs the remaining per-function
gates in the same call. Noninteractive callers should edit and rerun `finish`;
`diff --watch` exits immediately with `AGENT_ACTION: USE_FINISH_LOOP` in that
environment.

## RZIP utility

The project includes a small standalone helper for inspecting or extracting a
single Rare RZIP chunk. Both paths are relative to the repository root:

```sh
./conker rareunzip input.rzip build/output.bin
```

Game-overlay extraction continues to use the project-specific multi-chunk
extractor automatically; this utility is for individual chunks and research.

## Game-code reference assembly

The US profile includes reviewed raw-assembly boundaries for the complete
decompressed game overlay. EU/PAL boundary metadata is retained for future
work, but is not part of the active workflow. These splits make the generated
assembly manageable; they do not add C sources, symbols, match evidence, or
progress entries.

```sh
./conker game-asm
```

The output is ignored under `reference/game/<profile>/asm/`. In particular,
`reference/game/us/asm/game_1A6300.s` starts at `func_15178E50` and gives us a
bounded assembly target for the next clean-room C candidate.

Generate a starter C translation for any registered work item with:

```sh
./conker m2c func_15178E50 > /tmp/func_15178E50.c
```

For game work, `m2c` first reuses the ROM-derived assembly already under
`reference/game/<profile>/asm/`. If that split is unavailable, it can safely use
a validated raw per-function block under `asm/nonmatchings/`. It rebuilds the
complete game split only when neither input is available. `game-m2c` remains a
compatibility alias.

Register an overlay candidate with `"overlay": "game"` in
`progress/functions.json`, then use the same `diff` command for the US profile. Use
`./conker first-diff` after a full-ROM build to locate the first
differing word quickly.

`diff` reuses the generated assembly under `reference/game/us/asm/` for a fast
edit/diff loop. A focused one-shot diff omits unrelated `GLOBAL_ASM` members
from its ignored temporary compile source, so a large mixed unit does not
reassemble every unmatched function. `game-diff` remains a compatibility alias.
Run `./conker game-asm` explicitly whenever you need to refresh that ROM-derived
reference.

Use `./conker finish <work-item-id>` for the ordinary one-shot agent loop. It
detects the registered overlay, compiles the candidate once, records a
`CURRENT (0)` result, then checks generated progress and whitespace in the same
command. A nonzero result displays the normal focused diff and leaves progress
unchanged. `./conker diff --record <work-item-id>` and `./conker progress match
<work-item-id>` remain compatibility paths for focused and existing automation.
Contributors should not edit the inventory JSON directly.

To populate the work queue, review the US proposals, then register an explicitly
confirmed function. Registration creates matching work only; it deliberately
does not manufacture a single-function source-unit boundary:

```sh
./conker game-index
./conker register-game \
  --id func_15178E50 \
  --us func_15178E50 \
  --source src/game/func_15178E50.c
./conker next --ready
```

`game-index` is a shortlist, not match evidence. Review the assembly before
registration. Function registration alone does not create a source file because
the original source-unit boundary is still unknown.

After independently establishing an original object/source boundary, register
the unit and its complete membership separately:

```sh
./conker register-source-unit \
  --source src/game/<unit>.c \
  --function <first-id> --function <second-id> \
  --us-start <offset> --us-end <offset> \
  --evidence-kind object_symbols \
  --evidence-reference <reviewed-file-or-note>
```

For a large reviewed range, `--register-members` derives and registers every US
work item from the generated assembly in one transaction:

```sh
./conker register-source-unit \
  --source src/game/<unit>.c \
  --register-members \
  --us-start <offset> --us-end <offset> \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/<unit>.md
```

The command requires existing reviewed map boundaries and refuses a range if
any explicitly named function is omitted. Automatic member registration prints
the recovered membership and preserves any existing match evidence while
assigning previously unassigned work to the reviewed unit. It also creates a
minimal C skeleton when the reviewed source path is absent and preserves any
existing file byte-for-byte. Unmatched members continue to come from the raw
assembly reference through ordered `GLOBAL_ASM` pragmas. Their per-function
assembly is generated locally from the owned ROM and stays ignored.

Run `progress integrate` after boundary registration to put that source unit in
the canonical build immediately. Incomplete units build as one mixed C/ASM
object through the pinned asm-processor. Replace one pragma at a time with C,
then use `finish`. Focused diff refuses a target while
its pragma is still present. Once every member matches, run `progress integrate`
again to byte-verify and move the assembly-free unit under `src/game/done/`.
`./conker progress integrate --all-reviewed` promotes multiple
reviewed incomplete units in one transactional build.

`./conker game-build` incrementally rebuilds the canonical game overlay and
verifies every mixed or completed source unit against that same decompressed
payload. It preserves the prepared split and object cache, so an ordinary source
edit rebuilds only invalidated objects. Use `./conker game-build --refresh` to
discard that cache and recreate the split before a pull request, after shared
build/configuration changes, or while diagnosing stale generated state.
`finish` runs the recording diff and generated-progress/whitespace checks as the
per-function gate; batch the Python test suite and full game build after a
logical source-file group rather than after every small function. Run the
composed gate once after the final requested function:

```sh
./conker verify-batch <work-item-id> [<work-item-id>...]
```

It validates that every listed work item is matched, resolves main versus game
build requirements, runs the clean builds and Python suite, then checks metadata,
generated progress, and whitespace.

Focused diffs remain independent of that mixed build: their generated reference
map converts every canonical `c` range back to raw assembly from the owned ROM.
This prevents a candidate from ever being compared with an object compiled from
the same source.

## RZIP and assets

`./conker rzip-extract` separates the default US game archive into executable
code, game data, padding, and the ROM's indexed asset-bank entries. The renamed
debug beta is available as `--profile debug`; `--profile ects` handles its raw
game overlay, 8,427-entry flat RZIP stream, and indexed asset banks.
Use `--manifest-only` for a fast validation/index pass or `--keep-rzip` to retain
the original compressed chunks beside decoded assets. See the
[RZIP and asset extraction guide](docs/rzip-assets.md) for the two-level index
and output layout.

`./conker beta-index` builds a cached, relocation-insensitive correlation report
for retail US, the debug beta, and the ECTS beta. It records direct and
cross-version source-path leads under `build/beta-index/report.json`; it never
updates progress or proves a function match or source-unit boundary. See the
[beta evidence guide](docs/beta-evidence.md).

## Active and future ROM profiles

Game C source currently compiles against the active `us` profile. The preserved
`eu` configuration has its own ROM checksum, symbols, link layout, assets, and
target assembly so it can be activated later without recreating the research.
When that happens, release differences should use narrow version-specific
logic rather than duplicating the source tree.

`progress/functions.json` records instruction-match evidence for each active
work item. Existing EU/PAL records remain valid future metadata.
`progress/source_units.json` separately records proposed or reviewed C-file
boundaries and their link-integration state. Reviewed evidence is mandatory
before integration. A registered function may remain unassigned while its
original source boundary is unknown. Mixed units are already part of the
canonical build; only assembly-free units under `src/game/done/` are counted as
completed source files. The generated summary reports exact matched function
bytes against the complete main and game executable ranges, so independently
verified C functions count even while neighboring functions remain inline
`GLOBAL_ASM`. It separately reports fully matched source-unit bytes, which
credit a reviewed range only after every function in that unit matches
byte-for-byte. EU/PAL bytes are reported separately but excluded from active
completion until that target is activated. See the generated [progress summary](docs/progress.md)
and [CONTRIBUTING.md](CONTRIBUTING.md).

## Library track

`lib/` is reserved for independently built Nintendo 64 library code. It is
kept separate from `src/`. Initialize the pinned dependency with
`git submodule update --init --recursive`, then build its default archive with
`./conker libultra`. It is linked into a ROM only after its object boundaries
are mapped for the active US target. See [the library track](docs/library-track.md).
