#include "types.h"

/*
 * Reviewed source unit: src/game/game_80B80.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15053750
 * - func_150538CC
 * - func_150548E4
 * - func_15054A94
 * - func_15054F74
 * - func_1505528C
 * - func_15055A2C
 * - func_15055B0C
 * - func_15055C88
 * - func_15055D48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game80B80Object {
    s32 field_0;
    u8 pad4[0xE0];
    s16 field_E4;
    s16 field_E6;
} Game80B80Object;

void func_150536D0(Game80B80Object *arg0) {
    arg0->field_0 = 0xD;
    arg0->field_E4 = 0;
    arg0->field_E6 = 0;
}
void func_150536E8(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
}
void func_1505371C(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
}
void func_15062BDC(u8 *, f32, f32);
f32 fabsf(f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15053750 CURRENT (6625) */
void func_15053750(u8 *arg0) {
    f32 current;
    f32 previous;
    f32 delta;
    f32 limit;
    s32 direction;

    current = *(f32 *)(arg0 + 0x154);
    previous = *(f32 *)(arg0 + 0x14C);
    delta = current - previous;
    if (delta != 0.0f) {
        limit = *(f32 *)(arg0 + 0x15C);
        if (fabsf(delta) < limit) {
            func_15062BDC(arg0, current, *(f32 *)(arg0 + 0x150));
        } else {
            direction = 1;
            if (delta < 0.0f) {
                direction = -1;
            }
            func_15062BDC(arg0, (f32)direction * limit + previous,
                           *(f32 *)(arg0 + 0x150));
        }
    }
    current = *(f32 *)(arg0 + 0x158);
    previous = *(f32 *)(arg0 + 0x150);
    delta = current - previous;
    if (delta != 0.0f) {
        limit = *(f32 *)(arg0 + 0x15C);
        if (fabsf(delta) < limit) {
            func_15062BDC(arg0, *(f32 *)(arg0 + 0x14C), current);
            return;
        }
        direction = 1;
        if (delta < 0.0f) {
            direction = -1;
        }
        func_15062BDC(arg0, *(f32 *)(arg0 + 0x14C),
                       (f32)direction * limit + previous);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15053750 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15053750.s")
/* Call context: func_15060F28: unique active project prototype */
void func_15060F28(u8 *, s32);

void func_15053894(u8 *arg0) {
    if (++arg0[0x7F] >= 0x1F) {
        func_15060F28(arg0, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_150538CC.s")
void func_150548D8(s32 arg0) {

}
u32 func_150ADA20();
void func_10010344(s32, void *, s32, s32, s32);
extern s8 D_8008FD8C;
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150548E4 CURRENT (910) */
void func_150548E4(u8 *arg0) {
    s32 var_s1;
    s32 var_v0;
    u8 *var_s2;
    u8 *temp_s0;

    temp_s0 = (arg0[0x65] * 0x32C) - 0x32C + &D_800CC2D0;
    var_s1 = 0;
    if (D_8008FD8C > 0) {
        var_s2 = &D_800CC2D0;
        do {
            if ((((s32)(arg0 - &D_800CC2D0) / 812) + 1 == var_s2[0x274]) &&
                (temp_s0[0x232] == 1)) {
                *(s32 *)(temp_s0 + 0x218) = 0;
                if (func_150ADA20() & 1) {
                    temp_s0[0x232] = 2;
                    var_v0 = 0x1DB;
                } else {
                    temp_s0[0x232] = 3;
                    var_v0 = 0x1DC;
                }
                func_10010344(var_v0 & 0xFFFF, temp_s0, 0x7D00, 0x1F4, 0x9C4);
            }
            var_s1++;
            var_s2 += 0x32C;
        } while (var_s1 < D_8008FD8C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150548E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_150548E4.s")
void func_15054A0C(u8 *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x2D0);
    if ((temp_v0 != 0) && ((*(f32 *)((u8 *)temp_v0 + 0x18) - 1.0f) <= *(f32 *)((u8 *)temp_v0 + 8))) {
        func_15060F28(arg0, 0);
    }
}
void func_15054A5C(u8 *arg0, void *arg1) {
    *(s8 *)((u8 *)*(void **)((u8 *)arg1 + 0x31C) + 0x11A) = 0;
    func_151027E8(arg1);
    func_15060F28(arg0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15054A94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15054F74.s")
void func_150335C8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_15055260(void *arg0, void *arg1, s32 arg2) {
    func_150335C8(arg0, arg1, 0x4D, arg2, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_1505528C.s")
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(s32);
extern u16 D_8009919C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15055A2C CURRENT (777) */
void func_15055A2C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    s32 sp34;
    s32 sp30;
    s32 var_v1;
    u16 var_a0;

    var_a0 = 0x60D;
    if (arg4 == 1) {
        var_v1 = 0x64;
    } else {
        sp30 = 0x3E8;
        var_a0 = D_8009919C[func_150ADA20(0x60D) % 6U];
        var_v1 = 0x3E8;
    }
    sp30 = var_v1;
    sp34 = (s32)var_a0;
    func_10010F88(sp34, 0x7FBCU,
                  (s32)(s16)(func_150ADA20((s32)var_a0) % 500U), 0, 0,
                  (s32)arg1, (s32)arg2, (s32)arg3, sp30, 0xBB8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15055A2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055A2C.s")
/* Call context: func_1505E650: unique active project prototype */
void func_1505E650(u8 *, s32, s32, f32, f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15055B0C CURRENT (200) */
void func_15055B0C(u8 *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0) = 0x27;
    func_1505E650(arg0, (s32) *(u16 *)((u8 *)arg0 + 0x84), 0, 0.0f, 0.0f, 0.0f, 0);
    *(s16 *)((u8 *)arg0 + 0xE4) = 0;
    *(s16 *)((u8 *)arg0 + 0xE6) = 0;
    *(s16 *)((u8 *)arg0 + 0x21C) = (s16) arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15055B0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055B0C.s")
/* Call context: func_15060F28: unique active project prototype */
extern u8 D_800BE9A0;
extern s32 D_800BE9E4;

void func_15055B64(u8 *arg0) {
    u16 temp_v0;

    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    *(s32 *)((u8 *)arg0 + 0xF8) = (s32) (*(s32 *)((u8 *)arg0 + 0xF8) | 0x01000000);
    temp_v0 = *(u16 *)((u8 *)arg0 + 0x21C);
    if ((s32) D_800BE9A0 < (s32) temp_v0) {
        *(u16 *)((u8 *)arg0 + 0x21C) = (u16) (temp_v0 - D_800BE9E4);
        return;
    }
    *(u16 *)((u8 *)arg0 + 0x21C) = 0U;
    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        func_15060F28(arg0, 1);
    }
}
/* Call context: func_15060F28: unique active project prototype */
extern f32 D_800BE9A4;

void func_15055BF8(u8 *arg0) {
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    *(s32 *)((u8 *)arg0 + 0xF8) = (s32) (*(s32 *)((u8 *)arg0 + 0xF8) | 0x01000000);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x18) < (*(f32 *)((u8 *)arg0 + 0x180) - 100.0f)) {
        func_15060F28(arg0, 0);
    }
}
void func_1506160C(u8 *, s32, s32, s32, u8);
s32 func_1506E46C(u8 *, s32 *, s32);
void func_15060A30(s32, u8 *);
void func_1507CD64(u8 *, s32);
extern f32 D_80099418;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15055C88 CURRENT (505) */
void func_15055C88(u8 *arg0) {
    s32 sp2C;
    u8 *child;

    sp2C = 0x2007E4;
    if (!(*(s32 *)(arg0 + 0x9C) & 0x1000) && func_1506E46C(arg0, &sp2C, 1) != 0) {
        func_15060A30(sp2C, arg0);
    }
    child = *(u8 **)(arg0 + 0x31C);
    *(s8 *)(child + 0x36) = 0x64;
    func_1506160C(arg0, 2, 0, 6, 0);
    arg0[0x89] = 0xC8;
    arg0[0x83] = 0xC8;
    *(s32 *)arg0 = 0x29;
    *(f32 *)(arg0 + 0x1CC) = D_80099418;
    *(f32 *)(arg0 + 0x24) = 0.0f;
    *(f32 *)(arg0 + 0x20) = 0.0f;
    *(f32 *)(arg0 + 0x3C) = 0.0f;
    func_1507CD64(arg0, 9);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15055C88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055C88.s")
void func_1506D538(void);
extern f32 D_8009941C;
extern u8 D_800CC2D0;
extern u16 D_800D18A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15055D48 CURRENT (340) */
void func_15055D48(void *arg0) {
    u16 temp_t7;
    void *temp_v0;
    f32 scale;
    f32 value0;
    f32 value1;
    f32 value2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    *(u8 *)((u8 *)temp_v0 + 0x36) =
        (u8)(*(u8 *)((u8 *)temp_v0 + 0x36) + D_800BE9A0);
    if ((s32)*(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x31C) + 0x36) >= 0x8D) {
        temp_v0 = &D_800D18A0;
        temp_t7 = *(u16 *)temp_v0 |
                  (1 << ((s32)((u8 *)arg0 - &D_800CC2D0) / 812));
        *(u16 *)temp_v0 = temp_t7;
        if (temp_t7 & 0xFFFF) {
            *(u8 *)((u8 *)arg0 + 0x125) = 0xFF;
            *(u8 *)((u8 *)arg0 + 0x104) = 0xFF;
            *(u8 *)((u8 *)arg0 + 0x89) = 0xFF;
            *(s32 *)((u8 *)arg0 + 0xF8) |= 0x200;
            *(s16 *)((u8 *)arg0 + 0xE4) = 0;
            *(s16 *)((u8 *)arg0 + 0xE6) = 0;
            *(s8 *)((u8 *)arg0 + 7) = 0;
            *(s8 *)((u8 *)arg0 + 0x1CA) = 0;
            *(s32 *)arg0 = 5;
            *(f32 *)((u8 *)arg0 + 0x3C) = 0.0f;
            *(f32 *)((u8 *)arg0 + 0x20) = 0.0f;
            *(f32 *)((u8 *)arg0 + 0x24) = 0.0f;
            return;
        }
        func_1506D538();
    }
    scale = D_8009941C;
    value0 = *(f32 *)((u8 *)arg0 + 0x14C);
    value1 = *(f32 *)((u8 *)arg0 + 0x150);
    value2 = *(f32 *)((u8 *)arg0 + 0x3C);
    *(s8 *)((u8 *)arg0 + 0x1CA) = 0;
    *(f32 *)((u8 *)arg0 + 0x14C) = value0 * scale;
    *(f32 *)((u8 *)arg0 + 0x150) = value1 * scale;
    *(f32 *)((u8 *)arg0 + 0x3C) = value2 * scale;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15055D48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055D48.s")
