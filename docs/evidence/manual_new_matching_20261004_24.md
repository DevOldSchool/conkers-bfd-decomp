# Fresh manual matching — batch 24

Five new functions; fifteen manual comparisons. Best candidates preserved beside ASM.

| Function | Source unit | Best CURRENT |
| --- | --- | ---: |
| func_15109C20 | game_1368C0.c | 1265 |
| func_1513BBFC | game_168A90.c | 10188 |
| func_15165628 | game_191C30.c | 2709 |
| func_15182FDC | game_1AFC80.c | 4870 |
| func_15060778 | game_83300.c | 2818 |

Validation: full US refresh passed; image and mapped rodata unchanged. Progress and whitespace clean.
No exact matches, compilation repairs, permutations or shared dependency edits; setup adapter stays separate.
Starter issues corrected: omitted unused argument slot, phantom helper arguments and byte pointer for a halfword sound handle. Fixtures retained locally.
Speed: audit helper inputs and complete copy spans before compiling; use established source intrinsics for raw sqrt instructions.
