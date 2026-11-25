# US MP3 source metadata fields

This batch reconstructs **14,532 bytes** of readable metadata fields in 156
bank-16 streams. The existing coefficient sources remain unchanged. Native
objdiff grows the corresponding spectral units without counting storage twice.

## Format and boundary

The [ID3v1 field layout](https://id3.org/ID3v1) supplies the three-byte marker,
five fixed-width text fields and one genre byte. These source tags begin at the
runtime audio boundary established by the independent MPEG frame scanners;
additional stored bytes follow them. They are not claimed to be runtime
dialogue or speaker records. See the earlier
[MP3 cue and tag survey](../assets/audio/us_mp3_cue_assets.md).

Each editable field contains printable ASCII text and an explicit terminator
flag. A field without a NUL must fill its native width. A terminated field
rebuilds its text and the single NUL; every subsequent byte in that field is
excluded. Spaces in a full-width field remain authored text. No arbitrary byte
override or inferred trailing fill is supported.

This distinction matters: 151 tags contain command-line-looking bytes after
the title's NUL, and spaces after the artist's NUL. The codec excludes all
**5,436 bytes** after field terminators and all **51,423 bytes** following the
128-byte tag records. Existing opaque cues, incomplete coefficient bytes and
other reservoir suffixes remain outside credit as before.

## Build and report integration

The spectral builder initializes separate `manifest.json` and `tag.json`
sources under `build/assets/mp3-metadata/us/<entry>/`. Existing coefficient
manifests, coefficient JSON and raw backing are preserved. A changed or missing
metadata source fails without replacement; explicit
`./conker mp3-assets recover-metadata --entry <index>` backs up the existing
folder before restoration. Make tracks metadata source changes and missing
files as spectral build prerequisites.

The generated text spans are composed with freshly encoded coefficient spans
in the actual linked stream object. Source hashes are rechecked before batch
publication. Receipts include metadata hashes, encoder dependencies and exact
generated ranges. Native objdiff checks the entire linked object against the
independent ROM and credits only the generated ranges. Its fresh-encode mode
continues to bypass both receipts and the spectral cache.

The public coefficient-only codec and default `packed_stream` behavior retain
their previous scope. The ROM builder and native report explicitly enable
metadata composition.

## Independent checks

A separate frame scanner agrees with all 156 tag boundaries. Direct field
reads independently reproduce the selected ranges, and **936 text/genre
mutations** each change exactly the intended original byte. Focused tests cover
unknown field suffixes, stream tails, invalid text, source preservation,
explicit recovery, source races, actual linked-object credit and Make scheduling.
A single-stream pilot and a 20-stream expansion both reproduced their original
streams exactly before full-batch validation.

## Accepted batch

The complete US asset build reproduced all 67,108,864 ROM bytes in 246 seconds
including setup and Docker. All 2,899 Docker tests passed in 292.956 seconds
(eight existing skips). Native objdiff, progress and whitespace checks passed.

The report adds exactly 14,532 matched and complete Data bytes. Matched Data is
**63,059,876 / 65,120,512 (96.835655%)**. Code measures, denominators and unit
counts are unchanged. Only the 156 selected spectral units and bank-16 raw
remainder change; every prior MPEG range remains covered. All 26,118 prior
source hashes are preserved.

Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus uncommitted changes.
Source fingerprint:
`109a82077d8b06fcc85ce02dc143ac551c8f17983d8bee0541fc990dae121255`.
Report SHA-256:
`8597735e78692cecdb06f1638e87c5e19206a47a98140952ed6d88510a4cc5a4`.
