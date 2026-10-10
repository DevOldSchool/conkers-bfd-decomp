#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_124260.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_secondary_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F6DE4
 * - func_150F706C
 * - func_150F7310
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F739C(s32 arg0);
void func_15149368(s32 arg0);

void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_150F6DB0(void *arg0) {
    struct {
        void *sp18;
        u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3E, (s32)arg0);
}
typedef struct Game124260Copy3 {
    s32 words[3];
} Game124260Copy3;

typedef struct Game124260Spawn {
    void *owner;
    u8 channel;
    u8 pad5[3];
    void *children[2];
    u8 pad10[0x64];
    u8 active;
    u8 pad75[3];
} Game124260Spawn;

typedef struct Game124260Descriptor {
    s32 flags;
    s32 field4;
    s16 type;
    s16 duration;
    s32 fieldC;
    s32 field10;
    u8 color[4];
    u8 secondary[4];
    u8 opacity;
    u8 amount;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Game124260Copy3 vector30;
    Game124260Copy3 vector3C;
    Game124260Copy3 vector48;
    f32 field54;
    s32 field58;
    s32 field5C;
    u8 field60;
    u8 field61;
    s8 field62;
    s8 field63;
    u8 field64;
    u8 field65;
    u8 field66;
    u8 pad67;
    s16 field68;
    u8 pad6A[2];
    f32 field6C;
} Game124260Descriptor;

void *func_10022EC0(void *, const void *, u32);
void *func_15130280(void *, u8, void *, s32, u8, s32);
void *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A1BB0;
extern Game124260Copy3 D_800A5480;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F6DE4 CURRENT (1758) */
void *func_150F6DE4(void *arg0) {
    Game124260Spawn spawn;
    Game124260Descriptor descriptor;
    Game124260Spawn *target;
    void *result;
    s32 i;

    spawn.owner = arg0;
    i = 0;
    spawn.channel = *((u8 *)arg0 + 0x3B);
    do {
        spawn.children[i] = 0;
        i = (i + 1) & 0xFF;
    } while (i < 2);
    spawn.active = 0;
    result = func_15149130(300, -1, 0x43, -1, 0, 0x37, 0x78, 255, 1);
    if (result != 0) {
        target = (Game124260Spawn *)((u8 *)result + 0x28);
        func_10022EC0(target, &spawn, 0x78U);
        descriptor.type = 0x4417;
        descriptor.flags = 0x200004;
        descriptor.field4 = 0;
        descriptor.duration = 300;
        descriptor.fieldC = 0;
        descriptor.field10 = 0;
        descriptor.color[0] = 255;
        descriptor.color[1] = 255;
        descriptor.color[2] = 255;
        descriptor.color[3] = 255;
        descriptor.opacity = 255;
        descriptor.field2C = D_800A1BB0;
        descriptor.field28 = D_800A1BB0;
        descriptor.vector30 = D_800A5480;
        descriptor.vector3C = D_800A5480;
        descriptor.vector48 = D_800A5480;
        descriptor.field1E = 1;
        descriptor.field20 = 255;
        descriptor.field22 = 1;
        descriptor.field58 = 0x64C000;
        descriptor.field60 = 8;
        descriptor.field61 = 6;
        descriptor.field62 = -1;
        descriptor.field63 = -1;
        descriptor.field64 = 3;
        descriptor.field65 = 0;
        descriptor.field5C = 0;
        descriptor.field66 = 255;
        descriptor.field68 = 10;
        descriptor.amount = 100;
        descriptor.secondary[0] = 0;
        descriptor.secondary[1] = 0;
        descriptor.secondary[2] = 255;
        descriptor.secondary[3] = 255;
        descriptor.field54 = 0.0f;
        descriptor.field24 = 1.0f;
        descriptor.field6C = 20.0f;
        target->children[0] = func_15130280(&descriptor, 1, 0, 0,
            *((u8 *)result + 0xC), *((u8 *)result + 1));
        descriptor.secondary[0] = 255;
        descriptor.secondary[1] = 0;
        descriptor.secondary[2] = 0;
        descriptor.secondary[3] = 255;
        target->children[1] = func_15130280(&descriptor, 1, 0, 0,
            *((u8 *)result + 0xC), *((u8 *)result + 1));
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F6DE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F6DE4.s")
typedef struct Game124260Vector {
    f32 x, y, z;
} Game124260Vector;

typedef struct Game124260Owner {
    s32 live;
    u8 pad4[0x10];
    Game124260Vector position;
    u8 pad20[0x1B];
    u8 channel;
} Game124260Owner;

typedef struct Game124260Child {
    u8 pad0[0x40];
    Game124260Copy3 position;
    u8 pad4C[0x28];
    s8 mode;
} Game124260Child;

typedef struct Game124260Root {
    u8 pad0[0xE];
    s16 status;
    u8 pad10[0x18];
    Game124260Spawn state;
} Game124260Root;

void func_15145740(void *, void *, void *, void *, f32);
void func_15081690(void *, f32, f32, f32, f32, f32, f32, void *,
                  f32, s32, s32, s32, s32, s32, s32);
s32 func_1506196C(u8 *, s32);
void func_1502EA98(void *, s32, s32, s32, s32, s32, s32);
extern f32 D_800D9A50[3];
extern f32 D_800A1BB4, D_800A1BB8;
extern u8 D_800C35EA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F706C CURRENT (53) */
void func_150F706C(Game124260Root *arg0) {
    struct {
        Game124260Copy3 copied;
        Game124260Vector position;
    } work;
    Game124260Spawn *state;
    Game124260Owner *owner;

    owner = arg0->state.owner;
    state = &arg0->state;
    if (owner->live == 0 || owner->channel != state->channel) {
        arg0->status = -1;
        return;
    }
    if (D_800C35EA == 1) {
        if (state->children[0] != 0 && state->children[1] != 0) {
            ((Game124260Child *)state->children[0])->mode = 3;
            ((Game124260Child *)state->children[1])->mode = 3;
        }
    } else {
        work.position.x = owner->position.x;
        work.position.y = owner->position.y + 46.0f;
        work.position.z = owner->position.z;
        func_15145740(owner, D_800D9A50, 0, 0, 0.0f);
        D_800D9A50[0] *= D_800A1BB4;
        D_800D9A50[1] *= D_800A1BB4;
        D_800D9A50[2] *= D_800A1BB4;
        func_15081690(owner, work.position.x, work.position.y, work.position.z,
            D_800D9A50[0], D_800D9A50[1], D_800D9A50[2], state->pad10,
            D_800A1BB8, 0, 0, 1, -1, 0, 0);
        state->active |= 1;
        if (state->children[0] != 0 && state->children[1] != 0) {
            if (state->pad10[0x59] == 0) {
                ((Game124260Child *)state->children[1])->mode = 3;
                ((Game124260Child *)state->children[0])->mode =
                    ((Game124260Child *)state->children[1])->mode;
                return;
            }
            work.copied = *(Game124260Copy3 *)(state->pad10 + 8);
            ((Game124260Child *)state->children[1])->position = work.copied;
            ((Game124260Child *)state->children[0])->position = work.copied;
            if (state->pad10[0x59] == 1) {
                ((Game124260Child *)state->children[0])->mode = -1;
                ((Game124260Child *)state->children[1])->mode = 3;
                return;
            }
            if (func_1506196C(*(u8 **)state->pad10, 0) < 255) {
                ((Game124260Child *)state->children[0])->mode = -1;
                ((Game124260Child *)state->children[1])->mode = 3;
                return;
            }
            func_1502EA98(*(u8 **)state->pad10, 255, 0, 0, 127, 0, 16);
            ((Game124260Child *)state->children[0])->mode = 3;
            ((Game124260Child *)state->children[1])->mode = -1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F706C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F706C.s")
void func_15149514(s32, u8, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F7310 CURRENT (260) */
void func_150F7310(void *arg0, void *arg1, u8 arg2) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x3E) {
        if ((*(s32 *)temp_a2 == *(s32 *)arg1) || (*(u8 *)((u8 *)temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        func_15149514((s32) arg1, arg2, (s32) temp_a2, (s32) ((u8 *)temp_a2 + 4), (s32) arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F7310 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F7310.s")
/* Call context: func_1514EDF0: unique active project prototype */
void func_1514EDF0(s32, s32);

void func_150F739C(s32 arg0) {
    s32 var_s0;
    void *temp_a0;
    u8 *state;

    state = (u8 *)arg0;
    state += 0x28;
    var_s0 = 0;
    do {
        temp_a0 = ((void **)(state + 8))[var_s0];
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        var_s0++;
        var_s0 &= 0xFF;
    } while (var_s0 < 2);
    func_1514EDF0(arg0, *(s32 *)state);
}
void func_150F740C(s32 arg0) {
    func_150F739C(arg0);
    func_1514933C(arg0);
}
void func_150F7438(s32 arg0) {
    func_150F739C(arg0);
    func_15149368(arg0);
}
