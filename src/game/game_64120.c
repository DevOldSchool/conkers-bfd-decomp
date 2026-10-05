#include "types.h"

/*
 * Reviewed source unit: src/game/game_64120.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15036CE8
 * - func_15036F34
 * - func_15037698
 * - func_150379DC
 * - func_150380C0
 * - func_15038468
 * - func_15038620
 * - func_15039A78
 * - func_15039CC8
 * - func_15039ED0
 * - func_1503A08C
 * - func_1503A678
 * - func_1503A830
 * - func_1503B708
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game64120InitBlock {
    f32 first[3];
    f32 second[3];
    u8 pad18[0x18];
    u8 field30[3];
    u8 field33[3];
    u8 field36[3];
    u8 pad39;
    s16 field3A[3];
    s16 field40[3];
    u8 pad46[2];
} Game64120InitBlock;

typedef struct Game64120InitState {
    u8 pad0[0x324];
    Game64120InitBlock *volatile block;
} Game64120InitState;

void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
extern f32 D_80098250;

typedef struct Game64120OutputBlock {
    u8 pad0[0x30];
    f32 x;
    f32 y;
    f32 z;
} Game64120OutputBlock;

typedef struct Game64120Output {
    u8 pad0[0x40];
    Game64120OutputBlock block;
} Game64120Output;

typedef struct Game64120Record {
    u8 pad0[0x18];
    f32 y;
    u8 pad1C[0x158];
    f32 x;
    f32 z;
    u8 pad17C[0x58];
    Game64120Output *output;
    u8 pad1D8[0x14C];
    Game64120InitBlock *block324;
    u8 pad328[4];
} Game64120Record;

extern Game64120Record D_800CC2D0[];

void func_15036C70(Game64120InitState *arg0) {
    f32 value;
    s32 offset;
    Game64120InitBlock *block;

    block = func_10003C40(sizeof(*block), 1, 0, 0);
    arg0->block = block;
    func_100226F0(block, sizeof(*block));
    value = D_80098250;
    offset = 0;
    do {
        *(f32 *)((u8 *)arg0->block + offset) = value;
        *(f32 *)((u8 *)arg0->block + offset + 0xC) = value;
        offset += 4;
    } while (offset != 0xC);
}
void func_150379DC(f32 *, s32, s32, s32, f32, s32, s32);
void func_15038620(s32, s32, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_80098354;
extern f32 D_80098358;
extern f32 D_8009835C;
extern u8 D_800C35EA;
extern f32 D_800C3FE8[3];
extern void *D_800D154C;
extern u8 D_800C3E78;
extern u8 D_800C3FFA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15036CE8 CURRENT (1995) */
void func_15036CE8(void) {
    Game64120Record *record;
    Game64120InitBlock *block;
    f32 value;
    s32 first;
    s32 last;
    s32 mode;

    record = &D_800CC2D0[D_800C3E78];
    block = record->block324;
    if (block != 0) {
        switch (record->pad0[4]) {
        case 0x3B:
        case 0x75:
        case 0x80:
        case 0x88:
        case 0x90:
        case 0x96:
        case 0x98:
        case 0x9C:
        case 0x9D:
        case 0x9F:
        case 0xA0:
        case 0xB0:
        case 0xB1:
        case 0xB2:
        case 0xB4:
            if (D_800C3FFA == 0) {
                D_800C3FFA = 1;
                return;
            }
            break;
        }
        if (D_800C35EA == 1 && D_800C3FFA == 0) {
            D_800C3FFA = 1;
            return;
        }
        first = 0;
        last = 1;
        if (D_800C3FFA == 0) {
            mode = 7;
            last = 0;
            first = 1;
            if (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0x100) {
                block->field3A[0] = 0x2D;
                block->field40[0] = 0x40;
                value = D_80098354;
            } else {
                value = D_80098358;
                if (value == block->first[0]) {
                    D_800C3FFA = 1;
                    return;
                }
            }
        } else {
            mode = 0xC;
            value = D_8009835C;
        }
        if (D_800C3FFA == 0 && !(*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0x100)) {
            D_800C3FE8[0] = value;
            D_800C3FE8[1] = value;
            D_800C3FE8[2] = value;
        } else {
            func_150379DC(D_800C3FE8, mode, 0, D_800C3E78, 90.0f, 0xFF, 0);
        }
        func_15038620(mode, 0, D_800C3FE8, D_800C3E78, first, 0,
                       D_800C3FFA, 3, 0, 0, 0, last, 0);
        D_800C3FFA++;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15036CE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15036CE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15036F34.s")
extern s32 D_800CC4A4;
void func_15038468(f32 *, f32 *, f32, f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15037698 CURRENT (3313) */
s32 func_15037698(s32 arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 *arg6, f32 arg7, s32 arg8, s32 arg9) {
    f32 delta[3];
    f32 basis[3];
    f32 *second;
    f32 angle;
    f32 elevation;
    f32 deltaZ;
    f32 deltaY;
    f32 *first;

    if (arg8 != 0) {
        arg6[0] = arg3;
        arg6[1] = arg4;
        arg6[2] = arg5;
        return 1;
    }
    arg0 = *(s32 *)((u8 *)&D_800CC4A4 + (arg0 * 0x32C));
    first = (f32 *)(arg0 + (arg1 << 6));
    if (arg0 == 0) {
        return 0;
    }
    second = (f32 *)(arg0 + (arg2 << 6));
    second[11] = 0.0f;
    second[7] = 0.0f;
    second[3] = 0.0f;
    first[3] = 0.0f;
    first[7] = 0.0f;
    first[11] = 0.0f;
    second[15] = 1.0f;
    first[15] = 1.0f;
    basis[0] = first[4];
    basis[1] = first[5];
    basis[2] = first[6];
    delta[0] = arg3 - first[12];
    deltaY = arg4 - first[13];
    delta[1] = deltaY;
    deltaZ = arg5 - first[14];
    delta[2] = deltaZ;
    func_15038468(&angle, &elevation,
                  (second[2] * deltaZ) + ((delta[0] * second[0]) + (deltaY * second[1])),
                  (second[6] * deltaZ) + ((delta[0] * second[4]) + (deltaY * second[5])),
                  (second[10] * deltaZ) + ((delta[0] * second[8]) + (deltaY * second[9])),
                  arg9);
    if ((angle < arg7) && (-arg7 < angle)) {
        arg6[0] = arg3;
        arg6[1] = arg4;
        arg6[2] = arg5;
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15037698 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15037698.s")
extern f32 D_8009862C;
extern s16 D_800C3FF4[];
extern void *D_800DBFF0;

s32 func_15037880(s32 arg0, f32 *arg1) {
    Game64120Record *temp_v0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_t8;

    temp_v0 = &D_800CC2D0[arg0];
    temp_t8 = (*(u16 *)((u8 *)temp_v0 + 0x2F8)) & 7;
    if (temp_t8 == 1) {
        arg1[0] = *(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
        arg1[1] = *(f32 *)((u8 *)D_800DBFF0 + 0x2FC);
        arg1[2] = *(f32 *)((u8 *)D_800DBFF0 + 0x300);
        return 1;
    }
    if (temp_t8 == 2) {
        if (temp_v0->pad0[5] == 4) {
            temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0x14) - (f32)D_800C3FF4[0];
            temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x1C) - (f32)D_800C3FF4[2];
            if (D_8009862C < ((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1))) {
                return 1;
            }
        }
        arg1[0] = (f32)D_800C3FF4[0];
        arg1[1] = (f32)D_800C3FF4[1];
        arg1[2] = (f32)D_800C3FF4[2];
        return 1;
    }
    if (temp_t8 == 3) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_150379DC.s")
s32 func_15037698(s32, s32, s32, f32, f32, f32, f32 *, f32, s32, s32);
extern f32 D_8009863C;
extern f32 D_80098640;
extern f32 D_80098644;
extern u8 D_800CC40B[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150380C0 CURRENT (5123) */
s32 func_150380C0(f32 *output, s32 arg1, s32 arg2, s32 ownerIndex, f32 arg4,
                   s32 preferredType, f32 *bestDistance, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10) {
    s32 index;
    f32 distance;
    f32 dx;
    f32 dz;
    f32 dy;
    s32 found;
    f32 radius;
    s32 type;
    s32 ownerLink;
    s32 includeSameType;
    s32 excludedType;
    Game64120Record *owner;
    Game64120Record *record;
    s32 candidateType;

    found = -1;
    includeSameType = 1;
    excludedType = -1;
    if (D_800C35EA == 1 || *((u8 *)&D_800C35EA + 1) == 1) {
        dx = D_8009863C;
        output[0] = dx;
        output[1] = dx;
        output[2] = dx;
        return 0;
    }
    owner = &D_800CC2D0[ownerIndex];
    type = owner->pad0[4];
    ownerLink = ownerIndex + 1;
    if (type == 5 || type == 0xAD || type == 0xAE || type == 0xAF) {
        includeSameType = 0;
    }
    if (type == 0x2D) {
        excludedType = 0x2C;
    }
    index = 0;
    if (arg9 == 0) {
        radius = (f32)(owner->pad1D8[0x65] * 8);
        radius = radius * radius;
    } else {
        radius = D_80098640;
    }
    for (record = D_800CC2D0; index != 0x19; index++, record++) {
        if (*(s32 *)record == 0) {
            continue;
        }
        candidateType = record->pad0[4];
        if (candidateType == 0xFF) {
            continue;
        }
        if (index == ownerIndex) {
            continue;
        }
        if (ownerLink == record->pad1C[0x49]) {
            continue;
        }
        if (index + 1 != owner->pad1C[0x49] &&
            (includeSameType != 0 || type != candidateType) &&
            excludedType != candidateType &&
            ((arg8 == 0 && (*(u16 *)((u8 *)owner + 0x2F8) & 7) != 4) ||
             record->pad1C[0x10B] != 0xFF) &&
            ((*(u16 *)((u8 *)owner + 0x2F8) & 7) != 5 ||
             record->pad1C[0x10B] == 0xFF)) {
            dx = *(f32 *)((u8 *)owner + 0x14) - *(f32 *)((u8 *)record + 0x14);
            dz = *(f32 *)((u8 *)owner + 0x1C) - *(f32 *)((u8 *)record + 0x1C);
            dy = owner->y - record->y;
            distance = (dx * dx) + (dz * dz) + (dy * dy);
            if (index == owner->pad1D8[0x4A] &&
                (owner->pad1D8[0x4B] == 1 || owner->pad1D8[0x4B] == 0xC)) {
                distance = 0.0f;
            }
            if ((distance < radius && distance < *bestDistance) ||
                preferredType == candidateType) {
                if (func_15037698(ownerIndex, arg1, arg2,
                                  (f32)*(s16 *)((u8 *)record + 0x1A4),
                                  (f32)*(s16 *)((u8 *)record + 0x1AA),
                                  (f32)*(s16 *)((u8 *)record + 0x1A8),
                                  output, arg4, arg7, arg10) != 0) {
                    *bestDistance = distance;
                    found = index;
                    if (preferredType == record->pad0[4]) {
                        break;
                    }
                }
            }
        }
    }
    if (found != -1) {
        return D_800CC40B[found * sizeof(Game64120Record)] + 1;
    }
    dx = D_80098644;
    output[0] = dx;
    output[1] = dx;
    output[2] = dx;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150380C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_150380C0.s")
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_80098648;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15038468 CURRENT (475) */
void func_15038468(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 var_fv0;
    f32 factor;

    switch (arg5) {                                 /* irregular */
    case 0:
        *arg0 = func_150484A0(arg2, arg4);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        *arg1 = var_fv0;
        break;
    case 1:
        *arg0 = func_150484A0(-arg4, arg2);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        *arg1 = var_fv0;
        break;
    case 2:
        *arg0 = func_150484A0(arg4, -arg2);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        *arg1 = var_fv0;
        break;
    case 3:
        *arg0 = func_150484A0(arg4, -arg3);
        var_fv0 = func_150484A0(-arg2, sqrtf((arg3 * arg3) + (arg4 * arg4)));
        *arg1 = var_fv0;
        break;
    }
    factor = D_80098648;
    *arg0 *= factor;
    *arg1 *= factor;
    var_fv0 = *arg0;
    if (var_fv0 > 180.0f) {
        *arg0 = var_fv0 - 360.0f;
    }
    var_fv0 = *arg1;
    if (var_fv0 > 180.0f) {
        *arg1 = var_fv0 - 360.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15038468 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15038468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15038620.s")
typedef struct Game64120Entry {
    u8 data[0x18];
} Game64120Entry;

extern Game64120Entry D_80098068[];

Game64120Entry *func_15039A54(s32 arg0, s32 arg1) {
    return &D_80098068[arg1];
}
extern void * D_800CC5E8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15039A78 CURRENT (1237) */
void func_15039A78(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, s32 arg6) {
    Game64120Entry *temp_v0;
    register f32 margin;
    register f32 upperY;
    register f32 valueX;
    register f32 lowerY;
    register f32 upperX;
    register f32 valueY;
    register f32 bound;

    void *temp_v1;

    temp_v1 = *(void **)((u8 *)&D_800CC5E8 + arg6 * 0x32C);
    temp_v0 = func_15039A54(arg6, 0);
    if ((temp_v1 != 0) && (*(s32 *)((u8 *)temp_v1 + 0x2C) != 0x100)) {
        margin = *(f32 *)((u8 *)temp_v0 + 0x10);
        valueX = *arg0;
        if (((*(f32 *)((u8 *)temp_v0 + 0) + margin) < valueX) || (valueX < (*(f32 *)((u8 *)temp_v0 + 4) - margin))) {
            *arg0 = arg4;
            *arg1 = arg5;
            if (arg2 != 0) {
                *arg2 = *arg0;
                *arg3 = *arg1;
            }
        } else {
            if (arg2 != 0) {
                *arg2 = valueX;
                *arg3 = *arg1;
            }
            if (*arg0 < *(f32 *)((u8 *)temp_v0 + 4)) {
                *arg0 = *(f32 *)((u8 *)temp_v0 + 4);
            } else {
                upperX = *(f32 *)((u8 *)temp_v0 + 0);
                if (upperX < *arg0) {
                    bound = upperX;
                } else {
                    bound = *arg0;
                }
                *arg0 = bound;
            }
            upperY = *(f32 *)((u8 *)temp_v0 + 8);
            margin = *(f32 *)((u8 *)temp_v0 + 0x14);
            valueY = *arg1;
            if (((upperY + margin) < valueY) || (lowerY = *(f32 *)((u8 *)temp_v0 + 0xC), (valueY < (lowerY - margin)))) {
                *arg1 = arg5;
                return;
            }
            if (valueY < lowerY) {
                *arg1 = lowerY;
                return;
            }
            if (upperY < valueY) {
                bound = upperY;
            } else {
                bound = valueY;
            }
            goto block_34;
        }
    } else {
        valueX = *arg0;
        upperX = *(f32 *)((u8 *)temp_v0 + 4);
        if (valueX < upperX) {
            *arg0 = upperX;
        } else {
            upperX = *(f32 *)((u8 *)temp_v0 + 0);
            if (upperX < valueX) {
                bound = upperX;
            } else {
                bound = valueX;
            }
            *arg0 = bound;
        }
        valueY = *arg1;
        lowerY = *(f32 *)((u8 *)temp_v0 + 0xC);
        if (valueY < lowerY) {
            *arg1 = lowerY;
            return;
        }
        upperY = *(f32 *)((u8 *)temp_v0 + 8);
        if (upperY < valueY) {
            bound = upperY;
        } else {
            bound = valueY;
        }
block_34:
        *arg1 = bound;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15039A78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039A78.s")
typedef struct Game64120ControllerView {
    s32 kind;
    u8 type;
    u8 pad05[0x37];
    f32 field3C;
    u8 pad40[0x44];
    u16 animation;
    u8 pad86[0x27];
    u8 fieldAD;
    u8 padAE[0x11C];
    u8 field1CA;
    u8 pad1CB[0x130];
    u8 flags2FB;
    u8 pad2FC[0x20];
    u8 *extra31C;
    u8 pad320[4];
    Game64120InitBlock *block324;
} Game64120ControllerView;

extern u16 *D_80084380[];
extern u8 D_80097E7C[];
extern u8 D_80098050[];
extern u8 D_800BE9B4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15039CC8 CURRENT (280) */
void func_15039CC8(Game64120ControllerView *object) {
    u8 *block;
    s32 type;
    s32 group;
    s32 count;
    s32 index;
    u16 *animations;

    block = (u8 *) object->block324;
    if (block != 0) {
        type = object->type;
        if (((type == 0x53) && (object->animation == 0x15)) ||
            (D_800BE9B4 != 0)) {
            index = 0;
            do {
                index++;
                block++;
                block[0x2F] = 0x28;
                block[0x32] = 0;
                block[0x35] = 4;
            } while (index != 3);
        }
        group = D_80097E7C[type];
        if (group != 0) {
            group--;
            animations = D_80084380[group];
            count = D_80098050[group];
            for (index = 0; index < count; index++) {
                if (object->animation == animations[index]) {
                    object->flags2FB |= 4;
                    return;
                }
            }
            if (object->kind == 1) {
                if ((object->field1CA == 0) ||
                    ((object->fieldAD != 0) && (object->field3C < 5.0f)) ||
                    (object->extra31C[0x197] != 0) ||
                    (object->field3C > 20.0f)) {
                    object->flags2FB |= 4;
                }
            } else if (object->field1CA == 0) {
                object->flags2FB |= 4;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15039CC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039CC8.s")
void func_15039A78(f32 *, f32 *, f32 *, f32 *, f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15039ED0 CURRENT (1758) */
void func_15039ED0(s32 arg0, f32 *arg1, register f32 *arg2, f32 *arg3,
                   f32 *arg4, f32 arg5, f32 arg6, s32 arg7) {
    Game64120Entry *entry;
    f32 marginX;
    f32 marginY;
    f32 valueX;
    f32 valueY;
    f32 bound;

    if (arg0 == 0) {
        func_15039A78(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return;
    }
    entry = func_15039A54(arg7, arg0);
    marginX = *(f32 *)(entry->data + 0x10);
    valueX = *arg1;
    if ((*(f32 *)(entry->data + 0) + marginX < valueX) ||
        (valueX < *(f32 *)(entry->data + 4) - marginX)) {
        *arg1 = arg5;
        *arg2 = arg6;
        if (arg3 != 0) {
            *arg3 = *arg1;
            *arg4 = *arg2;
        }
    } else {
        if (arg3 != 0) {
            *arg3 = valueX;
            *arg4 = *arg2;
        }
        if (*arg1 < *(f32 *)(entry->data + 4)) {
            bound = *(f32 *)(entry->data + 4);
        } else if (*(f32 *)(entry->data + 0) < *arg1) {
            bound = *(f32 *)(entry->data + 0);
        } else {
            bound = *arg1;
        }
        *arg1 = bound;
        marginY = *(f32 *)(entry->data + 0x14);
        valueY = *arg2;
        if ((*(f32 *)(entry->data + 8) + marginY < valueY) ||
            (valueY < *(f32 *)(entry->data + 0xC) - marginY)) {
            *arg2 = arg6;
            return;
        }
        if (valueY < *(f32 *)(entry->data + 0xC)) {
            bound = *(f32 *)(entry->data + 0xC);
        } else if (*(f32 *)(entry->data + 8) < valueY) {
            bound = *(f32 *)(entry->data + 8);
        } else {
            bound = valueY;
        }
        *arg2 = bound;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15039ED0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039ED0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A08C.s")
extern u8 D_800C3E78;

void func_1503A60C(void) {
    Game64120OutputBlock *temp_v0;
    Game64120Record *temp_v1;

    temp_v0 = &D_800CC2D0[D_800C3E78].output->block;
    temp_v1 = &D_800CC2D0[D_800C3E78];
    temp_v0->x = temp_v1->x;
    temp_v0->y = D_800CC2D0[D_800C3E78].y;
    temp_v0->z = D_800CC2D0[D_800C3E78].z;
}
typedef struct Game64120Motion {
    u8 pad0[0xC];
    f32 zero0;
    u8 pad10[0xC];
    f32 zero1;
    u8 pad20[0xC];
    f32 zero2;
    f32 x;
    f32 y;
    f32 z;
    f32 one;
} Game64120Motion;

typedef union Game64120FloatBits {
    f32 value;
    u32 bits;
} Game64120FloatBits;

void func_150A7BC0(void *);
void func_150A7CB0(void *, u32, u32, u32);
void func_150A7A48(void *, void *, void *);
void func_10023A10(void *, void *, s32);
extern u8 D_80084404[];
extern u8 D_800C3FFA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503A678 CURRENT (482) */
void func_1503A678(void) {
    Game64120FloatBits scaleZ;
    Game64120FloatBits scaleY;
    Game64120FloatBits scaleX;
    u8 transform[0x40];
    u8 transformed[0x40];
    f32 original[3];
    Game64120Record *record;
    Game64120Motion *motion;
    f32 factor;

    record = &D_800CC2D0[D_800C3E78];
    if (record->pad0[4] != 0x22) {
        return;
    }
    factor = (f32)(u32)record->pad1D8[0x32] * 0.015625f + 1.0f;
    if (D_800C3FFA == 0) {
        scaleX.value = factor;
        scaleY.value = 1.0f;
        scaleZ.value = factor;
    } else {
        scaleX.value = 1.0f / factor;
        scaleY.value = 1.0f;
        scaleZ.value = scaleX.value;
    }
    motion = ((Game64120Motion *)record->output) + D_80084404[D_800C3FFA];
    motion->one = 1.0f;
    motion->zero0 = 0.0f;
    motion->zero1 = 0.0f;
    motion->zero2 = 0.0f;
    original[0] = motion->x;
    original[1] = motion->y;
    original[2] = motion->z;
    func_150A7BC0(transform);
    func_150A7CB0(transform, scaleX.bits, scaleY.bits, scaleZ.bits);
    func_150A7A48(motion, transform, transformed);
    func_10023A10(transformed, motion, 0x40);
    motion->x = original[0];
    motion->y = original[1];
    motion->z = original[2];
    D_800C3FFA++;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503A678 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A678.s")
void func_15036F34(void);
void func_1503A678(void);
extern u8 D_800C3FFA;

void func_1503A7F0(void) {
    s32 temp_t6;
    s32 sp1C;

    temp_t6 = D_800C3FFA;
    D_800C3FFA = 0;
    sp1C = temp_t6;
    func_15036F34();
    D_800C3FFA = sp1C;
    func_1503A678();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A830.s")
s32 func_15037880(s32, f32 *);
s32 func_150380C0(f32 *, s32, s32, s32, f32, s32, f32 *, s32, s32, s32, s32);
extern f32 D_800986EC;
extern f32 D_800C3FD0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503B708 CURRENT (450) */
void func_1503B708(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4,
                   s32 arg5, f32 *arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    f32 *scratch;
    f32 value;

    scratch = D_800C3FD0;
    value = D_800986EC;
    *(f32 *)((u8 *)arg0 + 0) = value;
    *(f32 *)((u8 *)arg0 + 4) = value;
    *(f32 *)((u8 *)arg0 + 8) = value;
    scratch[0] = value;
    scratch[1] = value;
    scratch[2] = value;
    if (func_15037880(arg3, arg0) == 0) {
        func_150380C0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                      arg8, arg9, arg10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503B708 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503B708.s")
