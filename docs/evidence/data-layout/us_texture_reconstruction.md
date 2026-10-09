# Continuing US texture reconstruction

The sustained task is to exhaust textures that can be reconstructed exactly,
including the other proven texture formats. This square-CI4 checkpoint is not
completion of that wider task.

## Square CI4 checkpoint

All 704 proven 64x64 CI4 entries were independently round-tripped through indexed
PNG. Fresh default RZIP compression exactly reproduced 663 stored entries.
The canonical flat YAML now selects those 663 entries, adding 587 textures and
962,684 stored bytes to the previous 76-texture checkpoint. No encoder or
texture editor changes were needed.

The combined selection contains **1,089,881 stored bytes** and **1,379,040 decoded
bytes**. The complete flat stream is partitioned into 942 nonoverlapping ranges:
663 reconstructed entries and 279 raw intervals. Raw and decoded bytes receive
no matching credit. The selected Data denominator is **1,296,953 bytes**:
201,632 initialized CPU bytes, 5,440 font bytes and 1,089,881 stored texture bytes.

All 41 remaining square entries passed PNG reconstruction but failed compressed
byte equality. A bounded standard-zlib search tested every combination of levels
1–9, memory levels 1–9, windows 9–15 and strategies 0–4 (2,835 settings per entry).
None reproduced the original storage. They remain raw and receive no credit.
This establishes a limitation of these encoder settings, not impossibility of
reconstruction with another evidenced encoder implementation.

The installed Apple gzip 457.140.3.700.1 was also tested at levels 1–9, removing
only the standard gzip wrapper before comparing its raw DEFLATE bytes. It
produced no exact matches for those 41 residuals.

A separate encoder-only experiment compiled the official
[zlib 1.1.3 release](https://zlib.net/fossils/zlib-1.1.3.tar.gz). At level 9 it
reproduced the same 3,483-entry exact set across all 3,873 proven textures,
with no recoveries or regressions. The downloaded archive SHA-256 was
`cae5847bc0e1cf113d3f70d037400da3e47c2e2b7b1c96b0b08447a5fbb906f4`.
This experiment remains ignored research, not a build dependency.

Unresolved square indices: 102, 158, 187, 205, 307, 337, 497, 498, 585, 636, 637, 664, 798, 1380, 1775, 1909, 2634, 2635, 2636, 2637, 2713, 3064, 3197, 3351, 3499, 3511, 3590, 3591, 3592, 3593, 3594, 3596, 3597, 3820, 3822, 3913, 3975, 4184, 4513, 4766, 7128.

## Evidence and remaining work

Ignored exact census and encoder-search evidence lives in
`build/us/texture-exhaustion-validation/`. Per-entry build proofs remain under
`build/us/textures/`; native matching evidence is in `build/us/objdiff-report/`.
The canonical YAML records each selected physical ROM boundary.

Remaining scope includes proven rectangular/tiled CI4, CI8, RGBA16 and native
pixel formats, and diagnosis of the residual compressed-byte mismatches. Existing
format contracts and reversible PNG codecs must remain the evidence boundary;
size or visual resemblance alone does not qualify a payload as a texture.

An independent census of the other existing catalogs checked 528 direct CI8,
6 RGBA16, 91 native, 13 rectangular CI4 and 2,534 tiled-view records. Their union
contains 3,169 unique flat entries, with no overlap with the 704 square entries.
All passed PNG round-trip checks. Default compression matched 2,820 entries
(2,922,187 stored bytes); 349 have residual compressed-byte differences. Those
2,820 are candidates for the next integration, not yet credited matches.

The exact other-format candidates comprise 1,514 CI4, 1,222 CI8, 6 RGBA16,
37 RGBA32, 15 I8, 12 IA8, 13 I4 and 1 IA16 texture. Census records retain the
format, dimensions, row layout, physical bounds and hashes; overlapping family
contracts are deduplicated by physical flat index.

## Square checkpoint validation

- Full US ROM build passed in 334.24 seconds (command elapsed time).
- Full Docker suite: 2,179 tests run, 8 skipped, no failures; 532.065 seconds
  test-runner time and 543.44 seconds command elapsed time.
- Canonical progress and tracked whitespace checks passed.
- Native objdiff report: **all 663 texture units fully matched and complete**,
  totaling 1,089,881 stored bytes; no compile errors and snapshot status
  `current`. Command elapsed time: 778.85 seconds. A separate checkout was
  running six two-worker permutation containers during this validation, so
  these timings are not an isolated performance benchmark.
- Aggregate Data: **1,096,425 / 1,296,953 matched bytes (84.53853%)** and
  **1,095,657 complete bytes (84.47932%)**. Code totals are unchanged.
- Independent whole-ROM comparison confirms the original US SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

Report source fingerprint:
`49b3e287b65cb540ac25639ec4da37e88edf5d2b432d4cb679fc429c2cdaaab5`.

These timings describe commands, not total workflow duration.
