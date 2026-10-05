# Manual matching — 2026-10-04

209 fresh functions: five matched, 171 deferred, 33 blocked. Best deferred C,
scores and blockers remain in source and `progress/functions.json`.
Freshness was checked against available Git/inventory; lost private attempts
could not be excluded after the environment reset.

Accepted full-span US `CURRENT (0)` matches: `func_150D0E90`, `func_15103430`,
`func_15059140`, `func_150636F0`, `func_150F26A0`. `game_1308E0` was integrated;
[jump-table placement evidence](game_90840_jump_table.md) is retained separately.

Clean verification at `2c3500328ea5ff828e1454c3eb9e06e5bf5398d3` returned
`BATCH_COMPLETE`: 1,872 tests run, 37 skipped; US build, layout, mapped rodata,
metadata, progress and whitespace passed. Integrated image SHA-1:
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

Workflow findings:

- Audit raw argument reads, widths and branch delays; starters inferred false RNG arguments and incorrect timer semantics.
- Reuse established types and prove buffer extents; existing Vec3 types removed opcode/register differences in `func_151C5280`.
- Check declaration conflicts before generating starters; bounded exact-symbol reads reduce lookup time and truncation.
