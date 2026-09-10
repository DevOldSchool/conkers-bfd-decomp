#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A89B0.c
 * Boundary evidence: docs/evidence/game_raw_sorted_record_object_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517B500
 * - func_1517B6E8
 * - func_1517B89C
 * - func_1517BBAC
 * - func_1517CFC4
 * - func_1517D074
 * - func_1517D578
 * - func_1517D690
 * - func_1517D7B0
 * - func_1517DE5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s16 D_800DD470[];
extern void *D_800DBFF0;
extern u8 D_8008CEB0;
extern u8 D_80095CE1[];
extern u8 D_800DDD1C;
extern s32 D_8003809C;
extern s32 D_800DD478[];
extern s32 D_800DDA90;
extern s32 D_800DDD58;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 pad7;
    s16 unk8;
    s16 unkA;
    f32 unkC;
} Game1A89B0Record;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    u8 unk8;
    u8 pad9[4];
    s8 unkD;
} Game1A89B0Position;

extern Game1A89B0Record D_800DDD28[];

void func_10004074(s32);
void func_10006240(s32, s32, s32);
s32 func_151EF610();
s32 func_1517D074(s32, s16, s16, s16, f32, s32, s32, s32, s32, s32);
void func_1517D578(s16, s16, s16, f32, s32, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517B500 CURRENT (675) */
s32 func_1517B500(Game1A89B0Position *arg0, Game1A89B0Position *arg1, s32 *arg2, s16 arg3) {
    s32 sp24;
    s32 temp_t1;
    s32 temp_t8;
    s32 temp_v1;

    temp_t8 = (*arg2 * 3) / 2;
    *arg2 = temp_t8;
    temp_t1 = D_80095CE1[arg0->unk8 * 10] << 8;
    if (temp_t8 >= temp_t1) {
        *arg2 = temp_t8 - temp_t1;
    }
    arg1->unk0 = arg0->unk0;
    arg1->unk2 = arg0->unk2;
    arg1->unk4 = arg0->unk4;
    temp_v1 = 0x29 - arg0->unkD;
    if (temp_v1 == 0) {
        arg0->unkD = (arg0->unkD - (func_151EF610() % 8)) + 4;
    } else if (temp_v1 < 0) {
        sp24 = func_151EF610();
        arg0->unkD = ((arg0->unkD - ((func_151EF610() % -temp_v1) >> 1)) - (sp24 % 8)) + 4;
    } else {
        sp24 = func_151EF610();
        arg0->unkD = (arg0->unkD + ((func_151EF610() % temp_v1) >> 1) + (sp24 % 8)) - 4;
    }
    arg1->unk0 = arg0->unk0;
    arg1->unk2 = arg0->unk2;
    arg1->unk4 = arg0->unk4;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517B500 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B500.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517B6E8 CURRENT (40) */
s32 func_1517B6E8(void *arg0, void *arg1, s32 *arg2, u8 *arg3) {
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_v0;

    temp_v0 = *arg2;
    if (temp_v0 >= 0x600) {
        *(s16 *)((u8 *)arg1 + 2) = (s16) ((*(s16 *)((u8 *)arg0 + 2) + (temp_v0 >> 6)) - 0x18);
        *(s16 *)((u8 *)arg1 + 0) = (s16) ((*(s16 *)((u8 *)arg0 + 0) + ((s32) *arg2 >> 8)) - 6);
        temp_t0 = *arg3;
        temp_t1 = (s32) ((s32) (temp_t0 << 7) / (s32) (((s32) *arg2 >> 6) - 0x17)) >> 4;
        if (temp_t1 < (s32) temp_t0) {
            *arg3 = (u8) temp_t1;
        }
        *arg2 = 0x600;
    } else {
        *(s16 *)((u8 *)arg1 + 0) = (s16) *(s16 *)((u8 *)arg0 + 0);
        *(s16 *)((u8 *)arg1 + 2) = (s16) *(s16 *)((u8 *)arg0 + 2);
    }
    *(s16 *)((u8 *)arg1 + 4) = (s16) *(s16 *)((u8 *)arg0 + 4);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517B6E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B6E8.s")
s32 func_1517B7A8(void *arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = *arg2;
    if (temp_v0 >= 0x300) {
        if (temp_v0 >= 0x501) {
            *arg2 = temp_v0 - 0x200;
        } else {
            *arg2 = 0x300;
        }
    }
    *(s16 *)((u8 *)arg1 + 0) = (s16) *(s16 *)((u8 *)arg0 + 0);
    *(s16 *)((u8 *)arg1 + 2) = (s16) *(s16 *)((u8 *)arg0 + 2);
    *(s16 *)((u8 *)arg1 + 4) = (s16) *(s16 *)((u8 *)arg0 + 4);
    return 0;
}
s32 func_1517B7F8(void *arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 temp_v1;
    s32 temp_v0;

    temp_v0 = *arg2;
    if (temp_v0 >= 0xD00) {
        return 1;
    }
    temp_v1 = temp_v0 - 0x600;
    if (temp_v0 >= 0x100) {
        temp_v1 = 0x190000 - (temp_v1 * temp_v1);
        *(s16 *)((u8 *)arg1 + 2) = (s16) (*(s16 *)((u8 *)arg0 + 2) + (temp_v1 / 7680));
        temp_v0 = *arg2;
        if (temp_v0 >= 0x200) {
            if (temp_v0 >= 0xA01) {
                *arg2 = temp_v0 - 0x800;
            } else {
                *arg2 = 0x200;
            }
        }
    } else {
        *(s16 *)((u8 *)arg1 + 2) = (s16) *(s16 *)((u8 *)arg0 + 2);
    }
    *(s16 *)((u8 *)arg1 + 0) = (s16) *(s16 *)((u8 *)arg0 + 0);
    *(s16 *)((u8 *)arg1 + 4) = (s16) *(s16 *)((u8 *)arg0 + 4);
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B89C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517BBAC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517CFC4 CURRENT (105) */
void func_1517CFC4(void) {
    u8 *var_s0;
    s32 *var_s2;
    s32 temp_a0;
    s32 temp_a1;
    s32 var_s1;

    var_s2 = D_800DD478;
    var_s0 = (u8 *)&D_800DDA90;
    var_s1 = 0;
    do {
        temp_a0 = *(s32 *)(var_s0 + 8);
        if (temp_a0 != 0) {
            temp_a1 = var_s2[var_s1 * 0x1A];
            if (temp_a1 != 0) {
                func_10006240(temp_a0, temp_a1, D_8003809C);
                func_10004074(*(s32 *)(var_s0 + 8));
            }
            *(s32 *)(var_s0 + 8) = 0;
        }
        var_s1 += 1;
        var_s0 += 0x10;
    } while (var_s1 != 0xF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517CFC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517CFC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D074.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517D578 CURRENT (40) */
void func_1517D578(s16 arg0, s16 arg1, s16 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    Game1A89B0Record *temp_v1;
    s32 temp_v0;

    temp_v0 = D_8008CEB0;
    if (temp_v0 < 3) {
        temp_v1 = &D_800DDD28[temp_v0];
        temp_v1->unk0 = arg0;
        temp_v1->unk2 = arg1;
        temp_v1->unk4 = arg2;
        temp_v1->unkC = arg3;
        D_8008CEB0 = temp_v0 + 1;
        temp_v1->unk8 = arg4;
        temp_v1->unkA = arg5;
        temp_v1->unk6 = arg6;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517D578 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D578.s")
void func_1517D5FC(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_1517D578(
        arg0,
        arg1,
        arg2,
        *(f32 *)((u8 *)D_800DBFF0 + (arg3 * 0x9A0) + 0x380),
        arg4,
        arg5,
        D_800DDD1C >> 3);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517D690 CURRENT (669) */
s32 func_1517D690(s32 arg0, s32 arg1) {
    s32 sp4C;
    Game1A89B0Record *temp_v0_3;
    s32 temp_v0;
    s32 var_s2;
    u8 temp_t0;
    u8 temp_t8;
    u8 temp_v0_2;

    var_s2 = arg0;
    sp4C = D_800DDD58;
    temp_t8 = D_800DDD1C + 5;
    temp_v0 = temp_t8 & 0xFF;
    D_800DDD1C = temp_t8;
    if (temp_v0 >= 0xC8) {
        D_800DDD1C = temp_v0 - 0xC8;
    }
    temp_v0_2 = D_8008CEB0;
    if (temp_v0_2 != 0) {
        do {
            temp_t0 = temp_v0_2 - 1;
            D_8008CEB0 = temp_t0;
            if (arg1 != 0) {
                temp_v0_3 = &D_800DDD28[temp_t0 & 0xFF];
                var_s2 = func_1517D074(var_s2, temp_v0_3->unk0, temp_v0_3->unk2, temp_v0_3->unk4,
                                       temp_v0_3->unkC, (u16)temp_v0_3->unk8, (u16)temp_v0_3->unkA,
                                       0x10, 0x20, ((temp_v0_3->unk6 * 0x280) << 1) + arg1);
            }
            temp_v0_2 = D_8008CEB0;
        } while (temp_v0_2 != 0);
    }
    D_800DDD58 = sp4C;
    return var_s2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517D690 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D7B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517DE5C.s")
void func_1517E05C(s32 arg0, s32 arg1, s32 arg2) {
    D_800DD470[0] = arg0;
    D_800DD470[1] = arg1;
    D_800DD470[2] = arg2;
}
