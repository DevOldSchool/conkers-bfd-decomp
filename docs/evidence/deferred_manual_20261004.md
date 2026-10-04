# Deferred matching: 2026-10-04

Latest five items; manual US ASM-to-C. Shared changes: no.

| Function | Source under src/game/ | Best valid CURRENT | Revisions |
| --- | --- | --- | --- |
| 15157F80 | game_1844C0.c | 1435; original retained | 2 |
| 15063628 | game_90840.c | 481; original retained | 1 |
| 15058EA4 | game_83300.c | 55 → 0; FP bound lifetime | 1 |
| 1510CDB8 | game_139FC0.c | 1625; unsigned color shifts repaired | 2 |
| 151A8A78 | game_1D4E00.c | 767 → 115; owner repair/u8 event | 2 |

13 target finish calls; one match, four best valid deferred candidates.
CDB8 baseline signed color shifts and A8A78 zero owner argument were invalid.
A8A78 now differs only in nineteen register rows; instructions/control/stack/count agree.
Eight functions passed focused0/layout/progress/whitespace (seven existing owners).
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Speed leads: reuse actual FP temporaries for successive bounds; type byte events
to recover incoming homes. Check owner arguments and unsigned shifts first.
Starter F80 typed cursor +8 scales to64 bytes: preserved candidate has correct8-byte stride.
Prior 47B80 focused-padding issue persists; complete mixed span/ROM were exact.
Pending [1500E738 mapping proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
