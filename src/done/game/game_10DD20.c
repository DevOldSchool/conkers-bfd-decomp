#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10DD20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 */

typedef struct Game10DD20Object {
    u8 pad00[0x14];
    Vec3f position;
} Game10DD20Object;
typedef struct Game10DD20Hit {
    f32 height;
    s16 vertices[3][3];
    u8 pad16[2];
    s32 owner;
    u8 flags, kind;
    u8 pad1E[2];
    void *record;
} Game10DD20Hit;

void func_10010630(u16, void *, s32, s16, u16);
s32 func_15046C80(void *, u16, f32, void *);
void func_1504715C(void *, void *);
f32 func_150ADA68(void);
void func_150E7FEC(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E83AC(void *, s16, u8, s32);
void *func_151541B8(void *, f32, f32, f32, f32, u8, s32);
struct Blood36C3CActor;
void func_15136C3C(struct Blood36C3CActor *, u8, u8, u8, u8, u8, u8, s32);
void func_151D40D4(void *, s32, s32, s32, s32, s32, s32, s32);
void func_151D5334(void *, f32, f32, f32, u8, u8, s32);
void func_151D5514(void *, u8, s32);
extern u8 D_800C35EA;

void func_150E0870(Game10DD20Object *arg0, u8 arg1, s32 arg2) {
    Vec3f origin;
    Vec3f impact;
    u8 hitValid;

    if (arg0 != NULL) {
        if (D_800C35EA != 1) {
            func_10010630(0x2BB, arg0, 0x7FFF, 0x3E8, 0x7D0);
            func_10010630(0x2BA, arg0, 0x7FFF, 0x3E8, 0x7D0);
        }
        origin.x = arg0->position.x;
        origin.y = arg0->position.y + 20.0f;
        origin.z = arg0->position.z;
        hitValid = 0;
        {
            Vec3f top;
            Game10DD20Hit hit;

            top.x = origin.x;
            top.y = origin.y + 100.0f;
            top.z = origin.z;
            func_1504715C(&hit, arg0);
            if (func_15046C80(&top, 0, origin.y - 200.0f, &hit) && (hit.flags & 1)) {
                impact.x = top.x;
                hitValid = 1;
                impact.y = hit.height;
                impact.z = top.z;
                func_150E7FEC(func_150ADA68() * 125.0f + 204.0f, (func_150ADA20() % 101U + 0x9B) & 0xFF,
                              hit.vertices, &impact, func_150ADA20() % 302U + 500, 0, 1, 0, 0, 0, arg1, 0);
            }
        }
        func_151D5404(&origin, 506.0f, 1013.0f, 0.0009871669f, 15, 20, arg1, arg2);
        func_151D5334(&origin, 506.0f, 1013.0f, 0.0009871669f, 5, arg1, arg2);
        func_151D5514(&origin, arg1, arg2);
        func_151D3FF4(&origin.x, arg1, arg2);
        func_150E83AC(hitValid ? &impact : &origin, func_150ADA20() % 62U + 0x78, arg1, arg2);
        func_151541B8(&origin, func_150ADA68() * 4.0f + 12.0f, 1.6409999f,
                      func_150ADA20() % 56U + 200, 0.0f, arg1, arg2);
        func_15136C3C((struct Blood36C3CActor *)arg0, 1, 1, 1, 1, 0, arg1, arg2);
        func_151D40D4(&origin, 0, (s32)arg0, (s32)arg0, 0, 0x16, 0x15, 0);
    }
}
