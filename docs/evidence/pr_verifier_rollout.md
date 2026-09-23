# PR verification rollout evidence — 2026-09-23

This records implementation validation, not an active protected GitHub check.
The public changes and private deployment bundle need publication and owner-side
activation as described in [CI](../ci.md).

## Reviewed inputs

- Public PR: https://github.com/DevOldSchool/conkers-bfd-decomp/pull/12
- Head: `5cefc17f41b4fe0e4e4005eaa89b3bbbd63802b9`.
- Base: `f2caf3aac99a5e6f9aaa796a674821101a97de0c`.
- Replacement public image:
  `ghcr.io/devoldschool/conkers-bfd-decomp-toolchain@sha256:b3e29a92f2c26f11a58fbafde2d5d3b1184416e21b635e07b2a6303591ed5c8b`.
- Dedicated status App: `5045941`.

## Validation results

| Stage | Result |
| --- | --- |
| Public image access | Anonymous index, manifest, configuration and layer download succeeded |
| Image import | OCI import preserved the exact published index digest |
| Compiler smoke | IDO and Mupen64Plus debugger smoke tests passed |
| Active C compilation | 719 tracked source units compiled without ROM access; disabled candidates stayed disabled |
| Python tooling tests | 1,080 tests completed successfully (11 skipped); the focused CI suite contains 21 tests |
| Metadata, progress, whitespace and workflow syntax | Passed |
| Clean US main image | Passed under both the old cached image and replacement image |
| Clean integrated game image | Initial runs failed `.game_rodata_b4080`; the symbol-boundary correction passed a clean `BATCH_COMPLETE` integration run |
| Focused function checks | All 1,072 existing C matches reported `CURRENT (0)` and both original-assembly proofs passed; eight targeted rechecks also passed in the clean batch |
| Independent host hashes | Corrected bounded reader passed against both real clean-build outputs on tmpfs; oversized output was rejected |
| Public App status / required-check migration | Not activated or reported as successful |

The old and replacement images have identical IDO `cc` and asm-processor
`build.py` SHA-256 values, matching asm-processor and splat Git revisions, and
the same MIPS linker version. Combined with compilation, smoke tests, the clean
main image, and the same game failure under both images, this supports using
the publicly retrievable replacement pin. The old `883d74...` manifest was not retrievable anonymously during this
check; its original publication history remains unconfirmed.

Docker Desktop's registry proxy rejected direct pulls on the local test machine.
A temporary pinned `crane` client downloaded the image anonymously; an OCI import
preserved its digest. Runtime checks used that exact image. No credentials were
needed for the download, and no ROM or build artifacts were uploaded.

## Clean-build integration correction

The rodata failure came from a lost raw-reference split at `func_15086C68`.
When its unit became a C range, the split-only empty body disappeared from the
raw map. A fresh reference absorbed its eight bytes into the preceding assembly
fallback, and the separate C stub emitted them again. Later functions moved by
eight bytes. Cached references concealed the duplication.

Six already-reviewed empty-body boundaries now have explicit function symbols
in `config/symbols/game-us.txt`; see the [boundary evidence](game_raw_reconciled_empty_stub_splits.md).
All six are exactly `jr $ra; nop` in the checksum-validated game image. A fresh
`game_B4080` object has zero function-offset mismatches. The six stubs plus both
affected switch functions passed one clean `verify-batch` with `BATCH_COMPLETE`.
No C bodies, raw instruction bytes, or match records were changed.

The next full run exposed an independent comparison-context issue at
`func_151B4C98`: its 56-byte registered span includes 12 bytes of terminal
alignment. The stripped interactive candidate has only the 44-byte body at the
end of its object; the complete compiled source unit contains all 56 bytes.
The private verifier now compiles each complete source unit once, checks its
reviewed symbol layout, and compares the unchanged full registered span against
the independent raw reference. It never invents padding or truncates the
reference. This change is private verification policy, not new match evidence
or a change to the interactive `finish` command.

Ordinary function-sized spans retain the project's focused compilation and
byte-verified address-alias proof, also cached per source. This preserves the
existing proof for equivalent labels such as `D_800C3EA0` and
`D_800C3D68 + 0x138` in `func_1502AB04`; unrelated assembly relocations in a
complete mixed unit can make that deliberately narrow alias proof ineligible.
Only spans longer than their emitted function symbol need the complete object
for actual alignment bytes. Both routes retain full registered-span comparison,
and the complete unit still passes the source-layout gate.

The final comparison run passed all 1,074 selected checks, both in-container
binary comparisons and generated-progress validation. Its original host-output
transport then failed because Docker's copy/archive API could not see the
tmpfs-backed files. The corrected reader captures a size-limited `head` stream
with a timeout and hashes it on the host; it never forwards binary data or
container diagnostics to the workflow log. A separate offline tmpfs test using
both real clean-build outputs passed their independently pinned host hashes and
rejected an oversized read. A fresh hosted run is still required before
activation; these local stages are not presented as one successful hosted run.

The inventory policy also pins registered addresses, spans, symbols, source
ownership, unit membership and integration modes to the trusted revision.
Match-state and evidence updates are allowed; a PR cannot redefine or shorten
its own reference span to bypass the comparison. Regression tests cover both
ordinary progress updates and rejected reference/layout changes.

## Activation decisions

The private repository plan does not support required environment reviewers.
Manual dispatch by `DevOldSchool`, an explicit reviewed-revisions checkbox, and
owner checks on every credentialed job form the approval boundary. Both
`github.actor_id` and `github.triggering_actor` are checked, including reruns.
Private repository writers remain trusted and must be restricted accordingly.

The first rules migration preserves the existing review-count policy and requires
only the named public aggregate and App-bound private US result. Add another
eligible code owner before opting into `--require-reviews`.

Before activation, publish/review the public changes, promote the resulting trusted tooling SHA in
the private verifier, and obtain a fresh owner-dispatched result for the new
head/base pair. Do not reuse the tested snapshot as evidence for later commits.
Raw private logs are deliberately excluded from this repository.
