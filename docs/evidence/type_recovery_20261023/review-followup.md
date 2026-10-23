# PR 170 review follow-up (US, 2026-10-23–24)

The requested redundant-mask probe removes the entire retained +625 regression.
Dead-local cleanup gains another 38 points. This follow-up reduces the current
measured sum by **663**, with no candidate regressions or new matches. The
cumulative PR reduction becomes **4,030**; its prior 420-byte match remains
`func_1510B7B4`.

## Measurement

Source base: `fed0a221aa6dba4189e08bd084180ec3ab418f4c`.
Immutable baseline: [sdk-gfx-16ee20-final.tsv](sdk-gfx-16ee20-final.tsv), SHA-256
`96ff868459831b1849228a61b9ebf564cd7906f01838ea29f64170756e40af5f`.
Use its measured `new` column, not stale candidate annotations.

| Source | Candidates rescored | Before -> after | Reduction |
| --- | ---: | ---: | ---: |
| `effects/effects_sight.c` | 17 | 61,471 -> 60,846 | 625 |
| `game_32740.c` | 3 | 3,142 -> 3,124 | 18 |
| `game_476D0.c` | 3 | 3,380 -> 3,360 | 20 |
| `camera/camera_camera.c` | 15 | 39,341 -> 39,341 | 0 |
| `game_16EE20.c` | 23 | 42,888 -> 42,888 | 0 |
| **Touched cohort** | **61** | **150,222 -> 149,559** | **663** |

Paired read-only `probe` results, each a single targeted hypothesis:

| Candidate / change | Before -> after | Frame before -> after / reference |
| --- | ---: | --- |
| `151CAB78`: pass `mode` directly to the shared `u8` parameter | 2,182 -> 1,557 | 0xE8 -> 0xE8 / 0xE8 |
| `15005290`: delete dead `view_offset` recurrence | 2,472 -> 2,454 | 0x78 -> 0x70 / 0x70 |
| `1501B0A0`: delete write-only `temp_t8` | 1,506 -> 1,486 | 0x60 -> 0x60 / 0x50 |
| `15126378`: delete dead initial `target` assignment | 12,492 -> 12,492 | 0xE0 -> 0xE0 / 0xD0 |

All four remain deferred candidates. No permutation, assembly edit, compiler
flag change or inventory hand edit was used. All compiles, scoring, builds and
finish transactions were serial; two additional workers reviewed read-only.

## Review disposition

| Finding | Resolution |
| --- | --- |
| `GameRenderView` violates the default three-identical-copy promotion rule | Correct under the default rule. This task explicitly authorized recovery from differently named/padded views and matched field evidence; it is a task-specific recovery, not nominal copy promotion. The unchanged default rule still applies to ordinary matching. |
| `game_path.h` has no three local copies | Same distinction. Its shared eight-byte point contract comes from the reviewed matched readers and indexed-stride evidence in [spatial-point.md](spatial-point.md), not a claim of three identical typedefs. |
| Already-matched bodies changed beyond a type rename | Separately reviewed below: three address/type edits, including `1501A220` in addition to the two reported. All have independent full-span zero evidence. This follow-up adds no matched-body edits. |
| Avoidable `151CAB78` +625 regression | Fixed. `mode` is only 0 or 4; the existing shared `u8` parameter supplies the conversion. Score returns to the original 1,557. This supersedes the retained-regression rationale in [round.md](round.md). |
| Direct type headers are invisible to m2c | Not reproduced. `flattened_source_context` declines them and `prepare_m2c_context` selects IDO preprocessing. The generated context includes the complete shared type and root declaration. Corrected the workflow's fast-path-only wording; no global SDK include was added. |
| F3DEX selection depends silently on include order | Hardened. Preserve the two initial headers required by declaration discovery, reject an already-selected incompatible GBI by asserting `G_GEOMETRYMODE == 0xD9`. Moving the define ahead of both includes would hide the shared declarations from static discovery. The encoding check follows the mandatory source-unit metadata. |
| Private render views remain | Intentional boundaries, listed below. They are not identical copies that can all be deleted safely. |
| Some accesses remain raw | Opaque fields and required pointer/integer ABI conversions stay raw. The dead camera address assignment is removed. Further matched-body cleanup is not necessary for this correction. |
| Two unused locals remain | Removed `view_offset` and `temp_t8`. Only `view_offset` became unused in this PR; `temp_t8` was already write-only in the base. Both deletions improve scores. |

The task's relevant authorization was to recover layouts accessed under
different names or padded bytes, then "Replace the source-local copies and
the now-unneeded casts in matched and deferred code." This is broader than
the default nominal-promotion workflow. It does not authorize guessed fields,
nonidentical binaries or bypassing any validation gate.

## Separate review of existing matched address changes

| Function | Address/type equivalence and independent raw evidence |
| --- | --- |
| `15127EB8` | Old raw store and `D_800BE628[selector].field84` both store float 1.0 at `base + u8_selector*0x180 + 0x84`. Raw US 0x15127F0C..0x15127F30 confirms the byte selector, multiply and `swc1`. The access remains after `1510B32C`, so no root load moved across the call. |
| `1501A39C` | Old integer address and `(u32)&D_800BE628[0].viewports[i]` both emit `base + 0x40 + i*0x10`, with i limited to 0/1. Raw US 0x1501A44C..0x1501A468 and pinned `Vp` layout agree. |
| `1501A220` | Allocation remains `count*0x180` with arguments `(1,1,0)`. The explicit cast preserves the allocator's existing 32-bit integer return as a pointer. Raw US 0x1501A258..0x1501A278 computes the same size and stores v0 unchanged. |

The header layouts are unchanged. Prior independent checks are recorded in
[render-fields-validation.json](render-fields-validation.json); this
follow-up also rechecks all matched functions in their touched sources.
The new cleanup removes no observable operation: neither local contributes
to a retained result (`view_offset` is read only by its discarded increment),
and all later camera `target` reads follow a controller/actor pointer
assignment, including the comma expression inside the short-circuit condition.

## Remaining views and deliberately partial adoption

| Source-local view | Reason retained |
| --- | --- |
| `Game1A11B0View` | Width-only view; possible later cleanup, with no direct deferred-score exposure. |
| `Game13D350Record` | Matched users name an opaque payload at BC; adopting the matrix member requires another matched-body review. |
| `Game1AB530CameraInfo` / `Game1AB530DepthRange` | Camera adoption regressed 583 -> 663; the depth view also spells viewport members differently. |
| `Game1AC2F0FillViewportPrefix` / `Game1AC2F0Viewport` | Matched bounds names differ; deferred adoption encounters the existing `1517F564` extra-argument compile error. |
| `Game1D2480View` | Includes the height field at 08, still without the required matched-C evidence. |
| `GameC2350Viewport` / `GameC2350Record` | Its private twelve-slot view overlaps real calibration/projection fields. Only the first two viewport slots are justified. |

Raw offsets 0x34/0x38 and plane stores 0x88..0xB7 remain opaque. Display-command
integer addresses and the integer allocator-to-owner conversion are required.
The earlier `1501B0A0` field-adoption trial regressed 1,506 -> 1,516; removing
its unused local here is a different, directly reviewed hypothesis.
No remaining private view was promoted merely to make the conversion look
complete. See [render-fields.md](render-fields.md) and [sdk-gfx-16ee20.md](sdk-gfx-16ee20.md)
for earlier rejected or blocked adoptions.

## Validation

- All **123 existing matches** in the touched sources pass independent full-span
  US `finish` with `CURRENT (0)` and `STOP_MATCHED`: camera 30, effects 21,
  SDK source 65 and game_476D0 seven. The final SDK guard supersedes an earlier
  65 successful checks; all 65 were repeated after the guard correction.
- **66 before/after compiler pairs** cover five canonical sources and all 61
  separately activated candidates. All compile. Canonical sources have no
  warnings; the same nine deferred warning emissions remain, with none added.
- Live m2c context checks confirm `ido-preprocessed` with no error for render,
  path and view owners, including their definitions and root declarations.
  Static initial-header discovery remains intact.
- Both invalid GBI-order tests exit 1 with the intended hard compiler error.
  IDO treats `#error` and negative array bounds as nonfatal warnings (605/654),
  so the final guard uses a negative-bitfield constraint only under invalid
  selection. For valid F3DEX2 input that declaration is entirely preprocessed
  away. The static layout scanner records this diagnostic as an unsupported
  bitfield and excludes it from recovery clusters. Its initial placement was also corrected to preserve required
  source-unit metadata placement before the matched rechecks began.
- The [full final sweep](review-followup-final.tsv) has the same 1,383 rows,
  1,335 scores, 48 pre-existing error IDs and four pre-existing zero IDs.
  Raw score sum is **2,791,612 -> 2,790,949**. Only the three recorded scores
  improve; there are no regressions, new errors or new zeros. Removing the
  separately recorded 353-point coverage addition gives an original-cohort
  sum of **2,790,596**, a cumulative reduction of **4,030**.
- `CONKER_JOBS=1 ./conker verify-batch func_151C8674 func_15127EB8
  func_1501A220 func_15142B7C` reports **BATCH_COMPLETE**. Each touched source
  with existing matches has a nominee. `game_32740.c` has no matched functions;
  all three of its candidates compile and clean integration covers its
  retained assembly. The matching test subset passes: 1,062 tests, six skipped.
  The batch log has zero cfe warnings. The 2,072,880-byte US GAME image equals the independent
  ROM extraction byte for byte, SHA-1
  `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- Source hashes are stable through final compiler audit, focused checks, full
  sweep and batch. Progress and whitespace gates pass. There are no pending
  batch IDs.

Detailed check results and source hashes: [review-followup-validation.json](review-followup-validation.json).
The ignored reproduction ledger is `build/us/manual-attempts/pr170-review-20261023/`.
The next lead ranking is unchanged from [level-header.md](level-header.md).
