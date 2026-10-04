# Deferred matching: 2026-10-04

Latest seven items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 15114A1C | game_13F9D0.c | Valid candidate1361; word slots/count paths repaired | 2 |
| 150A6360 | game_D36C0.c | Blocked10115; starter invalid, alternate entries/FPU rounding | 0 |
| 1511F788 | game_14C3F0.c | Valid candidate2065; local one-float call repaired | 2 |
| 1505D408 | game_83300.c | Valid candidate4714→2569; parameter normalization repaired | 2 |
| 150EA944 | game_117D90.c | Valid candidate645→105; 16 FP register rows remain | 2 |
| 151216F8 | game_14D110.c | Valid candidate525→60; one adjacent scheduling swap | 2 |
| 150B0A60 | game_DDF10.c | Valid candidate2115→1840; RNG/output lifetimes repaired | 2 |

Six valid candidates preserved transactionally; rejected revisions and invalid starters annotated.
All include one baseline; no permutation. Regressions/neutral revisions reverted to the best valid C.
Clean verify-batch: BATCH_COMPLETE; full US GAME/external rodata equal ROM.
Existing 151149AC/1511F768/1505DF10 rechecked at0; layout/progress/whitespace passed.
Suite: 1,823 tests, OK with 37 skipped; metadata valid. No new C match credit.

Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); shared linker remains unchanged.
1515942C remains blocked by a shared caller contract; 150A6360 needs full-span/rounding recovery.
Speed leads, unbenchmarked: warn during ready about prototype conflicts and multi-entry spans;
audit raw LW/SW widths before register work. Diagnose table placement incrementally, then clean-check before commit.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
