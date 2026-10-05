# Deferred matching: 2026-10-04

Manual US ASM-to-C; shared dependencies: no.

| Function | Source under src/game/ | Valid CURRENT | Preserved candidate | Fresh revisions |
| --- | --- | --- | --- | --- |
| 150FC438 | game_128D70.c | 629 | allocation-failure address wrap | 1 |
| 15103254 | game_130240.c | 828→438 | incoming word-home byte views | 2 |
| 151321D0 | game_15F680.c | 260 | wrapping lifetime subtraction | 2 |
| 151AC810 | game_1D9A00.c | 796 | baseline; home/snapshot trials regressed | 2 |
| 1517F814 | game_1AC2F0.c | 320 | wrapping selector addresses | 2 |

14 target finish calls, nine fresh revisions. All five retain canonical ASM;
no new exact C matches. 37 independent focused CURRENT (0) checks passed.
Unchanged owner15133FD8 focused100 omits one alignment NOP; its full152-byte
linked span matches ROM after clean rebuild (SHA25698b17761…).
US BATCH_COMPLETE: GAME/rodata exact;1,823 tests,37 skipped (37.289s);
layout/progress/whitespace pass.

Speed lead: byte views recovered LBU reads without narrowing formals.
Halfword views changed pointer reuse and regressed; register hints were neutral.
These are observed assembly effects, not speed benchmarks.
Reject invalid signed/null arithmetic before ranking scores. Saved scores may
be stale: 150FC438 saved319 reproduced629 over the full registered span.
Descriptor padding requires consumer evidence: 15130280 copies0x70 bytes.
Batch gate omits focused diffs; run them independently.
Speed proposal: build once, compare all required spans, check layout/progress once.
Pending [1500E738 mapping](game_3ba70_jump_table.md).
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
