#include "types.h"

/*
 * Reviewed source unit: src/game/game_200930.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D3480
 * - func_151D3D50
 * - func_151D3E04
 * - func_151D3E6C
 * - func_151D40D4
 * - func_151D42E8
 * - func_151D4408
 * - func_151D469C
 * - func_151D4794
 * - func_151D4C38
 * - func_151D4DAC
 * - func_151D5174
 * - func_151D5334
 * - func_151D5404
 * - func_151D5514
 * - func_151D5714
 * - func_151D57F8
 * - func_151D5A18
 * - func_151D5B6C
 * - func_151D5D60
 * - func_151D5E30
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game200930ResourceSlots {
    s32 entries[4];
} Game200930ResourceSlots;

void func_100043B4(s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3480.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3D50 CURRENT (739) */
s32 func_151D3D50(u8 *arg0) {
    void *sp18;
    f32 temp_fv0;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if (*(s16 *)((u8 *)arg0 + 0x170) > 0) {
        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (*(f32 *)((u8 *)temp_v0 + 4) + (*(f32 *)((u8 *)temp_v0 + 8) * D_800BE9A4));
        sp18 = temp_v0;
        temp_fv0 = func_15144B68(*(f32 *)((u8 *)temp_v0 + 4));
        *(f32 *)((u8 *)temp_v0 + 4) = temp_fv0;
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) ((func_15047D60(temp_fv0) * *(f32 *)((u8 *)temp_v0 + 0xC)) + *(f32 *)((u8 *)arg0 + 0x54));
        *(s16 *)((u8 *)arg0 + 0x170) = (s16) (*(s16 *)((u8 *)arg0 + 0x170) - D_800BE9E4);
    } else {
        *(s32 *)((u8 *)arg0 + 0x20) = (s32) *(s32 *)((u8 *)arg0 + 0x50);
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
        *(s32 *)((u8 *)arg0 + 0x28) = (s32) *(s32 *)((u8 *)arg0 + 0x58);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3D50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3D50.s")
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3E04 CURRENT (373) */
void func_151D3E04(void *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 arg4) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4);
    if (temp_v0 != 0) {
        func_15143134(arg2, arg1, temp_v0 + ((arg3 & 0xFF) << 6));
        return;
    }
    *(f32 *)((u8 *)arg1 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + arg4);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3E04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3E04.s")
extern u8 D_800CC2D0[];
s32 func_1505D1C4(f32, f32, f32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3E6C CURRENT (2377) */
void func_151D3E6C(void *arg0, void *arg1, void *arg2) {
    u16 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v0 != 0) {
        var_v1 = (u16)(*(u16 *)((u8 *)arg0 + 0x76) - *(s16 *)((u8 *)temp_v0 + 0x12));
    } else {
        var_v1 = *(u16 *)((u8 *)arg0 + 0x76);
    }
    func_1505D1C4(((*(f32 *)arg1) + (*(f32 *)arg2)) * 0.5f,
                  ((*(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg2 + 4))) * 0.5f,
                  ((*(f32 *)((u8 *)arg1 + 8)) + (*(f32 *)((u8 *)arg2 + 8))) * 0.5f,
                  ((s32)arg0 - (s32)D_800CC2D0) / 0x32C, var_v1, 0, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3E6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3E6C.s")
u32 func_150ADA20(void);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game200930Position {
    s32 x;
    s32 y;
    s32 z;
} Game200930Position;

typedef struct Game200930Particle {
    u8 type;
    s8 subtype;
    s16 duration;
    s8 flags;
} Game200930Particle;

void func_151D3F14(void *arg0, u8 arg1, s32 arg2) {
    Game200930Particle particle;
    Game200930Position position;

    particle.type = 3;
    particle.subtype = -1;
    particle.duration = (func_150ADA20() % 3U) + 4;
    particle.flags = 0;
    position.x = (s32)*(f32 *)((u8 *)arg0 + 0);
    position.y = (s32)*(f32 *)((u8 *)arg0 + 4);
    position.z = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&particle, &position.x,
                   (func_150ADA20() % 13U) + 0x14,
                   0xFF, 0xE8, 0xAB, 0xFF, 0, 0, arg1, arg2);
}
void func_151D3FF4(s32 arg0, u8 arg1, s32 arg2) {
    Game200930Particle particle;
    Game200930Position position;

    particle.type = 3;
    particle.subtype = -1;
    particle.duration = (func_150ADA20() % 11U) + 0x14;
    particle.flags = 0;
    position.x = (s32)*(f32 *)(arg0 + 0);
    position.y = (s32)*(f32 *)(arg0 + 4);
    position.z = (s32)*(f32 *)(arg0 + 8);
    func_151602C0((u8 *)&particle, &position.x,
                   (func_150ADA20() % 24U) + 0x22,
                   0xFF, 0xA1, 0xA2, 0xFF, 0, 0, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D40D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D42E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4408.s")
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_151D4668(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3C, (s32)arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D469C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4794.s")
void func_15149514(s32, u8, s32, s32, s32);
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D4C38 CURRENT (1130) */
void func_151D4C38(u8 *arg0, void *arg1, u8 arg2) {
    u8 *temp_a2;
    u8 *temp_a2_2;

    if (arg2 == 0x3C) {
        if ((*(s32 *)((u8 *)arg0 + 0x28) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)(arg0 + 0x28) + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 4) {
        temp_a2 = arg0 + 0x28;
        if ((*(s32 *)((u8 *)arg0 + 0x28) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            *(u8 *)((u8 *)temp_a2 + 0x10) = (u8) (*(u8 *)((u8 *)temp_a2 + 0x10) & 0xFFFE);
        }
    } else {
        temp_a2_2 = arg0 + 0x28;
        func_15149514((s32) arg1, arg2, (s32) temp_a2_2, (s32) (temp_a2_2 + 4), (s32) arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D4C38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4C38.s")
void func_15131828(s32, s32, s32, s32);
void func_15131958(void *, f32, s32);

s32 func_151D4D04(s32 arg0, s32 arg1) {
    u8 *sp20;
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131828(arg0, arg0 + 0xAC, (s32)temp_a2, arg0 + 0xAA);
    func_15131958((void *)(arg0 + 0x58), *(f32 *)(temp_a2 + 0xC),
                  (s32)temp_a2);
    return 1;
}
/* Call context: func_151D469C: unique active project prototype */
void func_151D469C(u8 *, s32, s32, s32, s32);

void func_151D4D58(u8 *arg0) {
    func_151D469C(arg0, 0, 0x50, 0xFF, 1);
    func_151D469C(arg0, 1, 0x50, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4DAC.s")
void func_151D5148(void *arg0) {
    void *temp_v0;
    s16 temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    temp_v1 = *(s16 *)((u8 *)temp_v0 + 0x24);
    if (temp_v1 > 0) {
        *(s16 *)((u8 *)temp_v0 + 0x24) = (s16) (temp_v1 - 1);
        temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    }
    *(s16 *)((u8 *)temp_v0 + 0x1AA) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x1AA) + 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5174.s")
void func_15164F0C(u8, u8, void *, u8, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5334 CURRENT (928) */
void func_151D5334(void *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4,
                   u8 arg5, s32 arg6) {
    typedef struct {
        s32 x;
        s32 y;
        s32 z;
    } Position;
    struct {
        Position position;
        f32 value1;
        f32 value2;
        f32 value3;
        u32 pad_18;
    } data;
    s32 i;

    i = 0;
    data.position = *(Position *)arg0;
    data.value1 = arg1;
    data.value2 = arg2;
    data.value3 = arg3;
    if ((D_80082FA0 + 1) > 0) {
        do {
            func_15164F0C(arg4, i, &data, arg5, arg6);
            i++;
        } while (D_80082FA0 >= i);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5334 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5334.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5404.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5514.s")
void func_151541B8(s32, f32, s32, f32, f32, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151D3FF4(s32, u8, s32);
void func_151D5514(s32, u8, s32);

void func_151D5648(s32 arg0, u8 arg1, s32 arg2) {
    volatile s32 spacer;
    f32 random_float;
    u32 random_value;

    func_151D5514(arg0, arg1, arg2);
    func_151D3FF4(arg0, arg1, arg2);
    random_float = func_150ADA68();
    random_value = (func_150ADA20() % 56U) + 0xC8;
    func_151541B8(arg0, (random_float * 4.0f) + 12.0f, 0x3FD20C49,
                  (f32)random_value, 0.0f, arg1, arg2);
}
void func_15145EA4(s32 *, s32 *, s32, s32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);

typedef struct Game200930Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game200930Vec3;

typedef struct Game200930RayLocals {
    Game200930Vec3 *second_ptr;
    Game200930Vec3 *first_ptr;
    s32 input[2];
    s32 transform;
    Game200930Vec3 first;
    Game200930Vec3 second;
} Game200930RayLocals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5714 CURRENT (2337) */
void func_151D5714(void *arg0, s32 arg1, s32 arg2, u8 arg3,
                   f32 arg4, u8 arg5, s32 arg6) {
    Game200930RayLocals locals;
    s32 temp_a2;
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4);
    if ((temp_v0 != 0) && ((*(u8 *)((u8 *)arg0 + 0x74) & 0xF) != 0xF)) {
        temp_a2 = temp_v0 + (arg3 << 6);
        locals.second_ptr = &locals.second;
        locals.first_ptr = &locals.first;
        locals.transform = temp_a2;
        locals.input[0] = arg1;
        locals.input[1] = arg2;
        func_15145EA4(locals.input, (s32 *)&locals.second_ptr, temp_a2, 2);
        locals.first.x -= locals.second.x;
        locals.first.y -= locals.second.y;
        locals.first.z -= locals.second.z;
        func_151D4408(&locals.second, &locals.first, locals.transform, arg0,
                       arg4, arg5, arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5714 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D57F8.s")
/* Call context: func_15145740: unique active project prototype */
/* Call context: func_15145EA4: unique active project prototype */
void func_15145740(void *, void *, void *, void *, f32);
void func_15145EA4(s32 *, s32 *, s32, s32);
extern f32 D_800AB240;
extern f32 D_800AB244;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5A18 CURRENT (4979) */
void func_151D5A18(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4, s32 arg5, u8 arg6) {
    s32 sp44;
    s32 sp40;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 var_ft4;
    f32 var_ft5;

    func_15145740(arg0, arg2, arg3, arg4, D_800AB240);
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        sp40 = arg1;
        sp44 = arg5;
        func_15145EA4(&sp44, &sp40, *(s32 *)((u8 *)arg0 + 0x1D4) + (arg6 << 6), 1);
        return;
    }
    temp_fa1 = *(f32 *)((u8 *)arg2 + 0);
    if ((D_800AB244 < fabsf(temp_fa1)) || (D_800AB244 < fabsf(*(f32 *)((u8 *)arg2 + 8)))) {
        temp_fv1 = *(f32 *)((u8 *)arg2 + 8);
        temp_fa0 = 1.0f / sqrtf((temp_fa1 * temp_fa1) + (temp_fv1 * temp_fv1));
        var_ft4 = temp_fv1 * temp_fa0;
        var_ft5 = -temp_fa1 * temp_fa0;
    } else {
        var_ft4 = 1.0f;
        var_ft5 = 0.0f;
    }
    *(f32 *)((u8 *)arg1 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (34.0f * var_ft5));
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 49.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) + (34.0f * var_ft4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5A18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5A18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5B6C.s")
s32 func_10003C40(s32, s32, s32, s32);
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5D60 CURRENT (1085) */
void func_151D5D60(volatile s32 arg0, s16 arg1, s32 arg2, s32 *arg3, u8 *arg4) {
    u8 fallback;
    s32 *entry;
    s32 value;
    s32 allocated;
    s32 offset;

    if (arg4 == 0) {
        arg4 = &fallback;
    }
    *arg4 = 0;
    entry = (s32 *)(arg0 + (arg1 * 4));
    value = *entry;
    if (value == 0) {
        allocated = func_10003C40(arg2 * 2, 1, 2, 1);
        *entry = allocated;
        if (allocated == 0) {
            *arg3 = 0;
            return;
        }
        *arg4 = 1;
        value = *entry;
    }
    offset = arg2;
    if (D_800BE9C0 != 0) {
        offset = 0;
    }
    *arg3 = offset + value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5D60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5D60.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5E30 CURRENT (405) */
void func_151D5E30(Game200930ResourceSlots *arg0) {
    register s32 resource;
    s32 index;

    index = 0;
    do {
        resource = arg0->entries[index];
        if (resource != 0) {
            func_100043B4(resource, 3);
        }
        index = (index + 1) & 0xFF;
    } while (index < 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5E30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5E30.s")
