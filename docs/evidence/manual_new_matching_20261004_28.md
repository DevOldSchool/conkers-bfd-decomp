# Fresh manual matching, batch 28

| Function | Best US CURRENT | Outcome |
| --- | ---: | --- |
| func_151582C8 | 1235 | deferred |
| func_150031EC | 1837 | deferred |
| func_151349D0 | 2481 | deferred |
| func_1505DADC | 3102 | deferred |
| func_150636F0 | 0 | matched |

Fifteen manual comparisons; four best candidates retained. No permutation or shared game types changed. The match required its ROM-proven jump-table placement.

Starter issues: `150049A4` has three inputs; collision vertices need 18 bytes; request payload offsets need byte arithmetic. Audit raw helper spans before editing; bounded symbol reads reduce repeated lookup costs.

Clean batch: full US image SHA1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, mapped rodata, layout, progress and whitespace passed; 1,823 tests passed (37 skipped), `BATCH_COMPLETE`. Local tool adapter excluded.
