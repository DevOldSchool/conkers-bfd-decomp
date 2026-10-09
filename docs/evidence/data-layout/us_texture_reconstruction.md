# US texture reconstruction

The canonical flat YAML now selects **5,665 distinct textures**. The new batch
adds 1,278 complete model-material, animation-frame and ROM-binding textures to
the fully passing 4,387-texture checkpoint committed as `f2f7e20`. All 5,665 units passed
the full build, suite and native-report gates; earlier passing checkpoints
remain recorded below.

## Selection and resource identity

The game has 7,762 runtime flat-resource slots but 7,760 physical streams.
Runtime slots **1767 and 1768 are empty**. Source contracts therefore resolve
consumer IDs through the validated compressed-size table at `0x80091D20`.
File and linker-part names retain physical stream ordinals; runtime IDs are
recorded explicitly in each extended source manifest. The size table must cover
the whole archive, and every nonempty extent must equal its decoded RZIP span.

The selected families, deduplicated in this order, are:

| Source contract | Distinct textures |
| --- | ---: |
| Existing square CI4 | 704 |
| Direct CI8 | 757 |
| Direct RGBA16 | 10 |
| Direct native formats | 144 |
| Direct rectangular CI4 | 15 |
| Runtime tiled ranges | 2,524 |
| Reviewed HUD selector resources | 159 |
| Additional reviewed HUD/menu artwork | 74 |
| Model material consumers | 1,190 |
| ROM animation frame sets | 24 |
| ROM defaults and texture bindings | 64 |
| **Total** | **5,665** |

The tiled runtime catalog has 2,526 resources before deduplication: 1,822 CI4
and 704 CI8 payloads. Two already have direct contracts. Only actual runtime
ranges and the validated six-resource override qualify; the legacy gallery's
neighbor/phase adjustment is not used for matching. Direct sources use
consumer dimensions, not legacy preview-shape overrides. Reviewed HUD sources
retain their top-left origin; the other texture codecs preserve their existing
bottom-left source interpretation. A partial HUD preview cannot qualify as a
full reconstruction. Additional artwork has reviewed source-pixel contracts;
this does not establish its runtime placement.

The audit supersedes an uncommitted 3,873-entry trial that used older surveys'
physical indices as runtime IDs. That trial passed byte reconstruction, but
its consumer associations were not sufficient evidence. Corrected runtime
bundles live at `build/assets/texture-build/us/runtime/<physical-index>/`.
Earlier local bundles, including the pilot and all square sources, are
preserved without overwriting them. Existing gallery extraction behavior is
unchanged; the build explicitly supplies runtime-indexed entries to the surveys.

## Model consumer evidence

The additional catalog parses model banks 01, 03, 04 and 09 and reuses their
validated texture resolvers. It also checks ROM render-state consensus,
animation frame arrays, character defaults, object/scene bindings and reviewed
attachment/UI state. Each source manifest records its concrete model/material
consumer or frame-set binding. Runtime resource IDs remain distinct from
physical storage ordinals.

A preview qualifies only when decoding its PNG recovers the **entire original
payload**, including all palette entries. Cropped images, transformed alpha,
unrepresented mip levels and trailing bytes receive no credit. Missing consumer
evidence or a changed reference ROM fails closed. Overlapping consumers are
counted once and all 4,387 previous source bundles retain their hashes.

The independent census found 1,278 new complete payloads, totaling 1,821,586
stored bytes. Fresh compression reproduced all of them: 1,250 with default
zlib and 28 with GNU gzip. The production catalog returns exactly the same
resource set as the independent model, frame and binding audits.

## Exact reconstruction

All 5,665 source PNGs round-trip to their complete original payloads.
Default zlib level-9 compression reproduces 5,217 entries. The remaining 448
select **GNU gzip 1.12 at level 9**; every selected encoder must reproduce the
original compressed bytes before any output in the batch is replaced.

The GNU encoder uses `-n -9 -c`. Its fixed header and CRC/size trailer are
validated and removed, leaving freshly encoded raw DEFLATE with a new RZIP
length header. No compressed ROM bytes or token recipes are used as source.
Every output is decoded independently and checked for exact extent and hash.
Changed pixels, palettes, manifests, encoder output or concurrent source
changes fail closed. This workflow does not support asset editing.

`./conker texture-assets build` runs in the pinned toolchain container, which
provides GNU gzip 1.12. Surveys and extraction retain host dispatch.

Selected storage is **6,933,902 bytes**, with **11,348,960 decoded bytes**.
The entire flat archive is partitioned into 6,241 nonoverlapping rows:
5,665 rebuilt entries and 576 raw intervals. The selected Data denominator is
**7,140,974 bytes**, including 201,632 initialized CPU bytes and 5,440 font
bytes. Decoded bytes and raw ranges receive no additional credit.

Raw means ROM-backed storage, not necessarily unidentified content. Exhausting
these reviewed contracts does not prove that all remaining flat payloads are
non-textures. Broader coverage needs new complete format/consumer evidence.

## Historical passing checkpoint

Commit `94cdf4564690c7492e14afbfe20c145cf0a83fc1` reconstructed **663 square
CI4 textures**, totaling **1,089,881 stored bytes**. All 663 native units were
fully matched and complete, with no compile errors and a current snapshot.
The full US ROM was identical. The suite ran 2,179 tests with 8 skips and no
failures; canonical progress and whitespace checks passed.

Its report fingerprint was
`49b3e287b65cb540ac25639ec4da37e88edf5d2b432d4cb679fc429c2cdaaab5`.
Aggregate Data was 1,096,425 / 1,296,953 matched bytes (84.53853%) and
1,095,657 complete bytes (84.47932%). Code totals were unchanged.

Command elapsed times were 334.24 seconds for the build, 543.44 seconds for
tests (532.065 seconds in the runner), and 778.85 seconds for the report.
Another checkout was running six permutation containers, so these are not
isolated performance benchmarks or total workflow duration.

The 41 remaining square entries could not be reproduced by 2,835 standard
zlib configurations per entry or installed Apple gzip levels 1–9. GNU gzip
subsequently recovered them. An encoder-only experiment with the official
[zlib 1.1.3 source](https://zlib.net/fossils/zlib-1.1.3.tar.gz) reproduced the
same default-zlib exact set for the earlier trial, with no recoveries.
Archive SHA-256:
`cae5847bc0e1cf113d3f70d037400da3e47c2e2b7b1c96b0b08447a5fbb906f4`.
That experiment is not a build dependency.

## Evidence and validation

Ignored per-entry census and command logs live under
`build/us/texture-exhaustion-validation/`; reconstruction proofs are under
`build/us/textures/`, and independent native comparisons are under
`build/us/objdiff-report/`. The canonical YAML records every selected physical
ROM boundary. Generated reports and ROM-derived images are not committed.

Passing 4,387-texture checkpoint validation (commit `f2f7e20`):

- Fresh PNG-derived compression: all 4,387 streams exactly match, totaling
  5,112,316 bytes; command elapsed time 58.74 seconds.
- Full US ROM build passed in 315.87 seconds. Independent comparison confirms
  all 67,108,864 bytes match and SHA-1 is
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Full container suite: 2,188 tests, 8 skipped, no failures; 219.949 seconds in
  the runner and 225.81 seconds command elapsed time.
- All 663 checkpoint source bundles retain their original hashes.
- All 159 HUD selector PNGs match the independent reviewed preview pixels;
  the additional artwork renderer validates 40 groups covering 74 resources.
- Native report: all 4,387 texture units fully matched and complete, totaling
  5,112,316 stored bytes, with no compile errors and snapshot status `current`.
  Command elapsed time: 604.00 seconds.
- Canonical progress validation, progress rendering and whitespace checks passed.
- Aggregate Data: 5,118,860 / 5,319,388 matched bytes (96.23025%) and
  5,118,092 complete bytes (96.215805%). Code totals are unchanged.

Report source fingerprint:
`575bafcfe96e4450b918c8a3d4ac0e5066c50c3412232b773bd19a4a9d71c833`.

These are command timings, not total workflow duration.

## Current model batch validation

- 37 focused catalog, reconstruction and Make tests passed.
- All 4,387 committed source bundles retain their hashes.
- Full US ROM build passed in 442.46 seconds; independent comparison confirms
  byte equality with the original 67,108,864-byte US ROM.
- Full container suite: 2,192 tests, 8 skipped, no failures; 254.961 seconds in
  the runner and 262.51 seconds command elapsed time.
- All 5,665 PNG-derived compressed sources match, totaling 6,933,902 bytes.
- Native report: all 5,665 texture units fully matched and complete, with no
  compile errors and snapshot status `current`. Command elapsed time: 752.12 seconds.
- Aggregate Data: 6,940,446 / 7,140,974 matched bytes (97.19187%) and
  6,939,678 complete bytes (97.181114%). Code totals are unchanged.
- Canonical progress validation, progress rendering and whitespace checks passed.

Report source fingerprint:
`058543eab17a71aa79cac5b9988f520e941ba8e32821a54fce4684b18f0166b1`.
