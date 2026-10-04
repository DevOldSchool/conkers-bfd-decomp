# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 150EEC84 | game_11A680.c | 741; wrapping addresses/shift, frame recovered | 2 |
| 1510B690 | game_138B40.c | 535; wrapping matrix offsets/counter narrowing | 2 |
| 151406AC | game_169510.c | 1037; partial sentinel, head/cursor reuse | 2 |
| 1503EB78 | game_6B320.c | 227; cursor/scalar reuse, frame recovered | 2 |
| 150548E4 | game_80B80.c | 910; word subtraction before signed division | 1 |

14 target finish calls; nine bounded revisions. Best valid C deferred;
canonical ASM retained. No new exact matches. Five affected matched owners
passed full-span focused0, layout/progress/whitespace. BATCH_COMPLETE.
US GAME/mapped rodata equal ROM; 1,823 tests (35.589s), 37 skipped.

Rejected legacy forms: EEC84 signed/unbounded shift (raw SLLV masks count31);
B690 negative signed shifts after counter rollover; 406AC unsupported EC
sentinel tail padding; 548E4 unrelated pointer subtraction/scalar indexing.
Speed lead: reuse consumed inputs for actual loaded values/cursors;
EB78 frame78→60 and CURRENT395→227, EEC84 frame40→38. Unbenchmarked.
548E4 starter context-error fallback suggests s32 RNG despite active u32.
verify-batch omits focused checks: run finish first.
151898C0 padding/AB04 symbolic alias remain nonzero focused discrepancies;
complete linked spans equal ROM. Pending [1500E738 mapping](game_3ba70_jump_table.md).
47B80 padding,1515942C contract,150A6360 span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
