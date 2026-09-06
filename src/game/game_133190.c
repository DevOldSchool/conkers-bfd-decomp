#include "types.h"

/*
 * Reviewed source unit: src/game/game_133190.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15105CE0
 * - func_1510608C
 * - func_151061EC
 * - func_15106214
 * - func_151064B4
 * - func_151064DC
 * - func_15106510
 * - func_15106558
 * - func_15106584
 * - func_151065BC
 * - func_15106610
 * - func_151067B8
 * - func_15106E78
 * - func_15106EF8
 * - func_15106F24
 * - func_15106F50
 * - func_15106F98
 * - func_151070F8
 * - func_151072BC
 * - func_15107604
 * - func_1510761C
 * - func_1510764C
 * - func_15107678
 * - func_151076A4
 * - func_15107700
 * - func_151078E4
 * - func_15107924
 * - func_15107A20
 * - func_15107AE0
 * - func_15107B78
 * - func_15107C1C
 * - func_15107E48
 * - func_15107F54
 * - func_15107F98
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game133190Subobject {
    u8 pad0[8];
    s32 field_8;
} Game133190Subobject;

typedef struct Game133190Target {
    u8 pad0[0x28];
    Game133190Subobject subobject;
} Game133190Target;

typedef struct Game133190Holder {
    Game133190Target *target;
} Game133190Holder;

typedef struct Game133190Object {
    u8 pad0[0x60];
    Game133190Holder *holder;
} Game133190Object;

#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15105CE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_1510608C.s")
s32 func_151061E0(s32 arg0) {
    return arg0 + 0x88;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151061EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106214.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151064B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151064DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106510.s")
f32 func_15106540(f32 arg0) {
    return arg0 * arg0 * arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106584.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151065BC.s")
f32 func_151065EC(f32 arg0) {
    return 3.0f * arg0 * arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106610.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151067B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106E78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106EF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106F24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106F98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151070F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151072BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107604 CURRENT (20) */
Game133190Holder *func_15107604(Game133190Object *arg0) {
    Game133190Holder *holder = arg0->holder;
    Game133190Subobject *subobject = &holder->target->subobject;

    subobject->field_8 = 0;
    return holder;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107604 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107604.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_1510761C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_1510764C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107678.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151076A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107700.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151078E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107924.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107A20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107AE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107B78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107C1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107E48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107F54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107F98.s")
