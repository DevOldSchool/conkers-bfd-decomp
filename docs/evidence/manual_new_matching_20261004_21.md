# Fresh manual matching — batch 21

Five new functions; fifteen manual comparisons. Best candidates remain disabled beside ASM.

| Function | Best CURRENT | Remaining differences |
| --- | ---: | --- |
| func_151B5BF0 | 3080 | Frame, packet homes and checksum registers |
| func_150585F0 | 595 | Unused argument home and float scheduling |
| func_151041E4 | 2306 | Frame, pointer homes and switch scheduling |
| func_1510CB10 | 6625 | Frame, address folding and pointer registers |
| func_1510E388 | 2374 | Frame, pointer homes and float registers |

Validation: full US refresh passed; image and mapped rodata unchanged. Progress and whitespace clean.
No exact matches or shared dependency edits; approved m2c adapter stays separate.
Starter bug: func_1510CB10 advances a u16 pointer by two elements; ASM advances two bytes. Corrected before comparisons.
Speed: verify unused argument positions and core/game aliases before recovering C.
