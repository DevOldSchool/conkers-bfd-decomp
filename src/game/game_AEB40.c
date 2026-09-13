#include "types.h"

/*
 * Reviewed source unit: src/game/game_AEB40.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15081690
 * - func_15081C20
 * - func_15081E0C
 * - func_15081E78
 * - func_150825C0
 * - func_1508295C
 * - func_150829D8
 * - func_15082A44
 * - func_150832AC
 * - func_15083384
 * - func_15083568
 * - func_150836CC
 * - func_150837D4
 * - func_150838EC
 * - func_150839B8
 * - func_15083AC8
 * - func_15083DA0
 * - func_15083E0C
 * - func_15083E90
 * - func_15083FB0
 * - func_15084044
 * - func_1508434C
 * - func_150843AC
 * - func_15084488
 * - func_15084558
 * - func_150849A0
 * - func_150849CC
 * - func_15084A18
 * - func_15084C30
 * - func_15084CB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameAEB40State {
    u8 pad0[0x1C9];
    u8 field_1C9;
    u8 pad1CA[0xFA];
    u8 *field_2C4;
    u8 field_2C8;
    u8 field_2C9;
} GameAEB40State;

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081C20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081E78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150825C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_1508295C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150829D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15082A44.s")
s32 func_1515D440();                                /* extern */
s32 func_1515D480(u8);                              /* extern */
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150832AC CURRENT (830) */
void func_150832AC(u8 *arg0) {
    s32 var_s1;
    u8 temp_a0;
    u8 var_s3;
    u8 *var_s0;

    temp_v1 = (void *)(*(void **)((u8 *)arg0 + 0x144));
    if (temp_v1 != 0) {
        temp_a0 = *(u8 *)((u8 *)temp_v1 + 0x2F);
        var_s0 = arg0;
        var_s3 = temp_a0;
        if (temp_a0 == 0) {
            if (*(u8 *)((u8 *)arg0 + 0x127) == 0) {
                var_s3 = 5;
            } else {
                var_s3 = 3;
            }
        }
        var_s1 = 0;
        if (D_80082FA0 >= 0) {
            do {
                *(s32 *)((u8 *)var_s0 + 0x304) = func_1515D480(var_s3);
                var_s1 += 1;
                var_s0 += 4;
            } while (D_80082FA0 >= var_s1);
        }
        if (*(s32 *)((u8 *)(arg0 + (var_s1 * 4)) + 0x300) != 0) {
            *(u8 *)((u8 *)arg0 + 0x301) = var_s3;
        }
        *(s32 *)((u8 *)arg0 + 0x314) = func_1515D440();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150832AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150832AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083384.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150836CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150837D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150838EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150839B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083AC8.s")
extern s32 D_800D20FC;
extern u8 D_800D2100;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15083DA0 CURRENT (10) */
s32 func_15083DA0(void) {
    s32 var_v0;
    s32 var_v1;
    s32 temp_v1;

    var_v1 = 1;
    var_v0 = 0;
    if ((s32) D_800D2100 > 0) {
        do {
            if (var_v1 == *(u8 *)((u8 *)(D_800D20FC + (var_v0 * 0x30)) + 0x28)) {
                var_v1 += 1;
                var_v0 = 0;
            }
            var_v0 += 1;
        } while (var_v0 < (s32) D_800D2100);
    }
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15083DA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083DA0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15083E0C CURRENT (410) */
s32 func_15083E0C(s32 arg0) {
    s32 temp_t6;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return -1;
    }
    var_v1 = 0;
    if ((s32) D_800D2100 > 0) {
        var_a2 = 0;
        var_a3 = D_800D20FC;
loop_4:
        var_v1 += 1;
        var_a3 += 0x30;
        if (temp_t6 == *(u8 *)((u8 *)var_a3 + 0x28)) {
            return (s32) ((var_a2 + D_800D20FC) - D_800D20FC) / 48;
        }
        var_a2 += 0x30;
        if (var_v1 >= (s32) D_800D2100) {
            /* Duplicate return node #7. Try simplifying control flow for better match */
            return -1;
        }
        goto loop_4;
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15083E0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083E0C.s")
extern s32 D_800CC2D0;
extern u8 D_800CC30B;
extern s32 D_800CC5FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15083E90 CURRENT (410) */
s32 *func_15083E90(s32 arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *var_v1;
    s32 temp_t6;
    s32 var_a0;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return 0;
    }
    if ((D_800CC2D0 != 0) && (temp_t6 == D_800CC30B)) {
        return &D_800CC2D0;
    }
    var_a0 = 2;
    if ((*(s32 *)((u8 *)&D_800CC5FC + 0) != 0) && (temp_t6 == *(u8 *)((u8 *)&D_800CC5FC + 0x3B))) {
        return &D_800CC5FC;
    }
    var_v1 = &D_800CC5FC + 0x32C;
loop_9:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (temp_t6 == *(u8 *)((u8 *)var_v1 + 0x3B))) {
        return var_v1;
    }
    temp_v1_3 = var_v1 + 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0x32C) != 0) && (temp_t6 == *(u8 *)((u8 *)temp_v1_3 + 0x3B))) {
        return temp_v1_3;
    }
    temp_v1_2 = temp_v1_3 + 0x32C;
    if ((*(s32 *)((u8 *)temp_v1_3 + 0x32C) != 0) && (temp_t6 == *(u8 *)((u8 *)temp_v1_2 + 0x3B))) {
        return temp_v1_2;
    }
    temp_v1 = temp_v1_2 + 0x32C;
    var_a0 += 4;
    if ((*(s32 *)((u8 *)temp_v1_2 + 0x32C) != 0) && (temp_t6 == *(u8 *)((u8 *)temp_v1 + 0x3B))) {
        return temp_v1;
    }
    var_v1 = temp_v1 + 0x32C;
    if (var_a0 == 0x1A) {
        return 0;
    }
    goto loop_9;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15083E90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083E90.s")
/* Call context: func_15083E90: unique active project prototype */
void *func_15083E90(u8 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15083FB0 CURRENT (474) */
s32 func_15083FB0(s32 arg0) {
    s32 temp_a0;
    void *temp_v0;

    temp_a0 = arg0;
    temp_a0 &= 0xFF;
    temp_v0 = func_15083E90(temp_a0);
    if (temp_v0 != 0) {
        return (s32) ((u8 *)temp_v0 - (u8 *)&D_800CC2D0) / 0x32C;
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15083FB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083FB0.s")
extern s32 *func_1505EEF4(s32 arg0);

s32 func_15084000(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = func_1505EEF4(arg0);
    if (temp_v0 != 0) {
        return (s32) ((u8 *) temp_v0 - (u8 *) &D_800CC2D0) / 0x32C;
    }
    return -1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084044.s")
void func_150843AC(GameAEB40State *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508434C CURRENT (100) */
void func_1508434C(GameAEB40State *arg0) {
    s32 index;
    s32 count;

    count = arg0->field_2C9;
    if (count == 0) {
        count = 1;
    }
    index = 0;
    if (count > 0) {
        do {
            func_150843AC(arg0, index);
            index += 1;
        } while (index != count);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508434C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_1508434C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150843AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084488.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084558.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150849A0 CURRENT (15) */
u8 func_150849A0(void *arg0) {
    u8 temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x1C9);
    if (temp_v0 != 0) {
        temp_v1 = *(u8 **)((u8 *)arg0 + 0x2C4);
        temp_v1_2 = *(u8 **)((u8 *)arg0 + 0x2C4);
        return *(temp_v1_2 + temp_v0 - 1);
    }
    temp_v1 = *(u8 **)((u8 *)arg0 + 0x2C4);
    return *temp_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150849A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150849A0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150849CC CURRENT (235) */
u8 func_150849CC(void *arg0, s32 *arg1) {
    s32 var_v1;
    s32 temp_v1;
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x1C9);
    if (temp_v0 != 0) {
        var_v1 = temp_v0 - 1;
    } else {
        temp_v0_2 = *(u8 *)((u8 *)arg0 + 0x2C8);
        var_v1 = 0;
        if (temp_v0_2 != 0) {
            var_v1 = temp_v0_2 - 1;
        }
    }
    if (arg1 != 0) {
        temp_v1 = var_v1;
        *arg1 = temp_v1;
    } else {
        temp_v1 = var_v1;
    }
    return *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x2C4) + temp_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150849CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150849CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084A18.s")
u32 func_150ADA20();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15084C30 CURRENT (1080) */
void func_15084C30(void *arg0) {
    void *sp1C;
    u32 temp_hi;
    void *temp_v1;

    if (*(u8 *)((u8 *)arg0 + 4) == 0x94) {
        temp_v1 = *(void **)((u8 *)arg0 + 0x2D0);
        sp1C = temp_v1;
        temp_hi = func_150ADA20() % (u32) (s32) *(f32 *)((u8 *)temp_v1 + 0x18);
        {
            f32 var_fv0 = (f32) temp_hi;
        if ((s32) temp_hi < 0) {
            var_fv0 += 4294967296.0f;
        }
        *(f32 *)((u8 *)temp_v1 + 8) = var_fv0;
    }
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15084C30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084C30.s")
extern u8 D_800BE590;
extern u16 D_800BE598;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15084CB0 CURRENT (140) */
s32 func_15084CB0(s32 arg0) {
    s32 var_v0;
    s32 var_v1;
    u16 *var_a2;

    var_v1 = 0;
    var_v0 = 0;
    if ((s32) D_800BE590 > 0) {
        var_a2 = &D_800BE598;
loop_2:
        if (arg0 == *var_a2) {
            var_v1 = var_v0;
        } else {
            var_v0 += 1;
            var_a2 += 2;
            if (var_v0 < (s32) D_800BE590) {
                goto loop_2;
            }
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15084CB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084CB0.s")
