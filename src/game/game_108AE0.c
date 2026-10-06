#include "types.h"

/*
 * Reviewed source unit: src/game/game_108AE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DB714
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150DB630(void *arg0) {
    f32 value;

    if (**(f32 *volatile *)((u8 *)arg0 + 0x120) > 255.0f) {
        *(u8 *)((u8 *)arg0 + 0x5C) = 0xFF;
    } else {
        value = **(f32 *volatile *)((u8 *)arg0 + 0x120);
        if (value < 0.0f) {
            *(u8 *)((u8 *)arg0 + 0x5C) = 0;
        } else {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u32)value;
        }
    }
    return 1;
}

typedef struct Game108AE0Vertex {
    s16 x, y, z, flag;
    u8 attributes[8];
} Game108AE0Vertex;

typedef struct Game108AE0Values {
    f32 *data[4];
} Game108AE0Values;

typedef struct Game108AE0Owner {
    u8 pad0[0xC0];
    Game108AE0Vertex template[4];
    u8 *buffers[4];
    Game108AE0Values values;
} Game108AE0Owner;

void *func_10022EC0(void *, const void *, u32);
f32 func_151423D8(u8);
void func_151D5D60(void *, s16, s32, void **, u8 *);
extern f32 D_800A0BF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DB714 CURRENT (268) */
void *func_150DB714(void *owner, s32 bufferIndex) {
    void *vertices;
    void *result;
    f32 cosine;
    s32 angle;
    f32 sine;
    f32 offsetX;
    f32 offsetZ;
    Game108AE0Values *values;
    u8 fresh;
    u8 *slot;
    void *template;

    func_151D5D60(((Game108AE0Owner *)owner)->buffers, ((s16 *)&bufferIndex)[1], 0x40, &vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            slot = (u8 *)owner + ((s16 *)&bufferIndex)[1] * 4;
            template = ((Game108AE0Owner *)owner)->template;
            func_10022EC0(*(u8 **)(slot + 0x100), template, 0x40U);
            func_10022EC0(*(u8 **)(slot + 0x100) + 0x40, template, 0x40U);
        }
    } else {
        return 0;
    }
    angle = (s32)(*(((Game108AE0Owner *)owner)->values.data[1]) * D_800A0BF0);
    sine = func_151423D8((u8)angle);
    cosine = func_151423D8((u8)(angle - 0x40));
    values = (Game108AE0Values *)((u8 *)owner + 0x110);
    offsetX = *values->data[2] * sine;
    offsetZ = -*values->data[2] * cosine;
    ((Game108AE0Vertex *)vertices)[0].x = (s32)(values->data[0][0] + offsetX);
    ((Game108AE0Vertex *)vertices)[0].y = (s32)(*values->data[3] + values->data[0][1]);
    ((Game108AE0Vertex *)vertices)[0].z = (s32)(values->data[0][2] + offsetZ);
    ((Game108AE0Vertex *)vertices)[0].flag = 0;
    ((Game108AE0Vertex *)vertices)[1].x = (s32)(values->data[0][0] + offsetX);
    ((Game108AE0Vertex *)vertices)[1].y = (s32)(values->data[0][1] - *values->data[3]);
    ((Game108AE0Vertex *)vertices)[1].z = (s32)(values->data[0][2] + offsetZ);
    ((Game108AE0Vertex *)vertices)[1].flag = 0;
    ((Game108AE0Vertex *)vertices)[2].x = (s32)(values->data[0][0] - offsetX);
    ((Game108AE0Vertex *)vertices)[2].y = (s32)(values->data[0][1] - *values->data[3]);
    ((Game108AE0Vertex *)vertices)[2].z = (s32)(values->data[0][2] - offsetZ);
    ((Game108AE0Vertex *)vertices)[2].flag = 0;
    ((Game108AE0Vertex *)vertices)[3].x = (s32)(values->data[0][0] - offsetX);
    ((Game108AE0Vertex *)vertices)[3].y = (s32)(*values->data[3] + values->data[0][1]);
    ((Game108AE0Vertex *)vertices)[3].z = (s32)(values->data[0][2] - offsetZ);
    ((Game108AE0Vertex *)vertices)[3].flag = 0;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DB714 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_108AE0/func_150DB714.s")
