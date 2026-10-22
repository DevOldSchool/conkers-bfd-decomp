#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A0790.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_slot_view_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151733D8
 * - func_151733E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1A0790Output {
    u8 field0;
    u8 field1;
    u8 field2;
    u8 field3;
    s16 field4;
    s16 field6;
    s16 field8;
    s16 fieldA;
    u16 fieldC;
    u16 fieldE;
} Game1A0790Output;

void func_151733E4(s32, s32, s32, s32, s32);
extern s8 *D_800B0DF0;
extern Game1A0790Output D_8008CC70;
extern s8 D_800DD2E0;

void func_151732E0(s32 arg0) {
    s8 temp_a0;

    if ((*(s16 *)(D_800B0DF0 + 0x40) == *(s16 *)(D_800B0DF0 + 0x3C)) && (*(s16 *)(D_800B0DF0 + 0x3C) == 0)) {
        *(s16 *)(D_800B0DF0 + 0x40) = 0x64;
    }
    D_8008CC70.field0 = ((u8 *)D_800B0DF0)[0x42];
    D_8008CC70.field1 = ((u8 *)D_800B0DF0)[0x43];
    D_8008CC70.field2 = ((u8 *)D_800B0DF0)[0x44];
    D_8008CC70.field3 = ((u8 *)D_800B0DF0)[0x45];
    D_8008CC70.field4 = *(s16 *)(D_800B0DF0 + 0x3A);
    D_8008CC70.field6 = *(s16 *)(D_800B0DF0 + 0x3C);
    D_8008CC70.field8 = *(s16 *)(D_800B0DF0 + 0x3E);
    D_8008CC70.fieldA = *(s16 *)(D_800B0DF0 + 0x40);
    D_8008CC70.fieldC = *(u16 *)(D_800B0DF0 + 2);
    D_8008CC70.fieldE = *(u16 *)D_800B0DF0;
    if (D_800B0DF0[0x46] != -1) {
        D_800DD2E0 = 1;
        temp_a0 = D_800B0DF0[0x46];
        func_151733E4((s32)temp_a0, (s32)temp_a0, arg0, 0, -1);
        return;
    }
    D_800DD2E0 = 0;
    func_151733E4(0, 0, arg0, 0, -1);
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151733D8 CURRENT (60) */
void *func_151733D8(void *arg0, s32 arg1) {
    void *result = arg0;

    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151733D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733D8.s")
s8 func_15173994(s32);
extern u8 D_800DD2E4[];
extern s16 D_800DD2E8;
extern s16 D_800DD2EA;
extern s16 D_800DD2EC;
extern s16 D_800DD2EE;
extern s16 D_800DD2F0;
extern u16 D_800DD2F2;
extern u16 D_800DD2F4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151733E4 CURRENT (12429) */
void func_151733E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 *index;
    Game1A0790Output *out;
    s32 from;
    s32 to;
    s16 *near;
    s16 *far;
    s16 *field8;
    s16 *fieldA;
    u16 *fieldC;
    u16 *fieldE;

    D_800DD2F0 = arg3;
    if (arg4 == -1) {
        out = (Game1A0790Output *)D_800DD2E4;
        near = &D_800DD2EC;
        far = &D_800DD2EE;
        field8 = &D_800DD2E8;
        fieldA = &D_800DD2EA;
        fieldC = &D_800DD2F2;
        fieldE = &D_800DD2F4;
    } else {
        out = &(&D_8008CC70)[arg4];
        near = &(&D_8008CC70)[arg4].field4;
        far = &(&D_8008CC70)[arg4].field6;
        field8 = &(&D_8008CC70)[arg4].field8;
        fieldA = &(&D_8008CC70)[arg4].fieldA;
        fieldC = &(&D_8008CC70)[arg4].fieldC;
        fieldE = &(&D_8008CC70)[arg4].fieldE;
    }
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            index = &arg0;
        } else {
            index = &arg1;
        }
        switch (*index) {
        case 0x7C:
            *index = 1;
            break;
        case 0x7D:
            *index = 2;
            break;
        case 0x7E:
            *index = func_15173994(arg2);
            break;
        case 0x7F:
            *index = 2;
            break;
        }
    }
    out->field0 = ((&D_8008CC70)[arg1].field0 - (&D_8008CC70)[arg0].field0) * arg3 / 4096 + (&D_8008CC70)[arg0].field0;
    out->field1 = ((&D_8008CC70)[arg1].field1 - (&D_8008CC70)[arg0].field1) * arg3 / 4096 + (&D_8008CC70)[arg0].field1;
    out->field2 = ((&D_8008CC70)[arg1].field2 - (&D_8008CC70)[arg0].field2) * arg3 / 4096 + (&D_8008CC70)[arg0].field2;
    out->field3 = ((&D_8008CC70)[arg1].field3 - (&D_8008CC70)[arg0].field3) * arg3 / 4096 + (&D_8008CC70)[arg0].field3;
    *near = (u16)(&D_8008CC70)[arg0].field4 + ((u16)(&D_8008CC70)[arg1].field4 - (u16)(&D_8008CC70)[arg0].field4) * arg3 / 4096;
    *far = (u16)(&D_8008CC70)[arg0].field6 + ((u16)(&D_8008CC70)[arg1].field6 - (u16)(&D_8008CC70)[arg0].field6) * arg3 / 4096;
    *field8 = (u16)(&D_8008CC70)[arg0].field8 + ((u16)(&D_8008CC70)[arg1].field8 - (u16)(&D_8008CC70)[arg0].field8) * arg3 / 4096;
    *fieldA = (u16)(&D_8008CC70)[arg0].fieldA + ((u16)(&D_8008CC70)[arg1].fieldA - (u16)(&D_8008CC70)[arg0].fieldA) * arg3 / 4096;
    if ((s16)(&D_8008CC70)[arg0].fieldC == -1) {
        from = *(s16 *)(D_800B0DF0 + 2);
    } else {
        from = (s16)(&D_8008CC70)[arg0].fieldC;
    }
    if ((s16)(&D_8008CC70)[arg1].fieldC == -1) {
        to = *(s16 *)(D_800B0DF0 + 2);
    } else {
        to = (s16)(&D_8008CC70)[arg1].fieldC;
    }
    *fieldC = (to - from) * arg3 / 4096 + from;
    if ((s16)(&D_8008CC70)[arg0].fieldE == -1) {
        from = *(s16 *)D_800B0DF0;
    } else {
        from = (s16)(&D_8008CC70)[arg0].fieldE;
    }
    if ((s16)(&D_8008CC70)[arg1].fieldE == -1) {
        to = *(s16 *)D_800B0DF0;
    } else {
        to = (s16)(&D_8008CC70)[arg1].fieldE;
    }
    *fieldE = (to - from) * arg3 / 4096 + from;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151733E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733E4.s")
extern void *D_800DBFF0;
extern u8 D_800DBEA8[];
extern u8 D_800DD2E4[];

void func_151738C4(s32 arg0) {
    if (D_800B0DF0[0x46] == -1) {
        if (*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 1) {
            func_151733E4(6, 6, arg0, 0, -1);
            D_800DBEA8[0] = D_800DD2E4[0];
            D_800DBEA8[1] = D_800DD2E4[1];
            D_800DBEA8[2] = D_800DD2E4[2];
            return;
        }
        func_151733E4(0, 0, arg0, 0, -1);
        D_800DBEA8[0] = ((u8 *)D_800B0DF0)[5];
        D_800DBEA8[1] = ((u8 *)D_800B0DF0)[6];
        D_800DBEA8[2] = ((u8 *)D_800B0DF0)[7];
    }
}

s8 func_15173994(s32 arg0) {
    return D_800B0DF0[0x46];
}
