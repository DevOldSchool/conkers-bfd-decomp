# Code rules

A matching function proves the source is faithful to the ROM; it does not prove
the source is readable. This guide is the project's code-rule profile: what
matched C must look like before it counts as matched under the rules, and how
`./conker rules` checks it.

## Two laws

1. **The bytes win.** A change made for readability must not change the
   compiled output. When a style rule and the bytes disagree, keep the bytes and
   write `// RULE-EXCEPTION: <rule>, <reason the bytes give>` at the code.
2. **Identical bytes alone are not a match.** A function counts as matched
   under the rules only when its bytes match *and* it passes every [match] rule
   below. A byte-identical function that fails one is `MATCH-PENDING`: keep its
   source, because it is the best-known state, and treat it as open work.

Progress therefore has two numbers: **bytes matched** (what
`progress/functions.json` and objdiff already report) and **matched under the
rules** (the subset that `./conker rules` passes).

## [match] rules

| rule | requirement | what the checker flags |
| --- | --- | --- |
| R1 | One type name, one definition: the same type name must not have conflicting definitions. A type used by one unit may stay at the top of that unit. | The same type name defined with different bodies in two files, used by the function. Identical copies are not flagged; they are left to the R1 cleanup pass. |
| R2 | Each global is declared `extern` once, in a header, and defined in its owning unit. New `extern`s follow the R2 ruling under Rule changes. | A global the unit declares `extern` at file scope that the function uses, or a block-scope `extern` in the function itself. |
| R4 | Access goes through typed members, not fixed offsets. | A constant added to a byte-pointer cast (`(u8 *)arg0 + 0x58`, `(u8 *)&D_x + 4`), a byte-pointer cast indexed by a constant (`((u8 *)arg0)[0x58]`), or a pointer cast of a byte pointer plus a constant (`*(s32 *)(arg0 + 0x2C)`). A byte view of a plain scalar inside its own size is exempt (`((u8 *)&word)[3]` for a 32-bit `word`); pointers, arrays and offsets past the scalar's size are not. |
| R17 | No fake code: nothing that exists only to steer the compiler. | `volatile` on parameters, locals, casts or members without a `// volatile: <evidence>` note on the same line (only a `volatile` inside a cast of a literal or KSEG1 hardware address is exempt; a volatile member counts where it is accessed through the struct that declares it, or by member name where the access's base type cannot be resolved, as in `(*pp)->m` or `a->b->m`), empty `if`/`else` blocks, bare `;` statements, `do { } while (0)` in a body, self-assignment, `+ 0` and `* 1` (zero offsets inside casts are reported as R4, and stride indexing such as `k * 3 + 0` is exempt). |
| R18 | No assembly bodies. | `asm`, `__asm`, `__asm__` in a C body. GLOBAL_ASM functions are unmatched, not graded. |

The checks are deliberately narrow: hardware `volatile`, the stride-indexing
idiom and other genuine code pass. Where the checker flags genuine original
code, fix the checker, not the source.

## Advisory rules

These never block a match; they list open readability work.

| rule | what the checker reports |
| --- | --- |
| R7 | Placeholder names, as the [naming ruling](#naming) defines them: `func_`, `D_`, `B_`, `jtbl_` and the m2c names `temp_`, `var_`, `phi_`, `spXX`, `argN`, plus legacy `unkXX` members. `unk_<HEX>` is the ruling's name for an unknown member, not a placeholder. Keep a placeholder until evidence names the thing; never invent a confident name. |
| R25 | Prototypes outside a header: file-scope prototypes of functions defined elsewhere, and block-scope prototypes. |
| R27 | Struct members named `pad*`, which the project uses for untouched ranges. Name them `unk_<HEX>` (uppercase hex, no `0x`) when touched; `--strict-padding` counts them under R17 instead. |
| R33 | A function without a header comment directly above it. |
| R35 | An `if`/`else`/loop body without braces. |
| R37 | `#if 0` outside the parking form below. |

## Project profile

| item | this project |
| --- | --- |
| Compiler and dialect | IDO 5.3 (static recompilation), `-O2 -g3 -mips2 -signed -Xcpluscomm`. C89: declarations at the top of a block, no `for`-loop declarations, `stdint.h` or `stdbool.h`. `//` comments are accepted. Plain `char` is signed under the default flags; use the `types.h` aliases (`s8`, `u8`, ...). |
| Types | `types.h` aliases and the pinned SDK's headers (`lib/ultralib`), never local copies. Shared game types live in `include/`; unit-private types may stay in their unit (see the [shared type rules](decompilation-workflow.md#shared-type-definitions)). |
| Naming | The maintainers' ruling in [Naming](#naming) below: project conventions, advisory, recorded names first. |
| Layout | K&R braces, four-space indent, no spaces inside parentheses. |
| Line information | The ROM bytes never change. The ROM carries no line information and no source uses `__LINE__`, so comments, indentation and blank lines cannot affect them. Which statements share a source line can affect what the compiler emits: the build is `-g3`, where a line boundary limits instruction scheduling, and `func_1501EA18`, `func_150DAE70` and `func_15196748` only reproduce the ROM with certain statements on one line (see [IDO source idioms](decompilation-workflow.md#ido-source-idioms)). A layout change that fails the byte gate is reverted, and the lines it would have split carry a `// RULE-EXCEPTION: layout` note. Layout and comment changes go through the byte gate once per batch, in their own commits. |
| Parking | Unmatched functions are `GLOBAL_ASM`. Unfinished C candidates are parked in `#if 0 /* CONKER_DEFERRED_CANDIDATE <function> CURRENT (<score>) */` blocks, which the checker skips and R37 exempts. |
| Byte gates | `./conker build` (full ROM, main and debugger) and `./conker game-build` (game overlay); `verify-batch` for function batches. |
| Rule checker | `./conker rules` |
| Globals | Globals that matched C uses are declared in `include/globals.h`, maintained by `./conker hoist-externs`. Units that define storage of their own (file-scope variables or `static` locals) do not include it, because IDO's layout of a unit's own storage can shift when the unit sees thousands more declarations; their `extern`s stay local and remain R2 work. |
| Rule changes | Padding members (`pad*`) are advisory R27 rather than R17, because they name untouched ranges, the honest form R27 allows; `--strict-padding` restores R17. R2 is not relaxed: no surviving source shows the original declared externs in units. **R2 ruling for new `extern`s:** when the global's owning module is clear, adding its `extern` to that module's header is a pre-approved shared change, as long as the edit only adds the declaration; it still goes through `finish` / the byte gates as usual. Until modules have their own headers, that header is `include/globals.h`. Otherwise a unit-local `extern` is allowed and recorded as R2 debt for the R2 cleanup pass, which `./conker hoist-externs` runs. |
| Tooling | New standalone tools are written in C where practical (as `tools/rules/rules_check.c` is); the existing Python tooling stays. |

## Naming

This is the maintainers' ruling. It sets project conventions, not claims
about the original source. It is **advisory**: a naming rule never makes a
function `MATCH-PENDING`.

**Recorded names come first.** A name recorded in the SDK headers or a ROM
string keeps its exact spelling, even when it breaks the table below
(`osSendMesg`, `OSThread`). Cite the evidence in the declaration's comment.

**Placeholders stay until evidence names them.** These are `func_`, `D_`,
`B_`, `jtbl_` and m2c names (`temp_`, `var_`, `phi_`, `spXX`, `argN`). Never invent a
confident name (R7).

| Kind | Convention | Example |
| --- | --- | --- |
| Functions | `snake_case` with a module prefix | `player_update`, `camera_set_target` |
| Types (struct/union/enum/typedef) | `PascalCase`. In new or touched types, the struct tag and its typedef share the name. Existing anonymous typedefs are not retagged just for this. | `typedef struct PlayerState { ... } PlayerState;` |
| Struct members, locals, parameters | `lowerCamel` | `animFrame`, `targetPos` |
| Globals | `g` + module word + `PascalCase`. Never `gSP`, `gDP` or `gs`, which are GBI macro namespaces. | `gCameraTarget`, `gPlayerState` |
| File-local statics | `s` + module word + `PascalCase`. Adding `static` changes symbol binding, so it still goes through the byte gates. | `sBloodSpawnTable` |
| Macros, `#define` constants | `UPPER_SNAKE` | `MAX_ACTORS` |
| Enum constants | `UPPER_SNAKE`, prefixed with the enum's name | `ANIM_STATE_IDLE` |
| Unknown struct members | `unk_` + uppercase hex offset, no `0x`; arrays for unknown ranges. Existing `unkXX` and `pad*` names are legacy, normalised when touched. | `unk_7C`, `unk_70[0x10]` |

Renaming happens in its own commits and passes the byte gates once per batch.
A rename alone never counts as a match.

## Running the checker

```sh
./conker rules                       # summary: both numbers and per-rule counts
./conker rules --pending             # one line per MATCH-PENDING function and its rules
./conker rules --findings src/game/game_100810.c
./conker rules --advisory --max-lines 200
```

The checker is read-only and needs no ROM. It lexes C without expanding
macros and treats every live C function definition under `src/` as
bytes-matched. Unmatched code is `GLOBAL_ASM`, and parked candidates are
skipped. It reads one branch of every conditional chain. `#if 0`/`1`,
`#ifdef`, `#ifndef` and `defined` are evaluated against the US build's `-D`
flags (the Makefile's `CFLAGS` and `PROFILE_CFLAGS_us`, mirrored in the
checker), the file's own `#define`s and `#undef`s, and the macros of the
`include/` headers it includes, followed transitively. SDK headers under
`lib/ultralib` are not read, so their macros count as undefined. Any other
condition counts as true, so its `#else` is skipped. It always reads `include/` for shared types. R1 compares
only the files it reads, so run it over all of `src/` (the default) for the
full count. It builds with the host `cc`, or inside the toolchain image when
the host has none. `--fail-on-pending` exits 1 when any function is
`MATCH-PENDING`; nothing in CI uses it yet.

## Hoisting extern globals (R2)

```sh
./conker hoist-externs               # report what would move and why the rest stays
./conker hoist-externs --apply       # move it, then run the byte gates
```

The tool moves a global into `include/globals.h` when every unit declares it
alike (an unbounded array agrees with one bounded form, which the header
takes), every type it names is visible to the header (`types.h`,
`game_vec.h`), and no macro, function or other header uses the name. It
removes the moved declarations from their units and adds
`#include "globals.h"`. A global that stays is reported with its reason:
declared with different types, or naming a unit-private type. Run it after
matching new functions; it needs a host `cc`.

A global declared with different types can often take one declaration
without changing any code:

```sh
./conker unify-externs               # try candidates; report what unifies
./conker unify-externs --apply       # write them, re-check every retyped unit
./conker hoist-externs --apply       # then move them, and run the byte gates
```

For each such global the tool proposes a variant the header can name that
keeps every declaration's information. Named types outrank sized scalars,
which outrank byte and `void` placeholders, so `struct OSThread_s` is never
rewritten to `u8`. Among equals it prefers the variant most units use. It
rewrites the other units, compiles each of them in the toolchain container
and keeps the global only when every retyped unit's code (with relocations),
data, rodata and section sizes are identical. Globals that share a retyped
unit are retried apart, and failures try the next candidate. Only a compiler
diagnostic or a changed object counts against a candidate. If the container
cannot read a source (Docker Desktop bind mounts can briefly fail after a
file is replaced), the compile is retried, and a persistent failure stops the
run without deciding anything, so the result does not depend on the host.
Sources are restored by rewriting them in place, and each compile first waits
until the container sees the host's exact file contents. A prior
`./conker game-build` supplies the GLOBAL_ASM inputs that game units need.
What remains has no information-preserving candidate (a unit uses a private
named type) or changes code under every candidate. It needs a reader's
judgement about which type the original used.

## Clearing MATCH-PENDING functions

A [match] finding is a clue to the real source, not something to hide:

- **R4:** declare or extend the struct the offsets belong to and use its
  members. This is the usual shape of a structural pass over one unit.
- **R2:** run `./conker unify-externs --apply`, then
  `./conker hoist-externs --apply`. A global left behind either changes code
  under every candidate type (settle the type the original used, which is type
  recovery through the byte gates) or names a unit-private type (promote the
  type first). New `extern`s follow the R2 ruling under Rule changes.
- **R1:** promote the shared layout to one header type under the
  [shared type rules](decompilation-workflow.md#shared-type-definitions), or
  give unit-private copies distinct names.
- **R17:** find what the original wrote: a missing helper or macro (an
  open-coded GBI macro is the usual cause of `+ 0` and `* 1`), a wrong type,
  or two merged variables.

Every such change is a source change: it goes through `finish` or the byte
gates like any other C edit, and a change that breaks a match is reverted.
