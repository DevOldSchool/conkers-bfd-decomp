# Fresh manual matching — batch 42

| Function | Best CURRENT | Result |
| --- | ---: | --- |
| func_151718F0 | 2784 | Deferred |
| func_151742EC | — | Callback contract blocked |
| func_15084044 | 1934 | Deferred |
| func_150E7994 | — | Shared return contract blocked |
| func_151797B0 | 1054 | Deferred |

Nine comparisons, no compilation repairs or shared dependency changes.
Corrected native allocation-size reads; preserved real buffer lifetimes and cleanup.
Boundary-relative subtraction recovered native particle wrapping arithmetic.
Speed: resolve dispatch/return contracts before edits; filter saved declaration lookups narrowly.
Tool c24dd86cee4389973dc878eb3f22484dc782a166; adapter excluded.
Full US image/rodata/layout, progress and whitespace passed; no accepted matches or empty verify-batch.
