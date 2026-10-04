# Deferred matching: 2026-10-04

Latest four items; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Status / fresh full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 1501A490 | game_476D0.c | Valid candidate2615→1325; actual command cursor restored | 2 |
| 1514BC08 | game_177B50.c | Valid candidate360→70; seven commutative operand swaps remain | 2 |
| 151CB970 | effects/effects_sight.c | Invalid starter repaired; valid872→70, tail load/ADD remain | 2 |
| 151194D4 | game_144C70.c | Valid candidate2379→1958; full-width tag/shared pass lifetimes | 2 |

Best valid candidates preserved through defer; neutral/regressing revisions reverted.
13 candidate finish calls: four baselines, eight revisions, one compile-only call repair.
No permutation or new match credit. No registered matched C callers of 151194D4 found;
caller search is incomplete. Raw callers and recursion support the full-width tag.
Existing 1501AF44/1514B8B0/151CB918/151193AC rechecked at0; per-function gates passed.
Clean verify-batch: BATCH_COMPLETE; full US GAME/external rodata equal ROM.
Suite: 1,823 tests, OK with 37 skipped; metadata/progress/whitespace passed.

Speed observations: operand spelling improved FP allocation; named products regressed.
Declaration order repaired addressed float offsets; keep cursor changes isolated next pass.
Unbenchmarked lead: screen saved candidates against ready declarations before compiling;
151CB970 omitted a required argument, and some stored scores were stale.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); shared linker unchanged.
1515942C remains blocked by a shared caller contract; 150A6360 by full-span/FPU semantics.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
