# Bounded US scene fields

This batch reconstructs 34,702 physical bytes in bank 0C, alongside the separately
verified 170,856-byte trigger/sphere batch. Only fields consumed by authenticated
native code receive credit. Other bytes, including zero-valued fields with no
established role, remain in preserved backing and the unmatched denominator.

| Child | Records | Native stride | Regenerated fields | Bytes |
| --- | ---: | ---: | --- | ---: |
| 2 | 511 | 68 | position, rotation, scale | 12,264 |
| 4 | 511 | 24 | member count and typed references | 2,398 |
| 6 | 438 | 24 | spawn position, view selection/position, heading, options | 10,074 |
| 8 | 337 | 24 | view position and three view parameters | 6,066 |
| 10 | 975 | 4 | sprite selection and flags | 3,900 |

## Original consumers

`func_150039E0` loads bank 0C child 2 as 68-byte model-placement records.
It converts signed position halfwords at 0/2/4 to runtime position 16/18/20,
rotation halfwords at 6/8/10 to runtime float angles 0/4/8, and stored scale
floats at 32/36/40 to runtime scale 44/48/52. `func_150045C4` uses
`func_1511490C` to form the draw matrix and transform model vertices.
`func_151148A8` constructs rotations from those angles via `func_150A8050`;
`func_150A7CB0` places the scale factors on the matrix diagonal. This proves
field roles and conversion paths, not bit-exact emulation of native trig.
The other 44 bytes of each placement record remain uncredited.

`func_15017578` loads child 4 with a 24-byte stride. `func_150174C0` reads
member count at halfword 2 and references from halfword 8 onward. A reference
contains a high-nibble kind and a 12-bit index; kind 2 receives the static
model-count offset at relocation. `func_1508ECC0` looks up linked members;
`func_1508EE0C` routes kind 2 to model handling and kind 3 to sphere handling.
`func_15113E54` traverses model links. The codec derives count from the member
list; unused reference slots and the header/state fields stay raw.

`func_15016690` loads child 6 with a 24-byte stride. `func_15084D70` selects
spawn records, uses signed XYZ halfwords at 0/2/4, and copies the view selector
and heading bytes 6/7, three view-position floats 8/12/16, option byte 20,
and signed transition/alternate-spawn bytes 21/22. `func_1507DFE4` converts
the heading for the spawn call. Byte 23 remains unexplained and uncredited.
The exact gameplay meanings of the option and transition values are not inferred.

`func_15005290` loads child 8 with a 24-byte stride. `func_15096A68` converts
XYZ halfwords 0/2/4 to a view packet and copies float slots 12/16/20 to the
packet's three view parameters. Bytes 6 through 11 stay raw; these contain
nonzero values in some records and have no established interpretation here.

`func_1500ABA0` loads the 60-byte child 10. `func_1500AC14` loads resources
for its fifteen sprite selections. `func_1500BEC0` passes each record's two
unsigned halfwords to `func_1500AD84`, which handles sprite selection,
stores low flag bits and handles bit 7 through a separate mask. All original
flags are zero, but their field and native consumer are independently proved.

The manifest pins 25 complete registered native spans, including shared archive
loaders. The builder checks the normalized US ROM SHA-1, explicit scene/child
selection, archive flags, record extents and exact YAML bank ownership.

## Reconstruction and evidence

`./conker scene-fields build` preserves editable `records.json`, checked
`manifest.json` and `backing.bin` under `build/assets/scene-fields/us`.
It regenerates selected slices from named values, checks their independently
reviewed extents and digests, and combines them with the existing volume
sources into the actual `asset_bank_0c.o` input. Both source families must be
valid and unchanged before publication. Explicit recovery backs up edited inputs.
Missing source files fail; normal rebuilding never silently restores them.

Native objdiff freshly encodes fields, checks the entire actual linked bank,
and compares only regenerated slices with independent original ROM ranges.
The new unit is `assets/scenes/fields`; `assets/scenes/volumes` retains its
existing sources, ranges and proof. No source dump or unused field receives credit.

The independent audit reads every selected native field directly by offset,
mutates every field component in each child's first and last records, checks
unknown bytes are preserved, and rejects mutations at both endpoints of all
25 native consumer spans. The adjacent JSON records counts and source preservation.
Focused tests also cover missing/edited inputs, recovery, concurrent changes,
linked-object disagreement and Make dependencies on both source families.

## Accepted checkpoint

The full US asset build reproduced all 67,108,864 bytes of the original ROM
(SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`) in 105 seconds.
The full Docker suite passed 2,587 tests in 132.974 seconds (8 skips). Native
objdiff, progress and whitespace gates passed. Matched Data increased by 34,702
to 62,163,625 / 65,120,512 bytes; code measures were unchanged. Prior asset
proofs and source hashes remained unchanged. Exact fingerprint/report hashes
and counts are recorded in the adjacent JSON for base commit
`094102644c4c2f5aefaa0fc4b609416918f66f58` plus these uncommitted changes.

The subsequent [model-control extension](us_scene_model_controls.md) preserves this
checkpoint and documents the version-2 child-2 schema and its additional coverage.
