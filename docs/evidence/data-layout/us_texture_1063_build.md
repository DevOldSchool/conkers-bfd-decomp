# US flat texture 1063 build input

This records the original single-texture pilot. The subsequent
[reconstruction summary](us_texture_reconstruction.md) owns the current selection,
partition and report totals; the pilot pixels and texture identity are preserved.

This pilot reconstructs flat RZIP entry 1063 from an indexed PNG. The source
ROM is the reviewed US image, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
Its 64x64 CI4 image contains the `MILK` and `SAFE` lettering described in the
[texture format evidence](../../rzip-assets.md#loader-proven-us-64x64-ci4-textures).

| Range | Bytes | Representation |
| --- | ---: | --- |
| ROM `[0x3440A9, 0x344695)` | 1,516 | Four-byte big-endian length plus raw DEFLATE |
| Decoded pixels | 2,048 | CI4, including the stored odd-row permutation |
| Decoded palette | 32 | Sixteen big-endian RGBA5551 words |

The PNG decoder restores pixel indices, all palette slots, source row origin
and the odd-row 32-bit swap. The existing level-9 raw-DEFLATE encoder then
recreates the original 1,516 stored bytes exactly. This is fresh compression
of the PNG-derived payload; the original compressed chunk is used only as an
independent reference. No compressed bytes or compression-token recipe are
stored in the input bundle. This result establishes one texture's encoder
compatibility, not an exact compressor for the whole flat archive.

## Build contract

```sh
./conker texture-assets build
./conker build --all
./conker objdiff report
```

The first build initializes absent inputs at
`build/assets/texture-build/us/1063/{manifest.json,1063.ci4.png}` through an atomic
directory rename. Existing pilot files in the parent are migrated byte-for-byte
with resumable cleanup. An existing partial bundle is refused. Existing PNGs
are never replaced. The manifest is checked
against the checksum-validated ROM, including its original payload and stored
digests, coordinates and encoder settings. Changed pixels or palette values
are rejected: this pilot supports exact reconstruction only. Recompression
with a different size or different bytes also fails, so zlib output drift
cannot silently preserve matching credit. Inputs are hashed before and after
packing to reject concurrent changes.

The `assets_flat_rzip` group retains its original extent and byte alignment.
`config/profiles/us/assets/flat.yaml` partitions it into the raw prefix, rebuilt
texture and raw suffix. The verifier derives texture boundaries by walking
the validated flat RZIP archive and rejects YAML drift. The Makefile links
`build/us/assets/flat/textures/1063.o` from the newly encoded part under
`build/us/textures/parts/`; Splat's extracted binary remains a separate reference.
The adjacent raw ranges receive no reconstruction credit. The build preserves
unchanged part timestamps and recreates missing parts; missing or altered
source inputs fail instead of reusing stale output.

## Data report

`assets/flat/textures/1063` contributes 1,516 stored bytes to the ordinary Data
category. Its 2,080 decoded bytes are not counted again. The candidate is a copy
of the actual ROM linker object. A fresh PNG encode must equal that object's
complete `.data` section. The independent target wraps the original compressed
ROM interval with the same binary-input naming convention. Native objdiff
measures the match; completion additionally requires exact bytes and verified
source and link-input hashes. Changed source inputs invalidate report freshness.

The resulting data denominator is 208,588 bytes: 201,632 initialized CPU bytes,
5,440 font bytes and 1,516 texture bytes. Other textures and audio remain outside
the published scope. Generated PNGs, ROMs, binaries and reports remain ignored.

## Validation

The pilot was branched from main `47c4c311b58e736956ca3805814db787692cc356`.
The pinned Docker runtime's zlib 1.3 independently produced stored SHA-256
`5f5aa11d806a70dee0b8547f6525dd469202dc1945829ccf3b8196cbe2aa9721` from
decoded SHA-256
`0737e718e4331fa55106bd80147edd575715e42957227cf479e05e75c50775a1`.

- `./conker build --all` passed; a separate byte comparison confirmed all
  67,108,864 bytes equal the original US ROM.
- `./conker test` passed 2,174 tests with eight skips. The final report-input
  race guard additionally passed all 24 `test_objdiff_data_targets.py` tests
  with one ROM-opt-in skip in the pinned Docker runtime.
- `./conker progress check` and whitespace checks passed.
- `./conker objdiff report` passed with no compilation errors and a current
  source fingerprint. Native `assets/flat/textures/1063` measures are
  1,516 total, 1,516 matched and 1,516 completed bytes. Aggregate data measures
  are 208,588 total, 8,060 matched (3.8640766%) and 7,292 completed bytes.

The validated source fingerprint is
`252ea45f8396a0d40437bed06625c9743635e7d67dadd792890f93b03cc9d6ce`.
Local logs are retained under `build/us/texture-1063-validation/`; native
report, per-asset proofs and source/link hashes are under
`build/us/objdiff-report/`. These are local validation results, not publication.

Synthetic tests cover changed pixels/palettes, missing and partial inputs,
manifest and YAML drift, incorrect compressed bytes/size, source changes during
packing, missing-output recovery, incremental Make scheduling and stale or
concurrently changed linker objects. These tests do not contain game assets.
