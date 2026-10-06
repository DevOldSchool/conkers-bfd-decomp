# Segment geometry and angular/profile helpers

Sources: `game_16EE20.c` and `game_75BD0.c`. Pointer-carrier ABIs are
retained; raw callees remain numeric.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `15048720` | `angle_lerp_degrees_single_wrap_delta` | 56 |
| `151451F0` | `segment_sphere_test_unit_direction` | 212 |
| `15145548` | `vec3f_closest_point_on_segment` | 244 |
| `15145974` | `vec3f_to_yaw_pitch_degrees_lut` | 152 |
| `15145A0C` | `semicircle_profile_scaled_lut` | 68 |

## Segment/sphere test

Arguments are origin O, unit direction D, center C, radius r, maximum forward
distance L, two surface-point outputs and their signed distances t0/t1. The
center and surface-point pointers retain their existing s32 carrier types.
Original callers at `15145C40` and `151C896C` normalize their displacement
with `15145128` and use the returned magnitude as L.

Raw `151452C4` computes p=(C-O) dot D and q=|C-O| squared minus p squared.
It rejects q>r squared without writing outputs. Otherwise s=sqrt(r squared-q),
negated when p<s; it writes t0=p-s, t1=p+s and the corresponding O+tD points,
then fails if (first point-O) dot D is negative. The wrapper then:

1. Returns false if the callee failed
2. Returns false if both signed distances are negative
3. Returns true if t0 is nonnegative and t1 is negative
4. Otherwise returns whether t0<L

For ordinary finite unit-direction inputs, step 3 handles an origin inside
the sphere, and an origin on its surface facing outward, accepting even when
L is zero or negative. There is no length validation. The first output is the forward exit in this case, so outputs are
not always near/far ordered. They are sphere-surface points, not clipped
segment endpoints, and may already have been written on a false result.
Neither helper normalizes D, adds an epsilon, validates finite inputs, or
promises arbitrary pointer-overlap safety. Negative radius is squared.

## Closest point on a segment

Inputs are start O, endpoint displacement D, query P, output Q and optional
scalar t. Raw `1514563C` computes t=(D dot P-D dot O)/|D| squared and Q=O+tD.
The wrapper changes Q to O for t<0 and O+D for t>1. The optional scalar stays
unclamped. If the computed squared length is exactly zero, Q becomes O and
the optional scalar remains untouched. D is neither the second endpoint nor
necessarily a unit vector. No epsilon/finite checks or overlap guarantee are
added. Original `15102EB8` constructs a scaled endpoint-minus-start vector
and calls this helper at `15102FF8` before comparing Q with the query.

## Degree angles and interpolation

`15145974` returns yaw through its required output pointer and optional pitch:
yaw=atan2_lut(x,z)*K; pitch=atan2_lut(sqrt(x*x+z*z),y)*K-90. Both original
constants at `800A56BC/800A56C0` are 0x42652EE0 (57.2957763671875), establishing
degrees. The original LUT atan helper `150484A0` returns a nonnegative turn.
Yaw runs from +Z toward +X; pitch is negative toward +Y and positive toward -Y.
The zero vector produces yaw 0 and pitch -90 when requested. There is no
normalization or finite-input/aliasing safeguard. Callers include transformed
vectors at `1501453C` and a triangle-derived normal at `151C91DC`.

`15048720` takes (fraction, start, target) and returns start plus fraction times
`15048A70`'s [single-wrap degree delta](trig_angle_helper_semantics.md). It does
not normalize angles, clamp fraction or wrap the result. Normalized endpoints
follow the shortest arc, with half-turn ties choosing -180; unrestricted
inputs need not. For example, (1,0,720) produces 360 because the delta helper
corrects only once. Original calls `151282C4/15128328/1512833C` use the same
transition fraction as coordinate interpolation; the first result is then
multiplied by the original pi/180 constant. Raw `15048758` remains unchanged.

## Scaled semicircle-profile lookup

Exact behavior is table[trunc(arg0*arg2*100)]*arg1. The 101 reviewed samples
from `800A548C` approximate sqrt(1-(i/100) squared); indices 0..99 have maximum
absolute error below 4.65e-6. Original index 100 is about 0.001145, not zero;
its design intent is unproven and no idealized formula replaces it. The helper
does not take absolute value, clamp, interpolate or validate the index.

Original caller `151CB110` supplies (abs(v),1,1) at `151CB214`, then
(abs(x),first_result,1/first_result) at `151CB2B4`, supporting scaled circular
profile sampling. The 404 reviewed data bytes have SHA-1
`bc34db493962b43b2f8cf879abea5f402d0e68e6`; this does not establish a larger
allocation boundary or make out-of-range indices valid.

## Evidence and acceptance

All 732 registered target bytes were checked against the checksum-validated US
ROM, along with the original intersection, projection, atan and delta callees
and the cited constants. References are original `141970.s`, `484A0.s`,
`48720.s` and `489B0.s` plus their caller families.
