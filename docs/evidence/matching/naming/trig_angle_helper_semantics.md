# Trigonometric lookup and angle-delta helpers

Names describe original US approximations, not exact mathematical functions.

| Symbol | C name | Span |
| --- | --- | --- |
| `15048360` | `trig_acos_radians_clamped_lut` | `0xA8` |
| `15048408` | `trig_asin_radians_clamped_lut` | `0x98` |
| `150484A0` | `trig_atan2_positive_radians_lut` | `0x140` |
| `150487E0` | `trig_asin_radians_lut` | `0x84` |
| `15048864` | `trig_asin_turn256_lut_ones_complement` | `0x64` |
| `150488C8` | `trig_asin_radians_lut_interpolated` | `0xE8` |
| `150489B0` | `trig_cos_turn256_lut` | `0x90` |
| `15048A40` | `trig_sin_turn256_lut` | `0x30` |
| `15048A70` | `angle_delta_degrees_f32_single_wrap` | `0x60` |
| `15048AD0` | `angle_delta_degrees_s32_single_wrap` | `0x40` |

## Inverse-trigonometric approximations

`15048360/15048408` clamp the input at +/-1, scale by 32767, convert to a signed
halfword and invoke `15048664/150486B8`, respectively. The returned unsigned
acos or signed asin value is multiplied by approximately pi/65535. ROM words
at `80098DD0/DD8` establish 32767; `DD4/DDC` hold `4.793763218913227e-05`.
These are quantized, biased approximations, without ideal endpoint guarantees.
Original callers include `1503C970/15049FE0` for acos and `150ED538` for asin.

`150484A0` implements the argument order atan2(first, second), using vector
length, the acos helper and quadrant correction. Its axis results are 0,
pi/2, pi and 3pi/2 around a nonnegative turn; the zero vector returns zero.
Constants at `80098DE0..80098DF8` establish those units. The original game-code
scan found 79 direct calls, including `150CF05C` and matrix decomposition
in `1503E5F8`; this is not a claim about runtime coverage or indirect callers.

The three helpers in `game_75C90.c` index the unsigned-halfword table
`D_80098E00` using the integer conversion of `abs(input) * 255.99998`.
All 256 stored values agree with floor(asin(i/256)/(pi/2) * 65536).
`150487E0` scales by (pi/2)/65536 and applies sign. `15048864` instead shifts
the table value right ten and, for negative input, returns 255 minus that
magnitude as a float. It is not a 256-minus-magnitude wrap. `150488C8`
interpolates adjacent values, using 65535 as the upper value at index 255.
These three helpers do not clamp input or validate table bounds. The first
two retain their overwritten second float parameters without ABI repair.

Original calls at `1503E774` and `150490EC` establish matrix-angle extraction
and subsequent quadrant handling. No direct JAL to `150488C8` appeared in the
bounded game-code scan; this does not establish that the helper is unused.

## Byte-turn sine/cosine and degree deltas

`D_8009A220` is a 65-entry quarter-wave cosine table: its values agree with
cos(i*pi/128) within `2.74e-7`. `150489B0` mirrors/signs this table for an
unsigned byte phase, giving 1,0,-1,0 at phases 0,64,128,192. `15048A40`
passes phase minus 64 through that byte-argument helper, establishing sine.
The pair is called at `15044C08/15044C18`; the bounded scan finds 55 sine and
45 cosine direct calls. Some reconstructed caller-local labels reverse the
names; the original table, not those labels, establishes these identities.

`15048A70` returns target minus current after at most one 360-degree correction,
using current-minus-target comparisons `>180` and `<=-180`. `15048AD0` uses
integer comparisons `>=181` and `<-179`. The half-turn tie returns -180.
Neither performs arbitrary-angle modulo normalization. Original callers
`15117608/15117638` compare changes around angular integration; `15099508`
is the integer helper's direct call.

## Complete-span evidence

Independent original references `48360.s`, `484A0.s`, `487E0.s` and `489B0.s`
cover all 1,456 bytes and agree with the checksum-validated original game
image. Registered versus ELF symbol sizes are `0x98/0x94` for `15048408`,
`0x140/0x13C` for `150484A0`, `0xE8/0xDC` for `150488C8`, and `0x40/0x34`
for `15048AD0`; full-span checks retain every trailing zero word.
