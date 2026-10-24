# D_800DBFF0 root and owner recovery (US, 2026-10-23)

One shared-owner lead is retained, reducing the current measured score sum by
**555**, from **2,793,996 to 2,793,441**. No candidate regresses or reaches
zero. The preceding prototype lead's 630-point reduction brings the PR total
to **1,185** against its original 2,794,626 baseline. No new matches are claimed.

## Baseline and complete measurement

Continuation base: `9036d84acd6104b840ab062c67bf5462fb836bf8`.
The current baseline is the preceding [final sweep](final.tsv), copied
unchanged to the task ledger (SHA-256
`b2216058515cbf828fc9c5a19375c10d0e52fe1ab21069020088c5ac8bd1d87d`).
Scores compare measured `new` columns; stored inventory annotations are not
used as the baseline.

The [new full exact sweep](root-owner-final.tsv) visits all 1,384 candidates:
1,335 scored, the identical 49 compiler failures and the same four pre-existing
zeros. It confirms only the two improvements below. The full sweep takes
126.1 seconds of scorer subprocess time, excluding static research, matched
rechecks, clean integration and handoff.

| Scope | Scored candidates | Before -> after | Reduction | New matches |
| --- | ---: | ---: | ---: | ---: |
| Direct callers changed by this lead | 2 | 7,505 -> 6,950 | 555 | 0 |
| Every saved candidate in the two touched sources | 7 | 13,788 -> 13,233 | 555 | 0 |
| All direct root dependents | 35, plus one unchanged compiler failure | 101,170 -> 100,615 | 555 | 0 |
| Full current-baseline comparison | 1,335 | 2,793,996 -> 2,793,441 | **555** | **0** |

| Candidate / source | Before | After | Reduction |
| --- | ---: | ---: | ---: |
| `func_15155CFC`, `src/game/game_182C30.c` | 4,701 | 4,196 | 505 |
| `func_150C8A68`, `src/game/game_F5D80.c` | 2,804 | 2,754 | 50 |

## Shared contract and evidence

`D_800DBFF0` points to contiguous 0x9A0-byte camera/view owners, already
represented by shared `struct108` in `include/types.h`. Its actor links are
consistent with `struct127.camera` at 0x318 and the view's actor at 0x3D0.
The declaration report contained 57 declarations, 17 variants in 51 files,
including integers, byte/void pointers and many sparse camera views. Existing
owner definitions are reused; no padded local view is promoted into a second
competing full owner.

Independent raw allocation code for `func_15005290` computes count times
0x9A0, calls the allocator at 0x15005334, stores its return through
`D_800DBFF0` at 0x15005354, and advances the view cursor by 0x9A0 at
0x1500542C. Matched `func_80011BB8` loads this global at 0x80011C08, reads
its float at 0x380 at 0x80011CE4 and advances the record cursor by 0x9A0 at
0x80011CF0 (`reference/us/asm/EB00.s`). The shared owner already declares
`f32 unk380`; both selected raw GAME functions also issue `lwc1` from
0x380 (0x15155DB8 and 0x150C8C0C).

A focused `include/game_view.h` now declares `extern struct108 *D_800DBFF0`.
The two callers include it and remove their source-local `extern s32` copies.
Their deferred reads become `D_800DBFF0[index].unk380`, replacing the
integer-address casts and hard-coded record arithmetic. This is a shared
type and field-access change: control flow, locals, statement order, other
arithmetic and all matched bodies remain unchanged. The header is opt-in;
it does not inject a conflicting global declaration into all other users.

Paired compiler output explains the improvement without a statement rewrite.
For `func_15155CFC`, IDO changes scheduling of the index multiplication and
global load around the existing height branch, using that branch's delay slot
instead of a no-op and changing temporaries. For `func_150C8A68`, saved
register assignments for the root, view index and 0x9A0 stride shift, along
with loop temporaries. Both retain the same float read and frame sizes
(0x48 and 0xA0 respectively; reference frames are 0x68 and 0x98). These are still nonzero candidates, not matches.
The ledger preserves both before/after objects and disassemblies.

## Neutral and rejected owner views

The initial eight-source trial rescored 25 candidates, 24 successfully:
**73,157 -> 72,602**. Its single compile failure, `func_1510D0EC`, already
fails the baseline because of a conflicting function declaration. The six
neutral sources were fully restored before the final sweep and gates.
[Exact broad trial comparisons](root-owner-trials.tsv).

| Examined lead / source | Decision |
| --- | --- |
| Existing owner instead of `Game184DF0Camera` (`game_1B1600.c`) | All seven candidates unchanged. Restore the local sparse view; no score benefit from nominal owner replacement. |
| Existing owner instead of `Game637C0Target` (`game_637C0.c`) | Candidate remains 5,406. Restore; no repetition of the previous neutral matrix work. |
| Existing owner instead of `GameFBBF0Camera` (`game_FBBF0.c`) | Candidate remains 7,973. Restore; yaw at 0x37C is already a correctly typed float. |
| Existing owner instead of `Game112F90Camera` (`game_112F90.c`) | Candidate remains 6,720. Restore; root-position fields already have correct widths. |
| Existing owner instead of `Game139FC0LevelEntry` (`game_139FC0.c`) | Three measured candidates unchanged; the fourth has the same pre-existing compile failure. Restore; no gain from reusing the 0x5F0 word. |
| Root flag read in `game_100810.c` | All four candidates unchanged. Restore; the original explicit cast already establishes a word load. |
| Global six-camera layout promotion | Layout cluster 26 has 0x9A0 stride but sparse owner views and differing field names (`position` versus `x/y/z`). Do not merge them by matched member renaming; reuse of the existing owner above is tested separately. |
| Owner's 0x3D4 pointee and 0x2AC/0x5D4 numeric fields | `struct108.unk3D4` is currently actor-typed even though actor 0x31C and the initializer associate it with a child/status record. Some numeric declarations also differ from float accesses in other local views. The selected callers do not use these members; do not expand this measured gain into an untested whole-owner retype. Coordinate all users before changing the header. |

No neutral source, new speculative layout or rejected member retype remains
in the implementation. No assembly, compiler flags, shared tooling, asset
inputs or inventories changed. No permutation was run, and neither improving
candidate reached zero or required an inventory transaction.

## Validation

Every existing match in the two edited sources was rechecked through
independent full-span US `finish`: **13/13 CURRENT (0)**, reviewed layout,
progress and whitespace gates, all `STOP_MATCHED`. Rechecks only; no new
function matches. A separate **nine-pair** compiler audit covers both canonical
files and all seven individually activated deferred candidates: no compile
errors and zero `cfe` warnings on either side.

`CONKER_JOBS=1 ./conker verify-batch func_15155780 func_150C99B4` reports
**BATCH_COMPLETE** with one existing match per touched file. The matching
subset passes 1,062 tests, six skipped. The batch log contains zero `cfe`
warnings; the earlier documented SDK/library warning baseline remains
unchanged. The 2,072,880-byte integrated US GAME image equals the independently
extracted reference byte for byte, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
No pending batch IDs. [Machine-readable score and validation evidence](root-owner-validation.json).

The final implementation files are `include/game_view.h`,
`src/game/game_182C30.c` and `src/game/game_F5D80.c`. The proof covers the US
GAME image and mapped data; no asset reconstruction inputs changed.
The ignored durable ledger is
`build/us/manual-attempts/root-owner-type-recovery-20261023/`.

## Next five owner/ABI leads

Weights use the new measured scores of deferred dependents and overlap;
they must not be added or treated as predicted gains. Already-neutral pool
and root view substitutions should not be repeated without new evidence.

| Priority | Contract | Scored dependents | Weight | Evidence to resolve |
| ---: | --- | ---: | ---: | --- |
| 1 | `func_10003C40` allocator return/argument ABI | 42 | 89,298 | Integer versus pointer return declarations, including the root allocation; audit the raw allocator and matched callers. |
| 2 | `D_800D154C` actor pointer | 43 | 86,474 | Reconcile byte arithmetic and typed owner fields before sharing the global. |
| 3 | `D_800BE628` view transform storage | 23 | 59,865 | Distinguish the 0x180 record owner from interior transform payloads. |
| 4 | `D_800A5480` vector/copy contract | 20 | 55,645 | Separate float reads from unchanged three-word aggregate copies. |
| 5 | `func_150A8050` matrix-builder arguments | 17 | 54,869 | Establish float versus integer-word roles from callee and full caller ABI. |
