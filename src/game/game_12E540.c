#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_12E540.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15101378
 * - func_151019C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100111C8(u16);

void func_15101090(void *arg0) {
    u8 *p;

    p = (u8 *)arg0 + 0x110;
    if (*(u16 *)(p + 0x90) != 0) {
        func_100111C8(*(u16 *)(p + 0x90));
    }
    if (*(void **)(p + 0x28) != NULL) {
        func_1516972C(*(void **)(p + 0x28));
    }
    if (*(void **)(p + 0x2C) != NULL) {
        func_1516972C(*(void **)(p + 0x2C));
    }
    if (*(void **)(p + 0x24) != NULL) {
        func_1516972C(*(void **)(p + 0x24));
    }
    if (*(void **)(p + 0x30) != NULL) {
        func_1516972C(*(void **)(p + 0x30));
    }
    if (*(void **)(p + 0x34) != NULL) {
        func_1516972C(*(void **)(p + 0x34));
    }
    func_1513CA6C(arg0);
}

void func_15101148(void *arg0) {
    u8 *p;

    p = (u8 *)arg0 + 0x110;
    if (*(void **)(p + 0x28) != NULL) {
        func_1516979C(*(void **)(p + 0x28));
    }
    if (*(void **)(p + 0x2C) != NULL) {
        func_1516979C(*(void **)(p + 0x2C));
    }
    if (*(void **)(p + 0x24) != NULL) {
        func_1516979C(*(void **)(p + 0x24));
    }
    if (*(void **)(p + 0x30) != NULL) {
        func_1516979C(*(void **)(p + 0x30));
    }
    if (*(void **)(p + 0x34) != NULL) {
        func_1516979C(*(void **)(p + 0x34));
    }
    func_1513CAA0(arg0);
}

void func_151011E8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x124) + 0x110;
    *(s32 *)(temp_v0 + 0x28) = 0;
    func_1513CA6C(arg0);
}

void func_15101210(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x124) + 0x110;
    *(s32 *)(temp_v0 + 0x28) = 0;
    func_1513CAA0(arg0);
}

void func_15101238(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x18) + 0x110;
    *(s32 *)(temp_v0 + 0x2C) = 0;
    func_151617C4(arg0);
}

void func_15101260(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x18) + 0x110;
    *(s32 *)(temp_v0 + 0x2C) = 0;
    func_151617E4(arg0);
}

void func_15101288(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xD0) + 0x110;
    *(s32 *)(temp_v0 + 0x24) = 0;
    func_1513173C(arg0);
}

void func_151012B0(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xD0) + 0x110;
    *(s32 *)(temp_v0 + 0x24) = 0;
    func_1513175C(arg0);
}

void func_151012D8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x170) + 0x110;
    *(s32 *)(temp_v0 + 0x30) = 0;
    func_151411A4(arg0);
}

void func_15101300(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x170) + 0x110;
    *(s32 *)(temp_v0 + 0x30) = 0;
    func_151411C4(arg0);
}
void func_15101328(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xA8) + 0x110;
    *(s32 *)(temp_v0 + 0x34) = 0;
    func_1513173C(arg0);
}
void func_15101350(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xA8) + 0x110;
    *(s32 *)(temp_v0 + 0x34) = 0;
    func_1513175C(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12E540/func_15101378.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12E540/func_151019C4.s")
