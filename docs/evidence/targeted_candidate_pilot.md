# Targeted candidate tooling pilot, 2026-09-21

This tooling experiment uses saved manual candidates from the current checkout
as read-only inputs. It does not change their source or inventory, resume a
scan, register a match, or claim batch completion. The changes implement earlier
manual observations; the larger manual batch supplied concrete test cases.

## Fixed storage-shape cohort

Each candidate was compiled with the project's IDO flags and scored with the
pinned differ against a newly assembled independent raw reference over its full
registered US span. Variants are independent rewrites of the original candidate.
The probe stops at its first non-improvement, including identical emitted code.

| Function | Source | Baseline and probe scores | Compilations | Compiler/scorer seconds |
| --- | --- | --- | --- | --- |
| `func_150FCF1C` | `src/game/game_129EE0.c` | 17, 17 | 2 | 1.693 |
| `func_1515BAE0` | `src/game/game_188F90.c` | 4, 2, 0 | 3 | 2.010 |
| `func_150E8A80` | `src/game/game_115F30.c` | 17, 17 | 2 | 1.355 |

The first function's guarded aggregate suffix scope and the third function's
scalar wrapper emitted unchanged text. For `func_1515BAE0`, wrapping the first
`s8` temporary in a one-member structure scored 2; wrapping the second temporary
scored 0. The wrapper preserves scalar type, signedness, uses and lifetime.
No padding or ABI changes were introduced.

This is **one instruction-zero candidate, zero newly accepted matches**.
`finish` and a clean `verify-batch` were not run because this is a read-only
compiler pilot, so batch success and end-to-end matching cost remain unmeasured.
The table's times exclude container startup, reference assembly, orchestration
and analysis. Seven compilations took 5.058 seconds in the scoring loops.
Saved input hashes, scores and candidate variants are in the isolated worktree's
ignored `build/targeted-pilot/` directory.

Keep the stack strategy opt-in until integration validation supports wider use:

```sh
./conker permute func_1515BAE0 --stack-shapes --budget 8
```

This command is a follow-up for the checkout containing that saved candidate;
it was not run in this task. This singleton source unit requires integration
after matching, so `automate --function` deliberately excludes it. Direct
`permute` runs `finish` on an exact result. After `STOP_MATCHED`, run
`./conker progress integrate func_1515BAE0`, then `./conker progress check`,
`git -c core.whitespace=cr-at-eol diff --check`, and finally
`./conker verify-batch func_1515BAE0`; stop at any failed gate.
Ordinary register-only search budgets are unchanged.
The strategy permits at most eight generated candidates, stops on its first
non-improving compiled shape even with `--exhaustive`, and caches the outcome.
Mixed constants or control-flow changes do not qualify as stack-only evidence.

## Early switch-table gate

The gate passes on the saved integrated objects for `func_1501C730`,
`func_150A03B0`, and `func_1514EA1C`. They include a function at a nonzero object
offset and a carried HI16 with a signed negative LO16. A temporary copy of the
real `func_1501C730` object with one table addend increased by four bytes was
rejected at case 0; its complete text section was unchanged. Individual checks
took 0.050-0.078 seconds locally, including ROM validation and decompression.

The reader supports ELF32 big-endian MIPS REL objects and bounded IDO dispatches
identified by raw `jtbl_` references, including the scheduled guard/load/store
form in `func_1501C730`. It validates raw bytes against the checksum-validated
ROM, derives table size from an unsigned bounds check, and resolves candidate
HI16/LO16 and R_MIPS_32 relocations. Missing or unsupported evidence fails closed
for these identified tables. Other unrecognized indirect-dispatch conventions
are outside this initial gate's coverage.

The additional gate runs at instruction zero in diagnosis, permutation and
required focused diffs. It never substitutes for `finish`, final linker placement,
external-rodata verification or the clean batch gate.

## Regression validation

The full Python suite passed: 1,011 tests, eight skipped. Tests cover stack-only
classification, opt-in routing, width/address/member preservation, unsafe
control-flow and shadowing rejection, early plateau stopping, scheduled table
bounds, truncated objects, missing relocations, changed case targets, and blocking
instruction zero before acceptance. Whitespace checks passed.
