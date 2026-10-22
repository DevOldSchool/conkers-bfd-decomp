# Game shared prototypes for cast-pass leads (US)

Reviewed on 2026-10-22 on `claude/shared-game-prototypes`, based on the
warning-cleanup branch `claude/dedupe-intrinsic-pragmas` (`18064ad8`). That
pass cleared IDO `cfe` warnings with use-site casts only; four of its casts
pointed at declarations that disagree between sources. This pass follows the
[RNG shared prototype](rng_shared_prototype.md) method: one declaration in
`include/game_functions.h`, local copies removed, affected matches rechecked
with full-span US `finish`, `#if 0` callers compiled with `diagnose-diff`,
then a clean `verify-batch`. Warnings were checked by compiling each edited
source directly with the build's IDO flags (`verify-batch` does not print
compiler output).

## Fixed

### `func_15131D4C`: `void (void *, u8)`

Defined `(s32, u8)` in `game_15D730.c`, declared
`(Game981E0MenuInput *, s32)` in `game_981E0.c`. Its sibling wrapper
`func_151494E0` (matched, `game_1765E0.c`) has the same shape and forwards a
`void *` payload to `func_15169260`, so the shared entry uses `void *`. The
definition and `game_15D730.c`'s local `func_15169260` declaration take
`void *` in that slot. Its only caller, `func_150717E0`:

| Prototype | Call arguments | Score |
| --- | --- | --- |
| `(s32, u8)` | `(s32)&sp20`, then `(void *)(s32)&sp20` | CURRENT (300): address built in `a2` and copied |
| `(void *, u8)` | `&sp20` twice | CURRENT (300): address recomputed per call |
| `(void *, u8)` | `(void *)(s32)&sp20` twice | CURRENT (0) |

The target saves the integer address once and reloads it for the second call,
so the caller keeps the integer form with a comment that records the reason.

### `func_1513C73C`: shared, still `s32` first and fourth parameters

Eight identical local copies now live in the header, spelled as the matched
definition in `game_169510.c`. The `s32 *` spelling survived only in three
`#if 0` candidate calls, which now pass `(s32)&packet`. The pointer-like
parameters are forwarded unchanged to `func_1513C350` (deferred) and
`func_1513E2AC`, both declared `s32` there, so typing them as pointers is a
family retype for separate review.

## Left

- `func_15149130`: one declaration (`void *`, header) that agrees with its
  matched definition. The `(s32)`/`(u32)` casts sit in callers whose own
  return type is `s32` (for example `func_151CD2C0`), not in a prototype
  disagreement.
- `D_800D154C`: `game_981E0.c` uses it as a byte pointer (indexing, offset
  arithmetic and pointer subtraction against `D_800CC2D0`), `game_A28B0.c`
  through about 200 `GameA28B0State` member accesses, ten other files as
  `void *`. Any single type rewrites hundreds of matched expressions; the fix
  is a shared actor structure, which is type-reconstruction work.
- `func_151494E0` calls in `func_1507FF94` (`game_AC030.c`), `func_151AA17C`
  and `func_151AA210` (`game_1D6E80.c`) keep `(s32 *)(s32)&x`: a plain `&x`
  scores CURRENT (331), (300) and (300), the same integer-address effect as
  `func_150717E0`.
