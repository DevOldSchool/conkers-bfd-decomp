# Camera source-unit completion work

This source-local pass continues `src/game/camera/camera_camera.c` from the
reviewed 45-member range at game offsets `0x122AE0:0x1287E0`. The unit remains
mixed and in progress: 24 functions are accepted C matches, while all 21
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

The initial reconstruction compiled the complete 100-byte executable sequence,
including the return-delay NOP, exactly. Its required registered span remains
108 bytes: the raw return is at `0x151287D0`, its delay slot at `0x151287D4`, and
the final two section-alignment NOPs at `0x151287D8` and `0x151287DC`. The
initial focused object omitted those last two words, yielding CURRENT 200.

Matching `func_15125924` below adds its genuine 328-byte C body to the focused
prefix. At that checkpoint, the final function starts at `0xE44`, with the same
modulo-16 position as its authentic unit offset `0x5C94`. The compiler naturally emits
the required two final zero words. The unchanged comparator now reports
CURRENT 0 over all 108 bytes, and the full source-unit layout passes. No
comparison-tool extension or manually added padding is included.

## Retail-only branch locals

Owned earlier-build evidence supplies a useful source-lifetime clue for
`func_15125924`. Debug `func_1512B258` and ECTS `func_151167E4` retain the
retail `0x30` frame and the type/value homes at SP+`0x2C`/`0x28`. Retail adds a
flags/difference restoration tail without increasing that frame. The two
values used only in that tail have non-overlapping lifetimes with the values
consumed by the outer decision.

Placing `s32 flags` and `f32 difference` declarations in the existing else
branch recovers the original frame and matches the complete 328-byte retail
span at CURRENT 0. No operations, fields, calls, or storage objects are added.
This does not establish the original source text; the independent retail
instruction comparison and layout gate establish the accepted result.

The earlier inputs were independently normalized and verified:

- Debug ROM SHA-1: `3b99222ee76f6277a963142cd807b3df25d5174f`
- ECTS ROM SHA-1: `06597dc935651f8995bfacc30fde6e621d44c3e1`

The same review found unchanged `0x48` frames in all three versions of
`func_15125A6C`; those bodies provide no basis for inventing extra locals or
padding in its still-deferred candidate.

## Camera update loop

`func_15122AE0` now expresses its existing signed camera-index induction as a
single for-loop, retaining the same 16-bit increment conversion and every body
operation. This places the initial zero in the raw entry branch's delay slot
and matches the complete 380-byte span at CURRENT 0. No loop bounds, calls,
field operations, or compiler settings change.

## Further scoped evidence

For `func_15124C38`, the three retail-only float output scalars now live in
their existing early-return branch. The debug body retains the same `0x60` frame; neither earlier body
contains that float-output call. Keeping their original order and identities improves
CURRENT 3598 to 3092, but the frame, output homes and FP/control scheduling
remain different. The implementation stays deferred.

The callback helper contract used by `func_151277B0` is now established through
the documented MAIN link/runtime mapping: runtime `func_100111C8` refers to
matched `func_800111C8`, defined as `void func_800111C8(u16)`. The existing
camera declaration is correct; its frame/register differences remain and no
body change was made for this contract review.

## Bounded negative results

- `func_15125924`: sharing the disjoint initial type and later flags local
  worsens CURRENT 10 to 50; removing the named target pointer is neutral at
  10. Those probes were rejected before the distinct beta-supported
  branch-local declarations above produced an exact match
- `func_151256BC`: replacing named derived-address locals with their repeated
  typed expressions leaves CURRENT 295 and the `0x48` versus `0x38` frame
  unchanged. A later true-arm declaration-scope probe regresses to 867 and
  enlarges the frame; the original CURRENT 295 candidate is preserved
- `func_15125490`: its stale deferred parameter declaration was repaired to
  agree with the existing void-pointer prototype, retaining the same project
  typed field view internally. It compiles again and remains CURRENT 560
- `func_15123A54`: scoping the real retail-only old-distance scalar to its
  collision-success branch is neutral at CURRENT 5742. The prior candidate
  is preserved; it is not merged with the separate entry-distance snapshot
- `func_15123568`: a proposed unsigned shift-mask literal was not tried after
  fresh diagnosis showed that the relevant shift-one and shift instructions
  already match. CURRENT 230 remains unchanged

These results do not exhaust possible future evidence. They do exclude
repeating the same unchanged hypotheses as new progress. Acceptance still
requires independent full-span CURRENT 0, every member's exact layout, the
complete US ROM and game image, data/rodata checks, and a clean batch gate.
