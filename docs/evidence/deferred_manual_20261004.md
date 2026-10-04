# Deferred matching: 2026-10-04

Latest eight items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 1500E738 | game_3BA70.c | Focused candidate0 retained; table approval pending | 1 |
| 1505A250 | game_83300.c | Valid candidate3711→3520; FP lifetimes remain | 2 |
| 1511617C | game_1435C0.c | Valid candidate226; intrinsic repaired, frame/FP remain | 2 |
| 150888A8 | game_B4080.c | Valid candidate3167→1432; prototype/homes repaired | 2 + 2 compile repairs |
| 1505DDA8 | game_83300.c | Valid candidate1964; byte stride/index/call repaired | 2 |
| 1515942C | game_1865D0.c | Blocked3560; conflicting shared caller contract | 0 |
| 151C7038 | game_1F4350.c | Valid candidate863; one-pointer call repaired | 2 |
| 1504A140 | game_770F0.c | Valid candidate4804 retained; regressions rejected | 2 |

Six valid nonzero candidates and exact C preserved transactionally; blocked starter annotated invalid.
Canonical func_1500E738 linking failed +64bytes; reopen-match restored ASM without losing C.
Recovered clean verify-batch: BATCH_COMPLETE; full GAME and external rodata match ROM.
Suite: 1,823 tests, OK with 37 skipped. Layout, metadata, progress and whitespace passed.
Existing 1500E70C/15087DCC/1505DF10 rechecked at0; no new match credit.
Pending [mapping proof/proposal](game_3ba70_jump_table.md); shared linker remains unchanged.

Speed: audit callee contracts, intrinsics and byte strides before register revisions.
Confirmed workflow issue: call_signatures.py:198–246 trusts local prototypes before matched definitions.
Improve ready with an early conflict warning and external-table placement check.
Commit identity: DevOldSchool-AI-Agent. No personal memory or permutation used.
