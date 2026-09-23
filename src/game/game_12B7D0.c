#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B7D0.c
 * Boundary evidence: docs/evidence/game_raw_slot_motion_attachment_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FE604
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12B7D0Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game12B7D0Vec3;

u32 func_150ADA20();
f32 func_150ADA68();
void func_15145740(void *, void *, void *, void *, f32);
void func_150FE49C(void *, u8, s32, Game12B7D0Vec3 *, Game12B7D0Vec3 *);
s32 func_151C229C(Game12B7D0Vec3 *, Game12B7D0Vec3 *, s32, s32, s32, s32,
                   f32, f32, f32, f32, f32, s32, void *, s32, s32, s32,
                   s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
extern f32 D_800A1FEC;

s32 func_150FE320(void *arg0, u8 arg1, s32 arg2) {
    u32 random;
    struct {
        f32 sp78;
        f32 sp7C;
        s32 unused80;
        Game12B7D0Vec3 sp84;
        Game12B7D0Vec3 sp90;
        Game12B7D0Vec3 sp9C;
        Game12B7D0Vec3 spA8;
    } locals;

    if (arg0 == 0) {
        return 0;
    }
    func_15145740(arg0, &locals.sp84, &locals.spA8, 0, 0.0f);
    func_150FE49C(arg0, arg1, arg2, &locals.sp9C, &locals.sp90);
    locals.sp78 = func_150ADA68();
    locals.sp7C = func_150ADA68();
    random = func_150ADA20();
    return func_151C229C(&locals.sp90, &locals.sp84, 0, 0, 0, 0, 300.0f, D_800A1FEC,
                          (locals.sp78 * 10.0f) + 25.0f, (locals.sp7C * 200.0f) + 600.0f,
                          50.0f, (random % 56U) + 0xC8, arg0,
                          1, 1, 0, 0xFF, 1, 1, 0, 0x23, 0.0f, 0xFF, -1,
                          0, arg1, arg2);
}

void func_15145EA4(s32 *, s32 *, s32, s32);
void func_151D3E6C(void *, void *, void *, s32);
void func_151D3F14(void *, u8, s32);
void func_150FE604(void *, Game12B7D0Vec3 *, u8, s32);
void func_150FE7D4(void *);
extern s32 D_800A1FC8;
extern s32 D_800A1FD4;
extern u8 D_80088B94;

void func_150FE49C(void *arg0, u8 arg1, s32 arg2,
                   Game12B7D0Vec3 *arg3, Game12B7D0Vec3 *arg4) {
    struct {
        Game12B7D0Vec3 *input_ptr;
        Game12B7D0Vec3 *output_ptr;
        void *source_ptr;
        void *target_ptr;
        Game12B7D0Vec3 output;
        Game12B7D0Vec3 input;
    } locals;

    if (arg0 == 0) {
        return;
    }
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        locals.source_ptr = &D_800A1FC8;
        locals.target_ptr = &D_800A1FD4;
        locals.input_ptr = &locals.input;
        locals.output_ptr = &locals.output;
        func_15145EA4((s32 *)&locals.source_ptr, (s32 *)&locals.input_ptr,
                      *(s32 *)((u8 *)arg0 + 0x1D4) + (D_80088B94 << 6), 2);
    } else {
        locals.input.x = *(f32 *)((u8 *)arg0 + 0x14);
        locals.input.y = *(f32 *)((u8 *)arg0 + 0x18) + 70.0f;
        locals.input.z = *(f32 *)((u8 *)arg0 + 0x1C);
        locals.output = locals.input;
    }
    func_151D3E6C(arg0, &locals.input, &locals.output, 0x23);
    func_151D3F14(&locals.input, arg1, arg2);
    func_150FE604(arg0, &locals.input, arg1, arg2);
    func_150FE7D4(arg0);
    if (arg3 != 0) {
        *arg3 = locals.input;
    }
    if (arg4 != 0) {
        *arg4 = locals.output;
    }
}
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32,
                   s32, s32, s32, s32);
extern s32 D_800A1FE0;
extern f32 D_800A1FF0;
extern f32 D_800A1FF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FE604 CURRENT (330) */
void func_150FE604(void *arg0, Game12B7D0Vec3 *arg1, u8 arg2, s32 arg3) {
    f32 values[2];
    u8 mask;
    u32 random0;
    u32 random1;
    u8 *object;
    u8 *actor = arg0;

    if ((*(s32 *)(actor + 0x1D4) != 0) && ((actor[0x74] & 0xF) != 0xF)) {
        f32 factor = 2.0f;

        values[1] = (func_150ADA68() * factor) + D_800A1FF0;
        values[0] = (func_150ADA68() * 15.0f) + 35.0f;
        object = *(u8 **)(actor + 0x31C);
        if ((object != 0) && (object[0x197] != 0) &&
            ((object = *(u8 **)(actor + 0x318)) != 0)) {
            mask = ~(1 << object[0x23D]);
        } else {
            mask = 0xFF;
        }
        random0 = func_150ADA20();
        random1 = func_150ADA20();
        func_15102B38((s32)arg0, D_80088B94, (s32)&D_800A1FC8,
                       (s32)&D_800A1FE0, values,
                       (random0 % 3U) + 4, (random1 % 56U) + 0xC8,
                       (func_150ADA68() * D_800A1FF4) + 500.0f,
                       (s32)arg1, mask, 0, -1, arg2, arg3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FE604 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B7D0/func_150FE604.s")
extern void func_151D3E04(s32 arg0, s32 arg1, s32 *arg2, u8 arg3, f32 arg4);
extern u8 D_80088B94;
extern s32 D_800A1FC8;

void func_150FE794(s32 arg0, s32 arg1, s32 arg2) {
    func_151D3E04(arg0, arg2, &D_800A1FC8, D_80088B94, 0.0f);
}
u32 func_150ADA20(void *);
void func_151D8868(s8 *, s32, s32, s32);

void func_150FE7D4(void *arg0) {
    struct {
        s8 field_0;
        s8 pad1;
        s16 field_2;
        s8 field_4;
        s8 field_5;
        s8 field_6;
    } sp18;

    if (*(void **)((u8 *)arg0 + 0x318) != 0) {
        sp18.field_0 = 1;
        sp18.field_2 = (s16) ((func_150ADA20(arg0) % 13U) + 0x14);
        sp18.field_5 = (s8) (1 << *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x318) + 0x23D));
        func_150ADA20(arg0);
        sp18.field_4 = 8;
        sp18.field_6 = -1;
        func_151D8868(&sp18.field_0, 0, 0xFF, 1);
    }
}
