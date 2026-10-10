# Scalar clamps, wrapping and angular distance

Source: `game_16EE20.c`. Mathematical roles do not establish gameplay
activation.

| Symbol | C name | Span |
| --- | --- | --- |
| `15143DA8` | `scalar_clamp_s32_in_place` | `0x60` |
| `151444DC` | `scalar_wrap_s32_inclusive` | `0x4C` |
| `15144528` | `scalar_wrap_f32_preserve_endpoints` | `0x70` |
| `15144BC8` | `angle_wrap_degrees_f32_preserve_endpoints` | `0x64` |
| `15144C2C` | `scalar_wrap_s16_period255` | `0x60` |
| `15144C8C` | `angle_distance_radians_f32` | `0x60` |

## Clamp and integer wrapping

The clamp sorts its two signed bounds, updates the pointed-to value if needed,
and returns 1 for a lower correction, 2 for an upper correction or 0 without a
store. Equality is unchanged. Its original XOR swap and pointer contract remain.

The signed-word wrapper takes `(value, upper, lower)` and repeatedly subtracts
or adds `upper-lower+1`, including both endpoints. It neither sorts nor validates
the bounds. Equal bounds have period one. Original MIPS `subu/addiu/addu`
operations remain; the alias does not promise portable C signed-overflow
behavior or termination for reversed bounds.

The signed-halfword wrapper subtracts 255 while value >=256 and adds 255 while
negative, preserving both 0 and 255. It is not modulo 256: 256 becomes 1,
-1 becomes 254, 510 becomes 255, and -255 becomes 0. Original sign extension
of input and intermediate halfwords is retained. Exhaustive arithmetic checking
of all 65,536 signed-halfword inputs terminated in [0,255]. No angle role is
inferred for this helper.

## Floating wrapping and endpoints

The generic float wrapper also takes `(value, upper, lower)`, but its period
is `upper-lower` with strict comparisons. Both endpoints remain: with bounds
0 and 360, 720 becomes 360 while -360 becomes 0. The degree helper specializes
this behavior to [0,360]. Neither checks finite values, ordered bounds, positive
width or arithmetic progress. Equal bounds pass an equal input but cannot
reduce an unequal finite input. Infinite or sufficiently large finite inputs
can also fail to progress. No exception-independent NaN behavior is promised.

Generic-wrapper calls at `150E6DD0/150E6DE4` use period 2pi, verified from
`800A1308`; call `151A669C` uses upper 2048 and lower zero, ruling out a
radians-only name. Degree-wrapper calls `150ED1DC/150ED1E8/150ED1F4` normalize
two angles and their difference before a half-turn correction. Call `15088ED0`
follows conversion by 360/65536 from an integer angle representation.

## Unsigned radian distance

`15144C8C` wraps both inputs through still-raw `15144B68`, computes their
absolute difference, and uses full-turn minus difference only when the result
is greater than a half-turn. Half-turn equality remains; direction is discarded.
For ordinary finite inputs this is unsigned shortest angular separation. The
callee's repeated-wrap limits remain, and its deferred implementation is untouched.

Original US words `800A56A4/800A56AC` contain `0x40C90FDB` (approximately
6.283185482), and `800A56A8` contains `0x40490FDB` (approximately 3.141592741).
Calls `150C2DB8/150C3114` supply the known atan2 helper's output; the latter
compares the result with a verified 0.4-radian threshold.

## Evidence and acceptance

All 576 original registered bytes in `reference/game/us/asm/141970.s` agree
with the checksum-validated US game image. A bounded direct-call scan found 10
JALs to the generic float wrapper, 12 to the degree wrapper and two to the
radian distance helper. It found none to the clamp or integer wrappers; their
names rely on unambiguous complete implementations, not inferred runtime use.
This does not establish absence of indirect callers.
