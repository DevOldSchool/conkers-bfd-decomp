# Timed viewport flash helpers

Source: `src/done/game/game_FF5C0.c`. Flash describes a white/black viewport
overlay, without lightning, weather, camera-flash or scene identity.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `150D2110` | `viewport_flash_create` | 188 |
| `150D21CC` | `viewport_flash_update_phase` | 176 |
| `150D227C` | `viewport_flash_queue_removal` | 44 |
| `150D22A8` | `viewport_flash_unlink_and_free` | 44 |
| `150D22D4` | `viewport_flash_decrement_count` | 32 |
| `150D22F4` | `viewport_flash_draw` | 128 |
| `150D2374` | `viewport_flash_spawner_update` | 220 |

## Constructor and callback ownership

The constructor increments byte `D_800D9900`, creates a timed managed object
through `15149130`, and copies a 0x18-byte packet to object+0x28 when allocation
succeeds. Its first argument is the signed-halfword lifetime stored by that
callee at +0xE, not an effect or asset ID. The packet starts with phase zero,
white-phase flag zero, the two float intervals, their sum and two alpha bytes.
The flag therefore selects the black path until the first phase update.
The counter increment occurs before allocation and is not rolled back on
failure; it is not a reliable allocation-success count. Existing byte wrap,
void return, packet padding and argument narrowing are unchanged.

The selected update index 0x2F, draw index 2 and removal index 0x26 reach
these original US data words, independently read from checksum-validated
game data:

| Table word | Target |
| --- | --- |
| `8008A5A4` | `150D21CC` |
| `8008A678` | `150D22F4` |
| `8008A720` (`8008A688 + 0x26*4`) | `150D227C` |
| `8008A848` (`8008A7B0 + 0x26*4`) | `150D22A8` |
| `8008A5A8` (update index 0x30) | `150D2374` |

Original `149130.s` stores the selectors at +0x11/+0x12/+0x13 and dispatches
the update, draw and removal tables. Its timer update subtracts `D_800BE9E4`
from the lifetime, calls the phase callback, then requests removal when the
lifetime is negative. This timer is separate from the float phase cycle.

## Phase, viewport drawing and global color side effect

The phase updater adds `D_800BE9A4` to object+0x2C and repeatedly subtracts
the total interval at +0x38 while phase is strictly greater than that total.
It sets flag +0x28 to one when phase is less than or equal to the first
interval at +0x30; otherwise it clears the flag. Equality at either endpoint
is preserved by these comparisons. There is no positivity or finite-value
validation, no negative-phase correction and no guarantee of termination
for arbitrary interval inputs. No seconds-versus-frames unit is assigned.

The white phase calls `1515D4D4(255,255,255,255)`. Original `15D440.s`
shows a priority comparison against byte `800DCD27`, RGB stores at `800DCD20`,
a flag write at `800DCD7C`, and a priority update. The black phase does not
undo these writes. Their broader rendering policy remains unnamed.

Drawing selects white RGB with alpha at +0x3C when the flag equals one,
otherwise black RGB with alpha at +0x3D. It forwards the signed-halfword
view index and returns the advanced display-list cursor. Original callee
`1517F08C` in `17EE40.s` packs those RGBA bytes into a primitive-color
command and emits a fill rectangle from the selected 0x180-byte viewport
record at `D_800BE628`. The pinned `PR/gbi.h` identifies commands 0xFA and
0xF6. This establishes a viewport overlay without promising nonzero opacity,
full physical-screen coverage or restoration of prior graphics state.

## Counter release and periodic emission

Both removal wrappers decrement `D_800D9900` first. `150D227C` then calls
`1514933C`, which performs timer cleanup and queues managed removal through
`15169804`. `150D22A8` instead calls `15149368`, which performs the same
cleanup and unlinks/frees through `15169824`. The standalone decrement helper
does not inspect its argument, release an object or guard against underflow.
These paths preserve the staged/immediate distinction documented in the
[managed-object evidence](managed_object_helper_semantics.md).

The spawner subtracts `D_800BE9E4` from its custom countdown. On a strictly
negative result it emits one flash with a randomized signed-halfword lifetime
and the stored phase/alpha parameters, then replaces the countdown with a
second randomized delay. It does not catch up multiple emissions or preserve
overshoot. Both random choices retain the unsigned remainder by range+1 and
addition of the respective base; range validity, overflow and modulo bias
are unchanged. The existing fields called `base_id`/`random_id` supply the
lifetime, and their names/types are deliberately left untouched.

Original bodies occupy all 832 bytes in `D2110.s`, including both trailing
zero words at `150D2448/150D244C`. Original actor rendering at
`1502D128..1502D138` also reads the counter to select a numeric flag; no
stronger meaning for that flag is inferred. Existing boundary evidence is in
[the periodic-controller
audit](../../boundaries/game/families/game_raw_periodic_actor_resource_groups.md). Timer callees retain
their existing matched implementations; raw color and rectangle callees remain
evidence only.
