# Deferred matching: 2026-10-04

Latest five candidates; manual US ASM-to-C. Shared dependencies: no.

| Function | Source under src/game/ | Best valid CURRENT | Fresh revisions |
| --- | --- | --- | --- |
| 1506EA98 | game_981E0.c | 1174; wrapping actor address | 2 |
| 15159594 | game_1865D0.c | 716; canonical float call, three coordinates | 2 |
| 151670C0 | game_1944C0.c | 2253; wrapping table/signed slot addresses | 2 |
| 150C1E34 | game_EEE70.c | 3641; canonical unsigned RNG return | 2 |
| 151026BC | game_12F400.c | 600; simpler switch default retained | 1 |

14 target finish calls; nine fresh revisions. Best valid C deferred;
canonical ASM retained. No new exact matches. Six matched owner/callee
rechecks passed full-span focused0, layout/progress/whitespace.
BATCH_COMPLETE: US GAME/mapped rodata equal ROM; 1,823 tests (35.836s),
37 skipped. Local declaration audits found no affected matched C callers.

Rejected legacy forms: scalar-object address arithmetic, unsupported fourth
coordinate padding, and callee scalar/return type conflicts. Lower scores
from those forms are invalid. Qualifying the actual result byte, a callback
comma argument and a nested switch did not recover their delay slots.
C1E34 consumed-word reuse recovered frame50 but worsened CURRENT3641→3855.
Speed leads: audit canonical types first; reuse ledgers to stop equivalent
branch/volatile retries. Unbenchmarked. verify-batch omits focused checks;
run finish first. Padding/alias discrepancies and the pending
[1500E738 mapping](game_3ba70_jump_table.md) remain unresolved.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
