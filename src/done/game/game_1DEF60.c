#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1DEF60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 */

void *func_10022EC0(void *, const void *, u32);
typedef struct Game1DEF60B1AB0Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game1DEF60B1AB0Packet;

void func_151B1AB0(void *arg0) {
    u8 *temp_v0;
    Game1DEF60B1AB0Packet packet;

    if ((s32)arg0 != 0) {
        packet.owner = arg0;
        packet.type = *(u8 *)((u8 *)packet.owner + 0x3B);
        packet.value = 0.0f;
        temp_v0 = func_151491F4(0x3C, -1, 0x15, 1, 0x11, 0xC, 0xFF, 1);
        if (temp_v0 != 0) {
            func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
        }
    }
}
typedef struct Game1DEF60Owner {
    u8 pad00[0x7A];
    u16 field7A;
    u8 pad7C[0x158];
    s32 field1D4;
} Game1DEF60Owner;

typedef struct Game1DEF60Emitter {
    u8 pad00;
    u8 field01;
    u8 pad02[0xA];
    u8 field0C;
    u8 pad0D[0x1B];
    struct Game1DEF60Link {
        Game1DEF60Owner *owner;
        f32 field04;
        f32 accum;
    } link;
} Game1DEF60Emitter;

/* The spawn helper copies the entire 0x70-byte descriptor. */
typedef struct Game1DEF60Billboard {
    s32 flags, field04;
    s16 kind, lifetime;
    s32 field0C, field10;
    u8 color[10];
    s16 field1E, field20, field22;
    f32 size, width, height;
    f32 position[3], velocity[3];
    f32 field48, field4C, field50, field54;
    u32 flags58;
    s32 field5C;
    s8 modes[4];
    u8 pad64[0xC];
} Game1DEF60Billboard;

f32 func_150ADA68(void);
void *func_15130374(void *, u8, s32, u8, s32);
void func_15143134(f32 *, f32 *, s32);
extern f32 D_800BE9A4;
extern Vec3f D_8008FAD0;
extern Vec3f D_8008FADC;

void func_151B1B34(Game1DEF60Emitter *arg0) {
    struct Game1DEF60Link *link;
    Game1DEF60Billboard descriptor;
    u8 *result;
    f32 spin;
    Vec3f left;
    Vec3f right;

    link = &arg0->link;
    link->accum += (697.0f + func_150ADA68() * 342.0f) * 0.001f * D_800BE9A4;
    if (link->accum > 1.0f) {
        if (link->owner->field1D4 != 0) {
            {
                Vec3f leftOffset = D_8008FAD0;

                func_15143134(&leftOffset.x, &left.x, link->owner->field1D4 + 0x800);
            }
            {
                Vec3f rightOffset = D_8008FADC;

                func_15143134(&rightOffset.x, &right.x, link->owner->field1D4 + 0x640);
            }
            descriptor.color[9] = 0x29;
            descriptor.kind = 0xE03;
            descriptor.flags = 0x200005;
            descriptor.color[4] = 0xB0;
            descriptor.color[5] = 0xA0;
            descriptor.color[6] = 0x2A;
            descriptor.color[0] = 0x40;
            descriptor.color[1] = 0xB;
            descriptor.color[2] = 0x6A;
            descriptor.field04 = 0;
            descriptor.field0C = 0;
            descriptor.field10 = 0;
            descriptor.color[3] = 0xFF;
            descriptor.color[8] = 0xFF;
            descriptor.modes[0] = 3;
            descriptor.modes[1] = 3;
            descriptor.field54 = 0.0f;
            descriptor.flags58 = 0xE05;
            descriptor.modes[2] = 0xA;
            descriptor.modes[3] = -1;
            descriptor.field1E = 0x1E;
            descriptor.field20 = 8;
            descriptor.field22 = 0x32;
            descriptor.size = 1.0270001f;
            spin = 0.924f;
            do {
                descriptor.lifetime = func_150ADA20() % 41U + 0x1E;
                descriptor.color[7] = func_150ADA20() % 156U + 0x64;
                descriptor.width = descriptor.height = func_150ADA68() * 104.0f + 199.0f;
                {
                    f32 *origin;
                    u8 heading;
                    s16 yaw;

                    origin = (func_150ADA20() & 1) ? &left.x : &right.x;
                    heading = (link->owner->field7A >> 8) + 0x40;
                    yaw = func_150ADA20() % 100U + heading - 0x31;
                    func_15143874(yaw, 36.0f, &descriptor.position[0], &descriptor.position[2]);
                    descriptor.position[1] = 0.0f;
                    descriptor.position[0] += origin[0];
                    descriptor.position[1] = origin[1];
                    descriptor.position[2] += origin[2];
                    func_15143874(yaw, (func_150ADA68() * 1497.0f + 995.0f) * 0.01f,
                                  &descriptor.field48, &descriptor.field50);
                    descriptor.field4C = 0.0f;
                }
                descriptor.flags58 &= ~0xC0;
                if (func_150ADA20() & 1) {
                    descriptor.flags58 |= 0x40;
                }
                if (func_150ADA20() & 1) {
                    descriptor.flags58 |= 0x80;
                }
                result = func_15130374(&descriptor, 1, 4, arg0->field0C, arg0->field01);
                if (result != NULL) {
                    func_10022EC0(result + 0xA8, &spin, 4);
                }
                link->accum -= 1.0f;
            } while (link->accum > 1.0f);
        } else {
            while (link->accum > 1.0f) {
                link->accum -= 1.0f;
            }
        }
    }
}

void func_151B1FAC(void *arg0, void *arg1, u8 arg2) {
    s32 temp_t6;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (temp_t6 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    }
}
