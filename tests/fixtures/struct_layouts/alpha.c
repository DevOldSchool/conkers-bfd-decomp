/* Synthetic fixture: not copied project or ROM source. */
#include "types.h"

typedef struct AlphaVec3 {
    f32 x;
    f32 y;
    f32 z;
} AlphaVec3;

typedef struct AlphaOwner {
    u8 pad0[0x10];
    AlphaVec3 position;
    struct {
        f32 x, y, z;
    } velocity;
} AlphaOwner;

typedef struct AlphaBits {
    u32 flag : 1;
} AlphaBits;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_deferred CURRENT (3) */
typedef struct DeadVec3 { f32 x, y, z; } DeadVec3;
void func_deferred(DeadVec3 *arg0) { }
#endif

void func_alpha_use(AlphaVec3 *arg0) {
    AlphaOwner *owner = (AlphaOwner *)arg0;
    owner->position.x = arg0->x;
}

void func_alpha_cast(void *arg0) {
    ((AlphaVec3 *)arg0)->y = 1.0f;
}

void func_alpha_shared(arg0, arg1)
SharedVec3 *arg0;
s32 arg1;
{
    arg0->z = arg1;
}

void func_alpha_unmatched(AlphaVec3 *arg0) {
    arg0->x = 0.0f;
}
