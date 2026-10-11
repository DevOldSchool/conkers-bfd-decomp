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
live under ignored `.conker/debugger-assets/us/`, outside `make clean`. Only the
generated C include lives in `build/us/debugger-assets/`. Existing input pairs
from the old build directory are copied without overwrite on first preparation
or before `make clean` deletes generated files. Partial input sets stop preparation
and cleaning with an actionable error instead of re-extracting or discarding data.
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

Native data comparison uses the checksum-pinned, unmodified objdiff release.
The report has no artificial symbols, cropped sections or edited percentages.
The independent allocated-image check establishes byte equality separately from
objdiff's symbol-based data matching. TLB completion is separately proved as
[maintained original assembly](us_debugger_tlb.md), excluded from C-only statistics.

## Stock objdiff validation after review

The locally patched objdiff implementation and its 100% data/completion claims
have been withdrawn. The repository uses the checksum-pinned official v3.8.1
release. No Cargo build, custom data-diff option, artificial symbol or edited
native measure is required.

| Debugger measure | Stock result |
| --- | ---: |
| Matching code | 14,040 / 14,040 bytes (100%) |
| Matching initialized data | 112 / 4,720 bytes (2.3728814%) |
| Linked code | 152 / 14,040 bytes (1.0826211%) |
| Linked initialized data | 0 / 4,720 bytes (0%) |
| Matched native functions | 42 / 42 |
| Complete report units | 1 / 3 |
| Original assembly matching and linked code | 152 / 152 bytes (100%) |

Stock objdiff's data accounting does not cover the anonymous initialized bytes.
The existing per-unit completion rule therefore downgrades both C units; only
TLB is complete in the native report. This does not contradict the separate
runtime check: all 14,064 allocated code bytes and all 4,720 initialized data
bytes reproduce the checksum-validated US ROM. Native code totals exclude 24
verified alignment bytes. This change does not claim 100% native data or linked
completion, and does not alter the completion policy to obtain those values.

Main at `84ff754fe52c9c6dde5f469b6cce5e7bf8bcb6a5` was merged into the branch
as `d18f560eba32ea5cb2dfbd5c8cddce0e9a011172`. On that base with the review fixes,
`./conker test` passed all 2,493 tests (eight skips) in the new native ARM64
container. `./conker build --assets` produced a byte-identical US ROM, exit 0,
in 126 seconds including setup, SDK and Docker. The earlier clean 39-item batch
returned `BATCH_COMPLETE`, with full-span C and original-assembly, layout,
progress, whitespace and ordinary US ROM gates; its 2,483 host tests passed
with 56 skips. The review fixes change tooling and the generated include path,
not the debugger C function bodies or maintained TLB instructions.

The regression suite covers persistent input migration, actual `make clean`,
partial-input preservation, side-effect-free compile command construction,
missing or misplaced candidate sections, encoded relocation addends, preserved
objdiff options and reference-layout drift. ROM-free CI compilation also passed
locally for all 747 C files before the main merge; it does not establish matching.

Report provenance for the final reviewed inputs is recorded below. Generated
reports, ROMs, extracted assets and local logs remain ignored. Nothing has been
published to decomp.dev. Local logs are under
`build/us/manual-attempts/debugger-completion/`.

The final `./conker objdiff report` exited 0 and the snapshot reader returned
`current`. It reported no compile errors; both C debugger units were downgraded
for native data matching, as described above. All coverage, source/object hash
and native round-trip checks passed. Tested base: `d18f560eba32ea5cb2dfbd5c8cddce0e9a011172`
with the staged review fixes. Source fingerprint:
`00f5a552f64881745a7720549d510fb9edf756da9fe3a1a87fb8ef95f2f97ed2`.
Report SHA-256:
`aec19065a12749ad0b555ee9856209456ef4e6244028cfa4652074c5bd894aec`.
Preparation took 268.18 seconds and native report/validation
took 9.63 seconds. These are tool timings, not
total interactive work time. The log is `review-stock-report-final.log`; the
asset and test logs are `review-main-assets.log` and `review-main-tests2.log`.
