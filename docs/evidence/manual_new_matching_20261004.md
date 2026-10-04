# Manual matching batch — 2026-10-04

Five fresh functions; 14 manual candidates, no automated search or prior session memory.
Eligibility checked against Git/inventory. Reset environment lacked private attempt history;
lost uncommitted attempts cannot be excluded.

| Function | Source under `src/game/` | Result / US CURRENT | Attempts |
| --- | --- | --- | ---: |
| func_150D0E90 | game_FE340.c | Matched / 0 | 2 |
| func_1511B7D4 | game_1483E0.c | Deferred / 3548 | 3; first invalid |
| func_15146078 | game_16EE20.c | Deferred / 1755 | 3 |
| func_151B9CB0 | game_1E6B40.c | Deferred / 1910 | 3 |
| func_1502EC34 | game_58F80.c | Deferred / 1680 | 3 |

Best deferred C retained beside original ASM; residuals recorded in inventory.
Rotation candidate retains the raw initialization precondition `flags == 0`.
Changes: these five sources, canonical inventory/progress outputs and this report.
Shared dependency changes: none. Clean `verify-batch func_150D0E90`: BATCH_COMPLETE.
US integrated overlay/layout, focused CURRENT 0, progress and whitespace passed;
1,823 tests passed (37 skipped). Baseline full US ROM and RSP checks also passed.

Workflow findings:

- Starter countdown ignored branch-delay semantics: count 1 failed to terminate. Corrected and invalid attempt excluded.
- Starter timer narrowed before a full-word comparison; retain `s32` until the final halfword store.
- Explicit derived index plus established byte-parameter narrowing took the successful candidate from 710 to 0.
- Keep a compact attempted-function index in Git and back up private evidence so resets do not erase eligibility checks.
