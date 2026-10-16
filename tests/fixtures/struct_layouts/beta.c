/* Synthetic fixture: not copied project or ROM source. */
#include "types.h"

typedef struct {
    f32 posX;
    f32 y;
    f32 z;
} BetaVector;

typedef struct BetaCommand {
    u8 opcode;
    u8 pad1;
    u8 pad2[2];
    u32 data;
} BetaCommand;

typedef struct BetaPoint {
    f32 x, y, z;
    u8 pad[4];
} BetaPoint;

typedef struct BetaRoute {
    f32 x, y, z;
    s32 index;
} BetaRoute;

typedef struct BetaPair {
    s32 first, second;
} BetaPair;

void func_beta_local(void *arg0) {
    BetaVector copy;
    struct BetaRoute route;
    copy = *(BetaVector *)arg0;
    route.index = 0;
}

typedef struct GammaCommand {
    u8 opcode;
    u8 pad_1[3];
    u32 data;
} GammaCommand;
