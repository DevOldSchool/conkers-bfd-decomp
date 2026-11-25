#include "types.h"

/*
 * Reviewed source unit: src/game/game_A9820.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 */

typedef struct GameA9820Nested {
    u8 pad0[0x4];
    s32 field_4;
    u8 pad8[0xF];
    u8 field_17;
    u8 pad18[0x36];
    u8 field_4E;
    u8 field_4F;
    u8 pad50[0xC4];
    s16 field_114;
    s16 field_116;
    s16 field_118;
    u8 pad11A[0x7D];
    u8 field_197;
    u8 pad198[0xE];
    u16 field_1A6;
    u8 pad1A8[0xB];
    u8 field_1B3;
} GameA9820Nested;

typedef struct GameA9820Owner {
    u8 pad0[0x73C];
    s16 field_73C;
    u8 pad73E[0x21E];
    f32 field_95C;
    f32 field_960;
} GameA9820Owner;

typedef struct GameA9820Actor {
    s32 field_0;
    u8 field_4;
    u8 field_5;
    u8 pad6[0x36];
    f32 field_3C;
    u8 pad40[0x6D];
    u8 field_AD;
    u8 padAE[0x36];
    s16 field_E4;
    s16 field_E6;
    u8 padE8[0x54];
    u8 field_13C;
    u8 pad13D[0xF];
    f32 field_14C;
    f32 field_150;
    u8 pad154[0x1C4];
    GameA9820Owner *owner;
    GameA9820Nested *nested;
    u8 pad320[0xC];
} GameA9820Actor;

extern s8 D_8008FD8C;
extern GameA9820Actor D_800CC2D0[];
extern u8 D_800BE616;
/*
 * func_1507C3E0 had debug output in development builds. It sits behind the
 * constant `debug` local, so IDO keeps it through register allocation and
 * then deletes it. What survives is the saved ra, the homed a1-a3, the
 * argument area, the spilled debugValue store and the branch after the
 * scaled block. The declarations below stand in for that debug code; the
 * ROM does not record its real names or arguments.
 */
extern f32 gDebugFloats[8];
f32 debugReadFloat(void);
void debugPrintFloats(f32, f32, f32, f32);
void debugPrintPointers(void *, void *, void *);

void func_1507C3E0(GameA9820Actor *, s16 *, s16 *, s16 *);

void func_1507C370(void) {
    GameA9820Actor *actor;
    GameA9820Nested *nested;
    s32 index;

    actor = D_800CC2D0;
    index = 0;
    if (D_8008FD8C > 0) {
        do {
            nested = actor->nested;
            if (nested != 0) {
                func_1507C3E0(actor, &nested->field_114, &nested->field_116,
                              &nested->field_118);
            }
            index++;
            actor++;
        } while (index < D_8008FD8C);
    }
}
void func_1507C3E0(GameA9820Actor *arg0, s16 *arg1, s16 *arg2, s16 *arg3) {
    f32 height;
    f32 width;
    f32 depth;
    GameA9820Nested *nested;
    GameA9820Owner *owner;
    s32 scaled;
    s32 debug;
    s32 pad80;
    f32 e4, e6;
    s32 pad74;
    s32 pad70;
    s32 pad6C;
    s32 pad68;
    f32 debugValue;
    s32 pad60;
    s32 pad5C;
    s32 pad58;
    s32 pad54;
    s32 pad50;
    s32 pad4C;
    s32 pad48;
    s32 pad44;
    f32 stepX, stepY, stepZ;
    f32 z0, z1, z2, z3, z4, z5;

    debug = 0;
    scaled = 1;
    debugValue = 0.0f;
    if (arg0->field_0 == 0) {
        depth = 60.0f;
        width = 60.0f;
        height = 180.0f;
    } else if (arg0->field_0 == 0x2D) {
        owner = arg0->owner;
        e6 = owner->field_960;
        e4 = owner->field_95C;
        height = e6;
        depth = e4;
        width = depth;
    } else if (arg0->field_0 == 4) {
        height = arg0->field_E6 * 6.0f;
        depth = arg0->field_E4 * 3.0f;
        width = depth;
    } else if (arg0->field_0 == 0x2C) {
        depth = 80.0f;
        width = 80.0f;
        height = 160.0f;
    } else if (arg0->field_5 == 5) {
        height = 2.0f * arg0->field_E6;
        depth = arg0->field_E4;
        width = depth;
    } else {
        switch (arg0->field_4) {
        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x3B:
        case 0x75:
        case 0x80:
        case 0x82:
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
            nested = arg0->nested;
            if (nested != NULL && nested->field_4 != 0) {
                depth = 60.0f;
                height = 80.0f;
                width = depth;
            } else if (nested != NULL && nested->field_17 != 0) {
                depth = 70.0f;
                height = 300.0f;
                width = depth;
            } else if (arg0->field_AD != 0) {
                height = 180.0f;
                width = 90;
                depth = 90.0f;
            } else {
                width = 60.0f;
                depth = 60.0f;
                height = 180.0f;
                if (nested != NULL) {
                    owner = arg0->owner;
                    if ((owner != NULL && owner->field_73C != 0) || nested->field_197 != 0 ||
                        nested->field_1B3 != 0) {
                        width *= 2.0f;
                        depth *= 2.0f;
                    }
                    height += nested->field_1A6;
                }
            }
            if (nested != NULL && (nested->field_4E & 0xF) == 1 && nested->field_4F == 0 &&
                arg0->field_3C < 40.0f) {
                depth = 110.0f;
                height = 500.0f;
                width = depth;
            }
            break;
        case 0x25:
        case 0x2E:
            height = 70.0f;
            width = 90;
            depth = 90.0f;
            break;
        case 0x36:
            height = 257.0f;
            width = 90;
            depth = 90.0f;
            break;
        case 0x9A:
            height = 60.0f;
            depth = 45.0f;
            scaled = 0;
            width = depth;
            break;
        case 0xAC:
            depth = 30.0f;
            height = 90.0f;
            scaled = 0;
            width = depth;
            break;
        case 0x89:
        case 0xBA:
            height = 60.0f;
            depth = 30.0f;
            scaled = 0;
            width = depth;
            break;
        case 0x53:
            if (D_800BE616 != 0) {
                depth = 150.0f;
                height = 300.0f;
                width = depth;
            } else {
                height = 250.0f;
                width = 90;
                depth = 90.0f;
            }
            break;
        default:
            scaled = 0;
            height = 2.0f * arg0->field_E6;
            depth = arg0->field_E4;
            width = depth;
            break;
        }
        if (arg0->field_13C >= 101 && D_800CC2D0[arg0->field_13C - 100].field_4 == 0x13) {
            depth += 120.0f * arg0->field_14C;
            height += 100.0f * arg0->field_150;
        }
        while (1) {
            if (!debug) {
                break;
            }
            gDebugFloats[6] = stepX + stepY + stepZ;
            stepX = gDebugFloats[7];
            stepY = stepX * 4.0f;
            stepZ = stepY;
        }
        if (scaled) {
            height *= arg0->field_150;
            width *= arg0->field_14C;
            depth *= arg0->field_14C;
        }

    }
    if (debug) {
        debugValue += debugReadFloat();
    }
    switch (debug) {
    case 1:
        z0 = gDebugFloats[0];
        z1 = gDebugFloats[1];
        z2 = gDebugFloats[2];
        z3 = gDebugFloats[3];
        z4 = gDebugFloats[4];
        z5 = gDebugFloats[5];
        debugPrintFloats(z0 + z1 + z2 + z3 + z4 + z5, height, width, depth);
        debugPrintPointers(arg0, NULL, NULL);
        debugPrintPointers(arg1, arg2, arg3);
        debugPrintPointers(arg0, NULL, NULL);
        debugPrintPointers(arg1, arg2, arg3);
        debugPrintPointers(arg0, NULL, NULL);
        debugPrintPointers(arg1, arg2, arg3);
        debugPrintPointers(arg0, NULL, NULL);
        debugPrintPointers(arg1, arg2, arg3);
        debugPrintPointers(arg0, NULL, NULL);
        debugPrintPointers(arg1, arg2, arg3);
        debugPrintFloats(debugValue, 0.0f, 0.0f, 0.0f);
        height = debugReadFloat();
        break;
    }
    if (arg1 != NULL) {
        *arg1 = height;
    }
    if (arg2 != NULL) {
        *arg2 = width;
    }
    if (arg3 != NULL) {
        *arg3 = depth;
    }
}
