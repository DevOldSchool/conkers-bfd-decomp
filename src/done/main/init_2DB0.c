#include "types.h"

/*
 * Reviewed source unit: src/main/init_2DB0.c
 * Boundary evidence: docs/evidence/main_system_wrapper_boundaries.md
 */

s32 func_80023390(void);
u32 func_800233C0(void *);

s32 func_80002DB0(void *arg0, u32 arg1) {
    static u8 D_8002AB40 = 0;
    u8 *buffer;

    buffer = arg0;
    if (D_8002AB40 != 0) {
        buffer = (u8 *)arg0 - 0x2000;
    }
    if ((((u32)arg0 + arg1) & 0x3FFF) == 0x2000) {
        D_8002AB40 = 1;
    } else {
        D_8002AB40 = 0;
    }
    if (func_80023390() != 0) {
        return -1;
    }
    *(volatile u32 *)0xA4500000 = func_800233C0(buffer);
    *(volatile u32 *)0xA4500004 = arg1;
    return 0;
}
