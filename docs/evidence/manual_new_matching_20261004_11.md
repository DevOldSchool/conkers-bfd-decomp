# Manual matching batch 11 — 2026-10-04

Five fresh functions; eligibility checked against Git implementation history.

| Function | Best CURRENT | Remaining mismatch |
| --- | --- | --- |
| `func_151EADFC` | 3192 | Frame, powers array and command cursor scheduling |
| `func_1507FC2C` | 2919 | Frame, mask homes and branch scheduling |
| `func_150BAFEC` | 2488 | Packet/angle homes and float scheduling |
| `func_15150D1C` | 979 | Output homes, parameter handling and scratch registers |
| `func_151A26EC` | Blocked | Raw zero return conflicts with caller-family void declarations |

Four best candidates retained with original assembly active; no shared changes.
Three C candidates per function; one additional compile repair for IDO volatile declaration agreement.
Workflow: starters misread pointer strides, old-value counter tests and multi-field output buffers.
Speed: audit contracts first; explicit persistent output pointers recovered saved-register ownership in `func_15150D1C`.
Refreshed US GAME and mapped rodata byte-identical; progress and whitespace checks passed.
