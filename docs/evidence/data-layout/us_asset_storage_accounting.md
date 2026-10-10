# US bounded asset storage in the native Data denominator

The report now includes known storage even when no reconstructed candidate exists.
The previous font/texture/model selection omitted most model, animation and audio
storage, making roughly 97.64% matched misleading as an asset-wide measure.

The checksum-validated US ROM is 67,108,864 bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. All endpoints are exclusive.
The [storage map](us_asset_storage_map.md) documents the original boundary evidence.

| Included storage family | Bytes | Evidence |
| --- | ---: | --- |
| Flat assets | 9,494,881 | Exact RZIP consumption from `0x1A37E0` to `0xAB1941` |
| Model banks `01`, `03`, `04`, `09` | 2,992,648 | Original outer-table bank extents, including inner indices/gaps |
| Animation bank `02` | 4,052,696 | Original outer-table extent |
| Audio banks `16`, `17` | 46,472,440 | 23,586,160 MP3-bank bytes plus 22,886,280 sound-bank/sequence bytes |
| Other asset storage | 1,906,215 | Remaining banks, font, 15-byte flat alignment gap and 240-byte outer index |
| **Stored assets** | **64,918,880** | Font plus complete interval `0x1A37E0–0x3F8B800` |
| Initialized CPU data | 201,632 | Independent main/GAME/debugger loaded-image audit |
| **Data denominator** | **65,120,512** | Stored assets plus initialized CPU data |

## Accounting and credit

`scripts/objdiff_storage.py` checks the ROM checksum, exact flat-stream end and
outer/inner bank boundaries. Optional bank-family evidence labels come from the US
`asset_bank_categories` map in `config/rzip_layouts.json`. Unlabelled banks are
recorded as `unclassified`; labels do not affect report filters or byte accounting.
The map accepts nonempty string labels without a fixed vocabulary or a requirement
to classify every bank. It partitions 34 disjoint regions. Every rebuilt
font, texture or model range must belong wholly to exactly one region, have the
claimed size, and overlap no other rebuilt range. Subtracting those ranges leaves
the exact unmatched complement, including metadata, indices and gaps. Future
reconstruction within these regions replaces unmatched storage without growing
the denominator.

Each region's remaining spans are concatenated in ROM order into one independent
ELF target using the ordinary binary linker wrapper. Its allocated data must
match those original bytes exactly. The coverage proof records every physical
span; concatenation does not claim contiguous storage or original object ownership.
These 33 remainder units have no base object and are explicitly incomplete.
Native objdiff measures their bytes; the generator never patches native totals.
Validation rejects any credit, candidate or completion for these remainder units.

The existing reconstructed font (5,440 bytes), textures (8,284,692 bytes) and
models (28,216 bytes) retain their actual linker-input, fresh encode, independent
reference and source-stability checks. A copied raw asset or rewrapped encoded
MP3 stream does not automatically earn reconstruction credit. Model storage
categories describe bank families, not a count of visually finished models.
Embedded textures and decoded subresources do not create additional ROM storage.

## Explicit exclusions

This is a complete denominator for the bounded asset regions above, not every
byte in the ROM. Unassigned regions after main (80,480 bytes), after debugger
(1,016 bytes), and after the final bank (477,184 bytes) remain outside scope.
BSS, RSP and untracked boot code are excluded. GAME's compressed code/data archive
backing is not added to the decoded CPU-code/data measures; its container metadata
and gaps remain excluded too. Adding Code and Data therefore does not reconcile
to the physical ROM size. A lower percentage records newly counted work, not lost
matches.

## Validation

The results below are the original accounting checkpoint. The later
[bank-09 expansion](us_model_reconstruction.md#bank-09-expansion) adds 17,609
matched model bytes without changing the storage denominator.

Reproduce with `./conker test -p 'test_objdiff*.py'`, `./conker objdiff report`,
`./conker progress check` and `git diff --check`. Regression tests exercise
checksum and boundary failures, duplicate/overlapping/outside candidate ranges,
full and partial subtraction, byte-exact independent targets, and denial of raw
copy credit. Generated objects, reports and ROM slices stay ignored.

The preceding model reconstruction commit `4c86e22` passed the complete
byte-identical US `./conker build --assets` gate. This follow-up changes report
accounting, documentation and tests only; no reconstruction or ROM link inputs
change.

Local acceptance on 10 October 2026, on the completed working tree based on
`4c86e22`:

- Native Data: **8,301,843 / 65,120,512 matched bytes (12.74843%)**;
  8,301,075 complete bytes (12.747251%). No compile errors.
- All 7,866 pre-existing units retain identical native measures. The 33 added
  storage units total 56,618,141 bytes, with zero matched/complete data or code.
- Code remains 530,588 / 2,246,328 matched bytes (23.620237%).
- The 104 focused objdiff tests pass in Docker (one ROM-opt-in skip). All 17
  asset Make tests pass on the host, including the CI logging-race regression.
- Canonical progress and staged whitespace checks pass.
- Snapshot source fingerprint:
  `8b438f8c8f8654e8ac8575ab43bb0e3ba11e4c632229376bce2068d97774747c`.
- Native report SHA-256:
  `f19eca5a43d707b5bf79973a02f00ff081117cce21c8fa4e632ad7422183ce80`.

Private logs and the before/after audit remain under
`build/us/data-boundaries/storage-report-validation/`. The PR records the
committed revision containing these identical tested inputs. This local report
is not published until the protected report workflow uploads it.

The recovery/diagnostic follow-up was revalidated against this snapshot:
all 7,899 native unit measures, categories and totals remain identical, and the
complete US asset ROM remains byte-identical. The current report source
fingerprint is `103bf39b08136d58eb1bf740d909eae46266fc0922cd890ca46ad88a48211c27`. See the
[review-fix acceptance results](us_model_reconstruction.md#recovery-and-diagnostics-acceptance-10-october-2026).
