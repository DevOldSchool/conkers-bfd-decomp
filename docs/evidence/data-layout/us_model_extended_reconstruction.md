# Extended US scene-model reconstruction

Eight complete bank-04 bundles (`1, 4, 24, 33, 36, 53, 54, 64`) add **243,901
stored bytes** and **683,040 decoded bytes**. All eight freshly encode with
GNU gzip 1.12 level six. Their 134 nonempty parts include 26 newly supported
combinations of existing native fields: **101 referenced normal tables and
seven vertex-color descriptors**, plus primary or child face words and explicit
small zero intervals. [The inventory](us_model_extended_reconstruction.json)
records all stored/decoded hashes, extents, field counts, compression trials
and remaining exclusions. The US ROM SHA-1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Format evidence and boundaries

The [existing normal contract](us_model_reconstruction.md#normal-table-expansion)
proves `DC38000E` addresses as 64-byte tables containing 32 signed XY pairs.
The new codec requires the unique referenced tables to cover the entire normal
region contiguously after the primary display commands. A secondary header
pair may be empty or name exactly that referenced normal region. An unexplained
secondary array, unreferenced normal-sized region, overlap or gap remains
unsupported. Signed Z remains in the vertex flag; no preview normalization
enters stored data.

The [existing color-animation contract](us_model_reconstruction.md) supplies
native RGB triplets, vertex-index halfwords, twelve-byte descriptor rows and
the zero sentinel. The codec now accepts these fields in child models as well
as the primary model, and represents each observed small zero interval by its
explicit offset/length (at most twelve bytes). No nonzero tail is retained.
The selected primary and child suffixes include eight and twelve bytes;
internal color alignment includes one, two and three bytes.

Primary face tables retain their two-word header and existing collision
validation. Child tertiary tables must contain one unsigned word per decoded
face and have no primary header. Their broader runtime meaning remains
unresolved; reconstruction does not rename them as collision allocations.
All model headers, vertices, display commands, normal pairs, color records and
face words reparse to the same declared native ranges after encoding.

Existing source schemas are retained. The extended schema is tried only when
an established bundle-part codec rejects the layout, then independently checks
all native regions. Encoding checks the primary/child role against the actual
bundle slot. Existing loader and surface-consumer pins remain; every extended
normal case additionally checks full `1503D368` (208 bytes) and `1503D438`
(36 bytes) spans. Every color-bearing part, including a child, checks full
`15003120` (204 bytes) and `151739B0` (688 bytes) consumers. The original ROM
checksum and existing CBFD microcode evidence still bind signed normal meaning.

## Independent checks

All **258 field endpoint mutations** change the complete native part and
reparse exactly: 202 normal pairs, 14 RGB records and 42 face words. All eight
normal/color consumer endpoint mutations fail. All **24,122** prior editable
asset source hashes remain unchanged. An initial audit-script error assumed
every legacy record had a format tag; using its optional tag fixed that audit,
and the complete audit was rerun successfully.

Reconstruction of the whole **1,793,096-byte bank** is byte-identical to ROM,
SHA-256 `3b964924c1e014d5f28e70b1ee89b602a88fd03cc1d89397690ff05756ea6ce2`.
The production bank build verifies all 38 selected bundles, **1,085,871 stored
bytes and 499 nonempty parts**, against independent original slices. All 68
focused model-build tests pass, including the five new mutation, boundary,
role and consumer tests. Full ROM, Docker-suite and native-report results
follow below. Logs use `build/extended-`.

Entries 7 and 29 now reconstruct their decoded records fully, but zlib levels
six/nine and GNU gzip levels six/nine all fail stored equality; they remain
unselected. Entries 5, 8, 32, 34 and 37 retain secondary regions without normal
references, and entry 58 retains an unaccounted child region. Their bytes stay
raw and receive no new matching credit. Previously exhausted compression
candidates were not retried.

## Full acceptance checkpoint

The reconstructed **67,108,864-byte US ROM** is byte-identical to the original,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The asset build wrapper
recorded 101 seconds including setup, SDK and Docker. The complete Docker
suite passes **2,482 tests with eight skips** and no failures (115.154 seconds
in the runner). These are subprocess timings, not total workflow duration.
Canonical progress and whitespace checks pass.

The fresh native report validates **11,181 units**, with no compile errors and
a current source snapshot. All eight new units have equal total, matched and
complete counts. Matched and complete Data each gain exactly **243,901 bytes**.
Matched Data is **37,019,490 / 65,120,512 (56.84766%)**; complete Data is
37,018,722 (56.84648%). Code measures and the Data denominator are unchanged.
Among prior units, only `assets/storage/bank04/unreconstructed` changes, by the
expected reduction. No prior unit is removed. Total gain from the starting
main checkpoint is **4,963,337 matched bytes**. Results remain local.

Tested base: `094102644c4c2f5aefaa0fc4b609416918f66f58` plus these uncommitted
branch changes. Source fingerprint:
`88205f89016bdc8688cf24642e05d87efdddd001c9ba8f19d92b1de5a877685a`.
Native report SHA-256:
`572735d0bdd60f26c7715a22ecf8b1f16f6b668408397e28e489790cdc6fb5da`.
