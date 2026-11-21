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
| R1 | Each type is declared once. A type used by one unit may stay at the top of that unit. | The same type name defined with different bodies in two files, used by the function. |
| R2 | Each global is declared `extern` once, in a header, and defined in its owning unit. | A global the unit declares `extern` itself (at file or block scope) that the function uses. |
| R4 | Access goes through typed members, not fixed offsets. | A constant added to a byte-pointer cast (`(u8 *)arg0 + 0x58`), or a pointer cast of a byte pointer plus a constant (`*(s32 *)(arg0 + 0x2C)`). |
| R17 | No fake code: nothing that exists only to steer the compiler. | `volatile` without a `// volatile: <evidence>` note on the same line (casts of literal or KSEG1 hardware addresses are exempt), empty `if`/`else` blocks, bare `;` statements, `do { } while (0)` in a body, self-assignment, `+ 0` and `* 1` (zero offsets inside casts are reported as R4, and stride indexing such as `k * 3 + 0` is exempt). |
| R18 | No assembly bodies. | `asm`, `__asm`, `__asm__` in a C body. GLOBAL_ASM functions are unmatched, not graded. |

The checks are deliberately narrow: hardware `volatile`, the stride-indexing
idiom and other genuine code pass. Where the checker flags genuine original
code, fix the checker, not the source.

## Advisory rules

These never block a match; they list open readability work.

| rule | what the checker reports |
| --- | --- |
| R7 | Placeholder names: `func_`, `D_`, `B_`, `jtbl_`, `unk`, `temp_`, `var_`, `phi_`, `field_`, `spXX`, `argN`. Keep a placeholder until evidence names the thing; never invent a confident name. |
| R25 | Prototypes outside a header: file-scope prototypes of functions defined elsewhere, and block-scope prototypes. |
| R27 | Struct members named `pad*`, which the project uses for untouched ranges. Prefer `unk_<offset>`; `--strict-padding` counts them under R17 instead. |
| R33 | A function without a header comment directly above it. |
| R35 | An `if`/`else`/loop body without braces. |
| R37 | `#if 0` outside the parking form below. |

## Project profile

| item | this project |
| --- | --- |
| Compiler and dialect | IDO 5.3 (static recompilation), `-O2 -g3 -mips2 -signed -Xcpluscomm`. C89: declarations at the top of a block, no `for`-loop declarations, `stdint.h` or `stdbool.h`. `//` comments are accepted. Plain `char` is signed under the default flags; use the `types.h` aliases (`s8`, `u8`, ...). |
| Types | `types.h` aliases and the pinned SDK's headers (`lib/ultralib`), never local copies. Shared game types live in `include/`; unit-private types may stay in their unit (see the [shared type rules](decompilation-workflow.md#shared-type-definitions)). |
| Naming | Recorded names (SDK, strings) keep their spelling. Placeholders stay until evidence names them. The original team's naming style is unknown; the current conventions are PascalCase types, lowerCamel members and locals, `UPPER_SNAKE` constants. Type names that embed an address (`Game1045D0Position`) are R7 placeholders. |
| Layout | K&R braces, four-space indent, no spaces inside parentheses. |
| Line information | The ROM carries no line information and no source uses `__LINE__`, so layout and comment changes cannot change ROM bytes. They still go through the byte gate once per batch, in their own commits. |
| Parking | Unmatched functions are `GLOBAL_ASM`. Unfinished C candidates are parked in `#if 0 /* CONKER_DEFERRED_CANDIDATE <function> CURRENT (<score>) */` blocks, which the checker skips and R37 exempts. |
| Byte gates | `./conker build` (full ROM, main and debugger) and `./conker game-build` (game overlay); `verify-batch` for function batches. |
| Rule checker | `./conker rules` |
| Globals | Globals that matched C uses are declared in `include/globals.h`, maintained by `./conker hoist-externs`. Units that define storage of their own (file-scope variables or `static` locals) do not include it, because IDO's layout of a unit's own storage can shift when the unit sees thousands more declarations; their `extern`s stay local and remain R2 work. |
| Rule changes | Padding members (`pad*`) are advisory R27 rather than R17, because they name untouched ranges, the honest form R27 allows; `--strict-padding` restores R17. R2 is not relaxed: no surviving source shows the original declared externs in units. |
| Tooling | New standalone tools are written in C where practical (as `tools/rules/rules_check.c` is); the existing Python tooling stays. |

## Running the checker

```sh
./conker rules                       # summary: both numbers and per-rule counts
./conker rules --pending             # one line per MATCH-PENDING function and its rules
./conker rules --findings src/game/game_100810.c
./conker rules --advisory --max-lines 200
```

The checker is read-only and needs no ROM. It lexes C without preprocessing,
treats every live C function definition under `src/` as bytes-matched
(unmatched code is `GLOBAL_ASM`; parked candidates are skipped), and always
reads `include/` for shared types. R1 compares only the files it reads, so run
it over all of `src/` (the default) for the full count. It builds with the
host `cc`, or inside the toolchain image when the host has none.
`--fail-on-pending` exits 1 when any function is `MATCH-PENDING`; nothing in
CI uses it yet.

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
declared with different types, or naming a unit-private type. Those need type
recovery first. Run it after matching new functions; it needs a host `cc`.

## Clearing MATCH-PENDING functions

A [match] finding is a clue to the real source, not something to hide:

- **R4:** declare or extend the struct the offsets belong to and use its
  members. This is the usual shape of a structural pass over one unit.
- **R2:** run `./conker hoist-externs --apply`. A global it leaves behind is
  declared with different types in different units (settle the one type the
  original used, which is type recovery and goes through the byte gates), or
  names a unit-private type (promote the type first).
- **R1:** promote the shared layout to one header type under the
  [shared type rules](decompilation-workflow.md#shared-type-definitions), or
  give unit-private copies distinct names.
- **R17:** find what the original wrote: a missing helper or macro (an
  open-coded GBI macro is the usual cause of `+ 0` and `* 1`), a wrong type,
  or two merged variables.

Every such change is a source change: it goes through `finish` or the byte
gates like any other C edit, and a change that breaks a match is reverted.
