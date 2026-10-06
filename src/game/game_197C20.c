#include "types.h"

/*
 * Reviewed source unit: src/game/game_197C20.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516A7B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1516A770(u8 *arg0) {
    s32 var_v1;
    s32 var_v0;
    s32 delimiter;

    var_v0 = *arg0;
    var_v1 = 1;
    delimiter = 0xBD;
    if (var_v0 != 0) {
        do {
            if (delimiter == var_v0) {
                *(u8 *)((u8 *)arg0 + 0) = 0;
                var_v1 += 1;
            }
            var_v0 = *(u8 *)((u8 *)arg0 + 1);
            arg0 += 1;
        } while (var_v0 != 0);
    }
    return var_v1;
}
/* Descriptor fields and eight-byte bank entries follow the raw loads. */
typedef struct Game197C20Descriptor {
    u32 flags;
    u8 *text;
    u8 count;
    u8 actorIndex;
    u8 fieldA;
    u8 padB[0x1B];
    u16 size;
    u8 pad28[4];
    s32 field2C;
} Game197C20Descriptor;

typedef struct Game197C20BankEntry {
    Game197C20Descriptor *descriptor;
    u32 field4;
} Game197C20BankEntry;

typedef struct Game197C20Object {
    u8 pad0[0xD];
    u8 mode;
    u8 state;
    u8 kind;
    Game197C20Descriptor *descriptor;
    u8 supplied;
    u8 active;
    u16 size;
    s16 field18;
    u8 field1A;
    u8 pad1B[4];
    u8 field1F;
    u8 field20;
    u8 pad21[3];
    u8 *data;
    f32 field28;
    u8 pad2C[0xC];
    f32 width;
    f32 height;
} Game197C20Object;

void func_150428D4(void *, s32 *, s32 *, s32 *);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
u8 *func_1516C878(void *, s32, s16);
s32 func_1516A770(u8 *);
extern f32 D_800A6CD0;
extern f32 D_800A6CD4;
extern u8 D_800CC4B3[];
extern Game197C20BankEntry *D_800DD254;
extern Game197C20BankEntry *D_800DD258;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516A7B0 CURRENT (3139) */
void *func_1516A7B0(u32 arg0, volatile s32 arg1, volatile s32 arg2, volatile s32 arg3, Game197C20Descriptor *arg4, s32 arg5) {
    struct {
        s32 baseline;
        s32 height;
        s32 width;
    } dimensions;
    register f32 measured;
    u32 flags;
    s32 index;
    s32 actorIndex;
    Game197C20Object *object;
    Game197C20Descriptor *descriptor;

    object = func_15167A68(0x51, 0, 0x74, 0, arg5, 2);
    if (object != 0) {
        descriptor = arg4;
        if (arg4 == 0) {
            if (arg0 >= 0x100U) {
                descriptor = D_800DD258[arg0 - 0x100].descriptor;
            } else {
                descriptor = D_800DD254[arg0].descriptor;
            }
        }
        if (arg4 != 0) {
            object->mode = 2;
        } else if (arg0 >= 0x100U) {
            object->mode = 1;
        } else {
            object->mode = 0;
        }
        flags = descriptor->flags;
        descriptor->actorIndex = arg1;
        descriptor->fieldA = arg2;
        descriptor->field2C = arg3;
        object->kind = flags & 0xF;
        object->descriptor = descriptor;
        object->active = 1;
        object->field1F = 0;
        if (arg4 != 0) {
            object->supplied = 1;
            object->size = arg4->size;
        } else {
            object->supplied = 0;
            object->size = (s32) descriptor->size >> 1;
        }
        object->field18 = 0;
        object->field1A = 0;
        object->field28 = 0.0f;
        object->width = 0.0f;
        object->height = 0.0f;
        if (object->mode == 2) {
            descriptor->count = func_1516A770(descriptor->text);
        }
        index = 0;
        if (descriptor->count > 0) {
            do {
                func_150428D4(func_1516C878(descriptor, index, object->mode), &dimensions.width, &dimensions.height, &dimensions.baseline);
                measured = (f32) dimensions.width;
                if (object->width < measured) {
                    object->width = measured;
                }
                measured = (f32) dimensions.height;
                if (object->height < measured) {
                    object->height = measured;
                }
                index++;
            } while (index < descriptor->count);
        }
        if (descriptor->flags & 2) {
            measured = 25.0f;
        } else {
            measured = 18.0f;
        }
        object->width = (object->width + measured * 0.5f) * D_800A6CD0;
        object->height = (object->height + measured) * D_800A6CD4;
        object->data = func_1516C878(descriptor, 0, object->mode);
        object->field20 = 0;
        actorIndex = descriptor->actorIndex;
        descriptor->flags &= ~0x7000;
        D_800CC4B3[actorIndex * 0x32C] = 1;
        object->state = 0;
    }
    return object;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516A7B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516A7B0.s")
