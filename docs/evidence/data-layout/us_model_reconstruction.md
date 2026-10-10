# US direct-model reconstruction

The current selection reconstructs **221 direct models**, totaling **118,724
stored RZIP bytes**: 36 bank-03 models and 185 bank-09 models. The
[normal-table expansion](#normal-table-expansion) adds referenced signed XY
normal records and explicit zero suffixes to the native record schema.

The first model storage batch selected 22 direct bank-03 models from the
checksum-validated US ROM (SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`).
It adds 10,607 stored RZIP bytes to ordinary native Data comparison. It does
not establish model names, runtime appearance or new C-function matches.

## Selection and storage ownership

The original outer asset table owns bank 03 at `0xF8F278:0xF9E660`. Its inner
index owns each selected compressed extent. `config/model_build.us.json`
records the reviewed entry IDs and the existing raw-DEFLATE zlib encoder
contract. `config/profiles/us/assets/models03.yaml` partitions this bank into
selected records and retained raw ranges, including the index, gaps and
unselected models. Those raw ranges earn no model reconstruction credit.

Selected decimal entries: 3, 51, 55, 56, 70, 71, 72, 76, 81, 82, 89, 91, 94,
98, 100, 101, 104, 105, 108, 109, 110 and 113.

The existing direct-model parser proves a 40-byte header, 16-byte vertices and
8-byte display-list commands. Each record in the first batch ends exactly at its primary
display list and has no auxiliary regions. The input format preserves ten
native header words, signed position/UV components, unsigned flags and RGBA
bytes, and pairs of native command words. Unknown header or command semantics
remain uninterpreted; integer serialization preserves their bits. This is a
native record reconstruction, not an OBJ/glTF importer.

The bank contains 77 models, of which 25 have this complete region layout.
Twenty-two reproduce their original compressed bytes with the reviewed zlib
encoder. Entries 1, 39 and 54 fail that compression check, and the other 52
records contain additional regions. Those 55 records are excluded from the
first batch. Candidates contain no copied original compressed payloads or
opaque tails.

## Build and report contract

`./conker model-assets build` initializes source records below
`build/assets/model-build/us/<bank>/<entry>/` only when absent. Each bundle contains
`manifest.json` and `model.json`; existing incomplete or changed bundles fail
without being replaced. Initialization publishes a complete bundle atomically.
The packer validates every selected candidate and rechecks its source hashes
before replacing any linker inputs. Unchanged outputs retain their timestamps.

Every encode checks the full decoded size/hash and original compressed
size/hash. Edited geometry is retained but rejected by this exact-match build;
this command is not a ROM model-editing workflow. Compression drift fails
without choosing another encoder or falling back to original ROM bytes.

`./conker build --assets` links 221 reconstructed objects under
`build/us/assets/models/bank03/` and `bank09/`. The ordinary default build
continues to use the original banks. Each native report candidate is copied from the actual
model linker object and checked against a fresh encode of the current source.
Its independent target is wrapped from the original checksum-validated ROM
slice. Completion requires native matching, exact payload equality, source
hashes and linked-object hashes. The decoded byte total is not counted again.

Reproduction:

```sh
./conker model-assets build
./conker build --assets
./conker test
./conker objdiff report
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

Generated model records, binaries, ROMs and reports remain ignored.

## Acceptance results, 10 October 2026

Validated working-tree changes based on main
`08bd4b5339b578fb7acc76d03178a905fa9ae3a7`:

- All 22 models reconstruct 20,960 decoded bytes and 10,607 stored bytes exactly.
- Independently assembling the rebuilt entries and retained raw intervals
  reproduces the entire 62,440-byte bank 03.
- `./conker build --assets` passes: all 67,108,864 output ROM bytes equal the
  original, with SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- The complete Docker suite passes: 2,318 tests, eight skips, no failures.
  Focused tests cover record bounds, input preservation, compression drift,
  source races, incremental Make recovery and independent report targets.
- Native objdiff reports all 22 model units fully matched and complete:
  10,607 / 10,607 stored bytes, with no compile errors.
- At the initial, narrower report scope, aggregate Data was
  8,301,843 / 8,502,371 matched bytes (97.6415%);
  8,301,075 bytes are complete (97.63248%).
- Canonical progress and whitespace checks pass. No C-function inventory or
  source-unit ownership changes are part of this batch.

Report source fingerprint:
`46821402e8e6775c9ce634de08293ac5a785f5d583472ade3f41069f8331366f`.

Local logs are retained in `build/us/models/validation/`; the native report
and its per-file source/link proofs are in `build/us/objdiff-report/`.
These results apply to the working tree, not an additional committed revision.

The subsequent [complete storage accounting](us_asset_storage_accounting.md)
retains these model matches and adds all remaining bounded asset storage as
unmatched targets. The earlier aggregate percentage is historical.

## Input recovery and verification semantics

A missing or stale input bundle fails with its path and a recovery command;
ordinary builds never replace existing editable records. To restore a reviewed
entry explicitly (decimal bank-03 ID):

```sh
./conker model-assets recover --bank 3 --entry 3
./conker model-assets build
```

Recovery moves the entire previous folder, including edits and extra notes, to a
unique directory under `build/assets/model-build/recovery/us/03/`, then publishes
fresh reviewed inputs atomically. It prints the backup location. If publication
fails before a replacement appears, the original folder is restored. Unreviewed
IDs and symlink/non-directory destinations are rejected.

`batch.json` is a successful-build receipt, not an independent progress metric.
`matches_original` is necessarily true on success: decoded/stored hash checks
and a direct comparison with the original ROM slice all pass before any linker
part is written. Each model records its actual `stored_sha256`; the command
reports these verification gates explicitly. Native objdiff and the complete
ROM build remain independent acceptance checks.

Make tracks the reconstruction path's four codec modules (`model_build`,
`model_assets`, `texture_build`, `rzip_pack`) and the shared ROM/layout/build
inputs. Unrelated model inspection tools no longer invalidate the model stamp.
Missing `manifest.json` or `model.json` forces validation even if directory
mtime cannot distinguish the deletion. Report Make failures name
`build/us/objdiff-report/model-build.log`.

## Recovery and diagnostics acceptance, 10 October 2026

Validated the completed review-fix working tree based on `da1402e`:

- Docker focused suites pass: 17 model-build, 17 asset-Make, 105 objdiff
  (one ROM-opt-in skip), 15 profile-config and 16 RZIP tests; 170 total.
- Shell syntax, staged whitespace and canonical progress checks pass.
- All 22 model reconstructions reproduce 10,607 stored bytes exactly.
- A fresh `./conker build --assets` reproduces all 67,108,864 US ROM
  bytes, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- A fresh native report has no compile errors and retains identical measures
  for all 7,899 units, every category and the aggregate.
  Data remains 8,301,843 / 65,120,512 matched bytes (12.74843%).
- Source fingerprint:
  `103bf39b08136d58eb1bf740d909eae46266fc0922cd890ca46ad88a48211c27`.
- Native report SHA-256:
  `f19eca5a43d707b5bf79973a02f00ff081117cce21c8fa4e632ad7422183ce80`.

These checks cover explicit backup/recovery, failed-publication rollback,
preservation of orphaned records, missing-bank diagnostics, logged Make failures,
ROM mismatch rejection before output, precise rebuild dependencies, and layout
classification validation. The complete repository suite was not rerun locally
for these review fixes. Logs and the accounting audit are retained privately in
`build/us/models/validation/review/`; generated artifacts remain ignored.

## Bank-09 expansion

The expansion is based on main `f55e9d1` and adds 57 direct models from indexed
bank 09, ROM range `0x1204780–0x125CED0`. The selection is explicit in
`config/model_build.us.json` (contract schema 2, `banks.09`); individual source
bundles retain schema 1, so the existing bank-03 inputs remain compatible.
`config/profiles/us/assets/models09.yaml` partitions the bank into 111 spans.
These include 57 selected compressed records and 54 retained raw spans. The
index, gaps and all other records remain unmatched.

The selected models reconstruct 31,272 decoded bytes and 17,609 stored bytes.
All 296 direct bank-09 models were inspected with the existing parser. These
57 exhaust their complete decoded extent with ten header words, 16-byte vertex
records and eight-byte display-command pairs. The other 239 direct models have
additional regions or trailing storage and are excluded. Attachments, effect
containers, emission-point sets and unclassified records are also excluded.
No copied compressed stream or opaque tail is an editable reconstruction input.

Fifty-five selected models use unsegmented model-relative vertex addresses;
entries 426 and 431 use segment 1. The existing
[bank-09 consumer proof](../assets/models/us_bank09_relative_models.md)
pins the complete ROM-derived spans of `func_1518C900`, `func_15168E54` and
`func_15168E34`. The build rechecks those hashes before accepting bank 09.
Only bank 09 enables relative vertex parsing; command words are serialized
unchanged, and vertex alignment, cache bounds, model boundaries and the final
EndDL remain checked. This establishes native storage reconstruction, without
asserting model names or complete runtime appearance.

Build inputs now live at `build/assets/model-build/us/<bank>/<entry>/`.
Linker objects, report keys, source proofs and recovery backups include the bank,
so equal entry IDs cannot collide. Recovery requires an explicit `--bank`
selector, including for bank 03:

```sh
./conker model-assets recover --bank 9 --entry 2
./conker model-assets build
./conker build --assets
./conker objdiff report
```

The ordinary build continues to collapse both model groups to their original
bank inputs. Rebuilt mode tracks missing or edited source files separately for
each bank. Each Make target validates and publishes its own bank, with independent
stamps and receipts under `build/us/models/bank<bank>/`. Bank-09 consumer checks
do not block bank-03 builds or recovery. `./conker model-assets build --bank 3`
and `--bank 9` provide the same isolation; omitting `--bank` validates both banks
before publishing any parts and writes the combined `build/us/models/batch.json`
receipt. Native reporting compares actual linker objects against independently
wrapped original ROM slices. Data gains only the 17,609 newly reconstructed
stored bytes; its 65,120,512-byte denominator is
unchanged. Generated inputs, ROMs and reports remain ignored.

### Bank-09 acceptance, 10 October 2026

Validated the completed working tree based on main `f55e9d1`:

- All 79 models exactly reconstruct 52,232 decoded bytes and 28,216 stored bytes.
- Rebuilt entries plus retained raw intervals reproduce the complete 62,440-byte
  bank 03 and 362,320-byte bank 09.
- The fresh `./conker build --assets` passes; all 67,108,864 ROM bytes equal the
  original, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Focused Docker suites run 162 tests: 24 model-build, 18 asset-Make, 105 objdiff
  and 15 profile tests. There are 161 passes, one ROM-opt-in skip and no failures.
  The complete repository suite was not rerun for this expansion.
- The fresh native report contains 7,956 units and no compile errors. All 79
  model units are fully matched and complete, totaling 28,216 stored bytes.
- Native Data is 8,319,452 / 65,120,512 matched bytes (12.775471%); 8,318,684
  bytes are complete (12.774292%). The increase is exactly 17,609 bytes;
  the denominator and Code measures are unchanged.
- Canonical progress and whitespace checks pass. No C sources, function
  inventories or source-unit ownership records changed.

Source fingerprint:
`ac011557cab70f46216ec2e8527b373784c411fb2898bed52d6920095a706c0a`.
Native report SHA-256:
`ff9c48f47d34767de84f28f5e2f42d1b3674a69b21bf773e547a59c677872a1a`.

Private logs and byte/accounting audits are under
`build/us/models/validation/expansion/`; native report/source/link proofs are
in `build/us/objdiff-report/`. These results apply to the completed working
tree, not an additional committed revision.


### Bank isolation and review acceptance, 10 October 2026

Validated the completed review-fix working tree based on `5e522ed`:

- Required bank arguments reject omitted selectors; recovery requires `--bank`.
- The real Makefile test builds both banks in parallel, preserves unchanged
  outputs, isolates edits and missing parts, and allows bank-03 rebuilding when
  bank-09 validation fails. Asset ordering follows the ROM storage map.
- Docker suites pass: 26 model-build, 19 asset-Make, 15 profile-config,
  10 ROM-build-mode and 27 objdiff-data tests; 97 run, 96 passed and one
  ROM-opt-in skip. The complete repository suite was not rerun for this follow-up.
- Fresh per-bank receipts validate all 79 models: 52,232 decoded bytes and
  28,216 stored bytes, with the original decoded/stored hashes and ROM bytes.
- `./conker build --assets` passes; all 67,108,864 US ROM bytes equal the
  original, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Canonical progress, shell syntax and whitespace checks pass.

At this checkpoint, the native report from expansion commit `5e522ed` was
retained as historical evidence rather than regenerated. The bank-slot acceptance
below supersedes that report validation with a fresh run. The reviewed selection,
record format and stored byte totals are unchanged. Private validation logs,
tested source hashes and the byte comparison are under
`build/us/models/validation/pr92-review/`.

Full game-archive decoding remains part of the bank-09 consumer check. A ten-run
host benchmark measured a median 8.22 ms for decoding versus 1.059 s for the
complete 79-model review (under 1%). This follow-up keeps the existing verifier
rather than introducing a cache or another archive decoder.


### Bank-slot and fresh-report acceptance, 10 October 2026

Validated the completed follow-up working tree based on `e875625`:

- Model bank slots fall back to their original raw bank inputs when their profile
  entries are no longer reconstruction groups. Make tests cover either bank raw,
  both raw, exact storage ordering and linking the original bytes without packing.
- Docker suites pass: 20 asset-Make and 10 ROM-build-mode tests, with no skips
  or failures. These are the affected suites for this Make-only follow-up;
  the earlier model, profile and objdiff tests remain recorded above.
- A fresh `./conker build --assets` passes. Direct comparison confirms all
  67,108,864 US ROM bytes equal the original, SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- A fresh `./conker objdiff report` passes, with independent full-disassembly
  reference verification, per-unit coverage validation and no compile errors.
  All 79 model units are fully matched and complete, totaling 28,216 stored bytes.
- All 7,956 unit measures, category measures and aggregate measures equal the
  previous report. Data remains 8,319,452 / 65,120,512 matched bytes (12.775471%).
- Native snapshot status is `current`: the source fingerprint and editable asset
  hashes match this tree. Canonical progress and whitespace checks also pass.

Source fingerprint:
`e51fcd7b1dda7d7529244cb9d2ac83a1281f755cd2df6670e83a049a46b8831c`.
The newly generated report has the same SHA-256 as the earlier report because
all report contents remain identical:
`ff9c48f47d34767de84f28f5e2f42d1b3674a69b21bf773e547a59c677872a1a`.

Validation ran before committing these identical source inputs. Documentation
and tests are outside the native source fingerprint. Logs, the preserved prior
report and the independent byte/accounting audit remain private under
`build/us/models/validation/pr92-final/`.


## Normal-table expansion

The new selection adds 142 models and 90,508 stored bytes to the reconstruction
contract. The complete selection encodes 206,264 decoded bytes into 118,724
stored bytes; decoded bytes are not a second report allocation. Per-entry ROM
ranges, hashes, normal-table counts, suffix sizes and excluded-entry reasons
are recorded in [the selection audit](us_model_normal_reconstruction.json).

Each admitted `DC38000E` command references a complete 64-byte table of 32
signed X/Y byte pairs, using the [existing normal consumer
contract](../assets/models/us_asset_inventory.md). Signed Z remains in the
vertex flag. The structured `normal_xy_s8` field preserves all 32 slots,
including unused slots and zero vectors. No preview-normal normalization or
fallback enters reconstruction. Unique referenced tables must cover the
region immediately after the primary display list with no gaps or overlaps.
Every pointer and extent is rechecked during encoding.

Some records have exactly eight zero bytes after the primary list or final
normal table. `zero_suffix_bytes: 8` records this observed suffix explicitly;
the encoder regenerates zeros. This is not an inferred alignment requirement.
Nonzero suffixes, other lengths, auxiliary header regions, unreferenced normal
blocks and incomplete blocks remain unsupported. The original simple record
schema remains unchanged for existing editable inputs.

All admitted entries must re-encode their complete decoded payload and freshly
compress to their independently checked original stored bytes. Entries whose
compression differs stay excluded; original compressed data is never used as
a candidate fallback. The existing bank partitions, Make recipes and native
objdiff candidate path consume the expanded reviewed selection.

### Normal-table acceptance, 11 October 2026

- The 221 models rebuild all 206,264 decoded bytes and 118,724 stored bytes
  exactly. Independent bank assembly reproduces the complete 62,440-byte bank
  03 and 362,320-byte bank 09.
- Mutating a signed normal value is rejected by the original-payload gate in
  all 101 selected models with normal tables. Focused Docker tests cover
  pointer gaps, overlaps, truncated tables, explicit suffixes and invalid values.
- `./conker build --assets` passes. An additional direct comparison confirms
  all 67,108,864 ROM bytes equal the original, SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- The full Docker suite on the isolated PR batch runs 2,346 tests with eight
  skips and no failures. The focused model suite passes all 29 tests.
- A fresh `./conker objdiff report` validates 8,098 units with no compile errors.
  All 221 model units are fully matched and complete: 118,724 stored bytes.
- Native Data is 8,409,960 / 65,120,512 matched bytes (12.914456%); 8,409,192
  bytes are complete (12.913277%). Both counts gain exactly 90,508 bytes over
  the previous 79-model report; the denominator is unchanged.
- Native snapshot status is `current`; source and editable-asset fingerprints,
  canonical progress and staged whitespace checks pass.

Source fingerprint:
`dfd22940e4137902934774a0d023da38e575bab19caab468d900876f1abdb73f`.
Native report SHA-256:
`4092d2f4e502558a2448c2027ab71ae1c73de8ec7ed045546b0f5a7b763c8a7b`.

Validation ran before committing the same source inputs. Documentation and tests
are outside the native source fingerprint. Private logs are `build/model-normal-*`;
ROMs, editable model records, objects and reports remain ignored. This is local
verification; publishing the PR does not publish the native report.
