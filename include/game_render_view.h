#ifndef CONKER_GAME_RENDER_VIEW_H
#define CONKER_GAME_RENDER_VIEW_H

#include "types.h"
#include "PR/gbi.h"

/* Render records have an independently indexed 0x180-byte allocation stride.
 * Bounds and projection fields are backed by matched game_476D0/game_138520
 * readers; normalization and matrices are backed by render-command users.
 */
typedef struct GameRenderView {
    u8 unknown00[4];
    f32 width;
    u8 unknown08[4];
    f32 field0C;
    f32 field10;
    u8 unknown14[0x10];
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
    f32 center_x;
    f32 center_y;
    u8 unknown3C[4];
    Vp viewports[2];
    u8 unknown60[4];
    f32 base_x;
    f32 base_y;
    f32 scale_x;
    f32 scale_y;
    f32 value_x;
    f32 value_y;
    u8 unknown7C[8];
    f32 field84;
    u8 unknown88[0x30];
    u16 normalization;
    u8 unknownBA[2];
    f32 matrix[16];
    u8 unknownFC[4];
    Mtx matrices[2];
} GameRenderView;

extern GameRenderView *D_800BE628;

#endif
