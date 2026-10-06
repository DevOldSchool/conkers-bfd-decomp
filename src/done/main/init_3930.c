#include "types.h"

/*
 * Reviewed source unit: src/main/init_3930.c
 * Boundary evidence: docs/evidence/boundaries/main/main_system_wrapper_boundaries.md
 */

extern u8 D_80038080;
extern u32 D_80038090;
extern u32 D_80038094;
extern u32 D_80038098;
extern u32 D_8003809C;

void func_80003930(void) {
    if (D_80038080 != 0) {
        D_80038090 = 0x807F5000;
        D_80038094 = 0x807FE000;
        D_8003809C = 0x807FE000;
        D_80038098 = 0x807F5000;
        return;
    }
    D_80038090 = 0x803F5000;
    D_80038094 = 0x803FE000;
    D_8003809C = 0x803FE000;
    D_80038098 = 0x803F5000;
}
