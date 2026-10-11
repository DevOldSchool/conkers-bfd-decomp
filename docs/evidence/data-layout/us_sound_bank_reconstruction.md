# US B1 sound-bank reconstruction

The B1 control and 26 bounded external regions are rebuilt from typed native
records. They total 434,837 stored bytes: 4,885 bytes of freshly compressed
control and 429,952 external bytes. Twenty-five unexplained external spans,
656 bytes in total, remain raw inputs and receive no reconstruction credit.
ADPCM sample payloads remain outside this change.

## Consumer and format evidence

The [audio runtime evidence](../assets/audio/us_non_mp3_audio_assets.md) identifies
bank `0x17` entries 0, 1 and 2 as compressed control, external sound-bank data
and sample storage. The full loader function at ROM `0x8180` (856 bytes) is
pinned before reconstruction. The complete matched `audio/bnkf.o` object at
`0x128D0:0x12D80` proves the B1 revision, bank/instrument counts, encoded external
addresses, relocation bases, native sound/wave pointers and unpatched flags.
Its [reconstruction evidence](../libraries/libultrare_us_sequence_helper_reconstruction.md)
includes all seven functions and final object padding.

The complete matched `audio/n_load.o` object at `0x214F0:0x22040` is also pinned.
The native loader derives predictor-book size from order and predictor count,
copies the sixteen loop-history samples, and consumes sample offset, length,
loop start/end/count and signed book coefficients. See the
[audio engine evidence](../libraries/libultrare_us_audio_engine_reconstruction.md).
The source layouts in those matched objects agree with the typed graph parser.

Control contains a B1 header, one bank, 170 instrument addresses, the embedded
first instrument and its 1,762 encoded sound addresses. All 7,768 decoded bytes
are rebuilt, including four explicit zero suffix bytes. Fresh zlib level-nine
RZIP compression reproduces all 4,885 stored bytes; there is no stored-byte
fallback.

External records contain 169 instruments, 2,786 sounds, 2,786 envelopes, 2,786
key maps, 2,786 ADPCM wavetables, 2,786 predictor books and 491 loops. Native
record fields cover 399,840 bytes. Another 30,112 bytes are explicit zero gaps
of two, four or eight bytes between the referenced records. Nonzero gaps are
never emitted by the typed encoder and split the external candidates into
26 contiguous regions. All known reserved bytes and initial patch flags must
be zero. Counted arrays and signed native field widths are checked.

The wave-table word at `+0x14` remains neutrally named `conker_field_0x14`.
The native patcher explicitly clears it; 2,761 stored values are zero and 25
are 112. Reconstruction preserves this native field without assigning it an
unproven meaning. The 25 unexplained surrounding spans are separate exclusions,
not an extension of that field or a reason to copy them into candidates.

## Source, linker and report path

`./conker audio-assets build-sound-bank` reviews the checksum, complete consumer
spans, typed graph, exact profile partition and independently encoded bytes.
Editable `manifest.json` and `records.json` files live under
`build/assets/sound-bank-build/us/control/` and one directory per external
region's eight-digit hexadecimal offset. Generated records remain ignored.
Missing complete folders initialize from the reviewed ROM. Malformed or partial
folders fail without replacement. Explicit recovery,
`./conker audio-assets recover-sound-bank --part <control-or-offset>`, retains
the entire previous directory under the ignored recovery path.

The US profile now has 322 bank-17 splits. The external entry occupies 26 typed
regions and 25 raw exclusions in its original position. The boundary verifier
rechecks the entire bank against native descriptors and graph extents. Make
links typed control/region objects from freshly generated parts and keeps the
unknown spans on their ordinary raw extraction path. Missing inputs and parts
invalidate the packer; unchanged output preserves timestamps.

Native objdiff compares each actual ROM linker object with a separately built
original-ROM target. It rechecks editable inputs and linked-object hashes.
The 27 reconstructed extents are subtracted exactly once from bank-17 raw
storage. The 656 excluded external bytes, sample payloads, sequence metadata
and padding stay in the denominator with their existing reconstruction status.

## Validation

The production builder reconstructs all 27 parts exactly. A repeated private
candidate build preserved all source and output modification times. All 136
native field mutations changed rebuilt bytes; all six consumer endpoint
mutations were rejected. Tests cover array counts, reserved fields, typed
values, gaps and overlaps, unknown-byte exclusions, fresh compression, source
preservation, recovery, actual objdiff candidates and Make invalidation.

The [part inventory](us_sound_bank_reconstruction.json) records exact bounds
and hashes. The full Docker suite passed 2,409 tests with eight skips. All 27
actual linker objects reproduce their original bytes, and the full 67,108,864-byte
US ROM is identical (SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`).
All 1,412 existing model and sequence source files retained their hashes.

The fresh native report contains 8,610 units with no compile errors. All 27
sound-bank units match completely, adding exactly 434,837 matched and complete
Data bytes. Only the unreconstructed bank-17 unit shrinks; every other prior
unit, Code measure and the 65,120,512-byte Data denominator remains unchanged.
Matched Data is 10,350,633 bytes (15.894582%); complete Data is 10,349,865 bytes
(15.893403%). The source snapshot is current.

- Source fingerprint: `7090d3ebfdb3a8572329b2d6867b05c870f4b56d818283ca66c89a82d6b36187`.
- Report SHA-256: `a7598fd920493a2fef7ebaf2c6656b2bb52c0375cdd661e3040b92cab72f278e`.

Private logs and audits are under `build/sound-bank-*`.
