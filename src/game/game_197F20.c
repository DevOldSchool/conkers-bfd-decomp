#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_197F20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516AA70
 * - func_1516B6BC
 * - func_1516C934
 * - func_1516CC58
 * - func_1516D0CC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516AA70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516B6BC.s")
extern s32 D_800DD254;
extern s32 D_800DD258;

u8 *func_1516C878(void *arg0, s32 arg1, s16 arg2) {
    s32 count;
    u8 *cursor;
    s32 value;

    switch (arg2) {
    case 0:
        cursor = ((u8 *(*)[2])D_800DD254)[*(s32 *)((u8 *)arg0 + 4)][0];
        break;
    case 1:
        cursor = ((u8 *(*)[2])D_800DD258)[*(s32 *)((u8 *)arg0 + 4)][0];
        break;
    case 2:
        cursor = *(u8 **)((u8 *)arg0 + 4);
        break;
    }
    count = 0;
    if (arg1 > 0) {
        value = *cursor;
        do {
            count += 1;
            if (value != 0) {
                do {
                    value = cursor[1];
                    cursor += 1;
                } while (value != 0);
            }
            if (value == 0) {
                do {
                    value = cursor[1];
                    cursor += 1;
                } while (value == 0);
            }
        } while (count != arg1);
    }
    return cursor;
}
void *func_150417AC(void *, f32, f32, void *, s32, s32, s32, s32, f32, f32, s32);
void func_150428D4(void *, s32 *, s32 *, s32 *);
extern u8 D_800859A0[];
extern u8 D_800BE9C0;
extern u8 *D_800BE9C8[];
extern s32 D_800BEBA4;

typedef struct {
    u8 pad0[0x10];
    s32 *flags;
    u8 pad14[0x10];
    u8 *text;
    u8 pad28[8];
    f32 x, y;
    u8 pad38[0x18];
    f32 targetX, targetY;
} Game197F20Text;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516C934 CURRENT (4466) */
void *func_1516C934(u8 *arg0, Game197F20Text *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    u8 *original;
    u8 line[80];
    s32 width;
    s32 height;
    s32 spacing;
    f32 x;
    f32 y;
    f32 offset;
    s32 flags;
    s32 count;
    s32 index;
    s32 first;
    s32 full;
    u8 value;
    u8 *out;
    u8 *scan;
    u8 next;
    u8 ch;
    u8 last;

    index = 0;
    count = 0;
    original = arg0;
    x = arg1->targetX - arg1->x;
    y = arg1->targetY - arg1->y;
    out = arg0;
    arg0 += 8;
    *(s32 *)out = 0xDE000000;
    *(u8 **)(out + 4) = D_800859A0;
    first = 1;
    if (*arg1->text == 10) {
        scan = arg1->text + index;
        do {
            next = scan[1];
            index += 1;
            scan += 1;
        } while (next == 10);
    }
    do {
        full = (D_800BEBA4 < ((s32)(arg0 - D_800BE9C8[D_800BE9C0]) >> 3)) ? 1 : 0;
        if (full != 0) {
            return original;
        }
        ch = arg1->text[index];
        out = line + count;
        value = ch & 255;
        *out = ch;
        if (value == 10) {
            *out = 0;
            value = 0 & 255;
        }
        if (value == 0) {
            func_150428D4(line, &width, &height, &spacing);
            if (first == 0) {
                y += (f32)height;
            } else {
                first = 0;
            }
            flags = *arg1->flags;
            if (flags & 0x20000) {
                offset = (arg1->x - (f32)(width >> 1)) - 1.0f;
            } else {
                offset = 0.0f;
            }
            if (flags & 0x40000) {
                arg0 = func_150417AC(arg0, x + offset + 1.0f, y, line,
                                      255, 255, 255, arg5, 4096.0f, 4096.0f, count);
            } else if (!(flags & 4)) {
                arg0 = func_150417AC(arg0, x + offset + 1.0f, y, line,
                                      0, 0, 0, arg5, 4096.0f, 4096.0f, count);
            } else {
                arg0 = func_150417AC(arg0, x + offset, y, line,
                                      arg2, arg3, arg4, arg5, 4096.0f, 4096.0f, count);
            }
            count = 0;
            y += (f32)spacing;
        } else {
            count += 1;
        }
        last = arg1->text[index];
        index += 1;
    } while (last != 0);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516C934 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516C934.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516CC58.s")
f32 func_15047C00(f32);                             /* extern */
extern u16 D_80090562;
extern u16 D_80090582;
extern f32 D_800A6DE4;
extern f32 D_800A6DE8;
extern void *D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516D0CC CURRENT (3528) */
void func_1516D0CC(void *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    volatile f32 sp2C;
    volatile f32 sp28;
    volatile f32 sp24;
    volatile f32 sp20;
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft2;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv0_4;
    f32 var_ft0;
    f32 var_ft2;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;

    var_ft2 = (f32)(u32) D_80090562;
    var_ft2 = *(f32 *)((u8 *)arg0 + 0x38) / var_ft2;
    var_ft0 = (f32)(u32) D_80090582;
    sp1C = var_ft2 * var_ft0 * 0.25f * *(f32 *)((u8 *)arg0 + 0x28);
    temp_ft2 = func_15047C00(*(f32 *)((u8 *)arg0 + 0x58) + D_800A6DE4);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x38) * 0.5f;
    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x3C);
    temp_fa1 = *arg2;
    temp_ft2 *= temp_fv1;
    sp28 = temp_fa1;
    sp2C = temp_fa1 - temp_ft5;
    temp_fa0 = ((temp_ft2 * D_800A6DE8 * *(f32 *)((u8 *)arg0 + 0x28)) + *arg1) - sp1C;
    sp24 = temp_fa0 - temp_fv1;
    sp20 = temp_fv1 + temp_fa0;
    if (arg0 != 0) {
        top = sp2C;
        bottom = sp28;
        temp_fv0 = *(f32 *)((u8 *)D_800BE628 + 0x24);
        if (top < temp_fv0) {
            *arg2 = temp_fv0 + temp_ft5;
        } else {
            temp_fv0_2 = *(f32 *)((u8 *)D_800BE628 + 0x28);
            if (temp_fv0_2 < bottom) {
                *arg2 = temp_fv0_2;
            }
        }
        left = sp24;
        right = sp20;
        temp_fv0_3 = *(f32 *)((u8 *)D_800BE628 + 0x2C);
        if (left < temp_fv0_3) {
            *arg1 -= left - temp_fv0_3;
        } else {
            temp_fv0_4 = *(f32 *)((u8 *)D_800BE628 + 0x30);
            if (temp_fv0_4 < right) {
                *arg1 += temp_fv0_4 - right;
            }
        }
        *arg1 = (f32) (s32) *arg1;
        *arg2 = (f32) (s32) *arg2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516D0CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D0CC.s")
void func_1516D2D8(void) {

}

void func_1516D2E0(void *arg0) {
    if ((arg0 != 0) && (*(u8 *)((u8 *)arg0 + 0) == 0x51)) {
        *(s8 *)(*(u8 **)((u8 *)arg0 + 0x10) + 8) = 0;
        func_1516972C(arg0);
        *(s8 *)((u8 *)arg0 + 0x15) = 0;
    }
}
typedef struct {
    s32 field_0;
    u8 pad_4[4];
    u8 field_8;
} Game197F20Data;

typedef struct {
    u8 field_0;
    u8 pad_1[0xF];
    Game197F20Data *field_10;
    u8 pad_14[0xC];
    u8 field_20;
} Game197F20State;

void func_1516D328(Game197F20State *arg0) {
    if ((arg0 != 0) && (arg0->field_0 == 0x51)) {
        arg0->field_10->field_0 |= 0x100;
        arg0->field_10->field_0 &= ~0x400;
        arg0->field_20 = arg0->field_10->field_8;
    }
}
void *func_1516D378(void *arg0) {
    s32 *temp_v1;

    if ((arg0 != 0) && (*(u8 *)((u8 *)arg0 + 0) == 0x51)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x10);
        *temp_v1 |= 0x100;
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x10);
        *temp_v1 &= ~0x400;
        return arg0;
    }
    return 0;
}
void *func_1516D3C4(void *arg0) {
    s32 *temp_v1;

    if ((arg0 != 0) && (*(u8 *)((u8 *)arg0 + 0) == 0x51)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x10);
        *temp_v1 |= 0x500;
        return arg0;
    }
    return 0;
}
