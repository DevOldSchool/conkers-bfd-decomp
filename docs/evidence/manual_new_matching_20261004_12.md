# Manual matching batch 12 — 2026-10-04

Five fresh functions; Git history showed no prior target implementation.

| Function | Best CURRENT | Remaining mismatch |
| --- | --- | --- |
| `func_151D9534` | 2086 | Average spill, float scheduling and effect-address folding |
| `func_15158D2C` | 5871 | Frame, shift masks and callback scheduling |
| `func_15170F4C` | 6028 | Frame, float spills and parameter handling |
| `func_151BF0C8` | 961 | Second packet immediate ownership and byte-store order |
| `func_1502AC88` | 2536 | Global-base reuse, local homes and scheduling |

Best candidates retained with original assembly active; no shared changes or new exact matches.
Thirteen manual C comparisons; no permutation. Two candidates for the dispatcher/cache, three for each other function.
Workflow: starters misread actor reload timing and undersized packet/alignment buffers.
Speed: check writer widths and SDK intrinsic declarations before compiling; `fabsf` needs the SDK intrinsic pragma.
Refreshed US GAME/mapped rodata, independent byte comparison, progress and whitespace passed; confirmation returned 0 after an unexplained initial outer status 1.
