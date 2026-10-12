# US ADPCM reconstruction from PCM16

This records the validated first PCM16 frame batch. The later
[complete sample reconstruction](us_adpcm_complete_reconstruction.md) adds
pre-saturation headroom and zero alignment, replacing the frame partition with
complete sample units. The acceptance values below describe the first batch.

The PCM encoder rebuilds 21,691,971 stored bytes across 2,690 complete-frame
regions from 2,258 native samples. This includes 2,143 complete runtime payloads
and 547 matching frame runs in the remaining 115 samples. The original sample
entry occupies 21,705,520 bytes. Its other 13,549 bytes remain raw and uncredited:
5,418 bytes of ambiguous frames plus 8,131 bytes of sample tails and storage gaps.

## Native evidence and encoding inputs

Bank `0x17` entry 2 stores samples referenced by the B1 graph. The full control
loader, bank patcher and native audio loader spans are pinned by the
[sound-bank reconstruction](us_sound_bank_reconstruction.md). The matched
`audio/n_load.o` consumes the sample offset, predictor book and length rounded
down to a multiple of nine bytes. Its ADPCM frame contains one scale/predictor
header and sixteen signed four-bit residuals. Books contain signed coefficients
indexed by predictor and order. See the
[audio engine evidence](../libraries/libultrare_us_audio_engine_reconstruction.md).

Each source directory contains a mono PCM16 WAV, a semantic encoding plan and a
manifest. The plan carries native scale/predictor pairs and the referenced book;
it contains no original residual bytes. The source context uses the first native
wavetable reference to each unique sample range, explicitly recorded in the
manifest. Multiple native references remain in the sound-bank graph.

The encoder derives residuals from the PCM samples, predictor coefficients,
prior decoded history and scale. Nonclipped samples use the inverse fixed-point
prediction equation. Clipped vectors use a bounded search for the first signed
residual solution in lexicographic order. Every residual nibble is freshly
packed. There is no original-frame fallback.

Clipping can erase information: multiple residual vectors can decode to the
same saturated PCM16 values. The canonical encoder differs from original bits
in 602 nine-byte frames across 115 samples, while decoding to identical PCM.
Those frames are explicitly excluded by
`config/adpcm_reconstruction.us.json`. Their adjacent matching runs are complete
native frames, not selected individual bytes. The encoder processes each whole
sample before selecting its reviewed regions, so history remains continuous.

The entire PCM payload and native encoding plan are checked against the reviewed
source context, including excluded frames. An edit to an excluded region cannot
silently pass. Changes to codebook context, frame parameters, sample format,
counts or selected bytes fail before publication. Original encoded ROM bytes
serve only as independent comparison targets and initialization of semantic
source fields.

## Source, linker and report path

`./conker audio-assets build-adpcm` validates the original ROM, complete consumer
spans, native graph and exact profile partition, then generates editable inputs
under `build/assets/adpcm-build/us/<sample>/`. Complete missing directories are
initialized; existing partial or invalid directories are preserved and rejected.
`./conker audio-assets recover-adpcm --sample <index>` backs up the entire source
directory before restoring reviewed inputs.

All samples must encode and all source hashes must remain stable before any
candidate part is published. Unchanged output preserves timestamps. Make links
fresh parts from `build/us/adpcm/parts/audio/bank17/samples/`; raw gaps continue
through ordinary extraction. Each complete-frame region has its own actual ROM
linker object and native objdiff unit. Shared PCM inputs are encoded once per
sample during report preparation, with hashes retained on every region.

The boundary verifier derives 5,104 sample-entry spans from native extents and
the reviewed exclusions. It rejects missing, overlapping or renamed regions.
Native report preparation compares actual linker objects with independently
wrapped original ROM targets, and subtracts reconstructed regions from raw
storage exactly once. The Data denominator is unchanged.

## Validation

The private candidate builder reproduced all 2,690 regions exactly. The full Docker suite passed
2,427 tests with eight skips and no failures. New tests cover fresh residuals,
clipping, native widths, complete frames, raw exclusions, WAV formats, source
preservation, recovery, batch failure, actual linker objects and Make
invalidation. The full 67,108,864-byte US ROM is byte-identical to the original, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. All 2,690 actual linker objects
reproduce 21,691,971 original bytes, and all 16,748 prior asset source files
retain their hashes. The 2,258 sample directories contain 6,774 source files.

The native report has 11,300 units with no compile errors and a current source
snapshot. Every new ADPCM unit matches completely. Matched and complete Data
each increase by 21,691,971 bytes. Only the unreconstructed bank-17 unit shrinks;
all other prior units, Code measures and the 65,120,512-byte Data denominator
remain unchanged. Matched Data is 32,042,604 bytes (49.205086%); complete Data is
32,041,836 bytes (49.203907%).

- Source fingerprint: `f5240075bc9e483d9604b9cf927e9816da7c2b8a35eb259062729df780f17334`.
- Report SHA-256: `76b503cae686a8968fd40deaa19d057b18a43be16bea877556f1551bc4cff53f`.

The [part inventory](us_adpcm_reconstruction.json) records the frame bounds and
hashes. Private validation logs and audits are under `build/adpcm-*`.
Generated WAVs, frame plans, ROMs and reports remain ignored.
