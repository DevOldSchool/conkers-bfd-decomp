# Manual matching batch 10 — 2026-10-04

Five fresh functions; Git eligibility checked without prior session memory.

| Function | Best CURRENT | Remaining mismatch |
| --- | --- | --- |
| `func_151BC104` | Blocked | Helper declared void returns a consumed pointer |
| `func_15044660` | 1370 | Register allocation and address scheduling |
| `func_150EB1C0` | 195 | Registers only; instruction order and homes agree |
| `func_1512C20C` | 2316 | Frame, vector homes and float scheduling |
| `func_151A6C90` | Blocked | Eight-argument call conflicts with six-parameter definition |

Three best candidates retained with original assembly active; no shared changes.
Workflow: starters can omit actor arguments or misread count-controlled variadic helpers.
Raw caveat: `func_15044660` reads an uninitialized index for special actor kinds; preserved without a seed.
Speed: audit helper returns and argument counts before C; reuse proven temporary lifetimes before rearranging locals.
Refreshed US GAME and mapped rodata byte-identical; progress and whitespace checks passed.
