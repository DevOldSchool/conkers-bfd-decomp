# Vector, quaternion and translation/rotation helpers

Nine existing matched C helpers use source-local descriptive aliases. Numeric
linked symbols, signatures, structures, operation order and registered spans
remain unchanged. The two mixed source units retain all deferred members.

| Symbol | C name | Span |
| --- | --- | --- |
| `150442C0` | `matrixf_add_basis_translation` | `0xB0` |
| `15048B10` | `matrixf_build_inverse_translation_rotation` | `0x120` |
| `15048F20` | `vec3f_add` | `0x38` |
| `15048F58` | `vec3f_subtract` | `0x38` |
| `15048F90` | `vec3f_displacement` | `0x38` |
| `15049148` | `vec3f_scale` | `0x34` |
| `1504917C` | `vec3f_normalize_or_zero` | `0x70` |
| `150491EC` | `vec3f_direction_between_points_or_zero` | `0x74` |
| `15049C40` | `quaternion_align_hemisphere` | `0x78` |

## Three-component vectors

The arithmetic helpers read/write floats at offsets 0, 4 and 8. Addition stores
second plus first in the third argument. Subtraction stores first minus second;
displacement instead stores second minus first. Scale multiplies each input
component by its scalar and writes the third argument. Existing void pointers
and the scalar's integer-register ABI remain unchanged.

At `1512EB78`, the original caller builds a normalized direction between two
points, then projects/scales a displacement and adds it at `1512EBA4`.
Reflection code at `150E20B0` uses first-minus-second subtraction after scaling
a normal by twice a dot product. Caller `150F6B74` forms second-minus-first,
measures it and normalizes it at `150F6B98`. Matrix decomposition scales rows
by reciprocal length at `1503E6D0`. These are generic numeric operations,
without a character, world-unit or coordinate-handedness claim.

`1504917C` obtains sqrt(x*x + y*y + z*z) through `150AD930`. A nonzero result
becomes its reciprocal; a zero result remains the multiplier for all three
output components. It has no epsilon or special NaN/infinity/overflow/underflow
protection. Preserve the old-style declaration and argument-less call: the
original instructions at `15049184..1504918C` retain incoming `a0` for the
length callee. Naming does not repair that reconstructed C calling convention.
`150491EC` forms second-minus-first directly in the destination, then invokes
that normalizer in place.

## Quaternion sign alignment

`15049C40` computes a four-component dot product and negates the second
argument in place only when the result is strictly negative. It normalizes
neither input; zero or unordered comparisons do not select the negation.
The quaternion role follows original caller `15038620`: matrix conversions
at `150397B0/150397BC`, this helper at `150397C8`, interpolation at `150397DC`,
and conversion back at `150397E8`. No component-order claim is required.

## Matrix operations and limits

`150442C0` adds x*row0 + y*row1 + z*row2 to row3 xyz, writing only offsets
`+0x30/+0x34/+0x38`. Basis and fourth-column elements are unchanged. Original
caller `151134A8` supplies an offset after constructing a diagonal scale matrix
at `1511347C`, so a normalized or rotation-only basis must not be assumed.
The corresponding disabled caller C remains supporting evidence, not a match.

`15048B10` decomposes the input into translation, Euler angles and scale through
`1503E5F8`. It constructs negative translation and calls the rotation builder separately
for negative X, Y and Z angles. The composition call chain combines negative
translation with Z, then Y, then X. Extracted scales are unused:
this is not a general matrix inverse. Original caller `1503366C` supplies a
selected 0x40-byte transform and later composes the result with another matrix.
The decomposition's radians-to-degrees constant at `8009891C` is approximately
57.295776; the rotation builder's inverse unit conversion at `8009F6C0` is
approximately 0.017453292. Padded locals, casts and declarations stay intact.

## Full-span evidence

Original references `442C0.s`, `48B10.s` and `49C40.s` support all 1,032 target
bytes, independently checked against the checksum-validated game image.
`150442C0` retains three registered zero words at `15044364/368/36C` beyond
its `0xA4` ELF symbol size. `150491EC` similarly retains `15049254/258/25C`
beyond its `0x68` symbol size. Full registered spans, not symbol sizes alone,
gate the naming edits. Static caller evidence does not establish gameplay
activation or complete indirect-call coverage.
