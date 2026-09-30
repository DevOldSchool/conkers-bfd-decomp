# Bounded sprite, motion and angle candidates (US)

These candidates remain deferred, with original assembly active. They do not
add matched bytes or complete source units. No compiler setting, shared header,
assembly body, artificial padding, volatile access or automated search changed.

- `func_150B7220`, `game_E4070.c`: reused the existing sprite descriptor and
  named the three real packed-coordinate words formerly covered by its padding.
  The typed candidate scored 4266; signed word types also scored 4266; distinct
  edge values scored 4246. Argument preservation, frame layout and initializer
  scheduling remain different. The existing type's byte layout is unchanged.
- `func_15116BAC`, `game_143DE0.c`: first typed motion/sound candidate scored
  5909. The three axes use halfword current values, fullword targets and
  halfword delta outputs. The sound table's existing 12-byte stride is retained;
  two actual trailing halfword fields replace equivalent padding. Frame,
  register and control-flow differences remain.
- `func_1512D390`, `game_15A840.c`: the initial typed owner/state candidate
  scored 1090. An explicit lower-clamp store and separate decay path improved
  it to 490. The derived-state pointer is still materialized differently;
  associated load scheduling and zero-comparison operands remain unmatched.
- `func_15048FC8`, `game_75FC0.c`: the existing `sqrtf` declaration and intrinsic
  pragma were below this caller. Moving them above it improved its old 3363
  candidate to 1585. Using one coherent angle accumulator reached 45, with all
  opcodes, control flow, constants and stack rows equal. Seven final-angle FPR
  rows still select f2 instead of f12. A separate radians local and an explicit
  quotient assignment also scored 45 and were discarded. Neither the old
  250-variant search nor the adjacent function's exhausted scoped-register
  experiment was repeated.

After deferral, the complete incremental US game-code image and all mapped
external rodata remained byte-identical to the owned ROM. All 1,068 tests
passed (12 skipped), and progress/whitespace checks passed. There are no new
matches or pending batch IDs in this candidate-only pass.

## Subsequent point-table and particle-event candidates

- `func_15156B54`, `game_183640.c`: a typed 3-by-10 position table,
  six-byte light descriptor, and the raw-proven two-argument `15156D24`
  contract produced 2047. Reordering actual locals and structuring the
  coordinate updates scored 2131; the first candidate is retained. Frame,
  coordinate-conversion scheduling, and register/operand differences remain.
- `func_15194810`, `game_1C1150.c`: reuse of the existing particle and event
  packet layouts produced 120 on the first candidate. Only two switch-table
  relocation rows and three call-delay scheduling rows differ. A correctly
  typed collision-result local and a contiguous real-local workspace both
  remained at 120 and were discarded. The original assembly remains active.
  Its raw table at `0x800A82D0` is not newly mapped: a reviewed mapping would
  be needed only after the instruction shape is resolved. No tooling,
  instruction, linker or compiler-setting change was made for this candidate.

## Owner-event callback contract

The local `func_15169850` declaration in `game_1BDC20.c` described five
integers. Its raw callee instead dereferences arguments one, three and four,
homes and masks the second to a byte, and forwards the fifth as a record
pointer. The corrected pointer/byte contract agrees with the callee candidate
and the matched `15149514` wrapper's byte argument.

Removing integer-address casts improves `15191980` from historical 2074 to
725. Fully named owner/event fields scored 805 and were discarded.
`15191A84` improves from 2479 to 1615 with the declaration, then to 890
with a shared pointer to the actual owner fields. A concrete word-pointer
event argument remained 890 and was discarded. Both stay deferred; repeated
event-pointer reloads and return/delay-slot scheduling still differ. No fake
volatile accesses or artificial stack homes were added.

`func_15060D54` also remains deferred. A typed 812-byte actor record and
25-record counted loop scored 2465. A pointer-bound loop scored 16380 and
an explicit remainder/four-record traversal scored 8135; both were discarded
after two non-improvements. Loop control, register allocation and division
scheduling differ.

The raw `func_150A751C` in `game_D4450.c` is blocked without a source
change. It uses v0 continuation addresses with non-call jumps to the custom
`150A76F0` helper, live odd floating registers, FCSR-sensitive conversions,
and stack restoration before its saved-register reloads. The emitted starter
omits continuation bodies and reports an unset register. No ordinary-C match
or original-ASM provenance proof is claimed by this blocker classification.
