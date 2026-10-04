# Fresh manual matching, batch 25

| Function | Best US CURRENT | Outcome |
| --- | ---: | --- |
| func_150C16C0 | 3154 | deferred |
| func_150C9DC4 | 991 | deferred |
| func_150E5558 | 40 | deferred |
| func_1511B51C | 1528 | deferred |
| func_150198FC | — | ABI blocked before comparison |

Twelve manual comparisons; best candidates retained. No permutation or shared game dependencies changed.

Starter issues: omitted unused argument slots and a phantom RNG input. Audit forwarding wrappers too: `1517EFAC` passes A0 to `1517EF00`, contradicting its existing void contract. Checking helper inputs and copied spans before editing avoids invalid comparisons.

Full US refresh: image SHA1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`; mapped rodata, progress and whitespace passed. Tool override adapter excluded.
