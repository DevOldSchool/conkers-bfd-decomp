# D_800CC2D0 actor pool follow-up (US, 2026-10-23)

No actor type change is retained. Two shared-type hypotheses and the matrix
cast-removal variant produced no score reduction and were fully restored.
The existing round reduction remains 630; this continuation adds zero matches
and zero reduction against the current baseline.

## Current baseline

Continuation base: `6b61b26a935d4f1dcaf7f1b0263c07698bb54f69`.
The comparison point is the preceding round's [final sweep](final.tsv), copied
unchanged into the task ledger as `baseline.tsv` (SHA-256
`b2216058515cbf828fc9c5a19375c10d0e52fe1ab21069020088c5ac8bd1d87d`).
Use its measured `new` column, not the older stored inventory score.

All 1,384 candidates include 1,335 measured scores totaling **2,793,996**,
49 compiler failures and four pre-existing zeros. The pool has 157 direct
deferred dependents: 153 scored, four unscored, weight **337,469**; 91 scored
pool dependents exceed 1,000. Counts exclude matched functions, and weights
represent complete candidate scores rather than a predicted gain from this
symbol. [Exact pool cohort](actor-pool-dependents.tsv).

## Evidence and trials

The existing `struct127` already has the pool's 0x32C stride, position fields
at 0x14/0x18/0x1C and scale fields at 0x14C/0x150. A global header cannot be
included everywhere without reconciling the 24 declaration variants in 95
sources; several declarations describe an interior alias or a padded view.

| Trial | Sources / candidates rescored | Sum before -> after | Reduction | New matches |
| --- | --- | ---: | ---: | ---: |
| Focused `extern struct127 D_800CC2D0[]` header; replace address-only scalar declarations | `game_173D40.c`, `game_1A5C00.c`, `game_43820.c`; nine candidates (the last has no deferred body) | 9,625 -> 9,625 | 0 | 0 |
| Shared 64-byte matrix type and the actor's 0x1D4 pointee | Three source units; eight deferred candidates in `game_1B1600.c` and `game_637C0.c` | 16,998 -> 16,998 | 0 | 0 |
| Remove integer-address casts using the recovered matrix pointer | Same eight candidates; only the disabled `func_15036310` expression additionally changes | 16,998 -> 16,998 | 0 | 0 |
| Full exact sweep under the shared matrix types | All 1,384 candidates, 1,335 scored | 2,793,996 -> 2,793,996 | **0** | **0** |

[Per-candidate trial comparisons](actor-pool-trials.tsv) and
[full sweep summary](actor-pool-measurement.json). The full sweep has no
changed score and exactly the same 49 failing candidates. It took 152.3
seconds of scorer subprocess time, excluding research and handoff. The matrix
focused sweep took 0.9 seconds and its cast-removal rescore 0.8 seconds.
One initial rescore invocation used invalid repeated-source syntax; it exited
at argument parsing and performed no compiles. The corrected command repeats
`--source` for each path. No permutations or inventory transactions ran.

The matrix trial promoted three identical full `f32 values[16]` definitions:
`Game61950Matrix`, `Game184150Matrix`, and `Game637C0Matrix`, into
`include/game_matrix.h`, exposed through `game_functions.h`. Existing matched
body edits in `game_61950.c` and `game_1B1600.c` changed type names only.
`struct127.unk1D4` changed from `struct255 *` to the shared matrix pointer.
The disabled `game_637C0.c` candidate replaced its padded actor view with
`struct127` and corresponding field names via a focused pool declaration.
No other actor views were forced into this definition.

Matched `func_15034728` indexes the 0x1D4 matrix base by `i << 6` and writes
float elements at row stride 0x10. Matched `func_15060BE0` independently loads
0x1D4 at US address 0x15060BF8, loads a model byte at 0x15060C30, shifts it by
six at 0x15060C38 and adds it to that base at 0x15060C3C; it reads floats at
matrix offsets 0x10/0x14/0x18 and 0x30/0x34/0x38. This supports a 64-byte
float-matrix pointee, but adopting its name alone changes no measured code.

The cast-removal variant replaced
`(GameActorMatrix *)((u32)actor->unk1D4 + ((u32)arg2 << 6))` with
`actor->unk1D4 + arg2` in disabled `func_15036310`. It remained 5,406, with
frame 0x98 against reference 0x78. No statement ordering, local variables,
control flow or matrix arithmetic was reshaped. Automatic review initially
rejected this expression change as out of scope. Additional read-only checks
confirmed its disabled-only scope, the 64-byte stride and recorded indices
4/9; review accepted the exact retry under the user's explicit step 3b
cast-removal authorization. The expression was measured and then restored
with the rest of the neutral trial.

## Other actor leads rejected or deferred

| View | Evidence | Decision |
| --- | --- | --- |
| Tail at 0x2E4 | Matched `func_150344A0` reads signed halfwords at 0x2E4/0x2E6. The raw US instructions for `func_15079B30` compute pool-relative 0x2E4/0x2E8/0x2EC addresses and perform word counter operations; the preserved candidate uses `s32 *`. | A single numeric field view would discard real word/halfword uses. Retain the existing definitions until a coordinated union or extension policy is established; no isolated narrowing. |
| Entity-id byte records | Matched `GameA9D90EntityIdRecord` and `GameB4080EntityIdRecord` use `D_800CC40F`, which is pool base + 0x13F, with the same 0x32C stride. | Their byte at local offset zero is an interior entity-id alias, not evidence that the pool's active-state word should become a byte. |
| Position/search and yaw layout clusters | Several equal-size records are sparse views or use different field spellings. The nested pointer at 0x31C also has distinct partial pointee views. | The workflow's identical-field-name and non-partial-view promotion criteria do not permit merging them by matched member renames. Resolve owner/extension contracts first. |

## Validation and restored state

All measured candidates in the focused trials compiled. No trial reached zero,
so none went through `finish`. Because no trial passed the score-reduction
keep gate, matched rechecks and a batch for those discarded types would not
establish an accepted change; they were not run or claimed. All five matrix
trial implementation files were restored from backups verified against HEAD;
the two trial headers were deleted. The earlier declaration trial was also
fully restored. Implementation, assembly, tooling and inventories are unchanged.
There are no pending batch IDs.

`git diff --exit-code HEAD -- include src progress config` passes after
restoration. The integrated US GAME image still equals the independently
extracted image byte for byte: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
The preceding clean **BATCH_COMPLETE**, 52 matched rechecks and no-new-cfe-warning
result continue to apply to the unchanged implementation; this follow-up adds
evidence only and makes no claim that the discarded shared types passed those
gates. See [the original round's exact validation scope](round.md).

## Next five investigations

1. `D_800DBFF0` root/owner contract: 35 scored dependents, weight 101,170,
   plus one baseline error; reconcile typed prefixes and extensions.
2. `D_800D154C` actor pointer: 43 scored dependents, weight 86,474;
   coordinate with the existing actor owner before changing globals.
3. `D_800A5480` vector/copy contract: 20 scored dependents, weight 55,645;
   distinguish numerical reads from unchanged three-word copies.
4. `func_150A8050` matrix-builder ABI: 17 scored dependents, weight 54,869;
   establish float versus integer-word argument roles from the raw callee.
5. Actor 0x31C owner/extension and 0x2E4 tail views: pool-wide upper bound
   153 scored dependents, weight 337,469, not an isolated-field impact count.
   Requires coordinated view design; the tested nominal pool/matrix promotions
   above should not be repeated without new evidence.

The task ledger is `build/us/manual-attempts/actor-pool-type-recovery-20261023/`.
It preserves the original baseline, every raw trial sweep, the full neutral
sweep, proposal/patch snapshots and the restoration checkpoint.
