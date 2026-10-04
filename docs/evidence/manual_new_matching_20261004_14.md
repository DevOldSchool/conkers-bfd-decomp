# Manual matching batch 14 — 2026-10-04

Five fresh functions; Git history showed no prior target implementations.

| Function | Best CURRENT | Status / residual |
| --- | --- | --- |
| `func_150DE458` | 767 | Deferred: FP registers, output home 0x60 (recorded 0x64 is a typo), scheduling |
| `func_151D2830` | 3025 | Deferred: parameter homes and command store timing |
| `func_15059140` | 0 | Matched: independent 644-byte span and layout passed |
| `func_150F6DE4` | 1758 | Deferred: packet placement and scheduling |
| `func_1510D0EC` | 2543 | Deferred: frame, spill homes and register ownership |

Four best candidates retained with original assembly active; no shared helper/header edits.
Fourteen manual comparisons; no permutation or compilation repairs.
Workflow: raw caller setup proves an unused third argument omitted by the starter; a local declaration restored the exact match.
Speed: use exact-symbol queries and extract one raw callee body; broad searches and multi-function files caused truncation.
Clean batch passed: full US image and mapped rodata equality, progress, whitespace; 1823 tests passed (37 skipped).
