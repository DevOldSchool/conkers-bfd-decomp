#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_126BD0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
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

void func_150F9720(u8 arg0) {
    Game126BD0Message message;

    message.value = 0;
    message.selector = D_800A1C40[arg0].first;
    func_151494E0((void *)(s32)&message, 0x42);
    message.selector = D_800A1C40[arg0].second;
    func_151494E0((void *)(s32)&message, 0x42);
}
void func_150F9788(u8 *arg0) {

}

void func_150F9794(void *arg0) {
    func_150F9788(arg0);
    func_1514933C(arg0);
}

void func_150F97C0(void *arg0) {
    func_150F9788(arg0);
    func_15149368(arg0);
}
void *func_15102B38(s32, u8, s32, s32, f32 *, s16, u8, f32, s32, u8, s32, s16, u8, s32);
void func_15145EA4(s32 *, s32 *, s32, s32);
f32 func_150ADA68(void);
extern u8 D_80088B50;
extern s32 D_800A1C48;
extern s32 D_800A1C54;

void func_150F97EC(void *arg0, u8 arg1, s32 arg2) {
    s32 position[3];
    s32 matrix;
    f32 dimensions[2];
    s32 *source;
    s32 *target;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        return;
    }
    source = &D_800A1C48;
    target = position;
    matrix = *(s32 *)((u8 *)arg0 + 0x1D4) + (D_80088B50 << 6);
    func_15145EA4((s32 *)&source, (s32 *)&target, matrix, 1);
    dimensions[1] = (func_150ADA68() * 1) + 2.0f;
    dimensions[0] = (func_150ADA68() * 14.0f) + 28.0f;
    func_15102B38((s32)arg0, D_80088B50, (s32)&D_800A1C48, (s32)&D_800A1C54,
                   dimensions, (func_150ADA20() % 3U) + 4,
                   (func_150ADA20() % 156U) + 0x64,
                   (func_150ADA68() * 300.0f) + 400.0f,
                   (s32)position, 0xFF, 0, -1, arg1, arg2);
}
typedef struct Game126BD0Workspace {
    f32 vectors[5][3];
    u8 unused[0x3C];
} Game126BD0Workspace;

s32 func_150FF288(void *);
void func_150FF474(void *, void *, u8, s32);
s32 func_150FF6E0(void *, void *, void *, void *, void *, void *, s32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);

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
                          (lookup[2] << 6) + *(s32 *)(arg0 + 0x1D4), arg0,
                          1.0f, arg1, arg2);
            func_150FF474(workspace.vectors[3], workspace.vectors[4], arg1,
                          arg2);
        }
    }
}
