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

`compile_c.py` reads each compile source once and prepares the include for focused
compiles. In-process probe/permutation loops reuse unchanged preparation after
checking input and output contents; edits, metadata changes and deleted outputs
invalidate that cache; the Make dependency
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

## Stock objdiff validation after review at `49dfab93`

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

## Follow-up review validation on 2026-10-12

The second review tightened the remaining legacy SI mismatch fallback, moved
reference assembly hashes out of editable-source provenance, made debugger
layout loading lazy, and shared Make's runtime assembler settings with the
maintained-assembly candidate. Legal one-past-end pointer values still require
the full linked-ROM proof. Allocated image bounds now come from the shared
layout, and compile preparation reads source once and caches unchanged inputs
by content. Extraction uses exclusive creation to preserve concurrent edits.

Verified on `426b28349df232e8a83beaed62e6750e4e3467c5` with these review fixes. The full
Docker suite passed 2,501 tests (eight skips); the final nine-test relocation
suite also passed, including the added section-end-label case. A fresh
`./conker build --assets` returned a byte-identical US ROM in 125 seconds.
The stock report passed all coverage, source/object hash and native round-trip
checks, with no compile errors and the unchanged debugger metrics above.
Temporarily removing its generated TLB reference left the real saved snapshot
`current`; the reference was restored afterward. Its hash remains checked
during report generation. Removing `build/` itself also removes the local report.

Source fingerprint for that review:
`684f55ea7b05ee0843899da4895dd45187e8f8639ec588ca7f7f8554a975ef2f`.
Native report SHA-256:
`aec19065a12749ad0b555ee9856209456ef4e6244028cfa4652074c5bd894aec`.
Preparation took 302.00 seconds and report/validation
13.88 seconds. Logs: `review2-tests.log`,
`review2-assets.log`, and `review2-report.log` in the local evidence directory.

## UI symbol-boundary matching continuation

The next pass corrects the UI's reference payload boundaries using the existing
ROM/access map: 109 strings end at their first NUL, and the glyph array contains
96 eight-byte glyphs. The state scalars, arrays and pointer tables use the
reviewed reconstruction's extents. This prevents inferred symbols from absorbing
neighbors or compiler alignment. No section bytes are removed.

Six existing C definitions (five reserved-storage objects and the three-element
video-record array) now have global visibility so IDO retains their names in the
ELF symbol table. Their initializers, placement and bytes are unchanged. This is
a choice for the maintained reconstruction, not evidence of original source
linkage. Reserved words remain unresolved; their names do not assert their
original purpose or allocation. No symbol is injected into a compiled object.

Stock objdiff compares both complete UI sections at 100% after these changes.
An independent temporary reference link still reproduces all 4,720 original data
bytes. Comparing the old and new UI objects confirms identical `.text`, `.data`
and `.rodata` contents. Runtime verification additionally resolves all pointers
and checks the full allocated image against the US ROM.

The formatter remains a separate blocker; see the [bounded source experiments
and native comparison limits](debugger_printf_rodata.md#remaining-native-comparison-blocker).
PR #102 remains a draft at the user’s request. The figures in this subsection
precede the completion-policy correction recorded below.

### Verified continuation result

Tested `49dfab93c011bc624fbae080398a763958f69963` plus the UI definitions and
canonical symbol metadata described above:

| Debugger measure | Official v3.8.1 result |
| --- | ---: |
| Matching code | 14,040 / 14,040 bytes (100%) |
| Matching initialized data | 4,368 / 4,720 bytes (92.54237%) |
| Linked code | 7,008 / 14,040 bytes (49.91453%) |
| Linked initialized data | 4,256 / 4,720 bytes (90.16949%) |
| Complete units | 2 / 3 |

The UI unit independently reaches 100% matching and linked code/data. The
formatter is the only debugger completion downgrade; TLB remains 100% matching
and linked in its Original assembly category. The completion policy is unchanged.

All 38 registered C functions passed fresh full-span `CURRENT (0)` checks.
The clean 39-item debugger batch returned `BATCH_COMPLETE`, including the full
TLB span proof, layout, progress and whitespace gates, a byte-identical ordinary
US ROM and 2,502 tests run with eight skips. The additional `./conker build
--assets` returned a byte-identical US ROM in 105 seconds. No formatter C body,
TLB instruction, compiler flag, shared header or objdiff implementation changed.

The final report passed native round-trip, coverage and source/object hash
validation, with no compile errors; the snapshot reader returned `current`.
Its source fingerprint is `bb0f1b2901608b808703ba65a540d403b32969785fd482d4dc07b0ce913a4693`;
native report SHA-256 is `0d982015254daae703b8347c1812fd7f7aa85c3d8c11afdd216a053060a7ae8f`.
Logs and rejected experiments remain ignored under
`build/us/manual-attempts/debugger-completion/linked-*`.


## Completion-policy verification (2026-10-12)

This supersedes the earlier completion downgrades. Linked completion now follows
independent build/ROM proof; native matching remains a separate measurement.
The correction changes report policy, tests and documentation only. It does not
change C, assembly, compiler settings, object symbols or reconstructed assets.

| Debugger metric | Stock objdiff v3.8.1 |
| --- | ---: |
| Matching code | 14,040 / 14,040 bytes (100%) |
| Matching initialized data | 4,368 / 4,720 bytes (92.54237%) |
| Linked code | 14,040 / 14,040 bytes (100%) |
| Linked initialized data | 4,720 / 4,720 bytes (100%) |
| Matched functions / complete units | 42 / 42; 3 / 3 |

`./conker objdiff report` passed fresh generation, full reference images,
actual linker-input equivalence, runtime ROM proof, input hashes, native parser
round-trip and every coverage denominator, with no compile errors. Debugger
verification still covers all 14,064 allocated code bytes and 4,720 initialized
data bytes; 24 independently verified code alignment bytes remain outside the
native instruction denominator. Generation and validation took 289.96 seconds.

A before/after audit of all 10,866 report units found identical matched byte
counts, denominators, function comparisons and nonempty-section comparisons.
Completion changes only for the formatter and 14 previously eligible main SDK
units (15,388 SDK code bytes and 608 SDK data bytes). Three data-only VI objects
have empty `.text` sections whose displayed percentage changes from omitted/zero
to 100 via stock objdiff's completion fallback. They contain zero bytes and grant
no matching credit. Re-running stock objdiff on the same fresh objects with the
old completion flags reproduced the entire previous report exactly. Neither
production report was rewritten by the audit.

`./conker test -q -b` passed 2,504 tests with eight skips in 108.551 seconds.
Regression tests cover partial/zero native data matching with verified completion,
missing proofs, absent candidates, legacy configuration, unchanged measures and
stale source, linked and reference inputs. `./conker progress check` and whitespace
checks passed. Prior focused, clean-batch and reconstructed-assets verification
above remains applicable to unchanged build/source inputs; these were not rerun
as an empty function batch or claimed as new asset-build results.

The report was generated on `e4b6e8c3dca559d83dede3a4f510c6d7b6e925f9` plus
this policy correction, identified by the exact input fingerprint below:

- Source fingerprint: `c8f8e5ebb45ceab1580d1af068de2fa1033c101914b70819214ffe4024053870`.
- Native report SHA-256: `cee8d436182b00f17e649e144b16de4c0447b51793f58d5934ec730266e5eece`.

Logs, the previous report, the isolated old-flags control and the strict comparison
are ignored local evidence under
`build/us/manual-attempts/debugger-completion/completion-policy/`.
The report has not been published to decomp.dev. PR #102 remains a draft.
