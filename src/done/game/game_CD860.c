#include "types.h"

/*
 * Reviewed source unit: src/game/game_CD860.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_descriptor_callback_families.md
 */

void func_150A3444(s32, s16, s16, s16);
void func_151C970C(s32, void *);
void func_150A2864(u32, s32);
void func_150A2940(s32, s32, s32);
void func_150A3398(s32, u16, s32, s32, s32, s32);
extern s32 D_800D3098;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    f32 strength;
    u8 kind;
    u8 pad15[2];
    u8 mode;
    s32 value;
    s32 packed;
    s32 state;
    u8 pad24[0x10];
} GameCD860Zone;

typedef struct {
    u8 pad0[0x78];
    u8 state;
} GameCD860ActorOwner;

typedef struct {
    s32 id;
    u8 pad4[0x37];
    u8 field3B;
    u8 pad3C[0x103];
    u8 field13F;
    u8 pad140[0x1DC];
    GameCD860ActorOwner *owner;
    u8 pad320[0xC];
} GameCD860Actor;

typedef struct {
    u8 pad0[8];
    s32 value;
    s32 flag;
} GameCD860Query;

extern GameCD860Actor D_800CC2D0[];
extern u8 D_800C35EA;
extern s8 D_8008FD90;
extern s32 D_800D3840;
GameCD860Actor *func_1505EEF4(s32);
s32 func_150A29C8(s32, s32);
s32 func_150A2D84(s32, s32);
s32 func_150A2EE4(s32, s32);
s32 func_150A2FA4(s32, s32);
s32 func_150A2CA4(s32);
void func_150A3330(s32, s32 *, s32 *, s32 *, s32 *);

s32 func_150A03B0(s32 arg0, u32 arg1, void *arg2) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_v0;

    switch (arg1) {
    case 0:
        func_150A2864(arg0, 0);
        return 1;
    case 1:
        func_150A2864(arg0, 1);
        return 1;
    case 2:
        func_150A2940(arg0, *(s32 *)((u8 *)arg2 + 8), *(s32 *)((u8 *)arg2 + 0xC));
        return 1;
    case 3:
        func_150A3444(arg0, *(s16 *)((u8 *)arg2 + 0xA),
                        *(s16 *)((u8 *)arg2 + 0xE),
                        *(s16 *)((u8 *)arg2 + 0x12));
        break;
    case 4:
        func_150A3398(arg0, *(u16 *)((u8 *)arg2 + 0xA),
                        *(s32 *)((u8 *)arg2 + 0xC),
                        *(s32 *)((u8 *)arg2 + 0x10),
                        *(s32 *)((u8 *)arg2 + 0x14),
                        *(s32 *)((u8 *)arg2 + 0x18));
        break;
    case 5:
        temp_v0 = *(s32 *)((u8 *)arg2 + 8);
        if (temp_v0 == 0x3E7) {
            var_a0 = 2;
        } else {
            if (temp_v0 != 0) {
                var_v0 = 0;
            } else {
                var_v0 = 1;
            }
            var_a0 = var_v0;
        }
        func_151C970C(var_a0, (void *)(D_800D3098 + (arg0 * 0x34)));
        break;
    }
    return 0;
}
s32 func_150A04D8(s32 arg0, u32 arg1, GameCD860Query *arg2) {
    switch (arg1) {
    case 6: {
        s32 ret;
        s32 id;
        s32 result;
        s32 type;

        id = arg2->value & 0xFFFF0FFF;
        type = arg2->value & 0xF000;
        switch (type) {
        case 0x2000: {
            GameCD860Actor *actor;

            actor = func_1505EEF4(id);
            if (actor == 0) {
                return 0;
            }
            result = func_150A29C8(actor - D_800CC2D0, arg0);
        }
            break;
        case 0x9000:
            result = func_150A2D84(id, arg0);
            break;
        }
        if (result == 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        return ret;
    }
    case 8: {
        s32 a, b, c, d;

        func_150A3330(arg0, &a, &b, &c, &d);
        if (c != 0 && D_800C35EA == 0) {
            return 1;
        }
        break;
    }
    case 9: {
        s32 a, b, c, d;

        func_150A3330(arg0, &a, &b, &c, &d);
        if (c != 0 && D_800C35EA == 1) {
            return 1;
        }
        break;
    }
    case 10: {
        s32 x;
        s32 z;

        x = ((GameCD860Zone *)D_800D3098)[arg0].x;
        z = ((GameCD860Zone *)D_800D3098)[arg0].z;
        return (x << 16) | (z & 0xFFFF);
    }
    case 11:
    case 12: {
        GameCD860Actor *actor;
        s32 index;

        actor = D_800CC2D0;
        for (index = 0; index < 25; index++, actor++) {
            if (arg2->value == actor->id && func_150A29C8(index, arg0) == 0) {
                if (arg1 == 11) {
                    return actor->field13F | 0x2000;
                }
                return actor->field3B;
            }
        }
        return 0;
    }
    case 7:
        return ((GameCD860Zone *)D_800D3098)[arg0].kind;
    case 13: {
        s32 value;
        s32 id;
        s32 result;
        s32 type;
        GameCD860Actor *actor;

        id = arg2->value & 0xFFFF0FFF;
        type = arg2->value & 0xF000;
        switch (type) {
        case 0x2000:
            actor = func_1505EEF4(id);
            result = func_150A2EE4(actor - D_800CC2D0, arg0);
            break;
        case 0x9000:
            result = func_150A2FA4(id, arg0);
            break;
        }
        return result;
    }
    case 14:
        return ((GameCD860Zone *)D_800D3098)[arg0].y;
    case 15:
        if (func_150A2CA4(arg0) == -1) {
            return 0;
        }
        return 1;
    case 16:
        if (func_150A2CA4(arg0) == -1) {
            s32 index;

            for (index = 0; index < D_8008FD90; index++) {
                if (func_150A2D84(index, arg0) == 0) {
                    if (D_800D3840 == 2) {
                        return 1;
                    }
                    if (arg2->flag != 0) {
                        if (D_800CC2D0[index].owner->state != 3 &&
                            func_150A2D84(index, arg2->value & 0xFFFF0FFF) == 0) {
                            return 1;
                        }
                    } else {
                        return 1;
                    }
                }
            }
            return 0;
        }
        return 1;
    case 17:
        if (arg2->value == 0) {
            return ((GameCD860Zone *)D_800D3098)[arg0].mode;
        }
        if (arg2->value == 1) {
            return ((GameCD860Zone *)D_800D3098)[arg0].value;
        }
        if (arg2->value == 2) {
            return ((GameCD860Zone *)D_800D3098)[arg0].packed;
        }
        if (arg2->value == 3) {
            return ((GameCD860Zone *)D_800D3098)[arg0].state;
        }
        break;
    case 18:
        return ((GameCD860Zone *)D_800D3098)[arg0].strength;
    }
    return 0;
}
