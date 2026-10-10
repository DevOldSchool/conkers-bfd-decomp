# US bank-03 model reconstruction

The first model storage batch selects 22 direct bank-03 models from the
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
8-byte display-list commands. Each selected record ends exactly at its primary
display list and has no auxiliary regions. The input format preserves ten
native header words, signed position/UV components, unsigned flags and RGBA
bytes, and pairs of native command words. Unknown header or command semantics
remain uninterpreted; integer serialization preserves their bits. This is a
native record reconstruction, not an OBJ/glTF importer.

The bank contains 77 models. Twenty-five have this complete region layout;
22 reproduce their original compressed bytes with the reviewed zlib encoder.
Entries 1, 39 and 54 do not reproduce their original RZIP bytes with this
encoder; they and the 52 records with additional regions are excluded from
this first batch. No original compressed payload
is copied into a reconstructed candidate and no opaque tail is admitted.

## Build and report contract

`./conker model-assets build` initializes source records below
`build/assets/model-build/us/03/<entry>/` only when absent. Each bundle contains
`manifest.json` and `model.json`; existing incomplete or changed bundles fail
without being replaced. Initialization publishes a complete bundle atomically.
The packer validates every selected candidate and rechecks its source hashes
before replacing any linker inputs. Unchanged outputs retain their timestamps.

Every encode checks the full decoded size/hash and original compressed
size/hash. Edited geometry is retained but rejected by this exact-match build;
this command is not a ROM model-editing workflow. Compression drift fails
without choosing another encoder or falling back to original ROM bytes.

`./conker build --assets` links 22 reconstructed objects under
`build/us/assets/models/bank03/`. The ordinary default build continues to use
the original bank. Each native report candidate is copied from the actual
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
- Aggregate Data is 8,301,843 / 8,502,371 matched bytes (97.6415%);
  8,301,075 bytes are complete (97.63248%).
- Canonical progress and whitespace checks pass. No C-function inventory or
  source-unit ownership changes are part of this batch.

Report source fingerprint:
`46821402e8e6775c9ce634de08293ac5a785f5d583472ade3f41069f8331366f`.

Local logs are retained in `build/us/models/validation/`; the native report
and its per-file source/link proofs are in `build/us/objdiff-report/`.
These results apply to the working tree, not an additional committed revision.
