#include "types.h"

/*
 * Reviewed source unit: src/game/game_128790.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FB324
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_150FB240(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4);

s32 func_150FB2E0(void *arg0) {
    func_150FB240((u8 *) arg0 + 0x2E, *(s16 *)((u8 *) arg0 + 0x22), *(s16 *)((u8 *) arg0 + 0x70), *(s16 *)((u8 *) arg0 + 0x26), *(s16 *)((u8 *) arg0 + 0x28));
    return 1;
}
typedef struct Game128790Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game128790Vec3;

typedef struct Game128790Locals {
    void *outputs[3];
    void *inputs[3];
    Game128790Vec3 vec44;
    Game128790Vec3 vec50;
    Game128790Vec3 vec5C;
    Game128790Vec3 vec68;
    s32 pad74;
    s32 buffer;
    Game128790Vec3 result7C;
    Game128790Vec3 result88;
    Game128790Vec3 result94;
} Game128790Locals;

void func_15145EA4(s32 *, s32 *, s32, s32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);
void func_150FEC28(void *, s32, void *, void *, void *, s32, s32);
extern Game128790Vec3 D_800A1D30;
extern Game128790Vec3 D_800A1D3C;
extern Game128790Vec3 D_800A1D48;
extern Game128790Vec3 D_800A1D54;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FB324 CURRENT (1147) */
void func_150FB324(u8 *arg0, s32 arg1, s32 arg2) {
    Game128790Locals locals;

    locals.vec68 = D_800A1D30;
    locals.vec5C = D_800A1D3C;
    locals.vec50 = D_800A1D48;
    locals.vec44 = D_800A1D54;
    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        locals.inputs[0] = &locals.vec68;
        locals.inputs[1] = &locals.vec50;
        locals.inputs[2] = &locals.vec44;
        locals.outputs[0] = &locals.result94;
        locals.outputs[1] = &locals.result88;
        locals.outputs[2] = &locals.result7C;
        locals.buffer = *(s32 *)(arg0 + 0x1D4) + 0x380;
        func_15145EA4((s32 *)locals.inputs, (s32 *)locals.outputs,
                      locals.buffer, 3);
        locals.result7C.x -= locals.result88.x;
        locals.result7C.y -= locals.result88.y;
        locals.result7C.z -= locals.result88.z;
        func_150FEC28(arg0, 0xE, &locals.vec68, &locals.vec5C,
                      &locals.result94, ((u8 *)&arg1)[3], arg2);
        func_151D4408(&locals.result88, &locals.result7C, locals.buffer,
                       arg0, 1.0f, ((u8 *)&arg1)[3], arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FB324 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_128790/func_150FB324.s")
