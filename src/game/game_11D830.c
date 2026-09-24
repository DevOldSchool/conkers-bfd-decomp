#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D830.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F03F8
 * - func_150F07E4
 * - func_150F088C
 * - func_150F0A24
 * - func_150F0BEC
 * - func_150F0E48
 * - func_150F1020
 * - func_150F1170
 * - func_150F15F8
 * - func_150F1684
 * - func_150F16DC
 * - func_150F1A00
 * - func_150F1B48
 * - func_150F1CB0
 * - func_150F1D10
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11D830Inner {
    u8 pad0[0x138];
    s32 field_138;
} Game11D830Inner;

typedef struct Game11D830Object {
    u8 pad0[0x178];
    Game11D830Inner *inner;
} Game11D830Object;

typedef struct Game11D830AltInner {
    u8 pad0[0x13C];
    s32 field_13C;
} Game11D830AltInner;

typedef struct Game11D830AltObject {
    u8 pad0[0x18];
    Game11D830AltInner *inner;
} Game11D830AltObject;

Game11D830Inner *func_150F0380(Game11D830Object *arg0) {
    Game11D830Inner *inner = arg0->inner;

    inner->field_138 = 0;
    return inner;
}
Game11D830AltInner *func_150F03E8(Game11D830AltObject *arg0);
void func_151617C4(Game11D830AltObject *arg0);
void func_151617E4(Game11D830AltObject *arg0);

void func_150F0390(Game11D830AltObject *arg0) {
    func_150F03E8(arg0);
    func_151617C4(arg0);
}
void func_150F03BC(Game11D830AltObject *arg0) {
    func_150F03E8(arg0);
    func_151617E4(arg0);
}
Game11D830AltInner *func_150F03E8(Game11D830AltObject *arg0) {
    Game11D830AltInner *inner = arg0->inner;

    inner->field_13C = 0;
    return inner;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F03F8.s")
/* Call context: func_1516972C: unique active declaration in the allowed source */
void * func_1516972C(void *, s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F07E4 CURRENT (1472) */
void func_150F07E4(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x60);
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)temp_v0 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0, (s32) arg1, (void *) temp_t6);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 0);
        if (temp_a0 == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(u8 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_a0;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F07E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F07E4.s")
/* Call context: func_1516972C: unique active declaration in the allowed source */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F088C CURRENT (1792) */
void func_150F088C(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x170)) || (*(u8 *)((u8 *)(arg0 + 0x170) + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0, (s32) arg1, (void *) temp_t6);
        }
    } else {
        temp_v0 = (void *)(arg0 + 0x170);
        if (temp_t6 == 0x2D) {
            temp_a0 = *(s32 *)((u8 *)arg0 + 0x170);
            temp_v1 = *(s32 *)((u8 *)arg1 + 0);
            if (temp_v1 == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x170) = (s32) *(u8 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x170) = temp_v1;
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F088C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F088C.s")
void func_15160A58(s32, s32, void *, s32, s32, s32, s32, s32,
                   s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800A1674;
extern u8 D_800A1680;

void func_150F0938(s32 arg0) {
    func_15160A58(arg0, 0x25, &D_800A1674, 2, 0x12C, 4, 0, 0xFF,
                  0, 0xFF, 0, -1, 0, 0, 0xFF, 1);
    func_15160A58(arg0, 2, &D_800A1680, 2, 0x12C, 0xD, 0xFF, 0xFF,
                  0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0A24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0BEC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A1870;
extern f32 D_800A1874;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F0E48 CURRENT (533) */
s32 func_150F0E48(u8 *arg0, s32 arg1) {
    u8 *temp_s0;
    u8 *temp_v0;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0xA8));
    if (*(u8 *)((u8 *)arg0 + 0xAC) != *(u8 *)((u8 *)temp_v0 + 0x3B)) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
    temp_s0 = (void *)(arg0 + 0xA8);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    *(f32 *)((u8 *)temp_s0 + 8) = (f32) (*(f32 *)((u8 *)temp_s0 + 8) + (D_800A1870 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xC) + (D_800A1874 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0x10) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x10) + (0.25f * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 8) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 8));
    *(f32 *)((u8 *)temp_s0 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0xC));
    *(f32 *)((u8 *)temp_s0 + 0x10) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x10));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 8)) * 243.0f) + 780.0f);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0xC)) * 243.0f) + 780.0f);
    *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x10)) * 50.0f) + 200.0f);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F0E48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0E48.s")
void *func_1516972C(void *, s32, void *);           /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1020 CURRENT (2723) */
void *func_150F1020(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *var_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        var_v0 = (void *)(arg0 + 0xA8);
        temp_a0 = *(s32 *)((u8 *)arg0 + 0xA8);
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a0) {
            *(s32 *)((u8 *)arg0 + 0xA8) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)var_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return var_v0;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)((u8 *)arg0 + 0xA8) = temp_v1;
            *(u8 *)((u8 *)var_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
            return var_v0;
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return var_v0;
    }
    if (((temp_t6 == 0) || (var_v0 = arg0 + 0xA8, (temp_t6 == 0x43))) && ((var_v0 = arg0 + 0xA8, (*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0xA8))) || (*(u8 *)((u8 *)var_v0 + 4) == (u8) *(s32 *)((u8 *)arg1 + 4)))) {
        var_v0 = func_1516972C(arg0, temp_t6, arg0);
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1020 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1020.s")
void func_10022EC0(void *, void *, s32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game11D830SpawnPacket {
    void *field_0;
    u8 field_4;
    u8 pad5[3];
    f32 field_8;
    f32 field_C;
    f32 field_10;
    f32 field_14;
} Game11D830SpawnPacket;

void func_150F10D4(void *arg0) {
    Game11D830SpawnPacket packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = 0.0f;
    packet.field_C = *(f32 *)((u8 *)arg0 + 0x14);
    packet.field_10 = *(f32 *)((u8 *)arg0 + 0x18);
    packet.field_14 = *(f32 *)((u8 *)arg0 + 0x1C);
    temp_v0 = func_15149130(0x12C, -1, 0x4C, -1, 0, 0x3A, 0x18, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0x18);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1170.s")
void func_15149514(s32, u8, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F15F8 CURRENT (86) */
void func_150F15F8(void *arg0, void *arg1, u8 arg2) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x43) {
        if ((*(s32 *)arg1 == *(s32 *)temp_a2) || (*(u8 *)((u8 *)temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0, (s32) arg1, temp_a2);
        }
    } else {
        func_15149514((s32) arg1, arg2, (s32) temp_a2, (s32) ((u8 *)temp_a2 + 4), (s32) arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F15F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F15F8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1684 CURRENT (455) */
void func_150F1684(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v1;

    temp_v1 = arg0 + 0x18;
    if ((arg2 == 0x43) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)temp_v1) || (*(u8 *)(temp_v1 + 4) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C(arg0, (s32) arg1, (void *) (s32) arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1684 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1684.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F16DC.s")
typedef struct Game11D830Weights {
    u16 value[3];
} Game11D830Weights;

f32 func_15047C00(f32);
extern Game11D830Weights D_80088B00;
extern f32 D_800A18E8;
extern f32 D_800A18EC;
extern f32 D_800A18F0;
extern s32 D_800BE9E4;
extern u8 D_800CC298[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1A00 CURRENT (1581) */
void func_150F1A00(void *arg0) {
    Game11D830Weights weights;
    s32 index;
    s32 flags;
    s32 i;
    s32 j;
    f32 *row;
    f32 *cursor;
    f32 current;
    f32 scale;

    weights = D_80088B00;
    index = 0;
    flags = *(s32 *)((u8 *)arg0 + 0x2E4);
    if ((flags & 3) == 3) {
        index = 1;
    }
    if ((flags & 0xC) == 0xC) {
        index = 2;
    }
    *(s16 *)(D_800CC298 + 0x14) += weights.value[index] * D_800BE9E4;
    scale = ((func_15047C00((f32)*(s16 *)(D_800CC298 + 0x14) * D_800A18E8) + 1.0f)
             * 0.5f * D_800A18EC) + D_800A18F0;
    row = (f32 *)((u8 *)*(void **)((u8 *)arg0 + 0x1D4) + 0xF80);
    for (i = 0; i != 3; i++) {
        cursor = row;
        j = 1;
        current = *cursor * scale;
        do {
            j++;
            *cursor = current;
            current = cursor[1] * scale;
            cursor++;
        } while (j != 3);
        *cursor = current;
        row += 4;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1A00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1A00.s")
extern u8 D_800CC354[];
extern f32 D_800A18F4;
extern f32 D_800A18F8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1B48 CURRENT (1520) */
void *func_150F1B48(void *arg0, s32 arg1) {
    s32 matched;
    s32 increment;
    s32 value;
    s16 *out = (s16 *)arg0;

    if (*(u16 *)(D_800CC354 + arg1 * 0x32C) == 0x21) {
        matched = 1;
    } else {
        matched = 0;
    }
    increment = D_800BE9E4 * 0x222;
    if (matched != 0) {
        value = *(s16 *)(D_800CC298 + 0x12) - increment;
        if (D_800A18F4 < (f32)value) {
            *(s16 *)(D_800CC298 + 0x12) = value;
        } else {
            *(s16 *)(D_800CC298 + 0x12) = -0x1999;
        }
    } else {
        value = *(s16 *)(D_800CC298 + 0x12) + increment;
        if ((f32)value < D_800A18F8) {
            *(s16 *)(D_800CC298 + 0x12) = value;
        } else {
            *(s16 *)(D_800CC298 + 0x12) = 0x1555;
        }
    }
    out[0] = 0xB2;
    out[2] = 0xB8;
    out[1] = *(s16 *)(D_800CC298 + 0x12);
    out[4] = 0xB2 + 2 * 6;
    out[3] = *(s16 *)(D_800CC298 + 0x12);
    out[6] = 0xB8 + 2 * 6;
    out[5] = *(s16 *)(D_800CC298 + 0x12);
    out[8] = 0xBE + 2 * 6;
    out[7] = *(s16 *)(D_800CC298 + 0x12);
    out[10] = 0xC4 + 2 * 6;
    out[9] = *(s16 *)(D_800CC298 + 0x12);
    out[11] = *(s16 *)(D_800CC298 + 0x12);
    return &out[12];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1B48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1B48.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1CB0 CURRENT (460) */
void func_150F1CB0(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0x84) == 0x14) {
        *(s8 *)((u8 *)arg0 + 0x68) = 0x1B;
    } else {
        *(s8 *)((u8 *)arg0 + 0x68) = 0xC;
    }
    *(s8 *)((u8 *)arg0 + 0x69) = 0x13;
    if ((*(s32 *)((u8 *)arg0 + 0x2E4) & 3) == 3) {
        *(s8 *)((u8 *)arg0 + 0x69) = 0x14;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x2E4) & 0xC) == 0xC) {
        *(s8 *)((u8 *)arg0 + 0x69) = 0x17;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1CB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1CB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1D10.s")
