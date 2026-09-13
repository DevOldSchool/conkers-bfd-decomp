#include "types.h"

/*
 * Reviewed source unit: src/game/game_1844C0.c
 * Boundary evidence: docs/evidence/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15157010
 * - func_151571C4
 * - func_151572D0
 * - func_15157420
 * - func_15157898
 * - func_15157918
 * - func_15157AA8
 * - func_15157DEC
 * - func_15157F80
 * - func_15157FE8
 * - func_15158078
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157010.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_151571C4.s")
extern void func_151571C4(void *arg0);
extern void func_1518CA04(s32 arg0);
extern void func_1503F7B8(s32 arg0);
extern void func_15169804(s32 arg0);

void func_15157248(void *arg0) {
    func_151571C4(arg0);
    func_1518CA04(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503F7B8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169804((s32) arg0);
}
void func_1515728C(void *arg0) {
    func_151571C4(arg0);
    func_1518CA04(*(s32 *)((u8 *)arg0 + 0x18));
    func_1503F7B8(*(s32 *)((u8 *)arg0 + 0x68));
    func_15169824((s32) arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_151572D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157420.s")
extern u8 D_800BE9C0;
void func_150A7BC0(s32 arg0, s32 arg1);

s32 func_15157860(s32 arg0) {
    func_150A7BC0((s32)((u8 *)arg0 + (D_800BE9C0 << 6) + 0x7C), arg0);
    return 1;
}
void func_15169260(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800A6060;
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157898.s")
/* Call context: func_150A8050: unique active project prototype */
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157918 CURRENT (840) */
s32 func_15157918(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    u8 *temp_v1_7;
    u8 *temp_v1_8;
    u8 *temp_v1_9;

    func_150A8050(arg0 + (D_800BE9C0 << 6) + 0x7C, *(f32 *)((u8 *)arg0 + 0x120), *(s32 *)((u8 *)arg0 + 0x124), *(f32 *)((u8 *)arg0 + 0x128));
    temp_a0 = (void *)(arg0 + 0x120);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xAC) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB0) = (f32) *(f32 *)((u8 *)arg0 + 0x58);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB4) = (f32) *(f32 *)((u8 *)arg0 + 0x5C);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x7C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x7C) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_2 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_2 + 0x80) = (f32) (*(f32 *)((u8 *)temp_v1_2 + 0x80) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_3 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_3 + 0x84) = (f32) (*(f32 *)((u8 *)temp_v1_3 + 0x84) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_4 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_4 + 0x8C) = (f32) (*(f32 *)((u8 *)temp_v1_4 + 0x8C) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_5 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_5 + 0x90) = (f32) (*(f32 *)((u8 *)temp_v1_5 + 0x90) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_6 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_6 + 0x94) = (f32) (*(f32 *)((u8 *)temp_v1_6 + 0x94) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_7 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_7 + 0x9C) = (f32) (*(f32 *)((u8 *)temp_v1_7 + 0x9C) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_8 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_8 + 0xA0) = (f32) (*(f32 *)((u8 *)temp_v1_8 + 0xA0) * *(f32 *)((u8 *)temp_a0 + 0xC));
    temp_v1_9 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_9 + 0xA4) = (f32) (*(f32 *)((u8 *)temp_v1_9 + 0xA4) * *(f32 *)((u8 *)temp_a0 + 0xC));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15157918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157AA8.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15157D88(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x4C, arg0 + 0x50, arg0);
}
s32 func_15157DC8(s32 arg0) {
    func_15157DEC(arg0, arg0 + 0x120);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157DEC.s")
typedef struct Game1844C0DisplayCommand {
    u32 word0;
    void *word1;
} Game1844C0DisplayCommand;

typedef struct Game1844C0Matrix {
    u8 bytes[0x40];
} Game1844C0Matrix;

extern u8 D_80089470;
extern Game1844C0Matrix D_800DCC10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15157F80 CURRENT (1235) */
Game1844C0DisplayCommand *func_15157F80(Game1844C0DisplayCommand *arg0, s32 arg1,
                                       s32 arg2, s32 arg3, u8 *arg4) {
    Game1844C0DisplayCommand *temp_v1;
    Game1844C0DisplayCommand *temp_a1;

    temp_v1 = arg0++;
    temp_v1->word0 = 0xDA380003;
    temp_v1->word1 = &D_80089470;
    temp_a1 = arg0++;
    temp_a1->word0 = 0xDA380007;
    temp_a1->word1 = &D_800DCC10[arg2];
    *arg4 = 1;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15157F80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157F80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15157FE8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158078 CURRENT (260) */
void func_15158078(s32 arg0, u8 arg1) {
    func_15169260(&D_800A6060, 3, arg0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158078 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1844C0/func_15158078.s")
