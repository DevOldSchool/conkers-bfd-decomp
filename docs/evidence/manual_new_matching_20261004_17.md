# Fresh manual matching — batch 17

Five new functions; twelve comparisons and one compile repair.
Four best candidates remain disabled beside their original ASM.

| Function | Best CURRENT | Comparisons | Remaining differences |
| --- | ---: | ---: | --- |
| func_150144B8 | 207 | 3 | Thirty stack-only rows; buffers eight bytes high |
| func_15136404 | 1329 | 3 | Frame, buffer homes, FP constants, byte load |
| func_151AADF8 | Blocked | 0 | Existing two-argument RNG declaration conflicts with raw no-input calls |
| func_151D7A38 | 574 | 3 | Frame, vector homes, loop delay slot |
| func_151E6964 | 3149 | 3 | Frame, scan registers, allocation scheduling |

Validation: full US image and mapped rodata unchanged; progress and whitespace clean.
No exact matches or shared matching dependency edits in this batch.
Speed: flag incompatible active RNG declarations before emitting unset-argument scaffolds.
Approved m2c a8e59d6 remains selected; its local adapter is excluded from this commit.
