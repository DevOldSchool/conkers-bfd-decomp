#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3DB80.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_small_units_3D6F0_3FC30.md
 */

typedef struct Game3DB80Object {
    s16 field_0;
    u8 pad2[2];
    s16 field_4;
} Game3DB80Object;

/* The raw copy spans four consecutive words at sp+0x38..sp+0x47. */
typedef struct Game3DB80Payload {
    Game3DB80Object *object;
    f32 field4;
    s32 field8;
    f32 fieldC;
} Game3DB80Payload;

void *func_10022EC0(void *, const void *, u32);
void func_1510F800(s32);
s32 func_1510FD20(s16, s16, Game3DB80Object *);
f32 func_15144598(Game3DB80Object *);

s32 func_150106D0(Game3DB80Object *arg0) {
    Game3DB80Payload payload;
    s32 temp_v0;
    void *temp_v0_2;

    payload.object = arg0;
    payload.field4 = func_15144598(arg0);
    payload.fieldC = 0.0f;
    func_1510F800(0);
    temp_v0 = func_1510FD20(arg0->field_0, arg0->field_4, arg0);
    payload.field8 = temp_v0;
    if (temp_v0 == 0) {
        return 1;
    }
    temp_v0_2 = func_15149130(0x12C, -1, 0x59, -1, 0, 0, 0x10, 0xFF, 0);
    if (temp_v0_2 != 0) {
        func_10022EC0((u8 *)temp_v0_2 + 0x28, &payload, sizeof(payload));
    }
    return 1;
}
