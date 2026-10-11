# m2c fork starter comparison (US), 2026-10-11

## Result and scope

Switching the pinned starter generator from upstream
[m2c](https://github.com/matt-kempster/m2c) `09e0e72` to the project's
patched mirror of it at `a03c6f2` raised the number of unedited starters that compile from 27 to
79 of 201 never-attempted GAME functions, with no starter losing compilation.
These are starter-quality measurements only; no function was matched and
compiled starters remain far from `CURRENT (0)`.

The sample is every third entry of `./conker next` on `main` at `074c18eb`:
raw-ASM functions with no `deferred` record, 780 bytes and larger. Per-function
results are in [m2c_fork_starter_comparison.json](m2c_fork_starter_comparison.json).

## Method

Each function was generated with `./conker m2c` three times: the pinned cached
tool, and `CONKER_MIPS_TO_C` pointing at fork snapshots `3b8f39a` and `a03c6f2`.
Each unedited starter was scored with one `./conker probe` batch after
prepending the `M2C_*` definitions from the fork's `m2c_macros.h`.

## Results

| Generator | Starters compiled | m2c failures |
| --- | --- | --- |
| Upstream `09e0e72` (previous pin) | 27 | 11 |
| Fork `3b8f39a` | 75 | 11 |
| Fork `a03c6f2` (new pin) | 79 | 10 |

- Fork `3b8f39a` to `a03c6f2`: 73 starters changed text; of 75 compiled by
  both, 16 scored lower and none higher; 4 more compiled. The main change emits
  typed word and function-pointer loads from byte-addressed tables instead of
  byte dereferences.
- Upstream to `a03c6f2`: 52 more compiled. Of 27 compiled by both, 9 scored
  lower, 10 higher and 8 equal (median change 0). The gain is compilability,
  mainly typed `u8 X[]` externs and explicit byte-pointer arithmetic where
  upstream emitted `M2C_UNK` operands IDO rejects.

## Remaining starter blockers (fork `a03c6f2`)

Most common first compile errors among the 122 failing starters:

- 36 undeclared stack locals (`spXX`) and 30 undeclared globals (`D_*`).
- 13 call arity mismatches with existing declarations.
- 9 unsized local arrays (`u32 spXX[]`) and 8 syntax errors.

Ten functions produce no starter. Nine are `jr` jump-table functions: seven
extract without their jump table and two read a table whose symbol lacks a
`jtbl`/`jpt_`-style name. One reports a missing branch target. The same nine
jump-table functions also fail with the previous pin.
