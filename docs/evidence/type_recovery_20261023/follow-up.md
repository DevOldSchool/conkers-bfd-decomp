# Shared type follow-up: rejected trials (US, 2026-10-23)

This pass retains no implementation changes. The current baseline remains
**2,793,441**, the PR's cumulative reduction remains **1,185**, and there
are no new matches. The baseline is [the root-owner final sweep](root-owner-final.tsv)
at implementation commit `0f5e45d101e1ba06c92f255f7a0eb088298ead8d`.
Comparisons use its measured `new` column, not stored candidate annotations.

## Executed trials

| Shared contract | Candidates | Successfully scored | Before -> after | Decision |
| --- | ---: | ---: | ---: | --- |
| `D_800D154C` / existing `struct127` current actor | 13 | 12 | 43,085 -> 43,085 | Neutral; restore three sources and remove the trial header. |
| `D_800A5480` / existing `Vec3f` aggregate-copy contract | 19 | 19 | 39,647 -> 39,647 | Neutral; restore six sources and remove the trial header. |
| `func_1000FA64` / matched main sound-queue alias | 44 | 42 | 95,859 -> 96,544 | Net regression of 685, with no improving candidate; restore six sources and remove the trial header. |

The cohorts are separate, totaling 73 successfully measured candidates. All
pre-existing errors in the valid trial results are unchanged. No candidate
reaches zero. [Per-candidate baseline comparisons](follow-up-trials.tsv).

The current-actor trial introduced a focused `extern struct127 *D_800D154C`
header in `game_AC030.c`, `game_64120.c` and `game_120950.c`. Only deferred
read expressions changed: the real id byte, 0x2F8 unsigned halfword, and
0x31C child/status pointer were accessed through the existing shared owner.
Matched bodies remained unchanged. Sparse `GameA28B0State` and `game_981E0`
users were not forced into the owner by renaming matched fields or rewriting
byte arithmetic. The one baseline compiler failure was preserved.

The vector trial replaced six aggregate-copy records with existing `Vec3f`
and shared the constant declaration in a focused header. Sources:
`game_12FDD0.c`, `game_203E20.c`, `game_3E890.c`, `game_1E58B0.c`,
`game_133190.c`, `game_1FC830.c`. Matched bodies changed type names only;
scalar integer bit-copy views were preserved. Matched `func_151D1074`
writes three float coordinates through the position callback; existing
matched vector users also copy the default into position/rotation fields.
This provides a type hypothesis, but the compiler emits the same scored code.
The first invocation lacked required includes in `game_203E20.c`, producing
two syntax errors. Those results were immediately marked invalid in the
ledger, the missing overlay/vector includes were repaired, and all 19
candidates compiled on the corrected rescore. The apparent missing score
sum from the invalid invocation is never counted as an improvement.

The sound trial shared the exact declaration of matched `func_8000FA64`
through its GAME execution alias `func_1000FA64`: `u16` return/sound/far range,
`s16` coordinates/near range, with all other words/pointers unchanged.
Main code links at 0x80000000 and executes at 0x10000000 (see
`scripts/prepare_main_library_object.py`); raw main instructions and the
matched C definition establish the narrow fields. No function bodies changed.
Six prototype users were tested: `game_200930.c`, `game_19A8B0.c`,
`game_1D3420.c`, `game_CDE80.c`, `game_3BA70.c`, `game_E1280.c`.
Only `func_150A23E4` changes, **265 -> 950**; adopting the callee's narrow
range/coordinate contract changes caller code generation. A physically
compatible narrow callee does not guarantee the historical GAME caller
prototype had the same spelling. The net-worse proposal is fully restored.
No attempt reshapes that caller to hide the regression.

## Additional contracts examined

| Lead | Evidence / reason to leave unchanged |
| --- | --- |
| `func_10003C40` allocator | Matched main wrapper `func_80003C40` returns `s32` through `func_80003C6C`; GAME declarations differ between integer and pointer results but all four parameter widths agree. A pointer-only declaration requires a coordinated return-chain audit. No narrow-argument or return-register mismatch is established by the conflict report alone. |
| `func_150A8050` matrix builder | Raw callee moves argument words directly into float registers and multiplies them, proving float-bit inputs. Most callers already declare floats. Matched `func_151B76CC` deliberately loads two inputs through integer-word views while supplying the same bits. A global numerical conversion would be incorrect; any coordinated spelling change must preserve that matched word ABI. No prototype-only gain is established here. |
| `D_800C35EA` scalar/array conflict | The reported variants are byte scalar versus byte-addressed aliases, not an incorrect word-width declaration. Existing reads already establish byte loads. No unsupported narrowing trial. |
| `D_800C3E78` signedness conflict | Both signed and unsigned byte views have matched users. The report does not establish a common interpretation that would preserve every matched reader. Leave both views until their sentinel/range roles are reconciled. |
| `D_800BE628` render record | 0x180 stride is backed by allocation/indexing. Existing views expose different real fields, including width at 0x04, dimensions at 0x0C/0x10, clipping bounds at 0x24..0x38, viewport data and matrices. They are sparse views, not three identical complete owners; do not merge them by inventing padding roles or renaming matched fields. Further complete-owner evidence is required. |

## Restored state and validation scope

Every trial file was restored from a backup verified against HEAD. All three
trial headers were deleted. Implementation, assembly, tooling and inventories
remain byte-identical to tested commit `0f5e45d101e1ba06c92f255f7a0eb088298ead8d`;
the tested source hash manifest still agrees. The US GAME image still equals
the independent reference byte for byte (2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). Whitespace checks pass.

Because no trial passes the score-reduction keep gate, none is accepted or
claimed to pass matched rechecks/clean integration. No `finish`, inventory
transactions, permutations or empty batch ran. There are no pending batch IDs.
The previous **BATCH_COMPLETE**, matched rechecks and no-new-warning result
apply to the unchanged implementation; this commit records evidence only.
The valid vector rescore compiled every selected candidate, while the actor
and sound trials preserve their baseline errors. Scorer subprocess times:
actor 1.4 seconds, repaired vector 1.9 seconds, sound 4.0 seconds, excluding
research, source preparation and handoff.

Ignored ledger: `build/us/manual-attempts/shared-types-followup-20261023/`.
It preserves the baseline, valid and invalid trial outputs, patch snapshots,
restoration records and next actions. The overall continuation goal remains
active; these hypotheses should not be repeated without new evidence.

## Next five investigations

Weights use the unchanged current measured scores and overlap; no projected
score reduction is claimed. They are investigation priorities, with the
promotion/ABI constraints above remaining applicable.

| Priority | Contract | Scored dependents | Weight |
| ---: | --- | ---: | ---: |
| 1 | `D_800BE628` complete render-record owner and interior matrices | 23 | 59,865 |
| 2 | `D_800DBEF4` root pointer and payload record views | 22 | 56,384 |
| 3 | `func_15145128` actor/particle pointee contract | 13 | 45,265 |
| 4 | `D_800B0DF0` level-header pointer views | 13 | 43,380 |
| 5 | `D_800D2104` resource/script table entries | 12 | 36,026 |
