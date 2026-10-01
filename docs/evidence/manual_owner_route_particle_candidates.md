# Bounded owner, route and particle candidates (US)

All four functions remain deferred. Their original assembly is active and no
additional matched bytes are claimed. These are manual source-only attempts;
there is no automated permutation, changed compiler setting, assembly patch,
artificial padding or added volatility.

- `151A8624`, `game_1D4E00.c`: a typed 80-byte descriptor and 40-byte
  owner packet scored 1828. A full-word cached mode and ternary timed flag
  scored 2078 and were discarded. The raw entry explicitly normalizes two
  arguments, but no qualifying existing declaration was found for narrower
  formals. Word-sized formals were retained under the repository's declaration
  evidence rule; the narrow-formal experiment was not run.
- `15088D58`, `game_B4080.c`: typed route/actor fields and real interpolation
  call contracts scored 375. Placing the actual entry/angle locals before the
  coefficient arrays and using full-word status/rotation reached 80. A
  full-word cached link reached 20, with exact frame, stack, opcodes and
  control flow. Three GPR operand rows remain. A narrow rotation and reversed
  comparison scored 40 and were discarded.
- `150AFE64`, `game_DC6B0.c`: six actual transformed output scalars and the
  concrete large-call contracts scored 246. Combining the matrix pointers
  scored 860. Reloading the final owner into its word argument reached 26;
  one commuted addition and two matrix spill-offset rows remain. A coherent
  real-field workspace scored 1155 and was discarded.
- `1514AD9C`, `game_177B50.c`: the actual 72-byte particle and canonical RNG
  declarations first scored 1863 after removing a conflicting old declaration.
  Separating the second RNG call from its later scaling and changing initializer
  order reached 14. Only the two initial halfword stores are reversed. A nested
  comma initializer also scored 14 with less direct source; a material
  temporary scored 20. Both were discarded and the clear second candidate
  was retained. Incoming formals stay word-sized with an explicit byte cast
  at the final submission.

The callback research also excluded `150D596C`, `151D2DCC` and `151D2E14`:
the older inventory/history already records helper-ABI or pointer/prototype
attempts. Those hypotheses were not repeated merely because the current
recovery ledger did not contain them.

After deferral, the complete incremental US game-code image (2,072,880 bytes)
and every mapped external rodata payload remain byte-identical to the owned
ROM. All 1,075 tests pass (12 skipped), and progress/whitespace checks pass.
There are no pending new match IDs; no empty acceptance batch was run.
