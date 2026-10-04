# Manual matching batch 13 — 2026-10-04

Five fresh functions; no prior target implementation found in Git history.

| Function | Best CURRENT | Status / residual |
| --- | --- | --- |
| `func_15035D6C` | 7153 | Deferred: saved registers, frame and command scheduling |
| `func_1509ED74` | — | Blocked: helper declares three arguments; raw uses two |
| `func_150124A0` | — | Blocked: raw consumes pointer return; matched helper is void |
| `func_150870D0` | 4028 | Deferred: frame, byte homes and register/store scheduling |
| `func_150DB9E0` | — | Blocked: shared helper arity conflicts with raw call |

Best C retained with original assembly active; no shared helper/header changes or new exact matches.
Six manual comparisons; no permutation, compilation repairs or repeated failed checks.
Workflow: check raw callee argument use before trusting starter declarations; early ABI checks saved compilation.
Speed: restrict source queries to relevant declarations and save output before displaying it; one broad query truncated.
Refreshed US GAME, mapped rodata, image equality, progress and whitespace passed (exit 0).
