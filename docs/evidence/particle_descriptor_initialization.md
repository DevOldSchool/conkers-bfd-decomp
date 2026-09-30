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
