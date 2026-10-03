#include "types.h"

/*
 * Reviewed source unit: src/game/game_1188E0.c
 * Boundary evidence: docs/evidence/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EB484
 * - func_150EB614
 * - func_150EB8C4
 * - func_150EBC80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game1188E0Vector;

s32 func_150EB484(Game1188E0Vector *, f32 *, void *);

void func_150EB430(Game1188E0Vector *arg0, Game1188E0Vector *arg1, void *arg2) {
    f32 sp1C[3];
    Game1188E0Vector *temp_a3 = arg1;

    sp1C[0] = arg0->x + temp_a3->x;
    sp1C[1] = arg0->y + temp_a3->y;
    sp1C[2] = arg0->z + temp_a3->z;
    func_150EB484(arg0, sp1C, arg2);
}
void func_150A2864(s32, s32);
void *func_15083E90(s32);
s32 func_150A34B0(void *, Game1188E0Vector *, f32 *, void *);
void func_150EBC80(void *, u8, s32);
extern s32 D_80088AA0[];
extern s32 D_80088AB0[];
extern s32 D_80088AD0;
extern u8 *D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EB484 CURRENT (550) */
s32 func_150EB484(Game1188E0Vector *arg0, f32 *arg1, void *arg2) {
    u8 *spawned;
    s32 *index_ptr;
    s32 *alternate_ptr;
    s32 index;
    s32 id;
    s32 offset;

    spawned = func_15083E90(9);
    if (spawned != 0) {
        index_ptr = D_80088AA0;
        index = 0;
        do {
            id = *index_ptr;
            offset = id * 0x34;
            if (func_150A34B0(D_800D3098 + offset, arg0, arg1, arg2) != 0) {
                func_150A2864(id, 1);
                *(s32 *)(spawned + 0x2E8) = index + 1;
                func_150EBC80(D_800D3098 + offset, 0xFF, 1);
                return 1;
            }
            index++;
            index_ptr++;
        } while (index < 4);
        alternate_ptr = D_80088AB0;
        do {
            if (func_150A34B0(D_800D3098 + (*alternate_ptr * 0x34),
                               arg0, arg1, arg2) != 0) {
                return 1;
            }
            alternate_ptr++;
        } while (alternate_ptr != &D_80088AD0);
        return 0;
    }
    if (func_150A34B0(D_800D3098 + 0xF70, arg0, arg1, arg2) != 0) {
        *(s32 *)(D_800D3098 + 0xF88) = 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EB484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB484.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB614.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB8C4.s")
typedef struct Game1188E0Event {
    u8 type;
    u8 pad1;
    s16 duration;
    u8 field4;
    u8 field5;
    s8 field6;
    u8 pad7;
} Game1188E0Event;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_150E83AC(void *, s16, u8, s32);
void *func_151D8868(void *, s32, u8, s32);
void *func_15164F0C(u8, u8, void *, u8, s32);
void func_151D3FF4(void *, u8, s32);
void func_151D5514(void *, u8, s32);
void *func_151541B8(void *, f32, f32, f32, f32, u8, s32);
extern f32 D_800A14FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EBC80 CURRENT (130) */
void func_150EBC80(void *arg0, u8 arg1, s32 arg2) {
    Game1188E0Vector position;
    f32 random;
    f32 step;
    Game1188E0Event event;
    f32 scale;
    u8 index;

    position.x = ((s16 *)arg0)[0];
    position.y = ((s16 *)arg0)[1];
    position.z = ((s16 *)arg0)[2];
    step = ((s16 *)arg0)[4] * 0.5f;
    func_150E83AC(&position, (s16)((func_150ADA20() % 101U) + 0x12C),
                  arg1, arg2);
    event.type = 1;
    event.duration = (func_150ADA20() % 21U) + 0xF;
    event.field4 = 0;
    event.field6 = -1;
    event.field5 = 1;
    func_151D8868(&event, 0, arg1, arg2);
    func_15164F0C(0, 0, 0, arg1, arg2);
    scale = D_800A14FC;
    index = 0;
    do {
        func_151D3FF4(&position, arg1, arg2);
        func_151D5514(&position, arg1, arg2);
        random = func_150ADA68();
        func_151541B8(&position, random * 4.0f + 12.0f, scale,
                     (f32)((func_150ADA20() % 56U) + 0xC8), 0.0f, arg1, arg2);
        index++;
        position.y += step;
    } while (index < 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EBC80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EBC80.s")
