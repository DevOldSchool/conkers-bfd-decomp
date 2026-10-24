# D_800BE628 shared render record (US, 2026-10-23)

The recovered 0x180-byte render owner removes **1,265** measured mismatch
points and produces one independently verified new match:
`func_1510B7B4` (420 bytes). The current sum falls **2,793,441 -> 2,792,176**.
The PR now retains three type leads, totaling **2,450** points of reduction
against its original 2,794,626 baseline, with **one** new C match.

## Baseline and population accounting

Continuation base: `e2488c96341a81d0ec7b1985cd478796df8bbb99`.
The comparison point is [the preceding full final sweep](root-owner-final.tsv),
SHA-256 `734c08f490eb28242cf48171016de1c37b3851f9f34f118a5e4a21058761f3a1`.
Use its measured `new` column, not stored candidate annotations: the new
match's stored score was 1,065, but the current measured baseline was 1,265.

| Scope | Baseline cohort | Before -> after | Reduction | New matches |
| --- | ---: | ---: | ---: | ---: |
| `func_1510B7B4` | 1 candidate | 1,265 -> 0 | 1,265 | 1 |
| Every candidate originally preserved in the two retained source files | 3 candidates | 3,299 -> 2,034 | 1,265 | 1 |
| All measured direct `D_800BE628` dependents | 23 candidates | 59,865 -> 58,600 | 1,265 | 1 |
| Complete current-baseline population | 1,335 scored candidates | 2,793,441 -> 2,792,176 | **1,265** | **1** |

The [new full exact sweep](render-owner-final.tsv) visits 1,383 remaining
candidates: 1,334 measured scores, the identical 49 compiler failures and the
same four pre-existing zeros. Exactly one baseline candidate is absent because
it is now registered matched C with independent full-span `CURRENT (0)`;
it contributes zero to the original comparison cohort. No other measured
score changes. The full sweep takes 121.3 seconds of scorer subprocess time,
excluding research, matching transactions, compile/layout checks and handoff.

## Recovered owner and evidence

`include/game_render_view.h` defines `GameRenderView` and the focused
`extern GameRenderView *D_800BE628`. This recovers a shared record from
independent matched readers and raw record-address evidence, rather than
nominally promoting any one private padded view. Its allocation/indexing
stride is 0x180. Unknown ranges stay opaque bytes; naming a few known fields
does not claim the whole record's semantics are understood.

| Offset / extent | Shared field | Evidence |
| --- | --- | --- |
| 0x04 | `f32 width` | Matched `func_15173D00` in `game_1A11B0.c` uses the record width. |
| 0x0C/0x10 | `f32 field0C/field10` | Matched `func_1510B070` reads these dimensions as float projection bounds. |
| 0x24..0x30 | Float `top`, `bottom`, `left`, `right` | Matched `func_1501A490` and `func_1517F9F4` clip against these four bounds. |
| 0x40..0x5F | `Vp viewports[2]` | Matched render users address `base + buffer*0x10 + 0x40`; `game_C2350.c`'s scale/translate halfword layout agrees with SDK `Vp`. |
| 0x64..0x78 | Float base, scale and value pairs | Matched `func_1510B958` reads all six through its old `Game138B40Record` view; field names are retained exactly. |
| 0x84 | `f32 field84` | Matched `func_1510B458` and `func_1510B51C` pass this float into projection setup. |
| 0xB8 | `u16 normalization` | Raw/newly matched `func_1510B7B4` uses `lhu` at 0x1510B828 before the normalization command. |
| 0xBC..0xFB | `f32 matrix[16]` | Matched `func_1510B5F8` passes this payload to projection setup/conversion; raw matrix multiplication reads float elements, and the `game_FECC0.c` view supplies the same sixteen-float layout. |
| 0x100..0x17F | `Mtx matrices[2]` | Matched render/projection users address `base + buffer*0x40 + 0x100`; SDK `Mtx` is 0x40 bytes. The two slots fill the 0x180 record. |

The SDK supplies `Vp` and `Mtx`; no local substitutes are introduced.
Buffer indexing uses the existing front/back selector (the scheduler toggles
it with XOR 1); the record separates those slots from calibration fields.
The old byte-addressed views that described twelve viewport-sized chunks
spanned unrelated calibration/projection storage and are left private.
This lead does not force all local views into one spelling or rename any
matched member access.

A pinned IDO/o32 compile emits 21 layout facts into an ignored data object.
Every size/member offset equals the independent expected layout, including
record size 0x180, SDK sizes 0x10/0x40, normalization at 0xB8, float matrix at
0xBC and fixed matrices at 0x100. [Exact compiler measurements](render-owner-validation.json).

Retained implementation changes: `include/game_render_view.h`,
`src/game/game_138B40.c`, `src/game/game_FECC0.c`, plus the supported function
inventory transaction. The shared owner replaces two private padded views.
The existing matched `func_1510B958` changes type names only. In the zero
candidate, the normalization load and matrix address become real typed
member accesses; all command blocks, statements, locals and ordering remain
unchanged. Its prior recorded residual described IDO CSE/reuse of the two
record-index computations. The recovered member/SDK-array address forms now
produce the retail instruction sequence without function reshaping.

## New match and validation

The isolated sweep zero was followed by supported `resume`, targeted
`next --ready --function func_1510B7B4`, source-diff inspection and a separate
`finish`. Readiness reported the already-authorized dirty source, mixed
source unit, no recorded issue and `post-match-action: stop`. `finish` proved
independent full registered span **CURRENT (0)**, preserved unit layout,
progress and whitespace, with **STOP_MATCHED**. No new function was selected.

After trimming unused fields without matched reader evidence, both the new
function and old `func_1510B958` passed full-span `finish` again. This extra
zero check is a dependency-refinement recheck, not a second new match or an
individual statement revision. Neither source unit is claimed complete.
`game_FECC0.c` has no existing matched C function to nominate: its canonical
unit and only deferred candidate were compiled separately, while full clean
integration verifies its retained assembly.

A five-pair before/after compiler audit covers both canonical units and
every historically/currently preserved candidate in those files, including
the new match's old candidate. Every unit compiles, with **zero cfe warnings
before and after**. No permutations ran; there is one new type hypothesis,
one supported match transaction and no manual function-body reshaping.

`CONKER_JOBS=1 ./conker verify-batch func_1510B7B4 func_1510B958` reports
**BATCH_COMPLETE**. All 1,062 matching-subset tests pass, six skipped.
The batch log has zero `cfe` warnings. The 2,072,880-byte integrated US GAME
image equals the independent ROM extraction byte for byte, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. No assembly, compiler options,
shared tooling or asset reconstruction inputs changed. No pending batch IDs.
The tested-source hash manifest pins the committed runtime inputs; the PR
records the resulting tested commit.

## Rejected adoption variants

[Per-candidate trials](render-owner-trials.tsv) preserve both valid screens:

- Initial three-source trial: eight candidates, including the new zero.
  `game_157840.c`'s typed bounds reads worsen `func_1512B1B8`
  **5,577 -> 5,652**, with no improvement elsewhere in that file. Record
  indexing changes scheduling/temporaries. Restore that source completely;
  its regression is absent from the accepted final sweep.
- Additional bounds adoption in `game_A9D90.c` and `game_197F20.c`: five
  measured candidates plus one unchanged baseline error, **14,850 -> 14,845**.
  Only `func_1507DB6C` improves, **5,190 -> 5,185**. The five-point gain is
  rejected because `game_A9D90.c` contains the pre-existing conflicting
  `func_1507E1D0` prototype error and cannot satisfy the every-candidate-
  compiles gate without a separate coordinated ABI repair. The other source
  is neutral. Both files were restored exactly to the clean-batch-tested
  implementation; no repeated build is needed for those discarded edits.

The broader root/placed-object surveys found that `D_800DBEF4` indexes
0xA0-byte placed-object records, with resource/flags, pivot, motion and linked
owner views. Its union/tag semantics need recovery before a flat numerical
record is imposed. Several function conflicts were also audited: the byte
slots of `func_1513D2F0` already agree at callers (remaining differences are
pointer/address/return spellings), and `func_150859AC` callers already narrow
indices or pass small selector constants. No unsupported scalar narrowing
trial or speculative owner merge was retained.

Ignored ledger: `build/us/manual-attempts/render-owner-recovery-20261023/`.
It preserves the immutable baseline, raw trial/final sweeps, match/recheck
logs, before/after compile artifacts, compiled layout data, rejected
extension patch and checkpoint. Future score comparisons start from
`render-owner-final.tsv`, whose population excludes the newly matched item.
