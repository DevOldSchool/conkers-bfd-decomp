# Light callback and cleanup argument matching (US)

This batch corrects source-local argument contracts in the existing reviewed
`src/game/effects/light.c` unit. No shared headers, raw assembly, compiler flags
or source-unit boundaries changed.

## Cleanup helper

The already matched `func_1515F10C` in `game_18A8F0.c` accepts one list-node
pointer. The independent raw reference at `15D440.s` confirms that incoming a1
is overwritten by the list head before use. Previous declarations and callers
in `light.c` incorrectly supplied a duplicate second argument.

Using a one-pointer declaration and call resolves the old `CURRENT (15)`
near-miss in the 188-byte `func_151602C0`. It now reports full-span
`CURRENT (0)`, including the original allocation reload into a1 followed by
the move to a0 in the cleanup call's delay slot. The historical local-variable
and function-pointer-cast probes were not repeated; the matched callee provides
new, concrete declaration evidence.

## Callback dispatchers

The two 92-byte routines `func_15161804` and `func_15161860` use tables at
`0x8008B208` and `0x8008B2B0`. A bounded inspection of 42 retail pointer words
starting at each address, using the checksum-validated US ROM's decompressed
game-data payload, found seven distinct targets per span:

- First span: `func_150F0390`, `func_15101238`, `func_15161714`,
  `func_1516176C`, `func_151617C4`, `func_15190464`, `func_1519C200`
- Second span: `func_150F03BC`, `func_15101260`, `func_15161740`,
  `func_15161798`, `func_151617E4`, `func_15190490`, `func_1519C22C`

Every distinct target already has a matched definition. They consume one owner
argument or ignore all incoming arguments. None consumes a second argument.
This corroborates the one-argument callback interface; it is not a new claim
about original table or source-unit ownership.

Removing only the spurious cleanup argument left the first dispatcher at 240.
Correcting its callback declaration/call then produced `CURRENT (0)`. The
independently inspected second dispatcher matched on its first revised
candidate with both corrections. Each focused check also preserved source-unit
symbol layout and passed generated-progress and whitespace checks.

All three functions remain members of the mixed light source unit. Their
focused results alone are not source-unit completion or clean-batch evidence.

The clean three-function batch on 2026-09-30 returned `BATCH_COMPLETE`.
The full 2,072,880-byte US game-code image and all mapped external rodata
remained byte-identical to the owned ROM. All 1,068 tests passed (12 skipped);
metadata, generated progress and whitespace checks also passed.
