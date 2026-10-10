# Folded cosine lookup and scaled direction components

Source: `game_16EE20.c`. The folded cosine is distinct from the earlier cosine
helper.

| Symbol | C name | Span |
| --- | --- | --- |
| `151423D8` | `trig_cos_turn256_lut_folded` | `0x6C` |
| `1514373C` | `trig_scaled_sin_cos_radians` | `0x58` |
| `15143794` | `vec3f_from_yaw_pitch_turn256_lut` | `0xA0` |
| `15143834` | `vec3f_from_yaw_pitch_turn256_lut_wrapper` | `0x40` |
| `15143874` | `trig_scaled_sin_cos_turn256_lut` | `0x64` |

## Cosine table and signed zeros

`D_8009A220` contains 65 floats at initialized game-data offset 0x17700,
with SHA-1 `88a7c0902dedcd55acd23ab7bf25bea5a1dd1187`. It samples cosine over
a quarter turn: entries 0/16/32/48/64 are approximately
1/0.9238795042/0.7071067095/0.3826833963/0.

The new alias describes the existing unsigned-byte phase fold: bit 0x40 reflects
the low-six-bit index, and quadrants 0/3 are positive while 1/2 are negative.
A full turn is 256 phase units. At phases 0/64/128/192, outputs are
1/-0/-1/+0. The already-named `150489B0` instead produces +0 at 64 and -0 at
192. These implementations are not substituted or combined; their exact
signed-zero behavior and linked addresses remain distinct. In particular,
phase minus 64 produces sine, regardless of old caller-local variable names.

## Scaled sine-first pairs

`1514373C` accepts a radian angle and scale r. It calls the original cosine
`15047C00` and sine `15047D60`, then writes r*sin(angle) through the first
output and r*cos(angle) through the second. Their complete original spans and
the existing libultrare/gu reconstruction establish the radian roles; they are
not inferred from the order of the calls.

Original caller `151955A0` first converts a degree value through
`800A8708 = 0x3C8EFA35` (approximately pi/180). Its output pointers address
stack X/Z components at +0x30/+0x38. This corroborates sine-first ordering
without assigning a universal coordinate-plane convention to the two-pointer API.

`15143874` provides the same scaled sine-first/cosine-second pair using the
folded byte-phase lookup. Its s16 input is retained, with the low byte consumed
by the callee. Existing local `cosine` actually holds sine and is unchanged.
Caller `150F2230` supplies random &255 and scale 100, writing X/Z while keeping
Y zero. Its original caller declaration is preserved without an ABI repair.

## Three-component lookup direction

For low-byte yaw a, pitch b and scale r, `15143794` stores:

- X = r*cos(b)*sin(a)
- Y = -r*sin(b)
- Z = r*cos(b)*cos(a)

These denote the existing lookup results, not idealized trig replacements.
Angles use 256 units per turn, but both original argument types remain s16.
Pitch uses the negative-Y sine convention shown above. The multiplication grouping,
sequential stores and negative-zero behavior remain. There is no normalization,
finite-value or arbitrary output-overlap guarantee.

Original caller `151BC3F0` supplies yaw random &255 and pitch random%65-32,
then uses the three components as velocity. `15143834` is a pure forwarding
wrapper with the existing signed-halfword argument handling. A bounded direct-
JAL scan finds no caller for this wrapper; that does not establish it is unused.

## Full-span evidence

All 520 original registered bytes in `reference/game/us/asm/141970.s` agree
with the checksum-validated US game image. Direct game-call counts are
298/13/78/0/40 in table order above, without claiming exhaustive indirect-call
coverage. The adjacent radian 3D helper remains raw/deferred.
