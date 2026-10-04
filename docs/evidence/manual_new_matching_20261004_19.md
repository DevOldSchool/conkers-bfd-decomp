# Fresh manual matching — batch 19

Five new functions; fifteen comparisons. Best candidates remain disabled beside ASM.

| Function | Best CURRENT | Comparisons | Remaining differences |
| --- | ---: | ---: | --- |
| func_15096A68 | 4205 | 3 | Frame, packet registers, spills and scheduling |
| func_1509BBA0 | 1290 | 3 | Key/flag registers and six extra rows |
| func_150D2450 | 951 | 3 | Frame, float homes and pointer scheduling |
| func_150FED30 | 3188 | 3 | Byte-home materialization and call/control scheduling |
| func_1514F8F8 | 2199 | 3 | Frame, buffer homes and hoisted pointers |

Validation: full US image and mapped rodata unchanged; progress and whitespace clean.
No exact matches or shared matching dependency edits. Approved m2c adapter stays separate.
Speed: include matched callee definitions in the single batched lookup.
