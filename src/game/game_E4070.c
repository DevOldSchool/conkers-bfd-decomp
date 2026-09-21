#include "types.h"

/*
 * Reviewed source unit: src/game/game_E4070.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B6BC0
 * - func_150B6C90
 * - func_150B6D34
 * - func_150B6D78
 * - func_150B6E3C
 * - func_150B709C
 * - func_150B71A8
 * - func_150B7220
 * - func_150B73F0
 * - func_150B76BC
 * - func_150B77A8
 * - func_150B791C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150B6C90(void);
void func_150B6D34(void);
void func_150B6D78(void);
void func_150B7484(void);
void func_150B7560(void);
void func_150B765C(void);
void func_150B768C(void);
void func_150B77A8(void);
void func_150B791C(void);
extern s8 D_800D9890;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6BC0 */
void func_150B6BC0(s32 arg0) {
    switch ((u8)D_800D9890) {
    case 1:
        func_150B6C90();
        return;
    case 2:
        func_150B6D34();
        return;
    case 4:
        func_150B6D78();
        return;
    case 5:
        func_150B7484();
        return;
    case 6:
        func_150B7560();
        return;
    case 7:
        func_150B765C();
        return;
    case 8:
        func_150B77A8();
        return;
    case 9:
        func_150B768C();
        return;
    case 10:
        func_150B791C();
    default:
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6BC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6BC0.s")
extern s32 D_800BE9E8;
extern s32 D_800D9894;
extern s32 D_800D9898;
extern s32 D_800D989C;
extern s32 D_800D98A0;
extern s32 D_800D98C0;
extern s8 D_800D9890;
void func_1516972C(s32);
s32 func_151A4FD0(s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6C90 CURRENT (2125) */
void func_150B6C90(void) {
    s32 *var_v0;
    s32 *var_v1;

    if (D_800D9894 != 0) {
        func_1516972C(D_800D9894);
    }
    D_800D9894 = func_151A4FD0(0, 0, 0xFF, 0, 0, D_800BE9E8, 0, 0);
    D_800D9890 = 3;
    var_v0 = &D_800D98A0;
    var_v1 = &D_800D98C0;
    D_800D9898 = 0;
    D_800D989C = 0;
    do {
        var_v0 += 4;
        var_v0[-3] = 0;
        var_v0[-2] = 0;
        var_v0[-1] = 0;
        var_v0[-4] = 0;
    } while (var_v0 != var_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6C90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6C90.s")
extern s32 D_800D9898;
extern s32 D_800D98A4;
extern s8 D_800D9890;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6D34 CURRENT (2720) */
void func_150B6D34(void) {
    u8 *var_v1;
    void *temp_v0;

    var_v1 = (u8 *) &D_800D9898;
    do {
        temp_v0 = *(void **)(var_v1 + 0x14);
        var_v1 += 4;
        if (temp_v0 != 0) {
            *(s32 *)((u8 *)temp_v0 + 0x20) = 1;
        }
    } while (var_v1 != (u8 *) &D_800D98A4);
    D_800D9890 = 3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6D34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6D34.s")
extern s32 D_800D9894;
extern s32 D_800D98C0;
extern s8 D_800D9890;
void func_1516972C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6D78 CURRENT (20) */
void func_150B6D78(void) {
    s32 *var_s0;
    s32 *var_s1;
    s32 temp_a0;

    if (D_800D9894 != 0) {
        func_1516972C(D_800D9894);
        D_800D9894 = 0;
    }
    var_s1 = &D_800D98C0;
    var_s0 = &D_800D9898;
    do {
        temp_a0 = *var_s0;
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
            *var_s0 = 0;
        }
        var_s0 += 1;
    } while (var_s0 != var_s1);
    D_800D9890 = 3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6D78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6D78.s")
extern s32 D_800BE9E4;

void func_150B6DFC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + (D_800BE9E4 * 0x30));
    if (*(s16 *)((u8 *)arg0 + 0x34) >= 0x801) {
        *(s16 *)((u8 *)arg0 + 0x34) = -0xC00;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6E3C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B709C CURRENT (260) */
void func_150B709C(void *arg0) {
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x18);
    if (temp_v0 == 0x1E) {
        var_v1 = *(u8 *)((u8 *)arg0 + 0x45) + (D_800BE9E4 * 8);
        if (var_v1 >= 0x100) {
            var_v1 = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x45) = (u8) var_v1;
    }
    var_v0 = temp_v0 + (D_800BE9E4 * 2);
    if (var_v0 >= 0x1F) {
        var_v0 = 0x1E;
    }
    *(s32 *)((u8 *)arg0 + 0x18) = var_v0;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (((s32) (var_v0 * -0x54) / 30) + 0xE6);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (((s32) (var_v0 * -0x32) / 30) + 0xAA);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B709C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B709C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B71A8 CURRENT (20) */
void func_150B71A8(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x38);
    if (temp_v0 != 0x1000) {
        *(s16 *)((u8 *)arg0 + 0x38) = (s16) (temp_v0 + (D_800BE9E4 << 8));
        if (*(s16 *)((u8 *)arg0 + 0x38) >= 0x1001) {
            *(s16 *)((u8 *)arg0 + 0x38) = 0x1000;
        }
    } else {
        temp_v0_2 = *(s16 *)((u8 *)arg0 + 0x3A);
        if (temp_v0_2 != 0x1000) {
            *(s16 *)((u8 *)arg0 + 0x3A) = (s16) (temp_v0_2 + (D_800BE9E4 << 8));
            if (*(s16 *)((u8 *)arg0 + 0x3A) >= 0x1001) {
                *(s16 *)((u8 *)arg0 + 0x3A) = 0x1000;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B71A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B71A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7220.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B73F0 CURRENT (175) */
void func_150B73F0(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x18);
    temp_lo = (s32) (*(s16 *)((u8 *)arg0 + 0x24) << 0x10) / (s32) *(s32 *)((u8 *)arg0 + 0x1C);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1A);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (((s32) ((*(s16 *)((u8 *)arg0 + 0x20) - temp_v0) * temp_lo) >> 0x10) + temp_v0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (((s32) ((*(s16 *)((u8 *)arg0 + 0x22) - temp_v1) * temp_lo) >> 0x10) + temp_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B73F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B73F0.s")
typedef struct {
    void *resource;
    u8 pad04[0x10];
    s16 position[3];
    u8 pad1A[2];
    f32 scale_x;
    f32 scale_y;
    s16 field24;
    s16 field26;
    s16 field28;
    s16 field2A;
    s16 field2C;
    s16 field2E;
    u8 field30;
    u8 field31;
    u8 field32;
    u8 field33;
    u8 field34;
    u8 field35;
    u8 field36;
    u8 field37;
    u8 field38;
    u8 field39;
} GameE4070Descriptor;

extern u8 D_800918DC;
s32 func_15169968(void *);

void func_150B7484(void) {
    GameE4070Descriptor descriptor;

    descriptor.field31 = 1;
    descriptor.field2C = 0x58;
    descriptor.scale_x = 60.0f;
    descriptor.scale_y = 60.0f;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.position[2] = 0;
    descriptor.field2E = 0x58;
    descriptor.field30 = 6;
    descriptor.resource = &D_800918DC;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field39 = 0;
    descriptor.field36 = 7;
    descriptor.field37 = 0x15;
    descriptor.field38 = 1;
    descriptor.field28 = 0x51;
    descriptor.field2A = 0x51;
    if (D_800D9898 != 0) {
        func_1516972C(D_800D9898);
    }
    D_800D9898 = func_15169968(&descriptor);
    D_800D9890 = 3;
}
void func_150B7560(void) {
    GameE4070Descriptor descriptor;

    if (D_800D9898 != 0) {
        func_1516972C(D_800D9898);
        D_800D9898 = 0;
    }
    descriptor.position[2] = 0x4D;
    descriptor.field31 = 0xF;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.field2C = 0x58;
    descriptor.field2E = 0x58;
    descriptor.field30 = 0;
    descriptor.resource = &D_800918DC;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field36 = 7;
    descriptor.field37 = 0x11;
    descriptor.field38 = 1;
    descriptor.field39 = 0;
    descriptor.field28 = 0x1000;
    descriptor.field2A = 0x1000;
    descriptor.scale_x = 60.0f;
    descriptor.scale_y = 60.0f;
    if (D_800D98A4 != 0) {
        func_1516972C(D_800D98A4);
    }
    D_800D98A4 = func_15169968(&descriptor);
    D_800D9890 = 3;
}
void func_150B76BC(s32 arg0, s32 arg1);
extern s8 D_800D9890;

void func_150B765C(void) {
    func_150B76BC(0x3C, 1);
    D_800D9890 = 3;
}
void func_150B768C(void) {
    func_150B76BC(0xE6, 2);
    D_800D9890 = 3;
}
extern u8 D_800918E8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B76BC CURRENT (1315) */
void func_150B76BC(s32 arg0, s32 arg1) {
    GameE4070Descriptor descriptor;
    s32 *entry;
    s32 resource;

    descriptor.field30 = 6;
    descriptor.field2E = 0x40;
    entry = &(&D_800D9898)[arg1];
    resource = *entry;
    descriptor.field31 = 1;
    descriptor.field2C = 0x58;
    descriptor.scale_x = (f32)arg0;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.position[2] = 0;
    descriptor.resource = &D_800918E8;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field39 = 0;
    descriptor.field36 = 7;
    descriptor.field37 = 0x15;
    descriptor.field38 = 1;
    descriptor.field28 = 0x51;
    descriptor.field2A = 0x51;
    descriptor.scale_y = 170.0f;
    if (resource != 0) {
        func_1516972C(resource);
    }
    *entry = func_15169968(&descriptor);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B76BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B76BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B77A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B791C.s")
