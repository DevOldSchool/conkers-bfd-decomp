# Actor vertical-motion and sound-handle wrappers

Five existing matched helpers in `src/game/game_83300.c` use source-local
aliases. Numeric linkage, signatures, operations and complete spans remain
unchanged. Sound names deliberately distinguish proven actor-handle storage;
no voice/effect, one-shot/loop, character or model identity is inferred.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `15058EA4` | `actor_update_vertical_acceleration_and_clamp_velocity` | 128 |
| `15060A30` | `actor_play_sound_store_handle_8c` | 108 |
| `15060A9C` | `actor_play_sound_without_saved_handle` | 104 |
| `15060B04` | `actor_play_sound_without_saved_handle_with_volume` | 108 |
| `15060B70` | `actor_play_sound_store_handle_8e` | 52 |

## Height-conditioned acceleration and velocity limits

If actor Y at +0x18 exceeds argument one, the helper writes argument two to
+0x24. Otherwise, if Y is below argument three, it writes argument four there.
If neither strict comparison passes, the field is preserved. It then caps
velocity +0x20 above at argument five, returning immediately on that path;
otherwise it caps below at argument six. No bound/threshold reordering,
position integration or convergence guarantee is added.

Original motion code `1505A770` uses +0x24 to decrement +0x20 in time-scaled
substeps, then integrates +0x20 into Y. Positive values of this acceleration
term therefore decrease the stored vertical velocity. Original call sites include `1504CB78`,
`15052DA0`, `150B1374`, `150B1720` and `150D7E20`. One caller supplies equal
height thresholds but separately changes velocity; the helper alone does not
establish a hover or bounce policy.

## Sound routing and retained actor handles

The word at actor+0x318 chooses routes, but its broader meaning is not assigned.
The 0x8C/0x8E qualifiers identify observed handle-storage fields, not semantic
sound classes. Existing pointer-carrier and sound-ID argument types remain.

- `15060A30`: zero +0x318 calls `10010344` with volume 28000 and parameters
  500/2500. That callee rejects actor state word zero or five, replaces the
  matching actor sound-record group keyed by actor byte +0x3B OR 0x20000,
  and stores the result at +0x8C. Nonzero +0x318 calls `15060778` with volume
  24000 and mode one, passing the existing +0x8C handle and saving its result
- `15060A9C`: zero +0x318 calls `10010630` with volume 24000 and 500/2500.
  That callee rejects state word zero, but not five, and retains no result in
  the actor's two handle slots. Nonzero +0x318 uses `15060778` mode zero,
  starting from handle zero and saving no actor handle
- `15060B04`: uses the same routes/storage behavior as `15060A9C`, with caller
  volume. Its direct route passes the full s32 value; the `15060778` route
  first narrows it to u16. This difference and all original ABIs remain
- `15060B70`: calls `10010154` with volume 28000 and 500/2500. It rejects state
  word zero or five. The nonzero +0x318 route passes existing +0x8E to
  `10010BE8`; the zero route replaces the group keyed by actor byte +0x3B
  OR 0x10000. Accepted routes save the result at +0x8E

The mode-zero/one helper additionally adjusts volume by
`50*((actor word +0x184 >> 3)&0x30)`. These are preserved numeric controls,
not a newly inferred attenuation unit or gameplay effect.

“Without saved handle” refers only to the actor-side storage distinction.
The spatial route still registers callback `1000EE70`, which copies actor XYZ
into its sound record; those sounds are not globally untracked or detached.
The wrappers do not establish looping, successful playback, or immediate
release/replacement of every underlying voice. No meaning beyond the stated
numeric predicates is assigned to actor states zero/five here.

## Evidence and acceptance

Original bodies and motion consumers are in
`reference/game/us/asm/55E50.s`; the main-runtime callees appear under their
8000xxxx/8001xxxx views in `reference/us/asm/EB00.s`. The sound/volume path
reaches `10010BE8 -> 10017438`; original `reference/us/asm/15550.s` contains
the latter and its volume-argument store at sound-state+0x44.
Existing [actor initialization evidence](actor_initialization_helper_semantics.md)
supports the motion-field roles. All 500 registered bytes require full-span
CURRENT (0), existing layout, clean batch, tests, progress, whitespace, RSP
and exact main/game images. Raw callees remain evidence only; no audio or
other ASM-to-C implementation, source-unit completion or asset identity is
claimed.
