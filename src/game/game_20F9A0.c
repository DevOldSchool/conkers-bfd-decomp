#include "types.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_20F9A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_extended_code_selected_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151E2834
 * - func_151E3344
 * - func_151E43DC
 * - func_151E50C8
 * - func_151E565C
 * - func_151E5FF4
 * - func_151E6C1C
 * - func_151E81EC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void *D_8008FDD4;
extern s8 D_80087270;

s32 func_151E24F0(s32 *arg0) {
    s32 count;
    s32 i;
    s32 old;
    s32 slot;
    s8 used[4];
    s8 allowed[4];
    u8 mask;
    s16 available;

    if (arg0 == NULL) {
        D_800E0BCE[0] = 0;
        D_800E0BCE[1] = 0;
    }
    if (D_800AB694[*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10] == 8) {
        mask = 0;
        count = 0;
        if (D_800E0BEE != 0) {
            for (i = 0; i < 4; i++) {
                used[i] = 0;
            }
            for (i = 0; i < 4; i++) {
                if (D_8008FE44[i] >= 0) {
                    count++;
                    used[D_8008FE44[i]] = 1;
                    mask |= 1 << D_8008FE44[i];
                }
            }
            available = D_800BE740;
            mask = available & ~mask;
            if (count < 3 && mask != 0) {
                for (i = 0; i < 4; i++) {
                    allowed[i] = 1;
                    if (count == 1 && !(available & (1 << i))) {
                        allowed[i] = 0;
                    }
                }
                slot = 0;
                if (arg0 == NULL) {
                    for (slot = 16; slot >= count * 2; slot--) {
                        D_8008FE44[slot] = D_8008FE44[slot - count];
                        D_800E0C00[slot] = D_800E0C00[slot - count];
                    }
                    slot = count;
                    for (i = 0; i < 4 && slot < count * 2; i++) {
                        if (used[i] == 0 && allowed[i] != 0) {
                            old = slot - count;
                            D_8008FE44[slot] = i;
                            D_800E0C00[slot] = D_800E0C00[old];
                            D_800E0BCE[old] = slot;
                            (&D_80087270)[slot] = 10;
                            slot++;
                        }
                    }
                } else {
                    for (i = 0; i < 4 && slot < count; i++) {
                        if (used[i] == 0 && allowed[i] != 0) {
                            arg0[slot] = i;
                            slot++;
                        }
                    }
                }
                return count;
            }
        }
    }
    return 0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E2834.s")
void func_15017790(void);
void func_1509CC94();
void func_1509CDDC(s32);
s32 func_1509CF28(s32, s32 *);
void func_1509D054(void);
u16 func_1509CA30(s32);
s32 func_1509CA50(s32);
void func_15085710(s16, s32, s32);
void func_151E7EF8(void);
void func_1501C730(s32, s32, s32, s32, s32);
extern s8 D_80087270;
extern u8 D_800DD2C0;
extern s32 D_800E9D00;

void func_151E30C4(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;

    sp24 = 0;
    if (D_8008FDB4 != 0) {
        sp28 = D_8008FDAC;
    } else {
        func_1509CF28(D_8008FF00, &sp2C);
        func_1509D08C(D_8008FF00, D_8008FF04, &sp28, &sp24);
        func_1509D054();
    }
    func_15017790();
    func_1509CC94(sp28);
    func_1509CDDC(sp28);
    D_800BE9F4 = func_1509CA30(sp28);
    func_15085710(0, 9, sp24);
    D_800BE3E4 = sp24;
    D_800DD2C0 = func_1509CA50(sp28);
    if (D_8008FDB4 == 2) {
        D_800DD2C0 = D_800E0BD1;
    }
    D_8008FD70 = 0;
    D_800D23A8 = 0;
    D_8008FDBC = 0;
    D_8008FDA8 = -1;
    D_800E0B94 = 0;
    *(u8 *)&D_800E0B99 = 1;
    D_8008FD8C = 1;
    D_8008FD90 = 1;
    D_8008FD94 = 1;
    D_800BE618 = 1;
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    D_80087270 = 0;
    D_800D18A8 = 0;
    D_800E0BB1 = 1;
    func_151E7EF8();
    *(u8 *)&D_800D2E40 = 1;
    func_1501C730(6, D_800BE9F4, func_1509CA50(sp28), 0, 1);
}
/* Call context: func_1501C730: unique active declaration in the allowed source */
void func_1501C730(s32, s32, s32, s32, s32);
extern s8 D_80087270;
extern s32 D_800E9D00;
extern void func_151E2834(void);
extern s32 func_151F2CDC(void);
extern void func_151F2D6C(s32 arg0, s32 arg1);
extern void func_151E530C(void);
extern u8 D_800C35EA;

void func_151E327C(void) {
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    D_80087270 = 0;
    D_8008FD8C = 1;
    D_8008FD90 = 1;
    D_8008FD94 = 1;
    D_8008FDBC = 0;
    D_800BE618 = 1;
    D_800D23A8 = 0;
    D_800E0B94 = 0;
    D_800D2E40 = 0;
    func_1501C730(6, (s32) D_800BE3DF, (s32) D_800BE3E0, 0, 1);
    *(u8 *)&D_800E0B99 = 1;
    D_800E0BB1 = 1;
    func_151E7EF8();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E3344.s")
void func_151E4264(void) {
    if (D_8008FD80 != 0) {
        D_8008FD80 = 0;
        return;
    }
    func_151E530C();
    if ((D_800E0B9A != 0) || (D_800C35EA != 1)) {
        if ((D_800C35EA == 1) && (func_151F2CDC() == 1)) {
            func_151F2D6C(0, 0x2DE0);
        }
        D_800E0B94 = 7;
        D_800E0A88 = func_151E2834;
        D_8008FD74 = 8;
    }
}
typedef struct {
    s16 value;
    s8 alternate;
    s8 selected;
} Game20F9A0Selection;

void func_1501D348(s32, s32, s32, u8, s32);
extern void *D_8008FDD4;
extern Game20F9A0Selection D_800AB7A4[];

void func_151E4314(void) {
    Game20F9A0Selection *entry;
    s8 index;
    s8 choice;

    index = D_800AB692[*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10];
    if (index >= 0) {
        entry = &D_800AB7A4[index];
        if (D_800E0C00[0] != 0) {
            choice = entry->selected;
        } else {
            choice = entry->alternate;
        }
        func_1501D348(entry->value, choice, 0, 0, 0);
        D_8008FD80 = 1;
        D_800E0B94 = 5;
        D_8008FD8C = 1;
        D_8008FD90 = 1;
    } else {
        func_151E2834();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E43DC.s")
void func_151E557C(void);
extern Game20F9A0Selection D_800AB7BC[];

void func_151E4BD8(void) {
    s16 selection;
    s8 alternate;
    s8 count;
    s32 i;

    D_8008FE2C = 0;
    D_800BEAC1 = 0;
    D_8008FDA4 = 0;
    D_800E0A90 = 0;
    count = 0;
    alternate = D_800AB68C[*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10 + 7];
    D_8008FDC0 &= 0xF369;
    if (D_800AB68C[*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10 + 5] >= 0) {
        for (i = 0; i < 4; i++) {
            if (D_800E0AC0[i] == 1) count++;
        }
        count = count >= 2;
    }
    if (alternate < 0 || count != 0) {
        if (alternate == -2 && D_800E0A86 == 0) {
            D_800E0B94 = 6;
            D_8008FD80 = 2;
            D_8008FDC0 = 0;
            return;
        }
        selection = 0x1D;
        if (count == 0) {
            D_800E0B94 = 3;
        } else {
            D_800E0B94 = 6;
            D_8008FD80 = 4;
        }
    } else {
        selection = D_800AB7BC[alternate].value;
        D_800E0B94 = 6;
        D_8008FD80 = 1;
    }
    D_800D2E40 = 0;
    func_1501C730(6, selection, 0, 0, 1);
    func_151E557C();
    D_8008FD8C = 1;
    D_8008FD90 = 1;
}

void func_151E4DC4(void) {
    D_800E0B94 = 0xA;
}

void func_151E4DD8(void) {
    if (D_800E0B9A & 0x8020) {
        D_800E0B94 = 4;
    }
}
void func_151E557C(void);
void func_1501C730(s32, s32, s32, s32, s32);

void func_151E4E00(void) {
    D_8008FDCC = 0;
    func_151E557C();
    D_800E0B94 = 3;
    D_8008FDA4 = 0;
    D_8008FD80 = 0;
    D_800D2E40 = 0;
    func_1501C730(6, 0x1D, 0, 0, 1);
}
void func_151E55A8(void);

void func_151E4E64(void) {
    func_151E530C();
    func_151E55A8();
    if (D_800E0A90 >= 0x4B1) {
        D_800E0B9A |= 0x8000;
    }
    if (D_800E0B9A != 0) {
        D_800E0B94 = 7;
        D_800E0A88 = func_151E4E00;
        D_8008FD74 = 8;
    }
}
extern f32 D_800DDDC8;
extern f32 D_800DDDD8;

void func_151E4EE8(void) {
    s32 alpha;

    D_8008FDD0 = 1.0f - (f32)(u32)D_800E0B96 / 255.0f;
    if (D_8008FD74 == 0xFF) {
        if (D_800ABA2C < D_800DDDC8) {
            D_800E0B96 += D_800BE9E4;
            if (D_800E0B96 < 0x55) {
                D_800DDDD8 = D_800ABA30;
            } else {
                D_800DDDD8 = D_800ABA34;
            }
        }
        if (D_800DDDC8 < 1.0f) {
            return;
        }
        if (D_800E0B96 < 0x6E) {
            return;
        }
    } else if (D_800E0B96 != 0xFF) {
        alpha = D_800E0B96 + D_800BE9E4 * D_8008FD74;
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        D_800E0B96 = alpha;
        return;
    }
    D_800E0B96 = 0xFF;
    D_8008FD74 = 8;
    D_8008FDD0 = 1.0f;
    D_800E0A88();
}
extern void *D_8008FDD4;

void func_151E5034(void) {
    *(f32 *)((u8 *)D_8008FDD4 + 0) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 4) = 0.0f;
    *(s8 *)((u8 *)D_8008FDD4 + 0x2B) = 0;
    *(s16 *)((u8 *)D_8008FDD4 + 0x20) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x3E) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x41) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x43) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x44) = 0;
    *(f32 *)((u8 *)D_8008FDD4 + 0x10) = 0.0f;
    *(s8 *)((u8 *)D_8008FDD4 + 0x2A) = 0;
    *(f32 *)((u8 *)D_8008FDD4 + 0x14) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 0x18) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 0xC) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 8) = 0.0f;
}
void func_15017790(void);
void func_151E6BFC(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E50C8 CURRENT (730) */
void func_151E50C8(void) {
    s8 *var_v0;
    u32 end;
    s8 *var_v1;
    s8 temp_t0;
    s8 temp_t1;
    s8 temp_t2;
    s8 temp_t9;

    var_v0 = D_8008FE57;
    var_v1 = D_800E0BE3;
    temp_t9 = D_8008FE54;
    temp_t0 = D_8008FE55;
    temp_t1 = D_8008FE56;
    D_800E0BE2 = temp_t1;
    *(s8 *)((u32)&D_800E0BE2 - 1) = temp_t0;
    *(s8 *)((u32)&D_800E0BE2 - 2) = temp_t9;
    end = (u32)D_8008FE6B;
copy_bytes:
    {
        temp_t9 = *((s8 *)var_v0 + 0);
        temp_t0 = *((s8 *)var_v0 + 1);
        temp_t1 = *((s8 *)var_v0 + 2);
        temp_t2 = *((s8 *)var_v0 + 3);
        var_v0 += 4;
        var_v1 += 4;
        *((s8 *)var_v1 - 4) = temp_t9;
        *((s8 *)var_v1 - 3) = temp_t0;
        *((s8 *)var_v1 - 2) = temp_t1;
        *((s8 *)var_v1 - 1) = temp_t2;
    }
    if ((u32)var_v0 != end) {
        goto copy_bytes;
    }
    D_800E0A90 = 0;
    func_151E6BFC();
    if (D_8008FDD4 == 0) {
        D_8008FDD4 = D_800E0AF0;
        func_151E5034();
        if (*(s8 *)((u8 *)D_8008FDD4 + 0x3E) == 1) {
            s8 index = *(s8 *)((u8 *)D_8008FDD4 + 0x2C);
            *(s8 *)((u8 *)D_8008FDD4 + 0x2C) = D_800AB570[index];
        }
    }
    func_15017790();
    D_800E0B94 = 0xB;
    D_800D2E40 = 0;
    func_1501C730(6, 0x25, 0, 0, 1);
    D_800E0B95 = D_800E0B94;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E50C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E50C8.s")
void func_15042D78(u8);
void func_151E6964(s32);

void func_151E51EC(void) {
    u8 sp1F;

    sp1F = D_800E0B94;
    D_8003C8E0 = 0x08000000;
    D_800E0BDC = 0xFF;
    func_15042D78(0x81);
    D_800E0B9A = D_800BE930;
    if (D_8008FE28 != 0) {
        D_8008FE28 -= 1;
        D_800E0B9A = 0;
    }
    if ((u8)D_800E0B94 == 0) {
        func_151E6964(2);
    } else if ((u8)D_800E0B94 == 8) {
        func_151E6964(4);
    } else {
        func_151E6964(1);
    }
    D_8008FDEC[(u8)D_800E0B94]();
    if ((u8)D_800E0B94 != 7) {
        D_800E0A90 += D_800BE9E4;
        if (D_800E0B94 != sp1F) {
            D_800E0B95 = sp1F;
            D_800E0A90 = 0;
        }
    }
    D_8003C8E0 = 0;
}

void func_151E530C(void) {
    f32 temp_fv0;
    s32 var_v1;

    if ((u8) D_800E0B94 != 2) {
        if (D_800E0B96 != 0) {
            var_v1 = D_800E0B96 - (D_800BE9E4 * D_8008FD74);
            if (var_v1 < 0) {
                var_v1 = 0;
            }
            D_800E0B96 = (u8) var_v1;
        }
        if ((D_8008FDD4 != 0) && (*(s8 *)((u8 *)D_8008FDD4 + 0x2B) == 0) && (*(f32 *)((u8 *)D_8008FDD4 + 0xC) > 0.0f)) {
            temp_fv0 = *(f32 *)((u8 *)D_8008FDD4 + 8);
            if (temp_fv0 > 0.5f) {
                var_v1 = (s32) ((temp_fv0 - 0.5f) * 524.0f);
                if (var_v1 >= 0x100) {
                    var_v1 = 0xFF;
                }
                D_800E0B96 = (u8) var_v1;
            }
        }
    }
}
void func_151DDBA0(void);
void func_151E4BD8(void);
extern u8 D_800CC2D0[];

void func_151E53E8(s32 arg0) {
    s32 i;

    D_800E0A90 = 0;
    D_8008FE2C = 0;
    D_80087270 = 0;
    if (D_800BE616 != 0) {
        D_800E0B94 = 7;
        D_8008FD74 = 8;
        if (D_800AB68C[(*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10) + 7] != -1) {
            *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 4;
            D_800E0A88 = func_151E4BD8;
        } else {
            *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 3;
            D_800E0A88 = func_151DDBA0;
        }
        for (i = 0; i < D_8008FD90; i++) {
            *(s16 *)((u8 *)D_8008FDD4 + i * 0xC + 0x6C) = *(s16 *)(*(u8 **)(D_800CC2D0 + i * 0x32C + 0x31C) + 0x1AA);
        }
        D_8008FDC0 &= 0xE35F;
        D_800E0A86 = arg0;
        if (D_800AB68C[(*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10) + 7] == -2) {
            if (arg0 == 0) {
                func_151E4BD8();
                return;
            }
            D_800E0A88 = func_151DDBA0;
            *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 3;
        }
    } else {
        D_800E0B94 = 4;
    }
}
extern u8 D_80084060[4];

void func_151E557C(void) {
    D_80084060[0] = 0;
    D_80084060[1] = 1;
    D_80084060[2] = 2;
    D_80084060[3] = 3;
}

void func_151E55A8(void) {
    s32 value;
    s32 step;

    if (D_800E0B98 == 0) {
        step = D_800BE9E4 * 8;
    } else {
        step = -D_800BE9E4 * 8;
    }
    value = D_800E0B97;
    value += step;
    if (value >= 0x100) {
        value = 0x1FE - value;
        D_800E0B98 ^= 1;
    } else if (value < 0) {
        value = -value;
        D_800E0B98 ^= 1;
    }
    D_800E0B97 = (u8)value;
}

void func_151E562C(void) {
    if (D_800E0A8C != 0) {
        D_800E0A8C = 0;
    }
}

s8 func_151E564C(void) {
    return D_8008FDC8;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E565C.s")

s32 func_151E5F64(s32 arg0) {
    s8 var_v1;

    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        var_v1 = D_800E0C00[(s32)arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}

s8 func_151E5FAC(void) {
    if (D_800E0BEB != 0) {
        if (D_8008FD8C >= 5) {
            return D_8008FD90;
        }
        return D_8008FD8C;
    }
    return D_8008FD90;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E5FF4.s")
void *func_10003C40(s32, s32, s32, s32);
void func_10004074(s32);
s32 func_1502B5C8(u32 *, s32, ...);
extern u8 **D_800E0BD8;

void func_151E6964(s32 kind) {
    u8 *cursor;
    u8 *end;
    s32 i;
    u32 length;

    if (D_800E0BEA != D_800BEAAB) {
        D_800BEAAB = D_800E0BEA;
        D_800E0BD3 = 0;
    }
    if (kind == D_800E0BD3) {
        return;
    }
    if (D_800E0BD4 != NULL) {
        func_10004074((s32)D_800E0BD4);
        D_800E0BD4 = NULL;
        if (D_8008FDD8 != NULL) {
            func_10004074((s32)D_8008FDD8);
            func_10004074((s32)D_800E0B88);
            func_10004074((s32)D_800E0BD8);
            D_8008FDD8 = NULL;
        }
    }
    D_800E0BD3 = kind;
    if (D_800E0BD3 != 0) {
        D_800E0BD4 = (u8 *)func_1502B5C8(&length, 3, 0x1C, D_800BEAAB, kind - 1);
        cursor = D_800E0BD4;
        end = cursor + length;
        i = 0;
        do {
            while (*cursor != 0) {
                cursor++;
            }
            while (*cursor == 0) {
                cursor++;
            }
            i++;
        } while (cursor < end);
        D_800E0BD8 = func_10003C40((i + 1) << 2, 1, 0, 0);
        cursor = D_800E0BD4;
        end = cursor + length;
        i = 0;
        do {
            D_800E0BD8[i] = cursor;
            i++;
            while (*cursor != 0) {
                cursor++;
            }
            while (*cursor == 0) {
                cursor++;
            }
        } while (cursor < end);
        if (kind == 1) {
            D_8008FDD8 = (u8 *)func_1502B5C8(&length, 3, 0x1C, D_800BEAAB, 2);
            D_800E0B88 = func_10003C40(0x140, 1, 0, 0);
            cursor = D_8008FDD8;
            for (i = 0; i < 0x50; i++) {
                D_800E0B88[i] = cursor;
                while (*cursor != 0) {
                    cursor++;
                }
                while (*cursor == 0) {
                    cursor++;
                }
            }
        }
    }
}

void func_151E6BFC(void) {
    D_800E0BD3 = 0;
    D_800E0BD4 = 0;
    D_8008FDD8 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E6C1C.s")

void func_151E7DC0(void) {
    s32 index;
    u8 id;
    void *resource;

    if ((*(f32 *)((u8 *)D_8008FDD4 + 8) < D_800ABA8C) && (*(s8 *)((u8 *)D_8008FDD4 + 0x3E) == 0)) {
        return;
    }
    for (index = 0; index < 2; index++) {
        if (*(s8 *)((u8 *)D_8008FDD4 + 0x3E) == 0) {
            id = ((u8 (*)[6])D_8008FFB0)[index][*(s8 *)((u8 *)D_8008FDD4 + 0x2C)];
        } else {
            id = D_8008FFB0[index * 6];
        }
        resource = func_151149AC(id);
        if (resource != 0) {
            *(s32 *)((u8 *)resource + 0x80) = 2;
        }
    }
}
void func_10017870(s32);

void func_151E7E9C(void) {
    if (D_800E0BE9 == 2) {
        func_10017870(1);
        return;
    }
    if (D_800E0BE9 == 0) {
        func_10017870(2);
        return;
    }
    func_10017870(4);
}
void func_151DE7D4(void);

void func_151E7EF8(void) {
    u32 cursor;
    u32 checksum;
    u32 end;

    func_151E7E9C();
    cursor = (u32)func_151DDC20;
    end = (u32)func_151DE7D4;
    checksum = 0;
    if (cursor < end) {
        do {
            checksum += *(u32 *)cursor;
            cursor += 4;
        } while (cursor < end);
    }
    if (checksum != 0xBFC924E3U) {
        *(s32 *)(u32)D_10003330 = 0;
    }
}
typedef struct Game20F9A0SpawnConfig {
    f32 scale;
    s8 yOffset;
    u8 model, appearance, pad7;
} Game20F9A0SpawnConfig;

typedef struct Game20F9A0SpawnPosition {
    s16 x, y, z;
    u8 angle, pad7;
} Game20F9A0SpawnPosition;

typedef struct Game20F9A0Descriptor {
    u8 unk_00[4];
    u8 unk_04;
    u8 unk_05;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E[0x22];
} Game20F9A0Descriptor;

typedef struct Game20F9A0Actor {
    u8 unk_00[4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06[0x62];
    u8 unk_68;
    u8 unk_69[0xE3];
    f32 unk_14C;
    f32 unk_150;
    u8 unk_154[0x1A4];
    u16 unk_2F8;
    u8 unk_2FA[0x22];
    void *unk_31C;
    u8 unk_320[0xC];
} Game20F9A0Actor;

typedef struct Game20F9A0Menu {
    u8 unk_00[0x2C];
    s8 unk_2C;
} Game20F9A0Menu;

void func_15060F28(u8 *, s32);
s32 func_15083E0C(u8);
void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, u32);
s32 func_15082A44(void *, s32, s32, s32, s32);
void func_15083384(void *, s32);
void func_1505E650(void *, s32, f32, f32, f32, f32, s32);
extern Game20F9A0SpawnConfig D_800AB57C[];
extern Game20F9A0SpawnPosition D_800AB940[];
extern Game20F9A0Descriptor *D_800D20FC;
extern Game20F9A0Actor *D_800E0BA0[];

void func_151E7F60(s32 arg0, s32 arg1) {
    s32 objectId;
    s32 descriptorId;
    Game20F9A0Descriptor *descriptor;
    Game20F9A0SpawnPosition *position;
    s32 model;
    s32 positionId;
    Game20F9A0Actor *actor;

    if (D_800E0BA0[arg0] != NULL) {
        func_15060F28((u8 *)D_800E0BA0[arg0], 1);
    }
    descriptorId = func_15083E0C(arg0 + 0x10);
    descriptor = &D_800D20FC[descriptorId];
    model = D_800AB57C[arg1].model;
    positionId = arg0;
    if (((Game20F9A0Menu *)D_8008FDD4)->unk_2C == 7) {
        positionId = arg0 + 1;
    }
    descriptor->unk_04 = model;
    position = &D_800AB940[positionId];
    descriptor->unk_06 = position->x;
    descriptor->unk_08 = position->y;
    descriptor->unk_08 += D_800AB57C[arg1].yOffset;
    descriptor->unk_0A = position->z;
    descriptor->unk_0C = position->angle;
    if (model == 0x53) {
        descriptor->unk_0D = 0x24;
    } else {
        descriptor->unk_0D = 0xE;
    }
    objectId = func_15082A44(descriptor, descriptorId, 0, 0, 0);
    if (objectId != 0) {
        actor = &((Game20F9A0Actor *)D_800CC2D0)[objectId - 1];
        D_800E0BA0[arg0] = actor;
        actor->unk_05 = 7;
        actor->unk_2F8 |= 3;
        actor->unk_150 = D_800AB57C[arg1].scale;
        actor->unk_14C = D_800AB57C[arg1].scale;
        if (actor->unk_04 == 0 || actor->unk_04 == 0x80) {
            actor->unk_31C = func_10003C40(0x1C0, 1, 0, 0);
            func_100226F0(actor->unk_31C, 0x1C0);
        }
        if (model == 0x3B) {
            actor->unk_68 = arg0 + 1;
        }
        func_15083384(actor, D_800AB57C[arg1].appearance);
        func_1505E650(actor, 0xF, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E81EC CURRENT (400) */
void func_151E81EC(void) {
    D_800E0BA4 = 0;
    D_800E0BA0[0] = NULL;
    D_800E0BA8 = 0;
    D_800E0BAC = 0;
    D_8008FD84 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E81EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E81EC.s")
s32 func_1517EFDC();                                /* extern */
extern s8 D_800D2E43;

void func_151E8214(void) {
    if ((u8) D_800E0B94 != 8) {
        if (func_1517EFDC() == 0) {
            D_800E0A90 = 0;
        }
        if (D_800E0A90 >= 0xA1) {
            D_8008FDCC = 0;
            D_800E0B94 = 8;
            D_8008FD8C = 1;
            D_8008FD90 = 1;
            D_8008FDA4 = 0;
            D_800E0A80 = -2;
            D_800E0A90 = 0;
            *(u8 *)&D_800D2E43 = 1;
        }
    }
}
void func_1501C730(s32, s32, s32, s32, s32);
extern u8 **D_800E0BD8;

void func_151E82B8(void) {
    func_151E530C();
    if ((D_800E0A80 == -1) && (D_800E0A90 >= 0x79)) {
        D_800E0B94 = 9;
        D_800E0A90 = 0;
        D_8008FDCC = 0xFF;
        D_800E0A80 = 0;
        func_1501C730(6, 0x1D, 0, 0, 1);
        return;
    }
    if (D_800E0A80 == -2) {
        D_800E0A80 = 0;
    }
    if ((D_800E0A90 >= 0x1BE) && (D_800E0A80 >= 0)) {
        if (D_800E0BD8[D_800E0A80][0] != 0x2A) {
            do {
                D_800E0A80 += 1;
            } while (D_800E0BD8[D_800E0A80][0] != 0x2A);
        }
        D_800E0A80 += 1;
        if (D_800E0BD8[D_800E0A80][0] == 0x3D) {
            D_800E0A80 = -1;
        }
        D_800E0A90 = 0;
    }
}
/* Call context: func_1501C730: unique active declaration in the allowed source */
/* Call context: func_1501D348: unique active project prototype */
/* Call context: func_151E5034: unique active declaration in the allowed source */
/* Call context: func_151E530C: unique active declaration in the allowed source */
void func_1501D348(s32, s32, s32, u8, s32);

void func_151E83E8(void) {
    if (D_800E0A80 == 0) {
        D_800E0A80 = -1;
        func_1501D348(0x1D, 6, 0, 0U, 0);
    }
    func_151E530C();
    if (func_1517EFDC() == 0) {
        D_800E0A90 = 0;
    }
    if (D_800E0A90 >= 0x65) {
        func_151E5034();
        D_8008FDA4 = 0;
        D_800E0B94 = 1;
        D_800E0A90 = 0;
        D_800D2E40 = 0;
        func_1501C730(6, 0x21, 0, 0, 1);
    }
}
