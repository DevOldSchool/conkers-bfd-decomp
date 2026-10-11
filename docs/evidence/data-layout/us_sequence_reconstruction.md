# US compact-sequence reconstruction

The 149 compact sequences in bank `0x17`, entry 3, are reconstructed from
editable native event records. Their payloads total 684,228 stored bytes.
The S1 descriptor table and 232 bytes of inter-sequence padding retain their
original extraction path and do not receive reconstruction credit.

## Native format and consumers

The loader uses the S1 offset/length descriptors to select a sequence and calls
`func_80017F80` to initialize it. This path is documented in the
[audio runtime evidence](../assets/audio/us_non_mp3_audio_assets.md).
The decoder is the Conker implementation in
`lib/libultrare/src/libultrare/audio/n_csq.c`. Its complete 3,296-byte compiled
object was independently matched to ROM `[0x17F80, 0x18C60)` as recorded in the
[libultrare reconstruction evidence](../libraries/libultrare_us_audio_engine_reconstruction.md).
The sequence builder pins this whole object and the complete registered loader
functions at ROM `0x8180` (856 bytes) and `0x8CE8` (504 bytes).

Each sequence begins with sixteen big-endian u32 track offsets and a u32
division. Each active track contains delta times and typed events:

- MIDI messages retain explicit status bytes or running-status omission,
  one or two seven-bit data fields, and note-on duration when present. The
  native consumer replaces the status channel with the track index.
- Tempo events contain a u24 microsecond value. Loop-start events carry the
  Conker u16 marker value. End-of-track terminates the physical track.
- Loop-end events contain repeat count, current count and a u32 backward
  offset. These six bytes are physical reads, bypassing compressed byte reads.
  The codec parses the non-replaying path used by the native marker collector;
  it preserves the stored current count rather than simulating playback edits.

The native byte reader expands `FE distance:u16 length:u8` references into
previous physical sequence bytes and treats `FE FE` as a literal `FE`.
References are not recursively expanded. Records contain typed events and an
explicit list of logical reference positions, physical distances and lengths.
The encoder builds the logical bytes from event fields, emits references and
escapes literal bytes, then independently reparses the resulting payload to
require agreement with every record. A changed event that disagrees with a
retained reference fails; the encoder never substitutes an original stream.
Variable-length fields preserve their explicit encoded width, including
observed nonminimal leading continuation bytes.

All 1,287 active tracks parse to their exact descriptor-defined ends, containing
297,894 events and 29,952 references. No unexplained header gaps, physical
suffixes or partially consumed references are admitted. Loop physical fields
cannot overlap an active reference. Opaque byte fields are rejected.

## Build and native Data path

Run `./conker audio-assets build-sequences`. Each reviewed sequence receives
`manifest.json` and `sequence.json` under
`build/assets/sequence-build/us/<index>/`. Generated records remain private and
ignored. Missing complete folders initialize from the reviewed ROM. Partial,
malformed or changed inputs fail without replacement. Explicit recovery is
`./conker audio-assets recover-sequence --entry <decimal-index>`; it retains
the entire former input directory under the ignored recovery path.

The builder checks the US ROM checksum, consumer spans, YAML extents, complete
record encoding and independent original bytes. It publishes parts only after
the complete batch passes. Make uses those parts for the actual ROM linker
objects under `build/us/assets/audio/bank17/sequences/`, retaining original
asset ordering. Index and padding targets are excluded from these recipes.
Edited inputs, missing manifests, missing records and missing parts invalidate
the packer; unchanged outputs preserve their modification times.

Native objdiff preparation takes the actual linker object as the candidate,
rebuilds a separate original-ROM reference, and verifies candidate bytes against
current source records. Source and linker hashes must remain stable through
report validation. The 149 payload extents are subtracted once from the raw
bank-17 storage span. Decoded MIDI events do not add to the denominator.

## Initial validation

The production builder reproduces all 149 sequences exactly. Focused tests
cover running status, variable-width deltas and durations, escaped literals,
physical loop fields, reference consistency, malformed values, source
preservation and recovery, descriptor/YAML disagreement, independent targets,
actual candidate objects, and Make invalidation. Six consumer endpoint
mutations are rejected. All 149 division edits change reconstructed bytes;
1,204 of 1,277 event edits change bytes and the other 73 correctly fail because
the retained reference plan no longer agrees with the edited events.

Per-sequence ranges, hashes and event counts are in
[the sequence inventory](us_sequence_reconstruction.json). Full ROM and native
report acceptance are recorded below.


### Build acceptance, 11 October 2026

All 16 sequence tests, 23 asset-Make tests and 27 report tests pass. The full
Docker suite runs 2,395 tests with eight skips and no failures. The production
builder and independent source audit reproduce all 149 payloads from 298
editable input files. All 149 actual linker objects independently contain the
same 684,228 original ROM bytes.

`./conker build --assets` passes. Independent comparison confirms all
67,108,864 output bytes equal the original US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The separate native report acceptance below establishes Data credit.

Private logs and byte/linker audits are `build/sequence-*`.


### Native report acceptance, 11 October 2026

A fresh `./conker objdiff report` validates 8,583 units without compile errors.
All 149 sequence units are fully matched and complete, totaling 684,228 bytes.
Matched Data is 9,915,796 / 65,120,512 bytes (15.226839%); complete Data is
9,915,028 bytes (15.225660%). Both counts gain exactly 684,228 bytes.

Every prior unit retains its measures except the unreconstructed bank-17 span,
which loses precisely those payload bytes. Sequence index and padding remain
uncredited. Code measures and the Data denominator are unchanged. Source,
editable input and linker-object hashes validate as a `current` snapshot.
Canonical progress and whitespace checks also pass.

Source fingerprint:
`234755355bdb73aae62a4fb0d18e49fe1978bcdde08b02358d45668bd4bc4100`.
Native report SHA-256:
`a743f785b1ce9dc1256ae442cb7e8445c499c7d120858a1eaa09abf81f27a0a1`.
