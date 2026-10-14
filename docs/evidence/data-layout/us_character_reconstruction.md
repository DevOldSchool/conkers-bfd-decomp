# US native character reconstruction

Follow-up: [EOF-bounded compression](us_bounded_compression.md) extends the
selection while preserving the historical validation recorded below.

This batch adds 171 complete bank-01 character containers: **667,138 stored
RZIP bytes** and **1,496,952 decoded bytes**. Each source record has typed
native fields, then independently reproduces the entire decoded and compressed
ROM extent. [The companion inventory](us_character_reconstruction.json) records
all selected entries, original extents, hashes, encoder choices and consumer
spans. It uses the checked US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Format and consumer evidence

The existing [native model inventory](../assets/models/us_asset_inventory.md#rigged-character-model-geometry-and-animation-companions)
and [character format guide](../../rzip-assets.md#character-containers-and-animation)
prove the 56-byte header's seven offset/size pairs. The source representation
rebuilds fourteen header words, signed native vertices/UVs, unsigned flags/RGBA,
vertex-boundary words, primary/alternate display-list pointers, paired display
commands, 16-byte joints, 12-byte texture descriptors, signed XY normal pairs,
and the optional procedural-joint byte pair. Joint pivots remain native f32
values; the codec never bakes a preview transform into stored vertices.

`model_character_build.verify_consumers` pins the full registered US loader
(`1503CF20`, 1,096 bytes), descriptor initializer (`1503DC3C`, 224 bytes),
joint/pose consumer (`150A81D0`, 4,876 bytes), normal scanner/relocator
(`1503D368`, 208 bytes; `1503D438`, 36 bytes), and procedural-index consumers
(`1503DA3C`, 96 bytes; `15034860`, 1,620 bytes). The inventory records SHA-1
for each full original code span, and production reconstruction verifies them.

Every region must occupy its declared range without overlap. All remaining
intervals must be observed zero storage of at most 15 bytes, represented by
explicit offset/length records. Empty sections stay empty. Both display-list
passes retain original command words and pointer offsets. Native parser checks
still require valid joint indices, descriptor relationships, normal sources,
and display-list termination. No opaque regions, original compressed streams,
or preview geometry enter the candidate.

## Selection and integration

The pilot reconstructs all 183 decoded bank-01 entries exactly (1,742,936
bytes). Fresh pinned compression admits 171: 13 zlib level-nine, 140 zlib
level-six and 18 GNU gzip 1.12 level-six. Selection tries no fallback at build
time. Entries 26, 33, 58, 83, 84, 93, 118, 146, 150, 151, 159 and 180 remain
unmatched because none of those encoders reproduces their stored stream.

`config/profiles/us/assets/models01.yaml` partitions the original 774,792-byte
bank into reviewed containers and preserved raw index/gap/unselected ranges.
The Makefile uses these exact parts for reconstructed ROM builds; its ordinary
original-assets path remains available. A dedicated codec dependency causes
changes to the character packer to invalidate the bank's reconstruction stamp.
Actual rebuilt link objects and independent ROM targets enter native objdiff
through the existing model-asset path, with full source and object hash checks.
Decoded bytes add no separate Data allocation.

Independent reconstruction reproduces the complete bank, SHA-256
`75a654d86e8ce5b8c0df6f13a1814a95423a28d5cc44e5e769cc1eb4a3aff61d`.
All 851 first/last vertex/normal and joint-pivot mutations produce different
native bytes and reparse to the edited records. All 14 endpoint mutations of
the seven pinned consumers fail verification. Joint mutations use exactly
representable f32 values; an initial arbitrary float addition was correctly
rejected by the encode/reparse equality guard.

The focused character suite passes four tests. Production reconstruction
verifies all 171 containers against their independent original ROM bytes.
Full reconstructed-ROM, Docker-suite and native-report acceptance follows
below. Work is based on main `094102644c4c2f5aefaa0fc4b609416918f66f58` plus
this branch's verified child-table batch; logs use `build/character-`.

## Full acceptance checkpoint

The reconstructed 67,108,864-byte US ROM is byte-identical to the configured
original, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The Docker suite
passes **2,471 tests with 8 skips**. Canonical progress and whitespace checks
pass. An initial full-build failure exposed the remaining raw bank-01 entry in
`ASSET_BINS_us`; replacing it with the explicit model partition fixed the
link-object mismatch, and the full build and all following gates were rerun.

The native report validates **11,054 units**, has no compile errors, and its
source snapshot is current. All 171 new units have identical total, matched
and complete byte counts. Matched Data rises by exactly **667,138 bytes** to
**33,023,333 / 65,120,512 (50.711105%)**; complete Data is 33,022,565
(50.709927%). Code matching and the Data denominator are unchanged. All
23,542 previously verified asset source files retain their prior hashes.
The additional bounded GNU gzip level-nine trial reproduces none of the
12 remaining character streams, which stay raw and receive no new credit.

Tested base: `094102644c4c2f5aefaa0fc4b609416918f66f58`, with the uncommitted
branch changes. Native source fingerprint:
`deadf310224f503e43ba0285b92bfb9d512b23bc35231b7635d73ec5885e1f60`.
Report SHA-256:
`1d115604dbf2af013715d80fd809d3cbabe5de405e3be9e0882225eef21cd472`.
These are local verification results, not a published decomp.dev update.
