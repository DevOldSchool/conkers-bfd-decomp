#include "types.h"

/*
 * Reviewed source unit: src/game/game_12E540.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15101090
 * - func_15101148
 * - func_15101378
 * - func_151019C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1513CA6C(void);
void func_100111C8(u16);
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15101090 CURRENT (1558) */
void func_15101090(void *arg0) {
    void *object;

    if (*(u16 *)((u8 *)arg0 + 0x1A0) != 0) {
        func_100111C8(*(u16 *)((u8 *)arg0 + 0x1A0));
    }
    object = *(void **)((u8 *)arg0 + 0x138);
    if (object != 0) {
        func_1516972C(object);
    }
    object = *(void **)((u8 *)arg0 + 0x13C);
    if (object != 0) {
        func_1516972C(object);
    }
    object = *(void **)((u8 *)arg0 + 0x134);
    if (object != 0) {
        func_1516972C(object);
    }
    object = *(void **)((u8 *)arg0 + 0x140);
    if (object != 0) {
        func_1516972C(object);
    }
    object = *(void **)((u8 *)arg0 + 0x144);
    if (object != 0) {
        func_1516972C(object);
    }
    func_1513CA6C();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15101090 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12E540/func_15101090.s")
void func_1513CAA0(void);
void *func_1516979C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15101148 CURRENT (2583) */
void func_15101148(void *arg0) {
    void *sp18;
    void *var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x138) != 0) {
        func_1516979C(*(s32 *)((u8 *)arg0 + 0x138));
    }
    var_v0 = (u8 *)arg0 + 0x110;
    if (*(s32 *)((u8 *)arg0 + 0x13C) != 0) {
        sp18 = func_1516979C(*(s32 *)((u8 *)arg0 + 0x13C));
        var_v0 = sp18;
    }
    if (*(s32 *)((u8 *)var_v0 + 0x24) != 0) {
        sp18 = func_1516979C(*(s32 *)((u8 *)var_v0 + 0x24));
        var_v0 = sp18;
    }
    if (*(s32 *)((u8 *)var_v0 + 0x30) != 0) {
        sp18 = func_1516979C(*(s32 *)((u8 *)var_v0 + 0x30));
        var_v0 = sp18;
    }
    if (*(s32 *)((u8 *)var_v0 + 0x34) != 0) {
        func_1516979C(*(s32 *)((u8 *)var_v0 + 0x34));
    }
    func_1513CAA0();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15101148 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12E540/func_15101148.s")
void func_1513CA6C(void);

void func_151011E8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x124) + 0x110;
    *(s32 *)(temp_v0 + 0x28) = 0;
    func_1513CA6C();
}
void func_1513CAA0(void);

void func_15101210(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x124) + 0x110;
    *(s32 *)(temp_v0 + 0x28) = 0;
    func_1513CAA0();
}
void func_151617C4(void);

void func_15101238(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x18) + 0x110;
    *(s32 *)(temp_v0 + 0x2C) = 0;
    func_151617C4();
}
void func_151617E4(void);

void func_15101260(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x18) + 0x110;
    *(s32 *)(temp_v0 + 0x2C) = 0;
    func_151617E4();
}
void func_1513173C(void);

void func_15101288(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xD0) + 0x110;
    *(s32 *)(temp_v0 + 0x24) = 0;
    func_1513173C();
}
void func_1513175C(void);

void func_151012B0(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xD0) + 0x110;
    *(s32 *)(temp_v0 + 0x24) = 0;
    func_1513175C();
}
void func_151411A4(void);

void func_151012D8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x170) + 0x110;
    *(s32 *)(temp_v0 + 0x30) = 0;
    func_151411A4();
}
void func_151411C4(void);

void func_15101300(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x170) + 0x110;
    *(s32 *)(temp_v0 + 0x30) = 0;
    func_151411C4();
}
void func_15101328(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xA8) + 0x110;
    *(s32 *)(temp_v0 + 0x34) = 0;
    func_1513173C();
}
void func_15101350(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0xA8) + 0x110;
    *(s32 *)(temp_v0 + 0x34) = 0;
    func_1513175C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12E540/func_15101378.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12E540/func_151019C4.s")
