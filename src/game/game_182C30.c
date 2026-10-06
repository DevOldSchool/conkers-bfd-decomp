#include "types.h"

/*
 * Reviewed source unit: src/game/game_182C30.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_indexed_controller_view_worklist.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515589C
 * - func_15155CFC
 * - func_15155FD4
 * - func_15156028
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0xE];
    s16 fieldE;
    s8 field10;
    u8 field11;
    u8 pad12[2];
    s32 field14;
    u8 pad18[0x80];
    f32 field98;
} Game182C30Effect;

s32 func_1518C900(s32); /* extern */
Game182C30Effect *func_15167A68(s32, s32, s32, s32, s32, s32); /* extern */

Game182C30Effect *func_15155780(s32 arg0, s32 arg1) {
    Game182C30Effect *effect;

    effect = func_15167A68(0x50, 0, 0xA0, 1, arg1, 1);
    if (effect == 0) {
        return effect;
    }
    effect->field10 = arg0;
    effect->field11 = 0;
    effect->field14 = 0;
    effect->field98 = 0.0f;
    func_1518C900(0xA6);
    return effect;
}
Game182C30Effect *func_15155780(s32, s32);
void *func_15155FD4(s32);
extern u8 D_800CC37D[];

void func_151557FC(s32 arg0, s32 arg1, f32 arg2) {
    Game182C30Effect *effect;

    effect = func_15155FD4(arg0);
    if (effect == 0) {
        effect = func_15155780(arg0, 0xFF);
    }
    if (effect != 0) {
        effect->field98 = arg2;
        if (D_800CC37D[arg0 * 0x32C] != 0) {
            effect->fieldE = 0;
            effect->field11 = 0;
            return;
        }
        effect->field11 = 3;
        effect->fieldE = (s16)arg1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_1515589C.s")
f32 func_15048A40(u8);
void *func_15096934(void *);
void func_15043D90(s32, f32, f32, s32, f32, f32, f32, f32, f32, f32);
extern u8 D_800BE9C0;
extern u8 D_800CC2D0[];
extern s32 D_800DBFF0;
extern s32 *D_800E03E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155CFC CURRENT (4991) */
void *func_15155CFC(void *arg0, Game182C30Effect *arg1, s32 arg2) {
    f32 angle;
    f32 height;
    u8 *actor;

    arg2 = (s16)arg2;
    if (arg1->field11 == 1 || arg1->field11 == 3) {
        actor = D_800CC2D0 + ((u8)arg1->field10 * 0x32C);
        if ((*(u8 **)(actor + 0x31C))[0x75] == 5) {
            height = 85.0f;
        } else {
            height = 0.0f;
        }
        angle = *(f32 *)(D_800DBFF0 + arg2 * 0x9A0 + 0x380);
        arg0 = func_15096934(arg0);
        func_15043D90((s32)((u8 *)arg1 + (D_800BE9C0 << 6) + 0x18),
            0.0f, angle, 0, 2.25f, 2.25f, 2.25f,
            *(f32 *)(actor + 0x14),
            (func_15048A40(*((u8 *)arg1 + 0x12)) * 15.0f) +
              (*(f32 *)(actor + 0x18) + 160.0f + height + arg1->field98),
            *(f32 *)(actor + 0x1C));
        {
            u32 *command;

            command = arg0;
            arg0 = (u8 *)arg0 + 8;
            command[0] = 0xDA380003;
            command[1] = (u32)((u8 *)arg1 + (D_800BE9C0 << 6) + 0x18);
        }
        {
            u32 *command;

            command = arg0;
            arg0 = (u8 *)arg0 + 8;
            command[0] = 0xD9FFFFFE;
            command[1] = 0;
        }
        {
            u32 *command;

            command = arg0;
            arg0 = (u8 *)arg0 + 8;
            command[0] = 0xDE000000;
            command[1] = *D_800E03E0;
        }
        {
            u32 *command;

            command = arg0;
            arg0 = (u8 *)arg0 + 8;
            command[1] = 1;
            command[0] = 0xD9FFFFFF;
        }
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155CFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155CFC.s")
extern void func_1515F10C(void *arg0);
extern void func_15169804(s32 arg0);
extern void func_1518CA04(s32 arg0);

void func_15155EF8(void *arg0) {
    void *temp_a1;

    temp_a1 = arg0;
    if (*(void **)((u8 *)temp_a1 + 0x14) != 0) {
        func_1515F10C(*(void **)((u8 *)temp_a1 + 0x14));
    }
    func_15169804((s32) temp_a1);
    func_1518CA04(0xA6);
}
/* Call context: func_15155FD4: unique active project prototype */
void * func_15155FD4(s32);
extern u8 D_800C3E78;

void func_15155F3C(void) {
    Game182C30Effect *effect;

    effect = func_15155FD4(D_800C3E78);
    if (effect != 0) {
        if (effect->field11 == 2) {
            effect->field11 = 0;
            return;
        }
        if (effect->field11 == 3) {
            effect->field11 = 2;
        }
    }
}
void *func_15155FD4(s32);                           /* extern */
extern u8 D_800C3E78;

void func_15155F90(void) {
    void *temp_v0;

    temp_v0 = func_15155FD4(D_800C3E78);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x11) == 3)) {
        *(u8 *)((u8 *)temp_v0 + 0x11) = 1U;
    }
}
typedef struct Game182C30Node {
    u8 pad_0[8];
    struct Game182C30Node *next;
    u8 pad_C[4];
    u8 field_10;
} Game182C30Node;

typedef struct {
    u8 pad_0[0x140];
    Game182C30Node *field_140;
    u8 pad_144[0x5C];
} Game182C30Block;

extern Game182C30Block D_800DCE50;
extern Game182C30Block D_800DD190;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155FD4 CURRENT (50) */
void *func_15155FD4(s32 arg0) {
    Game182C30Node *var_v1;
    Game182C30Block *var_a1;

    var_a1 = &D_800DCE50;
    do {
        var_v1 = var_a1->field_140;
        var_a1++;
        while (var_v1 != 0) {
            if (arg0 == var_v1->field_10) {
                return var_v1;
            }
            var_v1 = var_v1->next;
        }
    } while (var_a1 != &D_800DD190);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155FD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155FD4.s")
extern u8 D_800CC2D0[];
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15156028 CURRENT (1225) */
void func_15156028(u8 *arg0, s32 *arg1, u8 arg2) {
    s32 first;
    s32 second;
    u8 type;

    if (arg2 == 0) {
        first = (s32)((u32)*arg1 - (u32)D_800CC2D0) / 0x32C;
        if (first >= 0 && first < 0x19 && first == arg0[0x10]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        first = (s32)((u32)arg1[0] - (u32)D_800CC2D0) / 0x32C;
        second = (s32)((u32)arg1[1] - (u32)D_800CC2D0) / 0x32C;
        if (first >= 0 && first < 0x19 && second >= 0 && second < 0x19) {
            type = arg0[0x10];
            if (first == type) {
                arg0[0x10] = (u8)second;
                return;
            }
            if (second == type) {
                arg0[0x10] = (u8)first;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15156028 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15156028.s")
