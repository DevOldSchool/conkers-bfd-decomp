# Fresh manual matching — batch 23

Five new functions; twelve manual comparisons. Four best candidates preserved beside ASM.

| Function | Source unit | Best CURRENT / status |
| --- | --- | ---: |
| func_151739B0 | game_1A0E60.c | 2332 |
| func_151A6350 | game_1D3800.c | 3944 |
| func_1502BAD0 | game_58F80.c | 1940 |
| func_150A0D8C | game_CDE80.c | 1208 |
| func_150A5B90 | game_D3040.c | blocked: handwritten register ABI |

Validation: full US refresh passed; image and mapped rodata unchanged. Progress and whitespace clean.
No exact matches, compilation repairs, permutations or shared dependency edits; setup adapter stays separate.
Starter issues corrected: halfword stride counts elements instead of bytes; extra vertex offsets can exceed the four-vertex output; zone radius read crosses a helper call. Fixtures retained locally.
Speed: audit pointer units, output bounds and post-call reloads before compiling; skip handwritten custom-register functions early.
