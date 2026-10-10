#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FB600.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_buffer_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CE150
 * - func_150CE200
 * - func_150CE694
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void *func_10022EC0(void *, const void *, u32);
extern void *func_1515FF74(s8 *arg0, s32 arg1, s32 arg2);
extern f32 D_800A07FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CE150 CURRENT (10315) */
void *func_150CE150(void *arg0, s16 arg1, s32 arg2) {
    s8 sp916;
    s16 sp914;
    s8 sp912;
    s8 sp911;
    s8 sp910;
    s8 sp34;
    s32 sp30;
    f32 sp2C;
    f32 sp28;
    u8 sp24;
    void *sp20;
    void *var_v0;

    if (arg0 == 0) {
        return 0;
    }
    sp910 = 1;
    sp911 = 1;
    sp912 = 0;
    sp916 = 2;
    sp30 = 0x2710;
    sp34 = 0;
    sp28 = D_800A07FC;
    sp2C = D_800A07FC;
    sp914 = arg1;
    sp20 = arg0;
    sp24 = *(u8 *)((u8 *)arg0 + 0x3B);
    var_v0 = func_1515FF74(&sp910, 0x8F0, arg2 & 0xFF);
    if (var_v0 != 0) {
        var_v0 = func_10022EC0((u8 *)var_v0 + 0x18, &sp20, 0x8F0);
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CE150 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB600/func_150CE150.s")
typedef struct {
    s32 active;
    u8 pad4[0x37];
    u8 generation;
    u8 pad3C[0x198];
    s32 transform;
} GameFB600LinkedObject;

typedef struct GameFB600Remap {
    GameFB600LinkedObject *object;
    u8 generation;
    u8 pad5[3];
    f32 width;
    f32 height;
    s32 step;
    u8 flags;
    u8 pad15[3];
    u32 left;
    u32 top;
    u32 right;
    u32 bottom;
    f32 center[2];
    s16 columns[0x280];
    s16 rows[0x280];
} GameFB600Remap;

typedef struct GameFB600Actor {
    u8 pad0[0x18];
    GameFB600Remap remap;
} GameFB600Actor;

void func_15143134(f32 *, f32 *, s32);
s32 func_15144CEC(f32 *, f32 *, f32 *, f32 *, f32 *, s32);
extern s32 D_80082FA4;
extern f32 D_800A07F0[3];
extern f32 D_800A0800;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CE200 CURRENT (960) */
s32 func_150CE200(GameFB600Actor *arg0) {
    f32 transformed[3];
    f32 projectedZ;
    f32 projectedW;
    f32 scale;
    GameFB600Remap *remap;
    f32 width;
    f32 height;
    f32 maxX;
    s32 transform;

    remap = &arg0->remap;
    if (arg0->remap.object->active == 0) {
        return 0;
    }
    if (remap->generation != remap->object->generation) {
        return 0;
    }
    transform = remap->object->transform;
    if (transform == 0) {
        remap->flags &= 0xFFFE;
    } else {
        func_15143134(D_800A07F0, transformed, transform + 0xD00);
        if (func_15144CEC(transformed, remap->center, &projectedZ, &projectedW, &scale, D_80082FA4)) {
            maxX = D_800A0800;
            width = remap->width * scale;
            height = remap->height * scale;
            remap->left = (s32)(remap->center[0] - width);
            remap->top = (s32)(remap->center[1] - height);
            remap->right = (s32)(remap->center[0] + width);
            remap->bottom = (s32)(remap->center[1] + height);
            if (maxX < (f32)(s32)remap->left ||
                (f32)(s32)remap->right < 0.0f ||
                (f32)(s32)remap->top > 215.0f ||
                (f32)(s32)remap->bottom < 0.0f) {
                remap->flags &= 0xFFFE;
            } else {
                if ((f32)(s32)remap->left < 0.0f) {
                    remap->left = 0;
                }
                if ((f32)(s32)remap->top < 0.0f) {
                    remap->top = 0;
                }
                if (maxX < (f32)(s32)remap->right) {
                    remap->right = 0x123;
                }
                if ((f32)(s32)remap->bottom > 215.0f) {
                    remap->bottom = 0xD7;
                }
                remap->flags |= 1;
                return 1;
            }
        } else {
            remap->flags &= 0xFFFE;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CE200 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB600/func_150CE200.s")

void *func_10022EC0(void *, const void *, u32);
extern s32 D_800BE620;

void func_150CE450(GameFB600Actor *arg0, s32 pixels) {
    s16 *columnCursor;
    s16 *rowCursor;
    s16 *pixelCursor;
    s32 sourceAddress;
    s32 byteOffset;
    s32 row;
    u32 firstColumn;
    u32 start;
    s32 firstRow;
    u32 end;
    u32 columnSource;
    u32 rowSource;
    u32 accumulator;
    u32 columnIndex;
    u32 rowIndex;
    s32 pixelIndex;
    s16 *rowMapping;
    GameFB600Remap *remap;

    remap = &arg0->remap;
    if (remap->flags & 1) {
        accumulator = 0;
        columnSource = remap->left;
        columnIndex = remap->left;
        if (columnIndex <= remap->right) {
          columnCursor = &remap->columns[columnIndex];
          do {
            *columnCursor = columnSource;
            accumulator += remap->step;
            if (accumulator >= 0x10000U) {
                columnSource = columnIndex;
                accumulator -= 0x10000;
            }
            columnIndex++;
            columnCursor++;
          } while (columnIndex <= remap->right);
        }
        accumulator = 0;
        firstRow = remap->top;
        rowSource = firstRow;
        rowCursor = remap->rows;
        for (rowIndex = firstRow; rowIndex <= remap->bottom; rowIndex++) {
            rowCursor[rowIndex] = rowSource;
            accumulator += remap->step;
            if (accumulator >= 0x10000U) {
                rowSource = rowIndex;
                accumulator -= 0x10000;
            }
        }
        for (row = remap->bottom; row >= (s32)remap->top; row--) {
            start = remap->left;
            end = remap->right;
            rowMapping = &remap->rows[row];
            if (row != remap->bottom &&
                (rowMapping[1] == rowMapping[0])) {
                func_10022EC0((void *)(pixels + ((row * D_800BE620 + start) * 2)),
                    (void *)(pixels + (((row + 1) * D_800BE620 + start) * 2)), (end - start) * 2 + 2);
            } else {
                pixelIndex = end;
                if ((s32)end >= (s32)start) {
                    rowMapping = &remap->rows[row];
                    pixelCursor = remap->columns;
                    do {
                        *(u16 *)(pixels + row * D_800BE620 * 2 + pixelIndex * 2) =
                            ((u16 *)((u8 *)pixels + pixelCursor[pixelIndex] * 2))[*rowMapping * D_800BE620];
                        pixelIndex--;
                    } while ((s32)pixelIndex >= (s32)remap->left);
                }
            }
        }
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CE694 CURRENT (1817) */
void func_150CE694(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    arg2 = temp_t6;
    if (arg2 == 0x2D) {
        temp_v0 = (u8 *)arg0 + 0x18;
        temp_a0 = *(s32 *)temp_v0;
        temp_v1 = *(s32 *)arg1;
        if (temp_v1 == temp_a0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((arg2 == 0) &&
               ((*(s32 *)arg1 == *(s32 *)((u8 *)arg0 + 0x18)) ||
                (*(u8 *)((u8 *)arg0 + 0x1C) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C((u8 *)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CE694 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB600/func_150CE694.s")
