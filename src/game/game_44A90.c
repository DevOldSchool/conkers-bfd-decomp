#include "types.h"

/*
 * Reviewed source unit: src/game/game_44A90.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150175E0
 * - func_15017640
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800BE616;
extern s8 D_800D2456;
extern s8 D_800D2457;
extern void *D_800D2E4C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150175E0 CURRENT (1195) */
void func_150175E0(void) {
    if ((D_800BE616 == 0) && !(*(u8 *)((u8 *)D_800D2E4C + 0x18) & 1)) {
        D_800D2456 = 3;
        D_800D2457 = 3;
        return;
    }
    D_800D2456 = 6;
    D_800D2457 = 6;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150175E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_44A90/func_150175E0.s")

void func_100226F0(void *arg0, s32 arg1, void *arg2);
void func_15048134(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);

extern f32 D_800968B0;
typedef struct Game44A90Vec {
    f32 x;
    f32 y;
    f32 z;
} Game44A90Vec;

extern s16 D_8009DCB4[3];
extern u8 D_800D23D0;
extern f32 D_800D2410;
extern Game44A90Vec D_800D2428;
extern Game44A90Vec D_800D2438;
extern s32 D_800D2444;
extern u8 D_800D2454;
extern u8 D_800D2458;
extern s32 D_800D245C;
extern u8 D_800D2460;
extern u8 D_800D246D;
extern u8 D_800D247D;
extern s32 D_800D24C0;
extern u8 D_800D24C8;
extern s32 D_800D2588;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15017640 CURRENT (1225) */
void func_15017640(void) {
    f32 *value;
    u8 *entry;
    s32 entryIndex;

    D_800D2458 = 0;
    D_800D2588 = 0;
    D_800D2438.x = 0.0f;
    D_800D2438.y = 0.0f;
    D_800D2438.z = 0.0f;
    D_800D2428.x = D_8009DCB4[0];
    D_800D2428.y = D_8009DCB4[1];
    value = &D_800D2410;
    D_800D2428.z = D_8009DCB4[2];
    D_800D2444 = 0;
    D_800D245C = 0;

    do {
        *value++ = 1.0f;
    } while (value < &D_800D2428.x);

    D_800D246D = 0;
    D_800D247D = 0;
    entryIndex = 2;
    entry = &D_800D2460 + (entryIndex * 0x10);
    entry[0x1D] = 0;
    entry[0x2D] = 0;
    entry[0x3D] = 0;
    entry[0x0D] = 0;
    D_800D24C0 = 0;

    func_100226F0(&D_800D24C8, 0xC0, &D_800D2438);
    func_15048134(&D_800D23D0, &D_800D2454, 50.0f, 60.6f, 53.0f, D_800968B0, 1.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15017640 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_44A90/func_15017640.s")
