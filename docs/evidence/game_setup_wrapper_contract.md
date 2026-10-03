# Setup-wrapper helper contract (US)

The deferred constant wrappers `func_151A0E40` and `func_151A0F28` in
`game_1CE2F0.c` previously called the matched empty helper `func_151A11CC`
through incompatible function-pointer casts. Its declaration described four
parameters, while every known raw caller supplies 28 argument words.

The three direct callers are `151A0E40`, `151A0F28`, and `151A1010`, all in
the independent `reference/game/us/asm/1A0E40.s` unit. Each writes every
outgoing stack slot from `sp+0x10` through `sp+0x6C` and then calls
`151A11CC` directly. No other caller or C declaration was found in the
available source, include, configuration, and reference assembly.

The coherent local contract uses `f32` for one-based argument slots 1, 2,
4, 5, 11, and 18, and full-word `s32` for the remaining slots:

- The leading floating arguments remain in `f12` and `f14`; the helper
  stores both with `swc1`
- The scaled caller computes `250.0f * input` at `151A1068` and transfers
  that result to `a3` at `151A1084`, proving floating-point data in slot 4
- The constant callers supply the same slot with bits `0x43230000`,
  represented by `163.0f`
- Stack offsets `0x10`, `0x28`, and `0x44` receive float stores in all
  three callers, establishing slots 5, 11, and 18
- Other slots carry constants, forwarded words, integer calculations,
  truncated float-to-integer results, or byte values promoted to words

The helper's empty body is unchanged. Because it consumes none of its
arguments, this evidence does not recover the original unused formal names,
signedness, or historical declared arity. The declaration represents the
concrete compatible contract supplied by all known callers. No narrow formal
types were introduced.

Both constant wrappers now express direct calls and improve from historical
`CURRENT (2309)` to full-span `CURRENT (1662)`. Their `0x78` frames agree,
but entry argument homes and constant/selector store scheduling remain
different. Naming the real float and selector values scored 1666; a byte
selector local scored 1662. The simpler direct-call form is retained after
these two non-improvements. Equivalent probes were not repeated for the
independently inspected sibling.

Both wrappers remain deferred with original assembly active and contribute
no new matched bytes. The scaled wrapper's implementation and incoming
formals are unchanged; its existing 28-slot helper-call typedef now agrees
with the corrected helper declaration. The helper and all other accepted
members passed independent full-span `CURRENT (0)` rechecks. The scaled
candidate was not remeasured; its older score and four-argument-helper reason
remain historical metadata, not a current blocker diagnosis.

The eight-member regression batch returned `BATCH_COMPLETE`. All 21 unit
members retain their reviewed positions and extents, the `0x2310` text extent
is preserved, and no data, rodata, or BSS storage was added. The complete US
ROM, RSP payloads, 2,072,880-byte GAME image, and mapped external rodata remain
byte-identical. All 1,703 tests passed in both the ordinary host suite
(37 tool-dependent skips) and the pinned toolchain/ROM suite (one skip).
Progress and whitespace gates passed. These are regression checks, not new
function matches or completion of the mixed source unit.
