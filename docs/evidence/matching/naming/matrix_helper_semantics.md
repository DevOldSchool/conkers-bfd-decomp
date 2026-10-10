# Matrix construction and translation helpers

Source: `src/done/game/game_71240.c`; naming retains the accepted `f32`
rotation-argument contracts.

| Symbol | C name | Complete span |
| --- | --- | --- |
| `15043D90` | `matrix_fixed_build_scaled_euler_transform` | `0xD8` bytes |
| `15043E68` | `matrix_fixed_build_euler_transform` | `0x60` bytes |
| `15043EC8` | `matrixf_scale_basis_and_set_translation` | `0xA4` bytes |
| `15043F6C` | `matrixf_build_scaled_euler_transform` | `0x84` bytes |
| `15043FF0` | `matrix_fixed_get_translation_signed_fraction` | `0xB0` bytes |
| `150440A0` | `matrixf_build_look_at_pose` | `0x220` bytes |

## Construction and conversion

`15043D90` and `15043E68` initialize rotation through `150A8050`, set
translation at float-matrix `+0x30/+0x34/+0x38`, and convert through `150A7790`.
The latter multiplies all sixteen floats by 65536 and packs their high/low
halfwords into the N64 fixed-matrix layout. The scaled builder additionally
multiplies each three-component basis row by its corresponding scale.
`151669A0` chooses the scaled builder at `15166AB0` or the unit-scale builder
at `15166AE4`. Integer destination addresses are preserved. The third rotation
argument uses the accepted `f32` contract, matching `150A8050` and `150A9B0C`;
the earlier `volatile s32` float-bit representation was superseded by the
source-quality cleanup on main.

`15043EC8` changes an existing float matrix: it overwrites translation and
scales the three basis rows. It neither initializes rotation nor writes the
fourth-column values at `+0x0C/+0x1C/+0x2C/+0x3C`. Caller `1503CE7C` first
builds a look-at pose through `150440A0`, then applies this helper at `1503CEA0`.

`15043F6C` obtains a scaled rotational basis from `150A9B0C`, writes translation
and supplies the affine fourth column `0,0,0,1`. Caller `150BF654` supplies
rotation floats from `+0/+4/+8`, scales from `+0x2C/+0x30/+0x34`, and signed
position halfwords from `+0x10/+0x12/+0x14`, before composition through
`150A7A48`. The two rotation callees `150A8050` and `150A9B0C` have different
Euler compositions; the float and fixed builders are not interchangeable.
No additional angle-order convention or shared ABI is introduced.

## Translation extraction and look-at pose

`15043FF0` computes each output axis as a signed halfword from
`+0x18/+0x1A/+0x1C` plus a signed halfword from `+0x38/+0x3A/+0x3C` divided
by 65536. All six original loads are `lh`: the low half is not decoded as
unsigned. The name preserves this behavior without claiming a general correct
16.16 conversion. Caller `150533B4` supplies a selected `0x40`-byte matrix;
other direct sites are `15037BBC` and `1503AD58`. The helper itself has no
index/sentinel guard.

`150440A0` normalizes position minus target, then `up` cross that backward
axis, then backward cross side. It writes the side/up/backward basis rows,
position directly as translation, and the affine fourth column. This is a
pose transform, not an inverse view matrix. `1503648C` builds an actor matrix
that its caller subsequently scales; further direct sites are `1503CE7C` and
`150E5058`. Coincident points and parallel-up degeneracy remain unchecked.

## Span evidence

The independent reference `reference/game/us/asm/43D90.s` covers the complete
`[15043D90,150442C0)` interval, 1,328 bytes. Original instruction words agree
with the checksum-validated game image. `150440A0` has a `0x21C` ELF symbol
size, but its registered `0x220` span also includes the final zero word at
`150442BC`; comparisons must include it. Boundary/integration evidence remains
in [the source-group audit](../../boundaries/game/mapping/game_remaining_upstream_c_groups.md).
