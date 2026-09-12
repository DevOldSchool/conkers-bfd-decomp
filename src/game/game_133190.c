#include "types.h"

/*
 * Reviewed source unit: src/game/game_133190.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15105CE0
 * - func_1510608C
 * - func_151061EC
 * - func_15106214
 * - func_15106610
 * - func_151067B8
 * - func_15106E78
 * - func_15106F50
 * - func_15106F98
 * - func_151070F8
 * - func_151072BC
 * - func_15107604
 * - func_151076A4
 * - func_15107700
 * - func_15107924
 * - func_15107A20
 * - func_15107AE0
 * - func_15107B78
 * - func_15107C1C
 * - func_15107E48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game133190Subobject {
    u8 pad0[8];
    s32 field_8;
} Game133190Subobject;

typedef struct Game133190Target {
    u8 pad0[0x28];
    Game133190Subobject subobject;
} Game133190Target;

typedef struct Game133190Holder {
    Game133190Target *target;
} Game133190Holder;

typedef struct Game133190Object {
    u8 pad0[0x60];
    Game133190Holder *holder;
} Game133190Object;

#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15105CE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_1510608C.s")
s32 func_151061E0(s32 arg0) {
    return arg0 + 0x88;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151061EC CURRENT (75) */
void *func_151061EC(u8 *arg0) {
    return arg0 + (*(s32 *)((u8 *)arg0 + 0x48) * 0x34) + 0x88;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151061EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151061EC.s")
/* Call context: func_151061E0: unique active project prototype */
/* Call context: func_151064B4: unique active project prototype */
/* Call context: func_151064DC: unique active project prototype */
/* Call context: func_15106510: unique active project prototype */
/* Call context: func_15106540: unique active project prototype */
/* Call context: func_15106558: unique active project prototype */
/* Call context: func_15106584: unique active project prototype */
/* Call context: func_151065BC: unique active project prototype */
/* Call context: func_151065EC: unique active project prototype */
f32 func_151064B4(f32);
f32 func_151064DC(f32);
f32 func_15106510(f32);
f32 func_15106540(f32);
f32 func_15106558(f32);
f32 func_15106584(f32);
f32 func_151065BC(f32);
f32 func_151065EC(f32);
s32 func_15146078(f32, s32, s32, s32);              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15106214 CURRENT (1386) */
void func_15106214(s32 arg0) {
    f32 sp78;
    f32 sp64;
    f32 sp60;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs0;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;

    temp_v0 = func_151061E0(arg0);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x64);
    var_s2 = 0;
    var_fs0 = temp_fv1;
    if (*(s32 *)((u8 *)arg0 + 0x48) > 0) {
        var_s1 = temp_v0;
        var_s3 = temp_v0 + 0x10;
        var_s4 = temp_v0 + 0x1C;
        var_s5 = temp_v0 + 0x28;
        sp78 = temp_fv1;
        do {
            *(f32 *)((u8 *)var_s1 + 0) = var_fs0;
            temp_fs5 = func_151064B4(var_fs0);
            sp64 = func_151064DC(var_fs0);
            sp60 = func_15106510(var_fs0);
            temp_fs1 = func_15106540(var_fs0);
            temp_fs2 = func_15106558(var_fs0);
            temp_fs3 = func_15106584(var_fs0);
            temp_fs4 = func_151065BC(var_fs0);
            temp_fv0 = func_151065EC(var_fs0);
            *(f32 *)((u8 *)var_s1 + 4) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38) * temp_fs1) + ((*(f32 *)((u8 *)arg0 + 0x14) * temp_fs5) + (*(f32 *)((u8 *)arg0 + 0x20) * sp64) + (*(f32 *)((u8 *)arg0 + 0x2C) * sp60)));
            *(f32 *)((u8 *)var_s1 + 8) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C) * temp_fs1) + ((*(f32 *)((u8 *)arg0 + 0x18) * temp_fs5) + (*(f32 *)((u8 *)arg0 + 0x24) * sp64) + (*(f32 *)((u8 *)arg0 + 0x30) * sp60)));
            *(f32 *)((u8 *)var_s1 + 0xC) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40) * temp_fs1) + ((*(f32 *)((u8 *)arg0 + 0x1C) * temp_fs5) + (*(f32 *)((u8 *)arg0 + 0x28) * sp64) + (*(f32 *)((u8 *)arg0 + 0x34) * sp60)));
            *(f32 *)((u8 *)var_s1 + 0x10) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38) * temp_fv0) + ((*(f32 *)((u8 *)arg0 + 0x14) * temp_fs2) + (*(f32 *)((u8 *)arg0 + 0x20) * temp_fs3) + (*(f32 *)((u8 *)arg0 + 0x2C) * temp_fs4)));
            *(f32 *)((u8 *)var_s1 + 0x14) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C) * temp_fv0) + ((*(f32 *)((u8 *)arg0 + 0x18) * temp_fs2) + (*(f32 *)((u8 *)arg0 + 0x24) * temp_fs3) + (*(f32 *)((u8 *)arg0 + 0x30) * temp_fs4)));
            *(f32 *)((u8 *)var_s1 + 0x18) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40) * temp_fv0) + ((*(f32 *)((u8 *)arg0 + 0x1C) * temp_fs2) + (*(f32 *)((u8 *)arg0 + 0x28) * temp_fs3) + (*(f32 *)((u8 *)arg0 + 0x34) * temp_fs4)));
            var_s2 += 1;
            if (func_15146078(sp64, var_s3, var_s4, var_s5) == 0) {
                *(f32 *)((u8 *)var_s1 + 0x1C) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x20) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x24) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x28) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x2C) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x30) = 0.0f;
            }
            var_s1 += 0x34;
            var_s3 += 0x34;
            var_s4 += 0x34;
            var_s5 += 0x34;
            var_fs0 += sp78;
        } while (var_s2 < *(s32 *)((u8 *)arg0 + 0x48));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15106214 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106214.s")
f32 func_151064B4(f32 arg0) {
    f32 temp_fv1;

    temp_fv1 = 1.0f - arg0;
    return temp_fv1 * temp_fv1 * temp_fv1;
}
f32 func_151064DC(f32 arg0) {
    f32 temp_fv1;

    temp_fv1 = 1.0f - arg0;
    return 3.0f * arg0 * temp_fv1 * temp_fv1;
}
f32 func_15106510(f32 arg0) {
    return 3.0f * arg0 * arg0 * (1.0f - arg0);
}
f32 func_15106540(f32 arg0) {
    return arg0 * arg0 * arg0;
}
f32 func_15106558(f32 arg0) {
    f32 temp_fv1;

    temp_fv1 = 1.0f - arg0;
    return -3.0f * temp_fv1 * temp_fv1;
}
f32 func_15106584(f32 arg0) {
    return ((9.0f * arg0 * arg0) - (12.0f * arg0)) + 3.0f;
}
f32 func_151065BC(f32 arg0) {
    return (-9.0f * arg0 * arg0) + (6.0f * arg0);
}
f32 func_151065EC(f32 arg0) {
    return 3.0f * arg0 * arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106610.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151067B8.s")
void func_15106E78(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);
void func_1510761C(void *arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106E78.s")
void func_15106EF8(s32 arg0) {
    func_15106E78(arg0);
    func_15169804(arg0);
}
void func_15106F24(s32 arg0) {
    func_15106E78(arg0);
    func_15169824(arg0);
}
extern void (*D_80088C28[])(void *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15106F50 CURRENT (237) */
void func_15106F50(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void (*temp_v0)(void *, s32, s32, s32);

    arg2 &= 0xFF;
    temp_v0 = D_80088C28[*(u8 *)((u8 *)arg0 + 0x5C)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2, arg3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15106F50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106F98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151070F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151072BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107604 CURRENT (20) */
Game133190Holder *func_15107604(Game133190Object *arg0) {
    Game133190Holder *holder = arg0->holder;
    Game133190Subobject *subobject = &holder->target->subobject;

    subobject->field_8 = 0;
    return holder;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107604 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107604.s")
void func_1516972C(void *arg0);

void func_1510761C(void *arg0) {
    volatile void **field_30 = (volatile void **)((u8 *)arg0 + 0x30);

    if (*field_30 != 0) {
        func_1516972C((void *)*field_30);
    }
}
void func_1510764C(s32 arg0) {
    func_1510761C((void *)arg0);
    func_1514933C(arg0);
}
void func_15107678(s32 arg0) {
    func_1510761C((void *)arg0);
    func_15149368(arg0);
}
extern u8 D_80088C38;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151076A4 CURRENT (605) */
void func_151076A4(void *arg0, s32 arg1, u8 arg2) {
    if (*(void **)((u8 *)&D_80088C38 + (*(u8 *)((u8 *)arg0 + 0x68) * 4)) != 0) {
        (*(void (**)(void *, s32, u8))((u8 *)&D_80088C38 + (*(u8 *)((u8 *)arg0 + 0x68) * 4)))(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151076A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151076A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107700.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151078E4(void *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x60);
    func_15169850(arg1, (s32) arg2, temp_a2, temp_a2 + 4, (s32) arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107924.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107A20.s")
extern f32 D_800A2420;
extern f32 D_800A2424;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107AE0 CURRENT (2490) */
void func_15107AE0(void *arg0, void *arg1, void *arg2, void *arg3) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = *(f32 *)((u8 *)arg1 + 0) - temp_fv1;
    temp_fa0 = *(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)arg0 + 4);
    {
        f32 temp_fa1 = *(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fv1 + (temp_fv0 * D_800A2420));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + (temp_fa0 * D_800A2420));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (temp_fa1 * D_800A2420));
    *(f32 *)((u8 *)arg3 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + (temp_fv0 * D_800A2424));
    *(f32 *)((u8 *)arg3 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + (temp_fa0 * D_800A2424));
    *(f32 *)((u8 *)arg3 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (temp_fa1 * D_800A2424));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107AE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107AE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107B78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107C1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107E48.s")
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);

void func_15107F54(void *arg0, u8 arg1, f32 *arg2, f32 *arg3) {
    func_15143134(arg2, arg3, *(s32 *)((u8 *)arg0 + 0x1D4) + (arg1 << 6));
}
void func_15107F98(void *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x60);
    func_15169850(arg1, (s32) arg2, temp_a2, temp_a2 + 4, (s32) arg0);
}
