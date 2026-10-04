# Manual matching batch 5 — 2026-10-04

Five fresh functions; two candidates retained, three blocked. No exact matches.
Eligibility checked against Git implementation history; prior session memory unused.

| Function | Result | Remaining issue |
| --- | --- | --- |
| `func_15036310` | Deferred, CURRENT 5406 | Literal float folding, temporary stores and frame |
| `func_1505959C` | Deferred, CURRENT 852 | Initial scheduling, frame and selection home |
| `func_150A6500` | Blocked, no candidate | Multiple entries, cross-span branch, GPR saves in FPRs |
| `func_150A7DF0` | Blocked, no candidate | Dynamic handwritten call frames and single-word FPR saves |
| `func_150E5FD0` | Blocked, no candidate | Raw pointer result conflicts with matched void callee |

Seven finish calls: six candidates and one declaration repair.
Best bodies stay disabled beside the original ASM; inventory records the blockers.
`1505959C` reused its unused incoming slot: score 1912 → 852, later registers recovered.
Its caller advisory found no direct matched C callers; coverage is incomplete.

Speed: detect handwritten frame/entry families and void-result consumers before compiling.
Warm focused compilation remains fast; use discovered reference paths instead of guessing.
Validation: refreshed US GAME binary and mapped rodata matched; progress and whitespace passed.
