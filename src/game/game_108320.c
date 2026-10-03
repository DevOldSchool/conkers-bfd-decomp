#include "types.h"

/*
 * Reviewed source unit: src/game/game_108320.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DAE70
 * - func_150DB114
 * - func_150DB2D8
 * - func_150DB518
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DAE70.s")
extern f32 D_800A0BE4;
extern f32 D_800A0BE8;
extern f32 D_800A0BEC;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DB114 CURRENT (2565) */
s32 func_150DB114(u8 *arg0) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fa1;
    s16 temp_v1;
    u8 *var_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x134);
    var_v0 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)arg0 + 0x110) = (f32) (*(f32 *)((u8 *)arg0 + 0x110) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x114) = (f32) (*(f32 *)((u8 *)arg0 + 0x114) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x118) = (f32) (*(f32 *)((u8 *)arg0 + 0x118) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + (*(f32 *)((u8 *)arg0 + 0x110) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x114) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + (*(f32 *)((u8 *)arg0 + 0x118) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x124) = (f32) (*(f32 *)((u8 *)arg0 + 0x124) + (*(f32 *)((u8 *)arg0 + 0x12C) * D_800BE9A4));
    if (D_800A0BE4 < *(f32 *)((u8 *)arg0 + 0x124)) {
        var_v0 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)var_v0 + 0x14) = (f32) D_800A0BE4;
        *(f32 *)((u8 *)var_v0 + 0x1C) = (f32) -*(f32 *)((u8 *)var_v0 + 0x1C);
        var_fa1 = D_800A0BE8;
    } else {
        var_fa1 = D_800A0BEC;
        if (*(f32 *)((u8 *)var_v0 + 0x14) < var_fa1) {
            *(f32 *)((u8 *)var_v0 + 0x14) = var_fa1;
            *(f32 *)((u8 *)var_v0 + 0x1C) = (f32) -*(f32 *)((u8 *)var_v0 + 0x1C);
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)var_v0 + 0x20);
    *(f32 *)((u8 *)var_v0 + 0x18) = (f32) (*(f32 *)((u8 *)var_v0 + 0x18) + (temp_fv0_2 * D_800BE9A4));
    temp_fv1 = *(f32 *)((u8 *)var_v0 + 0x18);
    if (D_800A0BE4 < temp_fv1) {
        *(f32 *)((u8 *)var_v0 + 0x18) = (f32) D_800A0BE4;
        *(f32 *)((u8 *)var_v0 + 0x20) = (f32) -temp_fv0_2;
    } else if (temp_fv1 < var_fa1) {
        *(f32 *)((u8 *)var_v0 + 0x18) = var_fa1;
        *(f32 *)((u8 *)var_v0 + 0x20) = (f32) -temp_fv0_2;
    }
    *(f32 *)((u8 *)var_v0 + 0xC) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) + (*(f32 *)((u8 *)var_v0 + 0x10) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) * *(f32 *)((u8 *)var_v0 + 0x14));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) * *(f32 *)((u8 *)var_v0 + 0x18));
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x5C) - *(u8 *)((u8 *)var_v0 + 0x28);
    if (temp_v1 < 0) {
        *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DB114 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB114.s")
typedef struct Game108320Vertex {
    s16 x, y, z, flag;
    u8 attributes[8];
} Game108320Vertex;

typedef struct Game108320Geometry {
    u8 pad0[0x2C];
    f32 width, height, x, y, z, directionX;
    u8 pad44[4];
    f32 directionZ;
    u8 pad4C[0x74];
    Game108320Vertex templateVertices[4];
    Game108320Vertex *buffers[4];
} Game108320Geometry;

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DB2D8 CURRENT (10) */
void *func_150DB2D8(Game108320Geometry *arg0, s32 arg1) {
    Game108320Vertex *vertices;
    Game108320Vertex *result;
    f32 offsetX;
    f32 offsetZ;
    u8 created;
    Game108320Geometry *bufferOwner;

    func_151D5D60(arg0->buffers, ((s16 *)&arg1)[1], 0x40,
                 (void **)&vertices, &created);
    result = vertices;
    if (vertices != 0) {
        if (created != 0) {
            bufferOwner = (Game108320Geometry *)((u32)arg0 + ((s16 *)&arg1)[1] * 4);
            func_10022EC0(bufferOwner->buffers[0], arg0->templateVertices, 0x40U);
            func_10022EC0(bufferOwner->buffers[0] + 4, arg0->templateVertices, 0x40U);
        }
    } else {
        return 0;
    }
    {
        offsetX = arg0->width * arg0->directionX;
        offsetZ = -arg0->width * arg0->directionZ;
        vertices[0].x = (s32)(arg0->x + offsetX);
        vertices[0].y = (s32)(arg0->y + arg0->height);
        vertices[0].z = (s32)(arg0->z + offsetZ);
        vertices[0].flag = 0;
        vertices[1].x = (s32)(arg0->x + offsetX);
        vertices[1].y = (s32)(arg0->y - arg0->height);
        vertices[1].z = (s32)(arg0->z + offsetZ);
        vertices[1].flag = 0;
        vertices[2].x = (s32)(arg0->x - offsetX);
        vertices[2].y = (s32)(arg0->y - arg0->height);
        vertices[2].z = (s32)(arg0->z - offsetZ);
        vertices[2].flag = 0;
        vertices[3].x = (s32)(arg0->x - offsetX);
        vertices[3].y = (s32)(arg0->y + arg0->height);
        vertices[3].z = (s32)(arg0->z - offsetZ);
        vertices[3].flag = 0;
        return result;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DB2D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB2D8.s")
typedef struct Game108320SpawnConfig {
    s8 field_00;
    u8 pad01;
    s16 field_02;
    s16 field_04;
    u8 pad06[2];
    s32 field_08;
    s32 field_0C;
    u8 colour[4];
    u8 pad14[0x2C];
    s32 field_40;
    u8 field_44;
    u8 field_45;
    u8 tail_pad[0x10];
} Game108320SpawnConfig;

void *func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DB518 CURRENT (14) */
void func_150DB518(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s16 arg5, u8 arg6, s32 arg7) {
    Game108320SpawnConfig config;
    u8 *result;

    if ((arg0 != 0) && (arg1 != 0) && (arg2 != 0) && (arg3 != 0) &&
        (arg4 != 0) && (arg5 != 0)) {
        config.field_00 = 0x17;
        config.field_0C = 0x243A;
        config.field_40 = 0x401;
        config.field_44 = 0xFF;
        config.field_08 = 0;
        config.field_04 = arg5;
        config.field_45 = 0xFF;
        config.colour[2] = 0xC8;
        config.colour[1] = 0xC8;
        config.colour[0] = 0xC8;
        config.colour[3] = 0xC8;
        config.field_02 = 0x401;
        result = func_1513D524((s32)&config, 0, 0xA, 0, 8, 0, 0x14,
                               arg6, arg7);
        if (result != 0) {
            *(s32 *)(result + 0x110) = arg0;
            *(s32 *)(result + 0x114) = arg1;
            *(s32 *)(result + 0x118) = arg2;
            *(s32 *)(result + 0x11C) = arg4;
            *(s32 *)(result + 0x120) = arg3;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DB518 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB518.s")
