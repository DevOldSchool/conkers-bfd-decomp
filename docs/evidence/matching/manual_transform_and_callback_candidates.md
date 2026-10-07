# Bounded transform and callback candidates (US)

All three new candidates remain deferred with original assembly active. They
add no matched bytes. The attempts are manual, with no automatic permutation,
assembly or compiler-setting changes, artificial padding or added volatility.

- `func_15145EA4`, `game_16EE20.c`: real 4-by-4 transform storage and
  correctly stepped input/output pointer arrays scored 512. Sharing loop
  locals reduced that to 358. Directly decrementing the incoming parameter
  scored 984 and was discarded. Placing the actual x scalar before the matrix
  reached 353 with exact frame and stack offsets. Counter register coalescing,
  one entry move and the initial floating comparison operand order remain.
- `func_1515FDA0`, `effects/colourframebuffer.c`: named linked-node storage,
  416-byte group stride and typed callback/iteration tables scored 5566.
  Structured duplicate slot reloads scored 5576; explicit callback-table and
  group register hints scored 5621. Both were discarded. The first candidate
  remains; global-address hoisting, frame and control scheduling differ.
  Naming the existing node's next pointer preserves the constructor's existing
  payload offset and 24-byte total layout.
- `func_151A743C`, `game_1D4140.c`: the raw `1514AB5C` callee consumes
  leading floats in f12/f14, then a2/a3 and eight stack words. It does not
  consume the apparent live a0/a1 values reported by the starter. Its real
  declaration has 12 argument words, not 14. The destroy helper `1516972C`
  takes one pointer, as its matched definition confirms. Corrected contracts
  and typed state first scored 1206; direct actual-field expressions scored
  98. A separate initialization pointer scored 232 and was discarded.
  Reordering the two actual locals reached 90 with exact frame and stack
  offsets. Derived-state rematerialization and threshold load order remain.

The already-matched `151A73EC` retains authoritative `CURRENT (0)` after
removing its phantom second destroy-helper argument. The existing framebuffer
constructor `1515FF74` also retains `CURRENT (0)`. Their clean regression
batch ended in `BATCH_COMPLETE`: all 2,072,880 US game-code bytes and mapped
external rodata remain identical to the owned ROM, and all 1,075 tests pass
(12 skipped). Neither recheck is counted as a new match.
