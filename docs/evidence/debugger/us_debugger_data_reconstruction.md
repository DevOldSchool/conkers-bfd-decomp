# Debugger UI data reconstruction

The UI source supplies 1,408 `.data` bytes at `0x160036F0..0x16003C70`
and 2,848 `.rodata` bytes at `0x16003CE0..0x16004800`. Together with the
[formatter's 464 bytes](debugger_printf_rodata.md), this covers all 4,720
loader-proven initialized bytes. The canonical profile places each actual C
section into the allocated debugger image, retaining its original ordering.

The definitions reconstruct four six-byte controller slots, pointer tables,
register descriptors, initial state, four 32-word TLB buffers, callbacks, decimal
powers and three video records. Unresolved reserved storage remains explicitly
reserved, including the `0x80500000` word; zero bytes are not reclassified as BSS.
The video record's 72 coefficient bytes retain the independently reviewed
comparison with main's VI records without claiming an unproved SDK structure.
Definitions and compiler alignment reproduce the complete original section.

`scripts/debugger_assets.py` extracts 96 eight-by-eight monochrome glyphs into
an editable 128-by-48 PGM atlas, and 109 strings into JSON. These local inputs
and their generated C include live under ignored `build/us/debugger-assets/`.
Repacking reads those editable files, not original encoded bytes; it preserves
bit order, reviewed string addresses, terminators and alignment. Existing edits
are not overwritten. A changed pixel or string reaches the actual C object and
is rejected by ROM verification if it differs from the original. No extracted
asset or generated include belongs in a commit.

`compile_c.py` prepares the include for focused compiles; the Make dependency
also refreshes the actual linker object after input changes. Native report
provenance records both editable inputs and checks they stay unchanged through
generation. Candidate storage, relocations and symbols must equal the actual
runtime linker object, and the complete allocated debugger image must equal the
checksum-validated ROM.

The existing address-alias comparison now accepts these allocated sections only
at their canonical placements. It requires the entire source unit's text and
every owned data section to match the ROM before emitting the bounded comparison
object. The independent full-span `CURRENT (0)` and layout gates still apply.

Native data comparison uses the pinned, locally maintained objdiff full-section
patch documented in `toolchain/patches/README.md`. The report has no artificial
symbols, cropped sections or edited percentages. TLB completion is separately
proved as [maintained original assembly](us_debugger_tlb.md). Its source object
may earn native matching credit while remaining excluded from C-only statistics.

## Initial data completion validation on 2026-10-11

Validated on `codex/debugger-completion`, based on commit
`fc0d8b90418f64c41a299c38d6d27a8a37d74dad`, with uncommitted source changes.
Before promotion of TLB to maintained assembly, the production
`./conker objdiff report` completed successfully and its snapshot reader returned
`current` for the following source fingerprint. The maintained-assembly
validation below supersedes this snapshot. Source fingerprint:
`b0e90683f28eec1a8233c7a05a2d0961d1ee6035b790b9044093193035bf29d3`.
Native report SHA-256:
`e2548c9428f3dec826ce7e916403a51e2d7cd349b92ce7cf70807c85c0551488`.

| Debugger measure | Verified result |
| --- | ---: |
| Linked code | 14,040 / 14,040 bytes (100%) |
| Matched and linked initialized data | 4,720 / 4,720 bytes (100%) |
| C-matched code | 13,888 / 14,040 bytes (98.91737%) |
| Complete report units | 3 / 3 |

The report excludes 24 independently verified zero alignment bytes from its
code denominator. Runtime verification includes all 14,064 loaded code bytes
and all 4,720 data bytes. The remaining 152 instruction bytes are the verified
TLB assembly routine; its registered proof also includes eight alignment bytes.
There are no debugger completion downgrades and no report compile errors.
Unmatched data in other overlays remains subject to the existing completion
downgrade rules.

All 38 registered debugger C spans passed fresh full-span `CURRENT (0)` and
layout/progress/whitespace gates. A clean 39-item `verify-batch`, including the
TLB original-assembly proof, returned `BATCH_COMPLETE`; its host suite passed
2,462 tests with 53 skips. The full Docker suite passed 2,461 tests with nine
skips. After the final report-only reference and build-order repairs, all 121
focused objdiff tests passed with four skips. The patched native executable
also passed ten independent positive and negative synthetic ELF regressions.

`./conker build --assets` produced a byte-identical US ROM with these debugger
sources and placements (exit 0, 673 seconds including setup). The ordinary
US ROM build also passed. Later fixes change report preparation only: original
reference data is linked and verified separately, and runtime preparation runs
before code snapshots so main's mandatory object refreshes cannot stale them.
All final input hashes, native coverage checks and report round-trip checks
passed. Shared build/report tooling changed; no shared C headers changed.

Local logs, per-function rechecks, candidate history and the clean batch list
are under `build/us/manual-attempts/debugger-completion/`. The final report run
is `production-report4.log`; generated reports, ROMs and extracted assets remain
ignored and are not evidence files to commit. This validation does not publish
the report to decomp.dev.

## Maintained assembly completion validation on 2026-10-11

The final production report on the same branch and base commit includes
`src/debugger/tlb.s` as maintained source and labels it **Original assembly**.
The source is assembled separately from the independent reference; its object
is identical to the actual runtime linker input. All 160 allocated bytes match
the checked ROM, and native objdiff matches all 152 instruction bytes. The
function inventory remains `original_asm`, excluded from C-only matching.

| Debugger measure | Verified result |
| --- | ---: |
| Matching code | 14,040 / 14,040 bytes (100%) |
| Linked code | 14,040 / 14,040 bytes (100%) |
| Matching initialized data | 4,720 / 4,720 bytes (100%) |
| Linked initialized data | 4,720 / 4,720 bytes (100%) |
| Matched native functions | 42 / 42 |
| Complete report units | 3 / 3 |
| Original assembly matching and linked code | 152 / 152 bytes (100%) |

`./conker objdiff report` exited successfully, with no compile errors or
debugger completion downgrades. The snapshot reader returned `current`.
Unrelated SDK data downgrades remain in force. All native coverage, round-trip,
source-hash and object-hash checks passed. Source fingerprint:
`f25b18b8694f15eb84075ad50ded3728837688126322d1fd6b0433648ca672ec`.
Native report SHA-256:
`03fd591cc2e8c00efedd5ec0274ed5b455082c0048f6b193ebcab02546109465`.
Preparation took 892.87 seconds; native report generation and validation took
8.73 seconds. These are report-tool timings, not total interactive task time.

The maintained source passed a fresh clean
`CONKER_TEST_RUNNER=host ./conker verify-batch func_16003650` with
`BATCH_COMPLETE`, an ordinary byte-identical US ROM, full debugger code/data
verification, progress and whitespace gates, and 2,468 host tests (55 skips).
After the report-only address-label resolution fix, all 124 focused Docker
objdiff tests passed (two skips). Negative cases reject changed instructions,
padding, relocated buffer addresses, runtime objects, missing maintained source
and incomplete report proofs. The prior 38 C full-span matches remain unchanged.

A fresh `./conker build --assets` also produced a byte-identical US ROM with
maintained TLB assembly (exit 0; 705.27 seconds for the build, 716 seconds
including setup, SDK and Docker). The tested base is
`fc0d8b90418f64c41a299c38d6d27a8a37d74dad` with the uncommitted inputs identified
by the source fingerprint above. Shared build/report tooling changed; no shared
C headers changed.

Local evidence logs are `tlb-maintained-batch2.log`,
`tlb-maintained-assets.log`, and `tlb-maintained-production-report.log` under
`build/us/manual-attempts/debugger-completion/`. Generated reports and extracted
assets remain ignored. This validation does not publish the report to decomp.dev.
