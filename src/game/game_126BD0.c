#include "types.h"

/*
 * Reviewed source unit: src/game/game_126BD0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F9720
 * - func_150F97EC
 * - func_150F9950
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game126BD0LookupRecord {
    u8 first;
    u8 second;
} Game126BD0LookupRecord;

typedef struct Game126BD0Message {
    s32 value;
    u8 selector;
} Game126BD0Message;

extern Game126BD0LookupRecord D_800A1C40[];
void func_151494E0(Game126BD0Message *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F9720 CURRENT (908) */
void func_150F9720(s32 arg0) {
    Game126BD0Message message;
    Game126BD0Message *message_ptr;
    Game126BD0LookupRecord *record;
    s32 index;

    index = arg0 & 0xFF;
    record = &D_800A1C40[index];
    message.value = 0;
    message_ptr = &message;
    message.selector = record->first;
    func_151494E0(message_ptr, 0x42);
    message.selector = record->second;
    func_151494E0(message_ptr, 0x42);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F9720 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_126BD0/func_150F9720.s")
void func_150F9788(s32 arg0) {

}
void func_1514933C(s32);

void func_150F9794(s32 arg0) {
    func_150F9788(arg0);
    func_1514933C(arg0);
}
void func_15149368(s32 arg0);

void func_150F97C0(s32 arg0) {
    func_150F9788(arg0);
    func_15149368(arg0);
}
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32,
                    s32, s32, s32, s32, s32);
void func_15145EA4(s32 *, s32 *, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern u8 D_80088B50;
extern s32 D_800A1C48;
extern s32 D_800A1C54;

typedef struct {
    u32 random1;
    u32 random2;
    s32 pad4C;
    s32 *target;
    s32 *source;
    f32 dimensions[2];
    s32 pad60;
    s32 position[3];
} Game126BD0_97ECLocals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F97EC CURRENT (1245) */
void func_150F97EC(void *arg0, u8 arg1, s32 arg2) {
    Game126BD0_97ECLocals locals;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        locals.source = &D_800A1C48;
        locals.target = locals.position;
        func_15145EA4((s32 *)&locals.source, (s32 *)&locals.target,
                      *(s32 *)((u8 *)arg0 + 0x1D4) + (D_80088B50 << 6), 1);
        locals.dimensions[1] = func_150ADA68() * 1.0f + 2.0f;
        locals.dimensions[0] = func_150ADA68() * 14.0f + 28.0f;
        locals.random1 = func_150ADA20();
        locals.random2 = func_150ADA20();
        func_15102B38((s32)arg0, D_80088B50,
                       (s32)&D_800A1C48, (s32)&D_800A1C54,
                       locals.dimensions, locals.random1 % 3U + 4,
                       locals.random2 % 156U + 100,
                       func_150ADA68() * 300.0f + 400.0f,
                       (s32)locals.position, 0xFF, 0, -1, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F97EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_126BD0/func_150F97EC.s")
typedef struct Game126BD0Workspace {
    f32 vectors[5][3];
    u8 unused[0x3C];
} Game126BD0Workspace;

s32 func_150FF288(void *);
void func_151D3F14(void *, u8, s32);
void func_150FF474(void *, void *, u8, s32);
s32 func_150FF6E0(void *, void *, void *, void *, void *, void *, s32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F9950 CURRENT (135) */
void func_150F9950(u8 *arg0, u8 arg1, s32 arg2) {
    Game126BD0Workspace workspace;
    u8 *lookup;

    lookup = (u8 *)func_150FF288(arg0);
    if (lookup != 0) {
        if (func_150FF6E0(workspace.vectors[4], workspace.vectors[3],
                          workspace.vectors[2], workspace.vectors[1],
                          workspace.vectors[0], arg0, (s32)lookup) != 0) {
            func_151D3F14(workspace.vectors[3], arg1, arg2);
            func_151D4408(workspace.vectors[2], workspace.vectors[1],
                          *(s32 *)(arg0 + 0x1D4) + (lookup[2] << 6), arg0,
                          1.0f, arg1, arg2);
            func_150FF474(workspace.vectors[3], workspace.vectors[4], arg1,
                          arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F9950 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_126BD0/func_150F9950.s")
