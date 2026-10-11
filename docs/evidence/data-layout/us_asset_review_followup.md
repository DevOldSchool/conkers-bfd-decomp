# PR 96 asset review follow-up

This follow-up preserves the reconstructed assets and their native Data credit.
It addresses the review of model/audio builders and report plumbing; it adds no
asset selection or ROM data.

## Review dispositions

| Finding | Change |
| --- | --- |
| Malformed attachment/effect row sizes escape as tracebacks | Boundary re-parsing converts native row errors to `ValueError`, allowing the normal input-preservation and recovery message. Regression tests retain the edited files. |
| CPU-bound ADPCM report workers use threads | Native source decoding and fresh report encoding use processes, with `CONKER_JOBS` controlling concurrency. The report ROM is passed once per worker, not once per sample. |
| One changed WAV re-encodes every sample | The batch builder reuses individual outputs only when the encoder fingerprint, complete source hashes, reviewed extents and stored-byte hashes agree. Missing outputs, malformed receipts or changed inputs force fresh encoding. |
| Copied gzip wrapper and texture-specific error | `rzip_gzip.py` owns GNU gzip version, level, wrapper, checksum and decode validation for levels six and nine; diagnostics refer to asset builds through `./conker`. |
| Retired frame-run ADPCM format | `adpcm_layout.py` accepts only complete samples; the Makefile no longer excludes legacy raw gaps. Retired contracts are rejected explicitly. |
| Copied report functions | A shared helper checks actual linker candidates, builds independent original targets, validates extents and records source/link hashes for models, sequences, sound banks and samples. |
| Copied source/recovery scaffolding | `asset_inputs.py` owns manifest hashing, batch source rechecks and staged recovery/rollback, including complete-tree recovery. Format-specific encoding and publication remain explicit. |
| Repeated native consumer checks | `audio_consumers.py` owns the common loader span and verification loop. Boundary verification checks shared sound/sample consumers once. |
| Repeated native constants and effect range | Model builders use the existing move-memory command constant; effect selection uses one named range. |
| Migration error only suggests individual recovery | ADPCM errors retain the individual command and also explain `recover-adpcm --all` for schema migration. |

## Incremental builds and independent report checks

A single Make batch remains intentional: it checks all inputs before publishing
any changed output. Incrementality is inside the builder, at sample granularity.
The receipt is disposable build state, not new source data or report evidence.
Every invoked packer checks source contents, even when timestamps are unchanged.
Existing malformed or partial source folders still fail without replacement.

Reports deliberately bypass build receipts and freshly encode all samples.
Otherwise an edited receipt could falsely associate current sources with an old
object. Process workers reduce the CPU serialization cost while preserving the
independent source-to-object comparison, final source-hash checks and original
ROM targets. Full consumer checks and every sample extent remain required.

The focused tests cover unchanged builds, a metadata-only WAV edit, preserved
invalid PCM edits, missing/corrupt outputs, stale encoder fingerprints, malformed
receipts, report cache bypass, process spawn, shared recovery rollback and the
malformed model boundary regression.

## Acceptance

Validated against the inputs of this follow-up, with commit `30ff4115` as the
comparison baseline. The PR records the final tested commit; committing the
validated files does not change the report input fingerprint.

- `./conker test`: **2,448 tests, eight skips, no failures** in the pinned Docker runner.
- `./conker build --assets`: **all 67,108,864 US ROM bytes identical**, SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The command recorded 1,218 seconds
  including setup, SDK and Docker.
- `./conker objdiff report`: **10,868 units**, no compile errors and a current
  snapshot. Every unit's measures equal the baseline. The native report JSON is
  byte-identical too; this follow-up adds or removes no Code or Data credit.
- All **2,258 actual sample linker objects** reproduce **21,705,520 bytes**.
  All **23,522 editable asset inputs** retain their baseline hashes.
- Canonical progress, Python/shell syntax and whitespace checks passed.

Matched Data remains **32,056,153 / 65,120,512 bytes (49.225892%)**; complete Data
remains **32,055,385 bytes**. The local report generator recorded
1006.568 seconds of preparation and
10.322 seconds for report generation/validation;
these exclude wrapper setup and are not a controlled before/after benchmark.

Report SHA-256:
`db6efdc094dcbd4b03e7b95f7ff55d53f7fe44db8368d4fb7548cf5419f68ea2`.

Build-input fingerprint:
`5b219b0b596926d129dc42cd11b3b9903d2923b7ee2e9eb06170a401ab9838c1`.
