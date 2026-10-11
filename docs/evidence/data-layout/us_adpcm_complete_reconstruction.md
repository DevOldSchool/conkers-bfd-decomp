# US ADPCM reconstruction from PCM

All 21,705,520 bytes of bank `0x17` entry 2 are reconstructed from 2,258 native
sample sources, encoding parameters and derived zero alignment. Of these,
21,697,389 bytes are complete ADPCM frames and 8,131 bytes are zero padding.
There is no raw sample-storage fallback.

## Native formats and reversible sources

The full control loader, bank patcher and audio loader spans are pinned by the
[sound-bank reconstruction](us_sound_bank_reconstruction.md). The matched
`audio/n_load.o` consumes sample offsets, predictor books and lengths rounded
down to multiples of nine bytes. Each native frame contains a scale/predictor
header and sixteen signed four-bit residuals. Predictor books contain signed
coefficients indexed by order and predictor.

The source directories contain editable WAVs, semantic encoding plans and
manifests. Plans carry scale/predictor pairs and native book coefficients; they
contain no original residual bytes. The source context uses the first native
wavetable reference to each unique sample range, recorded in the manifest.
All other references remain in the native sound-bank graph.

For 2,143 samples, ordinary PCM16 retains enough information to reproduce the
original residuals. The encoder uses inverse fixed-point prediction; clipped
vectors use a bounded search for the first signed residual solution in
lexicographic order. That route reconstructs every frame in these samples.

The other 115 sources use standard mono IEEE Float32 WAVs. They retain the
reconstructed signal immediately before signed-16 saturation, normalized by
32,768. The observed signal range is -35,749 through 35,987, so the floating
representation preserves every integer signal value exactly. Values outside
[-1, 1] retain the small amount of headroom that PCM16 loses. Applying native
saturation reproduces the existing decoded PCM16 signal exactly.

The headroom encoder derives residuals directly from that signal. It saturates
history between native eight-sample vectors, as the decoder does. Every nibble
is freshly packed; neither encoder takes original residuals or frame bytes as
inputs. Native scale/predictor and book context are checked before encoding,
and changes to the entire PCM signal are checked even when playback would
clip the change away. These are reversible reconstruction sources, not a claim
to have recovered the original authoring recordings.

## Complete storage layout

Native wavetable lengths equal complete-frame lengths rounded to two bytes.
All 1,149 single-byte sample tails are zero. Sample bases, and the end of the
entry, then align to eight bytes; all 1,714 gaps (6,982 bytes) are zero. The
layout verifier derives each boundary from the native lengths, requires these
alignment rules, checks every padding byte and rejects gaps, overlap, nonzero
padding or an uncovered suffix.

Each of the 2,258 sample parts contains its complete runtime payload followed
by the derived zeros up to the next sample. This consolidates the earlier
2,690 exact frame regions and their raw exclusions into complete sample units.
The selection contract uses schema `conker-adpcm-complete-samples-v2` and lists
the 115 headroom sources explicitly. It does not contain raw audio or encoded
residuals.

## Build and native report path

`./conker audio-assets build-adpcm` validates the ROM, complete consumers,
source context and profile partition before encoding. Source directories live
under `build/assets/adpcm-build/us/<sample>/`. Missing complete folders can be
initialized. Existing malformed or partial folders fail without replacement.
Recovery for one sample remains available with
`./conker audio-assets recover-adpcm --sample <index>`.

`./conker audio-assets recover-adpcm --all` prepares the full replacement tree
before moving the existing tree into an ignored recovery directory. It retains
all previous files, including extra notes. A staging failure leaves existing
inputs untouched; a publication failure restores the previous tree. The initial
migration checks the previous report's source hashes before this explicit
recovery and retains the backup.

All samples must encode and source hashes must remain stable before publishing
parts. Make links actual candidate objects from those parts, with unchanged
outputs retaining timestamps. Native objdiff compares each actual linker object
with an independently wrapped original-ROM target. It rechecks complete source
and object hashes, accounts for every storage byte once and preserves the Data
denominator. Generated WAVs, plans, ROMs and reports remain ignored.

## Validation state

The complete-entry codec and the separate private builder each reconstructed
all 21,705,520 bytes exactly. Tests cover clipping, predictor history, exact
float WAVs, malformed fields, native zero alignment, source preservation,
actual linker candidates and transactional full-tree recovery. The sample
Float32 WAV is recognized by the macOS audio inspector at the native 22,050 Hz.
Production migration preserved all 6,774 previous source files in a retained
backup. All 2,258 encoding plans and 2,143 PCM16 WAVs are unchanged; the 115
headroom WAVs saturate to the previous PCM16 signals. All 16,748 other asset
source files retain their hashes.

The completed acceptance gates are:

- `./conker build --assets`: all 67,108,864 bytes equal the original US ROM,
  SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- All 2,258 actual linker objects reproduce the complete 21,705,520-byte entry.
- `./conker test`: 2,440 tests, eight skips, no failures; the final focused set
  passed 102 tests.
- `./conker objdiff report`: 10,868 units, no compile errors and a current
  snapshot. Matched Data is 32,056,153 / 65,120,512 bytes (49.225892%);
  complete Data is 32,055,385 bytes (49.224713%). This batch adds 13,549 bytes
  to both measures. The denominator and Code measures are unchanged.
- Every previous non-sample unit retains its measures except unreconstructed
  bank-17 storage, which decreases from 75,244 to 61,695 bytes. Sample units
  consolidate from 2,690 frame regions into 2,258 complete samples.
- Canonical progress and whitespace gates pass.

Report SHA-256: `db6efdc094dcbd4b03e7b95f7ff55d53f7fe44db8368d4fb7548cf5419f68ea2`.

Build-input fingerprint: `3af0c305246af91acadf874d0a02f78c163ec6ecd01fc5a2c6dc288ba97ae3fb`.

The report was generated with the final source changes present before the
batch commit. Its fingerprint and asset source hashes remain the acceptance
identity after committing; generated report files remain ignored.
