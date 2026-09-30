# Collision-position helper matching (US)

The reviewed `game_E7DE0.c` group pairs `func_150BA930` with its direct caller
`func_150BAA14`. This pass preserves the existing source-unit boundary.

## Position helper

The 208-byte `func_150BA930` had an otherwise exact candidate at `CURRENT (30)`:
the load of the global height threshold and the load of the owner's height
were reversed. Earlier separate-threshold-local and direct-field comparison
attempts had scored 201 and 111 and were not repeated.

Assigning the existing `value` local within the comparison's right-hand operand
preserves the value for the selected output while evaluating the threshold on
the left. This natural expression shape recovered the original two-load order
and produced authoritative full-span `CURRENT (0)` on the first new expression
revision. The source-unit symbol layout, progress and whitespace gates passed.
No extra loads, volatile qualifiers, padding or assembly were introduced.

The fourth helper argument is homed as a full word and never read by the raw
callee. Keeping that unused word as `s32` also lets the caller perform its
original byte-to-word argument conversion. The helper's code remained at 30
with that declaration change alone, before the expression correction.

## Direct caller candidate

`func_150BAA14` remains unmatched at best 298, improved from 658. Its local
collision-hit record has the 0x24-byte layout written by `func_1504715C`, and
its position is a real three-float array. The recovered third float parameter
of `func_1514C678` is moved directly from a2 into an FPR by the raw callee;
there is no integer conversion or m2c bitwise placeholder in the candidate.

The original call to `func_151D5404` supplies eight words, although its matched
callee consumes only the first six arguments. The source-local call-site
declaration preserves those evidenced outgoing arguments without changing the
callee or other callers. Global player addressing preserves the original
32-bit address calculation and the observed 0x9A0 stride.

The remaining mismatch comprises owner-load scheduling, six GPR rows and two
random-value spill-offset rows. An opaque owner pointer and a suffix-scoped
random local did not improve it. The best candidate is disabled, with original
assembly active. The source unit remains mixed.

The clean group gate on 2026-09-30 returned `BATCH_COMPLETE` for
`func_150BA930`. The full US game-code image and external rodata matched the
owned ROM, all 1,068 tests passed (12 skipped), and metadata, generated-progress
and whitespace checks passed.
