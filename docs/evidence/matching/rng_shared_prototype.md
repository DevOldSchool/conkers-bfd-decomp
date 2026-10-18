# Game RNG shared prototype (US)

Reviewed on 2026-10-18 from main revision `bb098992`, on
`claude/shared-rng-prototype`. The change moves every source-local
declaration of the game RNG `func_150ADA20` into one entry in
`include/game_functions.h`. No call site, matched body, assembly, compiler
option or asset input changes.

## Callee and caller contract

The RNG at `0x150ADA20` is not matched yet (deferred candidate in
`src/game/game_DAE50.c`). Its raw code overwrites `$a0` with
`lui $a0, %hi(D_800885B0)` as its first instruction, so it reads no
argument and returns a 32-bit value in `$v0`.

On `origin/main` the 209 referencing sources held 273 local declarations in
eleven spellings: `u32 (void)` 192, `s32 (void)` 30, `u32 ()` 26 (plus one
block-scope copy in `func_151C0360`), `s32 ()` 18, `u32 (void *)` 3
(`game_12B250.c`, `game_12B7D0.c`, `game_197120.c`), and one each of
`s32 (f32 *)` (`game_16EE20.c`), `u32 (s32)` (`game_80B80.c`) and
`u32 (u32)` (`game_AC030.c`). The sources hold 1202 calls: 390 active calls
from 179 matched functions in 87 files, and 812 in `#if 0` deferred candidates.

Active calls that pass a value: 25 in 18 matched functions across 11 files
(`game_12B250`, `12B7D0`, `12CCF0`, `16EE20`, `197120`, `1ED0F0`, `1F2730`,
`2062D0`, `A28B0`, `AC030`, `E2E00`). Deferred candidates in `game_114B80.c`
and `game_80B80.c` also pass values.

Return signedness: no matched caller depends on an `s32` result. Every
matched use in an `s32`-declared source masks it, applies `% NU`, casts it to
`u32` or narrows it; none uses a signed compare, shift, division or
integer-to-float conversion.

## Rejected `u32 func_150ADA20(void);`

A first pass declared `(void)` in the header and removed the arguments from
all 27 active argument-passing calls (including the two in
`game_122650.c`, since fixed on main by PR 144). Full-span US `finish` over
the 213 affected matched functions gave 211 CURRENT (0) and two
regressions, both in `game_AC030.c`:

| Function | Call without argument | Score |
| --- | --- | --- |
| `func_1507EEF4` | `func_150ADA20()` ×2 instead of `(arg0)` | CURRENT (200): adds a `sw $a0, 0x20($sp)` home, loses a `nop` |
| `func_1507F4C0` | `func_150ADA20()` instead of `(range)` | CURRENT (273): `range` no longer in `$a0`; 13 register rows |

The changed code also shifted later game text, so `game-build` failed
with `.game_rodata_1bc650: linked rodata differs from ROM at 0x800A7B7C`
(absolute jump-table labels). With the original argument calls restored, IDO
rejects them against a `(void)` prototype ("Type u32 of this argument is
incompatible with type void of function prototype description"), and
`game_AC030.c` already includes `game_functions.h`. A cast or other per-site
construct to keep those calls compiling would be a fake match, so the `(void)`
spelling was abandoned.

## Adopted `u32 func_150ADA20();`

Some matched callers pass a value and the rest pass none. The callee ignores
it, so the shared declaration is deliberately unprototyped to fit that call
contract. The header comment records this. All 273 local copies are removed,
and 27 sources that lacked `game_functions.h` now include it directly after
`types.h`. No call arguments change.

Verification (US ROM SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`):

- `./conker game-build`: byte-verified, game code SHA-1
  `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- Full-span US `finish` over 213 matched functions: all CURRENT (0) with
  layout, progress and whitespace gates. These are the 179 callers (including
  `func_151C0360`, whose block-scope copy was removed) plus the 34 other matched
  functions in the 27 sources that newly include the header.
- `./conker verify-batch` over the same 213 IDs: `BATCH_COMPLETE`
  (matching test subset, 980 tests, OK).
- `diagnose-diff` sample of nine deferred candidates covering every former
  spelling and the newly including sources. All compile:
  `func_15055A2C` (777), `func_15143E94` (933), `func_150FE0B8` (171),
  `func_151D8F30` (425), `func_15075650` (3069), `func_150DFEFC` (110),
  `func_15102920` (2441) and the RNG's own candidate `func_150ADA20` (3600)
  keep their recorded scores. `func_150E7FEC` (`game_114B80.c`, call
  `func_150ADA20(arg4, arg5)`) did not compile at the base revision against
  that file's local `s32 (void)` copy. It now compiles and scores 1973
  (marker: 2172).

The ignored attempt logs are under `build/us/matching-attempts/`.
