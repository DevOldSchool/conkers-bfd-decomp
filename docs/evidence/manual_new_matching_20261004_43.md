# Manual matching batch 43

| Function | Source | Best CURRENT |
| --- | --- | ---: |
| func_151990AC | effects/characterflamethrower.c | 5250 |
| func_151C5280 | game_1F2730.c | 441 |

Two fresh candidates retained; six comparisons, no exact matches or shared dependency edits.
Emission packet consumers and complete transform outputs audited; scaffold fields replaced with supported C.
Workflow issue: incidental live FP registers produced false RNG arguments in the starter.
Speed improvement: reusing the existing Vec3 type removed every opcode/control-flow and register difference in 151C5280.
Tool: m2c c24dd86cee4389973dc878eb3f22484dc782a166; local adapter excluded.

Full US refresh, layout, mapped rodata, image, progress and whitespace passed.
Integrated SHA-1: 90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5. Matching paused.
