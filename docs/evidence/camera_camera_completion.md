# Camera source-unit completion work

This source-local pass continues `src/game/camera/camera_camera.c` from the
reviewed 45-member range at game offsets `0x122AE0:0x1287E0`. The unit remains
mixed and in progress: 21 functions are accepted C matches, while all 24
remaining members retain assembly. Deferred C is evidence for further work,
not match credit or a completed source unit.

Independent reference input is the checksum-validated US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; its decompressed game-code SHA-1 is
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The existing boundary evidence
remains [the camera-family review](game_beta_camera_rope_bee.md). No boundary,
compiler setting, comparison rule, shared source, or assembly payload changes
are made here.

## Previously untranslated state-transition function

`func_15128030` now has a deferred implementation reconstructed from the raw
US instructions. Its state switch, interpolation calls, field accesses, and
finite-value arithmetic are represented in C. Reusing actual non-overlapping
scalar lifetimes recovers the original `0x30` stack frame. The focused score
improves from the initial 3498 to 2548; it is not an exact match.

The completed-transition return needs particular care. At `0x15128204`, raw
code loads the target pointer from camera offset `0x3D0` into integer V0.
Every later call is to `func_15048720`, whose only callee is `func_15048A70`.
Neither raw helper modifies integer V0 or camera memory. The completion arm
at `0x1512835C:0x1512837C` therefore returns that pointer value, whereas the
continuing-transition arm explicitly returns 1. The deferred C returns the
pointer explicitly instead of inventing a dual floating/integer return ABI or
using a missing non-void return. Its extra pointer reload remains a real
matching obstacle. Timer subtraction uses unsigned arithmetic before the
halfword store to preserve the raw wrapping operation.

Control scheduling, integer/FP allocation, and five interpolation ADD operand
orders remain different. Finite-value arithmetic correspondence does not
establish identical exceptional NaN payload propagation. These unresolved
properties are additional reasons to retain the assembly implementation.

## Final member and genuine section alignment

`func_15128774` was reconstructed directly from the current raw US field
loads and stores, replacing the historical deferred form and its separate
partial structures. The new definition agrees with the existing camera caller
prototype. One real coordinate scalar is reused for three ordered load/store
pairs; no storage or instructions are added for alignment.

The complete 100-byte executable sequence, including the return-delay NOP,
compiles exactly. The required registered span is still 108 bytes: the raw
return is at `0x151287D0`, its delay slot at `0x151287D4`, and the final two
section-alignment NOPs at `0x151287D8` and `0x151287DC`. Those two words are
missing from the focused C object, yielding CURRENT 200. They are not trimmed
from the comparison and the function is not marked matched.

The focused compiler omits remaining assembly members. The current accepted
C prefix is `0xCFC` bytes, while this member's authentic unit offset is
`0x5C94`; their modulo-16 alignment differs. Future preceding C matches may
restore the natural compiler section tail. That must be demonstrated by a
fresh full-span comparison and source-unit layout/integration gates, rather
than simulated with dummy storage, extra functions, or manual padding.

## Bounded negative results

- `func_15125924`: sharing the disjoint initial type and later flags local
  worsens CURRENT 10 to 50; removing the named target pointer is neutral at
  10. The best candidate is preserved. Its only remaining differences are
  the `0x38` versus `0x30` stack adjustment instructions
- `func_151256BC`: replacing named derived-address locals with their repeated
  typed expressions leaves CURRENT 295 and the `0x48` versus `0x38` frame
  unchanged. The earlier candidate is preserved
- `func_15123568`: a proposed unsigned shift-mask literal was not tried after
  fresh diagnosis showed that the relevant shift-one and shift instructions
  already match. CURRENT 230 remains unchanged

These results do not exhaust possible future evidence. They do exclude
repeating the same unchanged hypotheses as new progress. Acceptance still
requires independent full-span CURRENT 0, every member's exact layout, the
complete US ROM and game image, data/rodata checks, and a clean batch gate.
