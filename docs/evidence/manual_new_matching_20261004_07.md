# Manual matching batch 7 — 2026-10-04

Five fresh functions; Git eligibility checked without prior session memory.

| Function | Best CURRENT | Remaining mismatch |
| --- | --- | --- |
| `func_1509E3DC` | 265 | Default-zero placement, epilogue and jump-table relocations |
| `func_150E1AB0` | 5622 | Quad unrolling, narrow argument loads and frame |
| `func_150E9178` | 585 | Packet homes and saved-register allocation |
| `func_15108850` | 886 | Second packet/saved-pointer homes and scheduling |
| `func_151196D4` | 13134 | Sum-loop unrolling, scale spill and frame |

All deferred; best bodies retained with original assembly active. No shared dependencies changed.
Corrected our earlier source-local `func_1508C5B8` return declaration to `s32`, supported by raw return and dispatcher use.
Speed: audit raw return registers even when a caller ignores them; inspect jump tables before trusting void starters.
Refreshed US GAME and mapped rodata byte-identical; progress and whitespace checks passed.
