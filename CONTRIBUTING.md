# Contributing

Thank you for helping with the decompilation. Human and AI-assisted
contributions use the same workflow and review standard.

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
   available. Then use `./conker next` to find available function work.

Maintainers add game-overlay work with `./conker game-index` followed by
`./conker register-game`. Review the US assembly body before registering it.
Function registration updates the function inventory and generated progress;
it does not claim that one function equals one original C source file.

Register a source unit separately only after reviewing real object-boundary
evidence. The range must already exist in the active map. Either name every
already-registered function explicitly:

```sh
./conker register-source-unit \
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
  --source src/game/<unit>.c \
  --register-members \
  --us-start <offset> --us-end <offset> \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/<unit>.md
```

Accepted evidence kinds are `linker_map`, `object_symbols`, and
`structural_analysis`. Sixteen-byte alignment or a successful standalone build
does not by itself prove an original source-file boundary. Successful source-unit
registration creates a minimal C skeleton if the path does not exist and never
overwrites existing work. The skeleton contains one ordered `GLOBAL_ASM` pragma
per unmatched member. Its assembly is generated locally from the owned ROM and
remains ignored. After registration, run `./conker progress integrate --profile
us <symbol>` to map the reviewed unit into the real build as one mixed C/ASM
object. The transaction is retained only when the complete build remains
byte-identical.

## Function workflow

Claim the related GitHub issue before editing a function. Work in a branch or
separate Git worktree, and keep a pull request focused on one C source file
unless a maintainer approves a shared dependency change.

```sh
./conker m2c <work-item-id> > /tmp/<work-item-id>.c
# Replace that function's GLOBAL_ASM pragma with C at the same position.
./conker diff <work-item-id>
./conker progress match <work-item-id>
# For a raw reviewed unit, integrate once to enter mixed mode.
# For a mixed unit, integrate only after its final function is matched.
./conker progress integrate <work-item-id>  # when one condition above applies
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

During the edit loop, `./conker diff --watch <work-item-id>` keeps
one Docker container and asm-differ process open, detects the registered overlay,
and rebuilds the candidate whenever its C source or project headers change. Exit
the watcher before running `progress match` for final machine-readable evidence.
Ordinary build-tool commands also reuse a repository-scoped warm container;
`./conker stop` removes it when the session is finished.

A function is matched for the active target only when its US focused diff
reports `CURRENT (0)`. Run `./conker progress match <work-item-id>` to
verify that result again, update the function inventory and any assigned source
unit, and regenerate the progress files. Focused diff refuses to credit a
function while its own `GLOBAL_ASM` pragma remains. If no reviewed source unit
is assigned, only the function inventory changes. Do not edit the inventory JSON
by hand.

`progress integrate` has two safe phases. For a reviewed incomplete unit it
maps the source as C, lets asm-processor inject the remaining generated assembly,
and verifies the complete raw ROM or game overlay. For an already mixed unit
whose every function is matched, it verifies again and moves the source to
`src/game/done/`. Source-unit ranges must start and end on reviewed 16-byte IDO
object boundaries. Do not edit generated nonmatching assembly, move completed
files, or edit progress JSON by hand.

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
