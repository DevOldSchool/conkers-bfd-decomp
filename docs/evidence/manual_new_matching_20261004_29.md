# Fresh manual matching, batch 29

| Function | Best US CURRENT | Outcome |
| --- | ---: | --- |
| func_15086098 | — | blocked: shared return ABI |
| func_150CCEB0 | — | blocked: shared return ABI |
| func_150DB714 | 268 | deferred |
| func_1519203C | 210 | deferred |
| func_15040FCC | 2465 | deferred |

Nine manual comparisons; three best valid candidates retained. One incorrect descriptor-offset attempt was annotated invalid. No permutation or shared dependency edits.

Workflow issues: two matched `void` helpers actually forward pointers; the starter drops an unused argument slot. Audit raw return paths, argument slots and complete copy spans before editing. Signed pixel arithmetic avoids redundant loop cursors.

Full US refresh, mapped rodata, progress and whitespace passed; image SHA1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. No new match, pending batch or test claim. Local tool adapter excluded.
