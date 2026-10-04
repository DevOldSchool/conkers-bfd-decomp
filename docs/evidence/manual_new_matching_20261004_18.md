# Fresh manual matching — batch 18

Five new functions; thirteen comparisons, including one rejected candidate.
Four best candidates remain disabled beside their original ASM.

| Function | Best CURRENT | Comparisons | Remaining differences |
| --- | ---: | ---: | --- |
| func_15085710 | Blocked | 1 invalid | Existing u8 parameter conflicts with raw word stores/arithmetic |
| func_1512DEA4 | 4583 | 3 | Frame, offset homes, mode branches, FP scheduling |
| func_1513E83C | 2230 | 3 | Frame, buffer homes, sign extension, loop scheduling |
| func_15140410 | 730 | 3 | Stack homes and copy scheduling; vertex arithmetic/registers agree |
| func_15158684 | 2965 | 3 | Folded addresses and FP/GPR scheduling; frame/snapshot agree |

Validation: full US image and mapped rodata unchanged; progress and whitespace clean.
Refresh reported success despite outer exit 1; incremental confirmation returned 0.
No exact matches or shared matching dependency edits. Approved m2c adapter stays separate.
Speed: flag target parameter conflicts before the first C comparison.
