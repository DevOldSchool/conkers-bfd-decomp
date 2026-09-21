#include "types.h"

/*
 * Reviewed source unit: src/game/game_1844C0.c
 * Boundary evidence: docs/evidence/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15157010
 * - func_151571C4
 * - func_151572D0
 * - func_15157420
 * - func_15157918
 * - func_15157AA8
 * - func_15157DEC
 * - func_15157F80
 * - func_15157FE8
 * - func_15158078
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157010.s")
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
extern void func_1503F7B8(s32 arg0);
extern void func_15169804(s32 arg0);

void func_15157248(void *arg0) {
    func_151571C4(arg0);
    func_1518CA04(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503F7B8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169804((s32) arg0);
}
void func_1515728C(void *arg0) {
    func_151571C4(arg0);
    func_1518CA04(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503F7B8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169824((s32) arg0);
}
extern s32 D_800BE9E4;
extern s32 (*D_8008AD90[])(u8 *, u8 *, u8);
extern s32 (*D_8008ADA0[])(u8 *, u8 *, u8);
void func_1503F4B0(s32, u8 *, u8);
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151572D0 CURRENT (3363) */
void func_151572D0(u8 *arg0) {
    u8 stopped = 0;
    s8 index;
    s16 count;
    s32 product;

    if (*(u8 *)(arg0 + 0x10) & 1) {
        *(s16 *)(arg0 + 0x16) = *(s16 *)(arg0 + 0x16) - D_800BE9E4;
        if (*(s16 *)(arg0 + 0x16) < 0) {
            stopped = 1;
        }
    }
    if (stopped == 0) {
        index = *(s8 *)(arg0 + 0x11);
        if (index != -1 && D_8008AD90[index](arg0, arg0, stopped) == 0) {
            stopped = 1;
        }
        index = *(s8 *)(arg0 + 0x12);
        if (index != -1 && D_8008ADA0[index](arg0, arg0, stopped) == 0) {
            stopped = 1;
        }
    }
    if (stopped == 0) {
        func_1503F4B0(*(s32 *)(arg0 + 0x68), arg0, stopped);
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
void func_150A7BC0(s32 arg0, s32 arg1);

s32 func_15157860(s32 arg0) {
    func_150A7BC0((s32)((u8 *)arg0 + (D_800BE9C0 << 6) + 0x7C), arg0);
    return 1;
}
void func_15169260(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800A6060;
void func_10022EC0(void *, void *, s32);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157918 CURRENT (840) */
s32 func_15157918(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    u8 *temp_v1_7;
    u8 *temp_v1_8;
    u8 *temp_v1_9;

    func_150A8050(arg0 + (D_800BE9C0 << 6) + 0x7C, *(f32 *)((u8 *)arg0 + 0x120), *(s32 *)((u8 *)arg0 + 0x124), *(f32 *)((u8 *)arg0 + 0x128));
    temp_a0 = (void *)(arg0 + 0x120);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xAC) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB0) = (f32) *(f32 *)((u8 *)arg0 + 0x58);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB4) = (f32) *(f32 *)((u8 *)arg0 + 0x5C);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x7C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x7C) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_2 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_2 + 0x80) = (f32) (*(f32 *)((u8 *)temp_v1_2 + 0x80) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_3 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_3 + 0x84) = (f32) (*(f32 *)((u8 *)temp_v1_3 + 0x84) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_4 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_4 + 0x8C) = (f32) (*(f32 *)((u8 *)temp_v1_4 + 0x8C) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_5 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_5 + 0x90) = (f32) (*(f32 *)((u8 *)temp_v1_5 + 0x90) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_6 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_6 + 0x94) = (f32) (*(f32 *)((u8 *)temp_v1_6 + 0x94) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_7 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_7 + 0x9C) = (f32) (*(f32 *)((u8 *)temp_v1_7 + 0x9C) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_8 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_8 + 0xA0) = (f32) (*(f32 *)((u8 *)temp_v1_8 + 0xA0) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_9 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_9 + 0xA4) = (f32) (*(f32 *)((u8 *)temp_v1_9 + 0xA4) * *(f32 *)((u8 *)temp_a0 + 0xC));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15157918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157AA8.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15157D88(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x4C, arg0 + 0x50, arg0);
}
s32 func_15157DC8(s32 arg0) {
    func_15157DEC(arg0, arg0 + 0x120);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157DEC.s")
typedef struct Game1844C0DisplayCommand {
    u32 word0;
    void *word1;
} Game1844C0DisplayCommand;

typedef struct Game1844C0Matrix {
    u8 bytes[0x40];
} Game1844C0Matrix;

extern u8 D_80089470;
extern Game1844C0Matrix D_800DCC10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157F80 CURRENT (1235) */
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157FE8 CURRENT (1460) */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158078 CURRENT (260) */
void func_15158078(s32 arg0, u8 arg1) {
    func_15169260(&D_800A6060, 3, arg0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158078 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15158078.s")
