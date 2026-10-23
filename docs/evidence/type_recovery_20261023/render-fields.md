# D_800BE628 render-owner field adoption (US, 2026-10-23)

Wider use of the existing `GameRenderView` fields reduces the measured deferred
score sum by **835**, from **2,792,094 to 2,791,259**, with four improvements,
no regressions and no new matches. The PR cumulative reduction is **3,367**;
its earlier `func_1510B7B4` match remains exact and is counted only once.

## Measurement

Continuation base: `d699b0863c0253da025c613b9cad66fcb38cfe91`.
The immutable comparison point is [spatial-point-final.tsv](spatial-point-final.tsv),
SHA-256 `f43ca9034a32cb16ac96347a6942594bcf1b4008acad785847affa2d7b9e4340`.
Comparisons use measured `new` scores, never stored inventory annotations.

| Retained source / candidate | Candidates rescored | Before -> after | Reduction |
| --- | ---: | ---: | ---: |
| `camera/camera_camera.c` | 15 | 39,941 -> 39,341 | 600 |
| `game_476D0.c` | 3 | 3,545 -> 3,380 | 165 |
| `game_138B40.c` | 1 | 635 -> 565 | 70 |
| **Retained source cohort** | **19** | **44,121 -> 43,286** | **835** |
| **Full sweep** | **1,334 scored** | **2,792,094 -> 2,791,259** | **835** |

The four improvements are `func_15126378` 13,092 -> 12,492,
`func_1501A764` 800 -> 675, `func_1501B22C` 1,239 -> 1,199 and
`func_1510B690` 635 -> 565. Their frames remain 0xE0, 0x38, 0x38 and 0xA0.
All other scores are unchanged. The [full final sweep](render-fields-final.tsv)
contains the same 1,383 deferred rows, 1,334 scores, 49 compiler-error IDs and
four pre-existing zero IDs. Those errors are outside the retained sources.
The scorer subprocess takes 116.9 seconds, excluding research, validation and
delivery. No compiler error is counted as a numerical improvement.

## Shared contract and evidence

This extends adoption of the existing [render owner](render-owner.md), without
changing its header, layout or matched member names. Matched `func_1510B070`
proves float fields at 0x0C/0x10; matched `func_1510B958` proves the scale/value
pairs at 0x6C..0x78. Matched `func_1510B458` and `func_1510B51C` establish the
float at 0x84, also written by matched `func_15127EB8`. Matched render users
and the SDK establish 0x10-byte `Vp` slots at 0x40 and 0x40-byte `Mtx` slots
at 0x100. Allocation and record addressing retain the 0x180 stride. The
previous pinned IDO/o32 layout probe remains applicable to the unchanged header.

- Camera code adopts shared scale and field84 accesses. Its `target` local
  remains a byte pointer because it later holds unrelated actor/controller
  views; the first scale reads cross no call or store.
- `game_476D0.c` removes local integer-root declarations. Matched allocation
  explicitly converts the existing integer allocator return to the shared
  owner pointer; the allocator ABI is unchanged. The matched viewport-command
  address uses the SDK array. Deferred projection reads preserve signed
  viewport halfwords at 0x44/0x4C. The plane writer uses shared value_x/value_y
  reads and retains byte views for the still-opaque 0x88..0xB7 stores.
- `game_138B40.c` replaces expanded matrix-address arithmetic with
  `&D_800BE628[index].matrices[buffer]`, preserving
  `base + index*0x180 + 0x100 + buffer*0x40`.

No local insertion/removal, statement reorder or control-flow reshaping was
used. Only three matched bodies have address/type changes: `func_15127EB8`,
`func_1501A220` and `func_1501A39C`; the other retained matched bodies are
unchanged. Two independent workers researched/reviewed read-only. All edits,
compiles, sweeps and inventory transactions were serial.

## Rejected trials and remaining opaque fields

[All bounded trial scores](render-fields-trials.tsv).

| Trial | Before -> trial | Why rejected |
| --- | ---: | --- |
| Camera-info owner, `func_1517EAAC` / `game_1AB530.c` | 583 -> 663 | +80 regression; restore entire source. |
| Projection writer, `func_1510B128` / `game_138520.c` | 1,759 -> 1,815 | +56 regression; restore entire source. |
| Calibration reads, `func_1501B0A0` / `game_476D0.c` | 1,506 -> 1,516 | +10 regression; restore its exact body and confirm final 1,506. |
| Culling-loop owner indexing, `func_151787AC` / `game_1A5C00.c` | 4,852 -> 4,527 | Discard the 325-point gain: required existing match `func_15178E14` reports `BLOCKED_TOOLING` before scoring. Restore entire source. |

The culling validation error is `game comparison member spans are not
contiguous and unambiguous`: registered `func_15178750` spans 92 bytes through
0x151787AC, while separately registered `func_151787A4` overlaps its final
eight bytes. The inventory is unchanged. No unchanged failing recheck was
retried and no metadata was altered to bypass the gate.

Raw US stores suggest float height (0x08), scale ratios (0x14/0x18), derived
scales (0x1C/0x20), viewport centers (0x34/0x38), aspect (0x60), projection
factors (0x7C/0x80) and four three-float culling normals (0x88..0xB7).
Their direct C producers/consumers remain deferred (`func_1501A8C0`,
`func_1501B22C`, `func_1510B128`, `func_150A6360`), so this is raw/deferred
corroboration, not the matched-C field evidence required for promotion.
Those ranges stay opaque. There is no established field evidence here for
0x00, 0x3C, 0xBA or 0xFC.

## Validation

- All **39/39 existing matches** in the three retained sources pass independent
  full-span `finish`: camera 30, game_476D0 seven, game_138B40 two. Each reports
  `CURRENT (0)` and `STOP_MATCHED`, including layout/progress/whitespace gates.
- **22 before/after pinned compiler pairs** cover three canonical sources and
  all 19 independently activated deferred candidates. Every compile succeeds.
  Canonical sources have no cfe warnings. The same two deferred warning-709
  call sites remain: `15122C5C` -> `15125A6C` and `15126378` -> `15127EB8`.
  No new warning is introduced. The raw audit has two extra pairs for the
  discarded game_1A5C00 trial; those are excluded from the retained count.
- `CONKER_JOBS=1 ./conker verify-batch func_15127EB8 func_1501A220 func_1510B7B4`
  supplies one matched nominee per retained source and reports
  **BATCH_COMPLETE**: 1,062 tests, six skipped, zero cfe warnings in its log.
- The 2,072,880-byte US GAME image is identical to independent ROM extraction,
  SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Retained source hashes
  remain unchanged through full sweep, rechecks and clean integration.

[Machine-readable validation](render-fields-validation.json) records the
source hashes, all matched checks, compiler pairs, score changes and rejected
validation. No pending batch IDs. No assembly, compiler flags, tooling,
inventory or asset inputs changed; no permutations. This validates GAME and
mapped-data integration and makes no new asset-reconstruction claim.
The ignored detailed ledger is `build/us/manual-attempts/render-fields-20261023/`.

## Next five investigations

Weights are measured exposure, not predicted gain. The first lead is a
compile prerequisite, so a repaired comparison point is needed before any
subsequent score credit. Previously rejected field substitutions should not
be repeated without a new hypothesis.

| Priority | Lead | Measured exposure | Next evidence needed |
| ---: | --- | ---: | --- |
| 1 | Render-source ABI gate in `game_16EE20.c` | Render reader `15144CEC`: 3,547; source scored sum 42,535 plus one baseline error | Deferred `15145EA4` uses `f32 **` outputs; later declaration uses `s32 *` and caller `1514654C` casts its `f32 **` values. Reconcile against raw calls before another owner trial. |
| 2 | `D_800B0DF0` level header | 13 candidates / 43,380 | Concrete callback/count/dimension/transition roles; most current access widths already agree. |
| 3 | `func_151A8B20` signature | 2 / 5,439 | Matched `void *(void *, s16, s32, u8, s32)` versus local caller signatures; explicit narrow values may make adoption neutral. |
| 4 | Actor 0x31C / owner 0x3D4 child contract | `func_150BDB70`: 1,520 | Resolve `struct126 *` / `struct127 *` ownership using matched camera writer and raw initialization. |
| 5 | Allocator return chain `80003C40` -> `80003C6C` / GAME alias | 42 GAME dependents / 89,251 | Establish the inner allocator return contract before changing its matched integer-address wrapper. |

Other blocked render sources remain distinct: `game_A9D90.c` has a deferred
`u8 *` definition versus a `void *` declaration affecting matched callers;
`game_18A8F0.c` differs on a top-level volatile pointer parameter; and
`game_1AC2F0.c` passes two arguments to the matched one-argument
`func_15048A40`. These are untried investigations, not proven fixes or reasons
to widen a canonical signature merely to compile.
