# Manual init matching handoff

Matching stopped at the user’s request; the completion goal remains unfinished.

- Branch: `codex/manual-init-matching`; starting commit: `490ed96`.
- 39 new full-span US C matches. Two complete units, `init_3BD0.c` and `init_11FA0.c`, moved to `src/done/main/`.
- Original 214-function cohort: 148 matched, 46 raw assembly candidates, 20 original assembly functions.
- Literal remaining `src/main/init*.c` files: 142/208 matched; 66 remain.
- All 46 raw assembly functions retain deferred C candidates and reasons in source/inventory. Nonzero candidates receive no match credit.
- No pending verification batch or active C candidate. Final A750 experiment scored 29419; preferred 25805 candidate independently restored and deferred.

## Verification

Last source-changing commit: `c15db90` (full commit below). Clean batch 68 completed for `func_8000EE70`, `func_8000ECCC`, `func_8000EDA0`, `func_8000EC24`, and `func_8000EF40`: `BATCH_COMPLETE`, byte-exact US ROM, layout and linked-data checks, 1,899 tests passing with 37 skips, metadata/progress and whitespace checks passing. Subsequent changes before this handoff contain candidate-history metadata only; source, headers, assembly and build implementation remain identical. The full-span focused matches and earlier clean batches are recorded in the ledger. EU/PAL was not a gate.

Tested source commit: `c15db90339ee18c2e07df662b4d96f4e803a2637`.

## New exact matches

| Function | Current source |
| --- | --- |
| `func_80003BD0` | `src/done/main/init_3BD0.c` |
| `func_800043B4` | `src/main/init_3C40.c` |
| `func_80004470` | `src/main/init_4470.c` |
| `func_80004514` | `src/main/init_4470.c` |
| `func_80012020` | `src/done/main/init_11FA0.c` |
| `func_8000B1B0` | `src/main/init_B1B0.c` |
| `func_8000B1FC` | `src/main/init_B1B0.c` |
| `func_8000B294` | `src/main/init_B1B0.c` |
| `func_8000B2F4` | `src/main/init_B1B0.c` |
| `func_8000B548` | `src/main/init_B1B0.c` |
| `func_8000B8B8` | `src/main/init_B1B0.c` |
| `func_8000BF60` | `src/main/init_B1B0.c` |
| `func_8000C7E8` | `src/main/init_B1B0.c` |
| `func_8000D758` | `src/main/init_B1B0.c` |
| `func_8000DEC4` | `src/main/init_B1B0.c` |
| `func_8000E17C` | `src/main/init_B1B0.c` |
| `func_8000E2F4` | `src/main/init_B1B0.c` |
| `func_8000E7A0` | `src/main/init_B1B0.c` |
| `func_8000E934` | `src/main/init_B1B0.c` |
| `func_8000EC24` | `src/main/init_EB00.c` |
| `func_8000ECCC` | `src/main/init_EB00.c` |
| `func_8000EE70` | `src/main/init_EB00.c` |
| `func_8000F4D8` | `src/main/init_EB00.c` |
| `func_8000F568` | `src/main/init_EB00.c` |
| `func_8000F85C` | `src/main/init_EB00.c` |
| `func_8000FC18` | `src/main/init_EB00.c` |
| `func_8000FD38` | `src/main/init_EB00.c` |
| `func_8000FDF4` | `src/main/init_EB00.c` |
| `func_8000FF90` | `src/main/init_EB00.c` |
| `func_800100E0` | `src/main/init_EB00.c` |
| `func_80010558` | `src/main/init_EB00.c` |
| `func_80010720` | `src/main/init_EB00.c` |
| `func_80010BE8` | `src/main/init_EB00.c` |
| `func_80010F30` | `src/main/init_EB00.c` |
| `func_800114D0` | `src/main/init_EB00.c` |
| `func_80011BB8` | `src/main/init_EB00.c` |
| `func_80008180` | `src/main/init_8180.c` |
| `func_800084D8` | `src/main/init_8180.c` |
| `func_8000B060` | `src/main/init_A420.c` |

## Remaining functions

Scores are recorded candidates, not proof of acceptance; revalidate input context before resuming.

| Function | State | Recorded score |
| --- | --- | --- |
| `func_80001420` | `raw_asm` | 30 |
| `func_80001194` | `raw_asm` | 90 |
| `func_80002DB0` | `raw_asm` | 20 |
| `func_80003220` | `raw_asm` | 6183 |
| `func_80003920` | `raw_asm` | 60 |
| `func_80003ACC` | `raw_asm` | 760 |
| `func_80003C6C` | `raw_asm` | 1401 |
| `func_80004074` | `raw_asm` | 668 |
| `func_800046E4` | `raw_asm` | 60 |
| `func_8000480C` | `raw_asm` | 1465 |
| `func_800049E0` | `raw_asm` | 1817 |
| `func_800056A0` | `raw_asm` | 600 |
| `func_80008F90` | `raw_asm` | 1811 |
| `func_80009400` | `raw_asm` | 450 |
| `func_800095A0` | `raw_asm` | 1400 |
| `func_800097CC` | `raw_asm` | 475 |
| `func_800099BC` | `raw_asm` | 395 |
| `func_80009BE4` | `raw_asm` | 95 |
| `func_80009CBC` | `raw_asm` | 330 |
| `func_8000A03C` | `raw_asm` | 685 |
| `func_8000A348` | `raw_asm` | 65 |
| `func_8000BCBC` | `raw_asm` | 10 |
| `func_8000C350` | `raw_asm` | 10 |
| `func_8000C530` | `raw_asm` | 48 |
| `func_8000C934` | `raw_asm` | 24 |
| `func_8000CEAC` | `raw_asm` | 1608 |
| `func_8000D2F8` | `raw_asm` | 726 |
| `func_8000D96C` | `raw_asm` | 1068 |
| `func_8000DF68` | `raw_asm` | 605 |
| `func_8000F6B8` | `raw_asm` | 230 |
| `func_8000FA64` | `raw_asm` | 1483 |
| `func_8000FE88` | `raw_asm` | 8 |
| `func_8000FEF0` | `raw_asm` | 500 |
| `func_80010154` | `raw_asm` | 2065 |
| `func_80010344` | `raw_asm` | 745 |
| `func_80010630` | `raw_asm` | 1984 |
| `func_80010FFC` | `raw_asm` | 935 |
| `func_80011310` | `raw_asm` | 3775 |
| `func_80011624` | `raw_asm` | 298 |
| `func_80008CE8` | `raw_asm` | 80 |
| `func_80008120` | `original_asm` | — |
| `func_80005AB0` | `original_asm` | — |
| `func_80005B04` | `original_asm` | — |
| `func_80005BE0` | `raw_asm` | 945 |
| `func_80005C2C` | `original_asm` | — |
| `func_800061F8` | `original_asm` | — |
| `func_80006240` | `raw_asm` | 245 |
| `func_8000625C` | `original_asm` | — |
| `func_8000632C` | `original_asm` | — |
| `func_80006380` | `original_asm` | — |
| `func_80006424` | `original_asm` | — |
| `func_80006828` | `original_asm` | — |
| `func_8000692C` | `original_asm` | — |
| `func_8000696C` | `original_asm` | — |
| `func_80006E00` | `original_asm` | — |
| `func_8000709C` | `original_asm` | — |
| `func_800071D0` | `original_asm` | — |
| `func_8000777C` | `original_asm` | — |
| `func_800079D8` | `raw_asm` | 1275 |
| `func_80007A24` | `raw_asm` | 10 |
| `func_80007A38` | `original_asm` | — |
| `func_80007C74` | `original_asm` | — |
| `func_80007DA0` | `original_asm` | — |
| `func_80007DAC` | `original_asm` | — |
| `func_8000A420` | `raw_asm` | 230 |
| `func_8000A750` | `raw_asm` | 25805 |

## Preserved evidence

The complete task reasoning ledger is committed alongside this handoff as [ledger.md](ledger.md). It records hypotheses, attempts, scores, rejected approaches, restorations and batch outcomes. The transactional function inventory records the latest deferral reason for each remaining candidate.

Detailed compiler snapshots and full diffs remain under `build/us/matching-attempts/`; readiness records, pending state and clean batch logs remain under `build/us/manual-attempts/manual-init-20261005/` in the isolated worktree. These detailed build artifacts are ignored and are not part of Git. Keep the worktree when handing off; use the supported `matching-history export/import` commands if moving detailed snapshots. No ROM or binary artifact is included in this handoff.

The branch is intentionally submitted as a draft without merging newer main changes after the stop request. Matching was manual; no permutation search was used.
