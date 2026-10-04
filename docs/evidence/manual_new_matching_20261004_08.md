# Manual matching batch 8 — 2026-10-04

Five fresh functions; Git eligibility checked without prior session memory.

| Function | Best CURRENT | Remaining mismatch |
| --- | --- | --- |
| `func_151D6BFC` | 3543 | Second packet home and argument reuse |
| `func_1506DE84` | 275 | Constant-address scheduling and jump-table mapping |
| `func_1510C8A8` | 2898 | Carry homes and register lifetimes |
| `func_1510E120` | 3154 | Command cursors and local homes |
| `func_1511A494` | 4215 | Search branches, frame and snapshot homes |

All deferred; best bodies retained with original assembly active. No shared dependencies changed.
Workflow: `game_981E0`'s fixed constructor rodata mapping excludes the dispatcher jump table; acceptance would require a reviewed mapping change.
Raw caveat: `func_1510C8A8` reads uncleared halfwords before its first primary record; the candidate preserves those reads.
Speed: audit starter widths, float call contracts, writes and jump-table coverage before revisions.
Refreshed US GAME and mapped rodata byte-identical; progress and whitespace checks passed.
