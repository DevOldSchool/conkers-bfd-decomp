# Clean-room bootstrap

The project intentionally begins without imported C sources, symbols, or
extracted assets. The bootstrap goal is a raw-assembly rebuild of the active US
ROM before any C function is promoted.

## Established baseline

1. The reviewed US ROM SHA-1 is pinned as the active target in `config/roms.json`.
   The EU/PAL SHA-1 and maps are retained for the future regional target.
2. The profile maps were independently derived from the owned ROMs. Their generated
   assembly and asset output remains ignored.
3. `./conker build --all` rebuilds all active profiles (currently US) from
   untouched generated assembly and verifies the byte-for-byte ROM baseline.
4. `./conker m2c` and `./conker diff` provide the first shared C candidate
   workflow. `m2c` prepares the raw reference profile, while `diff` reuses an
   existing reference and prepares it automatically only when it is missing.

`./conker m2c <work-item-id>` produces a C starting point. It does not claim
that the output is type-correct or matched. `./conker diff <work-item-id>`
compiles the registered C candidate with the pinned IDO
compiler and compares it with the generated reference object.

Once the focused diff reports `CURRENT (0)`, use `./conker progress match
<work-item-id>`. The command verifies the match, updates the canonical
function inventory and any separately assigned source unit, and refreshes
generated progress. Do not edit those JSON inventories manually.

Function registration does not imply a C-file boundary. Use `./conker
register-source-unit` only after recording reviewed linker-map, object-symbol,
or structural-analysis evidence and registering every function in that range.
The command creates the reviewed unit's C skeleton without replacing an existing
file. It adds ordered `GLOBAL_ASM` pragmas for unmatched functions and generates
their assembly locally from the owned ROM. Run `./conker progress integrate
<work-item-id>` to put the reviewed unit into the canonical build as one
mixed C/ASM object, retained only after byte-identical verification.

Replace each function's pragma with C at the same source position. Focused diff
refuses to test a target still backed by its pragma. When every function in the
mixed unit is matched, run `progress integrate` again. It moves the source under
`src/game/done/`, updates the active map and inventories, and retains those
changes only if the complete ROM or game overlay remains byte-identical.

Use `./conker diff --watch <work-item-id>` while iterating. It keeps
the pinned Docker environment and asm-differ process alive, automatically
chooses the registered overlay, and recompiles after source or header changes.

Do not copy C sources, function names, comments, symbols, or generated files
from another decompilation repository. Reviewed raw-assembly boundary maps are
the sole exception: each imported offset must be confirmed against the owned
regional ROM reference and must never be used as match evidence. External tool
dependencies may be used only under their own licenses and must be pinned.

## Regional targets

Compile and verify the C source under `PROFILE=us`. A function is matched after
the US diff reports `CURRENT (0)`. This records a matched function; a source
unit is complete only after it is also integrated into the US full-ROM link and
moved under `src/game/done/`.

EU/PAL remains a future goal. Its checksum, split maps, and existing inventory
records are preserved, but no EU/PAL ROM, build, or diff is required for active
work. When that target is activated, regional differences belong in narrowly
scoped build macros or data/configuration rather than a forked source tree.
