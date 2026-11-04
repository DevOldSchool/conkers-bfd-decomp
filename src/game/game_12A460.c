#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_12A460.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FCFD4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150FCFB0(s32 arg0) {
    func_15103828();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12A460/func_150FCFD4.s")
typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 *unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 unk34[0x24];
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
} Sub150FD514;

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_15047D60(f32);
f32 func_150AD78C(f32);
void func_150E7FEC(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E83AC(void *, s16, u8, s32);
void func_15107B78(void *, s16, s16, u8, s32);
f32 func_15144B68(f32);
void func_151D5334(void *, f32, f32, f32, u8, u8, s32);
void func_1505D024(void *, s32, s32, s32);
f32 func_150ADA68();
extern f32 D_800A1F40;
extern f32 D_800A1F44;
extern f32 D_800A1F48;
extern f32 D_800A1F4C;
extern f32 D_800A1F50;
extern f32 D_800A1F54;
extern f32 D_800A1F58;
extern f32 D_800A1F5C;
extern f32 D_800A1F60;
extern f32 D_800A1F64;
extern f32 D_800A1F68;
extern f32 D_800BE9A4;

s32 func_150FD514(u8 *arg0) {
    u8 *obj;
    Sub150FD514 *sub;
    f32 z;
    f32 x;
    f32 pos[3];

    obj = *(u8 **)(arg0 + 0x110);
    if (obj != NULL) {
        sub = (Sub150FD514 *)(arg0 + 0x110);
        if (*(s32 *)obj == 0 || sub->unk4 != obj[0x3B]) {
            sub->unk0 = NULL;
            obj = NULL;
        }
        x = *(f32 *)(obj + 0x14);
        z = *(f32 *)(obj + 0x1C);
    } else {
        sub = (Sub150FD514 *)(arg0 + 0x110);
        x = *(f32 *)(arg0 + 0x34);
        z = *(f32 *)(arg0 + 0x3C);
    }
    if (obj != NULL) {
        func_1502EA98(obj, 0xFF, 0, 0, 0xFF, 0, 4);
        sub->unk2C += (D_800A1F40 + func_150ADA68() * D_800A1F44) * D_800BE9A4;
        while (sub->unk2C > 1.0f) {
            func_15107B78(obj, func_150ADA20() & 0xFF, func_150ADA20() % 101 - 0x3F, arg0[0xC], arg0[1]);
            sub->unk2C -= 1.0f;
        }
    }
    if (sub->unkC > 20.0f) {
        *(f32 *)(arg0 + 0x2C) = (50.0f - sub->unkC) * D_800A1F48 * sub->unk8;
    } else if (sub->unkC > 10.0f) {
        *(f32 *)(arg0 + 0x2C) = sub->unk8;
    } else {
        *(f32 *)(arg0 + 0x2C) = sub->unkC * D_800A1F4C * sub->unk8;
        if (sub->unk58 == 0) {
            if (obj != NULL) {
                func_1505D024(obj, 0x16, *(u16 *)(obj + 0x7A), -1);
                func_10010F88(0x69D, 0x7D00, 0, 0, 0, *(f32 *)(arg0 + 0x34), *(f32 *)(arg0 + 0x38), *(f32 *)(arg0 + 0x3C), 500, 3000);
            }
            sub->unk58 = 1;
            func_151D5404(arg0 + 0x34, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14, arg0[0xC], arg0[1]);
            func_151D5334(arg0 + 0x34, 506.0f, 1013.0f, 0.0009871669f, 5, arg0[0xC], arg0[1]);
            if (sub->unk59 & 1) {
                pos[0] = *(f32 *)(arg0 + 0x34);
                pos[1] = sub->unk30;
                pos[2] = *(f32 *)(arg0 + 0x3C);
                func_150E7FEC(func_150ADA68() * 78.0f + 125.0f, (func_150ADA20() % 76 + 0xB4) & 0xFF, sub->unk34, pos, func_150ADA20() % 207 + 0x12E, 0, 1, 0, 0, 0, arg0[0xC], 0);
                func_150E83AC(pos, func_150ADA20() % 80 + 0xF3, arg0[0xC], arg0[1]);
            }
        }
    }
    arg0[0x5C] = func_15047D60(sub->unk10) * 57.0f + 198.0f;
    sub->unk10 += D_800A1F50 * D_800BE9A4;
    sub->unk10 = func_15144B68(sub->unk10);
    sub->unk1C += D_800A1F54 * D_800BE9A4;
    sub->unk20 += D_800A1F58 * D_800BE9A4;
    sub->unk1C = func_15144B68(sub->unk1C);
    sub->unk20 = func_15144B68(sub->unk20);
    sub->unk14 = func_150AD78C(sub->unk1C) * D_800A1F5C + D_800A1F60;
    sub->unk18 = func_150AD78C(sub->unk20) * 1192.0f + D_800A1F64;
    if (sub->unk28 != NULL) {
        *(f32 *)(sub->unk28 + 0x2C) = *(f32 *)(sub->unk28 + 0x30) = *(f32 *)(arg0 + 0x2C) * D_800A1F68;
        sub->unk28[0x5C] = arg0[0x5C];
        *(f32 *)(sub->unk28 + 0x34) = x;
        *(f32 *)(sub->unk28 + 0x3C) = z;
    }
    *(f32 *)(arg0 + 0x34) = x;
    *(f32 *)(arg0 + 0x3C) = z;
    sub->unkC -= D_800BE9A4;
    if (sub->unkC < 0.0f) {
        return 0;
    }
    return 1;
}
void func_150FDB0C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x110;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)(arg1 + 8);
        }
    } else if (arg2 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) || (temp_v0[4] == arg1[4])) {
            *(s32 *)temp_v0 = 0;
        }
    }
}
