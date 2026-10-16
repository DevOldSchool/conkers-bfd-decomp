# US native character animation reconstruction

This batch reconstructs **119 complete bank-02 entries, 3,752,256 stored bytes**,
from **2,539 descriptor/frame pairs and 54,355 source frames**. These bank
entries are uncompressed. Their native bytes enter the build directly after
reconstruction from typed records; no compressed stream or opaque frame blob
is an input. [The companion inventory](us_animation_reconstruction.json)
records every selected extent, hash, clip/frame count, excluded entry and
full consumer span. The original US ROM SHA-1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Native format and bounds

The [existing animation evidence](../assets/models/us_asset_inventory.md#rigged-character-model-geometry-and-animation-companions)
proves the paired eight-byte segment table, ten-byte descriptor header,
optional header halfwords, translation masks, rotation/scale descriptors and
MSB-first packed frame channels. `model_animation_build` preserves the signed
root-base bytes and unsigned remaining header bytes, explicit optional and
mask halfwords, and per-axis base/width/optional-scale fields. Byte nine and
optional words retain their native storage fields without invented semantics.
Frames rebuild signed joint-translation triplets and separate root, rotation
and scale offsets constrained by the declared bit widths. Segment offsets,
sizes and the final flag are derived from the rebuilt aligned parts.

Only observed zero descriptor/stream padding of at most seven bytes is
accepted. Unused low bits in the last packed channel byte must also be zero.
The native frame stride must equal all decoded channels: any per-frame tail,
nonzero alignment, undeclared channel, out-of-width value or uncovered storage
fails. Build inputs retain neither a source bitstream nor an opaque fallback.

Frame count follows descriptor duration and byte-eight keyframe spacing.
A generic duration of `0xFF` means **255 ticks**, as the runtime initializer
proves; it is not permission to decode the entire remaining segment as frames.
Entries `0x92` and `0xB7` through `0xB9` need separate character-specific duration
and route evidence and are deliberately excluded from this codec's reviewed
entry path. Entry 124's post-duration bytes remain raw. Entries 82 and 83
still have the previously documented truncated descriptor/frame-tail cases.
The other direct companion payloads remain raw; their table/stream format has
not been established here. Total unselected count is 26 out of 145 present
entries. The survey inventory records each exact rejection.

Four complete original code spans gate production reconstruction:

| Consumer | Address | Bytes |
| --- | --- | ---: |
| Joint/pose unit, including packed-channel decoder and continuation labels | `0x150A81D0` | 4,876 |
| Duration/stride frame transfer | `0x1502D824` | 764 |
| Zeroed descriptor initialization and duration overrides | `0x1505E0C4` | 1,420 |
| Paired segment relocation | `0x1503D484` | 140 |

These are full registered spans, not return-bounded snippets. The hand-written
channel decoder's internal labels remain covered by the entire joint/pose
unit. Endpoint mutations of all four spans fail the consumer hash guard.

## Independent reconstruction and build integration

All 54,355 frames agree with the existing independent native pose decoder for
root translation, joint translations, rotations and optional scales. **951**
first/last frame field mutations change the native stream and reparse to the
edited records: 396 rotation, 202 root, 168 scale and 185 translation mutations.
All eight consumer endpoint mutations are rejected. All 23,884 previously
verified asset source hashes remain unchanged.

The complete **4,052,696-byte bank** is reconstructed from selected native
entries plus explicitly raw index, gap and unresolved ranges. It equals the
original bank byte-for-byte, SHA-256
`1cefc77132fdf0815c0a3ed57f66fcdc9a8035f9fefa6b70ca28364b0b4f0bb7`.
`config/profiles/us/assets/models02.yaml` is checked against the original
indexed boundaries. The Makefile links the resulting native parts in bank
order, includes the new codec in reconstruction dependencies, and keeps
unchanged part/object timestamps stable. A separate native encoder contract
prevents bank 02 from selecting any RZIP compressor override.

The focused codec suite passes five tests and all 27 incremental asset build
tests pass. `./conker model-assets build --bank 2` independently verifies all
119 entries against their ROM slices. Full reconstructed-ROM, Docker-suite
and native-report gates follow below. Test base is main
`094102644c4c2f5aefaa0fc4b609416918f66f58` with this branch's uncommitted changes.
Private logs and audits use `build/animation-`; generated editable records and
rendered reports remain ignored.

## Full acceptance checkpoint

`./conker build --assets` reproduces all **67,108,864 US ROM bytes**, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The Docker suite passes **2,477
tests with eight skips** and no failures. Canonical progress and whitespace
checks pass. Build-wrapper elapsed time was 138 seconds, including setup,
SDK and Docker; the test runner recorded 150.947 seconds. These subprocess
measurements are not total workflow time or an isolated performance benchmark.

The native report validates **11,173 units**, has no compile errors, and has
a current source snapshot. Every one of the 119 animation units has identical
total, matched and complete byte counts. Matched and complete Data each gain
exactly **3,752,256 bytes**. Matched Data is now **36,775,589 / 65,120,512
(56.473125%)**; complete Data is 36,774,821 (56.471943%). Code measures and the
Data denominator are unchanged. Comparing all prior unit measures finds only
the expected reduction of `assets/storage/bank02/unreconstructed`; every other
existing unit is unchanged and none was removed. This is local evidence, not
a published decomp.dev update.

Source fingerprint:
`1b0b3ce27b1f15aa634011db9e34fecd6aee0b2514fe85ec4b397439b4caab5f`.
Native report SHA-256:
`e53ea2e4871b14994427fdf662e4e4e11e222e255a4fa1204d564218b7407dee`.
The tested base remains `094102644c4c2f5aefaa0fc4b609416918f66f58` with these
uncommitted branch changes.
