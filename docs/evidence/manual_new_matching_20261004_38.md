# Fresh manual matching, batch 38

| Function | Best US CURRENT | Outcome |
| --- | ---: | --- |
| func_1508BC20 | 3749 | deferred |
| func_1508E89C | — | blocked: conflicting helper ABI |
| func_150F26A0 | 0 | matched |
| func_15047390 | — | blocked: conflicting helper declaration |
| func_150623F4 | 1405 | deferred |

Eight comparisons; two best candidates retained. No compiler repairs or shared game edits.

Workflow: checking declaration conflicts in `next --ready` would avoid blocked starters. Direct field expressions recovered the exact load order in `func_150F26A0`. Verified m2c `c24dd86cee4389973dc878eb3f22484dc782a166` selected; local adapter excluded.

Clean `verify-batch func_150F26A0` returned `BATCH_COMPLETE`: 1823 tests, 37 skipped; full US integration, layout, mapped rodata, progress and whitespace passed. Image SHA1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
