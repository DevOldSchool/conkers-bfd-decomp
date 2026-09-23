#include "types.h"

/*
 * Reviewed source unit: src/game/game_10B380.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DDED0
 * - func_150DDFAC
 * - func_150DE12C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DDED0 CURRENT (230) */
void func_150DDED0(void *arg0) {
    void *object;
    u8 tag;

    object = func_151491F4(0x64, 2, -1, 1, 0, 1, 0xFF, 0);
    if (object == 0) {
        return;
    }
    tag = *(u8 *)((u8 *)arg0 + 0x72);
    switch (tag) {
    case 0xFB:
        *(s8 *)((u8 *)object + 0x28) = 1;
        break;
    case 0xFC:
        *(s8 *)((u8 *)object + 0x28) = 2;
        break;
    case 0xFD:
        *(s8 *)((u8 *)object + 0x28) = 4;
        break;
    case 0xFE:
        *(s8 *)((u8 *)object + 0x28) = 3;
        break;
    default:
        func_1516972C(object);
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DDED0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DDED0.s")
extern void func_150DBD70(u8, void *);

void func_150DDF88(void *arg0) {
    func_150DBD70(*(u8 *)((u8 *)arg0 + 0x28), arg0);
}
void *func_1513C73C(s32 *, s32, s32, void *, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32);
s32 func_150ADA20();
f32 func_150ADA68();

typedef struct {
    s32 field_00;
    s16 field_04;
    s8 field_06;
    u8 pad_07;
    s32 field_08;
    s32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 pad_16[2];
    s32 field_18;
    u32 pad_1C;
} Game10B380Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DDFAC CURRENT (233) */
s32 func_150DDFAC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, void *arg5) {
    void *sp8C;
    s32 sp88;
    Game10B380Packet packet;
    f32 sp5C;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    u8 *entry;

    sp8C = *(void **)(arg0 + 0x98);
    sp88 = *(s32 *)(arg0 + 0x94);
    sp5C = (func_150ADA68() * 70.0f) + 10.0f;
    *(s8 *)((u8 *)sp8C + 0x20) = 4;
    switch (func_150ADA20() & 1) {
    case 0:
        packet.field_06 = 0x1D;
        break;
    case 1:
        packet.field_06 = 0x1E;
        break;
    }
    packet.field_08 = 0;
    packet.field_0C = 0;
    packet.field_00 = 0x11;
    packet.field_04 = 0x64;
    packet.field_10 = 0xFF;
    packet.field_11 = 0xFF;
    packet.field_12 = 0;
    packet.field_13 = 0;
    packet.field_14 = 0;
    packet.field_15 = 0xFF;
    packet.field_18 = 0x30002;
    sp50 = func_150ADA20();
    sp54 = func_150ADA20();
    sp4C = func_150ADA20();
    entry = (u8 *)(sp88 + ((s8)arg0[0x2D] * 0x14));
    func_1513C73C(&packet.field_00, 5, 0, arg5, *(f32 *)entry, arg4,
                   *(f32 *)(entry + 8), sp5C, sp5C, sp50 & 0xFF,
                   (sp4C & 1) + (sp54 & 1), 0, arg0[0xC], arg0[1]);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DDFAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DDFAC.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DE12C CURRENT (233) */
s32 func_150DE12C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, void *arg5) {
    void *sp8C;
    s32 sp88;
    Game10B380Packet packet;
    f32 sp5C;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    u8 *entry;

    sp8C = *(void **)(arg0 + 0x98);
    sp88 = *(s32 *)(arg0 + 0x94);
    sp5C = (func_150ADA68() * 10.0f) + 10.0f;
    *(s8 *)((u8 *)sp8C + 0x20) = 4;
    switch (func_150ADA20() & 1) {
    case 0:
        packet.field_06 = 0x1B;
        break;
    case 1:
        packet.field_06 = 0x1C;
        break;
    }
    packet.field_08 = 0;
    packet.field_0C = 0;
    packet.field_00 = 0x11;
    packet.field_04 = 0x64;
    packet.field_10 = 0xFF;
    packet.field_11 = 0xFF;
    packet.field_12 = 0;
    packet.field_13 = 0;
    packet.field_14 = 0;
    packet.field_15 = 0xAA;
    packet.field_18 = 0x30002;
    sp50 = func_150ADA20();
    sp54 = func_150ADA20();
    sp4C = func_150ADA20();
    entry = (u8 *)(sp88 + ((s8)arg0[0x2D] * 0x14));
    func_1513C73C(&packet.field_00, 5, 0, arg5, *(f32 *)entry, arg4, *(f32 *)(entry + 8), sp5C, sp5C, sp50 & 0xFF, (sp4C & 1) + (sp54 & 1), 0, arg0[0xC], arg0[1]);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DE12C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DE12C.s")
typedef struct Game10B380Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} Game10B380Object;

s32 func_150DE2A4(Game10B380Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_28 = value * 8;
    }

    return 1;
}
void func_150DE2C4(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) - 0x1A);
    *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) - 0x1A);
    if ((*(s16 *)((u8 *)arg0 + 0x34) < 0xA) || (*(s16 *)((u8 *)arg0 + 0x36) < 0xA)) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
    }
}
