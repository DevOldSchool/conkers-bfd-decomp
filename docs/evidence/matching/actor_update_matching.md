# Actor update and related manual follow-ups (US)

## `func_15052590`, `game_7FA40.c`

The existing reviewed singleton contains a 464-byte actor update routine.
Its source-local working owner type follows the raw field offsets and widths.
The first typed C candidate matched every row except the operand order of the
final floating-point smoothing addition (`CURRENT (10)`). Expressing the
existing field update with `+=`, instead of naming a redundant copy of its old
value, produced authoritative full-span `CURRENT (0)` on the second candidate.
No compiler setting, raw assembly, shared header or source boundary changed.

The required source-unit transition moved the function to
`src/done/game/game_7FA40.c` and kept the complete US game-code image and mapped
external rodata byte-identical. The clean integration-boundary batch passed:
1,068 tests, 12 skipped, metadata, generated-progress and whitespace gates.
The result was `BATCH_COMPLETE`. This is one new verified match and one
completed source unit, not just a focused instruction result.

## Corrected motion callback candidate

The source-local `func_15143874` declaration in `game_1D5FD0.c` incorrectly
specified an integer second parameter. Its matched definition in
`game_16EE20.c` and independent raw callee both consume the saved a1 word as a
float, with no integer conversion. The raw caller `func_151A8F6C` likewise
moves its floating result directly into a1.

The old 396 candidate numerically converted that float to an integer. It was
replaced with the correct float contract and call, scoring 491. Removing the
redundant saved-argument aliases also scored 491. This numerically higher
score is retained because the prior cast was not semantically correct.
Remaining differences include a rematerialized rather than saved state pointer,
0x28 versus 0x30 frame, and floating-register allocation. It remains deferred.

## Quad interpolation candidate

For `func_1514A19C`, the old 2245 candidate unnecessarily loaded interpolation
bases before random-float calls. The independent raw code loads each base after
the call and saves no FPRs. Moving the calls first improved the candidate to
595; a typed state record gave 585. Direct random expressions and compound
smoothing updates reached 525 and restored the original 0x20 frame. A typed
owner record also scored 525. Pointer-strength reduction and load ordering
remain different. The best candidate is deferred; the earlier 250-variant
automated search was not repeated.

## Custom-ABI raw work item

`func_15018500` cannot enter the ordinary C loop. Its independent raw span
keeps the return address in s4, reads caller stack+0x44 without allocating a
frame, includes internal exported labels, and returns with `jr s4`. The normal
m2c ready step could not interpret this nonstandard return. The supported
`block-raw` transaction preserves its original source unchanged and prevents
repeated inappropriate C attempts. This is not a new match or an original-ASM
verification claim.
