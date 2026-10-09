# US CI4 texture reconstruction batch

This is the historical 26-texture checkpoint. The
[next 50-texture batch](us_ci4_texture_batch_50.md) records the current selection.

This batch extends the [texture 1063 pilot](us_texture_1063_build.md) with 25
additional textures using the same indexed-PNG and raw-DEFLATE reconstruction.
Selection and ROM storage boundaries are recorded in
`config/profiles/us/assets/flat.yaml`; no game assets are committed.

New flat indices: **1064, 1065, 1074, 1081, 1082, 1132, 1167, 1168, 1177, 1178,
1180, 1191, 1192, 1207, 1231, 1242, 1252, 1260, 1279, 1280, 1281, 1296, 1297,
1325 and 1328**. These are the next 25 members of the proven 64x64 family after
the pilot, in physical archive order. All 25 reproduced their original compressed
bytes without encoder changes. Other indices between them are outside this
selected family cohort; they remain raw storage and receive no credit.

| Scope | Textures | Stored bytes | Decoded bytes |
| --- | ---: | ---: | ---: |
| Existing pilot | 1 | 1,516 | 2,080 |
| Newly reconstructed | 25 | 37,401 | 52,000 |
| Combined selection | 26 | 38,917 | 54,080 |

The complete flat stream is partitioned into 44 nonoverlapping ranges: 26
reconstructed textures and 18 raw intervals. Each texture's source coordinates
come from walking the checksum-validated US RZIP archive, not from candidate
compression. The verifier requires the entire YAML partition to agree with
those coordinates. Raw interval names use their ROM starts, so adding a texture
does not require renaming unrelated asset identities.

Indices 1296 and 1297 retain the previously proven **linear** row layout. The
other 24 selected textures use the odd-row 32-bit swap. Both forms reverse the
source bottom-left origin for PNG and restore it when packing. The row layouts
and palette words are verified as source data, not selected by image heuristics.

## Batch build and reporting

`./conker texture-assets build` loads the ROM and verifies the selection once,
then reconstructs each PNG independently. The existing 1063 input bundle remains
at `build/assets/texture-build/us/`; additional bundles live at
`build/assets/texture-build/us/<index>/`. Each has its own manifest and indexed
PNG. Existing inputs are never overwritten, and changed pixels/palettes or
nonidentical compression fail. All candidates and source hashes must validate
before existing linker parts are replaced.

The Make rule tracks nested source bundles and prepares all selected parts in
one pack operation. Report preparation builds the selected linker objects in
one four-job Make call, then independently compares each actual `.data` section
with a fresh PNG encode and its original stored ROM range. Each texture remains
a separate native objdiff unit. Cross-batch source/link hashes are rechecked
before report completion; raw intervals and decoded bytes add no matching credit.

The current Data denominator is **245,989 bytes**: 201,632 initialized CPU bytes,
5,440 font bytes and 38,917 stored texture bytes. This is selected reconstruction
coverage, not a percentage of all ROM assets. The earlier pilot report is a
historical checkpoint with its own smaller denominator and source fingerprint.

The full ROM build, Docker suite and native report run once for this group.
Ignored evidence is retained under `build/us/texture-batch-validation/` and
`build/us/objdiff-report/`; per-texture build proofs live under
`build/us/textures/`.

## Validation

- `./conker texture-assets build`: all 26 textures reproduce their original
  compressed bytes (38,917 stored bytes).
- `./conker build --all`: full US ROM byte-identical; command elapsed time
  **45.60 seconds** with the warm four-job build.
- `./conker test`: 2,179 tests in 150.700 seconds, with 8 skips and one stale
  assertion expecting the former serial build command. After updating that
  assertion to require the four-job command, all 18 tests in
  `test_repository_safety.py` passed in Docker. No implementation change was
  needed, and the unaffected suite was not repeated.
- `./conker progress check`: canonical progress and report rendering valid.
- `./conker objdiff report`: all 26 texture units are 100% matched and complete,
  totaling 38,917 stored bytes; the 25 new units add 37,401 bytes. No compile
  errors; snapshot status is `current`. Command elapsed time: **236.78 seconds**.
  Aggregate Data is 45,461 / 245,989 matched bytes (**18.480907%**) and 44,693
  complete bytes (**18.168697%**). This denominator covers reviewed initialized
  data and selected rebuilt assets, not the entire ROM.
- Independent whole-ROM comparison confirms SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

Report source fingerprint:
`d3dca1b75a350c51d0c7c43f266bd86447543d7cb7083a49da31e64b9e97614b`.

Timings above are measured command/test durations, not end-to-end workflow time.
