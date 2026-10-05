# Actor distances and heading-relative horizontal offsets

Four existing matched C helpers in `game_83300.c` use source-local aliases.
Numeric linked symbols, signatures, padded locals, declarations and arithmetic
remain unchanged. No player or character identity follows from a pool index.

| Symbol | C name | Span |
| --- | --- | --- |
| `1505A6F8` | `actor_distance_xz` | `0x34` |
| `1505A72C` | `actor_distance_xyz` | `0x44` |
| `1505D34C` | `xz_offset_scale_rotate_heading_degrees` | `0xBC` |
| `1505DF10` | `actor_distance_squared_to_pool_actor` | `0xCC` |

## Actor-base distance pair

Both inputs are actor bases, with float positions at +0x14/+0x18/+0x1C,
not pointers to three-component vectors. The XZ helper returns
`sqrt(dx*dx + dz*dz)`; the XYZ helper preserves accumulation order
`sqrt((dx*dx + dz*dz) + dy*dy)`. Differences are first actor minus second.
There are no pointer, activity, overflow/underflow or finite-value checks, and
no physical-unit conversion is applied.

Original caller `1507839C` passes `D_800D154C` and
`D_800CC2D0 + actor[0x222]*0x32C` at `150783F0/15078440`. Its remaining mode
uses the absolute difference of +0x18, independently identifying Y as vertical.

## Indexed pool distance and auxiliary outputs

`1505DF10` selects `D_800CC2D0 + index*0x32C` using the existing u8 argument.
It computes X = targetX - sourceX, Y = sourceY - targetY and
Z = sourceZ - targetZ. Preserve those mixed signs for heading calculation.
It writes the signed Y difference, then the low 16 bits of
`1505A630(X, Z, 0)` to the heading output, then X*X+Z*Z to the horizontal
squared-distance output. It returns `(X*X + Y*Y) + Z*Z` without a square root.

The original heading helper uses positive-radian atan2 with (-X,Z), multiplies
by `800994D8` (`0x4622F983`, approximately 65536/(2pi)), performs its unsigned
conversion, adds 0x4000 and masks to 16 bits. Its approximation and original
calling convention remain; no idealized atan2 replacement is made.

At `1505DE5C`, the caller compares total squared distance and the returned
heading. At `1505DC10`, another caller subsequently takes sqrt(horizontal
squared distance) and negates the vertical output at `1505DC68..1505DC80`
for pitch calculation. There are no index, active-slot or output-pointer checks.
Output write order remains vertical, heading, horizontal; arbitrary overlap is
not promised. An unused sixth argument home in callers does not change the
existing five-argument C signature.

## Heading-relative XZ offset

Let theta = (headingDegrees - 90) times the float degree-to-radian constant.
The two offsets u/v are multiplied by scale unless it is exactly 1.0. With C/S
representing the original cosine/sine approximations, this helper returns
X = u*C + v*S and writes Z = -u*S + v*C through its pointer argument. It adds
no actor position itself and is not an ordinary zero-offset planar rotation.

The existing local members named `rotation.sine` and `rotation.cosine` are
misleadingly reversed: `150AD780` adds pi/2 then falls through into the sine
implementation at `150AD78C`. Their spellings, calls and expression order are
preserved. Original data contains `80099520 = 0x3C8EFA35` (approximately pi/180)
and `8009F710 = 0x3FC90FDB` (approximately pi/2).

Caller `1505D5FC` supplies actor +0x40 heading and +0x14C horizontal scale.
At `1505D628..1505D650`, it adds the return to actor X and the pointer output
to actor Z. That call reuses the caller's second-offset slot for the Z output;
the scalar offsets have already been passed by value. Calls
`1505CAF0/1505CCC8` corroborate the same output direction.
No handedness, general finite-value or arbitrary pointer-overlap guarantee is
introduced; the -90 adjustment and scale==1 fast path remain exact.

## Full-span evidence

All 512 original registered bytes in `reference/game/us/asm/55E50.s` agree
with the checksum-validated US game image. Bounded original-game direct-call
counts are 12/7/3/2 in table order above; these are not complete indirect-call
coverage claims. The raw heading/trig/collision helpers and ambiguous bound
setters retain their status. Full registered CURRENT (0), existing source-unit
layout and complete-image equality gate the aliases.
