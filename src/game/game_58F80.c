#include "types.h"

/*
 * Reviewed source unit: src/game/game_58F80.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502BAD0
 * - func_1502BD84
 * - func_1502BEE4
 * - func_1502C1A4
 * - func_1502C408
 * - func_1502C608
 * - func_1502C6E8
 * - func_1502C974
 * - func_1502CCFC
 * - func_1502D54C
 * - func_1502D630
 * - func_1502D824
 * - func_1502DB84
 * - func_1502DF38
 * - func_1502E4C4
 * - func_1502EA0C
 * - func_1502EAFC
 * - func_1502EC34
 * - func_1502EE8C
 * - func_1502EEF4
 * - func_1502F01C
 * - func_1502F264
 * - func_1502F3C8
 * - func_1502F490
 * - func_1502F9FC
 * - func_1502FBE8
 * - func_1502FD70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BAD0.s")
typedef struct Game58F80BD84Actor {
    s32 field0;
    u8 field4;
    u8 field5;
    u8 pad6[0x9E];
    u8 fieldA4;
    u8 padA5[0x53];
    s32 fieldF8;
    u8 padFC[0x38];
    u8 field134;
    u8 field135;
    u8 pad136[0x93];
    u8 field1C9;
    u8 pad1CA[0xA];
    s32 field1D4;
    u8 pad1D8[0x24];
    s8 field1FC;
    u8 pad1FD[0x63];
    s32 field260;
} Game58F80BD84Actor;

void func_150345E4(s32);
void func_1502DF38(s32, s32);
void func_1502C608(s32);
void func_1502E4C4(s32);
void func_1502F264(s32);
void func_1502FBE8(void *);
void func_1503A08C(void *);
void func_1503A830(void *);
void func_1503DF48(s32);
void func_150A4B04(void *);
void func_1517AD00(u8, u8, s32);
void func_1502EEF4(void);
void func_1502EAFC(void *);
extern u8 D_800C666F[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502BD84 CURRENT (620) */
void func_1502BD84(Game58F80BD84Actor *arg0, volatile s32 arg1) {
    s32 type;

    type = arg0->field5;
    arg0->field1D4 = 0;
    if (type == 5) {
        func_1502DF38(arg1, 1);
        return;
    }
    if (arg0->field4 != 0xFF && type != 3) {
        if (type == 2) {
            func_1502C608(arg1);
            return;
        }
        if (arg0->field1C9 != 0) {
            func_1502FBE8(arg0);
        }
        func_1502E4C4(arg1);
        func_1502DF38(arg1, 0);
        func_1503A08C(arg0);
        if (arg0->field1D4 == 0) {
            arg0->field1FC = 2;
        } else {
            func_150345E4(arg1);
            func_1503A830(arg0);
        }
        if (D_800C666F[arg1 * 0x10] != 0) {
            func_1503DF48(arg1);
        }
        if (arg0->field0 != 0) {
            func_1502EEF4();
            func_1502F264(arg1);
            if (arg0->fieldA4 != 0) {
                func_1502EAFC(arg0);
            }
            if (arg0->fieldF8 & 0x4000) {
                func_150A4B04(arg0);
            }
            if (arg0->field260 != 0) {
                func_1517AD00(arg0->field134, arg0->field135, arg1);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502BD84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BD84.s")
typedef struct Game58F80Actor {
    s32 active;
    u8 model;
    u8 kind;
    u8 pad6[0xE];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    u8 pad20[0x45];
    u8 owner65;
    u8 flags66;
    u8 pad67[0x21];
    u8 field88;
    u8 pad89[0x43];
    s16 fieldCC;
    u8 padCE[0x55];
    u8 field123;
    u8 pad124[0x3C];
    u16 field160;
    u8 pad162[0x1E];
    f32 field_180;
    u8 pad184[0x1A];
    u16 field_19E;
    u8 pad1A0[0xD4];
    u8 field_274;
    u8 pad275[0x5F];
    u8 *effect2D4;
    u8 pad2D8[0x54];
} Game58F80Actor;

extern u8 D_800CC2D0;
extern u8 D_800D121C;
extern u8 D_800BEAC0;
extern s8 D_800C3E90;
extern s8 D_800C3E70;
extern s32 D_800C3E74;
void func_100226F0(void *, s32);
void func_1503F964(void);
void func_1502BD84(Game58F80BD84Actor *, s32);
void func_1502F3C8(void);
void func_1502F948(void *);
void func_15030468(void);
void func_1507C22C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502BEE4 CURRENT (4512) */
void func_1502BEE4(void) {
    u8 ordered[25];
    u8 depth[25];
    s32 count;
    s32 maximum;
    s32 i;
    s32 j;
    u8 flag;
    Game58F80Actor *actor;
    Game58F80Actor *owner;

    func_1503F964();
    D_800C3E90 = 0;
    D_800C3E74 = 0;
    maximum = 0;
    actor = (Game58F80Actor *)&D_800CC2D0;
    do {
        flag = actor->field_274;
        actor++;
        if (flag != 0) {
            D_800C3E74 |= 1 << (flag + 31);
        }
    } while (actor < (Game58F80Actor *)&D_800D121C);
    func_100226F0(depth, 25);
    actor = (Game58F80Actor *)&D_800CC2D0;
    for (i = 0; i < 25; i++, actor++) {
        if (actor->active != 0) {
            if (actor->owner65 != 0) {
                owner = actor;
                depth[i] = 0;
                while (owner->owner65 != 0) {
                    depth[i]++;
                    owner = (Game58F80Actor *)&D_800CC2D0 + owner->owner65 - 1;
                }
                if (maximum < depth[i]) {
                    maximum = depth[i];
                }
            } else {
                func_1502BD84((Game58F80BD84Actor *)actor, i);
            }
        }
    }
    count = 0;
    if (maximum != 0) {
        for (i = 1; i <= maximum; i++) {
            for (j = 0; j < 25; j++) {
                if (i == depth[j]) {
                    ordered[count++] = j;
                }
            }
        }
        for (i = 0; i < count; i++) {
            j = ordered[i];
            func_1502BD84((Game58F80BD84Actor *)((Game58F80Actor *)&D_800CC2D0 + j), j);
        }
    }
    func_1502F3C8();
    actor = (Game58F80Actor *)&D_800CC2D0;
    do {
        if (actor->active != 0) {
            func_1502F948(actor);
        }
        actor++;
    } while (actor != (Game58F80Actor *)&D_800D121C);
    func_15030468();
    if (D_800BEAC0 == 0) {
        func_1507C22C(0);
    }
    D_800C3E70 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502BEE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BEE4.s")



extern u8 D_800CC2D0;
extern u8 D_800D121C;
extern u8 D_800C3638;
extern u8 D_800C3656;
extern s32 D_80082FA0;
s32 func_150229E4(void *);
s32 func_1506196C(u8 *, s32);
void *func_1510D970(s32, s32, s32, s32, s32);
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502C1A4 CURRENT (320) */
void func_1502C1A4(void) {
    s32 kind;
    s32 index;
    s32 needed;
    s32 flag;
    u8 *effect;
    Game58F80Actor *actor;

    actor = (Game58F80Actor *)&D_800CC2D0;
    do {
        flag = actor->active;
        if (flag != 0) {
            flag = actor->model;
            needed = 0;
            if (actor->kind != 3 && flag != 0xFF &&
                actor->field123 == 0 && (actor->flags66 & 0x10) != 0x10 &&
                actor->field160 != 0 && actor->owner65 == 0 &&
                (D_800C3638 == 0 || D_800C3656 != 0 || func_150229E4(actor) != 0) &&
                (actor->field88 == 0 || actor->fieldCC >= -150)) {
                index = 0;
                if (D_80082FA0 >= 0) {
                    do {
                        if (func_1506196C((u8 *)actor, index) != 0) {
                            needed = 1;
                        }
                        index++;
                    } while (D_80082FA0 >= index);
                }
            }
            if (needed != 0) {
                if (actor->effect2D4 == 0) {
                    if (actor->model == 0x4D) {
                        kind = 2;
                        flag = 1;
                    } else {
                        kind = 0;
                        flag = 0;
                    }
                    effect = func_1510D970(0, (s32)actor, kind, 0, flag);
                    actor->effect2D4 = effect;
                }
            } else {
                effect = actor->effect2D4;
                if (effect != 0) {
                    func_1516972C(effect);
                    actor->effect2D4 = 0;
                }
            }
        }
        actor++;
    } while (actor != (Game58F80Actor *)&D_800D121C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502C1A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C1A4.s")
extern u8 D_800BE9C0;
extern s16 D_800C3E7A;
extern void *D_800C3E80[];
void func_150A9984(void *, u16);
typedef struct {
    s32 field_0;
} Game58F80Word;
extern Game58F80Word D_800C3E88;
extern s32 D_800C3E8C;

void func_1502C380(void) {
    Game58F80Word *destination;

    destination = &D_800C3E88;
    destination->field_0 = (s32)D_800C3E80[D_800BE9C0];
    D_800C3E8C = destination->field_0;
    D_800C3E7A = 0;
}
extern u8 D_800CC406[];

u8 func_1502C3BC(s32 arg0) {
    u8 var_v1;

    var_v1 = D_800CC406[arg0 * 0x32C];
    if ((s32)var_v1 >= 0x46) {
        var_v1 = 0xB;
    }
    return var_v1;
}
typedef struct Game58F80Sprite {
    s16 x, y, z;
    s16 width, height;
    u8 alpha, green, blue, mode;
    void *output;
} Game58F80Sprite;
s32 func_15094F70(void *, void *, s32, void *, s32, s32, s32, s32, s32);
void *func_15095760(void *, s16 *);
extern u8 D_800873D0[];
extern u8 D_80087408[];
extern u8 *D_8008CA4C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502C408 CURRENT (5531) */
void *func_1502C408(void *arg0, s32 arg1) {
    Game58F80Sprite sprite;
    s32 width;
    s32 height;
    s16 angle;
    s32 alpha;
    u8 *actor;
    s32 scale;
    u8 texture;

    if (D_800BEAC0 != 0) {
        return arg0;
    }
    actor = &D_800CC2D0 + arg1 * 0x32C;
    alpha = actor[7];
    scale = actor[0x122];
    angle = *(s16 *)(actor + 0x60);
    if (alpha == 0) {
        return arg0;
    }
    height = scale * 19;
    width = height;
    if (*(s32 *)actor == 3) {
        height = scale * 15;
        width = height;
    }
    texture = func_1502C3BC(arg1);
    {
        u32 *command = arg0;
        arg0 = (u8 *)arg0 + 8;
        command[0] = 0xDE000000;
        command[1] = (u32)D_800873D0;
    }
    {
        u32 *command = arg0;
        arg0 = (u8 *)arg0 + 8;
        command[0] = 0xE7000000;
        command[1] = 0;
    }
    arg0 = (void *)func_15094F70(arg0, D_8008CA4C[texture], angle, &sprite, 0, 0, 0, 2, 3);
    sprite.mode = 0;
    sprite.alpha = alpha;
    sprite.width = width;
    sprite.height = height;
    sprite.x = (s32)*(f32 *)(actor + 0x14);
    sprite.z = (s32)*(f32 *)(actor + 0x1C);
    sprite.y = (s32)(*(f32 *)(actor + 0x18) + (f32)(scale / 2));
    arg0 = func_15095760(arg0, &sprite.x);
    *(u32 *)arg0 = 0xDE000000;
    *(u32 *)((u8 *)arg0 + 4) = (u32)D_80087408;
    return (u8 *)arg0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502C408 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C408.s")
typedef struct Game58F80ActorC608 {
    u8 pad0[7];
    u8 field_7;
    u8 pad8[0x58];
    s16 field_60;
    s16 field_62;
} Game58F80ActorC608;

extern u8 D_800BEAC0;
extern u8 D_800CC2D0;
extern u8 *D_8008CA4C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502C608 CURRENT (821) */
void func_1502C608(s32 arg0) {
    s16 sp22;
    s16 sp20;
    void *sp18;
    s16 temp_a2;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 var_v1;
    s32 temp_t2;
    void *temp_a1;

    if (D_800BEAC0 == 0) {
        temp_a1 = (u8 *)&D_800CC2D0 + (arg0 * 0x32C);
        temp_v1 = *(s16 *)((u8 *)temp_a1 + 0x60);
        temp_a2 = *(s16 *)((u8 *)temp_a1 + 0x62);
        if (*(u8 *)((u8 *)temp_a1 + 7) != 0) {
            sp22 = temp_v1;
            sp18 = temp_a1;
            sp20 = temp_a2;
            temp_t2 = D_8008CA4C[func_1502C3BC(arg0)][4] << 8;
            temp_v1 = sp22;
            temp_a2 = sp20;
            temp_a1 = sp18;
            temp_v1_2 = temp_v1 + temp_a2;
            var_v1 = temp_v1_2;
            if (temp_v1_2 >= temp_t2) {
                var_v1 = temp_v1_2 - temp_t2;
            } else if (var_v1 < 0) {
                var_v1 += temp_t2;
            }
            *(s16 *)((u8 *)temp_a1 + 0x60) = var_v1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502C608 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C608.s")
typedef struct Game58F80LodActor {
    u8 pad0[5];
    u8 kind;
    u8 pad6[0xE];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0x1C];
    f32 scale;
    u8 pad40[0x188];
    u8 lod;
    u8 locked;
    u8 pad1CA[0xFA];
    u8 *models;
    u8 modelCount;
} Game58F80LodActor;

typedef struct Game58F80LodView {
    u8 pad0[0x2F8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad304[0x69C];
} Game58F80LodView;

extern Game58F80LodView *D_800DBFF0;
extern f32 D_80096DE0;
extern f32 D_80096DE4;
extern u8 D_800BE616;
extern u8 D_800C35EA;
u8 func_150849A0(void *);
void func_150837D4(s32, u8, s32, void *);

/* Semantic role: actor_update_distance_representation.
 * With override +1C9 zero, choose from the automatic prefix by view distance,
 * subject to kind, state, actor +3C and count checks; record applied ordinal +1C8.
 * These conditions do not establish unconditional distance bands.
 * See docs/evidence/actor_representation_selection_semantics.md.
 */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502C6E8 CURRENT (1493) */
void func_1502C6E8(s32 arg0, s16 arg1, s32 arg2) {
    Game58F80LodView *view;
    s32 selected;
    s32 maximum;
    f32 ranges[4];
    f32 delta;
    f32 distance;
    s32 model;
    Game58F80LodActor *actor;

    actor = (Game58F80LodActor *)(&D_800CC2D0 + arg0 * 0x32C);
    view = D_800DBFF0 + arg1;
    if (actor->locked == 0 && actor->kind != 7) {
        ranges[0] = 500.0f;
        ranges[1] = D_80096DE0;
        ranges[2] = D_80096DE4;
        ranges[3] = 2000.0f;
        maximum = actor->modelCount - 1;
        if (maximum != -1) {
            model = func_150849A0(actor);
            delta = view->x - actor->x;
            distance = delta * delta;
            delta = view->y - actor->y;
            delta *= delta;
            distance += delta;
            delta = view->z - actor->z;
            delta *= delta;
            distance += delta;
            if (distance < ranges[0] * ranges[0]) {
                selected = 0;
            } else if (distance < ranges[1] * ranges[1]) {
                selected = 1;
            } else if (distance < ranges[2] * ranges[2]) {
                selected = 2;
            } else {
                selected = 4;
                if (distance < ranges[3] * ranges[3]) {
                    selected = 3;
                }
            }
            if (selected >= 2 && actor->scale < 3.0f) {
                selected--;
            }
            if (model != 0) {
                if (model == 0x5A && selected == 0) {
                    selected = 1;
                }
            } else if (D_800BE616 != 0) {
                selected = 1;
            }
            if (D_800C35EA == 1) {
                selected = 0;
            }
            if (maximum < selected) {
                selected = maximum;
                if (maximum < 0) {
                    selected = 0;
                }
            }
            if (selected != -1 && selected != actor->lod) {
                func_150837D4(arg0, actor->models[selected], 0, actor);
                actor->lod = selected;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502C6E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C6E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C974.s")
void func_1502EC34(u8 *, s32 *, s32 *, s32 *, s32 *);
extern u8 D_800D9B68[];
extern u8 D_800D9B78[];

void func_1502CC34(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11, s32 *arg12, s32 *arg13) {
    s32 offset;
    u8 *first;
    u8 *second;

    offset = arg1 * 3;
    first = D_800D9B68 + offset;
    *arg4 = first[0];
    second = D_800D9B78 + offset;
    *arg5 = first[1];
    *arg6 = first[2];
    *arg7 = second[0];
    *arg8 = second[1];
    *arg9 = second[2];
    *arg10 = 0;
    *arg11 = 0;
    *arg12 = 0;
    *arg13 = arg3[3];
    if (arg0[0xA4] != 0) {
        func_1502EC34(arg0, arg10, arg11, arg12, arg13);
    }
}
/* Semantic role: actor_emit_model_display_lists.
 * Prepares the selected actor model and emits parts not suppressed by +0x94.
 * Mode 3 uses the secondary table; other modes use the primary table.
 * Also performs render-state setup and actor/model usage updates.
 * See docs/evidence/actor_model_display_list_semantics.md.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502CCFC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502D54C CURRENT (135) */
void func_1502D54C(s32 arg0, void *arg1) {
    s32 temp_t1;
    void *temp_v0;

    temp_v0 = (u8 *)&D_800CC2D0 + (arg0 * 0x32C);
    if ((*(u8 *)((u8 *)temp_v0 + 0x66) & 0xC) == 4) {
        *(s32 *)((u8 *)arg1 + 0) =
            (s32)(*(u8 *)((u8 *)temp_v0 + 0x1E0) + *(u8 *)((u8 *)temp_v0 + 0x1DD)) / 2;
        *(s32 *)((u8 *)arg1 + 4) =
            (s32)(*(u8 *)((u8 *)temp_v0 + 0x1E1) + *(u8 *)((u8 *)temp_v0 + 0x1DE)) / 2;
        temp_t1 = (s32)(*(u8 *)((u8 *)temp_v0 + 0x1E2) +
                              *(u8 *)((u8 *)temp_v0 + 0x1DF)) / 2;
        *(volatile s32 *)((u8 *)arg1 + 8) = temp_t1;
        *(s32 *)((u8 *)arg1 + 0) = 0xFF - *(s32 *)((u8 *)arg1 + 0);
        *(s32 *)((u8 *)arg1 + 4) = 0xFF - *(s32 *)((u8 *)arg1 + 4);
        *(s32 *)((u8 *)arg1 + 8) = 0xFF - temp_t1;
        return;
    }
    *(s32 *)((u8 *)arg1 + 8) = 0xFF;
    *(s32 *)((u8 *)arg1 + 4) = 0xFF;
    *(s32 *)((u8 *)arg1 + 0) = 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502D54C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D54C.s")
void func_150A7A00(void *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern f32 D_80096DE8;
extern f32 D_80096DEC;
extern f32 D_80096DF0;
extern f32 D_80096DF4;
extern u8 D_800D2CA8[];
extern f32 D_800D9B1C;
extern f32 D_800D9B20;
extern u16 D_800DD2E8;
extern u16 D_800DD2EC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502D630 CURRENT (1104) */
void func_1502D630(Game58F80Actor *arg0, s32 *arg1, s32 arg2) {
    f32 far;
    f32 near;
    f32 step;
    f32 first;
    f32 last;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    f32 amount;

    if (D_800D9B1C != 0.0f) {
        first = 1.0f / D_800D9B1C;
    } else {
        first = D_80096DE8;
    }
    if (D_800D9B20 != 0.0f) {
        last = 1.0f / D_800D9B20;
    } else {
        last = D_80096DEC;
    }
    step = (first - last) * D_80096DF0;
    near = (f32)(u32)D_800DD2E8 * step + last;
    far = (f32)(u32)D_800DD2EC * step + last;
    func_150A7A00(D_800D2CA8 + (arg2 << 6), arg0->field_14,
                 arg0->field_18, arg0->field_1C, &x, &y, &z, &w);
    w = (w != 0.0f) ? 1.0f / w : D_80096DF4;
    if (w < 0.0f) {
        amount = 0.0f;
    } else if (w >= far) {
        amount = 0.0f;
    } else if (w <= near) {
        amount = 1.0f;
    } else {
        amount = (w - far) / (near - far);
    }
    arg1[3] = (1.0f - amount) * 255.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502D630 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D630.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D824.s")
extern u16 D_800C4ED0[];

s32 func_1502DB20(s32 arg0) {
    switch (arg0) {
        case 0x3B:
        case 0x75:
        case 0x82:
        case 0x88:
        case 0x90:
        case 0x96:
        case 0x98:
        case 0x9C:
        case 0x9D:
        case 0x9F:
        case 0xA0:
        case 0xB1:
        case 0xB2:
        case 0xB4:
            return D_800C4ED0[arg0] - 4;
        default:
            return D_800C4ED0[arg0];
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DB84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DF38.s")
extern s8 D_800C3E90;

void func_1502E474(void) {
    if ((u16)D_800C3E7A != 0) {
        func_150A9984(D_800C3E80[D_800BE9C0], (u16)D_800C3E7A);
    }
    D_800C3E90 = 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502E4C4.s")
void func_1502E9FC(s32 arg0, s32 arg1) {
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EA0C CURRENT (860) */
void func_1502EA0C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    *(s8 *)((u8 *)arg0 + 0xA4) = 4;
    *(s8 *)((u8 *)arg0 + 0xA5) = 0;
    *(s8 *)((u8 *)arg0 + 0xA6) = (s8) arg5;
    *(s8 *)((u8 *)arg0 + 0xA7) = 0xFF;
    *(s32 *)((u8 *)arg0 + 0xA0) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EA0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EA0C.s")
void func_1502EA50(u8 *arg0) {
    arg0[0xA4] = 5;
}
void func_1502EA60(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 2;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}
void func_1502EA7C(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 3;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}
void func_1502EA98(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0xA4);
    if ((temp_v0 != 6) && (temp_v0 != 7)) {
        if (arg5 != 0) {
            *(u8 *)((u8 *)arg0 + 0xA5) = 0xFF;
        } else {
            *(s8 *)((u8 *)arg0 + 0xA5) = 0;
        }
        *(s32 *)((u8 *)arg0 + 0xA0) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
        *(s8 *)((u8 *)arg0 + 0xA6) = (s8) arg6;
    }
    *(u8 *)((u8 *)arg0 + 0xA4) = 6U;
}
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EAFC CURRENT (570) */
void func_1502EAFC(void *arg0) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_t1;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;

    switch (*(u8 *)((u8 *)arg0 + 0xA4)) {
    case 2:
    case 3:
        temp_lo = *(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4;
        temp_v1 = *(u8 *)((u8 *)arg0 + 0xA5);
        if (temp_lo < (s32) temp_v1) {
            *(u8 *)((u8 *)arg0 + 0xA5) = (u8) (temp_v1 - temp_lo);
            return;
        }
        *(u8 *)((u8 *)arg0 + 0xA5) = 0U;
        return;
    case 5:
        temp_v1_2 = *(u8 *)((u8 *)arg0 + 0xA7);
        temp_t1 = D_800BE9E4 * 0xA;
        if (temp_t1 < (s32) temp_v1_2) {
            *(u8 *)((u8 *)arg0 + 0xA7) = (u8) (temp_v1_2 - temp_t1);
        } else {
            *(u8 *)((u8 *)arg0 + 0xA4) = 0U;
        }
        /* fallthrough */
    case 4:
        *(u8 *)((u8 *)arg0 + 0xA5) += *(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4;
        return;
    case 6:
        temp_lo_2 = *(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4;
        temp_v1_3 = *(u8 *)((u8 *)arg0 + 0xA5);
        if ((s32) temp_v1_3 < (0xFF - temp_lo_2)) {
            *(u8 *)((u8 *)arg0 + 0xA5) = (u8) (temp_v1_3 + temp_lo_2);
        } else {
            *(u8 *)((u8 *)arg0 + 0xA5) = 0xFFU;
        }
        *(u8 *)((u8 *)arg0 + 0xA4) = 7U;
        return;
    case 7:
        temp_lo_3 = *(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4;
        temp_v1_4 = *(u8 *)((u8 *)arg0 + 0xA5);
        if (temp_lo_3 < (s32) temp_v1_4) {
            *(u8 *)((u8 *)arg0 + 0xA5) = (u8) (temp_v1_4 - temp_lo_3);
            return;
        }
        *(u8 *)((u8 *)arg0 + 0xA4) = 0U;
    default:
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EAFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EAFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EC34.s")
extern u8 D_800CC33A[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EE8C CURRENT (450) */
s32 func_1502EE8C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = D_800CC33A[(arg0 * 0x32C) + arg1];
    var_v1 = temp_v0;
    if (temp_v0 >= 2) {
        if (temp_v0 >= 4) {
            var_v1 = 2;
        } else {
            var_v1 = temp_v0 - 2;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EE8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EE8C.s")
s32 func_1507E3C0(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EEF4 CURRENT (1750) */
void func_1502EEF4(s32 arg0) {
    s32 temp_v1;
    s32 var_s1;
    u8 temp_v0;
    u8 temp_v0_2;
    void *var_s0;

    var_s0 = (arg0 * 0x32C) + &D_800CC2D0;
    var_s1 = 0;
    do {
        if (*(u8 *)((u8 *)var_s0 + 0x6C) < 0xA) {
            temp_v1 = func_1502EE8C(arg0, var_s1) & 0xFF;
            if (temp_v1 == 0) {
                temp_v0 = *(u8 *)((u8 *)var_s0 + 0x6C);
                if (temp_v0 > 0) {
                    *(u8 *)((u8 *)var_s0 + 0x6C) = temp_v0 - 1;
                }
            } else if (1 == temp_v1) {
                temp_v0_2 = *(u8 *)((u8 *)var_s0 + 0x6C);
                if (temp_v0_2 < 2) {
                    *(u8 *)((u8 *)var_s0 + 0x6C) = temp_v0_2 + 1;
                }
            } else {
                *(u8 *)((u8 *)var_s0 + 0x6C) = 1;
            }
        }
        var_s1 += 1;
        var_s0 = (u8 *)var_s0 + 1;
    } while (var_s1 != 2);
    func_1507E3C0((arg0 * 0x32C) + &D_800CC2D0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EEF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EEF4.s")
typedef struct Game58F80TileExtent {
    u32 words[2];
    u16 width;
    u16 height;
} Game58F80TileExtent;

typedef struct Game58F80TileCommand {
    u32 word0;
    u32 word1;
} Game58F80TileCommand;

extern Game58F80TileExtent *D_800C5338[];

u8 *func_1507E908(void *, s32);
extern void *D_800D1C90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502F01C CURRENT (2693) */
void *func_1502F01C(Game58F80TileCommand *arg0, s32 arg1) {
    u8 selected[2];
    u8 *actor;
    u8 *record;
    u8 kind;
    s32 index;
    s32 values[2];
    void **slot;
    Game58F80TileExtent *tiles;

    actor = &D_800CC2D0 + arg1 * 0x32C;
    kind = actor[4];
    record = 0;
    index = 0;
    do {
        u8 selection = actor[index + 0x6C];
        slot = &D_800D1C90[kind];
        if (selection >= 10) {
            selected[index] = selection - 10;
        } else {
            u8 animation = actor[0x6F];
            selected[index] = ((u8 *)*slot)[index * 3 + selection + 8];
            if (animation != 0 && record == 0) {
                record = func_1507E908(actor, animation);
            }
            if (record != 0) {
                values[0] = record[0];
                values[1] = record[1];
                if (record != 0) {
                    if (values[index] == ((u8 *)*slot)[index * 3 + 10] ||
                        actor[index + 0x6C] == 0) {
                        selected[index] = values[index];
                    }
                }
            }
        }
        index++;
    } while (index != 2);
    tiles = D_800C5338[actor[4]];
    if (tiles != 0) {
        {
            Game58F80TileCommand *command = arg0++;
            command->word0 = 0xDB060018;
            command->word1 = tiles[selected[0]].words[0];
        }
        {
            Game58F80TileCommand *command = arg0++;
            command->word0 = 0xDB06001C;
            command->word1 = tiles[selected[1]].words[0];
        }
        {
            Game58F80TileCommand *command = arg0++;
            command->word0 = 0xDB060028;
            command->word1 = tiles[actor[0x68]].words[0];
        }
        {
            Game58F80TileCommand *command = arg0++;
            command->word0 = 0xDB06002C;
            command->word1 = tiles[actor[0x69]].words[0];
        }
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502F01C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F01C.s")

extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502F264 CURRENT (4130) */
void func_1502F264(s32 arg0) {
    u8 *actor = (u8 *)((u32)&D_800CC2D0 + (u32)arg0 * 0x32CU);
    u8 *parent;
    u8 *transform;
    u32 src;
    u32 dst;
    u8 index;
    s32 count;

    index = actor[0x65];
    if (index != 0) {
        parent = (u8 *)((u32)&D_800CC2D0 + index * 0x32CU - 0x32CU);
        if ((actor[0x101] & 2) != 2) {
            transform = *(u8 **)(parent + 0x1D4);
            if (transform == 0) {
                *(f32 *)(actor + 0x14) = *(f32 *)(parent + 0x14);
                *(f32 *)(actor + 0x18) = *(f32 *)(parent + 0x18);
                *(f32 *)(actor + 0x1C) = *(f32 *)(parent + 0x1C);
            } else {
                transform = (u8 *)((u32)transform + (*(u32 *)(actor + 0x5C) << 6));
                *(f32 *)(actor + 0x14) = *(f32 *)(transform + 0x30);
                *(f32 *)(actor + 0x18) = *(f32 *)(transform + 0x34);
                *(f32 *)(actor + 0x1C) = *(f32 *)(transform + 0x38);
            }
            *(f32 *)(actor + 0x180) = *(f32 *)(parent + 0x180);
            *(f32 *)(actor + 0x20) = -4.0f;
            if (!(actor[0x101] & 0x20)) {
                *(u16 *)(actor + 0x76) = *(u16 *)(parent + 0x76);
                *(f32 *)(actor + 0x3C) = *(f32 *)(parent + 0x3C);
                *(f32 *)(actor + 0x40) = *(f32 *)(parent + 0x40);
                *(u16 *)(actor + 0x76) = *(u16 *)(parent + 0x76);
                *(u16 *)(actor + 0x7A) = *(u16 *)(parent + 0x7A);
                *(u16 *)(actor + 0x78) = *(u16 *)(parent + 0x78);
            }
            if (!(actor[0x101] & 0x40)) {
                actor[7] = parent[7];
                count = 0;
                src = (u32)parent;
                actor[8] = parent[8];
                dst = (u32)actor;
                actor[9] = parent[9];
                actor[0xA] = parent[0xA];
                actor[0xF] = parent[0xF];
                if (D_80082FA0 >= 0) {
                    do {
                        *(u8 *)(dst + 0xBU) = *(u8 *)(src + 0xBU);
                        count = (s32)((u32)count + 1U);
                        src++;
                        dst++;
                    } while (count <= D_80082FA0);
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502F264 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F264.s")

void func_1502F490(Game58F80Actor *, f32 *, f32 *, f32 *, s32);
extern u8 D_800CC2D0;
extern u8 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502F3C8 CURRENT (979) */
void func_1502F3C8(void) {
    Game58F80Actor *actor;
    f32 limit;
    f32 current;
    u8 other_index;

    actor = (Game58F80Actor *) &D_800CC2D0;
    do {
        if (actor->active != 0) {
            other_index = actor->field_274;
            if (other_index != 0) {
                actor->field_18 = actor->field_180;
                func_1502F490((Game58F80Actor *) ((u8 *) &D_800CC2D0 + (other_index * 0x32C) - 0x32C), &actor->field_14, &actor->field_18, &actor->field_1C, actor->field_19E);
                current = actor->field_18;
                limit = actor->field_180;
                if (current < limit) {
                    actor->field_18 = limit;
                } else {
                    actor->field_180 = current;
                }
            }
        }
        actor += 1;
    } while (actor != (Game58F80Actor *) &D_800D121C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502F3C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F3C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F490.s")
extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_10023A10(void *arg0, void *arg1, s32 arg2);

void func_1502F948(void *arg0) {
    s32 temp_v1;
    void *temp_v0;

    if ((*(s32 *)((u8 *)arg0 + 0xF8) & 0x4000) == 0 ||
        *(s32 *)((u8 *)arg0 + 0x264) == 0 ||
        *(void **)((u8 *)arg0 + 0x1D4) == 0) {
        return;
    }
    temp_v1 = *(u8 *)((u8 *)arg0 + 4);
    if (*(void **)((u8 *)arg0 + 0x1D8) == 0) {
        temp_v0 = func_10003C40(D_800C4ED0[temp_v1] << 6, 1, 1, 2);
        *(void **)((u8 *)arg0 + 0x1D8) = temp_v0;
        if (temp_v0 == 0) {
            return;
        }
    }
    func_10023A10(*(void **)((u8 *)arg0 + 0x1D4), *(void **)((u8 *)arg0 + 0x1D8), D_800C4ED0[temp_v1] << 6);
}
void *func_150C3160(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502F9FC CURRENT (4582) */
void *func_1502F9FC(void *arg0, s32 arg1) {
    Game58F80TileExtent **table;
    s32 index;
    s32 tile;
    s32 kind;
    u8 *actor;
    Game58F80TileExtent *extent;
    u8 *coordinates;
    Game58F80TileCommand *output;
    Game58F80TileCommand *command;
    u32 s;
    u32 t;
    u32 width;
    u32 height;

    output = arg0;
    actor = &D_800CC2D0 + arg1 * 0x32C;
    kind = actor[4];
    if (kind == 0x89 || kind == 0xBA) {
        output = func_150C3160(output, actor);
        goto done;
    }
    if (kind == 0) {
        tile = 14;
    } else if (kind == 0x96) {
        tile = 7;
    } else if (kind == 0x28) {
        tile = 4;
    } else if (kind == 1 || kind == 2 || kind == 3 || kind == 4) {
        tile = 5;
    } else {
        tile = 0;
    }
    table = &D_800C5338[kind];
    index = 0;
    if (*table != 0) {
        coordinates = &D_800CC2D0 + arg1 * 0x32C;
        do {
            extent = *table + tile;
            s = *(s16 *)(coordinates + 0x27A);
            t = *(s16 *)(coordinates + 0x27E);
            width = extent->width;
            height = extent->height;
            s = (s + 2) & 0xFFFF;
            t = (t + 2) & 0xFFFF;
            width = (width * 4 - 2) & 0xFFFF;
            height = (height * 4 - 2) & 0xFFFF;
            command = output;
            command->word0 = ((s & 0xFFF) << 12) | 0xF2000000U | (t & 0xFFF);
            command->word1 = (((5 - index) & 7) << 24) |
                             ((width & 0xFFF) << 12) | (height & 0xFFF);
            output++;
            index++;
            coordinates += 2;
        } while (index != 2);
    }
done:
    return output;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502F9FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F9FC.s")
extern u8 D_800C35EA;
extern u8 D_800C3638;
extern u16 D_800C5A90[];
extern void *D_800D1588[];
void func_150837D4(s32, u8, s32, void *);
void func_1505E650(void *, s32, f32, f32, f32, f32, s32);
void func_1507EABC(void *);

/* Semantic role: actor_apply_representation_override.
 * Zero returns; 0xFF clears the override and applies entry zero. Other selectors
 * apply a changed, in-range one-based entry, then check routes and expression.
 * Rejected nonzero selectors remain stored and still inhibit automatic choice.
 * See docs/evidence/actor_representation_selection_semantics.md.
 */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502FBE8 CURRENT (979) */
void func_1502FBE8(void *arg0) {
    u8 *actor = arg0;
    u8 current = actor[0x1C9];
    s32 actor_index = (s32)((u32)actor - (u32)&D_800CC2D0) / 0x32C;
    void *old;
    s32 next;
    s32 selection;
    s32 mode;
    s32 value;

    if (current == 0) {
        return;
    }
    old = D_800D1588[actor[4]];
    if (current == 0xFF) {
        actor[0x1C9] = 0;
        next = 0;
    } else {
        next = current - 1;
        if (next >= actor[0x2C9] || next == actor[0x1C8]) {
            return;
        }
    }
    selection = *(u8 *)(*(u8 **)(actor + 0x2C4) + next);
    func_150837D4(actor_index, selection, 0, old);
    actor[0x1C8] = next;
    mode = D_800C35EA;
    if (mode == 1) {
        D_800C3638 = 0;
    }
    if (old != D_800D1588[selection]) {
        value = *(u16 *)(actor + 0x84);
        if (value >= D_800C5A90[selection]) {
            *(u16 *)(actor + 0x84) = 0xFFFF;
            func_1505E650(arg0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0);
        } else {
            *(u16 *)(actor + 0x84) = 0xFFFF;
            func_1505E650(arg0, value, 1.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        mode = D_800C35EA;
    }
    if (mode == 1) {
        D_800C3638 = 1;
    }
    func_1507EABC(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502FBE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FBE8.s")
extern u8 D_80038080;
extern s32 D_800BE9F0;
extern u8 D_800D2040;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502FD70 CURRENT (35) */
void func_1502FD70(void *arg0) {
    s32 temp_v0_3;
    u8 *temp_v1;
    s32 temp_a1;
    u8 temp_a2;
    u8 temp_v0;
    void *temp_v0_2;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((D_80038080 == 0) && (D_800BE9F0 == 0x1D)) {
        *(&D_800D2040 + temp_v0) = 2;
        return;
    }
    temp_v1 = &D_800D2040 + temp_v0;
    temp_a1 = *temp_v1;
    if (0xFF != temp_a1) {
        temp_v0_2 = *(void **)((u8 *)arg0 + 0x144);
        if (temp_v0_2 != 0) {
            temp_a2 = *(u8 *)((u8 *)temp_v0_2 + 0x2E);
            if (temp_a2 != 0xFF) {
                if (temp_a2 != 0) {
                    temp_v0_3 = temp_a2 * 0x1E;
                    if ((s32)temp_a1 < temp_v0_3) {
                        *temp_v1 = (u8)temp_v0_3;
                    }
                } else {
                    goto block_9;
                }
            }
        } else {
block_9:
            *temp_v1 = 3;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502FD70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FD70.s")
