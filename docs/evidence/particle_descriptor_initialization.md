# Particle descriptor initialization order (US)

The neighboring emitters `func_150B5A3C` and `func_150B5C38` each cover a
508-byte registered span in the existing reviewed `game_E2E00.c` source unit.
Both construct the same working 0x74-byte particle descriptor, copy a
three-float position by value, submit it to `func_15152B38`, and invoke the
same two additional emitter helpers. This does not establish original type
or field names, or change the reviewed source boundary.

The original functions allocate a 0x90-byte stack frame and place the record
at SP+0x1C. Its final initialized byte is at SP+0x8F. The field widths come
from the independent raw stores; the vector copy uses three integer word
loads/stores rather than separate floating-point assignments. The recovered
working structures use ordinary alignment and actual fields, without extra
stack padding or assembly bodies.

The first candidate for `func_150B5A3C` copied m2c's scheduled store order and
scored `CURRENT (875)`. Initializing the same fields in physical offset order
recovered the raw temporary-register order and instruction scheduling, giving
authoritative full-span `CURRENT (0)`. The independently inspected sibling
`func_150B5C38` then matched on its first candidate using the same source
shape and its own constants.

This is a reusable source-shape hypothesis, not a general instruction to sort
initializers. Do not move stores across calls, volatile accesses or observable
aliasing. Each target still requires its own raw-reference comparison, layout
gate and clean integrated batch verification.

Validation on 2026-09-30: both functions passed their individual full-span
`CURRENT (0)` and source-unit layout gates. The clean batch verified the
complete 2,072,880-byte US game-code image and all existing external rodata
against the owned ROM. All 1,068 tests passed (12 skipped), and metadata,
progress and whitespace checks passed. The result was `BATCH_COMPLETE`.

## Owner-position emitter

`func_151A3150` uses the same descriptor in its reviewed singleton source unit
`game_1D0600.c`. The source-local owner type reflects the original byte loads
at offsets 1 and 0xC, dimensions at 0x38/0x3C, position and optional offset
vectors at 0x40/0x4C, and flags at 0x68. It first copies the position by value,
conditionally adds the offset under flag 0x1000, then initializes the remaining
independent descriptor fields in physical order. Its first manual candidate
matched the entire 576-byte registered span with `CURRENT (0)`.

The required source-unit transition moved it to `src/game/done/game_1D0600.c`
and the integrated US game-code image remained byte-identical. No shared type,
compiler flag, assembly body, or linker mapping changed for this emitter.
Its clean singleton batch (required by the integration boundary) also returned
`BATCH_COMPLETE`: full game-code and external-rodata comparisons, 1,068 tests
(12 skipped), metadata, progress and whitespace all passed.

## Adjacent and table-driven emitters

`func_151A2F0C` (580 bytes) matched on its first candidate with the same owner
and descriptor layout, after independently checking its dimensions, count,
color and lifetime constants. Its reviewed source unit remains mixed.

`func_1515D130` (784 bytes) selects a 0x40-byte parameter record, accumulates a
randomized emission rate in its owner's state, and emits particles around a
short-vector origin. Physical-order descriptor initialization reproduced all
instructions immediately, with only an eight-byte stack-placement difference.
Moving the two used pointer declarations before the descriptor, without adding
fields or padding, produced full-span `CURRENT (0)` on the second candidate.
The source-local parameter record's stride, field widths and owner offsets
come directly from the independent assembly; no shared structure was changed.

The raw `func_15152B38` consumes its incoming a0-a2 only. Incoming a3 is not
saved before its first nested call and is assigned internally before use.
Three-argument callers therefore use a concrete three-argument source-local
declaration rather than copying an m2c unset-register placeholder. Existing
four-argument callers have not been rewritten merely to change that spelling.

### Bounded unmatched candidates

The same pass preserved typed, disabled candidates for five related emitters.
None is counted as matched, and their original assembly remains active:

- `func_150F85A0`: `CURRENT (266)`, three pre-RNG store-scheduling rows differ.
  Legacy RNG declaration did not change the result; byte-array light storage
  scored 271. The typed-record candidate was restored.
- `func_151C2F48`: best 570, after natural local ordering fixed the descriptor,
  light and coordinate offsets. Scratch offsets, one pointer-derived base and
  zero-float scheduling still differ. A used-context record probe scored 614.
- `func_15109848`: best 550. Consecutive velocity-component expressions matched
  the original prefix through offset 0x1AC; subsequent owner-load scheduling
  and register allocation differ. Byte-pointer owner access did not improve it.
- `func_151C36D8`: best 2058. Byte-argument promotion is cached in a new scratch
  slot and the frame grows by eight bytes. Inline conditional and widened-
  argument probes scored 2066 and 3502; both were discarded.
- `func_151C329C`: first candidate 2058 with the same structural mismatch as
  its independently inspected sibling. Equivalent exhausted probes were skipped.

These are source-shape hypotheses for future manual work, not evidence to relax
stack, register, layout or ROM acceptance gates.

The clean group gate on 2026-09-30 verified `func_151A2F0C` and
`func_1515D130` with `BATCH_COMPLETE`. The full US game-code image and external
rodata remained byte-identical, all 1,068 tests passed (12 skipped), and
metadata, generated progress and whitespace checks passed.
