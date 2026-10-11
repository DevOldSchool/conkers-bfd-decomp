#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1844C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151571C4
 * - func_151572D0
 * - func_15157420
 * - func_15157918
 * - func_15157AA8
 * - func_15157F80
 * - func_15157FE8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Raw identity-matrix entry reads only a0. Legacy callers also forward
 * an unused a1, so retain an unspecified argument list for those calls. */
void func_150A7BC0();

void *func_10022EC0(void *, const void *, u32);
/* Raw callee forwards full-width a0 and stores full-width a1. */
s32 func_1503F62C(s32, s32, void *, void *, void **, void *, void *);
void *func_1515D480(s32);
extern s32 D_80082FA0;

s32 func_15157010(s32 arg0, s32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 var_s0;
    s32 var_s1;
    s32 temp_v0_2;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_v0;

    temp_v0_2 = *(u8 *)arg0;
    var_s0 = 0x36;
    if (temp_v0_2 & 0x80) {
        var_s0 = 0x5B;
    } else if (temp_v0_2 & 0x10) {
        var_s0 = 0x4C;
    }
    temp_v0 = func_15167A68(var_s0, arg7, arg5 + 0x120, 1, (u8) (s32) (u8) arg6, 1U);
    if (temp_v0 == 0) {
        return 0;
    }
    func_10022EC0(temp_v0 + 0x10, (u8 *) arg0, 0x58);
    func_1503F62C(*(s32 *)((u8 *)(temp_v0) + 0x18), *(s32 *)((u8 *)(temp_v0) + 0x1C), temp_v0 + 0x6C, temp_v0 + 0x70, (void **)(temp_v0 + 0x74), temp_v0 + 0x78, temp_v0 + 0x68);
    temp_s0 = temp_v0 + 0x7C;
    func_150A7BC0(temp_s0);
    temp_s1 = temp_v0 + 0xBC;
    func_150A7BC0(temp_s1);
    *(u8 **)(*(u8 **)(temp_v0 + 0x68) + 0x3E0) = temp_s0;
    *(u8 **)(*(u8 **)(temp_v0 + 0x68) + 0x3E4) = temp_s1;
    func_1503F5B8(*(void **)((u8 *)(temp_v0) + 0x68), 1, arg1, arg2, 0.0f, 0);
    *(s32 *)((u8 *)(temp_v0) + 0xFC) = arg3;
    *(s32 *)((u8 *)(temp_v0) + 0x118) = arg4;
    *(s8 *)((u8 *)(temp_v0) + 0x100) = 0;
    var_s1 = 0;
    temp_s0 = temp_v0;
    do {
        var_s1 += 1;
        temp_s0 += 4;
        *(s32 *)((u8 *)(temp_s0) + 0x100) = 0;
    } while (var_s1 < 4);
    *(u8 **)((u8 *)(temp_v0) + 0x114) = 0;
    if (arg3 != 0) {
        var_s1 = 0;
        temp_s0 = temp_v0;
        if (D_80082FA0 >= 0) {
            do {
                *(void **)((u8 *)(temp_s0) + 0x104) = func_1515D480(arg3);
                var_s1 += 1;
                temp_s0 += 4;
            } while (D_80082FA0 >= var_s1);
        }
        *(u8 **)((u8 *)(temp_v0) + 0x114) = func_1515D440();
    }
    return (s32) temp_v0;
}
void func_100043B4(s32, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151571C4 CURRENT (890) */
void func_151571C4(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    void *var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = *(s32 *)((u8 *)var_s0 + 0x104);
            if (temp_v0 != 0) {
                func_100043B4(temp_v0, 4);
            }
            var_s1 += 1;
            var_s0 = (u8 *)var_s0 + 4;
        } while (D_80082FA0 >= var_s1);
    }
    temp_v0_2 = *(s32 *)((u8 *)arg0 + 0x114);
    if (temp_v0_2 != 0) {
        func_100043B4(temp_v0_2, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151571C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_151571C4.s")
extern void func_151571C4(void *arg0);
extern void func_1518CA04(s32 arg0);

void func_15157248(void *arg0) {
    func_151571C4(arg0);
    func_1518CA04(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503F7B8(*(void **)((u8 *)arg0 + 0x68));
    func_15169804(arg0);
}
void func_1515728C(void *arg0) {
    func_151571C4(arg0);
    func_1518CA04(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503F7B8(*(void **)((u8 *)arg0 + 0x68));
    func_15169824(arg0);
}
extern s32 D_800BE9E4;
extern s32 (*D_8008AD90[])(u8 *);
extern s32 (*D_8008ADA0[])(u8 *);
void func_1503F4B0(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151572D0 CURRENT (2291) */
void func_151572D0(u8 *arg0) {
    u8 stopped = 0;
    s8 index;
    s16 count;
    s32 product;
    s32 callback_result;

    if (*(u8 *)(arg0 + 0x10) & 1) {
        *(s16 *)(arg0 + 0x16) = (s16)((u32)(s32)*(s16 *)(arg0 + 0x16) - (u32)D_800BE9E4);
        if (*(s16 *)(arg0 + 0x16) < 0) {
            stopped = 1;
        }
    }
    if (stopped == 0) {
        index = *(s8 *)(arg0 + 0x11);
        if (index != -1) {
            callback_result = D_8008AD90[index](arg0);
            if (callback_result == 0) {
                stopped = 1;
            }
        }
        index = *(s8 *)(arg0 + 0x12);
        if (index != -1) {
            callback_result = D_8008ADA0[index](arg0);
            if (callback_result == 0) {
                stopped = 1;
            }
        }
    }
    if (stopped == 0) {
        func_1503F4B0(*(void **)(arg0 + 0x68));
    }
    if (stopped == 0 && (*(u8 *)(arg0 + 0x10) & 0x20)) {
        count = *(s16 *)(arg0 + 0x16);
        if (count < *(s16 *)(arg0 + 0x64)) {
            product = count * *(s16 *)(arg0 + 0x66);
            if (product < *(u8 *)(arg0 + 0x43)) {
                *(u8 *)(arg0 + 0x43) = product;
            }
        }
    }
    if (stopped != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151572D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_151572D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157420.s")
extern u8 D_800BE9C0;

s32 func_15157860(s32 arg0) {
    func_150A7BC0((s32)((u8 *)arg0 + (D_800BE9C0 << 6) + 0x7C), arg0);
    return 1;
}
void func_15169260(void *arg0, s32 arg1, s32 arg2, u8 arg3);
extern u8 D_800A6060;
void *func_10022EC0(void *, const void *, u32);
s32 func_15157010(s32, s32, f32, s32, s32, s32, s32, s32);

s32 func_15157898(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4,
                  s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    s32 temp_v0;

    temp_v0 = func_15157010(arg0, arg2, arg3, arg4, arg5, arg6 + 0x38,
                            (s32)arg7, arg8);
    if (temp_v0 == 0) {
        return 0;
    }
    {
        s32 sp2C = temp_v0;
    func_10022EC0((void *)(temp_v0 + 0x120), (void *)arg1, 0x38);
    return sp2C;
    }
}
/* Call context: func_150A8050: unique active project prototype */
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157918 CURRENT (140) */
s32 func_15157918(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_v1;

    func_150A8050(arg0 + (D_800BE9C0 << 6) + 0x7C, *(f32 *)((u8 *)arg0 + 0x120), *(s32 *)((u8 *)arg0 + 0x124), *(f32 *)((u8 *)arg0 + 0x128));
    temp_a0 = (void *)(arg0 + 0x120);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xAC) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB0) = (f32) *(f32 *)((u8 *)arg0 + 0x58);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB4) = (f32) *(f32 *)((u8 *)arg0 + 0x5C);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x7C) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x80) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x84) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x8C) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x90) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x94) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x9C) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0xA0) *= *(f32 *)(temp_a0 + 0xC);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0xA4) *= *(f32 *)(temp_a0 + 0xC);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15157918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157918.s")
/* Slot 0 of D_8008AD90 receives the live owner. The selected constructor
 * paths reserve 0x158 bytes and copy 0x38 bytes at +0x120. These partial
 * views name only observed fields; unknown bytes remain opaque. The local
 * vector is the actual 12-byte velocity snapshot. Timing globals and the
 * live owner remain stable apart from these writes during normal execution,
 * with matching nontrapping binary32 operations.
 */
typedef struct Game1844C0MotionVector {
    f32 x;
    f32 y;
    f32 z;
} Game1844C0MotionVector;

typedef struct Game1844C0MotionOwnerPrefix {
    u8 unknown00[0x54];
    f32 positionX54;
    f32 positionY58;
    f32 positionZ5C;
} Game1844C0MotionOwnerPrefix;

typedef struct Game1844C0MotionExtension {
    f32 value00;
    f32 value04;
    f32 value08;
    u8 unknown0C[4];
    Game1844C0MotionVector velocity10;
    f32 rate1C;
    f32 rate20;
    f32 rate24;
    f32 acceleration28;
    f32 damping2C;
    u8 flags30;
} Game1844C0MotionExtension;

extern f32 D_800BE9A4;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157AA8 CURRENT (121) */
s32 func_15157AA8(u8 *arg0) {
    Game1844C0MotionOwnerPrefix *owner;
    Game1844C0MotionExtension *motion;
    Game1844C0MotionVector initialVelocity;
    u32 remaining;
    f32 accelerationX;
    f32 accelerationY;
    f32 accelerationZ;

    owner = (Game1844C0MotionOwnerPrefix *)arg0;
    motion = (Game1844C0MotionExtension *)(arg0 + 0x120);
    if (motion->flags30 & 1U) {
        initialVelocity = motion->velocity10;
        if (motion->flags30 & 8U) {
            remaining = (u32)D_800BE9E4;
            if (remaining != 0U) {
                do {
                    motion->velocity10.x =
                        motion->velocity10.x * motion->damping2C;
                    motion->velocity10.z =
                        motion->velocity10.z * motion->damping2C;
                    remaining -= 1U;
                } while (remaining != 0U);
            }
        }

        if (motion->flags30 & 4U) {
            accelerationY = motion->acceleration28;
            motion->velocity10.y =
                motion->velocity10.y + accelerationY * D_800BE9A4;
        } else {
            accelerationY = 0.0f;
        }

        accelerationX =
            (motion->velocity10.x - initialVelocity.x) * D_800BE9A8;
        accelerationZ =
            (motion->velocity10.z - initialVelocity.z) * D_800BE9A8;

        owner->positionX54 = owner->positionX54 +
            (initialVelocity.x + (0.5f * accelerationX) * D_800BE9A4) * D_800BE9A4;
        owner->positionY58 = owner->positionY58 +
            (initialVelocity.y + (0.5f * accelerationY) * D_800BE9A4) * D_800BE9A4;
        owner->positionZ5C = owner->positionZ5C +
            (initialVelocity.z + (0.5f * accelerationZ) * D_800BE9A4) * D_800BE9A4;
    }

    if (motion->flags30 & 2U) {
        motion->value00 = motion->value00 + motion->rate1C * D_800BE9A4;
        motion->value04 = motion->value04 + motion->rate20 * D_800BE9A4;
        motion->value08 = motion->value08 + motion->rate24 * D_800BE9A4;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15157AA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157AA8.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15157D88(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x4C, arg0 + 0x50, arg0);
}
s32 func_15157DC8(s32 arg0) {
    func_15157DEC((u8 *)arg0, (u8 *)(arg0 + 0x120));
    return 1;
}
void func_15157DEC(u8 *arg0, u8 *arg1) {
    u8 *temp_v0;

    func_150A8050((u8 *)((s32)arg0 + (D_800BE9C0 << 6) + 0x7C),
                   *(f32 *)(arg1 + 0), *(s32 *)(arg1 + 4), *(f32 *)(arg1 + 8));
    *(f32 *)(arg0 + (D_800BE9C0 << 6) + 0xAC) = *(f32 *)(arg0 + 0x54);
    *(f32 *)(arg0 + (D_800BE9C0 << 6) + 0xB0) = *(f32 *)(arg0 + 0x58);
    *(f32 *)(arg0 + (D_800BE9C0 << 6) + 0xB4) = *(f32 *)(arg0 + 0x5C);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0x7C) *= *(f32 *)(arg1 + 0xC);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0x80) *= *(f32 *)(arg1 + 0xC);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0x84) *= *(f32 *)(arg1 + 0xC);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0x8C) *= *(f32 *)(arg1 + 0x10);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0x90) *= *(f32 *)(arg1 + 0x10);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0x94) *= *(f32 *)(arg1 + 0x10);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0x9C) *= *(f32 *)(arg1 + 0xC);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0xA0) *= *(f32 *)(arg1 + 0xC);
    temp_v0 = (u8 *)((u32)arg0 + (D_800BE9C0 << 6));
    *(f32 *)(temp_v0 + 0xA4) *= *(f32 *)(arg1 + 0xC);
}
typedef struct Game1844C0DisplayCommand {
    u32 word0;
    void *word1;
} Game1844C0DisplayCommand;

typedef struct Game1844C0Matrix {
    u8 bytes[0x40];
} Game1844C0Matrix;

extern u8 D_80089470;
extern Game1844C0Matrix D_800DCC10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157F80 CURRENT (1435) */
Game1844C0DisplayCommand *func_15157F80(Game1844C0DisplayCommand *arg0, s32 arg1,
                                       s32 arg2, s32 arg3, u8 *arg4) {
    Game1844C0DisplayCommand *temp_v1;
    Game1844C0DisplayCommand *temp_a1;

    temp_v1 = arg0++;
    temp_v1->word0 = 0xDA380003;
    temp_v1->word1 = &D_80089470;
    temp_a1 = arg0++;
    temp_a1->word0 = 0xDA380007;
    temp_a1->word1 = &D_800DCC10[arg2];
    *arg4 = 1;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15157F80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157F80.s")
extern s32 D_800BE628;
extern u8 *D_800DC2A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157FE8 CURRENT (1860) */
void *func_15157FE8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_a3;
    u8 *var_v1;

    temp_a3 = &D_800BE9C0;
    var_v1 = (u8 *)arg0;
    *(s32 *)var_v1 = 0xDA380007;
    *(s32 *)(var_v1 + 4) = D_800BE628 + (arg2 * 0x180) + (*temp_a3 << 6) + 0x100;
    arg0 = (void *)((u8 *)arg0 + 8);
    *(s32 *)arg0 = 0xDA380005;
    *(s32 *)((u8 *)arg0 + 4) = (s32)(D_800DC2A0[*temp_a3] + (arg2 << 6));
    arg0 = (void *)((u8 *)arg0 + 8);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15157FE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157FE8.s")
void func_15158078(s32 arg0, u8 arg1) {
    func_15169260(&D_800A6060, 3, arg0, arg1);
}
