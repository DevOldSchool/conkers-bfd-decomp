#include "types.h"

/*
 * Reviewed source unit: src/game/game_3B920.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500E470
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *, s32);
void func_15004FE0(s32);
void func_1500AC14(void);
void func_1500BEC0(void);
void func_1500E5C0(void);
void func_15012370(void);
s8 func_15012720(void);
void func_150127B0(void);
void func_151645C4(s32);
void func_151732E0(s32);
void func_151872B0(s32);
void func_1519582C(void);
void func_151EF640(s32);
void func_15008B90(void);
void func_15008BE0(void);
void func_1500ABA0(s32);
void func_15012FE0(void);
void func_15178EB0(void);
extern s8 D_80088B60;
extern s8 D_8008CD00;
extern void (*D_80082D90[])(void);
extern void *D_800B0DF0;
extern s32 D_800BE4E0;
extern u8 *D_800D2E4C;
extern s8 D_800DD190;
extern s32 D_800DD198;
extern u8 D_800DD404;
extern s8 D_800DD405;
extern s8 D_800DD406;
extern s32 D_800E0930;
extern s32 D_800E0934;
extern s32 D_800E0940;
extern s8 D_800E0A10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500E470 CURRENT (330) */
void func_1500E470(s32 arg0) {
    u8 temp_v0;

    D_800DD190 = -1;
    func_100226F0(&D_800DD198, 0x18);
    D_800DD404 = 0xFF;
    D_800DD405 = 0;
    D_800DD406 = 0;
    D_800E0930 = 0;
    D_800E0934 = 0;
    D_800E0940 = 0;
    D_8008CD00 = 0;
    D_80088B60 = 0;
    D_800BE4E0 = 0;
    D_800E0A10 = func_15012720();
    func_15012370();
    func_151EF640(0x40);
    func_151732E0(arg0);
    func_15004FE0(arg0);
    func_150127B0();
    func_1519582C();
    func_15008BE0();
    func_15008B90();
    func_1500E5C0();
    temp_v0 = *((u8 *)D_800B0DF0 + 0xA);
    if (temp_v0 != 0) {
        D_80082D90[temp_v0]();
    }
    func_1500ABA0(arg0);
    func_1500BEC0();
    func_1500AC14();
    func_151872B0(arg0);
    func_15178EB0();
    func_15012FE0();
    func_151645C4(((D_800D2E4C[4] & 0x80) == 0) & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500E470 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3B920/func_1500E470.s")
