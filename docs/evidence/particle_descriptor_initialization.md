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
