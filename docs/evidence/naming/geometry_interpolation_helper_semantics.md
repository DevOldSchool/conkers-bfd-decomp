# Geometry and cubic interpolation helpers

Source: `game_16EE20.c`. Generic geometry and interpolation roles, without
actor, effect or scene identities.

| Symbol | C name | Span |
| --- | --- | --- |
| `15142838` | `matrix_fixed_build_xz_y_scaled_transform` | `0xDC` |
| `15142914` | `matrixf_build_xz_y_scaled_transform` | `0xCC` |
| `15142A80` | `cubic_lagrange_weight_minus_one` | `0x40` |
| `15142AC0` | `cubic_lagrange_weight_zero` | `0x44` |
| `15142B04` | `cubic_lagrange_weight_one` | `0x40` |
| `15142B44` | `cubic_lagrange_weight_two` | `0x38` |
| `15143E64` | `vec3f_length` | `0x30` |
| `151450B4` | `vec3f_cross` | `0x74` |
| `15145128` | `vec3f_normalize_checked` | `0xC8` |

## Transform builders

Both builders call `150A8050` with three Euler angles, set translation in row3
xyz, scale rows0/2 xyz by the first scale and row1 xyz by the second. The fixed
version builds a local float matrix and packs it through `150A7790`; the float
version writes directly to the destination. They preserve two independent
scales, unlike the separately scaled XYZ builders already named in
`game_71240.c`. The degree-to-radian constant at `8009F6C0` is approximately
0.017453292. Fixed conversion uses `cvt.w.s`; no truncation claim is made.

The fixed builder's original call at `151337A0` supplies object scales, rotation
and position. The float builder's call at `150AE440` is followed by use of its
result to transform a position at `150AE46C`. No handedness, inverse-transform
or orthonormal-basis contract is introduced.

## Four cubic Lagrange basis weights

The weights correspond to interpolation knots -1, 0, 1 and 2, respectively:

- `(1-t)*(t-2)*t/6`
- `(t+1)*(t-1)*(t-2)/2`
- `(2-t)*(t+1)*t/2`
- `(t+1)*(t-1)*t/6`

ROM words `800A5624/800A5628` both contain `0x3E2AAAAB`, the float
approximation to 1/6. Original caller `150E7994` calls all four at
`150E7B90..150E7C18` and combines them with four two-component control points,
sampling t from -1 toward 2 with step `3/(count-1)`. The existing float
multiplication grouping and constant loads are retained; the functions do not
clamp t or validate a caller's control-point count.

## Vector operations

Length reads three float components and returns `sqrt(x*x + y*y + z*z)`.
Original caller `15081C20` constructs displacement vectors and measures them
at `15081D9C/15081DE0`. It adds no overflow, underflow or finite-value protection.

Cross writes first-input cross second-input in three sequential stores.
Original `15144E80` uses it twice to construct perpendicular vectors from
triangle edges; calls `151D51C8/151D51D8` form another paired cross-product
chain. Output overlapping either input is not promised to be safe.

Checked normalization tests computed squared magnitude for exact zero. That
case returns zero without changing the destination or optional magnitude and
reciprocal outputs. Otherwise it returns one, writes the normalized vector,
and optionally writes magnitude and reciprocal magnitude. Original caller
`150F4570` supplies both outputs at `150F45CC`, checks failure and then uses
the returned magnitude. "Checked" means this exact-zero test only, without an
epsilon or NaN/infinity protection. Preserve the original write order and
pointer contracts; arbitrary overlap among the output pointers is not promised.
This differs from the already-named `vec3f_normalize_or_zero`.

## Full-span evidence

All 1,040 registered bytes in original reference `141970.s` agree with the
checksum-validated US game image. Existing source-group boundary evidence is
in [the callback helper audit](../game_state_callback_helper_groups.md).
Deferred callers support roles, not runtime activation.
