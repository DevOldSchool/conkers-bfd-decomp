#include "types.h"

/*
 * Reviewed source unit: src/game/game_137DE0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 */

typedef struct {
    void *resource;
    u8 pad_4[4];
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    u8 pad_1A[2];
    f32 field_1C;
    f32 field_20;
    s16 field_24;
    s16 field_26;
    s16 field_28;
    s16 field_2A;
    s16 field_2C;
    s16 field_2E;
    s8 field_30;
    s8 field_31;
    u8 field_32;
    u8 field_33;
    u8 field_34;
    s8 field_35;
    s8 field_36;
    s8 field_37;
    s8 field_38;
    s8 field_39;
} Game137DE0Descriptor;

void func_15169968(void *);
extern u8 D_800917EC;
extern f32 D_800A26A0;

void func_1510A930(s32 arg0, s32 arg1, s32 arg2) {
    Game137DE0Descriptor descriptor;
    s32 total;

    descriptor.resource = &D_800917EC;
    descriptor.field_30 = 0xA;
    descriptor.field_2C = 0x40;
    descriptor.field_2E = 0x20;
    descriptor.field_28 = 0x18FC;
    descriptor.field_2A = 0x1A12;
    descriptor.field_36 = 7;
    total = arg0 + arg1 + arg2;
    descriptor.field_39 = 0;
    descriptor.field_8 = (arg0 << 16) | arg1;
    descriptor.field_C = (arg2 << 16) | total;
    descriptor.field_10 = 0x2710;
    descriptor.field_14 = total;
    descriptor.field_18 = 0;
    descriptor.field_24 = 0;
    descriptor.field_26 = 0;
    descriptor.field_31 = 1;
    descriptor.field_32 = 0xFF;
    descriptor.field_33 = 0xFF;
    descriptor.field_34 = 0xFF;
    descriptor.field_37 = 0x11;
    descriptor.field_35 = 0;
    descriptor.field_16 = 0;
    descriptor.field_1C = 228.0f;
    descriptor.field_20 = D_800A26A0;
    func_15169968(&descriptor);
}
