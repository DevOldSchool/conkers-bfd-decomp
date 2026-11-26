#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_803A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 */

/* Call context: func_1505E650: unique active project prototype */
void func_1505E650(u8 *, s32, f32, f32, f32, f32, s32);

void func_15052EF0(u8 *arg0) {
    *(s8 *)((u8 *)arg0 + 0x125) = 0x64;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    func_1505E650(arg0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
extern u8 D_800CC2D0[];

void func_15052F58(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = D_800CC2D0 + (arg0 * 0x32C);
    temp_v0[0x13C] = 0;
    *(s32 *)(temp_v0 + 0x218) = 0;
    temp_v0[0x232] = arg1;
}
void *func_15033E84(void *);
void func_1506E5FC(void);
s32 func_15083568(s32, s32, f32, s32);
void func_15060F28(u8 *, s32);
void func_1506160C(u8 *, u8, u8, u8, u8);
extern s32 D_800BE9F0;
extern u8 D_800C3E78;
extern s32 D_800D1580;

typedef struct Game803A0Child {
    u8 unk_0[0x27];
    u8 unk_27;
    u8 unk_28[8];
    u8 unk_30;
    u8 unk_31[0x1D];
    u8 unk_4E;
} Game803A0Child;
typedef struct Game803A0Actor {
    s32 unk_0;
    u8 unk_4;
    u8 unk_5[0x13];
    f32 unk_18;
    u8 unk_1C[4];
    f32 unk_20;
    u8 unk_24[0x1C];
    f32 unk_40;
    u8 unk_44[0x18];
    s32 unk_5C;
    u8 unk_60[5];
    u8 unk_65;
    u8 unk_66[0x10];
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u8 unk_7C[7];
    u8 unk_83;
    u8 unk_84[5];
    u8 unk_89;
    u8 unk_8A[0x77];
    u8 unk_101;
    u8 unk_102[0x22];
    u8 unk_124;
    u8 unk_125;
    u8 unk_126[0x16];
    u8 unk_13C;
    u8 unk_13D[0x13];
    f32 unk_150;
    u8 unk_154[0x78];
    f32 unk_1CC;
    u8 unk_1D0[0x48];
    s32 unk_218;
    u8 unk_21C[0x16];
    u8 unk_232;
    u8 unk_233[6];
    u8 unk_239;
    u8 unk_23A[0xE2];
    Game803A0Child *unk_31C;
    u8 unk_320[0xC];
} Game803A0Actor;
typedef struct Game803A0Info {
    u8 unk_0[6];
    u8 unk_6;
} Game803A0Info;

void func_15052F9C(Game803A0Actor *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    Game803A0Actor *actor;
    s32 subtype;
    s32 removeOwner;
    Game803A0Info *info;

    removeOwner = 0;
    subtype = -1;
    if (arg0->unk_4 == 0x48) {
        info = func_15033E84(arg0);
        if (info != NULL) {
            subtype = info->unk_6;
        }
    }
    actor = &((Game803A0Actor *)D_800CC2D0)[arg0->unk_124];
    if (arg8 != 0 || (actor->unk_18 < arg0->unk_18 + arg1 * arg0->unk_150 && actor->unk_20 < 0.0f)) {
        arg0->unk_13C = arg0->unk_124 + 100;
        if (arg9 != 0) {
            D_800D1580 = arg9;
            func_1506E5FC();
        }
        actor->unk_1CC = actor->unk_18;
        actor->unk_76 = arg0->unk_7A;
        actor->unk_31C->unk_30 = 0;
        if (arg0->unk_0 == 0x20) {
            s32 angle;
            s32 mode;

            actor->unk_20 = 0.0f;
            mode = 2;
            arg0->unk_20 = 0.0f;
            if (arg0->unk_4 == 0x48) {
                if (subtype == 0x7A) {
                    arg0->unk_65 = arg0->unk_124 + 1;
                    arg0->unk_5C = arg2;
                    arg0->unk_101 |= arg3;
                    func_1505E650((u8 *)actor, 5, 1.0f, 0.0f, 0.0f, 0.0f, 0);
                    func_15083568((s32)actor, 0x79, 1.0f, 0);
                    removeOwner = 1;
                }
            } else {
                arg0->unk_150 = 0.75f;
                actor->unk_18 = arg0->unk_18;
                mode = 1;
                if (D_800BE9F0 == 6) {
                    mode = 0x81;
                }
            }
            actor->unk_76 = arg0->unk_7A;
            angle = actor->unk_76;
            actor->unk_78 = angle;
            actor->unk_7A = angle;
            actor->unk_40 = (f32)(s16)(angle + 0x4000) * 0.0054931640625f;
            actor->unk_31C->unk_4E = mode;
            actor->unk_83 = 0;
            actor->unk_89 = 0;
        } else {
            actor->unk_65 = D_800C3E78 + 1;
            actor->unk_5C = arg2;
            actor->unk_101 |= arg3;
            actor->unk_89 = 0;
        }
        actor->unk_125 = arg6;
        actor->unk_239 = arg7;
        actor->unk_31C->unk_27 = 0;
        arg0->unk_232 = arg5;
        arg0->unk_218 = 0;
        if (arg4 != 0) {
            func_1506160C((u8 *)actor, 1, 0, 0, 0);
            actor->unk_101 |= 0x40;
        }
    }
    if (removeOwner != 0) {
        func_15060F28((u8 *)arg0, 0);
    }
}

void func_1505327C(u8 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4) {
    u8 *source;
    u8 *actor;
    Vec3f position;
    u8 *object;

    actor = &D_800CC2D0[arg0[0x124] * 0x32C];
    if (actor[0x89] != 0 || actor[0x104] != 0) {
        return;
    }
    object = *(u8 **)(actor + 0x31C);
    if (object == NULL || object[0x6B] == 0) {
        actor[0x125] = 0xFF;
        *(f32 *)(actor + 0x20) = arg1;
        *(f32 *)(actor + 0x24) = arg2;
        actor[0x83] = 0xFF;
        actor[0x89] = 0xFF;
        *(u16 *)(actor + 0x76) = *(u16 *)(arg0 + 0x7A);
        arg0[0x232] = arg3;
        *(s32 *)(arg0 + 0x218) = 0;
        func_1505E650(actor, 0x32, 1.3f, 4.0f, 0.0f, 0.0f, 0);
        (*(u8 **)&D_800CC2D0[arg0[0x124] * 0x32C + 0x31C])[0x30] = 0x46;
        *(f32 *)(*(u8 **)&D_800CC2D0[arg0[0x124] * 0x32C + 0x31C] + 0x28) = *(f32 *)(arg0 + 0x14);
        *(f32 *)(*(u8 **)&D_800CC2D0[arg0[0x124] * 0x32C + 0x31C] + 0x2C) = *(f32 *)(arg0 + 0x1C);
        if (*(u8 **)(arg0 + 0x1D4) != NULL && arg4 != -1) {
            source = *(u8 **)(arg0 + 0x1D4) + (arg4 << 6);
            func_15043FF0(&position, (struct Game71240TransformSource *)source);
            *(f32 *)(*(u8 **)&D_800CC2D0[arg0[0x124] * 0x32C + 0x31C] + 0x28) = position.x;
            *(f32 *)(*(u8 **)&D_800CC2D0[arg0[0x124] * 0x32C + 0x31C] + 0x2C) = position.z;
        }
        (*(u8 **)&D_800CC2D0[arg0[0x124] * 0x32C + 0x31C])[0x27] = 1;
    }
}
