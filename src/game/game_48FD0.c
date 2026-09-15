#include "types.h"

/*
 * Reviewed source unit: src/game/game_48FD0.c
 * Boundary evidence: docs/evidence/game_raw_controller_io_group.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501BB20
 * - func_1501BBB8
 * - func_1501C010
 * - func_1501C0F0
 * - func_1501C17C
 * - func_1501C1B0
 * - func_1501C53C
 * - func_1501C57C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u64 func_10026968(s32, s32, s32, s32);
u64 func_10026868(u64, s32, s32);
void func_10024A40(void *, u64, s32, s32, void *, s32);
extern s32 D_8002BD10;
extern s32 D_8002BD14;
extern u8 D_80084064;
extern u8 D_8003B218[];
extern u8 D_800BE6E0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501BB20 CURRENT (1307) */
void func_1501BB20(void) {
    u64 temp_ret;

    if (D_80084064 != 0) {
        temp_ret = func_10026968(0, 0x19, D_8002BD10, D_8002BD14);
        temp_ret = func_10026868(temp_ret, 0, 0xF4240);
        func_10024A40(D_800BE6E0, temp_ret, 0, 0, D_8003B218, 6);
        D_80084064 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501BB20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BB20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BBB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C010.s")
extern u8 D_80084060[4];
extern u8 D_800BE93C[4];
extern u8 D_800BE944[4];
extern f32 D_800BE950[4];
extern f32 D_800BE960[4];
extern f32 D_800BE970[4];
extern f32 D_800BE980[4];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C0F0 CURRENT (25) */
void func_1501C0F0(u8 arg0, f32 arg1, f32 arg2) {
    u8 temp_v0;
    s32 temp_v1;

    temp_v0 = D_80084060[arg0];
    if ((temp_v0 < 4) && (D_800BE944[temp_v0] != 0)) {
        D_800BE93C[temp_v0] = 1;
        temp_v1 = temp_v0 * 4;
        *(f32 *)((u8 *)D_800BE950 + temp_v1) = 0.0f;
        *(f32 *)((u8 *)D_800BE960 + temp_v1) = arg1;
        *(f32 *)((u8 *)D_800BE970 + temp_v1) = arg2;
        *(f32 *)((u8 *)D_800BE980 + temp_v1) = arg1 + arg2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C0F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C0F0.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C17C CURRENT (205) */
void func_1501C17C(s32 arg0) {
    u8 temp_v0;

    arg0 = arg0 & 0xFF;
    temp_v0 = D_80084060[arg0];
    if ((s32)temp_v0 < 4) {
        D_800BE93C[temp_v0] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C17C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C1B0.s")
void func_1501C17C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C53C CURRENT (220) */
void func_1501C53C(void) {
    s32 temp_t6;
    s32 var_s0;

    var_s0 = 0;
    do {
        func_1501C17C(var_s0 & 0xFF);
        temp_t6 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t6;
    } while (temp_t6 < 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C53C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C53C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C57C.s")
