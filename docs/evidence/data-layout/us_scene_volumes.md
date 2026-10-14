# US scene trigger volumes and collision spheres

The bounded source reconstructs 85 populated child segments in bank 0C:
3,204 trigger volumes (166,608 bytes) and 177 collision spheres (4,248 bytes).
Only their 170,856 physical ROM bytes are credited. The 251,832-byte linker
bank remains exact; directories, other children and gaps remain raw storage.
The accompanying JSON records every selected range and full consumer digest.

## Native evidence

`func_15017930` loads bank 0C, scene index, child 5 and divides its byte length
by 52. `func_15017B20` initializes every record with `func_150A0D14` and builds
bounds with `func_15017FA4`. The latter reads signed XYZ at offsets 0/2/4,
shape dimensions at 6/8/10, rotations at 12/16 and the low two shape bits at
21. Shape-dependent geometry uses these values to generate transformed bounds.
The upper six bits at 21 select a behavior kind; byte 22 contains flags and
byte 23 a mode. Only observed low-four-bit flags are supported by this codec.

`func_150A09D0` dispatches behavior using the kind and mode. It consumes the
signed action value at 24, packed parameter at 28 and mutable state at 32.
For example, kind 2 passes the high half of the packed parameter, XYZ and
value to `func_1000FC18`; kind 7 uses the mode and values in event calls.
`func_150A0D8C` checks the disabled byte at 20 and consumes kind-6 strength
from offset 16. Thus the second rotation slot also has behavior-specific
union use; the source preserves its native float value without assigning a
single interpretation to all behavior kinds.

Offsets 36/40/44/48 are four working rotation-cache floats. The initializer
reads angles 12/16 and writes all four slots through the native trigonometric
helpers. Every selected stored record initializes them to positive zero.
The codec derives those initial zeros and rejects nonzero cache storage.
These slots are mutable runtime fields, not alignment padding.

`func_15004FE0` loads bank 0C child 3 and divides its size by 24. Each six-float
source becomes a 20-byte runtime sphere: XYZ truncate to signed halfwords;
radius squared becomes a word; X plus/minus radius produce broad-phase bounds;
the last two floats truncate to halfword parameters. `func_150379DC` checks
those bounds and squared-distance containment. A nonzero final activation
index calls `func_1507E9E8(index - 1)`. The other auxiliary field is preserved
as `response_parameter`; its exact gameplay role is not inferred here.
`func_1503DDD0` marks and removes runtime spheres. All six source floats are
finite. The selected radius is always 300 and both auxiliary values are zero.

The manifest authenticates complete registered instruction spans, including
terminal padding, for all nine named scene consumers and three shared archive
loaders. The builder also checks the original US ROM SHA-1, bank and child
flags, explicit scene/child selection and exact YAML linker ownership.

## Build and bounded reporting

Run `./conker scene-volumes build`. Editable `records.json`, a checked manifest
and `backing.bin` live under `build/assets/scene-volumes/us`. Each source record
has named typed fields; raw or unknown fields are rejected. Packing freshly
encodes every selected child, validates its exact size and digest, overlays
only those ranges, and compares the full bank with the independent ROM.
Missing, edited, invalid or concurrently changed inputs fail and remain intact.
Explicit `./conker scene-volumes recover` backs up the old directory first.

Make builds the actual `asset_bank_0c.o` from the reconstructed bank. Native
objdiff re-encodes current sources, validates the entire actual linker object,
and compares only freshly generated physical ranges with original ROM slices.
The remaining bank bytes stay in the raw-storage denominator.

The independent audit reads all 3,381 native records by offsets, checks every
initial cache, mutates fields in each child's endpoint records, and checks all
24 native consumer endpoint guards. It also checks the sphere loader's field
conversions and preserves every prior source hash. Focused schema, provenance,
recovery, Make and report tests cover source edits and omitted inputs.
Full ROM, full test suite and native-report acceptance are recorded below when
complete.

## Accepted checkpoint

At base commit `094102644c4c2f5aefaa0fc4b609416918f66f58` with the recorded uncommitted
source fingerprint, `./conker build --assets` reproduced all 67,108,864 US ROM bytes
(SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`) in 101 seconds.
The full Docker suite passed 2,579 tests (8 skips), native objdiff had zero
compile errors, and progress/whitespace gates passed. Matched Data rose by
170,856 to 62,128,923 / 65,120,512 bytes (95.406075%); code measures were unchanged.
All 10,679 prior asset proofs and 26,046 unique source hashes were preserved.
The exact report hash and source fingerprint are in the adjacent JSON evidence.
