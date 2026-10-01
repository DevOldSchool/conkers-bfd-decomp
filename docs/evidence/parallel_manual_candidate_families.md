# Parallel manual candidate families

These source-only experiments preserve disabled C candidates. None is a new
match; original ASM remains active. Manual limits and full-span acceptance
were retained. Independent worker scores were reproduced by the integrator
through supported inventory transactions, not by copying generated metadata.

## Owner and effect packets

`func_150FC438` improved 3381 → 2316 → 319. The source-local owner packet is
32 bytes, and the effect packet is 56 bytes, consistent with the observed
copies. Natural local ordering and physical field initialization recovered
all later instructions. The remaining six rows concern the incoming a2
byte-formal normalization. An existing caller declares a3 as u8, but a2 as
s32; no narrowed-a2 experiment was performed without qualifying evidence.

`func_15103254` scored 2892 → 3105 → 828. Its ordinary 0x70-byte descriptor
reuses the proven field layout. A direct random-kind store and initializer
ordering improved allocation; word formals remain. Raw byte reloads, the
first random-flag spill and final flag scheduling still differ.

## Lifecycle and quad callbacks

`func_151321D0` improved 404 → 517 → 260. The source names only observed
fields in the existing actor type. The special callback's ROM pointer at
0x80089988 resolves to the already matched one-owner `func_151332DC`;
cleanup entries at 0x80089980/0x80089984 resolve to one-owner
`func_151A7908`/`func_151B5FCC`. Callback table neighborhoods are evidence
for call contracts, not newly claimed table ownership. Combining the flag
clear with its condition and ordering real locals reproduces the first
0xE8 bytes and stack exactly. The later dead flag changes register from a1
to v1, affecting the alpha update and final predicate.

`func_151AC810` scored 796 with the already proven paired-vertex source shape.
All geometry arithmetic and stores agree. Narrowing a word selector at use
sites introduces a cached spill in place of raw signed-halfword argument-home
reloads. No existing target declaration was found, so no narrowed-formal
experiment was performed. The owned ROM contains its callback pointer at
0x80089E48; a qualifying interface declaration remains a possible lead.

`func_151BECB8` improved 2505 → 776 → 711. Typed 812-byte actor traversal,
two actual three-float vectors, and explicit switch arms recover register
roles. Frame extent, vector workspace offsets, ready-state scheduling and
the sparse-switch join still differ. No stack padding was added.

## Independent particle worker

The worker owned only `game_E4FF0.c` in a separate checkout and generated
workspace. Its source-only changes and proof ledger were handed to one
integrator. Both best scores were independently reproduced there:

- `func_150B879C`: 614 → 435 → 977, best 435 retained. Real local ordering
  recovers frame/stack and control flow. Zero/scale FP allocation and final
  flag-combine scheduling remain. Raw `func_15130374` forwards v0 from
  `func_15130280`, whose independent raw paths return null or the allocated
  object. This supports the source-local pointer return annotation used by
  the caller, without rewriting a shared helper.
- `func_150B82D0`: 7198 → 7198 → 5283 → 5069. Const qualification did not
  hoist the original extern loads. Cached scalars improved the loop but grew
  the frame. An additional concrete hypothesis used exact owned-ROM values
  from 0x8009FD68/6C/70: bit patterns C4C44000, 45444000, 3C23D70A. These represent
  -1570.0f, 3140.0f and the nearest f32 to 0.01. Literal hoisting improved to 5069,
  but the 0xE8 frame still exceeds the target 0xE0 and allocation differs.

No empty clean batch was run. The candidate checkpoint is validated by an
incremental complete game-code/external-rodata comparison and progress and
whitespace gates; all accepted functions remain subject to mandatory clean
batch and integration gates. The combined workflow-selector/bootstrap tests
passed 1,092 tests (12 skipped) before this source-only checkpoint.
