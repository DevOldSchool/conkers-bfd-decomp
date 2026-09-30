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
