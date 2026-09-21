#include "types.h"

/*
 * Reviewed source unit: src/game/game_FB060.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CDBB0
 * - func_150CDCF4
 * - func_150CDF10
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
s32 func_15046C80(f32 *, s32, f32, f32 *);
void func_1504715C(f32 *, void *);
u32 func_150ADA20(void);
extern f32 D_800A07B0;

typedef struct GameFB060Trace {
    f32 scratch;
    u8 pad_4[0x20];
    f32 position[3];
} GameFB060Trace;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CDBB0 CURRENT (275) */
void func_150CDBB0(void *arg0, u8 arg1, s32 arg2) {
    GameFB060Trace trace;

    if (arg0 != 0) {
        func_1504715C(&trace.scratch, arg0);
        trace.position[0] = *(f32 *)((u8 *)arg0 + 0x14);
        trace.position[1] = *(f32 *)((u8 *)arg0 + 0x18) + 1000.0f;
        trace.position[2] = *(f32 *)((u8 *)arg0 + 0x1C);
        if (func_15046C80(trace.position, 0,
                          *(f32 *)((u8 *)arg0 + 0x18) - D_800A07B0,
                          &trace.scratch) != 0) {
            trace.position[1] = trace.scratch;
            func_1514C678(trace.position[0], trace.position[1],
                           *(s32 *)&trace.position[2], 251.0f, 0, 0xFF,
                           (func_150ADA20() & 0xF) + 0x23, 0x17, 0,
                           0.0f, 0, arg1);
            func_1514C678(trace.position[0], trace.position[1],
                           *(s32 *)&trace.position[2], 290.0f, 0, 0xFF,
                           (func_150ADA20() % 21U) + 0x1E, 0x18, 0,
                           0.0f, 0, arg1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CDBB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB060/func_150CDBB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB060/func_150CDCF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB060/func_150CDF10.s")
