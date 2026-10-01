# Manual interpolation, actor effect and descriptor candidates

These candidates remain disabled and do not count as matches:

- `func_1501FC8C`, `game_49D30.c`: corrected the local declaration of
  `func_1501F72C` to return its raw v0 sample index. Six-float position output
  and staged interval arithmetic improved 933 → 738 → 633. The exact frame
  is recovered, but result spills and floating-point scheduling still differ.
- `func_1502C1A4`, `game_58F80.c`: named observed fields in the existing
  812-byte actor. Shared active/model scratch and explicit creation branches
  improved 940 → 380 → 320. Frame and register selection agree; global-address
  initialization and creation-store delay scheduling still differ.
- `func_150B85C0`, `game_E4FF0.c`: typed descriptor, vector copies and existing
  descriptor-consumer signature. Its 0x70-byte extent follows the consumer's
  copy contract. All incoming integer formals remain word-sized; the byte
  consumer argument uses an explicit cast. Scheduled initial stores plus a
  ternary random flag improved 1668 → 293. Sorting the final stores worsened
  to 1155; restoring them and retaining the independently proven local order
  gave 285. Frame, argument homes and descriptor fields agree. Final flag
  expression allocation and store scheduling differ. No artificial padding,
  volatile accesses or assembly body was introduced.

The successful dispatcher in the same pass is documented separately in
`game_61490_jump_table.md`. Existing helper implementations were not rewritten.
