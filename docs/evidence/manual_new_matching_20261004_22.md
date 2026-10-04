# Fresh manual matching — batch 22

Five new functions; fifteen manual comparisons. Best candidates remain disabled beside ASM.

| Function | Source unit | Best CURRENT |
| --- | --- | ---: |
| func_150DF920 | game_10CD70.c | 1696 |
| func_150E6B84 | game_113D60.c | 1907 |
| func_150EB614 | game_1188E0.c | 466 |
| func_150F6B00 | game_123FB0.c | 1672 |
| func_150FA1B8 | game_127060.c | 2446 |

Validation: full US refresh passed; image and mapped rodata unchanged. Progress and whitespace clean.
No exact matches, compilation repairs, permutations or shared dependency edits; m2c adapter stays separate.
Starter issues: E6B84's third emitter input is float bits; F6B00 adds phantom float arguments to integer variadic helpers. Corrected before comparisons.
Speed: audit raw callee contracts and complete output sizes before translating the starter.
