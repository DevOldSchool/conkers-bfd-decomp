# US CI4 reconstruction: 50 additional textures

This is the historical 76-texture checkpoint. See the [continuing reconstruction](us_texture_reconstruction.md) for the current selection.

This batch extends the [26-texture checkpoint](us_ci4_texture_batch.md) to 76
exactly reconstructed textures, using the existing PNG and RZIP encoder unchanged.
The user requested a larger 50-asset batch to share the build and report costs.

New flat indices: **35, 36, 38, 39, 44, 46, 48, 49, 51, 61, 62, 63, 64, 65, 66,
67, 68, 69, 70, 72, 73, 74, 75, 76, 77, 78, 79, 92, 101, 109, 110, 111, 112,
113, 117, 118, 119, 120, 121, 122, 129, 130, 144, 145, 151, 152, 153, 154,
155 and 156**.

Selection walks the remaining proven 64x64 CI4 family in physical archive order.
Every selected entry passes indexed-PNG encode/decode equality and fresh RZIP
compression equality against its checksum-validated ROM range. Index **102**
passes the PNG round trip but fails compressed-byte equality: both encodings
are 1,508 bytes, with different contents. It remains raw storage with no credit;
no encoder changes or compression search were attempted.

| Scope | Textures | Stored bytes | Decoded bytes |
| --- | ---: | ---: | ---: |
| Previous selection | 26 | 38,917 | 54,080 |
| Newly reconstructed | 50 | 88,280 | 104,000 |
| Combined selection | 76 | 127,197 | 158,080 |

`config/profiles/us/assets/flat.yaml` partitions the full flat stream into 109
nonoverlapping ranges: 76 reconstructed textures and 33 raw intervals. Original
RZIP archive coordinates define every boundary. Each added texture uses the
existing source bundle at `build/assets/texture-build/us/<index>/`; the original
1063 bundle retains its existing location. Existing inputs are preserved.

The Data denominator becomes **334,269 bytes**: 201,632 initialized CPU bytes,
5,440 font bytes and 127,197 stored texture bytes. Decoded bytes and remaining
raw intervals receive no additional credit. This is selected reconstruction
coverage, not a percentage of all ROM assets.

## Validation

The batch uses one full US ROM build, Docker suite and native objdiff report.
Per-entry proof and source/link hash verification retain the same requirements
as the earlier batch. Ignored selection evidence and command logs live under
`build/us/texture-batch-50-validation/`; build proofs are under
`build/us/textures/`, with the native report under `build/us/objdiff-report/`.

- `./conker texture-assets build`: all 76 textures reconstruct their original
  127,197 compressed bytes exactly.
- `./conker build --all`: byte-identical full US ROM; command elapsed time
  **43.36 seconds**. An independent whole-file comparison confirms SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- `./conker test`: **2,179 tests run, 8 skipped**, with no failures;
  148.618 seconds in the test runner and 153.54 seconds command elapsed time.
- `./conker progress check`: canonical progress and report rendering valid.
- `./conker objdiff report`: all 76 texture units are fully matched and complete,
  totaling 127,197 stored bytes. The 50 new units contribute 88,280 matched and
  complete bytes; index 102 is absent from reconstructed units. No compile
  errors, with snapshot status `current`. Command elapsed time: **210.10 seconds**.
- Aggregate Data: **133,741 / 334,269 matched bytes (40.009995%)** and
  **132,973 complete bytes (39.78024%)**. Code totals remain unchanged.
- Tracked and new-file whitespace checks pass.

Report source fingerprint:
`a036fea15be0d21978a324adc09c1c2867ed132652743d59a9469d34507c04d3`.

Recorded timings are command/test durations, not end-to-end workflow time.
