#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B250.c
 * Boundary evidence: docs/evidence/game_raw_slot_motion_attachment_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FE0B8
 * - func_150FE288
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12B250Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game12B250Vec3;

void func_15145740(void *, void *, void *, void *, f32);
void func_150FDF38(void *, u8, s32, Game12B250Vec3 *, Game12B250Vec3 *);
u32 func_150ADA20();
f32 func_150ADA68(void);
s32 func_151C229C(Game12B250Vec3 *, Game12B250Vec3 *, s32, s32, s32,
                   s32, f32, f32, f32, f32, f32, s32, void *, s32, s32,
                   s32, s32, s32, s32, s32, s32, f32, s32, s32, s32,
                   s32, s32);
extern f32 D_800A1F94;
extern f32 D_800A1F98;
extern s32 D_800BE9F0;

s32 func_150FDDA0(void *arg0, u8 arg1, s32 arg2) {
    u32 random;
    struct {
        f32 sp7C;
        f32 sp80;
        s32 pad84[2];
        Game12B250Vec3 sp8C;
        Game12B250Vec3 sp98;
        Game12B250Vec3 spA4;
        Game12B250Vec3 spB0;
    } locals;

    if (arg0 == 0) {
        return 0;
    }
    func_15145740(arg0, &locals.sp98, &locals.spB0, 0, 0.0f);
    func_150FDF38(arg0, arg1, arg2, &locals.spA4, &locals.sp8C);
    locals.sp7C = func_150ADA68();
    locals.sp80 = func_150ADA68();
    random = func_150ADA20();
    return func_151C229C(&locals.sp8C, 0, &locals.sp8C, &locals.sp98,
                          0, 0, 300.0f, D_800A1F94,
                          (locals.sp7C * 10.0f) + 25.0f,
                          (locals.sp80 * 201.0f) + D_800A1F98, 50.0f,
                          (random % 56U) + 0xC8, arg0, 1, 1, 0, 0xFF,
                          1, 1, 0, D_800BE9F0 == 0x2B ? 0x27 : 0x1A,
                          0.0f, 0xFF, -1, 0, arg1, arg2);
}

void func_15145EA4(s32 *, s32 *, s32, s32);
void func_151D3E6C(void *, void *, void *, s32);
void func_151D3F14(void *, u8, s32);
void func_150FE0B8(u8 *, Game12B250Vec3 *, u8, s32);
void func_150FE288(void *);
extern s32 D_800A1F70;
extern s32 D_800A1F88;
extern u8 D_80088B80;
extern s32 D_800BE9F0;

void func_150FDF38(void *arg0, u8 arg1, s32 arg2,
                   Game12B250Vec3 *arg3, Game12B250Vec3 *arg4) {
    struct {
        Game12B250Vec3 *input_ptr;
        Game12B250Vec3 *output_ptr;
        void *source_ptr;
        void *target_ptr;
        Game12B250Vec3 output;
        Game12B250Vec3 input;
    } locals;

    if (arg0 == 0) {
        return;
    }
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        locals.source_ptr = &D_800A1F70;
        locals.target_ptr = &D_800A1F88;
        locals.input_ptr = &locals.input;
        locals.output_ptr = &locals.output;
        func_15145EA4((s32 *)&locals.source_ptr, (s32 *)&locals.input_ptr,
                      *(s32 *)((u8 *)arg0 + 0x1D4) + (D_80088B80 << 6), 2);
    } else {
        locals.input.x = *(f32 *)((u8 *)arg0 + 0x14);
        locals.input.y = *(f32 *)((u8 *)arg0 + 0x18) + 56.0f;
        locals.input.z = *(f32 *)((u8 *)arg0 + 0x1C);
        locals.output = locals.input;
    }
    func_151D3E6C(arg0, &locals.input, &locals.output,
                   D_800BE9F0 == 0x2B ? 0x28 : 0x1E);
    func_151D3F14(&locals.input, arg1, arg2);
    func_150FE0B8(arg0, &locals.input, arg1, arg2);
    func_150FE288(arg0);
    if (arg3 != 0) {
        *arg3 = locals.input;
    }
    if (arg4 != 0) {
        *arg4 = locals.output;
    }
}
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32,
                   s32, s32, s32, s32);
extern s32 D_800A1F7C;
extern f32 D_800A1F9C;
extern f32 D_800A1FA0;
extern f32 D_800A1FA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FE0B8 CURRENT (171) */
void func_150FE0B8(u8 *arg0, Game12B250Vec3 *arg1, u8 arg2, s32 arg3) {
    f32 values[2];
    u8 mask;
    u32 random0;
    u32 random1;
    u8 *object;

    if ((*(s32 *)(arg0 + 0x1D4) != 0) && ((arg0[0x74] & 0xF) != 0xF)) {
        values[1] = (func_150ADA68() * 1.5f) + 2.0f;
        values[0] = (func_150ADA68() * D_800A1F9C) + D_800A1FA0;
        object = *(u8 **)(arg0 + 0x31C);
        if ((object != 0) && (object[0x197] != 0) &&
            ((object = *(u8 **)(arg0 + 0x318)) != 0)) {
            mask = ~(1 << object[0x23D]);
        } else {
            mask = 0xFF;
        }
        random0 = func_150ADA20();
        random1 = func_150ADA20();
        func_15102B38((s32)arg0, D_80088B80, (s32)&D_800A1F70,
                       (s32)&D_800A1F7C, values,
                       (random0 % 5U) + 6, (random1 % 101U) + 0x9B,
                       (func_150ADA68() * 199.0f) + D_800A1FA4,
                       (s32)arg1, mask, 0, -1, arg2, arg3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FE0B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FE0B8.s")
extern void func_151D3E04(s32 arg0, s32 arg1, s32 *arg2, u8 arg3, f32 arg4);

void func_150FE248(s32 arg0, s32 arg1, s32 arg2) {
    func_151D3E04(arg0, arg2, &D_800A1F70, D_80088B80, 0.0f);
}
typedef struct {
    s8 field_0;
    s8 pad1;
    s16 field_2;
    s8 field_4;
    s8 field_5;
    s8 field_6;
} Game12B250EventPacket;

u32 func_150ADA20(void *);
void func_151D8868(s8 *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FE288 CURRENT (400) */
void func_150FE288(void *arg0) {
    Game12B250EventPacket packet;

    if (*(void **)((u8 *)arg0 + 0x318) != 0) {
        packet.field_0 = 1;
        packet.field_2 = (func_150ADA20(arg0) % 9U) + 0xF;
        packet.field_5 = 1 << *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x318) + 0x23D);
        packet.field_4 = (func_150ADA20(arg0) & 3) + 3;
        packet.field_6 = -1;
        func_151D8868(&packet.field_0, 0, 0xFF, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FE288 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FE288.s")
