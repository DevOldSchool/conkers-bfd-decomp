# Fresh manual matching, batch 27

| Function | Best US CURRENT | Outcome |
| --- | ---: | --- |
| func_151B2690 | 4223 | deferred |
| func_15062800 | 4339 | deferred |
| func_150B0348 | 1851 | deferred |
| func_150E76D0 | 1082 | deferred |
| func_150F4A38 | 1667 | deferred |

Fifteen manual comparisons; best candidates retained. No permutation or shared game dependencies changed.

Starter issues: `15033EC4` has two inputs; RNG calls have none. Audit raw input use and complete copy spans before editing. Save bounded symbol reads to reduce repeated lookup costs.

Full US refresh: image SHA1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`; layout, mapped rodata, progress and whitespace passed. Tool adapter excluded.
