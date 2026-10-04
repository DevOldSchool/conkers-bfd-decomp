# Fresh manual matching — batch 16

Five new functions; fourteen manual comparisons, no permutation or compile repairs.
Best candidates remain disabled beside their original ASM.

| Function | Best CURRENT | Attempts | Remaining differences |
| --- | ---: | ---: | --- |
| func_151E7F60 | 3521 | 3 | Frame, homes, persistent global base |
| func_15004FE0 | 1464 | 2 | Count/index homes, GPR and FP ordering |
| func_150C73E0 | 1150 | 3 | FP scheduling and quarter constant reuse |
| func_150E1570 | 775 | 3 | Loop registers and initialization order |
| func_151C4820 | 974 | 3 | Frame, vector/timestep homes, tail scheduling |

Validation: US image and mapped rodata unchanged; progress and whitespace clean.
No exact matches or shared matching dependency edits in this batch.
Speed: retain complete writer buffers and expose parallel FP products before tuning homes.
Approved m2c a8e59d6 is active; its local override adapter is excluded from this commit.
