# Manual matching batch 15 — 2026-10-04

Five fresh targets; Git history showed mapping or caller changes only.

| Function | Best CURRENT | Status / residual |
| --- | --- | --- |
| `func_15150178` | 1119 | Deferred: frame, direction home, saved registers |
| `func_150139AC` | — | Blocked: allocator return, resource arity and sound return contracts |
| `func_1510CE60` | 7208 | Deferred: bitmap placement, count register and scheduling |
| `func_1515AF90` | — | Blocked: matched allocator wrapper declared void |
| `func_151B9964` | 860 | Deferred: frame and register/scheduling ownership |

Three best candidates retained with original assembly active; no shared edits.
Nine manual comparisons; one undefined-NULL compilation repair; no permutation.
Workflow issues: conflicting helper contracts; starters infer RNG arguments from leftover registers; `next --ready` sometimes returns 1 despite complete context.
Speed: check helper contracts before C, restrict declaration queries and extract one raw callee body.
Validation: refreshed US image and mapped rodata match; progress and whitespace pass. No pending matches, so no empty batch gate.
