#include "types.h"

/*
 * Reviewed source unit: src/game/game_127060.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F9BB0
 * - func_150FA1B8
 * - func_150FA468
 * - func_150FA520
 * - func_150FAAEC
 * - func_150FAE18
 * - func_150FB188
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game127060State {
    u8 pad0[0x54];
    f32 field54;
    f32 field58;
    f32 field5C;
} Game127060State;

typedef struct Game127060Transform {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
} Game127060Transform;

#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150F9BB0.s")
typedef struct { f32 x, y, z; } Game127060Vector;
typedef struct {
    u8 pad0[0x48];
    f32 width, height;
    u8 pad50[8];
    u8 flags;
} Game127060FirstParams;
typedef struct {
    u8 pad0[0x34];
    Game127060Vector position, direction;
    u8 pad4C[0xC4];
    Game127060FirstParams params;
} Game127060First;
typedef struct { u8 pad0[4]; f32 size; } Game127060SecondParams;
typedef struct {
    u8 pad0[0x34];
    Game127060Vector position, direction;
    u8 pad4C[0xC];
    volatile u32 flags;
    u8 pad5C[0x114];
    Game127060SecondParams params;
} Game127060Second;
typedef struct {
    s32 active;
    u8 pad4[0x37];
    u8 generation;
    u8 pad3C[0x198];
    u8 *transform;
} Game127060Owner;
typedef struct {
    Game127060Owner *owner;
    u8 generation;
    u8 pad5[3];
    Game127060First *first[2];
    Game127060Second *second[2];
} Game127060Group;
typedef struct {
    u8 pad0[0xE];
    s16 age;
    u8 pad10[0x18];
    Game127060Group group;
} Game127060Effect;

void func_15145EA4(s32 *, s32 *, s32, s32);
extern Game127060Vector D_800A1CCC, D_800A1CD8, D_800A1CE4, D_800A1CF0;
extern f32 D_800A1D94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FA1B8 CURRENT (2446) */
void func_150FA1B8(Game127060Effect *effect) {
    Game127060Vector first[2];
    Game127060Vector second[2];
    Game127060Vector *inputs[4];
    Game127060Vector *outputs[4];
    Game127060Group *group;
    Game127060Owner *owner;
    void *object;
    s32 i;
    u32 next;
    Game127060Group *cursor;
    Game127060FirstParams *firstParams;
    Game127060SecondParams *secondParams;
    f32 width, height, size;

    owner = effect->group.owner;
    group = &effect->group;
    if (!owner->active || owner->generation != group->generation) {
        effect->age = -1;
        return;
    }
    if (owner->transform) {
        inputs[0] = &D_800A1CCC;
        inputs[1] = &D_800A1CD8;
        inputs[2] = &D_800A1CE4;
        inputs[3] = &D_800A1CF0;
        outputs[0] = &first[0];
        outputs[1] = &first[1];
        outputs[2] = &second[0];
        outputs[3] = &second[1];
        func_15145EA4((s32 *)inputs, (s32 *)outputs, (s32)(owner->transform + 0x40), 4);
        i = 0;
        do {
            cursor = (Game127060Group *)((u8 *)group + i * 4);
            object = cursor->first[0];
            if (object) {
                ((Game127060First *)object)->params.flags |= 1;
                ((Game127060First *)object)->position = first[i];
                ((Game127060First *)object)->direction = second[i];
            }
            object = cursor->second[0];
            if (object) {
                next = ((Game127060Second *)object)->flags | 2;
                ((Game127060Second *)object)->flags = next;
                ((Game127060Second *)object)->flags = next & ~4;
                ((Game127060Second *)object)->position = first[i];
                ((Game127060Second *)object)->direction = second[i];
            }
            next = (i + 1) & 0xFF;
            i = next;
        } while (i < 2);
    } else {
        i = 0;
        do {
            cursor = (Game127060Group *)((u8 *)group + i * 4);
            object = cursor->first[0];
            if (object) {
                firstParams = &((Game127060First *)object)->params;
                firstParams->flags &= ~1;
            }
            object = cursor->second[0];
            if (object) ((Game127060Second *)object)->flags &= ~2;
            next = (i + 1) & 0xFF;
            i = next;
        } while (i < 2);
    }
    height = 15.0f;
    width = 6.0f;
    size = D_800A1D94;
    i = 0;
    do {
        cursor = (Game127060Group *)((u8 *)group + i * 4);
        object = cursor->first[0];
        if (object) {
            firstParams = &((Game127060First *)object)->params;
            if (effect->age < 10) {
                firstParams->width = 0.0f;
                firstParams->height = 0.0f;
            } else {
                firstParams->width = width;
                firstParams->height = height;
            }
        }
        object = cursor->second[0];
        if (object) {
            secondParams = &((Game127060Second *)object)->params;
            if (effect->age < 10) secondParams->size = 0.0f;
            else secondParams->size = size;
        }
        next = (i + 1) & 0xFF;
        i = next;
    } while (i < 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FA1B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA1B8.s")
void func_1515D4D4(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FA468 CURRENT (2894) */
void func_150FA468(void *arg0, s32 arg1, s32 arg2) {
    switch ((u8)arg2) {
    case 0x4C:
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        func_1515D4D4(0, 0, 0, 0xFF);
        break;
    case 0x4D:
        *(s8 *)((u8 *)arg0 + 0x11) = 0x1E;
        break;
    case 0x4E:
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        break;
    case 0x4F:
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        func_1515D4D4(0xFF, 0xFF, 0xFF, 0xFF);
        break;
    default:
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FA468 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA520.s")
void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_80088B60;
extern s32 D_800D3098;

void func_150FAA40(u8 arg0, s32 arg1) {
    struct { s32 first; s32 second; f32 value; } packet;
    s32 temp_v0;

    if (D_80088B60 == 0) {
        packet.first = D_800D3098 + 0x71C;
        packet.second = D_800D3098 + 0x6E8;
        packet.value = 0.0f;
        temp_v0 = func_15149130(0x12C, -1, 0x57, -1, 0, 0x46, 0xC, (s32)arg0, arg1);
        if (temp_v0 != 0) {
            D_80088B60 = 1;
        }
        if (temp_v0 != 0) {
            func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0xCU);
        }
    }
}
typedef struct Game127060Emission {
    s32 first;
    s32 second;
    f32 count;
} Game127060Emission;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1514470C(s32, void *);
void func_150F4570(f32 *, f32 *, u8, f32, f32, f32, s32, s32, s32, s32);
extern u8 D_80088B2C;
extern u8 *D_80088B30;
extern f32 *D_80088B34;
extern f32 D_800A1DB8;
extern f32 D_800A1DBC;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FAAEC CURRENT (2754) */
void func_150FAAEC(u8 *arg0) {
    f32 first[3];
    f32 second[3];
    f32 duration;
    f32 random;
    f32 range;
    s32 index;
    Game127060Emission *emission;

    emission = (Game127060Emission *)(arg0 + 0x28);
    emission->count += (D_800A1DB8 + func_150ADA68() * D_800A1DBC) * D_800BE9A4;
    if (emission->count > 1.0f) {
        range = 1.0f;
        do {
            func_1514470C(emission->first, first);
            func_1514470C(emission->second, second);
            index = (func_150ADA20() % D_80088B2C) & 0xFF;
            duration = func_150ADA68() * 25.0f + 30.0f;
            random = func_150ADA68();
            func_150F4570(first, second, D_80088B30[index * 2 + 1], duration,
                1.0f / duration, (random * range + range) * D_80088B34[index],
                1, func_150ADA20() % 3U + 750, arg0[0xC], arg0[1]);
            emission->count -= 1.0f;
        } while (emission->count > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FAAEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAAEC.s")

extern void func_1516972C(s32 arg0);

void func_150FACE4(s32 arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        func_1516972C(arg0);
    }
}
void func_1515F170(s32, s32);
void func_151494E0(s32, s32);
extern s32 D_800D3098;

void func_150FAD28(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0(D_800D3098 + 0x514, 0x30);
    func_151494E0(0, 0x4D);
}
void func_150FAD78(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0(D_800D3098 + 0x514, 0x31);
    func_151494E0(0, 0x4C);
}
void func_150FADC8(void *arg0, s32 arg1, u8 arg2) {

    if (arg2 == 0x53) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
        return;
    }
    if (arg2 == 0x54) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAE18.s")
void func_15157DEC(Game127060State *, Game127060Transform *);
extern f32 D_800A1DC0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FB188 CURRENT (654) */
s32 func_150FB188(Game127060State *arg0) {
    Game127060Transform transform;

    arg0->field5C = 0.0f;
    arg0->field54 = -95.0f;
    arg0->field58 = -80.0f;
    transform.field0 = 0.0f;
    transform.field4 = 0.0f;
    transform.field8 = 0.0f;
    transform.fieldC = D_800A1DC0;
    transform.field10 = D_800A1DC0;
    func_15157DEC(arg0, &transform);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FB188 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FB188.s")

void func_15157F80(s32, s32, s32, s32, s32);
s32 func_151D710C(s32, s32, s32, s32, s32);

void func_150FB1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15157F80(func_151D710C(arg0, arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}
